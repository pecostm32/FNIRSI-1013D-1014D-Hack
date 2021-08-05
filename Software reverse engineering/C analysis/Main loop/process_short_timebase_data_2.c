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
    puVar16 = DAT_8000b29c;
    puVar18 = (uint *)0x0;

    //read the data
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

    if (pcVar2[0x23] == '\x01')    //Trigger on channel 2?
    {
      local_30 = FUN_800291e0();
    }

    if (pcVar2[10] == '\x19')
    {
      FUN_8001363c(DAT_8000b29c,0,puVar12);
    }

    if (pcVar2[10] == '\x1a')
    {
      FUN_800141c8(DAT_8000b29c,0,puVar12);
    }

    if (pcVar2[10] == '\x1b')
    {
      FUN_800130c4(DAT_8000b29c,0,puVar12);
    }

    if ((DAT_8000b264[10] == '\x1c') || (DAT_8000b264[10] == '\x1d'))
    {
      fpga_write_cmd('\x1f');
      fpga_write_data(data);
      fpga_write_data(data_00);

      puVar22 = puVar6;

      if ((byte)DAT_8000b264[10] < 0xb)
      {
        puVar22 = puVar15;
      }

      fpga_write_cmd('#');   //0x23

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

    if (((byte)DAT_8000b264[10] < 0x19) && (puVar22 = puVar6, (byte)DAT_8000b264[10] < 9))
    {
      puVar22 = puVar15;
    }

    //Translate based on channel 2 volts per div
    uVar14 = translate_parameter(0xb,(uint)(byte)DAT_8000b264[0xf]);

    uVar13 = DAT_8000b288;
    puVar16 = DAT_8000b29c;
    puVar17 = DAT_8000b2a4;
    puVar4 = DAT_8000b2a4;
    puVar5 = DAT_8000b2a8;

    while (DAT_8000b2a4 = puVar4, DAT_8000b2a8 = puVar5, puVar22 != (uint *)0x0)
    {
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
      puVar4 = DAT_8000b2a4;
      puVar5 = DAT_8000b2a8;
    }

    puVar22 = puVar12;

    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar6, (byte)pcVar2[10] < 9))
    {
      puVar22 = puVar15;
    }

    puVar16 = puVar4 + -1;
    puVar17 = puVar5 + -1;

    if (((uint)puVar22 & 1) == 0)
    {
      *puVar5 = *puVar4;
      puVar16 = puVar4;
      puVar17 = puVar5;
    }

    uVar11 = puVar16[1];
    iVar19 = (int)puVar22 + -1 >> 1;

    while (iVar19 != 0)
    {
      uVar1 = puVar16[2];
      puVar17[1] = uVar11;
      uVar11 = puVar16[3];
      iVar19 = iVar19 + -1;
      puVar17 = puVar17 + 2;
      *puVar17 = uVar1;
      puVar16 = puVar16 + 2;
    }

    iVar19 = (int)puVar22 + -1;

    if (-1 < iVar19)
    {
      puVar5[iVar19] = puVar4[iVar19];
    }

    puVar22 = puVar12;

    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar15, 8 < (byte)pcVar2[10]))
    {
      puVar22 = puVar6;
    }

    puVar16 = DAT_8000b2a8;
    uVar13 = DAT_8000b294;

    if ((pcVar2[0xf] == '\x06') && (puVar22 != (uint *)0x0))
    {
      puVar16 = puVar5 + -1;

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

      puVar15 = (uint *)0x0;
      puVar16 = DAT_8000b2a8;
      uVar13 = DAT_8000b294;

      if (puVar22 != (uint *)0x0)
      {
        do
        {
          puVar16 = puVar5 + (int)puVar15;

          if (*puVar16 < *(ushort *)(pcVar2 + 0x12))
          {
            *puVar16 = 0;
          }
          else
          {
            *puVar16 = *puVar16 - *(short *)(pcVar2 + 0x12);
          }

          puVar15 = (uint *)((uint)((int)puVar15 + 1) & 0xfffeffff);
          puVar16 = DAT_8000b2a8;
          uVar13 = DAT_8000b294;
        } while (puVar15 < puVar22);
      }
    }

    do
    {
      if (uVar13 < *puVar16)
      {
        *puVar16 = (ushort)uVar13;
      }

      puVar12 = (uint *)((int)puVar12 + -1);
      puVar16 = puVar16 + 1;
    } while (puVar12 != (uint *)0x0);

    puVar16 = DAT_8000b2a8;
    iVar19 = DAT_8000b298;

    if ((byte)pcVar2[10] < 0x19)   //Timebase
    {
      do
      {
        uVar14 = (uint)*puVar16;
        uVar13 = (uint)puVar16[1];
        uVar20 = (uint)puVar16[2];
        uVar25 = uVar14 + 6;
        bVar27 = uVar25 <= uVar13;
        bVar26 = uVar13 == uVar25;

        if (bVar27 && !bVar26)
        {
          uVar25 = uVar20 + 6;
        }

        if (bVar27 && !bVar26)
        {
          bVar27 = uVar25 <= uVar13;
          bVar26 = uVar13 == uVar25;
        }

        if (bVar27 && !bVar26)
        {
          puVar16[1] = (ushort)(uVar14 + uVar20 >> 1);
        }

        if (uVar13 + 6 < uVar14 && uVar13 + 6 < uVar20)
        {
          puVar16[1] = (ushort)(uVar14 + uVar20 >> 1);
        }

        iVar19 = iVar19 + -1;
        puVar16 = puVar16 + 1;
      } while (iVar19 != 0);
    }

    FUN_80007714();
    FUN_800093ac();

    if (pcVar2[0x48] == '\0')
    {
      FUN_80006ce8();
    }
  }


  pcVar2 = DAT_8000b264;

  if (0x18 < (byte)DAT_8000b264[10])
  {
    if (DAT_8000b264[0x23] == '\0') {
      if (*DAT_8000b264 != '\0') {
        FUN_80006a94(*(undefined2 *)(DAT_8000b264 + 0x26));
        FUN_80005080();
      }
      if (pcVar2[0xc] != '\0') {
        FUN_80008fac();
        FUN_80007df4();
      }
    }
    else {
      if (DAT_8000b264[0xc] != '\0') {
        FUN_800097e0(*(undefined2 *)(DAT_8000b264 + 0x26));
        FUN_80007df4();
      }
      if (*pcVar2 != '\0') {
        FUN_80006250();
        FUN_80005080();
      }
    }
  }

