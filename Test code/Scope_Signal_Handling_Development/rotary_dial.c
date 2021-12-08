//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <math.h>
#include "rotary_dial.h"

//-----------------------------------------------------------------------------------------------------

#define PI                         3.1415926535897932384
#define PI2                        6.2831853071795864769

//-----------------------------------------------------------------------------------------------------

#define DIAL_SIZE                  135.0
#define DIAL_X_DISPLACEMENT         20.0
#define DIAL_Y_DISPLACEMENT          8.0
#define DIAL_RING_X_DISPLACEMENT    20.0    //0.15 of the size, since the ring diameter is 0.7 times the size
#define DIAL_RING_Y_DISPLACEMENT    20.0

#define RIDGE_RADIUS                20.0
#define RIDGE_LENGTH                43.0
#define RIDGE_WIDTH                 13.0

//-----------------------------------------------------------------------------------------------------

#define DIAL_CAP_COLOR             0xE3D9CA
#define DIAL_BODY_COLOR            0xD4CABB
#define DIAL_LINE_COLOR            0xF2EDE7

#define RIDGE_TOP_COLOR            0xFFFFFF
#define RIDGE_MIDDLE_COLOR         0xDDD1C2
#define RIDGE_BOTTOM_COLOR         0x000000

//-----------------------------------------------------------------------------------------------------

#define CalcCoord(c)  (BORDER_SIZE + ((c) * xc->scaler))
#define CalcCoordX(x) (BORDER_SIZE + ((rotarydial->xpos + (x)) * xc->scaler))
#define CalcCoordY(y) (BORDER_SIZE + ((rotarydial->ypos + (y)) * xc->scaler))

//-----------------------------------------------------------------------------------------------------

void RotaryDialSetup(tagXlibContext *xc, tagRotaryDial *rotarydial)
{
  MouseRange  *mouse = &rotarydial->mouse;
  
  //The cap is shifted left and up to create 3D look
  //Calculate bounding box coordinates based on cap of the rotary dial
  int xo = rotarydial->xpos - DIAL_X_DISPLACEMENT;
  int yo = rotarydial->ypos - DIAL_Y_DISPLACEMENT;
  int l  = xo;
  int r  = xo + DIAL_SIZE;
  int t  = yo;
  int b  = yo + DIAL_SIZE;

  rotarydial->xc = xc;
  
  //Fill in the mouserange struct to be able to use the rotary dial via the mouse
  //An extra 5 pixels to allow for selection outside the cap
  mouse->left   = CalcCoord(l) - 5;
  mouse->right  = CalcCoord(r) + 5;
  mouse->top    = CalcCoord(t) - 5;
  mouse->bottom = CalcCoord(b) + 5;
  
  mouse->data = rotarydial;
  mouse->move = NULL;
  mouse->down = RotaryDialDown;
  mouse->up   = RotaryDialUp;
  
  //Draw the rotary dial itself
  RotaryDialDraw(rotarydial);
}

//-----------------------------------------------------------------------------------------------------

void RotaryDialDraw(tagRotaryDial *rotarydial)
{
  tagXlibContext *xc = rotarydial->xc;
  
  //Calculate radius of the cap and the indicator
  double r  = DIAL_SIZE / 2.0;
  double r1 = RIDGE_RADIUS;
  double r2 = r1 + RIDGE_LENGTH;
  
  //Calculate the coordinates for drawing the body, cap and the ring on the cap
  int x  = CalcCoordX(0);
  int y  = CalcCoordY(0);
  int x1 = CalcCoordX(DIAL_X_DISPLACEMENT);
  int y1 = CalcCoordY(DIAL_Y_DISPLACEMENT);
  int x2 = CalcCoordX(DIAL_RING_X_DISPLACEMENT);
  int y2 = CalcCoordY(DIAL_RING_Y_DISPLACEMENT);
  
  int d  = DIAL_SIZE * xc->scaler;
  int dr = DIAL_SIZE * 0.7 * xc->scaler;

  //Calculate angle, sin and cosine for the given position
  double a = ((360.0 - rotarydial->position) / 180.0) * PI;
  double s  = sin(a);
  double c  = cos(a);

  //Set the line attributes
  XSetLineAttributes(xc->display, xc->gc, 1, LineSolid, CapButt, JoinMiter);
  
  //Draw the body of the rotary dial with a perimeter line
  XSetForeground(xc->display, xc->gc, DIAL_BODY_COLOR);
  XFillArc(xc->display, xc->win, xc->gc, x1, y1, d, d, Angle0, Angle360);
  XSetForeground(xc->display, xc->gc, DIAL_LINE_COLOR);
  XDrawArc(xc->display, xc->win, xc->gc, x1, y1, d, d, Angle0, Angle360);

  //Draw the cap of the rotary dial with a perimeter line
  XSetForeground(xc->display, xc->gc, DIAL_CAP_COLOR);
  XFillArc(xc->display, xc->win, xc->gc, x, y, d, d, Angle0, Angle360);
  XSetForeground(xc->display, xc->gc, DIAL_LINE_COLOR);
  XDrawArc(xc->display, xc->win, xc->gc, x, y, d, d, Angle0, Angle360);

  //Draw the ring on the cap
  XSetLineAttributes(xc->display, xc->gc, 4, LineSolid, CapButt, JoinMiter);
  XSetForeground(xc->display, xc->gc, DIAL_BODY_COLOR);
  XDrawArc(xc->display, xc->win, xc->gc, x2, y2, dr, dr, Angle0, Angle360);

  XPoint     points[5];
  XSegment   lines[2];
  
  double r3 = a + (PI * 0.5);
  double s1 = sin(r3);
  double c1 = cos(r3);
  
  x += r * xc->scaler + 1;
  y += r * xc->scaler + 1;

  //Ridge width has a 90 degree angle on the radial
  double ox = (RIDGE_WIDTH * s1) / 2;
  double oy = (RIDGE_WIDTH * c1) / 2;

  //Ridge start on the radial
  x2 = x + (r1 * s);
  y2 = y + (r1 * c);

  //Ridge end on the radial
  int x3 = x + (r2 * s);
  int y3 = y + (r2 * c);

  //Ridge outer coordinates
  int rx1 = x2 - ox;
  int ry1 = y2 - oy;
  int rx2 = x3 - ox;
  int ry2 = y3 - oy;
  int rx3 = x3 + ox;
  int ry3 = y3 + oy;
  int rx4 = x2 + ox;
  int ry4 = y2 + oy;

  //Setup for drawing the middle ridge section
  points[0].x = rx1;
  points[0].y = ry1;
  
  points[1].x = rx2;
  points[1].y = ry2;
  
  points[2].x = rx3;
  points[2].y = ry3;

  points[3].x = rx4;
  points[3].y = ry4;

  points[4].x = rx1;
  points[4].y = ry1;
  
  XSetForeground(xc->display, xc->gc, RIDGE_MIDDLE_COLOR);
  XFillPolygon(xc->display, xc->win, xc->gc, points, 5, Nonconvex, CoordModeOrigin);

  //Set the line attributes
  XSetLineAttributes(xc->display, xc->gc, 1, LineSolid, CapButt, JoinMiter);

  //Setup for drawing the top lines
  lines[0].x1 = rx1;
  lines[0].x2 = rx2;
  lines[0].y1 = ry1;
  lines[0].y2 = ry2;

  lines[1].x1 = rx2;
  lines[1].x2 = rx3;
  lines[1].y1 = ry2;
  lines[1].y2 = ry3;
  
  XSetForeground(xc->display, xc->gc, RIDGE_BOTTOM_COLOR);
  XDrawSegments(xc->display, xc->win, xc->gc, lines, 2);

  //Setup for drawing the bottom lines
  lines[0].x1 = rx1;
  lines[0].x2 = rx4;
  lines[0].y1 = ry1;
  lines[0].y2 = ry4;

  lines[1].x1 = rx4;
  lines[1].x2 = rx3;
  lines[1].y1 = ry4;
  lines[1].y2 = ry3;
  
  XSetForeground(xc->display, xc->gc, RIDGE_TOP_COLOR);
  XDrawSegments(xc->display, xc->win, xc->gc, lines, 2);
}

//-----------------------------------------------------------------------------------------------------

void RotaryDialDrawPosition(MouseEvent *event, Bool deltacheck)
{
  tagRotaryDial *rotarydial = event->data;
  XMotionEvent *motionevent = &event->event->xmotion;
  tagXlibContext *xc = rotarydial->xc;
  
  int    dir;
  int    degree;
  double rad;
  
  //Calculate radius of the cap
  double r  = DIAL_SIZE / 2.0;

  //Calculate center point of the cap
  int x = rotarydial->xpos + r;
  int y = rotarydial->ypos + r;

  //Scale to screen coordinates
  x = CalcCoord(x);
  y = CalcCoord(y);
  
  //For x on vertical center line the angle is either 0 or 180 degree
  if(motionevent->x == x)
  {
    //Below and on the horizontal center line 0 degree
    if(motionevent->y <= y)
      degree = 180;
    else
      degree = 0;
  }
  //For x left of the vertical center line the range is 1 to 179 degree
  else if(motionevent->x < x)
  {
    //For y on the horizontal center line the angle is 90 degree
    if(motionevent->y == y)
      degree = 90;
    else
    {
      //Y below or above the horizontal center line gives 1 to 89 and 91 to 179 degree
      rad = atan((double)(y - motionevent->y) / (double)(x - motionevent->x));
      degree = 90 + (rad * (180.0 / PI));
    }
  }
  //For x right of the vertical center line the range is 181 to 359 degree
  else
  {
    //For y on the horizontal center line the angle is 270 degree
    if(motionevent->y == y)
      degree = 270;
    else
    {
      //Y below or above the horizontal center line gives 181 to 269 and 271 to 359 degree
      rad = atan((double)(motionevent->y - y) / (double)(motionevent->x - x));
      degree = 270 + (rad * (180.0 / PI));
    }
  }
  
  //Filter movement into 15 degree steps
  degree = (degree / 15) * 15;
  
  //Only draw when moved
  if(rotarydial->position != degree)
  {
    //Determine direction of movement
    if(degree > rotarydial->position)
    {
      //Detect counter clock wise through zero
      if((rotarydial->position < 20) && (degree > 340))
        dir = -1;
      else
        dir = 1;
    }
    else
    {
      //Detect clock wise through zero
      if((rotarydial->position > 340) && (degree < 20))
        dir = 1;
      else
        dir = -1;
    }
    
    //Save the new position
    rotarydial->position = degree;

    //Draw the new position
    RotaryDialDraw(rotarydial);

    //Check if there is an action on this rotary dial
    if(rotarydial->action)
      rotarydial->action(dir);
  }
}

//-----------------------------------------------------------------------------------------------------

void RotaryDialDown(MouseEvent *event)
{
  tagRotaryDial *rotarydial = event->data;
  
  //Starting with moving so draw a new position without delta checking
  RotaryDialDrawPosition(event, False);

  //Set the pointer for handling the moving
  rotarydial->mouse.move = RotaryDialMove;
}

//-----------------------------------------------------------------------------------------------------

void RotaryDialUp(MouseEvent *event)
{
  tagRotaryDial *rotarydial = event->data;
  
  //Starting with moving so draw a new position with delta checking to limit falling through the ends
  RotaryDialDrawPosition(event, True);

  //Set the pointer for handling the moving
  rotarydial->mouse.move = NULL;
}

//-----------------------------------------------------------------------------------------------------

void RotaryDialMove(MouseEvent *event)
{
  tagRotaryDial *rotarydial = event->data;
  
  //Move the indicator to the new position with delta checking to limit falling through the ends
  RotaryDialDrawPosition(event, True);
}

//-----------------------------------------------------------------------------------------------------
