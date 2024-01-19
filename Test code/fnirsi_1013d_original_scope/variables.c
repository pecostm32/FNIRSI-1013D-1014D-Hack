//----------------------------------------------------------------------------------------------------------------------------------

#include "variables.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Timer data
//----------------------------------------------------------------------------------------------------------------------------------

volatile uint32 timer0ticks;

//----------------------------------------------------------------------------------------------------------------------------------
//Touch data
//----------------------------------------------------------------------------------------------------------------------------------

#ifndef USE_TP_CONFIG
uint8  tp_config_data[186];

uint32 xscaler;
uint32 yscaler;
#endif

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

//This first buffer is defined as 32 bits to be able to write it to file
uint32 maindisplaybuffer[SCREEN_SIZE / 2];

uint16 displaybuffer1[SCREEN_SIZE];
uint16 displaybuffer2[SCREEN_SIZE];

uint16 gradientbuffer[SCREEN_HEIGHT];

//----------------------------------------------------------------------------------------------------------------------------------
//Scope data
//----------------------------------------------------------------------------------------------------------------------------------

FATFS fs;

SCOPESETTINGS scopesettings;

SCOPESETTINGS savedscopesettings1;
SCOPESETTINGS savedscopesettings2;

MEASUREMENTS channel1measurements;
MEASUREMENTS channel2measurements;

ADC2CALIBRATIONDATA channel1adc2calibration;
ADC2CALIBRATIONDATA channel2adc2calibration;

//Need to make sure some of these are 32 bit aligned to allow usage as source and target for file operations
uint16 channel1tracebuffer1[3000];    //In original code at 0x8019D5EA
uint16 channel1tracebuffer2[3000];    //In original code at 0x8019ED5A
uint16 channel1tracebuffer3[3000];    //Target buffer for processed trace data. In original code at 0x801A916A

//declared as uint32 for use with file functions, but used with shorts (3000)
uint32 channel1tracebuffer4[1500];    //In original code at 0x801AC04A

uint16 channel2tracebuffer1[3000];    //In original code at 0x801A04CA
uint16 channel2tracebuffer2[3000];    //In original code at 0x801A1C3A
uint16 channel2tracebuffer3[3000];    //In original code at 0x801AA8DA

//declared as uint32 for use with file functions, but used with shorts (3000)
uint32 channel2tracebuffer4[1500];    //In original code at 0x801AD7BA

uint16 temptracebuffer1[3000];         //In original code at 0x801AEF26  (0x801AEF2A)
uint16 temptracebuffer2[3000];         //In original code at 0x801B8B60  (0x801B8B6A)

//declared as uint32 for use with file functions, but used with shorts (1000)
uint32 channel1ypoints[500];          //At 0x801C374A in original code
uint32 channel2ypoints[500];          //At 0x801C374A + 2000 in original code = 0x801C3F1A

uint16 disp_xpos = 0;                  //In original code at 0x80192EAA

uint16 disp_ch1_y = 0;
uint16 disp_ch2_y = 0;

uint16 disp_ch1_prev_y = 0;
uint16 disp_ch2_prev_y = 0;

uint8 zoom_select = 0;

uint16 disp_x_start = 0;               //In original code at 0x8019D5BA
uint16 disp_sample_count = 0;          //In original code at 0x8019D5BC


uint8 channel_1_process_anyway = 0;    //In original code at 0x8019D5A9 (Basically a channel setting)


uint16 system_ok;                      //In original code at 0x8019D5E4

uint8 parameter_buffer[7];
uint8 parameter_crypt_byte;

uint16 settingsworkbuffer[250];        //In original code at 0x8035344E. Used for loading from and writing to flash

uint32 channel1_min;
uint32 channel1_max;
uint32 channel1_center;
uint32 channel1_vpp;

uint32 channel2_min;
uint32 channel2_max;
uint32 channel2_center;
uint32 channel2_vpp;


//----------------------------------------------------------------------------------------------------------------------------------
//Test data
//----------------------------------------------------------------------------------------------------------------------------------

uint32 saved_sample_buffers_count = 0;

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

uint8 viewactive;                   //Not in the original code. Used to avoid copying settings to the flash

uint8 viewtype = VIEW_TYPE_PICTURE; //At 0x80192EE2 in original code
uint8 viewselectmode;               //In original code this is at 0x8035A97E. Signals if either the select all or the select button is active
uint8 viewpage;                     //In original code this is at 0x8035A97F. Is the page number of the current items on the screen. 16 items per page
uint8 viewpages;                    //Not in original code, but when only calculated once code gets simpler
uint8 viewitemsonpage;              //The original code works differently in validating the number of items on a page

uint8 viewbottommenustate;          //At 0x80192EE4 in original code

uint16 viewcurrentindex;            //Used for selecting previous or next item when viewing an item

uint16 viewavailableitems;          //Also done differently in the original code

uint8 viewitemselected[VIEW_ITEMS_PER_PAGE];                 //In original code this is at 0x8035A98B. Flags to signal if an item is selected or not

uint32 viewthumbnaildata[VIEW_THUMBNAIL_DATA_SIZE / 4];      //In original code at 0x802F19CE. 400000 bytes, but to make sure it is dword aligned declared as uint32

uint32 viewfilenumberdata[VIEW_FILE_NUMBER_DATA_SIZE / 4];   //In original code at 0x8035A99C. 2000 bytes, but to make sure it is dword aligned declared as uint32

                                                             //The original code uses a large buffer to load all the data into and writes it in one go to a file. This requires a lot of extra memory
uint32 viewfilesetupdata[VIEW_SETUP_DATA_SIZE / 4];          //Not in original code. 1000 bytes for storing the system settings to save to file or to load from file

//----------------------------------------------------------------------------------------------------------------------------------
//Calibration data
//----------------------------------------------------------------------------------------------------------------------------------

uint16 channel1_calibration_factor = 0x00DC;
uint16 channel1_calibration_data[] = { 0x054D, 0x0545, 0x0554, 0x054D, 0x0553, 0x054C, 0x054C };

uint16 channel2_calibration_factor = 0x00D9;
uint16 channel2_calibration_data[] = { 0x055B, 0x0556, 0x0561, 0x055B, 0x0560, 0x055A, 0x055A };

//----------------------------------------------------------------------------------------------------------------------------------
//Predefined data
//----------------------------------------------------------------------------------------------------------------------------------

const int8 *volt_div_texts[3][7] =
{
  { "5V/div", "2.5V/div", "1V/div", "500mV/div", "200mV/div", "100mV/div", "50mV/div" },
  { "50V/div", "25V/div", "10V/div", "5V/div", "2V/div", "1V/div", "500mV/div" },
  { "500V/div", "250V/div", "100V/div", "50V/div", "20V/div", "10V/div", "5V/div" }
};

const uint16 signal_adjusters[7] = { 0xAD, 0xAF, 0xB4, 0xB4, 0xB8, 0xB8, 0xB8 };

const uint16 timebase_adjusters[5] = { 0x01A9, 0x00AA, 0x0055, 0x002F, 0x0014 };

const uint32 short_timebase_settings[] =
{
     800,   // 50mS/div
     800,   // 20mS/div
    1800,   // 10mS/div
    2500,   //  5mS/div
    2500,   //  2mS/div
    2500,   //  1mS/div
    2500,   //500uS/div
    2500,   //200uS/div
    3000,   //100uS/div
    5596,   // 50uS/div
    9692,   // 20uS/div
   21980,   // 10uS/div
   21980,   //  5uS/div
   83420,   //  2uS/div
  206300,   //  1uS/div
  411100,   //500nS/div
  411100,   //250nS/div
  411100,   //100nS/div
  411100,   // 50nS/div
  411100,   // 25nS/div
  411100,   // 10nS/div
};

const uint8 zoom_select_settings[3][7] =
{
  { 8, 10, 5, 0, 2, 3, 4 },
  { 8,  7, 6, 0, 1, 9, 4 },
  { 8,  7, 5, 0, 1, 3, 4 }
};

const TIMECALCDATA time_calc_data[21] =
{
  {    100, 3, 3 },         // 50mS/div
  {  40000, 2, 4 },         // 20mS/div
  {  20000, 2, 4 },         // 10mS/div
  {  10000, 2, 4 },         //  5mS/div
  {   4000, 2, 4 },         //  2mS/div
  {   2000, 2, 4 },         //  1mS/div
  {   1000, 2, 4 },         //500uS/div
  {    400, 2, 4 },         //200uS/div
  {    200, 2, 4 },         //100uS/div
  {    100, 2, 4 },         // 50uS/div
  {  40000, 1, 5 },         // 20uS/div
  {  20000, 1, 5 },         // 10uS/div
  {  10000, 1, 5 },         //  5uS/div
  {   4000, 1, 5 },         //  2uS/div
  {   2000, 1, 5 },         //  1uS/div
  {   1000, 1, 5 },         //500nS/div
  {    500, 1, 5 },         //250nS/div
  {    200, 1, 5 },         //100nS/div
  {    100, 1, 5 },         // 50nS/div
  {  50000, 0, 6 },         // 25nS/div
  {  20000, 0, 6 }          // 10nS/div
};

const VOLTCALCDATA volt_calc_data[3][7] = 
{
  { {  10000, 3 },  {  5000, 3 }, {  2000, 3 }, {  1000, 3 }, {  400, 3 }, {  200, 3 }, {  100, 3 } },
  { { 100000, 3 },  { 50000, 3 }, { 20000, 3 }, { 10000, 3 }, { 4000, 3 }, { 2000, 3 }, { 1000, 3 } },
  { {   1000, 4 },  {   500, 4 }, {   200, 4 }, {   100, 4 }, {   40, 4 }, {   20, 4 }, {   10, 4 } }
};

const char *magnitude_scaler[8] = { "p", "n", "u", "m", "", "K", "M", "G"};

//Setup the bitmap header
//Consist of basic bitmap header followed by a DIB header (BITMAPINFOHEADER + BITMAPV3INFOHEADER)
//Could probably do with BITMAPV2INFOHEADER but the original uses V3
//The bitmap height is using a negative value for reversing the top to bottom lines. This allows just writing the frame buffer to the file
const uint8 bmpheader[70] = 
{
  //Header identifier
  'B', 'M',
  
  //Size of the file in bytes
   PICTURE_FILE_SIZE        & 0xFF,
  (PICTURE_FILE_SIZE >>  8) & 0xFF,
  (PICTURE_FILE_SIZE >> 16) & 0xFF,
  (PICTURE_FILE_SIZE >> 24) & 0xFF,

  //Reserved
  0, 0, 0, 0, 
  
  //Offset to the pixel array
   PICTURE_PIXEL_OFFSET        & 0xFF,
  (PICTURE_PIXEL_OFFSET >>  8) & 0xFF,
  (PICTURE_PIXEL_OFFSET >> 16) & 0xFF,
  (PICTURE_PIXEL_OFFSET >> 24) & 0xFF,
  
  //Size of DIB header
  56, 0, 0, 0,
  
  //Bitmap width in pixels
   800        & 0xFF,
  (800 >>  8) & 0xFF,
  (800 >> 16) & 0xFF,
  (800 >> 24) & 0xFF,

  //Bitmap height in pixels
   -480        & 0xFF,
  (-480 >>  8) & 0xFF,
  (-480 >> 16) & 0xFF,
  (-480 >> 24) & 0xFF,
  
  //Number of color planes
  1, 0,
  
  //Number of bits per pixel
  16, 0,
  
  //Compression method (BI_BITFIELDS)
  3, 0, 0, 0,

  //Pixel array size
   PICTURE_DATA_SIZE        & 0xFF,
  (PICTURE_DATA_SIZE >>  8) & 0xFF,
  (PICTURE_DATA_SIZE >> 16) & 0xFF,
  (PICTURE_DATA_SIZE >> 24) & 0xFF,

  //Horizontal resolution
  0, 0, 0, 0,

  //Vertical resolution
  0, 0, 0, 0,

  //Number of colors in the pallete
  0, 0, 0, 0,

  //Number of colors important
  0, 0, 0, 0,
  
  //Mask fields for BI_BITFIELDS compression
  //Red mask 0x0000F800
  0, 0xF8, 0, 0,
  
  //Green mask 0x000007E0
  0xE0, 7, 0, 0,

  //Blue mask 0x0000001F
  0x1F, 0, 0, 0,

  //Alpha mask 0x00000000
  0, 0, 0, 0,
};


    
    
    
    

//----------------------------------------------------------------------------------------------------------------------------------
