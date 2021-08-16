
//process_channel1_trigger

FUN_8000583c(void)

{
  short sVar1;
  ushort uVar2;
  bool bVar3;
  undefined *puVar4;
  void *pvVar5;
  uint uVar6;
  undefined2 uVar7;
  void *pvVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  uint unaff_r5;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar13;
  bool bVar14;
  
  puVar4 = PTR_DAT_80006024;
  iVar12 = DAT_80006020;
  bVar3 = false;

  if (*(ushort *)(DAT_8000601c + 0xe8) < 0xf)
  {
    return;
  }

  if (*(char *)(DAT_80006020 + 10) == '\x1b')
  {
    unaff_r5 = 10;
  }

  if (*(char *)(DAT_80006020 + 10) == '\x1c')
  {
    unaff_r5 = 0xf;
  }

  sVar1 = *(short *)(PTR_DAT_80006024 + 0x20);

  if (0x1c < *(byte *)(DAT_80006020 + 10))
  {
    unaff_r5 = 0x1e;
  }

  pvVar8 = DAT_80006030;

  if ((((sVar1 != 0) && (pvVar8 = DAT_80006034, sVar1 != 1)) && (pvVar8 = DAT_80006038, sVar1 != 2)) && (pvVar8 = DAT_8000603c, sVar1 != 3))
  {
    if (sVar1 == 4)
    {
      pvVar8 = (void *)((int)DAT_8000602c + 32000);
    }
    else
    {
      pvVar8 = DAT_80006040;
      if (((((sVar1 != 5) && (pvVar8 = DAT_80006044, sVar1 != 6)) &&
           ((pvVar8 = DAT_80006048, sVar1 != 7 &&
            ((pvVar8 = DAT_8000604c, sVar1 != 8 && (pvVar8 = DAT_80006050, sVar1 != 9)))))) &&
          ((pvVar8 = DAT_80006054, sVar1 != 10 &&
           ((((pvVar8 = DAT_80006058, sVar1 != 0xb && (pvVar8 = DAT_8000605c, sVar1 != 0xc)) &&
             (pvVar8 = DAT_80006060, sVar1 != 0xd)) &&
            ((pvVar8 = DAT_80006064, sVar1 != 0xe && (pvVar8 = DAT_80006068, sVar1 != 0xf)))))))) &&
         (((pvVar8 = DAT_8000606c, sVar1 != 0x10 &&
           ((pvVar8 = DAT_80006070, sVar1 != 0x11 && (pvVar8 = DAT_80006074, sVar1 != 0x12)))) &&
          (pvVar8 = DAT_80006078, sVar1 != 0x13))))
      {
        if (sVar1 == 0x14)
        {
          pvVar8 = (void *)((int)DAT_8000602c + 64000);
        }
        else
        {
          pvVar8 = DAT_8000607c;

          if ((((sVar1 != 0x15) && (pvVar8 = DAT_80006080, sVar1 != 0x16)) &&
              (pvVar8 = DAT_80006084, sVar1 != 0x17)) &&
             ((((pvVar8 = DAT_80006088, sVar1 != 0x18 && (pvVar8 = DAT_8000608c, sVar1 != 0x19)) &&
               ((pvVar8 = DAT_80006090, sVar1 != 0x1a &&
                ((pvVar8 = DAT_80006094, sVar1 != 0x1b && (pvVar8 = DAT_80006098, sVar1 != 0x1c)))))
               ) && (pvVar8 = DAT_8000609c, sVar1 != 0x1d))))
           goto LAB_80005a78;
        }
      }
    }
  }

  memcpy(pvVar8,DAT_8000602c,DAT_80006028);

LAB_80005a78:
  uVar6 = DAT_800060a0;
  uVar9 = *(ushort *)(PTR_DAT_80006024 + 0x20) + 1 & 0xfffeffff;
  uVar7 = (undefined2)uVar9;

  if (*(char *)(iVar12 + 0x23) == '\x01')
  {
    uVar9 = (uint)*(ushort *)(iVar12 + 0x2e);
    bVar14 = DAT_800060a0 <= uVar9;
    bVar13 = uVar9 == DAT_800060a0;

    if (bVar14 && !bVar13)
    {
      uVar9 = (uint)*(ushort *)(iVar12 + 0x32);
    }

    if (bVar14 && !bVar13)
    {
      bVar14 = DAT_800060a0 <= uVar9;
      bVar13 = uVar9 == DAT_800060a0;
    }

    if (bVar14 && !bVar13)
    {
      uVar11 = (uint)*(ushort *)(puVar4 + 10);
      uVar2 = *(ushort *)(PTR_DAT_80006024 + 0xe);
      uVar9 = (uint)uVar2;

      if (((((int)(uVar11 - 10) < (int)(uint)*(ushort *)(iVar12 + 0x2e)) &&
           ((uint)*(ushort *)(iVar12 + 0x2e) < uVar11 + 10)) ||
          (((int)(uVar11 - 10) < (int)(uint)*(ushort *)(iVar12 + 0x32) &&
           ((uint)*(ushort *)(iVar12 + 0x32) < uVar11 + 10)))) ||
         ((iVar10 = uVar11 - ((uint)*(ushort *)(iVar12 + 0x32) - (uint)*(ushort *)(iVar12 + 0x2e) &
                             0xffff), iVar10 + -10 < (int)(uint)*(ushort *)(iVar12 + 0x2e) &&
          ((int)(uint)*(ushort *)(iVar12 + 0x2e) < iVar10 + 10))))
      {
        if (uVar9 < unaff_r5)
        {
          *(ushort *)(puVar4 + 0xe) = uVar2 + 1;
        }

        bVar3 = uVar9 >= unaff_r5;
        *(undefined2 *)(puVar4 + 0x20) = uVar7;
      }
      else
      {
        *(undefined2 *)(puVar4 + 10) = *(undefined2 *)(iVar12 + 0x2e);
        if (uVar9 != 0)
        {
          *(ushort *)(puVar4 + 0xe) = uVar2 - 1;
        }
      }
    }
    if (unaff_r5 <= *(ushort *)(puVar4 + 0x20)) {
      *(undefined2 *)(puVar4 + 0x20) = 0;
    }
    if (!bVar3)
    {
      return;
    }
  }
  else
  {
    *(undefined2 *)(puVar4 + 0x20) = uVar7;

    if (unaff_r5 <= uVar9)
    {
      *(undefined2 *)(puVar4 + 0x20) = 0;
    }
  }

  pvVar8 = DAT_80006040;

  if (*(char *)(DAT_80006020 + 10) == '\x1b')
  {
    iVar12 = 0;

    do
    {
      uVar9 = divide((uint)*(ushort *)((int)DAT_80006030 + iVar12 * 2) +
                     (uint)*(ushort *)((int)pvVar8 + iVar12 * 2 + 6000) +
                     (uint)*(ushort *)((int)pvVar8 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)pvVar8 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 6000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 4000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)DAT_80006048 + iVar12 * 2) +
                     (uint)*(ushort *)((int)pvVar8 + iVar12 * 2 + 8000),unaff_r5);

      uVar9 = uVar9 & 0xffff;
      uVar7 = (undefined2)uVar9;

      if (uVar9 < 0x2f)
      {
        uVar7 = 0x2f;
      }
      else
      {
        if (0x1c0 < uVar9)
        {
          uVar7 = 0x1c0;
        }
      }

      iVar10 = iVar12 * 2;
      iVar12 = iVar12 + 1;
      *(undefined2 *)((int)DAT_8000602c + iVar10) = uVar7;

    } while (iVar12 < (int)uVar6);
  }

  if (*(char *)(DAT_80006020 + 10) == '\x1c')
  {
    iVar12 = 0;

    do
    {
      uVar9 = divide((uint)*(ushort *)((int)DAT_80006064 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 6000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 4000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 8000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 10000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 12000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 14000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 16000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 18000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2 + 20000) +
                     (uint)*(ushort *)((int)DAT_8000605c + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006060 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006030 + iVar12 * 2),unaff_r5);

      uVar9 = uVar9 & 0xffff;
      uVar7 = (undefined2)uVar9;

      if (uVar9 < 0x2f)
      {
        uVar7 = 0x2f;
      }
      else
      {
        if (0x1c0 < uVar9)
        {
          uVar7 = 0x1c0;
        }
      }

      iVar10 = iVar12 * 2;
      iVar12 = iVar12 + 1;
      *(undefined2 *)((int)DAT_8000602c + iVar10) = uVar7;

    } while (iVar12 < (int)uVar6);
  }

  pvVar5 = DAT_80006050;
  pvVar8 = DAT_80006038;

  if (*(char *)(DAT_80006020 + 10) != '\x1d')
  {
    return;
  }

  iVar12 = 0;

  do
  {
    uVar9 = divide_2((uint)*(ushort *)((int)DAT_8000606c + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006060 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)DAT_80006040 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)DAT_80006034 + iVar12 * 2) +
                     (uint)*(ushort *)((int)pvVar8 + iVar12 * 2) +
                     (uint)*(ushort *)((int)pvVar8 + iVar12 * 2 + 4000) +
                     (uint)*(ushort *)((int)pvVar8 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)DAT_80006040 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006048 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006048 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)pvVar5 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006054 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006058 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006058 + iVar12 * 2 + 2000) +
                     (uint)*(ushort *)((int)DAT_80006060 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006068 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006070 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006074 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006078 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006030 + iVar12 * 2) +
                     (uint)*(ushort *)(DAT_800060a4 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_8000607c + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006080 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006084 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006088 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_8000608c + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006090 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006094 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_80006098 + iVar12 * 2) +
                     (uint)*(ushort *)((int)DAT_8000609c + iVar12 * 2),unaff_r5);

    uVar9 = uVar9 & 0xffff;
    uVar7 = (undefined2)uVar9;

    if (uVar9 < 0x2f)
    {
      uVar7 = 0x2f;
    }
    else
    {
      if (0x1c0 < uVar9)
      {
        uVar7 = 0x1c0;
      }
    }

    iVar10 = iVar12 * 2;
    iVar12 = iVar12 + 1;
    *(undefined2 *)((int)DAT_8000602c + iVar10) = uVar7;

  } while (iVar12 < (int)uVar6);

  return;
}

