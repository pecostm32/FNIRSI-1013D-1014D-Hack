
// source = 0x8019D5A0
// dest = 0x80192E9C
// count = 0xA704                 == 42756

// 0x80192E9C + 0xA704 = 0x8019D5A0

//So data written from address 0x80192E9C to address 0x8019D5A0 is copied back to address 0x80192E9C in some special way
//The first copy is for 0xA18 (2584) bytes and concerns data that came from the flash
//The second special copy is for 0xA704 (42756) bytes.

//With this action it is well possible that the touch panel config is also filled in

//Some sort of run length packing is used.

//The first byte in the data is 0xC1
//The low nibble is copied to a variable anded with 0x07. So 1 to 7, because if it is zero the next byte of the data is copied to this variable
//The high nibble is copied to another variable
//If this is zero the next byte of the data is copied into this variable.


void do_some_initial_byte_handling(uchar *source,uchar *dest,uint count)

{
  byte bVar1;
  byte *pbVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  pbVar3 = dest + count;

  do
  {
    uVar4 = (uint)*source;
    pbVar2 = source + 1;
    uVar5 = uVar4 & 7;

    if ((*source & 7) == 0)
    {
      uVar5 = (uint)*pbVar2;
      pbVar2 = source + 2;
    }

    uVar6 = (int)uVar4 >> 4;
    source = pbVar2;

    if (uVar6 == 0) 
    {
      uVar6 = (uint)*pbVar2;
      source = pbVar2 + 1;
    }

    while (uVar5 = uVar5 - 1, uVar5 != 0)
    {
      *dest = *source;
      dest = dest + 1;
      source = source + 1;
    }

    if ((int)(uVar4 << 0x1c) < 0)
    {
      bVar1 = *source;
      source = source + 1;
      pbVar2 = dest + -(uint)bVar1;
      iVar7 = uVar6 + 1;

      do
      {
        bVar1 = *pbVar2;
        pbVar2 = pbVar2 + 1;
        *dest = bVar1;
        dest = dest + 1;
        iVar7 = iVar7 + -1;
      } while (-1 < iVar7);
    }
    else
    {
      uVar5 = uVar6;

      if (uVar6 != 0)
      {
        do
        {
          uVar5 = uVar5 - 1;
          dest[uVar5] = 0;
        } while (uVar5 != 0);

        dest = dest + uVar6;
      }
    }
  } while (dest < pbVar3);
  return;
}

