//Set PLL_PERIPH
undefined4 FUN_8003572c(int param_1,uint param_2)
{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined8 uVar9;
  
  if (DAT_800358e0 < param_2)
  {
    uVar8 = 0x1000000;
    FUN_800376f8(DAT_800358e8,DAT_800358e4);
    puVar1 = DAT_800358ec;
    *DAT_800358ec = *DAT_800358ec & 0x7fffffff;
    *puVar1 = *puVar1 & 0xfffff000;
    *puVar1 = *puVar1 | 0x1700;
    *puVar1 = *puVar1 | 0x80000000;
    uVar2 = *puVar1;
    uVar2 = FUN_8000090c((int)(short)((ushort)((uVar2 << 0x13) >> 0x1b) + 1) * (int)(short)((ushort)((uVar2 << 0x1a) >> 0x1e) + 1) * DAT_800358e0, (uVar2 & 3) + 1);
    FUN_800376f8(s_pll_hz___d_hz_800358f0,uVar2);
  }
  else 
  {
    uVar8 = 0;
    uVar2 = DAT_800358e0;
  }

  uVar9 = FUN_80000dc4(uVar2,param_2);
  uVar7 = (uint)uVar9;

  if ((int)((ulonglong)uVar9 >> 0x20) != 0) 
  {
    uVar7 = uVar7 + 1;
  }

  uVar3 = 0;
  if (0x10 < uVar7)
  {
    do 
    {
      uVar7 = uVar7 + 1 >> 1;
      uVar3 = uVar3 + 1;
    } while (0x10 < uVar7);

    if (3 < uVar3)
    {
      FUN_800376f8(s_mmc__u_error_cannot_set_clock_to_80035900,param_1,param_2);
      return 0xffffffff;
    }
  }

  if (DAT_80035928 < param_2)
  {
    if (DAT_8003592c < param_2)
    {
      if (DAT_80035930 < param_2)
      {
        iVar6 = 1;
      }
      else
      {
        iVar6 = 3;
      }
      iVar5 = 4;
    }
    else 
    {
      iVar6 = 0;
      iVar5 = 5;
    }
  }
  else 
  {
    iVar5 = 0;
    iVar6 = iVar5;
  }

  *(uint *)(DAT_80035934 + param_1 * 4) = uVar8 | iVar5 << 0x14 | uVar3 << 0x10 | iVar6 << 8 | uVar7 - 1 | 0x80000000;

  iVar6 = 1 << (uVar3 & 0xff);
  uVar4 = FUN_80000dc4(uVar2,iVar6);
  uVar4 = FUN_80000dc4(uVar4,uVar7);
  FUN_800376f8(PTR_s_mmc__u_set__mod_clk_req__u___par_80035938,param_1,param_2,uVar2,iVar6,uVar7,uVar4);
  return 0;
}

