//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "font_structs.h"
#include "scope_functions.h"
#include "display_lib.h"
#include "fnirsi_1013d_scope.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define CHANNEL1_COLOR         0x00FFFF00
#define CHANNEL2_COLOR         0x0000FFFF
#define TRIGGER_COLOR          0x0000FF00

#define CHANNEL1_TRIG_COLOR    0x00CCCC00
#define CHANNEL2_TRIG_COLOR    0x0000CCCC

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

//----------------------------------------------------------------------------------------------------------------------------------

extern uint8  havetouch;
extern uint16 xtouch;
extern uint16 ytouch;

//----------------------------------------------------------------------------------------------------------------------------------

SCOPESETTINGS scopesettings;

uint16 maindisplaybuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
uint16 displaybuffer1[SCREEN_WIDTH * SCREEN_HEIGHT];
uint16 displaybuffer2[SCREEN_WIDTH * SCREEN_HEIGHT];

//----------------------------------------------------------------------------------------------------------------------------------
//For touch filtering on slider movement

uint16 prevxtouch = 0;

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_display_lib(void)
{
  display_set_bg_color(0x00000000);
  
  display_set_screen_buffer(maindisplaybuffer);
  
  display_set_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);
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
  scope_run_stop_text(scopesettings.runstate);
  
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
    //Inactive so white foreground
    display_set_fg_color(0x00FFFFFF);
  }
  else
  {
    //Active so black foreground
    display_set_fg_color(0x00000000);
  }
  
  //Needs to be an arrow image but text for now
  
  //Display the text
  display_set_font(&font_3);
  display_text(16, 11, "RETURN");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_run_stop_text(int mode)
{
  //Check if run or stop mode
  if(mode == 0)
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
  if(mode == 0)
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
  "500nS/div", "200nS/div", "100nS/div",
   "50nS/div",  "20nS/div",  "10nS/div",
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
  display_slide_right_rect_onto_screen(231, 263, 499, 214, 63039);
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
  display_fill_rounded_rect(xpos, ypos, 45, 20, 2);

  //Draw the edge
  display_set_fg_color(edgecolor);
  display_draw_rounded_rect(xpos, ypos, 45, 20, 2);

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
