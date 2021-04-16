void FUN_8001d5d4(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  uint *puVar7;
  int iVar8;
  int *piVar9;
  
  uVar5 = DAT_8001d62c;
  iVar8 = 0;
  *DAT_8001d628 = DAT_8001d624;
  do 
  {
    FUN_8001764c(uVar5,iVar8,2);   //Setup port D0:15 pins for LCD
    uVar4 = DAT_8001d624;
    iVar3 = DAT_800164e0;
    iVar2 = DAT_800164dc;
    iVar1 = DAT_800164d8;
    iVar8 = iVar8 + 1;
  } while (iVar8 < 0x16);

  //Function jumps into FUN_800163CC

  iVar8 = DAT_800164d8 + -0x254000;
  piVar9 = (int *)(DAT_800164e0 + 8);
  *(int *)(DAT_800164dc + 4) = DAT_800164e0;
  *piVar9 = iVar1;
  *(undefined4 *)(iVar3 + 0xc) = 0;
  *(int *)(iVar3 + 0x10) = iVar8;
  *(undefined4 *)(iVar3 + 0x1c) = 800;
  *(undefined4 *)(iVar3 + 0x20) = 0x1e0;
  *(undefined4 *)(iVar3 + 0x2c) = 0x10;
  *(undefined4 *)(iVar3 + 0x4c) = 0x14;
  *(undefined4 *)(iVar3 + 0x50) = 0x16;
  *(undefined4 *)(iVar3 + 0x58) = 10;
  *(undefined4 *)(iVar3 + 0x5c) = 0;
  *(undefined4 *)(iVar3 + 0x18) = 1;
  *(undefined4 *)(iVar3 + 0x54) = 0x17;
  *(undefined4 *)(iVar3 + 0x44) = 0xd2;
  *(undefined4 *)(iVar3 + 0x48) = 0x2e;
  *(undefined4 *)(iVar3 + 0x14) = 0;
  *(undefined4 *)(iVar3 + 0x60) = 0;
  *(undefined4 *)(iVar3 + 100) = 1;
  *(undefined4 *)(iVar3 + 0x68) = 0;
  *(undefined4 *)(iVar3 + 0x30) = 2;
  *(undefined4 *)(iVar3 + 0x34) = 0;
  *(undefined4 *)(iVar3 + 0x38) = uVar4;
  iVar8 = 0x800;
  *(undefined4 *)(iVar3 + 0x3c) = 0;
  do {
    *(undefined4 *)(DAT_800164d8 + iVar8) = 0;
    iVar8 = iVar8 + 4;
  } while (iVar8 < 0x1000);
  puVar6 = *(undefined4 **)(iVar3 + 0x10);
  *puVar6 = 0;
  puVar6[1] = 0;
  puVar6[0x11] = puVar6[0x11] & 0xfffffff;
  puVar6[0x23] = 0xffffffff;
  puVar6[0x3d] = 0xffffffff;
  FUN_8000b8f8(*(undefined4 *)(iVar2 + 4));
  FUN_80028200(*(undefined4 *)(iVar2 + 4));
  puVar7 = *(uint **)(*(int *)(iVar2 + 4) + 0x10);
  *puVar7 = *puVar7 | 0x80000000;
  return;
}

