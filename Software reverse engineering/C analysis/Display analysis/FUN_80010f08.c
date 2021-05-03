void FUN_80010f08(void)

{
  ushort uVar1;
  ushort uVar2;
  undefined *puVar3;
  undefined *puVar4;
  int *piVar5;
  int iVar6;
  short sVar7;
  short sVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  undefined *puVar13;
  ushort *puVar14;
  short *psVar15;
  int iVar16;
  short *psVar17;
  uint uVar18;
  ushort *puVar19;
  short sVar20;
  
  sVar7 = FUN_800232b4(DAT_8001112c);
  sVar8 = FUN_800232b4(DAT_80011130);
  piVar5 = Global_Frame_Buffer_Pointer;
  puVar4 = PTR_DAT_8001113c;
  puVar3 = PTR_DAT_80011138;
  iVar10 = DAT_80011134;
  uVar9 = 0;
  do {
    iVar16 = 0xc5;
    psVar15 = (short *)(puVar3 + uVar9 * 0x18a);
    psVar17 = (short *)(*piVar5 + ((uint)*(ushort *)(puVar4 + 4) +
                                  (*(ushort *)(puVar4 + 6) + uVar9) * 800) * 2 + iVar10);
    do {
      sVar20 = *psVar15;
      if (*psVar15 == 0) {
        sVar20 = sVar7;
      }
      iVar16 = iVar16 + -1;
      *psVar17 = sVar20;
      iVar6 = DAT_8001114c;
      iVar11 = DAT_80011148;
      psVar15 = psVar15 + 1;
      psVar17 = psVar17 + 1;
    } while (iVar16 != 0);
    uVar9 = uVar9 + 1 & 0xfffeffff;
  } while (uVar9 < 0x3c);
  if (*(char *)(DAT_80011144 + 9) == '\0') {
    uVar9 = 8;
    do {
      iVar10 = 0x42;
      psVar15 = (short *)(*piVar5 + ((uint)*(ushort *)(puVar4 + 4) +
                                    (*(ushort *)(puVar4 + 6) + uVar9) * 800) * 2 + iVar6);
      psVar17 = (short *)(puVar3 + uVar9 * 0x18a + 0xf4);
      do {
        sVar7 = *psVar17;
        if (*psVar17 == 0) {
          sVar7 = sVar8;
        }
        iVar10 = iVar10 + -1;
        *psVar15 = sVar7;
        psVar15 = psVar15 + 1;
        psVar17 = psVar17 + 1;
      } while (iVar10 != 0);
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0x34);
  }
  else {
    uVar9 = 8;
    do {
      iVar16 = uVar9 * 0xc5;
      puVar13 = puVar3 + uVar9 * 0x18a;
      puVar19 = (ushort *)
                (*piVar5 + ((uint)*(ushort *)(puVar4 + 4) + (*(ushort *)(puVar4 + 6) + uVar9) * 800)
                           * 2 + iVar11 + 2);
      *puVar19 = ~*(ushort *)(puVar13 + 0xf4);
      uVar1 = *(ushort *)(puVar13 + 0xf6);
      iVar10 = 0x20;
      puVar14 = (ushort *)(puVar13 + 0xf4);
      do {
        uVar2 = puVar14[2];
        puVar19[1] = ~uVar1;
        uVar1 = puVar14[3];
        iVar10 = iVar10 + -1;
        puVar19 = puVar19 + 2;
        *puVar19 = ~uVar2;
        puVar14 = puVar14 + 2;
      } while (iVar10 != 0);
      iVar10 = *(ushort *)(puVar4 + 6) + uVar9;
      uVar9 = uVar9 + 1 & 0xfffeffff;
      *(ushort *)(*piVar5 + (iVar10 * 800 + 0x41 + (uint)*(ushort *)(puVar4 + 4)) * 2 + 0x4489c) =
           ~*(ushort *)(puVar3 + (iVar16 + 0x41) * 2 + 0xf4);
    } while (uVar9 < 0x34);
  }
  set_display_color(DAT_80011150);
  FUN_80018da0(*(ushort *)(puVar4 + 4) + 0xf4,*(ushort *)(puVar4 + 6) + 0xaf,
               *(ushort *)(puVar4 + 4) + 0x1b8,*(ushort *)(puVar4 + 6) + 0xea);
  iVar16 = Start_Of_Screen_Mem;
  iVar10 = Screen_Frame_Buffer;
  uVar1 = *(ushort *)(puVar4 + 4);
  uVar12 = *(ushort *)(puVar4 + 6) + 0xaf & 0xfffeffff;
  uVar9 = uVar1 + 0xf4 & 0xfffeffff;
  uVar18 = *(ushort *)(puVar4 + 6) + 0xeb & 0xfffeffff;
  if (uVar18 <= uVar12) {
    return;
  }
  do {
    iVar11 = uVar9 + uVar12 * 800;
    copy_short((void *)(iVar16 + iVar11 * 2),(void *)(iVar10 + iVar11 * 2),
               ((uVar1 + 0x1b8 & 0xfffeffff) - uVar9) + 1);
    uVar12 = uVar12 + 1;
  } while (uVar12 < uVar18);
  return;
}


