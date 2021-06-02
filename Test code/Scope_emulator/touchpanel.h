//-----------------------------------------------------------------------------------------------------

#ifndef TOUCHPANEL_H
#define TOUCHPANEL_H

//-----------------------------------------------------------------------------------------------------

#include "xlibfunctions.h"
#include "mousehandling.h"

//-----------------------------------------------------------------------------------------------------

//Function pointer to handle the events
typedef void (*HANDLETOUCH)(MouseEvent *event);

typedef struct
{
  tagXlibContext *xc;               //Xlib context for drawing
  HANDLETOUCH     action;           //Action to take on button down
  MouseRange      mouse;            //Mouse object for this button. Is used for setting the bounding box and to connect the handlers
  int             xpos;             //Un scaled x position
  int             ypos;             //Un scaled y position
  int             width;            //Un scaled width
  int             height;           //Un scaled height
  int             state;            //Signal mouse up or down
} tagTouchPanel;

//-----------------------------------------------------------------------------------------------------

void TouchPanelSetup(tagXlibContext *xc, tagTouchPanel *touchpanel);

void TouchDown(MouseEvent *event);
void TouchUp(MouseEvent *event);
void TouchMove(MouseEvent *event);

//-----------------------------------------------------------------------------------------------------

#endif /* TOUCHPANEL_H */

