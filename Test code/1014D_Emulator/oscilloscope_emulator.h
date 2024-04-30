//----------------------------------------------------------------------------------------------------------------------------------

#ifndef SCOPEEMULATOR_H
#define SCOPEEMULATOR_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "xlibfunctions.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define BorderColor                   0xE7E7E7
#define PanelColor                    0xF9F9F9
#define PanelLineColor                0xE3D9CA


#define SectionColor                  0xF6FAF3   //Color of the panel surrounding the channel and trigger rotaries


//----------------------------------------------------------------------------------------------------------------------------------

//Function to call for sending the main window a message indicating the display needs to be updated
void updatedisplaymessage(void);


void DrawOscilloscopeFrontPanel(tagXlibContext *xc);


//----------------------------------------------------------------------------------------------------------------------------------

#endif /* SCOPEEMULATOR_H */

