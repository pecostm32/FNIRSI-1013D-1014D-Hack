//----------------------------------------------------------------------------------------------------------------------------------

//Scan the touch panel

//Main state is displaying the scope data

//On touch the first action is to see where the touch is, so an array of boxes might be needed
//Difficulty lies in when a trace of cursor is selected.

//----------------------------------------------------------------------------------------------------------------------------------

#include "statemachine.h"
#include "touchpanel.h"
#include "scope_functions.h"
#include "display_lib.h"
#include "fnirsi_1013d_scope.h"

//----------------------------------------------------------------------------------------------------------------------------------

uint8 touchstate;

extern SCOPESETTINGS scopesettings;

extern uint8  havetouch;
extern uint16 xtouch;
extern uint16 ytouch;

extern uint16 maindisplaybuffer[];
extern uint16 displaybuffer1[];
extern uint16 displaybuffer2[];

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

        //Set the button inactive
        scope_main_return_button(0);

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
    //Right menu bar, so handle that
    
  }
  else
  {
    //Main screen part, so handle that
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void handle_main_menu_touch(void)
{
  int systemsettingsmenuopen = 0;
  int screenbrightnessopen = 0;
  int gridbrightnessopen = 0;
  int calibrationopen = 0;
  
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
          
          //Set the button inactive
          scope_main_menu_picture_view(0);
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
          
          //Set the button inactive
          scope_main_menu_waveform_view(0);
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
          
          //Set the button inactive
          scope_main_menu_usb_connection(0);
        }
      }
      //Check on system settings menu opened and being touched
      else if(systemsettingsmenuopen && (xtouch >= 150) && (xtouch <= 394) && (ytouch >= 46) && (ytouch <= 340))
      {
        //Check if on screen brightness
        if((ytouch >= 46) && (ytouch <= 105))
        {
          //Check if already open
          if(screenbrightnessopen == 0)
          {
            //Set the button active
            scope_system_settings_screen_brightness_item(1);

            //Wait until touch is released
            while(havetouch)
            {
              //Read the touch panel status
              tp_i2c_read_status();
            }

            //Check if the grid brightness slider is open
            if(gridbrightnessopen)
            {
              //Restore the screen under the grid brightness slider
              display_set_source_buffer(displaybuffer2);
              display_copy_rect_to_screen(394, 105, 331, 58);  //!!!!!!!!!!!! mod coords here
              
              //Signal it is closed
              gridbrightnessopen = 0;
            }
            //Check if the calibration text is open
            else if(calibrationopen)
            {
              //Restore the screen under the calibration text
              display_set_source_buffer(displaybuffer2);
              display_copy_rect_to_screen(394, 46, 244, 294);  //!!!!!!!!!!!! mod coords here
              
              //Signal it is closed
              calibrationopen = 0;
            }
            
            //Show the screen brightness slider
            scope_open_slider(394, 46, scopesettings.screenbrightness);
            
            //Signal the screen brightness slider is opened
            screenbrightnessopen = 1;
          }
        }
        
        
        
        
        
        
        
        
      }
      //Add handling for the brightness here
      
      
      else
      {
        //Check if system settings menu has been opened
        if(systemsettingsmenuopen)
        {
          //Restore the screen under the system settings menu when done
          display_set_source_buffer(displaybuffer2);
          display_copy_rect_to_screen(150, 46, 244, 294);
        }
        
        //!!!!!!!!!!!!!!!!!!!!!! ADD the screen restore code here when the coords are known!!!!!!!!!!!!!!!!
        
        
        
        //Touch outside the menu so quit
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
            
            //Need to call some function here
            //FUN_80002790
            
            //Display this
            scope_channel1_enable_select();
            scope_channel1_settings(0);
          }
          //Check on disable
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Disable the channel
            scopesettings.channel1.enable = 0;

            //Need to call some function here
            //FUN_80002790    //Check on trigger channel and write it to the fpga
                              //Only needed on disable, because it does not remember the prev setting
            
            //Reset the volts/div setting to max
            scopesettings.channel1.voltperdiv = 0;

            //Need to call some function here
            //FUN_8000689c    //Set volts per div in the fpga
            
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
            
            //Need to call some function here
            //FUN_800068d4  //set_channel1_fpga_coupling
            
            //Display this
            scope_channel1_coupling_select();
            scope_channel1_settings(0);
          }
          //Check on AC coupling
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Set the channel to AC coupling
            scopesettings.channel1.coupling = 1;

            //Need to call some function here
            //FUN_800068d4
            
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
            
            //Need to call some function here
            //FUN_80002790
            
            //Display this
            scope_channel2_enable_select();
            scope_channel2_settings(0);
          }
          //Check on disable
          else if((xtouch >= 418) && (xtouch <= 450))
          {
            //Disable the channel
            scopesettings.channel2.enable = 0;

            //Need to call some function here
            //FUN_80002790    //Check on trigger channel and write it to the fpga
                              //Only needed on disable, because it does not remember the prev setting
            
            //Reset the volts/div setting to max
            scopesettings.channel2.voltperdiv = 0;

            //Need to call some function here
            //FUN_8000689c    //Set volts per div in the fpga
            
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
            
            //Need to call some function here
            //FUN_800068d4  //set_channel2_fpga_coupling
            
            //Display this
            scope_channel2_coupling_select();
            scope_channel2_settings(0);
          }
          //Check on AC coupling
          else if((xtouch >= 418) && (xtouch <= 450))
          {
            //Set the channel to AC coupling
            scopesettings.channel2.coupling = 1;

            //Need to call some function here
            //FUN_800068d4
            
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
            //Enable the channel
            scopesettings.triggeredge = 0;
            
            //Need to call some function here
            
            //Display this
            scope_trigger_edge_select();
            scope_trigger_settings(0);
          }
          //Check on falling
          else if((xtouch >= 671) && (xtouch <= 716))
          {
            //Enable the channel
            scopesettings.triggeredge = 1;
            
            //Need to call some function here
            
            //Display this
            scope_trigger_edge_select();
            scope_trigger_settings(0);
          }
        }
        //Check on trigger channel
        else if((ytouch >= 188) && (ytouch <= 210))
        {
          //Check on DC coupling
          if((xtouch >= 632) && (xtouch <= 664))
          {
            //Set the channel 1 as trigger source
            scopesettings.triggerchannel = 0;
            
            //Need to call some function here
            
            //Display this
            scope_trigger_channel_select();
            scope_trigger_settings(0);
          }
          //Check on AC coupling
          else if((xtouch >= 680) && (xtouch <= 712))
          {
            //Set channel 2 as trigger source
            scopesettings.triggerchannel = 1;

            //Need to call some function here
            
            //Display this
            scope_trigger_channel_select();
            scope_trigger_settings(0);
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
