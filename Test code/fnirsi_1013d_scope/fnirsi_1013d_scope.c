//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "spi_control.h"
#include "display_control.h"
#include "fpga_control.h"
#include "touchpanel.h"

#include "fnirsi_1013d_scope.h"
#include "font_structs.h"
#include "display_lib.h"
#include "scope_functions.h"

#include "arm32.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 maindisplaybuffer[];

extern SCOPESETTINGS scopesettings;

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  //Initialize the clock system
  sys_clock_init();
  
	arm32_icache_enable();
	arm32_dcache_enable();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Turn of the display brightness
  set_backlight_brightness(0x0000);
  
  //sys_disable_display();
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, maindisplaybuffer);
  
  //Setup the display library for the scope hardware
  setup_display_lib();
  
  //Setup the touch panel interface
  tp_i2c_setup();
  
  scopesettings.rightmenustate = 0;
//  scopesettings.waveviewmode = 1;

//  scopesettings.runstate = 1;

  scopesettings.movespeed = 1;

  scopesettings.channel1.enable = 1;
  scopesettings.channel1.coupling = 0;
  scopesettings.channel1.magnification = 1;
  scopesettings.channel1.voltperdiv = 5;
  
  scopesettings.channel2.enable = 1;
  scopesettings.channel2.coupling = 1;
  scopesettings.channel2.magnification = 0;
  scopesettings.channel2.voltperdiv = 2;
  
  scopesettings.triggermode = 1;
  scopesettings.triggeredge = 1;
  scopesettings.triggerchannel = 1;
  
  scopesettings.batterychargelevel = 20;
  scopesettings.batterycharging = 1;
  
  //Analyze the original code to find the screen build up and other display functions
  
  
  //Setup the main parts of the screen
  setup_main_screen();
  
  //Set default brightness
  set_backlight_brightness(0xEA60);
  
  while(1)
  {
    
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
