//f_stat

int f_stat(void)

{
  uchar *in_r0;
  int iVar1;
  byte in_r1;
  byte in_r2;
  undefined4 uStack80;
  void *apvStack72 [7];
  int iStack44;
  byte bStack29;
  uchar *local_18 [3];
  
  local_18[0] = in_r0;

  iVar1 = mount_volume(local_18,(void **)&uStack80,2);

  if (iVar1 != 0)
  {
    return iVar1;
  }

  apvStack72[0] = uStack80;

  iVar1 = follow_path(apvStack72,(char *)local_18[0]);

  if (iVar1 == 0)
  {
    if ((bStack29 & 0xa0) == 0)
    {
      *(byte *)(iStack44 + 0xb) = *(byte *)(iStack44 + 0xb) & ~(in_r2 & 0x27) | in_r1 & in_r2 & 0x27;

      *(undefined *)((int)uStack80 + 3) = 1;

      iVar1 = FUN_800372c0();

      return iVar1;
    }

    return 6;
  }

  return iVar1;
}

