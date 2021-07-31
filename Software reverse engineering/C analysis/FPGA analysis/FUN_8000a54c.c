//Function called from main loop

void FUN_8000a54c(void)

{
  byte bVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  byte *pbVar5;
  undefined4 uVar6;
  int iVar7;
  uint uVar8;
  byte bVar9;
  bool bVar10;
  
  iVar2 = DAT_8000a6a8;
  bVar9 = 0xff;
  if (0xd < *(byte *)(DAT_8000a6a8 + 10)) {
    iVar7 = 0x1e;
    goto LAB_8000a5bc;
  }
  if (*(byte *)(DAT_8000a6a8 + 10) < 0xc) {
    if (*(byte *)(DAT_8000a6a8 + 10) < 9) {
      if (6 < *(byte *)(DAT_8000a6a8 + 10)) {
        iVar7 = 100;
        goto LAB_8000a5bc;
      }
      if (3 < *(byte *)(DAT_8000a6a8 + 10)) {
        iVar7 = 0x32;
        goto LAB_8000a5bc;
      }
      if (1 < *(byte *)(DAT_8000a6a8 + 10)) goto LAB_8000a5b0;
    }
    iVar7 = 3;
  }
  else {
LAB_8000a5b0:
    iVar7 = 10;
  }
LAB_8000a5bc:
  iVar4 = FUN_80017724(DAT_8000a6ac,0xc);
  puVar3 = PTR_DAT_8000a6b0;
  if (iVar4 == 0) {
    if (*(char *)(iVar2 + 0x39) == '\0') {
      *PTR_DAT_8000a6b0 = 0;
    }
    *(undefined *)(iVar2 + 0x39) = 1;
  }
  else {
    *(undefined *)(iVar2 + 0x39) = 0;
  }
  iVar4 = FUN_8001b3ac();
  uVar8 = iVar4 + (uint)((ulonglong)
                         (uint)((int)(short)(ushort)*(byte *)(DAT_8000a6b4 + 2) *
                               (int)(short)((short)iVar4 * 10)) * (ulonglong)DAT_8000a6b8 >> 0x28);
  if (*(char *)(iVar2 + 0x39) != '\0') {
    uVar8 = uVar8 - 7;
  }
  if (uVar8 < 0x19) {
    uVar8 = 0x19;
  }
  pbVar5 = (byte *)FUN_80000dc4((uVar8 - 0x19) * 0x14,0x15);
  bVar1 = *puVar3;
  DAT_8000a6bc[bVar1] = (byte)pbVar5;
  if ((int)(uint)bVar1 < iVar7 + -1) {
    *puVar3 = bVar1 + 1;
    return;
  }
  bVar10 = iVar7 != 0;
  if (bVar10) {
    pbVar5 = DAT_8000a6bc;
  }
  *puVar3 = 0;
  while (bVar10) {
    bVar1 = *pbVar5;
    pbVar5 = pbVar5 + 1;
    if (bVar1 < bVar9) {
      bVar9 = bVar1;
    }
    iVar7 = iVar7 + -1;
    bVar10 = iVar7 != 0;
  }
  *(byte *)(iVar2 + 0x38) = bVar9;
  FUN_80017760();
  FUN_80019704(0xffffff);
  FUN_80018f6c(0x2c0,5,0x2d5);
  FUN_80018f6c(0x2be,9);
  iVar2 = DAT_8000bde4;
  if (*(byte *)(DAT_8000bde4 + 0x38) < 4) {
    uVar6 = 0xff0000;
  }
  else {
    uVar6 = 0xbb00;
  }
  FUN_80019704(uVar6);
  if (0x14 < *(byte *)(iVar2 + 0x38)) {
    *(undefined *)(iVar2 + 0x38) = 0x14;
  }
  if (*(char *)(iVar2 + 0x38) != '\0') {
    FUN_80018f6c(0x2d5 - (uint)*(byte *)(iVar2 + 0x38),6,0x2d4,0x10);
  }
  if (*(char *)(iVar2 + 0x39) != '\0') {
    FUN_80019704(DAT_8000bde8);
    uVar8 = DAT_8000bdec;
    FUN_80018ca8(10,0x2c4,DAT_8000bdec);
    FUN_80018ca8(0xb,0x2c4,uVar8);
    FUN_80018ca8(0xc,0x2c4,uVar8);
    FUN_80018ef4(uVar8 | 1,8,0xe);
    FUN_80018ef4(0x2d0,9,0xd);
    FUN_80018ef4(uVar8 + 3,10);
    FUN_80018ef4(uVar8 + 4,0xb);
  }
  iVar7 = DAT_8001cd30;
  iVar2 = DAT_8001cd2c;
  uVar8 = 5;
  do {
    iVar4 = uVar8 * 800 + 0x2be;
    FUN_80000608(iVar7 + iVar4 * 2,iVar2 + iVar4 * 2,0x18);
    uVar8 = uVar8 + 1;
  } while (uVar8 < 0x24);
  return;
}

