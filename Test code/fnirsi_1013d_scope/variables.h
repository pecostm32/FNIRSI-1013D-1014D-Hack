//----------------------------------------------------------------------------------------------------------------------------------

#ifndef VARIABLES_H
#define VARIABLES_H

//----------------------------------------------------------------------------------------------------------------------------------

#include <string.h>

#include "types.h"
#include "font_structs.h"
#include "fnirsi_1013d_scope.h"
#include "ff.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Defines
//----------------------------------------------------------------------------------------------------------------------------------

#define VIEW_ITEM_XSTART                  2
#define VIEW_ITEM_YSTART                  0
#define VIEW_ITEM_WIDTH                 182
#define VIEW_ITEM_HEIGHT                120

#define VIEW_ITEM_XNEXT                 182
#define VIEW_ITEM_YNEXT                 120

#define VIEW_ITEM_XLAST                 720

#define VIEW_THUMBNAIL_DATA_SIZE     400000
#define VIEW_FILE_NUMBER_DATA_SIZE     2000
#define VIEW_SETUP_DATA_SIZE           1000

#define VIEW_MAX_ITEMS                 1000

#define VIEW_ITEMS_PER_PAGE              16

#define VIEW_TYPE_MASK                    1

#define VIEW_TYPE_PICTURE                 0
#define VIEW_TYPE_WAVEFORM                1

#define VIEW_ITEM_SELECTED_XSTART        77
#define VIEW_ITEM_SELECTED_YSTART        45

//States for displaying the selected signs
#define VIEW_ITEM_NOT_SELECTED            0
#define VIEW_ITEM_SELECTED_NOT_DISPLAYED  1
#define VIEW_ITEM_SELECTED_DISPLAYED      2
#define VIEW_ITEM_NOT_SELECTED_DISPLAYED  3

//States for select mode
#define VIEW_SELECT_NONE                  0
#define VIEW_SELECT_ALL                   1
#define VIEW_SELECT_INDIVIDUAL            2

//States for bottom file menu displaying
#define VIEW_BOTTON_MENU_INIT             3     //This is a combination of init and show, so show needs to be 1
#define VIEW_BOTTON_MENU_SHOW             1     //Needs to be 1 / 0 for the show and hide since an exor is used to toggle the modes
#define VIEW_BOTTON_MENU_HIDE             0

#define VIEW_TRACE_LOAD_OK                0
#define VIEW_TRACE_LOAD_ERROR             1

#define VIEW_CONFIRM_DELETE_NO            1
#define VIEW_CONFIRM_DELETE_YES           2

#define PICTURE_DATA_SIZE                 (800 * 480 * 2)                              //trace data
#define PICTURE_PIXEL_OFFSET              (70 + 15000)                                 //Bitmap header + trace data
#define PICTURE_FILE_SIZE                 (PICTURE_PIXEL_OFFSET + PICTURE_DATA_SIZE)  //Bitmap header + trace data + pixel data

#define MESSAGE_SAVE_SUCCESSFUL           0
#define MESSAGE_FILE_CREATE_FAILED        1
#define MESSAGE_FILE_OPEN_FAILED          2
#define MESSAGE_FILE_WRITE_FAILED         3
#define MESSAGE_FILE_READ_FAILED          4
#define MESSAGE_FILE_SEEK_FAILED          5

//----------------------------------------------------------------------------------------------------------------------------------
//Typedefs
//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagThumbnailData         THUMBNAILDATA,        *PTHUMBNAILDATA;

//----------------------------------------------------------------------------------------------------------------------------------
//Structs
//----------------------------------------------------------------------------------------------------------------------------------

struct tagThumbnailData
{
  uint8 filenumbermsb;
  uint8 filenumberlsb;
  uint8 channel1traceoffset;
  uint8 channel2traceoffset;
  uint8 triggerlevelscreenoffset;
  uint8 triggerpositiononscreen;
  uint8 channel1enable;
  uint8 channel2enable;
  uint8 traceposition;
  uint8 tracesamples;
  uint8 xydisplaymode;
  uint8 reserved[9];
  uint8 channel1data[180];
  uint8 channel2data[200];
};

//----------------------------------------------------------------------------------------------------------------------------------
//Linker variables
//----------------------------------------------------------------------------------------------------------------------------------

extern uint8 BSS_START;
extern uint8 BSS_END;

//----------------------------------------------------------------------------------------------------------------------------------
//Touch data
//----------------------------------------------------------------------------------------------------------------------------------

extern uint8  havetouch;
extern uint16 xtouch;
extern uint16 ytouch;

//----------------------------------------------------------------------------------------------------------------------------------
//State machine data
//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 previousxtouch;
extern uint16 previousytouch;

extern uint16 xtouchdisplacement;
extern uint16 ytouchdisplacement;

extern uint16 maxdisplacement;

extern uint8 touchstate;

extern uint32 previoustimerticks;

extern uint8 systemsettingsmenuopen;
extern uint8 screenbrightnessopen;
extern uint8 gridbrightnessopen;
extern uint8 calibrationopen;

//----------------------------------------------------------------------------------------------------------------------------------
//Scope data
//----------------------------------------------------------------------------------------------------------------------------------

extern FATFS fs;

extern SCOPESETTINGS scopesettings;

extern SCOPESETTINGS savedscopesettings1;
extern SCOPESETTINGS savedscopesettings2;

extern MEASUREMENTS channel1measurements;
extern MEASUREMENTS channel2measurements;

extern uint16 channel1tracebuffer1[];
extern uint16 channel1tracebuffer2[];
extern uint16 channel1tracebuffer3[];
extern uint32 channel1tracebuffer4[];

extern uint16 channel2tracebuffer1[];
extern uint16 channel2tracebuffer2[];
extern uint16 channel2tracebuffer3[];
extern uint32 channel2tracebuffer4[];

extern uint16 temptracebuffer1[];
extern uint16 temptracebuffer2[];

extern uint32 channel1ypoints[];
extern uint32 channel2ypoints[];

extern uint16 disp_xpos;

extern uint16 disp_ch1_y;
extern uint16 disp_ch2_y;

extern uint16 disp_ch1_prev_y;
extern uint16 disp_ch2_prev_y;

extern uint8 zoom_select;

extern uint16 disp_x_start;
extern uint16 disp_sample_count;

extern uint8 channel_1_process_anyway;

//----------------------------------------------------------------------------------------------------------------------------------
//Distances of touch point to traces and cursors
//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 distance_channel_1;
extern uint16 distance_channel_2;

extern uint16 distance_trigger_level;

extern uint16 distance_time_cursor_left;
extern uint16 distance_time_cursor_right;

extern uint16 distance_volt_cursor_top;
extern uint16 distance_volt_cursor_bottom;

//----------------------------------------------------------------------------------------------------------------------------------
//Previous trace and cursor settings
//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 previous_channel_1_offset;
extern uint16 previous_channel_2_offset;

extern uint16 previous_trigger_level_offset;

extern uint16 previous_trigger_point_position;

extern uint16 previous_left_time_cursor_position;
extern uint16 previous_right_time_cursor_position;

extern uint16 previous_top_volt_cursor_position;
extern uint16 previous_bottom_volt_cursor_position;

//----------------------------------------------------------------------------------------------------------------------------------
//Predefined data
//----------------------------------------------------------------------------------------------------------------------------------

extern const uint16 signal_adjusters[];

extern const uint16 timebase_adjusters[];

extern const uint8 zoom_select_settings[3][7];

extern const uint8 bmpheader[70];

//----------------------------------------------------------------------------------------------------------------------------------
//For touch filtering on slider movement
//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 prevxtouch;

//----------------------------------------------------------------------------------------------------------------------------------
//Data for picture and waveform view mode
//----------------------------------------------------------------------------------------------------------------------------------

extern FIL viewfp;

extern char viewfilename[];

extern uint8 viewtype;

extern uint8 viewselectmode;
extern uint8 viewpage;
extern uint8 viewpages;
extern uint8 viewitemsonpage;

extern uint8 viewbottommenustate;

extern uint16 viewcurrentindex;

extern uint16 viewavailableitems;

extern uint8 viewitemselected[VIEW_ITEMS_PER_PAGE];

extern uint32 viewthumbnaildata[VIEW_THUMBNAIL_DATA_SIZE / 4];

extern uint32 viewfilenumberdata[VIEW_FILE_NUMBER_DATA_SIZE / 4];

extern uint32 viewfilesetupdata[VIEW_SETUP_DATA_SIZE / 4];

//----------------------------------------------------------------------------------------------------------------------------------
//Display data
//----------------------------------------------------------------------------------------------------------------------------------

//This first buffer is defined as 32 bits to be able to write it to file
extern uint32 maindisplaybuffer[SCREEN_SIZE / 2];

extern uint16 displaybuffer1[SCREEN_SIZE];
extern uint16 displaybuffer2[SCREEN_SIZE];

//----------------------------------------------------------------------------------------------------------------------------------
//Fonts
//----------------------------------------------------------------------------------------------------------------------------------

extern FONTDATA font_0;
extern FONTDATA font_2;
extern FONTDATA font_3;
extern FONTDATA font_4;
extern FONTDATA font_5;

//----------------------------------------------------------------------------------------------------------------------------------
//Icons
//----------------------------------------------------------------------------------------------------------------------------------

extern const uint8 system_settings_icon[];
extern const uint8 picture_view_icon[];
extern const uint8 waveform_view_icon[];
extern const uint8 usb_icon[];
extern const uint8 screen_brightness_icon[];
extern const uint8 grid_brightness_icon[];
extern const uint8 trigger_50_percent_icon[];
extern const uint8 baseline_calibration_icon[];
extern const uint8 x_y_mode_display_icon[];
extern const uint8 confirmation_icon[];
extern const uint8 return_arrow_icon[];
extern const uint8 left_pointer_icon[];
extern const uint8 right_pointer_icon[];
extern const uint8 top_pointer_icon[];
extern const uint8 select_sign_icon[];
extern const uint8 waste_bin_icon[];
extern const uint8 previous_picture_icon[];
extern const uint8 next_picture_icon[];

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* VARIABLES_H */

