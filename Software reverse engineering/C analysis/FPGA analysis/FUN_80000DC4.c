//Process some data

//param_1 ==> data
//param_2 ==> count

longlong FUN_80000dc4(uint param_1,uint param_2)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  
  iVar3 = 0;
  uVar1 = param_2;
  if (param_2 <= param_1 >> 2)
  {
    if (param_2 <= param_1 >> 5)
    {
      if (param_2 <= param_1 >> 8)
      {
        if (param_1 >> 0xc < param_2) goto LAB_80000998;

        if (param_1 >> 0x10 < param_2) goto LAB_80000968;

        uVar1 = param_2 << 8;
        iVar3 = -0x1000000;

        if (uVar1 <= param_1 >> 0x10)
        {
          iVar3 = -0x10000;
          uVar1 = param_2 << 0x10;
        }

        if (param_1 >> 0xc < uVar1) goto LAB_80000998;

        bVar4 = uVar1 == 0;

        if (bVar4)
        {
          return (ulonglong)param_1 << 0x20;
        }

        do
        {
          if (bVar4)
          {
            uVar1 = uVar1 >> 8;
          }

LAB_80000968:
          bVar4 = uVar1 <= param_1 >> 0xf;
          if (bVar4) 
          {
            param_1 = param_1 + uVar1 * -0x8000;
          }

          bVar5 = uVar1 <= param_1 >> 0xe;
          if (bVar5)
          {
            param_1 = param_1 + uVar1 * -0x4000;
          }

          bVar6 = uVar1 <= param_1 >> 0xd;
          if (bVar6)
          {
            param_1 = param_1 + uVar1 * -0x2000;
          }

          bVar7 = uVar1 <= param_1 >> 0xc;
          if (bVar7)
          {
            param_1 = param_1 + uVar1 * -0x1000;
          }

          iVar3 = (((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 + (uint)bVar7;

LAB_80000998:
          bVar4 = uVar1 <= param_1 >> 0xb;
          if (bVar4)
          {
            param_1 = param_1 + uVar1 * -0x800;
          }

          bVar5 = uVar1 <= param_1 >> 10;
          if (bVar5)
          {
            param_1 = param_1 + uVar1 * -0x400;
          }

          bVar6 = uVar1 <= param_1 >> 9;
          if (bVar6)
          {
            param_1 = param_1 + uVar1 * -0x200;
          }

          uVar2 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;

          bVar5 = uVar1 <= param_1 >> 8;
          if (bVar5)
          {
            param_1 = param_1 + uVar1 * -0x100;
          }

          bVar4 = !bVar5 && CARRY4(uVar2,uVar2) || bVar5 && uVar2 * 2 + 1 <= uVar2;

          iVar3 = uVar2 * 2 + (uint)bVar5;
        } while (bVar4);
      }

      bVar4 = uVar1 <= param_1 >> 7;

      if (bVar4)
      {
        param_1 = param_1 + uVar1 * -0x80;
      }

      bVar5 = uVar1 <= param_1 >> 6;
      if (bVar5)
      {
        param_1 = param_1 + uVar1 * -0x40;
      }

      bVar6 = uVar1 <= param_1 >> 5;
      if (bVar6)
      {
        param_1 = param_1 + uVar1 * -0x20;
      }

      iVar3 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;
    }

    bVar4 = uVar1 <= param_1 >> 4;
    if (bVar4)
    {
      param_1 = param_1 + uVar1 * -0x10;
    }

    bVar5 = uVar1 <= param_1 >> 3;
    if (bVar5)
    {
      param_1 = param_1 + uVar1 * -8;
    }

    bVar6 = uVar1 <= param_1 >> 2;
    if (bVar6)
    {
      param_1 = param_1 + uVar1 * -4;
    }

    iVar3 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;
  }

  bVar4 = uVar1 <= param_1 >> 1;
  if (bVar4)
  {
    param_1 = param_1 + uVar1 * -2;
  }

  uVar2 = param_1 - uVar1;
  if (uVar1 > param_1)
  {
    uVar2 = param_1;
  }

  return CONCAT44(uVar2,(iVar3 * 2 + (uint)bVar4) * 2 + (uint)(uVar1 <= param_1));
}

