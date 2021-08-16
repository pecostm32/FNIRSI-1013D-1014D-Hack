//------------------------------------------------------------------------------------------------------------------------------------------------
//scope_get_short_timebase_data in my code

void FUN_80025468(void)
{
  ushort uVar1;
  char *pcVar2;
  char *pcVar3;
  ushort *puVar4;
  ushort *puVar5;
  uint *puVar6;
  undefined *puVar7;
  undefined *puVar8;
  uchar data;
  byte bVar9;
  short sVar10;
  ushort uVar11;
  uint *puVar12;
  uint uVar13;
  uint uVar14;
  uint *puVar15;
  ushort *puVar16;
  ushort *puVar17;
  uint *puVar18;
  int iVar19;
  uint uVar20;
  uint *puVar21;
  uint *puVar22;
  uint *unaff_r4;
  undefined4 uVar23;
  uint *puVar24;
  uint uVar25;
  bool bVar26;
  bool bVar27;
  int local_30;
  uchar data_00;
  
  iVar19 = DAT_80025710;  //0x8019D5A0 settings base
  bVar26 = false;
  uVar23 = DAT_80025714;  //0x000645DC

  //Switch on timebase setting. Handle (9 - 23) 50mS/div - 1uS/div
  switch(*(undefined *)(DAT_80025710 + 10))
  {
  case 9:
  case 10:
    uVar23 = 800;             //0x00000320
    break;
  case 0xb:
    uVar23 = DAT_80025734;    //0x00000708
    break;
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
    uVar23 = DAT_80025730;    //0x000009C4
    break;
  case 0x11:
    uVar23 = DAT_8002572c;    //0x00000BB8
    break;
  case 0x12:
    uVar23 = DAT_80025728;    //0x000015DC
    break;
  case 0x13:
    uVar23 = DAT_80025724;    //0x000025DC
    break;
  case 0x14:
  case 0x15:
    uVar23 = DAT_80025720;    //0x000055DC
    break;
  case 0x16:
    uVar23 = DAT_8002571c;    //0x000145DC
    break;
  case 0x17:
    uVar23 = DAT_80025718;    //0x000325DC
  }

  //For timebase 50mS/div - 50nS/div or trigger modes single and normal
  if ((*(byte *)(DAT_80025710 + 10) < 0x1c) || (*(char *)(DAT_80025710 + 0x21) != '\0'))
  {
    //Set the trigger level
    set_fpga_trigger_level();
  }

  //Write command 0x0E with the setting from the switch above
  fpga_write_cmd('\x0e');
  fpga_write_data((uchar)((uint)uVar23 >> 0x18));
  fpga_write_data((uchar)((uint)uVar23 >> 0x10));
  fpga_write_data((uchar)((uint)uVar23 >> 8));
  fpga_write_data((uchar)uVar23);

  //Write command 0x0F,0x00
  fpga_write_cmd('\x0f');
  fpga_write_data('\0');

  //Write command 0x28,0x00
  fpga_write_cmd('(');
  fpga_write_data('\0');

  //Write command 0x01,0x01
  fpga_write_cmd('\x01');
  fpga_write_data('\x01');

  //Write command 0x05
  fpga_write_cmd('\x05');

  //Wait for the FPGA to return 1 in the LSB
  do
  {
    bVar9 = fpga_read_data();
  } while ((bVar9 & 1) == 0);

  //And just to make sure?? Wait for the FPGA to return again 1 in the LSB
  do
  {
    bVar9 = fpga_read_data();
  } while ((bVar9 & 1) == 0);

  //Write command 0x01,0x00
  fpga_write_cmd('\x01');
  fpga_write_data('\0');


  puVar8 = PTR_DAT_8002573c;    //0x80192ec8
  puVar7 = PTR_DAT_80025738;    //0x80192ec6

  *(undefined *)(iVar19 + 0xb) = *(undefined *)(iVar19 + 10);  //Copy the timebase setting for what???    (0x8019d5ab)

  *(ushort *)puVar7 = (ushort)*(byte *)(iVar19 + 3);           //Copy the volts/div setting for channel 1 (0x80192ec6) Seen these addresses in the fpga handling
  *(ushort *)puVar8 = (ushort)*(byte *)(iVar19 + 0xf);         //Copy the volts/div setting for channel 2 (0x80192ec8) voltperdivbackup


  //Check some variable to see if an update on screen is needed
  if (*(char *)(iVar19 + 0x37) != '\0')
  {
    *(undefined *)(iVar19 + 0x37) = 0;  //Clear the flag
    set_frame_to_global_pointer();      //Write directly to the display
    set_display_fg_color(0);            //Black

    //xstart 2, ystart 47, xend 730, yend 479
    //Clear the trace area on the display
    display_fill_rect(2,0x2f,(ushort)DAT_80025740 + 0xfb,(ushort)DAT_80025740);  //0x000001DF

    display_draw_grid();
    display_draw_trace_pointers();

    //Copy the traces to the screen
    //xstart 2, ystart 46, xend 728, yend 478
    copy_rect_to_screen(2,0x2e,0x2d8,(ushort)DAT_80025744);
  }

  pcVar2 = PTR_DAT_8002574c;    //0x80192f08  Touch state
  pcVar3 = PTR_DAT_80025748;    //0x80192f02  Touch panel data

  //Wait loop for data to become ready or touch on panel
  do
  {
    fpga_write_cmd('\n');       //Write fpga command 0x0A
    bVar9 = fpga_read_data();

    if ((bVar9 & 1) != 0)
      break;

    tp_i2c_read_status();

    if (*pcVar3 != '\0')
    {
      bVar26 = true;            //Signal there is touch
      break;
    }
  } while (*pcVar2 != '\x02');  //As long as touch is not in state 2. (moving traces???)


  //Write command 0x0F,0x01
  fpga_write_cmd('\x0f');
  fpga_write_data('\x01');

  //Trigger mode single and normal
  if (*(char *)(iVar19 + 0x21) != '\0')
  {
    if (bVar26)  //Only if there was touch
    {
      *(undefined *)(iVar19 + 0x18) = 1;            //0x8019d5b8  some flag

      bVar26 = *(char *)(iVar19 + 0x21) != '\x01';  //Not in single mode  True for normal mode

      if (bVar26)
      {
        //Normal mode
        if (*(char *)(iVar19 + 0x36) == '\0')       //0x8019d5d6  Some state variable????
        {
          bVar26 = false;
        }
      }
      else
      {
        *(bool *)(iVar19 + 0x36) = bVar26;          //0x8019d5d6   Set for single mode???
      }

      *(bool *)(iVar19 + 0x17) = bVar26;            //0x8019d5b7   signal it in this variable

      return;
    }

    //Single trigger mode
    if (*(char *)(iVar19 + 0x21) == '\x01')         //This means a trigger was detected in the fpga sequence at the start of this function
    {
      //Switch to stop
      *(undefined *)(iVar19 + 0x3a) = 1;            //0x8019d5da   scope run mode state
      display_run_stop_text(1);                     //Stopped

      //Copy the volt/div settings
      *(ushort *)puVar7 = (ushort)*(byte *)(iVar19 + 3);
      *(ushort *)puVar8 = (ushort)*(byte *)(iVar19 + 0xf);
    }

    *(undefined *)(iVar19 + 0x36) = 1;              //Signal in some state variable single or normal
  }




  local_30 = 0;

  puVar12 = (uint *)fpga_prepare_for_transfer();   //Send command 0x14 and translate the received data



  puVar6 = DAT_8000b270;                           //0x000005DC   (1500)
  puVar15 = DAT_8000b268;                          //0x000002EE    (750)
  sVar10 = (short)puVar12;

  if ((byte)DAT_8000b264[10] < 0x19)               //0x8019D5AA so timebase settings (less then 25) (50S/div - 500nS/div)
  {
    if ((byte)DAT_8000b264[10] < 0xb)              //0x8019D5AA so timebase settings (50S/div - 20mS/div)
    {
      sVar10 = 10;                                 //parameter is 10??? for timebase 50S/div - 100mS/div handled in other code
    }
    else
    {
      if (puVar12 < DAT_8000b268)                  //0x000002EE (750)
      {
        sVar10 = sVar10 + 0xd11;                   //3345???   Less then 750 add big value
      }
      else
      {
        sVar10 = sVar10 + -0x2ee;                  //Else subtract 750
      }
    }
  }
  else 
  {
    switch(DAT_8000b264[10])                       //0x8019D5AA so timebase settings.  Use timebase_adjusters
    {
    case '\x19':                                   //200nS/div
      unaff_r4 = DAT_8000b26c;                     //0x01A9
      break;
    case '\x1a':                                   //100nS/div
      unaff_r4 = (uint *)0xaa;
      break;
    case '\x1b':                                   //50nS/div
      unaff_r4 = (uint *)0x55;
      break;
    case '\x1c':                                   //20nS/div
      unaff_r4 = (uint *)0x2f;
      break;
    case '\x1d':                                   //10nS/div
      unaff_r4 = (uint *)0x14;
    }

    if (puVar12 < unaff_r4)
    {
      sVar10 = 0xfff - ((short)unaff_r4 - sVar10);  //otherwise some other calc
    }
    else
    {                                              //Result > setting
      sVar10 = sVar10 - (short)unaff_r4;           //take setting off
    }
  }

  puVar12 = DAT_8000b270 + 0xfa;                    //0x000005DC + FA = 6D6 = 1750 Some offset in some data??? In asm code this is 2500
  data = (uchar)((ushort)sVar10 >> 8);
  data_00 = (uchar)sVar10;








  //Channel 1 handling (Channel 2 handling is similair but uses different functions at some points)
  if (*DAT_8000b264 != '\0')                       //Channel 1 enabled
  {
    fpga_write_cmd('\x1f');
    fpga_write_data(data);
    fpga_write_data(data_00);

    puVar22 = puVar6;                              //1500

    if ((byte)DAT_8000b264[10] < 0xb)              //Timebase setting
    {
      puVar22 = puVar15;                           //750
    }

    //Get the command to use based on the trigger channel
    uVar13 = translate_parameter(0xc,(uint)(byte)DAT_8000b264[0x23]);

    //Write it to the fpga           Use fpga_read_trace_data !!!!!
    fpga_write_cmd((uchar)uVar13);

    //Start reading the data
    fpga_bus_dir_in();
    puVar18 = DAT_8000b274;
    set_gpio_pin_low(DAT_8000b274,9);
    set_gpio_pin_low(puVar18,10);
    puVar24 = (uint *)0x0;

    if (puVar22 != (uint *)0x0)
    {
      do
      {
        set_gpio_pin_low(puVar18,8);
        set_gpio_pin_high(puVar18,8);
        puVar16 = DAT_8000b278 + (int)puVar24;                             //0x8019D5EA
        puVar24 = (uint *)((uint)((int)puVar24 + 1) & 0xfffeffff);
        *puVar16 = (ushort)puVar18[4] & 0xff;
      } while (puVar24 < puVar22);
    }


    pcVar2 = DAT_8000b264;
    *DAT_8000b278 = DAT_8000b278[1];


    if (pcVar2[0x23] == '\0')    //Trigger on channel 1 ?
    {
      local_30 = FUN_800291e0();  //scope_process_trigger
    }

    if (pcVar2[10] == '\x19')    //Timebase 250nS/div ?
    {
      FUN_8001363c(DAT_8000b278,0);  //0x8019D5EA   //scope_pre_process_250ns_data
    }

    if (pcVar2[10] == '\x1a')    //Timebase 100nS/div ?
    {
      FUN_800141c8(DAT_8000b278,0);  //scope_pre_process_100ns_data
    }

    if (pcVar2[10] == '\x1b')    //Timebase 50nS/div ?
    {
      FUN_800130c4(DAT_8000b278,0);  //scope_pre_process_50ns_data
    }

    //Timebase 25nS/div or 10nS/div
    if ((DAT_8000b264[10] == '\x1c') || (DAT_8000b264[10] == '\x1d'))
    {
      //prepare the fpga for reading again
      fpga_write_cmd('\x1f');
      fpga_write_data(data);
      fpga_write_data(data_00);

      puVar22 = puVar6;  //1500 bytes

      if ((byte)DAT_8000b264[10] < 0xb)  //Total bullshit since this part of the code is only for 0x1C and 0x1D setting!!!
      {
        puVar22 = puVar15;
      }

      fpga_write_cmd('!');    //0x21

      fpga_bus_dir_in();
      set_gpio_pin_low(puVar18,9);
      set_gpio_pin_low(puVar18,10);
      puVar24 = puVar18;

      if (puVar22 != (uint *)0x0)
      {
        puVar24 = DAT_8000b27c;  //0x01C208A0
      }

      //read the bytes
      puVar21 = (uint *)0x0;
      if (puVar22 != (uint *)0x0)
      {
        do {
          set_gpio_pin_low(puVar18,8);
          set_gpio_pin_high(puVar18,8);
          iVar19 = (int)puVar21 * 2;
          puVar21 = (uint *)((uint)((int)puVar21 + 1) & 0xfffeffff);
          *(ushort *)(DAT_8000b280 + iVar19) = (ushort)*puVar24 & 0xff;     //0x8019ED5A
        } while (puVar21 < puVar22);
      }

      FUN_8000460c();   //Different functions for channel 1 and 2  scope_pre_process_25ns_data, since most likely same processing on different data
      FUN_800062bc();   //scope_process_25ns_data
    }

    //Process further on the total data
    puVar22 = puVar12;    // = 2500

    //Check on time base and set number of bytes read
    if(((byte)DAT_8000b264[10] < 0x19) && (puVar22 = puVar6, (byte)DAT_8000b264[10] < 9))  //=1500
    {
      puVar22 = puVar15;  //=750
    }

/*
                             LAB_8000aad0                                    XREF[1]:     8000aa24(j)  
        8000aad0 8c 07 9f e5     ldr        r0,[DAT_8000b264]                                = 8019D5A0h
        8000aad4 0a 10 d0 e5     ldrb       r1,[r0,#0xa]=>DAT_8019d5aa
        8000aad8 19 00 51 e3     cmp        r1,#0x19
        8000aadc 08 40 a0 21     movcs      r4,r8                               =0x09c4  == 2500
        8000aae0 03 00 00 2a     bcs        LAB_8000aaf4
        8000aae4 0a 10 d0 e5     ldrb       r1,[r0,#0xa]=>DAT_8019d5aa
        8000aae8 09 00 51 e3     cmp        r1,#0x9
        8000aaec 07 40 a0 21     movcs      r4,r7                               =0x05DC  == 1500
        8000aaf0 06 40 a0 31     movcc      r4,r6                               =0x02EE  == 750
*/


    //Translate based on channel 1 volts per div
    uVar14 = translate_parameter(0xb,(uint)(byte)DAT_8000b264[3]);


    uVar13 = DAT_8000b288;    //0x51EB851F
    pcVar2 = DAT_8000b264;    //0x8019D5A0
    puVar16 = DAT_8000b278;   //0x8019D5EA
    puVar17 = DAT_8000b284;   //0x801A916A   some target buffer
    puVar4 = DAT_8000b284;    //0x801A916A
    puVar5 = DAT_8000b290;    //0x801AC04A   channel 1 buffer

    while (puVar22 != (uint *)0x0)
    {
      //Same processing as in long time base
      uVar20 = (uVar14 & 0xffff) * (uint)*puVar16 & 0xffff;

      uVar1 = (ushort)(DAT_8000b28c * uVar20 + DAT_8000b28c >> 0x10);
      uVar11 = uVar1 >> 6;

      if (0x32 < (int)(uVar20 + (uint)((ulonglong)uVar20 * (ulonglong)uVar13 >> 0x25) * -100))
      {
        uVar11 = (uVar1 >> 6) + 1;
      }

      puVar22 = (uint *)((int)puVar22 + -1);
      *puVar17 = uVar11;
      puVar16 = puVar16 + 1;
      puVar17 = puVar17 + 1;
    }


    //Same setup for getting count
    puVar22 = puVar12;    // = 2500

    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar6, (byte)pcVar2[10] < 9))
    {
      puVar22 = puVar15;
    }

    pcVar2 = DAT_8000b264;   //0x8019D5A0
    puVar4 = DAT_8000b284;   //0x801A916A    buffer with converted trace data
    puVar5 = DAT_8000b290;   //0x801AC04A    channel 1 buffer

    puVar16 = puVar4 + -1;  //Point to sample before the buffers start to overcome odd number of samples copying.
    puVar17 = puVar5 + -1;

    if (((uint)puVar22 & 1) == 0) // See if even number of samples
    {
      *puVar5 = *puVar4;  //Copy first sample
      puVar16 = puVar4;   //Point to start of buffers
      puVar17 = puVar5;
    }

    uVar11 = puVar16[1];  //Get the second sample
    iVar19 = (int)puVar22 + -1 >> 1;  //Take one of and div by two since two samples copied in one loop

    while (iVar19 != 0)     //Some copy action to the second channel trace buffer???????????
    {
      uVar1 = puVar16[2];    //Get third sample
      puVar17[1] = uVar11;   //Store second sample
      uVar11 = puVar16[3];   //Get fourth sample
      iVar19 = iVar19 + -1;  //One sample done
      puVar17 = puVar17 + 2; //Point to third sample
      *puVar17 = uVar1;      //Save it
      puVar16 = puVar16 + 2; //Point to third sample
    }

    iVar19 = (int)puVar22 + -1;

    if (-1 < iVar19)
    {
      puVar5[iVar19] = puVar4[iVar19];  //copy some last sample
    }

    //Get the size again based on the time base setting
    puVar22 = puVar12;    // = 2500

    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar6, (byte)pcVar2[10] < 9))
    {
      puVar22 = puVar15;
    }

    puVar16 = DAT_8000b290;     //0x801AC04A  buffer data is copied to
    puVar18 = puVar12;    // = 2500
    uVar13 = DAT_8000b294;      //0x00000191  limit value also used in long time base


    //Samples to handle and volt per div on smallest range
    if ((pcVar2[3] == '\x06') && (puVar22 != (uint *)0x0))
    {
      puVar16 = puVar5 + -1;               //0x801AC04A

      if (((uint)puVar22 & 1) != 0)
      {
        *puVar5 = *puVar5 << 1;
        puVar16 = puVar5;
      }

      uVar13 = (uint)puVar22 >> 1;

      while (uVar13 != 0)
      {
        puVar17 = puVar16 + 2;
        uVar13 = uVar13 - 1;
        puVar16[1] = puVar16[1] << 1;
        *puVar17 = *puVar17 << 1;
        puVar16 = puVar17;
      }


      puVar24 = (uint *)0x0;
      puVar16 = DAT_8000b290;              //0x801AC04A  buffer data is copied to
      uVar13 = DAT_8000b294;               //0x00000191  limit value also used in long time base

      if (puVar22 != (uint *)0x0)
      {
        do
        {
          puVar16 = puVar5 + (int)puVar24;

          if (*puVar16 < *(ushort *)(pcVar2 + 6))   //Screen trace offset
          {
            *puVar16 = 0;
          }
          else
          {
            *puVar16 = *puVar16 - *(short *)(pcVar2 + 6);
          }

          puVar24 = (uint *)((uint)((int)puVar24 + 1) & 0xfffeffff);
          puVar16 = DAT_8000b290;
          uVar13 = DAT_8000b294;
        } while (puVar24 < puVar22);
      }
    }

    do
    {
      if (uVar13 < *puVar16)            //Limit the data
      {
        *puVar16 = (ushort)uVar13;
      }

      puVar18 = (uint *)((int)puVar18 + -1);
      puVar16 = puVar16 + 1;
    } while (puVar18 != (uint *)0x0);


    puVar16 = DAT_8000b290;      //0x801AC04A
    iVar19 = DAT_8000b298;       //0x00000BB6   2998

//This is basically a filter where the data is averaged when a spike occurs.
//If the outer points are both more then 6 below or both more then 6 above above the middle sample it is smoothed

    if ((byte)pcVar2[10] < 0x19)   //Timebase
    {
      do
      {
        uVar13 = (uint)*puVar16;     //Get a sample

        uVar20 = (uint)puVar16[1];   //Get the next sample
        uVar14 = (uint)puVar16[2];   //And the one after that

        uVar25 = uVar13 + 6;         //Add 6 to the first one


        bVar27 = uVar25 <= uVar20;   //Check if it is smaller or equal to the next sample
        bVar26 = uVar20 == uVar25;   //Check if it is equal

        if (bVar27 && !bVar26)       //When it is smaller but not equal
        {
          uVar25 = uVar14 + 6;       //Use the third sample plus 6
        }

        if (bVar27 && !bVar26)       //When it is smaller but not equal
        {
          bVar27 = uVar25 <= uVar20;  //Check it again with the third sample
          bVar26 = uVar20 == uVar25;
        }

        if (bVar27 && !bVar26)        //When that is smaller make the middle sample an average of the other two
        {
          puVar16[1] = (ushort)(uVar13 + uVar14 >> 1);
        }

        if (uVar20 + 6 < uVar13 && uVar20 + 6 < uVar14)  //Check if the middle sample plus 6  is less then the other samples
        {
          puVar16[1] = (ushort)(uVar13 + uVar14 >> 1);   //If so make it the average of the two
        }

        iVar19 = iVar19 + -1;
        puVar16 = puVar16 + 1;
      } while (iVar19 != 0);
    }

    FUN_800049a0();
    FUN_80006654();

//Tot hier gehad














    if (pcVar2[0x48] == '\0')
    {
      FUN_80003ec8();
    }
  }











  //Channel 2 handling
  if (DAT_8000b264[0xc] != '\0')
  {
    fpga_write_cmd('\x1f');
    fpga_write_data(data);
    fpga_write_data(data_00);

    puVar22 = puVar6;

    if ((byte)DAT_8000b264[10] < 0xb)
    {
      puVar22 = puVar15;
    }

    uVar13 = translate_parameter(0xd,(uint)(byte)DAT_8000b264[0x23]);

    fpga_write_cmd((uchar)uVar13);

    fpga_bus_dir_in();
    puVar24 = DAT_8000b274;
    set_gpio_pin_low(DAT_8000b274,9);
    set_gpio_pin_low(puVar24,10);
    puVar16 = DAT_8000b29c;                      //0x801A04CA
    puVar18 = (uint *)0x0;

    if (puVar22 != (uint *)0x0) {
      do {
        set_gpio_pin_low(puVar24,8);
        set_gpio_pin_high(puVar24,8);
        puVar17 = puVar16 + (int)puVar18;
        puVar18 = (uint *)((uint)((int)puVar18 + 1) & 0xfffeffff);
        *puVar17 = (ushort)*DAT_8000b27c & 0xff;
      } while (puVar18 < puVar22);
    }
    pcVar2 = DAT_8000b264;
    *puVar16 = puVar16[1];
    if (pcVar2[0x23] == '\x01') {
      local_30 = FUN_800291e0();
    }
    if (pcVar2[10] == '\x19') {
      FUN_8001363c(DAT_8000b29c,0,puVar12);
    }
    if (pcVar2[10] == '\x1a') {
      FUN_800141c8(DAT_8000b29c,0,puVar12);
    }
    if (pcVar2[10] == '\x1b') {
      FUN_800130c4(DAT_8000b29c,0,puVar12);
    }
    if ((DAT_8000b264[10] == '\x1c') || (DAT_8000b264[10] == '\x1d')) {
      fpga_write_cmd('\x1f');
      fpga_write_data(data);
      fpga_write_data(data_00);
      puVar22 = puVar6;
      if ((byte)DAT_8000b264[10] < 0xb) {
        puVar22 = puVar15;
      }
      fpga_write_cmd('#');
      fpga_bus_dir_in();
      set_gpio_pin_low(puVar24,9);
      set_gpio_pin_low(puVar24,10);
      if (puVar22 != (uint *)0x0) {
        puVar16 = DAT_8000b2a0;
        puVar18 = DAT_8000b27c;
      }
      puVar21 = (uint *)0x0;
      if (puVar22 != (uint *)0x0) {
        do {
          set_gpio_pin_low(puVar24,8);
          set_gpio_pin_high(puVar24,8);
          puVar17 = puVar16 + (int)puVar21;
          puVar21 = (uint *)((uint)((int)puVar21 + 1) & 0xfffeffff);
          *puVar17 = (ushort)*puVar18 & 0xff;
        } while (puVar21 < puVar22);
      }
      FUN_80007380();
      FUN_80009018();
    }
    pcVar2 = DAT_8000b264;
    puVar22 = puVar12;
    if (((byte)DAT_8000b264[10] < 0x19) && (puVar22 = puVar6, (byte)DAT_8000b264[10] < 9)) {
      puVar22 = puVar15;
    }
    uVar14 = translate_parameter(0xb,(uint)(byte)DAT_8000b264[0xf]);
    uVar13 = DAT_8000b288;
    puVar16 = DAT_8000b29c;
    puVar17 = DAT_8000b2a4;
    puVar4 = DAT_8000b2a4;
    puVar5 = DAT_8000b2a8;
    while (DAT_8000b2a4 = puVar4, DAT_8000b2a8 = puVar5, puVar22 != (uint *)0x0) {
      uVar20 = (uVar14 & 0xffff) * (uint)*puVar16 & 0xffff;
      uVar1 = (ushort)(DAT_8000b28c * uVar20 + DAT_8000b28c >> 0x10);
      uVar11 = uVar1 >> 6;
      if (0x32 < (int)(uVar20 + (uint)((ulonglong)uVar20 * (ulonglong)uVar13 >> 0x25) * -100)) {
        uVar11 = (uVar1 >> 6) + 1;
      }
      puVar22 = (uint *)((int)puVar22 + -1);
      *puVar17 = uVar11;
      puVar16 = puVar16 + 1;
      puVar17 = puVar17 + 1;
      puVar4 = DAT_8000b2a4;
      puVar5 = DAT_8000b2a8;
    }
    puVar22 = puVar12;
    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar6, (byte)pcVar2[10] < 9)) {
      puVar22 = puVar15;
    }
    puVar16 = puVar4 + -1;
    puVar17 = puVar5 + -1;
    if (((uint)puVar22 & 1) == 0) {
      *puVar5 = *puVar4;
      puVar16 = puVar4;
      puVar17 = puVar5;
    }
    uVar11 = puVar16[1];
    iVar19 = (int)puVar22 + -1 >> 1;
    while (iVar19 != 0) {
      uVar1 = puVar16[2];
      puVar17[1] = uVar11;
      uVar11 = puVar16[3];
      iVar19 = iVar19 + -1;
      puVar17 = puVar17 + 2;
      *puVar17 = uVar1;
      puVar16 = puVar16 + 2;
    }
    iVar19 = (int)puVar22 + -1;
    if (-1 < iVar19) {
      puVar5[iVar19] = puVar4[iVar19];
    }
    puVar22 = puVar12;
    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar15, 8 < (byte)pcVar2[10])) {
      puVar22 = puVar6;
    }
    puVar16 = DAT_8000b2a8;
    uVar13 = DAT_8000b294;
    if ((pcVar2[0xf] == '\x06') && (puVar22 != (uint *)0x0)) {
      puVar16 = puVar5 + -1;
      if (((uint)puVar22 & 1) != 0) {
        *puVar5 = *puVar5 << 1;
        puVar16 = puVar5;
      }
      uVar13 = (uint)puVar22 >> 1;
      while (uVar13 != 0) {
        puVar17 = puVar16 + 2;
        uVar13 = uVar13 - 1;
        puVar16[1] = puVar16[1] << 1;
        *puVar17 = *puVar17 << 1;
        puVar16 = puVar17;
      }
      puVar15 = (uint *)0x0;
      puVar16 = DAT_8000b2a8;
      uVar13 = DAT_8000b294;
      if (puVar22 != (uint *)0x0) {
        do {
          puVar16 = puVar5 + (int)puVar15;
          if (*puVar16 < *(ushort *)(pcVar2 + 0x12)) {
            *puVar16 = 0;
          }
          else {
            *puVar16 = *puVar16 - *(short *)(pcVar2 + 0x12);
          }
          puVar15 = (uint *)((uint)((int)puVar15 + 1) & 0xfffeffff);
          puVar16 = DAT_8000b2a8;
          uVar13 = DAT_8000b294;
        } while (puVar15 < puVar22);
      }
    }
    do {
      if (uVar13 < *puVar16) {
        *puVar16 = (ushort)uVar13;
      }
      puVar12 = (uint *)((int)puVar12 + -1);
      puVar16 = puVar16 + 1;
    } while (puVar12 != (uint *)0x0);
    puVar16 = DAT_8000b2a8;
    iVar19 = DAT_8000b298;
    if ((byte)pcVar2[10] < 0x19) {
      do {
        uVar14 = (uint)*puVar16;
        uVar13 = (uint)puVar16[1];
        uVar20 = (uint)puVar16[2];
        uVar25 = uVar14 + 6;
        bVar27 = uVar25 <= uVar13;
        bVar26 = uVar13 == uVar25;
        if (bVar27 && !bVar26) {
          uVar25 = uVar20 + 6;
        }
        if (bVar27 && !bVar26) {
          bVar27 = uVar25 <= uVar13;
          bVar26 = uVar13 == uVar25;
        }
        if (bVar27 && !bVar26) {
          puVar16[1] = (ushort)(uVar14 + uVar20 >> 1);
        }
        if (uVar13 + 6 < uVar14 && uVar13 + 6 < uVar20) {
          puVar16[1] = (ushort)(uVar14 + uVar20 >> 1);
        }
        iVar19 = iVar19 + -1;
        puVar16 = puVar16 + 1;
      } while (iVar19 != 0);
    }
    FUN_80007714();
    FUN_800093ac();
    if (pcVar2[0x48] == '\0') {
      FUN_80006ce8();
    }
  }







  pcVar2 = DAT_8000b264;   //0x8019D5A0

  if (0x18 < (byte)DAT_8000b264[10])  //Timebase
  {
    if (DAT_8000b264[0x23] == '\0')    //Trigger channel on channel 1
    {
      if (*DAT_8000b264 != '\0')       //channel 1 enabled
      {
        FUN_80006a94(*(undefined2 *)(DAT_8000b264 + 0x26));  //trigger level screen offset
        FUN_80005080();
      }

      if (pcVar2[0xc] != '\0')  //channel 2 enabled
      {
        FUN_80008fac();
        FUN_80007df4();
      }
    }
    else
    {
      //trigger on channel 2
      if (DAT_8000b264[0xc] != '\0')    //channel 2 enabled
      {
        FUN_800097e0(*(undefined2 *)(DAT_8000b264 + 0x26));
        FUN_80007df4();
      }

      if (*pcVar2 != '\0')    //channel 1 enabled
      {
        FUN_80006250();
        FUN_80005080();
      }
    }
  }

  if (local_30 == 0)
  {
    pcVar2[0x1e] = '\0';     //scopesettings.triggerflag4
    pcVar2[0x18] = '\x01';   //scopesettings.triggerflag2
    pcVar2[0x17] = '\x01';   //scopesettings.triggerflag1
  }
  else
  {
    pcVar2[0x1e] = '\x01';
    pcVar2[0x18] = '\0';
    pcVar2[0x17] = '\0';
  }
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

