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

void ButtonInternalDrawArrowIcon(tagXlibContext *xc, int xpos, int ypos, int orientation);
void ButtonInternalDrawArrow(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor, int linecolor, int orientation);
void ButtonInternalDrawDiamond(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor, int linecolor, int linewidth);

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
  mouse->right  = CalcCoordX(button->width);
  mouse->bottom = CalcCoordY(button->height);
  
  //Switch on type for drawing the correct button
  switch(button->type)
  {
    case BUTTON_ROUNDED_RECT:
      ButtonDrawRoundedRect(button);
      break;
      
    case BUTTON_ARROW_UP:
    case BUTTON_ARROW_DOWN:
    case BUTTON_ARROW_LEFT:
    case BUTTON_ARROW_RIGHT:
      ButtonDrawArrow(button);
      break;
      
    case BUTTON_DIAMOND:
      ButtonDrawDiamond(button);
      break;
      
    case BUTTON_ANGLES_TOP:
    case BUTTON_ANGLES_BOTTOM:
      ButtonDrawArrow(button);
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
    case BUTTON_ARROW_DOWN:
    case BUTTON_ARROW_LEFT:
    case BUTTON_ARROW_RIGHT:
      ButtonDrawArrow(button);
      break;
      
    case BUTTON_DIAMOND:
      ButtonDrawDiamond(button);
      break;
      
    case BUTTON_ANGLES_TOP:
    case BUTTON_ANGLES_BOTTOM:
      ButtonDrawArrow(button);
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
    case BUTTON_ARROW_DOWN:
    case BUTTON_ARROW_LEFT:
    case BUTTON_ARROW_RIGHT:
      ButtonDrawArrow(button);
      break;
      
    case BUTTON_DIAMOND:
      ButtonDrawDiamond(button);
      break;
      
    case BUTTON_ANGLES_TOP:
    case BUTTON_ANGLES_BOTTOM:
      ButtonDrawArrow(button);
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
  tagButtonColors *buttoncolors = button->buttoncolors;

  int x = button->xpos + 1;
  int y = button->ypos + 1;
  int w = button->width - 2;
  int h = button->height - 2;
  int c;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, button->width + 4, button->height + 4, button->backgroundcolor);
  
  //Draw the panel cutout
  DrawFillRoundedRect(xc, button->xpos, button->ypos, button->radius, button->width, button->height, buttoncolors->buttoncutoutcolor, buttoncolors->buttoncutoutcolor, 1);

  //Check if up state active
  if(button->state == 0)
  {
    c = buttoncolors->buttondownbodycolor;
  }
  else
  {
    c = buttoncolors->buttonupbodycolor;
  }
  
  //Draw the down body
  DrawFillRoundedRect(xc, x, y, button->radius, w, h, c, buttoncolors->buttonlinecolor, 1);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    DrawFillRoundedRect(xc, button->xpos, button->ypos, button->radius, w, h, buttoncolors->buttonupbodycolor, buttoncolors->buttonlinecolor, 1);
  }
  
  //Add the text if needed
  if(button->text)
  {
    XGlyphInfo extents;

    //Get the height for centering the text on the button
    XftTextExtentsUtf8(xc->display, xc->font[button->fontid], button->text, strlen(button->text), &extents);
    
    //Calculate the base position of the text
    x += (button->width / 2);
    y += (button->height / 2) + (extents.height / 2);
    
    //Depending on the state shift the text to give the impression of the button moving up or down
    if(button->state == 0)
    {
      x -= 1;
      y -= 1;
    }
    else
    {
      x += 1;
    }
    
    PlaceText(xc, x, y, button->text, button->fontid, button->textcolorid, ALIGN_TEXT_CENTER);
  }
}

//-----------------------------------------------------------------------------------------------------

void ButtonDrawDiamond(tagButton *button)
{
  tagXlibContext  *xc = button->xc;
  tagButtonColors *buttoncolors = button->buttoncolors;

  int x = button->xpos + 1;
  int y = button->ypos + 1;
  int w = button->width - 2;
  int h = button->height - 2;
  int c;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, button->width + 4, button->height + 4, button->backgroundcolor);
  
  //Draw the panel cutout
  ButtonInternalDrawDiamond(xc, button->xpos, button->ypos, button->width, button->height, buttoncolors->buttoncutoutcolor, buttoncolors->buttoncutoutcolor, 1);

  //Check if up state active
  if(button->state == 0)
  {
    c = buttoncolors->buttondownbodycolor;
  }
  else
  {
    c = buttoncolors->buttonupbodycolor;
  }
  
  //Draw the down body
  ButtonInternalDrawDiamond(xc, x, y, w, h, c, buttoncolors->buttonlinecolor, 1);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    ButtonInternalDrawDiamond(xc, button->xpos, button->ypos, w, h, buttoncolors->buttonupbodycolor, buttoncolors->buttonlinecolor, 1);
  }
  
  //Add the text if needed
  if(button->text)
  {
    XGlyphInfo extents;

    //Get the height for centering the text on the button
    XftTextExtentsUtf8(xc->display, xc->font[button->fontid], button->text, strlen(button->text), &extents);
    
    //Calculate the base position of the text
    x += (button->width / 2);
    y += (button->height / 2) + (extents.height / 2);
    
    //Depending on the state shift the text to give the impression of the button moving up or down
    if(button->state == 0)
    {
      x -= 1;
      y -= 1;
    }
    else
    {
      x += 1;
    }
    
    PlaceText(xc, x, y, button->text, button->fontid, button->textcolorid, ALIGN_TEXT_CENTER);
  }
}

//-----------------------------------------------------------------------------------------------------

void ButtonDrawArrow(tagButton *button)
{
  tagXlibContext  *xc = button->xc;
  tagButtonColors *buttoncolors = button->buttoncolors;

  int x = button->xpos + 1;
  int y = button->ypos + 1;
  int w = button->width - 2;
  int h = button->height - 2;
  int c;
  
  //Clear the panel before redrawing
  FillRect(xc, button->xpos - 2, button->ypos - 2, button->width + 4, button->height + 4, button->backgroundcolor);

  //Draw the panel cutout
  ButtonInternalDrawArrow(xc, button->xpos, button->ypos, button->width, button->height, buttoncolors->buttoncutoutcolor, buttoncolors->buttoncutoutcolor, button->type);

  //Check if up state active
  if(button->state == 0)
  {
    c = buttoncolors->buttondownbodycolor;
  }
  else
  {
    c = buttoncolors->buttonupbodycolor;
  }
  
  //Draw the down body
  ButtonInternalDrawArrow(xc, x, y, w, h, c, buttoncolors->buttonlinecolor, button->type);
  
  //Check if up state active
  if(button->state == 0)
  {
    //If so draw the up body
    ButtonInternalDrawArrow(xc, button->xpos, button->ypos, w, h, buttoncolors->buttonupbodycolor, buttoncolors->buttonlinecolor, button->type);
  }
  
  //Switch on type for drawing the button icon or place the text
  switch(button->type)
  {
    case BUTTON_ARROW_UP:
    case BUTTON_ARROW_DOWN:
    case BUTTON_ARROW_LEFT:
    case BUTTON_ARROW_RIGHT:
      //Also a quick hack to just draw the needed icons
      //Check if up state active
      if(button->state == 0)
      {
        ButtonInternalDrawArrowIcon(xc, button->xpos + (button->width / 2) - 1, button->ypos + (button->height / 2), button->type);
      }
      else
      {
        ButtonInternalDrawArrowIcon(xc, button->xpos + (button->width / 2) + 1, button->ypos + (button->height / 2) + 1, button->type);
      }
      break;
      
    case BUTTON_ANGLES_TOP:
      //Add the text if needed
      //Bit of a hack to do two lines of text on this button
      if(button->text)
      {
        //Calculate the base position of the text
        x += (button->width / 2);
        y += 24;

        //Depending on the state shift the text to give the impression of the button moving up or down
        if(button->state == 0)
        {
          x -= 1;
          y -= 1;
        }
        else
        {
          x += 1;
        }

        PlaceText(xc, x, y, "RUN", button->fontid, button->textcolorid, ALIGN_TEXT_CENTER);
        PlaceText(xc, x, y + 16, "STOP", button->fontid, button->textcolorid, ALIGN_TEXT_CENTER);
      }
      break;
      
    case BUTTON_ANGLES_BOTTOM:
      //Add the text if needed
      if(button->text)
      {
        //Calculate the base position of the text
        x += (button->width / 2);
        y += 28;

        //Depending on the state shift the text to give the impression of the button moving up or down
        if(button->state == 0)
        {
          x -= 1;
          y -= 1;
        }
        else
        {
          x += 1;
        }

        PlaceText(xc, x, y, button->text, button->fontid, button->textcolorid, ALIGN_TEXT_CENTER);
      }
      break;
  }
}

//-----------------------------------------------------------------------------------------------------

void ButtonInternalDrawArrowIcon(tagXlibContext *xc, int xpos, int ypos, int orientation)
{
  //Setup coordinates for drawing the different parts
  int x = CalcCoord(xpos);
  int y = CalcCoord(ypos);
  int s = CalcScaled(5);
  
  //By using arrays of object structures single function calls can be done  
  XPoint points[4];
  
  switch(orientation)
  {
    case BUTTON_ARROW_UP:
    {
      //Setup points for the fill
      points[0].x = x;
      points[0].y = y - s;

      points[1].x = x + s;
      points[1].y = y + s;

      points[2].x = x - s;
      points[2].y = y + s;

      points[3].x = x;
      points[3].y = y - s;
      break;
    }
      
    case BUTTON_ARROW_DOWN:
    {
      //Setup points for the fill
      points[0].x = x - s;
      points[0].y = y - s;

      points[1].x = x + s;
      points[1].y = y - s;

      points[2].x = x;
      points[2].y = y + s;

      points[3].x = x - s;
      points[3].y = y - s;
      break;
    }

    case BUTTON_ARROW_LEFT:
    {
      //Setup points for the fill
      points[0].x = x - s;
      points[0].y = y;

      points[1].x = x + s;
      points[1].y = y - s;

      points[2].x = x + s;
      points[2].y = y + s;

      points[3].x = x - s;
      points[3].y = y;
      break;
    }

    case BUTTON_ARROW_RIGHT:
    {
      //Setup points for the fill
      points[0].x = x - s;
      points[0].y = y - s;

      points[1].x = x + s;
      points[1].y = y;

      points[2].x = x - s;
      points[2].y = y + s;

      points[3].x = x - s;
      points[3].y = y - s;
      break;
    }
  }

  //Setup the line based on given line width
  XSetLineAttributes(xc->display, xc->gc, 1, LineSolid, CapButt, JoinMiter);
  
  //Make black arrows
  XSetForeground(xc->display, xc->gc, 0x000000);
  XFillPolygon(xc->display, xc->win, xc->gc, points, 4, Nonconvex, CoordModeOrigin);
}

//-----------------------------------------------------------------------------------------------------

void ButtonInternalDrawArrow(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor, int linecolor, int orientation)
{
  //Setup coordinates for drawing the different parts
  int x = CalcCoord(xpos);
  int y = CalcCoord(ypos);
  int w = CalcScaled(width);
  int h = CalcScaled(height);
  int d = ((width + height) * 3) / 20;
  int xe = x + w;
  int ye = y + h;
  
  //By using arrays of object structures single function calls can be done  
  XPoint points[7];
  
  switch(orientation)
  {
    case BUTTON_ARROW_UP:
    case BUTTON_ANGLES_TOP:
    {
      int x1 = x + d;
      int y1 = y + d;

      //Setup points for the fill
      points[0].x = x1;
      points[0].y = y;

      points[1].x = xe - d;
      points[1].y = y;

      points[2].x = xe;
      points[2].y = y1;

      points[3].x = xe;
      points[3].y = ye;

      points[4].x = x;
      points[4].y = ye;

      points[5].x = x;
      points[5].y = y1;

      points[6].x = x1;
      points[6].y = y;
      break;
    }
      
    case BUTTON_ARROW_DOWN:
    case BUTTON_ANGLES_BOTTOM:
    {
      int y1 = ye - d;

      //Setup points for the fill
      points[0].x = x;
      points[0].y = y;

      points[1].x = xe;
      points[1].y = y;

      points[2].x = xe;
      points[2].y = y1;

      points[3].x = xe - d;
      points[3].y = ye;

      points[4].x = x + d;
      points[4].y = ye;

      points[5].x = x;
      points[5].y = y1;

      points[6].x = x;
      points[6].y = y;
      break;
    }

    case BUTTON_ARROW_LEFT:
    {
      int x1 = x + d;

      //Setup points for the fill
      points[0].x = x1;
      points[0].y = y;

      points[1].x = xe;
      points[1].y = y;

      points[2].x = xe;
      points[2].y = ye;

      points[3].x = x1;
      points[3].y = ye;

      points[4].x = x;
      points[4].y = ye - d;

      points[5].x = x;
      points[5].y = y + d;

      points[6].x = x1;
      points[6].y = y;
      break;
    }

    case BUTTON_ARROW_RIGHT:
    {
      int x1 = xe - d;

      //Setup points for the fill
      points[0].x = x;
      points[0].y = y;

      points[1].x = x1;
      points[1].y = y;

      points[2].x = xe;
      points[2].y = y + d;

      points[3].x = xe;
      points[3].y = ye - d;

      points[4].x = x1;
      points[4].y = ye;

      points[5].x = x;
      points[5].y = ye;

      points[6].x = x;
      points[6].y = y;
      break;
    }
  }

  //Setup the line based on given line width
  XSetLineAttributes(xc->display, xc->gc, 1, LineSolid, CapButt, JoinMiter);
  
  //Perform the fills first with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillPolygon(xc->display, xc->win, xc->gc, points, 7, Nonconvex, CoordModeOrigin);
  
  //Draw the lines on top of the fills and use the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawLines(xc->display, xc->win, xc->gc, points, 7, CoordModeOrigin);
}

//-----------------------------------------------------------------------------------------------------

void ButtonInternalDrawDiamond(tagXlibContext *xc, int xpos, int ypos, int width, int height, int fillcolor, int linecolor, int linewidth)
{
  //Setup coordinates for drawing the different parts
  int x = BORDER_SIZE + (xpos * xc->scaler);
  int y = BORDER_SIZE + (ypos * xc->scaler);
  int w = width * xc->scaler;
  int h = height * xc->scaler;
  int dx = ((w * 3) / 10);
  int dy = ((h * 3) / 10);
  int xs = x + dx;
  int xe = x + w;
  int ye = y + h;
  
  //By using arrays of object structures single function calls can be done  
  XPoint points[7];
  
  //Setup for drawing the four outer lines
  points[0].x = xs;
  points[0].y = y;
  
  points[1].x = xe;
  points[1].y = y;

  points[2].x = xe;
  points[2].y = y + dy;

  points[3].x = xe - dx;
  points[3].y = ye;

  points[4].x = x;
  points[4].y = ye;

  points[5].x = x;
  points[5].y = ye - dy;

  points[6].x = xs;
  points[6].y = y;
  
  //Setup the line based on given line width
  XSetLineAttributes(xc->display, xc->gc, linewidth, LineSolid, CapButt, JoinMiter);

  //Perform the fill first with the fill color
  XSetForeground(xc->display, xc->gc, fillcolor);
  XFillPolygon(xc->display, xc->win, xc->gc, points, 7, Nonconvex, CoordModeOrigin);
  
  //Draw the lines on top of the fill and use the line color
  XSetForeground(xc->display, xc->gc, linecolor);
  XDrawLines(xc->display, xc->win, xc->gc, points, 7, CoordModeOrigin);
}

//-----------------------------------------------------------------------------------------------------
