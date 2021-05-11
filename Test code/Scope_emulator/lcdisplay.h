#ifndef LCDISPLAY_H
#define LCDISPLAY_H

#include "xlibfunctions.h"

#define LcDisplayBackGroundColor      0x88C800
#define LcDisplayOffColor             0x78B000
#define LcDisplayOnColor              0x000000
#define LcDisplaytledgecolor          0x202020
#define LcDisplaybredgecolor          0xA0A0A0

//Position is given as top left of the bounding box the display is in

typedef struct
{
  tagXlibContext *xc;               //Xlib context for drawing
  int             xpos;             //Un scaled x position
  int             ypos;             //Un scaled y position
  int             chars;            //Number of characters on a line
  int             lines;            //Number of lines
  int             offcolor;         //Color of the dots when off
  int             oncolor;          //Color of the dots when on
  int             bgcolor;          //Color of the background
  int             tledgecolor;      //Color of the top left edge of the display
  int             bredgecolor;      //Color of the bottom right edge of the display
} tagLcDisplay;


void LcdDisplaySetup(tagXlibContext *xc, tagLcDisplay *display);
void LcdDisplayText(tagLcDisplay *display, int col, int row, char *text);
void LcdDisplayDraw(tagLcDisplay *display);
void LcdDisplayDrawChar(tagLcDisplay *display, int xpos, int ypos, char character);

#endif /* LCDISPLAY_H */

