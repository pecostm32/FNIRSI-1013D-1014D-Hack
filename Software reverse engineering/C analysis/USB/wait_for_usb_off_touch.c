void wait_for_usb_off_touch(void)

{
  undefined *puVar1;
  
  tp_i2c_read_status();
  if (0xa0 < *(ushort *)(PTR_DAT_80029fe4 + 2) - 0x59) {
    return;
  }
  if (*(ushort *)(PTR_DAT_80029fe4 + 4) < 0xd3) {
    return;
  }
  if (0x13f < *(ushort *)(PTR_DAT_80029fe4 + 4)) {
    return;
  }
  if (*PTR_DAT_80029fe4 == '\0') {
    return;
  }


  set_frame_to_global_pointer();
  set_display_fg_color(0);
  display_fill_rect(0x58,0xd2,0xfc,(ushort)DAT_80029fe8);
  set_display_fg_color(DAT_80029fec);
  select_font(PTR_FONT_5_80029ff0);
  set_font_paint_mode(2);
  display_text(s_ON_/_OFF_80029ff4,0x7d,0xfe);
  copy_frame_to_screen();
  *PTR_DAT_8002a000 = 0;

  tp_i2c_read_status();
  puVar1 = PTR_DAT_8002b120;

  if (*PTR_DAT_8002b120 == '\0')
  {
    return;
  }

  do
  {
    tp_i2c_read_status();
  } while (*puVar1 != '\0');
  return;
}

