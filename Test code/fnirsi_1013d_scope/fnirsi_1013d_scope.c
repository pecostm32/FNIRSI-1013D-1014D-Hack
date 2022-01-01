//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "spi_control.h"
#include "timer.h"
#include "interrupt.h"
#include "display_control.h"
#include "fpga_control.h"
#include "touchpanel.h"
#include "power_and_battery.h"

#include "fnirsi_1013d_scope.h"
#include "display_lib.h"
#include "scope_functions.h"
#include "statemachine.h"

#include "sd_card_interface.h"
#include "ff.h"

#include "usb_interface.h"

#include "arm32.h"

#include "variables.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

extern IRQHANDLERFUNCION interrupthandlers[];

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
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

  //Setup power monitoring
  power_interrupt_init();

  //Setup battery monitoring
  battery_check_init();

  //Enable interrupts only once. In the original code it is done on more then one location.
  arm32_interrupt_enable();

  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();

  //Initialize FPGA (PORT E)
  fpga_init();

  //Turn off the display brightness
  fpga_set_backlight_brightness(0x0000);

  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, (uint16 *)maindisplaybuffer);

  //Setup the display library for the scope hardware
  scope_setup_display_lib();

  //Setup the touch panel interface
  tp_i2c_setup();

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
    display_set_font(&font_3);
    display_text(30, 50, "SD ERROR");

    //On error just hang
    while(1);
  }

#ifndef USE_TP_CONFIG
  //Save the touch panel configuration to be save
  save_tp_config();
#endif

  //In the original code there is some hardware check function here. Actions are not performed unless some data in the FLASH is not set
  //This tests the basic hardware and verifies the touch panel

  //Setup the USB interface
  usb_device_init();

  //Load configuration data from FLASH
  scope_load_configuration_data();

  //Enable or disable the channels based on the scope loaded settings
  fpga_set_channel_enable(&scopesettings.channel1);
  fpga_set_channel_enable(&scopesettings.channel2);

  //Set the volts per div for each channel based on the loaded scope settings
  fpga_set_channel_voltperdiv(&scopesettings.channel1);
  fpga_set_channel_voltperdiv(&scopesettings.channel2);

  //Set the channels AC or DC coupling based on the loaded scope settings
  fpga_set_channel_coupling(&scopesettings.channel1);
  fpga_set_channel_coupling(&scopesettings.channel2);

  //Enable something in the FPGA
  fpga_enable_system();

  //Setup the trigger system in the FPGA based on the loaded scope settings
  fpga_set_sample_rate(scopesettings.samplerate);
  fpga_set_trigger_channel();
  fpga_swap_trigger_channel();   //This is a bit redundant since the correct channel should be in the loaded settings.
  fpga_set_trigger_edge();
  fpga_set_trigger_level();
  fpga_set_trigger_mode();

  //Set the trace offsets in the FPGA
  fpga_set_channel_offset(&scopesettings.channel1);
  fpga_set_channel_offset(&scopesettings.channel2);

  //Some initialization of the FPGA??. Data written with command 0x3C
  fpga_set_battery_level();      //Only called here and in hardware check

  //In the original code there is another hardware check function here. Actions are not performed unless some data in the FLASH is not set
  //This is for testing the analog response
  //When all tests run through the flash is updated to no longer run the hardware tests.


  //Here a function is called that looks at some system file????? Firmware upgrade!!!
  
  
  //Setup the main parts of the screen
  scope_setup_main_screen();

  //Set screen brightness
  fpga_set_translated_brightness();


  
#if 0
  int8  filename[100];
  int8  *ptr;
  int32  samplerate;

  //Enable the trigger circuit
  scopesettings.samplemode = 1;
  
  //Set number of samples
  scopesettings.samplecount = 3000;
  scopesettings.nofsamples  = 1500;
  
  
  
  samplerate = 15;
  
  {
    memcpy(filename, "trigger_data_", 13);

    ptr = scope_print_decimal(&filename[13], samplerate, 0);

    memcpy(ptr, ".bin", 5);

    //Create a file for the touch panel configuration. Fails if it already exists
    if(f_open(&viewfp, filename, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
    {
      int32   index;
      uint32  data1;
      uint32  data2;
      uint32 *ptr;

      //Set the needed sample rate
      //Set the clock divider??
      fpga_set_sample_rate(samplerate);
      
      //Set the trigger base
      fpga_write_cmd(0x0E);
      fpga_write_int(1800);

      //Trigger channel on channel 1
      fpga_write_cmd(0x15);
      fpga_write_byte(0x00);
      
      //Volt per div
      fpga_write_cmd(0x33);
      fpga_write_byte(0x04);

      //Write the offset to channel 1
      fpga_write_cmd(0x32);
      fpga_write_short(750);

      //Write the trigger level
      fpga_write_cmd(0x17);
      fpga_write_short(128);
      
      //Need to clear the compensation values before doing the calibration
      scopesettings.channel1.adc1compensation = 0;
      scopesettings.channel1.adc2compensation = 0;


      //Wait 50ms to settle
      timer0_delay(50);

      //Find the top offset value by going from bottom 200 to top 1500 in increments of 50
      for(index=0;index<20;index++)
      {
        //Do a conversion run and wait until it is done
        fpga_do_conversion();

        //Send the command for getting some data from the FPGA
        fpga_write_cmd(0x14);

        //Get the data, only 4 bits for first byte
        data1 = fpga_read_byte();
        data2 = fpga_read_byte();
        
        //Get the average from a sample run
        fpga_read_sample_data(&scopesettings.channel1, 100);

        f_write(&viewfp, channel1tracebuffer1, sizeof(channel1tracebuffer1), 0);

        ptr = channel1tracebuffer4;

        *ptr++ = scopesettings.channel1.adc1rawaverage;
        *ptr++ = scopesettings.channel1.adc2rawaverage;
        *ptr++ = scopesettings.channel1.min;
        *ptr++ = scopesettings.channel1.max;
        *ptr++ = scopesettings.channel1.average;
        *ptr++ = scopesettings.channel1.peakpeak;
        *ptr++ = scopesettings.channel1.center;

        *ptr++ = data1;
        *ptr++ = data2;

        f_write(&viewfp, channel1tracebuffer4, 36, 0);
      }  

      //Close the file to finish the write
      f_close(&viewfp);
    }
  }  

  //Show the saved successful message
  scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  
  
  
#endif  
  

  
  
  //Monitor the battery, process and display trace data and handle user input until power is switched off
  while(1)
  {
    //Monitor the battery status
    battery_check_status();

    //Go through the trace data and make it ready for displaying
    scope_acquire_trace_data();

    //Display the trace data
    scope_display_trace_data();

    //Handle the touch panel input
    touch_handler();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
