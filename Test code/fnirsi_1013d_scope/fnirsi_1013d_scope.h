//----------------------------------------------------------------------------------------------------------------------------------

#ifndef FNIRSI_1013D_SCOPE_H
#define FNIRSI_1013D_SCOPE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagTouchCoords         TOUCHCOORDS,        *PTOUCHCOORDS;
typedef struct tagScopeSettings       SCOPESETTINGS,      *PSCOPESETTINGS;
typedef struct tagChannelSettings     CHANNELSETTINGS,    *PCHANNELSETTINGS;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagTouchCoords
{
  uint16 x1;
  uint16 x2;
  uint16 y1;
  uint16 y2;
};

struct tagChannelSettings
{
  uint8  enable;
  uint8  coupling;
  uint8  magnification;
  uint8  voltperdiv;
  uint8  voltperdivbackup;
  uint8  fftenable;

  uint16 traceoffset;   //No idea if this is correct. Found at 0x8019d5a6 and 0x8019d5b2 in the original code
};

struct tagScopeSettings
{
  CHANNELSETTINGS channel1;
  CHANNELSETTINGS channel2;
  
  uint8 timeperdivbackup;
  
  uint8 timeperdiv;
  uint8 triggermode;
  uint8 triggeredge;
  uint8 triggerchannel;
  
  uint16 triggerposition;    //Position on screen of the trigger point in the signal displaying
  uint16 triggeroffset;      //Screen offset of the trigger level indicator
  uint16 triggerlevel;       //Actual trigger level set to the FPGA
  
  uint8 triggerflag1;        //0x8019D5B7 in original code
  uint8 triggerflag2;        //0x8019D5B8 in original code
  uint8 triggerflag3;        //0x8019D5D6 in original code
  uint8 triggerflag4;        //0x8019D5BE in original code
  
  
  uint8 movespeed;
  uint8 temp;                //??
  
  uint8 rightmenustate;
  uint8 waveviewmode;
  
  uint8 updatescreen;        //0x8019D5D7 in original code
  uint8 batterychargelevel;
  uint8 batterycharging;
  uint8 runstate;
  
  uint8 screenbrightness;
  uint8 gridbrightness;
  uint8 alwaystrigger50;
  uint8 xymodedisplay;
  
  uint8 timecursorsenable;
  uint8 voltcursorsenable;
  
  uint16 timecursor1position;
  uint16 timecursor2position;
  
  uint16 voltcursor1position;
  uint16 voltcursor2position;
  
  uint16 channel1pixelA;       //Long time base code writes these variables, where the first is the actual sample and the second is the possible limited one
  uint16 channel1pixelB;
  uint16 channel2pixelA;
  uint16 channel2pixelB;
  
  uint32 previoustimerticks;
  
  uint8 measuresstate[2][12];
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* FNIRSI_1013D_SCOPE_H */

