void FUN_8000e6f8(void)

{
  short sVar1;
  undefined *puVar2;
  undefined *puVar3;
  int *piVar4;
  short sVar5;
  short sVar6;
  uint uVar7;
  uint uVar8;
  short *psVar9;
  int iVar10;
  short *psVar11;
  short sVar12;
  
  sVar5 = FUN_800232b4(DAT_8000e7e4);
  sVar6 = FUN_800232b4(0);
  puVar2 = PTR_DAT_8000e7e8;
  *(undefined2 *)PTR_DAT_8000e7e8 = 2;
  *(undefined2 *)(puVar2 + 2) = 0x2e;
  *(undefined2 *)(puVar2 + 4) = 0x97;
  *(undefined2 *)(puVar2 + 6) = 0x2e;
  set_screen_to_global_pointer();
  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_DAT_8000e7ec;
  uVar7 = 0xeb;
  uVar8 = uVar7;
  do {
    while (uVar7 < 0xeb) {
      iVar10 = 0x95;
      psVar9 = (short *)(puVar3 + uVar7 * 0x12a);
      psVar11 = (short *)(*piVar4 +
                         ((uint)*(ushort *)puVar2 +
                         ((uint)*(ushort *)(puVar2 + 2) + (uVar7 - uVar8)) * 800) * 2);
      do {
        sVar1 = *psVar9;
        sVar12 = sVar5;
        if ((sVar1 != 0) && (sVar12 = sVar1, sVar1 == -0x800)) {
          sVar12 = sVar6;
        }
        iVar10 = iVar10 + -1;
        *psVar11 = sVar12;
        psVar9 = psVar9 + 1;
        psVar11 = psVar11 + 1;
      } while (iVar10 != 0);
      uVar7 = uVar7 + 1 & 0xfffeffff;
    }
    uVar7 = (uVar8 - (uVar8 * DAT_8000e7f4 >> 0x14)) - 1 & 0xffff;
    uVar8 = uVar7;
  } while (uVar7 != 0);
  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}

