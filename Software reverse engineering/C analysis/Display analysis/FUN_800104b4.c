void FUN_800104b4(int param_1)

{
  int iVar1;
  int iVar2;
  ushort *puVar3;
  uint uVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  bool bVar8;
  
  set_frame_to_global_pointer();
  uVar4 = 0;
  bVar8 = *(char *)(DAT_800105d0 + 0x16) == '\0';
  puVar6 = PTR_DAT_800105d8;
  if (bVar8) {
    puVar6 = PTR_DAT_800105dc;
  }
  iVar5 = *Global_Frame_Buffer_Pointer;
  if (bVar8) {
    do {
      iVar2 = 0;
      iVar1 = 0x28;
      puVar3 = (ushort *)(puVar6 + uVar4 * 0x50);
      do {
        iVar7 = iVar2 + uVar4 * 800;
        if (param_1 == 0) {
          *(ushort *)(iVar5 + iVar7 * 2 + 0x2318) = *puVar3;
        }
        else {
          *(ushort *)(iVar5 + iVar7 * 2 + 0x2318) = ~*puVar3;
        }
        iVar1 = iVar1 + -1;
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 1;
      } while (iVar1 != 0);
      uVar4 = uVar4 + 1 & 0xfffeffff;
    } while (uVar4 < 0x24);
  }
  else {
    do {
      iVar2 = 0;
      iVar1 = 0x28;
      puVar3 = (ushort *)(puVar6 + uVar4 * 0x50);
      do {
        iVar7 = iVar2 + uVar4 * 800;
        if (param_1 == 0) {
          *(ushort *)(iVar5 + iVar7 * 2 + 0x2318) = *puVar3;
        }
        else {
          *(ushort *)(iVar5 + iVar7 * 2 + 0x2318) = ~*puVar3;
        }
        iVar1 = iVar1 + -1;
        iVar2 = iVar2 + 1;
        puVar3 = puVar3 + 1;
      } while (iVar1 != 0);
      uVar4 = uVar4 + 1 & 0xfffeffff;
    } while (uVar4 < 0x24);
  }
  iVar1 = Start_Of_Screen_Mem;
  iVar5 = Screen_Frame_Buffer;
  uVar4 = 5;
  do {
    iVar2 = uVar4 * 800 + 0x1ec;
    copy_short((void *)(iVar1 + iVar2 * 2),(void *)(iVar5 + iVar2 * 2),0x29);
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x29);
  return;
}

