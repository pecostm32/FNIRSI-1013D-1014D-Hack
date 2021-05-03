void FUN_80010bd0(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  ushort uVar6;
  ushort uVar7;
  uint uVar8;
  int iVar9;
  ushort *puVar10;
  uint uVar11;
  int iVar12;
  ushort uVar13;
  uint uVar14;
  ushort *puVar15;
  
  uVar5 = FUN_800232b4(DAT_80010ce4);
  uVar6 = FUN_800232b4(0);
  uVar7 = FUN_800232b4(0xffffff);
  uVar8 = DAT_80010cf4;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80010cec;
  puVar1 = PTR_DAT_80010ce8;
  uVar11 = 0;
  do {
    iVar12 = 0xf4;
    puVar10 = (ushort *)(puVar1 + uVar11 * 0x1e8);
    puVar15 = (ushort *)
              (*piVar3 +
              ((uint)*(ushort *)(puVar2 + 4) + (*(ushort *)(puVar2 + 6) + uVar11) * 800) * 2);
    do {
      uVar14 = (uint)*puVar10;
      uVar13 = uVar5;
      if (((uVar14 != 0) && (uVar13 = uVar6, uVar14 != 0xf800)) &&
         (uVar13 = *puVar10, uVar14 == uVar8)) {
        uVar13 = uVar7;
      }
      iVar12 = iVar12 + -1;
      *puVar15 = uVar13;
      puVar10 = puVar10 + 1;
      puVar15 = puVar15 + 1;
    } while (iVar12 != 0);
    uVar11 = uVar11 + 1 & 0xfffeffff;
  } while (uVar11 < DAT_80010cf8);
  set_display_color(DAT_80010cfc);
  FUN_80018da0((uint)*(ushort *)(puVar2 + 4),(uint)*(ushort *)(puVar2 + 6),
               *(ushort *)(puVar2 + 4) + 0xf3,*(ushort *)(puVar2 + 6) + 0x125);
  FUN_800117a8(0);
  FUN_800114f4(0);
  FUN_80010d00();
  FUN_80011c3c();
  FUN_800118f4();
  iVar4 = Start_Of_Screen_Mem;
  iVar12 = Screen_Frame_Buffer;
  uVar11 = (uint)*(ushort *)(puVar2 + 6);
  uVar8 = (uint)*(ushort *)(puVar2 + 4);
  uVar14 = uVar11 + 0x126 & 0xfffeffff;
  if (uVar14 <= uVar11) {
    return;
  }
  do {
    iVar9 = uVar8 + uVar11 * 800;
    copy_short((void *)(iVar4 + iVar9 * 2),(void *)(iVar12 + iVar9 * 2),
               ((uVar8 + 0xf3 & 0xfffeffff) - uVar8) + 1);
    uVar11 = uVar11 + 1;
  } while (uVar11 < uVar14);
  return;
}


