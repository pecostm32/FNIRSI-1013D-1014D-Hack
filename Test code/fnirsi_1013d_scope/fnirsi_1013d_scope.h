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
  uint8 enable;
  uint8 coupling;
  uint8 magnification;
  uint8 voltperdiv;
  uint8 fftenable;
};

struct tagScopeSettings
{
  CHANNELSETTINGS channel1;
  CHANNELSETTINGS channel2;
  
  uint8 timeperdiv;
  uint8 triggermode;
  uint8 triggeredge;
  uint8 triggerchannel;
  
  uint8 movespeed;
  
  uint8 rightmenustate;
  uint8 waveviewmode;
  
  uint8 batterychargelevel;
  uint8 batterycharging;
  uint8 runstate;
  
  uint8 screenbrightness;
  uint8 gridbrightness;
  uint8 alwaystrigger50;
  uint8 xymodedisplay;
  
  uint8 measuresstate[2][12];
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* FNIRSI_1013D_SCOPE_H */

