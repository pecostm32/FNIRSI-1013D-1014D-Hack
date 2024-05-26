//----------------------------------------------------------------------------------------------------------------------------------

#ifndef SCOPEEMULATOR_H
#define SCOPEEMULATOR_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "mousehandling.h"
#include "xlibfunctions.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define SimBorderColor                   0xE7E7E7
#define SimPanelColor                    0xF9F9F9
#define SimPanelLineColor                0xE3D9CA


#define SimSectionColor                  0xF6FAF3   //Color of the panel surrounding the channel and trigger rotaries

//----------------------------------------------------------------------------------------------------------------------------------

//Function to call for sending the main window a message indicating the display needs to be updated
void updatedisplaymessage(void);

void DrawOscilloscopeFrontPanel(tagXlibContext *xc);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* SCOPEEMULATOR_H */

