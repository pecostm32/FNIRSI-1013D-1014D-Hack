//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "Scope_Processing.h"
#include "Scope_Signal_Handling_Development.h"

#include "stub_functions.h"

#include "fnirsi_1013d_scope.h"
#include "fpga_control.h"
#include "scope_functions.h"
#include "statemachine.h"
#include "display_lib.h"
#include "variables.h"
#include "power_and_battery.h"

//----------------------------------------------------------------------------------------------------------------------------------

int interrupthandlers[64];

//----------------------------------------------------------------------------------------------------------------------------------

pthread_t scope_processing_thread;

volatile int quit_scopeprocessing_thread_on_zero = 0;

volatile int is_scopeprocessing_stopped = 0;

//----------------------------------------------------------------------------------------------------------------------------------

int startscopeprocessing(void)
{
  //Setup for keeping the arm core thread running
  quit_scopeprocessing_thread_on_zero = 1;
  
  //Signal not stopped
  is_scopeprocessing_stopped = 0;
  
  //Start up the arm core thread
  return(pthread_create(&scope_processing_thread, NULL, scopeprocessingthread, NULL));
}

//----------------------------------------------------------------------------------------------------------------------------------

void stopscopeprocessing(void)
{
  //Stop the arm core thread
  quit_scopeprocessing_thread_on_zero = 0;
  
  //Wait until process is stopped
  while(is_scopeprocessing_stopped == 0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void *scopeprocessingthread(void *arg)
{
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
  
  //Turn of the display brightness
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
    
    //On error just hang, as long as system is up
    while(quit_scopeprocessing_thread_on_zero);
    
    is_scopeprocessing_stopped = 1;
    
    //Exit the thread the way it is supposed to
    pthread_exit(NULL);
  }
  
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
  fpga_set_sample_rate(scopesettings.timeperdiv);
  fpga_set_trigger_channel();
  fpga_swap_trigger_channel();   //This is a bit redundant since the correct channel should be in the loaded settings.
  fpga_set_trigger_edge();
  fpga_set_trigger_level();
  fpga_set_trigger_mode();
  
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
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    int32 offset;
    uint32 offset1;
    uint32 offset2;
    int8   valuestring[100];
    int8  *ptr;
    
    int8 headerstring[] = "low,high,result\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    for(offset1=200;offset1<=1500;offset1+=50)
    {
      for(offset2=1500;offset2>=200;offset2-=50)
      {
        offset = fpga_read_parameter_ic(0x12, (offset1 & 0x0000FFFF) | (offset2 << 16));


        ptr = scope_print_decimal(valuestring, offset1, 0);
        
        *ptr++ = ',';
        
        ptr = scope_print_decimal(ptr, offset2, 0);
        
        *ptr++ = ',';
        
        if(offset < 0)
        {
          *ptr++ = '-';
          
          offset = -offset;
        }
        
        ptr = scope_print_decimal(ptr, offset, 0);

        *ptr++ = '\n';

        f_write(&viewfp, valuestring, ptr - valuestring, 0);
      }
    }

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif

  
  //Keep running the scope until stopped
  while(quit_scopeprocessing_thread_on_zero)
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

  //Could emulate parameter save here
  //Check if not in view mode
  if(viewactive == VIEW_NOT_ACTIVE)
  {
    //Get the settings in the working buffer and write them to the flash
    scope_save_configuration_data();
  }
  
  //Close possible open files
  fpga_exit();
  disk_exit();

  usb_device_disable();
  
  //Signal process is stopped
  is_scopeprocessing_stopped = 1;
  
  //Exit the thread the way it is supposed to
  pthread_exit(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------
