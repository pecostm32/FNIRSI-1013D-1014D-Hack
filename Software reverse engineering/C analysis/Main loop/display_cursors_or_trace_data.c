void display_cursors(void)

{
  char cVar1;
  undefined2 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined *puVar8;
  ushort uVar9;
  int iVar10;
  ushort *puVar11;
  int iVar12;
  undefined2 *puVar13;
  uint uVar14;
  uint uVar15;
  int iVar16;
  ushort uVar17;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar18;
  
  pcVar7 = DAT_8002b64c;
  puVar6 = PTR_DAT_8002b648;
  cVar1 = *PTR_DAT_8002b648;

  if ((cVar1 == '\x02') && ((DAT_8002b64c[0x21] != '\x01' || (DAT_8002b64c[0x3a] == '\x01'))))
  {
    DAT_8002b64c[0x18] = '\x01';
    pcVar7[0x17] = '\x01';
  }

  puVar8 = PTR_DAT_8002b65c;
  iVar5 = DAT_8002b658;
  iVar4 = DAT_8002b654;
  uVar17 = (ushort)DAT_8002b650;
  iVar16 = DAT_8002b654 + 2000;

  if (8 < (byte)pcVar7[10])
  {
    if (pcVar7[0x18] != '\0')
    {
      set_frame_to_global_pointer();
      set_display_fg_color(0);
      display_fill_rect(2,0x2f,uVar17,uVar17 - 0xfb);
      display_draw_grid();
    }

    if (pcVar7[0x17] == '\0')
      goto LAB_8002b414;

    FUN_8001b424(pcVar7 + 0x1a,pcVar7 + 0x1c);

    if (*pcVar7 != '\0')
    {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02'))
      {
        *(undefined2 *)(puVar8 + 0x12) = 400;
      }

      FUN_8000410c();

      cVar1 = pcVar7[0x21];
      bVar18 = cVar1 != '\0';

      if (bVar18)
      {
        cVar1 = pcVar7[0x21];
      }

      if (((!bVar18 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) && ((pcVar7[0x23] == '\x01' || (pcVar7[9] != '\0'))))
      {
        FUN_8000583c();
      }

      if (*(char *)(iVar5 + 7) == '\0')
      {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b654);
      }
    }

    if (pcVar7[0xc] == '\0')
    {
LAB_8002b2e8:
      if (*(char *)(iVar5 + 7) != '\0')
        goto LAB_8002b2f4;
    }
    else
    {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02'))
      {
        *(undefined2 *)(puVar8 + 0x14) = 400;
      }

      FUN_80006f28();
      cVar1 = pcVar7[0x21];
      bVar18 = cVar1 != '\0';

      if (bVar18) {
        cVar1 = pcVar7[0x21];
      }
      if (((!bVar18 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) &&
         ((pcVar7[0x23] == '\0' || (pcVar7[0x15] != '\0')))) {
        FUN_80008594();
      }
      if (*(char *)(iVar5 + 7) == '\0') {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b668);
        goto LAB_8002b2e8;
      }
LAB_8002b2f4:
      set_frame_to_global_pointer();
      set_display_fg_color(DAT_8002b66c);
      if (*(ushort *)(pcVar7 + 0x1c) < 2) {
        *(undefined2 *)(pcVar7 + 0x1c) = 2;
      }
      uVar15 = 1;
      if (1 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2)) {
        do {
          puVar11 = (ushort *)(iVar4 + uVar15 * 2);
          puVar13 = (undefined2 *)(iVar16 + uVar15 * 2);
          FUN_80018d30(*puVar11 + 0x96,*puVar13,puVar11[1] + 0x96,puVar13[1]);
          uVar15 = uVar15 + 1 & 0xfffeffff;
        } while ((int)uVar15 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2));
      }
    }
    cVar1 = pcVar7[4];
    bVar18 = cVar1 != '\0';
    if (bVar18) {
      cVar1 = *pcVar7;
    }
    if (bVar18 && cVar1 != '\0') {
      FUN_800043e4();
    }
    cVar1 = pcVar7[0x10];
    bVar18 = cVar1 != '\0';
    if (bVar18) {
      cVar1 = pcVar7[0xc];
    }
    if (bVar18 && cVar1 != '\0') {
      set_display_fg_color(0);
      display_fill_rect(3,0x81,0x2d5,0xd1);
      FUN_800075dc();
      set_display_fg_color(DAT_8002b670);
      puVar13 = DAT_8002b674;
      uVar15 = 0;
      *DAT_8002b674 = DAT_8002b674[1];
      do {
        puVar11 = puVar13 + uVar15;
        if (0x50 < *puVar11) {
          *puVar11 = 0x50;
        }
        display_draw_vert_line((short)uVar15 + 3,0xd1 - *puVar11,0xd1);
        uVar15 = uVar15 + 1 & 0xfffeffff;
      } while (uVar15 < 0x2d3);
    }
LAB_8002b414:
    iVar4 = DAT_8002b678;
    if (pcVar7[0x18] == '\0') {
      return;
    }
    if (*(char *)(DAT_8002b678 + 0x292) != '\0') {
      display_draw_time_cursors();
    }
    if (*(char *)(iVar4 + 0x29a) != '\0') {
      display_draw_volt_cursors();
    }
    cVar1 = *(char *)(iVar4 + 0x292);
    bVar18 = cVar1 == '\0';
    if (bVar18) {
      cVar1 = *(char *)(iVar4 + 0x29a);
    }
    if (!bVar18 || cVar1 != '\0') {
      FUN_8000ebf8();
    }

    display_draw_trace_pointers();

    FUN_80021810();

    uVar15 = DAT_8002b67c;

    //Copy rect to screen
    iVar5 = Start_Of_Screen_Mem;
    iVar4 = Screen_Frame_Buffer;
    uVar14 = 0x2e;
    iVar16 = DAT_8002b67c + 0xf6;

    if (DAT_8002b67c < 0x2f)
    {
      return;
    }

    do
    {
      iVar10 = uVar14 * 800 + 2;
      copy_short((void *)(iVar5 + iVar10 * 2),(void *)(iVar4 + iVar10 * 2),iVar16);
      uVar14 = uVar14 + 1;
    } while (uVar14 < uVar15);
    return;
    //Down to here copy rect to screen
  }

  uVar9 = (ushort)(byte)pcVar7[0x3a];

  //Run stop mode
  if (uVar9 != 0)
  {
    //Done when in stop mode
    return;
  }

  if (cVar1 != '\x02')
  {
    uVar9 = *(ushort *)PTR_DAT_8002b65c;
  }
  else
  {
    *(undefined2 *)PTR_DAT_8002b65c = 0;
  }

  if (cVar1 == '\x02' || uVar9 == 0) {
    set_frame_to_global_pointer();
    set_display_fg_color(0);
    uVar9 = (ushort)DAT_8002b67c;
    display_fill_rect(2,0x2f,uVar17,uVar9);
    display_draw_grid();
    display_draw_trace_pointers();
    copy_rect_to_screen(2,0x2e,uVar9 + 0xf7,uVar9);
    set_screen_to_global_pointer();
  }
  iVar10 = DAT_8002b680;
  if (*pcVar7 != '\0') {
    set_screen_to_global_pointer();
    iVar12 = iVar10 - (uint)*DAT_8002b684;
    *(short *)(puVar8 + 0x16) = (short)iVar12;
    iVar12 = iVar12 * 0x10000 >> 0x10;
    if (iVar12 < 0x2f) {
      iVar12 = 0x2f;
    }
    else {
      if (0x1c0 < iVar12) {
        iVar12 = 0x1c0;
      }
    }
    *(short *)(puVar8 + 0x16) = (short)iVar12;
    if (*(char *)(iVar5 + 7) == '\0') {
      FUN_800067ac();
    }
  }
  if (pcVar7[0xc] == '\0') {
LAB_8002b590:
    if (*(char *)(iVar5 + 7) == '\0') goto LAB_8002b624;
  }
  else {
    set_screen_to_global_pointer();
    iVar10 = iVar10 - (uint)*DAT_8002b688;
    *(short *)(puVar8 + 0x18) = (short)iVar10;
    iVar10 = iVar10 * 0x10000 >> 0x10;
    if (iVar10 < 0x2f) {
      iVar10 = 0x2f;
    }
    else {
      if (0x1c0 < iVar10) {
        iVar10 = 0x1c0;
      }
    }
    *(short *)(puVar8 + 0x18) = (short)iVar10;
    if (*(char *)(iVar5 + 7) == '\0') {
      FUN_800094f8();
      goto LAB_8002b590;
    }
  }
  if (*(short *)puVar8 == 0) {
    *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);
    *(undefined2 *)(puVar8 + 4) = *(undefined2 *)(puVar8 + 0x18);
  }
  set_display_fg_color(DAT_8002b66c);
  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x96,*(undefined2 *)(puVar8 + 4),
               *(ushort *)(puVar8 + 0x16) + 0x96,*(undefined2 *)(puVar8 + 0x18));
  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x97,*(ushort *)(puVar8 + 4) + 1,
               *(ushort *)(puVar8 + 0x16) + 0x97,*(ushort *)(puVar8 + 0x18) + 1);
  *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);
  uVar2 = *(undefined2 *)(puVar8 + 0x18);
  *(undefined2 *)(puVar8 + 4) = uVar2;
  uVar17 = *(ushort *)puVar8;
  *(undefined2 *)(iVar4 + (uint)uVar17 * 2) = *(undefined2 *)(puVar8 + 0x16);
  *(undefined2 *)(iVar16 + (uint)uVar17 * 2) = uVar2;
LAB_8002b624:
  sVar3 = *(short *)puVar8;
  *(ushort *)puVar8 = sVar3 + 1U;
  if (0x2cf < (ushort)(sVar3 + 1U)) {
    *(undefined2 *)puVar8 = 0;
  }
                    // WARNING: Could not recover jumptable at 0x8002b644. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}

