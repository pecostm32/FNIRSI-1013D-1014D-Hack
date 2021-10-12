//process_channel1_trace_data

void FUN_8000410c(void)

{
  short sVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  short *psVar5;
  ushort *puVar6;
  short *psVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  
  uVar10 = 0;
  iVar9 = 10;
  uVar8 = 0;
  memcpy(DAT_800043a8,DAT_800043a4,DAT_800043a0);

  switch(*(undefined2 *)(PTR_DAT_800043ac + 0x1a))    //0x80192ec4  sample_index_select
  {
  case 1:
    scope_up_sample_x_2(DAT_800043a8,0,DAT_800043a0);  //up sample by 2
    break;
  case 2:
    FUN_80013eac(DAT_800043a8,0,4000);                          //up sample by 2.5
    break;
  case 3:
    scope_up_sample_x_5(DAT_800043a8,0,DAT_800043b0);  //up sample by 5
    break;
  case 4:
    scope_up_sample_x_10(DAT_800043a8,0,DAT_800043b4);   //up sample by 10
    break;
  case 5:
    FUN_80023648(DAT_800043a8,DAT_800043b8);
    break;
  case 6:
    FUN_80023710(DAT_800043a8,DAT_800043b8);
    break;
  case 7:
    FUN_80023804(DAT_800043a8,DAT_800043b8);
    break;
  case 8:
    FUN_80023574(DAT_800043a8,DAT_800043b8);
    break;
  case 9:
    FUN_8001408c(DAT_800043a8,0,DAT_800043bc);                 //up sample by 4
    break;
  case 10:
    FUN_80023734(DAT_800043a8,DAT_800043b8);
  }

  iVar3 = DAT_800043d0;
  switch(*(undefined2 *)(PTR_DAT_800043ac + 0x1a))
  {
  case 1:
    uVar8 = DAT_800043c0;
    break;
  case 2:
    uVar8 = DAT_800043c4;
    break;
  case 3:
    uVar8 = DAT_800043a0;
    break;
  case 4:
    uVar8 = DAT_800043c8;
    break;
  case 5:
    iVar9 = 0x14;
    break;
  case 6:
    iVar9 = 0x19;
    break;
  case 7:
    iVar9 = 0x32;
    break;
  case 8:
    iVar9 = 100;
    break;
  case 9:
    uVar8 = DAT_800043cc;
    break;
  case 10:
    iVar9 = 0x28;
  }

  if (((*(byte *)(DAT_800043d0 + 10) < 0xb) || (uVar4 = divide(DAT_800043b0,iVar9), uVar4 < *(ushort *)(iVar3 + 0x24))) || (uVar10 = uVar4 - *(ushort *)(iVar3 + 0x24) & 0xffff, uVar10 < uVar10 + 0x2ee))
  {
    sVar1 = (short)DAT_800043dc + 0x4a;
    psVar7 = (short *)((int)DAT_800043a8 + (*(ushort *)PTR_DAT_800043d4 + uVar10 + uVar8) * 2 + -0x3a9a);
    uVar10 = DAT_800043dc;
    psVar5 = DAT_800043d8;

    do
    {
      psVar5[1] = sVar1 - psVar7[1];
      psVar7 = psVar7 + 2;
      uVar10 = uVar10 - 1 & 0xffff;
      psVar5 = psVar5 + 2;
      *psVar5 = sVar1 - *psVar7;
    } while (uVar10 != 0);
  }

  puVar6 = DAT_800043e0;
  uVar10 = DAT_800043c0;
  puVar2 = PTR_DAT_800043ac;

  if (*(char *)(iVar3 + 0x3a) != '\0')
  {
    FUN_8000448c();

    puVar6 = DAT_800043e0;
    uVar10 = DAT_800043c0;
    puVar2 = PTR_DAT_800043ac;
  }
  do
  {
    iVar9 = (int)((((uint)*puVar6 - (uint)*(ushort *)(puVar2 + 0x12)) + 400) * 0x10000) >> 0x10;

    if (iVar9 < 0x2f)
    {
      iVar9 = 0x2f;
    }
    else
    {
      if (0x1c0 < iVar9)
      {
        iVar9 = 0x1c0;
      }
    }

    uVar10 = uVar10 - 1;
    *puVar6 = (ushort)iVar9;
    puVar6 = puVar6 + 1;
  } while (uVar10 != 0);

  return;
}

