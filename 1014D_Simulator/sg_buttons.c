//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "sg_buttons.h"

//-----------------------------------------------------------------------------------------------------

#define PI                         3.1415926535897932384
#define PI2                        6.2831853071795864769

#define CalcScaled(s) ((s) * xc->scaler)
#define CalcCoord(c)  (BORDER_SIZE + ((c) * xc->scaler))
#define CalcCoordX(x) (BORDER_SIZE + ((button->xpos + (x)) * xc->scaler))
#define CalcCoordY(y) (BORDER_SIZE + ((button->ypos + (y)) * xc->scaler))

//-----------------------------------------------------------------------------------------------------

void SG_ButtonInternalDrawArrow(tagXlibContext *xc, int xpos, int ypos, int size, int fillcolor, int linecolor, int orientation);

//-----------------------------------------------------------------------------------------------------

void SG_ButtonSetup(tagXlibContext *xc, tagSG_Button *button)
{
  MouseRange *mouse = &button->mouse;

  button->xc = xc;
  
  //Setup the mouse actions
  mouse->data = button;
  mouse->move = NULL;
  mouse->down = SG_ButtonDown;
  mouse->up   = SG_ButtonUp;

  //Set the top left origin of the button for mouse scanning
  mouse->left = CalcCoordX(0);
  mouse->top  = CalcCoordY(0);

  //Set the bottom right extremes for the button to allow for mouse scanning
  mouse->right  = CalcCoordX(button->width);
  mouse->bottom = CalcCoordY(button->height);
  
  //Switch on type for drawing the correct button
  switch(button->type)
  {
    case SG_BUTTON_ROUNDED_RECT:
      SG_ButtonDrawRoundedRect(button);
      break;
      
    case SG_BUTTON_ARROW_UP:
    case SG_BUTTON_ARROW_DOWN:
    case SG_BUTTON_ARROW_LEFT:
    case SG_BUTTON_ARROW_RIGHT:
      SG_ButtonDrawArrow(button);
      break;
  }
}

//-----------------------------------------------------------------------------------------------------

void SG_ButtonDown(MouseEvent *event)
{
  tagSG_Button *button = event->data;
  
  //Set state to pressed down
  button->state = 1;
  
  //Switch on type for drawing the correct button
  switch(button->type)
  {
    case SG_BUTTON_ROUNDED_RECT:
      SG_ButtonDrawRoundedRect(button);
      break;
      
    case SG_BUTTON_ARROW_UP:
    case SG_BUTTON_ARROW_DOWN:
    case SG_BUTTON_ARROW_LEFT:
    case SG_BUTTON_ARROW_RIGHT:
      SG_ButtonDrawArrow(button);
      break;
  }
}

//-----------------------------------------------------------------------------------------------------

void SG_ButtonUp(MouseEvent *event)
{
  tagSG_Button *button = event->data;

  //Set state to released up
  button->state = 0;
  
  //Switch on type for drawing the correct button
  switch(button->type)
  {
    case SG_BUTTON_ROUNDED_RECT:
      SG_ButtonDrawRoundedRect(button);
      break;
      
    case SG_BUTTON_ARROW_UP:
    case SG_BUTTON_ARROW_DOWN:
    case SG_BUTTON_ARROW_LEFT:
    case SG_BUTTON_ARROW_RIGHT:
      SG_ButtonDrawArrow(button);
      break;
  }
  
  //Check if there is an action on this button and execute it if so
  if(button->action)
    button->action();
}

//-----------------------------------------------------------------------------------------------------

void SG_ButtonDrawRoundedRect(tagSG_Button *button)
{
  tagXlibContext *xc = button->xc;

  int x = button->xpos + 2;
  int y = button->ypos + 2;
  int w = button->width - 4;
  int h = button->height - 4;
  int c;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, button->width + 4, button->height + 4, SG_ButtonPanelColor);
  
  //Draw the panel cutout
  DrawFillRoundedRect(xc, button->xpos, button->ypos, 6, button->width, button->height, SG_ButtonCutoutColor, SG_ButtonCutoutColor, 1);

  //Check if up state active
  if(button->state == 0)
  {
    c = SG_ButtonDownBodyColor;
  }
  else
  {
    c = SG_ButtonUpBodyColor;
  }
  
  //Draw the down body
  DrawFillRoundedRect(xc, x, y, 6, w, h, c, SG_ButtonLineColor, 1);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    DrawFillRoundedRect(xc, button->xpos, button->ypos, 6, w, h, SG_ButtonUpBodyColor, SG_ButtonLineColor, 1);
    
    x = button->xpos;
    y = button->ypos;
  }
  
  //Add the text if needed
  if(button->text)
  {
    x += (button->width / 2);
    y += (button->height / 2) + 5;
    
    PlaceText(xc, x, y, button->text, button->fontid, button->colorid, ALIGN_TEXT_CENTER);
  }
}

//-----------------------------------------------------------------------------------------------------

void SG_ButtonDrawArrow(tagSG_Button *button)
{
  tagXlibContext *xc = button->xc;

  int x = button->xpos + 2;
  int y = button->ypos + 2;
  int s = button->width - 4;
  int c;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, button->width + 4, button->width + 4, SG_ButtonPanelColor);

  //Draw the panel cutout
  SG_ButtonInternalDrawArrow(xc, button->xpos, button->ypos, button->width, SG_ButtonCutoutColor, SG_ButtonCutoutColor, button->type);

  //Check if up state active
  if(button->state == 0)
  {
    c = SG_ButtonDownBodyColor;
  }
  else
  {
    c = SG_ButtonUpBodyColor;
  }
  
  //Draw the down body
  SG_ButtonInternalDrawArrow(xc, x, y, s, c, SG_ButtonLineColor, button->type);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    SG_ButtonInternalDrawArrow(xc, button->xpos, button->ypos, s, SG_ButtonUpBodyColor, SG_ButtonLineColor, button->type);
  }  
}

//-----------------------------------------------------------------------------------------------------

void SG_ButtonInternalDrawArrow(tagXlibContext *xc, int xpos, int ypos, int size, int fillcolor, int linecolor, int orientation)
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
  
  switch(orientation)
  {
    case SG_BUTTON_ARROW_UP:
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
      break;
    }
      
    case SG_BUTTON_ARROW_DOWN:
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
      break;
    }

    case SG_BUTTON_ARROW_LEFT:
    {
      int x2 = x + w;
      int x3 = x2 - r;
      int x4 = x2 - cd;
      int y1 = y + w;
      int y2 = y1 - cd;
      int y3 = y + (w / 2);

      //Setup for filling and drawing the 3 arcs
      arcs[0].x      = x;
      arcs[0].y      = y3 - r;
      arcs[0].width  = cd;
      arcs[0].height = cd;
      arcs[0].angle1 = Angle120;
      arcs[0].angle2 = Angle120;

      arcs[1].x      = x4;
      arcs[1].y      = y;
      arcs[1].width  = cd;
      arcs[1].height = cd;
      arcs[1].angle1 = Angle330;
      arcs[1].angle2 = Angle120;

      arcs[2].x      = x4;
      arcs[2].y      = y2;
      arcs[2].width  = cd;
      arcs[2].height = cd;
      arcs[2].angle1 = Angle270;
      arcs[2].angle2 = Angle120;

      //Setup for drawing the three outer lines
      lines[0].x1 = x;
      lines[0].x2 = x3;
      lines[0].y1 = y3 - s;
      lines[0].y2 = y;

      lines[1].x1 = x;
      lines[1].x2 = x3;
      lines[1].y1 = y3 + s;
      lines[1].y2 = y1;

      lines[2].x1 = x2;
      lines[2].x2 = x2;
      lines[2].y1 = y + r;
      lines[2].y2 = y1 - r;

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
      break;
    }

    case SG_BUTTON_ARROW_RIGHT:
    {
      int x1 = x + r;
      int x2 = x + w;
      int x4 = x2 - cd;
      int y1 = y + w;
      int y2 = y1 - cd;
      int y3 = y + (w / 2);

      //Setup for filling and drawing the 3 arcs
      arcs[0].x      = x4;
      arcs[0].y      = y3 - r;
      arcs[0].width  = cd;
      arcs[0].height = cd;
      arcs[0].angle1 = Angle300;
      arcs[0].angle2 = Angle120;

      arcs[1].x      = x;
      arcs[1].y      = y;
      arcs[1].width  = cd;
      arcs[1].height = cd;
      arcs[1].angle1 = Angle90;
      arcs[1].angle2 = Angle120;

      arcs[2].x      = x;
      arcs[2].y      = y2;
      arcs[2].width  = cd;
      arcs[2].height = cd;
      arcs[2].angle1 = Angle150;
      arcs[2].angle2 = Angle120;

      //Setup for drawing the three outer lines
      lines[0].x1 = x2;
      lines[0].x2 = x1;
      lines[0].y1 = y3 - s;
      lines[0].y2 = y;

      lines[1].x1 = x2;
      lines[1].x2 = x1;
      lines[1].y1 = y3 + s;
      lines[1].y2 = y1;

      lines[2].x1 = x;
      lines[2].x2 = x;
      lines[2].y1 = y + r;
      lines[2].y2 = y1 - r;

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
      break;
    }
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
