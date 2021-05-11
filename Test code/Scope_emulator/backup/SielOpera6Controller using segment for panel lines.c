//sudo apt-get install libx11-dev
//sudo apt-get install -y libxft-dev

//Use software manager to install mscore for microsoft fonts like Arial



#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <X11/Xft/Xft.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NOF_FONTS_USED        5
#define NOF_TEXT_COLORS_USED  2

#define ALIGN_TEXT_LEFT       0
#define ALIGN_TEXT_RIGHT      1
#define ALIGN_TEXT_CENTER     2

typedef struct
{
  int       screen_num;  
  Window    root;
  Window    win;
  Display  *display;
  GC        gc;
  float     scaler;
  Visual   *visual;
  Colormap  cmap;
  XftDraw  *draw;
  XftColor  color[NOF_TEXT_COLORS_USED];
  XftFont  *font[NOF_FONTS_USED];
} tagXlibContext;

int DrawFrontPanel(tagXlibContext *xc);


int PlaceText(tagXlibContext *xc, int xpos, int ypos, char *text, int fontid, int colorid, int align);

int DrawLine(tagXlibContext *xc, int xp1, int yp1, int xp2, int yp2, int linecolor, int linewidth);
int DrawLines(tagXlibContext *xc, XPoint *points, int npoints, int linecolor, int linewidth);
int DrawSegments(tagXlibContext *xc, XSegment *segments, int nsegments, int linecolor, int linewidth);

int DrawRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int linecolor, int linewidth);
int DrawFillRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor, int linecolor, int linewidth);
int DrawFillRoundedRect(tagXlibContext *xc, int xpos, int ypos, int radius, int width, int height, int fillcolor, int linecolor, int linewidth);

int FillRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor);
int FillPolygon(tagXlibContext *xc, XPoint *points, int npoints, int fillcolor);


//Need to get screen size and determine a suitable width and height based on design being 3200 x 1200 pixels
//Scaling needs to be done in the code itself. Not like in html5 canvas where it is part of the system

//Fonts need to be scaled also!!!!!!

//Possible error handling needs to be build in

#define DESIGN_WIDTH       3200
#define DESIGN_HEIGHT      1200
#define BORDER_SIZE           8
#define BORDER_SIZE_2        16


//Colors used in the project
#define TextColor           "#F5F9FC"   //For the texts on the panel
#define LogoColor           "#D7E3F1"   //For the texts on the panel
#define PanelLineColor      0xF5F9FC    //For some lines on the panel
#define PanelBlackColor     0x000000    //For lines around the separate parts
#define PanelMetalColor     0x414244    //Background color of the panel and the plastic sides
#define PanelPlanesColor    0xA8CDF7    //Planes and stripes in the control section
#define PanelDividerColor   0xD7E3F1    //Program section separation stripes

//Open a window with design dimensions. It will fit itself to the default display and the window attributes give the actual size
//Based on this size the correct window size can be calculated.

//Resize event needs to be handled to make sure the design is redrawn with the new dimensions

int main(int argc,char **argv)
{
	Display *display = XOpenDisplay(NULL);
	int screen_num = DefaultScreen(display);
	Window root = RootWindow(display, screen_num);
	Window win = XCreateSimpleWindow(display, root, 0, 0, DESIGN_WIDTH + BORDER_SIZE_2, DESIGN_HEIGHT + BORDER_SIZE_2, 2, BlackPixel(display, screen_num), WhitePixel(display, screen_num));

	XMapWindow(display, win);
  
	XSelectInput(display, win, ExposureMask | KeyPressMask);
  
	GC gc = XCreateGC(display, win, 0, NULL);
  
  
  unsigned int width;	           //width and height for the new window.
  unsigned int height;
  
  unsigned int x;
  
  Atom WM_DELETE_WINDOW = XInternAtom(display, "WM_DELETE_WINDOW", False); 
  XSetWMProtocols(display, win, &WM_DELETE_WINDOW, 1);  
  
	XEvent event;
  XWindowAttributes wattrib;

  double fsize;
  
  int rflag = 1;


  tagXlibContext xc;
  
  //Update the window to get the correct size info
	XNextEvent(display, &event);

  //Get the size of the window to be able to determine the scaler
  XGetWindowAttributes(display, win, &wattrib);
  
  //For calculations take of a border of 5 pixels for each side
  width  = (wattrib.width - BORDER_SIZE_2) * 0.95;
  height = wattrib.height - BORDER_SIZE_2;
  
   
  xc.scaler = (float)width / (float)DESIGN_WIDTH;

  if((1200 * xc.scaler) > height)
    xc.scaler = (float)height / (float)1200;

  width = (3200 * xc.scaler) + BORDER_SIZE_2;
  height = (1200 * xc.scaler) + BORDER_SIZE_2;
  
  x = (wattrib.width - width) / 2;
  
  XMoveResizeWindow(display, win, x, wattrib.y, width, height);
  
  xc.screen_num = screen_num;
  xc.root = root;
  xc.win = win;
  xc.display = display;
  xc.gc = gc;
  
  xc.visual = DefaultVisual(display, screen_num);
  xc.cmap  = DefaultColormap(display, screen_num);

    
    
  fsize = 20 * xc.scaler;
  xc.font[0] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 14 * xc.scaler;
  xc.font[1] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 11 * xc.scaler;
  xc.font[2] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial Narrow", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);

  fsize = 62 * xc.scaler;
  xc.font[3] = XftFontOpen(display, screen_num, XFT_FAMILY, XftTypeString, "Arial Narrow", XFT_WEIGHT, XftTypeInteger, XFT_WEIGHT_BOLD, XFT_SIZE, XftTypeDouble, fsize, XFT_ANTIALIAS, XftTypeBool, True, NULL);
  
  rflag = XftColorAllocName(display, xc.visual, xc.cmap, TextColor, &xc.color[0]);

  rflag = XftColorAllocName(display, xc.visual, xc.cmap, LogoColor, &xc.color[1]);
  
  xc.draw = XftDrawCreate(display, win, xc.visual, xc.cmap);
  
  //Keep running until window is destroyed
	while(rflag)
	{
		XNextEvent(display, &event);
		switch(event.type)
		{
			case Expose:
        //Setup the screen
        DrawFrontPanel(&xc);
				break;
        
			case KeyPress:
				if(event.xkey.keycode == XKeysymToKeycode(display,XK_Escape))
				{
					rflag = 0;
				}
        break;
        
      case ClientMessage:
        if(event.xclient.data.l[0] == WM_DELETE_WINDOW)
        {
					rflag = 0;
        }
        break;
		}
	}
  
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[0]);
  XftColorFree(display, xc.visual, xc.cmap, &xc.color[1]);
  XftDrawDestroy(xc.draw);
  
  XDestroyWindow(display, win);
	XCloseDisplay(display);
	return 0;
}


int DrawFrontPanel(tagXlibContext *xc)
{
  int i,y;
  XPoint points[6];
  XSegment segments[10];
  
  //Draw the metal front panel base and the section underneath the keyboard
  DrawFillRect(xc, 101, 20, 3000, 1160, PanelMetalColor, PanelBlackColor, 1);
  
  //Draw the plastic side panels
  DrawFillRoundedRect(xc, 0,    0, 12, 100, 1200, PanelMetalColor, PanelBlackColor, 1);
  DrawFillRoundedRect(xc, 3100, 0, 12, 100, 1200, PanelMetalColor, PanelBlackColor, 1);
  
  //Draw the plastic panels besides the keyboard
  DrawFillRoundedRect(xc, 102, 721, 8, 20, 458, PanelMetalColor, PanelBlackColor, 1);
  DrawFillRoundedRect(xc, 3079, 721, 8, 20, 458, PanelMetalColor, PanelBlackColor, 1);
  
  //Draw the separator above the keyboard
  DrawLine(xc, 101, 720, 3099, 720, PanelBlackColor, 1);
  
  //Draw the program section borders
  FillRect(xc, 115, 452, 2970, 10, PanelDividerColor);
  FillRect(xc, 115, 663, 2970, 10, PanelDividerColor);
  
  //Panel stripes and planes
  for(i=0,y=71;i<8;i++,y+=45)
  {
    FillRect(xc,  115, y, 110, 5, PanelPlanesColor);
    FillRect(xc,  590, y, 110, 5, PanelPlanesColor);
    FillRect(xc, 2610, y, 110, 5, PanelPlanesColor);
    FillRect(xc, 2975, y, 110, 5, PanelPlanesColor);
  }
  
  //Modulations
  FillRect(xc, 240,  71, 335,  35, PanelPlanesColor);
  FillRect(xc, 240, 111, 335, 280, PanelPlanesColor);
  
  //Setup points for LFO III
  points[0].x = BORDER_SIZE +  (715 * xc->scaler);
  points[0].y = BORDER_SIZE +  (258 * xc->scaler);
  points[1].x = BORDER_SIZE + (1185 * xc->scaler);
  points[1].y = BORDER_SIZE +  (258 * xc->scaler);
  points[2].x = BORDER_SIZE + (1185 * xc->scaler);
  points[2].y = BORDER_SIZE +  (111 * xc->scaler);
  points[3].x = BORDER_SIZE + (1294 * xc->scaler);
  points[3].y = BORDER_SIZE +  (111 * xc->scaler);
  points[4].x = BORDER_SIZE + (1294 * xc->scaler);
  points[4].y = BORDER_SIZE +  (390 * xc->scaler);
  points[5].x = BORDER_SIZE +  (715 * xc->scaler);
  points[5].y = BORDER_SIZE +  (390 * xc->scaler);
  
  //LFO
  FillRect(xc, 715,  71, 580,  35, PanelPlanesColor);
  FillRect(xc, 715, 111, 455, 133, PanelPlanesColor);
  FillPolygon(xc, points, 6, PanelPlanesColor);

  //Noise
  FillRect(xc, 1310,  71, 110,  35, PanelPlanesColor);
  FillRect(xc, 1310, 111, 110, 133, PanelPlanesColor);

  //Setup points for DCO B
  points[0].x = BORDER_SIZE + (1310 * xc->scaler);
  points[0].y = BORDER_SIZE +  (258 * xc->scaler);
  points[1].x = BORDER_SIZE + (1785 * xc->scaler);
  points[1].y = BORDER_SIZE +  (258 * xc->scaler);
  points[2].x = BORDER_SIZE + (1785 * xc->scaler);
  points[2].y = BORDER_SIZE +  (111 * xc->scaler);
  points[3].x = BORDER_SIZE + (1894 * xc->scaler);
  points[3].y = BORDER_SIZE +  (111 * xc->scaler);
  points[4].x = BORDER_SIZE + (1894 * xc->scaler);
  points[4].y = BORDER_SIZE +  (390 * xc->scaler);
  points[5].x = BORDER_SIZE + (1310 * xc->scaler);
  points[5].y = BORDER_SIZE +  (390 * xc->scaler);
  
  //DCO
  FillRect(xc, 1435,  71, 460,  35, PanelPlanesColor);
  FillRect(xc, 1435, 111, 335, 133, PanelPlanesColor);
  FillPolygon(xc, points, 6, PanelPlanesColor);

  //VCF
  FillRect(xc, 1910,  71, 225,  35, PanelPlanesColor);
  FillRect(xc, 1910, 111, 225, 133, PanelPlanesColor);
  FillRect(xc, 1910, 258, 225, 133, PanelPlanesColor);

  //Dynamic ADSR
  FillRect(xc, 2150,  71, 445,  35, PanelPlanesColor);
  FillRect(xc, 2150, 111, 445, 133, PanelPlanesColor);
  FillRect(xc, 2150, 258, 445, 133, PanelPlanesColor);

  //Master
  FillRect(xc, 2735,  71, 225,  35, PanelPlanesColor);
  FillRect(xc, 2735, 111, 225, 133, PanelPlanesColor);
  FillRect(xc, 2735, 258, 225, 133, PanelPlanesColor);

  //Borders around midi and tape text in interfaces
  DrawRect(xc, 2845, 366, 37, 19, PanelLineColor, 2);
  DrawRect(xc, 2900, 366, 42, 19, PanelLineColor, 2);
  
  //Setup for drawing the lines near detune and the interfaces leds
  segments[0].x1 = BORDER_SIZE + (1841 * xc->scaler);
  segments[0].x2 = BORDER_SIZE + (1851 * xc->scaler);
  segments[0].y1 = BORDER_SIZE + (233 * xc->scaler);
  segments[0].y2 = BORDER_SIZE + (243 * xc->scaler);

  segments[1].x1 = BORDER_SIZE + (1851 * xc->scaler);
  segments[1].x2 = BORDER_SIZE + (1831 * xc->scaler);
  segments[1].y1 = BORDER_SIZE + (243 * xc->scaler);
  segments[1].y2 = BORDER_SIZE + (243 * xc->scaler);
  
  segments[2].x1 = BORDER_SIZE + (1831 * xc->scaler);
  segments[2].x2 = BORDER_SIZE + (1841 * xc->scaler);
  segments[2].y1 = BORDER_SIZE + (243 * xc->scaler);
  segments[2].y2 = BORDER_SIZE + (233 * xc->scaler);

  segments[3].x1 = BORDER_SIZE + (1841 * xc->scaler);
  segments[3].x2 = BORDER_SIZE + (1851 * xc->scaler);
  segments[3].y1 = BORDER_SIZE + (276 * xc->scaler);
  segments[3].y2 = BORDER_SIZE + (266 * xc->scaler);

  segments[4].x1 = BORDER_SIZE + (1851 * xc->scaler);
  segments[4].x2 = BORDER_SIZE + (1831 * xc->scaler);
  segments[4].y1 = BORDER_SIZE + (266 * xc->scaler);
  segments[4].y2 = BORDER_SIZE + (266 * xc->scaler);

  segments[5].x1 = BORDER_SIZE + (1841 * xc->scaler);
  segments[5].x2 = BORDER_SIZE + (1831 * xc->scaler);
  segments[5].y1 = BORDER_SIZE + (276 * xc->scaler);
  segments[5].y2 = BORDER_SIZE + (266 * xc->scaler);

  //Lines in interfaces section
  segments[6].x1 = BORDER_SIZE + (2892 * xc->scaler);
  segments[6].x2 = BORDER_SIZE + (2892 * xc->scaler);
  segments[6].y1 = BORDER_SIZE + (312 * xc->scaler);
  segments[6].y2 = BORDER_SIZE + (323 * xc->scaler);
  
  segments[7].x1 = BORDER_SIZE + (2892 * xc->scaler);
  segments[7].x2 = BORDER_SIZE + (2902 * xc->scaler);
  segments[7].y1 = BORDER_SIZE + (323 * xc->scaler);
  segments[7].y2 = BORDER_SIZE + (323 * xc->scaler);

  segments[8].x1 = BORDER_SIZE + (2892 * xc->scaler);
  segments[8].x2 = BORDER_SIZE + (2892 * xc->scaler);
  segments[8].y1 = BORDER_SIZE + (338 * xc->scaler);
  segments[8].y2 = BORDER_SIZE + (327 * xc->scaler);
  
  segments[9].x1 = BORDER_SIZE + (2892 * xc->scaler);
  segments[9].x2 = BORDER_SIZE + (2902 * xc->scaler);
  segments[9].y1 = BORDER_SIZE + (327 * xc->scaler);
  segments[9].y2 = BORDER_SIZE + (327 * xc->scaler);
    
  //Drawing the lines near detune and the interfaces leds
  DrawSegments(xc, segments, 10, PanelLineColor, 2);
    
  //All header texts with 20pt font
  PlaceText(xc,  408, 98, "MODULATIONS",      0, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 1005, 98, "L.F.O.",           0, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 1365, 98, "NOISE",            0, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 1665, 98, "D.C.O.",           0, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 2023, 98, "V.C.F.",           0, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 2373, 98, "DYNAMIC A.D.S.R.", 0, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 2848, 98, "MASTERS",          0, 0, ALIGN_TEXT_CENTER);
  
  //All sub header texts with 14pt font
  PlaceText(xc, 2848, 278, "INTERFACES", 1, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 1842, 262, "DETUNE",     1, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc,  736, 131, "I-II",       1, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 1202, 131, "III",        1, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 1450, 131, "A",          1, 0, ALIGN_TEXT_CENTER);
  PlaceText(xc, 1800, 131, "B",          1, 0, ALIGN_TEXT_CENTER);
  
  //All interface texts with 11pt font
  PlaceText(xc, 2878, 305, "INT.",   2, 0, ALIGN_TEXT_RIGHT);
  PlaceText(xc, 2878, 355, "EXT.",   2, 0, ALIGN_TEXT_RIGHT);
  PlaceText(xc, 2878, 380, "MIDI",   2, 0, ALIGN_TEXT_RIGHT);
  PlaceText(xc, 2906, 330, "VERIFY", 2, 0, ALIGN_TEXT_LEFT);
  PlaceText(xc, 2904, 380, "TAPE",   2, 0, ALIGN_TEXT_LEFT);

  //The name of the device  
  PlaceText(xc, 2744, 540, "OPERA 6", 3, 1, ALIGN_TEXT_LEFT);
  
  return 0;
}


int PlaceText(tagXlibContext *xc, int xpos, int ypos, char *text, int fontid, int colorid, int align)
{
  int x = BORDER_SIZE + (xpos * xc->scaler);
  int y = BORDER_SIZE + (ypos * xc->scaler);
  int l = strlen(text);
  
  XGlyphInfo extents;

  XftTextExtentsUtf8(xc->display, xc->font[fontid], text, l, &extents);
  
  switch(align)
  {
    case ALIGN_TEXT_RIGHT:
      x -= extents.width;
      break;
      
    case ALIGN_TEXT_CENTER:
      x -= (extents.width / 2);
      break;
  }
  
  XftDrawStringUtf8(xc->draw, &xc->color[colorid], xc->font[fontid], x, y, text, l);
  
  return 0;
}

int DrawLine(tagXlibContext *xc, int xp1, int yp1, int xp2, int yp2, int linecolor, int linewidth)
{
  //Setup for drawing
  int x1 = BORDER_SIZE + (xp1 * xc->scaler);
  int y1 = BORDER_SIZE + (yp1 * xc->scaler);
  int x2 = BORDER_SIZE + (xp2 * xc->scaler);
  int y2 = BORDER_SIZE + (yp2 * xc->scaler);
  
  //Setup for drawing the line based on the given width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapNotLast, JoinRound);
  
  //Set the color of the line
  XSetForeground(xc->display, xc->gc, linecolor);
  
  //Draw the actual line
  XDrawLine(xc->display, xc->win, xc->gc, x1, y1, x2, y2);

  return 0;  
}

int DrawLines(tagXlibContext *xc, XPoint *points, int npoints, int linecolor, int linewidth)
{
  //Setup for drawing the line based on the given width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapNotLast, JoinRound);
  
  //Draw the lines on top of the fills and use the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawLines(xc->display, xc->win, xc->gc, points, npoints);
  
  return 0;  
}

int DrawSegments(tagXlibContext *xc, XSegment *segments, int nsegments, int linecolor, int linewidth)
{
  //Setup for drawing the line based on the given width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapNotLast, JoinRound);
  
  //Draw the lines on top of the fills and use the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawSegments(xc->display, xc->win, xc->gc, segments, nsegments);

  return 0;
}

int DrawRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int linecolor, int linewidth)
{
  //Setup for drawing
  int x = BORDER_SIZE + (xpos * xc->scaler);
  int y = BORDER_SIZE + (ypos * xc->scaler);
  int w = width * xc->scaler;
  int h = height * xc->scaler;
  
  //Setup the line with the given line width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapNotLast, JoinRound);

  //Draw the outer line with the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawRectangle(xc->display, xc->win, xc->gc, x, y, w, h);

  return 0;  
}


int DrawFillRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor, int linecolor, int linewidth)
{
  //Setup for drawing and filling
  int x = BORDER_SIZE + (xpos * xc->scaler);
  int y = BORDER_SIZE + (ypos * xc->scaler);
  int w = width * xc->scaler;
  int h = height * xc->scaler;
  
  //Setup the line with the given line width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapNotLast, JoinRound);

  //First fill the rectangle with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillRectangle(xc->display, xc->win, xc->gc, x, y, w, h);
  
  //Then draw the outer line with the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawRectangle(xc->display, xc->win, xc->gc, x, y, w, h);
  
  return 0;
}

#define Angle0       0
#define Angle90     90 * 64
#define Angle180   180 * 64
#define Angle270   270 * 64


int DrawFillRoundedRect(tagXlibContext *xc, int xpos, int ypos, int radius, int width, int height, int fillcolor, int linecolor, int linewidth)
{
  //Setup coordinates for drawing the different parts
  int x = BORDER_SIZE + (xpos * xc->scaler);
  int y = BORDER_SIZE + (ypos * xc->scaler);
  int r = radius * xc->scaler;
  int w = width * xc->scaler;
  int h = height * xc->scaler;
  int cd = r * 2;
  int x1 = x + r;
  int x2 = x + w;
  int x3 = x2 - r;
  int x4 = x2 - cd;
  int y1 = y + r;
  int y2 = y + h;
  int y3 = y2 - r;
  int y4 = y2 - cd;
  int w1 = w - cd;
  int h1 = h - cd;
  
  //By using arrays of object structs single function calls can be done  
  XArc       arcs[4];
  XRectangle rects[3];
  XSegment   lines[4];
  
  //Setup for filling and drawing the 4 arcs
  arcs[0].x      = x;
  arcs[0].y      = y;
  arcs[0].width  = cd;
  arcs[0].height = cd;
  arcs[0].angle1 = Angle90;
  arcs[0].angle2 = Angle90;

  arcs[1].x      = x4;
  arcs[1].y      = y;
  arcs[1].width  = cd;
  arcs[1].height = cd;
  arcs[1].angle1 = Angle0;
  arcs[1].angle2 = Angle90;
  
  arcs[2].x      = x4;
  arcs[2].y      = y4;
  arcs[2].width  = cd;
  arcs[2].height = cd;
  arcs[2].angle1 = Angle270;
  arcs[2].angle2 = Angle90;
  
  arcs[3].x      = x;
  arcs[3].y      = y4;
  arcs[3].width  = cd;
  arcs[3].height = cd;
  arcs[3].angle1 = Angle180;
  arcs[3].angle2 = Angle90;
  
  //Setup for filling the three rects
  rects[0].x      = x1;
  rects[0].y      = y;
  rects[0].width  = w1;
  rects[0].height = r;
  
  rects[1].x      = x;
  rects[1].y      = y1;
  rects[1].width  = w;
  rects[1].height = h1;
  
  rects[2].x      = x1;
  rects[2].y      = y3;
  rects[2].width  = w1;
  rects[2].height = r;
  
  //Setup for drawing the four outer lines
  lines[0].x1 = x1;
  lines[0].x2 = x3;
  lines[0].y1 = y;
  lines[0].y2 = y;
  
  lines[1].x1 = x2;
  lines[1].x2 = x2;
  lines[1].y1 = y1;
  lines[1].y2 = y3;
  
  lines[2].x1 = x1;
  lines[2].x2 = x3;
  lines[2].y1 = y2;
  lines[2].y2 = y2;

  lines[3].x1 = x;
  lines[3].x2 = x;
  lines[3].y1 = y1;
  lines[3].y2 = y3;
  
  //Filling the arcs from the center point
  XSetArcMode(xc->display, xc->gc, ArcPieSlice);
  
  //Setup the line based on given line width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapNotLast, JoinRound);

  //Perform the fills first with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillArcs(xc->display, xc->win, xc->gc, arcs, 4);
  XFillRectangles(xc->display, xc->win, xc->gc, rects, 4);
  
  //Draw the lines on top of the fills and use the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawArcs(xc->display, xc->win, xc->gc, arcs, 4);
  XDrawSegments(xc->display, xc->win, xc->gc, lines, 4);
  
  return 0;
}

int FillRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor)
{
  //Setup for filling
  int x = BORDER_SIZE + (xpos * xc->scaler);
  int y = BORDER_SIZE + (ypos * xc->scaler);
  int w = width * xc->scaler;
  int h = height * xc->scaler;

  //First fill the rectangle with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillRectangle(xc->display, xc->win, xc->gc, x, y, w, h);
 
  return 0;
}

int FillPolygon(tagXlibContext *xc, XPoint *points, int npoints, int fillcolor)
{
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillPolygon(xc->display, xc->win, xc->gc, points, npoints, Nonconvex, CoordModeOrigin);
  
  return 0;
}