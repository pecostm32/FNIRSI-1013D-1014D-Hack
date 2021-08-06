//----------------------------------------------------------------------------------------------------------------------------------

#include "timer.h"
#include "interrupt.h"

//----------------------------------------------------------------------------------------------------------------------------------

volatile uint32 timer0ticks;

//----------------------------------------------------------------------------------------------------------------------------------

void timer0_setup(void)
{
  //Clear the ticks variable
  timer0ticks = 0;
  
  //Set the reload value for 1mS interrupt
  *TMR0_INTV_VALUE_REG = 24000;
  
  //Reset the counter
  *TMR0_CUR_VALUE_REG = 0;
  
  //Setup the interrupt for this timer
  setup_interrupt(TMR0_IRQ_NUM, timer0_irq_handler, 0);
  
  //Configurate and enable the timer 
  *TMR0_CTRL_REG = TMR_CLK_SRC_OSC24M | TMR_ENABLE;
  
  //Enable this timers interrupt
  *TMR_IRQ_EN_REG |= 1;
}

//----------------------------------------------------------------------------------------------------------------------------------

void timer0_irq_handler(void)
{
  //Clear the interrupt
  *TMR_IRQ_STA_REG |= 1;
  
  //Add one more milli second to the ticks
  timer0ticks++;
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 timer0_get_ticks(void)
{
  return(timer0ticks);  
}

//----------------------------------------------------------------------------------------------------------------------------------

void timer0_delay(uint32 timeout)
{
  uint32 curticks;
  uint32 prevticks;
  uint32 deltaticks;

  //Get the current ticks as previous
  prevticks = timer0_get_ticks();
  
  while(1)  
  {
    //Get the current ticks for delta check
    curticks = timer0_get_ticks();

    //Check on timer ticks overflow
    if(curticks >= prevticks)
    {
      //Not then the delta is simple subtraction of the values
      deltaticks = curticks - prevticks;
    }
    else
    {
      //In case of an overflow calculate the remainder of ticks to max count plus the current ticks
      deltaticks = (0xFFFFFFFF - prevticks) + curticks;
    }

    //Check if there is a timeout
    if(deltaticks > timeout)
    {
      //Done so break the loop
      break;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
