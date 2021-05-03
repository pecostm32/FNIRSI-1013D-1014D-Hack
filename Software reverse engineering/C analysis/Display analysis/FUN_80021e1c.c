void FUN_80021e1c(void)

{
  ulonglong uVar1;
  ushort xsize;
  int iVar2;
  undefined *puVar3;
  int *piVar4;
  char *pcVar5;
  undefined4 uVar6;
  ushort *puVar7;
  int iVar8;
  uint uVar9;
  undefined2 *puVar10;
  uint uVar11;
  int iVar12;
  uint uVar13;
  uint uVar14;
  short sVar15;
  uint uVar16;
  undefined4 unaff_r4;
  short sVar17;
  short *psVar18;
  int iVar19;
  short *psVar20;
  
  FUN_8001c6f0(DAT_80021edc + -0xc0,5,DAT_80021edc,0xe8);
  set_screen_to_global_pointer();
  sVar15 = (short)DAT_80021ee0;
  set_screen_to_global_pointer();
  uVar16 = DAT_80021ef0;
  iVar2 = DAT_80021eec;
  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_DAT_80021ee4;
  uVar13 = 0xba;
  do {
    uVar9 = uVar13 & 0xffff;
    while (uVar9 < 0xba) {
      iVar12 = 0xac;
      psVar18 = (short *)((*piVar4 + (uVar9 - uVar13) * 0x640) - iVar2);
      psVar20 = (short *)(puVar3 + uVar9 * 0x158);
      do {
        sVar17 = *psVar20;
        if (*psVar20 == 0) {
          sVar17 = sVar15;
        }
        iVar12 = iVar12 + -1;
        *psVar18 = sVar17;
        psVar18 = psVar18 + 1;
        psVar20 = psVar20 + 1;
      } while (iVar12 != 0);
      uVar9 = uVar9 + 1 & 0xfffeffff;
    }
    uVar1 = (ulonglong)uVar13;
    iVar12 = uVar13 - (uint)(uVar1 * uVar16 >> 0x24);
    uVar13 = iVar12 - 1;
  } while (uVar13 != 0);
  FUN_8001cfb8(iVar12,(int)(uVar1 * uVar16));
  FUN_8001cfb8();
  uVar16 = DAT_80016394;
  uVar9 = 0;
  set_frame_to_global_pointer();
  piVar4 = Global_Frame_Buffer_Pointer;
  iVar2 = DAT_8001639c;
  puVar3 = PTR_DAT_80016398;
  uVar13 = 0;
  do {
    iVar12 = 0xac;
    puVar10 = (undefined2 *)((*piVar4 + uVar13 * 0x640) - iVar2);
    puVar7 = (ushort *)(puVar3 + uVar13 * 0x158);
    do {
      uVar14 = (uint)*puVar7;
      if (*puVar7 == 0) {
        uVar14 = uVar16;
      }
      iVar12 = iVar12 + -1;
      *puVar10 = (short)uVar14;
      iVar19 = DAT_800163a4;
      puVar10 = puVar10 + 1;
      puVar7 = puVar7 + 1;
    } while (iVar12 != 0);
    uVar13 = uVar13 + 1 & 0xfffeffff;
  } while (uVar13 < 0xba);
  if (*(char *)(DAT_800163a4 + 0x21) == '\0') {
    uVar14 = 0x39;
    uVar13 = DAT_800163a8 - 0x276;
    do {
      puVar7 = (ushort *)(*piVar4 + (uVar14 * 800 + 5) * 2 + 0x4da);
      uVar11 = uVar13 & 0xffff;
      do {
        if (*puVar7 == uVar16) {
          *puVar7 = 0x7e0;
        }
        else {
          *puVar7 = 0;
        }
        uVar11 = uVar11 - 1 & 0xffff;
        puVar7 = puVar7 + 1;
      } while (uVar11 != 0);
      uVar14 = uVar14 + 1 & 0xfffeffff;
    } while (uVar14 < 0x61);
  }
  else {
    if (*(char *)(DAT_800163a4 + 0x21) == '\x01') {
      uVar14 = 0x39;
      uVar13 = DAT_800163ac - 0x296;
      do {
        puVar7 = (ushort *)(*piVar4 + (uVar14 * 800 + 5) * 2 + 0x51a);
        uVar11 = uVar13 & 0xffff;
        do {
          if (*puVar7 == uVar16) {
            *puVar7 = 0x7e0;
          }
          else {
            *puVar7 = 0;
          }
          uVar11 = uVar11 - 1 & 0xffff;
          puVar7 = puVar7 + 1;
        } while (uVar11 != 0);
        uVar14 = uVar14 + 1 & 0xfffeffff;
      } while (uVar14 < 0x61);
    }
    else {
      if (*(char *)(DAT_800163a4 + 0x21) == '\x02') {
        uVar14 = 0x39;
        uVar13 = DAT_800163b0 - 0x2b6;
        do {
          puVar7 = (ushort *)(*piVar4 + (uVar14 * 800 + 5) * 2 + 0x55a);
          uVar11 = uVar13 & 0xffff;
          do {
            if (*puVar7 == uVar16) {
              *puVar7 = 0x7e0;
            }
            else {
              *puVar7 = 0;
            }
            uVar11 = uVar11 - 1 & 0xffff;
            puVar7 = puVar7 + 1;
          } while (uVar11 != 0);
          uVar14 = uVar14 + 1 & 0xfffeffff;
        } while (uVar14 < 0x61);
      }
    }
  }
  if (*(char *)(iVar19 + 0x22) == '\0') {
    uVar14 = 0x7f;
    uVar13 = DAT_800163b4 - 0x271;
    do {
      puVar7 = (ushort *)(*piVar4 + (uVar14 * 800 + 5) * 2 + 0x4d0);
      uVar11 = uVar13 & 0xffff;
      do {
        if (*puVar7 == uVar16) {
          *puVar7 = 0x7e0;
        }
        else {
          *puVar7 = 0;
        }
        uVar11 = uVar11 - 1 & 0xffff;
        puVar7 = puVar7 + 1;
      } while (uVar11 != 0);
      uVar14 = uVar14 + 1 & 0xfffeffff;
    } while (uVar14 < 0x96);
  }
  else {
    uVar13 = 0x7f;
    do {
      puVar7 = (ushort *)(*piVar4 + (uVar13 * 800 + 5) * 2 + 0x530);
      sVar15 = 0x2f;
      do {
        sVar15 = sVar15 + -1;
        if (*puVar7 == uVar16) {
          *puVar7 = 0x7e0;
        }
        else {
          *puVar7 = 0;
        }
        puVar7 = puVar7 + 1;
      } while (sVar15 != 0);
      uVar13 = uVar13 + 1 & 0xfffeffff;
    } while (uVar13 < 0x96);
  }
  if (*(char *)(iVar19 + 0x23) == '\0') {
    uVar14 = 0xbd;
    uVar13 = DAT_800163b8 - 0x274;
    do {
      puVar7 = (ushort *)(*piVar4 + (uVar14 * 800 + 5) * 2 + 0x4d6);
      uVar11 = uVar13 & 0xffff;
      do {
        if (*puVar7 == uVar16) {
          *puVar7 = 0x7e0;
        }
        else {
          *puVar7 = 0;
        }
        uVar11 = uVar11 - 1 & 0xffff;
        puVar7 = puVar7 + 1;
      } while (uVar11 != 0);
      uVar14 = uVar14 + 1 & 0xfffeffff;
    } while (uVar14 < 0xd4);
  }
  else {
    if (*(char *)(iVar19 + 0x23) == '\x01') {
      uVar14 = 0xbd;
      uVar13 = DAT_800163bc - 0x2a4;
      do {
        puVar7 = (ushort *)(*piVar4 + (uVar14 * 800 + 5) * 2 + 0x536);
        uVar11 = uVar13 & 0xffff;
        do {
          if (*puVar7 == uVar16) {
            *puVar7 = 0x7e0;
          }
          else {
            *puVar7 = 0;
          }
          uVar11 = uVar11 - 1 & 0xffff;
          puVar7 = puVar7 + 1;
        } while (uVar11 != 0);
        uVar14 = uVar14 + 1 & 0xfffeffff;
      } while (uVar14 < 0xd4);
    }
  }
  set_display_color(DAT_800163c0);
  iVar2 = DAT_800163c4;
  iVar12 = DAT_800163c4 + -0xab;
  FUN_80018da0(iVar12,0x2e,DAT_800163c4,0xe7,uVar9,unaff_r4);
  set_display_color(uVar9);
  FUN_80018ca8(0x6b,iVar2 + -0xa0,iVar2 + -0xb);
  FUN_80018ca8(0xa9,iVar2 + -0xa0,iVar2 + -0xb);
  FUN_8001cccc(iVar12,0x2e,iVar2 + 1,0xe8);
  set_frame_to_global_pointer();
  set_display_color(0);
  display_clear_rect(0x23a,2,700,0x2c);
  FUN_800197c8(2);
  FUN_80019730(PTR_PTR_FUN_800128dc);
  set_display_color(0xff00);
  display_clear_rect(0x23a,5,600,0x28);
  set_display_color(0);
  display_text(&DAT_800128e0,0x246,0xf);
  set_display_color(0xffffff);
  FUN_80019730(PTR_PTR_FUN_800128e4);
  iVar2 = DAT_800128e8;
  if (*(char *)(DAT_800128e8 + 0x21) == '\0') {
    display_text(&DAT_800128fc,0x25e,7);
  }
  else {
    if (*(char *)(DAT_800128e8 + 0x21) == '\x01') {
      pcVar5 = s_Single_800128ec;
    }
    else {
      if (*(char *)(DAT_800128e8 + 0x21) != '\x02') goto LAB_80012754;
      pcVar5 = s_Normal_800128f4;
    }
    display_text(pcVar5,0x25e,7);
  }
LAB_80012754:
  xsize = (ushort)DAT_80012904;
  if (*(char *)(iVar2 + 0x23) == '\0') {
    set_display_color(DAT_80012908);
    display_clear_rect(xsize - 0x1c,0x19,xsize,0x28);
    set_display_color(0);
    pcVar5 = &DAT_8001290c;
  }
  else {
    if (*(char *)(iVar2 + 0x23) != '\x01') goto LAB_800127e4;
    set_display_color(DAT_80012910);
    display_clear_rect(xsize - 0x1c,0x19,xsize,0x28);
    set_display_color(0);
    pcVar5 = &DAT_80012914;
  }
  display_text(pcVar5,xsize - 0x18,0x1a);
LAB_800127e4:
  set_display_color(0xffffff);
  FUN_80018ef4(0x282,0x1b);
  FUN_80018ca8(0x26,0x27f,0x282);
  FUN_80018ca8(0x1b,0x282,0x285);
  if (*(char *)(iVar2 + 0x22) == '\0') {
    FUN_80018ca8(0x20,0x281);
    uVar6 = 0x21;
  }
  else {
    FUN_80018ca8(0x21,0x281);
    uVar6 = 0x20;
  }
  FUN_80018ca8(uVar6,0x280,0x284);
  iVar12 = Start_Of_Screen_Mem;
  iVar2 = Screen_Frame_Buffer;
  iVar19 = DAT_8001291c + -0x239;
  uVar16 = 5;
  do {
    iVar8 = uVar16 * 800 + 0x23a;
    copy_short((void *)(iVar12 + iVar8 * 2),(void *)(iVar2 + iVar8 * 2),iVar19);
    uVar16 = uVar16 + 1;
  } while (uVar16 < 0x29);
  return;
}

