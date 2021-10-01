//scope_display_cursor_measurements

void FUN_8000ebf8(void)

{
  short sVar1;
  longlong lVar2;
  char cVar3;
  char cVar4;
  char *pcVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  uint uVar12;
  uint unaff_r4;
  int iVar13;
  int iVar14;
  uint unaff_r5;
  ushort ypos;
  int unaff_r10;
  char local_84;
  undefined local_83;
  undefined local_82;
  undefined local_81;
  char local_80;
  char local_7f;
  char local_7e;
  char local_7d;
  undefined local_7c;
  undefined local_7b;
  undefined local_7a;
  undefined local_79;
  char local_74;
  undefined local_73;
  undefined local_72;
  undefined local_71;
  undefined local_70;
  char local_6f;
  char local_6e;
  char local_6d;
  char local_6c;
  undefined local_6b;
  undefined local_6a;
  undefined local_69;
  char local_60;
  undefined local_5f;
  undefined local_5e;
  undefined local_5d;
  undefined local_5c;
  char local_5b;
  char local_5a;
  char local_59;
  char local_58;
  undefined local_57;
  undefined local_56;
  undefined local_55;
  char local_50;
  undefined local_4f;
  undefined local_4e;
  undefined local_4d;
  char local_4c;
  char local_4b;
  char local_4a;
  char local_49;
  undefined local_48;
  undefined local_47;
  undefined local_46;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  
  ypos = (ushort)unaff_r10;

  set_frame_to_global_pointer();

  uVar12 = DAT_8000fb30;
  uVar7 = DAT_8000fb2c;
  uVar8 = DAT_8000fb10;
  pcVar5 = DAT_8000faf4;   //0x8019D5A0

  //0x801FA44C
  uVar6 = (uint)*(ushort *)(DAT_8000faf0 + 0x9e) - (uint)*(ushort *)(DAT_8000faf0 + 0x9c);  //0x801FA4EA - 0x801FA4E8

  //Time cursor positions subtracted
  uVar9 = (uint)*(ushort *)(DAT_8000faf0 + 0x96) - (uint)*(ushort *)(DAT_8000faf0 + 0x94);  //0x801FA4E2 - 0x801FA4E0

  //50 dots per division

  switch(DAT_8000faf4[10])  //Switch on time base setting
 {
  case '\t':  //9   50mS/div
    uVar11 = DAT_8000faf8;    //0x000F4240 = 1000000
    break;
  case '\n':  //10
    uVar11 = DAT_8000fafc;    //0x00061A80 = 400000
    break;
  case '\v':  //11
    uVar11 = DAT_8000fb00;    //0x00030D40 = 200000
    break;
  case '\f':  //12
    uVar11 = DAT_8000fb04;    //0x000186A0 = 100000
    break;
  case '\r':  //13
    uVar11 = DAT_8000fb08;    //0x00009C40 = 40000
    break;
  case '\x0e':  //14
    uVar11 = DAT_8000fb0c;    //0x00004E20 = 20000
    break;
  case '\x0f':  //15
    uVar11 = DAT_8000fb10;    //0x00002710 = 10000
    break;
  case '\x10':  //16
    uVar11 = 4000;
    break;
  case '\x11':  //17
    uVar11 = 2000;
    break;
  case '\x12':  //18
    uVar11 = 1000;
    break;
  case '\x13':  //19
    uVar11 = 400;
    break;
  case '\x14':  //20
    uVar11 = 200;
    break;
  case '\x15':  //21
    uVar11 = 100;
    break;
  case '\x16':  //22
    uVar9 = uVar9 * 0x28;             //40
    goto switchD_8000ec34_caseD_1b;
  case '\x17':  //23
    uVar9 = uVar9 * 0x14;             //20
    goto switchD_8000ec34_caseD_1b;
  case '\x18':  //24
    uVar9 = uVar9 * 10;               //10
    goto switchD_8000ec34_caseD_1b;
  case '\x19':  //25
    uVar9 = uVar9 * 5;
    goto switchD_8000ec34_caseD_1b;
  case '\x1a':  //26
    uVar9 = uVar9 * 2;

  default:
    goto switchD_8000ec34_caseD_1b;
  case '\x1c': //28   25nS/div
    uVar11 = 500;
    break;
  case '\x1d':  //29  10nS/div
    uVar9 = uVar9 * 200;
    goto switchD_8000ec34_caseD_1b;
  }

  uVar9 = uVar11 * uVar9;


switchD_8000ec34_caseD_1b:


  switch(DAT_8000faf4[3])  //switch on channel 1 volts div
  {
  case '\0':
    iVar10 = 100;
    goto LAB_8000ed7c;
  case '\x01':
    iVar10 = 0x32;
LAB_8000ed7c:
    unaff_r5 = uVar6 * iVar10;
    break;
  case '\x02':
    unaff_r5 = uVar6 * 0x14;
    break;
  case '\x03':
    unaff_r5 = uVar6 * 10;
    break;
  case '\x04':
    unaff_r5 = uVar6 * 4;
    break;
  case '\x05':
    unaff_r5 = uVar6 * 2;
    break;
  case '\x06':
    unaff_r5 = uVar6;
  }

  switch(DAT_8000faf4[0xf])
 {
  case '\0':
    iVar10 = 100;
    goto LAB_8000ede8;
  case '\x01':
    iVar10 = 0x32;
LAB_8000ede8:
    unaff_r4 = uVar6 * iVar10;
    break;
  case '\x02':
    unaff_r4 = uVar6 * 0x14;
    break;
  case '\x03':
    unaff_r4 = uVar6 * 10;
    break;
  case '\x04':
    unaff_r4 = uVar6 * 4;
    break;
  case '\x05':
    unaff_r4 = uVar6 * 2;
    break;
  case '\x06':
    unaff_r4 = uVar6;
  }
  if (DAT_8000faf4[2] == '\x01') {
    unaff_r5 = unaff_r5 * 10;
  }
  else {
    if (DAT_8000faf4[2] == '\x02') {
      unaff_r5 = unaff_r5 * 100;
    }
  }
  if (DAT_8000faf4[0xe] == '\x01') {
    unaff_r4 = unaff_r4 * 10;
  }
  else {
    if (DAT_8000faf4[0xe] == '\x02') {
      unaff_r4 = unaff_r4 * 100;
    }
  }

  local_84 = 'F';
  local_74 = 'V';
  local_73 = 0x31;
  local_72 = 0x20;
  local_71 = 0x3d;
  local_83 = 0x20;
  local_60 = 'V';
  local_50 = 'T';
  local_82 = 0x3d;
  local_5f = 0x32;
  local_4f = 0x20;
  local_81 = 0x20;
  local_4e = 0x3d;
  local_70 = 0x20;
  local_5e = 0x20;
  local_4d = 0x20;
  local_5d = 0x3d;
  local_5c = 0x20;

  sVar1 = (short)DAT_8000fb1c;
  if (unaff_r5 < DAT_8000faf8) {
    if (unaff_r5 < DAT_8000fb04) {
      if (unaff_r5 < DAT_8000fb10) {
        if (unaff_r5 < 1000) {
          cVar3 = (char)unaff_r5;
          if (unaff_r5 < 100) {
            if (unaff_r5 < 10) {
              local_6c = '\0';
              local_6f = cVar3 + (char)(uint)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb30 >> 0x23)
                                 * -10 + '0';
              local_6e = 'm';
              local_6d = 'V';
            }
            else {
              local_6c = 'V';
              local_6b = 0;
              cVar4 = (char)(uint)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb30 >> 0x23);
              local_6f = cVar4 + '0';
              local_6e = cVar3 + cVar4 * -10 + '0';
              local_6d = 'm';
            }
          }
          else {
            uVar6 = (uint)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb2c >> 0x25);
            local_6f = (char)uVar6 + '0';
            local_6e = (char)(uint)((ulonglong)(unaff_r5 + uVar6 * -100) * (ulonglong)DAT_8000fb30
                                   >> 0x23) + '0';
            local_6d = cVar3 + (char)(uint)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb30 >> 0x23) *
                               -10 + '0';
            local_6c = 'm';
            local_6b = 0x56;
            local_6a = 0;
          }
        }
        else {
          uVar6 = (uint)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb28 >> 0x26);
          local_6f = (char)uVar6 + '0';
          local_6e = '.';
          uVar11 = unaff_r5 + uVar6 * -1000;
          uVar6 = (uint)((ulonglong)uVar11 * (ulonglong)DAT_8000fb2c >> 0x25);
          local_6d = (char)uVar6 + '0';
          local_6c = (char)(uint)((ulonglong)(uVar11 + uVar6 * -100) * (ulonglong)DAT_8000fb30 >>
                                 0x23) + '0';
          local_6b = 0x56;
          local_6a = 0;
        }
      }
      else {
        uVar6 = (uint)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb24 >> 0x2d);
        local_6f = (char)uVar6 + '0';
        uVar11 = unaff_r5 + uVar6 * -10000;
        uVar6 = (uint)((ulonglong)uVar11 * (ulonglong)DAT_8000fb28 >> 0x26);
        local_6e = (char)uVar6 + '0';
        local_6d = '.';
        local_6c = (char)(uint)((ulonglong)(uVar11 + uVar6 * -1000) * (ulonglong)DAT_8000fb2c >>
                               0x25) + '0';
        local_6b = 0x56;
        local_6a = 0;
      }
    }
    else {
      local_6f = (char)((ulonglong)DAT_8000fb18 * (ulonglong)unaff_r5 + (ulonglong)DAT_8000fb18 >>
                       0x30) + '0';
      local_6e = (char)(uint)((ulonglong)
                              (unaff_r5 +
                              DAT_8000fb20 *
                              (uint)((ulonglong)DAT_8000fb18 * (ulonglong)unaff_r5 +
                                     (ulonglong)DAT_8000fb18 >> 0x30) * 0x20) *
                              (ulonglong)DAT_8000fb24 >> 0x2d) + '0';
      local_6c = 'V';
      uVar6 = unaff_r5 +
              (uint)((ulonglong)DAT_8000fb18 * (ulonglong)unaff_r5 + (ulonglong)DAT_8000fb18 >> 0x30
                    ) * DAT_8000fb20 * 0x20;
      local_6b = 0;
      local_6d = (char)(uint)((ulonglong)
                              (uVar6 + (uint)((ulonglong)uVar6 * (ulonglong)DAT_8000fb24 >> 0x2d) *
                                       -10000) * (ulonglong)DAT_8000fb28 >> 0x26) + '0';
    }
  }
  else {
    local_6f = (char)(uint)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb14 >> 0x32) + '0';
    local_6e = '.';
    uVar6 = unaff_r5 +
            (int)(short)(ushort)((ulonglong)unaff_r5 * (ulonglong)DAT_8000fb14 >> 0x32) * (int)sVar1
            * 0x40;
    local_6d = (char)((ulonglong)DAT_8000fb18 * (ulonglong)uVar6 + (ulonglong)DAT_8000fb18 >> 0x30)
               + '0';
    local_6c = (char)(uint)((ulonglong)
                            (uVar6 + (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar6 +
                                            (ulonglong)DAT_8000fb18 >> 0x30) * DAT_8000fb20 * 0x20)
                            * (ulonglong)DAT_8000fb24 >> 0x2d) + '0';
    local_6b = 0x4b;
    local_6a = 0x56;
    local_69 = 0;
  }
  if (unaff_r4 < DAT_8000faf8) {
    if (unaff_r4 < DAT_8000fb04) {
      if (unaff_r4 < DAT_8000fb10) {
        if (unaff_r4 < 1000) {
          cVar3 = (char)unaff_r4;
          if (unaff_r4 < 100) {
            if (unaff_r4 < 10) {
              local_58 = '\0';
              local_5b = cVar3 + (char)(uint)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb30 >> 0x23)
                                 * -10 + '0';
              local_5a = 'm';
              local_59 = 'V';
            }
            else {
              local_58 = 'V';
              local_57 = 0;
              cVar4 = (char)(uint)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb30 >> 0x23);
              local_5b = cVar4 + '0';
              local_5a = cVar3 + cVar4 * -10 + '0';
              local_59 = 'm';
            }
          }
          else {
            uVar6 = (uint)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb2c >> 0x25);
            local_5b = (char)uVar6 + '0';
            local_5a = (char)(uint)((ulonglong)(unaff_r4 + uVar6 * -100) * (ulonglong)DAT_8000fb30
                                   >> 0x23) + '0';
            local_59 = cVar3 + (char)(uint)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb30 >> 0x23) *
                               -10 + '0';
            local_58 = 'm';
            local_57 = 0x56;
            local_56 = 0;
          }
        }
        else {
          uVar6 = (uint)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb28 >> 0x26);
          local_5b = (char)uVar6 + '0';
          local_5a = '.';
          uVar11 = unaff_r4 + uVar6 * -1000;
          uVar6 = (uint)((ulonglong)uVar11 * (ulonglong)DAT_8000fb2c >> 0x25);
          local_59 = (char)uVar6 + '0';
          local_58 = (char)(uint)((ulonglong)(uVar11 + uVar6 * -100) * (ulonglong)DAT_8000fb30 >>
                                 0x23) + '0';
          local_57 = 0x56;
          local_56 = 0;
        }
      }
      else {
        uVar6 = (uint)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb24 >> 0x2d);
        local_5b = (char)uVar6 + '0';
        uVar11 = unaff_r4 + uVar6 * -10000;
        uVar6 = (uint)((ulonglong)uVar11 * (ulonglong)DAT_8000fb28 >> 0x26);
        local_5a = (char)uVar6 + '0';
        local_59 = '.';
        local_58 = (char)(uint)((ulonglong)(uVar11 + uVar6 * -1000) * (ulonglong)DAT_8000fb2c >>
                               0x25) + '0';
        local_57 = 0x56;
        local_56 = 0;
      }
    }
    else {
      local_5b = (char)((ulonglong)DAT_8000fb18 * (ulonglong)unaff_r4 + (ulonglong)DAT_8000fb18 >>
                       0x30) + '0';
      local_5a = (char)(uint)((ulonglong)
                              (unaff_r4 +
                              DAT_8000fb20 *
                              (uint)((ulonglong)DAT_8000fb18 * (ulonglong)unaff_r4 +
                                     (ulonglong)DAT_8000fb18 >> 0x30) * 0x20) *
                              (ulonglong)DAT_8000fb24 >> 0x2d) + '0';
      local_58 = 'V';
      uVar6 = unaff_r4 +
              (uint)((ulonglong)DAT_8000fb18 * (ulonglong)unaff_r4 + (ulonglong)DAT_8000fb18 >> 0x30
                    ) * DAT_8000fb20 * 0x20;
      local_57 = 0;
      local_59 = (char)(uint)((ulonglong)
                              (uVar6 + (uint)((ulonglong)uVar6 * (ulonglong)DAT_8000fb24 >> 0x2d) *
                                       -10000) * (ulonglong)DAT_8000fb28 >> 0x26) + '0';
    }
  }
  else {
    local_5b = (char)(uint)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb14 >> 0x32) + '0';
    local_5a = '.';
    uVar6 = unaff_r4 +
            (int)(short)(ushort)((ulonglong)unaff_r4 * (ulonglong)DAT_8000fb14 >> 0x32) * (int)sVar1
            * 0x40;
    local_59 = (char)((ulonglong)DAT_8000fb18 * (ulonglong)uVar6 + (ulonglong)DAT_8000fb18 >> 0x30)
               + '0';
    local_58 = (char)(uint)((ulonglong)
                            (uVar6 + DAT_8000fb20 *
                                     (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar6 +
                                            (ulonglong)DAT_8000fb18 >> 0x30) * 0x20) *
                            (ulonglong)DAT_8000fb24 >> 0x2d) + '0';
    local_57 = 0x4b;
    local_56 = 0x56;
    local_55 = 0;
  }
  cVar3 = (char)uVar9;

  if ((byte)DAT_8000faf4[10] < 0x1c) {
    if (DAT_8000fb34 <= uVar9) {
      local_4c = (byte)((ulonglong)uVar9 * (ulonglong)DAT_8000fb38 >> 0x39) + 0x30;
      uVar7 = uVar9 + DAT_8000fb3c * (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb38 >> 0x39) *
                      0x100;
      uVar8 = (uint)((ulonglong)uVar7 * (ulonglong)DAT_8000fb40 >> 0x36);
      local_4b = (char)uVar8 + '0';
      local_4a = (char)(uint)((ulonglong)(uVar7 + DAT_8000fb44 * uVar8 * 0x80) *
                              (ulonglong)DAT_8000fb14 >> 0x32) + '0';
      local_48 = 0x53;
      local_49 = 'm';
      local_47 = 0;
      uVar9 = divide(DAT_8000fb04,(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb14 >> 0x32));
      if (uVar9 == 1000) {
        local_80 = '1';
        local_7f = '0';
        local_7e = 'H';
        local_7d = 'z';
        local_7c = 0;
      }
      else {
        uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
        local_80 = (char)uVar8 + '0';
        local_7f = '.';
        local_7e = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >> 0x23)
                   + '0';
        local_7d = (char)uVar9 +
                   (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10 + '0';
        local_7c = 0x48;
        local_7b = 0x7a;
        local_7a = 0;
      }
      goto LAB_80010394;
    }
    if (uVar9 < DAT_8000fb48) {
      if (uVar9 < DAT_8000faf8) {
        if (DAT_8000fb04 <= uVar9) {
          local_4c = (char)((ulonglong)DAT_8000fb18 * (ulonglong)uVar9 + (ulonglong)DAT_8000fb18 >>
                           0x30) + '0';
          local_4b = (char)(uint)((ulonglong)
                                  (uVar9 + DAT_8000fb20 *
                                           (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar9 +
                                                  (ulonglong)DAT_8000fb18 >> 0x30) * 0x20) *
                                  (ulonglong)DAT_8000fb24 >> 0x2d) + '0';
          uVar8 = uVar9 + (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar9 +
                                 (ulonglong)DAT_8000fb18 >> 0x30) * DAT_8000fb20 * 0x20;
          local_4a = (char)(uint)((ulonglong)
                                  (uVar8 + (uint)((ulonglong)uVar8 * (ulonglong)DAT_8000fb24 >> 0x2d
                                                 ) * -10000) * (ulonglong)DAT_8000fb28 >> 0x26) +
                     '0';
          local_49 = 'u';
          local_48 = 0x53;
          local_47 = 0;
          uVar9 = divide(DAT_8000fb04,(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb28 >> 0x26));
          if (uVar9 == 1000) {
            local_80 = '1';
            local_7f = '0';
            local_7e = 'K';
            local_7c = 0x7a;
            local_7d = 'H';
            local_7b = 0;
          }
          else {
            uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
            local_80 = (char)uVar8 + '0';
            local_7f = '.';
            local_7e = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >>
                                   0x23) + '0';
            local_7d = (char)uVar9 +
                       (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10 + '0';
            local_7c = 0x4b;
            local_7b = 0x48;
            local_7a = 0x7a;
            local_79 = 0;
          }
          goto LAB_80010394;
        }
        if (uVar9 < DAT_8000fb10) {
          if (uVar9 < 1000) {
            if (99 < uVar9) {
              uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
              local_4c = (char)uVar8 + '0';
              local_4b = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >>
                                     0x23) + '0';
              local_4a = cVar3 + (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) *
                                 -10 + '0';
              local_48 = 0x53;
              local_49 = 'n';
              local_47 = 0;
              uVar9 = divide(DAT_8000fb04,uVar9);
              if (uVar9 != 1000) {
                uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)uVar7 >> 0x25);
                local_80 = (char)uVar8 + '0';
                local_7f = '.';
                local_7e = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)uVar12 >>
                                       0x23) + '0';
                local_7d = (char)uVar9 +
                           (char)(uint)((ulonglong)uVar9 * (ulonglong)uVar12 >> 0x23) * -10 + '0';
                local_7c = 0x4d;
                local_7b = 0x48;
                local_7a = 0x7a;
                local_79 = 0;
                goto LAB_80010394;
              }
              goto LAB_8001003c;
            }
            if (9 < uVar9) {
              local_48 = 0;
              cVar4 = (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23);
              local_4c = cVar4 + '0';
              local_4b = cVar3 + cVar4 * -10 + '0';
              local_4a = 'n';
              local_49 = 'S';
              uVar9 = divide(DAT_8000fb10,uVar9);
              if (uVar9 != 1000) {
                uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
                local_80 = (char)uVar8 + '0';
                local_7f = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)uVar12 >>
                                       0x23) + '0';
                local_7e = '.';
                local_7d = (char)uVar9 +
                           (char)(uint)((ulonglong)uVar9 * (ulonglong)uVar12 >> 0x23) * -10 + '0';
                local_7c = 0x4d;
                local_7b = 0x48;
                local_7a = 0x7a;
                local_79 = 0;
                goto LAB_80010394;
              }
              goto LAB_8000fe14;
            }
            if (uVar9 == 0) goto LAB_80010394;
            local_4c = cVar3 + (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) *
                               -10 + '0';
            local_4b = 'n';
            local_4a = 'S';
            local_49 = '\0';
            if (uVar9 == 1) goto LAB_80010258;
            uVar8 = divide(1000,uVar9);
            uVar9 = (uint)((ulonglong)uVar8 * (ulonglong)DAT_8000fb2c >> 0x25);
            local_80 = (char)uVar9 + '0';
            local_7f = (char)(uint)((ulonglong)(uVar8 + uVar9 * -100) * (ulonglong)uVar12 >> 0x23) +
                       '0';
            local_7e = (char)uVar8 +
                       (char)(uint)((ulonglong)uVar8 * (ulonglong)uVar12 >> 0x23) * -10 + '0';
            local_7d = 'M';
          }
          else {
            uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb28 >> 0x26);
            local_4c = (char)uVar8 + '0';
            local_4b = '.';
            uVar6 = uVar9 + uVar8 * -1000;
            uVar8 = (uint)((ulonglong)uVar6 * (ulonglong)DAT_8000fb2c >> 0x25);
            local_4a = (char)uVar8 + '0';
            local_49 = (char)(uint)((ulonglong)(uVar6 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >>
                                   0x23) + '0';
            local_48 = 0x75;
            local_47 = 0x53;
            local_46 = 0;
            uVar9 = divide(DAT_8000fb04,(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23));
            if (uVar9 == 1000) {
              local_80 = '1';
              local_7f = 'M';
              local_7e = 'H';
              local_7d = 'z';
              local_7c = 0;
              goto LAB_80010394;
            }
            uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)uVar7 >> 0x25);
            local_80 = (char)uVar8 + '0';
            local_7f = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)uVar12 >> 0x23) +
                       '0';
            local_7e = (char)uVar9 +
                       (char)(uint)((ulonglong)uVar9 * (ulonglong)uVar12 >> 0x23) * -10 + '0';
            local_7d = 'K';
          }
        }
        else {
          uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb24 >> 0x2d);
          local_4c = (char)uVar8 + '0';
          uVar12 = uVar9 + uVar8 * -10000;
          uVar8 = (uint)((ulonglong)uVar12 * (ulonglong)DAT_8000fb28 >> 0x26);
          local_4b = (char)uVar8 + '0';
          local_4a = '.';
          local_49 = (char)(uint)((ulonglong)(uVar12 + uVar8 * -1000) * (ulonglong)DAT_8000fb2c >>
                                 0x25) + '0';
          local_48 = 0x75;
          local_47 = 0x53;
          local_46 = 0;
          uVar9 = divide(DAT_8000fb04,(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25));
          if (uVar9 != 1000) {
            uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)uVar7 >> 0x25);
            local_80 = (char)uVar8 + '0';
            local_7f = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >>
                                   0x23) + '0';
            local_7e = '.';
            local_7d = (char)uVar9 +
                       (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10 + '0';
            local_7c = 0x4b;
            local_7b = 0x48;
            local_7a = 0x7a;
            local_79 = 0;
            goto LAB_80010394;
          }
          local_80 = '1';
          local_7f = '0';
          local_7e = '0';
          local_7d = 'K';
        }
        goto LAB_8000fc38;
      }
      local_4c = (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb14 >> 0x32) + '0';
      local_4b = '.';
      uVar8 = uVar9 + (int)(short)(ushort)((ulonglong)uVar9 * (ulonglong)DAT_8000fb14 >> 0x32) *
                      (int)sVar1 * 0x40;
      local_4a = (char)((ulonglong)DAT_8000fb18 * (ulonglong)uVar8 + (ulonglong)DAT_8000fb18 >> 0x30
                       ) + '0';
      local_49 = (char)(uint)((ulonglong)
                              (uVar8 + DAT_8000fb20 *
                                       (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar8 +
                                              (ulonglong)DAT_8000fb18 >> 0x30) * 0x20) *
                              (ulonglong)DAT_8000fb24 >> 0x2d) + '0';
      local_48 = 0x6d;
      local_47 = 0x53;
      local_46 = 0;
      uVar9 = divide(DAT_8000fb04,(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb24 >> 0x2d));
      if (uVar9 == 1000) {
        local_80 = '1';
        local_7f = 'K';
        local_7e = 'H';
        local_7d = 'z';
        local_7c = 0;
        goto LAB_80010394;
      }
      uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
      local_80 = (char)uVar8 + '0';
      local_7f = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >> 0x23) +
                 '0';
      local_7e = (char)uVar9 +
                 (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10 + '0';
    }
    else {
      uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb40 >> 0x36);
      local_4c = (char)uVar8 + '0';
      uVar8 = uVar9 + DAT_8000fb44 * uVar8 * 0x80;
      lVar2 = (ulonglong)uVar8 * (ulonglong)DAT_8000fb14;
      local_4b = (char)(uint)((ulonglong)lVar2 >> 0x32) + '0';
      local_4a = '.';
      local_49 = (char)((ulonglong)DAT_8000fb18 *
                        (ulonglong)
                        (uVar8 + (int)(short)(ushort)((ulonglong)lVar2 >> 0x32) * (int)sVar1 * 0x40)
                        + (ulonglong)DAT_8000fb18 >> 0x30) + '0';
      local_48 = 0x6d;
      local_47 = 0x53;
      local_46 = 0;
      uVar9 = divide(DAT_8000fb04,
                     (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar9 + (ulonglong)DAT_8000fb18 >>
                           0x30));
      if (uVar9 != 1000) {
        uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
        local_80 = (char)uVar8 + '0';
        local_7f = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >> 0x23)
                   + '0';
        local_7e = '.';
        local_7d = (char)uVar9 +
                   (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10 + '0';
        local_7c = 0x48;
        local_7b = 0x7a;
        local_7a = 0;
        goto LAB_80010394;
      }
      local_80 = '1';
      local_7f = '0';
      local_7e = '0';
    }
  }
  else {
    if (0x1d < (byte)DAT_8000faf4[10]) goto LAB_80010394;
    if (uVar9 < DAT_8000fb04) {
      if (uVar9 < DAT_8000fb10) {
        if (uVar9 < 1000) {
          if (uVar9 < 100) goto LAB_80010394;
          uVar6 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
          local_4c = (char)uVar6 + '0';
          local_4b = (char)(uint)((ulonglong)(uVar9 + uVar6 * -100) * (ulonglong)DAT_8000fb30 >>
                                 0x23) + '0';
          local_4a = cVar3 + (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10
                     + '0';
          local_49 = 'p';
          local_48 = 0x53;
          local_47 = 0;
          uVar9 = divide(DAT_8000fb10,uVar6);
          if (uVar9 != uVar8) {
            uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb28 >> 0x26);
            local_80 = (char)uVar8 + '0';
            local_7f = '.';
            uVar9 = uVar9 + uVar8 * -1000;
            uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)uVar7 >> 0x25);
            local_7e = (char)uVar8 + '0';
            local_7d = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)uVar12 >> 0x23) +
                       '0';
            local_7c = 0x47;
            local_7b = 0x48;
            local_7a = 0x7a;
            local_79 = 0;
            goto LAB_80010394;
          }
          local_80 = '1';
          local_7f = '0';
          local_7e = 'G';
          goto LAB_80010060;
        }
        uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb28 >> 0x26);
        local_4c = (char)uVar8 + '0';
        local_4b = '.';
        uVar9 = uVar9 + uVar8 * -1000;
        uVar6 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
        local_4a = (char)uVar6 + '0';
        local_49 = (char)(uint)((ulonglong)(uVar9 + uVar6 * -100) * (ulonglong)DAT_8000fb30 >> 0x23)
                   + '0';
        local_48 = 0x6e;
        local_47 = 0x53;
        local_46 = 0;
        uVar9 = divide(1000,uVar8);
        if (uVar9 == 1000)
        {
LAB_80010258:
          local_80 = '1';
          local_7f = 'G';
          local_7e = 'H';
          local_7d = 'z';
          local_7c = 0;
          goto LAB_80010394;
        }
        uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)uVar7 >> 0x25);
        local_80 = (char)uVar8 + '0';
        local_7f = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)uVar12 >> 0x23) + '0'
        ;
        local_7e = (char)uVar9 + (char)(uint)((ulonglong)uVar9 * (ulonglong)uVar12 >> 0x23) * -10 +
                   '0';
        local_7d = 'M';
      }
      else {
        uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb24 >> 0x2d);
        local_4c = (char)uVar8 + '0';
        uVar12 = uVar9 + uVar8 * -10000;
        uVar8 = (uint)((ulonglong)uVar12 * (ulonglong)DAT_8000fb28 >> 0x26);
        local_4b = (char)uVar8 + '0';
        uVar7 = DAT_8000fb28 * 5;
        local_4a = '.';
        local_49 = (char)(uint)((ulonglong)(uVar12 + uVar8 * -1000) * (ulonglong)uVar7 >> 0x25) +
                   '0';
        local_48 = 0x6e;
        local_47 = 0x53;
        local_46 = 0;
        uVar9 = divide(DAT_8000fb10,(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb28 >> 0x26));
        if (uVar9 != 1000) {
          uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)uVar7 >> 0x25);
          local_80 = (char)uVar8 + '0';
          local_7f = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >>
                                 0x23) + '0';
          local_7e = '.';
          local_7d = (char)uVar9 +
                     (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10 + '0';
          local_7c = 0x4d;
          local_7b = 0x48;
          local_7a = 0x7a;
          local_79 = 0;
          goto LAB_80010394;
        }
LAB_8000fe14:
        local_80 = '1';
        local_7f = '0';
        local_7e = '0';
        local_7d = 'M';
      }
LAB_8000fc38:
      local_7b = 0x7a;
      local_7c = 0x48;
      local_7a = 0;
      goto LAB_80010394;
    }
    local_4c = (char)((ulonglong)DAT_8000fb18 * (ulonglong)uVar9 + (ulonglong)DAT_8000fb18 >> 0x30)
               + '0';
    local_4b = (char)(uint)((ulonglong)
                            (uVar9 + DAT_8000fb20 *
                                     (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar9 +
                                            (ulonglong)DAT_8000fb18 >> 0x30) * 0x20) *
                            (ulonglong)DAT_8000fb24 >> 0x2d) + '0';
    uVar8 = uVar9 + (uint)((ulonglong)DAT_8000fb18 * (ulonglong)uVar9 + (ulonglong)DAT_8000fb18 >>
                          0x30) * DAT_8000fb20 * 0x20;
    local_4a = (char)(uint)((ulonglong)
                            (uVar8 + (uint)((ulonglong)uVar8 * (ulonglong)DAT_8000fb24 >> 0x2d) *
                                     -10000) * (ulonglong)DAT_8000fb28 >> 0x26) + '0';
    local_49 = 'n';
    local_48 = 0x53;
    local_47 = 0;
    uVar9 = divide(DAT_8000fb04,(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb28 >> 0x26));
    if (uVar9 != 1000) {
      uVar8 = (uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb2c >> 0x25);
      local_80 = (char)uVar8 + '0';
      local_7f = '.';
      local_7e = (char)(uint)((ulonglong)(uVar9 + uVar8 * -100) * (ulonglong)DAT_8000fb30 >> 0x23) +
                 '0';
      local_7d = (char)uVar9 +
                 (char)(uint)((ulonglong)uVar9 * (ulonglong)DAT_8000fb30 >> 0x23) * -10 + '0';
      local_7c = 0x4d;
      local_7b = 0x48;
      local_7a = 0x7a;
      local_79 = 0;
      goto LAB_80010394;
    }
LAB_8001003c:
    local_80 = '1';
    local_7f = '0';
    local_7e = 'M';
  }
LAB_80010060:
  local_7c = 0x7a;
  local_7d = 'H';
  local_7b = 0;
LAB_80010394:
  iVar10 = DAT_800104a8;
  iVar13 = 0x33;

  if (*(char *)(DAT_800104a8 + 0x292) != '\0')
  {
    local_2c = 0x33;
    iVar13 = 0x53;
    local_30 = 0x43;
  }

  if (*(char *)(DAT_800104a8 + 0x29a) != '\0') {
    iVar14 = iVar13;
    if (*pcVar5 != '\0') {
      iVar14 = iVar13 + 0x10;
      unaff_r10 = iVar13;
    }

    ypos = (ushort)unaff_r10;
    iVar13 = iVar14;

    if (pcVar5[0xc] != '\0') {
      iVar13 = iVar14 + 0x10;
      local_34 = iVar14;
    }
  }

  //Check if cursors enabled. Should have been done at the start of the function!!!!!
  if (*(char *)(DAT_800104a8 + 0x292) == '\0' && *(char *)(DAT_800104a8 + 0x29a) == '\0') {
    return;
  }

  set_display_fg_color(DAT_800104ac);  //0x00404040

  display_fill_rounded_rect(5,0x31,0x66,(short)iVar13 - 1,2);

  set_font_paint_mode(2);
  select_font(PTR_FONT_0_800104b0);
  set_display_fg_color(0xffffff);

  if (*(char *)(iVar10 + 0x292) != '\0') {
    display_text(&local_50,10,(ushort)local_2c);
    display_text(&local_84,10,(ushort)local_30);
  }
  if (*(char *)(iVar10 + 0x29a) == '\0') {
    return;
  }
  display_text(&local_74,10,ypos);
  display_text(&local_60,10,(ushort)local_34);
  return;
}

