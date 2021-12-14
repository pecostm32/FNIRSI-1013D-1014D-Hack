//--------------------------------------------------------------------------------

void perform_auto_set(void)

{
  char *pcVar1;
  char cVar2;
  bool bVar3;
  int iVar4;
  uint uVar5;
  uchar uVar6;
  char cVar7;
  undefined2 uVar8;
  short sVar9;
  ushort uVar10;
  int iVar11;
  int iVar12;
  uint uVar13;
  char *pcVar14;
  uint uVar15;
  char *pcVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  ushort *puVar20;
  bool bVar21;
  bool bVar22;
  bool bVar23;
  bool bVar24;
  uint local_50;
  uint local_4c;
  uint local_48;
  uint local_40;
  uint local_34;
  uint local_30;
  
  pcVar16 = DAT_80002758;                     //0x8019D5A0
  DAT_80002758[0x3a] = '\0';                  //run mode running
  *(undefined2 *)(pcVar16 + 6) = 200;         //channel 1 trace offset
  *(undefined2 *)(pcVar16 + 0x12) = 200;      //channel 2 trace offset
  *(undefined2 *)(pcVar16 + 0x24) = 0x16a;    //trigger position on screen


  *(undefined2 *)PTR_DAT_8000275c = 0;
  *(undefined2 *)PTR_DAT_80002760 = 400;
  *(undefined2 *)PTR_DAT_80002764 = 0;
  *(undefined2 *)PTR_DAT_80002768 = 400;

  pcVar16[0x21] = '\0';                        //trigger mode auto

  bVar23 = false;
  bVar3 = false;
  local_30 = 6;
  local_34 = 6;

  set_fpga_channel1_offset();
  set_fpga_channel2_offset();

  set_fpga_trigger_mode();

  display_trigger_settings(0);

  set_fpga_channel_trigger_channel();    //Stays on current set channel??

  display_run_stop_text(0);              //show running

  pcVar16[10] = '\x10';                  //Time base on 200us/div

  set_fpga_trigger_timebase();

  write_fpga_cmd_0x28();                //Write a 1 to the FPGA command 0x28. Select long time base system??


  iVar4 = DAT_8000276c;                //0x801A04CA  Channel 2 sample buffer
  uVar19 = 0;


  //Think this bit is for determining the signal strength
  do
  {
    cVar7 = (char)uVar19;
    pcVar16[3] = cVar7;              //First try on lowest sensitivity (5V/div)
    pcVar16[0xf] = cVar7;            //Both channel 1 and 2

    fpga_write_cmd('3');             //Channel 1 volts/div select

    if (pcVar16[3] == '\x06')
    {
      uVar6 = '\x05';
    }
    else
    {
      uVar6 = pcVar16[3];
    }

    fpga_write_data(uVar6);

    fpga_write_cmd('6');             //Channel 2 volts/div select

    if (pcVar16[0xf] == '\x06')
    {
      uVar6 = '\x05';
    }
    else 
    {
      uVar6 = pcVar16[0xf];
    }

    fpga_write_data(uVar6);

    set_fpga_channel1_offset();
    set_fpga_channel2_offset();

    delay_2(0x3c);                  //60ms delay

    iVar12 = DAT_80002770;          //0x8019D5EA  Channel 1 sample buffer
    uVar18 = 0;

    //get 1000 samples for both channels enabled or not, with some special timing
    do
    {
      iVar11 = (uVar18 * 0x14 & 0xffe0ffff) - 1;

      //Some timing loop. Absolute inacurate since it can be interrupted by the timer
      //but it seems to depend on the sample index.
      do
      {
        bVar24 = SCARRY4(iVar11,1);
        bVar21 = iVar11 + 1 < 0;
        bVar22 = iVar11 != -1;

        if (bVar22 && bVar21 == bVar24)
        {
          iVar11 = iVar11 + -1;
        }
      } while (bVar22 && bVar21 == bVar24);

      uVar8 = get_channel_1_avg_sample(1);          //Read a sample with command 0x24

      *(undefined2 *)(iVar12 + uVar18 * 2) = uVar8;  //Store in channel 1 sample buffer

      uVar8 = get_channel_2_avg_sample(1);          //Read a sample with command 0x26

      iVar11 = uVar18 * 2;
      uVar18 = uVar18 + 1 & 0xfffeffff;

      *(undefined2 *)(iVar4 + iVar11) = uVar8;      //Store in channel 2 sample buffer

      uVar5 = DAT_80002774;                         //0x0000FFFF
    } while (uVar18 < 1000);                        //Get 1000 samples with no proper sample relation

    uVar18 = 0;


    //Check if channel 1 is enabled
    if ((*pcVar16 != '\0') && (!bVar23))            //bVar23 starts with FALSE
    {
      calib_adjust_channel_1_samples();             //Multiply the samples with the scaling factor. Data from buffer 1 to buffer 3
      calib_copy_ch1_buf3_to_buf4();                //Samples into buffer 4

      double_channel1_samples();

      calib_ch1_limit_samples_on_401();             //Keep the samples in check

      iVar12 = 0x3d4;                               //980
      puVar20 = DAT_80002778;                       //0x801AC05E  Some samples into the 4th buffer
      uVar13 = uVar5;

      do
      {
        uVar17 = (uint)*puVar20;
        puVar20 = puVar20 + 1;

        if (uVar18 < uVar17)
        {
          uVar18 = uVar17;
        }

        if (uVar17 < uVar13)
        {
          uVar13 = uVar17;
        }

        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);

      local_4c = uVar18 - uVar13 & 0xffff;
      local_48 = uVar18 + uVar13 >> 1;

      if (pcVar16[0xc] == '\0')       //Channel 2 enable
      {
        uVar17 = 0x6e;
      }
      else
      {
        uVar17 = 0x46;
      }

      if (uVar18 < 0x12d)
      {
        if (uVar13 < 100)
        {
          cVar2 = pcVar16[0xc];     //Channel 2 enable
        }
        else
        {
          if (local_4c <= uVar17)
            goto LAB_80002288;       //Go and do channel 2

          cVar2 = pcVar16[0xc];      //Channel 2 enable
        }
      }
      else
      {
        cVar2 = pcVar16[0xc];        //Channel 2 enable
      }

      bVar23 = true;
      local_30 = uVar19 & 0xff;
      local_30._0_1_ = cVar7;

      if (cVar2 == '\0')             //Bail out if channel 2 is not enabled
        break;
    }

LAB_80002288:
    uVar18 = 0;

    //Check if channel 2 is enabled
    if ((pcVar16[0xc] != '\0') && (!bVar3))            //bVar3 starts with FALSE
    {
      calib_adjust_channel_2_samples();
      calib_copy_ch2_buf3_to_buf4();

      FUN_80006be0();

      calib_ch2_limit_samples_on_401();

      iVar12 = 0x3d4;
      puVar20 = DAT_8000277c;
      uVar13 = uVar5;

      do
      {
        uVar17 = (uint)*puVar20;
        puVar20 = puVar20 + 1;

        if (uVar18 < uVar17)
        {
          uVar18 = uVar17;
        }

        if (uVar17 < uVar13)
        {
          uVar13 = uVar17;
        }

        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);

      local_40 = uVar18 - uVar13 & 0xffff;
      local_50 = uVar18 + uVar13 >> 1;

      if (*pcVar16 == '\0')       //Channel 1 enable
      {
        uVar17 = 0x6e;
      }
      else
      {
        uVar17 = 0x46;
      }

      if (uVar18 < 0x12d)
      {
        if (uVar13 < 100)
        {
          cVar2 = *pcVar16;            //Channel 1 enable
        }
        else
        {
          if (local_40 <= uVar17)
            goto LAB_80002374;

          cVar2 = *pcVar16;       //Channel 1 enable
        }
      }
      else
      {
        cVar2 = *pcVar16;       //Channel 1 enable
      }

      bVar3 = true;
      local_34 = uVar19 & 0xff;
      local_34._0_1_ = cVar7;

      if (cVar2 == '\0')       //Channel 1 enable
        break;
    }

LAB_80002374:
    if ((bVar23 && bVar3) || (uVar19 = uVar19 + 1 & 0xfffeffff, 6 < uVar19))
      break;
  } while( true );


  uVar19 = DAT_80002780;
  cVar7 = *pcVar16;
  bVar21 = cVar7 != '\0';

  if (bVar21)
  {
    cVar7 = pcVar16[0xc];
  }

  if (bVar21 && cVar7 != '\0')
  {
    uVar13 = 100;
    uVar18 = 300;
  }
  else
  {
    uVar13 = 200;
    uVar18 = uVar13;
  }

  if (*pcVar16 == '\0')           //Channel 1 enable
  {
    uVar18 = 0;
    local_4c = 0;
  }

  uVar8 = (undefined2)DAT_80002780;

  if (*pcVar16 != '\0')           //Channel 1 enable
  {
    if (local_48 < uVar18)
    {
      *(short *)(pcVar16 + 6) = ((short)uVar18 - (short)local_48) + *(short *)(pcVar16 + 6);

      if (uVar19 < *(ushort *)(pcVar16 + 6))
      {
        *(undefined2 *)(pcVar16 + 6) = uVar8;
      }
    }
    else
    {
      pcVar1 = (char *)(local_48 - uVar18 & 0xffff);
      pcVar14 = pcVar1;

      if ((char *)(uint)*(ushort *)(pcVar16 + 6) < pcVar1)
      {
        pcVar14 = pcVar16;
      }

      sVar9 = (short)pcVar14;

      if ((char *)(uint)*(ushort *)(pcVar16 + 6) < pcVar1)
      {
        sVar9 = *(short *)(pcVar16 + 6);
      }

      *(short *)(pcVar16 + 6) = *(short *)(pcVar16 + 6) - sVar9;
    }
  }


  uVar18 = (uint)(byte)pcVar16[0xc];       //Channel 2 enable

  if ((byte)pcVar16[0xc] != 0)             //Channel 2 enable
  {
    uVar18 = local_40;

    if (local_50 < uVar13)
    {
      *(short *)(pcVar16 + 0x12) = ((short)uVar13 - (short)local_50) + *(short *)(pcVar16 + 0x12);

      if (uVar19 < *(ushort *)(pcVar16 + 0x12))
      {
        *(undefined2 *)(pcVar16 + 0x12) = uVar8;
      }
    }
    else
    {
      pcVar1 = (char *)(local_50 - uVar13 & 0xffff);
      pcVar14 = pcVar1;

      if ((char *)(uint)*(ushort *)(pcVar16 + 0x12) < pcVar1)
      {
        pcVar14 = pcVar16;
      }

      sVar9 = (short)pcVar14;

      if ((char *)(uint)*(ushort *)(pcVar16 + 0x12) < pcVar1)
      {
        sVar9 = *(short *)(pcVar16 + 0x12);
      }

      *(short *)(pcVar16 + 0x12) = *(short *)(pcVar16 + 0x12) - sVar9;
    }
  }

  local_40 = uVar18;

  if (*pcVar16 == '\0')       //Channel 1 enable
  {
    pcVar16[3] = '\0';
    fpga_write_cmd('3');
    cVar7 = pcVar16[3];
  }
  else
  {
    pcVar16[3] = (char)local_30;
    fpga_write_cmd('3');
    cVar7 = pcVar16[3];
  }

  if (cVar7 == '\x06')
  {
    uVar6 = '\x05';
  }
  else
  {
    uVar6 = pcVar16[3];
  }

  fpga_write_data(uVar6);


  set_fpga_channel1_offset();



  if (pcVar16[0xc] == '\0')       //Channel 2 enable
  {
    pcVar16[0xf] = '\0';
    fpga_write_cmd('6');
    cVar7 = pcVar16[0xf];
  }
  else
  {
    pcVar16[0xf] = (char)local_34;
    fpga_write_cmd('6');
    cVar7 = pcVar16[0xf];
  }

  if (cVar7 == '\x06')
  {
    uVar6 = '\x05';
  }
  else
  {
    uVar6 = pcVar16[0xf];
  }

  fpga_write_data(uVar6);


  set_fpga_channel2_offset();

  delay_2(0x32);


  //Think this bit is for determining the frequency of the signal

  if (pcVar16[0x23] == '\0')   //trigger channel??
  {
    uVar8 = 300;
  }
  else
  {
    uVar8 = 100;
  }

  *(undefined2 *)(pcVar16 + 0x26) = uVar8;

  if (*pcVar16 != pcVar16[0xc])  //Channel enables
  {
    *(undefined2 *)(pcVar16 + 0x26) = 200;
  }

  set_fpga_trigger_level();

  bVar21 = 0x18 < local_4c;

  if (!bVar21)
  {
    local_4c = local_40;
  }

  if (bVar21 || 0x18 < local_4c)
  {
    display_ch1_settings(0);
    display_ch2_settings(0);
    uVar10 = 0x1d;
    pcVar16[0x48] = '\x01';
    iVar4 = DAT_80002784;

    do
    {
      pcVar16[10] = (char)uVar10;
      set_fpga_trigger_timebase();
      get_short_timebase_data();    //Uses the normal capture system to get the samples

      if (pcVar16[0x23] == '\0')    //Trigger channel
      {
        calculate_ch1_min_max_avg();
        iVar12 = DAT_8000278c;
      }
      else
      {
        calculate_ch2_min_max_avg();
        iVar12 = DAT_80002788;
      }

      uVar13 = 0;
      puVar20 = (ushort *)(iVar12 + 0x14);
      uVar18 = 0;
      uVar19 = uVar5;
      iVar11 = iVar4;

      do
      {
        uVar17 = (uint)*puVar20;
        puVar20 = puVar20 + 1;

        if (uVar18 < uVar17)
        {
          uVar18 = uVar17;
        }

        if (uVar17 < uVar19)
        {
          uVar19 = uVar17;
        }

        iVar11 = iVar11 + -1;
      } while (iVar11 != 0);

      uVar15 = 10;
      uVar17 = uVar18 - uVar19 & 0xffff;
      *(short *)(pcVar16 + 0x26) = (short)(uVar18 + uVar19 >> 1);

      do
      {
        iVar11 = iVar12 + uVar15 * 2;

        if (((*(ushort *)(iVar11 + -2) < *(ushort *)(pcVar16 + 0x26)) && (*(ushort *)(pcVar16 + 0x26) < *(ushort *)(iVar11 + 2))) || ((*(ushort *)(pcVar16 + 0x26) < *(ushort *)(iVar11 + -2) && (*(ushort *)(iVar11 + 2) < *(ushort *)(pcVar16 + 0x26)))))
        {
          uVar13 = uVar13 + 1 & 0xfffeffff;
          uVar15 = uVar15 + 10 & 0xfffeffff;
        }

        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x2e4);

      bVar23 = uVar13 == 7;

      if (6 < uVar13)
      {
        bVar23 = uVar17 == 0x28;
      }
    } while (((6 >= uVar13 || uVar17 < 0x28) || bVar23) && (uVar10 = uVar10 - 1, 8 < uVar10));

    pcVar16[0x48] = '\0';       //Clear battery charge level????
    set_fpga_trigger_level();
    set_fpga_trigger_timebase();
  }
  else 
  {
    pcVar16[0x48] = '\0';
    pcVar16[10] = '\x13';                   //Time base on 19 ==> 20us/div

    if (!bVar23)    //Channel 1 flag for no successful sensitivity determined
    {
      pcVar16[3] = '\0';
      fpga_write_cmd('3');

      if (pcVar16[3] == '\x06')
      {
        uVar6 = '\x05';
      }
      else
      {
        uVar6 = pcVar16[3];
      }

      fpga_write_data(uVar6);
    }

    if (!bVar3)    //Channel 2 flag for no successful sensitivity determined
    {
      pcVar16[0xf] = '\0';

      fpga_write_cmd('6');

      if (pcVar16[0xf] == '\x06')
      {
        uVar6 = '\x05';
      }
      else
      {
        uVar6 = pcVar16[0xf];
      }

      fpga_write_data(uVar6);
    }

    set_fpga_channel1_offset();
    set_fpga_channel2_offset();

    set_fpga_trigger_level();
    set_fpga_trigger_timebase();
  }

  display_time_div_setting();
}


//-----------------------------------------------------------------------
//This bit is display_time_div_setting()

  set_frame_to_global_pointer();
  set_display_fg_color(0);
  display_fill_rect(0x18b,5,0x1e8,0x2c);
  set_display_fg_color(0xffffff);
  select_font(PTR_FONT_0_800124d0);

  switch(*(undefined *)(DAT_800124d4 + 10))
  {
  case 0:
    pcVar16 = s_50S/div_800124dc;
    break;
  case 1:
    pcVar16 = s_20S/div_800124e4;
    break;
  case 2:
    pcVar16 = s_10S/div_800124ec;
    break;
  case 3:
    pcVar16 = s_5S/div_800124f4;
    break;
  case 4:
    pcVar16 = s_2S/div_800124fc;
    break;
  case 5:
    pcVar16 = s_1S/div_80012504;
    break;
  case 6:
    pcVar16 = s_500mS/div_8001250c;
    break;
  case 7:
    pcVar16 = s_200mS/div_80012518;
    break;
  case 8:
    pcVar16 = s_100mS/div_80012524;
    break;
  case 9:
    pcVar16 = s_50mS/div_80012530;
    break;
  case 10:
    pcVar16 = s_20mS/div_8001253c;
    break;
  case 0xb:
    pcVar16 = s_10mS/div_80012548;
    break;
  case 0xc:
    pcVar16 = s_5mS/div_80012554;
    break;
  case 0xd:
    pcVar16 = s_2mS/div_8001255c;
    break;
  case 0xe:
    pcVar16 = s_1mS/div_80012564;
    break;
  case 0xf:
    pcVar16 = s_500uS/div_8001256c;
    break;
  case 0x10:
    pcVar16 = s_200uS/div_80012578;
    break;
  case 0x11:
    pcVar16 = s_100uS/div_80012584;
    break;
  case 0x12:
    pcVar16 = s_50uS/div_80012590;
    break;
  case 0x13:
    pcVar16 = s_20uS/div_8001259c;
    break;
  case 0x14:
    pcVar16 = s_10uS/div_800125a8;
    break;
  case 0x15:
    pcVar16 = s_5uS/div_800125b4;
    break;
  case 0x16:
    pcVar16 = s_2uS/div_800125bc;
    break;
  case 0x17:
    pcVar16 = s_1uS/div_800125c4;
    break;
  case 0x18:
    pcVar16 = s_500nS/div_800125cc;
    break;
  case 0x19:
    pcVar16 = s_250nS/div_80012640;
    break;
  case 0x1a:
    pcVar16 = s_100nS/div_8001264c;
    break;
  case 0x1b:
    pcVar16 = s_50nS/div_80012658;
    break;
  case 0x1c:
    pcVar16 = s_25nS/div_80012664;
    break;
  case 0x1d:
    pcVar16 = s_10nS/div_80012670;
    break;
  default:
    goto switchD_800122c0_caseD_1e;
  }
  display_text(pcVar16,(ushort)DAT_800124d8,0x10);
switchD_800122c0_caseD_1e:
  iVar12 = Start_Of_Screen_Mem;
  iVar4 = Screen_Frame_Buffer;
  uVar19 = 5;
  do {
    iVar11 = uVar19 * 800 + 0x17c;
    copy_short((void *)(iVar12 + iVar11 * 2),(void *)(iVar4 + iVar11 * 2),0x5f);
    uVar19 = uVar19 + 1;
  } while (uVar19 < 0x2a);
  return;
}

//--------------------------------------------------------------------------------

