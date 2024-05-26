#ifndef SG_ROTARY_DIAL_H
#define SG_ROTARY_DIAL_H

#include "xlibfunctions.h"
#include "mousehandling.h"

//Position is given as top left of the bounding box the rotary dial is in
//The size of the rotary dial is fixed

//Function pointer to handle the events
typedef void (*HANDLESGROTARYDIAL)(int direction);

typedef struct
{
  tagXlibContext   *xc;               //Xlib context for drawing
  HANDLESGROTARYDIAL  action;           //Action to take on rotary dial turned
  MouseRange        mouse;            //Mouse object for this button. Is used for setting the bounding box and to connect the handlers
  int               xpos;             //Un scaled x position
  int               ypos;             //Un scaled y position
  int               position;         //Position of the indicator on the cap of the rotary dial
} tagSG_RotaryDial;


void SG_RotaryDialSetup(tagXlibContext *xc, tagSG_RotaryDial *rotarydial);
void SG_RotaryDialDraw(tagSG_RotaryDial *rotarydial);

void SG_RotaryDialDrawPosition(MouseEvent *event, Bool deltacheck);

void SG_RotaryDialDown(MouseEvent *event);
void SG_RotaryDialUp(MouseEvent *event);
void SG_RotaryDialMove(MouseEvent *event);

#endif /* SG_ROTARY_DIAL_H */

