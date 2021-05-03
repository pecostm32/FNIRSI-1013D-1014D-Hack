void FUN_80009af4(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined2 uVar4;
  undefined2 *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  
  uVar8 = DAT_80009e48 * (uint)*(byte *)(DAT_80009e44 + 3) * 0xff + DAT_80009e48 >> 0x16;
  uVar8 = uVar8 << 0x10 | uVar8 << 8 | uVar8;
  uVar4 = FUN_800232b4(uVar8);
  set_display_color(uVar8);
  iVar1 = DAT_80009e4c;
  FUN_80018ca8(0xf9,2,DAT_80009e4c);
  FUN_80018ef4(0x16c,0x2e,0x1c1);
  iVar9 = 0x16c;
  do {
    FUN_80018ef4(iVar9,0xf7,0xfb);
    iVar9 = (iVar9 + 5) * 0x10000 >> 0x10;
  } while (iVar9 < iVar1);
  iVar9 = 0x16c;
  do {
    FUN_80018ef4(iVar9,0xf7,0xfb);
    iVar9 = (iVar9 + -5) * 0x10000 >> 0x10;
  } while (2 < iVar9);
  iVar9 = 0xf9;
  do {
    FUN_80018ca8(iVar9,0x16a,0x16e);
    iVar9 = (iVar9 + 5) * 0x10000 >> 0x10;
  } while (iVar9 < 0x1c1);
  iVar9 = 0xf9;
  do {
    FUN_80018ca8(iVar9,0x16a,0x16e);
    piVar2 = Global_Frame_Buffer_Pointer;
    iVar9 = (iVar9 + -5) * 0x10000 >> 0x10;
  } while (0x2e < iVar9);
  iVar9 = 0xf9;
  do {
    iVar6 = 0x24;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * 0x640 + 0x2d8);
    *puVar5 = uVar4;
    do {
      puVar5[5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 10;
      *puVar5 = uVar4;
    } while (iVar6 != 0);
    iVar6 = 0x24;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * 0x640 + 0x2d8);
    *puVar5 = uVar4;
    do {
      puVar5[-5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -10;
      *puVar5 = uVar4;
    } while (iVar6 != 0);
    iVar9 = (iVar9 + 0x32) * 0x10000 >> 0x10;
  } while (iVar9 < 0x1df);
  iVar9 = 0xf9;
  do {
    iVar6 = 0x24;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * 0x640 + 0x2d8);
    *puVar5 = uVar4;
    do {
      puVar5[5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 10;
      *puVar5 = uVar4;
    } while (iVar6 != 0);
    iVar6 = 0x24;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * 0x640 + 0x2d8);
    *puVar5 = uVar4;
    do {
      puVar5[-5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -10;
      *puVar5 = uVar4;
      iVar7 = DAT_80009e54;
    } while (iVar6 != 0);
    iVar9 = (iVar9 + -0x32) * 0x10000 >> 0x10;
  } while (0x32 < iVar9);
  iVar9 = 0;
  do {
    iVar6 = 4;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * 8000 + iVar7);
    do {
      puVar5[0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 100;
      *puVar5 = uVar4;
    } while (iVar6 != 0);
    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x28);
  iVar9 = 0;
  do {
    iVar6 = 4;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * -8000 + iVar7);
    do {
      puVar5[0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 100;
      *puVar5 = uVar4;
      iVar3 = DAT_80009e58;
    } while (iVar6 != 0);
    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x29);
  iVar9 = 0;
  do {
    iVar6 = 4;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * 8000 + iVar3);
    do {
      puVar5[-0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -100;
      *puVar5 = uVar4;
    } while (iVar6 != 0);
    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x28);
  iVar9 = 0;
  do {
    iVar6 = 4;
    puVar5 = (undefined2 *)(*piVar2 + iVar9 * -8000 + iVar3);
    do {
      puVar5[-0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -100;
      *puVar5 = uVar4;
    } while (iVar6 != 0);
    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x29);
  FUN_80018ca8(0x2e,2,iVar1);
  FUN_80018ca8(0x1c1,2,iVar1);
  FUN_80018ef4(2,0x2e,0x1c1);
  FUN_8001936c();
  iVar7 = *(int *)(*DAT_80018f68 + 0x4c);
  iVar9 = *(int *)(*DAT_80018f68 + 0x50);
  iVar6 = FUN_8002ac10(&stack0xffffffe8);
  while (iVar6 != 0) {
    FUN_8001cc4c(iVar1 + iVar7,iVar9 + 0x2e,iVar9 + 0x1c1);
    iVar6 = FUN_8002ab40();
  }
  FUN_80019a6c();
  return;
}

