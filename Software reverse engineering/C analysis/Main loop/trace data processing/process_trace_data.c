//-----------------------------------------------------------------------------------------------
//scope_process_trace_data
void process_trace_data(void)

{
  char cVar1;
  ushort uVar2;
  undefined2 uVar3;
  short sVar4;
  int *piVar5;
  int *piVar6;
  int iVar7;
  undefined *puVar8;
  char *pcVar9;
  undefined *puVar10;
  uint *ptr;
  ushort *puVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  ushort *puVar16;
  ushort *puVar17;
  int iVar18;
  ushort uVar19;
  uint uVar20;
  int iVar21;
  uint extraout_r1;
  undefined2 *puVar22;
  int iVar23;
  uint uVar24;
  int iVar25;
  int unaff_r4;
  uint uVar26;
  uint uVar27;
  ushort uVar28;
  uint uVar29;
  int iVar30;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar31;
  undefined8 uVar32;
  undefined8 uVar33;
  
  //For time base setting 100mS to 50S the code within the if is used.
  if (*(byte *)(DAT_80025460 + 10) < 9)   //Time base setting. 0x8019D5AA. 0 - 8 ==> 50S/div ~ 100mS/div
  {
    iVar13 = 2000;

    //This is written before every trace data read
    fpga_write_cmd('\r');       //Write command 0x0D
    fpga_write_data('\0');
    fpga_write_data('\0');
    fpga_write_data('\a');      //0x07
    fpga_write_data(-0x30);     //0xD0


    //From here on it is function FUN_80025750 (only called from this point so maybe not a separate function
    puVar10 = PTR_DAT_80025adc;                 //0x80192f02. touch panel data

    puVar8 = PTR_initialization_data_80025ad8;  //0x80192e9c

    iVar7 = DAT_80025ad4;                       //0x8019D5A0. base of settings

    switch(*(undefined *)(DAT_80025ad4 + 10))   //0x8019d5aa. Again time base setting
    {
    case 0:
      iVar13 = 2000;
      break;
    case 1:
      iVar13 = 1000;
      break;
    case 2:
      iVar13 = 400;
      break;
    case 3:
      iVar13 = 200;
      break;
    case 4:
      iVar13 = 0x50;
      break;
    case 5:
      iVar13 = 0x28;
      break;
    case 6:
      iVar13 = 0x14;
      break;
    case 7:
      iVar13 = 8;
      break;
    case 8:
      iVar13 = 4;
    }

    iVar21 = *(int *)(PTR_initialization_data_80025ad8 + 8);   //0x80192ea4 some previous timer ticks

    do
    {
      uVar14 = get_timer_ticks();

      //So some variable wait depending on the time base. This is error prone on timer overflow
      if ((uint)(iVar13 + iVar21) <= uVar14)
      {
        *(uint *)(puVar8 + 8) = uVar14;          //On time out store the current timer ticks
        goto LAB_8002582c;
      }
    //For smaller timeouts (500mS, 200mS and 100mS) stay in the loop even when there is touch
    } while ((5 < *(byte *)(iVar7 + 10)) || (tp_i2c_read_status(), *puVar10 == '\0'));


    delay_2(0x28);                                    //Timer based delay. 40mS

LAB_8002582c:
    fpga_write_cmd('(');                              //Write command 0x28
    fpga_write_data('\x01');                          //with data 0x01

    uVar26 = 0;
    fpga_write_cmd('$');                              //Write command 0x24

    fpga_bus_dir_in();                                //Read 10 bytes of data from the FPGA
    ptr = DAT_80025ae0;                               //0x01C20890
    set_gpio_pin_low(DAT_80025ae0,9);
    set_gpio_pin_low(ptr,10);
    uVar14 = 0;

    do
    {
      set_gpio_pin_low(ptr,8);
      set_gpio_pin_high(ptr,8);
      uVar14 = uVar14 + 1 & 0xfffeffff;
      uVar26 = (ptr[4] & 0xff) + uVar26 & 0xfffeffff; //Get the data and sum them together
    } while (uVar14 < 10);

    iVar13 = divide(uVar26,10);                       //Calculate an average of these 10 samples

    puVar17 = DAT_80025ae4;                           //0x8019D5EA
 
    *DAT_80025ae4 = (ushort)iVar13 & 0xff;            //0x8019D5EA. Store the signal average


    uVar26 = 0;                                       //Repeat this for channel 2
    fpga_write_cmd('&');                              //Write command 0x26
    fpga_bus_dir_in();
    set_gpio_pin_low(ptr,9);
    set_gpio_pin_low(ptr,10);
    uVar14 = 0;

    do
    {
      set_gpio_pin_low(ptr,8);
      set_gpio_pin_high(ptr,8);
      uVar14 = uVar14 + 1 & 0xfffeffff;
      uVar26 = (ptr[4] & 0xff) + uVar26 & 0xfffeffff;
    } while (uVar14 < 10);

    uVar15 = divide(uVar26,10);

    *DAT_80025ae8 = (short)(uVar15 & 0xff);          //0x801A04CA. Store the signal average





    puVar11 = DAT_80025af4;                          //0x801A916A
    uVar14 = DAT_80025af0;                           //0x51EB851F
    puVar16 = DAT_80025aec;                          //0x802F18F8  Some base address of a set of data. Set on init???
    uVar26 = extraout_r1;

    switch(*(undefined *)(iVar7 + 3))                //Switch on channel 1 volts / div to get some divider (trigger level divider in my code. Needs to be signal adjuster)
    {
    case 0:
      uVar26 = (uint)*DAT_80025aec;                  //0xAD
      break;
    case 1:
      uVar26 = (uint)DAT_80025aec[1];                //0xAF
      break;
    case 2:
      uVar26 = (uint)DAT_80025aec[2];                //0xB4
      break;
    case 3:
      uVar26 = (uint)DAT_80025aec[3];                //0xB4
      break;
    case 4:
      uVar26 = (uint)DAT_80025aec[4];                //0xB8
      break;
    case 5:
      uVar26 = (uint)DAT_80025aec[5];                //0xB8
      break;
    case 6:
      uVar26 = (uint)DAT_80025aec[6];                //0xB8
    }

    uVar26 = *puVar17 * uVar26 & 0xffff;              //0x8019D5EA. Multiply stored average with this signal divider????

    //Sample
    //0xFF x 0xB4 = 0xB34C
    //0x51EB851F * 0xB34C = 0x396000003234
    //0x396000003234 >> 0x25 = 0x1CB
    //0x1CB * -100 = 0xFFFF4CB4
    //0xB34C + 0xFFFF4CB4 = 0

    //0x51EB851F >> 0x0F = 0xA3D7
    //0xA3D7 * 0xB34C = 0x72BFF8D4
    //0x72BFF8D4 + 0xa3d7 = 0x72C09CAB
    //72C09CAB >> 0x16 = 0x1CB

    //Sample
    //0x24 * 0xB4 = 0x1950 * 0x51EB851F = 0x8199999A0B0 >> 0x25 = 0x40 * -100 = 0xFFFFE700   0x1950 + 0xFFFFE700 = 0x0050

    //0x51EB851F >> 0x0F = 0xA3D7 * 0x1950 = 0x10333230 + 0xa3d7 >> 0x16 = 0x40

    //r12 = 0x51EB851F
    //r1  = uVar26
    //umull r4,r3,r12,r1    r4 = low result, r3 = high result
    //mvn r4,#0x18          r4 = 0xFFFFFFE7
    //mov r3,r3, lsr #0x5   is >> 0x25
    //mul r3,r4,r3
    //add r4,r1,r3, lsl #0x2 makes uVar26 + ((uint)((ulonglong)uVar26 * (ulonglong)DAT_80025af0 >> 0x25) * -100)



    uVar28 = (ushort)(((int)DAT_80025af0 >> 0xf) * uVar26 + 0xa3d7 >> 0x10); //Do some processing on it???


    uVar19 = uVar28 >> 6;

    if (0x32 < (int)(uVar26 + (uint)((ulonglong)uVar26 * (ulonglong)DAT_80025af0 >> 0x25) * -100))
    {
      uVar19 = (uVar28 >> 6) + 1;
    }

    *DAT_80025af4 = uVar19;    //Store the result at 0x801a916a

    uVar26 = DAT_80025afc;     //0x00000191 (max displayable y pixels??)

    puVar17 = DAT_80025af8;    //0x801AC04A

    uVar28 = *puVar11;         //0x801A916A  original data = temp1

    *DAT_80025af8 = uVar28;    //Store the result at 0x801ac04a

    if (uVar26 < uVar28)       //Signal outside displayable range
    {
      *puVar17 = (ushort)uVar26;  //Max it on what is displayable
    }


    puVar17 = DAT_80025b00;     //0x801AA8DA

    switch(*(undefined *)(iVar7 + 0xf))     //Channel 2 volts per div
    {
    case 0:
      puVar16 = (ushort *)(uint)*puVar16;
      break;
    case 1:
      puVar16 = (ushort *)(uint)puVar16[1];
      break;
    case 2:
      puVar16 = (ushort *)(uint)puVar16[2];
      break;
    case 3:
      puVar16 = (ushort *)(uint)puVar16[3];
      break;
    case 4:
      puVar16 = (ushort *)(uint)puVar16[4];
      break;
    case 5:
      puVar16 = (ushort *)(uint)puVar16[5];
      break;
    case 6:
      puVar16 = (ushort *)(uint)puVar16[6];
    }

    //Do the same for channel 2
    uVar15 = (uVar15 & 0xff) * (int)puVar16 & 0xff00ffff;

    uVar28 = (ushort)(DAT_80025b04 * uVar15 + 0xa3d7 >> 0x10);
    uVar19 = uVar28 >> 6;
    if (0x32 < (int)(uVar15 + (uint)((ulonglong)uVar15 * (ulonglong)uVar14 >> 0x25) * -100))
    {
      uVar19 = (uVar28 >> 6) + 1;
    }
    *DAT_80025b00 = uVar19;
    puVar16 = DAT_80025b08;
    uVar28 = *puVar17;
    *DAT_80025b08 = uVar28;   //0x801AD7BA
    if (uVar26 < uVar28) 
    {
      *puVar16 = (ushort)uVar26;
    }

    //After this it jumps into display trace data
  }
  else 
  {
    //0x8019D5A0 + 3A = run mode ==> 0 is run, 0x80192f08 is touch state, where 2 seems to be moving of traces
    if ((*(char *)(DAT_80025460 + 0x3a) != '\x01') && (*PTR_DAT_80025464 != '\x02'))
    {
      //Partialy done!!!!!!!!!!!!!
      //scope_get_short_timebase_data in my code
      FUN_80025468();  //process short time base data



      //Still needs to be done!!!!!!!!!!
      //This is function FUN_80021a78 which is also only called from here
      iVar7 = DAT_80021bd4;
      uVar14 = DAT_80021bd0;
      pcVar9 = DAT_80021bcc;

      if (*DAT_80021bcc != '\0')
      {
        if ((byte)DAT_80021bcc[10] < 0xb)
        {
          iVar13 = 100;
          iVar21 = 600;
        }
        else
        {
          iVar13 = 200;
          iVar21 = 0x4b0;
        }

        uVar27 = 0;
        iVar12 = 0;
        puVar17 = (ushort *)(DAT_80021bd8 + iVar13 * 2);
        uVar26 = iVar21 - iVar13 & 0xffff;
        uVar15 = DAT_80021bd0;

        do
        {
          uVar24 = (uint)*puVar17;
          puVar17 = puVar17 + 1;

          if (uVar27 < uVar24)
          {
            uVar27 = uVar24;
          }

          iVar12 = iVar12 + uVar24;

          if (uVar24 < uVar15)
          {
            uVar15 = uVar24;
          }

          uVar26 = uVar26 - 1 & 0xffff;
        } while (uVar26 != 0);

        iVar13 = divide(iVar12,iVar21 - iVar13);

        *(short *)(iVar7 + 0xe4) = (short)uVar27;
        *(short *)(iVar7 + 0xe6) = (short)uVar15;
        *(short *)(iVar7 + 0xea) = (short)(uVar27 + uVar15 >> 1);
        *(short *)(iVar7 + 0xe8) = (short)uVar27 - (short)uVar15;
        *(short *)(iVar7 + 0xec) = (short)iVar13;

        FUN_80004a50();
        FUN_8000519c();
      }

      if (pcVar9[0xc] == '\0')
      {
        return;
      }

      uVar26 = 0;

      if ((byte)pcVar9[10] < 0xb)
      {
        iVar13 = 100;
        iVar21 = 600;
      }
      else
      {
        iVar13 = 200;
        iVar21 = 0x4b0;
      }

      puVar17 = (ushort *)(DAT_80021bdc + iVar13 * 2);
      iVar12 = 0;
      uVar15 = iVar21 - iVar13 & 0xffff;

      do
      {
        uVar27 = (uint)*puVar17;

        if (uVar26 < uVar27)
        {
          uVar26 = uVar27;
        }

        if (uVar27 < uVar14)
        {
          uVar14 = uVar27;
        }

        uVar15 = uVar15 - 1 & 0xffff;
        iVar12 = iVar12 + uVar27;
        puVar17 = puVar17 + 1;
      } while (uVar15 != 0);

      iVar13 = divide(iVar12,iVar21 - iVar13);

      *(short *)(iVar7 + 0xee) = (short)uVar26;
      *(short *)(iVar7 + 0xf0) = (short)uVar14;
      *(short *)(iVar7 + 0xf4) = (short)(uVar26 + uVar14 >> 1);
      *(short *)(iVar7 + 0xf2) = (short)uVar26 - (short)uVar14;
      *(short *)(iVar7 + 0xf6) = (short)iVar13;

      FUN_800077c4();

      iVar21 = DAT_8000855c;
      iVar13 = DAT_80008558;
      iVar7 = DAT_80008554;
      uVar26 = (uint)*(ushort *)(DAT_8000855c + 0xfc);
      uVar15 = (uint)*(ushort *)(DAT_8000855c + 0xfe);
      uVar28 = *(ushort *)(DAT_8000855c + 0xee);
      uVar14 = 0;

      if (*(byte *)(DAT_80008554 + 10) < 0xb)
      {
        uVar27 = 2;
      }
      else
      {
        uVar27 = 10;
      }

      uVar20 = 0;
      uVar19 = *(ushort *)(DAT_8000855c + 0xf0);
      uVar2 = *(ushort *)(DAT_8000855c + 0xf2);
      uVar24 = uVar26;

      if (uVar26 < uVar15)
      {
        do
        {
          uVar29 = (uint)*(ushort *)(DAT_80008558 + uVar24 * 2);
          uVar24 = uVar24 + 1 & 0xfffeffff;

          if (uVar29 < *(ushort *)(DAT_80008554 + 0x12))
          {
            uVar20 = uVar20 + (*(ushort *)(DAT_80008554 + 0x12) - uVar29);
          }
          else
          {
            uVar14 = uVar14 + (uVar29 - *(ushort *)(DAT_80008554 + 0x12));
          }
        } while (uVar24 < uVar15);

        if (uVar20 <= uVar14)
          goto LAB_80007fac;

        iVar12 = uVar20 - uVar14;
        *(undefined *)(DAT_8000855c + 0x1e3) = 1;
      }
      else
      {
LAB_80007fac:
        iVar12 = uVar14 - uVar20;
        *(undefined *)(DAT_8000855c + 0x1e3) = 0;
      }

      uVar14 = divide(iVar12,uVar15 - uVar26);

      if (uVar2 < 0x28)
      {
        *(undefined2 *)(iVar21 + 0xfc) = 0x32;
        *(undefined2 *)(iVar21 + 0xfe) = 0x3b6;
      }

      iVar12 = 0;
      uVar26 = (uint)*(ushort *)(iVar21 + 0xfc);

      while (uVar26 < *(ushort *)(iVar21 + 0xfe))
      {
        uVar15 = (uint)*(ushort *)(iVar13 + uVar26 * 2);
        uVar26 = uVar26 + 1 & 0xfffeffff;

        if (uVar15 < *(ushort *)(iVar7 + 0x12))
        {
          iVar18 = *(ushort *)(iVar7 + 0x12) - uVar15;
        }
        else
        {
          iVar18 = uVar15 - *(ushort *)(iVar7 + 0x12);
        }

        iVar12 = iVar12 + iVar18 * iVar18;
      }

      iVar13 = divide(iVar12,(uint)*(ushort *)(iVar21 + 0xfe) - (uint)*(ushort *)(iVar21 + 0xfc));
      piVar6 = DAT_80008564;
      puVar8 = PTR_DAT_80008560;
      uVar26 = (uint)(byte)PTR_DAT_80008560[3];
      DAT_80008564[uVar26] = (uint)uVar28;
      piVar6[uVar26 + 0x1e] = (uint)uVar19;
      piVar6[uVar26 + 0x3c] = iVar13;
      uVar15 = uVar26 + 1 & 0xff;
      piVar6[uVar26 + 0x5a] = uVar14 & 0xffff;
      puVar8[3] = (char)uVar15;

      if (uVar15 < uVar27)
        goto LAB_800084c8;

      iVar18 = uVar27 - 1;
      iVar12 = 0;
      puVar8[3] = 0;
      iVar13 = iVar18 >> 1;

      if (0 < iVar18)
      {
        iVar12 = *piVar6;
        iVar30 = piVar6[1];
        iVar25 = 0;
        piVar5 = piVar6;
        iVar23 = iVar13;

        while (iVar23 != 0)
        {
          iVar12 = iVar12 + iVar30;
          iVar30 = piVar5[3];
          iVar23 = iVar23 + -1;
          iVar25 = iVar25 + piVar5[2];
          piVar5 = piVar5 + 2;
        }

        iVar12 = iVar12 + iVar25;
      }

      if (-1 < iVar18)
      {
        iVar12 = iVar12 + piVar6[iVar18];
      }

      uVar14 = divide(iVar12,uVar27);
      uVar14 = uVar14 & 0xffff;
      iVar12 = 0;

      if (0 < iVar18)
      {
        iVar12 = *(int *)(DAT_80008568 + 4);
        iVar30 = *(int *)(DAT_80008568 + 8);
        iVar25 = 0;
        piVar6 = (int *)(DAT_80008568 + 4);
        iVar23 = iVar13;

        while (iVar23 != 0)
        {
          iVar12 = iVar12 + iVar30;
          iVar30 = piVar6[3];
          iVar23 = iVar23 + -1;
          iVar25 = iVar25 + piVar6[2];
          piVar6 = piVar6 + 2;
        }

        iVar12 = iVar12 + iVar25;
      }

      if (-1 < (int)(uVar27 - 1))
      {
        iVar12 = iVar12 + *(int *)(DAT_8000856c + (uVar27 - 1) * 4);
      }
    
    //In this range no measurements are calculated nor shown
    //Cursors are not displayed

      uVar26 = divide(iVar12,uVar27);

      cVar1 = *(char *)(iVar7 + 0x23);
      uVar26 = uVar26 & 0xffff;
      bVar31 = cVar1 == '\x01';

      if (bVar31)
      {
        cVar1 = *(char *)(iVar7 + 0x21);
      }

      if ((bVar31 && cVar1 == '\0') && (*(char *)(DAT_80008570 + 4) != '\0'))
      {
        *(short *)(iVar7 + 0x26) = (short)(uVar14 + uVar26 >> 1);
        set_fpga_trigger_level();
      }

      iVar12 = 0;

      if (0 < iVar18)
      {
        iVar12 = *(int *)(DAT_80008574 + 4);
        iVar30 = *(int *)(DAT_80008574 + 8);
        iVar25 = 0;
        piVar6 = (int *)(DAT_80008574 + 4);
        iVar23 = iVar13;

        while (iVar23 != 0)
        {
          iVar12 = iVar12 + iVar30;
          iVar30 = piVar6[3];
          iVar23 = iVar23 + -1;
          iVar25 = iVar25 + piVar6[2];
          piVar6 = piVar6 + 2;
        }

        iVar12 = iVar12 + iVar25;
      }

      if (-1 < (int)(uVar27 - 1))
      {
        iVar12 = iVar12 + *(int *)(DAT_80008578 + (uVar27 - 1) * 4);
      }

      uVar15 = divide(iVar12,uVar27);

      iVar12 = 0;

      if (0 < iVar18)
      {
        iVar12 = *(int *)(DAT_8000857c + 4);
        iVar18 = *(int *)(DAT_8000857c + 8);
        iVar30 = 0;
        piVar6 = (int *)(DAT_8000857c + 4);

        while (iVar13 != 0)
        {
          iVar12 = iVar12 + iVar18;
          iVar18 = piVar6[3];
          iVar13 = iVar13 + -1;
          iVar30 = iVar30 + piVar6[2];
          piVar6 = piVar6 + 2;
        }

        iVar12 = iVar12 + iVar30;
      }

      if (-1 < (int)(uVar27 - 1))
      {
        iVar12 = iVar12 + *(int *)(DAT_80008580 + (uVar27 - 1) * 4);
      }

      iVar12 = divide(iVar12,uVar27);
      iVar13 = DAT_8000858c;

      switch(*(undefined *)(iVar7 + 0xf))
      {
      case 0:
        unaff_r4 = DAT_80008584;
        break;
      case 1:
        unaff_r4 = DAT_80008588;
        break;
      case 2:
        unaff_r4 = 1000;
        break;
      case 3:
        unaff_r4 = 500;
        break;
      case 4:
        unaff_r4 = 200;
        break;
      case 5:
        unaff_r4 = 100;
        break;
      case 6:
        unaff_r4 = 0x32;
      }

      if (uVar14 < *(ushort *)(iVar7 + 0x12))
      {
        *(undefined *)(iVar21 + 0x1c3) = 1;
        iVar18 = (int)((ulonglong)((longlong)iVar13 * (longlong)(int)(unaff_r4 * (*(ushort *)(iVar7 + 0x12) - uVar14))) >> 0x20);
        *(int *)(iVar21 + 0x1c4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }
      else
      {
        *(undefined *)(iVar21 + 0x1c3) = 0;
        iVar18 = (int)((ulonglong)((longlong)iVar13 * (longlong)(int)(unaff_r4 * (uVar14 - *(ushort *)(iVar7 + 0x12)))) >> 0x20);
        *(int *)(iVar21 + 0x1c4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }

      if (uVar26 < *(ushort *)(iVar7 + 0x12))
      {
        *(undefined *)(iVar21 + 0x1d3) = 1;
        iVar18 = (int)((ulonglong)((longlong)iVar13 * (longlong)(int)(unaff_r4 * (*(ushort *)(iVar7 + 0x12) - uVar26))) >> 0x20);
        *(int *)(iVar21 + 0x1d4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }
      else
      {
        *(undefined *)(iVar21 + 0x1d3) = 0;
        iVar18 = (int)((ulonglong)((longlong)iVar13 * (longlong)(int)(unaff_r4 * (uVar26 - *(ushort *)(iVar7 + 0x12)))) >> 0x20);
        *(int *)(iVar21 + 0x1d4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }

      uVar32 = FUN_800397d0(unaff_r4);

      FUN_800397d0(iVar12);

      uVar33 = FUN_80036618();

      uVar32 = FUN_80039890((int)uVar33,(int)((ulonglong)uVar33 >> 0x20),(int)uVar32,(int)((ulonglong)uVar32 >> 0x20));

      FUN_800393ec((int)uVar32,(int)((ulonglong)uVar32 >> 0x20),0,DAT_80008590);

      iVar12 = FUN_8003972c();

      *(int *)(iVar21 + 500) = iVar12;

      iVar13 = (int)((ulonglong)((longlong)iVar13 * (longlong)(int)(unaff_r4 * (uVar15 & 0xffff))) >> 0x20);
      iVar13 = (iVar13 >> 4) - (iVar13 >> 0x1f);
      *(int *)(iVar21 + 0x1e4) = iVar13;
      cVar1 = *(char *)(iVar21 + 0x1c3);

      if (cVar1 == *(char *)(iVar21 + 0x1d3))
      {
        if (cVar1 != '\0')
        {
          iVar18 = *(int *)(iVar21 + 0x1d4);
          iVar30 = *(int *)(iVar21 + 0x1c4);
        }
        else
        {
          iVar18 = *(int *)(iVar21 + 0x1c4);
          iVar30 = *(int *)(iVar21 + 0x1d4);
        }

        iVar18 = iVar18 - iVar30;

        if (cVar1 == '\0')
          goto LAB_800083f8;

        *(int *)(iVar21 + 0x204) = iVar18;
      }
      else
      {
        iVar18 = *(int *)(iVar21 + 0x1c4) + *(int *)(iVar21 + 0x1d4);
LAB_800083f8:
        *(int *)(iVar21 + 0x204) = iVar18;
      }

      uVar14 = *(uint *)(iVar21 + 0x1d4);
      uVar26 = *(uint *)(iVar21 + 0x1c4);

      if (uVar26 < uVar14)
      {
        *(uint *)(iVar21 + 0x214) = uVar14;
      }
      else
      {
        *(uint *)(iVar21 + 0x214) = uVar26;
      }

      if (*(char *)(iVar7 + 0xe) == '\x01')
      {
        *(uint *)(iVar21 + 0x1d4) = uVar14 * 10;
        *(int *)(iVar21 + 0x1e4) = iVar13 * 10;
        *(uint *)(iVar21 + 0x1c4) = uVar26 * 10;
        *(int *)(iVar21 + 500) = iVar12 * 10;
        *(int *)(iVar21 + 0x204) = *(int *)(iVar21 + 0x204) * 10;
        iVar13 = *(int *)(iVar21 + 0x214) * 10;
      }
      else
      {
        if (*(char *)(iVar7 + 0xe) != '\x02')
          goto LAB_800084c8;

        *(uint *)(iVar21 + 0x1d4) = uVar14 * 100;
        *(uint *)(iVar21 + 0x1c4) = uVar26 * 100;
        *(int *)(iVar21 + 500) = iVar12 * 100;
        *(int *)(iVar21 + 0x1e4) = iVar13 * 100;
        *(int *)(iVar21 + 0x204) = *(int *)(iVar21 + 0x204) * 100;
        iVar13 = *(int *)(iVar21 + 0x214) * 100;
      }

      *(int *)(iVar21 + 0x214) = iVar13;

LAB_800084c8:
      if (*(char *)(iVar7 + 0xf) == '\x06')
      {
        uVar28 = 0xf;
      }
      else
      {
        uVar28 = 7;
      }

      if (*(ushort *)(iVar21 + 0xf2) < uVar28)
      {
        *(undefined4 *)(iVar21 + 0x204) = 0;
      }

      if (0x13 < *(ushort *)(iVar21 + 0xf2))
      {
        return;
      }

      *(undefined4 *)(iVar21 + 0x204) = 0;

      if (*(ushort *)(iVar7 + 0x12) + 5 <= (uint)*(ushort *)(iVar21 + 0xf4))
      {
        return;
      }

      if (*(ushort *)(iVar21 + 0xf4) + 5 <= (uint)*(ushort *)(iVar7 + 0x12))
      {
        return;
      }

      *(undefined4 *)(iVar21 + 500) = 0;
      *(undefined4 *)(iVar21 + 0x1c4) = 0;
      *(undefined4 *)(iVar21 + 0x1d4) = 0;
      *(undefined4 *)(iVar21 + 0x1e4) = 0;
      *(undefined4 *)(iVar21 + 0x214) = 0;
      return;
    }
  }




  //This is display_trace_data
  pcVar9 = DAT_8002b64c;        //0x8019D5A0  settings base
  puVar8 = PTR_DAT_8002b648;    //0x80192f08  touch state machine
  cVar1 = *PTR_DAT_8002b648;    //Get the actual state

  //   touch state           trigger mode (1 = single)        run mode (1 = stop) 
  if ((cVar1 == '\x02') && ((DAT_8002b64c[0x21] != '\x01' || (DAT_8002b64c[0x3a] == '\x01'))))
  {
    DAT_8002b64c[0x18] = '\x01';
    pcVar9[0x17] = '\x01';
  }

  puVar10 = PTR_DAT_8002b65c;
  iVar13 = DAT_8002b658;
  iVar7 = DAT_8002b654;
  uVar28 = (ushort)DAT_8002b650;
  iVar21 = DAT_8002b654 + 2000;

  if (8 < (byte)pcVar9[10]) {
    if (pcVar9[0x18] != '\0') {
      set_frame_to_global_pointer();
      set_display_fg_color(0);
      display_fill_rect(2,0x2f,uVar28,uVar28 - 0xfb);
      FUN_80009af4();
    }
    if (pcVar9[0x17] == '\0') goto LAB_8002b414;
    FUN_8001b424(pcVar9 + 0x1a,pcVar9 + 0x1c);
    if (*pcVar9 != '\0') {
      if ((pcVar9[0x3a] == '\0') && (*puVar8 != '\x02')) {
        *(undefined2 *)(puVar10 + 0x12) = 400;
      }
      FUN_8000410c();
      cVar1 = pcVar9[0x21];
      bVar31 = cVar1 != '\0';
      if (bVar31) {
        cVar1 = pcVar9[0x21];
      }
      if (((!bVar31 || cVar1 == '\x02') && (0x1a < (byte)pcVar9[10])) &&
         ((pcVar9[0x23] == '\x01' || (pcVar9[9] != '\0')))) {
        FUN_8000583c();
      }
      if (*(char *)(iVar13 + 7) == '\0') {
        FUN_80012a64(*(undefined2 *)(pcVar9 + 0x1a),0,*(undefined2 *)(pcVar9 + 0x1c),DAT_8002b654);
      }
    }
    if (pcVar9[0xc] == '\0') {
LAB_8002b2e8:
      if (*(char *)(iVar13 + 7) != '\0') goto LAB_8002b2f4;
    }
    else {
      if ((pcVar9[0x3a] == '\0') && (*puVar8 != '\x02')) {
        *(undefined2 *)(puVar10 + 0x14) = 400;
      }
      FUN_80006f28();
      cVar1 = pcVar9[0x21];
      bVar31 = cVar1 != '\0';
      if (bVar31) {
        cVar1 = pcVar9[0x21];
      }
      if (((!bVar31 || cVar1 == '\x02') && (0x1a < (byte)pcVar9[10])) &&
         ((pcVar9[0x23] == '\0' || (pcVar9[0x15] != '\0')))) {
        FUN_80008594();
      }
      if (*(char *)(iVar13 + 7) == '\0') {
        FUN_80012a64(*(undefined2 *)(pcVar9 + 0x1a),0,*(undefined2 *)(pcVar9 + 0x1c),DAT_8002b668);
        goto LAB_8002b2e8;
      }
LAB_8002b2f4:
      set_frame_to_global_pointer();
      set_display_fg_color(DAT_8002b66c);
      if (*(ushort *)(pcVar9 + 0x1c) < 2) {
        *(undefined2 *)(pcVar9 + 0x1c) = 2;
      }
      uVar14 = 1;
      if (1 < (int)(*(ushort *)(pcVar9 + 0x1c) - 2)) {
        do {
          puVar17 = (ushort *)(iVar7 + uVar14 * 2);
          puVar22 = (undefined2 *)(iVar21 + uVar14 * 2);
          FUN_80018d30(*puVar17 + 0x96,*puVar22,puVar17[1] + 0x96,puVar22[1]);
          uVar14 = uVar14 + 1 & 0xfffeffff;
        } while ((int)uVar14 < (int)(*(ushort *)(pcVar9 + 0x1c) - 2));
      }
    }
    cVar1 = pcVar9[4];
    bVar31 = cVar1 != '\0';
    if (bVar31) {
      cVar1 = *pcVar9;
    }
    if (bVar31 && cVar1 != '\0') {
      FUN_800043e4();
    }
    cVar1 = pcVar9[0x10];
    bVar31 = cVar1 != '\0';
    if (bVar31) {
      cVar1 = pcVar9[0xc];
    }
    if (bVar31 && cVar1 != '\0') {
      set_display_fg_color(0);
      display_fill_rect(3,0x81,0x2d5,0xd1);
      FUN_800075dc();
      set_display_fg_color(DAT_8002b670);
      puVar22 = DAT_8002b674;
      uVar14 = 0;
      *DAT_8002b674 = DAT_8002b674[1];
      do {
        puVar17 = puVar22 + uVar14;
        if (0x50 < *puVar17) {
          *puVar17 = 0x50;
        }
        display_draw_vert_line((short)uVar14 + 3,0xd1 - *puVar17,0xd1);
        uVar14 = uVar14 + 1 & 0xfffeffff;
      } while (uVar14 < 0x2d3);
    }
LAB_8002b414:
    iVar7 = DAT_8002b678;
    if (pcVar9[0x18] == '\0') {
      return;
    }
    if (*(char *)(DAT_8002b678 + 0x292) != '\0') {
      FUN_8000eb10();
    }
    if (*(char *)(iVar7 + 0x29a) != '\0') {
      FUN_8000eb84();
    }
    cVar1 = *(char *)(iVar7 + 0x292);
    bVar31 = cVar1 == '\0';
    if (bVar31) {
      cVar1 = *(char *)(iVar7 + 0x29a);
    }
    if (!bVar31 || cVar1 != '\0') {
      FUN_8000ebf8();
    }
    FUN_8000b5cc();
    FUN_80021810();
    uVar14 = DAT_8002b67c;
    iVar13 = Start_Of_Screen_Mem;
    iVar7 = Screen_Frame_Buffer;
    uVar26 = 0x2e;
    iVar21 = DAT_8002b67c + 0xf6;
    if (DAT_8002b67c < 0x2f) {
      return;
    }
    do {
      iVar12 = uVar26 * 800 + 2;
      copy_short((void *)(iVar13 + iVar12 * 2),(void *)(iVar7 + iVar12 * 2),iVar21);
      uVar26 = uVar26 + 1;
    } while (uVar26 < uVar14);
    return;
  }
  uVar19 = (ushort)(byte)pcVar9[0x3a];
  if (uVar19 != 0) {
                    // WARNING: Could not recover jumptable at 0x8002b490. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (cVar1 != '\x02') {
    uVar19 = *(ushort *)PTR_DAT_8002b65c;
  }
  else {
    *(undefined2 *)PTR_DAT_8002b65c = 0;
  }
  if (cVar1 == '\x02' || uVar19 == 0) {
    set_frame_to_global_pointer();
    set_display_fg_color(0);
    uVar19 = (ushort)DAT_8002b67c;
    display_fill_rect(2,0x2f,uVar28,uVar19);
    FUN_80009af4();
    FUN_8000b5cc();
    copy_rect_to_screen(2,0x2e,uVar19 + 0xf7,uVar19);
    set_screen_to_global_pointer();
  }
  iVar12 = DAT_8002b680;
  if (*pcVar9 != '\0') {
    set_screen_to_global_pointer();
    iVar18 = iVar12 - (uint)*DAT_8002b684;
    *(short *)(puVar10 + 0x16) = (short)iVar18;
    iVar18 = iVar18 * 0x10000 >> 0x10;
    if (iVar18 < 0x2f) {
      iVar18 = 0x2f;
    }
    else {
      if (0x1c0 < iVar18) {
        iVar18 = 0x1c0;
      }
    }
    *(short *)(puVar10 + 0x16) = (short)iVar18;
    if (*(char *)(iVar13 + 7) == '\0') {
      FUN_800067ac();
    }
  }
  if (pcVar9[0xc] == '\0') {
LAB_8002b590:
    if (*(char *)(iVar13 + 7) == '\0') goto LAB_8002b624;
  }
  else {
    set_screen_to_global_pointer();
    iVar12 = iVar12 - (uint)*DAT_8002b688;
    *(short *)(puVar10 + 0x18) = (short)iVar12;
    iVar12 = iVar12 * 0x10000 >> 0x10;
    if (iVar12 < 0x2f) {
      iVar12 = 0x2f;
    }
    else {
      if (0x1c0 < iVar12) {
        iVar12 = 0x1c0;
      }
    }
    *(short *)(puVar10 + 0x18) = (short)iVar12;
    if (*(char *)(iVar13 + 7) == '\0') {
      FUN_800094f8();
      goto LAB_8002b590;
    }
  }
  if (*(short *)puVar10 == 0) {
    *(undefined2 *)(puVar10 + 2) = *(undefined2 *)(puVar10 + 0x16);
    *(undefined2 *)(puVar10 + 4) = *(undefined2 *)(puVar10 + 0x18);
  }
  set_display_fg_color(DAT_8002b66c);
  FUN_80018d30(*(ushort *)(puVar10 + 2) + 0x96,*(undefined2 *)(puVar10 + 4),
               *(ushort *)(puVar10 + 0x16) + 0x96,*(undefined2 *)(puVar10 + 0x18));
  FUN_80018d30(*(ushort *)(puVar10 + 2) + 0x97,*(ushort *)(puVar10 + 4) + 1,
               *(ushort *)(puVar10 + 0x16) + 0x97,*(ushort *)(puVar10 + 0x18) + 1);
  *(undefined2 *)(puVar10 + 2) = *(undefined2 *)(puVar10 + 0x16);
  uVar3 = *(undefined2 *)(puVar10 + 0x18);
  *(undefined2 *)(puVar10 + 4) = uVar3;
  uVar28 = *(ushort *)puVar10;
  *(undefined2 *)(iVar7 + (uint)uVar28 * 2) = *(undefined2 *)(puVar10 + 0x16);
  *(undefined2 *)(iVar21 + (uint)uVar28 * 2) = uVar3;
LAB_8002b624:
  sVar4 = *(short *)puVar10;
  *(ushort *)puVar10 = sVar4 + 1U;
  if (0x2cf < (ushort)(sVar4 + 1U)) {
    *(undefined2 *)puVar10 = 0;
  }
                    // WARNING: Could not recover jumptable at 0x8002b644. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}

//-----------------------------------------------------------------------------------------------

