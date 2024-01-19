//----------------------------------------------------------------------------------------------------------------------------------

#include "fpga_control.h"
#include "fnirsi_1013d_scope.h"
#include "timer.h"
#include "variables.h"

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagByteBits    ByteBits;

typedef union tagByteAndBits  ByteAndBits;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagByteBits
{
  uint8 b0:1;
  uint8 b1:1;
  uint8 b2:1;
  uint8 b3:1;
  uint8 b4:1;
  uint8 b5:1;
  uint8 b6:1;
  uint8 b7:1;
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagByteAndBits
{
  uint8    byte;
  ByteBits bits;
};

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_init(void)
{
  //First set pin high in data register to avoid spikes when changing from input to output
  FPGA_CLK_INIT();
  
  //Initialize the three control lines for output
  FPGA_CTRL_INIT();
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_cmd(uint8 command)
{
  //Set the control lines for writing a command
  FPGA_CMD_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();

  //Write the data to the bus  
  FPGA_SET_DATA(command);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

uint8 fpga_read_cmd(void)
{
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_CMD_READ();

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();
 
  //Read the data
  return(FPGA_GET_DATA());
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_byte(uint8 data)
{
  //Set the control lines for writing a command
  FPGA_DATA_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();
  
  //Write the data to the bus  
  FPGA_SET_DATA(data);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

uint8 fpga_read_byte(void)
{
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();
 
  //Read the data
  return(FPGA_GET_DATA());
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_short(uint16 data)
{
  //Set the control lines for writing a command
  FPGA_DATA_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();
  
  //Write the msb to the bus  
  FPGA_SET_DATA(data >> 8);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
  
  //Write the lsb to the bus  
  FPGA_SET_DATA(data);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_read_short(void)
{
  uint16 data;
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();

  //Get the msb
  data = FPGA_GET_DATA() << 8;

  //Clock the data to the output of the FPGA
  FPGA_PULSE_CLK();

  //Get the lsb
  data |= FPGA_GET_DATA();
  
  //Read the data
  return(data);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_int(uint32 data)
{
  //Set the control lines for writing a command
  FPGA_DATA_WRITE();

  //Set the bus for writing
  FPGA_BUS_DIR_OUT();
  
  //Write the msb to the bus  
  FPGA_SET_DATA(data >> 24);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();

  //Write the mlsb to the bus  
  FPGA_SET_DATA(data >> 16);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
  
  //Write the lmsb to the bus  
  FPGA_SET_DATA(data >> 8);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
  
  //Write the lsb to the bus  
  FPGA_SET_DATA(data);
  
  //Clock the data into the FPGA
  FPGA_PULSE_CLK();
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_backlight_brightness(uint16 brightness)
{
  fpga_write_cmd(0x38);
  fpga_write_short(brightness);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_translated_brightness(void)
{
  uint16 data;
  
  //Translate the 0 - 100 brightness value into data for the FPGA
  data = fpga_read_parameter_ic(0x10, scopesettings.screenbrightness);
  
  //Write it to the FPGA
  fpga_set_backlight_brightness(data);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_get_version(void)
{
  fpga_write_cmd(0x06);

  return(fpga_read_short());
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_check_ready(void)
{
  int i;
  
  //Check if the FPGA is up and running by reading the version number
  while(fpga_get_version() != 0x1432)
  {
    //if not just wait a bit and try it again
    //At 600MHz CPU_CLK 1000 = ~200uS
    for(i=0;i<1000;i++)
    {
      __asm__ ("nop");
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_enable_system(void)
{
  //This command is only ever set with 1 as data and this function is only called at setup and check hardware
  fpga_write_cmd(0x04);
  fpga_write_byte(0x01);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_enable(void)
{
  //Send the command for channel 1 enable to the FPGA
  fpga_write_cmd(0x02);
  
  //Write the needed data based on the setting
  if(scopesettings.channel1.enable == 0)
  {
    //Disable the channel
    fpga_write_byte(0x00);
  }
  else
  {
    //Enable the channel
    fpga_write_byte(0x01);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_coupling(void)
{
  //Send the command for channel 1 coupling to the FPGA
  fpga_write_cmd(0x34);
  
  //Write the needed data based on the setting
  if(scopesettings.channel1.coupling == 0)
  {
    //Set the DC coupling for the channel
    fpga_write_byte(0x01);
  }
  else
  {
    //Set the AC coupling for the channel
    fpga_write_byte(0x00);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_voltperdiv(void)
{
  register uint32 setting = scopesettings.channel1.voltperdiv;
  
  //Send the command for channel 1 volts per div to the FPGA
  fpga_write_cmd(0x33);
  
  //Check if setting in range of what is allowed
  if(setting > 5)
    setting = 5;
  
  //Write it to the FPGA
  fpga_write_byte(setting);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_offset(void)
{
  uint32 offset;

  //Do some fractional calculation with sign correction?????
  //For now a copy of what Ghidra made of it
  offset = ((uint64)((uint64)0x51EB851F * (uint64)(scopesettings.channel1.traceoffset * channel1_calibration_factor)) >> 37);
  offset = (signal_adjusters[0] * offset) / signal_adjusters[scopesettings.channel1.voltperdiv];
  
  //Send the command for channel 1 offset to the FPGA
  fpga_write_cmd(0x32);

  //Write the calibrated offset data  
  fpga_write_short(channel1_calibration_data[scopesettings.channel1.voltperdiv] - offset);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_enable(void)
{
  //Send the command for channel 2 enable to the FPGA
  fpga_write_cmd(0x03);
  
  //Write the needed data based on the setting
  if(scopesettings.channel2.enable == 0)
  {
    //Disable the channel
    fpga_write_byte(0x00);
  }
  else
  {
    //Enable the channel
    fpga_write_byte(0x01);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_coupling(void)
{
  //Send the command for channel 2 coupling to the FPGA
  fpga_write_cmd(0x37);
  
  //Write the needed data based on the setting
  if(scopesettings.channel2.coupling == 0)
  {
    //Set the DC coupling for the channel
    fpga_write_byte(0x01);
  }
  else
  {
    //Set the AC coupling for the channel
    fpga_write_byte(0x00);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_voltperdiv(void)
{
  register uint32 setting = scopesettings.channel2.voltperdiv;
  
  //Send the command for channel 2 volts per div to the FPGA
  fpga_write_cmd(0x36);
  
  //Check if setting in range of what is allowed
  if(setting > 5)
    setting = 5;
  
  //Write it to the FPGA
  fpga_write_byte(setting);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_offset(void)
{
  uint32 offset;

  //Do some fractional calculation with sign correction?????
  //For now a copy of what Ghidra made of it  
  offset = ((uint64)((uint64)0x51EB851F * (uint64)(scopesettings.channel2.traceoffset * channel2_calibration_factor)) >> 37);
  offset = (signal_adjusters[0] * offset) / signal_adjusters[scopesettings.channel2.voltperdiv];
  
  //Send the command for channel 2 offset to the FPGA
  fpga_write_cmd(0x35);

  //Write the calibrated offset data  
  fpga_write_short(channel2_calibration_data[scopesettings.channel2.voltperdiv] - offset);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_timebase(void)
{
  uint32 data;
  uint8  command;
  
  //Translate the time per div setting to what the FPGA needs
  data = fpga_read_parameter_ic(0x0A, scopesettings.timeperdiv);
  
  //Get the FPGA command that needs the setting
  command = fpga_read_parameter_ic(0x14, 0xED);
  
  //Write the command to the FPGA
  fpga_write_cmd(command);
  
  //Write the data to the FPGA
  fpga_write_int(data);
  
  //Signal to reset the display
  disp_xpos = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_channel(void)
{
  //Send the command for selecting the trigger channel to the FPGA
  fpga_write_cmd(0x15);
  
  //Write the needed data based on the setting
  if(scopesettings.triggerchannel == 0)
  {
    //Set channel 1 as trigger input
    fpga_write_byte(0x00);
  }
  else
  {
    //Set channel 2 as trigger input
    fpga_write_byte(0x01);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_edge(void)
{
  //Send the command for selecting the trigger channel to the FPGA
  fpga_write_cmd(0x16);
  
  //Write the needed data based on the setting
  if(scopesettings.triggeredge == 0)
  {
    //Set trigger edge to rising
    fpga_write_byte(0x00);
  }
  else
  {
    //Set trigger edge to falling
    fpga_write_byte(0x01);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_swap_trigger_channel(void)
{
  //Check if channel 1 is disabled or channel 2 is enabled
  if((scopesettings.channel1.enable == 0) || (scopesettings.channel2.enable))
  {
    //Check if both channels are disabled
    if(scopesettings.channel2.enable == 0)
    {
      //If so do nothing
      return;
    }
    
    //Else check if channel 1 is enabled
    if(scopesettings.channel1.enable)
    {
      //Assume the correct setting is already in the FPGA and do nothing
      return;
    }
    
    //Only channel 2 enabled so set it as source
    scopesettings.triggerchannel = 1;
  }
  else
  {
    //Only channel 1 enabled so set that as source
    scopesettings.triggerchannel = 0;
  }
  
  //Write it the new setting to the FPGA
  fpga_set_trigger_channel();
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_level(void)
{
  uint32 voltperdiv;
  uint32 traceoffset;
  uint32 adjuster;
  uint32 level;
  
  //Check which channel is used for triggering
  if(scopesettings.triggerchannel == 0)
  {
    //Channel 1, so use its data
    voltperdiv  = scopesettings.channel1.voltperdiv;
    traceoffset = scopesettings.channel1.traceoffset;
  }
  else
  {
    //Channel 2, so use its data
    voltperdiv  = scopesettings.channel2.voltperdiv;
    traceoffset = scopesettings.channel2.traceoffset;
  }
  
  //Get the adjuster for the level based on the volts per div setting
  adjuster = signal_adjusters[voltperdiv];
  
  //Process the data different when on lowest volts per div setting
  if(voltperdiv == 6)
  {
    //check if trigger trace offset below channel trace offset
    if(scopesettings.triggeroffset < traceoffset)
    {
      //Below the trace
      //Use the trace screen offset minus half the delta of the screen offsets and scale it with the signal adjuster setting
      level = ((traceoffset - ((traceoffset - scopesettings.triggeroffset) / 2)) * 100) / adjuster;
    }
    else
    {
      //Above the trace
      //Use the trace screen offset plus half the delta of the screen offsets and scale it with the signal adjuster setting
      level = ((traceoffset + ((scopesettings.triggeroffset - traceoffset) / 2)) * 100) / adjuster;
    }
  }
  else
  {
    //Scale the screen offset with the signal adjuster setting
    level = (scopesettings.triggeroffset * 100) / adjuster;
  }
  
  //Store the result in the global settings
  scopesettings.triggerlevel = level;
  
  //Send the command for setting the trigger level to the FPGA
  fpga_write_cmd(0x17);
  
  //Write the actual level to the FPGA
  fpga_write_byte(level);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_trigger_mode(void)
{
  //Send the command for selecting the trigger mode to the FPGA
  fpga_write_cmd(0x1A);
  
  //Write the needed data based on the setting
  if(scopesettings.triggermode == 0)
  {
    //Set trigger mode to auto
    fpga_write_byte(0x00);
  }
  else
  {
    //Set trigger mode to single or normal
    fpga_write_byte(0x01);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_long_timebase(void)
{
  //Send the command for long time base to the FPGA
  fpga_write_cmd(0x0D);
  
  //Send the data, which is always 2000
  fpga_write_int(2000);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_short_timebase(void)
{
  //Write the command to set the short time base data to the FPGA
  fpga_write_cmd(0x0E);
  
  //Table settings ranges from setting 9 (50mS/div) to 29 (10nS/div)
  fpga_write_int(short_timebase_settings[scopesettings.timeperdiv - 9]);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_prepare_for_transfer(void)
{
  uint8  data1;
  uint8  data2;
  uint32 data;
  
  //Send the command for getting some data from the FPGA
  fpga_write_cmd(0x14);
  
  //Get the data, only 4 bits for first byte
  data1 = fpga_read_byte() & 0x0F;
  data2 = fpga_read_byte();
  
  //Prepare for translation
  data = (data1 << 12) | (data2 << 4) | data1;
  
  //Translate it via the special ic
  data = fpga_read_parameter_ic(0x11, data);
 
  return(data & 0x0FFF);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_read_trace_data(uint8 command, uint16 *buffer, int32 count)
{
  //Send a command for getting trace data from the FPGA
  fpga_write_cmd(command);
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();

  //Read the data as long as there is count
  while(count)
  {
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();
 
    //Read the data
    *buffer++ = (uint16)FPGA_GET_DATA();
    
    //One read done
    count--;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_average_trace_data(uint8 command)
{
  //Read ten bytes of trace data and average them
  uint16 data = 0;
  uint32 count = 10;
  
  //Send a command for getting trace data from the FPGA
  fpga_write_cmd(command);
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();

  //Read the data as long as there is count
  while(count)
  {
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();
 
    //Read the data
    data += (uint16)FPGA_GET_DATA();
    
    //One read done
    count--;
  }
  
  //Calculate the average and return it
  return(data / 10);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_battery_level(void)
{
  uint32 data = fpga_read_parameter_ic(0x16, scopesettings.batterychargelevel * scopesettings.channel2.traceoffset);
  
  //Send the command for setting the battery level to the FPGA
  fpga_write_cmd(0x3C);
  
  //Write the data
  fpga_write_short(data);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_setup_for_calibration(void)
{
  //Set the channels to lowest sensitivity and trace offset
  scopesettings.channel1.voltperdiv  = 0;
  scopesettings.channel1.traceoffset = 200;
  scopesettings.channel2.voltperdiv  = 0;
  scopesettings.channel2.traceoffset = 200;
  
  //Set the time base to 100us/div
  scopesettings.timeperdiv = 17;
  
  //Load the settings into the FPGA
  fpga_set_channel_1_voltperdiv();
  fpga_set_channel_1_offset();

  fpga_set_channel_2_voltperdiv();
  fpga_set_channel_2_offset();
  
  fpga_set_trigger_timebase();
  
  //Send the command for setting the trigger level to the FPGA
  fpga_write_cmd(0x17);
  
  //Write zero level to the FPGA
  fpga_write_byte(0);
  
  //Wait 100ms to settle
  timer0_delay(100);
  
  //Disable the trigger circuit??
  fpga_write_cmd(0x0F);
  fpga_write_byte(0x01);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_do_conversion(void)
{
  //Set the FPGA for short time base mode
  fpga_write_cmd(0x28);
  fpga_write_byte(0x00);
  
  //Reset the sample system
  fpga_write_cmd(0x01);
  fpga_write_byte(0x01);
  
  //Send check on ready command
  fpga_write_cmd(0x05);
  
  //Wait for the flag to become 1
  while((fpga_read_byte() & 1) == 0);
  
  //Test again to make sure it was no glitch?????
  while((fpga_read_byte() & 1) == 0);
  
  //Done with reset
  fpga_write_cmd(0x01);
  fpga_write_byte(0x00);
  
  //Send check on triggered or buffer full command to the FPGA
  fpga_write_cmd(0x0A);
  
  //Wait for the FPGA to signal triggered or buffer full
  while((fpga_read_byte() & 1) == 0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_1_trace_offset(uint32 offset)
{
  fpga_write_cmd(0x32);
  fpga_write_short(offset);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_2_trace_offset(uint32 offset)
{
  fpga_write_cmd(0x35);
  fpga_write_short(offset);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_command_0x1F(uint32 data)
{
  fpga_write_cmd(0x1F);
  fpga_write_short(data);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 fpga_process_channel_adc1_samples(uint32 channelid, uint32 voltperdiv)
{
  register uint32 count;
  register uint32 sample;
  register uint32 signaladjust;
  register uint32 command;
  register uint32 sum = 0;
  register uint32 divider;  
  
  //Set the number of samples to process based on the time base setting
  if(scopesettings.timeperdiv < 11)
  {
    //For 50ms and 20ms it is only 750 samples
    count = 750;
  }
  else
  {
    //For 10ms - 10ns it is 1500 samples
    count = 1500;
  }
  
  //Set the divider for calculating the average
  divider = count;
  
  //No idea what this is for, but in normal sample processing this is a value obtained from the special ic
  fpga_write_command_0x1F(100);

  //Translate this channel volts per div setting
  signaladjust = fpga_read_parameter_ic(0x0B, voltperdiv) & 0x0000FFFF;
  
  //Get the FPGA command to read from based on the trigger channel
  command = fpga_read_parameter_ic(channelid, scopesettings.triggerchannel);
  
  //Send the command for selecting the channels sample buffer
  fpga_write_cmd(command);
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();
  
  //Read the data as long as there is count
  while(count)
  {
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();

    //Read the data
    sample = FPGA_GET_DATA();
    
    //Adjust the data for the correct voltage per div setting
    sample = (41954 * sample * signaladjust) >> 22;
    
    //Limit the sample on max displayable
    if(sample > 401)
    {
      sample = 401;
    }
    
    //Add to the total sum for averaging
    sum += sample;
    
    //One read done
    count--;
  }  
  
  //In the original code the first 10 samples are discarded and only 1470 samples are used for the average
  //Need to see if this is necessary or if it is good as it is now
  
  //Calculate the average and return it
  return(sum / divider);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 fpga_average_adc1_samples(uint32 channelid)
{
  register uint32 count;
  register uint32 command;
  register uint32 sum = 0;
  register uint32 divider;  
  
  //Set the number of samples to process based on the time base setting
  if(scopesettings.timeperdiv < 11)
  {
    //For 50ms and 20ms it is only 750 samples
    count = 750;
  }
  else
  {
    //For 10ms - 10ns it is 1500 samples
    count = 1500;
  }
  
  //Set the divider for calculating the average
  divider = count;
  
  //No idea what this is for, but in normal sample processing this is a value obtained from the special ic
  fpga_write_command_0x1F(100);

  //Get the FPGA command to read from based on the trigger channel
  command = fpga_read_parameter_ic(channelid, scopesettings.triggerchannel);
  
  //Send the command for selecting the channels sample buffer
  fpga_write_cmd(command);
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();
  
  //Read the data as long as there is count
  while(count)
  {
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();

    //Add the sample to the total sum for averaging
    sum += FPGA_GET_DATA();
    
    //One read done
    count--;
  }  
  
  //In the original code the first 10 samples are discarded and only 1470 samples are used for the average
  //Need to see if this is necessary or if it is good as it is now
  
  //Calculate the average and return it
  return(sum / divider);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 fpga_average_adc2_samples(uint32 channelcmd)
{
  register uint32 count;
  register uint32 sum = 0;
  register uint32 divider;  
  
  //Set the number of samples to process based on the time base setting
  if(scopesettings.timeperdiv < 11)
  {
    //For 50ms and 20ms it is only 750 samples
    count = 750;
  }
  else
  {
    //For 10ms - 10ns it is 1500 samples
    count = 1500;
  }
  
  //Set the divider for calculating the average
  divider = count;
  
  //No idea what this is for, but in normal sample processing this is a value obtained from the special ic
  fpga_write_command_0x1F(100);

  //Send the command for selecting the channels sample buffer
  fpga_write_cmd(channelcmd);
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();
  
  //Read the data as long as there is count
  while(count)
  {
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();

    //Add the sample to the total sum for averaging
    sum += FPGA_GET_DATA();
    
    //One read done
    count--;
  }  
  
  //In the original code the first 10 samples are discarded and only 1470 samples are used for the average
  //Need to see if this is necessary or if it is good as it is now
  
  //Calculate the average and return it
  return(sum / divider);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 fpga_get_center_level(uint32 command, uint32 voltperdiv)
{
  //Do a 1000 samples
  register uint32 count = 1000;
  register uint32 min = 0x0FFFFFFF;
  register uint32 max = 0x00000000;
  register uint32 sample;
  register uint32 signaladjust;
  
  //Translate this channel volts per div setting
  signaladjust = fpga_read_parameter_ic(0x0B, voltperdiv) & 0x0000FFFF;
  
  //Have to make sure it does not need the command before every reading.
  //The original code uses both methods  
  //Send a command for getting trace data from the FPGA
  fpga_write_cmd(command);
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();

  //Read the data as long as there is count
  while(count)
  {
    //Variable delay based on the current count
    fpga_delay(1001 - count);
    
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();
 
    //Read the data
    sample = FPGA_GET_DATA();
  
    //Adjust the data for the correct voltage per div setting
    sample = (41954 * sample * signaladjust) >> 22;
    
    //Limit the sample on max displayable
    if(sample > 401)
    {
      sample = 401;
    }
    
    //Check against minimum value to get the lowest reading
    if(sample < min)
    {
      min = sample;
    }

    //Check against maximum value to get the highest reading
    if(sample > max)
    {
      max = sample;
    }
    
    //One sample done
    count --;
  }
  
  //Return the center value based on the min and the max values
  return((max + min) / 2); 
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_get_auto_set_values(uint32 flags)
{
  //Do a 1000 samples
  register uint32 count = 1000;
  register uint32 sample;
  
  //Initialize the min and max when channel is selected
  if(flags & 0x01)
  {
    channel1_min = 0x0FFFFFFF;
    channel1_max = 0x00000000;
  }  

  //Initialize the min and max when channel is selected and enabled
  if(flags & 0x02)
  {
    channel1_min = 0x0FFFFFFF;
    channel1_max = 0x00000000;
  }  

  //Read the data as long as there is count
  while(count)
  {
    //Variable delay based on the current count
    fpga_delay(1001 - count);
    
    //Get and process the sample when the channels is selected
    if(flags & 0x01)
    {
      //Send a command for getting trace data from the FPGA
      fpga_write_cmd(0x24);

      //Read the data
      sample = fpga_read_byte();

      //Adjust the data for the correct voltage per div setting
      sample = (41954 * sample * signal_adjusters[scopesettings.channel1.voltperdiv]) >> 22;

      //Limit the sample on max displayable
      if(sample > 401)
      {
        sample = 401;
      }

      //Check against minimum value to get the lowest reading
      if(sample < channel1_min)
      {
        channel1_min = sample;
      }

      //Check against maximum value to get the highest reading
      if(sample > channel1_max)
      {
        channel1_max = sample;
      }
    }
 
    //Get and process the sample when the channels is selected
    if(flags & 0x02)
    {
      //Send a command for getting trace data from the FPGA
      fpga_write_cmd(0x26);

      //Read the data
      sample = fpga_read_byte();

      //Adjust the data for the correct voltage per div setting
      sample = (41954 * sample * signal_adjusters[scopesettings.channel2.voltperdiv]) >> 22;

      //Limit the sample on max displayable
      if(sample > 401)
      {
        sample = 401;
      }

      //Check against minimum value to get the lowest reading
      if(sample < channel2_min)
      {
        channel2_min = sample;
      }

      //Check against maximum value to get the highest reading
      if(sample > channel2_max)
      {
        channel2_max = sample;
      }
    }
    
    //One sample done
    count --;
  }
  
  //Calculate the center and vpp values when channel is selected
  if(flags & 0x01)
  {
    channel1_center = (channel1_max + channel1_min) >> 1;
    channel1_vpp    =  channel1_max - channel1_min;
  }  

  //Calculate the center and vpp values when channel is selected
  if(flags & 0x02)
  {
    channel2_center = (channel2_max + channel2_min) >> 1;
    channel2_vpp    =  channel2_max - channel2_min;
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_init_parameter_ic(void)
{
  int i;
  
  //Prepare FPGA for reading the parameter ic
  fpga_write_cmd(0x64);
  fpga_write_cmd(0x64);
  
  //Need a delay here. In the scope it is delay(20) but not sure what the base of the delay is
  //It works without this one
//  fpga_delay(10);
  
  //Start the read action
  fpga_write_cmd(0x66);
  
  //Wait until the FPGA is ready with reading
  do
  {
    //Send command for status read
    fpga_write_cmd(0x67);
  }
  while((fpga_read_byte() & 0x01) == 0);

  for(i=0;i<7;i++)
  {
    //Send the command for reading a received byte
    fpga_write_cmd(0x68 + i);
    
    //Store in the global buffer
    parameter_buffer[i] = fpga_read_byte();
  }
  
  //Use the MSB of the received data as the next crypt byte
  parameter_crypt_byte = parameter_buffer[3];
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_parameter_ic(uint8 id, uint32 value)
{
  uint8 length = 3;
  int i;

  ByteAndBits crypt_in;
  ByteAndBits crypt_out;
  
  //First data byte is the crypt byte
  parameter_buffer[0] = parameter_crypt_byte;

  //Load the data bytes with the value
  parameter_buffer[3] = (uint8)(value >> 24);
  parameter_buffer[4] = (uint8)(value >> 16);
  parameter_buffer[5] = (uint8)(value >> 8);
  parameter_buffer[6] = (uint8)(value);

  //Check if MSB is actually used
  if(parameter_buffer[3] == 0x00)
  {
    //Set the MSB to a fixed value if not used
    parameter_buffer[3] = 0x69;
    
    //Take one of the length
    length--;

    //When MSB is not used check if MLSB is actually used
    if(parameter_buffer[4] == 0x00)
    {
      //Set the MLSB to a fixed value if not used
      parameter_buffer[4] = 0x96;
      
      //Take one of the length
      length--;

      //When MSB and MLSB are not used check if LMSB is actually used
      if(parameter_buffer[5] == 0x00)
      {
        //Set the LMSB to a fixed value if not used
        parameter_buffer[5] = 0x99;
        
        //Take one of the length
        length--;
      }
    }
  }

  //Set the parameter id mixed with the length of the value
  parameter_buffer[1] = (id << 2) | length;
  
  //Crypt the bytes
  for(i=1;i<7;i++)
  {
    //Crypting is an xor with the crypt byte
    parameter_buffer[i] ^= parameter_crypt_byte;
  }

  //Mangle the crypt byte
  crypt_in.byte = parameter_buffer[0];

  //Basically a swapping of bits in pairs
  crypt_out.bits.b0 = crypt_in.bits.b5;
  crypt_out.bits.b1 = crypt_in.bits.b3;
  crypt_out.bits.b2 = crypt_in.bits.b7;
  crypt_out.bits.b3 = crypt_in.bits.b1;
  crypt_out.bits.b4 = crypt_in.bits.b6;
  crypt_out.bits.b5 = crypt_in.bits.b0;
  crypt_out.bits.b6 = crypt_in.bits.b4;
  crypt_out.bits.b7 = crypt_in.bits.b2;

  //Put it back in the buffer
  parameter_buffer[0] = crypt_out.byte;
  
  //Calculate the checksum
  parameter_buffer[2] = parameter_buffer[0] + parameter_buffer[1] + parameter_buffer[3] + parameter_buffer[4] + parameter_buffer[5] + parameter_buffer[6];
  
  //Prepare FPGA for writing to the parameter ic
  fpga_write_cmd(0x65);
  fpga_write_cmd(0x65);
  
  //Write the data to the FPGA
  for(i=0;i<7;i++)
  {
    //Send the command for writing a send byte
    fpga_write_cmd(0x68 + i);
    
    //Write the byte to the FPGA
    fpga_write_byte(parameter_buffer[i]);
  }
  
  //Start the write action
  fpga_write_cmd(0x66);
  
  //Wait until the FPGA is ready with writing
  do
  {
    //Send command for status read
    fpga_write_cmd(0x67);
  }
  while((fpga_read_byte() & 0x01) == 0);
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 fpga_read_parameter_ic(uint8 id, uint32 value)
{
  int32  i = 0;
  int32  j = 0;
  int32  unvalid = 0;
  uint32 rcv_value;
  uint8  checksum;
  
  //Max retry on write read sequence
  while(i < 6)
  {
    //Start the sequence with a write
    fpga_write_parameter_ic(id, value);
    
    //Need a delay here. In the scope it is delay(500) but not sure what the base of the delay is
    //This one is actually needed to allow the parameter ic to respond. Tweaked with a scope attached to make sure no resend is done
    fpga_delay(500);
    
    //Reset counter
    j=0;
    
    //Max retry on read
    while(j < 50)
    {
      //Assume all will go well
      unvalid = 0;
      
      //Prepare FPGA for reading the parameter ic
      fpga_write_cmd(0x64);
      fpga_write_cmd(0x64);

      //Need a delay here. In the scope it is delay(20) but not sure what the base of the delay is
      //It works without this one
//      fpga_delay(10);

      //Start the read action
      fpga_write_cmd(0x66);

      //Wait until the FPGA is ready with reading
      do
      {
        //Send command for status read
        fpga_write_cmd(0x67);
      }
      while((fpga_read_byte() & 0x01) == 0);

      for(i=0;i<7;i++)
      {
        //Send the command for reading a received byte
        fpga_write_cmd(0x68 + i);

        //Store in the global buffer
        parameter_buffer[i] = fpga_read_byte();
      }
      
      //Get the crypt byte and invert it
      parameter_crypt_byte = ~parameter_buffer[0];
      
      //Decrypt the bytes
      for(i=1;i<7;i++)
      {
        //Decrypting is an xor with the crypt byte
        parameter_buffer[i] ^= parameter_crypt_byte;
      }
      
      //Restore the value
      rcv_value = 0;

      //Check the type byte on which bytes to use
      switch(parameter_buffer[1])
      {
        case 0xAA:
          rcv_value = (parameter_buffer[3] << 24);
         
        case 0xA5:
          rcv_value |= (parameter_buffer[4] << 16);
         
        case 0x5A:
          rcv_value |= (parameter_buffer[5] << 8);
         
        case 0x55:
          rcv_value |= parameter_buffer[6];
          break;
          
        default:
          unvalid = 1;
          break;
      }
      
      //Check if valid data type given
      if(unvalid == 0)
      {
        //Calculate the checksum
        checksum = parameter_crypt_byte + parameter_buffer[1] + parameter_buffer[3] + parameter_buffer[4] + parameter_buffer[5] + parameter_buffer[6];
        
        //Check if the checksum is correct
        if(checksum == parameter_buffer[2])
        {
          //Return the valid value
          return(rcv_value);
        }
      }
      
      //Need a delay here. In the scope it is delay(100) but not sure what the base of the delay is
      //It works without this one
      fpga_delay(100);
      
      //One more try if not valid
      j++;
    }
    
    //One more complete sequence try if not valid
    i++;
  }
  
  //If all fails just return 0
  return(0);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_delay(uint32 usec)
{
  uint32 loops = usec * 54;

  __asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"  "bne 1b":"=r"(loops):"0"(loops));
}

//----------------------------------------------------------------------------------------------------------------------------------
