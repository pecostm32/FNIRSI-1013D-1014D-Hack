//--------------------------------------------------------------------------------------------

void sys_init_usb(void)

{
  FUN_80021be0();

  usb_dev_bsp_init(4);
}

void usb_dev_bsp_init(int param)
{
  //this is usb_dev_bsp_init
  uart_printf(s_usb_init..._80037ec4);

  if (*DAT_80037ed4 != '\x04')  //0x8019D1DC
  {
    *DAT_80037ed4 = '\x04';
    FUN_80038f04();
    FUN_80029c48();
    FUN_80029574();
    FUN_80029a0c();
    FUN_80029a28();
    FUN_80029a44(2);
    FUN_80029a98(2);
    FUN_80029e10(0,0);
    return;
  }

  uart_printf(s_usb_type_err..._80037ed8);
  return;
}


//--------------------------------------------------------------------------------------------

void FUN_80021be0(void)

{
  longlong lVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  puVar2 = DAT_80021c2c;                                  //0x8019D234

  *(undefined4 *)(DAT_80021c28 + 0x30) = 1;               //0x8019D3A0 + 0x30 ==> 0x8019D3D0 = int32 1

  iVar3 = DAT_80021c34;                                   //0x80735000  some buffer???

  *puVar2 = 0x200;                                        //0x8019D234 = int32 0x200

  puVar2 = DAT_80021c30;                                  //0x8019D260  64 bit storage

  lVar1 = (ulonglong)*(uint *)(iVar3 + 4) * 0x200;        //Get 32 bit data from 0x80735004 and multiply it with 0x200
  uVar4 = (undefined4)lVar1;                              //LSB of result
  uVar5 = (undefined4)((ulonglong)lVar1 >> 0x20);         //MSB of result
  *DAT_80021c30 = uVar4;                                  //Store the 64 bit result
  puVar2[1] = uVar5;

  uVar4 = FUN_8000027c(uVar4,uVar5,0x200,0);              //Call this function with it

  *DAT_80021c38 = uVar4;                                  //0x8019D268 holds 32 bit result of the function call

  return;
}

//--------------------------------------------------------------------------------------------

ulonglong FUN_8000027c(uint param_1,uint param_2,uint param_3,uint param_4)

{
  bool bVar1;
  longlong lVar2;
  byte bVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  bool bVar12;
  bool bVar13;
  bool bVar14;
  
  bVar12 = (int)param_4 < 0;
  bVar13 = param_4 == 0;
  uVar10 = param_4;
  if (bVar13) {
    uVar10 = param_3;
  }
  uVar11 = count_leading_zeroes(uVar10);     //29 zeros because uVar10 will be 0x200
  uVar10 = uVar10 << (uVar11 + 1 & 0xff);    //Shift out the top bit

  if (!bVar13)
  {
    uVar11 = 0x3f - uVar11;
    bVar12 = (int)uVar11 < 0;
    bVar13 = uVar11 == 0;
  }
  if (bVar13) {
    uVar11 = 0x1f - uVar11;
    bVar12 = (int)uVar11 < 0;
  }
  if (bVar12) {
    return 0;
  }
  bVar12 = param_2 == 0;
  if (bVar12) {
    iVar5 = count_leading_zeroes(param_1);
  }
  else {
    iVar5 = count_leading_zeroes(param_2);
    iVar5 = 0x3f - iVar5;
    bVar12 = iVar5 == 0;
  }
  if (bVar12) {
    iVar5 = 0x1f - iVar5;
  }
  uVar6 = iVar5 - uVar11;
  bVar12 = (int)uVar6 < 0;
  if (!bVar12) {
    if (!bVar12) {
      bVar12 = (int)(4 - uVar6) < 0;
    }
    if (!bVar12) {
      uVar11 = 0;
      uVar10 = param_4 << (uVar6 & 0xff) | param_3 >> (0x20 - uVar6 & 0xff);
      param_3 = param_3 << (uVar6 & 0xff);
      while( true ) {
        bVar14 = param_3 <= param_1;
        bVar12 = !bVar14;
        bVar13 = CARRY4(param_2,~uVar10);
        bVar1 = param_2 + ~uVar10 + 1 <= param_2;
        uVar11 = uVar11 * 2 + (uint)(bVar12 && bVar13 || bVar14 && bVar1);
        if (bVar12 && bVar13 || bVar14 && bVar1) {
          param_2 = param_2 - (uVar10 + !bVar14);
        }
        if (bVar12 && bVar13 || bVar14 && bVar1) {
          param_1 = param_1 - param_3;
        }
        bVar12 = uVar6 == 0;
        uVar6 = uVar6 - 1;
        if (bVar12) break;
        bVar3 = (byte)uVar10;
        uVar10 = uVar10 >> 1;
        param_3 = (uint)(bVar3 & 1) << 0x1f | param_3 >> 1;
      }
      return (ulonglong)uVar11;
    }
    if ((int)(uVar11 - 0x20) < 5) {
      uVar10 = uVar10 | param_3 >> (uVar11 - 0x20 & 0xff);
    }
    uVar6 = *(uint *)(&DAT_8000052c + (uVar10 >> 0x1c) * 4);
    uVar10 = uVar11;
    if (0x1f < uVar11) {
      uVar10 = uVar11 - 0x20;
    }
    uVar7 = 0x20 - uVar10;
    if (0x1f < uVar11) {
      lVar2 = (ulonglong)param_4 * (ulonglong)uVar6 + ((ulonglong)param_3 * (ulonglong)uVar6 >> 0x20);
      uVar11 = (uint)lVar2;
      uVar6 = uVar6 + (int)((ulonglong)-(((int)((ulonglong)lVar2 >> 0x20) << (uVar7 & 0xff) | uVar11 >> (uVar10 & 0xff)) + (uint)(uVar11 << (uVar7 & 0xff) != 0)) * (ulonglong)uVar6 >> 0x20);
      lVar2 = (ulonglong)param_4 * (ulonglong)uVar6 + ((ulonglong)param_3 * (ulonglong)uVar6 >> 0x20);
      uVar11 = (uint)lVar2;
      uVar4 = (uVar6 + (int)((ulonglong)-(((int)((ulonglong)lVar2 >> 0x20) << (uVar7 & 0xff) | uVar11 >> (uVar10 & 0xff)) + (uint)(uVar11 << (uVar7 & 0xff) != 0)) * (ulonglong)uVar6 >> 0x20)) - 1;
      uVar11 = (uint)((ulonglong)param_2 * (ulonglong)uVar4 + ((ulonglong)param_1 * (ulonglong)uVar4 >> 0x20) >> 0x20) >> (uVar10 & 0xff);
      uVar7 = (uint)((ulonglong)param_3 * (ulonglong)uVar11);
      uVar6 = param_1 - uVar7;
      param_2 = param_2 - (uVar11 * param_4 + (int)((ulonglong)param_3 * (ulonglong)uVar11 >> 0x20) + (uint)(param_1 < uVar7));
      bVar12 = param_4 <= param_2;
      if (param_2 == param_4) {
        bVar12 = param_3 <= uVar6;
      }
      if (bVar12) {
        uVar10 = (uint)((ulonglong)param_2 * (ulonglong)uVar4 + ((ulonglong)uVar6 * (ulonglong)uVar4 >> 0x20) >> 0x20) >> (uVar10 & 0xff);
        uVar7 = (uint)((ulonglong)param_3 * (ulonglong)uVar10);
        param_2 = param_2 - (uVar10 * param_4 + (int)((ulonglong)param_3 * (ulonglong)uVar10 >> 0x20) + (uint)(uVar6 < uVar7));
        bVar12 = param_4 <= param_2;
        if (param_2 == param_4) {
          bVar12 = param_3 <= uVar6 - uVar7;
        }
        if (bVar12) {
          return (ulonglong)(uVar11 + uVar10 + 1);
        }
        return (ulonglong)(uVar11 + uVar10);
      }
      return (ulonglong)uVar11;
    }
    uVar11 = (uint)((ulonglong)param_3 * (ulonglong)uVar6);
    uVar6 = uVar6 + (int)((ulonglong)-(((int)((ulonglong)param_3 * (ulonglong)uVar6 >> 0x20) << (uVar7 & 0xff) | uVar11 >> (uVar10 & 0xff)) + (uint)(uVar11 << (uVar7 & 0xff) != 0)) * (ulonglong)uVar6 >> 0x20);
    uVar11 = (uint)((ulonglong)param_3 * (ulonglong)uVar6);
    uVar6 = uVar6 + (int)((ulonglong)-(((int)((ulonglong)param_3 * (ulonglong)uVar6 >> 0x20) << (uVar7 & 0xff) | uVar11 >> (uVar10 & 0xff)) + (uint)(uVar11 << (uVar7 & 0xff) != 0)) * (ulonglong)uVar6 >> 0x20);
    if (param_2 != 0) {
      uVar11 = (uint)((ulonglong)param_3 * (ulonglong)uVar6);
      uVar6 = uVar6 + (int)((ulonglong)-(((int)((ulonglong)param_3 * (ulonglong)uVar6 >> 0x20) << (uVar7 & 0xff) | uVar11 >> (uVar10 & 0xff)) + (uint)(uVar11 << (uVar7 & 0xff) != 0)) * (ulonglong)uVar6 >> 0x20);
    }
    lVar2 = (ulonglong)param_2 * (ulonglong)uVar6 + ((ulonglong)param_1 * (ulonglong)uVar6 >> 0x20);
    uVar11 = (uint)((ulonglong)lVar2 >> 0x20);
    uVar4 = (uint)lVar2 >> (uVar10 & 0xff) | uVar11 << (uVar7 & 0xff);
    uVar8 = (uint)((ulonglong)param_3 * (ulonglong)uVar4);
    uVar11 = uVar11 >> (uVar10 & 0xff);
    uVar7 = param_1 - uVar8;
    param_2 = param_2 - (uVar11 * param_3 + (int)((ulonglong)param_3 * (ulonglong)uVar4 >> 0x20) + (uint)(param_1 < uVar8));
    if (param_2 != 0 || param_3 <= uVar7) {
      lVar2 = (ulonglong)param_2 * (ulonglong)uVar6 + ((ulonglong)uVar7 * (ulonglong)uVar6 >> 0x20);
      uVar8 = (uint)((ulonglong)lVar2 >> 0x20);
      uVar9 = (uint)lVar2 >> (uVar10 & 0xff) | uVar8 << (0x20 - uVar10 & 0xff);
      uVar6 = uVar4 + uVar9;
      iVar5 = uVar11 + (uVar8 >> (uVar10 & 0xff)) + (uint)CARRY4(uVar4,uVar9);
      uVar7 = uVar7 - param_3 * uVar9;
      if (param_3 <= uVar7) {
        uVar7 = uVar7 - param_3;
        bVar12 = param_3 <= uVar7;
        if (bVar12) {
          uVar7 = uVar7 - param_3;
        }
        uVar10 = uVar6 + 1 + (uint)bVar12;
        return CONCAT44(iVar5 + (uint)(0xfffffffe < uVar6) + (uint)(bVar12 && uVar6 + 2 <= uVar6 + 1) + (uint)(param_3 <= uVar7 && uVar10 + 1 <= uVar10),uVar10 + (param_3 <= uVar7));
      }
      return CONCAT44(iVar5,uVar6);
    }
    return CONCAT44(uVar11,uVar4);
  }
  return 0;
}

//--------------------------------------------------------------------------------------------

