void FUN_8000d9bc(int param_1)

{
  int *piVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  ushort *puVar5;
  ushort *puVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  
  set_frame_to_global_pointer();
  set_display_color(0);
  display_clear_rect(0xa1,4,0x104,0x2d);
  pcVar4 = DAT_8000dcf0;
  uVar9 = DAT_8000dcf4;
  if (*DAT_8000dcf0 == '\0') {
    uVar9 = DAT_8000dcf8;
  }
  set_display_color(uVar9);
  display_clear_rect(0xa1,5,0xbf,0x28);
  set_display_color(0);
  FUN_800197c8(2);
  FUN_80019730(PTR_PTR_FUN_8000dcfc);
  display_text(&DAT_8000dd00,0xa6,0x10);
  set_display_color(0xffffff);
  if (pcVar4[1] == '\0') {
    pcVar3 = (char *)0x8000dd04;
  }
  else {
    pcVar3 = (char *)0x8000dd08;
  }
  display_text(pcVar3,199,8);
  set_display_color(0xffffff);
  if (pcVar4[2] == '\0') {
    display_text(&DAT_8000dd0c,0xe0,8);
  }
  else {
    if (pcVar4[2] == '\x01') {
      pcVar3 = &DAT_8000dd10;
    }
    else {
      if (pcVar4[2] != '\x02') goto LAB_8000dac0;
      pcVar3 = &DAT_8000dd14;
    }
    display_text(pcVar3,0xde,8);
  }
LAB_8000dac0:
  if (pcVar4[2] != '\0') {
    if (pcVar4[2] == '\x01') {
      switch(pcVar4[3]) {
      case '\0':
switchD_8000db84_caseD_0:
        pcVar4 = &DAT_8000dda4;
        break;
      case '\x01':
        pcVar4 = &DAT_8000dd60;
        break;
      case '\x02':
switchD_8000db84_caseD_2:
        pcVar4 = &DAT_8000dd68;
        break;
      case '\x03':
switchD_8000db84_caseD_3:
        pcVar4 = s_5V_div_8000dd1c;
        break;
      case '\x04':
        pcVar4 = &DAT_8000dd70;
        break;
      case '\x05':
        goto switchD_8000daf0_caseD_2;
      case '\x06':
        goto switchD_8000daf0_caseD_3;
      default:
        goto switchD_8000daf0_caseD_7;
      }
    }
    else {
      if (pcVar4[2] != '\x02') goto switchD_8000daf0_caseD_7;
      switch(pcVar4[3]) {
      case '\0':
        pcVar4 = &DAT_8000dd80;
        break;
      case '\x01':
        pcVar4 = &DAT_8000dd8c;
        break;
      case '\x02':
        pcVar4 = &DAT_8000dd98;
        break;
      case '\x03':
        goto switchD_8000db84_caseD_0;
      case '\x04':
        pcVar4 = &DAT_8000ddac;
        break;
      case '\x05':
        goto switchD_8000db84_caseD_2;
      case '\x06':
        goto switchD_8000db84_caseD_3;
      default:
        goto switchD_8000daf0_caseD_7;
      }
    }
    goto LAB_8000db34;
  }
  switch(pcVar4[3]) {
  case '\0':
    display_text(s_5V_div_8000dd1c,199,0x18);
    goto switchD_8000daf0_caseD_7;
  case '\x01':
    pcVar4 = s_2_5V_div_8000dd24;
    break;
  case '\x02':
switchD_8000daf0_caseD_2:
    pcVar4 = &DAT_8000dd78;
    break;
  case '\x03':
switchD_8000daf0_caseD_3:
    pcVar4 = &DAT_8000dd30;
    break;
  case '\x04':
    pcVar4 = &DAT_8000dd3c;
    break;
  case '\x05':
    pcVar4 = &DAT_8000dd48;
    break;
  case '\x06':
    pcVar4 = &DAT_8000dd54;
    break;
  default:
    goto switchD_8000daf0_caseD_7;
  }
LAB_8000db34:
  display_text(pcVar4,199,0x18);
switchD_8000daf0_caseD_7:
  piVar1 = Global_Frame_Buffer_Pointer;
  if (param_1 != 0) {
    uVar9 = 5;
    do {
      puVar5 = (ushort *)(*piVar1 + uVar9 * 0x640 + 0x142);
      iVar8 = 0x31;
      *puVar5 = ~*puVar5;
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
  uVar9 = 4;
  do {
    iVar7 = uVar9 * 800 + 0xa1;
    copy_short((void *)(iVar2 + iVar7 * 2),(void *)(iVar8 + iVar7 * 2),100);
    uVar9 = uVar9 + 1;
  } while (uVar9 < 0x2d);
  return;
}

