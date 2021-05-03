void FUN_80011154(void)

{
  undefined *puVar1;
  undefined *puVar2;
  int *piVar3;
  int iVar4;
  short sVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  short *psVar9;
  short *psVar10;
  short sVar11;
  
  sVar5 = FUN_800232b4(DAT_8001123c);
  set_screen_to_global_pointer();
  iVar4 = DAT_8001124c;
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80011244;
  puVar1 = PTR_DAT_80011240;
  uVar8 = 0xc5;
  do {
    uVar6 = 0;
    do {
      if (uVar8 < 0xc5) {
        uVar7 = 0xc5 - uVar8 & 0xffff;
        psVar9 = (short *)(puVar1 + (uVar6 * 0xc5 + uVar8) * 2);
        psVar10 = (short *)(*piVar3 + ((*(ushort *)(puVar2 + 6) + uVar6) * 800 +
                                      (uint)*(ushort *)(puVar2 + 4)) * 2 + iVar4);
        do {
          sVar11 = *psVar9;
          if (*psVar9 == 0) {
            sVar11 = sVar5;
          }
          uVar7 = uVar7 - 1 & 0xffff;
          *psVar10 = sVar11;
          psVar9 = psVar9 + 1;
          psVar10 = psVar10 + 1;
        } while (uVar7 != 0);
      }
      uVar6 = uVar6 + 1 & 0xfffeffff;
    } while (uVar6 < 0x3c);
    uVar8 = (uVar8 - (uVar8 * DAT_80011250 + 0xa3d7 >> 0x14)) - 1 & 0xffff;
  } while (1 < uVar8);
  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}

