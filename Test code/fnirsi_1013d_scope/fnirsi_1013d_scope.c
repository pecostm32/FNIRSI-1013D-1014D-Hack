//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "spi_control.h"
#include "display_control.h"
#include "fpga_control.h"

#include "fnirsi_1013d_scope.h"
#include "font_structs.h"
#include "display_lib.h"
#include "scope_functions.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern uint16 maindisplaybuffer[];

extern SCOPESETTINGS scopesettings;

//----------------------------------------------------------------------------------------------------------------------------------


int main(void)
{
  //Initialize the clock system
  sys_clock_init();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Turn of the display brightness
  set_backlight_brightness(0x0000);
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, maindisplaybuffer);
  
  //Setup the display library for the scope hardware
  setup_display_lib();
  
//  scopesettings.rightmenustate = 1;
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
  
  //Analyze the original code to find the screen build up and other display functions
  
  //CH1 menu header  on color  0x00FFFF00
  //CH1 menu header  off color 0x00444444
  
  //CH2 menu header  on color  0x0000FFFF
  //CH2 menu header  off color 0x00444444
  
  
  
//  display_set_font(&font_0);
//  display_set_fg_color(0x00942367);
//  display_text(150, 70, "This is font_0 which is fixed width");

//  display_set_fg_color(0x00333333);
//  display_fill_rounded_rect(30, 30, 80, 80, 2);
  
//  display_set_fg_color(0x00444444);
//  display_draw_rounded_rect(30, 30, 80, 80, 2);
  
 

//  display_fill_rect(0, 0, 800, 46);
//  display_fill_rect(0, 478, 800, 2);

  
//  display_fill_rect(0, 0, 1, 480);
//  display_fill_rect(727, 0, 73, 480);

//  display_set_font(&font_2);
//  display_set_fg_color(0x00B4FFFE);
//  display_text(20, 20, "This is a test with font_2");
  
//  display_set_fg_color(0x00D3374A);
//  display_fill_rect(320, 270, 160, 60);
  
  //Setup the main parts of the screen
  setup_main_screen();
  
  //Set default brightness
  set_backlight_brightness(0xEA60);
  
  while(1);
}

//----------------------------------------------------------------------------------------------------------------------------------
