//----------------------------------------------------------------------------------------------------------------------------------

#include "ccu_control.h"
#include "spi_control.h"
#include "display_control.h"
#include "fpga_control.h"

#include "types.h"
#include "font_structs.h"
#include "display_lib.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern FONTDATA font_0;
extern FONTDATA font_2;

DISPLAYDATA displaydata;

//----------------------------------------------------------------------------------------------------------------------------------

//Need a scope data structure holding the settings


//Need to trace more of the startup code

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
  sys_init_display(800, 480, 0x803849A0);
  
  //Analyze the original code to find the screen build up and other display functions
  
  //CH1 menu header  on color  0x00FFFF00
  //CH1 menu header  off color 0x00444444
  
  //CH2 menu header  on color  0x0000FFFF
  //CH2 menu header  off color 0x00444444
  
  
  display_set_bg_color(&displaydata, 0x00000000);
  display_set_screen_buffer(&displaydata, (uint16 *)0x803849A0);

  
//  display_set_font(&displaydata, &font_0);
//  display_set_fg_color(&displaydata, 0x00942367);
//  display_text(&displaydata, 150, 70, "This is font_0 which is fixed width");

  display_set_fg_color(&displaydata, 0x00333333);
  display_fill_rect(&displaydata, 0, 0, 800, 50);
  
 
  display_set_fg_color(&displaydata, 0x00444444);
  display_fill_rect(&displaydata, 0, 50, 800, 50);

//  display_fill_rect(&displaydata, 0, 0, 800, 46);
//  display_fill_rect(&displaydata, 0, 478, 800, 2);

  
//  display_fill_rect(&displaydata, 0, 0, 1, 480);
//  display_fill_rect(&displaydata, 727, 0, 73, 480);

//  display_set_font(&displaydata, &font_2);
//  display_set_fg_color(&displaydata, 0x00B4FFFE);
//  display_text(&displaydata, 20, 20, "This is a test with font_2");
  
//  display_set_fg_color(&displaydata, 0x00D3374A);
//  display_fill_rect(&displaydata, 320, 270, 160, 60);
  
  //Set default brightness
  set_backlight_brightness(0xEA60);
  
  while(1);
}

//----------------------------------------------------------------------------------------------------------------------------------
