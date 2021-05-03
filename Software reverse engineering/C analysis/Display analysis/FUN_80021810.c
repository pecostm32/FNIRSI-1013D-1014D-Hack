void FUN_80021810(void)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int *piVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  short *psVar13;
  int iVar14;
  undefined2 *puVar15;
  
  uVar5 = FUN_800232b4(DAT_80021a54);
  FUN_80019730(PTR_PTR_FUN_80021a58);
  FUN_80021168();
  FUN_8002098c();
  FUN_800197c8(2);
  uVar10 = 0;
  uVar11 = 0;
  while( true ) {
    while( true ) {
      iVar9 = DAT_80021a5c;
      iVar12 = uVar10 * 5 + uVar11;
      if (*(char *)(DAT_80021a5c + iVar12) == '\0') {
        return;
      }
      set_display_color(0);
      iVar14 = uVar10 * -0x1b;
      iVar3 = uVar11 * 0x91;
      sVar1 = (short)iVar3;
      sVar2 = (short)iVar14;
      display_clear_rect(sVar1 + 2,sVar2 + 0x1c4,sVar1 + 0x92,sVar2 + 0x1de);
      set_display_color(DAT_80021a60);
      FUN_80018ff0(iVar3 + 3,iVar14 + 0x1c5,iVar3 + 0x91,iVar14 + 0x1dd);
      if (*(byte *)(iVar9 + iVar12) < 0xd) {
        set_display_color(DAT_80021a64);
        display_clear_rect(sVar1 + 6,sVar2 + 0x1c8,sVar1 + 0x18,sVar2 + 0x1da);
        set_display_color(0);
        uVar6 = 0x31;
      }
      else {
        set_display_color(DAT_80021a68);
        display_clear_rect(sVar1 + 6,sVar2 + 0x1c8,sVar1 + 0x18,sVar2 + 0x1da);
        set_display_color(0);
        uVar6 = 0x32;
      }
      FUN_80018a08(uVar6,(iVar3 + 0xc) * 0x10000 >> 0x10,(iVar14 + 0x1ca) * 0x10000 >> 0x10);
      iVar14 = DAT_80021a74;
      piVar4 = Global_Frame_Buffer_Pointer;
      iVar8 = uVar10 * DAT_80021a6c;
      uVar7 = 0;
      iVar9 = iVar9 + iVar12 * 4;
      do {
        iVar12 = 0x34;
        puVar15 = (undefined2 *)(*piVar4 + (uVar7 * 800 + iVar8 * 0x20 + iVar3) * 2 + iVar14);
        psVar13 = (short *)(*(int *)(iVar9 + 0x78) + uVar7 * 0x68);
        do {
          if (*psVar13 != 0) {
            *puVar15 = uVar5;
          }
          iVar12 = iVar12 + -1;
          puVar15 = puVar15 + 1;
          psVar13 = psVar13 + 1;
        } while (iVar12 != 0);
        uVar7 = uVar7 + 1 & 0xfffeffff;
      } while (uVar7 < 0x10);
      set_display_color(DAT_80021a54);
      display_text(*(char **)(iVar9 + 0x18),sVar1 + 0x55,sVar2 + 0x1cb);
      uVar11 = uVar11 + 1 & 0xfffeffff;
      if (4 < uVar11) break;
      if (uVar11 == 4 && uVar10 == 4) {
        return;
      }
    }
    uVar10 = uVar10 + 1 & 0xfffeffff;
    if (4 < uVar10) break;
    uVar11 = 0;
  }
  return;
}


