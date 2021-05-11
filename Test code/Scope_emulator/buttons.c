//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "buttons.h"

//-----------------------------------------------------------------------------------------------------

#define PI                         3.1415926535897932384
#define PI2                        6.2831853071795864769

#define CalcScaled(s) ((s) * xc->scaler)
#define CalcCoord(c)  (BORDER_SIZE + ((c) * xc->scaler))
#define CalcCoordX(x) (BORDER_SIZE + ((button->xpos + (x)) * xc->scaler))
#define CalcCoordY(y) (BORDER_SIZE + ((button->ypos + (y)) * xc->scaler))

//-----------------------------------------------------------------------------------------------------

void ButtonSetup(tagXlibContext *xc, tagButton *button)
{
  MouseRange *mouse = &button->mouse;

  button->xc = xc;
  
  //Setup the mouse actions
  mouse->data = button;
  mouse->move = NULL;
  mouse->down = ButtonDown;
  mouse->up   = ButtonUp;

  //Set the top left origin of the button for mouse scanning
  mouse->left = CalcCoordX(0);
  mouse->top  = CalcCoordY(0);

  //Set the bottom right extremes for the button to allow for mouse scanning
  mouse->right  = CalcCoordX(ButtonSize);
  mouse->bottom = CalcCoordY(ButtonSize);
  
  //Switch on type for drawing the correct button
  switch(button->type)
  {
    case BUTTON_ROUNDED_RECT:
      ButtonDrawRoundedRect(button);
      break;
      
    case BUTTON_ARROW_UP:
      ButtonDrawArrowUp(button);
      break;
      
    case BUTTON_ARROW_DOWN:
      ButtonDrawArrowDown(button);
      break;
  }
}

//-----------------------------------------------------------------------------------------------------

void ButtonDown(MouseEvent *event)
{
  tagButton *button = event->data;
  
  //Set state to pressed down
  button->state = 1;
  
  //Switch on type for drawing the correct button
  switch(button->type)
  {
    case BUTTON_ROUNDED_RECT:
      ButtonDrawRoundedRect(button);
      break;
      
    case BUTTON_ARROW_UP:
      ButtonDrawArrowUp(button);
      break;
      
    case BUTTON_ARROW_DOWN:
      ButtonDrawArrowDown(button);
      break;
  }
}

//-----------------------------------------------------------------------------------------------------

void ButtonUp(MouseEvent *event)
{
  tagButton *button = event->data;

  //Set state to released up
  button->state = 0;
  
  //Switch on type for drawing the correct button
  switch(button->type)
  {
    case BUTTON_ROUNDED_RECT:
      ButtonDrawRoundedRect(button);
      break;
      
    case BUTTON_ARROW_UP:
      ButtonDrawArrowUp(button);
      break;
      
    case BUTTON_ARROW_DOWN:
      ButtonDrawArrowDown(button);
      break;
  }
  
  //Check if there is an action on this button and execute it if so
  if(button->action)
    button->action();
}

//-----------------------------------------------------------------------------------------------------

void ButtonDrawRoundedRect(tagButton *button)
{
  tagXlibContext *xc = button->xc;

  int x = button->xpos + 2;
  int y = button->ypos + 2;
  int s = ButtonSize - 4;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, ButtonSize + 4, ButtonSize + 4, ButtonPanelColor);
  
  //Draw the panel cutout
  DrawFillRoundedRect(xc, button->xpos, button->ypos, 6, ButtonSize, ButtonSize, ButtonCutoutColor, ButtonCutoutColor, 1);

  //Draw the down body
  DrawFillRoundedRect(xc, x, y, 6, s, s, ButtonDownBodyColor, ButtonLineColor, 1);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    DrawFillRoundedRect(xc, button->xpos, button->ypos, 6, s, s, ButtonUpBodyColor, ButtonLineColor, 1);
  }  
}

//-----------------------------------------------------------------------------------------------------

void ButtonDrawArrowDown(tagButton *button)
{
  tagXlibContext *xc = button->xc;

  int x = button->xpos + 2;
  int y = button->ypos + 2;
  int s = ButtonSize - 4;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, ButtonSize + 4, ButtonSize + 4, ButtonPanelColor);

  //Draw the panel cutout
  ButtonDrawArrow(xc, button->xpos, button->ypos, ButtonSize, ButtonCutoutColor, ButtonCutoutColor, BUTTON_ARROW_DOWN);

  //Draw the down body
  ButtonDrawArrow(xc, x, y, s, ButtonDownBodyColor, ButtonLineColor, BUTTON_ARROW_DOWN);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    ButtonDrawArrow(xc, button->xpos, button->ypos, s, ButtonUpBodyColor, ButtonLineColor, BUTTON_ARROW_DOWN);
  }  
}

//-----------------------------------------------------------------------------------------------------

void ButtonDrawArrowUp(tagButton *button)
{
  tagXlibContext *xc = button->xc;

  int x = button->xpos + 2;
  int y = button->ypos + 2;
  int s = ButtonSize - 4;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, ButtonSize + 4, ButtonSize + 4, ButtonPanelColor);

  //Draw the panel cutout
  ButtonDrawArrow(xc, button->xpos, button->ypos, ButtonSize, ButtonCutoutColor, ButtonCutoutColor, BUTTON_ARROW_UP);

  //Draw the down body
  ButtonDrawArrow(xc, x, y, s, ButtonDownBodyColor, ButtonLineColor, BUTTON_ARROW_UP);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    ButtonDrawArrow(xc, button->xpos, button->ypos, s, ButtonUpBodyColor, ButtonLineColor, BUTTON_ARROW_UP);
  }  
}

//-----------------------------------------------------------------------------------------------------

void ButtonDrawArrow(tagXlibContext *xc, int xpos, int ypos, int size, int fillcolor, int linecolor, int orientation)
{
  //Setup coordinates for drawing the different parts
  int x = CalcCoord(xpos);
  int y = CalcCoord(ypos);
  int r = CalcScaled(4);
  int w = CalcScaled(size);

  double a = (30.0 / 180.0) * PI;
  double s = sin(a) * r;
  double c = cos(a) * r;
  
  int cd = r * 2;
  
  //By using arrays of object structs single function calls can be done  
  XArc       arcs[4];
  XPoint     points[7];
  XSegment   lines[3];
  
  if(orientation == BUTTON_ARROW_UP)
  {
    int x1 = x + r;
    int x2 = x + w;
    int x3 = x2 - r;
    int x4 = x2 - cd;
    int x5 = x + (w / 2);
    int y1 = y + w;
    int y2 = y1 - cd;
    int y3 = y + r - s;
    int y4 = y1 - r - s;
    
    //Setup for filling and drawing the 3 arcs
    arcs[0].x      = x5 - r;
    arcs[0].y      = y;
    arcs[0].width  = cd;
    arcs[0].height = cd;
    arcs[0].angle1 = Angle30;
    arcs[0].angle2 = Angle120;

    arcs[1].x      = x;
    arcs[1].y      = y2;
    arcs[1].width  = cd;
    arcs[1].height = cd;
    arcs[1].angle1 = Angle150;
    arcs[1].angle2 = Angle120;

    arcs[2].x      = x4;
    arcs[2].y      = y2;
    arcs[2].width  = cd;
    arcs[2].height = cd;
    arcs[2].angle1 = Angle270;
    arcs[2].angle2 = Angle120;

    //Setup for drawing the three outer lines
    lines[0].x1 = x5 - c;
    lines[0].x2 = x1 - c;
    lines[0].y1 = y3;
    lines[0].y2 = y4;

    lines[1].x1 = x5 + c;
    lines[1].x2 = x3 + c;
    lines[1].y1 = y3;
    lines[1].y2 = y4;

    lines[2].x1 = x1;
    lines[2].x2 = x3;
    lines[2].y1 = y1;
    lines[2].y2 = y1;

    //Setup points for the fill
    points[0].x = lines[0].x1;
    points[0].y = lines[0].y1;

    points[1].x = lines[0].x2;
    points[1].y = lines[0].y2;

    points[2].x = lines[2].x1;
    points[2].y = lines[2].y1;

    points[3].x = lines[2].x2;
    points[3].y = lines[2].y2;

    points[4].x = lines[1].x2;
    points[4].y = lines[1].y2;

    points[5].x = lines[1].x1;
    points[5].y = lines[1].y1;

    points[6].x = lines[0].x1;
    points[6].y = lines[0].y1;
  }
  else
  {
    int x1 = x + r;
    int x2 = x + w;
    int x3 = x2 - r;
    int x4 = x2 - cd;
    int x5 = x + (w / 2);
    int y1 = y + w;
    int y2 = y1 - cd;
    int y3 = y + r + s;
    int y4 = y1 - r + s;
    
    //Setup for filling and drawing the 3 arcs
    arcs[0].x      = x5 - r;
    arcs[0].y      = y2;
    arcs[0].width  = cd;
    arcs[0].height = cd;
    arcs[0].angle1 = Angle210;
    arcs[0].angle2 = Angle120;

    arcs[1].x      = x;
    arcs[1].y      = y;
    arcs[1].width  = cd;
    arcs[1].height = cd;
    arcs[1].angle1 = Angle90;
    arcs[1].angle2 = Angle120;

    arcs[2].x      = x4;
    arcs[2].y      = y;
    arcs[2].width  = cd;
    arcs[2].height = cd;
    arcs[2].angle1 = Angle330;
    arcs[2].angle2 = Angle120;

    //Setup for drawing the three outer lines
    lines[0].x1 = x5 - c;
    lines[0].x2 = x1 - c;
    lines[0].y1 = y4;
    lines[0].y2 = y3;

    lines[1].x1 = x5 + c;
    lines[1].x2 = x3 + c;
    lines[1].y1 = y4;
    lines[1].y2 = y3;

    lines[2].x1 = x1;
    lines[2].x2 = x3;
    lines[2].y1 = y;
    lines[2].y2 = y;

    //Setup points for the fill
    points[0].x = lines[0].x1;
    points[0].y = lines[0].y1;

    points[1].x = lines[0].x2;
    points[1].y = lines[0].y2;

    points[2].x = lines[2].x1;
    points[2].y = lines[2].y1;

    points[3].x = lines[2].x2;
    points[3].y = lines[2].y2;

    points[4].x = lines[1].x2;
    points[4].y = lines[1].y2;

    points[5].x = lines[1].x1;
    points[5].y = lines[1].y1;

    points[6].x = lines[0].x1;
    points[6].y = lines[0].y1;
  }
  
  //Filling the arcs from the center point
  XSetArcMode(xc->display, xc->gc, ArcPieSlice);

  //Setup the line based on given line width
  XSetLineAttributes(xc->display, xc->gc, 1, LineSolid, CapButt, JoinMiter);
  
  //Perform the fills first with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillArcs(xc->display, xc->win, xc->gc, arcs, 3);
  XFillPolygon(xc->display, xc->win, xc->gc, points, 7, Nonconvex, CoordModeOrigin);
  
  //Draw the lines on top of the fills and use the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawArcs(xc->display, xc->win, xc->gc, arcs, 3);
  XDrawSegments(xc->display, xc->win, xc->gc, lines, 3);
}
