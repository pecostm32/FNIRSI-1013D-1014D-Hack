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

//Need to figure out how to instruct the linker to get the total size of program plus data


int main(void)
{
  //Initialize the clock system
  sys_clock_init();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(800, 480, 0x803849A0);
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  
  display_set_font(&displaydata, &font_2);
  display_set_fg_color(&displaydata, 0x00B4FFFE);
  display_set_bg_color(&displaydata, 0x00000000);
  display_set_screen_buffer(&displaydata, (uint16 *)0x803849A0);
  
  display_text(&displaydata, 20, 20, "This is a test");

  display_set_font(&displaydata, &font_0);
  display_set_fg_color(&displaydata, 0x00942367);

  display_text(&displaydata, 150, 70, "This is font_0 which is fixed width");

  
  display_set_fg_color(&displaydata, 0x0023377A);
  display_fill_rect(&displaydata, 300, 250, 200, 100);
  
  while(1);
}

//----------------------------------------------------------------------------------------------------------------------------------
