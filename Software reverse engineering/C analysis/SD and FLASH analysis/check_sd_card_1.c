int check_sd_card(uint p1,uint p2,uint p3)

{
  byte bVar1;
  byte *pbVar2;
  int iVar4;
  undefined *puVar5;
  uint uVar6;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar7;
  char *local_10;
  uchar *local_c;
  uint uStack8;
  code *UNRECOVERED_JUMPTABLE;
  byte *pbVar3;
  
  iVar4 = DAT_800337c0;
  pbVar3 = (byte *)p2;
  if (p2 != 0) {
    do {
      pbVar2 = pbVar3 + 1;
      bVar1 = *pbVar3;
      if (bVar1 < 0x20) {
        uVar6 = 0;
        goto LAB_80033774;
      }
      pbVar3 = pbVar2;
    } while (bVar1 != 0x3a);
    uVar6 = *(byte *)p2 - 0x30;
    bVar7 = uVar6 == 9;
    if (uVar6 < 10) {
      bVar7 = (byte *)(p2 + 2) == pbVar2;
    }
    if (((bVar7) && ((int)uVar6 < 1)) && (-1 < (int)uVar6)) {
LAB_80033774:
      puVar5 = *(undefined **)(DAT_800337c0 + uVar6 * 4);
      if (puVar5 != (undefined *)0x0) {
        *puVar5 = 0;
      }
      if (p1 != 0) {
        *(undefined *)p1 = 0;
      }
      *(uint *)(iVar4 + uVar6 * 4) = p1;
      local_10 = (char *)p1;
      local_c = (uchar *)p2;
      uStack8 = p3;
      if (p3 != 0) {
        UNRECOVERED_JUMPTABLE = UNRECOVERED_JUMPTABLE_00;
        some_sd_card_stuff_5(&local_c,&local_10,0);
                    // WARNING: Could not recover jumptable at 0x800337bc. Too many branches
                    // WARNING: Treating indirect jump as call
        iVar4 = (*UNRECOVERED_JUMPTABLE)();
        return iVar4;
      }
                    // WARNING: Could not recover jumptable at 0x800337a4. Too many branches
                    // WARNING: Treating indirect jump as call
      iVar4 = (*UNRECOVERED_JUMPTABLE_00)(0);
      return iVar4;
    }
  }
  return 0xb;
}


