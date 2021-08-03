//Some init function that does something with the SD card

void FUN_8000a024(void)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  undefined auStack688 [12];
  int local_2a4;
  int local_84;
  int local_80;
  uint local_7c;
  uint local_78;
  uint local_74;
  uint local_70;
  uint local_6c;
  uint local_58;
  uint local_48;
  uint local_40;
  uint local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  
  uVar4 = 0;
  uVar11 = 0;
  uVar10 = 0;
  uVar9 = 0;
  uVar8 = 0;
  uVar7 = 0;
  uVar6 = 0;
  uVar5 = 0;
  local_40 = 0;
  iVar2 = FUN_800337c4(auStack688,s_UTX_1013_bin_8000a40c,1);
  if (iVar2 != 0) {
    FUN_8003347c(auStack688);
    iVar2 = FUN_800337c4(auStack688,s_FSI_1013_bin_8000a41c,1);
    if (iVar2 != 0) {
      FUN_8003347c(auStack688);
      iVar2 = FUN_800337c4(auStack688,s_DAN_1013_bin_8000a42c,1);
      if (iVar2 != 0) {
        FUN_8003347c(auStack688);
        iVar2 = FUN_800337c4(auStack688,s_YPK_1013_bin_8000a43c,1);
        if (iVar2 != 0) {
          FUN_8003347c(auStack688);
          return;
        }
      }
    }
  }
  local_80 = FUN_800001cc(0x200000);
  local_84 = local_2a4;
  FUN_80033b18(auStack688,local_80,local_2a4,0);
  FUN_8003347c(auStack688);
  iVar2 = local_80 + local_84;
  local_2c = (uint)*(byte *)(iVar2 + -0x21) |
             (uint)*(byte *)(iVar2 + -0x22) << 8 |
             (uint)*(byte *)(iVar2 + -0x23) << 0x10 | (uint)*(byte *)(iVar2 + -0x24) << 0x18;
  local_30 = (uint)*(byte *)(iVar2 + -0x1d) |
             (uint)*(byte *)(iVar2 + -0x1f) << 0x10 | (uint)*(byte *)(iVar2 + -0x20) << 0x18 |
             (uint)*(byte *)(iVar2 + -0x1e) << 8;
  local_34 = (uint)*(byte *)(iVar2 + -0x19) |
             (uint)*(byte *)(iVar2 + -0x1b) << 0x10 | (uint)*(byte *)(iVar2 + -0x1c) << 0x18 |
             (uint)*(byte *)(iVar2 + -0x1a) << 8;
  local_78 = (uint)*(byte *)(iVar2 + -0x15) |
             (uint)*(byte *)(iVar2 + -0x17) << 0x10 | (uint)*(byte *)(iVar2 + -0x18) << 0x18 |
             (uint)*(byte *)(iVar2 + -0x16) << 8;
  local_48 = (uint)*(byte *)(iVar2 + -0x11) |
             (uint)*(byte *)(iVar2 + -0x13) << 0x10 | (uint)*(byte *)(iVar2 + -0x14) << 0x18 |
             (uint)*(byte *)(iVar2 + -0x12) << 8;
  local_38 = (uint)*(byte *)(iVar2 + -0xd) |
             (uint)*(byte *)(iVar2 + -0xe) << 8 |
             (uint)*(byte *)(iVar2 + -0xf) << 0x10 | (uint)*(byte *)(iVar2 + -0x10) << 0x18;
  local_70 = (uint)*(byte *)(iVar2 + -3);
  local_58 = (uint)*(byte *)(iVar2 + -9) |
             (uint)*(byte *)(iVar2 + -0xb) << 0x10 | (uint)*(byte *)(iVar2 + -0xc) << 0x18 |
             (uint)*(byte *)(iVar2 + -10) << 8;
  local_6c = (uint)*(byte *)(iVar2 + -4);
  local_74 = (uint)*(byte *)(iVar2 + -2);
  local_7c = (uint)*(byte *)(iVar2 + -1);
  if (local_84 != 0x24) {
    uVar3 = 0;
    do {
      bVar1 = *(byte *)(local_80 + uVar3);
      uVar4 = uVar4 + bVar1;
      if ((bVar1 & 0x80) != 0) {
        local_40 = local_40 + uVar3;
      }
      if ((bVar1 & 0x40) != 0) {
        uVar11 = uVar11 + uVar3;
      }
      if ((bVar1 & 0x20) != 0) {
        uVar10 = uVar10 + uVar3;
      }
      if ((bVar1 & 0x10) != 0) {
        uVar9 = uVar9 + uVar3;
      }
      if ((bVar1 & 8) != 0) {
        uVar8 = uVar8 + uVar3;
      }
      if ((bVar1 & 4) != 0) {
        uVar7 = uVar7 + uVar3;
      }
      if ((bVar1 & 2) != 0) {
        uVar6 = uVar6 + uVar3;
      }
      if ((bVar1 & 1) != 0) {
        uVar5 = uVar5 + uVar3;
      }
      uVar3 = uVar3 + 1;
    } while (uVar3 < local_84 - 0x24U);
  }
  if (uVar4 == local_2c) {
    uVar4 = local_40;
    if (local_40 == local_30) {
      uVar4 = local_34;
    }
    if (local_40 == local_30 && uVar11 == uVar4) {
      uVar4 = local_78;
      if (uVar10 == local_78) {
        uVar4 = local_48;
      }
      if (uVar10 == local_78 && uVar9 == uVar4) {
        uVar4 = local_38;
        if (uVar8 == local_38) {
          uVar4 = local_58;
        }
        if ((uVar8 == local_38 && uVar7 == uVar4) &&
           (uVar6 == ((uint)*(byte *)(iVar2 + -7) << 0x10 | (uint)*(byte *)(iVar2 + -8) << 0x18 |
                      (uint)*(byte *)(iVar2 + -6) << 8 | (uint)*(byte *)(iVar2 + -5)) &&
            uVar5 == (local_74 << 8 | local_70 << 0x10 | local_6c << 0x18 | local_7c))) {
          memclear((uint)DAT_8000a548,1000);
          flash_write___(0x27000,DAT_8000a548,1000);
          sys_init_watchdog();
          return;
        }
      }
    }
  }
  *(undefined *)(DAT_8000a524 + 2) = 100;
  fpga_write_cmd('8');
  fpga_write_data(-0x16);
  fpga_write_data((uchar)DAT_8000a528);
  set_display_fg_color(0xff0000);
  set_font_paint_mode(0);
  select_font(PTR_FONT_7_8000a52c);
  display_text(s_System_file_damaged_____8000a530,0x32,0x32);
  setup_usb_int();
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}

