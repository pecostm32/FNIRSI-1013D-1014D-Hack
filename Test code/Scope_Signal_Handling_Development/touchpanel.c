//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "touchpanel.h"

//-----------------------------------------------------------------------------------------------------

#define CalcScaled(s) ((s) * xc->scaler)
#define CalcCoord(c)  (BORDER_SIZE + ((c) * xc->scaler))
#define CalcCoordX(x) (BORDER_SIZE + ((touchpanel->xpos + (x)) * xc->scaler))
#define CalcCoordY(y) (BORDER_SIZE + ((touchpanel->ypos + (y)) * xc->scaler))

//-----------------------------------------------------------------------------------------------------

void TouchPanelSetup(tagXlibContext *xc, tagTouchPanel *touchpanel)
{
  MouseRange *mouse = &touchpanel->mouse;
  
  touchpanel->xc = xc;
  
  //Set the touchpanel pointer for mouse handling
  mouse->data = touchpanel;
  
  //Set the top left origin of the touch panel for mouse scanning
  mouse->left = CalcCoordX(0);
  mouse->top  = CalcCoordY(0);
  
  //Set the bottom right extremes for the button to allow for mouse scanning
  mouse->right  = CalcCoordX(touchpanel->width);
  mouse->bottom = CalcCoordY(touchpanel->height);
  
  //Setup the mouse actions
  mouse->down = TouchDown;
  mouse->up   = TouchUp;
  mouse->move = TouchMove;
}

//-----------------------------------------------------------------------------------------------------

void TouchDown(MouseEvent *event)
{
  tagTouchPanel *touchpanel = event->data;
  
  //Set state to pressed down
  touchpanel->state = 1;

  //Check if there is an action on this touch panel and execute it if so
  if(touchpanel->action)
    touchpanel->action(event);
}

//-----------------------------------------------------------------------------------------------------

void TouchUp(MouseEvent *event)
{
  tagTouchPanel *touchpanel = event->data;

  //Set state to released up
  touchpanel->state = 0;
  
  //Check if there is an action on this touch panel and execute it if so
  if(touchpanel->action)
    touchpanel->action(event);
}

//-----------------------------------------------------------------------------------------------------

void TouchMove(MouseEvent *event)
{
  tagTouchPanel *touchpanel = event->data;
  
  //Check if there is an action on this touch panel and execute it if so
  if((touchpanel->action) && (touchpanel->state))
    touchpanel->action(event);
}

//----------------------------------------------------------------------------------------------------------------------------------
