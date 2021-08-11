//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "font_structs.h"
#include "scope_functions.h"
#include "touchpanel.h"
#include "timer.h"
#include "fpga_control.h"
#include "display_lib.h"
#include "fnirsi_1013d_scope.h"

#include <string.h>

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

extern FONTDATA font_0;
extern FONTDATA font_2;
extern FONTDATA font_3;
extern FONTDATA font_4;
extern FONTDATA font_5;

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

extern uint8  havetouch;
extern uint16 xtouch;
extern uint16 ytouch;

extern uint8  touchstate;

//----------------------------------------------------------------------------------------------------------------------------------

SCOPESETTINGS scopesettings;

uint16 maindisplaybuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
uint16 displaybuffer1[SCREEN_WIDTH * SCREEN_HEIGHT];
uint16 displaybuffer2[SCREEN_WIDTH * SCREEN_HEIGHT];

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


uint16 disp_xpos;                      //In original code at 0x80192EAA


uint16 disp_ch1_y;
uint16 disp_ch2_y;

uint16 disp_ch1_prev_y;
uint16 disp_ch2_prev_y;

//----------------------------------------------------------------------------------------------------------------------------------
//For touch filtering on slider movement

uint16 prevxtouch = 0;

//----------------------------------------------------------------------------------------------------------------------------------

const uint16 signal_adjusters[7] = { 0xAD, 0xAF, 0xB4, 0xB4, 0xB8, 0xB8, 0xB8 };

const uint16 timebase_adjusters[5] = { 0x01A9, 0x00AA, 0x0055, 0x002F, 0x0014 };

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_display_lib(void)
{
  display_set_bg_color(0x00000000);
  
  display_set_screen_buffer(maindisplaybuffer);
  
  display_set_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);
  
  disp_xpos = 0;
  
  disp_ch1_y = 0;
  disp_ch2_y = 0;
  
  disp_ch1_prev_y = 0;
  disp_ch2_prev_y = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_main_screen(void)
{
  //Prepare the screen in a working buffer
//  display_set_screen_buffer(displaybuffer1);
  
  //Setup for clearing top and right menu bars
  display_set_fg_color(0x00000000);
  
  //Top bar for the main, channel and trigger menu and information
  display_fill_rect(0, 0, 730, 46);
  
  //Right bar for control buttons
  display_fill_rect(730, 0, 70, 480);
  
  //Setup the menu bar on the right side
  scope_setup_right_control_menu();
  
  //Check if normal or wave view mode
  if(scopesettings.waveviewmode == 0)
  {
    //Normal mode so show menu button
    scope_menu_button(0);
  }
  else
  {
    //Wave view mode so show return button
    scope_main_return_button(0);
  }
 
  //Show the user if the acquisition is running or stopped
  scope_run_stop_text();
  
  //Display the channel menu select buttons and their settings
  scope_channel1_settings(0);
  scope_channel2_settings(0);
  
  //Display the current time per div setting
  scope_time_div_setting();
  
  //Show the user selected move speed
  scope_move_speed(0);
  
  //Display the trigger menu select button and the settings
  scope_trigger_settings(0);
  
  //Show the battery charge level and charging indicator
  scope_battery_status();
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_right_control_menu(void)
{
  //Setup for clearing right menu bar
  display_set_fg_color(0x00000000);
  
  //Clear the right bar for the control buttons
  display_fill_rect(730, 0, 70, 480);
  
  //Display the control button
  scope_control_button(0);
  
  //Check in which state the right menu is in
  if(scopesettings.rightmenustate == 0)
  {
    //Main control state so draw the always used buttons
    scope_t_cursor_button(0);
    scope_v_cursor_button(0);
    scope_measures_button(0);
    scope_save_picture_button(0);
    
    //Check if in wave view mode
    if(scopesettings.waveviewmode == 0)
    {
      //Main control mode buttons
      scope_run_stop_button(0);
      scope_auto_set_button(0);
      scope_save_wave_button(0);
    }
    else
    {
      //Wave view mode buttons
      scope_page_up_button(0);
      scope_page_down_button(0);
      scope_delete_wave_button(0);
    }
  }
  else
  {
    //Channel sensitivity state
    scope_ch1_sensitivity_control(0,0);
    scope_ch2_sensitivity_control(0,0);
    
    //Check if in wave view mode
    if(scopesettings.waveviewmode == 0)
    {
      //Main control mode
      scope_50_percent_trigger_button(0);
    }
    else
    {
      //Wave view mode
      scope_show_grid_button(0);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
// Right side bar functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_control_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Grey color for inactive button
    display_set_fg_color(0x00333333);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 5, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00444444);
    
    //Draw the edge
    display_draw_rounded_rect(739, 5, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(748, 22, "CTRL");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_run_stop_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 65, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 65, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(746, 75, "RUN/");
  display_text(746, 90, "STOP");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_auto_set_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 125, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 125, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(746, 135, "AUTO");
  display_text(753, 150, "SET");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_page_up_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 65, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 65, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(749, 75, "page");
  display_text(757, 90, "up");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_page_down_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 125, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 125, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(749, 135, "page");
  display_text(748, 150, "down");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_t_cursor_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 185, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 185, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(746, 195, "T");
  display_text(765, 195, "CU");
  display_text(746, 210, "RSOR");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_v_cursor_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 245, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 245, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(746, 255, "V");
  display_text(765, 255, "CU");
  display_text(746, 270, "RSOR");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_measures_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 305, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 305, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(746, 315, "MEAS");
  display_text(746, 330, "URES");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_save_picture_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 365, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 365, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(746, 375, "SAVE");
  display_text(753, 390, "PIC");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_save_wave_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 425, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 425, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(746, 435, "SAVE");
  display_text(746, 450, "WAVE");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_delete_wave_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 425, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 425, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(745, 436, "delete");
  display_text(748, 449, "wave");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_50_percent_trigger_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 425, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 425, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(752, 436, "50%");
  display_text(749, 449, "TRIG");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_show_grid_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }

  //Draw the body of the button
  display_fill_rounded_rect(739, 425, 51, 50, 2);
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Edge color for the inactive button
    display_set_fg_color(0x00222222);
    
    //Draw the edge
    display_draw_rounded_rect(739, 425, 51, 50, 2);
  }
  
  //Check if inactive or active mode
  if(mode == 0)
  {
    //White text color for inactive button
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Black text color for activated button
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(748, 436, "show");
  display_text(752, 449, "grid");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_ch1_sensitivity_control(int type,int mode)
{
  //Check if V+ is active or inactive
  if((type == 0) && (mode != 0))
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }
  else
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  
  //Top button
  display_fill_rect(735, 78, 60, 60);

  //Check if V- is active or inactive
  if((type != 0) && (mode != 0))
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }
  else
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }

  //Bottom button
  display_fill_rect(735, 159, 60, 60);
  
  //Display V+ and V- the text in larger font and white color
  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_0);
  display_text(757, 99, "V+");
  display_text(757, 185, "V-");
  
  //Display the grey bar for the channel identifier text
  display_set_fg_color(0x00404040);
  display_fill_rect(735, 139, 60, 24);
  
  //Display the channel identifier in black
  display_set_fg_color(0x00000000);
  display_set_font(&font_2);
  display_text(756, 144, "CH1");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_ch2_sensitivity_control(int type,int mode)
{
  //Check if V+ is active or inactive
  if((type == 0) && (mode != 0))
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }
  else
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  
  //Top button
  display_fill_rect(735, 258, 60, 60);

  //Check if V- is active or inactive
  if((type != 0) && (mode != 0))
  {
    //Orange color for activated button
    display_set_fg_color(ITEM_ACTIVE_COLOR);
  }
  else
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }

  //Bottom button
  display_fill_rect(735, 339, 60, 60);
  
  //Display V+ and V- the text in larger font and white color
  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_0);
  display_text(757, 279, "V+");
  display_text(757, 365, "V-");
  
  //Display the grey bar for the channel identifier text
  display_set_fg_color(0x00404040);
  display_fill_rect(735, 319, 60, 24);
  
  //Display the channel identifier in black
  display_set_fg_color(0x00000000);
  display_set_font(&font_2);
  display_text(756, 324, "CH2");
}

//----------------------------------------------------------------------------------------------------------------------------------
// Top bar function
//----------------------------------------------------------------------------------------------------------------------------------

void scope_menu_button(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark blue background
    display_set_fg_color(0x00000078);
  }
  else
  {
    //Active so pale yellow background
    display_set_fg_color(0x00FFFF80);
  }
  
  //Draw the background
  display_fill_rect(0, 0, 80, 38);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Active so black foreground
    display_set_fg_color(0x00000000);
  }

  //Draw the menu symbol
  display_fill_rect(6,  11, 7, 7);
  display_fill_rect(15, 11, 7, 7);
  display_fill_rect(6,  20, 7, 7);
  display_fill_rect(15, 20, 7, 7);
  
  //Display the text
  display_set_font(&font_3);
  display_text(32, 11, "MENU");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_main_return_button(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so black background
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Active so white background
    display_set_fg_color(0x00FFFFFF);
  }
  
  //Draw the background
  display_fill_rect(0, 0, 80, 38);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00000000);
  }
  else
  {
    //Active so black foreground and white background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00FFFFFF);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(return_arrow_icon, 20, 6, 40, 25);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_run_stop_text(void)
{
  //Check if run or stop mode
  if(scopesettings.runstate == 0)
  {
    //Run mode. Black box
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Stop mode. Red box
    display_set_fg_color(0x00FF0000);
  }
  
  //Fill the box
  display_fill_rect(102, 12, 38, 18);

  //Select the font for the text
  display_set_font(&font_3);
  
  //Check if run or stop mode
  if(scopesettings.runstate == 0)
  {
    //Run mode. White text
    display_set_fg_color(0x00FFFFFF);
    display_text(106, 13, "RUN");
  }
  else
  {
    //Stop mode. Black text
    display_set_fg_color(0x00000000);
    display_text(103, 13, "STOP");
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

const int8 *volt_div_texts[3][7] =
{
  { "5V/div", "2.5V/div", "1V/div", "500mV/div", "200mV/div", "100mV/div", "50mV/div" },
  { "50V/div", "25V/div", "10V/div", "5V/div", "2V/div", "1V/div", "500mV/div" },
  { "500V/div", "250V/div", "100V/div", "50V/div", "20V/div", "10V/div", "5V/div" }
};

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel1_settings(int mode)
{
  int8 **vdtext;
  
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(161, 5, 99, 35);
  
  //Check if channel is enabled or disabled
  if(scopesettings.channel1.enable == 0)
  {
    //Disabled so off colors
    //Check if inactive or active
    if(mode == 0)
    {
      //Inactive, grey menu button
      display_set_fg_color(0x00444444);
    }
    else
    {
      //Active, light grey menu button
      display_set_fg_color(0x00BBBBBB);
    }
  }
  else
  {
    //Enabled so on colors
    //Check if inactive or active
    if(mode == 0)
    {
      //Inactive, channel 1 color menu button
      display_set_fg_color(CHANNEL1_COLOR);
    }
    else
    {
      //Active, blue menu button
      display_set_fg_color(0x000000FF);
    }
  }
  
  //Fill the button
  display_fill_rect(161, 5, 30, 35);

  //Select the font for the text
  display_set_font(&font_2);
  
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, black text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Active, white text
    display_set_fg_color(0x00FFFFFF);
    
    //Fill the settings background
    display_fill_rect(191, 5, 69, 35);
  }
  
  //Display the channel identifier text
  display_text(166, 16, "CH1");

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, white text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Active, black text
    display_set_fg_color(0x00000000);
  }
  
  //Check on which coupling is set
  if(scopesettings.channel1.coupling == 0)
  {
    //DC coupling
    display_text(199, 8, "DC");
  }
  else
  {
    //AC coupling
    display_text(199, 8, "AC");
  }
  
  //Print the probe magnification factor
  switch(scopesettings.channel1.magnification)
  {
    case 0:
      //Times 1 magnification
      display_text(224, 8, "1X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[0];
      break;
      
    case 1:
      //Times 10 magnification
      display_text(222, 8, "10X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[1];
      break;
      
    default:
      //Times 100 magnification
      display_text(220, 8, "100X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[2];
      break;
  }
  
  //Display the sensitivity when in range
  if(scopesettings.channel1.voltperdiv < 7)
  {
    display_text(199, 24, vdtext[scopesettings.channel1.voltperdiv]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel2_settings(int mode)
{
  int8 **vdtext;
  
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(288, 5, 99, 35);
  
  //Check if channel is enabled or disabled
  if(scopesettings.channel2.enable == 0)
  {
    //Disabled so on colors
    //Check if inactive or active
    if(mode == 0)
    {
      //Inactive, grey menu button
      display_set_fg_color(0x00444444);
    }
    else
    {
      //Active, light grey menu button
      display_set_fg_color(0x00BBBBBB);
    }
  }
  else
  {
    //Enabled so on colors
    //Check if inactive or active
    if(mode == 0)
    {
      //Inactive, cyan menu button
      display_set_fg_color(CHANNEL2_COLOR);
    }
    else
    {
      //Active, red menu button
      display_set_fg_color(0x00FF0000);
    }
  }
  
  //Fill the button
  display_fill_rect(288, 5, 30, 35);

  //Select the font for the text
  display_set_font(&font_2);
  
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, black text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Active, white text
    display_set_fg_color(0x00FFFFFF);
    
    //Fill the settings background
    display_fill_rect(318, 5, 69, 35);
  }
  
  //Display the channel identifier text
  display_text(293, 16, "CH2");

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, white text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Active, black text
    display_set_fg_color(0x00000000);
  }
  
  //Check on which coupling is set
  if(scopesettings.channel2.coupling == 0)
  {
    //DC coupling
    display_text(326, 8, "DC");
  }
  else
  {
    //AC coupling
    display_text(326, 8, "AC");
  }
  
  //Print the probe magnification factor
  switch(scopesettings.channel2.magnification)
  {
    case 0:
      //Times 1 magnification
      display_text(351, 8, "1X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[0];
      break;
      
    case 1:
      //Times 10 magnification
      display_text(349, 8, "10X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[1];
      break;
      
    default:
      //Times 10 magnification
      display_text(347, 8, "100X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[2];
      break;
  }
  
  //Display the sensitivity when in range
  if(scopesettings.channel2.voltperdiv < 7)
  {
    display_text(326, 24, vdtext[scopesettings.channel2.voltperdiv]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

const int8 *time_div_texts[30] =
{
    "50S/div",   "20S/div",   "10S/div",
     "5S/div",    "2S/div",    "1S/div",
  "500mS/div", "200mS/div", "100mS/div",
   "50mS/div",  "20mS/div",  "10mS/div",
    "5mS/div",   "2mS/div",   "1mS/div",
  "500uS/div", "200uS/div", "100uS/div",
   "50uS/div",  "20uS/div",  "10uS/div",
    "5uS/div",   "2uS/div",   "1uS/div",
  "500nS/div", "250nS/div", "100nS/div",
   "50nS/div",  "25nS/div",  "10nS/div",
};

//----------------------------------------------------------------------------------------------------------------------------------

void scope_time_div_setting(void)
{
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(395, 5, 93, 35);
  
  //Only display the text when in range
  if(scopesettings.timeperdiv < 30)
  {
    //White text
    display_set_fg_color(0x00FFFFFF);

    //Select the font for the text
    display_set_font(&font_0);

    //Display the text from the table
    display_text(402, 16, (int8 *)time_div_texts[scopesettings.timeperdiv]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_move_speed(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark blue background
    display_set_fg_color(0x00000078);
  }
  else
  {
    //Active so pale yellow background
    display_set_fg_color(0x00FFFF80);
  }
  
  //Draw the background
  display_fill_rect(493, 5, 40, 35);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Active so black text
    display_set_fg_color(0x00000000);
  }

  //Select the font for the text
  display_set_font(&font_3);
  
  //Display the common text
  display_text(496, 6, "move");
  
  //Check on which speed is set
  if(scopesettings.movespeed == 0)
  {
    display_text(501, 21, "fast");
  }
  else
  {
    display_text(499, 21, "slow");
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_trigger_settings(int mode)
{
  int8 *modetext = 0;
  
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(570, 5, 130, 35);
  
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, green menu button
    display_set_fg_color(TRIGGER_COLOR);
  }
  else
  {
    //Active, magenta menu button
    display_set_fg_color(0x00FF00FF);
  }
  
  //Fill the button
  display_fill_rect(570, 5, 31, 35);

  //Select the font for the text
  display_set_font(&font_4);
  
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, black text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Active, white text
    display_set_fg_color(0x00FFFFFF);
    
    //Fill the settings background
    display_fill_rect(601, 5, 88, 35);
  }
  
  //Display the channel identifier text
  display_text(582, 15, "T");

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, white text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Active, black text
    display_set_fg_color(0x00000000);
  }
  
  //Check on which trigger mode is set
  switch(scopesettings.triggermode)
  {
    case 0:
      modetext = "Auto";
      break;

    case 1:
      modetext = "Single";
      break;

    case 2:
      modetext = "Normal";
      break;
  }

  //Select the font for the texts
  display_set_font(&font_2);
  
  //Check if valid setting
  if(modetext)
  {
    //Display the selected text if so
    display_text(606, 7, modetext);
  }

  //Draw the trigger edge symbol
  display_draw_vert_line(642, 27, 38);
  
  //Draw the arrow based on the selected edge
  if(scopesettings.triggeredge == 0)
  {
    //rising edge
    display_draw_horz_line(27, 642, 645);
    display_draw_horz_line(38, 639, 642);
    display_draw_horz_line(32, 641, 643);
    display_draw_horz_line(33, 640, 644);
  }
  else
  {
    //falling edge
    display_draw_horz_line(27, 639, 642);
    display_draw_horz_line(38, 642, 645);
    display_draw_horz_line(32, 640, 644);
    display_draw_horz_line(33, 641, 643);
  }
  
  //Check on which channel is used for triggering
  switch(scopesettings.triggerchannel)
  {
    //Channel 1
    case 0:
      //Check if inactive or active
      if(mode == 0)
      {
        //Inactive, dark channel 1 trigger color box
        display_set_fg_color(CHANNEL1_TRIG_COLOR);
      }
      else
      {
        //Active, some blue box
        display_set_fg_color(0x003333FF);
      }
      
      //Fill the channel background
      display_fill_rect(605, 25, 28, 15);
      
      //Check if inactive or active
      if(mode == 0)
      {
        //Inactive, black text
        display_set_fg_color(0x00000000);
      }
      else
      {
        //Active, white text
        display_set_fg_color(0x00FFFFFF);
      }
      
      //Display the text
      display_text(608, 26, "CH1");
      break;
    
    //Channel 2
    case 1:
      //Check if inactive or active
      if(mode == 0)
      {
        //Inactive, dark cyan box
        display_set_fg_color(CHANNEL2_TRIG_COLOR);
      }
      else
      {
        //Active, some red box
        display_set_fg_color(0x00FF3333);
      }
      
      //Fill the channel background
      display_fill_rect(605, 25, 28, 15);
      
      //Check if inactive or active
      if(mode == 0)
      {
        //Inactive, black text
        display_set_fg_color(0x00000000);
      }
      else
      {
        //Active, white text
        display_set_fg_color(0x00FFFFFF);
      }
      
      //Display the text
      display_text(608, 26, "CH2");
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_battery_status(void)
{
  //Draw an empty battery symbol in white
  display_set_fg_color(0x00FFFFFF);
  display_fill_rect(701, 9, 3, 5);
  display_fill_rect(703, 5, 23, 13);
  
  //Check if there is any charge
  if(scopesettings.batterychargelevel)
  {
    //Keep charge level on max if above
    if(scopesettings.batterychargelevel > 20)
    {
      //Max for displaying the level
      scopesettings.batterychargelevel = 20;
    }

    //Check if charge level is low
    if(scopesettings.batterychargelevel < 4)
    {
      //Draw the level indicator in red
      display_set_fg_color(0x00FF0000);
    }
    else
    {
      //Draw the level indicator in dark green
      display_set_fg_color(0x0000BB00);
    }
    
    //Draw the indicator based on the level
    display_fill_rect(724 - scopesettings.batterychargelevel, 6, scopesettings.batterychargelevel + 1, 11);
  }  
  
  //Draw the battery charging indicator when plugged in
  if(scopesettings.batterycharging)
  {
    //Some light blue color
    display_set_fg_color(0x002222FF);

    //Draw an arrow when charging
    display_draw_horz_line(10, 708, 718);
    display_draw_horz_line(11, 708, 718);
    display_draw_horz_line(12, 708, 718);
    display_draw_vert_line(719, 8, 14);
    display_draw_vert_line(720, 9, 13);
    display_draw_vert_line(721, 10, 12);
    display_draw_vert_line(722, 11, 11);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
// Menu functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_main_menu(void)
{
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(0, 46, 149, 233);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(0, 46, 149, 233);
  
  //Three black lines between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(104, 9, 140);
  display_draw_horz_line(163, 9, 140);
  display_draw_horz_line(222, 9, 140);

  //Display the menu items  
  scope_main_menu_system_settings(0);
  scope_main_menu_picture_view(0);
  scope_main_menu_waveform_view(0);
  scope_main_menu_usb_connection(0);
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(0, 46, 149, 233, 63039);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_main_menu_system_settings(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00181818);
  }
  else
  {
    //Active so yellow background
    display_set_fg_color(0x00FFFF00);
  }
  
  //Draw the background
  display_fill_rect(9, 59, 131, 35);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00181818);
  }
  else
  {
    //Active so black foreground and yellow background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00FFFF00);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(system_settings_icon, 21, 63, 15, 25);
  
  //Display the text
  display_set_font(&font_3);
  display_text(69, 60, "System");
  display_text(68, 76, "settings");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_main_menu_picture_view(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00181818);
  }
  else
  {
    //Active so white background
    display_set_fg_color(0x00CCCCCC);
  }
  
  //Draw the background
  display_fill_rect(9, 116, 131, 35);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00181818);
  }
  else
  {
    //Active so black foreground and white background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00CCCCCC);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(picture_view_icon, 17, 122, 24, 24);
  
  //Display the text
  display_set_font(&font_3);
  display_text(73, 119, "Picture");
  display_text(79, 135, "view");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_main_menu_waveform_view(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00181818);
  }
  else
  {
    //Active so white background
    display_set_fg_color(0x00CCCCCC);
  }
  
  //Draw the background
  display_fill_rect(9, 175, 131, 35);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00181818);
  }
  else
  {
    //Active so black foreground and white background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00CCCCCC);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(waveform_view_icon, 17, 181, 24, 24);
  
  //Display the text
  display_set_font(&font_3);
  display_text(62, 178, "Waveform");
  display_text(79, 194, "view");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_main_menu_usb_connection(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00181818);
  }
  else
  {
    //Active so white background
    display_set_fg_color(0x00CCCCCC);
  }
  
  //Draw the background
  display_fill_rect(9, 235, 131, 35);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00181818);
  }
  else
  {
    //Active so black foreground and white background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00CCCCCC);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(usb_icon, 20, 239, 18, 25);
  
  //Display the text
  display_set_font(&font_3);
  display_text(80, 237, "USB");
  display_text(60, 253, "connection");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_channel1_menu(void)
{
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(161, 46, 183, 252);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(161, 46, 183, 252);
  
  //Three black lines between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(108, 175, 330);
  display_draw_horz_line(170, 175, 330);
  display_draw_horz_line(234, 175, 330);
  
  //Main texts in white  
  display_set_fg_color(0x00FFFFFF);
  
  //Select the font for the texts
  display_set_font(&font_3);
  
  //Display the texts
  display_text(176,  56, "open");
  display_text(183,  75, "CH");
  display_text(176, 118, "open");
  display_text(180, 137, "FFT");
  display_text(176, 182, "coup");
  display_text(179, 200, "ling");
  display_text(176, 247, "probe");
  display_text(176, 265, "mode");

  //Display the actual settings
  scope_channel1_enable_select();
  scope_channel1_fft_show();
  scope_channel1_coupling_select();
  scope_channel1_probe_magnification_select();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(161, 46, 183, 252, 69906);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel1_enable_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check if channel is disabled or enabled
  if(scopesettings.channel1.enable == 0)
  {
    //Disabled so dark grey box behind on
    display_fill_rect(239, 62, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(291, 62, 32, 22);
  }
  
  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if channel is disabled or enabled
  if(scopesettings.channel1.enable == 0)
  {
    //Disabled so channel 1 color box behind off
    display_fill_rect(291, 62, 32, 22);
  }
  else
  {
    //Enabled so channel 1 color box behind on
    display_fill_rect(239, 62, 32, 22);
  }

  //Check if channel is disabled or enabled
  if(scopesettings.channel1.enable == 0)
  {
    //Disabled so white on text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Enabled so black on text
    display_set_fg_color(0x00000000);
  }

  //Display the on text
  display_text(245, 65, "ON");

  //Check if channel is disabled or enabled
  if(scopesettings.channel1.enable == 0)
  {
    //Disabled so black off text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Enabled so white off text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the off text
  display_text(294, 65, "OFF");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel1_fft_show(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check if fft is disabled or enabled
  if(scopesettings.channel1.fftenable == 0)
  {
    //Disabled so dark grey box behind on
    display_fill_rect(239, 124, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(291, 124, 32, 22);
  }
  
  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if fft is disabled or enabled
  if(scopesettings.channel1.fftenable == 0)
  {
    //Disabled so channel 1 color box behind off
    display_fill_rect(291, 124, 32, 22);
  }
  else
  {
    //Enabled so channel 1 color box behind on
    display_fill_rect(239, 124, 32, 22);
  }

  //Check if fft is disabled or enabled
  if(scopesettings.channel1.fftenable == 0)
  {
    //Disabled so white on text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Enabled so black on text
    display_set_fg_color(0x00000000);
  }

  //Display the on text
  display_text(245, 127, "ON");

  //Check if fft is disabled or enabled
  if(scopesettings.channel1.fftenable == 0)
  {
    //Disabled so black off text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Enabled so white off text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the off text
  display_text(294, 127, "OFF");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel1_coupling_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check if coupling is dc or ac
  if(scopesettings.channel1.coupling == 0)
  {
    //DC so dark grey box behind ac text
    display_fill_rect(291, 188, 32, 22);
  }
  else
  {
    //AC so dark grey box behind dc text
    display_fill_rect(239, 188, 32, 22);
  }

  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if coupling is dc or ac
  if(scopesettings.channel1.coupling == 0)
  {
    //DC so channel 1 color box behind dc text
    display_fill_rect(239, 188, 32, 22);
  }
  else
  {
    //AC so channel 1 color box behind ac text
    display_fill_rect(291, 188, 32, 22);
  }

  //Check if coupling is dc or ac
  if(scopesettings.channel1.coupling == 0)
  {
    //DC so black dc text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //AC so white dc text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the dc text
  display_text(245, 191, "DC");

  //Check if coupling is dc or ac
  if(scopesettings.channel1.coupling == 0)
  {
    //DC so white ac text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //AC so black ac text
    display_set_fg_color(0x00000000);
  }

  //Display the off text
  display_text(296, 191, "AC");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel1_probe_magnification_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the boxes behind the not selected texts
  display_set_fg_color(0x00181818);
  
  //Check if coupling is dc or ac
  switch(scopesettings.channel1.magnification)
  {
    case 0:
      //dark grey times 10 and 100 magnification
      display_fill_rect(270, 245, 23, 38);
      display_fill_rect(299, 245, 30, 38);
      break;
      
    case 1:
      //dark grey times 1 and 100 magnification
      display_fill_rect(239, 245, 20, 38);
      display_fill_rect(299, 245, 30, 38);
      break;
      
    default:
      //dark grey times 1 and 10 magnification
      display_fill_rect(239, 245, 20, 38);
      display_fill_rect(270, 245, 23, 38);
      break;
  }
  
  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if which magnification to highlight
  switch(scopesettings.channel1.magnification)
  {
    case 0:
      //Highlight times 1 magnification
      display_fill_rect(239, 245, 20, 38);
      break;
      
    case 1:
      //Highlight times 10 magnification
      display_fill_rect(270, 245, 23, 38);
      break;
      
    default:
      //Highlight times 100 magnification
      display_fill_rect(299, 245, 30, 38);
      break;
  }

  //Check if magnification is 1x
  if(scopesettings.channel1.magnification == 0)
  {
    //Yes so black 1X text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white 1X text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the 1X text
  display_text(245, 247, "1");
  display_text(244, 265, "X");

  //Check if magnification is 10x
  if(scopesettings.channel1.magnification == 1)
  {
    //Yes so black 10X text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white 10X text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the 10X text
  display_text(274, 247, "10");
  display_text(276, 265, "X");

  //Check if magnification is 100x
  if(scopesettings.channel1.magnification > 1)
  {
    //Yes so black 100X text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white 100X text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the 100X text
  display_text(303, 247, "100");
  display_text(310, 265, "X");
}

//----------------------------------------------------------------------------------------------------------------------------------
void scope_open_channel2_menu(void)
{
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(288, 46, 183, 252);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(288, 46, 183, 252);
  
  //Three black lines between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(108, 302, 457);
  display_draw_horz_line(170, 302, 457);
  display_draw_horz_line(234, 302, 457);
  
  //Main texts in white  
  display_set_fg_color(0x00FFFFFF);
  
  //Select the font for the texts
  display_set_font(&font_3);
  
  //Display the texts
  display_text(303,  56, "open");
  display_text(310,  75, "CH");
  display_text(303, 118, "open");
  display_text(307, 137, "FFT");
  display_text(303, 182, "coup");
  display_text(306, 200, "ling");
  display_text(303, 247, "probe");
  display_text(303, 265, "mode");

  //Display the actual settings
  scope_channel2_enable_select();
  scope_channel2_fft_show();
  scope_channel2_coupling_select();
  scope_channel2_probe_magnification_select();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(288, 46, 183, 252, 69906);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel2_enable_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check if channel is disabled or enabled
  if(scopesettings.channel2.enable == 0)
  {
    //Disabled so dark grey box behind on
    display_fill_rect(366, 62, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(418, 62, 32, 22);
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if channel is disabled or enabled
  if(scopesettings.channel2.enable == 0)
  {
    //Disabled so channel 2 color box behind off
    display_fill_rect(418, 62, 32, 22);
  }
  else
  {
    //Enabled so channel 2 color box behind on
    display_fill_rect(366, 62, 32, 22);
  }

  //Check if channel is disabled or enabled
  if(scopesettings.channel2.enable == 0)
  {
    //Disabled so white on text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Enabled so black on text
    display_set_fg_color(0x00000000);
  }

  //Display the on text
  display_text(372, 65, "ON");

  //Check if channel is disabled or enabled
  if(scopesettings.channel2.enable == 0)
  {
    //Disabled so black off text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Enabled so white off text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the off text
  display_text(421, 65, "OFF");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel2_fft_show(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check if fft is disabled or enabled
  if(scopesettings.channel2.fftenable == 0)
  {
    //Disabled so dark grey box behind on
    display_fill_rect(366, 124, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(418, 124, 32, 22);
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if fft is disabled or enabled
  if(scopesettings.channel2.fftenable == 0)
  {
    //Disabled so channel 2 color box behind off
    display_fill_rect(418, 124, 32, 22);
  }
  else
  {
    //Enabled so channel 2 color box behind on
    display_fill_rect(366, 124, 32, 22);
  }

  //Check if fft is disabled or enabled
  if(scopesettings.channel2.fftenable == 0)
  {
    //Disabled so white on text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Enabled so black on text
    display_set_fg_color(0x00000000);
  }

  //Display the on text
  display_text(372, 127, "ON");

  //Check if fft is disabled or enabled
  if(scopesettings.channel2.fftenable == 0)
  {
    //Disabled so black off text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Enabled so white off text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the off text
  display_text(421, 127, "OFF");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel2_coupling_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check if coupling is dc or ac
  if(scopesettings.channel2.coupling == 0)
  {
    //DC so dark grey box behind ac text
    display_fill_rect(418, 188, 32, 22);
  }
  else
  {
    //AC so dark grey box behind dc text
    display_fill_rect(366, 188, 32, 22);
  }

  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if coupling is dc or ac
  if(scopesettings.channel2.coupling == 0)
  {
    //DC so channel 2 color box behind dc text
    display_fill_rect(366, 188, 32, 22);
  }
  else
  {
    //AC so channel 2 color box behind ac text
    display_fill_rect(418, 188, 32, 22);
  }

  //Check if coupling is dc or ac
  if(scopesettings.channel2.coupling == 0)
  {
    //DC so black dc text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //AC so white dc text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the dc text
  display_text(372, 191, "DC");

  //Check if coupling is dc or ac
  if(scopesettings.channel2.coupling == 0)
  {
    //DC so white ac text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //AC so black ac text
    display_set_fg_color(0x00000000);
  }

  //Display the off text
  display_text(423, 191, "AC");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel2_probe_magnification_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the boxes behind the not selected texts
  display_set_fg_color(0x00181818);
  
  //Check if coupling is dc or ac
  switch(scopesettings.channel2.magnification)
  {
    case 0:
      //dark grey times 10 and 100 magnification
      display_fill_rect(397, 245, 23, 38);
      display_fill_rect(426, 245, 30, 38);
      break;
      
    case 1:
      //dark grey times 1 and 100 magnification
      display_fill_rect(366, 245, 20, 38);
      display_fill_rect(426, 245, 30, 38);
      break;
      
    default:
      //dark grey times 1 and 10 magnification
      display_fill_rect(366, 245, 20, 38);
      display_fill_rect(397, 245, 23, 38);
      break;
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if which magnification to highlight
  switch(scopesettings.channel2.magnification)
  {
    case 0:
      //Highlight times 1 magnification
      display_fill_rect(366, 245, 20, 38);
      break;
      
    case 1:
      //Highlight times 10 magnification
      display_fill_rect(397, 245, 23, 38);
      break;
      
    default:
      //Highlight times 100 magnification
      display_fill_rect(426, 245, 30, 38);
      break;
  }

  //Check if magnification is 1x
  if(scopesettings.channel2.magnification == 0)
  {
    //Yes so black 1X text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white 1X text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the 1X text
  display_text(372, 247, "1");
  display_text(371, 265, "X");

  //Check if magnification is 10x
  if(scopesettings.channel2.magnification == 1)
  {
    //Yes so black 10X text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white 10X text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the 10X text
  display_text(401, 247, "10");
  display_text(403, 265, "X");

  //Check if magnification is 100x
  if(scopesettings.channel2.magnification > 1)
  {
    //Yes so black 100X text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white 100X text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the 100X text
  display_text(430, 247, "100");
  display_text(437, 265, "X");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_trigger_menu(void)
{
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(560, 46, 172, 186);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(560, 46, 172, 186);
  
  //Three black lines between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(107, 570, 722);
  display_draw_horz_line(168, 570, 722);
  
  //Main texts in white  
  display_set_fg_color(0x00FFFFFF);
  
  //Select the font for the texts
  display_set_font(&font_3);
  
  //Display the texts
  display_text(571,  56, "trig");
  display_text(571,  75, "mode");
  display_text(571, 118, "trig");
  display_text(571, 137, "edge");
  display_text(571, 182, "trig");
  display_text(573, 200, "CH");

  //Display the actual settings
  scope_trigger_mode_select();
  scope_trigger_edge_select();
  scope_trigger_channel_select();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(560, 46, 172, 186, 56415);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_trigger_mode_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the boxes behind the not selected texts
  display_set_fg_color(0x00181818);
  
  //Check which trigger mode is selected
  switch(scopesettings.triggermode)
  {
    case 0:
      //dark grey single and normal
      display_fill_rect(661, 57, 20, 38);
      display_fill_rect(692, 57, 21, 38);
      break;
      
    case 1:
      //dark grey auto and normal
      display_fill_rect(629, 57, 20, 38);
      display_fill_rect(692, 57, 21, 38);
      break;
      
    default:
      //dark grey auto and single
      display_fill_rect(629, 57, 20, 38);
      display_fill_rect(661, 57, 20, 38);
      break;
  }
  
  //Set trigger color for the box behind the selected text
  display_set_fg_color(TRIGGER_COLOR);
  
  //Check if which trigger mode to highlight
  switch(scopesettings.triggermode)
  {
    case 0:
      //Highlight auto mode
      display_fill_rect(629, 57, 20, 38);
      break;
      
    case 1:
      //Highlight single mode
      display_fill_rect(661, 57, 20, 38);
      break;
      
    default:
      //Highlight normal mode
      display_fill_rect(692, 57, 21, 38);
      break;
  }

  //Check if trigger mode is auto
  if(scopesettings.triggermode == 0)
  {
    //Yes so black auto text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white auto text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the auto text
  display_text(631, 58, "au");
  display_text(633, 75, "to");

  //Check if trigger mode is single
  if(scopesettings.triggermode == 1)
  {
    //Yes so black single text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white single text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the single text
  display_text(666, 56, "si");
  display_text(663, 66, "ng");
  display_text(665, 79, "le");

  //Check if trigger mode is normal
  if(scopesettings.triggermode > 1)
  {
    //Yes so black normal text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //No so white normal text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the normal text
  display_text(695, 56, "no");
  display_text(694, 66, "rm");
  display_text(696, 79, "al");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_trigger_edge_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check which trigger edge is selected
  if(scopesettings.triggeredge == 0)
  {
    //Rising so dark grey box behind falling
    display_fill_rect(671, 125, 45, 22);
  }
  else
  {
    //Falling so dark grey box behind rising
    display_fill_rect(626, 125, 40, 22);
  }
  
  //Set trigger color for the box behind the selected text
  display_set_fg_color(TRIGGER_COLOR);
  
  //Check which trigger edge is selected
  if(scopesettings.triggeredge == 0)
  {
    //Rising so trigger color box behind rising
    display_fill_rect(626, 125, 40, 22);
  }
  else
  {
    //Falling so trigger color box behind falling
    display_fill_rect(671, 125, 45, 22);
  }

  //Check which trigger edge is selected
  if(scopesettings.triggeredge == 0)
  {
    //Rising so black rising text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //Falling so white rising text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the rising text
  display_text(629, 127, "rising");

  //Check which trigger edge is selected
  if(scopesettings.triggeredge == 0)
  {
    //Rising so white falling text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Falling so black falling text
    display_set_fg_color(0x00000000);
  }

  //Display the falling text
  display_text(674, 127, "falling");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_trigger_channel_select(void)
{
  //Select the font for the texts
  display_set_font(&font_3);

  //Set dark grey color for the box behind the not selected text
  display_set_fg_color(0x00181818);
  
  //Check if channel is 1 or 2
  if(scopesettings.triggerchannel == 0)
  {
    //1 so dark grey box behind CH2 text
    display_fill_rect(680, 188, 32, 22);
  }
  else
  {
    //2 so dark grey box behind CH1 text
    display_fill_rect(632, 188, 32, 22);
  }

  //Set trigger color for the box behind the selected text
  display_set_fg_color(TRIGGER_COLOR);
  
  //Check if channel is 1 or 2
  if(scopesettings.triggerchannel == 0)
  {
    //1 so trigger color box behind CH1 text
    display_fill_rect(632, 188, 32, 22);
  }
  else
  {
    //2 so trigger color box behind CH2 text
    display_fill_rect(680, 188, 32, 22);
  }

  //Check if channel is 1 or 2
  if(scopesettings.triggerchannel == 0)
  {
    //1 so black CH1 text
    display_set_fg_color(0x00000000);
  }
  else
  {
    //2 so white CH1 text
    display_set_fg_color(0x00FFFFFF);
  }

  //Display the CH1 text
  display_text(635, 191, "CH1");

  //Check if channel is 1 or 2
  if(scopesettings.triggerchannel == 0)
  {
    //1 so white CH2 text
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //2 so black CH2 text
    display_set_fg_color(0x00000000);
  }

  //Display the CH2 text
  display_text(683, 191, "CH2");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_system_settings_menu(void)
{
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(150, 46, 244, 294);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(150, 46, 244, 294);
  
  //Four black lines between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(104, 159, 385);
  display_draw_horz_line(163, 159, 385);
  display_draw_horz_line(222, 159, 385);
  display_draw_horz_line(281, 159, 385);

  //Display the menu items  
  scope_system_settings_screen_brightness_item(0);
  scope_system_settings_grid_brightness_item(0);
  scope_system_settings_trigger_50_item();
  scope_system_settings_calibration_item(0);
  scope_system_settings_x_y_mode_item();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_left_rect_onto_screen(150, 46, 244, 294, 63039);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_system_settings_screen_brightness_item(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00181818);
  }
  else
  {
    //Active so yellow background
    display_set_fg_color(0x00FFFF00);
  }
  
  //Draw the background
  display_fill_rect(159, 59, 226, 36);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00181818);
  }
  else
  {
    //Active so black foreground and yellow background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00FFFF00);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(screen_brightness_icon, 171, 63, 24, 24);
  
  //Display the text
  display_set_font(&font_3);
  display_text(231, 60, "Screen");
  display_text(220, 76, "brightness");
  
  //Show the actual setting
  scope_system_settings_screen_brightness_value();
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_system_settings_screen_brightness_value(void)
{
  //Draw the yellow background
  display_set_fg_color(0x00FFFF00);
  display_fill_rect(332, 67, 32, 15);
  
  //Display the number with fixed width font and black color
  display_set_font(&font_0);
  display_set_fg_color(0x00000000);
  display_decimal(337, 68, scopesettings.screenbrightness);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_system_settings_grid_brightness_item(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00181818);
  }
  else
  {
    //Active so yellow background
    display_set_fg_color(0x00FFFF00);
  }
  
  //Draw the background
  display_fill_rect(159, 116, 226, 36);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00181818);
  }
  else
  {
    //Active so black foreground and yellow background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00FFFF00);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(grid_brightness_icon, 171, 122, 24, 24);
  
  //Display the text
  display_set_font(&font_3);
  display_text(240, 119, "Grid");
  display_text(220, 135, "brightness");
  
  //Show the actual setting
  scope_system_settings_grid_brightness_value();
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_system_settings_grid_brightness_value(void)
{
  //Draw the yellow background
  display_set_fg_color(0x00FFFF00);
  display_fill_rect(332, 124, 32, 15);
  
  //Display the number with fixed width font and black color
  display_set_font(&font_0);
  display_set_fg_color(0x00000000);
  display_decimal(337, 125, scopesettings.gridbrightness);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_system_settings_trigger_50_item(void)
{
  //Set the colors for white foreground and grey background
  display_set_fg_color(0x00FFFFFF);
  display_set_bg_color(0x00181818);

  //Display the icon with the set colors
  display_copy_icon_use_colors(trigger_50_percent_icon, 171, 181, 24, 24);
  
  //Display the text
  display_set_font(&font_3);
  display_text(229, 178, "Always");
  display_text(217, 194, "trigger 50%");
  
  //Show the state
  scope_display_slide_button(326, 183, scopesettings.alwaystrigger50);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_system_settings_calibration_item(int mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00181818);
  }
  else
  {
    //Active so yellow background
    display_set_fg_color(0x00FFFF00);
  }
  
  //Draw the background
  display_fill_rect(159, 235, 226, 36);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground and grey background
    display_set_fg_color(0x00FFFFFF);
    display_set_bg_color(0x00181818);
  }
  else
  {
    //Active so black foreground and yellow background
    display_set_fg_color(0x00000000);
    display_set_bg_color(0x00FFFF00);
  }

  //Display the icon with the set colors
  display_copy_icon_use_colors(baseline_calibration_icon, 171, 239, 24, 25);
  
  //Display the text
  display_set_font(&font_3);
  display_text(225, 237, "Baseline");
  display_text(219, 253, "calibration");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_system_settings_x_y_mode_item(void)
{
  //Set the colors for white foreground and grey background
  display_set_fg_color(0x00FFFFFF);
  display_set_bg_color(0x00181818);

  //Display the icon with the set colors
  display_copy_icon_use_colors(x_y_mode_display_icon, 171, 297, 24, 24);
  
  //Display the text
  display_set_font(&font_3);
  display_text(223, 295, "X-Y mode");
  display_text(231, 311, "display");
  
  //Show the state
  scope_display_slide_button(326, 299, scopesettings.xymodedisplay);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_calibration_start_text(void)
{
  //Save the screen under the baseline calibration start text
  display_set_destination_buffer(displaybuffer2);
  display_copy_rect_from_screen(395, 222, 199, 59);

  //Setup the text in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);

  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  display_fill_rect(395, 222, 199, 59);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  display_draw_rect(395, 222, 199, 59);

  //Display the text in white
  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_3);
  display_text(409, 227, "Please unplug");
  display_text(409, 243, "the probe and");
  display_text(409, 259, "USB first !");

  //Add the ok button
  scope_display_ok_button(517, 230, 0);
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_left_rect_onto_screen(395, 222, 199, 59, 63039);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_show_calibrating_text(void)
{
  //Restore the screen from under the calibration start text to get rid of it
  display_set_source_buffer(displaybuffer2);
  display_copy_rect_to_screen(395, 222, 199, 59);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  display_fill_rect(395, 222, 110, 59);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  display_draw_rect(395, 222, 110, 59);

  //Display the text in white
  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_3);
  display_text(409, 243, "Calibrating...");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_show_calibration_done_text(void)
{
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  display_fill_rect(395, 222, 110, 59);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  display_draw_rect(395, 222, 110, 59);

  //Display the text in white
  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_3);
  display_text(414, 235, "Calibration");
  display_text(416, 251, "successful");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_measures_menu(void)
{
  int item;
  int channel;
  
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  display_fill_rect(231, 263, 499, 214);

  //Draw the edge in black
  display_set_fg_color(0x00000000);
  display_draw_rect(231, 263, 499, 214);
  
  //Three horizontal black lines between the settings
  display_draw_horz_line(288, 232, 729);
  display_draw_horz_line(350, 232, 729);
  display_draw_horz_line(412, 232, 729);

  //Vertical separator between the channel sections
  display_draw_vert_line(481, 264, 476);
  
  //Vertical separators between the items
  display_draw_vert_line(294, 289, 476);
  display_draw_vert_line(356, 289, 476);
  display_draw_vert_line(418, 289, 476);
  display_draw_vert_line(544, 289, 476);
  display_draw_vert_line(606, 289, 476);
  display_draw_vert_line(668, 289, 476);
  
  //Channel 1 top bar
  display_set_fg_color(CHANNEL1_COLOR);
  display_fill_rect(482, 264, 247, 23);
  
  //Channel 2 top bar
  display_set_fg_color(CHANNEL2_COLOR);
  display_fill_rect(232, 264, 248, 23);

  //Display the channel identifier text in black
  display_set_fg_color(0x00000000);
  display_set_font(&font_2);
  display_text(490, 269, "CH1");
  display_text(240, 269, "CH2");
  
  //Display the menu items
  for(channel=0;channel<2;channel++)
  {
    //For each channel 12 items
    for(item=0;item<12;item++)
    {
      //Draw the separate items
      scope_measures_menu_item(channel, item);
    }
  }
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_right_rect_onto_screen(231, 263, 499, 214, 75646);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_measures_menu_item(int channel, int item)
{
  uint16  xpos;
  uint16  ypos;
  char   *text;
  
  //Set the x position offset for the given channel
  if(channel == 0)
  {
    //Channel 1 is on the right side
    xpos = 482;
  }
  else
  {
    //Channel 2 is on the left side
    xpos = 232;
  }
  
  //Set the text and the position for the given item 
  switch(item)
  {
    case 0:
      text  = "Vmax";
      xpos += 15;
      ypos  = 312;
      break;

    case 1:
      text  = "Vmin";
      xpos += 79;
      ypos  = 312;
      break;

    case 2:
      text  = "Vavg";
      xpos += 141;
      ypos  = 312;
      break;

    case 3:
      text  = "Vrms";
      xpos += 203;
      ypos  = 312;
      break;

    case 4:
      text  = "VPP";
      xpos += 19;
      ypos  = 376;
      break;

    case 5:
      text  = "VP";
      xpos += 86;
      ypos  = 376;
      break;

    case 6:
      text  = "Freq";
      xpos += 143;
      ypos  = 376;
      break;

    case 7:
      text  = "Cycle";
      xpos += 201;
      ypos  = 376;
      break;

    case 8:
      text  = "Tim+";
      xpos += 17;
      ypos  = 437;
      break;

    case 9:
      text  = "Tim-";
      xpos += 80;
      ypos  = 437;
      break;

    case 10:
      text  = "Duty+";
      xpos += 138;
      ypos  = 437;
      break;

    case 11:
      text  = "Duty-";
      xpos += 202;
      ypos  = 437;
      break;
      
    default:
      return;
  }
  
  //Check if item is on or off
  if(scopesettings.measuresstate[channel][item] == 0)
  {
    //Off so some dark grey text
    display_set_fg_color(0x00444444);
  }
  else
  {
    //On so white text
    display_set_fg_color(0x00FFFFFF);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(xpos, ypos, text);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_slider(uint16 xpos, uint16 ypos, uint8 position)
{
  //Save the screen under the screen brightness slider
  display_set_destination_buffer(displaybuffer2);
  display_copy_rect_from_screen(xpos, ypos, 331, 58);

  //Setup the slider menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);

  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(xpos, ypos, 331, 58);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(xpos, ypos, 331, 58);
  
  //Display the actual slider
  scope_display_slider(xpos, ypos, position);
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_left_rect_onto_screen(xpos, ypos, 331, 58, 63039);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_slider(uint16 xpos, uint16 ypos, uint8 position)
{
  uint16 x = xpos + 20;
  uint16 y = ypos + 24;
  uint16 w = (291 * position) / 100;
  uint16 ys = ypos + 23;
  uint16 ye = ypos + 35;

  //Clear the background first
  display_set_fg_color(0x00181818);
  display_fill_rect(xpos + 8, ypos + 17, 315, 24);
  
  //Draw the first part of the slider bar in a yellow color
  display_set_fg_color(0x00FFFF00);
  display_fill_rounded_rect(x, y, w, 10, 2);
  
  //Adjust positions for the grey part
  x += w;
  w  = 291 - w;
  
  //Draw the last part of the slider bar in a light grey color
  display_set_fg_color(0x00666666);
  display_fill_rounded_rect(x, y, w, 10, 2);
  
  //Adjust positions for drawing the knob
  x -= 11;
  y -= 6;
  
  //Draw the knob
  display_set_fg_color(0x00AAAAAA);
  display_fill_rounded_rect(x, y, 22, 22, 2);
  
  //Draw the black lines on the knob
  display_set_fg_color(0x00000000);
  display_draw_vert_line(x +  6, ys, ye);
  display_draw_vert_line(x + 11, ys, ye);
  display_draw_vert_line(x + 16, ys, ye);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 scope_move_slider(uint16 xpos, uint16 ypos, uint8 *position)
{
  uint16 xs = xpos + 20;
  uint16 value;
  int16 filter = xtouch - prevxtouch;
  
  //Check if update needed
  if((filter > -3) && (filter < 3))
  {
    //When change in movement less the absolute 3 don't process
    return(0);
  }
  
  //Save for next filter check
  prevxtouch = xtouch;
  
  //Make sure it stays in allowed range
  if(xtouch <= xs)
  {
    //Below slider keep it on 0
    value = 0;
  }
  else if(xtouch >= (xpos + 311))
  {
    //Above slider keep it on max
    value = 100;
  }
  else
  {
    //Based on xtouch position calculate a new position from 0 to 100
    value = ((xtouch - xs) * 100) / 291;
  }
  
  //Update the position variable
  *position = value;
  
  //Show the new position on screen
  scope_display_slider(xpos, ypos, value);
  
  //Signal there is change
  return(1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_slide_button(uint16 xpos, uint16 ypos, uint8 state)
{
  uint16 linex      = xpos + 8;
  uint16 lineystart = ypos + 6;
  uint16 lineyend   = ypos + 15;
  uint16 buttonx    = xpos + 4;
  uint32 edgecolor  = 0x00444444;
  uint32 fillcolor  = 0x00888888;
  
  if(state == 1)
  {
    //Displace the lines and button by 19 pixels
    linex   += 19;
    buttonx += 19;

    //Set the enabled colors
    edgecolor  = 0x00008800;
    fillcolor  = 0x0000FF00;
  }
  
  //Draw the background
  display_set_fg_color(fillcolor);
  display_fill_rounded_rect(xpos, ypos, 45, 21, 2);

  //Draw the edge
  display_set_fg_color(edgecolor);
  display_draw_rounded_rect(xpos, ypos, 45, 21, 2);

  //Draw button in dark grey
  display_set_fg_color(0x00444444);
  display_fill_rect(buttonx, ypos + 4, 19, 13);
  
  //Draw lines in black
  display_set_fg_color(0x00000000);  
  display_draw_vert_line(linex,     lineystart, lineyend);
  display_draw_vert_line(linex + 3, lineystart, lineyend);
  display_draw_vert_line(linex + 6, lineystart, lineyend);
  display_draw_vert_line(linex + 9, lineystart, lineyend);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_ok_button(uint16 xpos, uint16 ypos, uint8 mode)
{
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so dark grey background
    display_set_fg_color(0x00333333);
  }
  else
  {
    //Active so light grey background
    display_set_fg_color(0x00CCCCCC);
  }
  
  //Draw the background
  display_fill_rect(xpos, ypos, 66, 44);

  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive so white foreground
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Active so black foreground
    display_set_fg_color(0x00000000);
  }
  
  //Display the text
  display_set_font(&font_3);
  display_text(xpos + 24, ypos + 14, "OK");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_draw_grid(void)
{
  uint32 color;
  register uint32 i;
  
  //Only draw the grid when something will show (not in the original code)
  if(scopesettings.gridbrightness > 3)
  {
    //Calculate a grey shade based on the grid brightness setting
    color = (scopesettings.gridbrightness * 255) / 100;
    color = (color << 16) | (color << 8) | color;

    //Set the color for drawing
    display_set_fg_color(color);
    
    //Draw the edge
    display_draw_rect(2, 46, 726, 404);

    //Draw the center lines
    display_draw_horz_line(249,  2, 726);
    display_draw_vert_line(364, 46, 448);
    
    //Draw the ticks on the x line
    for(i=4;i<726;i+=5)
    {
      display_draw_vert_line(i, 247, 251);
    }

    //Draw the ticks on the y line
    for(i=49;i<448;i+=5)
    {
      display_draw_horz_line(i, 362, 366);
    }

    //Draw the horizontal dots
    for(i=99;i<448;i+=50)
    {
      display_draw_horz_dots(i, 4, 726, 5);
    }

    //Draw the vertical dots
    for(i=14;i<726;i+=50)
    {
      display_draw_vert_dots(i, 49, 448, 5);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_draw_pointers(void)
{
  uint32 position;
  
  //Draw channel 1 pointer when it is enabled
  if(scopesettings.channel1.enable)
  {
    //y position for the channel 1 trace center pointer
    position = 448 - scopesettings.channel1.traceoffset;
    
    //Limit on the top of the displayable region
    if(position < 46)
    {
      position = 46;
    }
    //Limit on the bottom of the displayable region
    else if(position > 441)
    {
      position = 441;
    }
    
    //Set the colors for drawing
    display_set_fg_color(CHANNEL1_COLOR);
    display_set_bg_color(0x00000000);
    
    //Select the font for this pointer id
    display_set_font(&font_0);
    
    //Draw the pointer
    display_left_pointer(2, position, '1');
  }
  
  //Draw channel 2 pointer when it is enabled
  if(scopesettings.channel2.enable)
  {
    //y position for the channel 2 trace center pointer
    position = 448 - scopesettings.channel2.traceoffset;
    
    //Limit on the top of the displayable region
    if(position < 46)
    {
      position = 46;
    }
    //Limit on the bottom of the displayable region
    else if(position > 441)
    {
      position = 441;
    }
    
    //Set the colors for drawing
    display_set_fg_color(CHANNEL2_COLOR);
    display_set_bg_color(0x00000000);
    
    //Select the font for this pointer id
    display_set_font(&font_0);
    
    //Draw the pointer
    display_left_pointer(2, position, '2');
  }
  
  //Draw trigger position and level pointer when time base in range of 10mS/div - 10nS/div
  if(scopesettings.timeperdiv > 10)
  {
    //x position for the trigger position pointer
    position = scopesettings.triggerposition + 2;
    
    //Limit on the left of the displayable region
    if(position < 10)
    {
      position = 10;
    }
    //Limit on the right of the displayable region
    else if(position > 718)
    {
      position = 718;
    }

    //Set the colors for drawing
    display_set_fg_color(TRIGGER_COLOR);
    display_set_bg_color(0x00000000);
    
    //Draw the pointer
    display_top_pointer(position, 47);

    //y position for the trigger level pointer
    position = 448 - scopesettings.triggeroffset;
    
    //Limit on the top of the displayable region
    if(position < 46)
    {
      position = 46;
    }
    //Limit on the bottom of the displayable region
    else if(position > 441)
    {
      position = 441;
    }
    
    //Select the font for this pointer id
    display_set_font(&font_3);
    
    //Draw the pointer
    display_right_pointer(707, position, 'T');
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_draw_time_cursors(void)
{
  //Only draw the lines when enabled
  if(scopesettings.timecursorsenable)
  {
    //Set the color for the dashed lines
    display_set_fg_color(CURSORS_COLOR);
   
    //Draw the lines
    display_draw_vert_dashes(scopesettings.timecursor1position, 48, 448, 3, 3);
    display_draw_vert_dashes(scopesettings.timecursor2position, 48, 448, 3, 3);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_draw_volt_cursors(void)
{
  //Only draw the lines when enabled
  if(scopesettings.voltcursorsenable)
  {
    //Set the color for the dashed lines
    display_set_fg_color(CURSORS_COLOR);
   
    //Draw the lines
    display_draw_horz_dashes(scopesettings.voltcursor1position, 5, 726, 3, 3);
    display_draw_horz_dashes(scopesettings.voltcursor2position, 5, 726, 3, 3);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_process_trace_data(void)
{
  //Based on the time base setting different actions are needed for getting the trace data
  //Check on time base setting if range is between 50S/div and 100ms/div
  if(scopesettings.timeperdiv < 9)
  {
    //Reads an average of ten data points for each channel, active or not
    scope_get_long_timebase_data();
    
    //Point needs to be drawn twice to be on the correct time base speed
    //So called here as well as in the main loop
    scope_display_trace_data();
  }
  else
  {
    //Check if running and not in a touch state
    if((scopesettings.runstate == 0) && (touchstate != 2))
    {
      //Read trace data for active channels
      scope_get_short_timebase_data();
      
      //scope_process_short_timebase_data();
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_get_long_timebase_data(void)
{
  //Default timeout for 50S/div
  uint32 timeout = 2000;
  uint32 curticks;
  uint32 signaladjust;
  uint32 temp1, temp2;
  
  //Send the time base command for the longer settings
  fpga_set_long_timebase();
  
  //Get the delay setting based on the time base
  switch(scopesettings.timeperdiv)
  {
    //20S/div
    case 1:
      timeout = 1000;
      break;

    //10S/div
    case 2:
      timeout = 400;
      break;

    //5S/div
    case 3:
      timeout = 200;
      break;

    //2S/div
    case 4:
      timeout = 80;
      break;

    //1S/div
    case 5:
      timeout = 40;
      break;

    //500mS/div
    case 6:
      timeout = 20;
      break;

    //200mS/div
    case 7:
      timeout = 8;
      break;

    //100mS/div
    case 8:
      timeout = 4;
      break;
  }
  
  //Make the timeout timer tick related by adding it to the previous capture
  timeout += scopesettings.previoustimerticks;
  
  //For smaller timeouts (500mS/div, 200mS/div and 100mS/div) stay in the wait loop even if there is touch
  while((scopesettings.timeperdiv > 5) || (havetouch == 0))
  {
    //Get the current ticks
    curticks = timer0_get_ticks();
  
    //Check if there is a timeout
    //While technically prone to error on timer ticks overflow the scope has to be running for >49 days before it occurs
    if(curticks >= timeout)
    {
      //Save the current ticks for next timeout and bail out the loop
      scopesettings.previoustimerticks = curticks;
      break;
    }
    
    //Scan the touch panel to see if there is user input
    tp_i2c_read_status();
  }
    
  //Wait an extra 40 milliseconds
  timer0_delay(40);
  
  //Some mode select command for the FPGA (0x01 for long time base)
  fpga_write_cmd(0x28);
  fpga_write_byte(0x01);
  
  //Read, accumulate and average 10 bytes of channel 1 trace data
  channel1tracebuffer1[0]= fpga_average_trace_data(0x24);
  
  //Read, accumulate and average 10 bytes of channel 2 trace data
  channel2tracebuffer1[0] = fpga_average_trace_data(0x26);
  
  //Need insight in the code that displays the data to get an understanding of the next bit of code
  //It is a more or less straight conversion from what Ghidra shows
  
  //Some fractional scaling on the signal to fit it on screen???
  //Adjust the channel 1 signal based on the volts per div setting
  signaladjust = channel1tracebuffer1[0] * signal_adjusters[scopesettings.channel1.voltperdiv];
  temp1 = ((0xA3D7 * signaladjust) + 0xA3D7) >> 0x16;
  temp2 = signaladjust + (((uint64)((uint64)signaladjust * (uint64)0x51EB851F) >> 0x25) * -100);
  
  //If above half the pixel up to next one?????
  if(temp2 > 50)
  {
    temp1++;
  }
  
  //Store it somewhere
  channel1tracebuffer3[0] = temp1;                    //At address 0x801A916A in original code
  
  //Check if data needs to be doubled
  if(scopesettings.channel1.voltperdiv == 6)          //This is missing in the original code
  {
    //Only on highest sensitivity
    temp1 <<= 1;
  }
  
  //Check if outside displayable range??
  if(temp1 > 401)
  {
    //Keep it on max allowed
    channel1tracebuffer4[0] = 401;                    //At address 0x801AC04A in original code
  }
  else
  {
    //Else store it again in an other location
    channel1tracebuffer4[0] = temp1;
  }
  
  //Some fractional scaling on the signal to fit it on screen???
  //Adjust the channel 2 signal based on the volts per div setting
  signaladjust = channel2tracebuffer1[0] * signal_adjusters[scopesettings.channel2.voltperdiv];
  temp1 = ((0xA3D7 * signaladjust) + 0xA3D7) >> 0x16;
  temp2 = signaladjust + (((uint64)((uint64)signaladjust * (uint64)0x51EB851F) >> 0x25) * -100);
  
  //If above half the pixel up to next one?????
  if(temp2 > 50)
  {
    temp1++;
  }
  
  //Store it somewhere
  channel2tracebuffer3[0] = temp1;               //At address 0x801AA8DA in original code
  
  //Check if data needs to be doubled
  if(scopesettings.channel2.voltperdiv == 6)     //This is missing in the original code
  {
    //Only on highest sensitivity
    temp1 <<= 1;
  }
  
  //Check if outside displayable range??
  if(temp1 > 401)
  {
    //Keep it on max allowed
    channel2tracebuffer4[0] = 401;               //At address 0x801AD7BA in original code
  }
  else
  {
    //Else store it again in an other location
    channel2tracebuffer4[0] = temp1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_get_short_timebase_data(void)
{
  uint32 data;
  uint32 count;
  uint32 command;
  uint32 triggered = 0;
  uint32 signaladjust;
  
  //Check if time base in range 50mS/div - 50nS/div or trigger mode is single or normal
  if((scopesettings.timeperdiv < 28) || scopesettings.triggermode)
  {
    //Set the trigger level if so
    fpga_set_trigger_level();
  }
  
  //Write the short time base setting to the FPGA
  fpga_set_short_timebase();
  
  //Some bounds setting. Zero here, One after trigger???
  fpga_write_cmd(0x0F);
  fpga_write_byte(0x00);

  //Some mode select command for the FPGA (0x00 for short time base)
  fpga_write_cmd(0x28);
  fpga_write_byte(0x00);

  //Some start command??
  fpga_write_cmd(0x01);
  fpga_write_byte(0x01);
  
  //Send check on ready command
  fpga_write_cmd(0x05);
  
  //Wait for the flag to become 1
  while((fpga_read_byte() & 1) == 0);
  
  //Test again to make sure it was no glitch?????
  while((fpga_read_byte() & 1) == 0);
  
  //Some stop command??
  fpga_write_cmd(0x01);
  fpga_write_byte(0x00);
  
  //Backup the settings
  scopesettings.timeperdivbackup = scopesettings.timeperdiv;
  scopesettings.channel1.voltperdivbackup = scopesettings.channel1.voltperdiv;
  scopesettings.channel2.voltperdivbackup = scopesettings.channel2.voltperdiv;
  
  //Check if screen needs to be redrawn
  if(scopesettings.updatescreen)
  {
    //Reset the flag so only done once until new request
    scopesettings.updatescreen = 0;
    
    //Draw directly on the screen
    display_set_screen_buffer(maindisplaybuffer);
      
    //Clear the trace portion of the screen
    display_set_fg_color(0x00000000);
    display_fill_rect(2, 47, 728, 432);
    
    //Draw the grid lines and dots based on the grid brightness setting
    scope_draw_grid();
    
    //Draw the signal center, trigger level and trigger position pointers
    scope_draw_pointers();
  }
  
  //Send check on triggered command to the FPGA
  fpga_write_cmd(0x0A);
  
  //Wait for the FPGA to signal triggered or touch panel is touched or signals or cursors are being moved
  while(((fpga_read_byte() & 1) == 0) && (havetouch == 0) && (touchstate != 2))
  {
    //Scan the touch panel
    tp_i2c_read_status();
  }
  
  //Some bounds setting. Zero here, One after trigger???
  fpga_write_cmd(0x0F);
  fpga_write_byte(0x01);
  
  //Check on trigger mode not being auto
  if(scopesettings.triggermode)
  {
    //Check if there is touch
    if(havetouch)
    {
      //Signal this in some state variables
      scopesettings.triggerflag2 = 1;
      
      //Check if single mode
      if(scopesettings.triggermode == 1)
      {
        //Signal this in the flags
        scopesettings.triggerflag1 = 0;
        scopesettings.triggerflag3 = 0;
      }
      else
      {
        //In normal mode
        if(scopesettings.triggerflag3 == 0)
        {
          scopesettings.triggerflag1 = 0;
        }
        else
        {
          scopesettings.triggerflag1 = 1;
        }
      }
      
      return;
    }
    
    //Check if in single mode
    if(scopesettings.triggermode == 1)
    {
      //Switch to stopped
      scopesettings.runstate = 1;
      
      //Show this on the screen
      scope_run_stop_text();
      
      //Backup the settings
      scopesettings.channel1.voltperdivbackup = scopesettings.channel1.voltperdiv;
      scopesettings.channel2.voltperdivbackup = scopesettings.channel2.voltperdiv;
    }
    
    //Switch some mode
    scopesettings.triggerflag3 = 1;
  }

  //Not sure if this name is correct. Sends command 0x14 and formats and translates returned data
  //Later on used to send to the FPGA with command 0x1F
  data = fpga_prepare_for_transfer();

  //Handle the returned data based on the time base setting
  //For the range 50mS/div - 500nS/div (50S/div - 100mS/div are handled in the long time base function)
  if(scopesettings.timeperdiv < 25)
  {
    //Check if range is 50mS/div - 20mS/div or 10mS/div - 500nS/div
    if(scopesettings.timeperdiv < 11)
    {
      //For 50mS/div and 20mS/div use 10
      data = 10;
    }
    else
    {
      //For 10mS/div - 500nS/div add or subtract data based on from FPGA returned value
      if(data < 750)
      {
        //Less the 750 make it bigger
        data = data + 3345;
      }
      else
      {
        //More then 750 make it smaller
        data = data - 750;
      }
    }
  }
  else
  {
    //Get correction value for the time base range 200nS/div - 10nS/div
    signaladjust = timebase_adjusters[scopesettings.timeperdiv - 25];
    
    //Check if need to add or subtract
    if(data < signaladjust)
    {
      //Perform some other adjustment
      data = 4095 - (signaladjust - data);
    }
    else
    {
      //Take adjuster of
      data = data - signaladjust;
    }
  }
  
  //Check if channel 1 is enabled
  if(scopesettings.channel1.enable)
  {
    //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
    fpga_write_cmd(0x1F);
    fpga_write_short(data);
    
    //Determine the number of bytes to read based on the time base setting
    if(scopesettings.timeperdiv < 11)
    {
      //For 50mS/div and 20mS/div only 750 bytes
      count = 750;
    }
    else
    {
      //For 10mS/div - 10nS/div 1500 bytes
      count = 1500;
    }
    
    //Get the FPGA command to read from based on the trigger channel
    command = fpga_read_parameter_ic(0x0C, scopesettings.triggerchannel);
    
    //Read the bytes into a trace buffer
    fpga_read_trace_data(command, channel1tracebuffer1, count);

    //Check if triggered on this channel
    if(scopesettings.triggerchannel == 0)
    {
      triggered = scope_process_trigger();
    }
    
    //Pre process data based on time base setting
    switch(scopesettings.timeperdiv)
    {
      //250nS/div
      case 25:
        //Call pre process function for it
        scope_pre_process_250ns_data(channel1tracebuffer1, 2500);
        break;

      //100nS/div
      case 26:
        //Call pre process function for it
        scope_pre_process_100ns_data(channel1tracebuffer1, 2500);
        break;

      //50nS/div
      case 27:
        //Call pre process function for it
        scope_pre_process_50ns_data(channel1tracebuffer1, 2500);
        break;

      //25nS/div and 10nS/div
      case 28:
      case 29:
        //Prepare FPGA for reading again
        //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
        fpga_write_cmd(0x1F);
        fpga_write_short(data);
        
        //Read the bytes into a trace buffer
        fpga_read_trace_data(0x21, channel1tracebuffer2, 1500);                //In original code this is done in buffer1
        
        //Call pre process function for it
        scope_pre_process_25ns_data(channel1tracebuffer2, 0, 1500);
        scope_process_25ns_data(channel1tracebuffer2, 0, 1500);
        break;
    }

    //Set sample count based on time base setting
    if(scopesettings.timeperdiv >= 25)
    {
      //For settings 250nS/div - 10nS/div. This would mean that for 250nS/div, 100nS/div and 50nS/div samples are interpolated???
      count = 2500;
    }
    else if(scopesettings.timeperdiv >= 11)  //In original code this is 9, but below that is handled in long time base function
    {                                        //And based on the code before I guessed it to be 11. Needs to be confirmed
      //For settings 10mS/div - 250nS/div
      count = 1500;
    }
    else
    {
      //For settings 50mS/div and 20mS/div
      count = 750;
    }

    //Adjust the data into another buffer
    scope_adjust_data(channel1tracebuffer3, channel1tracebuffer1, count, scopesettings.channel1.voltperdiv);
    
    //Copy the buffer to another buffer
    memcpy((uint8*)channel1tracebuffer4, (uint8*)channel1tracebuffer3, count);
    
    //Check if on highest sensitivity (50mV/div on 1x probe setting)
    if(scopesettings.channel1.voltperdiv == 6)
    {
      //Adjust data in buffer 4 to be twice the magnitude
      scope_double_data(channel1tracebuffer4, count);
      
      //Adjust the data for trace offset???
      scope_offset_data(channel1tracebuffer4, count, scopesettings.channel1.traceoffset);
    }

    //Limit the data to max range
    scope_limit_data(channel1tracebuffer4, count);   //In the original they process 2500 samples no matter what
    
    //Do additional handling for time base range 50mS/div - 500nS/div
    if(scopesettings.timeperdiv < 25)
    {
      //Filter the data
      scope_filter_data(channel1tracebuffer4, count - 2);    //In the original the do 2998 samples no matter what
    }
    
    //Call some functions here dedicated to channel 1
    //FUN_800049a0();
    //FUN_80006654();
    
    //And if some variable is 0 call another one
    //if (pcVar2[0x48] == '\0')
    //{
    //  FUN_80003ec8();
    //}
  }
  
  //Handle channel 2 here
  
  
  //Set flags based on being triggered
  if(triggered)
  {
    //Triggered????
    scopesettings.triggerflag4 = 1;
    scopesettings.triggerflag1 = 0;
    scopesettings.triggerflag2 = 0;
  }
  else
  {
    //Not triggered????
    scopesettings.triggerflag4 = 0;
    scopesettings.triggerflag1 = 1;
    scopesettings.triggerflag2 = 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_adjust_data(uint16 *destination, uint16 *source, uint32 count, uint8 voltperdiv)
{
  uint32 signaladjust;
  uint32 temp1, temp2, temp3;

  //Translate the channel 1 volts per div setting
  signaladjust = fpga_read_parameter_ic(0x0B, voltperdiv) & 0x0000FFFF;
  
  //Process the samples
  while(count)
  {
    //Some fractional scaling on the signal to fit it on screen???
    //Adjust the channel 1 signal based on the volts per div setting
    temp1 = *source * signaladjust;
    temp2 = ((0xA3D7 * temp1) + 0xA3D7) >> 0x16;
    temp3 = temp1 + (((uint64)(temp1 * 0x51EB851F) >> 0x25) * -100);

    //If above half the pixel up to next one?????
    if(temp3 > 50)
    {
      temp2++;
    }

    //Store it for further handling
    *destination = temp2;

    //Point to next source and destination
    source++;
    destination++;

    //One more sample done
    count--;
  }
  
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_offset_data(uint16 *buffer, uint32 count, uint32 offset)
{
  //Process the samples
  while(count)
  {
    //Check if the data is smaller then the offset
    if(*buffer < offset)
    {
      //If so limit to top of the screen
      *buffer = 0;
    }
    else
    {
      //Else take of the offset
      *buffer = *buffer - offset;
    }

    //Point to next sample
    buffer++;

    //One more sample done
    count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_limit_data(uint16 *buffer, uint32 count)
{
  //Process the samples
  while(count)
  {
    //Check if the data is smaller then the offset
    if(*buffer > 401)
    {
      //If so limit to top of the screen
      *buffer = 401;
    }

    //Point to next sample
    buffer++;

    //One more sample done
    count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_filter_data(uint16 *buffer, uint32 count)
{
  uint32 sample1, sample2, sample3;
  uint32 midlow, midhigh;
  
  //Process the samples
  while(count)
  {
    //Get three consecutive samples
    sample1 = buffer[0];
    sample2 = buffer[1];
    sample3 = buffer[2];
    
    //Set filter ranges
    midlow  = sample2 - 6;
    midhigh = sample2 + 6;
    
    //Check if first and last sample not near the middle sample and at the same side of it. (both below or above)
    if(((sample1 < midlow) && (sample3 < midlow)) || ((midhigh < sample1) && (midhigh < sample3)))
    {
      //If so set the middle sample to the average of the other two
      buffer[1] = (sample1 + sample3) >> 1;
    }

    //Point to next sample
    buffer++;

    //One more sample done
    count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_double_data(uint16 *buffer, uint32 count)
{
  //Process the samples
  while(count)
  {
    //Multiply the sample by two
    *buffer <<= 1;

    //Point to next sample
    buffer++;

    //One more sample done
    count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 scope_process_trigger(void)
{
  uint16 *buffer;
  uint32  index;
  uint32  level = scopesettings.triggerlevel;
  uint32  havetrigger = 1;
  uint32  lower  = 0;
  uint32  higher = 0;
  
  //Process based on time base setting and trigger mode
  //Skip for 50mS/div, 20mS/div, 250nS/div, 100nS/div, 50nS/div, 25nS/div and 10nS/div or single and normal trigger modes
  if((scopesettings.timeperdiv > 10) && (scopesettings.timeperdiv < 25) && (scopesettings.triggermode = 0))
  {
    //Select the trace buffer to process based on the trigger channel
    if(scopesettings.triggerchannel == 0)
    {
      //Channel 1 buffer
      buffer = channel1tracebuffer1;
    }
    else
    {
      //Channel 2 buffer
      buffer = channel2tracebuffer1;
    }

    //Set a starting point for checking on trigger
    index = 745;
    
    //Check on which edge to trigger
    if(scopesettings.triggeredge == 0)
    {
      //Rising edge
      //Only check around center point of the buffer
      while(index < 755)
      {
        //Check if previous sample lower then level and next sample equal or higher then level
        if((buffer[index - 1] < level) && (level <= buffer[index + 1]))
        {
          //Is this a triggered signal or not???
          havetrigger = 0;
          break;
        }
        
        //One sample done
        index++;
      }
    }
    else
    {
      //Falling edge
      //Only check around center point of the buffer
      while(index < 755)
      {
        //Check if previous sample higher then level and next sample equal or lower then level
        if((level < buffer[index - 1]) && (buffer[index + 1] <= level))
        {
          //Is this a triggered signal or not???
          havetrigger = 0;
          break;
        }
        
        //One sample done
        index++;
      }
    }
    
    //Set a new starting point for checking
    index = 100;
    
    //Process the buffer from sample 100 to sample 1400
    while(index < 1400)
    {
      //Check if sample lower then level
      if(buffer[index] < level)
      {
        //Signal had sample lower  then level
        lower = 1;
      }
      //Check if sample higher then level
      else if(buffer[index] > level)
      {
        //Signal had sample higher then level
        higher = 1;
      }
        
      //One sample done
      index++;
    }
    
    //Check if all samples where on trigger level
    if((lower == 0) || (higher == 0))
    {
      //Return zero if so
      return(0);
    }
    
    //Otherwise return the flag from edge scan
    return(havetrigger);  
  }
  
  //No valid time base or trigger setting just return 0
  return(0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_pre_process_250ns_data(uint16 * buffer, uint32 count)   //In original code an offset is used, but it is always 0
{
  uint32 cnt;
  uint32 sample;
  uint16 *ptr1 = temptracebuffer1;
  uint16 *ptr2 = buffer;
  
  //More efficient way of doing this would be to handle the samples from the end and keep them in a single buffer
  //Need to investigate this further
  //This has to do with what the FPGA returns. The time base setting in the FPGA is the same for these time base settings
  //So some manipulation of the samples needs to be done.
  //Base is 500nS/div so for 250nS/div they are doubled, for 100nS/div they are multiplied by 5, so probably for 50nS/div times 10
  
  //Only do half the samples
  cnt = count >> 1;
  
  //Check if odd number of samples to process
  if(cnt & 1)
  {
    //Copy the odd sample
    *ptr1 = *ptr2;
  }
  else
  {
    //Point to before data since copy loop starts on next data
    ptr1 -= 2;
    ptr2--;
  }
  
  //Handle two samples per loop
  cnt >>= 1;
  
  //Process the samples
  while(cnt)
  {
    //Copy samples with an interleave in the destination
    ptr1[2] = ptr2[1];
    ptr1[4] = ptr2[2];
    
    //Point to next destination and source
    ptr1 += 4;
    ptr2 += 2;
    
    //Two samples done
    cnt--;
  }
  
  //Average a sample in between
  cnt = (count >> 1) - 1;
  
  //Check if odd number of samples to process
  if(cnt & 1)
  {
    //Point to the buffer
    ptr1 = temptracebuffer1;
    
    //Average the odd sample
    ptr1[1] = (ptr1[0] + ptr1[2]) >> 1;
  }
  else
  {
    //Point to before data since copy loop starts on next data
    ptr1 = temptracebuffer1 - 2;
  }
  
  //Handle two samples per loop
  cnt >>= 1;

  //Process the samples
  while(cnt)
  {
    //Get the middle sample
    sample = ptr1[4];
    
    //Average the in between samples
    ptr1[3] = (ptr1[2] + sample) >> 1;
    ptr1[5] = (sample + ptr1[6]) >> 1;
    
    //Point to next set to handle
    ptr1 += 4;
    
    //Two samples done
    cnt--;
  }

  //Point to the buffers to copy back the samples to the original buffer
  ptr1 = temptracebuffer1;
  ptr2 = buffer;
  
  //Check if odd number of samples to process
  if(count & 1)
  {
    *ptr2 = *ptr1;
  }
  else
  {
    //Point to before data since copy loop starts on next data
    ptr1--;
    ptr2--;
  }
  
  //Two samples at a time so half the count
  cnt = count >> 1;
  
  //Copy the samples
  while(cnt)
  {
    //Do two samples per loop
    ptr2[1] = ptr1[1];
    ptr2[2] = ptr1[2];
    
    //Point to next destination and source
    ptr1 += 2;
    ptr2 += 2;
    
    //Two samples done
    cnt--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_pre_process_100ns_data(uint16 * buffer, uint32 count)
{
  uint32 cnt1, cnt2;
  uint32 sample1, sample2;
  int32  delta;
  uint16 *ptr1 = temptracebuffer1;
  uint16 *ptr2 = buffer;
  
  //Only one fifth of the samples
  cnt1 = count / 5;
  
  //Check if odd number of samples to process
  if(cnt1 & 1)
  {
    //Copy the odd sample
    *ptr1 = *ptr2;
  }
  else
  {
    //Point to before data since copy loop starts on next data
    ptr1 -= 5;
    ptr2--;
  }
  
  //Handle two samples per loop
  cnt2 = cnt1 >> 1;
  
  //Process the samples
  while(cnt2)
  {
    //Copy samples with an interleave of 5 in the destination
    ptr1[5]  = ptr2[1];
    ptr1[10] = ptr2[2];
    
    //Point to next destination and source
    ptr1 += 10;
    ptr2 += 2;
    
    //Two samples done
    cnt2--;
  }
  
  //One less sample to do
  cnt1--;
  
  //Point to the buffer to work in
  ptr1 = temptracebuffer1;
  
  //Process the samples to be interpolated in between the copied ones
  while(cnt1)
  {
    //The original code uses a different approach
    //Need to check if this is correct
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 = ptr1[0] << 22;
    sample2 = ptr1[5] << 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - sample2) / 5;
    
    for(cnt2=1;cnt2<5;cnt2++)
    {
      //Calculate the next sample with fixed point calculation
      sample1 += delta;
      
      //Store the decimal part of it
      ptr1[cnt2] = sample1 >> 22;
    }
    
    //One set of samples done
    cnt1--;
  }
  
  //Point to the buffers to copy back the samples to the original buffer
  ptr1 = temptracebuffer1;
  ptr2 = buffer;
  
  //Check if odd number of samples to process
  if(count & 1)
  {
    *ptr2 = *ptr1;
  }
  else
  {
    //Point to before data since copy loop starts on next data
    ptr1--;
    ptr2--;
  }
  
  //Two samples at a time so half the count
  cnt1 = count >> 1;
  
  //Copy the samples
  while(cnt1)
  {
    //Do two samples per loop
    ptr2[1] = ptr1[1];
    ptr2[2] = ptr1[2];
    
    //Point to next destination and source
    ptr1 += 2;
    ptr2 += 2;
    
    //Two samples done
    cnt1--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_pre_process_50ns_data(uint16 * buffer, uint32 count)
{
  uint32 cnt1, cnt2;
  uint32 sample1, sample2;
  int32  delta;
  uint16 *ptr1 = temptracebuffer1;
  uint16 *ptr2 = buffer;
  
  //Only one tenth of the samples
  cnt1 = count / 10;
  
  //Check if odd number of samples to process
  if(cnt1 & 1)
  {
    //Copy the odd sample
    *ptr1 = *ptr2;
  }
  else
  {
    //Point to before data since copy loop starts on next data
    ptr1 -= 10;
    ptr2--;
  }
  
  //Handle two samples per loop
  cnt2 = cnt1 >> 1;
  
  //Process the samples
  while(cnt2)
  {
    //Copy samples with an interleave of 10 in the destination
    ptr1[10] = ptr2[1];
    ptr1[20] = ptr2[2];
    
    //Point to next destination and source
    ptr1 += 20;
    ptr2 += 2;
    
    //Two samples done
    cnt2--;
  }

  //One less sample to do
  cnt2 = cnt1 - 1;
  
  //Point to the buffer to work in
  ptr1 = temptracebuffer1;
  
  //Process the samples to be interpolated in between the copied ones
  while(cnt2)
  {
    //The original code uses a different approach
    //Need to check if this is correct
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 = ptr1[0]  << 22;
    sample2 = ptr1[10] << 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - sample2) / 10;
    
    for(cnt2=1;cnt2<10;cnt2++)
    {
      //Calculate the next sample with fixed point calculation
      sample1 += delta;
      
      //Store the decimal part of it
      ptr1[cnt2] = sample1 >> 22;
    }
    
    //Point to next set of samples to do
    ptr1 += 10;
    
    //One set of samples done
    cnt2--;
  }
  
  //One less sample to do
  cnt2 = cnt1 - 1;

  //Point to another buffer for destination and the 5th before sample in the temporary buffer
  ptr1 = temptracebuffer2;
  ptr2 = temptracebuffer1 - 5;
  
  //Check if odd number of samples to process
  if(cnt1 & 1)
  {
    //Copy the odd sample
    ptr1[10] = ptr2[10];
  }
  
  //Half the number to do since two samples per loop
  cnt2 >>= 1;
  
  //Do them all
  while(cnt2)
  {
    //Copy the samples with an offset of 5 samples in the source, which is a calculated sample.
    ptr1[10] = ptr2[10];
    ptr1[20] = ptr2[20];
    
    //Point to next set of samples to do
    ptr1 += 10;
    ptr2 += 10;
    
    //One set of samples done
    cnt2--;
  }
  
  //Up sample a second set based on already up sampled samples
  //Two samples less to do
  cnt2 = cnt1 - 2;
  
  //Point to the buffer to work in
  ptr1 = temptracebuffer2;
  
  //Process the samples to be interpolated in between the copied ones
  while(cnt2)
  {
    //The original code uses a different approach
    //Need to check if this is correct
    //Get the samples shifted up for fractional calculations 10.22 bits
    sample1 = ptr1[0]  << 22;
    sample2 = ptr1[10] << 22;
    
    //Calculate a delta step between the samples
    delta = (sample1 - sample2) / 10;
    
    for(cnt2=1;cnt2<10;cnt2++)
    {
      //Calculate the next sample with fixed point calculation
      sample1 += delta;
      
      //Store the decimal part of it
      ptr1[cnt2] = sample1 >> 22;
    }
    
    //Point to next set of samples to do
    ptr1 += 10;
    
    //One set of samples done
    cnt2--;
  }
  
  //Copy back to original buffer an average of the two temporary samples
  //Do half the input count
  cnt1 = count >> 1;
  
  
  //Needs more processing here, but not sure if it is really needed and if the found errors are actual errors
  
  
  
  
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_pre_process_25ns_data(uint16 * buffer, uint32 offset, uint32 count)
{
  
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_process_25ns_data(uint16 * buffer, uint32 offset, uint32 count)
{
  
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_trace_data(void)
{
  uint32 xpos1;
  uint32 xpos2;
  uint32 dy;
 
  //Reset some flags if display touched for time base change and stopped or in auto or normal mode
  if((touchstate == 2) && ((scopesettings.triggermode != 1) || (scopesettings.runstate != 0)))
  {
    //Clear some flags
    scopesettings.triggerflag1 = 1;
    scopesettings.triggerflag2 = 1;
  }
  
  //Depending on the time base setting use different methods
  //Check if time base on 50mS/div - 10nS/div
  if(scopesettings.timeperdiv > 8)
  {
    
  }
  else
  {
    //Long time base data 50S/div - 100mS/div
    //Check if not running
    if(scopesettings.runstate != 0)
    {
      //Done for now
      return;
    }
    
    //Based on touch state get either the previous xpos or reset it
    if(touchstate == 2)
    {
      disp_xpos = 0;
    }
    
    //Draw directly to screen
    display_set_screen_buffer(maindisplaybuffer);
    
    //Check if back on start of screen
    if(disp_xpos == 0)
    {
      //Reset the screen
      //Clear the trace portion of the screen
      display_set_fg_color(0x00000000);
      display_fill_rect(2, 47, 728, 432);

      //Draw the grid lines and dots based on the grid brightness setting
      scope_draw_grid();

      //Draw the signal center, trigger level and trigger position pointers
      scope_draw_pointers();
    }

    //Check if channel 1 is enabled
    if(scopesettings.channel1.enable)
    {
      //Get the current sample for channel 1 coming up from the bottom of the screen
      disp_ch1_y = 449 - channel1tracebuffer4[0];
      
      //Check if it is within displayable region
      if(disp_ch1_y < 47)
      {
        //Limit on the top of the screen
        disp_ch1_y = 47;
      }
      else if(disp_ch1_y > 448)
      {
        //Limit on the bottom of the screen
        disp_ch1_y = 448;
      }
      
      //Skip drawing if in x-y mode
      if(scopesettings.xymodedisplay == 0)
      {
        //On start of screen need to start with fresh previous
        if(disp_xpos == 0)
        {
          //Make previous the current
          disp_ch1_prev_y = disp_ch1_y;
        }

        //Set x-y mode display trace color
        display_set_fg_color(CHANNEL1_COLOR);

        //Current x positions for drawing the trace lines
        xpos1 = disp_xpos + 3;
        xpos2 = disp_xpos + 4;

        //Check on rise speed of the signal
        if(disp_ch1_y < disp_ch1_prev_y)
        {
          //previous bigger then current so subtract from it to get positive delta
          dy = disp_ch1_prev_y - disp_ch1_y;
        }
        else
        {
          //current bigger then previous so subtract from it to get positive delta
          dy = disp_ch1_y - disp_ch1_prev_y;
        }
        
        //Take action based on the delta
        if(dy < 15)
        {
          //Less then 15 apart slow the trace by stopping on the average of the two points
          disp_ch1_y = (disp_ch1_y + disp_ch1_prev_y) >> 1;
        }
        else if(dy > 20)
        {
          //Else if delta bigger then 20 draw on a single x position 
          xpos2--;
        }

        //Draw the lines. Needs improvement
        display_draw_line(xpos1, disp_ch1_prev_y, xpos2, disp_ch1_y);
        display_draw_line(xpos1, disp_ch1_prev_y + 1, xpos2, disp_ch1_y + 1);

        //Copy the new points to the previous one
        disp_ch1_prev_y = disp_ch1_y;

        //Save in a point array for????
        channel1ypoints[disp_xpos] = disp_ch1_y;
      }
    }

    //Check if channel 2 is enabled
    if(scopesettings.channel2.enable)
    {
      //Get the current sample for channel 1 coming up from the bottom of the screen
      disp_ch2_y = 449 - channel2tracebuffer4[0];
      
      //Check if it is within displayable region
      if(disp_ch2_y < 47)
      {
        //Limit on the top of the screen
        disp_ch2_y = 47;
      }
      else if(disp_ch2_y > 448)
      {
        //Limit on the bottom of the screen
        disp_ch2_y = 448;
      }
      
      //Skip drawing if in x-y mode
      if(scopesettings.xymodedisplay == 0)
      {
        //On start of screen need to start with fresh previous
        if(disp_xpos == 0)
        {
          //Make previous the current
          disp_ch2_prev_y = disp_ch2_y;
        }

        //Set x-y mode display trace color
        display_set_fg_color(CHANNEL2_COLOR);

        //Current x positions for drawing the trace lines
        xpos1 = disp_xpos + 3;
        xpos2 = disp_xpos + 4;

        //Check on rise speed of the signal
        if(disp_ch2_y < disp_ch2_prev_y)
        {
          //previous bigger then current so subtract from it to get positive delta
          dy = disp_ch2_prev_y - disp_ch2_y;
        }
        else
        {
          //current bigger then previous so subtract from it to get positive delta
          dy = disp_ch2_y - disp_ch2_prev_y;
        }
        
        //Take action based on the delta
        if(dy < 15)
        {
          //Less then 15 apart slow the trace by stopping on the average of the two points
          disp_ch2_y = (disp_ch2_y + disp_ch2_prev_y) >> 1;
        }
        else if(dy > 20)
        {
          //Else if delta bigger then 20 draw on a single x position 
          xpos2--;
        }

        //Draw the lines
        display_draw_line(xpos1, disp_ch2_prev_y, xpos2, disp_ch2_y);
        display_draw_line(xpos1, disp_ch2_prev_y + 1, xpos2, disp_ch2_y + 1);

        //Copy the new points to the previous one
        disp_ch2_prev_y = disp_ch2_y;

        //Save in a point array for????
        channel2ypoints[disp_xpos] = disp_ch2_y;
      }
    }

    //Check if in x-y mode
    if(scopesettings.xymodedisplay)
    {
      //On start of screen need to start with fresh previous
      if(disp_xpos == 0)
      {
        //Make previous the current
        disp_ch1_prev_y = disp_ch1_y;
        disp_ch2_prev_y = disp_ch2_y;
      }
    
      //Set x-y mode display trace color
      display_set_fg_color(XYMODE_COLOR);
      
      //Draw some lines two dots wide
      //The offsets do not put it on center screen so needs adjusting
      display_draw_line(disp_ch1_prev_y + 150, disp_ch2_prev_y, disp_ch1_y + 150, disp_ch2_y);
      display_draw_line(disp_ch1_prev_y + 151, disp_ch2_prev_y, disp_ch1_y + 151, disp_ch2_y);

      //Copy the new points to the previous one
      disp_ch1_prev_y = disp_ch1_y;
      disp_ch2_prev_y = disp_ch2_y;
      
      //Save in a point array for????
      channel1ypoints[disp_xpos] = disp_ch1_y;
      channel2ypoints[disp_xpos] = disp_ch2_y;
    }

    //Point to next x position
    disp_xpos++;
    
    //Check if past the end of displayable region
    if(disp_xpos > 719)
    {
      //Reset the x position
      disp_xpos = 0;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
