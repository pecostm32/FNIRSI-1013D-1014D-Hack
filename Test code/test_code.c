//These sections of code can be used in the main function just before the endless while(1) loop


#if 0
//Code for creating 18 files with sample data and measurement data to get an insight in the calibration process
//A file is created per sample rate. Within each file there are sample buffers per channel, offset and volt per div setting
  int8  filename[100];
  int8  *ptr;
  int32  samplerate;

  //Disable the trigger circuit
  scopesettings.samplemode = 0;
  
  //Set number of samples
  scopesettings.samplecount = 3000;
  scopesettings.nofsamples  = 1500;
  
  
  for(samplerate=0;samplerate<18;samplerate++)
  {
    memcpy(filename, "calibration_data_", 17);

    ptr = scope_print_decimal(&filename[17], samplerate, 0);

    memcpy(ptr, ".bin", 5);

    //Create a file for the touch panel configuration. Fails if it already exists
    if(f_open(&viewfp, filename, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
    {
      int32   offset;
      int32   voltperdiv;
      uint32 *ptr;

      //Set the needed sample rate
      //Set the clock divider??
      fpga_set_sample_rate(sample_rate_time_per_div[samplerate]);
      
      //Set the trigger base
      scopesettings.timeperdiv = sample_rate_time_per_div[samplerate];
      fpga_set_time_base();
      
      
      //Need to clear the compensation values before doing the calibration
      scopesettings.channel1.adc1compensation = 0;
      scopesettings.channel1.adc2compensation = 0;
      scopesettings.channel2.adc1compensation = 0;
      scopesettings.channel2.adc2compensation = 0;

      for(voltperdiv=0;voltperdiv<6;voltperdiv++)
      {
        scopesettings.channel1.voltperdiv = voltperdiv;
        scopesettings.channel2.voltperdiv = voltperdiv;

        //Load the settings into the FPGA
        fpga_set_channel_voltperdiv(&scopesettings.channel1);
        fpga_set_channel_voltperdiv(&scopesettings.channel2);

        //Wait 50ms to settle
        timer0_delay(50);

        //Find the top offset value by going from bottom 200 to top 1500 in increments of 50
        for(offset=200;offset<=1500;offset+=50)
        {
          //Write the offset for both channels to the FPGA
          fpga_set_channel_trace_offsets(offset);

          //Wait 50ms to settle
          timer0_delay(50);

          //Do a conversion run and wait until it is done
          fpga_do_conversion();

          //Get the average from a sample run
          fpga_read_sample_data(&scopesettings.channel1, 100);

          f_write(&viewfp, channel1tracebuffer1, sizeof(channel1tracebuffer1), 0);

          //Get the average from a sample run
          fpga_read_sample_data(&scopesettings.channel2, 100);

          f_write(&viewfp, channel2tracebuffer1, sizeof(channel2tracebuffer1), 0);

          ptr = channel1tracebuffer4;

          *ptr++ = scopesettings.channel1.adc1rawaverage;
          *ptr++ = scopesettings.channel1.adc2rawaverage;
          *ptr++ = scopesettings.channel1.min;
          *ptr++ = scopesettings.channel1.max;
          *ptr++ = scopesettings.channel1.average;
          *ptr++ = scopesettings.channel1.peakpeak;
          *ptr++ = scopesettings.channel1.center;
          *ptr++ = 0;

          *ptr++ = scopesettings.channel2.adc1rawaverage;
          *ptr++ = scopesettings.channel2.adc2rawaverage;
          *ptr++ = scopesettings.channel2.min;
          *ptr++ = scopesettings.channel2.max;
          *ptr++ = scopesettings.channel2.average;
          *ptr++ = scopesettings.channel2.peakpeak;
          *ptr++ = scopesettings.channel2.center;
          *ptr++ = 0;

          f_write(&viewfp, channel1tracebuffer4, 64, 0);
        }  
      }

      //Close the file to finish the write
      f_close(&viewfp);
    }
  }  

  //Show the saved successful message
  scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
#endif  


#if 0
//Parameter 0x12 is for getting the trace offset value
//It returns the signed 32 bits result of the high 16 bits minus the low 16 bits times 100
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    int32 offset;
    uint32 offset1;
    uint32 offset2;
    int8   valuestring[100];
    int8  *ptr;
    
    int8 headerstring[] = "low,high,result\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    for(offset1=200;offset1<=1500;offset1+=50)
    {
      for(offset2=1500;offset2>=200;offset2-=50)
      {
        offset = fpga_read_parameter_ic(0x12, (offset1 & 0x0000FFFF) | (offset2 << 16));

        ptr = scope_print_decimal(valuestring, offset1, 0);
        
        *ptr++ = ',';
        
        ptr = scope_print_decimal(ptr, offset2, 0);
        
        *ptr++ = ',';
        
        if(offset < 0)
        {
          *ptr++ = '-';
          
          offset = -offset;
        }
        
        ptr = scope_print_decimal(ptr, offset, 0);

        *ptr++ = '\n';

        f_write(&viewfp, valuestring, ptr - valuestring, 0);
      }
    }

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif


#if 0
//The 0x0C and 0x0D parameters are for getting the FPGA sample read command. No matter if the trigger channel is 0 or 1 it always returns the same values
//0x0C ==> 0x20
//0x0D ==> 0x22

//At first I thought it was needed to obtain the correct sample data, but a final test shows it does not.
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    uint32 command;
    int8   valuestring[1000];
    int8  *ptr;
    
    int8 headerstring[] = "fpga channel command read\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    command = fpga_read_parameter_ic(0x0C, 0);

    int8 text1[] = "channel1 command, channel1 trigger source: ";

    f_write(&viewfp, text1, sizeof(text1) - 1, 0);
    
    ptr = scope_print_decimal(valuestring, command, 0);
    *ptr++ = '\n';

    f_write(&viewfp, valuestring, ptr - valuestring, 0);

    command = fpga_read_parameter_ic(0x0C, 1);

    int8 text2[] = "channel1 command, channel2 trigger source: ";

    f_write(&viewfp, text2, sizeof(text2) - 1, 0);
    
    ptr = scope_print_decimal(valuestring, command, 0);
    *ptr++ = '\n';

    f_write(&viewfp, valuestring, ptr - valuestring, 0);

    command = fpga_read_parameter_ic(0x0D, 0);

    int8 text3[] = "channel2 command, channel1 trigger source: ";

    f_write(&viewfp, text3, sizeof(text3) - 1, 0);
    
    ptr = scope_print_decimal(valuestring, command, 0);
    *ptr++ = '\n';

    f_write(&viewfp, valuestring, ptr - valuestring, 0);

    command = fpga_read_parameter_ic(0x0D, 1);

    int8 text4[] = "channel2 command, channel2 trigger source: ";

    f_write(&viewfp, text4, sizeof(text4) - 1, 0);
    
    ptr = scope_print_decimal(valuestring, command, 0);
    *ptr++ = '\n';

    f_write(&viewfp, valuestring, ptr - valuestring, 0);

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif


#if 0
//Returns the same values as already found in the software
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    uint32 voltperdiv;
    uint32 adjuster;
    int8   valuestring[1000];
    int8  *ptr;
    
    int8 headerstring[] = "parameter 0x0B read\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    for(voltperdiv=0;voltperdiv<7;voltperdiv++)
    {
      adjuster = fpga_read_parameter_ic(0x0B, voltperdiv);
      
      ptr = scope_print_decimal(valuestring, voltperdiv, 0);
      *ptr++ = ',';
        
      ptr = scope_print_decimal(ptr, adjuster, 0);
      *ptr++ = '\n';

      f_write(&viewfp, valuestring, ptr - valuestring, 0);
    }

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif


#if 0
//This returns a value to set to the FPGA clock divider by the looks of it
//The data is always written to the 0x0D command of the FPGA
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    uint32 timebase;
    uint32 data;
    uint32 command;
    int8   valuestring[1000];
    int8  *ptr;
    
    int8 headerstring[] = "parameter 0x0A read\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    for(timebase=0;timebase<34;timebase++)
    {
      data = fpga_read_parameter_ic(0x0A, timebase);

      //Get the FPGA command that needs the setting
      command = fpga_read_parameter_ic(0x14, 0xED);
      
      ptr = scope_print_decimal(valuestring, timebase, 0);
      *ptr++ = ',';
        
      ptr = scope_print_decimal(ptr, command, 0);
      *ptr++ = ',';
      
      ptr = scope_print_decimal(ptr, data, 0);
      *ptr++ = '\n';

      f_write(&viewfp, valuestring, ptr - valuestring, 0);
    }

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif


#if 0
//The brightness is translated based on a simple formula. (brightness * 560) + 4000
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    uint32 brightness;
    uint32 data;
    int8   valuestring[1000];
    int8  *ptr;
    
    int8 headerstring[] = "parameter 0x10 read\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    for(brightness=0;brightness<101;brightness++)
    {
      data = fpga_read_parameter_ic(0x10, brightness);

      
      ptr = scope_print_decimal(valuestring, brightness, 0);
      *ptr++ = ',';
        
      ptr = scope_print_decimal(ptr, data, 0);
      *ptr++ = '\n';

      f_write(&viewfp, valuestring, ptr - valuestring, 0);
    }

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif


#if 0
//No matter the input value it returns 32431
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    uint32 level;
    uint32 data;
    int8   valuestring[1000];
    int8  *ptr;
    
    int8 headerstring[] = "parameter 0x16 read\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    for(level=0;level<=30000;level++)
    {
      data = fpga_read_parameter_ic(0x16, level);
      
      ptr = scope_print_decimal(valuestring, level, 0);
      *ptr++ = ',';
        
      ptr = scope_print_decimal(ptr, data, 0);
      *ptr++ = '\n';

      f_write(&viewfp, valuestring, ptr - valuestring, 0);
    }

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif


#if 0
//Parameter 0x11 returns some pattern in the data that needs to be figured out
//worped is shifted right 4 positions and then 2 is added
  //Data read out special IC
  if(f_open(&viewfp, "special_ic_data.txt", FA_WRITE) == FR_OK)
  {
    uint32 input;
    uint8  byte1;
    uint8  byte2;
    uint32 worped;
    uint32 data;
    int8   valuestring[1000];
    int8  *ptr;
    
    //Need to figure out how the trigger point calculation works
    //The parameter ic is used to do some data manipulation
    //parameter 0x11
  //Get the data, only 4 bits for first byte
//  data1 = fpga_read_byte() & 0x0F;
//  data2 = fpga_read_byte();

    //Data   //Prepare for translation
    //data = (data1 << 12) | (data2 << 4) | data1;
    //need to figure this out
    
    int8 headerstring[] = "parameter 0x11 read\n";

    f_write(&viewfp, headerstring, sizeof(headerstring) - 1, 0);

    for(input=0;input<=3000;input++)
    {
      byte1 = input & 0x0F;
      byte2 = (input >> 8) & 0xFF;
      
      worped = (byte1 << 12) | (byte2 << 4) | byte1;
      
      data = fpga_read_parameter_ic(0x11, worped);
      
      ptr = scope_print_decimal(valuestring, input, 0);
      *ptr++ = ',';

      ptr = scope_print_decimal(ptr, byte1, 0);
      *ptr++ = ',';
      
      ptr = scope_print_decimal(ptr, byte2, 0);
      *ptr++ = ',';
      
      ptr = scope_print_decimal(ptr, worped, 0);
      *ptr++ = ',';
      
      ptr = scope_print_decimal(ptr, data, 0);
      *ptr++ = '\n';

      f_write(&viewfp, valuestring, ptr - valuestring, 0);
    }

    //Close the file to finish the write
    f_close(&viewfp);

    //Show the saved successful message
    scope_display_file_status_message(MESSAGE_SAVE_SUCCESSFUL, 1);
  }
#endif



