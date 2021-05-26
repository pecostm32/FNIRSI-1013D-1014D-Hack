#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xlibfunctions.h"

#include "mousehandling.h"

#include "lcdisplay.h"
#include "buttons.h"

#include "armtracedata.h"

#include "armdisassemble.h"

//----------------------------------------------------------------------------------------------------------------------------------

void DrawTracePanel(tagXlibContext *xc);

//----------------------------------------------------------------------------------------------------------------------------------

#define DESIGN_WIDTH       1600
#define DESIGN_HEIGHT      1000

//----------------------------------------------------------------------------------------------------------------------------------

#define TextColor               "#D5D5D5"

#define ArmLineColor            0x000000
#define ArmPanelColor           0x414244

//----------------------------------------------------------------------------------------------------------------------------------

const tagPlaceText texts[] =
{
  //Text, xpos, ypos, fontid, colorid, align
  //All header texts with 20pt font
  { "TRACE LINES",       780,  32, 0, 0, ALIGN_TEXT_CENTER },
  { "INSTRUCTION DATA",  780, 662, 0, 0, ALIGN_TEXT_CENTER },
  { "Scroll",           1560, 340, 0, 0, ALIGN_TEXT_CENTER }
};

tagLcDisplay lcdisplays[] =
{
  //  xc, xpos, ypos, chars, lines,          offcolor,          oncolor,                  bgcolor,           ledgecolor,          bredgecolor
  { NULL,   20,   40,   124,    32, LcDisplayOffColor, LcDisplayOnColor, LcDisplayBackGroundColor, LcDisplaytledgecolor, LcDisplaybredgecolor },
  { NULL,   20,  670,   124,    16, LcDisplayOffColor, LcDisplayOnColor, LcDisplayBackGroundColor, LcDisplaytledgecolor, LcDisplaybredgecolor }
};

//All the buttons on the front panel
tagButton buttons[] = 
{
  //        Mouserange set here to make a linked list. Search for object under mouse pointer needs to be done from last to first based on previous pointer
  //  xc,                 action,             previous, left, right, top, bottom, move, down,   up,  out,                 type, xpos, ypos, 
  { NULL,                   NULL, {               NULL,    0,     0,   0,      0, NULL, NULL, NULL, NULL },        BUTTON_ARROW_UP, 1545,  290, 0 },
  { NULL,                   NULL, {  &buttons[0].mouse,    0,     0,   0,      0, NULL, NULL, NULL, NULL },      BUTTON_ARROW_DOWN, 1545,  348, 0 }
};

//Set pointer to last mouse range for scanning
MouseRange *mouseranges = &buttons[1].mouse;

//----------------------------------------------------------------------------------------------------------------------------------

int listitems = 0;

//The emulator writes max 25000 lines per file
ARMV5TL_TRACE_ENTRY tracelist[25100];

//----------------------------------------------------------------------------------------------------------------------------------

int main(int argc,char **argv)
{
  //For now just a single file opened here
  FILE *fp = fopen("test_trace_000088.bin", "rb");
  
  if(fp)  
  {
    int size = fread(tracelist, 1, sizeof(tracelist) , fp);
    
    listitems = size / sizeof(ARMV5TL_TRACE_ENTRY);
    
    fclose(fp);
  }
  
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
    
  //Create all the used fonts
  fsize = 14 * xc.scaler;
  xc.font[0] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);
  
  //Create the used font colors
  rflag = XftColorAllocName(display, xc.visual, xc.cmap, TextColor, &xc.color[0]);
  
  xc.draw = XftDrawCreate(display, win, xc.visual, xc.cmap);
  
  //Keep running until window is destroyed
	while(rflag)
	{
		XNextEvent(display, &event);
		switch(event.type)
		{
			case Expose:
        //Setup the screen
        DrawTracePanel(&xc);
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
        MouseUp(mouseranges, &event);
        break;
        
      case MotionNotify:
        //Call mouse handling function move()
        MouseMove(mouseranges, &event);
        break;
        
      case ClientMessage:
        if((event.xclient.message_type == WM_PROTOCOLS) && (event.xclient.data.l[0] == WM_DELETE_WINDOW))
        {
					rflag = 0;
        }
        break;
		}
	}
  
  //Cleanup on close  
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[0]);
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[1]);
  XftDrawDestroy(xc.draw);
  
  WM_PROTOCOLS = 0;
  WM_DELETE_WINDOW = 0;
  
  //Throw away the window and close up the display
  XDestroyWindow(display, win);
	XCloseDisplay(display);
  
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Function for drawing the frontpanel and all the objects on it
void DrawTracePanel(tagXlibContext *xc)
{
  int i,n;
  
  //Draw the trace reader outline
  DrawFillRoundedRect(xc, 0, 0, 8, DESIGN_WIDTH, 1000, ArmPanelColor, ArmLineColor, 1);
 
  //Place all the texts
  n = sizeof(texts) / sizeof(tagPlaceText);
  for(i=0;i<n;i++)
    PlaceText(xc, texts[i].x, texts[i].y, texts[i].text, texts[i].fontid, texts[i].colorid, texts[i].align);
  
  //Setup all the displays
  n = sizeof(lcdisplays) / sizeof(tagLcDisplay);
  for(i=0;i<n;i++)
    LcdDisplaySetup(xc, &lcdisplays[i]);
  
  //Setup all the buttons
  n = sizeof(buttons) / sizeof(tagButton);
  for(i=0;i<n;i++)
    ButtonSetup(xc, &buttons[i]);
  
  LcdDisplayText(&lcdisplays[0], 0,  0, "ADDRESS     INSTRUCTION EXE  CUR  ASSEMBLY");


  LcdDisplayText(&lcdisplays[1], 0,  0, "REGISTERS   R0          R1          R2          R3          R4          R5          R6          R7");
  LcdDisplayText(&lcdisplays[1], 0,  1, "            0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000");
  LcdDisplayText(&lcdisplays[1], 0,  2, "BANK        R8          R9          R10         R11         R12");
  LcdDisplayText(&lcdisplays[1], 0,  3, "USER        0x00000000  0x00000000  0x00000000  0x00000000  0x00000000");
  LcdDisplayText(&lcdisplays[1], 0,  4, "FIQ         0x00000000  0x00000000  0x00000000  0x00000000  0x00000000");
  LcdDisplayText(&lcdisplays[1], 0,  5, "            R13         R14         R15         CSPR        SPSR");
  LcdDisplayText(&lcdisplays[1], 0,  6, "USER        0x00000000  0x00000000  0x00000000  0x00000000");
  LcdDisplayText(&lcdisplays[1], 0,  7, "FIQ         0x00000000  0x00000000                          0x00000000");
  LcdDisplayText(&lcdisplays[1], 0,  8, "IRQ         0x00000000  0x00000000                          0x00000000");
  LcdDisplayText(&lcdisplays[1], 0,  9, "SUPERVISOR  0x00000000  0x00000000                          0x00000000");
  LcdDisplayText(&lcdisplays[1], 0, 10, "ABORT       0x00000000  0x00000000                          0x00000000");
  LcdDisplayText(&lcdisplays[1], 0, 11, "UNDEFINED   0x00000000  0x00000000                          0x00000000");
  
  LcdDisplayText(&lcdisplays[1], 0, 13, "MEMORY      16 WORDS");
  LcdDisplayText(&lcdisplays[1], 0, 14, "0x81B7F340  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000");
  LcdDisplayText(&lcdisplays[1], 0, 15, "0x81B7F360  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000  0x00000000");


  
  char exetext[4][4] = { "NO ", "YES", "   ", "   " };
  
  char displaytext[128];
  char disassemtext[94];
  
  n = listitems - 31;
  n = 0;
  
  for(i=0;i<31;i++)
  {

    memset(disassemtext, 0x20, sizeof(disassemtext));
    disassemtext[0] = 0;
    
    ArmV5tlDisassemble(disassemtext, sizeof(disassemtext), (ARM_INSTRUCTION)tracelist[n].instruction_word);
  
    snprintf(displaytext, sizeof(displaytext), "0x%08X  0x%08X  %s       %s", tracelist[n].instruction_address, tracelist[n].instruction_word, exetext[tracelist[n].execution_status & 3], disassemtext);
    LcdDisplayText(&lcdisplays[0], 0, i + 1, displaytext);
    
    n++;
  }
    
    
    
    
  
}

//----------------------------------------------------------------------------------------------------------------------------------
