void sys_clock_init(void)

{
  undefined4 uVar1;
  uint *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  uint uVar5;
  
  puVar3 = PLL_STABLE_TIME_REG0;       
  uVar1 = DAT_8002808c;
  *PLL_STABLE_TIME_REG0 = DAT_8002808c;                          //PLL_STABLE_TIME_REG0 = 0x1FF
  puVar3[1] = uVar1;                                             //PLL_STABLE_TIME_REG2 = 0x1FF

  puVar3 = puVar3 + -0x6c;
  *puVar3 = 0x20000;                                             //CPU_CLK_SRC_REG = 0x20000           (CPU_CLK_SRC_PLL)

  piVar4 = (int *)((uint)puVar3 | DAT_80028094 >> 0xe);
  *piVar4 = DAT_80028094;                                        //AHB_APB_HCLKC_CFG_REG = 0x00012110  (CCU_HCLKC_DIV_2 | CCU_AHB_CLK_SRC_CPUCLK | CCU_APB_CLK_RATIO_2 | CCU_AHB_CLK_DIV_RATIO_2)

  uVar5 = DAT_80028098;
  puVar2 = (uint *)(piVar4 + -0x15);
  *puVar2 = *puVar2 & DAT_80028098 | 0x80001800;                 //PLL_CPU_CTRL_REG |= 0x80001800      (CCU_PLL_ENABLE | CCU_PLL_CPU_FACTOR_N(25))  ==> 600MHz

  uVar5 = uVar5 >> 0x14;

  do {                                                           //Wait till pll stable with max checks
    uVar5 = uVar5 - 1;
    if (uVar5 == 0) {
      return;
    }
  } while ((*puVar2 & 0x10000000) == 0);
  return;
}

