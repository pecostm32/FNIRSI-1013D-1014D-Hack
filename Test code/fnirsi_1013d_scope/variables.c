//----------------------------------------------------------------------------------------------------------------------------------

#include "variables.h"

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

SCOPESETTINGS savedscopesettings1;
SCOPESETTINGS savedscopesettings2;

MEASUREMENTS channel1measurements;
MEASUREMENTS channel2measurements;

//Need to make sure some of these are 32 bit aligned to allow usage as source and target for file operations
uint16 channel1tracebuffer1[3000];    //In original code at 0x8019D5EA
uint16 channel1tracebuffer2[3000];    //Not used in original code???
uint16 channel1tracebuffer3[3000];    //Target buffer for processed trace data. In original code at 0x801A916A

//declared as uint32 for use with file functions, but used with shorts (3000)
uint32 channel1tracebuffer4[1500];    //In original code at 0x801AC04A

uint16 channel2tracebuffer1[3000];    //In original code at 0x801A04CA
uint16 channel2tracebuffer2[3000];    //In original code at 0x801A1C3A
uint16 channel2tracebuffer3[3000];    //In original code at 0x801AA8DA

//declared as uint32 for use with file functions, but used with shorts (3000)
uint32 channel2tracebuffer4[1500];    //In original code at 0x801AD7BA

uint16 temptracebuffer1[6000];         //In original code at 0x801AEF26
uint16 temptracebuffer2[6000];         //In original code at 0x801B8B60

//declared as uint32 for use with file functions, but used with shorts (1000)
uint32 channel1ypoints[500];          //At 0x801C374A in original code
uint32 channel2ypoints[500];          //At 0x801C374A + 2000 in original code   = 0x801C3F1A

uint16 disp_xpos = 0;                  //In original code at 0x80192EAA

uint16 disp_ch1_y = 0;
uint16 disp_ch2_y = 0;

uint16 disp_ch1_prev_y = 0;
uint16 disp_ch2_prev_y = 0;

uint8 zoom_select = 0;

uint16 disp_x_start = 0;               //In original code at 0x8019D5BA
uint16 disp_sample_count = 0;          //In original code at 0x8019D5BC


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
//Data for picture and waveform view mode
//----------------------------------------------------------------------------------------------------------------------------------

FIL viewfp;                         //Since files are not opened concurrent using a global file pointer

char viewfilename[32];              //The original code uses a large buffer to create all the needed file names in. Here the file name is created when needed

uint8 viewtype = VIEW_TYPE_PICTURE; //At 0x80192EE2 in original code
uint8 viewselectmode;               //In original code this is at 0x8035A97E. Signals if either the select all or the select button is active
uint8 viewpage;                     //In original code this is at 0x8035A97F. Is the page number of the current items on the screen. 16 items per page
uint8 viewpages;                    //Not in original code, but when only calculated once code gets simpler
uint8 viewitemsonpage;              //The original code works differently in validating the number of items on a page

uint8 viewbottommenustate;          //At 0x80192EE4 in original code

uint16 viewcurrentindex;            //Used for selecting previous or next item when viewing an item

uint16 viewavailableitems;          //Also done differently in the original code

uint8 viewitemselected[16];         //In original code this is at 0x8035A98B. Flags to signal if an item is selected or not

uint32 viewthumbnaildata[VIEW_THUMBNAIL_DATA_SIZE / 4];      //In original code at 0x802F19CE. 400000 bytes, but to make sure it is dword aligned declared as uint32

uint32 viewfilenumberdata[VIEW_FILE_NUMBER_DATA_SIZE / 4];   //In original code at 0x8035A99C. 2000 bytes, but to make sure it is dword aligned declared as uint32

                                    //The original code uses a large buffer to load all the data into and writes it in one go to a file. This requires a lot of extra memory
uint32 viewfilesetupdata[250];      //Not in original code. 1000 bytes for storing the system settings to save to file or to load from file

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
