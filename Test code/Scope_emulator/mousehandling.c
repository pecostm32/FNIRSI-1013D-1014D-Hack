//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include "mousehandling.h"

MouseRange *currentrange = NULL;
Bool IsDown = False;


void MouseDown(XEvent *event)
{
  MouseEvent e;
  
  //Only handle left mouse button
  if(event->xbutton.button == Button1)
  {
    //Signal mouse button is down
    IsDown = True;
    
    //Check if there is an active range
    if(currentrange)
    {
      //Call the handler for down if present
      if(currentrange->down)
      {
        //Setup the mouse event
        e.event = event;
        e.data  = currentrange->data;
      
        //Call the actual handler
        currentrange->down(&e);
      }
    }
  }
}

void MouseUp(MouseRange *range, XEvent *event)
{
  MouseEvent e;
  
  //Only handle left mouse button
  if(event->xbutton.button == Button1)
  {
    //Signal mouse button is up again
    IsDown = False;
    
    //Check if there is an active range
    if(currentrange)
    {
      //Call the handler for down if present
      if(currentrange->up)
      {
        //Setup the mouse event
        e.event = event;
        e.data  = currentrange->data;
      
        //Call the actual handler
        currentrange->up(&e);
      }
    }
    
    //Rescan to see if cursor is in range of an object to release the previous if moved out of it
    currentrange = MouseScan(range, event->xmotion.x, event->xmotion.y);
  }
}

void MouseMove(MouseRange *range, XEvent *event)
{
  MouseEvent e;

  //See if cursor is in range of an object
  range = MouseScan(range, event->xmotion.x, event->xmotion.y);

  //Check if cursor moved out the current range
  if(range != currentrange)
  {
    //If so handle the out event for the previous range if active
    if(currentrange)
    {
      //See if an out function is specified for this range
      if(currentrange->out)
      {
        //Setup the mouse event
        e.event = event;
        e.data  = currentrange->data;
        
        //Call the actual handler
        currentrange->out(&e);
      }
    }
    
    //Check if there is no button down action active
    if(IsDown == False)
    {
      //If so update the current range to the new one
      currentrange = range;
    }
  }

  //Check if movement for an active current range
  if(currentrange)
  {
    //Call the handler for move if present
    if(currentrange->move)
    {
      //Setup the mouse event
      e.event = event;
      e.data  = currentrange->data;

      //Call the actual handler
      currentrange->move(&e);
    }
  }
}


MouseRange *MouseScan(MouseRange *range, int x, int y)
{
  while(range)
  {
    if((x >= range->left) && (x <= range->right) && (y >= range->top) && (y <= range->bottom))
      break;
    
    range = range->previous;
  }
  
  return(range);
}

