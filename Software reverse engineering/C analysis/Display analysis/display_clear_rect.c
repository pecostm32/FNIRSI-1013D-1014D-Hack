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
  FUN_8001936c();
  iVar1 = *(int *)(*DAT_80018fec + 0x4c);
  iVar2 = *(int *)(*DAT_80018fec + 0x50);
  uVar5 = (uint)xpos + iVar1;
  uVar3 = (uint)xsize + iVar1;
  iVar4 = (uint)ypos + iVar2;
  iVar2 = (uint)ysize + iVar2;
  local_20 = uVar5 & 0xffff | iVar4 * 0x10000;
  local_1c = uVar3 & 0xffff | iVar2 * 0x10000;
  iVar1 = FUN_8002ac10(&local_20);
  while (iVar1 != 0) {
    FUN_8001cd50(uVar5,iVar4,uVar3,iVar2);
    iVar1 = FUN_8002ab40();
  }
  FUN_80019a6c();
  return;
}


