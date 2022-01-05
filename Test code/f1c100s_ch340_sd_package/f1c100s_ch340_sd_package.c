//----------------------------------------------------------------------------------------------------------------------------------

#include "arm32.h"
#include "ccu_control.h"
#include "dram_control.h"
#include "bl_sd_card_interface.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------
//
//This bootloader is less then 16KB.
//  The startup screen program can there for be on the SD at sector 48
//
//----------------------------------------------------------------------------------------------------------------------------------

#define PROGRAM_START_SECTOR      48

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  //Buffer for reading sector from sd card
  unsigned char buffer[512];
  unsigned int length;
  unsigned int blocks;
  
  //Initialize the clock system
  sys_clock_init();
  
  //Initialize the internal DRAM
  sys_dram_init();

  //Instead of full memory management just the caches enabled
  arm32_icache_enable();
  arm32_dcache_enable();
  
  //Initialize the SD card
  if(sd_card_init() != SD_OK)
  {
    //On error just frees
    while(1);
  }
  
  //Load the first program sector from the SD card
  if(sd_card_read(PROGRAM_START_SECTOR, 1, buffer) != SD_OK)
  {
    //On error just frees
    while(1);
  }

  //Check if there is a brom header there
  if(memcmp(&buffer[4], "eGON.EXE", 8) != 0)
  {
    //On error just frees
    while(1);
  }
  
  //Get the length from the header
  length = ((buffer[19] << 24) | (buffer[18] << 16) | (buffer[17] << 8) | buffer[16]);
  
  //Calculate the number of sectors to read
  blocks = (length + 511) / 512;
  
  //Copy the first bytes to DRAM
  memcpy((void *)0x80000000, &buffer[32], 480);
  
  //Check if more data needs to be read
  if(blocks > 1)
  {
    //Already read the first block
    blocks--;
    
    //Load the remainder of the program from the SD card
    if(sd_card_read(PROGRAM_START_SECTOR + 1, blocks, (void *)0x800001E0) != SD_OK)
    {
      //On error just frees
      while(1);
    }
  }
 
  //Run the startup screen program
  unsigned int address = 0x80000000;

  __asm__ __volatile__ ("mov pc, %0\n" :"=r"(address):"0"(address));
}
