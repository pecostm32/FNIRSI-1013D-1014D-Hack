//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "f1c100s.h"
#include "f1c100s_ccu.h"
#include "f1c100s_uart.h"
#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern uint8 userinterfacecommand;    //Variable to hold the command to be sent to the main process
extern uint8 userinterfaceflag;       //Flag to signal there is a command to send to the main process

//----------------------------------------------------------------------------------------------------------------------------------
//UART0 control registers
void *F1C100sUART0(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI handler with the registers for SPI0
  return(F1C100sUART(&core->f1c100s_uart[0], address, mode));
}

//----------------------------------------------------------------------------------------------------------------------------------
//UART0 control registers read
void F1C100sUART0Read(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI read handler with the registers for SPI0
  F1C100sUARTRead(&core->f1c100s_uart[0], address, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//UART0 control registers write
void F1C100sUART0Write(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI write handler with the registers for SPI0
  F1C100sUARTWrite(&core->f1c100s_uart[0], address, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//UART0 control registers
void *F1C100sUART1(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI handler with the registers for SPI0
  return(F1C100sUART(&core->f1c100s_uart[1], address, mode));
}

//----------------------------------------------------------------------------------------------------------------------------------
//UART0 control registers read
void F1C100sUART1Read(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI read handler with the registers for SPI0
  F1C100sUARTRead(&core->f1c100s_uart[1], address, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//UART0 control registers write
void F1C100sUART1Write(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  //Call the SPI write handler with the registers for SPI0
  F1C100sUARTWrite(&core->f1c100s_uart[1], address, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//UART control registers
void *F1C100sUART(F1C100S_UART *registers, u_int32_t address, u_int32_t mode)
{
  F1C100S_MEMORY *ptr = NULL;
  
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case UART_REG0:
      ptr = &registers->reg0;
      break;
      
    case UART_REG1:
      ptr = &registers->reg1;
      break;
      
    case UART_REG2:
      ptr = &registers->reg2;
      break;
      
    case UART_LCR:
      ptr = &registers->lcr;
      break;
      
    case UART_MCR:
      ptr = &registers->mcr;
      break;
      
    case UART_LSR:
      ptr = &registers->lsr;
      break;
      
    case UART_MSR:
      ptr = &registers->msr;
      break;
      
    case UART_SCH:
      ptr = &registers->sch;
      break;
      
    case UART_USR:
      ptr = &registers->usr;
      break;
      
    case UART_TFL:
      ptr = &registers->tfl;
      break;
      
    case UART_RFL:
      ptr = &registers->rfl;
      break;
      
    case UART_HSK:
      ptr = &registers->hsk;
      break;
      
    case UART_HALT:
      ptr = &registers->halt;
      break;
      
    case UART_DBG_DLL:
      ptr = &registers->dbg_dll;
      break;
      
    case UART_DBG_DLH:
      ptr = &registers->dbg_dlh;
      break;
  }
  
  //Check if valid address has been given
  if(ptr)
  {
    //Return the pointer based on the requested mode
    switch(mode & ARM_MEMORY_MASK)
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

  return(NULL); 
}

//----------------------------------------------------------------------------------------------------------------------------------
//UART control registers read
void F1C100sUARTRead(F1C100S_UART *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case UART_REG0:
      //Check if UART1 is being addressed
      if(address == 0x01C25400)
      {
        //See if there is data from the user interface available
        if(userinterfaceflag == 1)
        {
          registers->reg0.m_8bit[0] = userinterfacecommand;
          userinterfaceflag = 0;
        }
        else
        {
          //No data available so return zero
          registers->reg0.m_8bit[0] = 0;
        }
      }
      break;
      
    case UART_REG1:
      break;
      
    case UART_REG2:
      break;
      
    case UART_LCR:
      break;
      
    case UART_MCR:
      break;
      
    case UART_LSR:
      registers->lsr.m_32bit = 0x60;
        
      //Check if UART1 is being addressed
      if(address == 0x01C25414)
      {
        //Just signal that there is data to be read
        registers->lsr.m_32bit |= 0x01;
      }
      break;
      
    case UART_MSR:
      break;
      
    case UART_SCH:
      break;
      
    case UART_USR:
      registers->usr.m_32bit = 0x02;
        
      //Check if UART1 is being addressed
      if(address == 0x01C2547C)
      {
        //Just signal that there is data to be read
        registers->usr.m_32bit |= 0x08;
      }
      break;
      
    case UART_TFL:
      break;
      
    case UART_RFL:
      break;
      
    case UART_HSK:
      break;
      
    case UART_HALT:
      break;
      
    case UART_DBG_DLL:
      break;
      
    case UART_DBG_DLH:
      break;
  }
 }

//----------------------------------------------------------------------------------------------------------------------------------
//UART control registers write
void F1C100sUARTWrite(F1C100S_UART *registers, u_int32_t address, u_int32_t mode)
{
  //Select the target register based on word address
  switch(address & 0x000000FC)
  {
    case UART_REG0:
      break;
      
    case UART_REG1:
      break;
      
    case UART_REG2:
      break;
      
    case UART_LCR:
      break;
      
    case UART_MCR:
      break;
      
    case UART_LSR:
      break;
      
    case UART_MSR:
      break;
      
    case UART_SCH:
      break;
      
    case UART_USR:
      break;
      
    case UART_TFL:
      break;
      
    case UART_RFL:
      break;
      
    case UART_HSK:
      break;
      
    case UART_HALT:
      break;
      
    case UART_DBG_DLL:
      break;
      
    case UART_DBG_DLH:
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
