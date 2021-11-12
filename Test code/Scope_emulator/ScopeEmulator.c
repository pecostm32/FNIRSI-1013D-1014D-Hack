#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include "xlibfunctions.h"

#include "scopeemulator.h"

#include "armthread.h"
#include "armv5tl.h"

#include "resources.h"
#include "touchpanel.h"  //All the panel resources are defined in this file. Needs to be the last include file

//----------------------------------------------------------------------------------------------------------------------------------

int DrawScopePanel(tagXlibContext *xc);

//----------------------------------------------------------------------------------------------------------------------------------
//For touch panel control
//                             xc,            action,   previous, left, right, top, bottom, move, down,   up, out,    xpos, ypos, width, height 
tagTouchPanel touchpanel = { NULL, touchpanelhandler, {     NULL,    0,     0,   0,      0, NULL, NULL, NULL, NULL },   60,   60,   800,    480, 0 };

//Set pointer to last mouse range for scanning
MouseRange *scopemouseranges = &touchpanel.mouse;

//----------------------------------------------------------------------------------------------------------------------------------
//Pointer to the touch panel driver data 
TOUCH_PANEL_DATA *global_touchpanel;

//----------------------------------------------------------------------------------------------------------------------------------

#define DESIGN_WIDTH       920
#define DESIGN_HEIGHT      630

//----------------------------------------------------------------------------------------------------------------------------------

//ID's for communication between the threads and the main window
Window main_window_id = 0;
Window display_msg_id = 0;

//Signal from arm emulator window thread to allow error free stop
extern int arm_emulator_still_running;

//----------------------------------------------------------------------------------------------------------------------------------

int main(int argc,char **argv)
{
  //The arm core needs to be readable from here to be able to get to the display data
  //Setup a key for getting the shared memory
  key_t key = SHARED_MEMORY_KEY;
 
  //Get a handle to the shared memory  sizeof(ARMV5TL_CORE) 0666 | 
  int shmid = shmget(key, sizeof(ARMV5TL_CORE), 0666 | IPC_CREAT); 

  //Check on error shmid == -1.
  if(shmid == -1)
  {
    //On error exit
    return(-1);
  }
  
  //Attach to the shared memory
  PARMV5TL_CORE parm_core = (PARMV5TL_CORE)shmat(shmid, (void*)0, 0);
  
  
  //Setup the pointer for the touch panel driver connection with the mouse system
  global_touchpanel = &parm_core->touchpaneldata;
  
  //Basic setup for the xlib system  
  //Since multi threads are used to control display objects initialize the xlib for it
  XInitThreads();
  
	Display *display = XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window root = RootWindow(display, screen_num);
	Window win = XCreateSimpleWindow(display, root, 0, 0, DESIGN_WIDTH + BORDER_SIZE_2, DESIGN_HEIGHT + BORDER_SIZE_2, 2, BlackPixel(display, screen_num), WhitePixel(display, screen_num));
  
	XMapWindow(display, win);
  
  //For mouse handling only button press and release are needed in combination with motion which is used for controlling the knobs
	XSelectInput(display, win, ExposureMask | KeyPressMask | ButtonPressMask | ButtonReleaseMask | PointerMotionMask );
  
	GC gc = XCreateGC(display, win, 0, NULL);
  
  unsigned int width;	           //width and height for the new window.
  unsigned int height;
  
  unsigned int x,y;
  
  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  Atom WM_PROTOCOLS = XInternAtom(display, "WM_PROTOCOLS", False);
  XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);
  
  //Create atom for the display messages
  display_msg_id = XInternAtom(display, "SCOPE_DISPLAY_MESSAGE", False); 

  //Set the window id for message sending
  main_window_id = win;
  
	XEvent event;

  double fsize;
  
  int rflag = 1;

  tagXlibContext xc;

  int numsizes;  
  XRRScreenSize *scrsize;
  
  //Get the size of the primary monitor
  scrsize = XRRSizes(display, screen_num, &numsizes);
  
  //For calculations take of a border of 5 pixels for each side
  width  = (scrsize->width - BORDER_SIZE_2) * 0.95;
  height = scrsize->height - BORDER_SIZE_2;
   
  //Determine the scaler based on the width
  xc.scaler = (float)width / (float)DESIGN_WIDTH;

  //See if it scaled fits for the height. If not determine the scaler based on the height
  if((DESIGN_HEIGHT * xc.scaler) > height)
    xc.scaler = (float)height / (float)DESIGN_HEIGHT;
  
  //Check if screen is larger than the desired size
  if(xc.scaler > 1.0)
  {
    //If so keep the scale on 1
    xc.scaler = 1.0;
  }

  //Calculate the new width and height
  width = (DESIGN_WIDTH * xc.scaler) + BORDER_SIZE_2;
  height = (DESIGN_HEIGHT * xc.scaler) + BORDER_SIZE_2;
  
  //Calculate a nice position on the screen
  x = 1350;
  y = 50;
  
  //Set the window to the new position and dimensions
  XMoveResizeWindow(display, win, x, y, width, height);
  
  //Setup the data for the drawing functions
  xc.screen_num = screen_num;
  xc.root = root;
  xc.win = win;
  xc.display = display;
  xc.gc = gc;
  
  xc.visual = DefaultVisual(display, screen_num);
  xc.cmap  = DefaultColormap(display, screen_num);
    
  //Create all the used fonts
  fsize = 30 * xc.scaler;
  xc.font[0] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 16 * xc.scaler;
  xc.font[1] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial Narrow", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);
  
  //Create the used font colors
  rflag = XftColorAllocName(display, xc.visual, xc.cmap, TextColor, &xc.color[0]);

  rflag = XftColorAllocName(display, xc.visual, xc.cmap, LogoColor, &xc.color[1]);
  
  xc.draw = XftDrawCreate(display, win, xc.visual, xc.cmap);

  //Image for the scope display
  x = BORDER_SIZE + (60 * xc.scaler);
  y = BORDER_SIZE + (60 * xc.scaler);
  width = 800 * xc.scaler;
  height = 480 * xc.scaler;
  
  //Setup the image based on a capture of the screen
  XImage *scopedisplay = XGetImage(display, win, x, y, width, height, 0, ZPixmap);
  
  //Start the arm processing core
  startarmcore();
  
  //Start the arm emulator window thread
  startarmemulator();
  
  //Keep running until window is destroyed
	while(rflag)
	{
		XNextEvent(display, &event);
		switch(event.type)
		{
			case Expose:
        //Setup the screen
        DrawScopePanel(&xc);
				break;
        
			case KeyPress:
        
				if(event.xkey.keycode == XKeysymToKeycode(display,XK_Escape))
				{
					rflag = 0;
				}
        break;
        
      case ButtonPress:
        //Call mouse handling function down()
        MouseDown(&event);
        break;
        
      case ButtonRelease:
        //Call mouse handling function up()
        MouseUp(scopemouseranges, &event);
        break;
        
      case MotionNotify:
        //Call mouse handling function move()
        MouseMove(scopemouseranges, &event);
        break;
        
      case ClientMessage:
        if((event.xclient.message_type == WM_PROTOCOLS) && (event.xclient.data.l[0] == WM_DELETE_WINDOW))
        {
					rflag = 0;
        }
        else if(event.xclient.message_type == display_msg_id)
        {
          //Need some scaling algo here to match the scope display to the screen display. The scaling will mostly be one but just in case
          int ix,iy,idx;

          uint16_t *dptr = (uint16_t *)&parm_core->dram[parm_core->displaymemory.startaddress].m_16bit[0];

          for(iy=0;iy<scopedisplay->height;iy++)
          {
            idx = iy * scopedisplay->bytes_per_line;

            for(ix=0;ix<scopedisplay->width;ix++)
            {
              scopedisplay->data[idx + 0] = (unsigned char)(*dptr << 3) & 0x00F8;   //Blue
              scopedisplay->data[idx + 1] = (unsigned char)(*dptr >> 3) & 0x00FC;   //Green
              scopedisplay->data[idx + 2] = (unsigned char)(*dptr >> 8) & 0x00F8;   //Red

              dptr++;

              idx += (scopedisplay->bits_per_pixel / 8);
            }
          }
          
          //Draw the image on the screen
          XPutImage(display, win, gc, scopedisplay, 0, 0, x, y, width, height);
        }
        break;
		}
	}
  
  //Stop the arm emulator window thread from running
  stoparmemulator();

  //Need to wait on the emulator window to stop
  //Otherwise an segmentation fault occurs on core data no longer available
  while(arm_emulator_still_running);
  
  //Stop the arm processing core
  stoparmcore();
  
  //Cleanup on close  
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[0]);
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[1]);
  XftDrawDestroy(xc.draw);
  
  //Signal window no longer available for messages
  main_window_id = 0;
  display_msg_id = 0;
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
  //detach from shared memory  
  shmdt(parm_core);   

  //destroy the shared memory 
  shmctl(shmid, IPC_RMID, NULL); 
  
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Function for drawing the frontpanel and all the objects on it
int DrawScopePanel(tagXlibContext *xc)
{
  //Draw the scope outline
  DrawFillRoundedRect(xc, 0, 0, 20, 920, 630, ScopeBorderColor, ScopeOuterLineColor, 1);
  
  //Draw the scope glass panel 
  DrawFillRoundedRect(xc, 8, 8, 16, 904, 614, ScopeBlackColor, ScopeBlackColor, 1);

  //Draw the display  
  DrawFillRect(xc, 60, 60, 800, 480, ScopeDisplayColor, ScopeDisplayColor, 1);

  //Setup the touchpanel
  TouchPanelSetup(xc, &touchpanel);
  
  //Place the front panels text  
  PlaceText(xc, 70, 600, "TABLET", 0, 0, ALIGN_TEXT_LEFT);
  PlaceText(xc, 250, 600, "OSCILLOSCOPE", 1, 0, ALIGN_TEXT_LEFT);

  PlaceText(xc, 780, 575, "100MHZ", 1, 0, ALIGN_TEXT_LEFT);
  PlaceText(xc, 780, 600, "1 GSa/s", 1, 0, ALIGN_TEXT_LEFT);

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Function to be called from other threads to send a message to the scope emulator window
void updatedisplaymessage()
{
  Display *display;
  XEvent   event;
 
  if(main_window_id && display_msg_id)
  {
    display = XOpenDisplay(NULL);
    
    event.xclient.type = ClientMessage;
    event.xclient.display = display;
    event.xclient.window = main_window_id;
    event.xclient.message_type = display_msg_id;
    event.xclient.format = 32;

    XSendEvent(display, main_window_id, False, NoEventMask, &event);
  
    XCloseDisplay(display);
  }
}

//-----------------------------------------------------------------------------------------------------

#define CalcCoordX(x) (BORDER_SIZE + ((touchpanel->xpos + (x)) * xc->scaler))
#define CalcCoordY(y) (BORDER_SIZE + ((touchpanel->ypos + (y)) * xc->scaler))

void touchpanelhandler(MouseEvent *event)
{
  XMotionEvent  *motionevent = &event->event->xmotion;
  tagTouchPanel *touchpanel = event->data;
  tagXlibContext *xc = touchpanel->xc;
  
  int x = motionevent->x - CalcCoordX(0);
  int y = motionevent->y - CalcCoordY(0);
  
  //The scope expects the touch data to run from 0 - 1024 for the x direction
  x = (x * 128) / 100;
  
  //For the y direction it expects it to run from 0 to 600
  y = (y * 100) / 80;

  //Let the touch panel driver know if the mouse is down
  global_touchpanel->mouse_down = touchpanel->state;
  
  //Touch panel data only uses the low 0x1FF part of the register addresses
  //On address 0x8150 is the low byte of the x coordinate
  global_touchpanel->panel_data[0x150] = x & 0xFF;
  global_touchpanel->panel_data[0x151] = (x >> 8) & 0xFF;

  //On address 0x8152 is the low byte of the y coordinate
  global_touchpanel->panel_data[0x152] = y & 0xFF;
  global_touchpanel->panel_data[0x153] = (y >> 8) & 0xFF;
}

//-----------------------------------------------------------------------------------------------------
    