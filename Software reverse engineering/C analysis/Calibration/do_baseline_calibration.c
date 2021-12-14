//--------------------------------------------------------------------------------

int do_baseline_calibration(void)

{
  int iVar1;
  undefined *puVar2;
  uchar uVar3;
  int iVar4;
  int iVar5;
  
  puVar2 = PTR_DAT_80027fe4;                                       //0x80192ED4
  iVar1 = DAT_80027fe0;                                            //0x8019D5A0  Settings base

  *(undefined *)(DAT_80027fe0 + 0x3a) = 0;                         //Scope run mode to running

  //Save some settings
  *(ushort *)(puVar2 + 2) = (ushort)*(byte *)(iVar1 + 10);         //timebase time/div
  *(ushort *)(puVar2 + 4) = (ushort)*(byte *)(iVar1 + 3);          //channel 1 volts/div
  *(ushort *)(puVar2 + 6) = (ushort)*(byte *)(iVar1 + 0xf);        //channel 2 volts/div
  *(undefined2 *)(puVar2 + 8) = *(undefined2 *)(iVar1 + 6);        //channel 1 trace offset
  *(undefined2 *)(puVar2 + 10) = *(undefined2 *)(iVar1 + 0x12);    //channel 2 trace offset
  *(undefined2 *)(puVar2 + 0xc) = *(undefined2 *)(iVar1 + 0x26);   //trigger level screen offset


  iVar4 = do_trace_offset_calibration();                           //When a 1 is returned the calibration was successful

  iVar5 = do_adc1_adc2_diff_calibration();

  //Restore the saved settings
  *(undefined *)(iVar1 + 10) = puVar2[2];
  *(undefined *)(iVar1 + 3) = puVar2[4];
  *(undefined *)(iVar1 + 0xf) = puVar2[6];
  *(undefined2 *)(iVar1 + 6) = *(undefined2 *)(puVar2 + 8);
  *(undefined2 *)(iVar1 + 0x12) = *(undefined2 *)(puVar2 + 10);
  *(undefined2 *)(iVar1 + 0x26) = *(undefined2 *)(puVar2 + 0xc);

  //Load the settings back to the FPGA
  fpga_write_cmd('3');  //0x33  Channel 1 volt/div setting

  if (*(char *)(iVar1 + 3) == '\x06')   //channel 1 volts/div setting
  {
    uVar3 = '\x05';
  }
  else
  {
    uVar3 = *(uchar *)(iVar1 + 3);
  }

  fpga_write_data(uVar3);

  fpga_write_cmd('6');   //0x36  Channel 2 volt/div setting

  if (*(char *)(iVar1 + 0xf) == '\x06')  //channel 2 volts/div setting
  {
    uVar3 = '\x05';
  }
  else
  {
    uVar3 = *(uchar *)(iVar1 + 0xf);
  }

  fpga_write_data(uVar3);

  set_fpga_channel1_offset();
  set_fpga_channel2_offset();
  set_fpga_trigger_timebase();
  set_fpga_trigger_level();

  return (uint)(iVar4 != 0 && iVar5 != 0);
}

//--------------------------------------------------------------------------------
//Only called from baseline calibration

bool do_trace_offset_calibration(void)

{
  longlong lVar1;
  bool bVar2;
  bool bVar3;
  ushort *puVar4;
  uchar uVar5;
  byte bVar6;
  ushort uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint local_64;
  uint local_58;
  uint local_44;
  uint local_40;
  uint local_3c;
  uint local_38;
  uint local_34;
  uint local_30;
  
  bVar2 = false;
  bVar3 = false;

  fpga_setup_for_calib();           //Ends with command 0x0F ==> 0x01 which might be a no trigger needed flag

  uVar13 = 200;                     //Some base trace offset value, also set in the previous function

  fpga_write_cmd('2');               //0x32    channel 1 trace offset
  fpga_write_data('\0');
  fpga_write_data(-0x38);

  fpga_write_cmd('5');               //0x35    channel 2 trace offset
  fpga_write_data('\0');
  fpga_write_data(-0x38);

  delay_2(0x32);                     //Wait 50ms to settle (timer tick delay)


  //This first step is done on 5V/div setting (1x probe magnificaton)

  //Some determination if the trace offsets are within some limits???
  //First try is offset 200, every next try adds 50
  do
  {
    uVar5 = (uchar)(uVar13 >> 8);     //Get high byte of trace offset

    fpga_write_cmd('2');              //0x32    channel 1 trace offset
    fpga_write_data(uVar5);
    fpga_write_data((uchar)uVar13);

    fpga_write_cmd('5');               //0x35    channel 2 trace offset
    fpga_write_data(uVar5);
    fpga_write_data((uchar)uVar13);

    delay_2(0x32);

    fpga_start_calib_conversion();

    do                                    //Wait for the conversion to be done
    {
      iVar8 = fpga_check_conversion_ready();
    } while (iVar8 == 0);

    write_fpga_cmd_0x1F(100);              //Also done in normal aquisition but there the data is obtained from the special ic and modified based on settings and value
    fpga_read_channel1_adc1_samples();          //Samples are stored in the first buffer for this channel 
    calib_adjust_channel_1_samples();      //Uses the 0x0B special ic command to get the adjuster and does the same as normal acquisition code
    calib_copy_ch1_buf3_to_buf4();
    calib_ch1_limit_samples_on_401();

    uVar9 = calib_average_samples(DAT_80003c18);    //0801AC04A   Fourth sample buffer

    if ((!bVar2) && (uVar9 < 0x17d))       //381 ???
    {
      bVar2 = true;
      local_58 = uVar13;      //Save the offset for channel 1 and the actual measured value
      local_38 = uVar9;
    }

    write_fpga_cmd_0x1F(100);              //Do channel 2
    fpga_read_channel2_adc1_samples();
    calib_adjust_channel_2_samples();
    calib_copy_ch2_buf3_to_buf4();
    calib_ch2_limit_samples_on_401();

    uVar9 = calib_average_samples(DAT_80003c1c);      //0x801AD7BA  channel 2 fourth sample buffer

    if ((!bVar3) && (uVar9 < 0x17d))
    {
      bVar3 = true;
      local_64 = uVar13;      //Save the offset for channel 2 and the actual measured value
      local_3c = uVar9;
    }
  } while ((!bVar2 || !bVar3) && (uVar13 = uVar13 + 0x32 & 0xfffeffff, uVar13 < DAT_80003c20));  //As long as not found and offset less then 1500


  //Second loop to get the lower limit??
  //Steps of 50 and not lower then 200
  bVar2 = false;
  bVar3 = false;
  uVar13 = DAT_80003c20;  //Start on offset 1500
  do
  {
    uVar5 = (uchar)(uVar13 >> 8);

    fpga_write_cmd('2');
    fpga_write_data(uVar5);
    fpga_write_data((uchar)uVar13);

    fpga_write_cmd('5');
    fpga_write_data(uVar5);
    fpga_write_data((uchar)uVar13);

    delay_2(0x32);

    fpga_start_calib_conversion();

    do 
    {
      iVar8 = fpga_check_conversion_ready();
    } while (iVar8 == 0);

    write_fpga_cmd_0x1F(100);
    fpga_read_channel1_adc1_samples();
    calib_adjust_channel_1_samples();
    calib_copy_ch1_buf3_to_buf4();
    calib_ch1_limit_samples_on_401();
    uVar9 = calib_average_samples(DAT_80003c18);

    if ((!bVar2) && (0x13 < uVar9))
    {
      bVar2 = true;
      local_40 = uVar9;
      local_30 = uVar13;
    }

    write_fpga_cmd_0x1F(100);
    fpga_read_channel2_adc1_samples();
    calib_adjust_channel_2_samples();
    calib_copy_ch2_buf3_to_buf4();
    calib_ch2_limit_samples_on_401();
    uVar9 = calib_average_samples(DAT_80003c1c);

    if ((!bVar3) && (0x13 < uVar9))
    {
      bVar3 = true;
      local_44 = uVar9;
      local_34 = uVar13;
    }
  } while ((!bVar2 || !bVar3) && (uVar13 = uVar13 - 0x32 & 0xffff, 200 < uVar13));

  //Channel 1 high and low offset send to special ic
  uVar13 = translate_parameter(0x12,local_58 | local_30 << 0x10);

  //Divide the result value with the averaged measured values subtracted from each other (high - low)
  uVar13 = divide(uVar13,local_38 - local_40);

  puVar4 = DAT_80003c28;    //0x802F18B0 base of calibration data
  uVar9 = DAT_80003c24;     //0x51EB851F a multiplication factor

  lVar1 = (longlong)(int)DAT_80003c24 * (longlong)(int)((uVar13 & 0xffff) * local_40);

  //Low result plus fractional multiplied high value
  DAT_80003c28[1] = (short)local_30 + ((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f));  //First calibration value  (channel1_calibration_data[0] in my code)

  //The division result
  *puVar4 = (ushort)uVar13;   //Calibration factor  (channel1_calibration_factor in my code)

  //Channel 2
  uVar13 = translate_parameter(0x12,local_64 | local_34 << 0x10);
  uVar13 = divide(uVar13,local_3c - local_44);
  iVar8 = DAT_80003c2c;
  lVar1 = (longlong)(int)uVar9 * (longlong)(int)((uVar13 & 0xffff) * local_44);
  puVar4[8] = ((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) + (short)local_34;
  puVar4[7] = (ushort)uVar13;


  //Section to determine the other calibration values??
  //Loop throught he other volt/div setting but not the last since that is the same ast the fore last
  //Trace offsets on lowest value
  *(undefined2 *)(iVar8 + 6) = 200;
  set_fpga_channel1_offset();

  *(undefined2 *)(iVar8 + 0x12) = 200;
  set_fpga_channel2_offset();

  uVar13 = translate_parameter(0xb,0);  //Get the adjustment value for 5V/div

  uVar13 = uVar13 & 0xffff;

  uVar14 = 1;

  do
  {
    *(char *)(iVar8 + 3) = (char)uVar14;  //Select channel 1 next volts per div setting

    fpga_write_cmd('3');                  //Write it to the fpga
    if (*(char *)(iVar8 + 3) == '\x06')
    {
      uVar5 = '\x05';
    }
    else
    {
      uVar5 = *(uchar *)(iVar8 + 3);
    }

    fpga_write_data(uVar5);

    *(char *)(iVar8 + 0xf) = (char)uVar14;   //Same for channel 2


    fpga_write_cmd('6');
    if (*(char *)(iVar8 + 0xf) == '\x06')
    {
      uVar5 = '\x05';
    }
    else
    {
      uVar5 = *(uchar *)(iVar8 + 0xf);
    }

    fpga_write_data(uVar5);

    delay_2(100);           //Wait 100ms


    fpga_start_calib_conversion();   //Start a conversion
    do
    {
      iVar10 = fpga_check_conversion_ready();
    } while (iVar10 == 0);

    write_fpga_cmd_0x1F(100);
    fpga_read_channel1_adc1_samples();
    calib_adjust_channel_1_samples();
    calib_copy_ch1_buf3_to_buf4();
    calib_ch1_limit_samples_on_401();
    uVar11 = calib_average_samples(DAT_80003c18);

    if (uVar14 == 1)
    {
      uVar12 = translate_parameter(0xb,1);   //Get volt/div 1 seeting adjustment value
      uVar11 = uVar11 + 1 & 0xfffeffff;

      //Based on measured average some calculation is done
      if (uVar11 < 200)
      {
        uVar7 = *puVar4;    //Get channel1 calibration factor
        iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(*puVar4 * uVar11)) >> 0x20);
        iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
        uVar7 = puVar4[1] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
      }
      else
      {
        lVar1 = (longlong)(int)uVar9 * (longlong)(int)(*puVar4 * uVar11);
        iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)*puVar4 * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
        uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[1];
      }

      //Fill in the second calibration value
      puVar4[2] = uVar7;
    }
    else
    {
      if (uVar14 == 2)
      {
        uVar12 = translate_parameter(0xb,2);

        if (uVar11 < 200)
        {
          uVar7 = *puVar4;
          iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4)) >> 0x20);
          iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
          uVar7 = puVar4[1] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
        }
        else
        {
          lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4);
          iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)*puVar4 * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
          uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[1];
        }

        puVar4[3] = uVar7;   //Third calib valeu
      }
      else
      {
        if (uVar14 == 3)
        {
          uVar12 = translate_parameter(0xb,3);

          if (uVar11 < 200)
          {
            uVar7 = *puVar4;
            iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4)) >> 0x20);
            iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
            uVar7 = puVar4[1] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
          }
          else
          {
            lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4);
            iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)*puVar4 * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
            uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[1];
          }

          puVar4[4] = uVar7;  //Fourth calib value
        }
        else
        {
          if (uVar14 == 4)
          {
            uVar12 = translate_parameter(0xb,4);

            if (uVar11 < 200)
            {
              uVar7 = *puVar4;
              iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4)) >> 0x20);
              iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
              uVar7 = puVar4[1] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
            }
            else
            {
              lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4);
              iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)*puVar4 * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
              uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[1];
            }

            puVar4[5] = uVar7;  //Fifth
          }
          else
          {
            if (uVar14 == 5)
            {
              uVar12 = translate_parameter(0xb,5);

              if (uVar11 < 200)
              {
                uVar7 = *puVar4;
                iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4)) >> 0x20);
                iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
                uVar7 = puVar4[1] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
              }
              else
              {
                lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * *puVar4);
                iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)*puVar4 * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
                uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[1];
              }

              puVar4[6] = uVar7;  //Sixth
            }
          }
        }
      }
    }

    //Channel 2 part
    write_fpga_cmd_0x1F(100);
    fpga_read_channel2_adc1_samples();
    calib_adjust_channel_2_samples();
    calib_copy_ch2_buf3_to_buf4();
    calib_ch2_limit_samples_on_401();
    uVar11 = calib_average_samples(DAT_80003c1c);

    if (uVar14 == 1)
    {
      uVar12 = translate_parameter(0xb,1);
      uVar11 = uVar11 + 1 & 0xfffeffff;
      if (uVar11 < 200)
      {
        uVar7 = puVar4[7];
        iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(puVar4[7] * uVar11)) >> 0x20);
        iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
        uVar7 = puVar4[8] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
      }
      else {
        lVar1 = (longlong)(int)uVar9 * (longlong)(int)(puVar4[7] * uVar11);
        iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)puVar4[7] * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
        uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[8];
      }
      puVar4[9] = uVar7;
    }
    else {
      if (uVar14 == 2) {
        uVar12 = translate_parameter(0xb,2);
        if (uVar11 < 200) {
          uVar7 = puVar4[7];
          iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7])) >> 0x20);
          iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
          uVar7 = puVar4[8] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
        }
        else {
          lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7]);
          iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)puVar4[7] * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
          uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[8];
        }
        puVar4[10] = uVar7;
      }
      else {
        if (uVar14 == 3) {
          uVar12 = translate_parameter(0xb,3);
          if (uVar11 < 200) {
            uVar7 = puVar4[7];
            iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7])) >> 0x20);
            iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
            uVar7 = puVar4[8] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
          }
          else {
            lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7]);
            iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)puVar4[7] * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
            uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[8];
          }
          puVar4[0xb] = uVar7;
        }
        else {
          if (uVar14 == 4) {
            uVar12 = translate_parameter(0xb,4);
            if (uVar11 < 200) {
              uVar7 = puVar4[7];
              iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7])) >> 0x20);
              iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
              uVar7 = puVar4[8] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
            }
            else {
              lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7]);
              iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)puVar4[7] * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
              uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[8];
            }
            puVar4[0xc] = uVar7;
          }
          else {
            if (uVar14 == 5) {
              uVar12 = translate_parameter(0xb,5);
              if (uVar11 < 200) {
                uVar7 = puVar4[7];
                iVar10 = (int)((ulonglong)((longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7])) >> 0x20);
                iVar10 = divide_2(uVar13 * ((iVar10 >> 5) - (iVar10 >> 0x1f)),uVar12 & 0xffff);
                uVar7 = puVar4[8] - ((short)(uint)((ulonglong)((uint)uVar7 * 200) * (ulonglong)uVar9 >> 0x25) - (short)iVar10);
              }
              else {
                lVar1 = (longlong)(int)uVar9 * (longlong)(int)(uVar11 * puVar4[7]);
                iVar10 = divide_2((uVar12 & 0xffff) * (uint)((ulonglong)((uint)puVar4[7] * 200) * (ulonglong)uVar9 >> 0x25),uVar13);
                uVar7 = (((short)(int)(lVar1 >> 0x25) - (short)(lVar1 >> 0x3f)) - (short)iVar10) + puVar4[8];
              }
              puVar4[0xd] = uVar7;
            }
          }
        }
      }
    }

    uVar14 = uVar14 + 1 & 0xfffeffff;
  } while (uVar14 < 6);



  //A test loop to verify the settings are correct
  //On several sensitivity settings the average readings need to be below some value

  uVar9 = 0;
  uVar13 = 0;
  fpga_setup_for_calib();
  iVar8 = DAT_80003db4;
  bVar6 = 0;
  do
  {
    *(undefined *)(iVar8 + 3) = 0;         //5V/div setting
    *(undefined *)(iVar8 + 0xf) = 0;

    while( true )
    {
      *(undefined2 *)(iVar8 + 6) = 200;    //Trace offsets 200
      *(undefined2 *)(iVar8 + 0x12) = 200;

      fpga_write_cmd('3');                 //Channel 1 volt per div select in fpga
      if (*(char *)(iVar8 + 3) == '\x06')
      {
        uVar5 = '\x05';
      }
      else
      {
        uVar5 = *(uchar *)(iVar8 + 3);
      }

      fpga_write_data(uVar5);

      fpga_write_cmd('6');                   //Channel 2 volt per div select in fpga
      if (*(char *)(iVar8 + 0xf) == '\x06')
      {
        uVar5 = '\x05';
      }
      else
      {
        uVar5 = *(uchar *)(iVar8 + 0xf);
      }

      fpga_write_data(uVar5);

      set_fpga_channel1_offset();
      set_fpga_channel2_offset();

      delay_2(100);

      fpga_start_calib_conversion();
      do
      {
        iVar10 = fpga_check_conversion_ready();
      } while (iVar10 == 0);

      //Channel 1
      write_fpga_cmd_0x1F(100);
      fpga_read_channel1_adc1_samples();
      calib_adjust_channel_1_samples();
      calib_copy_ch1_buf3_to_buf4();
      calib_ch1_limit_samples_on_401();
      iVar10 = calib_average_samples(DAT_80003db8);

      if (iVar10 - 0xc1U < 0xf)
      {
        if (bVar6 == 0)
        {
          uVar9 = uVar9 | 1;
        }
        else
        {
          if (bVar6 == 1)
          {
            uVar9 = uVar9 | 2;
          }
          else
          {
            if (bVar6 == 2)
            {
              uVar9 = uVar9 | 4;
            }
          }
        }
      }

      //Channel 2
      write_fpga_cmd_0x1F(100);
      fpga_read_channel2_adc1_samples();
      calib_adjust_channel_2_samples();
      calib_copy_ch2_buf3_to_buf4();
      calib_ch2_limit_samples_on_401();
      iVar10 = calib_average_samples(DAT_80003dbc);

      if (iVar10 - 0xc1U < 0xf)
      {
        if (bVar6 == 0)
        {
          uVar13 = uVar13 | 1;
        }
        else
        {
          if (bVar6 == 1)
          {
            uVar13 = uVar13 | 2;
          }
          else
          {
            if (bVar6 == 2)
            {
              uVar13 = uVar13 | 4;
            }
          }
        }
      }

      bVar6 = bVar6 + 1;  //First run = 0, so becomes 1, run after that it becomes 2

      if (2 < bVar6) //2 is not less then 1 so no bail, 2 is not less then 2 so again no bail
      {
        return uVar9 == 7 && uVar13 == 7;   //Channel 1 flags need to equal 7 and Channel 2 flags need to equal 7 for vaild result??
      }

      if (bVar6 == 0)   //Never gone happen here
        break;

      if (bVar6 == 1)   //True after first loop so switch to more sensitive setting 0.5V/div
      {
        *(undefined *)(iVar8 + 3) = 3;
        *(undefined *)(iVar8 + 0xf) = 3;
      }
      else
      {
        if (bVar6 == 2)  //True after second loop so again more sensitive. 0.2V/div
        {
          *(undefined *)(iVar8 + 3) = 4;
          *(undefined *)(iVar8 + 0xf) = 4;
        }
      }
    }
  } while( true );
}

//--------------------------------------------------------------------------------

bool do_adc1_adc2_diff_calibration(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  short sVar7;
  bool bVar8;
  bool bVar9;
  bool bVar10;
  bool bVar11;
  
  fpga_setup_for_calib();

  *(undefined *)(DAT_80003164 + 10) = 0x1d;  //Set the time base to 29 ==> 10ns/div

  set_fpga_trigger_timebase();

  fpga_start_calib_conversion();

  do
  {
    iVar1 = fpga_check_conversion_ready();
  } while (iVar1 == 0);

  write_fpga_cmd_0x1F(100);
  fpga_read_channel1_adc1_samples();

  write_fpga_cmd_0x1F(100);
  fpga_read_channel1_adc2_samples();

  write_fpga_cmd_0x1F(100);
  fpga_read_channel2_adc1_samples();

  write_fpga_cmd_0x1F(100);
  fpga_read_channel2_adc2_samples();

  uVar2 = calib_average_samples(DAT_80003168);    //0x8019D5EA  1st buffer
  uVar3 = calib_average_samples(DAT_8000316c);    //0x8019ED5A  2nd buffer

  uVar4 = calib_average_samples(DAT_80003170);    //0x801A04CA  1st buffer
  uVar5 = calib_average_samples(DAT_80003174);    //0x801A1C3A  2nd buffer

  iVar1 = DAT_80003178;                           //0x802F18B0  Calibration data base

  if (uVar2 < uVar3)
  {
    sVar7 = (short)uVar3 - (short)uVar2;
    *(undefined2 *)(DAT_80003178 + 0x1c) = 0;     //channel1adc2calibration.flag in my code
  }
  else
  {
    sVar7 = (short)uVar2 - (short)uVar3;
    *(undefined2 *)(DAT_80003178 + 0x1c) = 1;
  }
  *(short *)(iVar1 + 0x1e) = sVar7;               //channel1adc2calibration.compensation in my code

  if (uVar4 < uVar5)
  {
    *(undefined2 *)(iVar1 + 0x20) = 0;
    *(short *)(iVar1 + 0x22) = (short)uVar5 - (short)uVar4;
  }
  else
  {
    *(undefined2 *)(iVar1 + 0x20) = 1;
    *(short *)(iVar1 + 0x22) = (short)uVar4 - (short)uVar5;
  }

  //Some limiting check on the diff to decide if system is ok or not
  uVar6 = uVar3 + 0x19;
  bVar10 = uVar6 <= uVar2;
  bVar8 = uVar2 == uVar6;

  if (!bVar10 || bVar8)
  {
    uVar6 = uVar2 + 0x19;
  }

  if (!bVar10 || bVar8)
  {
    bVar10 = uVar6 <= uVar3;
    bVar8 = uVar3 == uVar6;
  }

  uVar2 = uVar5 + 0x19;
  bVar11 = uVar2 <= uVar4;
  bVar9 = uVar4 == uVar2;

  if (!bVar11 || bVar9)
  {
    uVar2 = uVar4 + 0x19;
  }

  if (!bVar11 || bVar9)
  {
    bVar11 = uVar2 <= uVar5;
    bVar9 = uVar5 == uVar2;
  }

  if ((!bVar11 || bVar9) && (!bVar10 || bVar8))
  {
    return 1;
  }

  return 0;
}

//--------------------------------------------------------------------------------

