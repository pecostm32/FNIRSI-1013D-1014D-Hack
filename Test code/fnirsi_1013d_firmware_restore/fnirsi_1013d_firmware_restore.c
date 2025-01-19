//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "fwb_spi_control.h"
#include "timer.h"
#include "interrupt.h"
#include "display_control.h"
#include "fwb_fpga_control.h"

#include "fnirsi_1013d_firmware_restore.h"
#include "fwb_display_lib.h"
#include "sin_cos_math.h"

#include "sd_card_interface.h"
#include "ff.h"

#include "arm32.h"

#include "fwb_variables.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

extern IRQHANDLERFUNCION interrupthandlers[];

FIL fp;

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  int32  status = 0;
  uint8  jedecid[3];
  
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

  //Set max screen brightness
  fpga_set_backlight_brightness(0xEA60);
  
  //Setup and check SD card on file system being present
  if(f_mount(&fs, "0", 1))
  {
    //Show SD card error message on failure

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
  
  //Display the startup screen  
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

  
  //Here it needs to change
  //Check if there is a file named FNIRSI_1013d_main.bin or FNIRSI_1013D_full.bin
  
  //if it is main.bin then start writing from 0x27000
  //if it is full.bin then start writing from 0
  
  //Try to restore the main flash part from the SD card
  if(restore_flash_data("FNIRSI_1013D_main.bin", 0x00027000) != 0)
  {
    //If the file is not found try to restore the full flash from the SD card
    if(restore_flash_data("FNIRSI_1013D_full.bin", 0x00000000) != 0)
    {
      //Inform the user no file has been found
      display_text(20, 440, "NO FILE TO RESTORE FROM FOUND");
      
      status = -1;
    }
  }
  
  //Clear a sector worth of data
  memset(massstoragedata, 0, 512);
  
#if 1  
  //Remove the brom boot sector Need SD card functions for this
  if(sd_card_write(16, 1, (uint8 *)massstoragedata) != SD_OK)
  {
    //Display special touch panel text in red
    display_set_fg_color(0x00FF0000);
    display_text(20, 440, "FAILED TO CLEAR SD SECTOR 16 (BROM BOOT)");
    
    status = -1;
  }
#endif
  
  //Inform the user done without error
  if(status == 0)
  {
    display_text(20, 440, "DONE WITH RESTORE");
  }

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

  //Show it is the firmware restore code
  display_set_fg_color(0x00801010);
  display_set_font(&font_7);
  display_text(165, 150, "FNIRSI-1013D FIRMWARE RESTORE");
  
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

int32 restore_flash_data(char *filename, uint32 address)
{
  int32  status = 0;
  uint32 block = 0;
  uint32 blocksize;
  uint32 size;
  uint32 bytes_read;
  
  //See if the requested file exists.
  if(f_open(&fp, filename, FA_READ) != FR_OK)
  {
    //Signal file not found or other failure
    status = -1;
  }
  //Write the full flash backup to the SD card  
  else
  {
    //Show which file is used
    display_text( 20, 351, "FILE FOUND");
    display_text(320, 351, filename);
    
    //Show restore is started
    display_text(20, 381, "RESTORING FLASH");
    
    //Get the file size and use it for the progress bar
    size = f_size(&fp);

    //There are 254 progress slices
    blocksize = size / 254;
    
    //Buffer is limited to 32Kbyte
    if(blocksize > 32768)
      blocksize = 32768;
    
    //Read the file in chunks and copy into the flash
    while(size && (status == 0))
    {
      //Get a block of data based on the calculated size
      if(f_read(&fp, (uint8 *)flashbuffer, blocksize, &bytes_read) != FR_OK)
      {
        //Bail out on error
        status = -1;
      }
      else
      {
        //Keep track of what has been read
        size -= bytes_read;
        
        
#if 0
        display_set_fg_color(0x00307850);
        display_fill_rect(320, 410, 350, 32);
        
        display_set_fg_color(0x00B4FFFE);
        display_text(320, 410, "SIZE LEFT: ");
        display_decimal(450, 410, size);
#endif        
        
        //If there still is data, write it to the flash
        if(bytes_read)
        {
          sys_spi_flash_write(address, (uint8 *)flashbuffer, bytes_read);
          
          //Point to the next part in the flash to write to
          address += bytes_read;
        }
        
        //Update the progress bar
        draw_progress_bar(320, 378, block);
       
        //Done another block
        block++;
        
        //Make sure it does not grow to big
        if(block > 254)
          block = 254;
      }
    }
  }
  
  //Close the file to finish the read process
  f_close(&fp);
  
  return(status);
}

//----------------------------------------------------------------------------------------------------------------------------------
