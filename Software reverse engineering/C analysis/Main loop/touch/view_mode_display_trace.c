
//Used to draw the trace data when loaded from picture or wave file

void view_mode_display_trace(void)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  uint uVar9;
  byte *unaff_r5;
  int count;
  byte *unaff_r7;
  code *UNRECOVERED_JUMPTABLE;
  bool bVar10;
  
  pcVar3 = DAT_8002b8b8;    //0x8019D5A0 base of settings

  if (DAT_8002b8b8[0x18] != '\0')  //triggerflag2
  {
    set_frame_to_global_pointer();
    set_display_fg_color(0);
    display_fill_rect(2,0x2f,(ushort)DAT_8002b8c0,(ushort)DAT_8002b8bc);
    display_draw_grid();
  }

  if (pcVar3[0x17] != '\0')   //triggerflag1
  {
    set_frame_to_global_pointer();

    if (*(char *)(DAT_8002b8c4 + 7) == '\0')  //0x80361378 + 7  = xy display mode
    {
      if (*pcVar3 != '\0')  //Channel 1 enable
      {
        //x start pos, offset, x end pos, buffer, color
        display_trace((uint)*(ushort *)(pcVar3 + 0x1a),0,(uint)*(ushort *)(pcVar3 + 0x1c),DAT_8002b8cc,DAT_8002b8d8);  //0x801C374A  = channel1ypoints
      }

      if (pcVar3[0xc] != '\0')  //Channel 2 enable
      {
        display_trace((uint)*(ushort *)(pcVar3 + 0x1a),0,(uint)*(ushort *)(pcVar3 + 0x1c),DAT_8002b8e0,DAT_8002b8dc);  //0x801C3F1A  = channel2ypoints
      }
    }
    else
    {
      //XY display mode
      set_frame_to_global_pointer();
      set_display_fg_color(DAT_8002b8c8);  //0x00FF00FF  purple

      if (*(ushort *)(pcVar3 + 0x1c) < 2)   //Number of samples
      {
        *(undefined2 *)(pcVar3 + 0x1c) = 2;
      }

      uVar9 = 1;
      iVar6 = *(ushort *)(pcVar3 + 0x1c) - 2;
      bVar10 = (int)(*(ushort *)(pcVar3 + 0x1c) - 3) < 0;

      if (1 < iVar6)
      {
        unaff_r5 = DAT_8002b8cc;  //0x801C374A
      }

      if (iVar6 != 1 && bVar10 == SBORROW4(iVar6,1))
      {
        unaff_r7 = unaff_r5 + 2000;  //0x801C3F1A
      }

      if (iVar6 != 1 && bVar10 == SBORROW4(iVar6,1))
      {
        do
        {
          display_draw_line(*(ushort *)(unaff_r5 + uVar9 * 2) + 0x96,(uint)*(ushort *)(unaff_r7 + uVar9 * 2),*(ushort *)((int)(unaff_r5 + uVar9 * 2) + 2) + 0x96,(uint)*(ushort *)((int)(unaff_r7 + uVar9 * 2) + 2));
          uVar9 = uVar9 + 1 & 0xfffeffff;
        } while ((int)uVar9 < (int)(*(ushort *)(pcVar3 + 0x1c) - 2));
      }
    }

    cVar1 = pcVar3[4];
    bVar10 = cVar1 != '\0';

    if (bVar10)
    {
      cVar1 = *pcVar3;
    }

    if ((bVar10 && cVar1 != '\0') && (8 < (byte)pcVar3[10]))
    {
      display_channel1_fft();
    }

    cVar1 = pcVar3[0x10];
    bVar10 = cVar1 != '\0';

    if (bVar10)
    {
      cVar1 = pcVar3[0xc];
    }

    if ((bVar10 && cVar1 != '\0') && (8 < (byte)pcVar3[10]))
    {
      set_display_fg_color(0);
      display_fill_rect(3,0x81,0x2d5,0xd1);
      calculate_channel2_fft();
      set_display_fg_color(DAT_8002b8d0);
      puVar4 = DAT_8002b8d4;
      uVar9 = 0;
      *DAT_8002b8d4 = DAT_8002b8d4[1];

      do
      {
        puVar7 = puVar4 + uVar9;

        if (0x50 < *puVar7)
        {
          *puVar7 = 0x50;
        }

        display_draw_vert_line((short)uVar9 + 3,0xd1 - *puVar7,0xd1);
        uVar9 = uVar9 + 1 & 0xfffeffff;
      } while (uVar9 < 0x2d3);
    }

    FUN_80021810();

    display_draw_trace_pointers();
  }

  uVar9 = DAT_8002b8bc;
  iVar2 = Start_Of_Screen_Mem;
  iVar6 = Screen_Frame_Buffer;

  if (pcVar3[0x18] == '\0')
  {
    return;
  }

  uVar8 = 0x2e;
  count = DAT_8002b8bc + 0xf6;

  if (DAT_8002b8bc < 0x2f)  //0x000001DF
  {
    return;
  }

  do
  {
    iVar5 = uVar8 * 800 + 2;
    copy_short((void *)(iVar2 + iVar5 * 2),(void *)(iVar6 + iVar5 * 2),count);
    uVar8 = uVar8 + 1;
  } while (uVar8 < uVar9);

  return;
}


