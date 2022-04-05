//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "fwb_spi_control.h"
#include "timer.h"
#include "interrupt.h"
#include "display_control.h"
#include "fwb_fpga_control.h"

#include "fnirsi_1014d_firmware_backup.h"
#include "fwb_display_lib.h"
#include "sin_cos_math.h"

#include "sd_card_interface.h"
#include "ff.h"

#include "fwb_usb_interface.h"

#include "arm32.h"

#include "fwb_variables.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

extern IRQHANDLERFUNCION interrupthandlers[];

FIL fp;

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  int32  status;
  uint8  jedecid[3];
  
  //Default assume 2MB flash so use 128 x 16KB blocks to copy to SD card
  uint32 blocksize = 16384;
  
  //Initialize data in BSS section
  memset(&BSS_START, 0, &BSS_END - &BSS_START);
  
  //Initialize the clock system
  sys_clock_init();
  
  //Instead of full memory management just the caches enabled
  arm32_icache_enable();
  arm32_dcache_enable();
  
  //Clear the interrupt variables
  memset(interrupthandlers, 0, 256);
  
  //Setup timer interrupt
  timer0_setup();
  
  //Enable interrupts only once. In the original code it is done on more then one location.
  arm32_interrupt_enable();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Turn of the display brightness
  fpga_set_backlight_brightness(0x0000);
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, (uint16 *)maindisplaybuffer);
  
  //Setup the display library for the scope hardware
  setup_display_lib();

  //Setup and check SD card on file system being present
  if(f_mount(&fs, "0", 1))
  {
    //Show SD card error message on failure
    //Set max screen brightness
    fpga_set_backlight_brightness(0xEA60);

    //Clear the display
    display_set_fg_color(0x00000000);
    display_fill_rect(0, 0, 800, 480);

    //Display the message in red
    display_set_fg_color(0x00FF0000);
    display_set_font(&font_5);
    display_text(30, 50, "SD ERROR");
    
    //On error just hang
    while(1);
  }

  //Setup the USB interface
  usb_device_init();
  
  //Display the startup screen  
  fpga_set_backlight_brightness(0xEA60);
  draw_startup_screen();

  //Text in light blue
  display_set_fg_color(0x00B4FFFE);
  display_set_font(&font_5);
  
  //Read the manufacturer id and device id
  sys_spi_flash_get_info(jedecid, 3);

  //Display the FLASH info
  display_text(20, 280, "FLASH information");
  display_text(20, 300, "Manufacturer ID: ");
  display_hex(200, 300, 2, jedecid[0]);
  display_text(20, 320, "Product ID: ");
  display_hex(200, 320, 4, (jedecid[1] << 8) | jedecid[2]);

  //Check if flash is 4MB (Only for ST and WINBOND determined on these values. For the others 2MB is used)
  if(((jedecid[0] == 0x20) || (jedecid[0] == 0xEF)) && (jedecid[2] == 0x16))
  {
    blocksize = 32768;
  }

  //Backup the full flash to the SD card
  status = save_full_flash_data(348, blocksize);

  //Check if the full flash backup succeeded
  if(status == 0)
  {
    //Write the firmware backup to the SD card
    status = save_firmware_data(388);
  }
  
  //Clear a sector worth of data
  memset(massstoragedata, 0, 512);
  
  //Remove the brom boot sector
  if(sd_card_write(16, 1, (uint8 *)massstoragedata) != SD_OK)
  {
    //Display special touch panel text in red
    display_set_fg_color(0x00FF0000);
    display_text(20, 440, "FAILED TO CLEAR SD SECTOR 16 (BROM BOOT)");
    
    status = -1;
  }
  
  //Inform the user done without error
  if(status == 0)
  {
    display_text(20, 440, "DONE WITH BACKUP, COPY FILES TO COMPUTER");
  }
  
  //Wait half a second to allow the SD card to be ready with writing
  timer0_delay(500);
  
  //Enable scope for mass storage connection, so user can copy the files
  usb_device_enable();

  //Just wait until switched off
  while(1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void setup_display_lib(void)
{
  display_set_bg_color(0x00000000);
  
  display_set_screen_buffer((uint16 *)maindisplaybuffer);
  
  display_set_dimensions(SCREEN_WIDTH, SCREEN_HEIGHT);
}

//----------------------------------------------------------------------------------------------------------------------------------

void draw_startup_screen(void)
{
  //Fill the background
  display_set_fg_color(0x00307850);
  display_fill_rect(0, 0, 800, 480);

  //Gradient for the text
  display_set_fg_y_gradient(gradientbuffer, 20, 130, 0x00FF6060, 0x00CC0000);
  
  //Draw the top line of text
  display_copy_icon_fg_color_y_gradient(letter_p_icon, 157, 20,  82, 110);
  display_copy_icon_fg_color_y_gradient(letter_e_icon, 258, 20,  81, 110);
  display_copy_icon_fg_color_y_gradient(letter_c_icon, 353, 20,  93, 110);
  display_copy_icon_fg_color_y_gradient(letter_o_icon, 461, 20, 103, 110);
  display_copy_icon_fg_color_y_gradient(letter_s_icon, 575, 48,  72,  81);

  //Show it is the firmware backup code
  display_set_fg_color(0x00801010);
  display_set_font(&font_7);
  display_text(165, 150, "FNIRSI-1014D FIRMWARE BACKUP");
  
  //Draw the raster
  display_set_fg_color(0x00000000);
  display_draw_rect(0, 0, 800, 480);
  display_draw_rect(1, 1, 798, 478);
}

//----------------------------------------------------------------------------------------------------------------------------------

void draw_progress_bar(uint32 xpos, uint32 ypos, uint32 progress)
{
  uint32 x1 = xpos - 1;
  uint32 x2 = xpos + 1;
  uint32 x3 = xpos + 4;
  
  uint32 y1 = ypos - 1;
  uint32 y2 = ypos + 1;
  uint32 y3 = ypos + 4;
  
  //Switch to other display buffer
  display_set_screen_buffer(displaybuffer);

  //Clear the progress bar area
  display_set_fg_color(0x00307850);
  display_fill_rect(x1, y1, 263, 32);

  //Draw the outline
  display_set_fg_color(0x00B4FFFE);
  display_draw_rounded_rect(xpos, ypos, 261, 30, 4);
  display_draw_rounded_rect(x2,   y2,   259, 28, 4);
  
  //Draw the progress bar
  display_fill_rounded_rect(x3, y3, progress, 22, 4);

  //Copy the updated bar to the main screen
  //This gives a smoother progress display
  display_set_screen_buffer((uint16 *)maindisplaybuffer);
  display_set_source_buffer(displaybuffer);
  display_copy_rect_to_screen(x1, y1, 263, 32);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 save_full_flash_data(uint32 ypos, uint32 blocksize)
{
  int32  status = 0;
  uint32 address = 0;
  uint32 block;
  uint32 y1 = ypos + 3;

  //Delete the file if it exists
  f_unlink("FNIRSI_1014D_full_flash_backup.bin");
  
  //Create a file for the full flash backup. Fails if it already exists
  if(f_open(&fp, "FNIRSI_1014D_full_flash_backup.bin", FA_CREATE_NEW | FA_WRITE | FA_READ) != FR_OK)
  {
    //Error message in red
    display_set_fg_color(0x00FF0000);
    display_text(20, y1, "ERROR CREATING FULL FLASH BACKUP FILE");

    //Signal failure
    status = -1;
  }
  //Write the full flash backup to the SD card  
  else
  {
    //Show backup is started
    display_text(20, y1, "BACKUPING FULL FLASH");
    
    for(block=0;block<128;block++)
    {
      //Read a block from the flash
      sys_spi_flash_read(address, (uint8 *)flashbuffer, blocksize);
      
      //Write the data to the SD card
      if(f_write(&fp, (uint8 *)flashbuffer, blocksize, 0) != FR_OK)
      {
        //Clear message part of the screen first
        display_set_fg_color(0x00307850);
        display_fill_rect(18, ypos - 1, 720, 32);
        
        //Error message in red
        display_set_fg_color(0x00FF0000);
        display_text(20, y1, "ERROR WRITING FULL FLASH BACKUP FILE");

        //Signal failure
        status = -1;
        break;
      }

      //Update the progress bar
      draw_progress_bar(320, ypos, block * 2);
        
      //Select the next address
      address += blocksize;
    }
  }
  
  //Close the file to finish the write process
  f_close(&fp);
  
  return(status);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 save_firmware_data(uint32 ypos)
{
  int32  status = 0;
  uint32 address = 0x00013000;
  uint32 blocksize = 15714;
  uint32 block;
  uint32 y1 = ypos + 3;
  
  uint32 index = 0;
  uint32 i;
  uint8 *sptr;
  uint8  byte;
  uint8  bitflag;
  int32  bit;
  
  //Firmware backup starts at 0x13000 in the flash and includes the special locations because these are cleared otherwise, so up to 0x1FE100
  
  //Delete the file if it exists
  f_unlink("FWB_FSI-1014.bin");
  
  //Create a file for the full flash backup. Fails if it already exists
  if(f_open(&fp, "FWB_FSI-1014.bin", FA_CREATE_NEW | FA_WRITE | FA_READ) != FR_OK)
  {
    //Error message in red
    display_set_fg_color(0x00FF0000);
    display_text(20, y1, "ERROR CREATING FIRMWARE BACKUP FILE");

    //Signal failure
    status = -1;
  }
  //Write the firmware backup to the SD card  
  else
  {
    //Show backup is started
    display_text(20, y1, "BACKUPING FIRMWARE");

    //Point to the data to handle when check calculating
    sptr = (uint8 *)flashbuffer;
    
    for(block=0;block<128;block++)
    {
      //Read a block from the flash
      sys_spi_flash_read(address, (uint8 *)flashbuffer, blocksize);
      
      //Write the data to the SD card
      if(f_write(&fp, (uint8 *)flashbuffer, blocksize, 0) != FR_OK)
      {
        //Clear message part of the screen first
        display_set_fg_color(0x00307850);
        display_fill_rect(18, ypos - 1, 720, 32);
        
        //Error message in red
        display_set_fg_color(0x00FF0000);
        display_text(20, y1, "ERROR WRITING FIRMWARE BACKUP FILE");

        //Signal failure
        status = -1;
        break;
      }
      
      //Calculate the check data on this block
      for(i=0;i<blocksize;i++,index++)
      {
        //Get the current byte
        byte = sptr[i];

        //Calculate the sum of all the data bytes
        fwcheckdata[0] += byte;

        //Calculate an index dependent occurrence of the individual bits
        for(bit=1,bitflag=0x80;bit<9;bit++)
        {
          //Check if the current bit is set
          if(byte & bitflag)
          {
            //If so add to the counter for this bit
            fwcheckdata[bit] += index;
          }

          //Select the next bit to check
          bitflag >>=1;
        }
      }

      //Update the progress bar
      draw_progress_bar(320, ypos, block * 2);
        
      //Select the next address
      address += blocksize;
    }
  }
  
  //Check if it is ok to write the check data
  if(status == 0)
  {
    //Clear 72 bytes to hold the data
    memset((uint8 *)flashbuffer, 0, 72);
    
    //Add the check data to the buffer
    index = 36;
    
    //Copy the data in byte by byte
    for(bit=0;bit<9;bit++)
    {
      sptr[index++] = fwcheckdata[bit] >> 24;
      sptr[index++] = fwcheckdata[bit] >> 16;
      sptr[index++] = fwcheckdata[bit] >> 8;
      sptr[index++] = fwcheckdata[bit];
    }

    //Write the check data to the SD card
    if(f_write(&fp, (uint8 *)flashbuffer, 72, 0) != FR_OK)
    {
      //Clear message part of the screen first
      display_set_fg_color(0x00307850);
      display_fill_rect(18, ypos - 1, 720, 32);

      //Error message in red
      display_set_fg_color(0x00FF0000);
      display_text(20, y1, "ERROR WRITING FIRMWARE BACKUP FILE");

      //Signal failure
      status = -1;
    }
  }
  
  //Close the file to finish the write process
  f_close(&fp);
  
  return(status);
}

//----------------------------------------------------------------------------------------------------------------------------------
