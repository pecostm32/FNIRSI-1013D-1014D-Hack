void sd_card_clk_init(int interface,uint frequency)

{
  uint *puVar1;
  uint uVar2;
  uint divisor;
  uint uVar3;
  int extraout_r1;
  int iVar4;
  int iVar5;
  uint uVar6;
  
  if (DAT_800358e0 < frequency)   //0x016E3600 = 24000000
  {
    uVar6 = 0x1000000;  //1000000  CCM_MMC_CTRL_PLL_PERIPH0

    uart_printf(DAT_800358e8,DAT_800358e4);

    puVar1 = PLL_PERIPH_CTRL_REG;

    *PLL_PERIPH_CTRL_REG = *PLL_PERIPH_CTRL_REG & 0x7fffffff;   //Disable the PLL

    *puVar1 = *puVar1 & 0xfffff000;    //Clear the lower 12 bits
    *puVar1 = *puVar1 | 0x1700;        //factor            (nfact=23+1, kfact=0+1, mfact=0+1)
    *puVar1 = *puVar1 | 0x80000000;    //Enable again

    uVar2 = *puVar1;

    //Calculate the output frequency of the PLL
    //                                      n factor                                              kfact                                         mfact
    uVar2 = divide_2((int)(short)((ushort)((uVar2 << 0x13) >> 0x1b) + 1) * (int)(short)((ushort)((uVar2 << 0x1a) >> 0x1e) + 1) * DAT_800358e0, (uVar2 & 3) + 1);

    uart_printf(s_pll_hz___d_hz_800358f0,uVar2);
  }
  else
  {
    uVar6 = 0;
    uVar2 = DAT_800358e0;   //0x016E3600 = 24000000
  }


  divisor = divide(uVar2,frequency);

  //Is the modulo
  if (extraout_r1 != 0)
  {
    divisor = divisor + 1;
  }

  uVar3 = 0;

  if (0x10 < divisor)
  {
    do
    {
      divisor = divisor + 1 >> 1;
      uVar3 = uVar3 + 1;
    } while (0x10 < divisor);

    if (3 < uVar3)
    {
      uart_printf(s_mmc__u_error_cannot_set_clock_to_80035900,interface,frequency);
      return;
    }
  }

  if (DAT_80035928 < frequency)         //0x00061A80
  {
    if (DAT_8003592c < frequency)       //0x017D7840
    {
      if (DAT_80035930 < frequency)     //0x02FAF080
      {
        iVar5 = 1;
      }
      else 
      {
        iVar5 = 3;
      }

      iVar4 = 4;
    }
    else
    {
      iVar5 = 0;
      iVar4 = 5;
    }
  }
  else
  {
    iVar4 = 0;
    iVar5 = iVar4;
  }

  *(uint *)(SDMMC0_CLK_REG + interface * 4) = uVar6 | iVar4 << 0x14 | uVar3 << 0x10 | iVar5 << 8 | divisor - 1 | 0x80000000;

  iVar5 = 1 << (uVar3 & 0xff);

  iVar4 = divide(uVar2,iVar5);

  iVar4 = divide(iVar4,divisor);

  uart_printf(PTR_s_mmc__u_set__mod_clk_req__u___par_80035938,interface,frequency,uVar2,iVar5,divisor,iVar4);

  return;
}

