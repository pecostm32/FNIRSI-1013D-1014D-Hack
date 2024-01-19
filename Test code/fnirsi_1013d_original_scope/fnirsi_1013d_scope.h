//----------------------------------------------------------------------------------------------------------------------------------

#ifndef FNIRSI_1013D_SCOPE_H
#define FNIRSI_1013D_SCOPE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagTouchCoords         TOUCHCOORDS,        *PTOUCHCOORDS;
typedef struct tagScopeSettings       SCOPESETTINGS,      *PSCOPESETTINGS;
typedef struct tagChannelSettings     CHANNELSETTINGS,    *PCHANNELSETTINGS;
typedef struct tagMeasurements        MEASUREMENTS,       *PMEASUREMENTS;

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

//Should these be 32 bit wide???
struct tagMeasurements
{
  int16 max;
  int16 min;
  int16 center;
  int16 peakpeak;
  int16 avg;
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
  uint8 runstate;            //0x8019D5DA in original code
  
  uint8 screenbrightness;
  uint8 gridbrightness;
  uint8 alwaystrigger50;
  uint8 xymodedisplay;
  uint8 confirmationmode;
  
  uint8 timecursorsenable;
  uint8 voltcursorsenable;
  
  uint16 timecursor1position;
  uint16 timecursor2position;
  
  uint16 voltcursor1position;
  uint16 voltcursor2position;
  
  uint32 previoustimerticks;
  
  uint8 measuresstate[2][12];
};

//----------------------------------------------------------------------------------------------------------------------------------

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

#define SCREEN_SIZE     (SCREEN_WIDTH * SCREEN_HEIGHT)

//----------------------------------------------------------------------------------------------------------------------------------

#define CHANNEL1_COLOR         0x00FFFF00
#define CHANNEL2_COLOR         0x0000FFFF
#define TRIGGER_COLOR          0x0000FF00

#define CHANNEL1_TRIG_COLOR    0x00CCCC00
#define CHANNEL2_TRIG_COLOR    0x0000CCCC

#define XYMODE_COLOR           0x00FF00FF

#define CURSORS_COLOR          0x0000AA11

#define ITEM_ACTIVE_COLOR      0x00EF9311

//----------------------------------------------------------------------------------------------------------------------------------

#define TOUCH_STATE_INACTIVE                 0x00
#define TOUCH_STATE_HAVE_DISPLACEMENT        0x01
#define TOUCH_STATE_X_Y_MODE                 0x02
#define TOUCH_STATE_MOVE_CHANNEL_1           0x03
#define TOUCH_STATE_MOVE_CHANNEL_2           0x04
#define TOUCH_STATE_MOVE_TRIGGER_LEVEL       0x05
#define TOUCH_STATE_MOVE_TIME_CURSOR_LEFT    0x06
#define TOUCH_STATE_MOVE_TIME_CURSOR_RIGHT   0x07
#define TOUCH_STATE_MOVE_VOLT_CURSOR_TOP     0x08
#define TOUCH_STATE_MOVE_VOLT_CURSOR_BOTTOM  0x09

#define TOUCH_STATE_MASK                     0x0F

#define TOUCH_STATE_MOVE_TRIGGER_POINT       0x80

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* FNIRSI_1013D_SCOPE_H */

