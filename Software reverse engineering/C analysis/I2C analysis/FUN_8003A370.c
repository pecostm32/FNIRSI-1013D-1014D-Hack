uint FUN_8003a370(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar2 = param_1 & 0x80000000;
  if ((int)uVar2 < 0) {
    param_1 = -param_1;
  }
  uVar3 = count_leading_zeroes(param_1);
  uVar1 = param_1 << (uVar3 & 0xff);
  if (uVar1 == 0) {
    return param_1;
  }
  bVar4 = (bool)((byte)(uVar1 >> 7) & 1);
  uVar2 = (uVar2 | (0x9d - uVar3) * 0x800000) + (uVar1 >> 8) + (uint)bVar4;
  if (!bVar4) {
    return uVar2;
  }
  if ((uVar1 & 0x7f) == 0) {
    uVar2 = uVar2 & 0xfffffffe;
  }
  return uVar2;
}

