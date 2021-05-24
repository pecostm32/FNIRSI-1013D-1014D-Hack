#ifndef BUTTON_H
#define BUTTON_H

#include "xlibfunctions.h"
#include "mousehandling.h"

//Position is given as top left of the bounding box the button is in
//The size of the button is fixed

#define BUTTON_ROUNDED_RECT    0
#define BUTTON_ARROW_UP        1
#define BUTTON_ARROW_DOWN      2

#define ButtonPanelColor        0x414244
#define ButtonCutoutColor       0x202020
#define ButtonLineColor         0xC8B393
#define ButtonUpBodyColor       0xE3D9CA
#define ButtonDownBodyColor     0xDBCDB9

#define ButtonSize              30


//Function pointer to handle the events
typedef void (*HANDLEBUTTON)(void);

typedef struct
{
  tagXlibContext *xc;               //Xlib context for drawing
  HANDLEBUTTON    action;           //Action to take on button down
  MouseRange      mouse;            //Mouse object for this button. Is used for setting the bounding box and to connect the handlers
  int             type;             //Type of button
  int             xpos;             //Un scaled x position
  int             ypos;             //Un scaled y position
  int             state;            //State of the button. Either up or down
} tagButton;


void ButtonSetup(tagXlibContext *xc, tagButton *button);
void ButtonDrawRoundedRect(tagButton *button);
void ButtonDrawArrowUp(tagButton *button);
void ButtonDrawArrowDown(tagButton *button);

void ButtonDown(MouseEvent *event);
void ButtonUp(MouseEvent *event);

void ButtonDrawArrow(tagXlibContext *xc, int xpos, int ypos, int size, int fillcolor, int linecolor, int orientation);


#endif /* BUTTON_H */

