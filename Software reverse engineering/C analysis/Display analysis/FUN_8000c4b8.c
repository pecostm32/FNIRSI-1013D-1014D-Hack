void FUN_8000c4b8(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  int iVar8;
  undefined2 *puVar9;
  int iVar10;
  
  set_frame_to_global_pointer();
  puVar1 = PTR_DAT_8000c678;
  uVar5 = *(uint *)(PTR_DAT_8000c678 + 4);
  *(ushort *)PTR_DAT_8000c678 =
       (ushort)(((uVar5 << 0x10) >> 0x1a) << 5) | (ushort)((uVar5 >> 0x13) << 0xb) |
       (ushort)((uVar5 << 0x18) >> 0x1b);
  uVar5 = DAT_8000c684;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8000c67c;
  uVar6 = *(uint *)(puVar1 + 8);
  *(ushort *)(puVar1 + 2) =
       (ushort)((uVar6 >> 0x13) << 0xb) | (ushort)(((uVar6 << 0x10) >> 0x1a) << 5) |
       (ushort)((uVar6 << 0x18) >> 0x1b);
  if (param_1 == 0) {
    set_display_color(DAT_8000c688);
    FUN_80018ff0(0x2e3,5,0x316,0x37,2);
    set_display_color(DAT_8000c68c);
    FUN_80018e68(0x2e3,5,0x316,0x37,2);
    uVar6 = 0;
    do {
      iVar10 = 0x3c;
      puVar9 = (undefined2 *)(*piVar3 + uVar6 * 0x640 + 0x187e);
      puVar7 = (ushort *)(puVar2 + uVar6 * 0x78);
      do {
        if (*puVar7 == uVar5) {
          *puVar9 = *(undefined2 *)puVar1;
        }
        iVar10 = iVar10 + -1;
        puVar9 = puVar9 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar10 != 0);
      uVar6 = uVar6 + 1 & 0xfffeffff;
    } while (uVar6 < 0x37);
  }
  else {
    set_display_color(uVar6);
    FUN_80018ff0(0x2e3,5,0x316,0x37,2);
    uVar6 = 0;
    do {
      iVar10 = 0x3c;
      puVar9 = (undefined2 *)(*piVar3 + uVar6 * 0x640 + 0x187e);
      puVar7 = (ushort *)(puVar2 + uVar6 * 0x78);
      do {
        if (*puVar7 == uVar5) {
          *puVar9 = 0;
        }
        iVar10 = iVar10 + -1;
        puVar9 = puVar9 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar10 != 0);
      uVar6 = uVar6 + 1 & 0xfffeffff;
    } while (uVar6 < 0x37);
  }
  iVar4 = Start_Of_Screen_Mem;
  iVar10 = Screen_Frame_Buffer;
  uVar5 = 3;
  do {
    iVar8 = uVar5 * 800 + 0x2df;
    copy_short((void *)(iVar4 + iVar8 * 2),(void *)(iVar10 + iVar8 * 2),0x40);
    uVar5 = uVar5 + 1;
  } while (uVar5 < 0x3a);
  return;
}

