#ifndef ROTARY_DIAL_H
#define ROTARY_DIAL_H

#include "xlibfunctions.h"
#include "mousehandling.h"

//Position is given as top left of the bounding box the rotary dial is in
//The size of the rotary dial is fixed

//Function pointer to handle the events
typedef void (*HANDLEROTARYDIAL)(int direction);

typedef struct
{
  tagXlibContext   *xc;               //Xlib context for drawing
  HANDLEROTARYDIAL  action;           //Action to take on rotary dial turned
  MouseRange        mouse;            //Mouse object for this button. Is used for setting the bounding box and to connect the handlers
  int               xpos;             //Un scaled x position
  int               ypos;             //Un scaled y position
  int               position;         //Position of the indicator on the cap of the rotary dial
} tagRotaryDial;


void RotaryDialSetup(tagXlibContext *xc, tagRotaryDial *rotarydial);
void RotaryDialDraw(tagRotaryDial *rotarydial);

void RotaryDialDrawPosition(MouseEvent *event, Bool deltacheck);

void RotaryDialDown(MouseEvent *event);
void RotaryDialUp(MouseEvent *event);
void RotaryDialMove(MouseEvent *event);

#endif /* ROTARY_DIAL_H */

