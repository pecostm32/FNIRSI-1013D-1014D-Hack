#ifndef SG_BUTTON_H
#define SG_BUTTON_H

#include "xlibfunctions.h"
#include "mousehandling.h"

//Position is given as top left of the bounding box the button is in
//The size of the button is fixed

#define SG_BUTTON_ROUNDED_RECT    0
#define SG_BUTTON_ARROW_UP        1
#define SG_BUTTON_ARROW_DOWN      2
#define SG_BUTTON_ARROW_LEFT      3
#define SG_BUTTON_ARROW_RIGHT     4

#define SG_ButtonPanelColor        0x414244
#define SG_ButtonCutoutColor       0x202020
#define SG_ButtonLineColor         0xC8B393
#define SG_ButtonUpBodyColor       0xE3D9CA
#define SG_ButtonDownBodyColor     0xDBCDB9

#define SG_ButtonSize              30


//Function pointer to handle the events
typedef void (*HANDLESGBUTTON)(void);

typedef struct
{
  tagXlibContext *xc;               //Xlib context for drawing
  HANDLESGBUTTON  action;           //Action to take on button down
  MouseRange      mouse;            //Mouse object for this button. Is used for setting the bounding box and to connect the handlers
  int             type;             //Type of button
  int             xpos;             //Un scaled x position
  int             ypos;             //Un scaled y position
  int             width;            //Un scaled width
  int             height;           //Un scaled height
  int             state;            //State of the button. Either up or down
  char           *text;
  int             fontid;
  int             colorid;
} tagSG_Button;


void SG_ButtonSetup(tagXlibContext *xc, tagSG_Button *button);

void SG_ButtonDrawRoundedRect(tagSG_Button *button);
void SG_ButtonDrawArrow(tagSG_Button *button);

void SG_ButtonDown(MouseEvent *event);
void SG_ButtonUp(MouseEvent *event);

#endif /* SG_BUTTON_H */

