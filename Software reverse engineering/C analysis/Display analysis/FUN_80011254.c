void FUN_80011254(void)

{
  ushort uVar1;
  undefined *puVar2;
  int *piVar3;
  undefined *puVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  short *psVar8;
  uint uVar9;
  short *psVar10;
  uint uVar11;
  short sVar12;
  uint uVar13;
  int iVar14;
  
  sVar6 = FUN_800232b4(DAT_8001137c);
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80011384;
  iVar14 = DAT_80011380;
  uVar13 = 0;
  do {
    FUN_80000878(*piVar3 + (uint)*(ushort *)(puVar2 + 4) * 2 +
                           (*(ushort *)(puVar2 + 6) + uVar13) * 0x640 + iVar14,0xae);
    iVar5 = DAT_80011390;
    puVar4 = PTR_DAT_8001138c;
    uVar13 = uVar13 + 1 & 0xfffeffff;
  } while (uVar13 < 0x3c);
  uVar13 = 0;
  do {
    iVar14 = 0x6e;
    psVar8 = (short *)(*piVar3 + ((uint)*(ushort *)(puVar2 + 4) +
                                 (*(ushort *)(puVar2 + 6) + uVar13) * 800) * 2 + iVar5);
    psVar10 = (short *)(puVar4 + uVar13 * 0xdc);
    do {
      sVar12 = *psVar10;
      if (*psVar10 == 0) {
        sVar12 = sVar6;
      }
      iVar14 = iVar14 + -1;
      *psVar8 = sVar12;
      psVar8 = psVar8 + 1;
      psVar10 = psVar10 + 1;
    } while (iVar14 != 0);
    uVar13 = uVar13 + 1 & 0xfffeffff;
  } while (uVar13 < 0x3c);
  set_display_color(DAT_80011394);
  FUN_80018da0(*(ushort *)(puVar2 + 4) + 0xf4,*(ushort *)(puVar2 + 6) + 0xaf,
               *(ushort *)(puVar2 + 4) + 0x162,*(ushort *)(puVar2 + 6) + 0xea);
  iVar5 = Start_Of_Screen_Mem;
  iVar14 = Screen_Frame_Buffer;
  uVar1 = *(ushort *)(puVar2 + 4);
  uVar11 = *(ushort *)(puVar2 + 6) + 0xeb & 0xfffeffff;
  uVar9 = *(ushort *)(puVar2 + 6) + 0xaf & 0xfffeffff;
  uVar13 = uVar1 + 0xf4 & 0xfffeffff;
  if (uVar11 <= uVar9) {
    return;
  }
  do {
    iVar7 = uVar13 + uVar9 * 800;
    copy_short((void *)(iVar5 + iVar7 * 2),(void *)(iVar14 + iVar7 * 2),
               ((uVar1 + 0x162 & 0xfffeffff) - uVar13) + 1);
    uVar9 = uVar9 + 1;
  } while (uVar9 < uVar11);
  return;
}

