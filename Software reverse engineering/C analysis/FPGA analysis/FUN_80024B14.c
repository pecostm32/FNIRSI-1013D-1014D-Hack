//Process the received bytes with some xoring scheme
void FUN_80024b14(void)
{
  byte *pbVar1;
  uint uVar2;
  byte bVar3;
  
  pbVar1 = DAT_80024c78;                                                 //0x8035EC04. Buffer in DRAM
  uVar2 = 1;
  bVar3 = ~*DAT_80024c78;                                                //Byte received from command 68 inverted
  *DAT_80024c78 = ~*DAT_80024c78;                                        //Keep it in the same spot for later

  do
  {
    if ((bVar3 & 0x80) != 0)                                             //When bit 7 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x80 | pbVar1[uVar2] & 0x7f;      //Invert bit 7 and or it back in with the rest of the bits
    }

    if ((bVar3 & 0x40) != 0)                                             //When bit 6 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x40 | pbVar1[uVar2] & 0xbf;      //Invert bit 6 and or it back in with the rest of the bits
    }

    if ((bVar3 & 0x20) != 0)                                             //When bit 5 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x20 | pbVar1[uVar2] & 0xdf;      //Invert bit 5 and or it back in with the rest of the bits
    }

    if ((bVar3 & 0x10) != 0)                                             //When bit 4 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 0x10 | pbVar1[uVar2] & 0xef;      //Invert bit 4 and or it back in with the rest of the bits
    }

    if ((bVar3 & 8) != 0)                                                //When bit 3 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 8 | pbVar1[uVar2] & 0xf7;         //Invert bit 3 and or it back in with the rest of the bits
    }

    if ((bVar3 & 4) != 0)                                                //When bit 2 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 4 | pbVar1[uVar2] & 0xfb;         //Invert bit 2 and or it back in with the rest of the bits
    }

    if ((bVar3 & 2) != 0)                                                //When bit 1 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 2 | pbVar1[uVar2] & 0xfd;         //Invert bit 1 and or it back in with the rest of the bits
    }

    if ((bVar3 & 1) != 0)                                                //When bit 0 of the byte from command 0x68 is set
    {
      pbVar1[uVar2] = ~pbVar1[uVar2] & 1 | pbVar1[uVar2] & 0xfe;         //Invert bit 0 and or it back in with the rest of the bits
    }

    uVar2 = uVar2 + 1 & 0xff;
  } while (uVar2 < 7);                                                  //Process each of the received bytes except the first
  return;
}

