//-----------------------------------------------------------------------------------
//Called via 0x8019D480

void FUN_8002fdd4(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  *(undefined4 *)(DAT_8002fe08 + 0x18) = 0;

  FUN_8001a258(DAT_8002fe0c,0,0x70);

  uVar3 = 8;
  puVar2 = DAT_8002fe10;

  while( true )
  {
    bVar5 = uVar3 == 0;
    if (!bVar5)
    {
      bVar5 = ((uint)puVar2 & 3) == 0;
    }

    if (bVar5)
      break;

    uVar3 = uVar3 - 1;
    *(undefined *)puVar2 = 0;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }

  uVar4 = uVar3 >> 2;

  if (uVar4 != 0)
  {
    uVar3 = uVar3 & 3;

    while (3 < (int)uVar4)
    {
      *puVar2 = 0;
      puVar2[1] = 0;
      puVar1 = puVar2 + 3;
      puVar2[2] = 0;
      uVar4 = uVar4 - 4;
      puVar2 = puVar2 + 4;
      *puVar1 = 0;
    }

    while (uVar4 != 0)
    {
      uVar4 = uVar4 - 1;
      *puVar2 = 0;
      puVar2 = puVar2 + 1;
    }
  }

  while (uVar3 != 0)
  {
    uVar3 = uVar3 - 1;
    *(undefined *)puVar2 = 0;
    puVar2 = (undefined4 *)((int)puVar2 + 1);
  }

  return;
}

//-----------------------------------------------------------------------------------

