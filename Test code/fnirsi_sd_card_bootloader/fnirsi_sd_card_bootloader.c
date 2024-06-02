//----------------------------------------------------------------------------------------------------------------------------------

#include "arm32.h"
#include "ccu_control.h"
#include "dram_control.h"
#include "display_control.h"
#include "bl_display_lib.h"
#include "bl_fpga_control.h"
#include "bl_sd_card_interface.h"
#include "bl_variables.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------
// This code now works but needs a debug flag to disable the displaying of information
//
// For the 1014D a new version that only loads the main code without showing messages and does not wait for the FPGA
// can be distilled and tested.
//
// There is a problem with the SD card code though when used with a specific 4GB card. Could be a speed issue
//----------------------------------------------------------------------------------------------------------------------------------
// The bootloader itself starts on sector 16, so in the package the firmware should be copied in from address 0x8000
//  to allow for 32KB boot loader
//----------------------------------------------------------------------------------------------------------------------------------

#define PROGRAM_START_SECTOR      80

//----------------------------------------------------------------------------------------------------------------------------------

//Buffer for reading header from SD card
unsigned char buffer[512];

uint32 ypos = 5;

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  unsigned int length;
  unsigned int blocks;
  int i,j, retval;
  
  //Initialize the clock system
  sys_clock_init();
  
  //Initialize the internal DRAM
  sys_dram_init();

  //Instead of full memory management just the caches enabled
  arm32_icache_enable();
  arm32_dcache_enable();

  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, (uint16 *)maindisplaybuffer);
  
  //Setup the display lib
  display_set_screen_buffer((uint16 *)maindisplaybuffer);
  display_set_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);
  
  //Try a setup where the program code is loaded immediately and the FPGA check is done after that
  //Might speed things up even further
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Got some time to spare
  for(j=0;j<1000;j++)
  {
    //At 600MHz CPU_CLK 1000 = ~200uS
    for(i=0;i<1000;i++);
  }
  
  //Wait and make sure FPGA is ready
  fpga_check_ready();

  //Turn of the display brightness
  fpga_set_backlight_brightness(0x78);
  
  //Setup for error message display
  display_set_fg_color(0x00FFFFFF);
  display_set_font(&font_0);
  
  //Initialize the SD card
  if(sd_card_init() != SD_OK)
  {
    display_set_fg_color(0x00FF0000);
    display_text(10, ypos, "SD card init failed");

    //On error just frees
    while(1);
  }

  display_text(10, ypos, "SD card OK");
  ypos += 16;
  
  //Load the first program sector from the SD card
  if(sd_card_read(PROGRAM_START_SECTOR, 1, buffer) != SD_OK)
  {
    display_set_fg_color(0x00FF0000);
    display_text(10, ypos, "SD card first read failed");
    
    //On error just frees
    while(1);
  }

  display_text(10, ypos, "First sector read OK");
  ypos += 16;

  //Check if there is a brom header there
  if(memcmp(&buffer[4], "eGON.EXE", 8) != 0)
  {
    display_set_fg_color(0x00FF0000);
    display_text(10, ypos, "Not an executable");
    
    //On error just frees
    while(1);
  }

  display_text(10, ypos, "Program found");
  ypos += 16;
  
  //Get the length from the header
  length = ((buffer[19] << 24) | (buffer[18] << 16) | (buffer[17] << 8) | buffer[16]);
  
  //Calculate the number of sectors to read
  blocks = (length + 511) / 512;

  display_text(10, ypos, "Number of blocks:");
  display_decimal(150, ypos, blocks);
  ypos += 16;
  
  //Copy the first program bytes to DRAM (So the eGON header is skipped)
  memcpy((void *)0x80000000, &buffer[32], 480);
  
  //Check if more data needs to be read
  if(blocks > 1)
  {
    //Already read the first block
    blocks--;
    
    //Load the remainder of the program from the SD card
    if((retval = sd_card_read(PROGRAM_START_SECTOR + 1, blocks, (void *)0x800001E0)) != SD_OK)
    {
      display_set_fg_color(0x00FF0000);
      display_text(10, ypos, "Failed reading program sector");
      ypos += 16;
      display_decimal(10, ypos, retval);
      ypos += 16;
      display_decimal(10, ypos, blocks);
      
      
      //On error just frees
      while(1);
    }
  }
 
  //Run the main program
  unsigned int address = 0x80000000;

  __asm__ __volatile__ ("mov pc, %0\n" :"=r"(address):"0"(address));
}
