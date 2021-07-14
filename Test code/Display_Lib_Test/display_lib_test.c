#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xlibfunctions.h"
#include "font_structs.h"
#include "types.h"
#include "display_lib.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define DESIGN_WIDTH       820
#define DESIGN_HEIGHT      500

//----------------------------------------------------------------------------------------------------------------------------------

extern FONTDATA font_0;
extern FONTDATA font_2;

DISPLAYDATA displaydata;

//----------------------------------------------------------------------------------------------------------------------------------

unsigned short displaybuffer[800 * 480];

//----------------------------------------------------------------------------------------------------------------------------------

int main(int argc,char **argv)
{
  //Basic setup for the xlib system  
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
  x = 150;
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

  //Image for the scope display
  x = BORDER_SIZE + (10 * xc.scaler);
  y = BORDER_SIZE + (10 * xc.scaler);
  width = 800 * xc.scaler;
  height = 480 * xc.scaler;
  
  //Setup the image based on a capture of the screen
  XImage *scopedisplay = XGetImage(display, win, x, y, width, height, 0, ZPixmap);
  
  //--------------------------------------------------------------------------------------------------------------------------------
  //Test section
  
  display_set_bg_color(&displaydata, 0x00000000);
  display_set_dimensions(&displaydata, 800, 480);
  display_set_screen_buffer(&displaydata, displaybuffer);

  display_set_fg_color(&displaydata, 0x00AA7733);
  display_draw_arc(&displaydata, 100, 100, 30, 600, 1900, 0);

  display_draw_line(&displaydata, 100, 80, 300, 40);

  display_draw_line(&displaydata, 350, 180, 150, 60);
  display_draw_line(&displaydata, 200, 40, 400, 40);
  display_draw_line(&displaydata, 750, 140, 700, 240);

  display_draw_line(&displaydata, 450, 120, 450, 340);
 
  display_set_fg_color(&displaydata, 0x00FF0000);
  
  display_draw_horz_line(&displaydata, 200, 30, 720);

  display_draw_horz_line(&displaydata, 300, 920, 120);

  display_draw_horz_line(&displaydata, 500, 60, 920);
  
  
  display_set_fg_color(&displaydata, 0x0000FF00);
  
  
  display_draw_vert_line(&displaydata, 670, 10, 340);
 
  display_set_fg_color(&displaydata, 0x004488AA);


  display_draw_arc(&displaydata, 240, 240, 30, 2100, 1100, 0);
  display_draw_arc(&displaydata, 240, 240, 50, 2100, 1100, 0);
  display_draw_arc(&displaydata, 240, 240, 100, 2100, 1100, 1);
  display_draw_arc(&displaydata, 240, 240, 150, 2100, 1100, 0);
  display_draw_arc(&displaydata, 240, 240, 350, 2100, 1100, 0);
  
  display_set_fg_color(&displaydata, 0x00FF88AA);
  
  display_draw_rect(&displaydata, 70, 50, 300, 50);


  display_draw_rounded_rect(&displaydata, 270, 250, 350, 80, 2);
  
//  display_fill_rounded_rect(&displaydata, 370, 320, 500, 300, 30);
  
  display_set_font(&displaydata, &font_0);
  display_set_fg_color(&displaydata, 0x00942367);
  display_text(&displaydata, 150, 70, "This is font_0 which is fixed width");

//  display_set_fg_color(&displaydata, 0x00333333);
//  display_fill_rect(&displaydata, 0, 0, 800, 50);
  
 
//  display_set_fg_color(&displaydata, 0x00444444);
//  display_fill_rect(&displaydata, 0, 50, 800, 50);

//  display_fill_rect(&displaydata, 0, 0, 800, 46);
//  display_fill_rect(&displaydata, 0, 478, 800, 2);

  
//  display_fill_rect(&displaydata, 0, 0, 1, 480);
//  display_fill_rect(&displaydata, 727, 0, 73, 480);

//  display_set_font(&displaydata, &font_2);
//  display_set_fg_color(&displaydata, 0x00B4FFFE);
//  display_text(&displaydata, 20, 20, "This is a test with font_2");
  
//  display_set_fg_color(&displaydata, 0x00D3374A);
//  display_fill_rect(&displaydata, 320, 270, 160, 60);
 
  
  //--------------------------------------------------------------------------------------------------------------------------------
  
  //Keep running until window is destroyed
	while(rflag)
	{
		XNextEvent(display, &event);
		switch(event.type)
		{
			case Expose:
        //Setup the screen
        {
          //Need some scaling algo here to match the scope display to the screen display. The scaling will mostly be one but just in case
          int ix,iy,idx;

          u_int16_t *dptr = displaybuffer;

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
        
			case KeyPress:
				if(event.xkey.keycode == XKeysymToKeycode(display,XK_Escape))
				{
					rflag = 0;
				}
        break;
        
      case ButtonPress:
        //Call mouse handling function down()
        break;
        
      case ButtonRelease:
        //Call mouse handling function up()
        break;
        
      case MotionNotify:
        //Call mouse handling function move()
        break;
        
      case ClientMessage:
        if((event.xclient.message_type == WM_PROTOCOLS) && (event.xclient.data.l[0] == WM_DELETE_WINDOW))
        {
					rflag = 0;
        }
        break;
		}
	}
  
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------
