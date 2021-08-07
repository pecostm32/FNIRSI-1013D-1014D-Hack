
undefined4 FUN_800291e0(void)

{
  ushort uVar1;
  bool bVar2;
  bool bVar3;
  undefined4 uVar4;
  uint uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  bool bVar10;
  
  bVar6 = *(byte *)(DAT_80029300 + 10);
  bVar2 = false;
  bVar10 = 10 < bVar6;
  bVar9 = bVar6 == 0xb;
  if (bVar10) {
    bVar6 = *(byte *)(DAT_80029300 + 0x21);
  }
  uVar4 = 1;
  bVar3 = false;
  if (bVar10) {
    bVar9 = bVar6 == 0;
  }
  if (!bVar9) {
    return 0;
  }
  if (0x18 < *(byte *)(DAT_80029300 + 10)) {
    return 0;
  }
  iVar7 = DAT_80029308;
  if (*(char *)(DAT_80029300 + 0x23) != '\0') {
    iVar7 = DAT_8002930c;
  }
  uVar5 = DAT_80029304;
  if (*(char *)(DAT_80029300 + 0x22) == '\0') {
    do {
      iVar8 = iVar7 + uVar5 * 2;
      if ((*(ushort *)(iVar8 + -2) < (ushort)*(byte *)(DAT_80029300 + 0x28)) &&
         ((ushort)*(byte *)(DAT_80029300 + 0x28) <= *(ushort *)(iVar8 + 2))) goto LAB_80029294;
      uVar5 = uVar5 + 1 & 0xfffeffff;
    } while (uVar5 < DAT_80029304 + 10);
  }
  else {
    do {
      iVar8 = iVar7 + uVar5 * 2;
      if (((ushort)*(byte *)(DAT_80029300 + 0x28) < *(ushort *)(iVar8 + -2)) &&
         (*(ushort *)(iVar8 + 2) <= (ushort)*(byte *)(DAT_80029300 + 0x28))) goto LAB_80029294;
      uVar5 = uVar5 + 1 & 0xfffeffff;
    } while (uVar5 < DAT_80029304 + 10);
  }
LAB_800292ac:
  uVar5 = 100;
  do {
    uVar1 = *(ushort *)(iVar7 + uVar5 * 2);
    if (*(byte *)(DAT_80029300 + 0x28) < uVar1) {
      bVar2 = true;
    }
    if (uVar1 < *(byte *)(DAT_80029300 + 0x28)) {
      bVar3 = true;
    }
    uVar5 = uVar5 + 1 & 0xfffeffff;
  } while (uVar5 < DAT_80029310);
  if (!bVar2 || !bVar3) {
    return 0;
  }
  return uVar4;
LAB_80029294:
  uVar4 = 0;
  goto LAB_800292ac;
}

