//----------------------------------------------------------------------------------------------------------------------------------

#include "sd_card_interface.h"
#include "ccu_control.h"
#include "timer.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

uint32 cardtype = 0;

//need some global variables for type of card indication
//


int sd_card_init(void)
{
  SD_CARD_COMMAND command;
  int32 result;
  
  //Clear the command structure
  memset(&command, 0, sizeof(SD_CARD_COMMAND));
  
  //Configure the port F IO pins since the SD card is connected there
  *PORT_F_CFG_REG = 0xFF222222;
  
  //De-assert SPI0 reset
  *CCU_BUS_SOFT_RST0 |= CCU_BSRR0_SD0_RST;

  //Open the SPI0 bus gate
  *CCU_BUS_CLK_GATE0 |= CCU_BCGR0_SD0_EN;
  
  //Wait a short wile for the device to become active
  sd_card_delay(1);
  
  //Setup the SD card clock at 400KHz
  sd_card_clk_init(400000);
  
  //Reset the SD card interface
  *SD0_HWRST &= ~SD_HWRST_ACTIVE;
  
  //Wait a wile for the device to be reset
  sd_card_delay(5000);

  //Make the SD card interface active again
  *SD0_HWRST |= SD_HWRST_ACTIVE;

  //Wait a wile for the device to become active again
  sd_card_delay(5000);
  
  //Reset the DMA, FIFO and controller
  *SD0_GCTL |= (SD_GCTL_DMA_RST | SD_GCTL_FIFO_RST | SD_GCTL_SOFT_RST);
  
  //Wait a wile for the system to be done resetting
  sd_card_delay(5000);
  
  //Disable card detect de-bounce
  *SD0_GCTL &= ~SD_GCTL_CD_DBC_ENB;
  
  //Turn card clock of when FSM in idle state
  *SD0_CKCR |= SD_CKCR_CCLK_CTRL;
  
  //Set the hardware to use only a single bit for data transfer
  *SD0_BWDR = SD_BWDR_1_BIT_WIDTH;
  
  //Set max timeout for data and response.
  *SD0_TMOR = 0xFFFFFFFF;

  //Turn the card clock on  
  *SD0_CKCR |= SD_CKCR_CCLK_ENB;
  
  //Update the card clock
  sd_card_update_clock();

  //Wait a while for the clock to stabilize 
  sd_card_delay(50);
  
  //Send reset command to the card
  command.cmdidx    = 0;
  command.cmdarg    = 0;
  command.resp_type = 0;
  sd_card_send_command(&command, 0);

  //Wait a wile for the card to reset
  sd_card_delay(500);
  
  //Send card interface condition command to the card
  command.cmdidx    = 8;
  command.cmdarg    = 0x00000155;
  command.resp_type = 5;
  result = sd_card_send_command(&command, 0);
  
  //Check if version 2.00 or later SD memory card
  //On result OK (0) it  probably is a SDSC, SDHC or SDXC card
  if(result == 0)
  {
    //Might need to check on returned information of command 8
    //Card could be not usable???
    
    //Send some initialization commands until the card is ready?????
    do
    {
      //Send application specific command follows command to the card
      command.cmdidx    = 55;
      command.cmdarg    = 0;
      command.resp_type = 5;
      sd_card_send_command(&command, 0);

      //Send host capacity support information command
      command.cmdidx    = 41;
      command.cmdarg    = 0x40FF8000;                      //Need to figure out these settings
      command.resp_type = 7;
      result = sd_card_send_command(&command, 0);
      
    //0 means still initializing  
    } while((command.response[3] & 0x80000000) == 0);

    //Check card capacity status. 1 means SDHC or SDXC. 0 means SDSC
    if(command.response[3] & 0x40000000)
    {
      //Signal TYPE_SD_HIGH...
      cardtype = 1;
    }
    else
    {
      //Signal TYPE_SD_LOW...
      cardtype = 2;
    }
  }
  else
  {
    //Version 1.1 or earlier card
    //Send reset command to the card
    command.cmdidx    = 0;
    command.cmdarg    = 0;
    command.resp_type = 0;
    sd_card_send_command(&command, 0);

    //Wait a wile for the card to reset
    sd_card_delay(500);
    
    //Send application specific command follows command to the card
    command.cmdidx    = 55;
    command.cmdarg    = 0;
    command.resp_type = 5;
    result = sd_card_send_command(&command, 0);
    
    
    
  }
  
  
  
  //Remainder of config here
  
  
  
  
  
  return(0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void sd_card_clk_init(uint32 frequency)
{
  
}

//----------------------------------------------------------------------------------------------------------------------------------

void sd_card_update_clock(void)
{
  
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 sd_card_send_command(PSD_CARD_COMMAND command, PSD_CARD_DATA data)
{
	uint32 cmdval = SD_CMD_START;
  int32  error = 0;
  uint32 timeout;
  
  //A command is always needed
  if(command == 0)
  {
    return(-1);
  }
  
  //Don't send stop transmission command ???
  if(command->cmdidx == 12)
  {
    return(0);
  }
  
  if(command->cmdidx == 0)
  {
    cmdval |= SD_CMD_SEND_INIT_SEQ;
  }
  
  if(command->resp_type & MMC_RSP_PRESENT)
  {
		cmdval |= SD_CMD_RESP_EXPIRE;
  }
  
  if(command->resp_type & MMC_RSP_136)
  {
		cmdval |= SD_CMD_LONG_RESPONSE;
  }

  if(command->resp_type & MMC_RSP_CRC)
  {
		cmdval |= SD_CMD_CHK_RESPONSE_CRC;
  }
  
  //Check if there is data in the mix
  if(data)
  {
    //Check if buffer is 32 bit aligned
    if((uint32)data->data & 3)
    {
      error = SD_ERROR;
      goto out;
    }
    
    cmdval |= (SD_CMD_DATA_EXPIRE | SD_CMD_WAIT_PRE_OVER);
    
    if(data->flags & MMC_DATA_WRITE)
    {
      cmdval |= SD_CMD_WRITE;
    }
    
    if(data->blocks > 1)
    {
      cmdval |= SD_CMD_AUTO_STOP;
    }
    
    *SD0_BKSR = data->blocksize;
    *SD0_BYCR = data->blocks * data->blocksize;
  }
  
  //Load the SD interface command argument and command register
  *SD0_CAGR = command->cmdarg;
  *SD0_CMDR = command->cmdidx | cmdval;

  //See if data needs to be written or read
  if(data)
  {
    //The original code is different!!!!!
    //For larger blobs of data it uses DMA
    
    //Send or receive the data using the cpu
    if(sd_send_data(data))
    {
      error = SD_ERROR_TIMEOUT;
      goto out;
    }
  }
  
  //Wait for the command to finish
  if((error = sd_rint_wait(1000, SD_RINT_COMMAND_DONE)))
  {
    goto out;
  }
  
  //See if data is involved
  if(data)
  {
    //Depending on the number of blocks wait for either auto command done or data transfered
    if(data->blocks > 1)
      cmdval = SD_RINT_AUTO_COMMAND_DONE;
    else
      cmdval = SD_RINT_DATA_OVER;
      
    //Wait for the data to finish
    if((error = sd_rint_wait(120, cmdval)))
    {
      goto out;
    }
  }

  //Check if card is allowed to send busy
  if(command->resp_type & MMC_RSP_BUSY)
  {
    //Setup for max 2 second wait
    timeout = timer0_get_ticks() + 2000;
    
    //Wait for the card to be done
    while(*SD0_STAR & SD_STATUS_CARD_DATA_BUSY)
    {
      //Check on timeout
      if(timer0_get_ticks() > timeout)
      {
        error = SD_ERROR_BUSY_TIMEOUT;
        goto out;
      }
    }
  }
  
  //Check if response is 136 bits
	if(command->resp_type & MMC_RSP_136)
  {
		command->response[0] = *SD0_RESP3;
		command->response[1] = *SD0_RESP2;
		command->response[2] = *SD0_RESP1;
		command->response[3] = *SD0_RESP0;
	}
  else
  {
		command->response[0] = *SD0_RESP0;
	}

out:
  //Check if there was an error
  if(error < 0)
  {
    //Reset the DMA, FIFO and controller
    *SD0_GCTL |= (SD_GCTL_DMA_RST | SD_GCTL_FIFO_RST | SD_GCTL_SOFT_RST);
    
    sd_card_update_clock();
  }
  
  //Clear all raw interrupts
  *SD0_RISR = 0xFFFFFFFF;

  //Reset the FIFO
  *SD0_GCTL |= SD_GCTL_FIFO_RST;
    
  return(error);  
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 sd_send_data(PSD_CARD_DATA data)
{
  return(0);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 sd_rint_wait(uint32 timeout, uint32 flag)
{
  return(0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void sd_card_delay(uint32 delay)
{
  uint32 loops = delay * 40000;

  __asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"  "bne 1b":"=r"(loops):"0"(loops));
}

//----------------------------------------------------------------------------------------------------------------------------------
