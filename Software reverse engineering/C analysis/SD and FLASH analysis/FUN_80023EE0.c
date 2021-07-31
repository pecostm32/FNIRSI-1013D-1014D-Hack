//sys_sd_card_init. This original one is longer????

undefined4 FUN_80023ee0(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int *piVar3;
  uint *puVar4;
  char *pcVar5;
  int iVar6;
  uint *puVar7;
  uint *puVar8;
  uint *puVar9;
  undefined4 unaff_r9;
  undefined2 local_40 [2];
  undefined4 local_3c;
  undefined4 local_38;
  uint local_34;
  uint local_30;
  uint local_2c;
  uint local_28;
  
  uVar2 = DAT_80024464;
  puVar7 = DAT_8002445c;
  puVar8 = DAT_8002445c + 0x400;
  puVar9 = DAT_8002445c;
  if ((param_1 != 0) && (puVar9 = puVar8, param_1 != 1)) {
    puVar9 = (uint *)0x0;
  }
  if (param_1 == 0) {
    unaff_r9 = DAT_80024460;
  }
  iVar6 = 0;
  if (param_1 == 0) {
    do {
      FUN_8001764c(unaff_r9,iVar6,2,0);
      iVar6 = iVar6 + 1;
    } while (iVar6 < 6);
  }
  else {
    if (param_1 == 1) {
      do {
        FUN_8001764c(uVar2,iVar6,3,0);
        iVar6 = iVar6 + 1;
      } while (iVar6 < 3);
    }
  }
  puVar4 = DAT_80024468;
  uVar1 = 1 << (param_1 + 8U & 0xff);
  *DAT_80024468 = *DAT_80024468 | uVar1;
  puVar4[0x98] = uVar1 | puVar4[0x98];
  FUN_800324d0(1);
  FUN_8003572c(param_1,DAT_8002446c);
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  puVar4[0x1e] = puVar4[0x1e] | 2;
  puVar4[0x1e] = puVar4[0x1e] & 0xfffffffd;
  uVar2 = DAT_80024470;
  FUN_8000bc34(DAT_80024470);
  puVar4[0x1e] = puVar4[0x1e] | 2;
  FUN_8000bc34(uVar2);
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  *puVar4 = *puVar4 | 7;
  FUN_8000bc34(uVar2);
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  *puVar4 = *puVar4 & 0xfffffeff;
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  puVar4[1] = puVar4[1] | 0x20000;
  puVar4 = puVar7;
  if ((param_1 != 0) && (puVar4 = puVar8, param_1 != 1)) {
    puVar4 = (uint *)0x0;
  }
  puVar4[3] = 0;
  puVar9[2] = 0xffffffff;
  if ((param_1 != 0) && (puVar7 = puVar8, param_1 != 1)) {
    puVar7 = (uint *)0x0;
  }
  puVar7[1] = puVar7[1] | 0x10000;
  FUN_80035c1c();
  FUN_800324d0(0x32);
  local_40[0] = 0;
  local_38 = 0;
  local_3c = 0;
  FUN_80036d3c(param_1,local_40);
  FUN_800324d0(500);
  local_3c = 5;
  local_40[0] = 8;
  local_38 = DAT_80024474;
  iVar6 = FUN_80036d3c(param_1,local_40,0);
  piVar3 = DAT_80024478;
  if (iVar6 == 0) {
    FUN_800376f8(s_SD2_0____80024498);
    local_40[0] = 0x37;
    local_38 = 0;
    local_3c = 5;
    FUN_80036d3c(param_1,local_40);
    uVar2 = _DAT_800244a4;
    local_40[0] = 0x29;
    local_3c = 7;
    local_38 = _DAT_800244a4;
    FUN_80036d3c(param_1,local_40,0);
    while ((local_28 & 0x80000000) == 0) {
      local_40[0] = 0x37;
      local_38 = 0;
      local_3c = 5;
      FUN_80036d3c(param_1,local_40);
      local_40[0] = 0x29;
      local_3c = 7;
      local_38 = uVar2;
      FUN_80036d3c(param_1,local_40,0);
    }
    if ((local_28 & 0x40000000) != 0) {
      pcVar5 = s__TYPE_SD_HIGH____800244a7 + 1;
      *piVar3 = 1;
      goto LAB_80024268;
    }
  }
  else {
    FUN_800376f8(s_SD1_1____8002447c);
    local_40[0] = 0;
    local_38 = 0;
    local_3c = 0;
    FUN_80036d3c(param_1,local_40);
    FUN_800324d0(500);
    local_40[0] = 0x37;
    local_38 = 0;
    local_3c = 5;
    iVar6 = FUN_80036d3c(param_1,local_40);
    uVar2 = DAT_800244e4;
    if (iVar6 == 0x98) {
      local_40[0] = 0;
      local_38 = 0;
      local_3c = 0;
      FUN_80036d3c(param_1,local_40);
      FUN_800324d0(1);
      uVar2 = DAT_800244c0;
      local_40[0] = 1;
      local_3c = 5;
      local_38 = DAT_800244c0;
      iVar6 = FUN_80036d3c(param_1,local_40,0);
      if (iVar6 == 0x98) {
        *piVar3 = 0;
        FUN_800376f8(s_ERR_DEVICE____800244d4);
        return 0xffffffff;
      }
      while ((local_28 & 0x80000000) == 0) {
        local_3c = 5;
        local_40[0] = 1;
        local_38 = uVar2;
        FUN_80036d3c(param_1,local_40,0);
      }
      *piVar3 = 3;
      pcVar5 = s_TYPE_MMC____800244c4;
      goto LAB_80024268;
    }
    if (iVar6 != 0) {
      *piVar3 = 0;
      FUN_800376f8(s_Init_Error____80024488);
      return 0xffffffff;
    }
    local_3c = 7;
    local_40[0] = 0x29;
    local_38 = DAT_800244e4;
    FUN_80036d3c(param_1,local_40,0);
    while ((local_28 & 0x80000000) == 0) {
      local_40[0] = 0x37;
      local_38 = 0;
      local_3c = 5;
      FUN_80036d3c(param_1,local_40);
      local_40[0] = 0x29;
      local_3c = 7;
      local_38 = uVar2;
      FUN_80036d3c(param_1,local_40,0);
    }
  }
  pcVar5 = s_TYPE_SD_LOW____800244e8;
  *piVar3 = 2;
LAB_80024268:
  FUN_800376f8(pcVar5);
  if (*piVar3 != 0) {
    local_40[0] = 2;
    local_3c = 7;
    local_38 = 0;
    FUN_80036d3c(param_1,local_40);
    puVar7 = DAT_800244bc;
    *DAT_800244bc = local_28;
    puVar7[1] = local_2c;
    puVar7[2] = local_30;
    puVar7[3] = local_34;
    if (*piVar3 == 3) {
      local_40[0] = 3;
      local_3c = 7;
      local_38 = 0x10000;
      iVar6 = FUN_80036d3c(param_1,local_40,0);
      if (iVar6 != 0) {
        return 0xffffffff;
      }
      local_28 = 0x10000;
    }
    else {
      local_40[0] = 3;
      local_3c = 7;
      local_38 = 0;
      iVar6 = FUN_80036d3c(param_1,local_40,0);
      if (iVar6 != 0) {
        return 0xffffffff;
      }
    }
    piVar3[1] = local_28;
  }
  FUN_8001bf1c(param_1,local_40,DAT_80024554);
  FUN_800262e0(param_1,local_40,1);
  return 0;
}

