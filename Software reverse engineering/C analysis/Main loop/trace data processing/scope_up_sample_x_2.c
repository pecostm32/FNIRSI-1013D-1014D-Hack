//------------------------------------------------------------------------------------------------------------------------------------------------
//From all locations this function is called with offset = 0 so could be removed

void scope_up_sample_x_2(uint16 *buffer,uint offset,uint count)
{
  ushort *puVar1;
  ushort *puVar2;
  uint uVar3;
  uint uVar4;
  uint16 *puVar5;
  uint16 *puVar6;
  uint uVar7;
  
  puVar1 = DAT_80013758;   //0x801AEF2A another trace buffer?
  uVar3 = count >> 1;      //Process two samples at a time

  if (uVar3 != 0)          //Only if there is data to process!! duhhh
  {
    puVar5 = (uint16 *)((int)buffer + offset * 2);   //Pointer to the data buffer with offset taken into account

    puVar2 = DAT_80013758 + -2;    //0x801AEF26 (pointer calc)

    puVar6 = (uint16 *)((int)puVar5 + -2);   //Buffer pointer also before the start

    if ((uVar3 & 1) != 0)   //First bit set of divided count???
    {
      *DAT_80013758 = *(ushort *)puVar5;
      puVar2 = puVar1;
      puVar6 = puVar5;
    }

    //Half the number of samples again
    uVar7 = (uVar3 << 0xf) >> 0x10;

    while (uVar7 != 0)
    {
      puVar2[2] = *(ushort *)((int)puVar6 + 2);   //dest[2] = source[1]

      puVar6 = (uint16 *)((int)puVar6 + 4);
      puVar2 = puVar2 + 4;

      *puVar2 = *(ushort *)puVar6;               //dest[4] = source[3]

      uVar7 = uVar7 - 1 & 0xffff;
    }
  }

  uVar7 = (count >> 1) - 1;

  if (0 < (int)uVar7)
  {
    puVar2 = puVar1 + -2;     //The temp trace buffer

    if ((uVar7 & 1) != 0)
    {
      puVar1[1] = (ushort)((uint)*puVar1 + (uint)puVar1[2] >> 1);
      puVar2 = puVar1;
    }

    uVar7 = uVar7 * 0x8000 >> 0x10;

    while (uVar7 != 0)
    {
      uVar4 = (uint)puVar2[4];
      puVar2[3] = (ushort)(puVar2[2] + uVar4 >> 1);
      uVar7 = uVar7 - 1 & 0xffff;
      puVar2[5] = (ushort)(uVar4 + puVar2[6] >> 1);
      puVar2 = puVar2 + 4;
    }
  }






  if (count == 0)
  {
    return;
  }

  puVar6 = (uint16 *)((int)buffer + -2);
  puVar2 = puVar1 + -1;

  if ((count & 1) != 0)
  {
    *(ushort *)buffer = *puVar1;
    puVar6 = buffer;
    puVar2 = puVar1;
  }

  if (uVar3 == 0)
  {
    return;
  }

  do
  {
    uVar3 = uVar3 - 1;
    *(ushort *)((int)puVar6 + 2) = puVar2[1];
    puVar2 = puVar2 + 2;
    puVar6 = (uint16 *)((int)puVar6 + 4);
    *(ushort *)puVar6 = *puVar2;
  } while (uVar3 != 0);

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

