//----------------------------------------------------------------------------------------------------------------------------------

#include "sd_card_interface.h"
#include "ccu_control.h"
#include "timer.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

//need some global variables for type of card indication
uint32 cardtype = 0;
uint32 cardrca = 0;
uint32 cidnumbers[4] = { 0, 0, 0, 0 };

//----------------------------------------------------------------------------------------------------------------------------------

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
  
  //Wait a while for the device to be reset
  sd_card_delay(500);

  //Make the SD card interface active again
  *SD0_HWRST |= SD_HWRST_ACTIVE;

  //Wait a while for the device to become active again
  sd_card_delay(50);
  
  //Reset the DMA, FIFO and controller
  *SD0_GCTL |= (SD_GCTL_DMA_RST | SD_GCTL_FIFO_RST | SD_GCTL_SOFT_RST);
  
  //Wait a while for the system to be done resetting
  sd_card_delay(50);
  
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

  //Wait a while for the card to reset
  sd_card_delay(50);
  
  //Send card interface condition command to the card
  command.cmdidx    = 8;
  command.cmdarg    = 0x00000155;        //31:12 reserved (0x00000), 11:8 supply voltage (0x1 = 2.7 - 3.6V), 7:0 check pattern (0x55)
  command.resp_type = 5;
  result = sd_card_send_command(&command, 0);
  
  //Check if version 2.00 or later SD memory card
  //On result OK (0) it probably is a SDSC, SDHC or SDXC card
  if(result == SD_OK)
  {
    //Might need to check on returned information of command 8
    //Response should match the given command arg
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
    
    //Check if there was a timeout condition
    //In the original code the wrong value is used. The sunxi code uses -ETIMEDOUT (0xFFFFFF68). In the scope code they check on ETIMEDOUT (0x98)
    //Is to determine the type of card being used. Not sure if it is actually needed since mmc cards don't fit in micro sd slots. (At least for what I found about it)
    if(result == SD_ERROR_TIMEOUT)
    {
      //Send reset command to the card
      command.cmdidx    = 0;
      command.cmdarg    = 0;
      command.resp_type = 0;
      sd_card_send_command(&command, 0);
    
      //Wait a wile for the card to reset
      sd_card_delay(50);

      //Send multi media card command to the card
      command.cmdidx    = 1;
      command.cmdarg    = 0x80FF8000;                           //Need to figure out these settings
      command.resp_type = 5;
      result = sd_card_send_command(&command, 0);

      //On timeout there is no valid card inserted
      if(result == SD_ERROR_TIMEOUT)
      {
        //No valid card so signal this in the type variable
        cardtype = 0;
        
        return(SD_ERROR);
      }

      //Wait for the card to become active
      while((command.response[3] & 0x80000000) == 0)
      {
        //Send multi media card command to the card
        command.cmdidx    = 1;
        command.cmdarg    = 0x80FF8000;                           //Need to figure out these settings
        command.resp_type = 5;
        sd_card_send_command(&command, 0);
      }

      //Signal TYPE_MMC...
      cardtype = 3;
    }
    else if(result)
    {
      //No valid card so signal this in the type variable
      cardtype = 0;

      return(SD_ERROR);
    }
    else
    {
      //Send host capacity support information command
      command.cmdidx    = 41;
      command.cmdarg    = 0x00FF8000;                      //Need to figure out these settings
      command.resp_type = 7;
      result = sd_card_send_command(&command, 0);

      //Wait for the card to become active
      while((command.response[3] & 0x80000000) == 0)
      {
        //Send application specific command follows command to the card
        command.cmdidx    = 55;
        command.cmdarg    = 0;
        command.resp_type = 5;
        sd_card_send_command(&command, 0);
       
        //Send host capacity support information command
        command.cmdidx    = 41;
        command.cmdarg    = 0x80FF8000;                      //Need to figure out these settings
        command.resp_type = 7;
        result = sd_card_send_command(&command, 0);
      }      
      
      //Signal TYPE_SD_LOW...
      cardtype = 2;
    }
  }
  
  //Only if a card has been detected
  if(cardtype)
  {
    //Send get CID numbers command to the card
    command.cmdidx    = 2;
    command.cmdarg    = 0;
    command.resp_type = 7;
    sd_card_send_command(&command, 0);
  
    //Save the numbers
    cidnumbers[0] = command.response[3];
    cidnumbers[1] = command.response[2];
    cidnumbers[2] = command.response[1];
    cidnumbers[3] = command.response[0];
    
    //Check if the card is a mmc type
    if(cardtype == 3)
    {
      //Send publish RCA command to the card
      command.cmdidx    = 3;
      command.cmdarg    = 0x10000;
      command.resp_type = 7;
      result = sd_card_send_command(&command, 0);
      
      if(result)
      {
        return(SD_ERROR);
      }
      
      command.response[3] = 0x10000;
    }
    else
    {
      //Send publish RCA command to the card
      command.cmdidx    = 3;
      command.cmdarg    = 0;
      command.resp_type = 7;
      result = sd_card_send_command(&command, 0);
      
      if(result)
      {
        return(SD_ERROR);
      }
    }
    
    cardrca = command.response[3];
  }
  
  return(SD_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 sd_card_clk_init(uint32 frequency)
{
  uint32 clock;
  uint32 div;
  uint32 n_ratio;
  
	uint32 oclk_dly = 0;
	uint32 sclk_dly = 0;
  
  //Check if pll clock needs to be used for the SD card interface
  if(frequency > 24000000)
  {
    //Set clock source to PLL_PERIPH and reset the other settings
    *CCU_SDMMC0_CLK = CCU_SDMMC0_CLK_SRC_PLL_PERIPH;

    //The input clock is 576MHz (Set in ccu_control)
    clock = 576000000;
  }
  else
  {
    //Set clock source to OSC24M and reset the other settings too
    *CCU_SDMMC0_CLK = CCU_SDMMC0_CLK_SRC_OSC24M;
    
    //Set the clock frequency to 24MHz
    clock = 24000000;
  }
  
  //Calculate the clock divider
  div = clock / frequency;
  
  //For an exact multiple one needs to be added since it is subtracted later
  if(clock % frequency)
    div++;
  
  //Start with pre divide of 1
  n_ratio = 0;
  
  //Divider can't be bigger then 16, so for each multiple increase the pre divide ratio
  while(div > 16)
  {
    n_ratio++;
    div = (div + 1) / 2;
  }
  
  //If the ratio is more then 3 the clock can't be set (could when the card clock divider is used)
  if(n_ratio > 3)
    return(SD_ERROR);
  
  //Determine delays
  //Not sure what these do. Manual is not clear on this, but the original code uses it.
  if(frequency > 4000000)
  {
    if(frequency > 25000000)
    {
      if(frequency > 50000000)
      {
        //frequency > 50MHz
        oclk_dly = 1;
      }
      else
      {
        //frequency <= 50MHz
        oclk_dly = 3;
      }
      
      //For frequency above 25MHz this needs to be 4
      sclk_dly = 4;
    }
    else
    {
      //frequency <= 25MHz but > 400KHz
      sclk_dly = 5;
    }
  }
  
  //Set the clock parameters and enable it
  *CCU_SDMMC0_CLK |= (CCU_SDMMC0_CLK_ENABLE | (sclk_dly << 20) | (n_ratio << 16) | (oclk_dly << 8) | (div - 1));
  
  //Nothing left to do and no errors so say it is ok
  return(SD_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 sd_card_update_clock(void)
{
  uint32 timeout;
  
  //Update the card clock
  *SD0_CMDR = SD_CMD_START | SD_CMD_UPCLK_ONLY | SD_CMD_WAIT_PRE_OVER;
  
  //Setup for max 2 second wait
  timeout = timer0_get_ticks() + 2000;

  //Wait for the clock update to be done
  while(*SD0_CMDR & SD_CMD_START)
  {
    //Check on timeout
    if(timer0_get_ticks() > timeout)
    {
      return(SD_ERROR_TIMEOUT);
    }
  }
  
  //All went well
  return(SD_OK);  
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 sd_card_send_command(PSD_CARD_COMMAND command, PSD_CARD_DATA data)
{
	uint32 cmdval = SD_CMD_START;
  int32  error = SD_OK;
  uint32 timeout;
  
  //A command is always needed
  if(command == 0)
  {
    return(SD_ERROR);
  }
  
  //Don't send stop transmission command ???
  if(command->cmdidx == 12)
  {
    return(SD_OK);
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
    if((error = sd_send_data(data)))
    {
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
        error = SD_ERROR_TIMEOUT;
        goto out;
      }
    }
  }

  //Get the short response (48) bits 
  command->response[0] = *SD0_RESP0;
  command->response[1] = *SD0_RESP1;
  
  //Check if expected response is 136 bits
	if(command->resp_type & MMC_RSP_136)
  {
    //Get the remainder of the response bits if so
		command->response[2] = *SD0_RESP2;
		command->response[3] = *SD0_RESP3;
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
  uint32  reading;
  uint32  status_bit;
  uint32 *buffer = (uint32 *)data->data;
  uint32  count;
  uint32  timeout;
  
  //Check if data being read
  if(data->flags & MMC_DATA_READ)
  {
    //If so check on fifo empty status
    status_bit = SD_STATUS_FIFO_EMPTY;
    
    //Signal reading
    reading = 1;
  }
  else
  {
    //If writing check on fifo full status
    status_bit = SD_STATUS_FIFO_FULL;
    
    //Signal writing
    reading = 0;
  }
  
  //Data is transfered in words while input count is in bytes, so divide by 4
  count = (data->blocksize * data->blocks) >> 2;
  
  //Set the timeout based on the number of 256 byte blocks
  timeout = count >> 6;
  
  //Make sure it is not less then 2 seconds
  if(timeout < 2000)
  {
    timeout = 2000;
  }
  
  //Make sure fifo is accessible for the cpu
  *SD0_GCTL |= SD_GCTL_FIFO_ACCESS_AHB;
    
  //Setup timeout for checking against the timer ticks
  timeout += timer0_get_ticks();

  while(count)
  {
    //Wait for the fifo to be ready
    while(*SD0_STAR & status_bit)
    {
      //Check on timeout
      if(timer0_get_ticks() > timeout)
      {
        return(SD_ERROR_TIMEOUT);
      }
    }
    
    //Check if reading or writing of data
    if(reading)
    {
      //Reading so get data from the fifo
      *buffer = *SD0_FIFO;
    }
    else
    {
      //Writing so write to the fifo
      *SD0_FIFO = *buffer;
    }
    
    //Update pointer and counter
    buffer++;
    count--;
  }
  
  //All went well so return ok
  return(SD_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 sd_rint_wait(uint32 timeout, uint32 status_bit)
{
  //Setup timeout for checking against the timer ticks
  timeout += timer0_get_ticks();
  
  //Wait for the card to be ready
  while(!(*SD0_RISR & status_bit))
  {
    //Check on timeout or error
    if((timer0_get_ticks() > timeout) || (*SD0_RISR & SD_RINT_INTERRUPT_ERROR_BITS))
    {
      return(SD_ERROR_TIMEOUT);
    }
  }
  
  return(SD_OK);
}

//----------------------------------------------------------------------------------------------------------------------------------

void sd_card_delay(uint32 delay)
{
  uint32 loops = delay * 40000;

  __asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"  "bne 1b":"=r"(loops):"0"(loops));
}

//----------------------------------------------------------------------------------------------------------------------------------
