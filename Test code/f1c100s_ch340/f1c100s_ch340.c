//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

#include "ccu_control.h"
#include "timer.h"
#include "interrupt.h"
#include "fpga_control.h"

#include "f1c100s_ch340.h"

#include "ch340_class.h"
#include "usb_interface.h"

#include "commands.h"

#include "arm32.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

extern IRQHANDLERFUNCION interrupthandlers[];

int16 volatile curchar;

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
  
  //Enable interrupts only once. In the original code it is done on more then one location.
  arm32_interrupt_enable();
  
  //Initialize FPGA (PORT E)
  fpga_init();
  
  //Setup the USB device
  usb_device_init();
  
  //Wait 200ms to allow the USB interface to disconnect before switching to CH340 mode
  //Is only needed when loaded via FEL and not when booted from SD card
  timer0_delay(200);
  
  //Enable the USB and it's interrupts
  usb_device_enable();
  
  //Keep handling the data
  while(1)
  {
    //Read a character from the USB receive buffer
    curchar = ch340Receive();
    
    //Check if any data to process
    if(curchar != -1)
    {
      handleinput();
    }    
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
