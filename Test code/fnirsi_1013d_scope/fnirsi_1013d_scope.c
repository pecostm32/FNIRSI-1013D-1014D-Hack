//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "spi_control.h"
#include "display_control.h"
#include "fpga_control.h"
#include "touchpanel.h"

#include "fnirsi_1013d_scope.h"
#include "display_lib.h"
#include "scope_functions.h"
#include "statemachine.h"

#include "arm32.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern uint8  havetouch;
extern uint16 xtouch;
extern uint16 ytouch;

extern uint8 touchstate;

extern uint8 systemsettingsmenuopen;
extern uint8 screenbrightnessopen;
extern uint8 gridbrightnessopen;
extern uint8 calibrationopen;

extern uint16 maindisplaybuffer[];

extern SCOPESETTINGS scopesettings;

//extern FONTDATA font_0;

//----------------------------------------------------------------------------------------------------------------------------------

int8 printhexnibble(uint8 nibble)
{
  //Check if needs to be converted to A-F character
  if(nibble > 9)
  {
    //To make alpha add 55. (55 = 'A' - 10)
    nibble += 55;
  }
  else
  {
    //To make digit add '0'
    nibble += '0';
  }

  return(nibble);
}

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  //Initialize the clock system
  sys_clock_init();
  
  //Instead of full memory management just the caches enabled
  arm32_icache_enable();
  arm32_dcache_enable();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Turn of the display brightness
  fpga_set_backlight_brightness(0x0000);
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, maindisplaybuffer);
  
  //Setup the display library for the scope hardware
  scope_setup_display_lib();
  
  //Initialize some variables for now
  systemsettingsmenuopen = 0;
  screenbrightnessopen = 0;
  gridbrightnessopen = 0;
  calibrationopen = 0;
  
  touchstate = 0;
  havetouch = 0;
  xtouch = 0;
  ytouch = 0;

  //Setup the touch panel interface
  tp_i2c_setup();
  
  scopesettings.rightmenustate = 0;
  scopesettings.waveviewmode = 1;

  scopesettings.runstate = 0;

  scopesettings.movespeed = 1;

  scopesettings.channel1.enable = 1;
  scopesettings.channel1.coupling = 0;
  scopesettings.channel1.magnification = 2;
  scopesettings.channel1.voltperdiv = 5;
  scopesettings.channel1.fftenable = 0;
  
  scopesettings.channel2.enable = 1;
  scopesettings.channel2.coupling = 1;
  scopesettings.channel2.magnification = 0;
  scopesettings.channel2.voltperdiv = 2;
  scopesettings.channel2.fftenable = 0;
  
  scopesettings.triggermode = 1;
  scopesettings.triggeredge = 1;
  scopesettings.triggerchannel = 1;
  
  scopesettings.timeperdiv = 5;
  
  scopesettings.batterychargelevel = 20;
  scopesettings.batterycharging = 1;
  
  scopesettings.screenbrightness = 67;
  scopesettings.gridbrightness = 45;
  scopesettings.alwaystrigger50 = 1;
  scopesettings.xymodedisplay = 0;
  
  int channel;
  int item;
  
  for(channel=0;channel<2;channel++)
  {
    //For each channel 12 items
    for(item=0;item<12;item++)
    {
      scopesettings.measuresstate[channel][item] = 0;
    }
  }
  
  scopesettings.measuresstate[0][4] = 1;
  scopesettings.measuresstate[0][7] = 1;

  scopesettings.measuresstate[1][2] = 1;
  scopesettings.measuresstate[1][10] = 1;
  
  //Analyze the original code to find the screen build up and other display functions
  
  
  fpga_init_parameter_ic();
  
  
  //Setup the main parts of the screen
  scope_setup_main_screen();
    
  //Set screen brightness
  fpga_set_translated_brightness(scopesettings.screenbrightness);
  
//  int8 buffer[20];
  
  while(1)
  {
/*
    //Check the touch panel status
    tp_i2c_read_status();
    
    display_set_fg_color(0x00000000);

    display_fill_rect(10, 50, 100, 60);

    display_set_fg_color(0x00FFFFFF);

    buffer[0] = '0';
    buffer[1] = 'x';
    buffer[2] = printhexnibble((xtouch >> 12) & 0x0F);
    buffer[3] = printhexnibble((xtouch >>  8) & 0x0F);
    buffer[4] = printhexnibble((xtouch >>  4) & 0x0F);
    buffer[5] = printhexnibble( xtouch        & 0x0F);
    buffer[6] = 0;
      
    display_set_font(&font_0);
    display_text(10, 50, buffer);
    
    buffer[2] = printhexnibble((ytouch >> 12) & 0x0F);
    buffer[3] = printhexnibble((ytouch >>  8) & 0x0F);
    buffer[4] = printhexnibble((ytouch >>  4) & 0x0F);
    buffer[5] = printhexnibble( ytouch        & 0x0F);
    
    display_text(10, 70, buffer);
*/
    
    touch_handler();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
