undefined8 FUN_800397d0(int param_1)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = count_leading_zeroes(param_1);

  uVar1 = param_1 << (uVar2 & 0xff);

  if (uVar1 != 0)
  {
    return CONCAT44((0x41d - uVar2) * 0x100000 + (uVar1 >> 0xb),uVar1 << 0x15);
  }

  return 0;
}

/*
        800397d0 10 3f 6f e1     clz        r3,r0
        800397d4 10 13 b0 e1     movs       r1,r0, lsl r3
        800397d8 05 00 00 0a     beq        LAB_800397f4
        800397dc 1d 30 63 e2     rsb        r3,r3,#0x1d
        800397e0 01 3b 83 e2     add        r3,r3,#0x400
        800397e4 81 0a a0 e1     mov        r0,r1, lsl #0x15              ;Only large input with data in lowest bits will result in r0 output
        800397e8 03 2a a0 e1     mov        r2,r3, lsl #0x14
        800397ec a1 15 82 e0     add        r1,r2,r1, lsr #0xb
        800397f0 1e ff 2f e1     bx         lr
                             LAB_800397f4                                    XREF[1]:     800397d8(j)  
        800397f4 00 00 a0 e3     mov        r0,#0x0
        800397f8 1e ff 2f e1     bx         lr
*/

//input = 0x32, output ==> r0 = 0, r1 = 0x40490000
//r3 = 0x1A                 26
//r1 = 0xC8000000   3355443200
//r3 = 0x403              1027
//r0 = 0x00                  0
//r2 = 0x40300000   1076887552
//r1 = 0x40490000   1078525952




//------------------------------------------------------------------------------------------------------------------


longlong FUN_800393ec(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  ulonglong uVar2;
  byte bVar3;
  uint uVar4;
  uint unaff_r4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  bool bVar13;
  
  bVar13 = (DAT_800396b4 & ~(param_2 >> 4)) == 0;

  if (!bVar13)
  {
    bVar13 = (DAT_800396b4 & ~(param_4 >> 4)) == 0;
  }

  if (bVar13)
  {
                    // WARNING: Subroutine does not return
    FUN_80039a08();
  }

  uVar8 = param_2 ^ param_4;
  uVar5 = DAT_800396b4 & param_2 >> 4;
  bVar13 = uVar5 == 0;
  uVar7 = uVar8 >> 0x1f;

  if (!bVar13)
  {
    uVar8 = DAT_800396b4 & param_4 >> 4;
    bVar13 = uVar8 == 0;
  }

  if (bVar13)
  {
    if ((param_2 & DAT_800396b4 << 4) == 0)
    {
      if ((param_4 & DAT_800396b4 << 4) == 0)
      {
        return (ulonglong)DAT_800396b8 << 0x20;
      }

      return (ulonglong)((param_2 ^ param_4) & 0x80000000) << 0x20;
    }

    bVar3 = (byte)(param_2 >> 0x18) ^ (byte)(param_4 >> 0x18);
  }
  else
  {
    iVar6 = (uVar5 | uVar7) - uVar8;
    uVar8 = param_4 << 0xb | 0x80000000;
    uVar5 = param_2 << 0xb | 0x80000000 | param_1 >> 0x15;
    uVar4 = uVar8 | param_3 >> 0x15;
    uVar7 = iVar6 + 0x3fe0000;

    if (uVar5 == uVar4 && param_1 * 0x800 == param_3 * 0x800)
    {
      uVar5 = 0x100000;
      uVar4 = 0;
    }
    else
    {
      uVar9 = (uint)*(byte *)((uVar8 >> 0x18) + 0x800395b4);
      uVar9 = uVar9 * (0x1000000 - uVar9 * (uVar8 >> 0x10)) >> 0xf;
      iVar10 = (int)((ulonglong)uVar4 * (ulonglong)uVar9);
      uVar9 = uVar9 * (0x10000 - ((int)((ulonglong)uVar4 * (ulonglong)uVar9 >> 0x20) + (uint)(iVar10 != 0))) + (int)((ulonglong)(uint)-iVar10 * (ulonglong)uVar9 >> 0x20);
      lVar1 = (ulonglong)uVar4 * (ulonglong)uVar9 + ((ulonglong)(param_3 * 0x800) * (ulonglong)uVar9 >> 0x20);
      iVar10 = (int)lVar1;
      uVar2 = (ulonglong)(0x80000000 - ((int)((ulonglong)lVar1 >> 0x20) + (uint)(iVar10 != 0))) * (ulonglong)uVar9 + ((ulonglong)(uint)-iVar10 * (ulonglong)uVar9 >> 0x20);
      uVar9 = (uint)(uVar2 >> 0x20);
      uVar4 = (uint)((uVar2 & 0xffffffff) * (ulonglong)uVar5 >> 0x20);
      uVar11 = (uint)((ulonglong)uVar9 * (ulonglong)(param_1 * 0x800) >> 0x20);
      lVar1 = (ulonglong)uVar9 * (ulonglong)uVar5 + (ulonglong)CONCAT14(CARRY4(uVar4,uVar11),uVar4 + uVar11);
      uVar9 = (uint)lVar1;
      iVar10 = (int)((ulonglong)lVar1 >> 0x20);
      iVar12 = iVar10 + 0x70000000;

      if (!SCARRY4(iVar10,0x70000000))
      {
        uVar9 = uVar9 << 1;
        uVar7 = iVar6 + 0x3fd0000;
        iVar10 = iVar10 * 2 + (uint)(byte)((byte)((ulonglong)lVar1 >> 0x18) >> 7);
      }

      uVar5 = iVar10 + (uint)(0xffffff7f < uVar9);
      uVar4 = uVar9 + 0x80 >> 8 | uVar5 * 0x1000000;
      uVar5 = uVar5 >> 8;

      if (uVar9 * 0x1000000 + 0x91000000 < 0x10000001)
      {
        iVar6 = uVar5 * param_3 + uVar4 * (uVar8 >> 0xb) + (int)((ulonglong)param_3 * (ulonglong)uVar4 >> 0x20);

        if (-1 < iVar12)
        {
          iVar6 = iVar6 + (param_1 & 0x1fffff) * -0x100000;
        }

        if ((int)(iVar6 + (param_1 & 0x1fffff) * -0x100000 + (uVar8 >> 0xc) + (uint)CARRY4((uint)((ulonglong)param_3 * (ulonglong)uVar4),param_3 >> 1 | (uVar8 >> 0xb) << 0x1f)) < 0)
        {
          bVar13 = 0xfffffffe < uVar4;
          uVar4 = uVar4 + 1;
          uVar5 = uVar5 + bVar13;
        }
      }
    }

    uVar9 = uVar7 & 0xfffffffe;
    uVar8 = uVar7;

    if (uVar9 < 0x7f00001)
    {
      uVar8 = unaff_r4;
    }

    iVar6 = uVar5 + uVar7 * -0x80000000 + uVar9 * 0x10;

    if (uVar9 < 0x7f00001)
    {
      return CONCAT44(iVar6,uVar4);
    }

    bVar13 = (int)uVar8 < 0;

    if (!bVar13)
    {
      bVar13 = (int)(iVar6 + 0x100000U ^ uVar8 << 0x1f) < 0;
    }

    if (!bVar13)
    {
      return CONCAT44(iVar6,uVar4);
    }

    if ((int)uVar8 < 0)
    {
      return (ulonglong)(iVar6 + 0x60000000U & 0x80000000) << 0x20;
    }

    bVar3 = (byte)((uint)(iVar6 + -0x60000000) >> 0x18);
  }

  return (ulonglong)((uint)(bVar3 >> 7) << 0x1f | 0x7ff00000) << 0x20;
}

//------------------------------------------------------------------------------------------------------------------

undefined8 FUN_80039a08(int param_1,uint param_2,int param_3,uint param_4)

{
  uint unaff_r5;
  uint uVar1;
  uint *in_lr;
  bool bVar2;
  bool bVar3;
  undefined8 uVar4;
  
  if ((((int)*in_lr < 0) || (unaff_r5 = param_4 * 2 + (uint)(param_3 != 0), unaff_r5 < 0xffe00001)) && (uVar1 = param_2 * 2 + (uint)(param_1 != 0), uVar1 < 0xffe00001))
  {
    if (uVar1 == 0xffe00000)
    {
      uVar1 = ((int)param_2 >> 0x1f) * -3 + 2;

      if (unaff_r5 == 0xffe00000)
      {
        uVar1 = (uVar1 - ((int)param_4 >> 0x1f)) + (uint)(0xffdfffff < unaff_r5);
      }
    }
    else
    {
      uVar1 = param_4 >> 0x1f;
    }
  }
  else
  {
    uVar1 = 8;
  }

  uVar1 = *in_lr >> uVar1 * 3 & 7;

  switch(uVar1)
  {
    case 4:
      break;

    case 5:
      param_3 = param_1;
      param_4 = param_2;
      break;

    case 6:
    case 7:
      return 0x7ff8000000000000;

    default:
                      // WARNING: Could not recover jumptable at 0x80039a78. Too many branches
                      // WARNING: Treating indirect jump as call
      uVar4 = (*(code *)(in_lr + uVar1 + 1))();
      return uVar4;
  }

  bVar2 = param_3 != 0;
  bVar3 = !bVar2 && CARRY4(param_4,param_4) || bVar2 && param_4 * 2 + 1 <= param_4;
  uVar1 = param_4 * 2 + (uint)bVar2;
  bVar2 = uVar1 != 0;

  if (bVar2)
  {
    bVar3 = uVar1 < 0x200001;
  }

  if (bVar3 && (bVar2 && uVar1 != 0x200000))
  {
    param_3 = 0;
  }

  if (bVar3 && (bVar2 && uVar1 != 0x200000))
  {
    param_4 = param_4 & 0x80000000;
  }

  return CONCAT44(param_4,param_3);
}

//------------------------------------------------------------------------------------------------------------------

