


//called with 0x8035344E
//called with 0x80356EE6

void restore_system_setup(void *buffer)

{
  char cVar1;
  ushort uVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int *piVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  int *piVar11;
  uint in_r1;
  undefined *puVar12;
  undefined2 *puVar13;
  undefined4 *puVar14;
  uint uVar15;
  void *pvVar16;
  undefined uVar17;
  undefined2 uVar18;
  int iVar19;
  undefined4 uVar20;
  int iVar21;
  undefined uVar22;
  undefined *puVar23;
  undefined4 uVar24;
  int iVar25;
  undefined *puVar26;
  undefined4 uVar27;
  bool bVar28;
  bool bVar29;
  int *piVar30;
  
  iVar21 = DAT_800019bc;
  puVar26 = PTR_DAT_800019b8;
  iVar19 = DAT_800019b4;
  puVar23 = DAT_800019b0;
                    // WARNING: Load size is inaccurate
  DAT_800019b0[0x3a] = *buffer;
  *puVar23 = *(undefined *)((int)buffer + 2);
  puVar23[3] = *(undefined *)((int)buffer + 4);
  puVar23[4] = *(undefined *)((int)buffer + 6);
  puVar23[1] = *(undefined *)((int)buffer + 8);
  puVar23[2] = *(undefined *)((int)buffer + 10);
  puVar23[0xc] = *(undefined *)((int)buffer + 0xc);
  puVar23[0xf] = *(undefined *)((int)buffer + 0xe);
  puVar23[0x10] = *(undefined *)((int)buffer + 0x10);
  puVar23[0xd] = *(undefined *)((int)buffer + 0x12);
  puVar23[0xe] = *(undefined *)((int)buffer + 0x14);
  puVar23[10] = *(undefined *)((int)buffer + 0x16);
  puVar23[0x16] = *(undefined *)((int)buffer + 0x18);
  puVar23[0x21] = *(undefined *)((int)buffer + 0x1a);
  puVar23[0x22] = *(undefined *)((int)buffer + 0x1c);
  puVar23[0x23] = *(undefined *)((int)buffer + 0x1e);
  puVar23[0x38] = *(undefined *)((int)buffer + 0x20);
  puVar23[0x42] = *(undefined *)((int)buffer + 0x22);
  puVar23[0x18] = *(undefined *)((int)buffer + 0x24);
  puVar23[0x17] = *(undefined *)((int)buffer + 0x26);
  *(undefined2 *)(puVar23 + 0x1a) = *(undefined2 *)((int)buffer + 0x28);
  *(undefined2 *)(puVar23 + 0x1c) = *(undefined2 *)((int)buffer + 0x2a);
  *(undefined2 *)PTR_DAT_800019c0 = *(undefined2 *)((int)buffer + 0x2c);
  *(undefined2 *)PTR_DAT_800019c4 = *(undefined2 *)((int)buffer + 0x2e);
  *(undefined2 *)PTR_DAT_800019c8 = *(undefined2 *)((int)buffer + 0x30);
  *(undefined2 *)PTR_DAT_800019cc = *(undefined2 *)((int)buffer + 0x32);
  puVar23[0xb] = *(undefined *)((int)buffer + 0x34);
  puVar23[0x43] = *(undefined *)((int)buffer + 0x36);
  *(undefined2 *)(puVar23 + 0x24) = *(undefined2 *)((int)buffer + 0x50);
  *(undefined2 *)(puVar23 + 0x26) = *(undefined2 *)((int)buffer + 0x52);
  *(undefined2 *)(puVar23 + 6) = *(undefined2 *)((int)buffer + 0x54);
  *(undefined2 *)(puVar23 + 0x12) = *(undefined2 *)((int)buffer + 0x56);
  *(undefined *)(iVar19 + 2) = *(undefined *)((int)buffer + 0x78);
  *(undefined *)(iVar19 + 3) = *(undefined *)((int)buffer + 0x7a);
  *(undefined *)(iVar19 + 4) = *(undefined *)((int)buffer + 0x7c);
  *(undefined *)(iVar19 + 7) = *(undefined *)((int)buffer + 0x7e);
  cVar1 = *puVar26;
  if (cVar1 == '\0') {
    *(undefined *)(iVar21 + 0x100) = *(undefined *)((int)buffer + 0xa0);
    *(undefined *)(iVar21 + 0x112) = *(undefined *)((int)buffer + 0xa2);
    *(undefined *)(iVar21 + 0x122) = *(undefined *)((int)buffer + 0xa4);
    *(undefined *)(iVar21 + 0x132) = *(undefined *)((int)buffer + 0xa6);
    *(undefined *)(iVar21 + 0x142) = *(undefined *)((int)buffer + 0xa8);
    *(undefined *)(iVar21 + 0x152) = *(undefined *)((int)buffer + 0xaa);
    *(undefined *)(iVar21 + 0x162) = *(undefined *)((int)buffer + 0xac);
    *(undefined *)(iVar21 + 0x172) = *(undefined *)((int)buffer + 0xae);
    *(undefined *)(iVar21 + 0x182) = *(undefined *)((int)buffer + 0xb0);
    *(undefined *)(iVar21 + 0x192) = *(undefined *)((int)buffer + 0xb2);
    *(undefined *)(iVar21 + 0x1a2) = *(undefined *)((int)buffer + 0xb4);
    *(undefined *)(iVar21 + 0x1b2) = *(undefined *)((int)buffer + 0xb6);
    *(undefined *)(iVar21 + 0x1c2) = *(undefined *)((int)buffer + 0xb8);
    *(undefined *)(iVar21 + 0x1d2) = *(undefined *)((int)buffer + 0xba);
    *(undefined *)(iVar21 + 0x1e2) = *(undefined *)((int)buffer + 0xbc);
    *(undefined *)(iVar21 + 0x1f2) = *(undefined *)((int)buffer + 0xbe);
    *(undefined *)(iVar21 + 0x202) = *(undefined *)((int)buffer + 0xc0);
    *(undefined *)(iVar21 + 0x212) = *(undefined *)((int)buffer + 0xc2);
    *(undefined *)(iVar21 + 0x232) = *(undefined *)((int)buffer + 0xc4);
    *(undefined *)(iVar21 + 0x242) = *(undefined *)((int)buffer + 0xc6);
    *(undefined *)(iVar21 + 0x252) = *(undefined *)((int)buffer + 200);
    *(undefined *)(iVar21 + 0x262) = *(undefined *)((int)buffer + 0xca);
    *(undefined *)(iVar21 + 0x272) = *(undefined *)((int)buffer + 0xcc);
    *(undefined *)(iVar21 + 0x282) = *(undefined *)((int)buffer + 0xce);
  }
  uVar2 = *(ushort *)((int)buffer + 0xd0);
  *(uint *)(iVar21 + 0x104) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x104) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xd2));
  uVar2 = *(ushort *)((int)buffer + 0xd4);
  *(uint *)(iVar21 + 0x114) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x114) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xd6));
  uVar2 = *(ushort *)((int)buffer + 0xd8);
  *(uint *)(iVar21 + 0x124) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x124) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xda));
  *(uint *)(iVar21 + 0x134) = (uint)*(ushort *)((int)buffer + 0xdc) << 0x10;
  *(uint *)(iVar21 + 0x134) = *(uint *)(iVar21 + 0x134) | (uint)*(ushort *)((int)buffer + 0xde);
  uVar2 = *(ushort *)((int)buffer + 0xe0);
  *(uint *)(iVar21 + 0x144) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x144) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xe2));
  uVar2 = *(ushort *)((int)buffer + 0xe4);
  *(uint *)(iVar21 + 0x154) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x154) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xe6));
  uVar2 = *(ushort *)((int)buffer + 0xe8);
  *(uint *)(iVar21 + 0x164) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x164) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xea));
  uVar2 = *(ushort *)((int)buffer + 0xec);
  *(uint *)(iVar21 + 0x174) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x174) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xee));
  uVar2 = *(ushort *)((int)buffer + 0xf0);
  *(uint *)(iVar21 + 0x184) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x184) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xf2));
  uVar2 = *(ushort *)((int)buffer + 0xf4);
  *(uint *)(iVar21 + 0x194) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x194) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xf6));
  uVar2 = *(ushort *)((int)buffer + 0xf8);
  *(uint *)(iVar21 + 0x1a4) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x1a4) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xfa));
  uVar2 = *(ushort *)((int)buffer + 0xfc);
  *(uint *)(iVar21 + 0x1b4) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x1b4) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0xfe));
  uVar2 = *(ushort *)((int)buffer + 0x100);
  *(uint *)(iVar21 + 0x1c4) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x1c4) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x102));
  uVar2 = *(ushort *)((int)buffer + 0x104);
  *(uint *)(iVar21 + 0x1d4) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x1d4) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x106));
  uVar2 = *(ushort *)((int)buffer + 0x108);
  *(uint *)(iVar21 + 0x1e4) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x1e4) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x10a));
  uVar2 = *(ushort *)((int)buffer + 0x10c);
  *(uint *)(iVar21 + 500) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 500) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x10e));
  uVar2 = *(ushort *)((int)buffer + 0x110);
  *(uint *)(iVar21 + 0x204) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x204) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x112));
  uVar2 = *(ushort *)((int)buffer + 0x114);
  *(uint *)(iVar21 + 0x214) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x214) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x116));
  uVar2 = *(ushort *)((int)buffer + 0x118);
  *(uint *)(iVar21 + 0x234) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x234) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x11a));
  uVar2 = *(ushort *)((int)buffer + 0x11c);
  *(uint *)(iVar21 + 0x244) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x244) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x11e));
  uVar2 = *(ushort *)((int)buffer + 0x120);
  *(uint *)(iVar21 + 0x254) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x254) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x122));
  uVar2 = *(ushort *)((int)buffer + 0x124);
  *(uint *)(iVar21 + 0x264) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x264) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x126));
  uVar2 = *(ushort *)((int)buffer + 0x128);
  *(uint *)(iVar21 + 0x274) = (uint)uVar2 << 0x10;
  *(uint *)(iVar21 + 0x274) = CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x12a));
  uVar2 = *(ushort *)((int)buffer + 300);
  *(uint *)(iVar21 + 0x284) = (uint)uVar2 << 0x10;
  puVar26 = (undefined *)CONCAT22(uVar2,*(undefined2 *)((int)buffer + 0x12e));
  *(undefined **)(iVar21 + 0x284) = puVar26;
  if (cVar1 == '\0') {
    puVar12 = (undefined *)((int)buffer + 0x12e);
    puVar26 = &PrefetchAbort;
    puVar7 = (undefined *)(iVar21 + -1);
    do {
      puVar7[1] = puVar12[2];
      puVar12 = puVar12 + 4;
      puVar26 = (undefined *)((uint)(puVar26 + -1) & 0xffff);
      puVar7 = puVar7 + 2;
      *puVar7 = *puVar12;
    } while (puVar26 != NULL);
    in_r1 = 0x18;
  }
  puVar23[0x39] = *(undefined *)((int)buffer + 400);
  puVar23[0x38] = *(undefined *)((int)buffer + 0x192);
  *(undefined2 *)PTR_DAT_800019d0 = *(undefined2 *)((int)buffer + 0x194);
  *(undefined2 *)PTR_DAT_800019d4 = *(undefined2 *)((int)buffer + 0x196);
  translate_parameter(0x15,in_r1);
  iVar21 = DAT_800019dc;
  iVar19 = DAT_800019d8;
  puVar14 = (undefined4 *)(DAT_800019dc >> 1);
  if ((DAT_800019d8 - (int)buffer < 0x1f5) || (1999 < DAT_800019d8 - (int)buffer)) {
    FUN_80000730(DAT_800019d8,(int)buffer + 1000,DAT_800019dc);
  }
  else {
    puVar8 = NULL;
    do {
      pvVar16 = (void *)((int)buffer + (int)puVar8 * 2);
      puVar13 = (undefined2 *)(iVar19 + (int)puVar8 * 2);
      puVar26 = (undefined *)((int)puVar8 + 2);
      *puVar13 = *(undefined2 *)((int)pvVar16 + 1000);
      puVar8 = (undefined4 *)((uint)puVar26 & 0xfffeffff);
      puVar13[1] = *(undefined2 *)((int)pvVar16 + 0x3ea);
    } while (puVar8 < puVar14);
  }
  puVar4 = DAT_800019e4;
  iVar19 = DAT_800019e0;
  puVar9 = (undefined4 *)(DAT_800019e0 - (int)buffer);
  bVar29 = SBORROW4((int)puVar9,2000);
  puVar8 = puVar9 + -500;
  bVar28 = puVar9 == (undefined4 *)0x7d0;
  if (2000 < (int)puVar9) {
    bVar29 = SBORROW4((int)DAT_800019e4,(int)puVar9);
    puVar8 = (undefined4 *)((int)DAT_800019e4 - (int)puVar9);
    bVar28 = DAT_800019e4 == puVar9;
  }
  if (!bVar28 && (int)puVar8 < 0 == bVar29) {
    puVar9 = NULL;
  }
  if (bVar28 || (int)puVar8 < 0 != bVar29) {
    FUN_80000730(DAT_800019e0,(int)buffer + 4000,iVar21);
  }
  else {
    do {
      pvVar16 = (void *)((int)buffer + (int)puVar9 * 2);
      puVar13 = (undefined2 *)(iVar19 + (int)puVar9 * 2);
      puVar26 = (undefined *)((int)puVar9 + 2);
      *puVar13 = *(undefined2 *)((int)pvVar16 + 4000);
      puVar9 = (undefined4 *)((uint)puVar26 & 0xfffeffff);
      puVar13[1] = *(undefined2 *)((int)pvVar16 + 0xfa2);
    } while (puVar9 < puVar14);
  }
  puVar3 = DAT_800019f0;
  puVar9 = DAT_800019ec;
  iVar19 = DAT_800019e8;
  puVar10 = (undefined4 *)(DAT_800019e8 - (int)buffer);
  bVar28 = SBORROW4((int)puVar10,(int)puVar4);
  puVar8 = (undefined4 *)((int)puVar10 - (int)puVar4);
  if ((int)puVar4 < (int)puVar10) {
    bVar28 = SBORROW4((int)DAT_800019ec,(int)puVar10);
    puVar8 = (undefined4 *)((int)DAT_800019ec - (int)puVar10);
    puVar4 = DAT_800019ec;
  }
  bVar29 = puVar10 != puVar4;
  if (bVar29 && (int)puVar8 < 0 == bVar28) {
    puVar10 = NULL;
  }
  if (bVar29 && (int)puVar8 < 0 == bVar28) {
    do {
      pvVar16 = (void *)((int)buffer + (int)puVar10 * 2);
      puVar13 = (undefined2 *)(iVar19 + (int)puVar10 * 2);
      puVar26 = (undefined *)((int)puVar10 + 2);
      *puVar13 = *(undefined2 *)((int)pvVar16 + 7000);
      puVar10 = (undefined4 *)((uint)puVar26 & 0xfffeffff);
      puVar13[1] = *(undefined2 *)((int)pvVar16 + 0x1b5a);
    } while (puVar10 < puVar3);
  }
  else {
    FUN_80000730(DAT_800019e8,(int)buffer + 7000);
  }
  puVar4 = DAT_800019f4;
  puVar10 = (undefined4 *)((int)DAT_800019f4 - (int)buffer);
  bVar28 = SBORROW4((int)puVar10,(int)puVar9);
  puVar8 = (undefined4 *)((int)puVar10 - (int)puVar9);
  if ((int)puVar9 < (int)puVar10) {
    bVar28 = SBORROW4((int)DAT_800019f8,(int)puVar10);
    puVar8 = (undefined4 *)((int)DAT_800019f8 - (int)puVar10);
    puVar9 = DAT_800019f8;
  }
  bVar29 = puVar10 != puVar9;
  if (bVar29 && (int)puVar8 < 0 == bVar28) {
    puVar10 = NULL;
  }
  if (bVar29 && (int)puVar8 < 0 == bVar28) {
    do {
      pvVar16 = (void *)((int)buffer + (int)puVar10 * 2);
      puVar14 = (undefined4 *)((int)puVar4 + (int)puVar10 * 2);
      *(undefined2 *)puVar14 = *(undefined2 *)((int)pvVar16 + 0x2134);
      puVar10 = (undefined4 *)((uint)((int)puVar10 + 2) & 0xfffeffff);
      *(undefined2 *)((int)puVar14 + 2) = *(undefined2 *)((int)pvVar16 + 0x2136);
    } while (puVar10 < puVar3);
    return;
  }
  puVar9 = (undefined4 *)((int)buffer + 0x2134);
  puVar8 = (undefined4 *)((int)DAT_800019f4 - (int)puVar9);
  bVar28 = puVar8 == NULL;
  if (puVar9 <= DAT_800019f4) {
    bVar28 = puVar14 == puVar8;
  }
  if ((puVar9 <= DAT_800019f4 && puVar8 <= puVar14) && !bVar28) {
    piVar5 = (int *)((int)DAT_800019f4 + (int)puVar14);
    piVar11 = (int *)((int)puVar9 + (int)puVar14);
    if ((undefined4 *)0x3 < puVar14) {
      bVar28 = ((uint)piVar5 & 3) == 0;
      do {
        if (!bVar28) {
          piVar11 = (int *)((int)piVar11 + -1);
          puVar14 = (undefined4 *)((int)puVar14 - 1);
          piVar5 = (int *)((int)piVar5 + -1);
          *(undefined *)piVar5 = *(undefined *)piVar11;
        }
        bVar28 = ((uint)piVar5 & 3) == 0;
      } while (!bVar28);
      puVar8 = (undefined4 *)((uint)piVar11 & 3);
      if (puVar8 == NULL) {
        while (puVar8 = puVar14 + -4, (undefined4 *)0xf < puVar14) {
          piVar30 = piVar11 + -1;
          iVar25 = piVar11[-2];
          iVar21 = piVar11[-3];
          piVar11 = piVar11 + -4;
          iVar19 = *piVar11;
          piVar5[-1] = *piVar30;
          piVar5[-2] = iVar25;
          piVar5[-3] = iVar21;
          piVar5 = piVar5 + -4;
          *piVar5 = iVar19;
          puVar14 = puVar8;
        }
        iVar19 = (int)puVar14 << 0x1d;
        bVar28 = iVar19 < 0;
        if ((bool)((byte)((uint)puVar8 >> 3) & 1)) {
          piVar30 = piVar11 + -1;
          piVar11 = piVar11 + -2;
          iVar19 = *piVar11;
          piVar5[-1] = *piVar30;
          piVar5 = piVar5 + -2;
          *piVar5 = iVar19;
        }
        if (bVar28) {
          piVar11 = piVar11 + -1;
          iVar19 = *piVar11;
          piVar5 = piVar5 + -1;
          *piVar5 = iVar19;
        }
        uVar18 = (undefined2)iVar19;
        if (((uint)puVar8 & 3) != 0) {
          bVar29 = (bool)((byte)((uint)puVar8 >> 1) & 1);
          uVar15 = (int)puVar14 << 0x1f;
          bVar28 = (int)uVar15 < 0;
          if (bVar29) {
            piVar11 = (int *)((int)piVar11 + -2);
            uVar18 = *(undefined2 *)piVar11;
          }
          if (bVar28) {
            uVar15 = (uint)*(byte *)((int)piVar11 + -1);
          }
          if (bVar29) {
            piVar5 = (int *)((int)piVar5 + -2);
            *(undefined2 *)piVar5 = uVar18;
          }
          if (bVar28) {
            *(char *)((int)piVar5 + -1) = (char)uVar15;
          }
          return;
        }
        return;
      }
      bVar28 = (undefined4 *)0x3 < puVar14;
      puVar14 = puVar14 + -1;
      if (bVar28) {
        piVar11 = (int *)((int)piVar11 - (int)puVar8);
        puVar26 = (undefined *)*piVar11;
        if (puVar8 < (undefined4 *)0x2) {
          do {
            piVar30 = piVar11;
            uVar15 = (int)puVar26 << 0x18;
            piVar11 = piVar30 + -1;
            puVar26 = (undefined *)*piVar11;
            bVar28 = (undefined4 *)0x3 < puVar14;
            puVar14 = puVar14 + -1;
            puVar8 = (undefined4 *)(uVar15 | (uint)puVar26 >> 8);
            piVar5 = piVar5 + -1;
            *piVar5 = (int)puVar8;
          } while (bVar28);
          piVar11 = (int *)((int)piVar30 + -3);
        }
        else {
          if (puVar8 < (undefined4 *)0x3) {
            do {
              piVar30 = piVar11;
              uVar15 = (int)puVar26 << 0x10;
              piVar11 = piVar30 + -1;
              puVar26 = (undefined *)*piVar11;
              bVar28 = (undefined4 *)0x3 < puVar14;
              puVar14 = puVar14 + -1;
              puVar8 = (undefined4 *)(uVar15 | (uint)puVar26 >> 0x10);
              piVar5 = piVar5 + -1;
              *piVar5 = (int)puVar8;
            } while (bVar28);
            piVar11 = (int *)((int)piVar30 + -2);
          }
          else {
            do {
              piVar30 = piVar11;
              uVar15 = (int)puVar26 << 8;
              piVar11 = piVar30 + -1;
              puVar26 = (undefined *)*piVar11;
              bVar28 = (undefined4 *)0x3 < puVar14;
              puVar14 = puVar14 + -1;
              puVar8 = (undefined4 *)(uVar15 | (uint)puVar26 >> 0x18);
              piVar5 = piVar5 + -1;
              *piVar5 = (int)puVar8;
            } while (bVar28);
            piVar11 = (int *)((int)piVar30 + -1);
          }
        }
      }
    }
    uVar22 = SUB41(puVar26,0);
    uVar17 = SUB41(puVar8,0);
    bVar29 = (bool)((byte)((uint)puVar14 >> 1) & 1);
    uVar15 = (int)puVar14 << 0x1f;
    bVar28 = (int)uVar15 < 0;
    if (bVar29) {
      uVar17 = *(undefined *)((int)piVar11 + -1);
      piVar11 = (int *)((int)piVar11 + -2);
      uVar22 = *(undefined *)piVar11;
    }
    if (bVar28) {
      uVar15 = (uint)*(byte *)((int)piVar11 + -1);
    }
    if (bVar29) {
      *(undefined *)((int)piVar5 + -1) = uVar17;
      piVar5 = (int *)((int)piVar5 + -2);
      *(undefined *)piVar5 = uVar22;
    }
    if (bVar28) {
      *(char *)((int)piVar5 + -1) = (char)uVar15;
    }
    return;
  }
  if ((undefined4 *)0x3 < puVar14) {
    puVar23 = (undefined *)((uint)DAT_800019f4 & 3);
    puVar26 = puVar23;
    if (puVar23 != NULL) {
      uVar17 = *(undefined *)puVar9;
      puVar8 = (undefined4 *)((int)buffer + 0x2135);
      if (puVar23 < (undefined *)0x3) {
        puVar8 = (undefined4 *)((int)buffer + 0x2136);
        puVar26 = (undefined *)(uint)*(byte *)(undefined4 *)((int)buffer + 0x2135);
      }
      puVar3 = (undefined4 *)((int)DAT_800019f4 + 1);
      *(undefined *)DAT_800019f4 = uVar17;
      puVar9 = puVar8;
      if (puVar23 < (undefined *)0x2) {
        puVar9 = (undefined4 *)((int)puVar8 + 1);
        uVar17 = *(undefined *)puVar8;
      }
      puVar8 = puVar3;
      if (puVar23 < (undefined *)0x3) {
        puVar8 = (undefined4 *)((int)puVar4 + 2);
        *(char *)puVar3 = (char)puVar26;
      }
      puVar14 = (undefined4 *)((int)puVar14 + (int)puVar23 + -4);
      puVar4 = puVar8;
      if (puVar23 < (undefined *)0x2) {
        puVar4 = (undefined4 *)((int)puVar8 + 1);
        *(undefined *)puVar8 = uVar17;
      }
    }
    puVar8 = (undefined4 *)((uint)puVar9 & 3);
    if (puVar8 == NULL) {
      while (puVar3 = puVar14 + -8, (undefined4 *)0x1f < puVar14) {
        uVar20 = puVar9[1];
        uVar24 = puVar9[2];
        uVar27 = puVar9[3];
        *puVar4 = *puVar9;
        puVar4[1] = uVar20;
        puVar4[2] = uVar24;
        puVar4[3] = uVar27;
        puVar8 = (undefined4 *)puVar9[4];
        uVar20 = puVar9[5];
        uVar24 = puVar9[6];
        uVar27 = puVar9[7];
        puVar9 = puVar9 + 8;
        puVar4[4] = puVar8;
        puVar4[5] = uVar20;
        puVar4[6] = uVar24;
        puVar4[7] = uVar27;
        puVar4 = puVar4 + 8;
        puVar14 = puVar3;
      }
      if ((bool)((byte)((uint)puVar3 >> 4) & 1)) {
        puVar8 = (undefined4 *)*puVar9;
        uVar20 = puVar9[1];
        uVar24 = puVar9[2];
        uVar27 = puVar9[3];
        puVar9 = puVar9 + 4;
        *puVar4 = puVar8;
        puVar4[1] = uVar20;
        puVar4[2] = uVar24;
        puVar4[3] = uVar27;
        puVar4 = puVar4 + 4;
      }
      if ((int)puVar14 << 0x1c < 0) {
        puVar8 = (undefined4 *)*puVar9;
        uVar20 = puVar9[1];
        puVar9 = puVar9 + 2;
        *puVar4 = puVar8;
        puVar4[1] = uVar20;
        puVar4 = puVar4 + 2;
      }
      puVar6 = puVar4;
      puVar10 = puVar9;
      if ((bool)((byte)((uint)puVar3 >> 2) & 1)) {
        puVar10 = puVar9 + 1;
        puVar8 = (undefined4 *)*puVar9;
        puVar6 = puVar4 + 1;
        *puVar4 = puVar8;
      }
      uVar18 = SUB42(puVar8,0);
      if (((uint)puVar3 & 3) != 0) {
        bVar29 = (bool)((byte)((uint)puVar3 >> 1) & 1);
        uVar15 = (int)puVar14 << 0x1f;
        bVar28 = (int)uVar15 < 0;
        puVar14 = puVar10;
        if (bVar29) {
          puVar14 = (undefined4 *)((int)puVar10 + 2);
          uVar18 = *(undefined2 *)puVar10;
        }
        if (bVar28) {
          uVar15 = (uint)*(byte *)puVar14;
        }
        puVar14 = puVar6;
        if (bVar29) {
          puVar14 = (undefined4 *)((int)puVar6 + 2);
          *(undefined2 *)puVar6 = uVar18;
        }
        if (bVar28) {
          *(char *)puVar14 = (char)uVar15;
        }
        return;
      }
      return;
    }
    bVar28 = (undefined4 *)0x3 < puVar14;
    puVar14 = puVar14 + -1;
    if (bVar28) {
      puVar9 = (undefined4 *)((int)puVar9 - (int)puVar8);
      puVar26 = (undefined *)*puVar9;
      puVar3 = puVar4;
      if (puVar8 == (undefined4 *)0x2) {
        do {
          puVar10 = puVar9;
          uVar15 = (uint)puVar26 >> 0x10;
          puVar9 = puVar10 + 1;
          puVar26 = (undefined *)*puVar9;
          bVar28 = (undefined4 *)0x3 < puVar14;
          puVar14 = puVar14 + -1;
          puVar8 = (undefined4 *)(uVar15 | (int)puVar26 << 0x10);
          puVar4 = puVar3 + 1;
          *puVar3 = puVar8;
          puVar3 = puVar4;
        } while (bVar28);
        puVar9 = (undefined4 *)((int)puVar10 + 6);
      }
      else {
        if (puVar8 < (undefined4 *)0x3) {
          do {
            puVar10 = puVar9;
            uVar15 = (uint)puVar26 >> 8;
            puVar9 = puVar10 + 1;
            puVar26 = (undefined *)*puVar9;
            bVar28 = (undefined4 *)0x3 < puVar14;
            puVar14 = puVar14 + -1;
            puVar8 = (undefined4 *)(uVar15 | (int)puVar26 << 0x18);
            puVar4 = puVar3 + 1;
            *puVar3 = puVar8;
            puVar3 = puVar4;
          } while (bVar28);
          puVar9 = (undefined4 *)((int)puVar10 + 5);
        }
        else {
          do {
            puVar10 = puVar9;
            uVar15 = (uint)puVar26 >> 0x18;
            puVar9 = puVar10 + 1;
            puVar26 = (undefined *)*puVar9;
            bVar28 = (undefined4 *)0x3 < puVar14;
            puVar14 = puVar14 + -1;
            puVar8 = (undefined4 *)(uVar15 | (int)puVar26 << 8);
            puVar4 = puVar3 + 1;
            *puVar3 = puVar8;
            puVar3 = puVar4;
          } while (bVar28);
          puVar9 = (undefined4 *)((int)puVar10 + 7);
        }
      }
    }
  }
  uVar22 = SUB41(puVar26,0);
  uVar17 = SUB41(puVar8,0);
  bVar29 = (bool)((byte)((uint)puVar14 >> 1) & 1);
  uVar15 = (int)puVar14 << 0x1f;
  bVar28 = (int)uVar15 < 0;
  if (bVar29) {
    puVar23 = (undefined *)((int)puVar9 + 1);
    uVar17 = *(undefined *)puVar9;
    puVar9 = (undefined4 *)((int)puVar9 + 2);
    uVar22 = *puVar23;
  }
  if (bVar28) {
    uVar15 = (uint)*(byte *)puVar9;
  }
  if (bVar29) {
    puVar23 = (undefined *)((int)puVar4 + 1);
    *(undefined *)puVar4 = uVar17;
    puVar4 = (undefined4 *)((int)puVar4 + 2);
    *puVar23 = uVar22;
  }
  if (bVar28) {
    *(char *)puVar4 = (char)uVar15;
  }
  return;
}


