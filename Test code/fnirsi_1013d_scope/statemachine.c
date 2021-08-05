//----------------------------------------------------------------------------------------------------------------------------------

//Scan the touch panel

//Main state is displaying the scope data

//On touch the first action is to see where the touch is, so an array of boxes might be needed
//Difficulty lies in when a trace or cursor is selected.

//----------------------------------------------------------------------------------------------------------------------------------

#include "statemachine.h"
#include "touchpanel.h"
#include "fpga_control.h"
#include "scope_functions.h"
#include "display_lib.h"
#include "fnirsi_1013d_scope.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern SCOPESETTINGS scopesettings;

extern uint8  havetouch;
extern uint16 xtouch;
extern uint16 ytouch;

extern uint16 maindisplaybuffer[];
extern uint16 displaybuffer1[];
extern uint16 displaybuffer2[];

//----------------------------------------------------------------------------------------------------------------------------------

uint8 touchstate = 0;

uint8 systemsettingsmenuopen = 0;
uint8 screenbrightnessopen = 0;
uint8 gridbrightnessopen = 0;
uint8 calibrationopen = 0;

//----------------------------------------------------------------------------------------------------------------------------------
//touch handler

void touch_handler(void)
{
  //Check on touch state
  if(touchstate == 0)
  {
    //No touch yet so scan for it
    scan_for_touch();
    
  }
}


//----------------------------------------------------------------------------------------------------------------------------------
//Top menu bar ranges from 0,0 to 730,46
//Right menu bar ranges from 730,0 to 800,480

void scan_for_touch(void)
{
  //Read the touch panel status
  tp_i2c_read_status();
  
  //Check if the panel is not touched
  if(havetouch == 0)
  {
    //Quit if so
    return;
  }
  
  //Draw directly to screen
  display_set_screen_buffer(maindisplaybuffer);

  //Scan for where the touch is applied
  if((xtouch <= 730) && (ytouch <= 46))
  {
    //Top menu bar, so handle that
    //Check if in main menu button range
    if(xtouch <= 80)
    {
      //Check if in normal state
      if(scopesettings.waveviewmode == 0)
      {
        //Set the button active
        scope_menu_button(1);

        //Wait until touch is released
        while(havetouch)
        {
          //Read the touch panel status
          tp_i2c_read_status();
        }

        //Set the button inactive
        scope_menu_button(0);

        //Save the screen rectangle where the menu will be displayed
        display_set_destination_buffer(displaybuffer2);
        display_copy_rect_from_screen(0, 46, 149, 233);

        //Go and setup the channel 1 menu
        scope_open_main_menu();

        //Go and handle the menu touch
        handle_main_menu_touch();

        //Restore the screen when done
        display_set_source_buffer(displaybuffer2);
        display_copy_rect_to_screen(0, 46, 149, 233);
      }
      else
      {
        //Set the button active
        scope_main_return_button(1);

        //Wait until touch is released
        while(havetouch)
        {
          //Read the touch panel status
          tp_i2c_read_status();
        }

        //Switch back to the main menu button and set it inactive
        scope_menu_button(0);

        //Reset the wave view mode back to normal state
        scopesettings.waveviewmode = 0;
      }
    }
    //Check if in channel 1 settings button range
    else if((xtouch >= 161) && (xtouch <= 260))
    {
      //Set the button active
      scope_channel1_settings(1);
      
      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }
      
      //Set the button inactive
      scope_channel1_settings(0);
      
      //Save the screen rectangle where the menu will be displayed
      display_set_destination_buffer(displaybuffer2);
      display_copy_rect_from_screen(161, 46, 183, 252);
      
      //Go and setup the channel 1 menu
      scope_open_channel1_menu();
      
      //Go and handle the menu touch
      handle_channel1_menu_touch();
      
      //Restore the screen when done
      display_set_source_buffer(displaybuffer2);
      display_copy_rect_to_screen(161, 46, 183, 252);
    }
    //Check if in channel 2 settings button range
    else if((xtouch >= 288) && (xtouch <= 387))
    {
      //Set the button active
      scope_channel2_settings(1);
      
      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }
      
      //Set the button inactive
      scope_channel2_settings(0);
      
      //Save the screen rectangle where the menu will be displayed
      display_set_destination_buffer(displaybuffer2);
      display_copy_rect_from_screen(288, 46, 183, 252);
      
      //Go and setup the channel 1 menu
      scope_open_channel2_menu();
      
      //Go and handle the menu touch
      handle_channel2_menu_touch();
      
      //Restore the screen when done
      display_set_source_buffer(displaybuffer2);
      display_copy_rect_to_screen(288, 46, 183, 252);
    }
    //Check if in move speed button range
    else if((xtouch >= 493) && (xtouch <= 533))
    {
      //Set the button active
      scope_move_speed(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }
      
      //Toggle the speed
      scopesettings.movespeed ^= 1;
      
      //Set the button inactive and show the new state
      scope_move_speed(0);
    }
    //Check if in trigger settings button range
    else if((xtouch >= 570) && (xtouch <= 700))
    {
      //Set the button active
      scope_trigger_settings(1);
      
      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }
      
      //Set the button inactive
      scope_trigger_settings(0);
      
      //Save the screen rectangle where the menu will be displayed
      display_set_destination_buffer(displaybuffer2);
      display_copy_rect_from_screen(560, 46, 172, 186);
      
      //Go and setup the channel 1 menu
      scope_open_trigger_menu();
      
      //Go and handle the menu touch
      handle_trigger_menu_touch();
      
      //Restore the screen when done
      display_set_source_buffer(displaybuffer2);
      display_copy_rect_to_screen(560, 46, 172, 186);
    }
  }
  else if(xtouch > 730)
  {
    //Check if control button is touched
    if((ytouch >= 3) && (ytouch <= 57))
    {
      //Highlight the button if touched
      scope_control_button(1);
      
      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_control_button(0);
      
      //Toggle the right menu state
      scopesettings.rightmenustate ^= 1;
      
      //Display the changed state
      scope_setup_right_control_menu();
    }
    //Not then handle the menus based on the selected menu state
    else
    {
      //Right menu bar, so handle it according to the menu state
      if(scopesettings.rightmenustate == 0)
      {
        //Basic control state
        handle_right_basic_menu_touch();
      }
      else
      {
        //Volts per div adjust state
        handle_right_volts_div_menu_touch();      
      }
    }
  }
  else
  {
    //Main screen part, so handle that
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handle_main_menu_touch(void)
{
  //Stay in the menu as long as there is no touch outside the menu  
  while(1)
  {
    //Scan the touch panel for touch
    tp_i2c_read_status();
    
    //Check if there is touch
    if(havetouch)
    {
      //Check if touch within the menu field
      if((xtouch >= 2) && (xtouch <= 149) && (ytouch >= 46) && (ytouch <= 279))
      {
        //Check if on system settings
        if((ytouch >= 46) && (ytouch <= 105))
        {
          //Check if already open
          if(systemsettingsmenuopen == 0)
          {
            //Set the button active
            scope_main_menu_system_settings(1);

            //Wait until touch is released
            while(havetouch)
            {
              //Read the touch panel status
              tp_i2c_read_status();
            }

            //Save the screen under the menu
            display_set_destination_buffer(displaybuffer2);
            display_copy_rect_from_screen(150, 46, 244, 294);
            
            //Show the system settings menu
            scope_open_system_settings_menu();
            
            //Signal the system settings menu is opened
            systemsettingsmenuopen = 1;
          }
        }
        //Check if on picture view
        else if((ytouch >= 107) && (ytouch <= 164))
        {
          //Set the button active
          scope_main_menu_picture_view(1);

          //Wait until touch is released
          while(havetouch)
          {
            //Read the touch panel status
            tp_i2c_read_status();
          }

          //Show and handle the picture view here
          
          //Close menu and switch to picture view screen
          
        }
        //Check if on waveform view
        else if((ytouch >= 166) && (ytouch <= 223))
        {
          //Set the button active
          scope_main_menu_waveform_view(1);

          //Wait until touch is released
          while(havetouch)
          {
            //Read the touch panel status
            tp_i2c_read_status();
          }

          //Show and handle the waveform view here

          //Close menu and switch to waveform view screen
        }
        //Check if on USB connection
        else if((ytouch >= 225) && (ytouch <= 278))
        {
          //Set the button active
          scope_main_menu_usb_connection(1);

          //Wait until touch is released
          while(havetouch)
          {
            //Read the touch panel status
            tp_i2c_read_status();
          }

          //Show and handle the usb connection here

          //Close menu and switch to usb connection screen
        }
      }
      //Check on system settings menu opened and being touched
      else if(systemsettingsmenuopen && (xtouch >= 150) && (xtouch <= 394) && (ytouch >= 46) && (ytouch <= 340))
      {
        //Check if on screen brightness
        if((ytouch >= 47) && (ytouch <= 103))
        {
          //Check if already open
          if(screenbrightnessopen == 0)
          {
            //Close any of the sub menus if open
            close_open_sub_menus();

            //Set this item active
            scope_system_settings_screen_brightness_item(1);

            //Wait until touch is released
            while(havetouch)
            {
              //Read the touch panel status
              tp_i2c_read_status();
            }

            //Show the screen brightness slider
            scope_open_slider(395, 46, scopesettings.screenbrightness);
            
            //Signal the screen brightness slider is opened
            screenbrightnessopen = 1;
          }
        }
        //Check if on grid brightness
        else if((ytouch >= 105) && (ytouch <= 162))
        {
          //Check if already open
          if(gridbrightnessopen == 0)
          {
            //Close any of the sub menus if open
            close_open_sub_menus();
            
            //Set this item active
            scope_system_settings_grid_brightness_item(1);

            //Wait until touch is released
            while(havetouch)
            {
              //Read the touch panel status
              tp_i2c_read_status();
            }

            //Show the screen brightness slider
            scope_open_slider(395, 104, scopesettings.gridbrightness);
            
            //Signal the screen brightness slider is opened
            gridbrightnessopen = 1;
          }
        }
        //Check if on always trigger 50%
        else if((ytouch >= 164) && (ytouch <= 221))
        {
          //Close any of the sub menus if open
          close_open_sub_menus();
          
          //Wait until touch is released
          while(havetouch)
          {
            //Read the touch panel status
            tp_i2c_read_status();
          }

          //Toggle the always trigger 50% state
          scopesettings.alwaystrigger50 ^= 1;
          
          //Show the state
          scope_display_slide_button(326, 183, scopesettings.alwaystrigger50);
        }
        //Check if on baseline calibration
        else if((ytouch >= 223) && (ytouch <= 280))
        {
          //Check if already open
          if(calibrationopen == 0)
          {
            //Close any of the sub menus if open
            close_open_sub_menus();

            //Set this item active
            scope_system_settings_calibration_item(1);

            //Wait until touch is released
            while(havetouch)
            {
              //Read the touch panel status
              tp_i2c_read_status();
            }

            //Show the start text
            scope_open_calibration_start_text();
            
            //Signal the calibration text is opened
            calibrationopen = 1;
          }
        }
        //Check if on x-y mode display
        else if((ytouch >= 282) && (ytouch <= 339))
        {
          //Close any of the sub menus if open
          close_open_sub_menus();
          
          //Wait until touch is released
          while(havetouch)
          {
            //Read the touch panel status
            tp_i2c_read_status();
          }

          //Toggle the x-y mode display state
          scopesettings.xymodedisplay ^= 1;
  
          //Show the state
          scope_display_slide_button(326, 299, scopesettings.xymodedisplay);
        }
      }
      //Check on screen brightness slider opened and being touched
      else if(screenbrightnessopen && (xtouch >= 395) && (xtouch <= 726) && (ytouch >= 46) && (ytouch <= 104))
      {
        //Move the slider to a new position and check if there was a change in position
        if(scope_move_slider(395, 46, &scopesettings.screenbrightness))
        {
          //Update the setting in the system settings menu
          scope_system_settings_screen_brightness_value();
          
          //Update the actual screen brightness
          fpga_set_translated_brightness(scopesettings.screenbrightness);
        }
      }
      //Check on grid brightness slider opened and being touched
      else if(gridbrightnessopen && (xtouch >= 395) && (xtouch <= 726) && (ytouch >= 105) && (ytouch <= 163))
      {
        //Move the slider to a new position and check if there was a change in position
        if(scope_move_slider(395, 104, &scopesettings.gridbrightness))
        {
          //Update the setting in the system settings menu
          scope_system_settings_grid_brightness_value();
          
          //Update the actual grid brightness if needed. There is no direct update of the background!
        }       
      }
      //Check on calibration start text opened and being touched
      else if((calibrationopen == 1) && (xtouch >= 395) && (xtouch <= 594) && (ytouch >= 223) && (ytouch <= 280))
      {
        //Check if touch is on the button
        if((xtouch >= 517) && (xtouch <= 583) && (ytouch >= 230) && (ytouch <= 272))
        {
          //Highlight the button
          scope_display_ok_button(517, 230, 1);
          
          //Wait until touch is released
          while(havetouch)
          {
            //Read the touch panel status
            tp_i2c_read_status();
          }
          
          //Show the baseline calibration active text
          scope_show_calibrating_text();
          
          //Start the calibration process
          
          //Show the calibration successful text if all went well
          scope_show_calibration_done_text();
          
          //Signal calibration has been done
          calibrationopen = 2;
        }
      }
      //Check on calibration done text opened and being touched
      else if((calibrationopen == 2) && (xtouch >= 395) && (xtouch <= 505) && (ytouch >= 223) && (ytouch <= 280))
      {
        //Nothing to do here so wait until touch is released
        while(havetouch)
        {
          //Read the touch panel status
          tp_i2c_read_status();
        }
      }
      else
      {
        //Close any of the sub menus if open
        close_open_sub_menus();
        
        //Check if system settings menu has been opened
        if(systemsettingsmenuopen)
        {
          //Restore the screen under the system settings menu when done
          display_set_source_buffer(displaybuffer2);
          display_copy_rect_to_screen(150, 46, 244, 294);
          
          //Clear the flag so it will be opened next time
          systemsettingsmenuopen = 0;
        }
        
        //Touch outside the menu's so quit
        return;
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handle_channel1_menu_touch(void)
{
  //Stay in the menu as long as there is no touch outside the menu  
  while(1)
  {
    //Scan the touch panel for touch
    tp_i2c_read_status();
    
    //Check if there is touch
    if(havetouch)
    {
      //Check if touch within the menu field
      if((xtouch >= 161) && (xtouch <= 344) && (ytouch >= 46) && (ytouch <= 298))
      {
        //Check on channel enable or disable
        if((ytouch >= 62) && (ytouch <= 84))
        {
          //Check on enable
          if((xtouch >= 239) && (xtouch <= 271))
          {
            //Enable the channel
            scopesettings.channel1.enable = 1;
            
            //Update the trigger channel selection in the FPGA as needed
            fpga_swap_trigger_channel();
            
            //Display this
            scope_channel1_enable_select();
            scope_channel1_settings(0);
          }
          //Check on disable
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Disable the channel
            scopesettings.channel1.enable = 0;

            //Update the trigger channel selection in the FPGA as needed
            fpga_swap_trigger_channel();
            
            //Reset the volts/div setting to max
            scopesettings.channel1.voltperdiv = 0;

            //Set volts per div in the FPGA
            fpga_set_channel1_voltperdiv();

            //Display this
            scope_channel1_enable_select();
            scope_channel1_settings(0);
          }
        }
        //Check on fft enable or disable
        else if((ytouch >= 124) && (ytouch <= 146))
        {
          //Check on enable
          if((xtouch >= 239) && (xtouch <= 271))
          {
            //Enable the channel
            scopesettings.channel1.fftenable = 1;
            
            //Display this
            scope_channel1_fft_show();
          }
          //Check on disable
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Disable the channel
            scopesettings.channel1.fftenable = 0;
            
            //Display this
            scope_channel1_fft_show();
          }
        }
        //Check on coupling DC or AD
        else if((ytouch >= 188) && (ytouch <= 210))
        {
          //Check on DC coupling
          if((xtouch >= 239) && (xtouch <= 271))
          {
            //Set the channel to DC coupling
            scopesettings.channel1.coupling = 0;
            
            //Update the FPGA
            fpga_set_channel1_coupling();
            
            //Display this
            scope_channel1_coupling_select();
            scope_channel1_settings(0);
          }
          //Check on AC coupling
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Set the channel to AC coupling
            scopesettings.channel1.coupling = 1;
            
            //Update the FPGA
            fpga_set_channel1_coupling();
            
            //Display this
            scope_channel1_coupling_select();
            scope_channel1_settings(0);
          }
        }
        //Check on probe magnification setting
        else if((ytouch >= 245) && (ytouch <= 283))
        {
          //Check on 1x
          if((xtouch >= 239) && (xtouch <= 259))
          {
            //Enable the channel
            scopesettings.channel1.magnification = 0;
            
            //Display this
            scope_channel1_probe_magnification_select();
            scope_channel1_settings(0);
          }
          //Check on 10x
          else if((xtouch >= 270) && (xtouch <= 293))
          {
            //Disable the channel
            scopesettings.channel1.magnification = 1;
            
            //Display this
            scope_channel1_probe_magnification_select();
            scope_channel1_settings(0);
          }
          //Check on 100x
          else if((xtouch >= 299) && (xtouch <= 329))
          {
            //Disable the channel
            scopesettings.channel1.magnification = 2;
            
            //Display this
            scope_channel1_probe_magnification_select();
            scope_channel1_settings(0);
          }
        }
        
        //Wait until touch is released before checking on a new position
        while(havetouch)
        {
          //Scan the touch panel for touch
          tp_i2c_read_status();
        }
      }
      else
      {
        //Touch outside the menu so quit
        return;
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handle_channel2_menu_touch(void)
{
  //Stay in the menu as long as there is no touch outside the menu  
  while(1)
  {
    //Scan the touch panel for touch
    tp_i2c_read_status();
    
    //Check if there is touch
    if(havetouch)
    {
      //Check if touch within the menu field
      if((xtouch >= 288) && (xtouch <= 471) && (ytouch >= 46) && (ytouch <= 298))
      {
        //Check on channel enable or disable
        if((ytouch >= 62) && (ytouch <= 84))
        {
          //Check on enable
          if((xtouch >= 366) && (xtouch <= 398))
          {
            //Enable the channel
            scopesettings.channel2.enable = 1;
            
            //Update the trigger channel selection in the FPGA as needed
            fpga_swap_trigger_channel();
            
            //Display this
            scope_channel2_enable_select();
            scope_channel2_settings(0);
          }
          //Check on disable
          else if((xtouch >= 418) && (xtouch <= 450))
          {
            //Disable the channel
            scopesettings.channel2.enable = 0;

            //Update the trigger channel selection in the FPGA as needed
            fpga_swap_trigger_channel();
            
            //Reset the volts/div setting to max
            scopesettings.channel2.voltperdiv = 0;

            //Set volts per div in the FPGA
            fpga_set_channel2_voltperdiv();
            
            //Display this
            scope_channel2_enable_select();
            scope_channel2_settings(0);
          }
        }
        //Check on fft enable or disable
        else if((ytouch >= 124) && (ytouch <= 146))
        {
          //Check on enable
          if((xtouch >= 366) && (xtouch <= 398))
          {
            //Enable the channel
            scopesettings.channel2.fftenable = 1;
            
            //Display this
            scope_channel2_fft_show();
          }
          //Check on disable
          else if((xtouch >= 418) && (xtouch <= 450))
          {
            //Disable the channel
            scopesettings.channel2.fftenable = 0;
            
            //Display this
            scope_channel2_fft_show();
          }
        }
        //Check on coupling DC or AD
        else if((ytouch >= 188) && (ytouch <= 210))
        {
          //Check on DC coupling
          if((xtouch >= 366) && (xtouch <= 398))
          {
            //Set the channel to DC coupling
            scopesettings.channel2.coupling = 0;
            
            //Update the FPGA
            fpga_set_channel2_coupling();
            
            //Display this
            scope_channel2_coupling_select();
            scope_channel2_settings(0);
          }
          //Check on AC coupling
          else if((xtouch >= 418) && (xtouch <= 450))
          {
            //Set the channel to AC coupling
            scopesettings.channel2.coupling = 1;
            
            //Update the FPGA
            fpga_set_channel2_coupling();
            
            //Display this
            scope_channel2_coupling_select();
            scope_channel2_settings(0);
          }
        }
        //Check on probe magnification setting
        else if((ytouch >= 245) && (ytouch <= 283))
        {
          //Check on 1x
          if((xtouch >= 366) && (xtouch <= 386))
          {
            //Enable the channel
            scopesettings.channel2.magnification = 0;
            
            //Display this
            scope_channel2_probe_magnification_select();
            scope_channel2_settings(0);
          }
          //Check on 10x
          else if((xtouch >= 397) && (xtouch <= 420))
          {
            //Disable the channel
            scopesettings.channel2.magnification = 1;
            
            //Display this
            scope_channel2_probe_magnification_select();
            scope_channel2_settings(0);
          }
          //Check on 100x
          else if((xtouch >= 426) && (xtouch <= 456))
          {
            //Disable the channel
            scopesettings.channel2.magnification = 2;
            
            //Display this
            scope_channel2_probe_magnification_select();
            scope_channel2_settings(0);
          }
        }
        
        //Wait until touch is released before checking on a new position
        while(havetouch)
        {
          //Scan the touch panel for touch
          tp_i2c_read_status();
        }
      }
      else
      {
        //Touch outside the menu so quit
        return;
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handle_trigger_menu_touch(void)
{
  //Stay in the menu as long as there is no touch outside the menu  
  while(1)
  {
    //Scan the touch panel for touch
    tp_i2c_read_status();
    
    //Check if there is touch
    if(havetouch)
    {
      //Check if touch within the menu field
      if((xtouch >= 560) && (xtouch <= 732) && (ytouch >= 46) && (ytouch <= 232))
      {
        //Check on trigger mode
        if((ytouch >= 57) && (ytouch <= 95))
        {
          //Check on auto
          if((xtouch >= 629) && (xtouch <= 649))
          {
            //Enable the channel
            scopesettings.triggermode = 0;
            
            //Need to call some function here
/*
            pcVar5[0x21] = '\0';    //Trigger mode auto
            FUN_80026828();         //Set FPGA trigger mode

            pcVar5[0x3a] = '\0';    //Scope run state

            pcVar5[0x18] = '\x01';
            pcVar5[0x17] = '\x01';

            display_run_stop_text((uint)(byte)pcVar5[0x3a]);
*/

            //Display this
            scope_trigger_mode_select();
            scope_trigger_settings(0);
          }
          //Check on single
          else if((xtouch >= 661) && (xtouch <= 681))
          {
            //Disable the channel
            scopesettings.triggermode = 1;

            //Need to call some function here
            
            //Limit time base setting to 10ms/div and down
            //If timebase < 11 make it 11
/*
            pcVar5[0x3a] = '\0';
            pcVar5[0x36] = '\0';
            pcVar5[0x37] = '\x01';

            FUN_80026828();    //Set change to FPGA
 
            display_run_stop_text((uint)(byte)pcVar5[0x3a]);

            if ((byte)pcVar5[10] < 0xb)
            {     //Time base change when less then 11 (below 5ms/div ??)
              pcVar5[10] = '\v';  //Make it 11
              FUN_800266c4();       //Translate a parameter and write to fpga
              display_time_div_setting();
            }
*/
            
            //Display this
            scope_trigger_mode_select();
            scope_trigger_settings(0);
          }
          //Check on normal
          else if((xtouch >= 692) && (xtouch <= 713))
          {
            //Disable the channel
            scopesettings.triggermode = 2;

            //Need to call some function here
/*
            FUN_80026828();

            pcVar5[0x3a] = '\0';

            display_run_stop_text((uint)(byte)pcVar5[0x3a]);

            pcVar5[0x36] = '\0';
            pcVar5[0x37] = '\x01';

            if ((byte)pcVar5[10] < 0xb)
            {
              pcVar5[10] = '\v';
              FUN_800266c4();
              display_time_div_setting();
            }
*/

            //Display this
            scope_trigger_mode_select();
            scope_trigger_settings(0);
          }
        }
        //Check on trigger edge
        else if((ytouch >= 125) && (ytouch <= 147))
        {
          //Check on rising
          if((xtouch >= 626) && (xtouch <= 666))
          {
            //Set the trigger edge to rising
            scopesettings.triggeredge = 0;
            
            //Update the FPGA
            fpga_set_trigger_edge();

            //Display this
            scope_trigger_edge_select();
            scope_trigger_settings(0);
          }
          //Check on falling
          else if((xtouch >= 671) && (xtouch <= 716))
          {
            //Set the trigger edge to falling
            scopesettings.triggeredge = 1;
            
            //Update the FPGA
            fpga_set_trigger_edge();

            //Display this
            scope_trigger_edge_select();
            scope_trigger_settings(0);
          }
        }
        //Check on trigger channel
        else if((ytouch >= 188) && (ytouch <= 210))
        {
          //Check on channel 1
          if((xtouch >= 632) && (xtouch <= 664))
          {
            //Only when the channel is enabled
            if(scopesettings.channel1.enable)
            {
              //Set the channel 1 as trigger source
              scopesettings.triggerchannel = 0;

              //Update the FPGA
              fpga_set_trigger_channel();

              //Display this
              scope_trigger_channel_select();
              scope_trigger_settings(0);
            }
          }
          //Check on channel 2
          else if((xtouch >= 680) && (xtouch <= 712))
          {
            //Only when the channel is enabled
            if(scopesettings.channel2.enable)
            {
              //Set channel 2 as trigger source
              scopesettings.triggerchannel = 1;

              //Update the FPGA
              fpga_set_trigger_channel();

              //Display this
              scope_trigger_channel_select();
              scope_trigger_settings(0);
            }
          }
        }
        
        //Wait until touch is released before checking on a new position
        while(havetouch)
        {
          //Scan the touch panel for touch
          tp_i2c_read_status();
        }
      }
      else
      {
        //Touch outside the menu so quit
        return;
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handle_right_basic_menu_touch(void)
{
  //Check if run/stop or page up button is touched
  if((ytouch >= 63) && (ytouch <= 117))
  {
    //Check on wave view state for which button is shown
    if(scopesettings.waveviewmode == 0)
    {
      //Run/stop so highlight that button if touched
      scope_run_stop_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_run_stop_button(0);

      //Toggle the run state
      scopesettings.runstate ^= 1;
/*
      if (pcVar5[0x3a] == '\0')  //scopesettings.runstate
      {
        pcVar5[0x3a] = '\x01';
        *(ushort *)puVar19 = (ushort)(byte)pcVar5[3];     //Save the volts/div setting for each channel when runstate is enabled (In 0x80192ec6)
        *(ushort *)puVar7 = (ushort)(byte)pcVar5[0xf];    //(In 0x80192ec8)
      }
      else
      {
        pcVar5[0x3a] = '\0';
        *(undefined2 *)PTR_DAT_800202ec = 0;
        *(undefined2 *)PTR_DAT_800202f0 = 400;
        *(undefined2 *)PTR_DAT_800202f4 = 0;
        *(undefined2 *)PTR_DAT_800202f8 = 400;
      }

         //Trigger mode              run state
      if ((pcVar5[0x21] == '\0') || (pcVar5[0x3a] != '\0'))
      {
        pcVar5[0x18] = '\x01';
        pcVar5[0x17] = '\x01';
      }
      else
      {
        pcVar5[0x36] = '\0';
        pcVar5[0x37] = '\x01';   //Update screen flag
      }
*/      
      //Display the changed state
      scope_run_stop_text(scopesettings.runstate);
    }
    else
    {
      //Page up so highlight that button if touched
      scope_page_up_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_page_up_button(0);

      //Some waveform counter needs to be checked and decremented
      //Previous waveform needs to be displayed
      //waveform_select_file
    }
  }
  //Check if auto set or page down button is touched
  else if((ytouch >= 123) && (ytouch <= 177))
  {
    //Check on wave view state for which button is shown
    if(scopesettings.waveviewmode == 0)
    {
      //Auto set so highlight that button if touched
      scope_auto_set_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_auto_set_button(0);

/*
      pcVar5[0x21] = '\0';            //Trigger mode
      FUN_80026828();                 //Set trigger mode in the FPGA
      display_trigger_settings(0);
      FUN_80002050();                 //Perform the actual auto set action?? (perform_auto_set)
      display_ch1_settings(0);
      display_ch2_settings(0);
*/      
    }
    else
    {
      //Page down so highlight that button if touched
      scope_page_down_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_page_down_button(0);

      //Some waveform counter needs to be checked and incremented
      //Next waveforms needs to be displayed
      //waveform_select_file
    }
  }
  //Check if time cursor button is touched
  else if((ytouch >= 183) && (ytouch <= 237))
  {
    //Highlight the button if touched
    scope_t_cursor_button(1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_t_cursor_button(0);
    
    //Time cursor only allowed for time base 50mS/div and lower
    if(scopesettings.timeperdiv > 8)
    {
      //Toggle the enable setting
      scopesettings.timecursorsenable ^= 1;
    }
  }
  //Check if volt cursor button is touched
  else if((ytouch >= 243) && (ytouch <= 297))
  {
    //Highlight the button if touched
    scope_v_cursor_button(1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_v_cursor_button(0);

    //Volt cursor only allowed for time base 50mS/div and lower
    if(scopesettings.timeperdiv > 8)
    {
      //Toggle the enable setting
      scopesettings.voltcursorsenable ^= 1;
    }
  }
  //Check if measures button is touched
  else if((ytouch >= 303) && (ytouch <= 357))
  {
    //Highlight the button if touched
    scope_measures_button(1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_measures_button(0);
    
    //Save the screen rectangle where the menu will be displayed
    display_set_destination_buffer(displaybuffer2);
    display_copy_rect_from_screen(231, 263, 499, 214);

    //Go and setup the channel 1 menu
    scope_open_measures_menu();

    //Go and handle the menu touch
    handle_measures_menu_touch();

    //Restore the screen when done
    display_set_source_buffer(displaybuffer2);
    display_copy_rect_to_screen(231, 263, 499, 214);
  }
  //Check if save picture button is touched
  else if((ytouch >= 363) && (ytouch <= 417))
  {
    //Highlight the button if touched
    scope_save_picture_button(1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_save_picture_button(0);
/*    
    //This needs to be done for save picture
    FUN_80025f2c();
    if ((pcVar5[0x43] != '\0') && (*PTR_DAT_80020300 == '\x01'))
    {
      FUN_8002c8e4();
      some_sd_card_stuff_3();
    }
*/
  }
  //Check if save or delete wave button is touched
  else if((ytouch >= 423) && (ytouch <= 477))
  {
    //Check on wave view state for which button is shown
    if(scopesettings.waveviewmode == 0)
    {
      //Save wave so highlight that button if touched
      scope_save_wave_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_save_wave_button(0);
/*
      //This needs to be done for save wave
      FUN_80025c38();
*/
    }
    else
    {
      //Delete wave so highlight that button if touched
      scope_delete_wave_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_delete_wave_button(0);
/*
      //This needs to be done for delete wave      
      iVar25 = FUN_8002b8e8();
      if(iVar25 == 0)
      {
        FUN_8002ca8c();
      }
      else
      {
        FUN_8002ca34();
        iVar25 = FUN_8002ca8c();
        
        if (iVar25 != 0)  //Last wave deleted then back to normal view mode
        {
          pcVar5[0x43] = '\0';
        }
      }
*/
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handle_right_volts_div_menu_touch(void)
{
  //Check if channel 1 V+ button is touched
  if((ytouch >= 78) && (ytouch <= 140))
  {
    //Highlight the button if touched
    scope_ch1_sensitivity_control(0,1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_ch1_sensitivity_control(0,0);
    
    //Only if channel is enabled
    if(scopesettings.channel1.enable)
    {
      //Check if setting not already on max
      if(scopesettings.channel1.voltperdiv < 6)
      {
        //Original code has some limit on updating when the scope is not running on the time base setting or a previous stored volts per div setting
        //The latter maybe has to do with a stored wave that is being looked at
        //The first check might have to do with not having the signal in memory to do the change on????
        //For now just allowing constant change within the max limit
        
        //Step up to the next setting. (Lowering the setting)
        scopesettings.channel1.voltperdiv++;
        
        //Show the change on the screen
        scope_channel1_settings(0);
        
        //Only update the FPGA in normal view mode
        if(scopesettings.waveviewmode == 0)
        {
          //Set the volts per div for this channel
          fpga_set_channel1_voltperdiv();
          
          //Need a ms timed delay
        }
        
      }
    }
/*
    if (*pcVar5 != '\0') //Channel enable
    {
      bVar2 = pcVar5[0x3a];   //Scope run mode
      bVar26 = bVar2 != 0;

      if (bVar26)             //Only when scope is not running
      {
        bVar2 = pcVar5[10];   //Time base
      }

        //No updating when scope stopped and the time base is more then 50mS/div
//        if(!((scopesettings.runstate != 0) && (scopesettings.timeperdiv < 9)))
//        {
//        }

      //Only increment when volts per div less then 6
      if (((!bVar26 || 8 < bVar2) && ((byte)pcVar5[3] < 6)) && ((pcVar5[0x3a] == '\0' || (((ushort)(byte)pcVar5[3] <= *(ushort *)puVar19 || (((ushort)(byte)pcVar5[3] - *(ushort *)puVar19 & 0xff) < 2))))))
      {
        pcVar5[3] = pcVar5[3] + '\x01';  //Add one to the volt/div setting
        display_ch1_settings(0);         //Display the result

        if (pcVar5[0x43] == '\0')        //View mode normal
        {
          FUN_8000689c();                //Set volts div in FPGA
          FUN_8000696c();                //Also some FPGA control (0x32, so the offset??)
          delay_2(0x3c);                 //Give it some time to settle
        }
      }
    }
*/
  }
  //Check if channel 1 V- button is touched
  else if((ytouch >= 163) && (ytouch <= 223))
  {
    //Highlight the button if touched
    scope_ch1_sensitivity_control(1,1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_ch1_sensitivity_control(1,0);
    
    //Only if channel is enabled
    if(scopesettings.channel1.enable)
    {
      //Check if setting not already on min
      if(scopesettings.channel1.voltperdiv > 0)
      {
        //Original code has some limit on updating when the scope is not running on the time base setting or a previous stored volts per div setting
        //The latter maybe has to do with a stored wave that is being looked at
        //For now just allowing constant change within the max limit
        
        //Step down to the next setting. (Increasing the setting)
        scopesettings.channel1.voltperdiv--;
        
        //Show the change on the screen
        scope_channel1_settings(0);
        
        //Only update the FPGA in normal view mode
        if(scopesettings.waveviewmode == 0)
        {
          //Set the volts per div for this channel
          fpga_set_channel1_voltperdiv();

          //Need a ms timed delay
        }
      }
    }
/*
    if (*pcVar5 != '\0') //Channel enable
    {
      bVar2 = pcVar5[0x3a];   //Scope run mode
      bVar26 = bVar2 != 0;

      if (bVar26)             //Only when stopped
      {
        bVar2 = pcVar5[10];   //Time base
      }

      if (((!bVar26 || 8 < bVar2) && (pcVar5[3] != '\0')) && ((pcVar5[0x3a] == '\0' || ((*(ushort *)puVar19 <= (ushort)(byte)pcVar5[3] || ((*(ushort *)puVar19 - (ushort)(byte)pcVar5[3] & 0xff) < 2))))))
      {
        pcVar5[3] = pcVar5[3] - '\x01';  //Take one of the volt/div setting
        display_ch1_settings(0);         //Display the result

        if (pcVar5[0x43] == '\0')        //View mode normal
        {
          FUN_8000689c();                //Set volts div in FPGA
          FUN_8000696c();                //Also some FPGA control (0x32, so the offset??)
          delay_2(0x3c);                 //Give it some time to settle
        }
      }
    }
*/
  }
  //Check if channel 2 V+ button is touched
  else if((ytouch >= 258) && (ytouch <= 320))
  {
    //Highlight the button if touched
    scope_ch2_sensitivity_control(0,1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_ch2_sensitivity_control(0,0);
    
    //Only if channel is enabled
    if(scopesettings.channel2.enable)
    {
      //Check if setting not already on max
      if(scopesettings.channel2.voltperdiv < 6)
      {
        //Original code has some limit on updating when the scope is not running on the time base setting or a previous stored volts per div setting
        //The latter maybe has to do with a stored wave that is being looked at
        //For now just allowing constant change within the max limit
        
        //Step up to the next setting. (Lowering the setting)
        scopesettings.channel2.voltperdiv++;
        
        //Show the change on the screen
        scope_channel2_settings(0);
        
        //Only update the FPGA in normal view mode
        if(scopesettings.waveviewmode == 0)
        {
          //Set the volts per div for this channel
          fpga_set_channel2_voltperdiv();
          
          //Need a ms timed delay
        }
      }
    }
/*
    if (*pcVar5[0x0C] != '\0') //Channel enable
    {
      bVar2 = pcVar5[0x3a];   //Scope run mode
      bVar26 = bVar2 != 0;

      if (bVar26)
      {
        bVar2 = pcVar5[10];   //Time base
      }

      if (((!bVar26 || 8 < bVar2) && ((byte)pcVar5[0xf] < 6)) && ((pcVar5[0x3a] == '\0' || (((ushort)(byte)pcVar5[0xf] <= *(ushort *)puVar7 || (((ushort)(byte)pcVar5[0xf] - *(ushort *)puVar7 & 0xff) < 2))))))
      {
        pcVar5[0x0F] = pcVar5[0x0F] + '\x01';  //Add one to the volt/div setting
        display_ch2_settings(0);         //Display the result

        if (pcVar5[0x43] == '\0')        //View mode normal
        {
          FUN_800095e8();                //Set volts div in FPGA
          FUN_800096b8();                //Also some FPGA control (0x32, so the offset??)
          delay_2(0x3c);                 //Give it some time to settle
        }
      }
    }
*/
  }
  //Check if channel 2 V- button is touched
  else if((ytouch >= 343) && (ytouch <= 403))
  {
    //Highlight the button if touched
    scope_ch2_sensitivity_control(1,1);

    //Wait until touch is released
    while(havetouch)
    {
      //Read the touch panel status
      tp_i2c_read_status();
    }

    //Button back to inactive state
    scope_ch2_sensitivity_control(1,0);
    
    //Only if channel is enabled
    if(scopesettings.channel2.enable)
    {
      //Check if setting not already on min
      if(scopesettings.channel2.voltperdiv > 0)
      {
        //Original code has some limit on updating when the scope is not running on the time base setting or a previous stored volts per div setting
        //The latter maybe has to do with a stored wave that is being looked at
        //For now just allowing constant change within the max limit
        
        //Step down to the next setting. (Increasing the setting)
        scopesettings.channel2.voltperdiv--;
        
        //Show the change on the screen
        scope_channel2_settings(0);
        
        //Only update the FPGA in normal view mode
        if(scopesettings.waveviewmode == 0)
        {
          //Set the volts per div for this channel
          fpga_set_channel2_voltperdiv();
          
          //Need a ms timed delay
        }
      }
    }
/*
    if (*pcVar5[0x0C] != '\0') //Channel enable
    {
      bVar2 = pcVar5[0x3a];   //Scope run mode
      bVar26 = bVar2 != 0;

      if (bVar26)
      {
        bVar2 = pcVar5[10];   //Time base
      }

      if (((!bVar26 || 8 < bVar2) && (pcVar5[0xf] != '\0')) && ((pcVar5[0x3a] == '\0' || ((*(ushort *)puVar7 <= (ushort)(byte)pcVar5[0xf] || ((*(ushort *)puVar7 - (ushort)(byte)pcVar5[0xf] & 0xff) < 2))))))
      {
        pcVar5[0xF] = pcVar5[0x0F] - '\x01';  //Take one of the volt/div setting
        display_ch1_settings(0);         //Display the result

        if (pcVar5[0x43] == '\0')        //View mode normal
        {
          FUN_800095e8();                //Set volts div in FPGA
          FUN_800096b8();                //Also some FPGA control (0x32, so the offset??)
          delay_2(0x3c);                 //Give it some time to settle
        }
      }
    }
*/
  }
  //Check if 50% trigger of show grid button is touched
  else if((ytouch >= 423) && (ytouch <= 477))
  {
    //Check on wave view state for which button is shown
    if(scopesettings.waveviewmode == 0)
    {
      //50% trigger so highlight that button if touched
      scope_50_percent_trigger_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_50_percent_trigger_button(0);
/*
      //This needs to be done for 50% trigger
      if (pcVar5[0x3a] == '\0')  //Run mode
      {
        FUN_80029314();
      }
*/
    }
    else
    {
      //Show grid so highlight that button if touched
      scope_show_grid_button(1);

      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }

      //Button back to inactive state
      scope_show_grid_button(0);
/*
      //This needs to be done for show grid    
      if (*(char *)(DAT_8002030c + 3) == '\x14')
      {
        *(undefined *)(DAT_8002030c + 3) = 0;
      }
      else
      {
        *(undefined *)(DAT_8002030c + 3) = 0x14;
      }
*/
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

const TOUCHCOORDS measures_item_touch_coords[2][12] =
{
  {
    //Channel 1 coordinates are on the right
    {482, 543, 289, 349}, {545, 605, 289, 349}, {607, 667, 289, 349}, {669, 729, 289, 349},
    {482, 543, 351, 411}, {545, 605, 351, 411}, {607, 667, 351, 411}, {669, 729, 351, 411},
    {482, 543, 413, 476}, {545, 605, 413, 476}, {607, 667, 413, 476}, {669, 729, 413, 476},
  },
  {
    //CHhannel 2 coordinates are on the left
    {232, 293, 289, 349}, {295, 355, 289, 349}, {357, 417, 289, 349}, {418, 480, 289, 349},
    {232, 293, 351, 411}, {295, 355, 351, 411}, {357, 417, 351, 411}, {418, 480, 351, 411},
    {232, 293, 413, 476}, {295, 355, 413, 476}, {357, 417, 413, 476}, {418, 480, 413, 476},
  }
};

//----------------------------------------------------------------------------------------------------------------------------------

void handle_measures_menu_touch(void)
{
  int channel;
  int item;
  int found;
  
  //Stay in the menu as long as there is no touch outside the menu  
  while(1)
  {
    //Scan the touch panel for touch
    tp_i2c_read_status();
    
    //Check if there is touch
    if(havetouch)
    {
      //Check if touch within the menu field
      if((xtouch >= 231) && (xtouch <= 730) && (ytouch >= 264) && (ytouch <= 477))
      {
        found = 0;
        channel = 0;

        //Check the touch positions for the separate items until one is found
        while((found == 0) && (channel < 2))
        {
          item = 0;
          
          //For each channel 12 items
          while((found == 0) && (item<12))
          {
            //Check if touch is on this item
            if((xtouch >= measures_item_touch_coords[channel][item].x1) && (xtouch <= measures_item_touch_coords[channel][item].x2) &&
               (ytouch >= measures_item_touch_coords[channel][item].y1) && (ytouch <= measures_item_touch_coords[channel][item].y2))
            {
              //Toggle the item
              scopesettings.measuresstate[channel][item] ^= 1;

              //There is an array for showing the items on screen. It works on a first come first serve system.
              //It looks for the first free spot and inserts itself there. This gives a messy image of the two channels interleaving with settings
              //On disable the list is shifted to fill the gap
              //For this an items in list counter might be useful
              
              //A nicer setup is to reserve separate sections per channel on the screen for the enabled items and always show them in a fixed
              //order. Makes reading them easier
              
              
              //Draw the changed item
              scope_measures_menu_item(channel, item);
              
              //Signal item found
              found = 1;
            }
            
            //Next item
            item++;
          }
          
          //Next channel
          channel++;
        }
        
        //Wait until touch is released before checking on a new position
        while(havetouch)
        {
          //Scan the touch panel for touch
          tp_i2c_read_status();
        }
      }
      else
      {
        //Touch outside the menu so quit
        return;
      }
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void close_open_sub_menus(void)
{
  //Only one of these menu's will be opened at any time
  
  //Check if the screen brightness slider is open
  if(screenbrightnessopen)
  {
    //Set the button inactive
    scope_system_settings_screen_brightness_item(0);

    //Restore the screen under the screen brightness slider
    display_set_source_buffer(displaybuffer2);
    display_copy_rect_to_screen(395, 46, 331, 58);

    //Signal it is closed
    screenbrightnessopen = 0;
  }
  //Check if the grid brightness slider is open
  else if(gridbrightnessopen)
  {
    //Set the button inactive
    scope_system_settings_grid_brightness_item(0);

    //Restore the screen under the grid brightness slider
    display_set_source_buffer(displaybuffer2);
    display_copy_rect_to_screen(395, 104, 331, 58);

    //Signal it is closed
    gridbrightnessopen = 0;
  }
  //Check if the calibration text is open
  else if(calibrationopen)
  {
    //Set the button inactive
    scope_system_settings_calibration_item(0);
    
    //Restore the screen under the calibration text
    display_set_source_buffer(displaybuffer2);
    display_copy_rect_to_screen(395, 222, 199, 59);

    //Signal it is closed
    calibrationopen = 0;
  }
}
