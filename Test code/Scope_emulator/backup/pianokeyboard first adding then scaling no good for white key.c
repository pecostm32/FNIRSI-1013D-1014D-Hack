//-----------------------------------------------------------------------------------------------------
//
//-----------------------------------------------------------------------------------------------------

#include "pianokeyboard.h"

//Tables for getting the right key id within an octave
const int  whitekeyconvtab[] = { 0, 2, 4, 5, 7, 9, 11 };
const int  blackkeyconvtab[] = { 1, 3, 6, 8, 10 };

//Table for determining if a key is a black key. Index 0 is used for drawing a whole white key without cutout for a black key
const Bool isblackkey[] = { False, False, True, False, True, False, False, True, False, True, False, True, False };

#define CalcScaled(d) ((d) * xc->scaler)

#define CalcCoord(c)  BORDER_SIZE + (((c) + 0.5) * xc->scaler)
#define CalcCoordX(x) BORDER_SIZE + ((keyboard->xpos + (x) + 0.5) * xc->scaler)
#define CalcCoordY(y) BORDER_SIZE + ((keyboard->ypos + (y) + 0.5) * xc->scaler)


void PianoKeyboardSetup(tagXlibContext *xc, tagPianoKeyboard *keyboard)
{
  MouseRange  *mouse = &keyboard->mouse;
  tagPianoKey *key;
  
  int i,x;

  //Set the context for this object
  keyboard->xc = xc;
  
  //Fill in the mouserange struct to be able to use the keyboard via the mouse
  mouse->left   = CalcCoord(keyboard->xpos);
  mouse->right  = CalcCoord(keyboard->xpos + KeyboardWidth);
  mouse->top    = CalcCoord(keyboard->ypos);
  mouse->bottom = CalcCoord(keyboard->ypos + WhiteKeyHeight);
  
  mouse->data = keyboard;
  mouse->move = NULL;
  mouse->down = PianoKeyboardDown;
  mouse->up   = PianoKeyboardUp;

  //For determining which key the mouse pointer is on a set of scaled metrics are needed
  keyboard->scaledoctavewidth = CalcScaled(OctaveWidth);
  keyboard->scaledwhitekeywidth = CalcScaled(WhiteKeyWidth);
  keyboard->scaledblackkeyheight = CalcScaled(BlackKeyHeight);
  
  //Unscaled x offset of the first black key
  x = StartOfFirstBlackKey;
  
  //Calculate the scaled x offsets for the 5 black keys in an octave
  for(i=0;i<NUMBER_BLACK_KEYS_PER_OCTAVE;i++)
  {
    //Scale the start and end offsets
    keyboard->blackxranges[i].xstart = CalcScaled(x);
    keyboard->blackxranges[i].xend = CalcScaled(x + BlackKeyWidth);
    
    //Go to the next offset
    x += BlackKeyDistance;
    
    //Check if next black key has two whites in between
    if(i == 1)
      x += BlackKeyGroupDistance;
  }
  
  //Start offset of the first octave
  x = 0;
  
  //Draw all the octaves
  for(i=0;i<NUMBER_OF_OCTAVES;i++)
  {
    //Draw current octave
    PianoKeyboardDrawOctave(keyboard, x, i * NUMBER_OF_KEYS_PER_OCTAVE);
    
    //Step up to next offset
    x += OctaveWidth;
  }
  
  //Draw the upper C key
  key = &keyboard->keys[NUMBER_OF_KEYS - 1];
  key->type = PianoKeyTypeWhiteFull;
  key->xpos = CalcCoordX(x);

  //Go and draw a white key
  PianoKeyboardDrawWhiteKey(keyboard, key, False);
}


void PianoKeyboardDrawOctave(tagPianoKeyboard *keyboard, int xpos, int keyid)
{
  tagXlibContext *xc = keyboard->xc;
  tagPianoKey *key;
  
  int i;
  int xb = xpos + StartOfFirstBlackKey;
  int xw = xpos;
  
  //Draw the separate keys for this octave. 7 white keys and 5 black keys
  for(i=1;i<NUMBER_OF_KEYS_PER_OCTAVE+1;i++,keyid++)
  {
    //Get the data for this key
    key = &keyboard->keys[keyid];
    
    //Check if current key is a black one
    if(isblackkey[i] == True)
    {
      //Setup for this key
      key->type = PianoKeyTypeBlack;
      key->xpos = xb;
      
      //Go and draw a black key in the up position
//      PianoKeyboardDrawBlackKey(keyboard, key, False);
      
      //Skip to next black key offset
      xb += BlackKeyDistance;
      
      //Check if last black key in first group (the two black keys between C, D and E)
      if(i == 4)
        xb += BlackKeyGroupDistance;
    }
    else
    {
      //Setup for this key. The index also specifies the white key type
      key->type = i;
      key->xpos = xw;

      //Go and draw a white key
      PianoKeyboardDrawWhiteKey(keyboard, key, False);
      
      //Skip to next white key offset
      xw += WhiteKeyWidth;
    }
  }
}


void PianoKeyboardDrawWhiteKey(tagPianoKeyboard *keyboard, tagPianoKey *key, Bool state)
{
  tagXlibContext *xc = keyboard->xc;
  XArc       arcs[3];
  XRectangle rects[4];
  XSegment   lines[8];
  
  //Setup coordinates for drawing the different parts
  int r = CalcScaled(WhiteKeyEndRadius);
  int w = CalcScaled(WhiteKeyWidth);
  int h = CalcScaled(WhiteKeyHeight);
  int x = CalcCoordX(key->xpos);
  int y = CalcCoordY(0);
  
  
  int cd = CalcScaled(WhiteKeyEndDiameter);

  int w1 = 0;
  int w2 = CalcScaled(WhiteKeyWidth - WhiteKeyEndDiameter);
  
  int h1 = CalcScaled(BlackKeyHeight);
  int h2 = CalcScaled(WhiteKeyHeight - BlackKeyHeight - WhiteKeyEndRadius);
  int h3 = CalcScaled(WhiteKeyBackMaskHeight);
  
  int x1 = CalcCoordX(key->xpos + WhiteKeyEndRadius);
  int x2 = key->xpos;
  int x3 = CalcCoordX(key->xpos + WhiteKeyWidth - WhiteKeyEndDiameter);
  
  int y1 = CalcCoordY(BlackKeyHeight);
  int y2 = CalcCoordY(WhiteKeyHeight - WhiteKeyEndDiameter);
  int y3 = CalcCoordY(WhiteKeyHeight - WhiteKeyEndRadius);
  int y4 = CalcCoordY(WhiteKeyBackMaskYpos);
  
  
  //If state is down draw a small rectangle at the end of the key with the set background color
  //This is because the key is shortened when down
  
   //Filling the arcs from the center point
  XSetArcMode(xc->display, xc->gc, ArcPieSlice);
  
  //Check if key is down
  if(state == True)
  {
    //Perform the fill with the given background color
    XSetForeground(xc->display, xc->gc, keyboard->backgroundcolor);
    XFillRectangle(xc->display, xc->win, xc->gc, x, y4, w, h3);
    
    //Shorten the key
    h1 -= CalcScaled(4);

    y1 += CalcScaled(15);
    y2 -= CalcScaled(4);
    y3 -= CalcScaled(4);
  }
 
  //For the body of the key different drawings are needed. 4 Different types exist
  switch(key->type)
  {
    case PianoKeyTypeWhiteFull:
      w1 = w;
      break;
    
    case PianoKeyTypeWhiteC:
      w1 = CalcScaled(5);
      
    case PianoKeyTypeWhiteF:
      w1 += CalcScaled(48);
      break;

    case PianoKeyTypeWhiteA:
      x2 = 5;
      
    case PianoKeyTypeWhiteD:
    case PianoKeyTypeWhiteG:
      break;
      
    //The E and B key have 4 rectangles and 3 arcs
    case PianoKeyTypeWhiteE:
    case PianoKeyTypeWhiteB:
      break;
  }
  
  //The two arcs at the bottom of the key are the same for all the keys
  arcs[0].x      = x3;
  arcs[0].y      = y2;
  arcs[0].width  = cd;
  arcs[0].height = cd;
  arcs[0].angle1 = Angle270;
  arcs[0].angle2 = Angle90;

  arcs[1].x      = x;
  arcs[1].y      = y2;
  arcs[1].width  = cd;
  arcs[1].height = cd;
  arcs[1].angle1 = Angle180;
  arcs[1].angle2 = Angle90;

  //The rectangle between the bottom arcs are the same for all the keys
  rects[0].x      = x1;
  rects[0].y      = y3;
  rects[0].width  = w2;
  rects[0].height = r;

  rects[1].x      = x;
  rects[1].y      = y1;
  rects[1].width  = w;
  rects[1].height = h2;
  
  rects[2].x      = x2;
  rects[2].y      = y;
  rects[2].width  = w1;
  rects[2].height = h1;
  
  //Perform the fills with the body color
  XSetForeground(xc->display, xc->gc, WhiteKeyBodyColor);
  XFillArcs(xc->display, xc->win, xc->gc, arcs, 2);
  XFillRectangles(xc->display, xc->win, xc->gc, rects, 3);
  
  //Dedicated functions are needed to draw the different parts of the keys since xlib does not have a path feature.
  
  //The fill with the body color is different since it needs to be done with the fill functions
  //There are three rects involved 
  //The top section which has different widths and starting positions but all have the same length for both up and down
  //The bottom section always has the same width and starting position but the length varies for up and down
  //The rounded of part always has same dimensions for both arcs and rects but starts on a different y position for up and down
  
  
  
  
  //The up state of a key has only a couple of shade lines.
  
  //The down state has more to envision the shades from the other keys
  
}

void PianoKeyboardDrawBlackKey(tagPianoKeyboard *keyboard, tagPianoKey *key, Bool state)
{
  tagXlibContext *xc = keyboard->xc;
  XArc       arcs[2];
  XRectangle rects[2];
  XSegment   lines[8];
  
  
  //CalcCoordX
  
  //Setup coordinates for drawing the different parts
  int r = CalcScaled(BlackKeyEndRadius);
  int w = CalcScaled(BlackKeyWidth);
  int h = CalcScaled(BlackKeyHeight);
  int n = CalcScaled(BlackKeyNarrowOffset);
  int cd = r * 2;
  int x = key->xpos;
  int y = 0;
  int x1 = x + r;
  int x2 = x + w;
  int x3 = x2 - r;
  int x4 = x2 - cd;
  int x5 = x + n;
  int x6 = x2 - n;
  int y1 = y + CalcScaled(BlackKeyUpHeight);
  int y2 = y + h;
  int y3 = y2 - r;
  int y4 = y2 - cd;
  int w1 = w - cd;
  int h1 = h - r;
  
  //Filling the arcs from the center point
  XSetArcMode(xc->display, xc->gc, ArcPieSlice);
  
  //Check if key is down
  if(state == True)
  {
    //If so a full lighter background is drawn and the key length is shortened afterwards
    //The two filled arcs at the bottom of the key
    arcs[0].x      = x4;
    arcs[0].y      = y4;
    arcs[0].width  = cd;
    arcs[0].height = cd;
    arcs[0].angle1 = Angle270;
    arcs[0].angle2 = Angle90;

    arcs[1].x      = x;
    arcs[1].y      = y4;
    arcs[1].width  = cd;
    arcs[1].height = cd;
    arcs[1].angle1 = Angle180;
    arcs[1].angle2 = Angle90;

    //Setup for filling the two rects (top and between the arcs)
    rects[0].x      = x;
    rects[0].y      = y;
    rects[0].width  = w;
    rects[0].height = h1;
    
    rects[1].x      = x1;
    rects[1].y      = y3;
    rects[1].width  = w1;
    rects[1].height = r;
    
    //Perform the fills with the background color
    XSetForeground(xc->display, xc->gc, BlackKeyBackGroundColor);
    XFillArcs(xc->display, xc->win, xc->gc, arcs, 2);
    XFillRectangles(xc->display, xc->win, xc->gc, rects, 2);
    
    //Shorten the key
    h1 -= CalcScaled(4);

    y1 += CalcScaled(15);
    y2 -= CalcScaled(4);
    y3 -= CalcScaled(4);
    y4 -= CalcScaled(4);
  }
  
  //Do the black body of the key
  //The two filled arcs at the bottom of the key
  arcs[0].x      = x4;
  arcs[0].y      = y4;
  arcs[0].width  = cd;
  arcs[0].height = cd;
  arcs[0].angle1 = Angle270;
  arcs[0].angle2 = Angle90;

  arcs[1].x      = x;
  arcs[1].y      = y4;
  arcs[1].width  = cd;
  arcs[1].height = cd;
  arcs[1].angle1 = Angle180;
  arcs[1].angle2 = Angle90;

  //Setup for filling the two rects (top and between the arcs)
  rects[0].x      = x;
  rects[0].y      = y;
  rects[0].width  = w;
  rects[0].height = h1;

  rects[1].x      = x1;
  rects[1].y      = y3;
  rects[1].width  = w1;
  rects[1].height = r;

  //Perform the fills first with the fill color
  XSetForeground(xc->display, xc->gc, BlackKeyBodyColor);
  XFillArcs(xc->display, xc->win, xc->gc, arcs, 2);
  XFillRectangles(xc->display, xc->win, xc->gc, rects, 2);
  
  //Setup the line based on given line width
  XSetLineAttributes(xc->display, xc->gc, CalcScaled(2), LineSolid, CapButt, JoinMiter);
  
  //The lines are shifted a small bit
  x  += 1;
  x2 -= 1;
  
  //So the arcs need to shift also
  arcs[0].x -= 1;
  arcs[1].x += 1;
  
  //Setup for drawing the eight lines
  lines[0].x1 = x;    //Left side of the key down towards the arc
  lines[0].x2 = x;
  lines[0].y1 = y;
  lines[0].y2 = y3;
  
  lines[1].x1 = x1;   //Bottom line between arcs
  lines[1].x2 = x3;
  lines[1].y1 = y2;
  lines[1].y2 = y2;
  
  lines[2].x1 = x2;   //Right side of the key down towards the arc
  lines[2].x2 = x2;
  lines[2].y1 = y;
  lines[2].y2 = y2;

  lines[3].x1 = x;    //Left side of the key to the top of the narrow
  lines[3].x2 = x5;   
  lines[3].y1 = y;
  lines[3].y2 = y1;

  lines[4].x1 = x2;   //Right side of the key to the top of the narrow
  lines[4].x2 = x6;   
  lines[4].y1 = y;
  lines[4].y2 = y1;
  
  lines[5].x1 = x5;   //Top of the narrow
  lines[5].x2 = x6;
  lines[5].y1 = y1;
  lines[5].y2 = y1;

  lines[6].x1 = x5;   //Left side of narrow to the end of the key
  lines[6].x2 = x;
  lines[6].y1 = y1;
  lines[6].y2 = y2;

  lines[7].x1 = x6;   //Right side of narrow to the end of the key
  lines[7].x2 = x2;
  lines[7].y1 = y1;
  lines[7].y2 = y2;

  //Draw the lines on top of the fills and use the line color
  XSetForeground(xc->display, xc->gc, BlackKeyLineColor);
  XDrawArcs(xc->display, xc->win, xc->gc, arcs, 2);
  XDrawSegments(xc->display, xc->win, xc->gc, lines, 8);
}

void PianoKeyboardDown(MouseEvent *event)
{
  
}

void PianoKeyboardUp(MouseEvent *event)
{
  
}

void PianoKeyboardMove(MouseEvent *event)
{
  
}
