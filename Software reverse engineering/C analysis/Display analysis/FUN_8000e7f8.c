void FUN_8000e7f8(int param_1)

{
  int iVar1;
  ushort uVar2;
  ushort uVar3;
  undefined *puVar4;
  int *piVar5;
  ushort *puVar6;
  ushort *puVar7;
  int iVar8;
  uint uVar9;
  
  piVar5 = Global_Frame_Buffer_Pointer;
  puVar4 = PTR_DAT_8000e8e8;
  if (param_1 == 0) {
    uVar9 = 0;
    do {
      memcpy((void *)(*piVar5 + uVar9 * 0x640),puVar4 + uVar9 * 0xa0,0xa0);
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0x2a);
  }
  else {
    uVar9 = 0;
    do {
      puVar6 = (ushort *)(puVar4 + uVar9 * 0xa0);
      puVar7 = (ushort *)(*piVar5 + uVar9 * 0x640);
      *puVar7 = ~*puVar6;
      uVar2 = puVar6[1];
      iVar8 = 0x27;
      do {
        iVar8 = iVar8 + -1;
        uVar3 = puVar6[2];
        puVar7[1] = ~uVar2;
        uVar2 = puVar6[3];
        puVar7 = puVar7 + 2;
        *puVar7 = ~uVar3;
        puVar6 = puVar6 + 2;
      } while (iVar8 != 0);
      iVar8 = uVar9 * 0x50;
      iVar1 = uVar9 * 800;
      uVar9 = uVar9 + 1 & 0xfffeffff;
      *(ushort *)(*piVar5 + (iVar1 + 0x4f) * 2) = ~*(ushort *)(puVar4 + (iVar8 + 0x4f) * 2);
    } while (uVar9 < 0x2a);
  }
  iVar1 = Start_Of_Screen_Mem;
  iVar8 = Screen_Frame_Buffer;
  uVar9 = 0;
  do {
    copy_short((void *)(iVar1 + uVar9 * 0x640),(void *)(iVar8 + uVar9 * 0x640),0x51);
    uVar9 = uVar9 + 1;
  } while (uVar9 < 0x2a);
  return;
}

