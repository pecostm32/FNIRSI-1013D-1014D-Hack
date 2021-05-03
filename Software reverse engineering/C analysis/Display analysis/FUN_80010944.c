void FUN_80010944(int param_1)

{
  int *piVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  ushort *puVar5;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  int iVar9;
  ushort uVar10;
  
  set_frame_to_global_pointer();
  puVar3 = PTR_DAT_80010a2c;
  puVar2 = PTR_DAT_80010a28;
  piVar1 = Global_Frame_Buffer_Pointer;
  if (param_1 == 0) {
    uVar8 = 0;
    do {
      memcpy((void *)(*piVar1 + uVar8 * 0x640 + 0x4bce),puVar3 + uVar8 * 0x44,0x44);
      uVar8 = uVar8 + 1 & 0xfffeffff;
    } while (uVar8 < 0x12);
  }
  else {
    uVar8 = 0;
    do {
      iVar9 = 0x22;
      puVar5 = (ushort *)(*piVar1 + uVar8 * 0x640 + 0x4bce);
      puVar7 = (ushort *)(puVar2 + uVar8 * 0x44);
      do {
        uVar10 = 0xf800;
        if (*puVar7 != 0) {
          uVar10 = ~*puVar7;
        }
        iVar9 = iVar9 + -1;
        *puVar5 = uVar10;
        puVar5 = puVar5 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar9 != 0);
      uVar8 = uVar8 + 1 & 0xfffeffff;
    } while (uVar8 < 0x12);
  }
  iVar4 = Start_Of_Screen_Mem;
  iVar9 = Screen_Frame_Buffer;
  uVar8 = 10;
  do {
    iVar6 = uVar8 * 800 + 0x62;
    copy_short((void *)(iVar4 + iVar6 * 2),(void *)(iVar9 + iVar6 * 2),0x2d);
    uVar8 = uVar8 + 1;
  } while (uVar8 < 0x20);
  return;
}

