//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include "led.h"

void LedSetup(tagXlibContext *xc, tagLed *led)
{
  led->xc = xc;
  
  led->x = BORDER_SIZE + (led->xpos * xc->scaler);
  led->y = BORDER_SIZE + (led->ypos * xc->scaler);
  led->d = led->diameter * xc->scaler;
  
  LedDraw(led);
}

//-----------------------------------------------------------------------------------------------------

void LedDraw(tagLed *led)
{
  tagXlibContext *xc = led->xc;
  
  //Set the body color of the led based on the state
  if(led->state)
    XSetForeground(xc->display, xc->gc, led->oncolor);
  else
    XSetForeground(xc->display, xc->gc, led->offcolor);

  XFillArc(xc->display, xc->win, xc->gc, led->x, led->y, led->d, led->d, Angle0, Angle360);
  
  XSetLineAttributes(xc->display, xc->gc, 1, LineSolid, CapButt, JoinMiter);
  XSetForeground(xc->display, xc->gc, led->edgecolor);
  XDrawArc(xc->display, xc->win, xc->gc, led->x, led->y, led->d, led->d, Angle0, Angle360);
  
  //Make sure the change is processed on screen
  XFlush(xc->display);
}

//-----------------------------------------------------------------------------------------------------

void LedSetState(tagLed *led, int state)
{
  if(state)
    led->state = 1;
  else
    led->state = 0;
    
  LedDraw(led);
}

//-----------------------------------------------------------------------------------------------------

