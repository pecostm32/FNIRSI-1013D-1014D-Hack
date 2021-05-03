void FUN_8001267c(int param_1)

{
  ushort xsize;
  int *piVar1;
  int iVar2;
  char *pcVar3;
  undefined4 uVar4;
  ushort *puVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  int count;
  uint uVar9;
  
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
  iVar8 = DAT_800128e8;
  if (*(char *)(DAT_800128e8 + 0x21) == '\0') {
    display_text(&DAT_800128fc,0x25e,7);
  }
  else {
    if (*(char *)(DAT_800128e8 + 0x21) == '\x01') {
      pcVar3 = s_Single_800128ec;
    }
    else {
      if (*(char *)(DAT_800128e8 + 0x21) != '\x02') goto LAB_80012754;
      pcVar3 = s_Normal_800128f4;
    }
    display_text(pcVar3,0x25e,7);
  }
LAB_80012754:
  xsize = (ushort)DAT_80012904;
  if (*(char *)(iVar8 + 0x23) == '\0') {
    set_display_color(DAT_80012908);
    display_clear_rect(xsize - 0x1c,0x19,xsize,0x28);
    set_display_color(0);
    pcVar3 = &DAT_8001290c;
  }
  else {
    if (*(char *)(iVar8 + 0x23) != '\x01') goto LAB_800127e4;
    set_display_color(DAT_80012910);
    display_clear_rect(xsize - 0x1c,0x19,xsize,0x28);
    set_display_color(0);
    pcVar3 = &DAT_80012914;
  }
  display_text(pcVar3,xsize - 0x18,0x1a);
LAB_800127e4:
  set_display_color(0xffffff);
  FUN_80018ef4(0x282,0x1b);
  FUN_80018ca8(0x26,0x27f,0x282);
  FUN_80018ca8(0x1b,0x282,0x285);
  if (*(char *)(iVar8 + 0x22) == '\0') {
    FUN_80018ca8(0x20,0x281);
    uVar4 = 0x21;
  }
  else {
    FUN_80018ca8(0x21,0x281);
    uVar4 = 0x20;
  }
  FUN_80018ca8(uVar4,0x280,0x284);
  piVar1 = Global_Frame_Buffer_Pointer;
  if (param_1 != 0) {
    uVar9 = 5;
    do {
      iVar8 = 0x3c;
      puVar5 = (ushort *)(*piVar1 + uVar9 * 0x640 + 0x472);
      do {
        puVar6 = puVar5 + 2;
        iVar8 = iVar8 + -1;
        puVar5[1] = ~puVar5[1];
        *puVar6 = ~*puVar6;
        puVar5 = puVar6;
      } while (iVar8 != 0);
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0x29);
  }
  iVar2 = Start_Of_Screen_Mem;
  iVar8 = Screen_Frame_Buffer;
  count = DAT_8001291c + -0x239;
  uVar9 = 5;
  do {
    iVar7 = uVar9 * 800 + 0x23a;
    copy_short((void *)(iVar2 + iVar7 * 2),(void *)(iVar8 + iVar7 * 2),count);
    uVar9 = uVar9 + 1;
  } while (uVar9 < 0x29);
  return;
}

