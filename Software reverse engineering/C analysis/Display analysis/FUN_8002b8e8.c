void FUN_8002b8e8(void)

{
  short sVar1;
  undefined *puVar2;
  int *piVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  short *psVar8;
  short *psVar9;
  uint uVar10;
  int iVar11;
  
  sVar4 = FUN_800232b4(DAT_8002b9a8);
  sVar5 = FUN_800232b4(DAT_8002b9ac);
  sVar6 = FUN_800232b4(DAT_8002b9b0);
  set_screen_to_global_pointer();
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_8002b9b4;
  uVar10 = 0xc0;
  do {
    iVar11 = 0xb4;
    psVar8 = (short *)(*piVar3 + uVar10 * 0x640 + 0x226);
    psVar9 = (short *)(puVar2 + uVar10 * 0x2d0 + -0x21c00);
    do {
      sVar1 = *psVar9;
      sVar7 = sVar6;
      if (((sVar1 != 0) && (sVar7 = sVar4, sVar1 != -0x800)) && (sVar7 = sVar1, sVar1 == 0x7e0)) {
        sVar7 = sVar5;
      }
      iVar11 = iVar11 + -1;
      *psVar8 = sVar7;
      psVar8 = psVar8 + 1;
      psVar9 = psVar9 + 2;
    } while (iVar11 != 0);
    uVar10 = uVar10 + 1 & 0xfffeffff;
  } while (uVar10 < 0x121);
  do {
    iVar11 = FUN_80022fd0();
  } while (iVar11 == 2);
  return;
}

