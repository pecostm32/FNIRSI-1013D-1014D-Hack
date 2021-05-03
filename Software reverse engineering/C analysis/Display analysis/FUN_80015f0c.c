void FUN_80015f0c(void)

{
  ushort xsize;
  int iVar1;
  undefined *puVar2;
  int *piVar3;
  char *pcVar4;
  undefined4 uVar5;
  ushort *puVar6;
  int iVar7;
  short sVar8;
  undefined2 *puVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  int iVar15;
  
  uVar13 = DAT_80016394;
  set_frame_to_global_pointer();
  piVar3 = Global_Frame_Buffer_Pointer;
  iVar1 = DAT_8001639c;
  puVar2 = PTR_DAT_80016398;
  uVar11 = 0;
  do {
    iVar15 = 0xac;
    puVar9 = (undefined2 *)((*piVar3 + uVar11 * 0x640) - iVar1);
    puVar6 = (ushort *)(puVar2 + uVar11 * 0x158);
    do {
      uVar12 = (uint)*puVar6;
      if (*puVar6 == 0) {
        uVar12 = uVar13;
      }
      iVar15 = iVar15 + -1;
      *puVar9 = (short)uVar12;
      iVar14 = DAT_800163a4;
      puVar9 = puVar9 + 1;
      puVar6 = puVar6 + 1;
    } while (iVar15 != 0);
    uVar11 = uVar11 + 1 & 0xfffeffff;
  } while (uVar11 < 0xba);
  if (*(char *)(DAT_800163a4 + 0x21) == '\0') {
    uVar12 = 0x39;
    uVar11 = DAT_800163a8 - 0x276;
    do {
      puVar6 = (ushort *)(*piVar3 + (uVar12 * 800 + 5) * 2 + 0x4da);
      uVar10 = uVar11 & 0xffff;
      do {
        if (*puVar6 == uVar13) {
          *puVar6 = 0x7e0;
        }
        else {
          *puVar6 = 0;
        }
        uVar10 = uVar10 - 1 & 0xffff;
        puVar6 = puVar6 + 1;
      } while (uVar10 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0x61);
  }
  else {
    if (*(char *)(DAT_800163a4 + 0x21) == '\x01') {
      uVar12 = 0x39;
      uVar11 = DAT_800163ac - 0x296;
      do {
        puVar6 = (ushort *)(*piVar3 + (uVar12 * 800 + 5) * 2 + 0x51a);
        uVar10 = uVar11 & 0xffff;
        do {
          if (*puVar6 == uVar13) {
            *puVar6 = 0x7e0;
          }
          else {
            *puVar6 = 0;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar6 = puVar6 + 1;
        } while (uVar10 != 0);
        uVar12 = uVar12 + 1 & 0xfffeffff;
      } while (uVar12 < 0x61);
    }
    else {
      if (*(char *)(DAT_800163a4 + 0x21) == '\x02') {
        uVar12 = 0x39;
        uVar11 = DAT_800163b0 - 0x2b6;
        do {
          puVar6 = (ushort *)(*piVar3 + (uVar12 * 800 + 5) * 2 + 0x55a);
          uVar10 = uVar11 & 0xffff;
          do {
            if (*puVar6 == uVar13) {
              *puVar6 = 0x7e0;
            }
            else {
              *puVar6 = 0;
            }
            uVar10 = uVar10 - 1 & 0xffff;
            puVar6 = puVar6 + 1;
          } while (uVar10 != 0);
          uVar12 = uVar12 + 1 & 0xfffeffff;
        } while (uVar12 < 0x61);
      }
    }
  }
  if (*(char *)(iVar14 + 0x22) == '\0') {
    uVar12 = 0x7f;
    uVar11 = DAT_800163b4 - 0x271;
    do {
      puVar6 = (ushort *)(*piVar3 + (uVar12 * 800 + 5) * 2 + 0x4d0);
      uVar10 = uVar11 & 0xffff;
      do {
        if (*puVar6 == uVar13) {
          *puVar6 = 0x7e0;
        }
        else {
          *puVar6 = 0;
        }
        uVar10 = uVar10 - 1 & 0xffff;
        puVar6 = puVar6 + 1;
      } while (uVar10 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0x96);
  }
  else {
    uVar11 = 0x7f;
    do {
      puVar6 = (ushort *)(*piVar3 + (uVar11 * 800 + 5) * 2 + 0x530);
      sVar8 = 0x2f;
      do {
        sVar8 = sVar8 + -1;
        if (*puVar6 == uVar13) {
          *puVar6 = 0x7e0;
        }
        else {
          *puVar6 = 0;
        }
        puVar6 = puVar6 + 1;
      } while (sVar8 != 0);
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0x96);
  }
  if (*(char *)(iVar14 + 0x23) == '\0') {
    uVar12 = 0xbd;
    uVar11 = DAT_800163b8 - 0x274;
    do {
      puVar6 = (ushort *)(*piVar3 + (uVar12 * 800 + 5) * 2 + 0x4d6);
      uVar10 = uVar11 & 0xffff;
      do {
        if (*puVar6 == uVar13) {
          *puVar6 = 0x7e0;
        }
        else {
          *puVar6 = 0;
        }
        uVar10 = uVar10 - 1 & 0xffff;
        puVar6 = puVar6 + 1;
      } while (uVar10 != 0);
      uVar12 = uVar12 + 1 & 0xfffeffff;
    } while (uVar12 < 0xd4);
  }
  else {
    if (*(char *)(iVar14 + 0x23) == '\x01') {
      uVar12 = 0xbd;
      uVar11 = DAT_800163bc - 0x2a4;
      do {
        puVar6 = (ushort *)(*piVar3 + (uVar12 * 800 + 5) * 2 + 0x536);
        uVar10 = uVar11 & 0xffff;
        do {
          if (*puVar6 == uVar13) {
            *puVar6 = 0x7e0;
          }
          else {
            *puVar6 = 0;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar6 = puVar6 + 1;
        } while (uVar10 != 0);
        uVar12 = uVar12 + 1 & 0xfffeffff;
      } while (uVar12 < 0xd4);
    }
  }
  set_display_color(DAT_800163c0);
  iVar1 = DAT_800163c4;
  iVar15 = DAT_800163c4 + -0xab;
  FUN_80018da0(iVar15,0x2e,DAT_800163c4,0xe7);
  set_display_color(0);
  FUN_80018ca8(0x6b,iVar1 + -0xa0,iVar1 + -0xb);
  FUN_80018ca8(0xa9,iVar1 + -0xa0,iVar1 + -0xb);
  FUN_8001cccc(iVar15,0x2e,iVar1 + 1,0xe8);
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
  iVar1 = DAT_800128e8;
  if (*(char *)(DAT_800128e8 + 0x21) == '\0') {
    display_text(&DAT_800128fc,0x25e,7);
  }
  else {
    if (*(char *)(DAT_800128e8 + 0x21) == '\x01') {
      pcVar4 = s_Single_800128ec;
    }
    else {
      if (*(char *)(DAT_800128e8 + 0x21) != '\x02') goto LAB_80012754;
      pcVar4 = s_Normal_800128f4;
    }
    display_text(pcVar4,0x25e,7);
  }
LAB_80012754:
  xsize = (ushort)DAT_80012904;
  if (*(char *)(iVar1 + 0x23) == '\0') {
    set_display_color(DAT_80012908);
    display_clear_rect(xsize - 0x1c,0x19,xsize,0x28);
    set_display_color(0);
    pcVar4 = &DAT_8001290c;
  }
  else {
    if (*(char *)(iVar1 + 0x23) != '\x01') goto LAB_800127e4;
    set_display_color(DAT_80012910);
    display_clear_rect(xsize - 0x1c,0x19,xsize,0x28);
    set_display_color(0);
    pcVar4 = &DAT_80012914;
  }
  display_text(pcVar4,xsize - 0x18,0x1a);
LAB_800127e4:
  set_display_color(0xffffff);
  FUN_80018ef4(0x282,0x1b);
  FUN_80018ca8(0x26,0x27f,0x282);
  FUN_80018ca8(0x1b,0x282,0x285);
  if (*(char *)(iVar1 + 0x22) == '\0') {
    FUN_80018ca8(0x20,0x281);
    uVar5 = 0x21;
  }
  else {
    FUN_80018ca8(0x21,0x281);
    uVar5 = 0x20;
  }
  FUN_80018ca8(uVar5,0x280,0x284);
  iVar15 = Start_Of_Screen_Mem;
  iVar1 = Screen_Frame_Buffer;
  iVar14 = DAT_8001291c + -0x239;
  uVar13 = 5;
  do {
    iVar7 = uVar13 * 800 + 0x23a;
    copy_short((void *)(iVar15 + iVar7 * 2),(void *)(iVar1 + iVar7 * 2),iVar14);
    uVar13 = uVar13 + 1;
  } while (uVar13 < 0x29);
  return;
}


