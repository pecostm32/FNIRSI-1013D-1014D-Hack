void display_clear_rect(ushort xpos,ushort ypos,ushort xsize,ushort ysize)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint local_20;
  uint local_1c;
  
  local_20 = (uint)xsize;
  local_1c = (uint)ysize;

  FUN_8001936c();                                      //Some depth count increment or context save

  iVar1 = *(int *)(*DAT_80018fec + 0x4c);
  iVar2 = *(int *)(*DAT_80018fec + 0x50);

  uVar5 = (uint)xpos + iVar1;
  uVar3 = (uint)xsize + iVar1;
  iVar4 = (uint)ypos + iVar2;
  iVar2 = (uint)ysize + iVar2;

  local_20 = uVar5 & 0xffff | iVar4 * 0x10000;
  local_1c = uVar3 & 0xffff | iVar2 * 0x10000;

  iVar1 = FUN_8002ac10(&local_20);                     //Also used in display text

  while (iVar1 != 0)
  {
    FUN_8001cd50(uVar5,iVar4,uVar3,iVar2);

    iVar1 = FUN_8002ab40();                            //Also used in display text
  }

  FUN_80019a6c();                                      //Some depth count decrement or context restore

  return;
}

//---------------------------------------------------------------------------------------

void FUN_8001cd50(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  iVar1 = *DAT_8001cdd4;

  if (param_1 < *(short *)(iVar1 + 8))
  {
    param_1 = (int)*(short *)(iVar1 + 8);
  }

  if (*(short *)(iVar1 + 0xc) < param_3)
  {
    param_3 = (int)*(short *)(iVar1 + 0xc);
  }

  if (param_1 <= param_3)
  {
    if (param_2 < *(short *)(iVar1 + 10))
    {
      param_2 = (int)*(short *)(iVar1 + 10);
    }

    if (*(short *)(iVar1 + 0xe) < param_4)
    {
      param_4 = (int)*(short *)(iVar1 + 0xe);
    }

    if (param_2 <= param_4)
    {
      iVar1 = *(int *)(DAT_8001cdd8 + (uint)*(byte *)(iVar1 + 0x11) * 4);
      (**(code **)(*(int *)(iVar1 + 0xc) + 0x10))(iVar1,param_1,param_2,param_3,param_4);
    }
  }

  return;
}

