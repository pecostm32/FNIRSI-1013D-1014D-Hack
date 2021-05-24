//For development the following packages are needed.
//sudo apt-get install libx11-dev
//sudo apt-get install libxft-dev
//sudo apt-get install libxrandr-dev

#ifndef XLIBFUNCTIONS_H
#define XLIBFUNCTIONS_H

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/keysym.h>

#include <X11/Xft/Xft.h>

#include <X11/extensions/Xrandr.h>

#define NOF_FONTS_USED        5
#define NOF_TEXT_COLORS_USED  2

#define ALIGN_TEXT_LEFT       0
#define ALIGN_TEXT_RIGHT      1
#define ALIGN_TEXT_CENTER     2

#define BORDER_SIZE           8
#define BORDER_SIZE_2        16

#define Angle0       0
#define Angle30     30 * 64
#define Angle60     60 * 64
#define Angle90     90 * 64
#define Angle120   120 * 64
#define Angle150   150 * 64
#define Angle180   180 * 64
#define Angle210   210 * 64
#define Angle240   240 * 64
#define Angle270   270 * 64
#define Angle300   300 * 64
#define Angle330   330 * 64
#define Angle360   360 * 64


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

typedef struct
{
  char *text;
  int   x;
  int   y;
  int   fontid;
  int   colorid;
  int   align;
} tagPlaceText;


int PlaceText(tagXlibContext *xc, int xpos, int ypos, char *text, int fontid, int colorid, int align);

int DrawLine(tagXlibContext *xc, int xp1, int yp1, int xp2, int yp2, int linecolor, int linewidth);
int DrawLines(tagXlibContext *xc, XPoint *points, int npoints, int linecolor, int linewidth);
int DrawSegments(tagXlibContext *xc, XSegment *segments, int nsegments, int linecolor, int linewidth);

int DrawRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int linecolor, int linewidth);
int DrawFillRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor, int linecolor, int linewidth);
int DrawFillRoundedRect(tagXlibContext *xc, int xpos, int ypos, int radius, int width, int height, int fillcolor, int linecolor, int linewidth);

int FillRect(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor);
int FillPolygon(tagXlibContext *xc, XPoint *points, int npoints, int fillcolor);


#endif /* XLIBFUNCTIONS_H */

