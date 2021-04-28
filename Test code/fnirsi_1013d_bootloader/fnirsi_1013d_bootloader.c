#include "ccu_control.h"
#include "dram_control.h"
#include "spi_control.h"
#include "display_control.h"
#include "fpga_control.h"

int main(void)
{
  //Buffer for reading header from flash
  unsigned char buffer[32];
  unsigned int length;
  unsigned short xsize;
  unsigned short ysize;
  unsigned short xpos;
  unsigned short ypos;
  int i,j;
  
  //Initialize the clock system
  sys_clock_init();
  
  //Initialize the internal DRAM
  sys_dram_init();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(800, 480, 0x81B00000);
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Load bitmap from flash
  //Get the header first
  sys_spi_flash_read(0x13000, buffer, 32);

  //Get the length from the header and take of the header plus an extra 8 bytes
  length = ((buffer[19] << 24) | (buffer[18] << 16) | (buffer[17] << 8) | buffer[16]) - 40;
  
  //Get the x and y sizes from the flash header
  xsize = (buffer[27] << 8) | buffer[26];
  ysize = (buffer[29] << 8) | buffer[28];
  
  //Center it on the display
  xpos = (800 - xsize) >> 1;
  ypos = (480 - ysize) >> 1;

  //Read the bitmap into DRAM. Skip an extra 8 bytes after the header
  sys_spi_flash_read(0x13028, (unsigned char *)0x81000000, length);
  
  //Display the bitmap
  display_bitmap(xpos, ypos, xsize, ysize, (unsigned short *)0x81000000, (unsigned short *)0x81B00000);
  
  //Got some 200mS to spare
  for(j=0;j<950;j++)
  {
    //At 600MHz CPU_CLK 1000 = ~200uS
    for(i=0;i<1000;i++);
  }
  
  //Wait and make sure FPGA is ready
  check_fpga_ready();
  
  //Set default brightness
  set_backlight_brightness(0xEA60);
  
  //Load the main program from flash
  //Get the header first
  sys_spi_flash_read(0x27000, buffer, 32);

  //Get the length from the header and take of the header
  length = ((buffer[19] << 24) | (buffer[18] << 16) | (buffer[17] << 8) | buffer[16]) - 32;

  //Read the main program into DRAM. 
  sys_spi_flash_read(0x27020, (unsigned char *)0x80000000, length);
  
  //Run the main program
  __asm__ __volatile__ ("mov pc, #0x80000000\n");  
  
  while(1);
}
