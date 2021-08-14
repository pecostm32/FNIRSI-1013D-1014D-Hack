//----------------------------------------------------------------------------------------------------------------------------------

#ifndef VARIABLES_H
#define VARIABLES_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "font_structs.h"
#include "fnirsi_1013d_scope.h"

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

extern SCOPESETTINGS scopesettings;

extern uint16 channel1tracebuffer1[];
extern uint16 channel1tracebuffer2[];
extern uint16 channel1tracebuffer3[];
extern uint16 channel1tracebuffer4[];

extern uint16 channel2tracebuffer1[];
extern uint16 channel2tracebuffer2[];
extern uint16 channel2tracebuffer3[];
extern uint16 channel2tracebuffer4[];

extern uint16 temptracebuffer1[];
extern uint16 temptracebuffer2[];

extern uint16 channel1ypoints[];
extern uint16 channel2ypoints[];

extern uint16 disp_xpos;

extern uint16 disp_ch1_y;
extern uint16 disp_ch2_y;

extern uint16 disp_ch1_prev_y;
extern uint16 disp_ch2_prev_y;

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

//----------------------------------------------------------------------------------------------------------------------------------
//For touch filtering on slider movement
//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 prevxtouch;

//----------------------------------------------------------------------------------------------------------------------------------
//Display data
//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 maindisplaybuffer[];
extern uint16 displaybuffer1[];
extern uint16 displaybuffer2[];

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
extern const uint8 return_arrow_icon[];

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* VARIABLES_H */

