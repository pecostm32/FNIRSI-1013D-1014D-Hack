void FUN_8000bf24(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  ushort *puVar6;
  int iVar7;
  uint uVar8;
  undefined2 *puVar9;
  int iVar10;
  ushort *puVar11;
  uint uVar12;
  
  puVar1 = PTR_DAT_8000c0bc;
  uVar8 = *(uint *)(PTR_DAT_8000c0bc + 4);
  *(ushort *)PTR_DAT_8000c0bc =
       (ushort)(((uVar8 << 0x10) >> 0x1a) << 5) | (ushort)((uVar8 >> 0x13) << 0xb) |
       (ushort)((uVar8 << 0x18) >> 0x1b);
  uVar8 = *(uint *)(puVar1 + 8);
  *(ushort *)(puVar1 + 2) =
       (ushort)((uVar8 << 0x18) >> 0x1b) |
       (ushort)((uVar8 >> 0x13) << 0xb) | (ushort)(((uVar8 << 0x10) >> 0x1a) << 5);
  set_frame_to_global_pointer();
  uVar8 = DAT_8000c0cc;
  iVar4 = DAT_8000c0c8;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8000c0c0;
  if (param_1 == 0) {
    uVar12 = 0;
    do {
      iVar10 = 0x3c;
      puVar6 = (ushort *)(*piVar3 + uVar12 * 0x640 + iVar4);
      puVar11 = (ushort *)(puVar2 + uVar12 * 0x78);
      do {
        uVar5 = *puVar11;
        if (uVar5 == uVar8) {
          uVar5 = *(ushort *)puVar1;
        }
        iVar10 = iVar10 + -1;
        *puVar6 = uVar5;
        puVar6 = puVar6 + 1;
        puVar11 = puVar11 + 1;
      } while (iVar10 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0x37);
    set_display_color(DAT_8000c0d0);
    FUN_80018e68(0x2e3,0x7d,0x316,0xaf,2);
  }
  else {
    set_display_color(*(uint *)(puVar1 + 8));
    FUN_80018ff0(0x2e3,0x7d,0x316,0xaf,2);
    uVar12 = 0;
    do {
      iVar10 = 0x3c;
      puVar9 = (undefined2 *)(*piVar3 + uVar12 * 0x640 + iVar4);
      puVar6 = (ushort *)(puVar2 + uVar12 * 0x78);
      do {
        if (*puVar6 == uVar8) {
          *puVar9 = 0;
        }
        iVar10 = iVar10 + -1;
        puVar9 = puVar9 + 1;
        puVar6 = puVar6 + 1;
      } while (iVar10 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0x37);
  }
  iVar10 = Start_Of_Screen_Mem;
  iVar4 = Screen_Frame_Buffer;
  uVar8 = 0x7b;
  do {
    iVar7 = uVar8 * 800 + 0x2df;
    copy_short((void *)(iVar10 + iVar7 * 2),(void *)(iVar4 + iVar7 * 2),0x40);
    uVar8 = uVar8 + 1;
  } while (uVar8 < 0xb2);
  return;
}

