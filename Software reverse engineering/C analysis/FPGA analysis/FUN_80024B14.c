void FUN_80024b14(void)

{
  byte *pbVar1;
  uint uVar2;
  byte bVar3;
  
  pbVar1 = DAT_80024c78;
  uVar2 = 1;
  bVar3 = ~*DAT_80024c78;
  *DAT_80024c78 = ~*DAT_80024c78;

  do
  {
    if ((bVar3 & 0x80) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x80 | pbVar1[uVar2] & 0x7f;
    }

    if ((bVar3 & 0x40) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x40 | pbVar1[uVar2] & 0xbf;
    }

    if ((bVar3 & 0x20) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x20 | pbVar1[uVar2] & 0xdf;
    }

    if ((bVar3 & 0x10) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x10 | pbVar1[uVar2] & 0xef;
    }

    if ((bVar3 & 8) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 8 | pbVar1[uVar2] & 0xf7;
    }

    if ((bVar3 & 4) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 4 | pbVar1[uVar2] & 0xfb;
    }

    if ((bVar3 & 2) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 2 | pbVar1[uVar2] & 0xfd;
    }

    if ((bVar3 & 1) != 0)
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 1 | pbVar1[uVar2] & 0xfe;
    }

    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 7);
  return;
}

