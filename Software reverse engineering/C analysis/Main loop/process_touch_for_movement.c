void FUN_8001bc30(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;

  //PTR_DAT_8001bc7c = 0x80192F08
  uVar2 = *(ushort *)(PTR_DAT_8001bc7c + 2);  //0x80192F0A   previous X touch
  uVar3 = *(ushort *)(PTR_DAT_8001bc7c + 6);  //0x80192F0E   new X touch
  uVar1 = *(ushort *)(PTR_DAT_8001bc7c + 4);  //0x80192F0C   previous Y touch

  if (uVar3 < uVar2)
  {
    uVar2 = uVar2 - uVar3;
  }
  else
  {
    uVar2 = uVar3 - uVar2;
  }

  uVar3 = *(ushort *)(PTR_DAT_8001bc7c + 8);  //0x80192F10   new Y touch

  if (uVar3 < uVar1)
  {
    uVar3 = uVar1 - uVar3;
  }
  else
  {
    uVar3 = uVar3 - uVar1;
  }

  if (uVar3 < uVar2)
  {
    *(ushort *)(PTR_DAT_8001bc7c + 0x2c) = uVar2;   //0x80192f34  absolute movement
  }
  else
  {
    *(ushort *)(PTR_DAT_8001bc7c + 0x2c) = uVar3;
  }
  return;
}

