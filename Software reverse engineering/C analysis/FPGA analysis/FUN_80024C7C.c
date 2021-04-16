//Do some data processing, based on the contents of some global variable
void FUN_80024c7c(void)
{
  byte bVar1;
  byte *pbVar2;
  byte bVar3;
  uint uVar4;
  
  pbVar2 = DAT_80024e14;           //0x8035EC04
  bVar1 = *DAT_80024e14;
  uVar4 = 1;

  do
  {
    if ((bVar1 & 0x80) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x80 | pbVar2[uVar4] & 0x7f;
    }

    if ((bVar1 & 0x40) != 0) 
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x40 | pbVar2[uVar4] & 0xbf;
    }

    if ((bVar1 & 0x20) != 0) 
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x20 | pbVar2[uVar4] & 0xdf;
    }

    if ((bVar1 & 0x10) != 0) 
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 0x10 | pbVar2[uVar4] & 0xef;
    }

    if ((bVar1 & 8) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 8 | pbVar2[uVar4] & 0xf7;
    }

    if ((bVar1 & 4) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 4 | pbVar2[uVar4] & 0xfb;
    }

    if ((bVar1 & 2) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 2 | pbVar2[uVar4] & 0xfd;
    }

    if ((bVar1 & 1) != 0)
    {
      pbVar2[uVar4] = ~pbVar2[uVar4] & 1 | pbVar2[uVar4] & 0xfe;
    }

    uVar4 = uVar4 + 1 & 0xff;
  } while (uVar4 < 7);

  bVar3 = 0;
  if ((bVar1 & 4) != 0) 
  {
    bVar3 = 0x80;
  }

  if ((bVar1 & 0x10) != 0)
  {
    bVar3 = bVar3 | 0x40;
  }

  if ((bVar1 & 1) != 0)
  {
    bVar3 = bVar3 | 0x20;
  }

  if ((bVar1 & 0x40) != 0)
  {
    bVar3 = bVar3 | 0x10;
  }

  if ((bVar1 & 2) != 0)
  {
    bVar3 = bVar3 | 8;
  }

  if ((bVar1 & 0x80) != 0)
  {
    bVar3 = bVar3 | 4;
  }

  if ((bVar1 & 8) != 0)
  {
    bVar3 = bVar3 | 2;
  }

  if ((bVar1 & 0x20) != 0)
  {
    bVar3 = bVar3 | 1;
  }

  *pbVar2 = bVar3;
  return;
}


