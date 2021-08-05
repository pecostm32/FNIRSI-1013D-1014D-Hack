//----------------------------------------------------------------------------------------------------
//void FUN_80009af4(void)

void display_draw_grid(void)
{
  int iVar1;
  int *piVar2;
  int iVar3;
  ushort uVar4;
  ushort *puVar5;
  int iVar6;
  int iVar7;
  ushort xend;
  uint uVar8;
  int iVar9;
  
  //                                     grid brightness
  //      0x0000A3D7                     0x80361378                 0000A3D7
  uVar8 = DAT_80009e48 * (uint)*(byte *)(DAT_80009e44 + 3) * 0xff + DAT_80009e48 >> 0x16;

  //Make it a grey shade
  uVar8 = uVar8 << 0x10 | uVar8 << 8 | uVar8;

  uVar4 = convert_color(uVar8);

  //Use it as a color
  set_display_fg_color(uVar8);

  iVar1 = DAT_80009e4c;
  xend = (ushort)DAT_80009e4c;            //0x000002D6

  display_draw_horz_line(0xf9,2,xend);
  display_draw_vert_line(0x16c,0x2e,0x1c1);

  iVar9 = 0x16c;

  do
  {
    display_draw_vert_line((ushort)iVar9,0xf7,0xfb);
    iVar9 = (iVar9 + 5) * 0x10000 >> 0x10;
  } while (iVar9 < iVar1);

  iVar9 = 0x16c;

  do
  {
    display_draw_vert_line((ushort)iVar9,0xf7,0xfb);
    iVar9 = (iVar9 + -5) * 0x10000 >> 0x10;
  } while (2 < iVar9);

  iVar9 = 0xf9;

  do
  {
    display_draw_horz_line((ushort)iVar9,0x16a,0x16e);
    iVar9 = (iVar9 + 5) * 0x10000 >> 0x10;
  } while (iVar9 < 0x1c1);

  iVar9 = 0xf9;

  do
  {
    display_draw_horz_line((ushort)iVar9,0x16a,0x16e);
    piVar2 = Global_Frame_Buffer_Pointer;
    iVar9 = (iVar9 + -5) * 0x10000 >> 0x10;
  } while (0x2e < iVar9);

  iVar9 = 0xf9;  //249 center y pos

  do
  {
    iVar6 = 0x24;
    puVar5 = (ushort *)(*piVar2 + iVar9 * 0x640 + 0x2d8);   //+728 (pixel 364)
    *puVar5 = uVar4;

    do
    {
      puVar5[5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 10;
      *puVar5 = uVar4;
    } while (iVar6 != 0);

    iVar6 = 0x24;
    puVar5 = (ushort *)(*piVar2 + iVar9 * 0x640 + 0x2d8);
    *puVar5 = uVar4;

    do
    {
      puVar5[-5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -10;
      *puVar5 = uVar4;
    } while (iVar6 != 0);

    iVar9 = (iVar9 + 0x32) * 0x10000 >> 0x10;  //+50
  } while (iVar9 < 0x1df);

  iVar9 = 0xf9;

  do
  {
    iVar6 = 0x24;
    puVar5 = (ushort *)(*piVar2 + iVar9 * 0x640 + 0x2d8);
    *puVar5 = uVar4;

    do
    {
      puVar5[5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 10;
      *puVar5 = uVar4;
    } while (iVar6 != 0);

    iVar6 = 0x24;
    puVar5 = (ushort *)(*piVar2 + iVar9 * 0x640 + 0x2d8);
    *puVar5 = uVar4;

    do
    {
      puVar5[-5] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -10;
      *puVar5 = uVar4;
      iVar7 = DAT_80009e54;
    } while (iVar6 != 0);

    iVar9 = (iVar9 + -0x32) * 0x10000 >> 0x10;
  } while (0x32 < iVar9);

  iVar9 = 0;

  do
  {
    iVar6 = 4;
    puVar5 = (ushort *)(*piVar2 + iVar9 * 8000 + iVar7);

    do
    {
      puVar5[0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 100;
      *puVar5 = uVar4;
    } while (iVar6 != 0);

    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x28);

  iVar9 = 0;

  do
  {
    iVar6 = 4;
    puVar5 = (ushort *)(*piVar2 + iVar9 * -8000 + iVar7);

    do
    {
      puVar5[0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + 100;
      *puVar5 = uVar4;
      iVar3 = DAT_80009e58;
    } while (iVar6 != 0);

    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x29);

  iVar9 = 0;

  do
  {
    iVar6 = 4;
    puVar5 = (ushort *)(*piVar2 + iVar9 * 8000 + iVar3);

    do
    {
      puVar5[-0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -100;
      *puVar5 = uVar4;
    } while (iVar6 != 0);

    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x28);

  iVar9 = 0;

  do
  {
    iVar6 = 4;
    puVar5 = (ushort *)(*piVar2 + iVar9 * -8000 + iVar3);

    do
    {
      puVar5[-0x32] = uVar4;
      iVar6 = iVar6 + -1;
      puVar5 = puVar5 + -100;
      *puVar5 = uVar4;
    } while (iVar6 != 0);

    iVar9 = (iVar9 + 1) * 0x10000 >> 0x10;
  } while (iVar9 < 0x29);

  display_draw_horz_line(0x2e,2,xend);
  display_draw_horz_line(0x1c1,2,xend);
  display_draw_vert_line(2,0x2e,0x1c1);
  display_draw_vert_line(xend,0x2e,0x1c1);

  return;
}

//----------------------------------------------------------------------------------------------------
//void FUN_8000b5cc(void)

void display_draw_trace_pointers(void)
{
  short sVar1;
  char *pcVar2;
  undefined4 uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  
  pcVar2 = DAT_8000b8d8;                                                   //0x8019D5A0 base of settings
  uVar4 = DAT_8000b8dc - 7;                                                //0x000001C1 - 7 (449 - 7) (end of y on screen) (pointers 7 pixels wide???)
  uVar7 = DAT_8000b8dc - (uint)*(ushort *)(DAT_8000b8d8 + 6) & 0xffff;     //0x8019D5A6 (short)  channel 1 trace screen offset
  uVar6 = DAT_8000b8dc - (uint)*(ushort *)(DAT_8000b8d8 + 0x12) & 0xffff;  //0x8019D5B2 (short)  channel 2 trace screen offset
  uVar5 = DAT_8000b8dc - (uint)*(ushort *)(DAT_8000b8d8 + 0x26) & 0xffff;  //0x8019D5C6 (short)  trigger level screen offset
  uVar8 = *(ushort *)(DAT_8000b8d8 + 0x24) + 2 & 0xfffeffff;               //0x8019D5C4 (short)  trigger position on screen

  if (uVar7 < 0x35)  //Limit on top line of screen
  {
    uVar7 = 0x35;
  }
  else
  {
    if (uVar4 < uVar7)  //limit on end of screen
    {
      uVar7 = uVar4;
    }
  }

  if (uVar6 < 0x35)
  {
    uVar6 = 0x35;
  }
  else 
  {
    if (uVar4 < uVar6)
    {
      uVar6 = uVar4;
    }
  }

  if (uVar5 < 0x35)
  {
    uVar5 = 0x35;
  }
  else
  {
    if (uVar4 < uVar5)
    {
      uVar5 = uVar4;
    }
  }

  if (uVar8 < 10)  //trigger position limit left side of screen
  {
    uVar8 = 10;
  }
  else
  {
    if (DAT_8000b8e0 < uVar8)  //0x000002CE 718 right side of screen
    {
      uVar8 = DAT_8000b8e0;
    }
  }

  if (*DAT_8000b8d8 != '\0')  //Channel 1 enable
  {
    set_display_fg_color(DAT_8000b8e4);  //0x00FFFF00 yellow
    uVar4 = uVar7;

    do
    {
      display_draw_horz_line((ushort)uVar4,2,0x15 - ((short)uVar7 - (ushort)uVar4));
      uVar4 = uVar4 - 1 & 0xffff;
    } while ((int)(uVar7 - 8) < (int)uVar4);

    uVar4 = uVar7;

    while (uVar4 < uVar7 + 8)
    {
      display_draw_horz_line((ushort)uVar4,2,0x15 - ((ushort)uVar4 - (short)uVar7));
      uVar4 = uVar4 + 1 & 0xfffeffff;
    }

    set_display_fg_color(0);
    select_font(PTR_FONT_0_8000b8e8);  //font_0

    display_character(0x31,6,(int)((uVar7 - 7) * 0x10000) >> 0x10);  //'1'
  }

  if (pcVar2[0xc] != '\0')  //Channel 2 enable
  {
    set_display_fg_color(DAT_8000b8ec);
    uVar7 = uVar6;

    do
    {
      display_draw_horz_line((ushort)uVar7,2,0x15 - ((short)uVar6 - (ushort)uVar7));
      uVar7 = uVar7 - 1 & 0xffff;
    } while ((int)(uVar6 - 8) < (int)uVar7);

    uVar7 = uVar6;

    while (uVar7 < uVar6 + 8)
    {
      display_draw_horz_line((ushort)uVar7,2,0x15 - ((ushort)uVar7 - (short)uVar6));
      uVar7 = uVar7 + 1 & 0xfffeffff;
    }

    set_display_fg_color(0);
    select_font(PTR_FONT_0_8000b8e8);

    display_character(0x32,6,(int)((uVar6 - 7) * 0x10000) >> 0x10);  //'2'
  }

  if (10 < (byte)pcVar2[10])  //time base setting (no pointers from 50S/div - 20mS/div)
  {
    set_display_fg_color(0xff00);

    uVar3 = DAT_8000b8f0;
    uVar7 = uVar5;

    do
    {
      display_draw_horz_line((ushort)uVar7,((short)uVar5 - (ushort)uVar7) + 0x2c3,(ushort)uVar3);
      uVar7 = uVar7 - 1 & 0xffff;
    } while ((int)(uVar5 - 8) < (int)uVar7);

    uVar7 = uVar5;

    while (uVar7 < uVar5 + 8)
    {
      display_draw_horz_line((ushort)uVar7,((ushort)uVar7 - (short)uVar5) + 0x2c3,(ushort)uVar3);
      uVar7 = uVar7 + 1 & 0xfffeffff;
    }

    set_display_fg_color(0);
    select_font(PTR_FONT_3_8000b8f4); //font_3

    display_character(0x54,0x2cc,(int)((uVar5 - 7) * 0x10000) >> 0x10);  //'T'

    set_display_fg_color(0xff00);

    uVar7 = uVar8;

    do
    {
      sVar1 = (short)uVar8;
      display_draw_vert_line((ushort)uVar7,0x30,0x3f - (sVar1 - (ushort)uVar7));
      uVar7 = uVar7 - 1 & 0xffff;
    } while ((int)(uVar8 - 7) < (int)uVar7);

    uVar7 = uVar8 + 7;

    if (uVar7 <= uVar8)
    {
      return;
    }

    do
    {
      display_draw_vert_line((ushort)uVar8,0x30,0x3f - ((ushort)uVar8 - sVar1));
      uVar8 = uVar8 + 1 & 0xfffeffff;
    } while (uVar8 < uVar7);
    return;
  }

  return;
}

//----------------------------------------------------------------------------------------------------

void display_draw_volt_cursors(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = DAT_8000ebec;
  set_frame_to_global_pointer();
  set_display_fg_color(uVar1);
  uVar1 = DAT_8000ebf4;              //0x000002D3
  iVar2 = DAT_8000ebf0;              //0x801FA44C  variables base
  uVar3 = 5;
  do {
    display_draw_horz_line(*(ushort *)(iVar2 + 0x9c),(ushort)uVar3,(ushort)uVar3 + 3);
    uVar3 = uVar3 + 6 & 0xfffeffff;
  } while (uVar3 < uVar1);
  uVar3 = 5;
  do {
    display_draw_horz_line(*(ushort *)(iVar2 + 0x9e),(ushort)uVar3,(ushort)uVar3 + 3);
    uVar3 = uVar3 + 6 & 0xfffeffff;
  } while (uVar3 < uVar1);
  return;
}

//----------------------------------------------------------------------------------------------------

void display_draw_time_cursors(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar1 = DAT_8000eb78;              //0x0000AA11  Color

  set_frame_to_global_pointer();
  set_display_fg_color(uVar1);

  uVar1 = DAT_8000eb80;              //0x000001BF  Position
  iVar2 = DAT_8000eb7c;              //0x801FA44C  variables base
  uVar3 = 0x30;

  do
  {
    display_draw_vert_line(*(ushort *)(iVar2 + 0x94), (ushort)uVar3, (ushort)uVar3 + 3);
    uVar3 = uVar3 + 6 & 0xfffeffff;
  } while (uVar3 < uVar1);

  uVar3 = 0x30;
  do {
    display_draw_vert_line(*(ushort *)(iVar2 + 0x96),(ushort)uVar3,(ushort)uVar3 + 3);
    uVar3 = uVar3 + 6 & 0xfffeffff;
  } while (uVar3 < uVar1);
  return;
}

//----------------------------------------------------------------------------------------------------

