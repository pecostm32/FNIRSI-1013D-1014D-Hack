int f_open(char **param_1,uchar *param_2,uint param_3)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  char *pcVar4;
  int iVar5;
  char *pcVar6;
  uint uVar7;
  bool bVar8;
  char *local_60 [2];
  char *local_58;
  byte local_52;
  char *local_3c;
  byte local_2d;
  char **ppcStack40;
  uchar *local_24;
  uint uStack32;
  
  if (param_1 == (char **)0x0) {
    return 9;
  }

  pcVar6 = (char *)(param_3 & 0x3f);
  ppcStack40 = param_1;
  local_24 = param_2;
  uStack32 = param_3;

  iVar2 = mount_volume (&local_24,local_60,(uint)pcVar6);

  if (iVar2 != 0) goto LAB_80033afc;
  local_58 = local_60[0];
  iVar2 = FUN_80034d68(&local_58,local_24);
  if ((iVar2 == 0) && ((local_2d & 0x80) != 0)) {
    iVar2 = 6;
  }
  if ((param_3 & 0x1c) == 0) {
    if (iVar2 != 0) goto LAB_80033afc;
    if ((local_52 & 0x10) != 0) {
      iVar2 = 4;
      goto LAB_80033afc;
    }
    bVar8 = (param_3 & 2) == 0;
    if (!bVar8) {
      bVar8 = (local_52 & 1) == 0;
    }
    if (!bVar8) goto LAB_80033868;
LAB_80033990:
    if (((uint)pcVar6 & 8) != 0) {
LAB_80033998:
      pcVar6 = (char *)((uint)pcVar6 | 0x40);
    }
  }
  else {
    if (iVar2 == 0) {
      if ((local_52 & 0x11) != 0) {
LAB_80033868:
        iVar2 = 7;
        goto LAB_80033afc;
      }
      if ((param_3 & 4) != 0) {
        iVar2 = 8;
        goto LAB_80033afc;
      }
    }
    else {
      if (iVar2 == 4) {
        iVar2 = FUN_80032c24(&local_58);
      }
      pcVar6 = (char *)((uint)pcVar6 | 8);
      if (iVar2 != 0) goto LAB_80033afc;
    }
    pcVar4 = local_3c;
    if (((uint)pcVar6 & 8) != 0) {
      uVar7 = (uint)*(ushort *)(local_3c + 0x1a);
      if (*local_60[0] == '\x03') {
        uVar7 = CONCAT22(*(undefined2 *)(local_3c + 0x14),*(ushort *)(local_3c + 0x1a));
      }
      uVar3 = FUN_80035314();
      pcVar4[0xe] = (char)uVar3;
      pcVar4[0xf] = (char)((uint)uVar3 >> 8);
      pcVar4[0x10] = (char)((uint)uVar3 >> 0x10);
      pcVar4[0x11] = (char)((uint)uVar3 >> 0x18);
      local_3c[0xb] = ' ';
      local_3c[0x1a] = '\0';
      local_3c[0x1b] = '\0';
      if (*local_60[0] == '\x03') {
        local_3c[0x14] = '\0';
        local_3c[0x15] = '\0';
      }
      local_3c[0x1c] = '\0';
      local_3c[0x1d] = '\0';
      local_3c[0x1e] = '\0';
      local_3c[0x1f] = '\0';
      local_60[0][3] = '\x01';
      if (uVar7 != 0) {
        uVar3 = *(undefined4 *)(local_60[0] + 0x30);
        iVar2 = FUN_80035f1c(&local_58,uVar7,0);
        if (iVar2 != 0) goto LAB_80033afc;
        iVar2 = FUN_80035ca8(local_60[0],uVar3);
        *(uint *)(local_60[0] + 0x10) = uVar7 - 1;
        if (iVar2 != 0) goto LAB_80033afc;
        goto LAB_80033990;
      }
      goto LAB_80033998;
    }
  }
  param_1[8] = *(char **)(local_60[0] + 0x30);
  param_1[9] = local_3c;
  pcVar4 = (char *)(uint)*(ushort *)(local_3c + 0x1a);
  if (*local_60[0] == '\x03') {
    pcVar4 = (char *)CONCAT22(*(undefined2 *)(local_3c + 0x14),*(ushort *)(local_3c + 0x1a));
  }
  param_1[2] = pcVar4;
  param_1[3] = *(char **)(local_3c + 0x1c);
  *param_1 = local_60[0];
  *(undefined2 *)(param_1 + 1) = *(undefined2 *)(local_60[0] + 6);
  *(char *)(param_1 + 4) = (char)pcVar6;
  *(undefined *)((int)param_1 + 0x11) = 0;
  param_1[7] = (char *)0x0;
  param_1[5] = (char *)0x0;
  FUN_8003558c(param_1 + 10,0,0x200);
  bVar8 = ((uint)pcVar6 & 0x20) == 0;
  if (!bVar8) {
    pcVar6 = param_1[3];
  }
  if (bVar8 || pcVar6 == (char *)0x0) {
    return iVar2;
  }
  param_1[5] = pcVar6;
  pcVar4 = param_1[2];
  uVar1 = *(ushort *)(local_60[0] + 10);
  do {
    if (pcVar6 <= (char *)((uint)uVar1 * 0x200)) {
      param_1[6] = pcVar4;
      if (((uint)pcVar6 & 0x1ff) == 0) {
        return iVar2;
      }
      if ((pcVar4 + -2 < (char *)(*(int *)(local_60[0] + 0x18) + -2)) &&
         (iVar5 = (uint)*(ushort *)(local_60[0] + 10) * (int)(pcVar4 + -2) +
                  *(int *)(local_60[0] + 0x2c), iVar5 != 0)) {
        pcVar6 = (char *)(iVar5 + ((uint)pcVar6 >> 9));
        param_1[7] = pcVar6;
        iVar5 = FUN_80033274(local_60[0][1],param_1 + 10,pcVar6,1);
        if (iVar5 == 0) {
          return iVar2;
        }
        iVar2 = 1;
      }
      else {
        iVar2 = 2;
      }
      goto LAB_80033afc;
    }
    pcVar4 = (char *)FUN_800351e0(param_1);
    if (pcVar4 < (char *)0x2) {
      iVar2 = 2;
    }
    if (pcVar4 == (char *)0xffffffff) {
      iVar2 = 1;
      param_1[6] = (char *)0xffffffff;
      goto LAB_80033afc;
    }
    pcVar6 = pcVar6 + (uint)uVar1 * -0x200;
  } while (iVar2 == 0);
  param_1[6] = pcVar4;
LAB_80033afc:
  *param_1 = (char *)0x0;
  return iVar2;
}

