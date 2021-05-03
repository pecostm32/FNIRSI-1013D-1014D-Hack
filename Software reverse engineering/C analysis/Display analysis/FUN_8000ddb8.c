void FUN_8000ddb8(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  char *pcVar5;
  ushort *puVar6;
  ushort *puVar7;
  int iVar8;
  ushort xpos;
  short sVar9;
  uint uVar10;
  
  set_frame_to_global_pointer();
  set_display_color(0);
  iVar1 = DAT_8000e100;
  display_clear_rect(0x120,4,(ushort)DAT_8000e100,0x2d);
  iVar2 = DAT_8000e104;
  uVar10 = DAT_8000e108;
  if (*(char *)(DAT_8000e104 + 0xc) == '\0') {
    uVar10 = DAT_8000e10c;
  }
  set_display_color(uVar10);
  display_clear_rect(0x120,5,(ushort)DAT_8000e110,0x28);
  set_display_color(0);
  FUN_800197c8(2);
  FUN_80019730(PTR_PTR_FUN_8000e114);
  display_text(&DAT_8000e11c,(ushort)DAT_8000e118,0x10);
  set_display_color(0xffffff);
  if (*(char *)(iVar2 + 0xd) == '\0') {
    pcVar5 = (char *)0x8000e124;
  }
  else {
    pcVar5 = (char *)0x8000e128;
  }
  xpos = (ushort)DAT_8000e120;
  display_text(pcVar5,xpos,8);
  set_display_color(0xffffff);
  if (*(char *)(iVar2 + 0xe) == '\0') {
    display_text(&DAT_8000e140,(ushort)DAT_8000e13c,8);
  }
  else {
    if (*(char *)(iVar2 + 0xe) == '\x01') {
      pcVar5 = (char *)0x8000e130;
    }
    else {
      if (*(char *)(iVar2 + 0xe) != '\x02') goto LAB_8000dec0;
      pcVar5 = (char *)0x8000e134;
    }
    display_text(pcVar5,(ushort)DAT_8000e12c,8);
  }
LAB_8000dec0:
  if (*(char *)(iVar2 + 0xe) != '\0') {
    if (*(char *)(iVar2 + 0xe) == '\x01') {
      switch(*(undefined *)(iVar2 + 0xf)) {
      case 0:
switchD_8000df84_caseD_0:
        pcVar5 = &DAT_8000e1cc;
        break;
      case 1:
        pcVar5 = &DAT_8000e188;
        break;
      case 2:
switchD_8000df84_caseD_2:
        pcVar5 = &DAT_8000e190;
        break;
      case 3:
switchD_8000df84_caseD_3:
        pcVar5 = s_5V_div_8000e144;
        break;
      case 4:
        pcVar5 = &DAT_8000e198;
        break;
      case 5:
        goto switchD_8000def0_caseD_2;
      case 6:
        goto switchD_8000def0_caseD_3;
      default:
        goto switchD_8000def0_caseD_7;
      }
    }
    else {
      if (*(char *)(iVar2 + 0xe) != '\x02') goto switchD_8000def0_caseD_7;
      switch(*(undefined *)(iVar2 + 0xf)) {
      case 0:
        pcVar5 = &DAT_8000e1a8;
        break;
      case 1:
        pcVar5 = &DAT_8000e1b4;
        break;
      case 2:
        pcVar5 = &DAT_8000e1c0;
        break;
      case 3:
        goto switchD_8000df84_caseD_0;
      case 4:
        pcVar5 = &DAT_8000e1d4;
        break;
      case 5:
        goto switchD_8000df84_caseD_2;
      case 6:
        goto switchD_8000df84_caseD_3;
      default:
        goto switchD_8000def0_caseD_7;
      }
    }
    goto LAB_8000df34;
  }
  switch(*(undefined *)(iVar2 + 0xf)) {
  case 0:
    display_text(s_5V_div_8000e144,xpos,0x18);
    goto switchD_8000def0_caseD_7;
  case 1:
    pcVar5 = s_2_5V_div_8000e14c;
    break;
  case 2:
switchD_8000def0_caseD_2:
    pcVar5 = &DAT_8000e1a0;
    break;
  case 3:
switchD_8000def0_caseD_3:
    pcVar5 = &DAT_8000e158;
    break;
  case 4:
    pcVar5 = &DAT_8000e164;
    break;
  case 5:
    pcVar5 = &DAT_8000e170;
    break;
  case 6:
    pcVar5 = &DAT_8000e17c;
    break;
  default:
    goto switchD_8000def0_caseD_7;
  }
LAB_8000df34:
  display_text(pcVar5,xpos,0x18);
switchD_8000def0_caseD_7:
  piVar3 = Global_Frame_Buffer_Pointer;
  if (param_1 != 0) {
    uVar10 = 5;
    do {
      puVar6 = (ushort *)(*piVar3 + uVar10 * 0x640 + 0x240);
      sVar9 = 0x31;
      *puVar6 = ~*puVar6;
      do {
        puVar7 = puVar6 + 2;
        sVar9 = sVar9 + -1;
        puVar6[1] = ~puVar6[1];
        *puVar7 = ~*puVar7;
        puVar6 = puVar7;
      } while (sVar9 != 0);
      uVar10 = uVar10 + 1 & 0xfffeffff;
    } while (uVar10 < 0x29);
  }
  iVar4 = Start_Of_Screen_Mem;
  iVar2 = Screen_Frame_Buffer;
  uVar10 = 4;
  do {
    iVar8 = uVar10 * 800 + 0x120;
    copy_short((void *)(iVar4 + iVar8 * 2),(void *)(iVar2 + iVar8 * 2),iVar1 + -0x11f);
    uVar10 = uVar10 + 1;
  } while (uVar10 < 0x2d);
  return;
}

