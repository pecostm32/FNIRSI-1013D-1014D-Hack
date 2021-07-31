//---------------------------------------------------------------------------------------------------
//save screen under menu item

void FUN_80002afc(void)

{
  uint uVar1;
  uint uVar2;
  undefined2 *puVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  undefined2 *puVar11;
  uint uVar12;
  int iVar13;
  undefined2 *puVar14;
  
  iVar6 = Screen_Frame_Buffer_2;
  iVar5 = Start_Of_Screen_Mem;
  uVar10 = *(ushort *)(PTR_DAT_80002b38 + 6) + 0xec & 0xfffeffff;
  uVar9 = *(ushort *)(PTR_DAT_80002b38 + 4) + 0x1bb & 0xfffeffff;
  uVar8 = *(ushort *)(PTR_DAT_80002b38 + 6) + 0xaf & 0xfffeffff;
  uVar7 = *(ushort *)(PTR_DAT_80002b38 + 4) + 0xf4 & 0xfffeffff;
  if (uVar8 < uVar10) {
    uVar12 = uVar9 - uVar7;
    uVar1 = uVar12 * 0x8000 >> 0x10;
    do {
      if (uVar7 < uVar9) {
        iVar13 = uVar7 + uVar8 * 800;
        puVar11 = (undefined2 *)(iVar5 + iVar13 * 2);
        puVar14 = (undefined2 *)(iVar6 + iVar13 * 2);
        uVar2 = uVar1;
        puVar3 = puVar14 + -1;
        puVar4 = puVar11 + -1;
        if ((uVar12 & 1) != 0) {
          *puVar14 = *puVar11;
          puVar3 = puVar14;
          puVar4 = puVar11;
        }
        while (uVar2 != 0) {
          puVar3[1] = puVar4[1];
          puVar3[2] = puVar4[2];
          uVar2 = uVar2 - 1 & 0xffff;
          puVar3 = puVar3 + 2;
          puVar4 = puVar4 + 2;
        }
      }
      uVar8 = uVar8 + 1 & 0xfffeffff;
    } while (uVar8 < uVar10);
    return;
  }
  return;
}

//---------------------------------------------------------------------------------------------------
//Slide in the bitmap

void FUN_80011154(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  ushort *puVar9;
  ushort *puVar10;
  ushort uVar11;
  
  uVar5 = convert_color(DAT_8001123c);
  set_screen_to_global_pointer();
  iVar4 = DAT_8001124c;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80011244;
  puVar1 = PTR_TEXT_BITMAP_CALIB_START_80011240;
  uVar8 = 0xc5;
  do {
    uVar6 = 0;
    do {
      if (uVar8 < 0xc5) {
        uVar7 = 0xc5 - uVar8 & 0xffff;
        puVar9 = (ushort *)(puVar1 + (uVar6 * 0xc5 + uVar8) * 2);
        puVar10 = (ushort *)
                  (*piVar3 + ((*(ushort *)(puVar2 + 6) + uVar6) * 800 +
                             (uint)*(ushort *)(puVar2 + 4)) * 2 + iVar4);
        do {
          uVar11 = *puVar9;
          if (*puVar9 == 0) {
            uVar11 = uVar5;
          }
          uVar7 = uVar7 - 1 & 0xffff;
          *puVar10 = uVar11;
          puVar9 = puVar9 + 1;
          puVar10 = puVar10 + 1;
        } while (uVar7 != 0);
      }
      uVar6 = uVar6 + 1 & 0xfffeffff;
    } while (uVar6 < 0x3c);
    uVar8 = (uVar8 - (uVar8 * DAT_80011250 + 0xa3d7 >> 0x14)) - 1 & 0xffff;
  } while (1 < uVar8);
  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}

//---------------------------------------------------------------------------------------------------
//Display the bitmap with the knob

void FUN_80010f08(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  ushort uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  undefined *puVar11;
  ushort *puVar12;
  int iVar13;
  uint uVar14;
  ushort *puVar15;
  ushort uVar16;
  
  uVar5 = convert_color(DAT_8001112c);
  uVar6 = convert_color(DAT_80011130);
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8001113c;
  puVar1 = PTR_TEXT_BITMAP_CALIB_START_80011138;
  iVar8 = DAT_80011134;
  uVar7 = 0;

  do
  {
    iVar13 = 0xc5;
    puVar12 = (ushort *)(puVar1 + uVar7 * 0x18a);
    puVar15 = (ushort *)(*piVar3 + ((uint)*(ushort *)(puVar2 + 4) + (*(ushort *)(puVar2 + 6) + uVar7) * 800) * 2 + iVar8);

    do
    {
      uVar16 = *puVar12;

      if (*puVar12 == 0)
      {
        uVar16 = uVar5;
      }

      iVar13 = iVar13 + -1;
      *puVar15 = uVar16;
      iVar4 = DAT_8001114c;
      iVar9 = DAT_80011148;
      puVar12 = puVar12 + 1;
      puVar15 = puVar15 + 1;
    } while (iVar13 != 0);

    uVar7 = uVar7 + 1 & 0xfffeffff;
  } while (uVar7 < 0x3c);

  if (*(char *)(DAT_80011144 + 9) == '\0')
  {
    uVar7 = 8;

    do
    {
      iVar8 = 0x42;
      puVar12 = (ushort *)(*piVar3 + ((uint)*(ushort *)(puVar2 + 4) + (*(ushort *)(puVar2 + 6) + uVar7) * 800) * 2 + iVar4);
      puVar15 = (ushort *)(puVar1 + uVar7 * 0x18a + 0xf4);

      do
      {
        uVar5 = *puVar15;
        if (*puVar15 == 0)
        {
          uVar5 = uVar6;
        }

        iVar8 = iVar8 + -1;
        *puVar12 = uVar5;
        puVar12 = puVar12 + 1;
        puVar15 = puVar15 + 1;
      } while (iVar8 != 0);
      uVar7 = uVar7 + 1 & 0xfffeffff;

    } while (uVar7 < 0x34);
  }
  else
  {
    uVar7 = 8;

    do
    {
      iVar13 = uVar7 * 0xc5;
      puVar11 = puVar1 + uVar7 * 0x18a;
      puVar15 = (ushort *)(*piVar3 + ((uint)*(ushort *)(puVar2 + 4) + (*(ushort *)(puVar2 + 6) + uVar7) * 800) * 2 + iVar9 + 2);
      *puVar15 = ~*(ushort *)(puVar11 + 0xf4);
      uVar5 = *(ushort *)(puVar11 + 0xf6);
      iVar8 = 0x20;
      puVar12 = (ushort *)(puVar11 + 0xf4);

      do
      {
        uVar6 = puVar12[2];
        puVar15[1] = ~uVar5;
        uVar5 = puVar12[3];
        iVar8 = iVar8 + -1;
        puVar15 = puVar15 + 2;
        *puVar15 = ~uVar6;
        puVar12 = puVar12 + 2;
      } while (iVar8 != 0);

      iVar8 = *(ushort *)(puVar2 + 6) + uVar7;
      uVar7 = uVar7 + 1 & 0xfffeffff;

      *(ushort *)(*piVar3 + (iVar8 * 800 + 0x41 + (uint)*(ushort *)(puVar2 + 4)) * 2 + 0x4489c) = ~*(ushort *)(puVar1 + (iVar13 + 0x41) * 2 + 0xf4);
    } while (uVar7 < 0x34);
  }

  //Draw the outline
  set_display_fg_color(DAT_80011150);  //0x00303030
  display_draw_rect(*(short *)(puVar2 + 4) + 0xf4,*(short *)(puVar2 + 6) + 0xaf,*(short *)(puVar2 + 4) + 0x1b8,*(short *)(puVar2 + 6) + 0xea);


  iVar13 = Start_Of_Screen_Mem;
  iVar8 = Screen_Frame_Buffer;
  uVar5 = *(ushort *)(puVar2 + 4);
  uVar10 = *(ushort *)(puVar2 + 6) + 0xaf & 0xfffeffff;
  uVar7 = uVar5 + 0xf4 & 0xfffeffff;
  uVar14 = *(ushort *)(puVar2 + 6) + 0xeb & 0xfffeffff;
  if (uVar14 <= uVar10) {
    return;
  }
  do {
    iVar9 = uVar7 + uVar10 * 800;
    copy_short((void *)(iVar13 + iVar9 * 2),(void *)(iVar8 + iVar9 * 2),
               ((uVar5 + 0x1b8 & 0xfffeffff) - uVar7) + 1);
    uVar10 = uVar10 + 1;
  } while (uVar10 < uVar14);
  return;
}

//---------------------------------------------------------------------------------------------------

void display_calibrating_text(void)

{
  undefined *puVar1;
  int *piVar2;
  undefined *puVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  ushort *puVar7;
  uint uVar8;
  ushort *puVar9;
  uint uVar10;
  ushort uVar11;
  uint uVar12;
  int iVar13;
  
  uVar5 = convert_color(DAT_8001137c);
  piVar2 = Global_Frame_Buffer_Pointer;
  puVar1 = PTR_DAT_80011384;
  iVar13 = DAT_80011380;
  uVar12 = 0;
  do
  {
    //Clear memory
    FUN_80000878(*piVar2 + (uint)*(ushort *)(puVar1 + 4) * 2 + (*(ushort *)(puVar1 + 6) + uVar12) * 0x640 + iVar13,0xae);

    iVar4 = DAT_80011390;
    puVar3 = PTR_TEXT_BITMAP_CALIBRATING_8001138c;
    uVar12 = uVar12 + 1 & 0xfffeffff;
  } while (uVar12 < 0x3c);

  uVar12 = 0;
  do
  {
    iVar13 = 0x6e;
    puVar7 = (ushort *)(*piVar2 + ((uint)*(ushort *)(puVar1 + 4) + (*(ushort *)(puVar1 + 6) + uVar12) * 800) * 2 + iVar4);
    puVar9 = (ushort *)(puVar3 + uVar12 * 0xdc);

    do
    {
      uVar11 = *puVar9;

      if (*puVar9 == 0)
      {
        uVar11 = uVar5;
      }
      iVar13 = iVar13 + -1;
      *puVar7 = uVar11;
      puVar7 = puVar7 + 1;
      puVar9 = puVar9 + 1;
    } while (iVar13 != 0);

    uVar12 = uVar12 + 1 & 0xfffeffff;
  } while (uVar12 < 0x3c);

  set_display_fg_color(DAT_80011394);
  display_draw_rect(*(short *)(puVar1 + 4) + 0xf4,*(short *)(puVar1 + 6) + 0xaf,*(short *)(puVar1 + 4) + 0x162,*(short *)(puVar1 + 6) + 0xea);

  iVar4 = Start_Of_Screen_Mem;
  iVar13 = Screen_Frame_Buffer;
  uVar5 = *(ushort *)(puVar1 + 4);
  uVar10 = *(ushort *)(puVar1 + 6) + 0xeb & 0xfffeffff;
  uVar8 = *(ushort *)(puVar1 + 6) + 0xaf & 0xfffeffff;
  uVar12 = uVar5 + 0xf4 & 0xfffeffff;
  if (uVar10 <= uVar8)
  {
    return;
  }

  do
  {
    iVar6 = uVar12 + uVar8 * 800;
    copy_short((void *)(iVar4 + iVar6 * 2),(void *)(iVar13 + iVar6 * 2),((uVar5 + 0x162 & 0xfffeffff) - uVar12) + 1);

    uVar8 = uVar8 + 1;
  } while (uVar8 < uVar10);

  return;
}

//---------------------------------------------------------------------------------------------------

