#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xlibfunctions.h"

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
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapButt, JoinMiter);
  
  //Set the color of the line
  XSetForeground(xc->display, xc->gc, linecolor);
  
  //Draw the actual line
  XDrawLine(xc->display, xc->win, xc->gc, x1, y1, x2, y2);

  return 0;  
}

int DrawLines(tagXlibContext *xc, XPoint *points, int npoints, int linecolor, int linewidth)
{
  //Setup for drawing the line based on the given width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapButt, JoinMiter);
  
  //Draw the lines on top of the fills and use the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawLines(xc->display, xc->win, xc->gc, points, npoints, CoordModeOrigin);
  
  return 0;  
}

int DrawSegments(tagXlibContext *xc, XSegment *segments, int nsegments, int linecolor, int linewidth)
{
  //Setup for drawing the line based on the given width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapButt, JoinMiter);
  
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
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapButt, JoinMiter);

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
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapButt, JoinMiter);

  //First fill the rectangle with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillRectangle(xc->display, xc->win, xc->gc, x, y, w, h);
  
  //Then draw the outer line with the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawRectangle(xc->display, xc->win, xc->gc, x, y, w, h);
  
  return 0;
}

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
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapButt, JoinMiter);

  //Perform the fills first with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillArcs(xc->display, xc->win, xc->gc, arcs, 4);
  XFillRectangles(xc->display, xc->win, xc->gc, rects, 3);
  
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
