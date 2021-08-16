//------------------------------------------------------------------------------------------------------------------------------------------------

void scope_pre_process_100ns_data(uint16 *buffer,uint offset,uint count)

{
  uint uVar1;
  ushort uVar2;
  ushort *puVar3;
  ushort *puVar4;
  uint uVar5;
  uint16 *puVar6;
  uint16 *puVar7;
  ushort uVar8;
  
  puVar3 = DAT_8001437c;                    //0x801AEF2A    temptracebuffer

  uVar5 = count * DAT_80014378 >> 0x12;     //0x0000CCCD  (reduces 2500 to 500 so / 5)

  if (uVar5 != 0)
  {
    puVar6 = (uint16 *)((int)buffer + offset * 2);
    puVar4 = DAT_8001437c + -5;
    puVar7 = (uint16 *)((int)puVar6 + -2);

    //Odd number to do
    if ((uVar5 & 1) != 0)
    {
      *DAT_8001437c = *(ushort *)puVar6;
      puVar4 = puVar3;
      puVar7 = puVar6;
    }

    //Two samples per run
    uVar1 = (uVar5 << 0xf) >> 0x10;

    //Process them interleaved on 5 samples
    while (uVar1 != 0)
    {
      puVar4[5] = *(ushort *)((int)puVar7 + 2);
      puVar7 = (uint16 *)((int)puVar7 + 4);
      uVar1 = uVar1 - 1 & 0xffff;
      puVar4 = puVar4 + 10;
      *puVar4 = *(ushort *)puVar7;
    }
  }

  uVar1 = DAT_80014380;    //0xCCCCCCCD

  if (0 < (int)(uVar5 - 1))
  {
    uVar5 = uVar5 - 1 & 0xffff;
    puVar4 = DAT_8001437c;

    do
    {
      uVar2 = *puVar4;
      uVar8 = puVar4[5];

      if (uVar2 < uVar8)
      {
        uVar8 = uVar8 - uVar2;
        puVar4[1] = uVar2 + (ushort)((uint)uVar8 * DAT_80014378 >> 0x12);
        puVar4[2] = (short)(uint)((ulonglong)uVar8 * 2 * (ulonglong)uVar1 >> 0x22) + uVar2;
        puVar4[3] = (short)(uint)((ulonglong)((uint)uVar8 * 3) * (ulonglong)uVar1 >> 0x22) + uVar2;
        puVar4[4] = uVar2 + (short)(uint)((ulonglong)uVar8 * 4 * (ulonglong)uVar1 >> 0x22);
      }
      else
      {
        uVar8 = uVar2 - uVar8;
        puVar4[1] = uVar2 - (ushort)((uint)uVar8 * DAT_80014378 >> 0x12);
        puVar4[2] = uVar2 - (short)(uint)((ulonglong)uVar8 * 2 * (ulonglong)uVar1 >> 0x22);
        puVar4[3] = uVar2 - (short)(uint)((ulonglong)((uint)uVar8 * 3) * (ulonglong)uVar1 >> 0x22);
        puVar4[4] = uVar2 - (short)(uint)((ulonglong)uVar8 * 4 * (ulonglong)uVar1 >> 0x22);
      }

      uVar5 = uVar5 - 1 & 0xffff;
      puVar4 = puVar4 + 5;
    } while (uVar5 != 0);
  }

  if (count == 0)
  {
    return;
  }

  puVar7 = (uint16 *)((int)buffer + -2);
  puVar4 = puVar3 + -1;

  if ((count & 1) != 0)
  {
    *(ushort *)buffer = *puVar3;
    puVar7 = buffer;
    puVar4 = puVar3;
  }

  uVar5 = count >> 1;

  if (uVar5 == 0)
  {
    return;
  }

  do
  {
    uVar5 = uVar5 - 1;
    *(ushort *)((int)puVar7 + 2) = puVar4[1];
    puVar4 = puVar4 + 2;
    puVar7 = (uint16 *)((int)puVar7 + 4);
    *(ushort *)puVar7 = *puVar4;
  } while (uVar5 != 0);

  return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------

