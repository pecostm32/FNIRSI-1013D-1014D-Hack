void calculate_absolute_touch_movement(void)

{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  
  uVar2 = *(ushort *)(PTR_DAT_8001bc7c + 2);   //80192f0a   prev x
  uVar3 = *(ushort *)(PTR_DAT_8001bc7c + 6);   //80192f0e   prev prev x
  uVar1 = *(ushort *)(PTR_DAT_8001bc7c + 4);   //80192f0c   prev y

  if (uVar3 < uVar2)    //x displacement
  {
    uVar2 = uVar2 - uVar3;
  }
  else
  {
    uVar2 = uVar3 - uVar2;
  }

  uVar3 = *(ushort *)(PTR_DAT_8001bc7c + 8);  // 80192f10  prev prev y

  if (uVar3 < uVar1)         //y displacement
  {
    uVar3 = uVar1 - uVar3;
  }
  else
  {
    uVar3 = uVar3 - uVar1;
  }

  if (uVar3 < uVar2)  //Keep the biggest
  {
    *(ushort *)(PTR_DAT_8001bc7c + 0x2c) = uVar2;
  }
  else
  {
    *(ushort *)(PTR_DAT_8001bc7c + 0x2c) = uVar3;
  }
  return;
}


