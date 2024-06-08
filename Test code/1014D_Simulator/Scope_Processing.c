//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "Scope_Processing.h"
#include "Scope_Signal_Handling_Development.h"

#include "stub_functions.h"

#include "fnirsi_1014d_scope.h"
#include "fpga_control.h"
#include "scope_functions.h"
#include "user_interface_functions.h"
#include "statemachine.h"
#include "display_lib.h"
#include "variables.h"

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
  //Clear the interrupt variables
  memset(interrupthandlers, 0, 256);
  
  //Setup timer interrupt
  timer0_setup();
  
  //Initialize SPI for flash (PORT C + SPI0)
  sys_spi_flash_init();
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Turn of the display brightness
  fpga_set_backlight_brightness(0x00);
  
  //Initialize display (PORT D + DEBE)
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, (uint16 *)maindisplaybuffer);
  
  //Setup the display library for the scope hardware
  ui_setup_display_lib();
  
  //Setup and check SD card on file system being present
  if(f_mount(&fs, "0", 1))
  {
    //Show SD card error message on failure
    //Set max screen brightness
    fpga_set_backlight_brightness(0x78);

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
  fpga_set_sample_rate(scopesettings.samplerate);
  fpga_set_time_base(scopesettings.timeperdiv);
  fpga_set_trigger_channel();
  fpga_swap_trigger_channel();   //This is a bit redundant since the correct channel should be in the loaded settings.
  fpga_set_trigger_edge();
  fpga_set_trigger_level();
  fpga_set_trigger_mode();
  
  fpga_set_channel_offset(&scopesettings.channel1);
  fpga_set_channel_offset(&scopesettings.channel2);
  
  //Setup the main parts of the screen
  ui_setup_main_screen();
  
  //Clear the sample memory
  memset(channel1tracebuffer, 128, sizeof(channel1tracebuffer));
  memset(channel2tracebuffer, 128, sizeof(channel2tracebuffer));
  
  //Set the number of samples in use
  scopesettings.nofsamples  = SAMPLES_PER_ADC;
  scopesettings.samplecount = SAMPLE_COUNT;
  
  //Show initial trace data. When in NORMAL or SINGLE mode the display needs to be drawn because otherwise if there is no signal it remains black
  scope_display_trace_data();

  //Set screen brightness
  fpga_set_translated_brightness();
  
  //Discard the first response from the user interface controller
  uart1_receive_data();
  
  //Initialize the state machine
  sm_init();

  
  //For testing use confirmation mode
  scopesettings.confirmationmode = 1;
  
  
  //Keep running the scope until stopped
  while(quit_scopeprocessing_thread_on_zero)
  {
    //Only do sampling when enabled. Gets disabled when a menu is open or when file viewing
    if(enablesampling)
    {
      //Go through the trace data and make it ready for displaying
      scope_acquire_trace_data();
    }

    //Only display trace data when enabled. Gets disabled when a menu is open or when file viewing, except when viewing a wave file
    if(enabletracedisplay)
    {
      //Display the trace data and the other enabled screen items
      scope_display_trace_data();
    }
    
    //Check if the user provided input and handle it
    sm_handle_user_input();
  }

  //Emulate parameter save here
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
