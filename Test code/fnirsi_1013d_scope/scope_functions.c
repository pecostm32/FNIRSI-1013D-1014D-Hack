//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "scope_functions.h"
#include "statemachine.h"
#include "touchpanel.h"
#include "timer.h"
#include "fpga_control.h"
#include "spi_control.h"
#include "display_lib.h"
#include "ff.h"

#include "usb_interface.h"
#include "variables.h"

#include "sin_cos_math.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_display_lib(void)
{
  display_set_bg_color(0x00000000);
  
  display_set_screen_buffer((uint16 *)maindisplaybuffer);
  
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
  scope_acqusition_settings(0);
  
  //Show the user selected move speed
  scope_move_speed(0);
  
  //Display the trigger menu select button and the settings
  scope_trigger_settings(0);
  
  //Show the battery charge level and charging indicator
  scope_battery_status();
  
  //Clear some flags to make the trace part of the screen refresh
  scopesettings.triggerflag1 = 1;
  scopesettings.triggerflag2 = 1;
  
  disp_xpos = 0;  
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_view_screen(void)
{
  //Switch to view mode so disallow saving of settings on power down
  viewactive = VIEW_ACTIVE;
  
  //Set scope run state to running to have it sample fresh data on exit
  scopesettings.runstate = 0;

  //This is different to the original since the thumbnail displaying does not use the settings data anymore
  //Only when picture and waveform display is used the settings are overwritten, since it makes use of the actual waveform functions and main touch handler
  //Created two separate function sets. One for saving and restoring the settings as is, and one for saving to and loading from a file buffer
  
  //Save the current settings
  scope_save_setup(&savedscopesettings1);
  
  //Initialize the view mode variables
  //Used for indicating if select all or select button is active
  viewselectmode = 0;
  
  //Start at first page. In the original code they start with 1 and subtract from the multiplied with 16 to get the correct file number index
  viewpage = 0;
  
  //Clear the item selected flags
  memset(viewitemselected, VIEW_ITEM_NOT_SELECTED, VIEW_ITEMS_PER_PAGE);
  
  //Set storage buffer for screen capture under selected signs and messages
  display_set_destination_buffer(displaybuffer2);
  display_set_source_buffer(displaybuffer2);
  
  //Display the file actions menu on the right side of the screen
  scope_setup_right_file_menu();
  
  //Load the list files for the current view type
  scope_load_list_files();
  
  //Display the available thumbnails for the current view type
  scope_count_and_display_thumbnails();
  
  //Handle touch for this part of the user interface
  handle_view_mode_touch();
  
  //Restore the current settings
  scope_restore_setup(&savedscopesettings1);

  //Make sure view mode is normal
  scopesettings.waveviewmode = 0;

  //And resume with auto trigger mode
  scopesettings.triggermode = 0;

  //Need to restore the original scope data and fpga settings

  //Is also part of startup, so could be done with a function
  //Set the volts per div for each channel based on the loaded scope settings
  fpga_set_channel_1_voltperdiv();
  fpga_set_channel_2_voltperdiv();

  //These are not done in the original code
  //Set the channels AC or DC coupling based on the loaded scope settings
  fpga_set_channel_1_coupling();
  fpga_set_channel_2_coupling();

  //Setup the trigger system in the FPGA based on the loaded scope settings
  fpga_set_trigger_timebase(scopesettings.timeperdiv);
  fpga_set_trigger_channel();
  fpga_set_trigger_edge();
  fpga_set_trigger_level();
  fpga_set_trigger_mode();

  //Set channel screen offsets
  fpga_set_channel_1_offset();
  fpga_set_channel_2_offset();



  //Reset the screen to the normal scope screen
  scope_setup_main_screen();

  //Restart the scope at this point in the code
  
          
//        FUN_8000a750();          //Restart the scope function
//        setup_main_screen();          

  //Back to normal mode so allow saving of settings on power down
  viewactive = VIEW_NOT_ACTIVE;
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_usb_screen(void)
{
  //Clear the whole screen
  display_set_fg_color(0x00000000);
  display_fill_rect(0, 0, 800, 480);
  
  //Set the light color for the equipment borders
  display_set_fg_color(0x00AAAAAA);
  
  //Draw the computer screen
  display_fill_rounded_rect(470, 115, 250, 190, 2);
  display_fill_rect(580, 305, 30, 20);
  display_fill_rounded_rect(550, 325, 90, 10, 2);
  display_fill_rect(550, 331, 89, 4);

  //Draw the scope
  display_fill_rounded_rect(80, 200, 180, 135, 2);

  //Draw the cable
  display_fill_rect(210, 188, 10, 12);
  display_fill_rect(213, 154, 4, 36);
  display_fill_rect(213, 150, 152, 4);
  display_fill_rect(361, 154, 4, 106);
  display_fill_rect(361, 260, 98, 4);
  display_fill_rect(458, 257, 12, 10);
  
  //Fill in the screens with a blue color
  display_set_fg_color(0x00000055);
  display_fill_rect(477, 125, 235, 163);
  display_fill_rect(88, 210, 163, 112);
  
  //Draw a dark border around the blue screens
  display_set_fg_color(0x00111111);
  display_draw_rect(477, 125, 235, 163);
  display_draw_rect(88, 210, 163, 112);
  
  //Display the text with font 5 and the light color
  display_set_font(&font_5);
  display_set_fg_color(0x00AAAAAA);
  display_text(125, 254, "ON / OFF");

  //Start the USB interface
  usb_device_enable();
  
  //Wait for the user to touch the scope ON / OFF section to quit
  while(1)
  {
    //Scan the touch panel for touch
    tp_i2c_read_status();
    
    //Check if there is touch
    if(havetouch)
    {
      //Check if touch within the text field
      if((xtouch >= 90) && (xtouch <= 250) && (ytouch >= 210) && (ytouch <= 320))
      {
        //Touched the text field so wait until touch is released and then quit
        tp_i2c_wait_for_touch_release();
        
        break;
      }
    }
  }
  
  //Stop the USB interface  
  usb_device_disable();
  
  //Re-sync the system files
  scope_sync_list_files();
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

void scope_setup_right_file_menu(void)
{
  int32 y;
  
  //Set black color for background
  display_set_fg_color(0x00000000);

  //Clear the right menu bar
  display_fill_rect(730, 0, 70, 480);

  //Grey color for separators
  display_set_fg_color(0x007F7F7F);
  
  //Draw the button separators
  for(y=80;y<480;y+=80)
  {
    //A 48 pixel long line
    display_draw_horz_line(y, 741, 789);
  }

  //White color for text
  display_set_fg_color(0x00FFFFFF);
  
  //Display the texts with this font
  display_set_font(&font_3);
  
  //Some buttons have two lines of text
  display_text(747, 34, "return");
  
  display_text(746, 104, "select");
  display_text(758, 119, "all");
  
  display_text(746, 191, "select");
  
  display_text(746, 271, "delete");

  display_text(750, 343, "page");
  display_text(758, 358, "up");

  display_text(750, 422, "page");
  display_text(748, 440, "down");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_bottom_file_menu(int mode)
{
  //Check if background needs to be saved
  if(mode == VIEW_BOTTON_MENU_INIT)
  {
    //Save the screen rectangle where the menu will be displayed
    display_copy_rect_from_screen(0, 420, 800, 60);
  }
  
  //Check if it needs to be drawn
  if(mode & VIEW_BOTTON_MENU_SHOW)
  {
    //Draw the background in grey
    display_set_fg_color(0x00202020);
    display_fill_rect(0, 420, 800, 60);
   
    //Draw the three separator lines in black
    display_set_fg_color(0x00000000);
    display_draw_vert_line(200, 423, 477);
    display_draw_vert_line(400, 423, 477);
    display_draw_vert_line(600, 423, 477);

    //Draw the icons in white    
    display_set_fg_color(0x00FFFFFF);
    display_copy_icon_fg_color(return_arrow_icon,      79, 436, 41, 27);
    display_copy_icon_fg_color(waste_bin_icon,        284, 433, 31, 33);
    display_copy_icon_fg_color(previous_picture_icon, 483, 438, 33, 24);
    display_copy_icon_fg_color(next_picture_icon,     683, 438, 33, 24);
    
    //Signal menu is visible
    viewbottommenustate = VIEW_BOTTON_MENU_SHOW;
  }
  else
  {
    //Hide the menu bar
    display_copy_rect_to_screen(0, 420, 800, 60);
    
    //Signal menu is not visible
    viewbottommenustate = VIEW_BOTTON_MENU_HIDE;
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

void scope_select_all_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //White for activated button
    display_set_fg_color(0x00FFFFFF);
  }

  //Draw the body of the button
  display_fill_rect(737, 100, 55, 40);
  
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
  display_text(746, 104, "select");
  display_text(758, 119, "all");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_select_button(int mode)
{
  //Check if inactive or active mode
  if(mode == 0)
  {
    //Black color for inactive button
    display_set_fg_color(0x00000000);
  }
  else
  {
    //White for activated button
    display_set_fg_color(0x00FFFFFF);
  }

  //Draw the body of the button
  display_fill_rect(737, 180, 55, 40);
  
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
  display_text(746, 191, "select");
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
  display_copy_icon_use_colors(return_arrow_icon, 20, 5, 41, 27);
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
  display_fill_rect(RUN_STOP_TEXT_XPOS, RUN_STOP_TEXT_YPOS, RUN_STOP_TEXT_WIDTH, RUN_STOP_TEXT_HEIGHT);

  //Select the font for the text
  display_set_font(&font_3);
  
  //Check if run or stop mode
  if(scopesettings.runstate == 0)
  {
    //Run mode. White text
    display_set_fg_color(0x00FFFFFF);
    display_text(RUN_STOP_TEXT_XPOS + 4, RUN_STOP_TEXT_YPOS + 1, "RUN");
  }
  else
  {
    //Stop mode. Black text
    display_set_fg_color(0x00000000);
    display_text(RUN_STOP_TEXT_XPOS + 1, RUN_STOP_TEXT_YPOS + 1, "STOP");
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel1_settings(int mode)
{
  int8 **vdtext;
  
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(CH1_BUTTON_XPOS, CH1_BUTTON_YPOS, CH1_BUTTON_BG_WIDTH, CH1_BUTTON_BG_HEIGHT);
  
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
  display_fill_rect(CH1_BUTTON_XPOS, CH1_BUTTON_YPOS, CH1_BUTTON_WIDTH, CH1_BUTTON_HEIGHT);

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
    display_fill_rect(CH1_BUTTON_XPOS + 30, CH1_BUTTON_YPOS, CH1_BUTTON_BG_WIDTH - 30, CH1_BUTTON_BG_HEIGHT);
  }
  
  //Display the channel identifier text
  display_text(CH1_BUTTON_XPOS + 5, CH1_BUTTON_YPOS + 11, "CH1");

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
    display_text(CH1_BUTTON_XPOS + 38, CH1_BUTTON_YPOS + 3, "DC");
  }
  else
  {
    //AC coupling
    display_text(CH1_BUTTON_XPOS + 38, CH1_BUTTON_YPOS + 3, "AC");
  }
  
  //Print the probe magnification factor
  switch(scopesettings.channel1.magnification)
  {
    case 0:
      //Times 1 magnification
      display_text(CH1_BUTTON_XPOS + 63, CH1_BUTTON_YPOS + 3, "1X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[0];
      break;
      
    case 1:
      //Times 10 magnification
      display_text(CH1_BUTTON_XPOS + 61, CH1_BUTTON_YPOS + 3, "10X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[1];
      break;
      
    default:
      //Times 100 magnification
      display_text(CH1_BUTTON_XPOS + 59, CH1_BUTTON_YPOS + 3, "100X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[2];
      break;
  }
  
  //Display the sensitivity when in range
  if(scopesettings.channel1.voltperdiv < 7)
  {
    display_text(CH1_BUTTON_XPOS + 38, CH1_BUTTON_YPOS + 19, vdtext[scopesettings.channel1.voltperdiv]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_channel2_settings(int mode)
{
  int8 **vdtext;
  
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(CH2_BUTTON_XPOS, CH2_BUTTON_YPOS, CH2_BUTTON_BG_WIDTH, CH2_BUTTON_BG_HEIGHT);
  
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
  display_fill_rect(CH2_BUTTON_XPOS, CH2_BUTTON_YPOS, CH2_BUTTON_WIDTH, CH2_BUTTON_HEIGHT);

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
    display_fill_rect(CH2_BUTTON_XPOS + 30, CH2_BUTTON_YPOS, CH2_BUTTON_BG_WIDTH - 30, CH2_BUTTON_BG_HEIGHT);
  }
  
  //Display the channel identifier text
  display_text(CH2_BUTTON_XPOS + 5, CH2_BUTTON_YPOS + 11, "CH2");

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
    display_text(CH2_BUTTON_XPOS + 38, CH2_BUTTON_YPOS + 3, "DC");
  }
  else
  {
    //AC coupling
    display_text(CH2_BUTTON_XPOS + 38, CH2_BUTTON_YPOS + 3, "AC");
  }
  
  //Print the probe magnification factor
  switch(scopesettings.channel2.magnification)
  {
    case 0:
      //Times 1 magnification
      display_text(CH2_BUTTON_XPOS + 63, CH2_BUTTON_YPOS + 3, "1X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[0];
      break;
      
    case 1:
      //Times 10 magnification
      display_text(CH2_BUTTON_XPOS + 61, CH2_BUTTON_YPOS + 3, "10X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[1];
      break;
      
    default:
      //Times 10 magnification
      display_text(CH2_BUTTON_XPOS + 59, CH2_BUTTON_YPOS + 3, "100X");
      
      //Set the volts per div text range to be used for this magnification
      vdtext = (int8 **)volt_div_texts[2];
      break;
  }
  
  //Display the sensitivity when in range
  if(scopesettings.channel2.voltperdiv < 7)
  {
    display_text(CH2_BUTTON_XPOS + 38, CH2_BUTTON_YPOS + 19, vdtext[scopesettings.channel2.voltperdiv]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_acqusition_settings(int mode)
{
  //Clear the area first
  display_set_fg_color(0x00000000);
  display_fill_rect(ACQ_BUTTON_XPOS, ACQ_BUTTON_YPOS, ACQ_BUTTON_BG_WIDTH, ACQ_BUTTON_BG_HEIGHT);
  
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
  display_fill_rect(ACQ_BUTTON_XPOS, ACQ_BUTTON_YPOS, ACQ_BUTTON_WIDTH, ACQ_BUTTON_HEIGHT);
  
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
    display_fill_rect(ACQ_BUTTON_XPOS + 30, ACQ_BUTTON_YPOS, ACQ_BUTTON_BG_WIDTH - 30, ACQ_BUTTON_BG_HEIGHT);
  }
  
  //Display the acquisition identifier text
  display_text(ACQ_BUTTON_XPOS + 4, ACQ_BUTTON_YPOS + 11, "ACQ");
  
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
  
  //Only display the text when in range of the text array
  if(scopesettings.acqusitionspeed < (sizeof(acquisition_speed_texts) / sizeof(int8 *)))
  {
    //Display the text from the table
    display_text(ACQ_BUTTON_XPOS + 38, ACQ_BUTTON_YPOS + 3, (int8 *)acquisition_speed_texts[scopesettings.acqusitionspeed]);
  }
  
  //Only display the text when in range of the text array
  if(scopesettings.timeperdiv < (sizeof(time_div_texts) / sizeof(int8 *)))
  {
    //Display the text from the table
    display_text(ACQ_BUTTON_XPOS + 38, ACQ_BUTTON_YPOS + 19, (int8 *)time_div_texts[scopesettings.timeperdiv]);
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
  //Prepare the battery symbol in a working buffer to avoid flicker
  display_set_screen_buffer(displaybuffer1);
  
  //Clear the background
  display_set_fg_color(0x00000000);
  display_fill_rect(701, 5, 25, 13);
  
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
  
  //Copy it to the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer((uint16 *)maindisplaybuffer);
  display_copy_rect_to_screen(701, 5, 25, 13);
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
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

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
  display_fill_rect(CH1_MENU_XPOS, CH1_MENU_YPOS, CH1_MENU_WIDTH, CH1_MENU_HEIGHT);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(CH1_MENU_XPOS, CH1_MENU_YPOS, CH1_MENU_WIDTH, CH1_MENU_HEIGHT);
  
  //Three black lines between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(CH1_MENU_YPOS +  62, CH1_MENU_XPOS + 14, CH1_MENU_XPOS + CH1_MENU_WIDTH - 14);
  display_draw_horz_line(CH1_MENU_YPOS + 124, CH1_MENU_XPOS + 14, CH1_MENU_XPOS + CH1_MENU_WIDTH - 14);
  display_draw_horz_line(CH1_MENU_YPOS + 188, CH1_MENU_XPOS + 14, CH1_MENU_XPOS + CH1_MENU_WIDTH - 14);
  
  //Main texts in white  
  display_set_fg_color(0x00FFFFFF);
  
  //Select the font for the texts
  display_set_font(&font_3);
  
  //Display the texts
  display_text(CH1_MENU_XPOS + 15, CH1_MENU_YPOS +  10, "open");
  display_text(CH1_MENU_XPOS + 22, CH1_MENU_YPOS +  29, "CH");
  display_text(CH1_MENU_XPOS + 15, CH1_MENU_YPOS +  72, "open");
  display_text(CH1_MENU_XPOS + 19, CH1_MENU_YPOS +  91, "FFT");
  display_text(CH1_MENU_XPOS + 15, CH1_MENU_YPOS + 136, "coup");
  display_text(CH1_MENU_XPOS + 18, CH1_MENU_YPOS + 154, "ling");
  display_text(CH1_MENU_XPOS + 15, CH1_MENU_YPOS + 201, "probe");
  display_text(CH1_MENU_XPOS + 15, CH1_MENU_YPOS + 219, "mode");

  //Display the actual settings
  scope_channel1_enable_select();
  scope_channel1_fft_show();
  scope_channel1_coupling_select();
  scope_channel1_probe_magnification_select();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(CH1_MENU_XPOS, CH1_MENU_YPOS, CH1_MENU_WIDTH, CH1_MENU_HEIGHT, 69906);
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
    display_fill_rect(CH1_MENU_XPOS + 78, CH1_MENU_YPOS + 16, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(CH1_MENU_XPOS + 130, CH1_MENU_YPOS + 16, 32, 22);
  }
  
  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if channel is disabled or enabled
  if(scopesettings.channel1.enable == 0)
  {
    //Disabled so channel 1 color box behind off
    display_fill_rect(CH1_MENU_XPOS + 130, CH1_MENU_YPOS + 16, 32, 22);
  }
  else
  {
    //Enabled so channel 1 color box behind on
    display_fill_rect(CH1_MENU_XPOS + 78, CH1_MENU_YPOS + 16, 32, 22);
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
  display_text(CH1_MENU_XPOS + 84, CH1_MENU_YPOS + 19, "ON");

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
  display_text(CH1_MENU_XPOS + 133, CH1_MENU_YPOS + 19, "OFF");
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
    display_fill_rect(CH1_MENU_XPOS + 78, CH1_MENU_YPOS + 78, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(CH1_MENU_XPOS + 130, CH1_MENU_YPOS + 78, 32, 22);
  }
  
  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if fft is disabled or enabled
  if(scopesettings.channel1.fftenable == 0)
  {
    //Disabled so channel 1 color box behind off
    display_fill_rect(CH1_MENU_XPOS + 130, CH1_MENU_YPOS + 78, 32, 22);
  }
  else
  {
    //Enabled so channel 1 color box behind on
    display_fill_rect(CH1_MENU_XPOS + 78, CH1_MENU_YPOS + 78, 32, 22);
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
  display_text(CH1_MENU_XPOS + 84, CH1_MENU_YPOS + 81, "ON");

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
  display_text(CH1_MENU_XPOS + 133, CH1_MENU_YPOS + 81, "OFF");
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
    display_fill_rect(CH1_MENU_XPOS + 130, CH1_MENU_YPOS + 142, 32, 22);
  }
  else
  {
    //AC so dark grey box behind dc text
    display_fill_rect(CH1_MENU_XPOS + 78, CH1_MENU_YPOS + 142, 32, 22);
  }

  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if coupling is dc or ac
  if(scopesettings.channel1.coupling == 0)
  {
    //DC so channel 1 color box behind dc text
    display_fill_rect(CH1_MENU_XPOS + 78, CH1_MENU_YPOS + 142, 32, 22);
  }
  else
  {
    //AC so channel 1 color box behind ac text
    display_fill_rect(CH1_MENU_XPOS + 130, CH1_MENU_YPOS + 142, 32, 22);
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
  display_text(CH1_MENU_XPOS + 84, CH1_MENU_YPOS + 145, "DC");

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
  display_text(CH1_MENU_XPOS + 135, CH1_MENU_YPOS + 145, "AC");
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
      display_fill_rect(CH1_MENU_XPOS + 109, CH1_MENU_YPOS + 199, 23, 38);
      display_fill_rect(CH1_MENU_XPOS + 138, CH1_MENU_YPOS + 199, 30, 38);
      break;
      
    case 1:
      //dark grey times 1 and 100 magnification
      display_fill_rect(CH1_MENU_XPOS +  78, CH1_MENU_YPOS + 199, 20, 38);
      display_fill_rect(CH1_MENU_XPOS + 138, CH1_MENU_YPOS + 199, 30, 38);
      break;
      
    default:
      //dark grey times 1 and 10 magnification
      display_fill_rect(CH1_MENU_XPOS +  78, CH1_MENU_YPOS + 199, 20, 38);
      display_fill_rect(CH1_MENU_XPOS + 109, CH1_MENU_YPOS + 199, 23, 38);
      break;
  }
  
  //Set channel 1 color for the box behind the selected text
  display_set_fg_color(CHANNEL1_COLOR);
  
  //Check if which magnification to highlight
  switch(scopesettings.channel1.magnification)
  {
    case 0:
      //Highlight times 1 magnification
      display_fill_rect(CH1_MENU_XPOS + 78, CH1_MENU_YPOS + 199, 20, 38);
      break;
      
    case 1:
      //Highlight times 10 magnification
      display_fill_rect(CH1_MENU_XPOS + 109, CH1_MENU_YPOS + 199, 23, 38);
      break;
      
    default:
      //Highlight times 100 magnification
      display_fill_rect(CH1_MENU_XPOS + 138, CH1_MENU_YPOS + 199, 30, 38);
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
  display_text(CH1_MENU_XPOS + 84, CH1_MENU_YPOS + 201, "1");
  display_text(CH1_MENU_XPOS + 83, CH1_MENU_YPOS + 219, "X");

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
  display_text(CH1_MENU_XPOS + 113, CH1_MENU_YPOS + 201, "10");
  display_text(CH1_MENU_XPOS + 115, CH1_MENU_YPOS + 219, "X");

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
  display_text(CH1_MENU_XPOS + 142, CH1_MENU_YPOS + 201, "100");
  display_text(CH1_MENU_XPOS + 149, CH1_MENU_YPOS + 219, "X");
}

//----------------------------------------------------------------------------------------------------------------------------------
void scope_open_channel2_menu(void)
{
 //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(CH2_MENU_XPOS, CH2_MENU_YPOS, CH2_MENU_WIDTH, CH2_MENU_HEIGHT);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(CH2_MENU_XPOS, CH2_MENU_YPOS, CH2_MENU_WIDTH, CH2_MENU_HEIGHT);
  
  //Three black lines between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(CH2_MENU_YPOS +  62, CH2_MENU_XPOS + 14, CH2_MENU_XPOS + CH2_MENU_WIDTH - 14);
  display_draw_horz_line(CH2_MENU_YPOS + 124, CH2_MENU_XPOS + 14, CH2_MENU_XPOS + CH2_MENU_WIDTH - 14);
  display_draw_horz_line(CH2_MENU_YPOS + 188, CH2_MENU_XPOS + 14, CH2_MENU_XPOS + CH2_MENU_WIDTH - 14);
  
  //Main texts in white  
  display_set_fg_color(0x00FFFFFF);
  
  //Select the font for the texts
  display_set_font(&font_3);
  
  //Display the texts
  display_text(CH2_MENU_XPOS + 15, CH2_MENU_YPOS +  10, "open");
  display_text(CH2_MENU_XPOS + 22, CH2_MENU_YPOS +  29, "CH");
  display_text(CH2_MENU_XPOS + 15, CH2_MENU_YPOS +  72, "open");
  display_text(CH2_MENU_XPOS + 19, CH2_MENU_YPOS +  91, "FFT");
  display_text(CH2_MENU_XPOS + 15, CH2_MENU_YPOS + 136, "coup");
  display_text(CH2_MENU_XPOS + 18, CH2_MENU_YPOS + 154, "ling");
  display_text(CH2_MENU_XPOS + 15, CH2_MENU_YPOS + 201, "probe");
  display_text(CH2_MENU_XPOS + 15, CH2_MENU_YPOS + 219, "mode");

  //Display the actual settings
  scope_channel2_enable_select();
  scope_channel2_fft_show();
  scope_channel2_coupling_select();
  scope_channel2_probe_magnification_select();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(CH2_MENU_XPOS, CH2_MENU_YPOS, CH2_MENU_WIDTH, CH2_MENU_HEIGHT, 69906);
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
    display_fill_rect(CH2_MENU_XPOS + 78, CH2_MENU_YPOS + 16, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(CH2_MENU_XPOS + 130, CH2_MENU_YPOS + 16, 32, 22);
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if channel is disabled or enabled
  if(scopesettings.channel2.enable == 0)
  {
    //Disabled so channel 2 color box behind off
    display_fill_rect(CH2_MENU_XPOS + 130, CH2_MENU_YPOS + 16, 32, 22);
  }
  else
  {
    //Enabled so channel 2 color box behind on
    display_fill_rect(CH2_MENU_XPOS + 78, CH2_MENU_YPOS + 16, 32, 22);
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
  display_text(CH2_MENU_XPOS + 84, CH2_MENU_YPOS + 19, "ON");

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
  display_text(CH2_MENU_XPOS + 133, CH2_MENU_YPOS + 19, "OFF");
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
    display_fill_rect(CH2_MENU_XPOS + 78, CH2_MENU_YPOS + 78, 32, 22);
  }
  else
  {
    //Enabled so dark grey box behind off
    display_fill_rect(CH2_MENU_XPOS + 130, CH2_MENU_YPOS + 78, 32, 22);
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if fft is disabled or enabled
  if(scopesettings.channel2.fftenable == 0)
  {
    //Disabled so channel 2 color box behind off
    display_fill_rect(CH2_MENU_XPOS + 130, CH2_MENU_YPOS + 78, 32, 22);
  }
  else
  {
    //Enabled so channel 2 color box behind on
    display_fill_rect(CH2_MENU_XPOS + 78, CH2_MENU_YPOS + 78, 32, 22);
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
  display_text(CH2_MENU_XPOS + 84, CH2_MENU_YPOS + 81, "ON");

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
  display_text(CH2_MENU_XPOS + 133, CH2_MENU_YPOS + 81, "OFF");
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
    display_fill_rect(CH2_MENU_XPOS + 130, CH2_MENU_YPOS + 142, 32, 22);
  }
  else
  {
    //AC so dark grey box behind dc text
    display_fill_rect(CH2_MENU_XPOS + 78, CH2_MENU_YPOS + 142, 32, 22);
  }

  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if coupling is dc or ac
  if(scopesettings.channel2.coupling == 0)
  {
    //DC so channel 2 color box behind dc text
    display_fill_rect(CH2_MENU_XPOS + 78, CH2_MENU_YPOS + 142, 32, 22);
  }
  else
  {
    //AC so channel 2 color box behind ac text
    display_fill_rect(CH2_MENU_XPOS + 130, CH2_MENU_YPOS + 142, 32, 22);
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
  display_text(CH2_MENU_XPOS + 84, CH2_MENU_YPOS + 145, "DC");

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
  display_text(CH2_MENU_XPOS + 135, CH2_MENU_YPOS + 145, "AC");
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
      display_fill_rect(CH2_MENU_XPOS + 109, CH2_MENU_YPOS + 199, 23, 38);
      display_fill_rect(CH2_MENU_XPOS + 138, CH2_MENU_YPOS + 199, 30, 38);
      break;
      
    case 1:
      //dark grey times 1 and 100 magnification
      display_fill_rect(CH2_MENU_XPOS +  78, CH2_MENU_YPOS + 199, 20, 38);
      display_fill_rect(CH2_MENU_XPOS + 138, CH2_MENU_YPOS + 199, 30, 38);
      break;
      
    default:
      //dark grey times 1 and 10 magnification
      display_fill_rect(CH2_MENU_XPOS +  78, CH2_MENU_YPOS + 199, 20, 38);
      display_fill_rect(CH2_MENU_XPOS + 109, CH2_MENU_YPOS + 199, 23, 38);
      break;
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(CHANNEL2_COLOR);
  
  //Check if which magnification to highlight
  switch(scopesettings.channel2.magnification)
  {
    case 0:
      //Highlight times 1 magnification
      display_fill_rect(CH2_MENU_XPOS + 78, CH2_MENU_YPOS + 199, 20, 38);
      break;
      
    case 1:
      //Highlight times 10 magnification
      display_fill_rect(CH2_MENU_XPOS + 109, CH2_MENU_YPOS + 199, 23, 38);
      break;
      
    default:
      //Highlight times 100 magnification
      display_fill_rect(CH2_MENU_XPOS + 138, CH2_MENU_YPOS + 199, 30, 38);
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
  display_text(CH2_MENU_XPOS + 84, CH2_MENU_YPOS + 201, "1");
  display_text(CH2_MENU_XPOS + 83, CH2_MENU_YPOS + 219, "X");

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
  display_text(CH2_MENU_XPOS + 113, CH2_MENU_YPOS + 201, "10");
  display_text(CH2_MENU_XPOS + 115, CH2_MENU_YPOS + 219, "X");

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
  display_text(CH2_MENU_XPOS + 142, CH2_MENU_YPOS + 201, "100");
  display_text(CH2_MENU_XPOS + 149, CH2_MENU_YPOS + 219, "X");
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_acquisition_menu(void)
{
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(ACQ_MENU_XPOS, ACQ_MENU_YPOS, ACQ_MENU_WIDTH, ACQ_MENU_HEIGHT);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(ACQ_MENU_XPOS, ACQ_MENU_YPOS, ACQ_MENU_WIDTH, ACQ_MENU_HEIGHT);

  //A black line between the settings
  display_set_fg_color(0x00000000);
  display_draw_horz_line(ACQ_MENU_YPOS +  135, ACQ_MENU_XPOS + 8, ACQ_MENU_XPOS + ACQ_MENU_WIDTH - 8);
  
  //Main texts in white  
  display_set_fg_color(0x00FFFFFF);

  //Select the font for the texts
  display_set_font(&font_3);
  
  //Display the texts
  display_text(ACQ_MENU_XPOS + 111, ACQ_MENU_YPOS +   8, "Sample Rate");
  display_text(ACQ_MENU_XPOS +  97, ACQ_MENU_YPOS + 143, "Time per Division");

  //Display the actual settings
  scope_acquisition_speed_select();
  scope_acquisition_timeperdiv_select();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_top_rect_onto_screen(ACQ_MENU_XPOS, ACQ_MENU_YPOS, ACQ_MENU_WIDTH, ACQ_MENU_HEIGHT, 69906);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_acquisition_speed_select(void)
{
  uint32 i,x,y;
  
  //Select the font for the texts
  display_set_font(&font_2);

  //Set dark grey color for the boxes behind the not selected texts
  display_set_fg_color(0x00383838);
  
  //Clear the boxes for the not selected items
  for(i=0;i<(sizeof(acquisition_speed_texts) / sizeof(int8 *));i++)
  {
    if(i != scopesettings.acqusitionspeed)
    {
      x = ((i & 3) * 72) + 10;
      y = ((i >> 2) * 23) + 33;
      
      display_fill_rect(ACQ_MENU_XPOS + x, ACQ_MENU_YPOS + y, 68, 20);
    }
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(TRIGGER_COLOR);

  //Get the position of the selected item
  x = ((scopesettings.acqusitionspeed & 3) * 72) + 10;
  y = ((scopesettings.acqusitionspeed >> 2) * 23) + 33;
  
  //Highlight the selected item
  display_fill_rect(ACQ_MENU_XPOS + x, ACQ_MENU_YPOS + y, 68, 20);

  
  for(i=0;i<(sizeof(acquisition_speed_texts) / sizeof(int8 *));i++)
  {
    if(i != scopesettings.acqusitionspeed)
    {
      //Available not selected texts in white  
      display_set_fg_color(0x00FFFFFF);
    }
    else
    {
      //Selected texts in black
      display_set_fg_color(0x00000000);
    }
    
    //Calculate the position of this text
    x = ((i & 3) * 72) + acquisition_speed_text_x_offsets[i];
    y = ((i >> 2) * 23) + 36;

    //Display the text from the table
    display_text(ACQ_MENU_XPOS + x, ACQ_MENU_YPOS + y, (int8 *)acquisition_speed_texts[i]);
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_acquisition_timeperdiv_select(void)
{
  uint32 c,i,x,y;
  
  //Select the font for the texts
  display_set_font(&font_2);

  //Set dark grey color for the boxes behind the not selected texts
  display_set_fg_color(0x00383838);
  
  //Clear the boxes for the not selected items
  for(i=0;i<(sizeof(time_div_texts) / sizeof(int8 *));i++)
  {
    //Settings displayed from smallest to highest value
    c = ((sizeof(time_div_texts) / sizeof(int8 *)) - 1) - i;
    
    if(c != scopesettings.timeperdiv)
    {
      x = ((i & 3) * 72) + 10;
      y = ((i >> 2) * 23) + 168;
      
      display_fill_rect(ACQ_MENU_XPOS + x, ACQ_MENU_YPOS + y, 68, 20);
    }
  }
  
  //Set channel 2 color for the box behind the selected text
  display_set_fg_color(TRIGGER_COLOR);

  //Get the position of the selected item
  c = ((sizeof(time_div_texts) / sizeof(int8 *)) - 1) - scopesettings.timeperdiv;
  x = ((c & 3) * 72) + 10;
  y = ((c >> 2) * 23) + 168;

  
  //Highlight the selected item
  display_fill_rect(ACQ_MENU_XPOS + x, ACQ_MENU_YPOS + y, 68, 20);
  
  for(i=0;i<(sizeof(time_div_texts) / sizeof(int8 *));i++)
  {
    //Settings displayed from smallest to highest value
    c = ((sizeof(time_div_texts) / sizeof(int8 *)) - 1) - i;
    
    //Check if the current text is the selected on
    if(c != scopesettings.timeperdiv)
    {
      //When not check if the current on is a viable candidate for full screen trace display
      if(viable_time_per_div[scopesettings.acqusitionspeed][c])
      {
        //Available but viable not selected texts in white  
        display_set_fg_color(0x00FFFFFF);
      }
      else
      {
        //Not viable but available not selected texts in grey
        display_set_fg_color(0x00686868);
      }
    }
    else
    {
      //Selected texts in black
      display_set_fg_color(0x00000000);
    }
    
    //Calculate the position of this text
    x = ((i & 3) * 72) + time_div_text_x_offsets[c];
    y = ((i >> 2) * 23) + 171;

    //Display the text from the table
    display_text(ACQ_MENU_XPOS + x, ACQ_MENU_YPOS + y, (int8 *)time_div_texts[c]);
  }  
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
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

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
  int y;
  
  //Setup the menu in a separate buffer to be able to slide it onto the screen
  display_set_screen_buffer(displaybuffer1);
  
  //Draw the background in dark grey
  display_set_fg_color(0x00181818);
  
  //Fill the background
  display_fill_rect(150, 46, 244, 353);

  //Draw the edge in a lighter grey
  display_set_fg_color(0x00333333);
  
  //Draw the edge
  display_draw_rect(150, 46, 244, 353);
  
  //Five black lines between the settings
  display_set_fg_color(0x00000000);
  
  for(y=104;y<350;y+=59)
  {
    display_draw_horz_line(y, 159, 385);
  }
  
  //Display the menu items  
  scope_system_settings_screen_brightness_item(0);
  scope_system_settings_grid_brightness_item(0);
  scope_system_settings_trigger_50_item();
  scope_system_settings_calibration_item(0);
  scope_system_settings_x_y_mode_item();
  scope_system_settings_confirmation_item();
  
  //Set source and target for getting it on the actual screen
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

  //Slide the image onto the actual screen. The speed factor makes it start fast and end slow, Smaller value makes it slower.
  display_slide_left_rect_onto_screen(150, 46, 244, 353, 63039);
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

void scope_system_settings_confirmation_item(void)
{
  //Set the colors for white foreground and grey background
  display_set_fg_color(0x00FFFFFF);
  display_set_bg_color(0x00181818);

  //Display the icon with the set colors
  display_copy_icon_use_colors(confirmation_icon, 171, 356, 24, 24);
  
  //Display the text
  display_set_font(&font_3);
  display_text(217, 354, "Notification");
  display_text(213, 370, "confirmation");
  
  //Show the state
  scope_display_slide_button(326, 358, scopesettings.confirmationmode);
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
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

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
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

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
  display_set_screen_buffer((uint16 *)maindisplaybuffer);

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

void scope_adjust_timebase(void)
{
  //Check if touch within the trace display region
  if((previousxtouch > 2) && (previousxtouch < 720) && (previousytouch > 50) && (previousytouch < 470))
  {
    //Check if touch on the left of the center line
    if(previousxtouch < 358)
    {
      //Check if not already on the highest setting (50S/div)
      if(scopesettings.timeperdiv > 0)
      {
        //Go up in time by taking one of the setting
        scopesettings.timeperdiv--;
        
        //18-11-2021 Temp for saving sample files
        saved_sample_buffers_count = 0;
        
      }
    }
    //Check if touch on the right of the center line
    else if(previousxtouch > 362)
    {
      //Check if not already on the lowest setting (10nS/div)
      if(scopesettings.timeperdiv < ((sizeof(time_div_texts) / sizeof(int8 *)) - 1))
      {
        //Go down in time by adding one to the setting
        scopesettings.timeperdiv++;
        
        //18-11-2021 Temp for saving sample files
        saved_sample_buffers_count = 0;
        
      }
    }
    
    //For time per div set with tapping on the screen the direct relation between the time per div and the sample rate is set
    //but only when the scope is running. Otherwise the sample rate of the acquired buffer still is valid.
    if(scopesettings.runstate == 0)
    {
      //Set the sample rate that belongs to the selected time per div setting
      scopesettings.acqusitionspeed = time_per_div_sample_rate[scopesettings.timeperdiv];
    }
    
    //Set the new setting in the FPGA
    fpga_set_trigger_timebase(scopesettings.timeperdiv);
    
    //Show he new setting on the display
    scope_acqusition_settings(0);
  }
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
    //Set the colors for drawing
    display_set_fg_color(CHANNEL1_COLOR);
    display_set_bg_color(0x00000000);

    //Select the font for this pointer id
    display_set_font(&font_0);
    
    //Check if in normal or x-y display mode
    if(scopesettings.xymodedisplay == 0)
    {
      //y position for the channel 1 trace center pointer.
      position = 441 - scopesettings.channel1.traceoffset;

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

      //Draw the pointer
      display_left_pointer(2, position, '1');
    }
    else
    {
      //y position for the channel 1 trace center pointer.
      position = 154 + scopesettings.channel1.traceoffset;

      //Limit on the left of the active range
      if(position < 166)
      {
        position = 166;
      }
      //Limit on the right of the active range
      else if(position > 548)
      {
        position = 548;
      }

      //Draw the pointer
      display_top_pointer(position, 47, '1');
    }
  }
  
  //Draw channel 2 pointer when it is enabled
  if(scopesettings.channel2.enable)
  {
    //y position for the channel 2 trace center pointer
    position = 441 - scopesettings.channel2.traceoffset;
    
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
  
  //Need to think about trigger position in 200mS - 20mS/div settings. Not sure if they work or need to be done in software
  //The original scope does not show them for 50mS and 20mS/div
  
  //Draw trigger position and level pointer when in normal display mode
  if(scopesettings.xymodedisplay == 0)
  {
    //x position for the trigger position pointer
    position = scopesettings.triggerposition + 2;
    
    //Limit on the left of the displayable region
    if(position < 2)
    {
      position = 2;
    }
    //Limit on the right of the displayable region
    else if(position > 712)
    {
      position = 712;
    }

    //Set the colors for drawing
    display_set_fg_color(TRIGGER_COLOR);
    display_set_bg_color(0x00000000);

    //Select the font for this pointer id
    display_set_font(&font_3);
    
    //Draw the pointer
    display_top_pointer(position, 47, 'H');

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

    //Need to reset the fore ground color
    display_set_fg_color(TRIGGER_COLOR);
    
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

void scope_acquire_trace_data(void)
{
  uint32 data;
  uint32 count;
  uint32 command;
  uint32 signaladjust;
  uint32 multiply;
  
  //Check if running and not in a trace or cursor displacement state
  if((scopesettings.runstate == 0) && (touchstate == 0))
  {
    //Set the trigger level
    fpga_set_trigger_level();

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

    //Send check on triggered command to the FPGA
    fpga_write_cmd(0x0A);

    //Wait for the FPGA to signal triggered or touch panel is touched or signals or cursors are being moved
    while(((fpga_read_byte() & 1) == 0) && (havetouch == 0))
    {
      //Scan the touch panel
      tp_i2c_read_status();
    }

    //Some bounds setting. Zero before, one here after trigger???
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
      }

      //Switch some mode
      scopesettings.triggerflag3 = 1;
    }

    //Not sure if this name is correct. Sends special ic command 0x14 and formats and translates returned data
    //Later on used to send to the FPGA with command 0x1F
    data = fpga_prepare_for_transfer();

    //Handle the returned data based on the time base setting
    //For the range 50mS/div - 500nS/div
    if(scopesettings.timeperdiv < 18)
    {
      //Check if range is 50mS/div - 20mS/div or 10mS/div - 500nS/div
      if(scopesettings.timeperdiv < 4)
      {
        //For 50mS/div and 20mS/div use 10
        data = 10;
      }
      else
      {
        //For 10mS/div - 500nS/div add or subtract data based on from FPGA returned value
        if(data < 750)
        {
          //Less then 750 make it bigger
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
      //Get correction value for the time base range 250nS/div - 10nS/div
      signaladjust = timebase_adjusters[scopesettings.timeperdiv - 18];

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

    //Only need a single count variable for both channels, since they run on the same sample rate
    //Have to see if an additional counter for multiple buffers is needed for 100 and 200ms settings
    //Determine the number of bytes to read based on the time base setting
    if(scopesettings.timeperdiv < 4)
    {
      //For 50mS/div and 20mS/div only 750 bytes
      count = 750;
      
      //For now set here, but could be moved to where the time base is set
      scopesettings.samplecount = 1500;
    }
    else
    {
      //For 10mS/div - 10nS/div 1500 bytes
      count = 1500;

      //For now set here, but could be moved to where the time base is set
      scopesettings.samplecount = 3000;
    }

    //Check if channel 1 is enabled
    if(scopesettings.channel1.enable)
    {
      //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
      fpga_write_cmd(0x1F);
      fpga_write_short(data);

      //Translate this channel volts per div setting
      signaladjust = fpga_read_parameter_ic(0x0B, scopesettings.channel1.voltperdiv) & 0x0000FFFF;

      //Set the flag for possibly doubling and offsetting the sample data
      multiply = scopesettings.channel1.voltperdiv == 6;

      //It seems it actually needs this. Using a fixed command 0x20 with or without the call to the special chip makes the trace garbage
      //Get the FPGA command to read from based on the trigger channel
      command = fpga_read_parameter_ic(0x0C, scopesettings.triggerchannel);

      //The first read function can also do the check on corrupted data (need to determine what the faulty value is 0x00 or 0xFF or all samples equal)
      //Have to decide if this should then signal this capture routine that it should discard this buffer and don't update the screen.
      //This would need a flag!!!!!!

      //Read the ADC1 bytes into a trace buffer and skip samples for ADC2 data
      fpga_read_adc1_data(command, channel1tracebuffer1, count, signaladjust, multiply, scopesettings.channel1.traceoffset);

      //Prepare FPGA for reading again
      //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
      fpga_write_cmd(0x1F);
      fpga_write_short(data);

      //Read and calibrate the ADC2 bytes into a trace buffer while skipping over the ADC1 samples
      fpga_read_adc2_data(0x21, channel1tracebuffer1, count, signaladjust, multiply, scopesettings.channel1.traceoffset, &channel1adc2calibration);

      //For 200mS and 100mS additional action is needed. Have to see if it will work
      //Additional sample buffers are needed but the question is if they are consecutive

      //Calculate some of the basic measurements like min, max, average, peak peak an another one (max + (min >> 1))???
  //    scope_calculate_min_max_avg((uint16 *)channel1tracebuffer1, &channel1measurements);

    }

    //Check if channel 2 is enabled
    if(scopesettings.channel2.enable)
    {
      //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
      fpga_write_cmd(0x1F);
      fpga_write_short(data);

      //Translate this channel volts per div setting
      signaladjust = fpga_read_parameter_ic(0x0B, scopesettings.channel2.voltperdiv) & 0x0000FFFF;

      //Set the flag for possibly doubling and offsetting the sample data
      multiply = scopesettings.channel2.voltperdiv == 6;

      //It seems it actually needs this. Using a fixed command 0x22 with or without the call to the special chip makes the trace garbage
      //Get the FPGA command to read from based on the trigger channel
      command = fpga_read_parameter_ic(0x0D, scopesettings.triggerchannel);

      //The first read function can also do the check on corrupted data (need to determine what the faulty value is 0x00 or 0xFF or all samples equal)
      //Have to decide if this should then signal this capture routine that it should discard this buffer and don't update the screen.
      //This would need a flag!!!!!!

      //Read the ADC1 bytes into a trace buffer and skip samples for ADC2 data
      fpga_read_adc1_data(command, channel2tracebuffer1, count, signaladjust, multiply, scopesettings.channel2.traceoffset);

      //Prepare FPGA for reading again
      //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
      fpga_write_cmd(0x1F);
      fpga_write_short(data);

      //Read and calibrate the ADC2 bytes into a trace buffer while skipping over the ADC1 samples
      fpga_read_adc2_data(0x23, channel2tracebuffer1, count, signaladjust, multiply, scopesettings.channel2.traceoffset, &channel2adc2calibration);

      //For 200mS and 100mS additional action is needed. Have to see if it will work
      //Additional sample buffers are needed but the question is if they are consecutive


      //Calculate some of the basic measurements like min, max, average, peak peak an another one (max + (min >> 1))???
  //    scope_calculate_min_max_avg((uint16 *)channel1tracebuffer2, &channel2measurements);

    }




    //Determine the trigger position based on the selected trigger channel
    scope_process_trigger(count);
    
    
      //Need to find the trigger point near the center of the buffer
      //And calculate the sample starting point based on the trigger position on the screen and the acquisition speed and time per div setting??
    

      //Implement the correct FPGA configuration on new sample rate and time per div setting selection!!!!!
      //Tapping on the screen needs to change both according to their original relation
      //Via the menu the sample rate is the base for the FPGA and the user can select the intended time per div
      //Show with grey text which time per div settings do not work well with the chosen sample rate.
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_process_trigger(uint32 count)
{
  uint16 *buffer;
  uint32  index;
  uint32  level = scopesettings.triggerlevel;
  uint32 sample1;
  uint32 sample2;
  
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

  disp_have_trigger = 0;
  
  //Set a starting point for checking on trigger
  //Count is half a sample buffer!!
  index = count - 5;
  count = 10;

  while(count--)
  {
    sample1 = buffer[index];
    sample2 = buffer[index + 1];

    if(((scopesettings.triggeredge == 0) && (sample1 < level) && (sample2 > level)) ||
       ((scopesettings.triggeredge == 1) && (sample1 > level) && (sample2 < level)))
    {
      //Set the current index as trigger point
      disp_trigger_index = index;
      
      //Signal trigger has been found
      disp_have_trigger = 1;
      
      //Done with checking
      break;
    }
    
    //Select next sample to check
    index++;
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_calculate_min_max_avg(uint16 *buffer, PMEASUREMENTS measurements)
{
  uint32 start;
  uint32 end;
  uint16 *ptr;
  uint32  min = 0xFFFF;
  uint32  max = 0;
  uint32  avg = 0;
  uint32  cnt1, cnt2;
  uint32  sample;
  
  //Check on time base setting for start and end points
  if(scopesettings.timeperdiv < 11)
  {
    //For 50mS/div and 20mS/div start at 100 and end at 600
    start = 100;
    end   = 600;
  }
  else
  {
    //For 10mS/div - 10nS/div start at 200 and end at 1200
    start =  200;
    end   = 1200;
  }
  
  //Point to the start of the data
  ptr = &buffer[start];
  
  //Calculate the number of samples to do
  cnt1 = end - start;
  cnt2 = cnt1;
  
  //Process the samples
  while(cnt2)
  {
    //Get the current sample and point to the next one
    sample = *ptr++;
    
    //Get the minimum value of the samples
    if(sample < min)
    {
      //Keep the lowest
      min = sample;
    }
    
    //Get the maximum value of the samples
    if(sample > max)
    {
      //Keep the highest
      max = sample;
    }
    
    //Add the samples for average calculation
    avg += sample;
    
    //One more sample done
    cnt2--;
  }
  
  //Save the results
  measurements->min = min;
  measurements->max = max;
  measurements->avg = avg / cnt1;
  measurements->peakpeak = max - min;
  measurements->maxplushalfmin = max + (min >> 1); 
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_trace_data(void)
{
  //See if it is possible to rework this to fixed point. A 32 bit mantissa is not accurate enough though
  
  //On the scope the last pixel interleaving is not working properly. Don't know why.
  
  //Check out the sin x/x interpolation downloaded from keysight (Sine wave reproduction using Sinc interpolation - v.1.0.py)
  
  //This needs more code to skip when stopped and no changes are made. It seems to be ok without this, but what is not needed is not needed
  //In the display trace routine the display only needs to be redrawn when certain conditions apply
  //  The user changes the sample rate or the time per div setting. Might need to block the setting of the sample rate when stopped because that makes no change to the current sample buffer.
  //  The user moves pointers around. Trace up and down should work, and trigger left and right. Changing the trigger level should not do anything, or even be disabled
  
  //Have to allow for moving the traces when either stopped or moving the traces without new samples coming in!!!!

  //For trace moving this requires additional code to overcome the offset being done in the FPGA


  //Need to compensate for the position being on the left side of the pointer
  uint32 triggerposition = scopesettings.triggerposition + 9;
  
  //Check if a trigger position has been found
  if(disp_have_trigger == 0)
  {
    //When not use the center of the sample buffer
    disp_trigger_index = scopesettings.samplecount / 2;
  }

  //Make sure the two settings are in range of the tables!!!!
  //SKipp displaying if not????


  //The amount of x positions needed per sample is based on the number of pixels per division, the set time per division and the sample rate.
  disp_xpos_per_sample = (50.0 * frequency_per_div[scopesettings.timeperdiv]) / sample_rate[scopesettings.acqusitionspeed];

  //This gives the step size for going through the samples. Is also the linear interleaving step for the y direction
  disp_sample_step = 1.0 / disp_xpos_per_sample;

  //The displayable x range is based on the number of samples and the number of x positions needed per sample
  //Halved to allow trigger position to be in the center
  double xrange = (scopesettings.samplecount * disp_xpos_per_sample) / 2.0;

  //x range needs to be at least 1 pixel  
  if(xrange < 1.0)
  {
    xrange = 1.0;
  }
  else if(xrange > 725.0)
  {
    //Limit on max screen pixels to avoid disp_xend becoming 0x80000000 due to overflow
    xrange = 725.0;
  }

  //Calculate the start end end x coordinates
  disp_xstart = triggerposition - xrange;
  disp_xend = triggerposition + xrange;
  
  //Limit on actual start of trace display
  if(disp_xstart < 3)
  {
    disp_xstart = 3;
  }
  
  //And limit on the actual end of the trace display
  if(disp_xend > 725)
  {
    disp_xend = 725;
  }
  
  //Determine first sample to use based on a full screen worth of samples and the trigger position in relation to the number of pixels on the screen
  disp_first_sample = disp_trigger_index - (((725.0 / disp_xpos_per_sample) * triggerposition) / 725.0) - 1;
  
  //If below the first sample limit it on the first sample
  if(disp_first_sample < 0)
  {
    disp_first_sample = 0;
  }

  //This makes sure no reading outside the buffer can occur
  if(disp_sample_step > ((scopesettings.samplecount) / 2))
  {
    disp_sample_step = (scopesettings.samplecount) / 2;
  }
    
    
    

  //If samplestep > 1 might be an idea to draw the in between samples on the same x position to avoid aliasing
  //If sample step < 1 then skip drawing on x positions. The draw line function does the linear interpolation



  //Use a separate buffer to clear the screen
  display_set_screen_buffer(displaybuffer1);

  //Clear the trace portion of the screen
  display_set_fg_color(0x00000000);
  display_fill_rect(2, 46, 728, 434);

  //Draw the grid lines and dots based on the grid brightness setting
  scope_draw_grid();

  
  
  //Need to determine if x y mode is enabled here


  //Check if channel1 is enabled
  if(scopesettings.channel1.enable)
  {
    //Go and do the actual trace drawing
    scope_display_channel_trace(channel1tracebuffer1, CHANNEL1_COLOR);
  }

  //Check if channel2 is enabled
  if(scopesettings.channel2.enable)
  {
    //Go and do the actual trace drawing
    scope_display_channel_trace(channel2tracebuffer1, CHANNEL2_COLOR);
  }





  //Draw the signal center, trigger level and trigger position pointers
  scope_draw_pointers();

  //Copy it to the actual screen buffer
  display_set_source_buffer(displaybuffer1);
  display_set_screen_buffer((uint16 *)maindisplaybuffer);
  display_copy_rect_to_screen(2, 46, 728, 434);


  
#if 0
  uint32 xpos1;
  uint32 xpos2;
  uint32 dy;
  uint16 *ptr;
 
  //Reset some flags if display touched for trace and cursor movement and stopped or in auto or normal mode
  if((touchstate) && ((scopesettings.triggermode != 1) || (scopesettings.runstate)))
  {
    //Set some flags
    scopesettings.triggerflag1 = 1;
    scopesettings.triggerflag2 = 1;
  }
  
  //Depending on the time base setting use different methods
  //Check if time base on 50mS/div - 10nS/div
  if(scopesettings.timeperdiv > 8)
  {
    //Use a separate display buffer
    display_set_screen_buffer(displaybuffer1);

    //Check if screen needs to be redrawn
    if(scopesettings.triggerflag2)
    {
      //Clear the trace portion of the screen
      display_set_fg_color(0x00000000);
      display_fill_rect(2, 46, 728, 434);

      //Draw the grid lines and dots based on the grid brightness setting
      scope_draw_grid();
    }
    
    //Check on another flag if this next bit needs to be done
    if(scopesettings.triggerflag1)
    {
      
      //Check if channel 1 is enabled
      if(scopesettings.channel1.enable)
      {
        //Check if running and not moving traces, cursors or pointers
        if((scopesettings.runstate == 0) && (touchstate == 0))
        {
          //Set some variable here
          //*(undefined2 *)(puVar8 + 0x12) = 400; 
        }
        
        //Call the zoom processing function
        //FUN_8000410c();
        
        //Check if auto or normal trigger mode and the time base in range of 50nS/div - 10nS/div and (trigger channel is channel 2 or some variable is set)
        if(((scopesettings.triggermode == 0) || (scopesettings.triggermode == 2)) &&  (scopesettings.timeperdiv > 26) && ((scopesettings.triggerchannel == 1) || channel_1_process_anyway))
        {
          //Process channel 1 trigger???
          //FUN_8000583c();
        }
        
        //Temporarily set to fixed values for testing
        disp_x_start = 3;
        disp_sample_count = 720;
        
        //Check if in normal display mode
        if(scopesettings.xymodedisplay == 0)
        {
          //Draw the trace on the screen
          scope_display_channel_trace((uint16 *)channel1tracebuffer4, disp_x_start, disp_sample_count, CHANNEL1_COLOR);
        }
      }
      

      //Do channel 2 here


      //Check on channel 1 FFT here
      
      
      //Check on channel 2 FFT here

    }
    
    
    //Check if screen needs to be redrawn
    if(scopesettings.triggerflag2)
    {
      //Draw the cursors with their measurement displays
      scope_draw_time_cursors();
      scope_draw_volt_cursors();
      scope_display_cursor_measurements();    //Still needs implementing

      //Draw the signal center, trigger level and trigger position pointers
      scope_draw_pointers();
      
      //Show the enabled measurements on the screen
      scope_display_measurements();    //Still needs implementing

      //Copy it to the actual screen buffer
      display_set_source_buffer(displaybuffer1);
      display_set_screen_buffer((uint16 *)maindisplaybuffer);
      display_copy_rect_to_screen(2, 46, 728, 434);
    }
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
    
    //Based on touchstate in move trace or cursor lines use either the previous x position or reset it
    if(touchstate)
    {
      disp_xpos = 0;
    }
    
    //Check if back on start of screen
    if(disp_xpos == 0)
    {
      //Use a separate buffer to clear the screen
      display_set_screen_buffer(displaybuffer1);

      //Clear the trace portion of the screen
      display_set_fg_color(0x00000000);
      display_fill_rect(2, 46, 728, 434);

      //Draw the grid lines and dots based on the grid brightness setting
      scope_draw_grid();
      
      //Draw the signal center, trigger level and trigger position pointers
      scope_draw_pointers();

      //Copy it to the actual screen buffer
      display_set_source_buffer(displaybuffer1);
      display_set_screen_buffer((uint16 *)maindisplaybuffer);
      display_copy_rect_to_screen(2, 46, 728, 434);
    }

    //Draw the traces directly to the screen
    display_set_screen_buffer((uint16 *)maindisplaybuffer);
    
    //Check if channel 1 is enabled
    if(scopesettings.channel1.enable)
    {
      //Destination buffer is declared as uint32 to be able to use it with file functions, so need to cast it to uint16 pointer here
      ptr = (uint16 *)channel1tracebuffer4;

      //Get the current sample for channel 1 coming up from the bottom of the screen
      disp_ch1_y = 449 - *ptr;
      
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

        //Destination buffer is declared as uint32 to be able to use it with file functions, so need to cast it to uint16 pointer here
        ptr = (uint16 *)channel1ypoints;
        
        //Save in a point array for picture and waveform save
        ptr[disp_xpos] = disp_ch1_y;
      }
    }

    //Check if channel 2 is enabled
    if(scopesettings.channel2.enable)
    {
      //Source buffer is declared as uint32 to be able to use it with file functions, so need to cast it to uint16 pointer here
      ptr = (uint16 *)channel2tracebuffer4;

      //Get the current sample for channel 1 coming up from the bottom of the screen
      disp_ch2_y = 449 - *ptr;
      
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

        //Destination buffer is declared as uint32 to be able to use it with file functions, so need to cast it to uint16 pointer here
        ptr = (uint16 *)channel2ypoints;
        
        //Save in a point array for picture and waveform save
        ptr[disp_xpos] = disp_ch2_y;
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

      //Destination buffer is declared as uint32 to be able to use it with file functions, so need to cast it to uint16 pointer here
      ptr = (uint16 *)channel1ypoints;
      
      //Save in a point array for picture and waveform save
      ptr[disp_xpos] = disp_ch1_y;
      
      //Destination buffer is declared as uint32 to be able to use it with file functions, so need to cast it to uint16 pointer here
      ptr = (uint16 *)channel2ypoints;
      
      //Save in a point array for picture and waveform save
      ptr[disp_xpos] = disp_ch2_y;
    }

    //Redraw the signal center, trigger level and trigger position pointers to be on top of the signals
    scope_draw_pointers();
    
    //Point to next x position
    disp_xpos++;
    
    //Check if past the end of displayable region
    if(disp_xpos > 719)
    {
      //Reset the x position
      disp_xpos = 0;
    }
  }
#endif  

}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_channel_trace(uint16 *buffer, uint32 color)
{
  double inputindex;
  
  register int32 previousindex;
  register int32 currentindex;
  register int32 sample1 = 0;
  register int32 sample2 = 0;
  register uint32 lastx = 0;
  register uint32 xpos = disp_xstart;

  uint32 firstpixel = 0;
  
  display_set_fg_color(color);
  
  //Get the first sample here!!
  
  

  //Process the sample data to screen data
  for(inputindex=disp_first_sample, previousindex = -1; xpos < disp_xend; inputindex += disp_sample_step, xpos++)
  {
    //Get the current integer index into the sample buffer
    currentindex = inputindex;

    //Check if linear approximation needs to be done. (Only when step < 1) pixels are skipped if so.
    if(currentindex != previousindex)
    {
      //Set new previous index
      previousindex = currentindex;

      //Get the sample
      sample2 = buffer[currentindex];

      //Limit the data to screen limits
      //Check if the data is bigger then max allowed
      if(sample2 > 401)
      {
        //If so limit to bottom of the screen
        sample2 = 401;
      }

      //Display y coordinates are inverted to signal orientation
      sample2 = 449 - sample2;


      if(firstpixel == 0)
      {
        firstpixel = 1;
      }
      else
      {
        //Need to draw a line here
        display_draw_line(lastx, sample1, xpos, sample2);
      }

      sample1 = sample2;

      lastx = xpos;
    }
  }

  //When step less then 1 the last pixel needs to be interpolated between current sample and next sample.
  if(disp_sample_step < 1.0)
  {
    //Calculate the scaler for the last y value based on the x distance from the last drawn position to the end of the screen
    //divided by the x distance it takes to where the next position should be drawn (Number of x steps per sample)
    double scaler =  (725.0 - lastx) / disp_xpos_per_sample;    // (1 / samplestep);

    //Get the current integer index into the sample buffer for retrieving the last sample
    currentindex = inputindex;

    //Signal adjust for correct voltage display
    //Need to check if this is correct
    sample2 = buffer[currentindex];

    //The limit the data to screen limits
    //Check if the data is bigger then max allowed
    if(sample2 > 401)
    {
      //If so limit to bottom of the screen
      sample2 = 401;
    }

    sample2 = 449 - sample2;

    sample2 = sample1 + ((double)((double)sample2 - (double)sample1) / scaler);

    display_draw_line(lastx, sample1, xpos, sample2);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_cursor_measurements(void)
{
  uint32 height = 5;
  uint32 ch1ypos = 52;
  uint32 ch2ypos = 52;
  uint32 delta;
  char   displaytext[10];
  
  //Check if need to do anything here
  if(scopesettings.timecursorsenable || (scopesettings.voltcursorsenable && (scopesettings.channel1.enable || scopesettings.channel2.enable)))
  {
    //Check if time cursor is enabled
    if(scopesettings.timecursorsenable)
    {
      //Add height for two text lines
      height += 32;
      
      //Shift the voltage text positions down
      ch1ypos += 32;
      ch2ypos += 32;
    }
    
    //Check if volt cursor is enabled
    if(scopesettings.voltcursorsenable)
    {
      //Check if channel 1 is enabled
      if(scopesettings.channel1.enable)
      {
        //Add height for one text line
        height += 16;
        
        //Shift the channel 2 voltage text down
        ch2ypos += 16;
      }
      
      //Check if channel 2 is enabled
      if(scopesettings.channel2.enable)
      {
        //Add height for one text line
        height += 16;
      }
    }
  
    //Set gray background for the cursor measurements
    display_set_fg_color(0x00404040);

    //Draw rounded rectangle depending on what is enabled.
    display_fill_rounded_rect(5, 49, 102, height, 2);

    //Use white text and font_0
    display_set_fg_color(0x00FFFFFF);
    display_set_font(&font_0);
    
    //Check if time cursor is enabled
    if(scopesettings.timecursorsenable)
    {
      //Time texts are always on the top two lines

      //Get the time delta based on the cursor positions
      delta = scopesettings.timecursor2position - scopesettings.timecursor1position;
      
      //Get the time calculation data for this time base setting. Only for the short time bases so take of the first 9
      PTIMECALCDATA tcd = (PTIMECALCDATA)&time_calc_data[scopesettings.timeperdiv - 9];
      
      //For the time multiply with the scaling factor and display based on the time scale
      delta *= tcd->mul_factor;
      
      //Format the time for displaying
      scope_print_value(displaytext, delta, tcd->time_scale, "T ", "S");
      display_text(10, 52, displaytext);
      
      //Calculate the frequency for this time. Need to adjust for stay within 32 bits
      delta /= 10;
      delta = 1000000000/ delta;
      
      //Format the frequency for displaying
      scope_print_value(displaytext, delta, tcd->freq_scale, "F ", "Hz");
      display_text(10, 68, displaytext);
    }
    
    //Check if volt cursor is enabled
    if(scopesettings.voltcursorsenable)
    {
      PVOLTCALCDATA vcd;
      uint32        volts;
      
      //Get the volts delta based on the cursor positions
      delta = scopesettings.voltcursor2position - scopesettings.voltcursor1position;
      
      //Check if channel 1 is enabled
      if(scopesettings.channel1.enable)
      {
        //Calculate the voltage based on the channel 1 settings
        vcd = (PVOLTCALCDATA)&volt_calc_data[scopesettings.channel1.magnification][scopesettings.channel1.voltperdiv];
        
        //Multiply with the scaling factor for the channel 1 settings
        volts = delta * vcd->mul_factor;
        
        //Channel 1 text has a variable position
        //Format the voltage for displaying
        scope_print_value(displaytext, volts, vcd->volt_scale, "V1 ", "V");
        display_text(10, ch1ypos, displaytext);
      }
      
      //Check if channel 2 is enabled
      if(scopesettings.channel2.enable)
      {
        //Calculate the voltage based on the channel 2 settings
        vcd = (PVOLTCALCDATA)&volt_calc_data[scopesettings.channel2.magnification][scopesettings.channel2.voltperdiv];
        
        //Multiply with the scaling factor for the channel 2 settings
        volts = delta * vcd->mul_factor;
        
        //Channel 2 text has a variable position
        //Format the voltage for displaying
        scope_print_value(displaytext, volts, vcd->volt_scale, "V2 ", "V");
        display_text(10, ch2ypos, displaytext);
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_measurements(void)
{
  
}


//----------------------------------------------------------------------------------------------------------------------------------
//Simple non optimized function for string copy that returns the position of the terminator
//----------------------------------------------------------------------------------------------------------------------------------
char *strcpy(char *dst, const char *src)
{
  while(*src)
  {
    *dst++ = *src++;
  }
  
  //Terminate the copy
  *dst = 0;
  
  return(dst);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_print_value(char *buffer, uint32 value, uint32 scale, char *header, char *sign)
{
  //Copy the header into the string buffer
  buffer = strcpy(buffer, header);

  //Need to find the magnitude scale for the input
  //The calculations are based on fixed point
  while(value >= 100000)
  {
    //Skip to the next magnitude
    scale++;
    
    //Bring the value in range
    value /= 1000;
  }

  //Format the remainder for displaying. Only 3 digits are allowed to be displayed
  if(value < 1000)
  {
    //Less then 1000 means x.yy
    buffer = scope_print_decimal(buffer, value, 2);
  }
  else if(value < 10000)
  {
    //More then 1000 but less then 10000 means xx.y
    value /= 10;
    buffer = scope_print_decimal(buffer, value, 1);
  }
  else
  {
    //More then 10000 and less then 100000 means xxx
    value /= 100;
    buffer = scope_print_decimal(buffer, value, 0);
  }

  //Make sure scale is not out of range
  if(scale > 7)
  {
    scale = 7;
  }
  
  //Add the magnitude scaler
  buffer = strcpy(buffer, magnitude_scaler[scale]);
  
  //Add the type of measurement sign
  strcpy(buffer, sign);
}

//----------------------------------------------------------------------------------------------------------------------------------

char *scope_print_decimal(char *buffer, uint32 value, uint32 decimals)
{
  char    b[12];
  uint32  i = 12;   //Start beyond the array since the index is pre decremented
  uint32  s;

  //For value 0 no need to do the work
  if(value == 0)
  {
    //Value is zero so just set 0 character
    b[--i] = '0';
  }
  else
  {
    //Process the digits
    while(value)
    {
      //Set current digit to decreased index
      b[--i] = (value % 10) + '0';

      //Check if decimal point needs to be placed
      if(i == 12 - decimals)
      {
        //If so put it in
        b[--i] = '.';
      }
      
      //Take of the current digit
      value /= 10;
    }
  }

  //Determine the size of the string
  s = 12 - i;
  
  //Copy to the buffer
  memcpy(buffer, &b[i], s);
  
  //terminate the string
  buffer[s] = 0;
  
  //Return the position of the terminator to allow appending
  return(&buffer[s]);
}

//----------------------------------------------------------------------------------------------------------------------------------
// File display functions
//----------------------------------------------------------------------------------------------------------------------------------
//Simplest setup here is to put all important data in a struct and make it such that a pointer is used to point to the active one
//This way no memory needs to be copied
//Needs a bit of a re write but might improve things a bit
//Depends on how the pointer setup effects the main code

void scope_save_setup(PSCOPESETTINGS settings)
{
  //For now just copy the settings to the given struct
  memcpy(settings, &scopesettings, sizeof(SCOPESETTINGS));
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_restore_setup(PSCOPESETTINGS settings)
{
  //For now just copy the settings from the given struct
  memcpy(&scopesettings, settings, sizeof(SCOPESETTINGS));
}

//----------------------------------------------------------------------------------------------------------------------------------
//These functions are for handling the settings to and from file

void scope_prepare_setup_for_file(void)
{
  uint16 *ptr = (uint16 *)viewfilesetupdata;
  uint32 index;
  uint32 channel;
  
  //No idea yet why this is done and what triggerflag4 is for
  if(scopesettings.triggerflag4)
  {
    //But these flags ensure the display is redrawn on trace displaying
    scopesettings.triggerflag2 = 1;
    scopesettings.triggerflag1 = 1;
  }
  
  //Best to clear the buffer first since not all bytes are used
  memset((uint8 *)viewfilesetupdata, 0, sizeof(viewfilesetupdata));
  
  //Copy the different settings to the file
  ptr[0]  = scopesettings.runstate;
  
  ptr[1]  = scopesettings.channel1.enable;
  ptr[2]  = scopesettings.channel1.voltperdiv;
  ptr[3]  = scopesettings.channel1.fftenable;
  ptr[4]  = scopesettings.channel1.coupling;
  ptr[5]  = scopesettings.channel1.magnification;
  
  ptr[6]  = scopesettings.channel2.enable;
  ptr[7]  = scopesettings.channel2.voltperdiv;
  ptr[8]  = scopesettings.channel2.fftenable;
  ptr[9]  = scopesettings.channel2.coupling;
  ptr[10] = scopesettings.channel2.magnification;

  ptr[11] = scopesettings.timeperdiv;
  
  ptr[12] = scopesettings.movespeed;
  
  ptr[13] = scopesettings.triggermode;
  ptr[14] = scopesettings.triggeredge;
  ptr[15] = scopesettings.triggerchannel;
  
  ptr[16] = scopesettings.batterychargelevel;
  
  ptr[17] = scopesettings.rightmenustate;

  ptr[18] = scopesettings.triggerflag2;
  ptr[19] = scopesettings.triggerflag1;

  ptr[20] = disp_x_start;

  //For time base settings 50S - 100mS per div disp_xpos is used as sample count
  if(scopesettings.timeperdiv < 9)
  {
    ptr[21] = disp_xpos;
  }
  else
  {
    ptr[21] = disp_sample_count;
  }

  //These are still unknown variables so set to zero for now
  ptr[22] = 0;
  ptr[23] = 0;
  ptr[24] = 0;
  ptr[25] = 0;
  
  ptr[26] = scopesettings.timeperdivbackup;
  
  ptr[27] = scopesettings.waveviewmode;
  
  ptr[40] = scopesettings.triggerposition;
  ptr[41] = scopesettings.triggeroffset;       //Is this one the correct one or should it be triggerlevel
  
  ptr[42] = scopesettings.channel1.traceoffset;
  ptr[43] = scopesettings.channel2.traceoffset;

  ptr[60] = scopesettings.screenbrightness;
  ptr[61] = scopesettings.gridbrightness;
  ptr[62] = scopesettings.alwaystrigger50;
  ptr[63] = scopesettings.xymodedisplay;
  
  //Point to the location in the buffer where the measurement states are set
  //Since the buffer is declared as uint32 the index will be based on that and the cast is needed for the assignment to the pointer
  //Need to verify this
  ptr = (uint16 *)&viewfilesetupdata[40];
  
  //Save the measurements enable states
  for(channel=0;channel<2;channel++)
  {
    //12 measurements per channel
    for(index=0;index<12;index++)
    {
      //Copy the current measurement state and point to the next one
      *ptr++ = scopesettings.measuresstate[channel][index];
    }
  }
  
  //The measurement values need to be copied in, but these seem to be 32 bits. With the buffer being 32 bit variables this is easy to do,
  //but I don't have these variables yet so skipped for now
  
  //Then the list of measurement numbers for display is copied in. The plan is to use a different setup in my code so also skipped
  
  
  //Point to the location in the buffer where the remaining parameters are copied
  //Since the buffer is declared as uint32 the index will be based on that and the cast is needed for the assignment to the pointer
  //Need to verify this
  ptr = (uint16 *)&viewfilesetupdata[100];
  
  ptr[0] = scopesettings.batterycharging;
  ptr[1] = scopesettings.batterychargelevel;   //Already copied in earlier so not really needed
  
  //Not sure what these two are for so set to zero for now.
  ptr[2] = 0;
  ptr[3] = 0;

  //No idea what this is for, but it is done in the original code
  fpga_read_parameter_ic(0x15, 0x18);
  
  //In the original code the sample buffers are saved here
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_restore_setup_from_file(void)
{
  uint16 *ptr = (uint16 *)viewfilesetupdata;
  uint32 index;
  uint32 channel;
  
  //Copy the different settings to the file
  scopesettings.runstate = ptr[0];
  
  scopesettings.channel1.enable        = ptr[1];
  scopesettings.channel1.voltperdiv    = ptr[2];
  scopesettings.channel1.fftenable     = ptr[3];
  scopesettings.channel1.coupling      = ptr[4];
  scopesettings.channel1.magnification = ptr[5];
  
  scopesettings.channel2.enable        = ptr[6];
  scopesettings.channel2.voltperdiv    = ptr[7];
  scopesettings.channel2.fftenable     = ptr[8];
  scopesettings.channel2.coupling      = ptr[9];
  scopesettings.channel2.magnification = ptr[10];

  scopesettings.timeperdiv = ptr[11];
  
  scopesettings.movespeed = ptr[12];
  
  scopesettings.triggermode    = ptr[13];
  scopesettings.triggeredge    = ptr[14];
  scopesettings.triggerchannel = ptr[15];
  
  scopesettings.batterychargelevel = ptr[16];
  
  scopesettings.rightmenustate = ptr[17];

  scopesettings.triggerflag2 = ptr[18];
  scopesettings.triggerflag1 = ptr[19];

  disp_x_start = ptr[20];

  //For time base settings 50S - 100mS per div disp_xpos is used as sample count
  if(scopesettings.timeperdiv < 9)
  {
    disp_xpos = ptr[21];
  }
  else
  {
    disp_sample_count = ptr[21];
  }

  //These are still unknown variables so set to zero for now
  //ptr[22] = 0;
  //ptr[23] = 0;
  //ptr[24] = 0;
  //ptr[25] = 0;
  
  scopesettings.timeperdivbackup = ptr[26];
  
  scopesettings.waveviewmode = ptr[27];
  
  scopesettings.triggerposition = ptr[40];
  scopesettings.triggeroffset   = ptr[41];       //Is this one the correct one or should it be triggerlevel
  
  scopesettings.channel1.traceoffset = ptr[42];
  scopesettings.channel2.traceoffset = ptr[43];

  scopesettings.screenbrightness = ptr[60];
  scopesettings.gridbrightness   = ptr[61];
  scopesettings.alwaystrigger50  = ptr[62];
  scopesettings.xymodedisplay    = ptr[63];
  
  //Point to the location in the buffer where the measurement states are set
  //Since the buffer is declared as uint32 the index will be based on that and the cast is needed for the assignment to the pointer
  //Need to verify this
  ptr = (uint16 *)&viewfilesetupdata[40];
  
  //Save the measurements enable states
  for(channel=0;channel<2;channel++)
  {
    //12 measurements per channel
    for(index=0;index<12;index++)
    {
      //Copy the current measurement state and point to the next one
      scopesettings.measuresstate[channel][index] = *ptr++;
    }
  }
  
  //The measurement values need to be copied in, but these seem to be 32 bits. With the buffer being 32 bit variables this is easy to do,
  //but I don't have these variables yet so skipped for now
  
  //Then the list of measurement numbers for display is copied in. The plan is to use a different setup in my code so also skipped
  
  
  //Point to the location in the buffer where the remaining parameters are copied
  //Since the buffer is declared as uint32 the index will be based on that and the cast is needed for the assignment to the pointer
  //Need to verify this
  ptr = (uint16 *)&viewfilesetupdata[100];
  
  scopesettings.batterycharging    = ptr[0];
  scopesettings.batterychargelevel = ptr[1];   //Already copied in earlier so not really needed
  
  //Not sure what these two are for so set to zero for now.
  //ptr[2] = 0;
  //ptr[3] = 0;

  //No idea what this is for, but it is done in the original code
  //In the original code there might be an error, since for waveform view the r1 register (parameter input) is not set in this function
  fpga_read_parameter_ic(0x15, 0x18);
  
  //In the original code the sample buffers are restored here
}

//----------------------------------------------------------------------------------------------------------------------------------
//In the original code they setup a list with all the available file names and index into that list when a file is used
//Here the file name is made on the fly when needed

void scope_print_file_name(uint32 filenumber)
{
  char    b[12];
  uint32  i = 12;   //Start beyond the array since the index is pre decremented
  uint32  s;

  //For file number 0 no need to do the work
  if(filenumber == 0)
  {
    //Value is zero so just set a 0 character
    b[--i] = '0';
  }
  else
  {
    //Process the digits
    while(filenumber)
    {
      //Set current digit to decreased index
      b[--i] = (filenumber % 10) + '0';

      //Take of the current digit
      filenumber /= 10;
    }
  }

  //Determine the size of the decimal part
  s = 12 - i;
  
  //Copy in the decimal file number
  memcpy(viewfilename, &b[i], s);
  
  //Add the extension
  memcpy(&viewfilename[s], view_file_extension[viewtype & VIEW_TYPE_MASK], 5);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_load_list_files(void)
{
  int32 result;
  
  //The original code is crap, so improved on it here
  //It also uses two separate functions for loading the lists
  //This code still needs more error handling with user feedback, but it will do for now
  
  //Try to open the thumbnail file for this view type
  result = f_open(&viewfp, list_file_name[viewtype & VIEW_TYPE_MASK], FA_READ);

  //Check the result
  if(result == FR_OK)
  {
    //Opened ok, so read the thumbnail data
    f_read(&viewfp, viewthumbnaildata, VIEW_THUMBNAIL_DATA_SIZE, 0);
    
    //Close the file
    f_close(&viewfp);
  }
  //Failure then check if file does not exist
  else if(result == FR_NO_FILE)
  {
    //Clear the thumbnail memory for a fresh file
    memset(viewthumbnaildata, 0, VIEW_THUMBNAIL_DATA_SIZE);
    
    //Need the file so create it
    result = f_open(&viewfp, list_file_name[viewtype & VIEW_TYPE_MASK], FA_CREATE_NEW | FA_WRITE | FA_READ);
    
    //Check if file is created ok
    if(result == FR_OK)
    {
      //Write the empty list to the file
      f_write(&viewfp, viewthumbnaildata, VIEW_THUMBNAIL_DATA_SIZE, 0);
    
      //Close the file
      f_close(&viewfp);
    }
  }
  
  //Try to open the file number file for this view type
  result = f_open(&viewfp, system_file_name[viewtype & VIEW_TYPE_MASK], FA_READ);
  
  //Check the result
  if(result == FR_OK)
  {
    //Opened ok, so read the file number data
    f_read(&viewfp, viewfilenumberdata, VIEW_FILE_NUMBER_DATA_SIZE, 0);

    //Close the file
    f_close(&viewfp);
  }
  //Failure then check if file does not exist
  else if(result == FR_NO_FILE)
  {
    //Clear the file number memory for a fresh file
    memset(viewfilenumberdata, 0, VIEW_FILE_NUMBER_DATA_SIZE);
    
    //Need the file so create it
    result = f_open(&viewfp, system_file_name[viewtype & VIEW_TYPE_MASK], FA_CREATE_NEW | FA_WRITE | FA_READ);
    
    //Check if file is created ok
    if(result == FR_OK)
    {
      //Write the empty list to the file
      f_write(&viewfp, viewfilenumberdata, VIEW_FILE_NUMBER_DATA_SIZE, 0);
    
      //Close the file
      f_close(&viewfp);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_save_list_files(void)
{
  int32 result;
  
  //The original code uses two separate functions for loading the lists
  //In the original code they try to create the file if open fails, but that is already done in the load function
  //and that is always called before a save is done, and the USB functionality is only operational when started via the menu
  //so the file can't be deleted in the meantime
  
  //Try to open the thumbnail file for this view type
  result = f_open(&viewfp, list_file_name[viewtype & VIEW_TYPE_MASK], FA_CREATE_ALWAYS | FA_WRITE);
  
  //Only if the file is opened write to it
  if(result == FR_OK)
  {
    //Write the list to the file
    f_write(&viewfp, viewthumbnaildata, VIEW_THUMBNAIL_DATA_SIZE, 0);

    //Close the file
    f_close(&viewfp);
  }
  else
  {
    //Show an error on the screen
  }
  
  //Try to open the file number file for this view type
  result = f_open(&viewfp, system_file_name[viewtype & VIEW_TYPE_MASK], FA_CREATE_ALWAYS | FA_WRITE);
  
  //Only if the file is opened write to it
  if(result == FR_OK)
  {
    //Write the list to the file
    f_write(&viewfp, viewfilenumberdata, VIEW_FILE_NUMBER_DATA_SIZE, 0);

    //Close the file
    f_close(&viewfp);
  }
  else
  {
    //Show an error on the screen
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//In the original code there are two separate functions for saving a picture or a waveform
//Since they are very similar in the basis I only made one function that handles all the tasks
//including restoring the data when a picture was made in waveform view mode.
//Another change is how a file number is obtained. Instead of probing the file system with every possible file until one is found that does not exist
//I use the file number list to get the first free number.

void scope_save_view_item_file(int32 type)
{
  uint32  newnumber;
  uint32  filenumber;
  uint32  result;
  uint16 *dptr;
  uint16 *sptr;
  
  //Point to the thumbnail data
  PTHUMBNAILDATA thumbnaildata = (PTHUMBNAILDATA)viewthumbnaildata;
  
  //Point to the file numbers
  uint16 *fnptr = (uint16 *)viewfilenumberdata;

  //Set the end pointer  
  uint16 *eptr = &fnptr[VIEW_MAX_ITEMS];
  
  //Save the current view type to be able to determine if the list files need to be reloaded
  uint32 currentviewtype = viewtype;
  
  //Switch to the given type
  viewtype = type;
  
  //Load the list files for this type. Needed for finding the file name and to add the thumbnail
  scope_load_list_files();

  //Find the first free file number
  //Most likely a more efficient solution for this problem exists, but this beats the original code where they try if a file number is free on the SD card with f_open
  for(newnumber=1;newnumber<VIEW_MAX_ITEMS;newnumber++)
  {
    //Start at the beginning of the list
    fnptr = (uint16 *)viewfilenumberdata;
    
    //Go through the list to see if the current number is in the list
    while((*fnptr) && (fnptr < eptr))
    {
      //Check if this number is in the list
      if(*fnptr == newnumber)
      {
        //Found it, so quit the loop
        break;
      }
      
      //Select the next number entry
      fnptr++;
    }
    
    //Check if not found
    if(*fnptr != newnumber)
    {
      //Can use this number since it is not in the list
      break;
    }
  }

  //Source is the entry before the last valid
  sptr = eptr - 2;

  //Destination is the last valid
  dptr = eptr - 1;
  
  //Bump all the entries in the list up
  //Compiler converts this to memmove
  while(dptr > (uint16 *)viewfilenumberdata)
  {
    *dptr-- = *sptr--;
  }
  
  //Fill in the new number
  *dptr = newnumber;
  
  //Find a free entry in the thumbnail list
  while(thumbnaildata < (PTHUMBNAILDATA)(((uint8 *)viewthumbnaildata) + VIEW_THUMBNAIL_DATA_SIZE))
  {
    //Get the file number from the current thumbnail
    filenumber = (thumbnaildata->filenumbermsb << 8) | thumbnaildata->filenumberlsb;
    
    //Check if the file number of this thumbnail is zero (not used) or matches the new file number
    if((filenumber == 0) || (filenumber == newnumber))
    {
      //If so create the thumbnail and quit the loop
      //This means that if there is no free slot or the new number is not found there will not be a thumbnail for it.
      //My version signals this.
      scope_create_thumbnail(newnumber, thumbnaildata);
      break;
    }

    //Select the next thumbnail set
    thumbnaildata++;
  }
  
  //save the amended lists
  scope_save_list_files();

  //Setup the filename
  scope_print_file_name(newnumber);
  
  //Open the new file. On failure signal this and quit
  result = f_open(&viewfp, viewfilename, FA_CREATE_NEW | FA_WRITE);

  //Check if file opened without problems
  if(result == FR_OK)
  {
    //For pictures the bitmap header needs to be written
    if(type == VIEW_TYPE_PICTURE)
    {
      //Write the bitmap header
      result = f_write(&viewfp, bmpheader, sizeof(bmpheader), 0);
    }

    //Check if still ok to proceed
    if(result == FR_OK)
    {
      //Save the settings for the trace portion of the data and write them to the file
      scope_prepare_setup_for_file();

      //Write the setup data to the file
      if((result = f_write(&viewfp, viewfilesetupdata, sizeof(viewfilesetupdata), 0)) == FR_OK)
      {
        //Write the trace data to the file
        //Save the channel 1 sample data
        if((result = f_write(&viewfp, (uint8 *)channel1tracebuffer4, 3000, 0)) == FR_OK)
        {
          //Save the channel 2 sample data
          if((result = f_write(&viewfp, (uint8 *)channel2tracebuffer4, 3000, 0)) == FR_OK)
          {
            //Save the channel 1 display data
            if((result = f_write(&viewfp, (uint8 *)channel1ypoints, 1500, 0)) == FR_OK)
            {
              //Save the channel 2 display data
              if((result = f_write(&viewfp, (uint8 *)channel2ypoints, 1500, 0)) == FR_OK)
              {
                //Finish with an empty blob of data to reach the needed file size
                //Clear part of the thumbnail data for this. Is reloaded anyway so does not matter
                memset((uint8 *)viewthumbnaildata, 0, 5000);
                
                //Save it to the file
                if((result = f_write(&viewfp, (uint8 *)viewthumbnaildata, 5000, 0)) == FR_OK)
                {
                  //For pictures extra code is needed to write the pixel data to the file
                  if(type == VIEW_TYPE_PICTURE)
                  {
                    //Write the pixel data
                    result = f_write(&viewfp, (uint8 *)maindisplaybuffer, PICTURE_DATA_SIZE, 0);
                  }
                }
              }
            }
          }
        }
      }
    }

    //Close the file
    f_close(&viewfp);

    //Check if all went well
    if(result == FR_OK)
    {
      //Show the saved successful message
      scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 0);
    }
    else
    {
      //Signal unable to write to the file
      scope_display_file_status_message(MESSAGE_FILE_WRITE_FAILED, 0);
    }
  }
  else
  {
    //Signal unable to create the file
    scope_display_file_status_message(MESSAGE_FILE_OPEN_FAILED, 0);
  }
  
  //When a picture is saved while viewing a waveform, reload the waveform lists
  if((type == VIEW_TYPE_PICTURE) && (currentviewtype == VIEW_TYPE_WAVEFORM) && (scopesettings.waveviewmode == 1))
  {
    //Restore the previous viewtype
    viewtype = currentviewtype;
    
    //Load the lists
    scope_load_list_files();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_remove_item_from_lists(uint32 delete)
{
  //Point to the file numbers
  uint16 *fnptr = (uint16 *)viewfilenumberdata;
  uint16 *dptr = &fnptr[viewcurrentindex];
  uint16 *sptr = &fnptr[viewcurrentindex + 1];
  uint16 *eptr = &fnptr[VIEW_MAX_ITEMS];
  
  //Get the file number for matching the item in the thumbnail list
  uint16 filenumber = fnptr[viewcurrentindex];
  
  //Point to the thumbnail data
  PTHUMBNAILDATA thumbnaildata = (PTHUMBNAILDATA)viewthumbnaildata;
  
  //The original code does this two at a time, which requires a check to see if there is an odd number of items to copy
  //Another method can be with memcpy and calculate the number of bytes that need to be moved
  //This solution only does the needed items, and with a max of 1000 items it does not really matter that much
  //Optimized compiling uses a memmove for this
  
  //Remove the item by shifting the others down
  while((sptr < eptr) && (*sptr))
  {
    //Copy the next item down
    *dptr++ = *sptr++;
  }
  
  //Clear the last entry
  *dptr = 0;
  
  //Locate the thumbnail data for the current file number
  while(thumbnaildata < (PTHUMBNAILDATA)(((uint8 *)viewthumbnaildata) + VIEW_THUMBNAIL_DATA_SIZE))
  {
    //Check if the file number of this thumbnail matches the current file number
    if(((thumbnaildata->filenumbermsb << 8) | thumbnaildata->filenumberlsb) == filenumber)
    {
      //If found, clear the file number
      thumbnaildata->filenumbermsb = 0;
      thumbnaildata->filenumberlsb = 0;

      //Done so quit the loop
      break;
    }

    //Select the next thumbnail set
    thumbnaildata++;
  }

  //Setup the file name for this file
  scope_print_file_name(filenumber);
  
  //Only delete when requested
  if(delete)
  {
    //Delete the file from the SD card
    f_unlink(viewfilename);                   //Need error handling with message here
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//This is used for both waveforms as well as pictures

int32 scope_load_trace_data(void)
{
  //Point to the file numbers
  uint16 *fnptr = (uint16 *)viewfilenumberdata;
  uint32 result;

  //Setup the file name for this view item  
  scope_print_file_name(fnptr[viewcurrentindex]);
  
  //Try to open the file for reading
  result = f_open(&viewfp, viewfilename, FA_READ);
  
  //Check if file opened ok
  if(result == FR_OK)
  {
    //For pictures the bitmap header needs to be skipped
    if(viewtype == VIEW_TYPE_PICTURE)
    {
      //SKip the first 70 bytes, which form the bitmap header
      result = f_lseek(&viewfp, 70);
    }
    
    //Check if still ok to proceed
    if(result == FR_OK)
    {
      //Checks on correct number of bytes read might be needed
      //Load the setup data to the file setup data buffer
      if((result = f_read(&viewfp, (uint8 *)viewfilesetupdata, 1000, 0)) == FR_OK)
      {
        //Copy the loaded data to the settings
        scope_restore_setup_from_file();

        //Load the channel 1 sample data
        if((result = f_read(&viewfp, (uint8 *)channel1tracebuffer4, 3000, 0)) == FR_OK)
        {
          //Load the channel 2 sample data
          if((result = f_read(&viewfp, (uint8 *)channel2tracebuffer4, 3000, 0)) == FR_OK)
          {
            //Load the channel 1 display data
            if((result = f_read(&viewfp, (uint8 *)channel1ypoints, 1500, 0)) == FR_OK)
            {
              //Load the channel 2 display data
              if((result = f_read(&viewfp, (uint8 *)channel2ypoints, 1500, 0)) == FR_OK)
              {
                //For waveform type view some variables need to be set to force the normal display in waveform view
                if(viewtype == VIEW_TYPE_WAVEFORM)
                {
                  scopesettings.triggerflag1 = 1;
                  scopesettings.triggerflag2 = 1;
                  scopesettings.runstate = 1;
                  scopesettings.waveviewmode = 1;
                }

                //Show the normal scope screen
                scope_setup_main_screen();

    //display the trace data

                //For now just a clean screen
                //Clear the trace portion of the screen
                display_set_fg_color(0x00000000);
                display_fill_rect(2, 46, 728, 434);
              }
            }
          }
        }
      }
    }
    else
    {
      //Signal unable to seek the file
      scope_display_file_status_message(MESSAGE_FILE_SEEK_FAILED, 0);
    }
    
    //Done with the file so close it
    f_close(&viewfp);
    
    //Check if one of the reads failed
    if(result != FR_OK)
    {
      //Signal unable to write to the file
      scope_display_file_status_message(MESSAGE_FILE_READ_FAILED, 0);
    }
  }
  else
  {
    //Signal unable to create the file
    scope_display_file_status_message(MESSAGE_FILE_OPEN_FAILED, 0);
  }

  //Check if all went well
  if(result == FR_OK)
  {
    //Tell it to the caller
    return(VIEW_TRACE_LOAD_OK);
  }

  //Remove the current item from the lists and delete the item from disk
  scope_remove_item_from_lists(1);
  
  //Save the list files
  scope_save_list_files();
  
  return(VIEW_TRACE_LOAD_ERROR);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_sync_list_files(void)
{
  uint32  t;
  uint32  save = 0;
  uint16 *fnptr;
  uint16 *eptr;
  
  //Handle the two types of list files
  for(t=0;t<VIEW_MAX_TYPES;t++)
  {
    //Set the current type to handle
    viewtype = t;
    
    //Load the files for this type
    scope_load_list_files();
    
    //Point to the file numbers
    fnptr = (uint16 *)viewfilenumberdata;

    //Set the end pointer  
    eptr = &fnptr[VIEW_MAX_ITEMS];
    
    //Go through the items in the system file and check if the files still exist on the SD card
    while((*fnptr) && (fnptr < eptr))
    {
      //Setup the filename
      scope_print_file_name(*fnptr);

      //Try to open the file. On failure remove it from the lists
      if(f_open(&viewfp, viewfilename, FA_READ) == FR_NO_FILE)
      {
        //Set the file index
//        viewcurrentindex = ((uint32)fnptr - (uint32)viewfilenumberdata) / sizeof(uint16);
        viewcurrentindex = (fnptr - (uint16 *)viewfilenumberdata) / sizeof(uint16);
        
        //Remove the current item from the lists without delete, since it is already removed from the SD card 
        scope_remove_item_from_lists(0);
        
        //Signal saving of the list files is needed
        save = 1;
      }
      else
      {
        //File exists so close it
        f_close(&viewfp);
      }
      
      //Select the next file number
      fnptr++;
    }
    
    //Check if there was a change
    if(save)
    {
      //Save the files if so
      scope_save_list_files();
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_count_and_display_thumbnails(void)
{
  uint16 *ptr;

  //Count how many items are available
  //The file contains shorts
  ptr = (uint16 *)viewfilenumberdata;

  //No items available yet
  viewavailableitems = 0;
  viewpages = 0;
  
  //A zero indicates no more entries. Make sure not to check beyond buffer size
  while(*ptr && (viewavailableitems < VIEW_MAX_ITEMS))
  {
    //One more item available
    viewavailableitems++;

    //Point to next entry
    ptr++;
  }

  //Calculate the number of pages available, based on number of items per page. 0 means 1 page
  //available items starts with 1 and with 16 items it would result in pages being 1, so need to subtract 1 before dividing
  if(viewavailableitems)
  {
    viewpages = (viewavailableitems - 1) / VIEW_ITEMS_PER_PAGE;
  }
  
  //Need to check if the current page is still valid
  if(viewpage > viewpages)
  {
    //Page no longer valid then use last page
    viewpage = viewpages;
  }
  
  //Display the thumbnails
  scope_display_thumbnails();
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_thumbnails(void)
{
  //Point to the file numbers
  uint16 *fnptr = (uint16 *)viewfilenumberdata;

  //Point to the thumbnail data
  PTHUMBNAILDATA thumbnaildata = (PTHUMBNAILDATA)viewthumbnaildata;
  
  //Flag for signaling thumbnail found
  uint32 found = 0;
    
  //Determine the first index based on the current page
  uint32 index = viewpage * VIEW_ITEMS_PER_PAGE;

  //Set black color for background
  display_set_fg_color(0x00000000);

  //Clear the thumbnail display area
  display_fill_rect(0, 0, 730, 480);
  
  //Set grey color for menu separator
  display_set_fg_color(0x00202020);
  
  //Separate the thumbnails from the menu bar
  display_draw_vert_line(730, 0, 479);
  
  //Check if there are items to display
  if(viewavailableitems)
  {
    //Determine the available items for the current page
    if(viewpage < viewpages)
    {
      //Not on the last page so full set available
      viewitemsonpage = VIEW_ITEMS_PER_PAGE;
    }
    else
    {
      //Get the remainder of items for the last page
      uint32 nofitems = viewavailableitems % VIEW_ITEMS_PER_PAGE;
      
      //See if a fraction of the max items per page is available
      if(nofitems)
      {
        //If so only display these
        viewitemsonpage = nofitems;
      }
      else
      {
        //If the remainder is zero there are max number of items on the last page
        viewitemsonpage = VIEW_ITEMS_PER_PAGE;
      }
    }

    //Determine the last index based on the available items on the current page
    uint32 lastindex = index + viewitemsonpage;

    //Start with first item for drawing
    uint32 xpos = VIEW_ITEM_XSTART;
    uint32 ypos = VIEW_ITEM_YSTART;

    //Draw the available items on the screen
    while(index < lastindex)
    {
      //Examining the original code makes believe there can be a mismatch between the two files so it is necessary to search for
      //the thumbnail for this file number. The original code uses a function for this and copies the data to buffers.
      //Here it is done directly from the source data

      //Get the thumbnail data for the current file
      while(thumbnaildata < (PTHUMBNAILDATA)(((uint8 *)viewthumbnaildata) + VIEW_THUMBNAIL_DATA_SIZE))
      {
        //Check if the file number of this thumbnail matches the current file number
        if(((thumbnaildata->filenumbermsb << 8) | thumbnaildata->filenumberlsb) == fnptr[index])
        {
          //If so signal found
          found = 1;
          break;
        }

        //Select the next thumbnail set
        thumbnaildata++;
      }

      //Check if thumbnail found
      if(found)
      {
        //Display the thumbnail
        //Need to make a distinction between normal display and xy display mode
        if(thumbnaildata->xydisplaymode == 0)
        {
          //Normal mode
          //Set the x start position based on trace position and skip three pixels.
          //Trace position can be > 0 when zoomed in stop mode 
          uint32 x = xpos + thumbnaildata->traceposition + 3;

          //Check if channel 1 is enabled
          if(thumbnaildata->channel1enable)
          {
            scope_display_thumbnail_data(x, ypos, thumbnaildata, 0);
          }

          //Check if channel 2 is enabled
          if(thumbnaildata->channel2enable)
          {
            scope_display_thumbnail_data(x, ypos, thumbnaildata, 1);
          }
        }
        else
        {
          //xy display mode so set the trace color for it
          display_set_fg_color(XYMODE_COLOR);

          //A minimum of 2 would also do, but the original code uses 5.
          //It does not check on a maximum of samples, which is needed because channel 1 is limited to 180 samples and channel 2 to 200 samples
          //Check on a minimum of 5 samples
          if(thumbnaildata->tracesamples < 5)
          {
            //If not set to zero for a single line drawing
            thumbnaildata->tracesamples = 0;
          }
          else
          {
            //If more then 5 take 5 samples of
            thumbnaildata->tracesamples -= 5;
          }

          //Check on maximum samples allowed
          if(thumbnaildata->tracesamples > 176)
          {
            thumbnaildata->tracesamples = 176;
          }

          //Point to the data of the two channels
          uint8 *channel1data = thumbnaildata->channel1data;
          uint8 *channel2data = thumbnaildata->channel2data;

          //Start with first sample
          uint32 sample = 0;

          //Center the xy display
          uint32 x = xpos + 29;

          //Keep the samples in registers
          register uint32 x1, x2, y1, y2;

          //Load the first samples
          x1 = *channel1data + x;
          y1 = *channel2data + ypos;

          //Point to the next samples
          channel1data++;
          channel2data++;

          //Draw the trace
          while(sample < thumbnaildata->tracesamples)
          {
            //Get second samples
            x2 = *channel1data + x;
            y2 = *channel2data + ypos;

            //Draw all the lines
            display_draw_line(x1, y1, x2, y2);

            //Swap the samples
            x1 = x2;
            y1 = y2;

            //Point to the next samples
            channel1data++;
            channel2data++;

            //One sample done
            sample++;
          }
        }
      }
      else
      {
        //Display thumbnail not found
        //This is not in the original code
        //Display the message in red and with font_0
        display_set_fg_color(0x00FF0000);
        display_set_font(&font_0);
        display_text(xpos + 15, ypos + 50, "THUMBNAIL NOT FOUND");
      }

      //Set grey color for item border
      display_set_fg_color(0x00202020);

      //Draw the border
      display_draw_rect(xpos, ypos, VIEW_ITEM_WIDTH, VIEW_ITEM_HEIGHT);

      //Skip to next coordinates
      xpos += VIEW_ITEM_XNEXT;

      //Check if next row needs to be used
      if(xpos > VIEW_ITEM_XLAST)
      {
        //Reset x position to beginning of row
        xpos = VIEW_ITEM_XSTART;

        //Bump y position to next row
        ypos += VIEW_ITEM_YNEXT;
      }

      //Select next index
      index++;

      //Reset the thumbnail data pointer and found flag
      thumbnaildata = (PTHUMBNAILDATA)viewthumbnaildata;
      found = 0;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//The original code uses the display_trace function for this but that needs preprocessing of the data, so separate function used here

void scope_display_thumbnail_data(uint32 xpos, uint32 ypos, PTHUMBNAILDATA thumbnaildata, uint32 channel)
{
  register uint32 index = 0;
  register uint32 sample1, sample2;
  register uint32 count = thumbnaildata->tracesamples - 4;
  register uint8 *channeldata;
  
  //Check if count not out of range
  if(count > 176)
  {
    //Limit on the number of displayable pixels
    count = 176;
  }
  
  //Initialize based on the channel
  if(channel == 0)
  {
    //Use channel 1 trace color
    display_set_fg_color(CHANNEL1_COLOR);
    
    //Point to the data for this trace
    channeldata = thumbnaildata->channel1data;
  }
  else
  {
    //Use channel 2 trace color
    display_set_fg_color(CHANNEL2_COLOR);
    
    //Point to the data for this trace
    channeldata = thumbnaildata->channel2data;
  }
  
  //Get the first sample
  sample1 = channeldata[index++] + ypos;
  
  //Do while the samples last
  while(index < count)
  {
    //Get the second sample
    sample2 = channeldata[index++] + ypos;

    //Draw the line for these samples
    display_draw_line(xpos, sample1, xpos + 1, sample2);
    
    //Skip to next position
    xpos++;
    
    //Swap the samples
    sample1 = sample2;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_create_thumbnail(uint32 filenumber, PTHUMBNAILDATA thumbnaildata)
{
  uint32  count;
  uint8  *dptr;
  uint16 *sptr;
  
  //The number of samples needs to be reduced by a factor 4
  //The original code does this in a stupid way, without filtering the data. For now I will use similar method without doing everything 4 times
  
  //Fill in the file number
  thumbnaildata->filenumberlsb =  filenumber       & 0xFF;
  thumbnaildata->filenumbermsb = (filenumber >> 8) & 0xFF;
  
  //Set the parameters for channel 1
  thumbnaildata->channel1enable      = scopesettings.channel1.enable;
  thumbnaildata->channel1traceoffset = (((scopesettings.channel1.traceoffset - 46) * 10000) / 36166) + 5;

  //Set the parameters for channel 2
  thumbnaildata->channel2enable      = scopesettings.channel2.enable;
  thumbnaildata->channel2traceoffset = (((scopesettings.channel2.traceoffset - 46) * 10000) / 36166) + 5;
  
  //Set trigger information
  thumbnaildata->triggerlevelscreenoffset = ((scopesettings.triggeroffset * 10000) / 36166) + 5;
  thumbnaildata->triggerpositiononscreen  = scopesettings.triggerposition / 4;
  
  //Set the xy display mode
  thumbnaildata->xydisplaymode = scopesettings.xymodedisplay;
  
  //For long timebase (50S/div - 100mS/div) use a different start and number of samples count
  if(scopesettings.timeperdiv < 9)
  {
    //Always start at the beginning
    thumbnaildata->traceposition = 0;
    
    //Use the current x position divided by 4 as sample count
    thumbnaildata->tracesamples = disp_xpos / 4;
  }
  else
  {
    //Start at where the current trace starts on screen divided by 4
    thumbnaildata->traceposition = disp_x_start / 4;
    
    //Use the display sample count divided by 4 as sample count
    thumbnaildata->tracesamples = disp_sample_count / 4;
  }
  
  //Do channel 1 data if it is enabled
  if(scopesettings.channel1.enable)
  {
    //Only take 176 samples
    count = 176;
    dptr = thumbnaildata->channel1data;
    sptr = (uint16 *)channel1ypoints + 2;
    
    //Do all the samples
    while(count)
    {
      //Reduce the magnitude of the sample to fit the thumbnail rectangle
      *dptr = (uint8)(((*sptr - 46) * 10000) / 36166) + 5;
      
      //Point to next samples
      dptr++;
      
      //Only take every fourth sample
      sptr += 4;
      
      //One sample done
      count--;
    }
  }
  else
  {
    //Not enabled then just clear the data
    memset(thumbnaildata->channel1data, 5, sizeof(thumbnaildata->channel1data));
  }
  
  //Do channel 2 data if it is enabled
  if(scopesettings.channel2.enable)
  {
    //Only take 176 samples
    count = 176;
    dptr = thumbnaildata->channel2data;
    sptr = (uint16 *)channel2ypoints + 2;
    
    //Do all the samples
    while(count)
    {
      //Reduce the magnitude of the sample to fit the thumbnail rectangle
      *dptr = (uint8)(((*sptr - 46) * 10000) / 36166) + 5;
      
      //Point to next samples
      dptr++;
      
      //Only take every fourth sample
      sptr += 4;
      
      //One sample done
      count--;
    }
  }
  else
  {
    //Not enabled then just clear the data
    memset(thumbnaildata->channel2data, 5, sizeof(thumbnaildata->channel2data));
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 scope_display_picture_item(void)
{
  //Display the new item
  if(scope_load_trace_data() == VIEW_TRACE_LOAD_ERROR)
  {
    //Return on an error
    return(VIEW_TRACE_LOAD_ERROR);
  }

  //And draw the bottom menu bar with a save of the background
  scope_setup_bottom_file_menu(VIEW_BOTTON_MENU_INIT);
  
  return(VIEW_TRACE_LOAD_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_selected_signs(void)
{
  uint32 index = 0;
  uint32 xpos = VIEW_ITEM_SELECTED_XSTART;
  uint32 ypos = VIEW_ITEM_SELECTED_YSTART;

  //Set the colors for displaying the selected sign. White sign on blue background
  display_set_fg_color(0x00FFFFFF);
  display_set_bg_color(0x000000FF);
  
  //Can't have more selects than items on the page  
  while(index < viewitemsonpage)
  {
    //Handle the current item based on its state
    switch(viewitemselected[index])
    {
      case VIEW_ITEM_SELECTED_NOT_DISPLAYED:
        //Make a copy of the screen under the selected sign location
        display_copy_rect_from_screen(xpos, ypos, 30, 30);
        
        //Display the selected sign
        display_copy_icon_use_colors(select_sign_icon, xpos, ypos, 30, 30);
        
        //Switch to displayed state
        viewitemselected[index] = VIEW_ITEM_SELECTED_DISPLAYED;
        break;

      case VIEW_ITEM_NOT_SELECTED_DISPLAYED:
        //Restore the screen on the selected sign location
        display_copy_rect_to_screen(xpos, ypos, 30, 30);
        
        //Switch to not selected state
        viewitemselected[index] = VIEW_ITEM_NOT_SELECTED;
        break;
    }
    
    //Skip to next coordinates
    xpos += VIEW_ITEM_XNEXT;
    
    //Check if next row needs to be used
    if(xpos > VIEW_ITEM_XLAST)
    {
      //Reset x position to beginning of selected row
      xpos = VIEW_ITEM_SELECTED_XSTART;
      
      //Bump y position to next row
      ypos += VIEW_ITEM_YNEXT;
    }
    
    //Select next index
    index++;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_file_status_message(int32 msgid, int32 alwayswait)
{
  uint32 checkconfirmation = scopesettings.confirmationmode;
  
  //Check if need to wait is requested
  if(alwayswait)
  {
    //If so override the setting
    checkconfirmation = 1;
  }
  
  //Need to save the screen buffer pointer and set it to the actual screen
  //When displaying trace data to avoid flickering data is drawn in a different screen buffer
  display_save_screen_buffer();

  //Save the screen rectangle where the message will be displayed
  display_set_screen_buffer((uint16 *)maindisplaybuffer);
  display_set_destination_buffer(displaybuffer2);
  display_copy_rect_from_screen(310, 210, 180, 60);
  
  //Draw the background in grey
  display_set_fg_color(0x00202020);
  display_fill_rect(310, 210, 180, 60);
  
  //Draw the border in a lighter grey
  display_set_fg_color(0x00303030);
  display_draw_rect(310, 210, 180, 60);

  //White color for text and use font_3
  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_3);
  
  switch(msgid)
  {
    case MESSAGE_SAVE_SUCCESSFUL:
      display_text(320, 220, "File saved successfully");
     
      //Don't wait for confirmation in case of success, unless requested
      checkconfirmation = alwayswait;
      break;

    case MESSAGE_FILE_CREATE_FAILED:
      display_text(320, 220, "Failed to create file");
      break;

    case MESSAGE_FILE_OPEN_FAILED:
      display_text(320, 220, "Failed to open file");
      break;

    case MESSAGE_FILE_WRITE_FAILED:
      display_text(320, 220, "Failed to write to file");
      break;

    case MESSAGE_FILE_READ_FAILED:
      display_text(320, 220, "Failed to read from file");
      break;

    case MESSAGE_FILE_SEEK_FAILED:
      display_text(320, 220, "Failed to seek in file");
      break;
  }

  //Display the file name in question
  display_text(320, 245, viewfilename);
  
  //Maybe wait for touch to continue in case of an error message
  if(checkconfirmation)
  {
    //wait for touch
    while(1)
    {
      //Read the touch panel status
      tp_i2c_read_status();

      //Check if the panel is touched
      if(havetouch)
      {
        //Done so quit the loop
        break;
      }
    }
  
    //Need to wait for touch to release before returning
    tp_i2c_wait_for_touch_release();
  }
  else
  {
    //Wait for half a second
    timer0_delay(500);
  }
  
  //Restore the original screen
  display_set_source_buffer(displaybuffer2);
  display_copy_rect_to_screen(310, 210, 180, 60);
  
  //Need to restore the screen buffer pointer
  display_restore_screen_buffer();
}

//----------------------------------------------------------------------------------------------------------------------------------
// Configuration data functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_load_configuration_data(void)
{
  //Get the settings data form the flash memory
  sys_spi_flash_read(0x001FD000, (uint8 *)settingsworkbuffer, sizeof(settingsworkbuffer));
  
  //Check if configuration data is ok
  if(settingsworkbuffer[200] == 0x1432)
  {
    //If they are ok, copy them to the actual settings
    scope_restore_config_data();
  }
  else
  {
    //Not ok, so reset to a default configuration
    scope_reset_config_data();
    
    //Get the settings in the working buffer and write them to the flash
    scope_save_configuration_data();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_save_configuration_data(void)
{
  //Save the settings for writing to the flash
  scope_save_config_data();

  //Write it to the flash
  sys_spi_flash_write(0x001FD000, (uint8 *)settingsworkbuffer, sizeof(settingsworkbuffer));
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_reset_config_data(void)
{
  //Load a default configuration in case of settings in flash being corrupted
  
  //Enable channel 1, dc coupling, 1x magnification, 50V/div, fft disabled and trace line in top part of the screen
  scopesettings.channel1.enable        = 1;
  scopesettings.channel1.coupling      = 0;
  scopesettings.channel1.magnification = 0;
  scopesettings.channel1.voltperdiv    = 0;
  scopesettings.channel1.fftenable     = 0;
  scopesettings.channel1.traceoffset   = 300;
  
  //Enable channel 2, dc coupling, 1x magnification, 50V/div, fft disabled and trace line in bottom part of the screen
  scopesettings.channel2.enable        = 1;
  scopesettings.channel2.coupling      = 0;
  scopesettings.channel2.magnification = 0;
  scopesettings.channel2.voltperdiv    = 0;
  scopesettings.channel2.fftenable     = 0;
  scopesettings.channel2.traceoffset   = 100;
  
  //Set trigger mode to auto, trigger edge to rising, trigger channel to channel 1, trigger position and trigger screen offset to center of the screen
  scopesettings.triggermode     = 0;
  scopesettings.triggeredge     = 0;
  scopesettings.triggerchannel  = 0;
  scopesettings.triggerposition = 362;
  scopesettings.triggeroffset   = 200;
  
  //Set move speed to fast
  scopesettings.movespeed = 0;
  
  //Set time base to 20uS/div
  scopesettings.timeperdiv = 12;
  
  //Set the related acquisition speed which is 5MHz
  scopesettings.acqusitionspeed = 5;
  
  //Enable some default measurements
  //Not yet implemented display wise and am thinking of a different way of doing it so left for later
  
  //Turn time cursor off and set some default positions
  scopesettings.timecursorsenable   = 0;
  scopesettings.timecursor1position = 183;
  scopesettings.timecursor2position = 547;
  
  //Turn volt cursor of and set some default positions
  scopesettings.voltcursorsenable   = 0;
  scopesettings.voltcursor1position = 167;
  scopesettings.voltcursor2position = 328;
  
  //Set right menu to normal state
  scopesettings.rightmenustate = 0;
  
  //Trigger flags to start mode
  scopesettings.triggerflag1 = 1;
  scopesettings.triggerflag2 = 1;

  //Set screen brightness to max, grid brightness to low, always 50% trigger on and x y mode display off
  scopesettings.screenbrightness = 100;
  scopesettings.gridbrightness   = 15;
  scopesettings.alwaystrigger50  = 1;
  scopesettings.xymodedisplay    = 0;
  
  //Set the settings integrity check flag
  system_ok = 0x1432;
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_save_config_data(void)
{
  uint32  channel;
  uint32  index;
  uint16 *ptr;
  
  //Save the channel 1 settings
  settingsworkbuffer[0]  = scopesettings.channel1.enable;
  settingsworkbuffer[3]  = scopesettings.channel1.coupling;
  settingsworkbuffer[4]  = scopesettings.channel1.magnification;
  settingsworkbuffer[1]  = scopesettings.channel1.voltperdiv;
  settingsworkbuffer[2]  = scopesettings.channel1.fftenable;
  settingsworkbuffer[42] = scopesettings.channel1.traceoffset;

  //Save the channel 2 settings
  settingsworkbuffer[5]  = scopesettings.channel2.enable;
  settingsworkbuffer[8]  = scopesettings.channel2.coupling;
  settingsworkbuffer[9]  = scopesettings.channel2.magnification;
  settingsworkbuffer[6]  = scopesettings.channel2.voltperdiv;
  settingsworkbuffer[7]  = scopesettings.channel2.fftenable;
  settingsworkbuffer[43] = scopesettings.channel2.traceoffset;
  
  //Save trigger settings
  settingsworkbuffer[12] = scopesettings.triggermode;
  settingsworkbuffer[13] = scopesettings.triggeredge;
  settingsworkbuffer[14] = scopesettings.triggerchannel;
  settingsworkbuffer[40] = scopesettings.triggerposition;
  settingsworkbuffer[41] = scopesettings.triggeroffset;
  
  //Save the time base
  settingsworkbuffer[10] = scopesettings.timeperdiv;

  //Save the acquisition speed
  settingsworkbuffer[17] = scopesettings.acqusitionspeed;
  
  //Save the move speed
  settingsworkbuffer[11] = scopesettings.movespeed;
  
  //Save the right menu state
  settingsworkbuffer[15] = scopesettings.rightmenustate;

  //Save the confirmation mode (not in the original code)
  settingsworkbuffer[16] = scopesettings.confirmationmode;
  
  //Save screen brightness, grid brightness, always 50% trigger and xy display mode
  settingsworkbuffer[60] = scopesettings.screenbrightness;
  settingsworkbuffer[61] = scopesettings.gridbrightness;
  settingsworkbuffer[62] = scopesettings.alwaystrigger50;
  settingsworkbuffer[63] = scopesettings.xymodedisplay;
  
  //Save the time cursor settings
  settingsworkbuffer[161] = scopesettings.timecursorsenable;
  settingsworkbuffer[162] = scopesettings.timecursor1position;
  settingsworkbuffer[163] = scopesettings.timecursor2position;
  
  //Save the volt cursor settings
  settingsworkbuffer[164] = scopesettings.voltcursorsenable;
  settingsworkbuffer[165] = scopesettings.voltcursor1position;
  settingsworkbuffer[166] = scopesettings.voltcursor2position;

  //Point to the first measurement enable setting
  ptr = &settingsworkbuffer[80];
  
  //Save the measurements enable states
  for(channel=0;channel<2;channel++)
  {
    //12 measurements per channel
    for(index=0;index<12;index++)
    {
      //Copy the current measurement state and point to the next one
      *ptr++ = scopesettings.measuresstate[channel][index];
    }
  }
  
  //Save the calibration data
  settingsworkbuffer[120] = channel1_calibration_factor;
  settingsworkbuffer[127] = channel2_calibration_factor;

  //Point to the first channel calibration value
  ptr = &settingsworkbuffer[121];
  
  //Copy the working set values to the saved values
  for(index=0;index<6;index++,ptr++)
  {
    //Copy the data for both channels
    ptr[0] = channel1_calibration_data[index];
    ptr[7] = channel2_calibration_data[index];
  }

  //Restore the ADC2 calibration
  settingsworkbuffer[134] = channel1adc2calibration.flag;
  settingsworkbuffer[135] = channel1adc2calibration.compensation;
  settingsworkbuffer[136] = channel2adc2calibration.flag;
  settingsworkbuffer[137] = channel2adc2calibration.compensation;
  
  //Save the system ok flag
  settingsworkbuffer[200] = system_ok;
}

//----------------------------------------------------------------------------------------------------------------------------------

void scope_restore_config_data(void)
{
  uint32  channel;
  uint32  index;
  uint16 *ptr;
  
  //Restore the channel 1 settings
  scopesettings.channel1.enable        = settingsworkbuffer[0];
  scopesettings.channel1.coupling      = settingsworkbuffer[3];
  scopesettings.channel1.magnification = settingsworkbuffer[4];
  scopesettings.channel1.voltperdiv    = settingsworkbuffer[1];
  scopesettings.channel1.fftenable     = settingsworkbuffer[2];
  scopesettings.channel1.traceoffset   = settingsworkbuffer[42];

  //Restore the channel 2 settings
  scopesettings.channel2.enable        = settingsworkbuffer[5];
  scopesettings.channel2.coupling      = settingsworkbuffer[8];
  scopesettings.channel2.magnification = settingsworkbuffer[9];
  scopesettings.channel2.voltperdiv    = settingsworkbuffer[6];
  scopesettings.channel2.fftenable     = settingsworkbuffer[7];
  scopesettings.channel2.traceoffset   = settingsworkbuffer[43];
  
  //Restore trigger settings
  scopesettings.triggermode     = settingsworkbuffer[12];
  scopesettings.triggeredge     = settingsworkbuffer[13];
  scopesettings.triggerchannel  = settingsworkbuffer[14];
  scopesettings.triggerposition = settingsworkbuffer[40];
  scopesettings.triggeroffset   = settingsworkbuffer[41];
  
  //Restore the time base
  scopesettings.timeperdiv = settingsworkbuffer[10];

  //Restore the acquisition speed
  scopesettings.acqusitionspeed = settingsworkbuffer[17];
  
  //Restore the move speed
  scopesettings.movespeed = settingsworkbuffer[11];
  
  //Restore the right menu state
  scopesettings.rightmenustate = settingsworkbuffer[15];
  
  //Restore the confirmation mode (not in the original code)
  scopesettings.confirmationmode = settingsworkbuffer[16];
  
  //Since it is added to the code need to make sure the loaded value is in range.
  //Was not the case on my system, even though the data position is not used in the code checked so far
  if(scopesettings.confirmationmode > 1)
  {
    scopesettings.confirmationmode = 1;
  }
  
  //Restore screen brightness, grid brightness, always 50% trigger and xy display mode
  scopesettings.screenbrightness = settingsworkbuffer[60];
  scopesettings.gridbrightness   = settingsworkbuffer[61];
  scopesettings.alwaystrigger50  = settingsworkbuffer[62];
  scopesettings.xymodedisplay    = settingsworkbuffer[63];
  
  //Restore the time cursor settings
  scopesettings.timecursorsenable   = settingsworkbuffer[161];
  scopesettings.timecursor1position = settingsworkbuffer[162];
  scopesettings.timecursor2position = settingsworkbuffer[163];
  
  //Restore the volt cursor settings
  scopesettings.voltcursorsenable   = settingsworkbuffer[164];
  scopesettings.voltcursor1position = settingsworkbuffer[165];
  scopesettings.voltcursor2position = settingsworkbuffer[166];

  //Point to the first measurement enable setting
  ptr = &settingsworkbuffer[80];
  
  //Restore the measurements enable states
  for(channel=0;channel<2;channel++)
  {
    //12 measurements per channel
    for(index=0;index<12;index++)
    {
      //Copy the current measurement state and point to the next one
      scopesettings.measuresstate[channel][index] = *ptr++;
    }
  }
  
  //Restore the calibration data
  channel1_calibration_factor = settingsworkbuffer[120];
  channel2_calibration_factor = settingsworkbuffer[127];

  //Point to the first channel calibration value
  ptr = &settingsworkbuffer[121];
  
  //Copy the saved values to the working set
  for(index=0;index<6;index++,ptr++)
  {
    //Copy the data for both channels
    channel1_calibration_data[index] = ptr[0];
    channel2_calibration_data[index] = ptr[7];
  }

  //The last entry is a copy of the fore last value
  //Different from the original code where they use a switch statement instead of an array index for getting the data
  channel1_calibration_data[6] = settingsworkbuffer[126];
  channel2_calibration_data[6] = settingsworkbuffer[133];

  //Restore the ADC2 calibration
  channel1adc2calibration.flag         = settingsworkbuffer[134];
  channel1adc2calibration.compensation = settingsworkbuffer[135];
  channel2adc2calibration.flag         = settingsworkbuffer[136];
  channel2adc2calibration.compensation = settingsworkbuffer[137];
  
  //Restore the system ok flag. This is a bit off bullshit. Should be a CRC over all the settings to really verify the integrity
  system_ok = settingsworkbuffer[200];
}

//----------------------------------------------------------------------------------------------------------------------------------

#ifndef USE_TP_CONFIG
void save_tp_config(void)
{
  //Create a file for the touch panel configuration. Fails if it already exists
  if(f_open(&viewfp, "FNIRSI_1013D_tp_config.bin", FA_CREATE_NEW | FA_WRITE | FA_READ) == FR_OK)
  {
    //Write the touch panel configuration to the sd card  
    f_write(&viewfp, tp_config_data, sizeof(tp_config_data), 0);
  
    //Close the file to finish the write
    f_close(&viewfp);
  }
}
#endif  

//----------------------------------------------------------------------------------------------------------------------------------
