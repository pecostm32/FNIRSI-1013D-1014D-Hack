//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "fnirsi_1013d_scope.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Touch data
//----------------------------------------------------------------------------------------------------------------------------------

uint8  havetouch;
uint16 xtouch;
uint16 ytouch;

//----------------------------------------------------------------------------------------------------------------------------------
//State machine data
//----------------------------------------------------------------------------------------------------------------------------------

uint16 previousxtouch = 0;
uint16 previousytouch = 0;

uint16 xtouchdisplacement = 0;
uint16 ytouchdisplacement = 0;

uint16 maxdisplacement = 0;

uint8 touchstate = 0;

uint32 previoustimerticks = 0;

uint8 systemsettingsmenuopen = 0;
uint8 screenbrightnessopen = 0;
uint8 gridbrightnessopen = 0;
uint8 calibrationopen = 0;

//----------------------------------------------------------------------------------------------------------------------------------
//Display data
//----------------------------------------------------------------------------------------------------------------------------------

uint16 maindisplaybuffer[SCREEN_SIZE];
uint16 displaybuffer1[SCREEN_SIZE];
uint16 displaybuffer2[SCREEN_SIZE];

//----------------------------------------------------------------------------------------------------------------------------------
//Scope data
//----------------------------------------------------------------------------------------------------------------------------------

SCOPESETTINGS scopesettings;

MEASUREMENTS channel1measurements;
MEASUREMENTS channel2measurements;

uint16 channel1tracebuffer1[6000];    //In original code at 0x8019D5EA
uint16 channel1tracebuffer2[6000];    //Not used in original code
uint16 channel1tracebuffer3[3000];    //Target buffer for processed trace data. In original code at 0x801A916A
uint16 channel1tracebuffer4[3000];    //Not used in original code

uint16 channel2tracebuffer1[6000];    //In original code at 0x801A04CA
uint16 channel2tracebuffer2[6000];    //In original code at 0x801A1C3A
uint16 channel2tracebuffer3[3000];    //In original code at 0x801AA8DA
uint16 channel2tracebuffer4[3000];    //In original code at 0x801AA8DA

uint16 temptracebuffer1[6000];         //In original code at 0x801AEF26
uint16 temptracebuffer2[6000];         //In original code at 0x801B8B60


uint16 channel1ypoints[1000];          //At 0x801C374A in original code
uint16 channel2ypoints[1000];          //At 0x801C374A + 2000 in original code

uint16 disp_xpos = 0;                  //In original code at 0x80192EAA

uint16 disp_ch1_y = 0;
uint16 disp_ch2_y = 0;

uint16 disp_ch1_prev_y = 0;
uint16 disp_ch2_prev_y = 0;

uint8 zoom_select = 0;

uint16 sample_start_index = 0;
uint16 sample_end_index = 0;


uint8 channel_1_process_anyway = 0;    //In original code at 0x8019D5A9 (Basically a channel setting)

//----------------------------------------------------------------------------------------------------------------------------------
//Distances of touch point to traces and cursors
//----------------------------------------------------------------------------------------------------------------------------------

uint16 distance_channel_1;
uint16 distance_channel_2;

uint16 distance_trigger_level;

uint16 distance_time_cursor_left;
uint16 distance_time_cursor_right;

uint16 distance_volt_cursor_top;
uint16 distance_volt_cursor_bottom;

//----------------------------------------------------------------------------------------------------------------------------------
//Previous trace and cursor settings
//----------------------------------------------------------------------------------------------------------------------------------

uint16 previous_channel_1_offset;
uint16 previous_channel_2_offset;

uint16 previous_trigger_level_offset;

uint16 previous_trigger_point_position;

uint16 previous_left_time_cursor_position;
uint16 previous_right_time_cursor_position;

uint16 previous_top_volt_cursor_position;
uint16 previous_bottom_volt_cursor_position;

//----------------------------------------------------------------------------------------------------------------------------------
//For touch filtering on slider movement
//----------------------------------------------------------------------------------------------------------------------------------

uint16 prevxtouch = 0;

//----------------------------------------------------------------------------------------------------------------------------------
//Predefined data
//----------------------------------------------------------------------------------------------------------------------------------

const uint16 signal_adjusters[7] = { 0xAD, 0xAF, 0xB4, 0xB4, 0xB8, 0xB8, 0xB8 };

const uint16 timebase_adjusters[5] = { 0x01A9, 0x00AA, 0x0055, 0x002F, 0x0014 };

const uint8 zoom_select_settings[3][7] =
{
  { 8, 10, 5, 0, 2, 3, 4 },
  { 8,  7, 6, 0, 1, 9, 4 },
  { 8,  7, 5, 0, 1, 3, 4 }
};

//----------------------------------------------------------------------------------------------------------------------------------
