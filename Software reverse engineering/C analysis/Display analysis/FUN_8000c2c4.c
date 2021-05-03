void FUN_8000c2c4(int param_1,int param_2)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  short *psVar7;
  int iVar8;
  short *psVar9;
  short sVar10;
  ushort *puVar11;
  ushort *puVar12;
  int count;
  int iVar13;
  uint uVar14;
  
  puVar1 = PTR_DAT_8000c490;
  uVar6 = *(uint *)(PTR_DAT_8000c490 + 4);
  *(ushort *)PTR_DAT_8000c490 =
       (ushort)(((uVar6 << 0x10) >> 0x1a) << 5) | (ushort)((uVar6 >> 0x13) << 0xb) |
       (ushort)((uVar6 << 0x18) >> 0x1b);
  uVar6 = *(uint *)(puVar1 + 8);
  *(ushort *)(puVar1 + 2) =
       (ushort)((uVar6 >> 0x13) << 0xb) | (ushort)(((uVar6 << 0x10) >> 0x1a) << 5) |
       (ushort)((uVar6 << 0x18) >> 0x1b);
  set_frame_to_global_pointer();
  iVar4 = DAT_8000c4a0;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8000c498;
  uVar6 = DAT_8000c494;
  uVar14 = 0;
  do {
    iVar13 = 0x3c;
    puVar11 = (ushort *)(*piVar3 + uVar14 * 0x640 + iVar4);
    puVar12 = (ushort *)(puVar2 + uVar14 * 0x78);
    do {
      uVar5 = *puVar12;
      if (uVar5 == uVar6) {
        uVar5 = *(ushort *)puVar1;
      }
      iVar13 = iVar13 + -1;
      *puVar11 = uVar5;
      puVar11 = puVar11 + 1;
      puVar12 = puVar12 + 1;
    } while (iVar13 != 0);
    uVar14 = uVar14 + 1 & 0xfffeffff;
  } while (uVar14 < 0xb0);
  set_display_color(0);
  FUN_800197c8(2);
  FUN_80019730(PTR_PTR_FUN_8000c4a4);
  display_text(&DAT_8000c4ac,(ushort)DAT_8000c4a8,0x144);
  if (param_1 == 0) {
    if (param_2 != 0) {
      uVar6 = 0xf;
      do {
        iVar13 = 0x3c;
        psVar7 = (short *)(*piVar3 + uVar6 * 0x640 + iVar4);
        psVar9 = (short *)(puVar2 + uVar6 * 0x78);
        do {
          sVar10 = *psVar9;
          if (sVar10 == 0) {
            sVar10 = *(short *)(puVar1 + 2);
          }
          iVar13 = iVar13 + -1;
          *psVar7 = sVar10;
          psVar7 = psVar7 + 1;
          psVar9 = psVar9 + 1;
        } while (iVar13 != 0);
        uVar6 = uVar6 + 1 & 0xfffeffff;
      } while (uVar6 < 0x4c);
    }
  }
  else {
    if (param_2 != 0) {
      uVar6 = 100;
      do {
        iVar13 = 0x3c;
        psVar7 = (short *)(puVar2 + uVar6 * 0x78);
        psVar9 = (short *)(*piVar3 + uVar6 * 0x640 + iVar4);
        do {
          sVar10 = *psVar7;
          if (sVar10 == 0) {
            sVar10 = *(short *)(puVar1 + 2);
          }
          iVar13 = iVar13 + -1;
          *psVar9 = sVar10;
          psVar7 = psVar7 + 1;
          psVar9 = psVar9 + 1;
        } while (iVar13 != 0);
        uVar6 = uVar6 + 1 & 0xfffeffff;
      } while (uVar6 < 0xa1);
    }
  }
  iVar13 = Start_Of_Screen_Mem;
  iVar4 = Screen_Frame_Buffer;
  uVar6 = DAT_8000c4b0;
  uVar14 = 0xf3;
  count = DAT_8000c4b4 + -0x2de;
  if (DAT_8000c4b0 < 0xf4) {
    return;
  }
  do {
    iVar8 = uVar14 * 800 + 0x2df;
    copy_short((void *)(iVar13 + iVar8 * 2),(void *)(iVar4 + iVar8 * 2),count);
    uVar14 = uVar14 + 1;
  } while (uVar14 < uVar6);
  return;
}

