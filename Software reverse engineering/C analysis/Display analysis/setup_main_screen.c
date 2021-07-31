void setup_main_screen(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ushort xsize;
  uint uVar4;
  
  set_frame_to_global_pointer();
  set_display_fg_color(0);
  iVar1 = DAT_8000ea10;
  xsize = (ushort)DAT_8000ea10;

  display_fill_rect(0,0,xsize,0x2e);
  display_fill_rect(0,0x1de,xsize,0x1e0);
  display_fill_rect(0,0,1,xsize - 0x140);
  display_fill_rect(0x2d7,0,xsize,0x1e0);

  FUN_8000bdf0();

  iVar2 = DAT_8000ea14;
  FUN_80010944(*(undefined *)(DAT_8000ea14 + 0x3a));
  FUN_8000e1e0();
  FUN_800104b4(0);
  if (*(char *)(iVar2 + 0x43) == '\0') {
    FUN_8000e7f8(0);
  }
  else {
    FUN_80012920();
  }
  setup_ch1_settings(0);
  setup_ch2_settings(0);
  FUN_80012280();
  set_trigger_settings(0);
  FUN_8000bcb8();
  FUN_8001cccc(0,0,iVar1,0x2e);
  FUN_8001cccc(0x2d7,0,iVar1,0x1e0);
  FUN_8001cccc(0,0,1,0x1e0);
  iVar3 = Start_Of_Screen_Mem;
  iVar2 = Screen_Frame_Buffer;
  uVar4 = 0x1de;
  do {
    copy_short((void *)(iVar3 + uVar4 * 0x640),(void *)(iVar2 + uVar4 * 0x640),iVar1 + 1);
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x1e0);
  return;
}

//--------------------------------------------------------------------------------------------------------------------------

void FUN_8000bdf0(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  ushort xsize;
  ushort ysize;
  uint uVar4;
  int iVar5;
  int iVar6;
  
  iVar1 = DAT_8000bf1c;
  iVar5 = DAT_8000bf20 + 0x140;
  iVar6 = DAT_8000bf20 + 0xf8;
  xsize = (ushort)iVar5;
  ysize = (ushort)DAT_8000bf20;

  if (*(char *)(DAT_8000bf1c + 0x42) == '\0')
  {
    set_frame_to_global_pointer();
    set_display_fg_color(0);

    display_fill_rect((ushort)iVar6,0,xsize,ysize);

    FUN_8000e1e0();  //empty function

    FUN_8000c4b8(0);

    if (*(char *)(iVar1 + 0x43) == '\0') {
      FUN_8000cbc0(0);
      FUN_8000bf24(0);
      FUN_8000cd6c(0);
    }
    else {
      FUN_8000d478();
      FUN_8000d630(0);
      FUN_8000d2a8(0);
    }
    FUN_8000c850(0);
    FUN_8000d0ec(0);
    FUN_8000ca00(0);
    FUN_8000c690(0);
  }
  else {
    set_frame_to_global_pointer();
    set_display_fg_color(0);
    display_fill_rect((ushort)iVar6,0,xsize,ysize);
    FUN_8000e1e0();
    FUN_8000c4b8(0);
    setup_ch1_menu(0,0);
    setup_ch2_menu(0,0);
    if (*(char *)(iVar1 + 0x43) == '\0') {
      FUN_8000cf2c(0);
    }
    else {
      FUN_8000d7ec();
    }
  }
  iVar2 = Start_Of_Screen_Mem;
  iVar1 = Screen_Frame_Buffer;
  uVar4 = 0;
  do {
    iVar3 = iVar6 + uVar4 * 800;
    copy_short((void *)(iVar2 + iVar3 * 2),(void *)(iVar1 + iVar3 * 2),(iVar5 - iVar6) + 1);
    uVar4 = uVar4 + 1;
  } while (uVar4 < 0x1e0);
  return;
}

//--------------------------------------------------------------------------------------------------------------------------


void FUN_8000c4b8(int param_1)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  ushort *puVar7;
  int iVar8;
  undefined2 *puVar9;
  int iVar10;
  
  set_frame_to_global_pointer();

  puVar1 = PTR_DAT_8000c678;    //0xE9DE

  uVar5 = *(uint *)(PTR_DAT_8000c678 + 4);

  *(ushort *)PTR_DAT_8000c678 = (ushort)(((uVar5 << 0x10) >> 0x1a) << 5) | (ushort)((uVar5 >> 0x13) << 0xb) | (ushort)((uVar5 << 0x18) >> 0x1b);

  uVar5 = DAT_8000c684;

  piVar3 = Global_Frame_Buffer_Pointer;

  puVar2 = PTR_DAT_8000c67c;

  uVar6 = *(uint *)(puVar1 + 8);

  *(ushort *)(puVar1 + 2) = (ushort)((uVar6 >> 0x13) << 0xb) | (ushort)(((uVar6 << 0x10) >> 0x1a) << 5) | (ushort)((uVar6 << 0x18) >> 0x1b);

  if (param_1 == 0)
  {
    set_display_fg_color(DAT_8000c688);    //0x00333333

    FUN_80018ff0(0x2e3,5,0x316,0x37,2);    //fill_rounded_rect

    set_display_fg_color(DAT_8000c68c);    //0x00444444

    FUN_80018e68(0x2e3,5,0x316,0x37,2);    //draw_rounded_rect

    uVar6 = 0;                             //r2
    do
    {
      iVar10 = 0x3c;
      puVar9 = (undefined2 *)(*piVar3 + uVar6 * 0x640 + 0x187e);   //0x804FB9B4 + (0 * 1600) + 6144  (0x1800)
      puVar7 = (ushort *)(puVar2 + uVar6 * 0x78);                  //0x800449E4 + (0 x 120)  55 lines

      //Bitmap a like in memory that is copied for on bits only

      do
      {
        if (*puVar7 == uVar5)    //short is 0xFFFF (so white)
        {
          *puVar9 = *(undefined2 *)puVar1;
        }

        iVar10 = iVar10 + -1;
        puVar9 = puVar9 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar10 != 0);

      uVar6 = uVar6 + 1 & 0xfffeffff;
    } while (uVar6 < 0x37);
  }
  else
  {
    set_display_fg_color(uVar6);
    FUN_80018ff0(0x2e3,5,0x316,0x37,2);

    uVar6 = 0;
    do {
      iVar10 = 0x3c;
      puVar9 = (undefined2 *)(*piVar3 + uVar6 * 0x640 + 0x187e);
      puVar7 = (ushort *)(puVar2 + uVar6 * 0x78);
      do {
        if (*puVar7 == uVar5) {
          *puVar9 = 0;
        }
        iVar10 = iVar10 + -1;
        puVar9 = puVar9 + 1;
        puVar7 = puVar7 + 1;
      } while (iVar10 != 0);
      uVar6 = uVar6 + 1 & 0xfffeffff;
    } while (uVar6 < 0x37);
  }


  //FUN_8001CCCC (copy rect to actual screen)
  iVar4 = Start_Of_Screen_Mem;
  iVar10 = Screen_Frame_Buffer;
  uVar5 = 3;
  do {
    iVar8 = uVar5 * 800 + 0x2df;
    copy_short((void *)(iVar4 + iVar8 * 2),(void *)(iVar10 + iVar8 * 2),0x40);
    uVar5 = uVar5 + 1;
  } while (uVar5 < 0x3a);
  return;
}


//--------------------------------------------------------------------------------------------------------------------------
//Display battery status

void FUN_8000bcb8(void)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  
  set_frame_to_global_pointer();
  set_display_fg_color(0xffffff);
  display_fill_rect(0x2c0,5,0x2d5,0x11);
  display_fill_rect(0x2be,9,0x2c1,0xd);
  iVar1 = DAT_8000bde4;
  if (*(byte *)(DAT_8000bde4 + 0x38) < 4) {
    uVar3 = 0xff0000;
  }
  else {
    uVar3 = 0xbb00;
  }
  set_display_fg_color(uVar3);
  if (0x14 < *(byte *)(iVar1 + 0x38)) {
    *(undefined *)(iVar1 + 0x38) = 0x14;
  }
  if (*(char *)(iVar1 + 0x38) != '\0') {
    display_fill_rect(0x2d5 - *(byte *)(iVar1 + 0x38),6,0x2d4,0x10);
  }
  if (*(char *)(iVar1 + 0x39) != '\0') {
    set_display_fg_color(DAT_8000bde8);
    uVar3 = DAT_8000bdec;
    FUN_80018ca8(10,0x2c4,DAT_8000bdec);   //10, 708, 718
    FUN_80018ca8(0xb,0x2c4,uVar3);         //11, 708, 718
    FUN_80018ca8(0xc,0x2c4,uVar3);         //12, 708, 718
    FUN_80018ef4(uVar3 | 1,8,0xe);         //719,  8, 14
    FUN_80018ef4(0x2d0,9,0xd);             //720,  9, 13
    FUN_80018ef4(uVar3 + 3,10);            //721, 10, 12
    FUN_80018ef4(uVar3 + 4,0xb);           //722, 11, 11
  }
  iVar2 = Start_Of_Screen_Mem;
  iVar1 = Screen_Frame_Buffer;
  uVar3 = 5;
  do {
    iVar4 = uVar3 * 800 + 0x2be;
    copy_short((void *)(iVar2 + iVar4 * 2),(void *)(iVar1 + iVar4 * 2),0x18);
    uVar3 = uVar3 + 1;
  } while (uVar3 < 0x24);
  return;
}

//--------------------------------------------------------------------------------------------------------------------------

void display_draw_rounded_rect(ushort xstart,ushort ystart,ushort xend,ushort yend,ushort radius)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  undefined2 in_stack_00000002;
  uint local_24;
  uint local_20;
  
  local_24 = (uint)xend;
  local_20 = (uint)yend;
  FUN_8001936c();

  iVar1 = *(int *)(*DAT_80018ef0 + 0x4c);  //X and Y offset
  iVar2 = *(int *)(*DAT_80018ef0 + 0x50);

  uVar5 = (uint)xstart + iVar1;
  uVar3 = (uint)xend + iVar1;
  iVar4 = (uint)ystart + iVar2;
  iVar2 = (uint)yend + iVar2;

  local_24 = uVar5 & 0xffff | iVar4 * 0x10000;
  local_20 = uVar3 & 0xffff | iVar2 * 0x10000;

  iVar1 = FUN_8002ac10(&local_24);

  while (iVar1 != 0)
  {
    FUN_8002ea74(uVar5,iVar4,uVar3,iVar2,_radius);
    iVar1 = FUN_8002ab40();
  }


  FUN_80019a6c();
  return;
}

//--------------------------------------------------------------------------------------------------------------------------

void display_fill_rounded_rect(ushort xstart,ushort ystart,ushort xend,ushort yend,ushort radius)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  bool bVar9;
  bool bVar10;
  undefined2 in_stack_00000002;
  undefined2 local_38;
  undefined2 local_36;
  undefined2 local_34;
  undefined2 local_32;
  int local_30;
  int local_2c;
  
  FUN_8001936c();
  iVar8 = *(int *)(*DAT_8001911c + 0x4c);
  iVar1 = *(int *)(*DAT_8001911c + 0x50);
  iVar5 = iVar8 + (uint)xstart;
  iVar7 = iVar1 + (uint)ystart;
  iVar8 = iVar8 + (uint)xend;
  iVar1 = iVar1 + (uint)yend;
  local_38 = (undefined2)iVar5;
  local_34 = (undefined2)iVar8;
  local_36 = (undefined2)iVar7;
  local_32 = (undefined2)iVar1;

  iVar2 = FUN_8002ac10(&local_38);

  if (iVar2 != 0)
  {
    local_2c = (iVar1 - iVar7) + 1;

    do
    {
      bVar10 = SBORROW4(local_2c,_radius * 2);
      bVar9 = local_2c + _radius * -2 < 0;
      if (bVar9 == bVar10) {
        iVar2 = (iVar8 - iVar5) + 1;
        bVar10 = SBORROW4(iVar2,_radius * 2);
        bVar9 = iVar2 + _radius * -2 < 0;
      }
      if (bVar9 == bVar10)
      {
        local_30 = _radius * _radius;
        iVar2 = iVar7;
        iVar6 = _radius;

        while (iVar2 <= iVar7 + _radius)
        {
          iVar3 = FUN_8001a320(local_30 - iVar6 * iVar6);
          iVar4 = (iVar5 + _radius) - iVar3;
          iVar3 = iVar3 + (iVar8 - _radius);
          FUN_8001cb24(iVar4,iVar2,iVar3);
          FUN_8001cb24(iVar4,iVar1 - (iVar2 - iVar7),iVar3);
          iVar2 = iVar2 + 1;
          iVar6 = iVar6 + -1;
        }
        FUN_8001cd50(iVar5,iVar2,iVar8,(iVar1 - _radius) + -1);
      }

      iVar2 = FUN_8002ab40();
    } while (iVar2 != 0);
  }
  FUN_80019a6c();
  return;
}



//--------------------------------------------------------------------------------------------------------------------------

void FUN_8002ea74(int param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int local_54;
  
  iVar1 = (param_4 - param_2) + 1;
  if ((iVar1 + param_5 * -2 < 0 == SBORROW4(iVar1,param_5 * 2)) && (iVar1 = (param_3 - param_1) + 1, iVar1 + param_5 * -2 < 0 == SBORROW4(iVar1,param_5 * 2)))
  {
    iVar9 = param_1 + param_5;
    local_54 = -1;
    iVar7 = param_2 + param_5;
    iVar8 = param_3 - param_5;
    iVar1 = param_2;
    iVar6 = param_5;

    while (iVar1 <= iVar7)
    {
      iVar2 = FUN_8001a320(param_5 * param_5 - iVar6 * iVar6);

      iVar3 = iVar9 - iVar2;
      iVar4 = iVar8 + iVar2;
      iVar5 = param_4 - (iVar1 - param_2);
      local_54 = iVar2 - local_54;

      if (local_54 < 2)
      {
        FUN_8001cba8(iVar3,iVar1);
        FUN_8001cba8(iVar4,iVar1);
        FUN_8001cba8(iVar3,iVar5);
        FUN_8001cba8(iVar4,iVar5);
      }
      else
      {
        FUN_8001cb24(iVar3,iVar1,iVar3 + local_54 + -1);
        FUN_8001cb24((iVar4 - local_54) + 1,iVar1,iVar4);
        FUN_8001cb24(iVar3,iVar5,iVar3 + local_54 + -1);
        FUN_8001cb24((iVar4 - local_54) + 1,iVar5,iVar4);
      }

      iVar1 = iVar1 + 1;
      iVar6 = iVar6 + -1;
      local_54 = iVar2;
    }

    FUN_8001cb24(iVar9 + 1,param_2,iVar8 + -1);
    FUN_8001cb24(iVar9 + 1,param_4,iVar8 + -1);
    FUN_8001cc4c(param_1,iVar7 + 1,(param_4 - param_5) + -1);
    FUN_8001cc4c(param_3,iVar7 + 1,(param_4 - param_5) + -1);
  }
  return;
}


//--------------------------------------------------------------------------------------------------------------------------


//--------------------------------------------------------------------------------------------------------------------------

