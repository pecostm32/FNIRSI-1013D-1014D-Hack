//------------------------------------------------------------------------------------------------------------------------------------------------

void main(void)

{
  int iVar1;
  undefined auStack568 [568];
  
  sys_clock_init();
  setup_mmu();
  sys_init_uart0(BAUD_115200);
  setup_timer_int();
  sys_spi0_init();
  fpga_init();
  turn_off_brightness();
  sys_init_display();
  setup_display_lib();
  tp_i2c_setup();
  iVar1 = check_sd_card((uint)auStack568,(uint)&DAT_8003545c,1);
  if (iVar1 != 0) {
    *(undefined *)(DAT_80035460 + 2) = 100;
    fpga_write_cmd('8');
    fpga_write_data(-0x16);
    fpga_write_data((uchar)DEFAULT_BRIGHTNESS);
    set_display_color(0);
    display_clear_rect(0,0,800,0x1e0);
    set_display_color(0xff0000);
    FUN_80019730(PTR_PTR_FUN_80035468);
    FUN_800197c8(0);
    display_text(s_SD_ERROR_8003546c,0x1e,0x32);
    do {
                    // WARNING: Do nothing block with infinite loop
    } while( true );
  }
  check_hardware();
  FUN_8002a17c();
  setup_power_mon_int();
  load_config_data();
  check_sys_ok_load_config_on_fail();
  FUN_8000690c();
  FUN_80009658();
  FUN_80001314();
  FUN_8000689c();
  FUN_800095e8();
  FUN_800068d4();
  FUN_80009620();
  FUN_80012a4c();
  FUN_80024e18();
  FUN_800266c4();
  FUN_800267e8();
  FUN_80002790();
  FUN_80026808();
  FUN_800267c4();
  FUN_80026828();
  FUN_8000696c();
  FUN_800096b8();
  FUN_80017ce0();
  FUN_80026918();
  FUN_8000a024();
  FUN_8000e8f0();

  get_brightness_from_settings();

  do
  {
    FUN_8000a54c();

    FUN_800253e8();        //Scan the touch panel

    thunk_FUN_8002b124();

    FUN_8001a3b4();        //Scan the touch panel and do stuff

  } while( true );
}

//------------------------------------------------------------------------------------------------------------------------------------------------

void FUN_8000a54c(void)

{
  byte bVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  byte *pbVar5;
  int iVar6;
  uint uVar7;
  byte bVar8;
  bool bVar9;
  
  iVar2 = DAT_8000a6a8;
  bVar8 = 0xff;

  if (0xd < *(byte *)(DAT_8000a6a8 + 10))
  {
    iVar6 = 0x1e;
    goto LAB_8000a5bc;
  }

  if (*(byte *)(DAT_8000a6a8 + 10) < 0xc)
  {
    if (*(byte *)(DAT_8000a6a8 + 10) < 9)
    {
      if (6 < *(byte *)(DAT_8000a6a8 + 10))
      {
        iVar6 = 100;
        goto LAB_8000a5bc;
      }

      if (3 < *(byte *)(DAT_8000a6a8 + 10))
      {
        iVar6 = 0x32;
        goto LAB_8000a5bc;
      }

      if (1 < *(byte *)(DAT_8000a6a8 + 10))
        goto LAB_8000a5b0;
    }

    iVar6 = 3;
  }
  else
  {
LAB_8000a5b0:
    iVar6 = 10;
  }

LAB_8000a5bc:
  iVar4 = FUN_80017724(DAT_8000a6ac,0xc);

  puVar3 = PTR_DAT_8000a6b0;

  if (iVar4 == 0)
  {
    if (*(char *)(iVar2 + 0x39) == '\0')
    {
      *PTR_DAT_8000a6b0 = 0;
    }

    *(undefined *)(iVar2 + 0x39) = 1;
  }
  else
  {
    *(undefined *)(iVar2 + 0x39) = 0;
  }

  iVar4 = FUN_8001b3ac();

  uVar7 = iVar4 + (uint)((ulonglong)(uint)((int)(short)(ushort)*(byte *)(DAT_8000a6b4 + 2) *(int)(short)((short)iVar4 * 10)) * (ulonglong)DAT_8000a6b8 >> 0x28);

  if (*(char *)(iVar2 + 0x39) != '\0')
  {
    uVar7 = uVar7 - 7;
  }
  if (uVar7 < 0x19)
  {
    uVar7 = 0x19;
  }

  pbVar5 = (byte *)divide((uVar7 - 0x19) * 0x14,0x15);

  bVar1 = *puVar3;
  DAT_8000a6bc[bVar1] = (byte)pbVar5;

  if ((int)(uint)bVar1 < iVar6 + -1)
  {
    *puVar3 = bVar1 + 1;
    return;
  }

  bVar9 = iVar6 != 0;

  if (bVar9)
  {
    pbVar5 = DAT_8000a6bc;
  }

  *puVar3 = 0;

  while (bVar9)
  {
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;

    if (bVar1 < bVar8)
    {
      bVar8 = bVar1;
    }

    iVar6 = iVar6 + -1;
    bVar9 = iVar6 != 0;
  }

  *(byte *)(iVar2 + 0x38) = bVar8;

  set_frame_to_global_pointer();

  set_display_color(0xffffff);

  display_clear_rect(0x2c0,5,0x2d5,0x11);

  display_clear_rect(0x2be,9,0x2c1,0xd);

  iVar2 = DAT_8000bde4;

  if (*(byte *)(DAT_8000bde4 + 0x38) < 4)
  {
    uVar7 = 0xff0000;
  }
  else
  {
    uVar7 = 0xbb00;
  }

  set_display_color(uVar7);

  if (0x14 < *(byte *)(iVar2 + 0x38))
  {
    *(undefined *)(iVar2 + 0x38) = 0x14;
  }

  if (*(char *)(iVar2 + 0x38) != '\0')
  {
    display_clear_rect(0x2d5 - *(byte *)(iVar2 + 0x38),6,0x2d4,0x10);
  }

  if (*(char *)(iVar2 + 0x39) != '\0')
  {
    set_display_color(DAT_8000bde8);

    uVar7 = DAT_8000bdec;

    FUN_80018ca8(10,0x2c4,DAT_8000bdec);

    FUN_80018ca8(0xb,0x2c4,uVar7);

    FUN_80018ca8(0xc,0x2c4,uVar7);

    FUN_80018ef4(uVar7 | 1,8,0xe);

    FUN_80018ef4(0x2d0,9,0xd);

    FUN_80018ef4(uVar7 + 3,10);

    FUN_80018ef4(uVar7 + 4,0xb);
  }

  iVar6 = Start_Of_Screen_Mem;
  iVar2 = Screen_Frame_Buffer;
  uVar7 = 5;

  do
  {
    iVar4 = uVar7 * 800 + 0x2be;

    copy_short((void *)(iVar6 + iVar4 * 2),(void *)(iVar2 + iVar4 * 2),0x18);

    uVar7 = uVar7 + 1;
  } while (uVar7 < 0x24);

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

void FUN_800253e8(void)

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
  
  if (*(byte *)(DAT_80025460 + 10) < 9)
  {
    fpga_write_cmd('\r');
    fpga_write_data('\0');
    fpga_write_data('\0');
    fpga_write_data('\a');
    fpga_write_data(-0x30);

    iVar13 = 2000;


    puVar10 = PTR_DAT_80025adc;
    puVar8 = PTR_initialization_data_80025ad8;
    iVar7 = DAT_80025ad4;

    switch(*(undefined *)(DAT_80025ad4 + 10))
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
        break;
    }

    iVar21 = *(int *)(PTR_initialization_data_80025ad8 + 8);

    do
    {
      uVar14 = get_timer_ticks();

      if ((uint)(iVar13 + iVar21) <= uVar14)
      {
        *(uint *)(puVar8 + 8) = uVar14;
        goto LAB_8002582c;
      }
    } while ((5 < *(byte *)(iVar7 + 10)) || (tp_i2c_read_status(), *puVar10 == '\0'));

    delay_2(0x28);

LAB_8002582c:
    fpga_write_cmd('(');
    fpga_write_data('\x01');

    uVar26 = 0;

    fpga_write_cmd('$');

    fpga_bus_dir_in();
    ptr = DAT_80025ae0;
    set_gpio_pin_low(DAT_80025ae0,9);
    set_gpio_pin_low(ptr,10);
    uVar14 = 0;

    do                                          //Read data from FPGA
    {
      set_gpio_pin_low(ptr,8);
      set_gpio_pin_high(ptr,8);

      uVar14 = uVar14 + 1 & 0xfffeffff;
      uVar26 = (ptr[4] & 0xff) + uVar26 & 0xfffeffff;
    } while (uVar14 < 10);

    iVar13 = divide(uVar26,10);

    puVar17 = DAT_80025ae4;
    *DAT_80025ae4 = (ushort)iVar13 & 0xff;
    uVar26 = 0;

    fpga_write_cmd('&');

    fpga_bus_dir_in();
    set_gpio_pin_low(ptr,9);
    set_gpio_pin_low(ptr,10);
    uVar14 = 0;

    do                                          //Read data from FPGA
    {
      set_gpio_pin_low(ptr,8);
      set_gpio_pin_high(ptr,8);

      uVar14 = uVar14 + 1 & 0xfffeffff;
      uVar26 = (ptr[4] & 0xff) + uVar26 & 0xfffeffff;
    } while (uVar14 < 10);

    uVar15 = divide(uVar26,10);

    *DAT_80025ae8 = (short)(uVar15 & 0xff);
    puVar11 = DAT_80025af4;
    uVar14 = DAT_80025af0;
    puVar16 = DAT_80025aec;
    uVar26 = extraout_r1;         //remainder of divide

    switch(*(undefined *)(iVar7 + 3))
    {
      case 0:
        uVar26 = (uint)*DAT_80025aec;
        break;

      case 1:
        uVar26 = (uint)DAT_80025aec[1];
        break;

      case 2:
        uVar26 = (uint)DAT_80025aec[2];
        break;

      case 3:
        uVar26 = (uint)DAT_80025aec[3];
        break;

      case 4:
        uVar26 = (uint)DAT_80025aec[4];
        break;

      case 5:
        uVar26 = (uint)DAT_80025aec[5];
        break;

      case 6:
        uVar26 = (uint)DAT_80025aec[6];
        break;
    }

    uVar26 = *puVar17 * uVar26 & 0xffff;
    uVar28 = (ushort)(((int)DAT_80025af0 >> 0xf) * uVar26 + 0xa3d7 >> 0x10);
    uVar19 = uVar28 >> 6;

    if (0x32 < (int)(uVar26 + (uint)((ulonglong)uVar26 * (ulonglong)DAT_80025af0 >> 0x25) * -100))
    {
      uVar19 = (uVar28 >> 6) + 1;
    }

    *DAT_80025af4 = uVar19;
    uVar26 = DAT_80025afc;
    puVar17 = DAT_80025af8;
    uVar28 = *puVar11;
    *DAT_80025af8 = uVar28;

    if (uVar26 < uVar28)
    {
      *puVar17 = (ushort)uVar26;
    }

    puVar17 = DAT_80025b00;

    switch(*(undefined *)(iVar7 + 0xf))
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
        break;
    }

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
    *DAT_80025b08 = uVar28;

    if (uVar26 < uVar28)
    {
      *puVar16 = (ushort)uVar26;
    }
  }
  else 
  {
    if ((*(char *)(DAT_80025460 + 0x3a) != '\x01') && (*PTR_DAT_80025464 != '\x02'))
    {
      FUN_80025468();

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

        FUN_800267c4();
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
          break;
      }

      if (uVar14 < *(ushort *)(iVar7 + 0x12)) {
        *(undefined *)(iVar21 + 0x1c3) = 1;
        iVar18 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (*(ushort *)(iVar7 + 0x12) - uVar14))) >> 0x20);
        *(int *)(iVar21 + 0x1c4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }
      else {
        *(undefined *)(iVar21 + 0x1c3) = 0;
        iVar18 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (uVar14 - *(ushort *)(iVar7 + 0x12)))) >> 0x20);
        *(int *)(iVar21 + 0x1c4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }
      if (uVar26 < *(ushort *)(iVar7 + 0x12)) {
        *(undefined *)(iVar21 + 0x1d3) = 1;
        iVar18 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (*(ushort *)(iVar7 + 0x12) - uVar26))) >> 0x20);
        *(int *)(iVar21 + 0x1d4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }
      else {
        *(undefined *)(iVar21 + 0x1d3) = 0;
        iVar18 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (uVar26 - *(ushort *)(iVar7 + 0x12)))) >> 0x20);
        *(int *)(iVar21 + 0x1d4) = (iVar18 >> 4) - (iVar18 >> 0x1f);
      }
      uVar32 = FUN_800397d0(unaff_r4);
      FUN_800397d0(iVar12);
      uVar33 = FUN_80036618();
      uVar32 = FUN_80039890((int)uVar33,(int)((ulonglong)uVar33 >> 0x20),(int)uVar32,
                            (int)((ulonglong)uVar32 >> 0x20));
      FUN_800393ec((int)uVar32,(int)((ulonglong)uVar32 >> 0x20),0,DAT_80008590);
      iVar12 = FUN_8003972c();
      *(int *)(iVar21 + 500) = iVar12;
      iVar13 = (int)((ulonglong)((longlong)iVar13 * (longlong)(int)(unaff_r4 * (uVar15 & 0xffff)))
                    >> 0x20);
      iVar13 = (iVar13 >> 4) - (iVar13 >> 0x1f);
      *(int *)(iVar21 + 0x1e4) = iVar13;
      cVar1 = *(char *)(iVar21 + 0x1c3);
      if (cVar1 == *(char *)(iVar21 + 0x1d3)) {
        if (cVar1 != '\0') {
          iVar18 = *(int *)(iVar21 + 0x1d4);
          iVar30 = *(int *)(iVar21 + 0x1c4);
        }
        else {
          iVar18 = *(int *)(iVar21 + 0x1c4);
          iVar30 = *(int *)(iVar21 + 0x1d4);
        }
        iVar18 = iVar18 - iVar30;
        if (cVar1 == '\0') goto LAB_800083f8;
        *(int *)(iVar21 + 0x204) = iVar18;
      }
      else {
        iVar18 = *(int *)(iVar21 + 0x1c4) + *(int *)(iVar21 + 0x1d4);
LAB_800083f8:
        *(int *)(iVar21 + 0x204) = iVar18;
      }
      uVar14 = *(uint *)(iVar21 + 0x1d4);
      uVar26 = *(uint *)(iVar21 + 0x1c4);
      if (uVar26 < uVar14) {
        *(uint *)(iVar21 + 0x214) = uVar14;
      }
      else {
        *(uint *)(iVar21 + 0x214) = uVar26;
      }
      if (*(char *)(iVar7 + 0xe) == '\x01') {
        *(uint *)(iVar21 + 0x1d4) = uVar14 * 10;
        *(int *)(iVar21 + 0x1e4) = iVar13 * 10;
        *(uint *)(iVar21 + 0x1c4) = uVar26 * 10;
        *(int *)(iVar21 + 500) = iVar12 * 10;
        *(int *)(iVar21 + 0x204) = *(int *)(iVar21 + 0x204) * 10;
        iVar13 = *(int *)(iVar21 + 0x214) * 10;
      }
      else {
        if (*(char *)(iVar7 + 0xe) != '\x02') goto LAB_800084c8;
        *(uint *)(iVar21 + 0x1d4) = uVar14 * 100;
        *(uint *)(iVar21 + 0x1c4) = uVar26 * 100;
        *(int *)(iVar21 + 500) = iVar12 * 100;
        *(int *)(iVar21 + 0x1e4) = iVar13 * 100;
        *(int *)(iVar21 + 0x204) = *(int *)(iVar21 + 0x204) * 100;
        iVar13 = *(int *)(iVar21 + 0x214) * 100;
      }
      *(int *)(iVar21 + 0x214) = iVar13;
LAB_800084c8:
      if (*(char *)(iVar7 + 0xf) == '\x06') {
        uVar28 = 0xf;
      }
      else {
        uVar28 = 7;
      }
      if (*(ushort *)(iVar21 + 0xf2) < uVar28) {
        *(undefined4 *)(iVar21 + 0x204) = 0;
      }
      if (0x13 < *(ushort *)(iVar21 + 0xf2)) {
        return;
      }
      *(undefined4 *)(iVar21 + 0x204) = 0;
      if (*(ushort *)(iVar7 + 0x12) + 5 <= (uint)*(ushort *)(iVar21 + 0xf4)) {
        return;
      }
      if (*(ushort *)(iVar21 + 0xf4) + 5 <= (uint)*(ushort *)(iVar7 + 0x12)) {
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
  pcVar9 = DAT_8002b64c;
  puVar8 = PTR_DAT_8002b648;
  cVar1 = *PTR_DAT_8002b648;
  if ((cVar1 == '\x02') && ((DAT_8002b64c[0x21] != '\x01' || (DAT_8002b64c[0x3a] == '\x01')))) {
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
      set_display_color(0);
      display_clear_rect(2,0x2f,uVar28,uVar28 - 0xfb);
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
      set_display_color(DAT_8002b66c);
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
      set_display_color(0);
      display_clear_rect(3,0x81,0x2d5,0xd1);
      FUN_800075dc();
      set_display_color(DAT_8002b670);
      puVar22 = DAT_8002b674;
      uVar14 = 0;
      *DAT_8002b674 = DAT_8002b674[1];
      do {
        puVar17 = puVar22 + uVar14;
        if (0x50 < *puVar17) {
          *puVar17 = 0x50;
        }
        FUN_80018ef4(uVar14 + 3,(0x50 - *puVar17 & 0xffff) + 0x81,0xd1);
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
    set_display_color(0);
    uVar14 = DAT_8002b67c;
    display_clear_rect(2,0x2f,uVar28,(ushort)DAT_8002b67c);
    FUN_80009af4();
    FUN_8000b5cc();
    FUN_8001cccc(2,0x2e,uVar14 + 0xf7,uVar14);
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
  set_display_color(DAT_8002b66c);
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

//------------------------------------------------------------------------------------------------------------------------------------------------

void thunk_FUN_8002b124(void)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined *puVar8;
  ushort uVar9;
  int iVar10;
  ushort *puVar11;
  int iVar12;
  undefined2 *puVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  ushort uVar17;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar18;
  
  pcVar7 = DAT_8002b64c;
  puVar6 = PTR_DAT_8002b648;
  cVar1 = *PTR_DAT_8002b648;
  if ((cVar1 == '\x02') && ((DAT_8002b64c[0x21] != '\x01' || (DAT_8002b64c[0x3a] == '\x01')))) {
    DAT_8002b64c[0x18] = '\x01';
    pcVar7[0x17] = '\x01';
  }
  puVar8 = PTR_DAT_8002b65c;
  iVar5 = DAT_8002b658;
  iVar4 = DAT_8002b654;
  uVar17 = (ushort)DAT_8002b650;
  iVar16 = DAT_8002b654 + 2000;
  if (8 < (byte)pcVar7[10]) {
    if (pcVar7[0x18] != '\0') {
      set_frame_to_global_pointer();
      set_display_color(0);
      display_clear_rect(2,0x2f,uVar17,uVar17 - 0xfb);
      FUN_80009af4();
    }
    if (pcVar7[0x17] == '\0') goto LAB_8002b414;
    FUN_8001b424(pcVar7 + 0x1a,pcVar7 + 0x1c);
    if (*pcVar7 != '\0') {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02')) {
        *(undefined2 *)(puVar8 + 0x12) = 400;
      }
      FUN_8000410c();
      cVar1 = pcVar7[0x21];
      bVar18 = cVar1 != '\0';
      if (bVar18) {
        cVar1 = pcVar7[0x21];
      }
      if (((!bVar18 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) &&
         ((pcVar7[0x23] == '\x01' || (pcVar7[9] != '\0')))) {
        FUN_8000583c();
      }
      if (*(char *)(iVar5 + 7) == '\0') {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b654);
      }
    }
    if (pcVar7[0xc] == '\0') {
LAB_8002b2e8:
      if (*(char *)(iVar5 + 7) != '\0') goto LAB_8002b2f4;
    }
    else {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02')) {
        *(undefined2 *)(puVar8 + 0x14) = 400;
      }
      FUN_80006f28();
      cVar1 = pcVar7[0x21];
      bVar18 = cVar1 != '\0';
      if (bVar18) {
        cVar1 = pcVar7[0x21];
      }
      if (((!bVar18 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) &&
         ((pcVar7[0x23] == '\0' || (pcVar7[0x15] != '\0')))) {
        FUN_80008594();
      }
      if (*(char *)(iVar5 + 7) == '\0') {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b668);
        goto LAB_8002b2e8;
      }
LAB_8002b2f4:
      set_frame_to_global_pointer();
      set_display_color(DAT_8002b66c);
      if (*(ushort *)(pcVar7 + 0x1c) < 2) {
        *(undefined2 *)(pcVar7 + 0x1c) = 2;
      }
      uVar15 = 1;
      if (1 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2)) {
        do {
          puVar11 = (ushort *)(iVar4 + uVar15 * 2);
          puVar13 = (undefined2 *)(iVar16 + uVar15 * 2);
          FUN_80018d30(*puVar11 + 0x96,*puVar13,puVar11[1] + 0x96,puVar13[1]);
          uVar15 = uVar15 + 1 & 0xfffeffff;
        } while ((int)uVar15 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2));
      }
    }
    cVar1 = pcVar7[4];
    bVar18 = cVar1 != '\0';
    if (bVar18) {
      cVar1 = *pcVar7;
    }
    if (bVar18 && cVar1 != '\0') {
      FUN_800043e4();
    }
    cVar1 = pcVar7[0x10];
    bVar18 = cVar1 != '\0';
    if (bVar18) {
      cVar1 = pcVar7[0xc];
    }
    if (bVar18 && cVar1 != '\0') {
      set_display_color(0);
      display_clear_rect(3,0x81,0x2d5,0xd1);
      FUN_800075dc();
      set_display_color(DAT_8002b670);
      puVar13 = DAT_8002b674;
      uVar15 = 0;
      *DAT_8002b674 = DAT_8002b674[1];
      do {
        puVar11 = puVar13 + uVar15;
        if (0x50 < *puVar11) {
          *puVar11 = 0x50;
        }
        FUN_80018ef4(uVar15 + 3,(0x50 - *puVar11 & 0xffff) + 0x81,0xd1);
        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x2d3);
    }
LAB_8002b414:
    iVar4 = DAT_8002b678;
    if (pcVar7[0x18] == '\0') {
      return;
    }
    if (*(char *)(DAT_8002b678 + 0x292) != '\0') {
      FUN_8000eb10();
    }
    if (*(char *)(iVar4 + 0x29a) != '\0') {
      FUN_8000eb84();
    }
    cVar1 = *(char *)(iVar4 + 0x292);
    bVar18 = cVar1 == '\0';
    if (bVar18) {
      cVar1 = *(char *)(iVar4 + 0x29a);
    }
    if (!bVar18 || cVar1 != '\0') {
      FUN_8000ebf8();
    }
    FUN_8000b5cc();
    FUN_80021810();
    uVar15 = DAT_8002b67c;
    iVar5 = Start_Of_Screen_Mem;
    iVar4 = Screen_Frame_Buffer;
    uVar14 = 0x2e;
    iVar16 = DAT_8002b67c + 0xf6;
    if (DAT_8002b67c < 0x2f) {
      return;
    }
    do {
      iVar10 = uVar14 * 800 + 2;
      copy_short((void *)(iVar5 + iVar10 * 2),(void *)(iVar4 + iVar10 * 2),iVar16);
      uVar14 = uVar14 + 1;
    } while (uVar14 < uVar15);
    return;
  }
  uVar9 = (ushort)(byte)pcVar7[0x3a];
  if (uVar9 != 0) {
                    // WARNING: Could not recover jumptable at 0x8002b490. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (cVar1 != '\x02') {
    uVar9 = *(ushort *)PTR_DAT_8002b65c;
  }
  else {
    *(undefined2 *)PTR_DAT_8002b65c = 0;
  }
  if (cVar1 == '\x02' || uVar9 == 0) {
    set_frame_to_global_pointer();
    set_display_color(0);
    uVar15 = DAT_8002b67c;
    display_clear_rect(2,0x2f,uVar17,(ushort)DAT_8002b67c);
    FUN_80009af4();
    FUN_8000b5cc();
    FUN_8001cccc(2,0x2e,uVar15 + 0xf7,uVar15);
    set_screen_to_global_pointer();
  }
  iVar10 = DAT_8002b680;
  if (*pcVar7 != '\0') {
    set_screen_to_global_pointer();
    iVar12 = iVar10 - (uint)*DAT_8002b684;
    *(short *)(puVar8 + 0x16) = (short)iVar12;
    iVar12 = iVar12 * 0x10000 >> 0x10;
    if (iVar12 < 0x2f) {
      iVar12 = 0x2f;
    }
    else {
      if (0x1c0 < iVar12) {
        iVar12 = 0x1c0;
      }
    }
    *(short *)(puVar8 + 0x16) = (short)iVar12;
    if (*(char *)(iVar5 + 7) == '\0') {
      FUN_800067ac();
    }
  }
  if (pcVar7[0xc] == '\0') {
LAB_8002b590:
    if (*(char *)(iVar5 + 7) == '\0') goto LAB_8002b624;
  }
  else {
    set_screen_to_global_pointer();
    iVar10 = iVar10 - (uint)*DAT_8002b688;
    *(short *)(puVar8 + 0x18) = (short)iVar10;
    iVar10 = iVar10 * 0x10000 >> 0x10;
    if (iVar10 < 0x2f) {
      iVar10 = 0x2f;
    }
    else {
      if (0x1c0 < iVar10) {
        iVar10 = 0x1c0;
      }
    }
    *(short *)(puVar8 + 0x18) = (short)iVar10;
    if (*(char *)(iVar5 + 7) == '\0') {
      FUN_800094f8();
      goto LAB_8002b590;
    }
  }
  if (*(short *)puVar8 == 0) {
    *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);
    *(undefined2 *)(puVar8 + 4) = *(undefined2 *)(puVar8 + 0x18);
  }
  set_display_color(DAT_8002b66c);
  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x96,*(undefined2 *)(puVar8 + 4),
               *(ushort *)(puVar8 + 0x16) + 0x96,*(undefined2 *)(puVar8 + 0x18));
  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x97,*(ushort *)(puVar8 + 4) + 1,
               *(ushort *)(puVar8 + 0x16) + 0x97,*(ushort *)(puVar8 + 0x18) + 1);
  *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);
  uVar2 = *(undefined2 *)(puVar8 + 0x18);
  *(undefined2 *)(puVar8 + 4) = uVar2;
  uVar17 = *(ushort *)puVar8;
  *(undefined2 *)(iVar4 + (uint)uVar17 * 2) = *(undefined2 *)(puVar8 + 0x16);
  *(undefined2 *)(iVar16 + (uint)uVar17 * 2) = uVar2;
LAB_8002b624:
  sVar3 = *(short *)puVar8;
  *(ushort *)puVar8 = sVar3 + 1U;
  if (0x2cf < (ushort)(sVar3 + 1U)) {
    *(undefined2 *)puVar8 = 0;
  }
                    // WARNING: Could not recover jumptable at 0x8002b644. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------


void FUN_8001a3b4(void)

{
  char cVar1;
  ushort uVar2;
  ushort uVar3;
  uint *ptr;
  undefined *puVar4;
  undefined *puVar5;
  short sVar6;
  undefined2 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint unaff_r4;
  int iVar11;
  code *UNRECOVERED_JUMPTABLE;
  bool bVar12;
  
  iVar8 = DAT_8001a5b8;
  puVar4 = PTR_DAT_8001a5b4;
  if (*PTR_DAT_8001a5b4 == '\0') {
    FUN_8001b674();
    iVar9 = DAT_8001a5c8;
    if (*puVar4 != '\x02') goto LAB_8001a410;
    *(undefined2 *)(puVar4 + 0xe) = *(undefined2 *)PTR_DAT_8001a5c4;
    *(undefined2 *)(puVar4 + 0x10) = *(undefined2 *)PTR_DAT_8001a5cc;
    *(undefined2 *)(puVar4 + 0x12) = *(undefined2 *)(iVar8 + 6);
    *(undefined2 *)(puVar4 + 0x14) = *(undefined2 *)(iVar8 + 0x12);
    *(undefined2 *)(puVar4 + 10) = *(undefined2 *)(iVar8 + 0x24);
    *(undefined2 *)(puVar4 + 0xc) = *(undefined2 *)(iVar8 + 0x26);
    *(undefined2 *)(puVar4 + 0x16) = *(undefined2 *)(iVar9 + 0x94);
    *(undefined2 *)(puVar4 + 0x18) = *(undefined2 *)(iVar9 + 0x96);
    *(undefined2 *)(puVar4 + 0x1a) = *(undefined2 *)(iVar9 + 0x9c);
    *(undefined2 *)(puVar4 + 0x1c) = *(undefined2 *)(iVar9 + 0x9e);
    if (*(char *)(iVar8 + 0x3a) == '\0') {
      *(undefined2 *)(puVar4 + 0xe) = 400;
    }
  }
  else {
    tp_i2c_read_status();
    puVar5 = PTR_DAT_8001a5bc;
    if (*PTR_DAT_8001a5bc == '\0') {
      *puVar4 = 0;
      puVar4[1] = 0;
      return;
    }
    *(undefined2 *)(puVar4 + 0x2e) = *(undefined2 *)(PTR_DAT_8001a5bc + 2);
    *(undefined2 *)(puVar4 + 0x30) = *(undefined2 *)(puVar5 + 4);
LAB_8001a410:
    if (*puVar4 == '\x01') {
      if ((10 < *(byte *)(iVar8 + 0xb)) || (*(char *)(iVar8 + 0x3a) == '\0')) {
        FUN_8001ac54();
      }
      *puVar4 = 0;
      return;
    }
    if (*puVar4 != '\x02') {
      return;
    }
  }
  if (*(char *)(DAT_8001a5c0 + 7) == '\0') {
    cVar1 = puVar4[1];
    if (cVar1 == '\x04') {
      FUN_8001a9c0();
    }
    else {
      if (cVar1 == '\x05') {
        FUN_8001a860();
      }
      else {
        if (cVar1 == '\x06') {
          FUN_8001aa6c();
        }
        else {
          if (cVar1 == '\a') {
            FUN_8001a910();
          }
        }
      }
    }
    iVar9 = DAT_8001a754;
    if (10 < *(byte *)(iVar8 + 10)) {
      if (puVar4[1] == '\0') {
        FUN_8001ab18();
      }
      cVar1 = puVar4[1];
      if (cVar1 != '\x01') {
        if (cVar1 == '\x02') {
          FUN_8001ab18();
          FUN_8001a5d0();
          if (*(char *)(iVar8 + 0x23) != '\0') {
            return;
          }
        }
        else {
          if (cVar1 != '\x03') {
            return;
          }
          FUN_8001ab18();
          FUN_8001a764();
          if (*(char *)(iVar8 + 0x23) != '\x01') {
            return;
          }
        }
      }
      iVar11 = 1;
      iVar9 = FUN_80017790();
      puVar4 = PTR_DAT_8001ac50;
      iVar8 = DAT_8001ac4c;
      if (iVar9 != 0) {
        return;
      }
      uVar2 = *(ushort *)(PTR_DAT_8001ac50 + 0x30);
      uVar3 = *(ushort *)(PTR_DAT_8001ac50 + 0x34);
      if (*(char *)(DAT_8001ac4c + 0x16) != '\0') {
        iVar11 = 5;
      }
      if (uVar2 < uVar3) {
        iVar9 = divide((uint)(ushort)(uVar3 - uVar2),iVar11);
        uVar10 = iVar9 + (uint)*(ushort *)(puVar4 + 0xc);
        bVar12 = 0x18b < uVar10;
        if (bVar12) {
          uVar10 = 0x18c;
        }
        uVar7 = (undefined2)uVar10;
        if (bVar12) {
          *(undefined2 *)(iVar8 + 0x26) = uVar7;
          return;
        }
      }
      else {
        iVar9 = divide((uint)(ushort)(uVar2 - uVar3),iVar11);
        uVar10 = (uint)*(ushort *)(puVar4 + 0xc);
        bVar12 = iVar9 + 6U < uVar10;
        if (bVar12) {
          iVar9 = uVar10 - iVar9;
        }
        uVar7 = (undefined2)iVar9;
        if (!bVar12) {
          uVar7 = 6;
        }
      }
      *(undefined2 *)(iVar8 + 0x26) = uVar7;
      return;
    }
    if ((*(char *)(iVar8 + 0x3a) != '\0') && (*(byte *)(iVar8 + 10) < 9)) {
      return;
    }
    if (puVar4[1] == '\x02') {
      iVar8 = 1;
      if (*(char *)(DAT_8001a754 + 0x16) != '\0') {
        iVar8 = 5;
      }
      iVar11 = FUN_80017790();
      puVar5 = PTR_DAT_8001a760;
      puVar4 = PTR_DAT_8001a75c;
      if (iVar11 != 0) {
        return;
      }
      if (*(char *)(DAT_8001a758 + 7) == '\0') {
        uVar2 = *(ushort *)(PTR_DAT_8001a760 + 0x30);
        uVar3 = *(ushort *)(PTR_DAT_8001a760 + 0x34);
        if (uVar3 <= uVar2) {
          iVar8 = divide((uint)(ushort)(uVar2 - uVar3),iVar8);
          uVar10 = (uint)*(ushort *)(puVar5 + 0x12);
          if (iVar8 + 7U < uVar10) {
            *(ushort *)(iVar9 + 6) = *(ushort *)(puVar5 + 0x12) - (short)iVar8;
          }
          else {
            *(undefined2 *)(iVar9 + 6) = 7;
          }
          goto joined_r0x8001a6a4;
        }
        iVar8 = divide((uint)(ushort)(uVar3 - uVar2),iVar8);
        uVar10 = (uint)*(ushort *)(puVar5 + 0x12);
        if (iVar8 + uVar10 < 0x18b) {
          *(short *)(iVar9 + 6) = (short)(iVar8 + uVar10);
        }
        else {
          *(undefined2 *)(iVar9 + 6) = 0x18b;
        }
joined_r0x8001a6f0:
        if (0x18b < uVar10) {
          *(undefined2 *)(puVar5 + 0x12) = 0x18b;
        }
        uVar2 = *(ushort *)(puVar5 + 0xe);
        sVar6 = (*(short *)(iVar9 + 6) - *(short *)(puVar5 + 0x12)) + uVar2;
      }
      else {
        uVar2 = *(ushort *)(PTR_DAT_8001a760 + 0x2e);
        uVar3 = *(ushort *)(PTR_DAT_8001a760 + 0x32);
        if (uVar2 < uVar3) {
          iVar8 = divide((uint)(ushort)(uVar3 - uVar2),iVar8);
          uVar10 = (uint)*(ushort *)(puVar5 + 0x12);
          if (iVar8 + uVar10 < 0x18b) {
            *(short *)(iVar9 + 6) = (short)(iVar8 + uVar10);
          }
          else {
            *(undefined2 *)(iVar9 + 6) = 0x18b;
          }
          goto joined_r0x8001a6f0;
        }
        iVar8 = divide((uint)(ushort)(uVar2 - uVar3),iVar8);
        uVar10 = (uint)*(ushort *)(puVar5 + 0x12);
        if (iVar8 + 7U < uVar10) {
          *(ushort *)(iVar9 + 6) = *(ushort *)(puVar5 + 0x12) - (short)iVar8;
        }
        else {
          *(undefined2 *)(iVar9 + 6) = 7;
        }
joined_r0x8001a6a4:
        if (uVar10 < 7) {
          *(undefined2 *)(puVar5 + 0x12) = 7;
        }
        uVar2 = *(ushort *)(puVar5 + 0xe);
        sVar6 = uVar2 - (*(short *)(puVar5 + 0x12) - *(short *)(iVar9 + 6));
      }
      uVar10 = (uint)uVar2;
      *(short *)puVar4 = sVar6;
      switch(*(undefined *)(DAT_80006a84 + 3)) {
      case 0:
        unaff_r4 = (uint)DAT_80006a88[1];
        break;
      case 1:
        unaff_r4 = (uint)DAT_80006a88[2];
        break;
      case 2:
        unaff_r4 = (uint)DAT_80006a88[3];
        break;
      case 3:
        unaff_r4 = (uint)DAT_80006a88[4];
        break;
      case 4:
        unaff_r4 = (uint)DAT_80006a88[5];
        break;
      case 5:
      case 6:
        unaff_r4 = (uint)DAT_80006a88[6];
      }
      switch(*(undefined *)(DAT_80006a84 + 3)) {
      case 0:
        uVar10 = (uint)*DAT_80006a8c;
        break;
      case 1:
        uVar10 = (uint)DAT_80006a8c[1];
        break;
      case 2:
        uVar10 = (uint)DAT_80006a8c[2];
        break;
      case 3:
        uVar10 = (uint)DAT_80006a8c[3];
        break;
      case 4:
        uVar10 = (uint)DAT_80006a8c[4];
        break;
      case 5:
        uVar10 = (uint)DAT_80006a8c[5];
        break;
      case 6:
        uVar10 = (uint)DAT_80006a8c[6];
      }
      iVar8 = (int)((ulonglong)
                    ((longlong)DAT_80006a90 *
                    (longlong)(int)((uint)*(ushort *)(DAT_80006a84 + 6) * (uint)*DAT_80006a88)) >>
                   0x20);
      iVar8 = divide_2((uint)*DAT_80006a8c * ((iVar8 >> 5) - (iVar8 >> 0x1f)),uVar10);
      uVar10 = unaff_r4 - iVar8 & 0xffff;
      fpga_write_cmd('2');
      fpga_write_data((uchar)(uVar10 >> 8));
      goto code_r0x800168fc;
    }
    if (puVar4[1] != '\x03') {
      return;
    }
  }
  else {
    FUN_8001a5d0();
  }
  iVar11 = 1;
  iVar9 = FUN_80017790();
  puVar5 = PTR_DAT_8001a858;
  puVar4 = PTR_DAT_8001a854;
  iVar8 = DAT_8001a850;
  if (iVar9 != 0) {
                    // WARNING: Could not recover jumptable at 0x8001a77c. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  uVar2 = *(ushort *)(PTR_DAT_8001a854 + 0x30);
  uVar3 = *(ushort *)(PTR_DAT_8001a854 + 0x34);
  if (*(char *)(DAT_8001a850 + 0x16) != '\0') {
    iVar11 = 5;
  }
  if (uVar2 < uVar3) {
    iVar9 = divide((uint)(ushort)(uVar3 - uVar2),iVar11);
    uVar2 = *(ushort *)(puVar4 + 0x14);
    uVar10 = iVar9 + (uint)uVar2;
    uVar7 = (undefined2)DAT_8001a85c;
    if (uVar10 < DAT_8001a85c) {
      *(short *)(iVar8 + 0x12) = (short)uVar10;
    }
    else {
      *(undefined2 *)(iVar8 + 0x12) = uVar7;
    }
    if (0x18b < uVar2) {
      *(undefined2 *)(puVar4 + 0x14) = uVar7;
    }
    uVar2 = *(ushort *)(puVar4 + 0x10);
    sVar6 = (*(short *)(iVar8 + 0x12) - *(short *)(puVar4 + 0x14)) + uVar2;
  }
  else {
    iVar9 = divide((uint)(ushort)(uVar2 - uVar3),iVar11);
    uVar2 = *(ushort *)(puVar4 + 0x14);
    if (iVar9 + 7U < (uint)uVar2) {
      *(ushort *)(iVar8 + 0x12) = uVar2 - (short)iVar9;
    }
    else {
      *(undefined2 *)(iVar8 + 0x12) = 7;
    }
    if (uVar2 < 7) {
      *(undefined2 *)(puVar4 + 0x14) = 7;
    }
    uVar2 = *(ushort *)(puVar4 + 0x10);
    sVar6 = uVar2 - (*(short *)(puVar4 + 0x14) - *(short *)(iVar8 + 0x12));
  }
  uVar10 = (uint)uVar2;
  *(short *)puVar5 = sVar6;
  switch(*(undefined *)(DAT_800097d0 + 0xf)) {
  case 0:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x10);
    break;
  case 1:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x12);
    break;
  case 2:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x14);
    break;
  case 3:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x16);
    break;
  case 4:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x18);
    break;
  case 5:
  case 6:
    unaff_r4 = (uint)*(ushort *)(DAT_800097d4 + 0x1a);
  }
  switch(*(undefined *)(DAT_800097d0 + 0xf)) {
  case 0:
    uVar10 = (uint)*DAT_800097d8;
    break;
  case 1:
    uVar10 = (uint)DAT_800097d8[1];
    break;
  case 2:
    uVar10 = (uint)DAT_800097d8[2];
    break;
  case 3:
    uVar10 = (uint)DAT_800097d8[3];
    break;
  case 4:
    uVar10 = (uint)DAT_800097d8[4];
    break;
  case 5:
    uVar10 = (uint)DAT_800097d8[5];
    break;
  case 6:
    uVar10 = (uint)DAT_800097d8[6];
  }
  iVar8 = (int)((ulonglong)
                ((longlong)DAT_800097dc *
                (longlong)
                (int)((uint)*(ushort *)(DAT_800097d0 + 0x12) * (uint)*(ushort *)(DAT_800097d4 + 0xe)
                     )) >> 0x20);
  iVar8 = divide_2((uint)*DAT_800097d8 * ((iVar8 >> 5) - (iVar8 >> 0x1f)),uVar10);
  uVar10 = unaff_r4 - iVar8 & 0xffff;
  fpga_write_cmd('5');
  fpga_write_data((uchar)(uVar10 >> 8));
code_r0x800168fc:
  ptr = PE_CFG0;
  gpio_config_pin(PE_CFG0,0,1);
  gpio_config_pin(ptr,1,1);
  gpio_config_pin(ptr,2,1);
  gpio_config_pin(ptr,3,1);
  gpio_config_pin(ptr,4,1);
  gpio_config_pin(ptr,5,1);
  gpio_config_pin(ptr,6,1);
  gpio_config_pin(ptr,7,1);
  set_gpio_pin_high(ptr,9);
  set_gpio_pin_low(ptr,10);
  ptr[4] = uVar10 & 0xff | ptr[4] & 0xffffff00;
  set_gpio_pin_low(ptr,8);
  ptr[4] = ptr[4] | 0x100;
  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------
//Read setting 0x11

uint FUN_8001bec4(void)
{
  byte bVar1;
  byte bVar2;
  uint uVar3;
  
  fpga_write_cmd('\x14');
  bVar1 = fpga_read_data();
  bVar2 = fpga_read_data();
  uVar3 = get_setting(0x11, bVar1 & 0xf | (bVar1 & 0xf) << 0xc | (uint)bVar2 << 4);
  return uVar3;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

