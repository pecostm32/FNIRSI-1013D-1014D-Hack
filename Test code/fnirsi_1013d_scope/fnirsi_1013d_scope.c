//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "spi_control.h"
#include "timer.h"
#include "interrupt.h"
#include "display_control.h"
#include "fpga_control.h"
#include "touchpanel.h"

#include "fnirsi_1013d_scope.h"
#include "display_lib.h"
#include "scope_functions.h"
#include "statemachine.h"

#include "sd_card_interface.h"
#include "ff.h"

#include "arm32.h"

#include "variables.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

extern uint8  havetouch;
extern uint16 xtouch;
extern uint16 ytouch;

extern uint8 touchstate;

extern uint8 systemsettingsmenuopen;
extern uint8 screenbrightnessopen;
extern uint8 gridbrightnessopen;
extern uint8 calibrationopen;

extern uint16 maindisplaybuffer[];

extern SCOPESETTINGS scopesettings;

extern IRQHANDLERFUNCION interrupthandlers[];

extern FONTDATA font_3;

//----------------------------------------------------------------------------------------------------------------------------------

int main(void)
{
  FATFS fs;
  
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
  sys_init_display(SCREEN_WIDTH, SCREEN_HEIGHT, maindisplaybuffer);
  
  //Setup the display library for the scope hardware
  scope_setup_display_lib();
  
  //Initialize some variables for now
  systemsettingsmenuopen = 0;
  screenbrightnessopen = 0;
  gridbrightnessopen = 0;
  calibrationopen = 0;
  
  touchstate = 0;
  havetouch = 0;
  xtouch = 0;
  ytouch = 0;
  
  viewtype = 0;

  //Setup the touch panel interface
  tp_i2c_setup();

  //Setup and check SD card on file system present
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
  
  scopesettings.rightmenustate = 0;
  scopesettings.waveviewmode = 0;

  scopesettings.runstate = 0;

  scopesettings.movespeed = 0;

  scopesettings.channel1.enable = 1;
  scopesettings.channel1.coupling = 0;
  scopesettings.channel1.magnification = 0;
  scopesettings.channel1.voltperdiv = 4;
  scopesettings.channel1.fftenable = 0;
  scopesettings.channel1.traceoffset = 220;
  
  scopesettings.channel2.enable = 0;
  scopesettings.channel2.coupling = 0;
  scopesettings.channel2.magnification = 0;
  scopesettings.channel2.voltperdiv = 3;
  scopesettings.channel2.fftenable = 0;
  scopesettings.channel2.traceoffset = 155;
  
  scopesettings.triggermode = 0;
  scopesettings.triggeredge = 1;
  scopesettings.triggerchannel = 0;
  
  scopesettings.triggerposition = 350;
  scopesettings.triggeroffset = 225;
  scopesettings.triggerlevel = 20;
  
  scopesettings.timeperdivbackup = 24;
  scopesettings.timeperdiv = 24;
  
  scopesettings.triggerflag1 = 0;
  scopesettings.triggerflag2 = 0;
  scopesettings.triggerflag3 = 0;
  scopesettings.triggerflag4 = 0;
  
  scopesettings.updatescreen = 1;
  
  scopesettings.batterychargelevel = 20;
  scopesettings.batterycharging = 1;
  
  scopesettings.screenbrightness = 67;
  scopesettings.gridbrightness = 46;
  scopesettings.alwaystrigger50 = 1;
  scopesettings.xymodedisplay = 0;
  
  scopesettings.timecursorsenable = 0;
  scopesettings.timecursor1position = 78;
  scopesettings.timecursor2position = 358;

 
  scopesettings.voltcursorsenable = 0;
  scopesettings.voltcursor1position = 169;
  scopesettings.voltcursor2position = 234;

  scopesettings.previoustimerticks = 0;
  
  int channel;
  int item;
  
  for(channel=0;channel<2;channel++)
  {
    //For each channel 12 items
    for(item=0;item<12;item++)
    {
      scopesettings.measuresstate[channel][item] = 0;
    }
  }
  
  scopesettings.measuresstate[0][4] = 1;
  scopesettings.measuresstate[0][7] = 1;

  scopesettings.measuresstate[1][2] = 1;
  scopesettings.measuresstate[1][10] = 1;

  
  
  
  //In the original code there is some hardware check function here. Actions are not performed unless some data in the FLASH is not set
  
  //Here USB setup needs to be done
  
  //Power monitoring adc and interrupt setup
  
  //Load configuration data from FLASH
  
  //Check if configuration data is ok and if not write new one to flash and reload it

  //Enable or disable the channels based on the scope loaded settings
  fpga_set_channel_1_enable();
  fpga_set_channel_2_enable();
  
  //Set the volts per div for each channel based on the loaded scope settings
  fpga_set_channel_1_voltperdiv();
  fpga_set_channel_2_voltperdiv();
  
  //Set the channels AC or DC coupling based on the loaded scope settings
  fpga_set_channel_1_coupling();
  fpga_set_channel_2_coupling();
  
  //Enable something in the FPGA
  fpga_enable_system();
  
  //Initialize the communication with the parameter IC
  fpga_init_parameter_ic();
  
  //Setup the trigger system in the FPGA based on the loaded scope settings
  fpga_set_trigger_timebase();
  fpga_set_trigger_channel();
  fpga_swap_trigger_channel();   //This is a bit redundant since the correct channel should be in the loaded settings.
  fpga_set_trigger_edge();
  fpga_set_trigger_level();
  fpga_set_trigger_mode();
  
  fpga_set_channel_1_offset();
  fpga_set_channel_2_offset();
  
  //Some initialization of the FPGA??. Data written with command 0x3C
  fpga_set_battery_level();      //Only called here and in hardware check

  //In the original code there is another hardware check function here. Actions are not performed unless some data in the FLASH is not set

  //Here a function is called that looks at some system file????? Firmware upgrade!!!

  
  //Setup the main parts of the screen
  scope_setup_main_screen();
    
  //Set screen brightness
  fpga_set_translated_brightness();

  
  
//  scope_draw_time_cursors();
//  scope_draw_volt_cursors();

//  scope_draw_pointers();
  
  while(1)
  {
    //Monitor the battery status

    
    //Go through the trace data and make it ready for displaying
    scope_process_trace_data();
    
    //Display the trace data
    scope_display_trace_data();
    
    //Handle the touch panel input
    touch_handler();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
