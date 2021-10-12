
void scope_up_sample_x_25(uint16 *buffer,uint offset,uint count)
{
  ushort uVar1;
  longlong lVar2;
  longlong lVar3;
  uint16 *puVar4;
  uint uVar5;
  ushort *puVar6;
  ushort *puVar7;
  undefined2 *puVar8;
  ushort uVar9;
  int iVar10;
  short *psVar11;
  int iVar12;
  ushort uVar13;
  short sVar14;
  uint uVar15;
  uint uVar16;
  int iVar17;
  uint16 *puVar18;
  uint uVar19;
  undefined2 *puVar20;
  
  puVar7 = (ushort *)(count * DAT_80013e70 + 0xa3d7 >> 0x14);  //((count * 0x0000A3D7) + 0xa3d7) >> 0x14  ==> / 25

  if (puVar7 != NULL)
  {
    puVar4 = (uint16 *)((int)buffer + offset * 2);
    puVar8 = DAT_80013e74;
    puVar18 = (uint16 *)((int)puVar4 + -2);

    if (((uint)puVar7 & 1) != 0)
    {
      puVar8 = DAT_80013e74 + 0x19;
      *puVar8 = *(undefined2 *)puVar4;
      puVar18 = puVar4;
    }

    uVar16 = (uint)((int)puVar7 << 0xf) >> 0x10;

    while (uVar16 != 0)
    {
      puVar8[0x19] = *(undefined2 *)((int)puVar18 + 2);
      puVar18 = (uint16 *)((int)puVar18 + 4);
      uVar16 = uVar16 - 1 & 0xffff;
      puVar8 = puVar8 + 0x32;
      *puVar8 = *(undefined2 *)puVar18;
    }
  }

  iVar17 = DAT_80013e78;
  uVar16 = 0;

  if (0 < (int)((int)puVar7 - 1U))
  {
    do
    {
      puVar6 = (ushort *)(DAT_80013e7c + uVar16 * 0x32);
      uVar1 = *puVar6;
      uVar9 = puVar6[0x19];
      sVar14 = 0xc;

      if (uVar1 < uVar9)
      {
        uVar13 = uVar9 - uVar1;
      }
      else
      {
        uVar13 = uVar1 - uVar9;
      }

      iVar10 = 0;
      uVar15 = (uint)uVar13;

      if (uVar1 < uVar9)
      {
        do
        {
          lVar2 = (longlong)iVar17 * (longlong)(int)(uVar15 * (iVar10 + 2));
          lVar3 = (longlong)iVar17 * (longlong)(int)(uVar15 * (iVar10 + 1));
          sVar14 = sVar14 + -1;
          puVar6[1] = ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f)) + uVar1;
          iVar10 = iVar10 + 2;
          puVar6 = puVar6 + 2;
          *puVar6 = ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f)) + uVar1;
        } while (sVar14 != 0);
      }
      else
      {
        do
        {
          lVar2 = (longlong)iVar17 * (longlong)(int)(uVar15 * (iVar10 + 2));
          lVar3 = (longlong)iVar17 * (longlong)(int)(uVar15 * (iVar10 + 1));
          sVar14 = sVar14 + -1;
          puVar6[1] = uVar1 - ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f));
          iVar10 = iVar10 + 2;
          puVar6 = puVar6 + 2;
          *puVar6 = uVar1 - ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f));
        } while (sVar14 != 0);
      }

      uVar16 = uVar16 + 1 & 0xfffeffff;
    } while ((int)uVar16 < (int)((int)puVar7 - 1U));
  }

  uVar16 = (int)puVar7 - 1;

  if (0 < (int)uVar16)
  {
    puVar8 = DAT_80013e84;
    puVar20 = DAT_80013e80;

    if ((uVar16 & 1) != 0)
    {
      puVar20 = DAT_80013e80 + 0x19;
      puVar8 = DAT_80013e84 + 0x19;
      *puVar8 = *puVar20;
    }

    uVar16 = uVar16 * 0x8000 >> 0x10;

    while (uVar16 != 0)
    {
      puVar8[0x19] = puVar20[0x19];
      puVar20 = puVar20 + 0x32;
      uVar16 = uVar16 - 1 & 0xffff;
      puVar8 = puVar8 + 0x32;
      *puVar8 = *puVar20;
    }
  }

  uVar16 = 0;
  puVar6 = puVar7 + -1;

  if (0 < (int)puVar6)
  {
    do
    {
      iVar10 = DAT_80013e88 + uVar16 * 0x32;
      uVar1 = *(ushort *)(iVar10 + 0x18);
      uVar9 = *(ushort *)(iVar10 + 0x4a);

      if (uVar1 < uVar9)
      {
        psVar11 = (short *)(iVar10 + 0x18);
        iVar10 = 0;
        sVar14 = 0xc;

        do
        {
          lVar2 = (longlong)iVar17 * (longlong)(int)((uint)(ushort)(uVar9 - uVar1) * (iVar10 + 1));
          lVar3 = (longlong)iVar17 * (longlong)(int)((uint)(ushort)(uVar9 - uVar1) * (iVar10 + 2));
          sVar14 = sVar14 + -1;
          psVar11[1] = ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f)) + uVar1;
          iVar10 = iVar10 + 2;
          psVar11 = psVar11 + 2;
          *psVar11 = ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f)) + uVar1;
        } while (sVar14 != 0);
      }
      else
      {
        psVar11 = (short *)(iVar10 + 0x18);
        iVar10 = 0;
        sVar14 = 0xc;

        do
        {
          lVar2 = (longlong)iVar17 * (longlong)(int)((uint)(ushort)(uVar1 - uVar9) * (iVar10 + 1));
          lVar3 = (longlong)iVar17 * (longlong)(int)((uint)(ushort)(uVar1 - uVar9) * (iVar10 + 2));
          sVar14 = sVar14 + -1;
          psVar11[1] = uVar1 - ((short)(int)(lVar2 >> 0x23) - (short)(lVar2 >> 0x3f));
          iVar10 = iVar10 + 2;
          psVar11 = psVar11 + 2;
          *psVar11 = uVar1 - ((short)(int)(lVar3 >> 0x23) - (short)(lVar3 >> 0x3f));
        } while (sVar14 != 0);
      }

      puVar7 = (ushort *)(uVar16 + 1);
      uVar16 = (uint)puVar7 & 0xfffeffff;
    } while ((int)uVar16 < (int)puVar6);
  }

  uVar16 = count >> 1;

  if (count != 0)
  {
    uVar15 = uVar16;
    puVar6 = DAT_80013e90;
    puVar7 = DAT_80013e8c;
    puVar18 = (uint16 *)((int)buffer + -2);

    if ((count & 1) != 0)
    {
      puVar7 = DAT_80013e8c + 1;
      puVar6 = DAT_80013e90 + 1;
      *(short *)buffer = (short)((uint)*puVar7 + (uint)*puVar6 >> 1);
      puVar18 = buffer;
    }

    while (uVar15 != 0)
    {
      *(short *)((int)puVar18 + 2) = (short)((uint)puVar7[1] + (uint)puVar6[1] >> 1);
      *(short *)(uint16 *)((int)puVar18 + 4) = (short)((uint)puVar6[2] + (uint)puVar7[2] >> 1);
      uVar15 = uVar15 - 1;
      puVar6 = puVar6 + 2;
      puVar7 = puVar7 + 2;
      puVar18 = (uint16 *)((int)puVar18 + 4);
    }
  }

  uVar5 = count * DAT_80013e94;
  uVar15 = uVar5 >> 0x13;
  uVar19 = uVar15 - 1;

  if (0 < (int)uVar19)
  {
    puVar6 = (ushort *)((int)buffer + -0xc);
    puVar7 = DAT_80013e98;

    if ((uVar19 & 1) != 0)
    {
      puVar6 = (ushort *)((int)buffer + 0xc);
      puVar7 = DAT_80013e98 + 0xc;
      *puVar7 = *puVar6;
    }

    uVar19 = uVar19 * 0x8000 >> 0x10;

    while (uVar19 != 0)
    {
      puVar7[0xc] = puVar6[0xc];
      puVar6 = puVar6 + 0x18;
      uVar19 = uVar19 - 1 & 0xffff;
      puVar7 = puVar7 + 0x18;
      *puVar7 = *puVar6;
    }
  }

  iVar17 = uVar15 - 2;

  if (0 < iVar17)
  {
    puVar7 = DAT_80013e9c;
  }

  uVar15 = 0;

  if (0 < iVar17)
  {
    do
    {
      iVar10 = DAT_80013e88 + uVar15 * 0x18;
      uVar1 = *(ushort *)(iVar10 + 0xc);
      uVar9 = *(ushort *)(iVar10 + 0x24);

      if (uVar1 < uVar9)
      {
        uVar19 = (uint)(ushort)(uVar9 - uVar1);
        iVar12 = 1;
        sVar14 = 5;
        psVar11 = (short *)(iVar10 + 0xe);
        *psVar11 = ((short)(int)((longlong)(int)puVar7 * (longlong)(int)uVar19 >> 0x21) - (short)((longlong)(int)puVar7 * (longlong)(int)uVar19 >> 0x3f)) + uVar1;

        do
        {
          lVar2 = (longlong)(int)puVar7 * (longlong)(int)(uVar19 * (iVar12 + 1));
          lVar3 = (longlong)(int)puVar7 * (longlong)(int)(uVar19 * (iVar12 + 2));
          sVar14 = sVar14 + -1;
          psVar11[1] = ((short)(int)(lVar2 >> 0x21) - (short)(lVar2 >> 0x3f)) + uVar1;
          iVar12 = iVar12 + 2;
          psVar11 = psVar11 + 2;
          *psVar11 = ((short)(int)(lVar3 >> 0x21) - (short)(lVar3 >> 0x3f)) + uVar1;
        } while (sVar14 != 0);
      }
      else
      {
        uVar19 = (uint)(ushort)(uVar1 - uVar9);
        iVar12 = 1;
        sVar14 = 5;
        psVar11 = (short *)(iVar10 + 0xe);
        *psVar11 = uVar1 - ((short)(int)((longlong)(int)puVar7 * (longlong)(int)uVar19 >> 0x21) - (short)((longlong)(int)puVar7 * (longlong)(int)uVar19 >> 0x3f));

        do
        {
          lVar2 = (longlong)(int)puVar7 * (longlong)(int)(uVar19 * (iVar12 + 1));
          lVar3 = (longlong)(int)puVar7 * (longlong)(int)(uVar19 * (iVar12 + 2));
          sVar14 = sVar14 + -1;
          psVar11[1] = uVar1 - ((short)(int)(lVar2 >> 0x21) - (short)(lVar2 >> 0x3f));
          iVar12 = iVar12 + 2;
          psVar11 = psVar11 + 2;
          *psVar11 = uVar1 - ((short)(int)(lVar3 >> 0x21) - (short)(lVar3 >> 0x3f));
        } while (sVar14 != 0);
      }

      uVar15 = uVar15 + 1 & 0xfffeffff;
    } while ((int)uVar15 < iVar17);
  }

  if (count != 0)
  {
    uVar15 = uVar16;
    puVar18 = (uint16 *)((int)buffer + -2);
    puVar7 = DAT_80013e90;

    if ((count & 1) != 0)
    {
      puVar7 = DAT_80013e90 + 1;
      *(short *)buffer = (short)((uint)*(ushort *)buffer + (uint)*puVar7 >> 1);
      puVar18 = buffer;
    }

    while (uVar15 != 0)
    {
      puVar4 = (uint16 *)((int)puVar18 + 4);
      *(ushort *)((int)puVar18 + 2) = (ushort)((uint)*(ushort *)((int)puVar18 + 2) + (uint)puVar7[1] >> 1);
      *(ushort *)puVar4 = (ushort)((uint)puVar7[2] + (uint)*(ushort *)puVar4 >> 1);
      uVar15 = uVar15 - 1;
      puVar18 = puVar4;
      puVar7 = puVar7 + 2;
    }
  }

  uVar5 = uVar5 >> 0x12;
  uVar15 = uVar5 - 1;

  if (0 < (int)uVar15)
  {
    puVar20 = (undefined2 *)((int)buffer + -6);
    puVar8 = DAT_80013ea0;

    if ((uVar15 & 1) != 0)
    {
      puVar20 = (undefined2 *)((int)buffer + 6);
      puVar8 = DAT_80013ea0 + 6;
      *puVar8 = *puVar20;
    }

    uVar15 = uVar15 * 0x8000 >> 0x10;

    while (uVar15 != 0)
    {
      puVar8[6] = puVar20[6];
      puVar20 = puVar20 + 0xc;
      uVar15 = uVar15 - 1 & 0xffff;
      puVar8 = puVar8 + 0xc;
      *puVar8 = *puVar20;
    }
  }

  uVar15 = DAT_80013ea8;
  uVar5 = uVar5 - 2;

  if (0 < (int)uVar5)
  {
    uVar5 = uVar5 & 0xffff;
    puVar7 = DAT_80013ea4;

    do
    {
      uVar1 = *puVar7;
      uVar9 = puVar7[6];

      if (uVar1 < uVar9)
      {
        uVar9 = uVar9 - uVar1;
        uVar19 = (uint)uVar9;
        puVar7[1] = uVar1 + (ushort)(uVar19 * DAT_80013e94 >> 0x12);
        puVar7[2] = uVar1 + (short)(uint)((ulonglong)uVar9 * 2 * (ulonglong)uVar15 >> 0x22);
        puVar7[3] = uVar1 + (short)(uint)((ulonglong)(uVar19 * 3) * (ulonglong)uVar15 >> 0x22);
        puVar7[4] = uVar1 + (short)(uint)((ulonglong)uVar9 * 4 * (ulonglong)uVar15 >> 0x22);
        puVar7[5] = uVar1 + (short)(uint)((ulonglong)(uVar19 * 5) * (ulonglong)uVar15 >> 0x22);
      }
      else
      {
        uVar9 = uVar1 - uVar9;
        uVar19 = (uint)uVar9;
        puVar7[1] = uVar1 - (ushort)(uVar19 * DAT_80013e94 >> 0x12);
        puVar7[2] = uVar1 - (short)(uint)((ulonglong)uVar9 * 2 * (ulonglong)uVar15 >> 0x22);
        puVar7[3] = uVar1 - (short)(uint)((ulonglong)(uVar19 * 3) * (ulonglong)uVar15 >> 0x22);
        puVar7[4] = uVar1 - (short)(uint)((ulonglong)uVar9 * 4 * (ulonglong)uVar15 >> 0x22);
        puVar7[5] = uVar1 - (short)(uint)((ulonglong)(uVar19 * 5) * (ulonglong)uVar15 >> 0x22);
      }

      uVar5 = uVar5 - 1 & 0xffff;
      puVar7 = puVar7 + 6;
    } while (uVar5 != 0);
  }

  if (count != 0)
  {
    puVar18 = (uint16 *)((int)buffer + -2);
    puVar7 = DAT_80013e90;

    if ((count & 1) != 0)
    {
      puVar7 = DAT_80013e90 + 1;
      *(short *)buffer = (short)((uint)*(ushort *)buffer + (uint)*puVar7 >> 1);
      puVar18 = buffer;
    }

    if (uVar16 != 0)
    {
      do
      {
        puVar6 = (ushort *)((int)puVar18 + 2);
        uVar16 = uVar16 - 1;
        puVar18 = (uint16 *)((int)puVar18 + 4);
        *puVar6 = (ushort)((uint)*puVar6 + (uint)puVar7[1] >> 1);
        puVar7 = puVar7 + 2;
        *(ushort *)puVar18 = (ushort)((uint)*(ushort *)puVar18 + (uint)*puVar7 >> 1);
      } while (uVar16 != 0);

      return;
    }

    return;
  }

  return;
}


