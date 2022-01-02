//----------------------------------------------------------------------------------------------------------------------------------

#include "fpga_control.h"
#include "fnirsi_1013d_scope.h"
#include "touchpanel.h"
#include "timer.h"
#include "variables.h"

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
  data = (scopesettings.screenbrightness * 560) + 4000;
  
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

void fpga_set_channel_enable(PCHANNELSETTINGS settings)
{
  //Send the command for channel enable to the FPGA
  fpga_write_cmd(settings->enablecommand);
  
  //Write the needed data based on the setting
  if(settings->enable == 0)
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

void fpga_set_channel_coupling(PCHANNELSETTINGS settings)
{
  //Send the command for channel 1 coupling to the FPGA
  fpga_write_cmd(settings->couplingcommand);
  
  //Write the needed data based on the setting
  if(settings->coupling == 0)
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

void fpga_set_channel_voltperdiv(PCHANNELSETTINGS settings)
{
  register uint32 setting = settings->voltperdiv;
  
  //Send the command for channel 1 volts per div to the FPGA
  fpga_write_cmd(settings->voltperdivcommand);
  
  //Check if setting in range of what is allowed
  if(setting > 5)
    setting = 5;
  
  //Write it to the FPGA
  fpga_write_byte(setting);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_channel_offset(PCHANNELSETTINGS settings)
{
  //Send the command for channel DC offset to the FPGA
  fpga_write_cmd(settings->offsetcommand);

  //Write the center offset data for this channel and volt per div setting
  fpga_write_short(settings->dc_calibration_offset[settings->voltperdiv]);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_sample_rate(uint32 samplerate)
{
  //Translate the time per div setting to what the FPGA needs
  //22-11-2021 Since the long time base settings have been removed and the system does things differently a translation is needed here
  //Old time base was 0 for 50S/div to 29 for 10nS/div
  //This is no longer the case. 0 means 200mS/div but needs the setting for 50mS/div. Same for 100mS/div. Simplest solution is a translation table
  
  //This most likely needs to be based on the acquisition speed and no longer the time per div setting, but that needs further investigation
  
  //Make sure the setting is in range of the table
  if(samplerate < (sizeof(sample_rate_settings) / sizeof(uint32)))
  {
    //Write the command to the FPGA
    fpga_write_cmd(0x0D);

    //Write the time base clock setting to the FPGA
    fpga_write_int(sample_rate_settings[samplerate]);
  }
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
  uint32 traceposition;
  int32  level;
  
  //The trace position on screen equals to ADC reading 128
  //The trigger vertical position is relative to the trace position.
  //The screen position values are volt/div related, so conversion to ADC level is needed
  
  //Check which channel is used for triggering
  if(scopesettings.triggerchannel == 0)
  {
    //Channel 1, so use its data
    voltperdiv    = scopesettings.channel1.voltperdiv;
    traceposition = scopesettings.channel1.traceposition;
  }
  else
  {
    //Channel 2, so use its data
    voltperdiv    = scopesettings.channel2.voltperdiv;
    traceposition = scopesettings.channel2.traceposition;
  }
  
  //The difference between the two positions determines the level offset on 128, but it needs to be scaled back first
  level = ((((int32)traceposition - (int32)scopesettings.triggerverticalposition) * 4194304) / (41954 * signal_adjusters[voltperdiv])) + 128;
  
  //Limit on extremes
  if(level < 0)
  {
    level = 0;
  }
  else if(level > 255)
  {
    level = 255;
  }
  
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

void fpga_set_time_base(uint32 timebase)
{
  //Write the command to set the short time base data to the FPGA
  fpga_write_cmd(0x0E);
  
  //Make sure setting is in range
  if(timebase < (sizeof(timebase_settings) / sizeof(uint32)))
  {
    //Table settings ranges from setting 0 (200mS/div) to 23 (5nS/div)
    fpga_write_int(timebase_settings[timebase]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_do_conversion(void)
{
  //Check if sampling with trigger system enabled
  if(scopesettings.samplemode == 1)
  {
    //Enable trigger system???
    fpga_write_cmd(0x0F);
    fpga_write_byte(0x00);
  }
  else
  {
    //Disable the trigger circuit??
    fpga_write_cmd(0x0F);
    fpga_write_byte(0x01);
  }
  
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
  
  //Check if sampling with trigger system enabled
  if(scopesettings.samplemode == 1)
  {
    //Wait for the FPGA to signal triggered or touch panel is touched
    while(((fpga_read_byte() & 1) == 0) && (havetouch == 0))
    {
      //Scan the touch panel
      tp_i2c_read_status();
    }
    
    //Disable trigger system???
    fpga_write_cmd(0x0F);
    fpga_write_byte(0x01);
  }
  else
  {
    //Wait for the FPGA to signal triggered or buffer full
    while((fpga_read_byte() & 1) == 0);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

uint16 fpga_prepare_for_transfer(void)
{
  uint32 data;
  
  //Send the command for getting some data from the FPGA
  fpga_write_cmd(0x14);
  
  //Get the data, only 4 bits for first byte
//  data1 = fpga_read_byte() & 0x0F;
//  data2 = fpga_read_byte();
  
  //Prepare the data
//  data = (((data1 << 12) | (data2 << 4) | data1) >> 4) + 2;
  
  //Just read a short, and with 0x0FFF and add 2
  //Have to see if the add 2 is needed
  data = (fpga_read_short() & 0x0FFF) + 2;
 
  return(data & 0x0FFF);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_read_sample_data(PCHANNELSETTINGS settings, uint32 triggerpoint)
{
  //Clear min and max and average for new calculations
  settings->min     = 0x7FFFFFFF;
  settings->max     = 0;
  settings->average = 0;
  
  //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
  fpga_write_cmd(0x1F);
  fpga_write_short(triggerpoint);
  
  //Send a command for getting ADC1 trace data from the FPGA
  fpga_write_cmd(settings->adc1command);
  
  //Signal no checking on the first ADC when compensating
  settings->checkfirstadc = 0;
  
  //Setup for reading the first ADC
  settings->compensation = settings->adc1compensation;
  settings->buffer = &settings->tracebuffer[1];
  
  //Read the data for the first ADC. Samples start on the second location, skipping every other sample
  fpga_read_adc_data(settings);

  //Save the calculated measurements
  settings->adc1rawaverage = settings->rawaverage;
  
  //Send command 0x1F to the FPGA followed by the translated data returned from command 0x14
  fpga_write_cmd(0x1F);
  fpga_write_short(triggerpoint);
  
  //Send a command for getting ADC2 trace data from the FPGA
  fpga_write_cmd(settings->adc2command);

  //Signal to check the readings of the first ADC on being zero when compensating
  settings->checkfirstadc = 1;

  //Setup for reading the first ADC
  settings->compensation = settings->adc2compensation;
  settings->buffer = &settings->tracebuffer[0];
  
  //Read the data for the second ADC. Samples start on the first location, skipping every other sample
  fpga_read_adc_data(settings);

  //Save the calculated measurements
  settings->adc2rawaverage = settings->rawaverage;
  
  //Calculate the overall average
  settings->average /= scopesettings.samplecount;

  //Calculate the peak to peak value
  settings->peakpeak = settings->max - settings->min;
  
  //Calculate the signal center
  settings->center = (settings->max + settings->min) / 2;
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_read_adc_data(PCHANNELSETTINGS settings)
{
  register int32  sample;
  register uint32 count;
  register uint32 sum = 0;
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();
  
  //Set the number of samples to read
  count = scopesettings.nofsamples;
  
  //Read the data as long as there is count
  while(count)
  {
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();

    //Read the data
    sample = FPGA_GET_DATA();
    
    //Sum the raw data for ADC difference calibration
    sum += sample;

    //Compensate the value for ADC in equality
    sample += settings->compensation;
    
    //Check if sample became negative
    if(sample < 0)
    {
      //Keep it on zero if so
      sample = 0;
    }
    
    //Check if sample over its max
    if(sample > 255)
    {
      //Keep it on max if so
      sample = 255;
    }
    
//Need to do the same for the top end of the reading. Have to figure out what is actually needed    
    
    //Check if busy with second ADC data
    if(settings->checkfirstadc)
    {
      //When ADC1 compensation is positive it bottoms out on this value
      if(settings->adc1compensation > 0)
      {
        //So when the compensated sample is below the positive ADC1 compensation value the reading need to be matched
        //The negative value is either equal or one less then the positive value in absolute sense
        if(sample < settings->adc1compensation)
        {
          //Match the two readings when within compensation range
          settings->buffer[1] = sample;
        }
      }
      else
      {
        //When ADC1 compensation is negative, ADC2 reading might need to be matched
        if(*settings->buffer < settings->adc2compensation)
        {
          //If that is the case get the ADC1 sample from the buffer
          sample = settings->buffer[1];
        }
      }
    }
    else
    {
      //When ADC2 compensation is positive it will bottom out on this value
      //So when the compensated sample is below the made positive ADC1 compensation value the readings need to be matched
      //For this the raw ADC1 sample is written to the ADC2 location
      
      //When ADC2 compensation is positive save the ADC1 sample for possible matching
      if(settings->adc2compensation > 0)
      {
        settings->buffer[-1] = sample;
      }
    }
    
    //Get the minimum value of the samples
    if(sample < settings->min)
    {
      //Keep the lowest
      settings->min = sample;
    }
    
    //Get the maximum value of the samples
    if(sample > settings->max)
    {
      //Keep the highest
      settings->max = sample;
    }
    
    //Add the samples for average calculation
    settings->average += sample;

    
    
    
    
    
    
    //Store the data
    *settings->buffer = sample;
    
    //Skip a sample to allow for ADC2 data to be placed into
    settings->buffer += 2;
    
    //One read done
    count--;
  }
 
  //Calculate the raw average
  settings->rawaverage = sum / scopesettings.nofsamples;
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_set_battery_level(void)
{
  //Send the command for setting the battery level to the FPGA??
  fpga_write_cmd(0x3C);
  
  //Write the data
  fpga_write_short(32431);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_write_command_0x1F(uint32 data)
{
  fpga_write_cmd(0x1F);
  fpga_write_short(data);
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
    channel2_min = 0x0FFFFFFF;
    channel2_max = 0x00000000;
  }  

  //Read the data as long as there is count
  while(count)
  {
    //Variable delay based on the current count
    fpga_delay(1001 - count);
    
    //Get and process the sample when the channel is selected
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
 
    //Get and process the sample when the channel is selected
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

uint32 fpga_get_zero_crossings(uint32 channel)
{
  register uint32 count;
  register uint32 sample;
  register uint32 zerocrossings = 0;
  register uint32 state = 0;
  register uint32 highlevel;
  register uint32 lowlevel;
  register uint32 signaladjust;
  
  //Set the number of samples to process based on the time base setting
  if(scopesettings.timeperdiv < 4)
  {
    //For 50ms and 20ms it is only 750 samples
    count = 750;
  }
  else
  {
    //For 10ms - 10ns it is 1500 samples
    count = 1500;
  }
  
  //No idea what this is for, but in normal sample processing this is a value obtained from the special ic
  fpga_write_command_0x1F(100);

  if(channel == 0)
  {
    //Send the command for selecting the channels sample buffer
    fpga_write_cmd(0x20);
    
//    highlevel = scopesettings.channel1.traceoffset + 8;
//    lowlevel  = scopesettings.channel1.traceoffset - 8;
    highlevel = 136;
    lowlevel  = 120;
    
    signaladjust = signal_adjusters[scopesettings.channel1.voltperdiv];
  }
  else
  {
    //Send the command for selecting the channels sample buffer
    fpga_write_cmd(0x22);
    
//    highlevel = scopesettings.channel2.traceoffset + 8;
//    lowlevel  = scopesettings.channel2.traceoffset - 8;
    highlevel = 136;
    lowlevel  = 120;
    
    signaladjust = signal_adjusters[scopesettings.channel2.voltperdiv];
  }
  
  //Set the bus for reading
  FPGA_BUS_DIR_IN();
  
  //Set the control lines for reading a command
  FPGA_DATA_READ();
  
  //Read the data as long as there is count
  while(count)
  {
    //Clock the data to the output of the FPGA
    FPGA_PULSE_CLK();

    sample = FPGA_GET_DATA();
    
    //Adjust the data for the correct voltage per div setting
    sample = (41954 * sample * signaladjust) >> 22;

    //Limit the sample on max displayable
    if(sample > 401)
    {
      sample = 401;
    }
    
    //For actual frequency determination the number of average samples between up going zero crossings are needed
    
    //Check against the high level
    if(sample > highlevel)
    {
      //If above check if in low state
      if(state == 0)
      {
        //If so flip the state
        state = 1;

        //Found a zero crossing
        zerocrossings++;
      }
    }
    //Check against the low level
    else if(sample < lowlevel)
    {
      //If below check if in high state
      if(state == 1)
      {
        //If so flip the state
        state = 0;
        
        //Found a zero crossing
        zerocrossings++;
      }
    }
    
    //One read done
    count--;
  }
  
  return(zerocrossings);
}

//----------------------------------------------------------------------------------------------------------------------------------

void fpga_delay(uint32 usec)
{
  uint32 loops = usec * 54;

  __asm__ __volatile__ ("1:\n" "subs %0, %1, #1\n"  "bne 1b":"=r"(loops):"0"(loops));
}

//----------------------------------------------------------------------------------------------------------------------------------
