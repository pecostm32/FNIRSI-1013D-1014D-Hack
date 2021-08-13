void FUN_8001ab18(void)

{
  ushort uVar1;
  ushort uVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  int divisor;
  
  divisor = 1;

  iVar5 = FUN_80017790();  //Check on touch in range. Not needed.


  puVar4 = PTR_DAT_8001abb0;   //0x80192f08     touch state base
  iVar3 = DAT_8001abac;        //0x8019D5A0     settings base

  if (iVar5 != 0)  //Not needed since touch will be in bounds
  {
    return;
  }

  uVar1 = *(ushort *)(PTR_DAT_8001abb0 + 0x2e);   //new x touch        xtouch
  uVar2 = *(ushort *)(PTR_DAT_8001abb0 + 0x32);   //some old x touch   previousxtouch

  if (*(char *)(DAT_8001abac + 0x16) != '\0')   //Move speed setting
  {
    divisor = 5;
  }


  if (uVar1 < uVar2)    //x new lower x old (left of)
  {
    //Calculate scaled diff
    uVar6 = divide((uint)(ushort)(uVar2 - uVar1),divisor);

    
    uVar1 = *(ushort *)(puVar4 + 10);  //Previous position, movement is done based on that and not the newly set, because it would move to fast

    if (uVar6 < uVar1)
    {
      *(ushort *)(iVar3 + 0x24) = uVar1 - (short)uVar6;
      return;
    }

    uVar6 = 0;
  }
  else
  {
    iVar5 = divide((uint)(ushort)(uVar1 - uVar2),divisor);
    uVar6 = iVar5 + (uint)*(ushort *)(puVar4 + 10);

    if (0x2cf < uVar6)
    {
      uVar6 = 0x2d0;
    }
  }

  *(short *)(iVar3 + 0x24) = (short)uVar6;   //Set new trigger point position on screen

  return;
}

