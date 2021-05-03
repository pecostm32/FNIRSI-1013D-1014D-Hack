void FUN_8002c5b8(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  int *piVar6;
  int iVar7;
  uint uVar8;
  ushort uVar9;
  ushort uVar10;
  uint uVar11;
  ushort *puVar12;
  int iVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  ushort uVar17;
  ushort *puVar18;
  uint local_38;
  
  uVar15 = 0;
  local_38 = 0;
  uVar9 = FUN_800232b4(0xffffff);
  uVar10 = FUN_800232b4(0x88);
  uVar1 = *(ushort *)(DAT_8002c780 + 2);
  uVar2 = *(ushort *)(DAT_8002c780 + 4);
  uVar3 = *(ushort *)(DAT_8002c780 + 6);
  uVar4 = *(ushort *)(DAT_8002c780 + 8);
  set_frame_to_global_pointer();
  piVar6 = Global_Frame_Buffer_Pointer;
  iVar13 = Screen_Frame_Buffer_2;
  uVar16 = 0;
  do {
    memcpy((void *)(*piVar6 + uVar16 * 0x640),(void *)(iVar13 + uVar16 * 0x640),DAT_8002c78c);
    uVar8 = DAT_8002c794;
    iVar7 = DAT_8002c790;
    uVar16 = uVar16 + 1 & 0xfffeffff;
  } while (uVar16 < 0x1e0);
  uVar16 = 0;
  do {
    uVar14 = 0;
    do {
      if (*(char *)(DAT_8002c780 + uVar15 + 0xd) != '\0') {
        local_38 = (uint)*(byte *)(DAT_8002c780 + 10) * 0x10 + -0x10 + uVar15 & 0xffff;
        if (*(byte *)(DAT_8002c780 + 0xc) <= local_38) break;
        uVar11 = 0;
        do {
          iVar13 = 0x1e;
          puVar12 = (ushort *)(PTR_DAT_8002c798 + uVar11 * 0x78);
          puVar18 = (ushort *)
                    (*Global_Frame_Buffer_Pointer +
                     ((uint)uVar3 + (uVar11 + uVar4 + uVar16) * 800 + uVar14) * 2 + iVar7);
          do {
            uVar5 = *puVar12;
            uVar17 = uVar10;
            if ((uVar5 != 0) && (uVar17 = uVar5, uVar5 == uVar8)) {
              uVar17 = uVar9;
            }
            iVar13 = iVar13 + -1;
            *puVar18 = uVar17;
            puVar12 = puVar12 + 2;
            puVar18 = puVar18 + 1;
          } while (iVar13 != 0);
          uVar11 = uVar11 + 1 & 0xfffeffff;
        } while (uVar11 < 0x1e);
      }
      uVar14 = (uint)uVar1 + (uint)uVar3 + uVar14 & 0xfffcffff;
      uVar15 = uVar15 + 1 & 0xff;
    } while (uVar14 < 700);
    if ((*(byte *)(DAT_8002c780 + 0xc) <= local_38) ||
       (uVar16 = (uint)uVar2 + (uint)uVar4 + uVar16 & 0xfffcffff, DAT_8002c79c <= uVar16)) {
      FUN_8001cccc(0,0,DAT_8002c7a0 + 0xfa);
      *Global_Frame_Buffer_Pointer = Start_Of_Screen_Mem;
      return;
    }
  } while( true );
}

