
//Makes use of the frame buffer at 0x804FB9B4
//Shares part of its function with code of address 0x80011FEC (Also used by FUN_8001178c)

//The data handling part. Only the data setup is unique


void FUN_800114d0(void)

{
  ushort uVar1;
  ushort uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined2 *puVar8;
  uint uVar9;
  undefined2 *puVar10;
  undefined2 *puVar11;
  uint unaff_r4;
  uint uVar12;
  uint uVar13;
  undefined2 *puVar14;
  
  uVar1 = *(ushort *)(PTR_DAT_800114f0 + 6);
  uVar2 = *(ushort *)(PTR_DAT_800114f0 + 4);
  FUN_800232b4(DAT_80012254);
  FUN_800232b4(DAT_80012258);
  iVar6 = DAT_80012264;
  iVar5 = DAT_80012260;
  uVar4 = DAT_8001225c;
  uVar13 = DAT_8001225c - unaff_r4;
  uVar9 = 0;
  uVar12 = uVar13 * 0x8000 >> 0x10;
  do {
    if (unaff_r4 < uVar4) {
      puVar14 = (undefined2 *)(iVar6 + (uVar9 * DAT_8001225c + unaff_r4) * 2);
      puVar11 = (undefined2 *)(iVar5 + (unaff_r4 + uVar9 * 800) * 2);
      uVar3 = uVar12;
      puVar8 = puVar11 + -1;
      puVar10 = puVar14 + -1;
      if ((uVar13 & 1) != 0) {
        *puVar14 = *puVar11;
        puVar8 = puVar11;
        puVar10 = puVar14;
      }
      while (uVar3 != 0) {
        puVar10[1] = puVar8[1];
        puVar10[2] = puVar8[2];
        uVar3 = uVar3 - 1 & 0xffff;
        puVar8 = puVar8 + 2;
        puVar10 = puVar10 + 2;
      }
    }
    uVar9 = uVar9 + 1 & 0xfffeffff;
  } while (uVar9 < 0x3b);
  set_display_color(DAT_80012268);
  display_clear_rect(0,0,(ushort)uVar4,0x3a);
  set_display_color(DAT_8001226c);
  FUN_80018da0(0,0,uVar4,0x3a);
  set_display_color(DAT_80012270);
  FUN_80018ff0(0x14,0x18,DAT_80012274,0x22,2);
  set_screen_pointer();
  piVar7 = DAT_80012278;
  uVar9 = 0;
  uVar12 = uVar4;
  do {
    uVar9 = uVar9 + 1 & 0xfffeffff;
    if (0x3a < uVar9) {
      uVar12 = (uVar12 - (uVar12 * DAT_8001227c >> 0x14)) - 1 & 0xffff;
      if (uVar12 < 2) {
        uVar13 = 0;
        uVar9 = (uVar4 - uVar12) * 0x8000 >> 0x10;
        do {
          puVar14 = (undefined2 *)(iVar6 + (uVar13 * DAT_8001225c + uVar12) * 2);
          puVar11 = (undefined2 *)(iVar5 + (uVar12 + uVar13 * 800) * 2);
          uVar3 = uVar9;
          puVar8 = puVar11 + -1;
          puVar10 = puVar14 + -1;
          if ((uVar4 - uVar12 & 1) != 0) {
            *puVar11 = *puVar14;
            puVar8 = puVar11;
            puVar10 = puVar14;
          }
          while (uVar3 != 0) {
            puVar8[1] = puVar10[1];
            puVar8[2] = puVar10[2];
            uVar3 = uVar3 - 1 & 0xffff;
            puVar8 = puVar8 + 2;
            puVar10 = puVar10 + 2;
          }
          do {
            uVar13 = uVar13 + 1 & 0xfffeffff;
            if (0x3a < uVar13) {
              *DAT_80017774 = DAT_80017770;
              return;
            }
          } while (uVar4 <= uVar12);
        } while( true );
      }
      uVar9 = 0;
    }
    if (uVar12 < uVar4) {
      puVar14 = (undefined2 *)
                (*piVar7 +
                ((uVar9 + (uVar1 + 0x3b & 0xfffeffff)) * 800 + (uVar2 + 0xf4 & 0xfffeffff)) * 2);
      puVar11 = (undefined2 *)(iVar5 + (uVar12 + uVar9 * 800) * 2);
      puVar8 = puVar14 + -1;
      puVar10 = puVar11 + -1;
      if ((uVar4 - uVar12 & 1) != 0) {
        *puVar14 = *puVar11;
        puVar8 = puVar14;
        puVar10 = puVar11;
      }
      uVar13 = (uVar4 - uVar12) * 0x8000 >> 0x10;
      while (uVar13 != 0) {
        puVar8[1] = puVar10[1];
        puVar10 = puVar10 + 2;
        uVar13 = uVar13 - 1 & 0xffff;
        puVar8 = puVar8 + 2;
        *puVar8 = *puVar10;
      }
    }
  } while( true );
}

