void FUN_80021810(void)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  char character;
  ushort uVar4;
  uint uVar5;
  undefined4 unaff_r4;
  undefined4 unaff_r5;
  undefined4 unaff_r6;
  int iVar6;
  undefined4 unaff_r7;
  uint uVar7;
  undefined4 unaff_r8;
  uint uVar8;
  int iVar9;
  short *psVar10;
  int iVar11;
  ushort *puVar12;
  undefined in_stack_ffffffd0;
  undefined uVar13;
  undefined2 uVar14;
  short sVar15;
  undefined4 in_stack_ffffffd8;
  
  uVar4 = convert_color(DAT_80021a54);
  select_font(PTR_FONT_1_80021a58);

  FUN_80021168();

  FUN_8002098c();

  set_font_paint_mode(2);

  uVar7 = 0;
  uVar8 = 0;

  while( true )
  {
    while( true )
    {
      iVar6 = DAT_80021a5c;
      iVar9 = uVar7 * 5 + uVar8;

      if (*(char *)(DAT_80021a5c + iVar9) == '\0')
      {
        return;
      }

      set_display_fg_color(0);
      iVar11 = uVar7 * -0x1b;
      sVar1 = (short)(uVar8 * 0x91);
      sVar15 = (short)iVar11;

      display_fill_rect(sVar1 + 2,sVar15 + 0x1c4,sVar1 + 0x92,sVar15 + 0x1de);

      set_display_fg_color(DAT_80021a60);

      uVar13 = 0;
      uVar14 = 0;

      display_fill_rounded_rect(sVar1 + 3,sVar15 + 0x1c5,sVar1 + 0x91,sVar15 + 0x1dd,2);

      if (*(byte *)(iVar6 + iVar9) < 0xd)
      {
        set_display_fg_color(DAT_80021a64);
        display_fill_rect(sVar1 + 6,(short)iVar11 + 0x1c8,sVar1 + 0x18,(short)iVar11 + 0x1da);
        set_display_fg_color(0);
        character = '1';
      }
      else
      {
        set_display_fg_color(DAT_80021a68);
        display_fill_rect(sVar1 + 6,(short)iVar11 + 0x1c8,sVar1 + 0x18,(short)iVar11 + 0x1da);
        set_display_fg_color(0);
        character = '2';
      }

      display_character(character, (uint16)CONCAT412(unaff_r4,CONCAT48(in_stack_ffffffd8, CONCAT44(iVar11,CONCAT22(uVar14,CONCAT11(uVar13,in_stack_ffffffd0))))),(uint16)CONCAT412(unaff_r8,CONCAT48(unaff_r7,CONCAT44(unaff_r6,unaff_r5))));

      iVar3 = DAT_80021a74;
      piVar2 = Global_Frame_Buffer_Pointer;
      sVar15 = (short)iVar11;
      iVar11 = uVar7 * DAT_80021a6c;
      uVar5 = 0;
      iVar6 = iVar6 + iVar9 * 4;

      do
      {
        iVar9 = 0x34;
        puVar12 = (ushort *)(*piVar2 + (uVar5 * 800 + iVar11 * 0x20 + uVar8 * 0x91) * 2 + iVar3);
        psVar10 = (short *)(*(int *)(iVar6 + 0x78) + uVar5 * 0x68);
        do
        {
          if (*psVar10 != 0)
          {
            *puVar12 = uVar4;
          }

          iVar9 = iVar9 + -1;
          puVar12 = puVar12 + 1;
          psVar10 = psVar10 + 1;
        } while (iVar9 != 0);

        uVar5 = uVar5 + 1 & 0xfffeffff;
      } while (uVar5 < 0x10);

      set_display_fg_color(DAT_80021a54);
      display_text(*(char **)(iVar6 + 0x18),sVar1 + 0x55,sVar15 + 0x1cb);

      uVar8 = uVar8 + 1 & 0xfffeffff;

      if (4 < uVar8)
        break;

      if (uVar8 == 4 && uVar7 == 4)
      {
        return;
      }
    }

    uVar7 = uVar7 + 1 & 0xfffeffff;
    if (4 < uVar7)
      break;

    uVar8 = 0;
  }
  return;
}

