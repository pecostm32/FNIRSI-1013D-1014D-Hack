void FUN_8000ea18(void)

{
  uint uVar1;
  uint uVar2;
  undefined *puVar3;
  int *piVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  ushort *puVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  
  uVar2 = DAT_8000eaf8;
  uVar1 = DAT_8000eaf4;
  set_screen_to_global_pointer();
  iVar7 = DAT_8000eb0c;
  uVar6 = DAT_8000eb08;
  uVar5 = DAT_8000eb04;
  piVar4 = Global_Frame_Buffer_Pointer;
  puVar3 = PTR_DAT_8000eafc;
  uVar15 = 0;
  do {
    uVar11 = 0;
    do {
      if (uVar15 != 0) {
        puVar8 = (undefined2 *)(*piVar4 + (uVar11 * 800 - uVar15) * 2 + 0x67174);
        puVar10 = (ushort *)(puVar3 + uVar11 * DAT_8000eb08 * 2);
        uVar12 = uVar15;
        do {
          uVar13 = (uint)*puVar10;
          uVar14 = uVar1;
          if (uVar13 != 0) {
            if (uVar13 == 0xf800) {
              uVar14 = 0;
            }
            else {
              uVar14 = uVar13;
              if (uVar13 == uVar5) {
                uVar14 = uVar2;
              }
            }
          }
          uVar12 = uVar12 - 1;
          *puVar8 = (short)uVar14;
          puVar8 = puVar8 + 1;
          puVar10 = puVar10 + 1;
        } while (uVar12 != 0);
      }
      uVar11 = uVar11 + 1 & 0xfffeffff;
    } while (uVar11 < 0xd6);
    iVar9 = (int)((ulonglong)((longlong)iVar7 * (longlong)(int)(uVar6 - uVar15)) >> 0x20);
    uVar15 = (((iVar9 >> 2) - (iVar9 >> 0x1f)) + uVar15 & 0xffff) + 1 & 0xfffeffff;
  } while (uVar15 < uVar6);
  return;
}

