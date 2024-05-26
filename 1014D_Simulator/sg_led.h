//-----------------------------------------------------------------------------------------------------

#ifndef LED_H
#define LED_H

//-----------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xlibfunctions.h"

//-----------------------------------------------------------------------------------------------------

#define LedBorderColor          0x226200    //One pixel wide border around the led
#define LedOnColor              0x98D800    //Body color of the led when on
#define LedOffColor             0x347400    //Body color of the led when off

//-----------------------------------------------------------------------------------------------------
//Position is given as top left of the bounding box the led is in

typedef struct
{
  tagXlibContext *xc;               //Xlib context for drawing
  int             state;            //State of the led. Either on or off
  int             xpos;             //Un scaled x position
  int             ypos;             //Un scaled y position
  int             diameter;         //Un scaled diameter
  int             offcolor;         //Color of the led when off
  int             oncolor;          //Color of the led when on
  int             edgecolor;        //Color of the ring around the led
  int             x;                //Scaled x position of the led
  int             y;                //Scaled y position of the led
  int             d;                //Scaled diameter of the led
} tagLed;

//-----------------------------------------------------------------------------------------------------

void LedSetup(tagXlibContext *xc, tagLed *led);
void LedDraw(tagLed *led);
void LedSetState(tagLed *led, int state);

//-----------------------------------------------------------------------------------------------------

#endif /* LED_H */

//-----------------------------------------------------------------------------------------------------
