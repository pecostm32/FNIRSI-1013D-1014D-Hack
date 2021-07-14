#ifndef MOUSEHANDLING_H
#define MOUSEHANDLING_H

#include <X11/Xlib.h>


typedef struct tagMouseEvent  MouseEvent;
typedef struct tagMouseRange  MouseRange;

//Function pointer to handle the events
typedef void (*HANDLEEVENT)(MouseEvent *event);

struct tagMouseRange
{
  MouseRange  *previous;         //Pointer to previous mouse range
  int          left;             //Left side of the bounding box the object is in
  int          right;            //Right side of the bounding box the object is in
  int          top;              //Top side of the bounding box the object is in
  int          bottom;           //Bottom side of the bounding box the object is in
  void        *data;             //Pointer to client data
  HANDLEEVENT  move;             //Function pointers for client handlers
  HANDLEEVENT  down;
  HANDLEEVENT  up;
  HANDLEEVENT  out;
};

struct tagMouseEvent
{
  XEvent *event;
  void   *data;
};


void MouseDown(XEvent *event);
void MouseUp(MouseRange *range, XEvent *event);
void MouseMove(MouseRange *range, XEvent *event);

MouseRange *MouseScan(MouseRange *range, int x, int y);


#endif /* MOUSEHANDLING_H */

