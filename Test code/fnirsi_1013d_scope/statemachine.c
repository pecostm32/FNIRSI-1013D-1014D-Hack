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
  //CHeck on touch state
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
      //Handle the main button
    }
    //Check if in channel 1 settings button range
    else if((xtouch >= 161) && (xtouch <= 260))
    {
      //Set the button active
      display_channel1_settings(1);
      
      //Wait until touch is released
      while(havetouch)
      {
        //Read the touch panel status
        tp_i2c_read_status();
      }
      
      //Set the button inactive
      display_channel1_settings(0);
      
      //Save the screen rectangle where the menu will be displayed
      display_set_destination_buffer(displaybuffer2);
      display_copy_rect_from_screen(160, 45, 185, 254);
      
      //Go and setup the channel 1 menu
      display_open_channel1_menu();
      
      //Go and handle the menu touch
      handle_channel1_menu_touch();
      
      //Restore the screen when done
      display_set_source_buffer(displaybuffer2);
      display_copy_rect_to_screen(160, 45, 185, 254);
    }
    //Check if in channel 2 settings button range
    else if((xtouch >= 288) && (xtouch <= 387))
    {
      
    }
    //Check if in move speed button range
    else if((xtouch >= 493) && (xtouch <= 533))
    {
      
    }
    //Check if in trigger settings button range
    else if((xtouch >= 570) && (xtouch <= 700))
    {
      
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

void handle_channel1_menu_touch(void)
{
  //Scan the touch panel
  //When touch outside the menu quit
  //Else scan for the possible settings
  
  //When enable is set to off the menu select button needs to be made grey!!!
  //On change of settings this needs to be reflected too

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
            
            //Display this
            display_channel1_enable_select();
            display_channel1_settings(0);
          }
          //Check on disable
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Disable the channel
            scopesettings.channel1.enable = 0;
            
            //Display this
            display_channel1_enable_select();
            display_channel1_settings(0);
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
            display_channel1_fft_show();
          }
          //Check on disable
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Disable the channel
            scopesettings.channel1.fftenable = 0;
            
            //Display this
            display_channel1_fft_show();
          }
        }
        //Check on coupling DC or AD
        else if((ytouch >= 188) && (ytouch <= 210))
        {
          //Check on enable
          if((xtouch >= 239) && (xtouch <= 271))
          {
            //Enable the channel
            scopesettings.channel1.coupling = 0;
            
            //Display this
            display_channel1_coupling_select();
            display_channel1_settings(0);
          }
          //Check on disable
          else if((xtouch >= 291) && (xtouch <= 323))
          {
            //Disable the channel
            scopesettings.channel1.coupling = 1;
            
            //Display this
            display_channel1_coupling_select();
            display_channel1_settings(0);
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
            display_channel1_probe_magnification_select();
            display_channel1_settings(0);
          }
          //Check on 10x
          else if((xtouch >= 270) && (xtouch <= 293))
          {
            //Disable the channel
            scopesettings.channel1.magnification = 1;
            
            //Display this
            display_channel1_probe_magnification_select();
            display_channel1_settings(0);
          }
          //Check on 100x
          else if((xtouch >= 299) && (xtouch <= 329))
          {
            //Disable the channel
            scopesettings.channel1.magnification = 2;
            
            //Display this
            display_channel1_probe_magnification_select();
            display_channel1_settings(0);
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
