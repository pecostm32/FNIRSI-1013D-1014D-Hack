//Check on ADC's

undefined4 FUN_80000e94(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  ushort uVar5;
  int iVar6;
  ushort *puVar7;
  undefined4 uVar8;
  ushort *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  bool bVar15;
  bool bVar16;
  
  bVar1 = false;
  bVar2 = false;
  uVar11 = 0;
  bVar3 = false;
  bVar4 = false;
  FUN_80026728();
  *(undefined *)(DAT_80001198 + 10) = 0x18;

  FUN_800266c4();
  FUN_80006948(400);
  FUN_80009694(400);
  FUN_8000bc00(100);
  FUN_80025b7c(0x96);

  puVar9 = DAT_8000119c;
  uVar13 = 400;

  do
  {
    FUN_80025b24();

    do
    {
      iVar6 = FUN_80025b0c();
    } while (iVar6 == 0);

    FUN_80006948(uVar13);
    FUN_80009694(uVar13);

    FUN_8000bc34(1000);                 //Delay

    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(1);
    puVar9[uVar11] = uVar5;
    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(2);
    puVar9[uVar11 + 1000] = uVar5;
    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(3);
    puVar9[uVar11 + 2000] = uVar5;
    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(4);
    iVar6 = uVar11 + 3000;
    uVar13 = uVar13 + 1 & 0xfffeffff;
    uVar11 = uVar11 + 1 & 0xfffeffff;
    puVar9[iVar6] = uVar5;
  } while (uVar13 < 0x3fd);

  uVar13 = 0;
  uVar14 = 0;
  uVar11 = 1000;
  iVar6 = 600;
  puVar7 = puVar9;

  do
  {
    uVar10 = (uint)puVar7[1];
    uVar12 = (uint)*puVar7;
    bVar16 = uVar10 <= uVar12;
    bVar15 = uVar12 == uVar10;

    if (!bVar16)
    {
      uVar11 = uVar11 - 1;
      uVar13 = uVar13 + (uVar10 - uVar12) + 1;
    }

    if (bVar16 && !bVar15)
    {
      bVar16 = puVar7[2] <= uVar10;
      bVar15 = uVar10 == puVar7[2];
    }

    if (bVar16 && !bVar15)
    {
      uVar14 = uVar14 + 1;
    }

    if (uVar10 < uVar12)
    {
      uVar11 = uVar11 + 1;
    }

    iVar6 = iVar6 + -1;
    puVar7 = puVar7 + 1;
  } while (iVar6 != 0);

  if ((uVar13 < 0x50 && uVar14 < 0x23) && (DAT_800011a0 < uVar11))
  {
    bVar3 = true;
  }

  uVar14 = 0;
  uVar13 = 0;
  uVar11 = 1000;
  puVar7 = puVar9 + 0x3e9;
  iVar6 = 600;

  do
  {
    uVar10 = (uint)*puVar7;
    uVar12 = (uint)puVar7[-1];
    bVar16 = uVar10 <= uVar12;
    bVar15 = uVar12 == uVar10;

    if (!bVar16)
    {
      uVar11 = uVar11 - 1;
      uVar14 = uVar14 + (uVar10 - uVar12) + 1;
    }

    if (bVar16 && !bVar15)
    {
      bVar16 = puVar7[1] <= uVar10;
      bVar15 = uVar10 == puVar7[1];
    }

    if (bVar16 && !bVar15)
    {
      uVar13 = uVar13 + 1;
    }

    if (uVar10 < uVar12)
    {
      uVar11 = uVar11 + 1;
    }

    iVar6 = iVar6 + -1;
    puVar7 = puVar7 + 1;
  } while (iVar6 != 0);

  if ((uVar14 < 0x50 && uVar13 < 0x23) && (DAT_800011a0 < uVar11))
  {
    bVar4 = true;
  }

  uVar14 = 0;
  uVar13 = 0;
  uVar11 = 1000;
  puVar7 = puVar9 + 0x7d1;
  iVar6 = 600;

  do
  {
    uVar10 = (uint)*puVar7;
    uVar12 = (uint)puVar7[-1];
    bVar16 = uVar10 <= uVar12;
    bVar15 = uVar12 == uVar10;

    if (!bVar16)
    {
      uVar11 = uVar11 - 1;
      uVar14 = uVar14 + (uVar10 - uVar12) + 1;
    }

    if (bVar16 && !bVar15)
    {
      bVar16 = puVar7[1] <= uVar10;
      bVar15 = uVar10 == puVar7[1];
    }

    if (bVar16 && !bVar15)
    {
      uVar13 = uVar13 + 1;
    }

    if (uVar10 < uVar12)
    {
      uVar11 = uVar11 + 1;
    }

    iVar6 = iVar6 + -1;
    puVar7 = puVar7 + 1;
  } while (iVar6 != 0);

  if ((uVar14 < 0x50 && uVar13 < 0x23) && (DAT_800011a0 < uVar11))
  {
    bVar1 = true;
  }

  uVar14 = 0;
  uVar13 = 0;
  uVar11 = 1000;
  puVar9 = puVar9 + 0xbb9;
  iVar6 = 600;

  do
  {
    uVar10 = (uint)*puVar9;
    uVar12 = (uint)puVar9[-1];
    bVar16 = uVar10 <= uVar12;
    bVar15 = uVar12 == uVar10;

    if (!bVar16)
    {
      uVar11 = uVar11 - 1;
      uVar14 = uVar14 + (uVar10 - uVar12) + 1;
    }

    if (bVar16 && !bVar15)
    {
      bVar16 = puVar9[1] <= uVar10;
      bVar15 = uVar10 == puVar9[1];
    }

    if (bVar16 && !bVar15)
    {
      uVar13 = uVar13 + 1;
    }

    if (uVar10 < uVar12)
    {
      uVar11 = uVar11 + 1;
    }

    iVar6 = iVar6 + -1;
    puVar9 = puVar9 + 1;
  } while (iVar6 != 0);

  if ((uVar14 < 0x50 && uVar13 < 0x23) && (DAT_800011a0 < uVar11))
  {
    bVar2 = true;
  }

  bVar15 = bVar3;
  if (bVar3)
  {
    bVar15 = bVar4;
  }

  if (!bVar3 || !bVar15)
  {
    if (bVar1 && bVar2)
    {
      uVar8 = 2;
    }
    else
    {
      uVar8 = 0;
    }

    return uVar8;
  }

  if (bVar1 && bVar2)
  {
    uVar8 = 3;
  }
  else
  {
    uVar8 = 1;
  }

  return uVar8;
}

