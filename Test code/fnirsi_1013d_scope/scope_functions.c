//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "font_structs.h"
#include "scope_functions.h"
#include "display_lib.h"
#include "fnirsi_1013d_scope.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern FONTDATA font_0;
extern FONTDATA font_2;
extern FONTDATA font_3;
extern FONTDATA font_4;
extern FONTDATA font_5;

//----------------------------------------------------------------------------------------------------------------------------------

SCOPESETTINGS scopesettings;

uint16 maindisplaybuffer[SCREEN_WIDTH * SCREEN_HEIGHT];
uint16 displaybuffer1[SCREEN_WIDTH * SCREEN_HEIGHT];
uint16 displaybuffer2[SCREEN_WIDTH * SCREEN_HEIGHT];

//----------------------------------------------------------------------------------------------------------------------------------

void setup_display_lib(void)
{
  display_set_bg_color(0x00000000);
  
  display_set_screen_buffer(maindisplaybuffer);
  
  display_set_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);
}

//----------------------------------------------------------------------------------------------------------------------------------

void setup_main_screen(void)
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
  display_right_control_menu();
  
  //Check if normal or wave view mode
  if(scopesettings.waveviewmode == 0)
  {
    //Normal mode so show menu button
    display_menu_button(0);
  }
  else
  {
    //Wave view mode so show return button
    display_main_return_button(0);
  }
 
  //Show the user if the acquisition is running or stopped
  display_run_stop_text(scopesettings.runstate);
  
  //Display the channel menu select buttons and their settings
  display_channel1_settings(0);
  display_channel2_settings(0);
  
  //Display the current time per div setting
  display_time_div_setting();
  
  //Show the user selected move speed
  display_move_speed(0);
  
  //Display the trigger menu select button and the settings
  display_trigger_settings(0);
  
  //Show the battery charge level and charging indicator
  display_battery_status();
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_right_control_menu(void)
{
  //Setup for clearing right menu bar
  display_set_fg_color(0x00000000);
  
  //Clear the right bar for the control buttons
  display_fill_rect(730, 0, 70, 480);
  
  //Display the control button
  display_control_button(0);
  
  //Check in which state the right menu is in
  if(scopesettings.rightmenustate == 0)
  {
    //Main control state so draw the always used buttons
    display_t_cursor_button(0);
    display_v_cursor_button(0);
    display_measures_button(0);
    display_save_picture_button(0);
    
    //Check if in wave view mode
    if(scopesettings.waveviewmode == 0)
    {
      //Main control mode buttons
      display_run_stop_button(0);
      display_auto_set_button(0);
      display_save_wave_button(0);
    }
    else
    {
      //Wave view mode buttons
      display_page_up_button(0);
      display_page_down_button(0);
      display_delete_wave_button(0);
    }
  }
  else
  {
    //Channel sensitivity state
    display_ch1_sensitivity_control(0,0);
    display_ch2_sensitivity_control(0,0);
    
    //Check if in wave view mode
    if(scopesettings.waveviewmode == 0)
    {
      //Main control mode
      display_50_percent_trigger_button(0);
    }
    else
    {
      //Wave view mode
      display_show_grid_button(0);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
// Right side bar functions
//----------------------------------------------------------------------------------------------------------------------------------

void display_control_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_run_stop_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_auto_set_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_page_up_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_page_down_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_t_cursor_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_v_cursor_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_measures_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_save_picture_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_save_wave_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_delete_wave_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_50_percent_trigger_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_show_grid_button(int mode)
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
    display_set_fg_color(0x00EF9311);
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

void display_ch1_sensitivity_control(int type,int mode)
{
  //Check if V+ is active or inactive
  if((type == 0) && (mode != 0))
  {
    //Orange color for activated button
    display_set_fg_color(0x00EF9311);
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
    display_set_fg_color(0x00EF9311);
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

void display_ch2_sensitivity_control(int type,int mode)
{
  //Check if V+ is active or inactive
  if((type == 0) && (mode != 0))
  {
    //Orange color for activated button
    display_set_fg_color(0x00EF9311);
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
    display_set_fg_color(0x00EF9311);
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

void display_menu_button(int mode)
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

void display_main_return_button(int mode)
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

void display_run_stop_text(int mode)
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

void display_channel1_settings(int mode)
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
      //Inactive, yellow menu button
      display_set_fg_color(0x00FFFF00);
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

void display_channel2_settings(int mode)
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
      display_set_fg_color(0x0000FFFF);
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

void display_time_div_setting(void)
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

void display_move_speed(int mode)
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

void display_trigger_settings(int mode)
{
  int8 *modetext = 0;
  
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(570, 5, 130, 35);
  
  //Check if inactive or active
  if(mode == 0)
  {
    //Inactive, green menu button
    display_set_fg_color(0x0000FF00);
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
  display_draw_horz_line(27, 642, 645);
  display_draw_vert_line(642, 27, 38);
  display_draw_horz_line(38, 639, 642);
  
  //Draw the arrow based on the selected edge
  if(scopesettings.triggeredge == 0)
  {
    //rising edge
    display_draw_horz_line(32, 641, 643);
    display_draw_horz_line(33, 640, 644);
  }
  else
  {
    //falling edge
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
        //Inactive, dark yellow box
        display_set_fg_color(0x00CCCC00);
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
        display_set_fg_color(0x0000CCCC);
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

void display_battery_status(void)
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

void display_open_channel1_menu(void)
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
  display_channel1_enable_select();
  display_channel1_fft_show();
  display_channel1_coupling_select();
  display_channel1_probe_magnification_select();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer(maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(161, 46, 184, 253, 4369);
}

//----------------------------------------------------------------------------------------------------------------------------------

void display_channel1_enable_select(void)
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
  
  //Set yellow color for the box behind the selected text
  display_set_fg_color(0x00FFFF00);
  
  //Check if channel is disabled or enabled
  if(scopesettings.channel1.enable == 0)
  {
    //Disabled so yellow box behind off
    display_fill_rect(291, 62, 32, 22);
  }
  else
  {
    //Enabled so yellow box behind on
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

void display_channel1_fft_show(void)
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
  
  //Set yellow color for the box behind the selected text
  display_set_fg_color(0x00FFFF00);
  
  //Check if fft is disabled or enabled
  if(scopesettings.channel1.fftenable == 0)
  {
    //Disabled so yellow box behind off
    display_fill_rect(291, 124, 32, 22);
  }
  else
  {
    //Enabled so yellow box behind on
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

void display_channel1_coupling_select(void)
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

  //Set yellow color for the box behind the selected text
  display_set_fg_color(0x00FFFF00);
  
  //Check if coupling is dc or ac
  if(scopesettings.channel1.coupling == 0)
  {
    //DC so yellow box behind dc text
    display_fill_rect(239, 188, 32, 22);
  }
  else
  {
    //AC so yellow box behind ac text
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

void display_channel1_probe_magnification_select(void)
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
  
  //Set yellow color for the box behind the selected text
  display_set_fg_color(0x00FFFF00);
  
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

