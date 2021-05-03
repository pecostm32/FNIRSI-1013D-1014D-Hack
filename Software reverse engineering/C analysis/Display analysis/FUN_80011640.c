void FUN_80011640(void)

{
  uint uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  ushort uVar9;
  uint uVar10;
  ushort *puVar11;
  
  uVar2 = FUN_800232b4(DAT_8001174c);
  uVar3 = FUN_800232b4(0);
  uVar4 = FUN_800232b4(0xffffff);
  set_screen_to_global_pointer();
  uVar1 = DAT_80011750;
  uVar5 = 0xf4;
  do {
    uVar7 = 0;
    do {
      if (uVar5 < 0xf4) {
        uVar6 = 0xf4 - uVar5 & 0xffff;
        puVar8 = (ushort *)(PTR_DAT_8001175c + uVar5 * 2 + uVar7 * 0x1e8);
        puVar11 = (ushort *)
                  (*Global_Frame_Buffer_Pointer +
                  ((*(ushort *)(PTR_DAT_80011754 + 6) + uVar7) * 800 +
                  (uint)*(ushort *)(PTR_DAT_80011754 + 4)) * 2);
        do {
          uVar10 = (uint)*puVar8;
          uVar9 = uVar2;
          if (((uVar10 != 0) && (uVar9 = uVar3, uVar10 != 0xf800)) &&
             (uVar9 = *puVar8, uVar10 == uVar1)) {
            uVar9 = uVar4;
          }
          uVar6 = uVar6 - 1 & 0xffff;
          *puVar11 = uVar9;
          puVar8 = puVar8 + 1;
          puVar11 = puVar11 + 1;
        } while (uVar6 != 0);
      }
      uVar7 = uVar7 + 1 & 0xfffeffff;
    } while (uVar7 < 0x126);
    uVar5 = (uVar5 - (uVar5 * DAT_80011760 >> 0x13)) - 1 & 0xffff;
  } while (uVar5 != 0);
  *Global_Frame_Buffer_Pointer = Screen_Frame_Buffer;
  return;
}

