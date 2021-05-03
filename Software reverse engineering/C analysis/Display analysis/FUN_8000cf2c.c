void FUN_8000cf2c(int param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int *piVar4;
  int iVar5;
  ushort uVar6;
  ushort *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined2 *puVar12;
  ushort *puVar13;
  uint uVar14;
  int iVar15;
  
  puVar1 = PTR_DAT_8000d0c4;
  uVar11 = *(uint *)(PTR_DAT_8000d0c4 + 4);
  *(ushort *)PTR_DAT_8000d0c4 =
       (ushort)((uVar11 << 0x18) >> 0x1b) |
       (ushort)(((uVar11 << 0x10) >> 0x1a) << 5) | (ushort)((uVar11 >> 0x13) << 0xb);
  uVar11 = *(uint *)(puVar1 + 8);
  *(ushort *)(puVar1 + 2) =
       (ushort)((uVar11 >> 0x13) << 0xb) | (ushort)(((uVar11 << 0x10) >> 0x1a) << 5) |
       (ushort)((uVar11 << 0x18) >> 0x1b);
  set_frame_to_global_pointer();
  uVar11 = DAT_8000d0d8;
  iVar5 = DAT_8000d0d4;
  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_DAT_8000d0cc;
  uVar2 = DAT_8000d0c8;
  if (param_1 == 0) {
    uVar14 = 0;
    do {
      iVar15 = 0x3c;
      puVar7 = (ushort *)(*piVar4 + uVar14 * 0x640 + iVar5);
      puVar13 = (ushort *)(puVar3 + uVar14 * 0x78);
      do {
        uVar6 = *puVar13;
        if (uVar6 == uVar11) {
          uVar6 = *(ushort *)puVar1;
        }
        iVar15 = iVar15 + -1;
        *puVar7 = uVar6;
        puVar7 = puVar7 + 1;
        puVar13 = puVar13 + 1;
      } while (iVar15 != 0);
      uVar14 = uVar14 + 1 & 0xfffeffff;
    } while (uVar14 < 0x37);
    set_display_color(DAT_8000d0e4);
    FUN_80018e68(DAT_8000d0e0,DAT_8000d0dc,0x316,uVar2,2);
  }
  else {
    set_display_color(*(uint *)(puVar1 + 8));
    FUN_80018ff0(DAT_8000d0e0,DAT_8000d0dc,0x316,uVar2,2);
    uVar14 = 0;
    do {
      iVar15 = 0x3c;
      puVar12 = (undefined2 *)(*piVar4 + uVar14 * 0x640 + iVar5);
      puVar7 = (ushort *)(puVar3 + uVar14 * 0x78);
      do {
        if (*puVar7 == uVar11) {
          *puVar12 = *(undefined2 *)(puVar1 + 2);
        }
        iVar15 = iVar15 + -1;
        puVar12 = puVar12 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar15 != 0);
      uVar14 = uVar14 + 1 & 0xfffeffff;
    } while (uVar14 < 0x37);
  }
  iVar15 = Start_Of_Screen_Mem;
  iVar5 = Screen_Frame_Buffer;
  uVar11 = DAT_8000d0e8;
  uVar14 = DAT_8000d0e8 - 0x37;
  iVar8 = DAT_8000d0e8 + 0x101;
  iVar9 = DAT_8000d0e8 - iVar8;
  if (DAT_8000d0e8 <= uVar14) {
    return;
  }
  do {
    iVar10 = iVar8 + uVar14 * 800;
    copy_short((void *)(iVar15 + iVar10 * 2),(void *)(iVar5 + iVar10 * 2),iVar9 + 0x141);
    uVar14 = uVar14 + 1;
  } while (uVar14 < uVar11);
  return;
}

