void FUN_8000d0ec(int param_1)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined *puVar3;
  int *piVar4;
  int iVar5;
  ushort uVar6;
  ushort *puVar7;
  int iVar8;
  uint uVar9;
  undefined2 *puVar10;
  ushort *puVar11;
  uint uVar12;
  int iVar13;
  int count;
  
  puVar1 = PTR_DAT_8000d284;
  uVar9 = *(uint *)(PTR_DAT_8000d284 + 4);
  *(ushort *)PTR_DAT_8000d284 =
       (ushort)(((uVar9 << 0x10) >> 0x1a) << 5) | (ushort)((uVar9 >> 0x13) << 0xb) |
       (ushort)((uVar9 << 0x18) >> 0x1b);
  uVar9 = *(uint *)(puVar1 + 8);
  *(ushort *)(puVar1 + 2) =
       (ushort)((uVar9 << 0x18) >> 0x1b) |
       (ushort)((uVar9 >> 0x13) << 0xb) | (ushort)(((uVar9 << 0x10) >> 0x1a) << 5);
  set_frame_to_global_pointer();
  uVar9 = DAT_8000d298;
  iVar5 = DAT_8000d294;
  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_DAT_8000d28c;
  uVar2 = DAT_8000d288;
  if (param_1 == 0) {
    uVar12 = 0;
    do {
      iVar13 = 0x3c;
      puVar7 = (ushort *)(*piVar4 + uVar12 * 0x640 + iVar5);
      puVar11 = (ushort *)(puVar3 + uVar12 * 0x78);
      do {
        uVar6 = *puVar11;
        if (uVar6 == uVar9) {
          uVar6 = *(ushort *)puVar1;
        }
        iVar13 = iVar13 + -1;
        *puVar7 = uVar6;
        puVar7 = puVar7 + 1;
        puVar11 = puVar11 + 1;
      } while (iVar13 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0x37);
    set_display_color(DAT_8000d2a0);
    FUN_80018e68(DAT_8000d29c,0xf5,0x316,uVar2,2);
  }
  else {
    set_display_color(*(uint *)(puVar1 + 8));
    FUN_80018ff0(DAT_8000d29c,0xf5,0x316,uVar2,2);
    uVar12 = 0;
    do {
      iVar13 = 0x3c;
      puVar10 = (undefined2 *)(*piVar4 + uVar12 * 0x640 + iVar5);
      puVar7 = (ushort *)(puVar3 + uVar12 * 0x78);
      do {
        if (*puVar7 == uVar9) {
          *puVar10 = 0;
        }
        iVar13 = iVar13 + -1;
        puVar10 = puVar10 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar13 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0x37);
  }
  iVar13 = Start_Of_Screen_Mem;
  iVar5 = Screen_Frame_Buffer;
  uVar9 = DAT_8000d2a4;
  uVar12 = 0xf3;
  count = DAT_8000d2a4 - 0xea;
  if (DAT_8000d2a4 < 0xf4) {
    return;
  }
  do {
    iVar8 = uVar12 * 800 + 0x2df;
    copy_short((void *)(iVar13 + iVar8 * 2),(void *)(iVar5 + iVar8 * 2),count);
    uVar12 = uVar12 + 1;
  } while (uVar12 < uVar9);
  return;
}


