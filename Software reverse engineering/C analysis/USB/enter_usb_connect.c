
//Called to draw the USB connect window and to enable th USB interrupts

void enter_usb_connect(void)

{
  uint uVar1;
  char cVar2;
  uint uVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  undefined2 *puVar8;
  ushort yend;
  ushort yend_00;
  ushort uVar9;
  uint uVar10;
  uint uVar11;
  int iStack28;
  
  set_frame_to_global_pointer();

  set_display_fg_color(0);
  display_fill_rect(0,0,(ushort)DAT_800221e0 + 0x140,(ushort)DAT_800221e0);  //Clear the screen

  uVar3 = DAT_800221e4;

  set_display_fg_color(DAT_800221e4);  //0x00AAAAAA

  iStack28 = DAT_800221e8;

  yend_00 = (ushort)DAT_800221e8;      //0x00000131

  display_fill_rounded_rect(0x1d6,0x73,0x2d0,yend_00,2);

  display_fill_rect(0x244,yend_00,0x262,yend_00 + 0x14);

  uVar9 = yend_00 + 0x1e;  //335  0x14F

  display_fill_rounded_rect(0x226,yend_00 + 0x14,0x280,uVar9,2);

  display_fill_rect(0x226,uVar9 & 0xfffa,0x280,uVar9);

  display_fill_rounded_rect(0x50,200,0x104,uVar9,2);


  display_fill_rect(0xd2,0xbe,0xdb,200);


  display_draw_vert_line(0xd5,0x99,0xbd);
  display_draw_vert_line(0xd6,0x99,0xbd);
  display_draw_vert_line(0xd7,0x99,0xbd);
  display_draw_vert_line(0xd8,0x99,0xbd);

  uVar9 = yend_00 + 0x3c;   //0x16d
  display_draw_horz_line(0x95,0xd5,uVar9);
  display_draw_horz_line(0x96,0xd5,uVar9);
  display_draw_horz_line(0x97,0xd5,uVar9);
  display_draw_horz_line(0x98,0xd5,uVar9);

  yend = yend_00 - 0x2f;
  display_draw_vert_line(0x16a,0x99,yend);
  display_draw_vert_line(0x16b,0x99,yend);
  display_draw_vert_line(0x16c,0x99,yend);
  display_draw_vert_line(uVar9,0x99,yend);

  iStack28 = iStack28 + -0x23;
  FUN_80018c30(0x170,0xfb,6);
  display_draw_horz_line(0xff,0x16b,0x1d6);
  display_draw_horz_line(0x100,0x16b,0x1d6);
  display_draw_horz_line(yend_00 - 0x30,0x16b,0x1d6);
  display_draw_horz_line(yend,0x16b,0x1d6);
  display_fill_rect(0x1cd,0xfc,0x1d6,yend_00 - 0x2c);


  set_display_fg_color(0x55);
  display_fill_rect(0x1dd,0x7d,yend_00 + 0x198,0x120);

  display_fill_rect(0x58,0xd2,0xfc,0x142);

  set_display_fg_color(DAT_800221ec);
  display_draw_rect(0x1dd,0x7d,yend_00 + 0x198,0x120);
  display_draw_rect(0x58,0xd2,0xfc,0x142);


  set_display_fg_color(uVar3);
  select_font(PTR_FONT_5_800221f0);
  set_font_paint_mode(2);
  display_text(s_ON_/_OFF_800221f4,0x7d,0xfe);
  copy_frame_to_screen();

  puVar4 = PTR_DAT_80022200;   //0x80192f00
  *PTR_DAT_80022200 = 1;

  setup_usb_int();

  cVar2 = *puVar4;

  while (cVar2 != '\0')        //*0x80192f00 As long as it is set keep scanning
  {
    wait_for_usb_off_touch();
    cVar2 = *puVar4;
  }

  sunxi_udc_disable();

  resync_view_item_system_files();
}  



//This reloads the two system files and resyncs them with the files on the card????
void resync_view_item_system_files(void)
{
  puVar4 = PTR_DAT_8002a1b4;
  *PTR_DAT_8002a1b4 = 0;

  resync_view_item_system_file();

  *puVar4 = 1;
  uVar11 = 0;

  resync_view_item_system_file();
}



void resync_view_item_system_file(void)
{
  load_selected_system_file();
  setup_filename_list();
  uVar3 = DAT_8002a2a4;
  iVar5 = DAT_8002a2a0;
  uVar10 = 0;
  do {
    if (*(short *)(iVar5 + uVar10 * 2 + 0x1e) == 0) break;
    iVar6 = f_open(&stack0xfffffdc0,(char *)(uVar10 * 0xf + iVar5 + 0x7ee),1);
    if (iVar6 == 4) {
      if (uVar10 < uVar3) {
        iVar6 = iVar5 + (uVar10 - uVar11) * 2;
        puVar8 = (undefined2 *)(iVar6 + 0x1e);
        puVar7 = (undefined2 *)(iVar6 + 0x1c);
        if ((uVar3 - uVar10 & 1) != 0) {
          puVar8 = (undefined2 *)(iVar6 + 0x20);
          puVar7 = (undefined2 *)(iVar6 + 0x1e);
          *puVar7 = *puVar8;
        }
        uVar1 = (uVar3 - uVar10) * 0x8000 >> 0x10;
        while (uVar1 != 0) {
          puVar7[1] = puVar8[1];
          puVar8 = puVar8 + 2;
          uVar1 = uVar1 - 1 & 0xffff;
          puVar7 = puVar7 + 2;
          *puVar7 = *puVar8;
        }
      }
      uVar11 = uVar11 + 1 & 0xfffeffff;
    }
    f_close(&stack0xfffffdc0);
    uVar10 = uVar10 + 1 & 0xfffeffff;
  } while (uVar10 < uVar3);
  *(undefined2 *)(DAT_8002a2a8 + 0xec) = 0;
  save_selected_system_file();
  return;
}


