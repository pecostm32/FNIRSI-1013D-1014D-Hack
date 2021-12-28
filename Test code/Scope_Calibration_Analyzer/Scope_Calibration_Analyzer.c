#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xlibfunctions.h"
#include "../../F1C100s/fnirsi_1013d_scope/sin_cos_math.h"
#include "../../F1C100s/fnirsi_1013d_scope/types.h"
#include "../../F1C100s/fnirsi_1013d_scope/font_structs.h"
#include "../../F1C100s/fnirsi_1013d_scope/display_lib.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define scope_screen    1

#if scope_screen
#define DESIGN_WIDTH      2120
#define DESIGN_HEIGHT      600
#else
#define DESIGN_WIDTH      1520
#define DESIGN_HEIGHT     1260
#endif

//----------------------------------------------------------------------------------------------------------------------------------

void load_display_signal_buffer(FILE *fp, u_int32_t index);

void make_image(tagXlibContext *xc, tagXlibDimensions *xd, XImage *scopedisplay);

//----------------------------------------------------------------------------------------------------------------------------------

extern FONTDATA font_0;
extern FONTDATA font_2;
extern FONTDATA font_3;
extern FONTDATA font_5;
extern FONTDATA font_7;

extern const uint16 system_settings_icon[];
extern const uint16 picture_view_icon[];
extern const uint16 waveform_view_icon[];
extern const uint16 usb_icon[];


extern const uint8 letter_c_icon[];
extern const uint8 letter_e_icon[];
extern const uint8 letter_o_icon[];
extern const uint8 letter_p_icon[];
extern const uint8 letter_s_icon[];

//DISPLAYDATA displaydata;

//----------------------------------------------------------------------------------------------------------------------------------

#if scope_screen
unsigned short maindisplaybuffer[2100 * 580];
unsigned short displaybuffer[2100 * 580];
unsigned short displaybuffer1[2100 * 580];

unsigned short gradientbuffer[580];
#else
unsigned short maindisplaybuffer[1500 * 1240];
unsigned short displaybuffer[1500 * 1240];
unsigned short displaybuffer1[1500 * 1240];
#endif

//----------------------------------------------------------------------------------------------------------------------------------

typedef unsigned long long   uint64;
typedef unsigned int         uint32;
typedef unsigned short       uint16;
typedef unsigned char        uint8;

typedef int         int32;

typedef struct tagADC2CalibrationData   ADC2CALIBRATIONDATA,  *PADC2CALIBRATIONDATA;

struct tagADC2CalibrationData
{
  uint16 flag;
  uint16 compensation;
};

uint16 samples1[3000];
uint16 samples2[3000];
uint16 samples3[3000];
uint16 samples4[3000];
uint16 samples5[3000];
uint16 samples6[3000];
uint16 samples7[3000];
uint16 samples8[3000];

ADC2CALIBRATIONDATA calib1;

//For 10.22 ==> 1 ==> 4194304
uint32 ch1k1 = 419431;
uint32 ch1k2 = 3774873;
uint32 filterch1 = 0;

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_channel_trace(uint16 *buffer, uint16 xpos, uint16 yoffset, uint16 count, uint32 color)
{
  register uint32 index = 0;
  register uint32 sample1, sample2;

  display_set_fg_color(color);
  
  sample1 = buffer[index++];
  
  while(index < count)
  {
    sample2 = buffer[index++];

    display_draw_line(xpos, sample1 + yoffset, xpos + 1, sample2 + yoffset);
    
    xpos++;
    
    sample1 = sample2;
  }
}

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
  x = 100;
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
  
#if scope_screen
  width  = 2100 * xc.scaler;
  height = 580 * xc.scaler;
#else  
  width  = 1500 * xc.scaler;
  height = 1240 * xc.scaler;
#endif
  
  tagXlibDimensions xd;
  
  xd.x = x;
  xd.y = y;
  xd.width = width;
  xd.height = height;
  
  //Setup the image based on a capture of the screen
  XImage *scopedisplay = XGetImage(display, win, x, y, width, height, 0, ZPixmap);
  
  //--------------------------------------------------------------------------------------------------------------------------------
  //Test section

  int32_t buffer_index = 0;
  
  FILE *fi = NULL;
  
  display_set_bg_color(0x00000000);
  display_set_dimensions(2100, 580);
  display_set_screen_buffer(displaybuffer);
  
  fi = fopen("calibration_data.bin", "rb");

  load_display_signal_buffer(fi, buffer_index);
  
  u_int32_t new_screen = 0;
  
  //--------------------------------------------------------------------------------------------------------------------------------
  
  //Keep running until window is destroyed
	while(rflag)
	{
		XNextEvent(display, &event);
		switch(event.type)
		{
			case Expose:
        make_image(&xc, &xd, scopedisplay);
				break;
        
			case KeyPress:
				if(event.xkey.keycode == XKeysymToKeycode(display,XK_Escape))
				{
					rflag = 0;
				}
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Right))
        {
          buffer_index++;

          if(buffer_index >= 156)
          {
            buffer_index = 0;
          }

          new_screen = 1;
        }
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Left))
        {
          if(buffer_index > 0)
          {
            buffer_index--;
          }
          else
          {
            buffer_index = 155;
          }

          new_screen = 1;
        }
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Up))
        {
          buffer_index += 26;

          if(buffer_index >= 156)
          {
            buffer_index -= 156;
          }

          new_screen = 1;
        }
        else if(event.xkey.keycode == XKeysymToKeycode(display,XK_Down))
        {
          buffer_index -= 26;
          
          if(buffer_index < 0)
          {
            buffer_index += 156;
          }

          new_screen = 1;
        }

        if(new_screen)
        {
          load_display_signal_buffer(fi, buffer_index);
          make_image(&xc, &xd, scopedisplay);
          
          new_screen = 0;
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
  
  if(fi)
  {
    fclose(fi);
  }
  
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void make_image(tagXlibContext *xc, tagXlibDimensions *xd, XImage *scopedisplay)
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
  XPutImage(xc->display, xc->win, xc->gc, scopedisplay, 0, 0, xd->x, xd->y, xd->width, xd->height);
}

//----------------------------------------------------------------------------------------------------------------------------------

void load_display_signal_buffer(FILE *fp, u_int32_t index)
{
  char   text_buffer[256];
  int32  buffer[16];
  uint32 y;

  display_set_fg_color(0x00000000);
  display_fill_rect(0, 0, 2100, 580);

  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_5);
  display_decimal(20, 15, index);
  
  //There are 6 volt per div settings
  //So volt per div is index / 26
  snprintf(text_buffer, 256, "Volt per div: %d", index / 26);
  display_text(140, 15, text_buffer);
  
  //For every volt per div setting there are 26 buffers
  //So offset is 200 + (50 * (index % 26))
  snprintf(text_buffer, 256, "Offset: %d", 200 + (50 * (index % 26)));
  display_text(340, 15, text_buffer);
  
  display_set_font(&font_0);
  
  if(fp)
  {
    u_int32_t seek_point = index * 12064;
    
    //Point to the buffer set
    fseek(fp, seek_point, SEEK_SET);

    //Get the sample data
    fread(&samples1, 2, 3000, fp);

    //Get the sample data
    fread(&samples2, 2, 3000, fp);
    
    //Get the measurement data
    fread(&buffer, 4, 16, fp);

    scope_display_channel_trace(samples1, 300, 80,  1500, 0x00FFFF00);
    
    y = 120;

    snprintf(text_buffer, 256, "ADC1 avg: %d", buffer[0]);
    display_text(20, y, text_buffer);
    
    snprintf(text_buffer, 256, "ADC diff: %d", buffer[0] - buffer[1]);
    display_text(160, y+10, text_buffer);

    snprintf(text_buffer, 256, "ADC2 avg: %d", buffer[1]);
    display_text(20, y+20, text_buffer);

    snprintf(text_buffer, 256, "min:      %d", buffer[2]);
    display_text(20, y+40, text_buffer);
    
    snprintf(text_buffer, 256, "max:      %d", buffer[3]);
    display_text(20, y+60, text_buffer);
    
    snprintf(text_buffer, 256, "average:  %d", buffer[4]);
    display_text(20, y+80, text_buffer);
    
    snprintf(text_buffer, 256, "peakpeak: %d", buffer[5]);
    display_text(20, y+100, text_buffer);
    
    snprintf(text_buffer, 256, "center:   %d", buffer[6]);
    display_text(20, y+120, text_buffer);
    
    scope_display_channel_trace(samples2, 300, 280,  1500, 0x0000FF00);

    y = 360;
    
    snprintf(text_buffer, 256, "ADC1 avg: %d", buffer[8]);
    display_text(20, y, text_buffer);
    
    snprintf(text_buffer, 256, "ADC diff: %d", buffer[8] - buffer[9]);
    display_text(160, y+10, text_buffer);

    snprintf(text_buffer, 256, "ADC2 avg: %d", buffer[9]);
    display_text(20, y+20, text_buffer);

    snprintf(text_buffer, 256, "min:      %d", buffer[10]);
    display_text(20, y+40, text_buffer);
    
    snprintf(text_buffer, 256, "max:      %d", buffer[11]);
    display_text(20, y+60, text_buffer);
    
    snprintf(text_buffer, 256, "average:  %d", buffer[12]);
    display_text(20, y+80, text_buffer);
    
    snprintf(text_buffer, 256, "peakpeak: %d", buffer[13]);
    display_text(20, y+100, text_buffer);
    
    snprintf(text_buffer, 256, "center:   %d", buffer[14]);
    display_text(20, y+120, text_buffer);
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------

#if 0
  *ptr++ = scopesettings.channel1.adc1rawaverage;
  *ptr++ = scopesettings.channel1.adc2rawaverage;
  *ptr++ = scopesettings.channel1.min;
  *ptr++ = scopesettings.channel1.max;
  *ptr++ = scopesettings.channel1.average;
  *ptr++ = scopesettings.channel1.peakpeak;
  *ptr++ = scopesettings.channel1.center;
#endif