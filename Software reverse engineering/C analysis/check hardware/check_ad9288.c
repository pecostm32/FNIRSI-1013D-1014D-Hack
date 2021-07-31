uint check_ad9288(void)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  ushort uVar5;
  int iVar6;
  ushort *puVar7;
  ushort *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  bool bVar14;
  bool bVar15;
  
  bVar1 = false;
  bVar2 = false;
  uVar10 = 0;
  bVar3 = false;
  bVar4 = false;

  FUN_80026728();                            //Do some FPGA control

  *(undefined *)(DAT_80001198 + 10) = 0x18;

  FUN_800266c4();
  FUN_80006948(400);
  FUN_80009694(400);
  delay_2(100);
  FUN_80025b7c(0x96);
  puVar8 = DAT_8000119c;
  uVar12 = 400;
  do {
    FUN_80025b24();
    do {
      iVar6 = FUN_80025b0c();
    } while (iVar6 == 0);
    FUN_80006948(uVar12);
    FUN_80009694(uVar12);
    delay(1000);
    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(1);
    puVar8[uVar10] = uVar5;
    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(2);
    puVar8[uVar10 + 1000] = uVar5;
    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(3);
    puVar8[uVar10 + 2000] = uVar5;
    FUN_80026698(0x14);
    uVar5 = FUN_800011a4(4);
    iVar6 = uVar10 + 3000;
    uVar12 = uVar12 + 1 & 0xfffeffff;
    uVar10 = uVar10 + 1 & 0xfffeffff;
    puVar8[iVar6] = uVar5;
  } while (uVar12 < 0x3fd);
  uVar12 = 0;
  uVar13 = 0;
  uVar10 = 1000;
  iVar6 = 600;
  puVar7 = puVar8;
  do {
    uVar9 = (uint)puVar7[1];
    uVar11 = (uint)*puVar7;
    bVar15 = uVar9 <= uVar11;
    bVar14 = uVar11 == uVar9;
    if (!bVar15) {
      uVar10 = uVar10 - 1;
      uVar12 = uVar12 + (uVar9 - uVar11) + 1;
    }
    if (bVar15 && !bVar14) {
      bVar15 = puVar7[2] <= uVar9;
      bVar14 = uVar9 == puVar7[2];
    }
    if (bVar15 && !bVar14) {
      uVar13 = uVar13 + 1;
    }
    if (uVar9 < uVar11) {
      uVar10 = uVar10 + 1;
    }
    iVar6 = iVar6 + -1;
    puVar7 = puVar7 + 1;
  } while (iVar6 != 0);
  if ((uVar12 < 0x50 && uVar13 < 0x23) && (DAT_800011a0 < uVar10)) {
    bVar3 = true;
  }
  uVar13 = 0;
  uVar12 = 0;
  uVar10 = 1000;
  puVar7 = puVar8 + 0x3e9;
  iVar6 = 600;
  do {
    uVar9 = (uint)*puVar7;
    uVar11 = (uint)puVar7[-1];
    bVar15 = uVar9 <= uVar11;
    bVar14 = uVar11 == uVar9;
    if (!bVar15) {
      uVar10 = uVar10 - 1;
      uVar13 = uVar13 + (uVar9 - uVar11) + 1;
    }
    if (bVar15 && !bVar14) {
      bVar15 = puVar7[1] <= uVar9;
      bVar14 = uVar9 == puVar7[1];
    }
    if (bVar15 && !bVar14) {
      uVar12 = uVar12 + 1;
    }
    if (uVar9 < uVar11) {
      uVar10 = uVar10 + 1;
    }
    iVar6 = iVar6 + -1;
    puVar7 = puVar7 + 1;
  } while (iVar6 != 0);
  if ((uVar13 < 0x50 && uVar12 < 0x23) && (DAT_800011a0 < uVar10)) {
    bVar4 = true;
  }
  uVar13 = 0;
  uVar12 = 0;
  uVar10 = 1000;
  puVar7 = puVar8 + 0x7d1;
  iVar6 = 600;
  do {
    uVar9 = (uint)*puVar7;
    uVar11 = (uint)puVar7[-1];
    bVar15 = uVar9 <= uVar11;
    bVar14 = uVar11 == uVar9;
    if (!bVar15) {
      uVar10 = uVar10 - 1;
      uVar13 = uVar13 + (uVar9 - uVar11) + 1;
    }
    if (bVar15 && !bVar14) {
      bVar15 = puVar7[1] <= uVar9;
      bVar14 = uVar9 == puVar7[1];
    }
    if (bVar15 && !bVar14) {
      uVar12 = uVar12 + 1;
    }
    if (uVar9 < uVar11) {
      uVar10 = uVar10 + 1;
    }
    iVar6 = iVar6 + -1;
    puVar7 = puVar7 + 1;
  } while (iVar6 != 0);
  if ((uVar13 < 0x50 && uVar12 < 0x23) && (DAT_800011a0 < uVar10)) {
    bVar1 = true;
  }
  uVar13 = 0;
  uVar12 = 0;
  uVar10 = 1000;
  puVar8 = puVar8 + 0xbb9;
  iVar6 = 600;
  do {
    uVar9 = (uint)*puVar8;
    uVar11 = (uint)puVar8[-1];
    bVar15 = uVar9 <= uVar11;
    bVar14 = uVar11 == uVar9;
    if (!bVar15) {
      uVar10 = uVar10 - 1;
      uVar13 = uVar13 + (uVar9 - uVar11) + 1;
    }
    if (bVar15 && !bVar14) {
      bVar15 = puVar8[1] <= uVar9;
      bVar14 = uVar9 == puVar8[1];
    }
    if (bVar15 && !bVar14) {
      uVar12 = uVar12 + 1;
    }
    if (uVar9 < uVar11) {
      uVar10 = uVar10 + 1;
    }
    iVar6 = iVar6 + -1;
    puVar8 = puVar8 + 1;
  } while (iVar6 != 0);
  if ((uVar13 < 0x50 && uVar12 < 0x23) && (DAT_800011a0 < uVar10)) {
    bVar2 = true;
  }
  bVar14 = bVar3;
  if (bVar3) {
    bVar14 = bVar4;
  }
  if (!bVar3 || !bVar14) {
    if (bVar1 && bVar2) {
      uVar10 = 2;
    }
    else {
      uVar10 = 0;
    }
    return uVar10;
  }
  if (bVar1 && bVar2) {
    uVar10 = 3;
  }
  else {
    uVar10 = 1;
  }
  return uVar10;
}

