//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_timer.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Processing of the timer is called every core instruction
void F1C100sProcessTimer(PARMV5TL_CORE core)
{
  //Check if a timer is enabled
  if(core->f1c100s_timer.tmr0_ctrl.m_32bit & TMR_CTRL_ENABLE)
  {
    //Do the pre scaler to get the actual timer clock
    if(--core->f1c100s_timer.prescaler[0] <= 0)
    {
      //Do the actual timer
      if(--core->f1c100s_timer.tmr0_cur_value.s_32bit <= 0)
      {
        //Reload the timer
        core->f1c100s_timer.tmr0_cur_value.m_32bit =  core->f1c100s_timer.tmr0_intv_value.m_32bit;
        
        //Check if interrupt is enabled for this timer
        if(core->f1c100s_timer.tmr_irq_en.m_32bit & TMR_IRQ_EN_TMR0_EN)
        {
          //Set the interrupt status for this timer to 1 in both the internal and readable register
          core->f1c100s_timer.tmr_irq_sta.m_32bit |= TMR_IRQ_EN_TMR0_EN;
          core->f1c100s_timer.interruptstatus |= TMR_IRQ_EN_TMR0_EN;
        }
        
        //Check if single mode
        if(core->f1c100s_timer.tmr0_ctrl.m_32bit & TMR_CTRL_MODE_SINGLE)
        {
          //Disable the timer if single mode set
          core->f1c100s_timer.tmr0_ctrl.m_32bit &= ~TMR_CTRL_ENABLE;
        }
      }
      
      //Reset the pre scaler
      core->f1c100s_timer.prescaler[0] = core->f1c100s_timer.prescalerreload[0];
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Timer control registers
void *F1C100sTimer(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case TMR_IRQ_EN:
      ptr = &core->f1c100s_timer.tmr_irq_en;
      break;
      
    case TMR_IRQ_STA:
      ptr = &core->f1c100s_timer.tmr_irq_sta;
      break;
      
    case TMR0_CTRL:
      ptr = &core->f1c100s_timer.tmr0_ctrl;
      break;
      
    case TMR0_INTV_VALUE:
      ptr = &core->f1c100s_timer.tmr0_intv_value;
      break;
      
    case TMR0_CUR_VALUE:
      ptr = &core->f1c100s_timer.tmr0_cur_value;
      break;
      
    case TMR1_CTRL:
      ptr = &core->f1c100s_timer.tmr1_ctrl;
      break;
      
    case TMR1_INTV_VALUE:
      ptr = &core->f1c100s_timer.tmr1_intv_value;
      break;
      
    case TMR1_CUR_VALUE:
      ptr = &core->f1c100s_timer.tmr1_cur_value;
      break;
      
    case TMR2_CTRL:
      ptr = &core->f1c100s_timer.tmr2_ctrl;
      break;
      
    case TMR2_INTV_VALUE:
      ptr = &core->f1c100s_timer.tmr2_intv_value;
      break;
      
    case TMR2_CUR_VALUE:
      ptr = &core->f1c100s_timer.tmr2_cur_value;
      break;
      
    case AVS_CNT_CTL:
      ptr = &core->f1c100s_timer.avs_cnt_ctl;
      break;
      
    case AVS_CNT0:
      ptr = &core->f1c100s_timer.avs_cnt0;
      break;
      
    case AVS_CNT1:
      ptr = &core->f1c100s_timer.avs_cnt1;
      break;
      
      ptr = &core->f1c100s_timer.avs_cnt_div;
  case AVS_CNT_DIV:
      break;
      
    case WDOG_IRQ_EN:
        ptr = &core->f1c100s_timer.wdog_irq_en;
        break;
      
    case WDOG_IRQ_STA:
      ptr = &core->f1c100s_timer.wdog_irq_sta;
      break;
      
    case WDOG_CTRL:
      ptr = &core->f1c100s_timer.wdog_ctrl;
      break;
      
    case WDOG_CFG:
      ptr = &core->f1c100s_timer.wdog_cfg;
      break;
      
    case WDOG_MODE:
      ptr = &core->f1c100s_timer.wdog_mode;
      break;
  }

  //Check if valid address has been given
  if(ptr)
  {
    //Return the pointer based on the requested mode
    switch(mode)
    {
      case ARM_MEMORY_WORD:
        //Return the word aligned data
        return(&ptr->m_32bit);

      case ARM_MEMORY_SHORT:
        //Return the short aligned data
        return(&ptr->m_16bit[(address & 2) >> 1]);

      case ARM_MEMORY_BYTE:
        //Return the byte aligned data
        return(&ptr->m_8bit[address & 3]);
    }
  }
  else
  {
    return(NULL); 
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Timer control registers read function
void F1C100sTimerRead(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case TMR_IRQ_EN:
      break;
      
    case TMR_IRQ_STA:
      //Copy the internal interrupt status to the readable register
      core->f1c100s_timer.tmr_irq_sta.m_32bit = core->f1c100s_timer.interruptstatus & 0x07;
      break;
      
    case TMR0_CTRL:
      break;
      
    case TMR0_INTV_VALUE:
      break;
      
    case TMR0_CUR_VALUE:
      break;
      
    case TMR1_CTRL:
      break;
      
    case TMR1_INTV_VALUE:
      break;
      
    case TMR1_CUR_VALUE:
      break;
      
    case TMR2_CTRL:
      break;
      
    case TMR2_INTV_VALUE:
      break;
      
    case TMR2_CUR_VALUE:
      break;
      
    case AVS_CNT_CTL:
      break;
      
    case AVS_CNT0:
      break;
      
    case AVS_CNT1:
      break;
      
    case AVS_CNT_DIV:
      break;
      
    case WDOG_IRQ_EN:
      break;
      
    case WDOG_IRQ_STA:
      break;
      
    case WDOG_CTRL:
      break;
      
    case WDOG_CFG:
      break;
      
    case WDOG_MODE:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Timer control registers write function
void F1C100sTimerWrite(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case TMR_IRQ_EN:
      break;
      
    case TMR_IRQ_STA:
      //Clear the bits in the internal interrupt status register on write with 1
      core->f1c100s_timer.interruptstatus &= ~(core->f1c100s_timer.tmr_irq_sta.m_32bit & 0x07);

      //Let the status register reflect the actual status after the clear
      core->f1c100s_timer.tmr_irq_sta.m_32bit = core->f1c100s_timer.interruptstatus & 0x07;
      break;
      
    case TMR0_CTRL:
      //Check on timer start condition
      if((core->f1c100s_timer.tmr0_ctrl.m_32bit & TMR_CTRL_ENABLE) && ((core->f1c100s_timer.ctrl_previous[0] & TMR_CTRL_ENABLE) == 0))
      {
        //Check if current value is zero or the reload bit is set to do a reload
        if((core->f1c100s_timer.tmr0_cur_value.m_32bit == 0) || (core->f1c100s_timer.tmr0_ctrl.m_32bit & TMR_CTRL_RELOAD))
        {
          //Load the interval value into the current value
          core->f1c100s_timer.tmr0_cur_value.m_32bit =  core->f1c100s_timer.tmr0_intv_value.m_32bit;

          //Clear the reload flag for a next reload
          core->f1c100s_timer.tmr0_ctrl.m_32bit &= ~TMR_CTRL_RELOAD;
        }
        
        //Save the new state for next write
        core->f1c100s_timer.ctrl_previous[0] = core->f1c100s_timer.tmr0_ctrl.m_32bit;
      }
      
      //Setup pre scaler. Check which clock should be used
      if((core->f1c100s_timer.tmr0_ctrl.m_32bit & TMR_CTRL_CLK_MASK) == 0)
      {
        //32KHz low osc (18750 instructions per tick)
        core->f1c100s_timer.prescalerreload[0] = 18750 << ((core->f1c100s_timer.tmr0_ctrl.m_32bit & TMR_CTRL_PRS_MASK) >> 4);
      }
      else
      {
        //24MHz clock (25 instructions per tick)
        core->f1c100s_timer.prescalerreload[0] = 25 << ((core->f1c100s_timer.tmr0_ctrl.m_32bit & TMR_CTRL_PRS_MASK) >> 4);
      }
      
      //Reset the actual pre scaler
      core->f1c100s_timer.prescaler[0] = core->f1c100s_timer.prescalerreload[0];
      break;
      
    case TMR0_INTV_VALUE:
      break;
      
    case TMR0_CUR_VALUE:
      break;
      
    case TMR1_CTRL:
      break;
      
    case TMR1_INTV_VALUE:
      break;
      
    case TMR1_CUR_VALUE:
      break;
      
    case TMR2_CTRL:
      break;
      
    case TMR2_INTV_VALUE:
      break;
      
    case TMR2_CUR_VALUE:
      break;
      
    case AVS_CNT_CTL:
      break;
      
    case AVS_CNT0:
      break;
      
    case AVS_CNT1:
      break;
      
    case AVS_CNT_DIV:
      break;
      
    case WDOG_IRQ_EN:
      break;
      
    case WDOG_IRQ_STA:
      break;
      
    case WDOG_CTRL:
      break;
      
    case WDOG_CFG:
      break;
      
    case WDOG_MODE:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
