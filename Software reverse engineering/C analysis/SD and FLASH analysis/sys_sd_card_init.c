//--------------------------------------------------------------------------------------------

uint sys_sd_card_init(void)

{
  uint uVar1;
  undefined4 *port;
  int *piVar2;
  int in_r0;
  uint *puVar3;
  char *pcVar4;
  int iVar5;
  uint *puVar6;
  uint *puVar7;
  uint *puVar8;
  undefined4 *unaff_r9;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  
  port = PORT_C_CFG0;
  puVar6 = SD_MMC_0_BASE;
  puVar7 = SD_MMC_0_BASE + 0x400;
  puVar8 = SD_MMC_0_BASE;
  if ((in_r0 != 0) && (puVar8 = puVar7, in_r0 != 1)) {
    puVar8 = (uint *)0x0;
  }
  if (in_r0 == 0) {
    unaff_r9 = PORT_F_CFG0;
  }
  iVar5 = 0;
  if (in_r0 == 0) {
    do {
      gpio_config_pin(unaff_r9,iVar5,2);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 6);
  }
  else {
    if (in_r0 == 1) {
      do {
        gpio_config_pin(port,iVar5,3);
        iVar5 = iVar5 + 1;
      } while (iVar5 < 3);
    }
  }
  puVar3 = BUS_CLK_GATING_REG0;
  uVar1 = 1 << (in_r0 + 8U & 0xff);
  *BUS_CLK_GATING_REG0 = *BUS_CLK_GATING_REG0 | uVar1;
  puVar3[0x98] = uVar1 | puVar3[0x98];
  FUN_800324d0(1);
  sd_card_clk_init(in_r0,DAT_8002446c);
  puVar3 = puVar6;
  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1)) {
    puVar3 = (uint *)0x0;
  }
  puVar3[0x1e] = puVar3[0x1e] | 2;
  puVar3[0x1e] = puVar3[0x1e] & 0xfffffffd;
  uVar1 = DAT_80024470;
  delay(DAT_80024470);
  puVar3[0x1e] = puVar3[0x1e] | 2;
  delay(uVar1);
  puVar3 = puVar6;
  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1)) {
    puVar3 = (uint *)0x0;
  }
  *puVar3 = *puVar3 | 7;
  delay(uVar1);
  puVar3 = puVar6;
  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1)) {
    puVar3 = (uint *)0x0;
  }
  *puVar3 = *puVar3 & 0xfffffeff;
  puVar3 = puVar6;
  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1)) {
    puVar3 = (uint *)0x0;
  }
  puVar3[1] = puVar3[1] | 0x20000;
  puVar3 = puVar6;
  if ((in_r0 != 0) && (puVar3 = puVar7, in_r0 != 1)) {
    puVar3 = (uint *)0x0;
  }
  puVar3[3] = 0;
  puVar8[2] = 0xffffffff;
  if ((in_r0 != 0) && (puVar6 = puVar7, in_r0 != 1)) {
    puVar6 = (uint *)0x0;
  }
  puVar6[1] = puVar6[1] | 0x10000;
  FUN_80035c1c();
  FUN_800324d0(0x32);
  FUN_80036d3c();
  FUN_800324d0(500);
  iVar5 = FUN_80036d3c();
  piVar2 = DAT_80024478;
  if (iVar5 == 0) {
    FUN_800376f8(s_SD2_0____80024498);
    FUN_80036d3c();
    FUN_80036d3c();
    while ((local_28 & 0x80000000) == 0) {
      FUN_80036d3c();
      FUN_80036d3c();
    }
    if ((local_28 & 0x40000000) != 0) {
      pcVar4 = s__TYPE_SD_HIGH____800244a7 + 1;
      *piVar2 = 1;
      goto LAB_80024268;
    }
  }
  else {
    FUN_800376f8(s_SD1_1____8002447c);
    FUN_80036d3c();
    FUN_800324d0(500);
    iVar5 = FUN_80036d3c();
    if (iVar5 == 0x98) {
      FUN_80036d3c();
      FUN_800324d0(1);
      iVar5 = FUN_80036d3c();
      if (iVar5 == 0x98) {
        *piVar2 = 0;
        FUN_800376f8(s_ERR_DEVICE____800244d4);
        return 0xffffffff;
      }
      while ((local_28 & 0x80000000) == 0) {
        FUN_80036d3c();
      }
      *piVar2 = 3;
      pcVar4 = s_TYPE_MMC____800244c4;
      goto LAB_80024268;
    }
    if (iVar5 != 0) {
      *piVar2 = 0;
      FUN_800376f8(s_Init_Error____80024488);
      return 0xffffffff;
    }
    FUN_80036d3c();
    while ((local_28 & 0x80000000) == 0) {
      FUN_80036d3c();
      FUN_80036d3c();
    }
  }
  pcVar4 = s_TYPE_SD_LOW____800244e8;
  *piVar2 = 2;
LAB_80024268:
  FUN_800376f8(pcVar4);
  if (*piVar2 != 0) {
    FUN_80036d3c();
    puVar6 = DAT_800244bc;
    *DAT_800244bc = local_28;
    puVar6[1] = local_2c;
    puVar6[2] = local_30;
    puVar6[3] = local_34;
    if (*piVar2 == 3) {
      iVar5 = FUN_80036d3c();
      if (iVar5 != 0) {
        return 0xffffffff;
      }
      local_28 = 0x10000;
    }
    else {
      iVar5 = FUN_80036d3c();
      if (iVar5 != 0) {
        return 0xffffffff;
      }
    }
    piVar2[1] = local_28;
  }
  FUN_8001bf1c();
  FUN_800262e0();
  return 0;
}


