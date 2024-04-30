#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>

#include <errno.h>

#include "oscilloscope_emulator.h"
#include "mousehandling.h"
#include "rotary_dial.h"
#include "buttons.h"

#include "armv5tl.h"

#include "user_interface_functions.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define DESIGN_WIDTH       1550   //31 cm 
#define DESIGN_HEIGHT       675   //13.5 cm

#define ScopeDisplayColor       0x161616

//----------------------------------------------------------------------------------------------------------------------------------
//Needed to make it compile because for some reason usleep is not defined or visible in the standard includes
extern int usleep (__useconds_t __useconds);

//----------------------------------------------------------------------------------------------------------------------------------
// Line color is minus 0x1B2637
// Down color is minus 0x080C11

tagButtonColors bluebutton =
{
  0x707070,            //Button panel cutout color
  0x137092,            //Button line color
  0x2E96C9,            //Button up body color
  0x268AB8             //Button down body color
};

tagButtonColors darkbluebutton =
{
  0x707070,            //Button panel cutout color
  0x082165,            //Button line color
  0x23479C,            //Button up body color
  0x1B3B8B             //Button down body color
};

tagButtonColors yellowbutton =
{
  0x808080,            //Button panel cutout color
  0xDCC03F,            //Button line color
  0xF7E676,            //Button up body color
  0xEFDA65             //Button down body color
};

tagButtonColors greenbutton =
{
  0x707070,            //Button panel cutout color
  0x5B8EF7,            //Button line color
  0x76B52E,            //Button up body color
  0x6EA91D             //Button down body color
};

tagButtonColors redbutton =
{
  0x707070,            //Button panel cutout color
  0xBF0000,            //Button line color
  0xDB1A2C,            //Button up body color
  0xD30E1B             //Button down body color
};

tagButtonColors whitebutton =
{
  0x909090,            //Button panel cutout color
  0xE4D9C8,            //Button line color
  0xFFFFFF,            //Button up body color
  0xF7F3EE             //Button down body color
};

tagButtonColors greybutton =
{
  0x303030,            //Button panel cutout color
  0x807860,            //Button line color
  0x9B9E97,            //Button up body color
  0x939286             //Button down body color
};

//----------------------------------------------------------------------------------------------------------------------------------

tagRotaryDialSettings smallrotary =
{
      50.0,            //Size
       7.5,            //X displacement
       3.0,            //Y displacement
       8.6,            //Ring X displacement
       7.6,            //Ring Y displacement
       7.4,            //Ridge radius
      16.0,            //Ridge length
       4.8,            //Ridge width
  0xF4F4F4,            //Cap color
  0xE8E8E8,            //Body color
  0xFFFFFF,            //Line color
  0xFFFFFF,            //Ridge top color
  0xC0C0C0,            //Ridge middle color
  0x000000             //Ridge bottom color
};

tagRotaryDialSettings bigrotary =
{
      65.0,            //Size
       9.7,            //X displacement
       3.9,            //Y displacement
      11.2,            //Ring X displacement
       9.9,            //Ring Y displacement
       9.6,            //Ridge radius
      20.8,            //Ridge length
       6.4,            //Ridge width
  0xF4F4F4,            //Cap color
  0xE8E8E8,            //Body color
  0xFFFFFF,            //Line color
  0xFFFFFF,            //Ridge top color
  0xC0C0C0,            //Ridge middle color
  0x000000             //Ridge bottom color
};

//----------------------------------------------------------------------------------------------------------------------------------

//All the rotary dials on the front panel
tagRotaryDial rotarydials[] =
{
  //Mouserange set here to make a linked list. Search for object under mouse pointer needs to be done from last to first based on previous pointer
  //xc is set during setup of the object
  //  xc,           action,   previous, left, right, top, bottom, move, down,   up,  out,                xpos, ypos, position
  { NULL,       selectdial, {                  NULL,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1028,   70,        0, &smallrotary },
  { NULL,      ch1position, { &rotarydials[0].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1028,  265,        0, &smallrotary },
  { NULL,      ch2position, { &rotarydials[1].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1168,  265,        0, &smallrotary },
  { NULL,  triggerposition, { &rotarydials[2].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1308,  265,        0, &smallrotary },
  { NULL,     triggerlevel, { &rotarydials[3].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1448,  265,        0, &smallrotary },
  { NULL,   ch1sensitivity, { &rotarydials[4].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1022,  475,        0, &bigrotary   },
  { NULL,   ch2sensitivity, { &rotarydials[5].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1162,  475,        0, &bigrotary   },
  { NULL,       timeperdiv, { &rotarydials[6].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL }, 1302,  475,        0, &bigrotary   },
};

//All the buttons on the front panel
tagButton buttons[] = 
{
  //Mouserange set here to make a linked list. Search for object under mouse pointer needs to be done from last to first based on previous pointer
  //xc is set during setup of the object
  //  xc,                 action,                previous, left, right, top, bottom, move, down,   up,  out,                     type,    xpos,    ypos, width, height, radius
  { NULL,            powerbutton, { &rotarydials[7].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,      60,     610,    80,     35,      2, 0, "POWER",     2, 1, &bluebutton,     PanelColor },
  { NULL,           selectbutton, {     &buttons[0].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     400,     600,    50,     25,      2, 0, "SEL",       3, 0, &whitebutton,    PanelColor },
  { NULL,        selectallbutton, {     &buttons[1].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     490,     600,    50,     25,      2, 0, "SEL ALL",   3, 0, &whitebutton,    PanelColor },
  { NULL,           deletebutton, {     &buttons[2].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     580,     600,    50,     25,      2, 0, "DEL",       3, 0, &whitebutton,    PanelColor },
  { NULL,             lastbutton, {     &buttons[3].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     670,     600,    50,     25,      2, 0, "LAST",      3, 0, &whitebutton,    PanelColor },
  { NULL,             nextbutton, {     &buttons[4].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     760,     600,    50,     25,      2, 0, "NEXT",      3, 0, &whitebutton,    PanelColor },
  { NULL,               f1button, {     &buttons[5].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     904,     105,    50,     25,      2, 0, "F1",        3, 0, &greybutton,     PanelColor },
  { NULL,               f2button, {     &buttons[6].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     904,     187,    50,     25,      2, 0, "F2",        3, 0, &greybutton,     PanelColor },
  { NULL,               f3button, {     &buttons[7].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     904,     269,    50,     25,      2, 0, "F3",        3, 0, &greybutton,     PanelColor },
  { NULL,               f4button, {     &buttons[8].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     904,     351,    50,     25,      2, 0, "F4",        3, 0, &greybutton,     PanelColor },
  { NULL,               f5button, {     &buttons[9].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     904,     433,    50,     25,      2, 0, "F5",        3, 0, &greybutton,     PanelColor },
  { NULL,               f6button, {    &buttons[10].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,     904,     515,    50,     25,      2, 0, "F6",        3, 0, &greybutton,     PanelColor },
  { NULL,        generatorbutton, {    &buttons[11].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_DIAMOND,          904,     600,    50,     25,      2, 0, "GEN",       3, 1, &darkbluebutton, PanelColor },
  { NULL,             slowbutton, {    &buttons[12].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1035,     175,    50,     25,      2, 0, "SLOW",      2, 0, &greybutton,     PanelColor },

  { NULL,             leftbutton, {    &buttons[13].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ARROW_LEFT,      1100,     120,    25,     35,      2, 0, "",          2, 0, &greybutton,     PanelColor },
  { NULL,               upbutton, {    &buttons[14].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ARROW_UP,        1150,      75,    35,     25,      2, 0, "",          2, 0, &greybutton,     PanelColor },
  { NULL,               okbutton, {    &buttons[15].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1150,     120,    35,     35,      4, 0, "OK",        2, 0, &greybutton,     PanelColor },
  { NULL,             downbutton, {    &buttons[16].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ARROW_DOWN,      1150,     175,    35,     25,      2, 0, "",          2, 0, &greybutton,     PanelColor },
  { NULL,            rightbutton, {    &buttons[17].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ARROW_RIGHT,     1210,     120,    25,     35,      2, 0, "",          2, 0, &greybutton,     PanelColor },
  
  { NULL, horizontalcursorbutton, {    &buttons[18].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1260,      75,    50,     25,      2, 0, "H CUR",     2, 0, &greybutton,     PanelColor },
  { NULL,   verticalcursorbutton, {    &buttons[19].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1260,     175,    50,     25,      2, 0, "V CUR",     2, 0, &greybutton,     PanelColor },
  { NULL,             menubutton, {    &buttons[20].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1350,      75,    50,     25,      2, 0, "MENU",      2, 0, &greybutton,     PanelColor },
  { NULL,      savepicturebutton, {    &buttons[21].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1350,     125,    50,     25,      2, 0, "S PIC",     2, 0, &greybutton,     PanelColor },
  { NULL,         savewavebutton, {    &buttons[22].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1350,     175,    50,     25,      2, 0, "S WAV",     2, 0, &greybutton,     PanelColor },

  { NULL,          runstopbutton, {    &buttons[23].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ANGLES_TOP,      1455,      75,    55,     50,      2, 0, "RUN",       2, 1, &redbutton,      PanelColor },
  { NULL,             autobutton, {    &buttons[24].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ANGLES_BOTTOM,   1455,     150,    55,     50,      2, 0, "AUTO",      2, 1, &bluebutton,     PanelColor },
  
  { NULL,        ch1enablebutton, {    &buttons[25].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1035,     360,    50,     25,     10, 0, "CH1",       2, 0, &yellowbutton,   0xEAEBE5 },
  { NULL,        ch1configbutton, {    &buttons[26].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1035,     430,    50,     25,     10, 0, "CONF",      2, 0, &yellowbutton,   0xEAEBE5 },
  { NULL,        ch2enablebutton, {    &buttons[27].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1175,     360,    50,     25,     10, 0, "CH2",       2, 0, &bluebutton,     0xEAEBE5 },
  { NULL,        ch2configbutton, {    &buttons[28].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1175,     430,    50,     25,     10, 0, "CONF",      2, 0, &bluebutton,     0xEAEBE5 },
  { NULL,           originbutton, {    &buttons[29].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1315,     395,    50,     25,     10, 0, "ORIG",      2, 0, &greenbutton,    0xEAEBE5 },
  { NULL,      triggermodebutton, {    &buttons[30].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1455,     375,    50,     25,      2, 0, "MODE",      2, 0, &greybutton,     0xEAEBE5 },
  { NULL,      triggeredgebutton, {    &buttons[31].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1455,     435,    50,     25,      2, 0, "EDGE",      2, 0, &greybutton,     0xEAEBE5 },
  { NULL,   triggerchannelbutton, {    &buttons[32].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1455,     500,    50,     25,      2, 0, "CHX",       2, 0, &greybutton,     0xEAEBE5 },
  { NULL, trigger50percentbutton, {    &buttons[33].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },    BUTTON_ROUNDED_RECT,    1455,     580,    50,     25,      2, 0, "50%",       2, 0, &greybutton,     0xEAEBE5 },
};

//Set pointer to last mouse range for scanning
MouseRange *scopemouseranges = &buttons[34].mouse;

//----------------------------------------------------------------------------------------------------------------------------------

//ID's for communication between the threads and the main window
Window main_window_id = 0;
Window display_msg_id = 0;

//----------------------------------------------------------------------------------------------------------------------------------

//Coupling with the data of the arm core process
extern ARMV5TL_CORE arm_core;

//----------------------------------------------------------------------------------------------------------------------------------

int main(int argc,char **argv)
{
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

  //Setup variables for event handling
  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  Atom WM_PROTOCOLS = XInternAtom(display, "WM_PROTOCOLS", False);
  
  //Attach the delete window to the protocols
  XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);

  //Create atom for the display messages
  display_msg_id = XInternAtom(display, "SCOPE_DISPLAY_MESSAGE", False); 

  //Set the window id for message sending
  main_window_id = win;
  
  
  unsigned int width;	           //width and height for the new window.
  unsigned int height;
  
  unsigned int x,y;
  
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
  x = 200;
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
  fsize = 22 * xc.scaler;
  xc.font[0] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 12.5 * xc.scaler;
  xc.font[1] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);
  
  fsize = 11 * xc.scaler;
  xc.font[2] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial Narrow", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 8 * xc.scaler;
  xc.font[3] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial Narrow", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);
  
  //Create the used font colors
  rflag = XftColorAllocName(display, xc.visual, xc.cmap, "#000000", &xc.color[0]);  //Black text

  rflag = XftColorAllocName(display, xc.visual, xc.cmap, "#FFFFFF", &xc.color[1]);  //White text
  
  xc.draw = XftDrawCreate(display, win, xc.visual, xc.cmap);

  //Need to wait for server to be ready!! ??
  usleep(50000);
  
  //Image for the scope display
  x = BORDER_SIZE + (40 * xc.scaler);
  y = BORDER_SIZE + (80 * xc.scaler);
  width = 800 * xc.scaler;
  height = 480 * xc.scaler;
  
  //Setup the image based on a capture of the screen
  XImage *scopedisplay = XGetImage(display, win, x, y, width, height, 0, ZPixmap);
    
  //Start the arm processing core
  startarmcore();
  
  //Keep running until window is destroyed
	while(rflag)
	{
    //Check if there are events and handle them if so
    while(XPending(display))
    {
      //Get the next event
      XNextEvent(display, &event);
      
      //Handle it based on its type
      switch(event.type)
      {
        case Expose:
          //Setup the screen
          DrawOscilloscopeFrontPanel(&xc);
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

            u_int16_t *dptr = (u_int16_t *)&arm_core.dram[arm_core.displaymemory.startaddress].m_16bit[0];

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

    //Process communication to scope backend here
	}
  
  //Stop the arm processing core
  stoparmcore();

  //Cleanup on close  
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[0]);
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[1]);
  XftDrawDestroy(xc.draw);
  
  //Signal window no longer available for messages
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Function for drawing the front panel and all the objects on it

void DrawOscilloscopeFrontPanel(tagXlibContext *xc)
{
  int i,n;
  int edgecolor;
  int coloradd;
  int x,y,w,h,r;
  
  //Simpler design with a small rounded edge
  
  
  //From right edge 5mm inwards and from top 6.5mm inwards
  //In corner 2mm from top
  //top line 73mm long
  //right line 126mm long

  //Draw the signal generator window outline
  DrawFillRoundedRect(xc, 0, 0, 18, DESIGN_WIDTH, DESIGN_HEIGHT, PanelColor, BorderColor, 1);

  
  //Setup for drawing the outside edge of the scope front panel
  x = 1;
  y = 1;
  r = 17;
  w = DESIGN_WIDTH - 2;
  h = DESIGN_HEIGHT - 2;

  //Setup color adding and start value
  coloradd  = 0x020202;
  edgecolor = BorderColor + 0x020202;

  //Draw the oudside edge of the scope front panel
  for(i=0;i<10;i++)
  {
    DrawRoundedRect(xc, x, y, r, w, h, edgecolor, 1);

    h -= 2;
    w -= 2;
    r -= 1;
    x += 1;
    y += 1;

    edgecolor += coloradd;
  }
  
  //Show the brand name in the top left corner on a yellow back ground
  FillRect(xc, 25, 12, 115, 35, 0xEDCD3C);
  PlaceText(xc, 32, 40, "FNIRSI", 0, 0, ALIGN_TEXT_LEFT);
  
  //Show the model name and some specifications in the top right corner
  FillRect(xc, DESIGN_WIDTH - 400, 12, 375, 35, 0x989D99);                        //A greyis color
  FillRect(xc, DESIGN_WIDTH - 390, 15, 120, 19, 0xEDCD3C);                        //Some yellow color
  PlaceText(xc, DESIGN_WIDTH - 385, 30, "FNIRSI-1014D", 1, 0, ALIGN_TEXT_LEFT);   //Black text
  PlaceText(xc, DESIGN_WIDTH - 90, 27, "100MHz", 2, 0, ALIGN_TEXT_LEFT);
  PlaceText(xc, DESIGN_WIDTH - 90, 41, "1 GSa/s", 2, 0, ALIGN_TEXT_LEFT);
  PlaceText(xc, DESIGN_WIDTH - 390, 43, "Dual channel digital storage oscilloscope", 3, 0, ALIGN_TEXT_LEFT);

  //Setup color adding variable
  coloradd  = 0x030303;
  edgecolor = 0xE1E1E1;

  //Setup for drawing the inside edge of the scope screen
  x = 40;
  y = 80;
  w = 802;
  h = 482;

  //Draw the inside edge of the scope screen
  for(i=0;i<10;i++)
  {
    DrawRect(xc, x, y, w, h, edgecolor, 1);

    h += 2;
    w += 2;
    x -= 1;
    y -= 1;

    edgecolor += coloradd;
  }
  
  //Draw the display  
  DrawFillRect(xc, 41, 81, 800, 480, ScopeDisplayColor, ScopeDisplayColor, 1);

  //Setup color adding variable
  coloradd  = 0x030303;
  edgecolor = 0xD5D5D5;
  
  //Setup for drawing the raised panel for the screen side buttons
  x = 875;
  y = 85;
  r = 24;
  w = 110;
  h = 475;

  //Draw the raised panel for the screen side buttons
  for(i=0;i<14;i++)
  {
    DrawRoundedRect(xc, x, y, r, w, h, edgecolor, 1);

    h -= 2;
    w -= 2;
    r -= 1;
    x += 1;
    y += 1;

    edgecolor += coloradd;
  }

  //Draw channel and trigger settings field
  DrawFillRoundedRect(xc, 1000, 225, 8, 530, 420, 0xEAEBE5, 0xF2F3F0, 1);
  DrawRoundedRect(xc, 1002, 227, 6, 260, 330, 0x72757F, 2);
  DrawRoundedRect(xc, 1280, 227, 6, 126, 330, 0x72757F, 2);
  DrawRoundedRect(xc, 1424, 227, 6, 104, 330, 0x72757F, 2);
  DrawRoundedRect(xc, 1424, 566, 6, 104, 56, 0x72757F, 2);

  //Setup all the rotary dials
  for(i=0;i<sizeof(rotarydials) / sizeof(tagRotaryDial);i++)
    RotaryDialSetup(xc, &rotarydials[i]);
  
  //Setup all the buttons
  for(i=0;i<(sizeof(buttons) / sizeof(tagButton));i++)
    ButtonSetup(xc, &buttons[i]);
  
 
}

//----------------------------------------------------------------------------------------------------------------------------------
//Function to be called from other threads to send a message to the oscilloscope emulator window
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
