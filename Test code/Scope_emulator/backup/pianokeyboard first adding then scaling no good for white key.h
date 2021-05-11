#ifndef PIANOKEYBOARD_H
#define PIANOKEYBOARD_H

#include "xlibfunctions.h"
#include "mousehandling.h"

//Position is given as top left of the bounding box the piano keyboard is in
//The size of the piano keyboard is fixed

#define NUMBER_OF_OCTAVES                 5

#define NUMBER_WHITE_KEYS_PER_OCTAVE      7
#define NUMBER_BLACK_KEYS_PER_OCTAVE      5
#define NUMBER_OF_KEYS_PER_OCTAVE         (NUMBER_WHITE_KEYS_PER_OCTAVE + NUMBER_BLACK_KEYS_PER_OCTAVE)

#define NUMBER_OF_KEYS                    ((NUMBER_OF_OCTAVES * NUMBER_OF_KEYS_PER_OCTAVE) + 1)
#define NUMBER_OF_BLACK_KEYS              (NUMBER_OF_OCTAVES * NUMBER_BLACK_KEYS_PER_OCTAVE)

#define WhiteKeyHeight              450
#define WhiteKeyWidth                82
#define WhiteKeyEndRadius            10
#define WhiteKeyEndDiameter          (WhiteKeyEndRadius * 2)
#define WhiteKeyBackMaskHeight       39
#define WhiteKeyBackMaskYpos        420

#define BlackKeyHeight              282
#define BlackKeyUpHeight            249
#define BlackKeyWidth                46
#define BlackKeyEndRadius             6
#define BlackKeyNarrowOffset         13
#define StartOfFirstBlackKey         53
#define BlackKeyDistance             92
#define BlackKeyGroupDistance        57

#define OctaveWidth                 (NUMBER_WHITE_KEYS_PER_OCTAVE * WhiteKeyWidth)
#define KeyboardWidth              ((NUMBER_OF_OCTAVES * OctaveWidth) + WhiteKeyHeight)

#define PianoKeyTypeBlack               0
#define PianoKeyTypeWhiteC              1
#define PianoKeyTypeWhiteD              3
#define PianoKeyTypeWhiteE              5
#define PianoKeyTypeWhiteF              6
#define PianoKeyTypeWhiteG              8
#define PianoKeyTypeWhiteA             10
#define PianoKeyTypeWhiteB             12
#define PianoKeyTypeWhiteFull          13


#define WhiteKeyBodyColor           0xE0E0E0
#define WhiteKeyOuterLineColor      0x000000
#define WhiteFirstShadeColor        0x999999
#define WhiteSecondShadeColor       0xB9B9B9
#define WhiteKeyUpShadeStartColor   0xE1E1E1
#define WhiteKeyDownShadeStartColor 0xBEBEBE
#define WhiteKeyShadeAddColor       0x050505

#define BlackKeyBodyColor           0x0D0F0C
#define BlackKeyLineColor           0x60625F
#define BlackKeyBackGroundColor     0x484A47

//X positions used for scanning for which key is under the mouse pointer
typedef struct
{
  int xstart;   //Scaled x position where black key starts
  int xend;     //Scaled x position where black key ends
} tagPianoBlackKeyXRange;

typedef struct
{
  int type;        //Type of key (black or white)
  int xpos;
} tagPianoKey;

typedef struct
{
  tagXlibContext         *xc;               //Xlib context for drawing
  tagPianoKey            *keys;             //Pointer to an array of key structs
  tagPianoBlackKeyXRange *blackxranges;
  MouseRange              mouse;            //Mouse object for this object. Is used for setting the bounding box and to connect the handlers
  int                     xpos;             //Un scaled x position
  int                     ypos;             //Un scaled y position
  int                     backgroundcolor;  //Color of the parts underneath the keyboard. Needs to be the same as used for the front panel layout
  int                     scaledoctavewidth;
  int                     scaledwhitekeywidth;
  int                     scaledblackkeyheight;
} tagPianoKeyboard;


void PianoKeyboardSetup(tagXlibContext *xc, tagPianoKeyboard *keyboard);
void PianoKeyboardDrawOctave(tagPianoKeyboard *keyboard, int xpos, int keyid);

void PianoKeyboardDrawWhiteKey(tagPianoKeyboard *keyboard, tagPianoKey *key, Bool state);
void PianoKeyboardDrawBlackKey(tagPianoKeyboard *keyboard, tagPianoKey *key, Bool state);


void PianoKeyboardDown(MouseEvent *event);
void PianoKeyboardUp(MouseEvent *event);
void PianoKeyboardMove(MouseEvent *event);


#endif /* PIANOKEYBOARD_H */

