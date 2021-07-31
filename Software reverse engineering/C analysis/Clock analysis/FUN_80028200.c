//Video clock configuration

void FUN_80028200(int param_1)
{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  
  puVar3 = DAT_80028324;
  puVar4 = *(uint **)(param_1 + 0x10);
  *DAT_80028324 = *DAT_80028324 & 0x7fffffff;
  *puVar3 = DAT_80028328;
  *puVar3 = *puVar3 | 0x80000000;
  FUN_8000bc00(1);
  puVar3 = DAT_8002832c;
  *DAT_8002832c = *DAT_8002832c | 0x10;
  puVar2 = puVar3 + 0x2d;
  *puVar2 = *puVar2 | 0x80000000;
  puVar3 = puVar3 + 0x98;
  *puVar3 = *puVar3 | 0x10;
  FUN_8000bc00(1);
  *puVar4 = *puVar4 & 0xfffffffe;
  puVar4[0x10] = ((uint)*(byte *)(param_1 + 0x50) + (uint)*(byte *)(param_1 + 0x54) + (uint)*(byte *)(param_1 + 0x58) & 0x1f) << 4 | 0x80000000;
  puVar4[0x11] = 0xf0000006;
  puVar4[0x12] = *(int *)(param_1 + 0x20) - 1U | (*(ushort *)(param_1 + 0x1c) - 1) * 0x10000;
  puVar4[0x13] = DAT_80028330;
  puVar4[0x14] = DAT_80028334;
  puVar4[0x15] = 0x160000;
  puVar4[0x16] = 0;
  puVar4[0x18] = 0;
  uVar1 = 0x10000000;

  if (*(int *)(param_1 + 0x5c) == 0)
  {
    uVar1 = 0x12000000;
  }

  if (*(int *)(param_1 + 0x60) == 0)
  {
    uVar1 = uVar1 | 0x1000000;
  }

  if (*(int *)(param_1 + 100) == 0)
  {
    uVar1 = uVar1 | 0x8000000;
  }

  if (*(int *)(param_1 + 0x68) == 0)
  {
    uVar1 = uVar1 | 0x4000000;
  }

  puVar4[0x22] = uVar1;
  puVar4[0x23] = 0;
  return;
}

