//This is a function that continues in FUN_8002b124 or jumps to LAB_80021A78

void FUN_800253e8(void)

{
  char cVar1;
  ushort uVar2;
  short sVar3;
  int *piVar4;
  int *piVar5;
  undefined *puVar6;
  char *pcVar7;
  undefined *puVar8;
  ushort *puVar9;
  undefined2 uVar10;
  ushort uVar11;
  undefined4 uVar12;
  int iVar13;
  uint uVar14;
  ushort *puVar15;
  ushort *puVar16;
  int iVar17;
  int iVar18;
  ushort uVar19;
  uint uVar20;
  int iVar21;
  undefined2 *puVar22;
  int iVar23;
  uint uVar24;
  uint uVar25;
  int iVar26;
  int unaff_r4;
  uint uVar27;
  uint uVar28;
  int iVar29;
  uint uVar30;
  int iVar31;
  code *UNRECOVERED_JUMPTABLE_00;
  bool bVar32;
  undefined8 uVar33;
  undefined8 uVar34;
  
  if (*(byte *)(DAT_80025460 + 10) < 9) {
    FUN_800169f8(0xd);
    FUN_800168fc(0);
    FUN_800168fc(0);
    FUN_800168fc(7);
    iVar13 = FUN_800168fc(2000);
    puVar8 = PTR_DAT_80025adc;
    puVar6 = PTR_DAT_80025ad8;
    iVar18 = DAT_80025ad4;
    switch(*(undefined *)(DAT_80025ad4 + 10)) {
    case 0:
      iVar13 = 2000;
      break;
    case 1:
      iVar13 = 1000;
      break;
    case 2:
      iVar13 = 400;
      break;
    case 3:
      iVar13 = 200;
      break;
    case 4:
      iVar13 = 0x50;
      break;
    case 5:
      iVar13 = 0x28;
      break;
    case 6:
      iVar13 = 0x14;
      break;
    case 7:
      iVar13 = 8;
      break;
    case 8:
      iVar13 = 4;
    }
    iVar21 = *(int *)(PTR_DAT_80025ad8 + 8);
    do {
      uVar14 = FUN_80023564();
      if ((uint)(iVar13 + iVar21) <= uVar14) {
        *(uint *)(puVar6 + 8) = uVar14;
        goto LAB_8002582c;
      }
    } while ((5 < *(byte *)(iVar18 + 10)) || (FUN_800177c4(), *puVar8 == '\0'));
    FUN_8000bc00(0x28);
LAB_8002582c:
    FUN_800169f8(0x28);
    FUN_800168fc(1);
    uVar27 = 0;
    FUN_800169f8(0x24);
    FUN_800167a0();
    iVar13 = DAT_80025ae0;
    FUN_80017738(DAT_80025ae0,9);
    FUN_80017738(iVar13,10);
    uVar14 = 0;
    do {
      FUN_80017738(iVar13,8);
      FUN_8001774c(iVar13,8);
      uVar14 = uVar14 + 1 & 0xfffeffff;
      uVar27 = (*(uint *)(iVar13 + 0x10) & 0xff) + uVar27 & 0xfffeffff;
    } while (uVar14 < 10);
    uVar11 = FUN_80000dc4(uVar27,10);
    puVar16 = DAT_80025ae4;
    *DAT_80025ae4 = uVar11 & 0xff;
    uVar27 = 0;
    FUN_800169f8(0x26);
    FUN_800167a0();
    FUN_80017738(iVar13,9);
    FUN_80017738(iVar13,10);
    uVar14 = 0;
    do {
      FUN_80017738(iVar13,8);
      FUN_8001774c(iVar13,8);
      uVar14 = uVar14 + 1 & 0xfffeffff;
      uVar27 = (*(uint *)(iVar13 + 0x10) & 0xff) + uVar27 & 0xfffeffff;
    } while (uVar14 < 10);
    uVar34 = FUN_80000dc4(uVar27,10);
    uVar27 = (uint)((ulonglong)uVar34 >> 0x20);
    uVar25 = (uint)uVar34 & 0xff;
    *DAT_80025ae8 = (short)uVar25;
    puVar9 = DAT_80025af4;
    uVar14 = DAT_80025af0;
    puVar15 = DAT_80025aec;
    switch(*(undefined *)(iVar18 + 3)) {
    case 0:
      uVar27 = (uint)*DAT_80025aec;
      break;
    case 1:
      uVar27 = (uint)DAT_80025aec[1];
      break;
    case 2:
      uVar27 = (uint)DAT_80025aec[2];
      break;
    case 3:
      uVar27 = (uint)DAT_80025aec[3];
      break;
    case 4:
      uVar27 = (uint)DAT_80025aec[4];
      break;
    case 5:
      uVar27 = (uint)DAT_80025aec[5];
      break;
    case 6:
      uVar27 = (uint)DAT_80025aec[6];
    }
    uVar27 = *puVar16 * uVar27 & 0xffff;
    uVar11 = (ushort)(((int)DAT_80025af0 >> 0xf) * uVar27 + 0xa3d7 >> 0x10);
    uVar19 = uVar11 >> 6;
    if (0x32 < (int)(uVar27 + (uint)((ulonglong)uVar27 * (ulonglong)DAT_80025af0 >> 0x25) * -100)) {
      uVar19 = (uVar11 >> 6) + 1;
    }
    *DAT_80025af4 = uVar19;
    uVar27 = DAT_80025afc;
    puVar16 = DAT_80025af8;
    uVar11 = *puVar9;
    *DAT_80025af8 = uVar11;
    if (uVar27 < uVar11) {
      *puVar16 = (ushort)uVar27;
    }
    puVar16 = DAT_80025b00;
    switch(*(undefined *)(iVar18 + 0xf)) {
    case 0:
      puVar15 = (ushort *)(uint)*puVar15;
      break;
    case 1:
      puVar15 = (ushort *)(uint)puVar15[1];
      break;
    case 2:
      puVar15 = (ushort *)(uint)puVar15[2];
      break;
    case 3:
      puVar15 = (ushort *)(uint)puVar15[3];
      break;
    case 4:
      puVar15 = (ushort *)(uint)puVar15[4];
      break;
    case 5:
      puVar15 = (ushort *)(uint)puVar15[5];
      break;
    case 6:
      puVar15 = (ushort *)(uint)puVar15[6];
    }
    uVar25 = uVar25 * (int)puVar15 & 0xff00ffff;
    uVar11 = (ushort)(DAT_80025b04 * uVar25 + 0xa3d7 >> 0x10);
    uVar19 = uVar11 >> 6;
    if (0x32 < (int)(uVar25 + (uint)((ulonglong)uVar25 * (ulonglong)uVar14 >> 0x25) * -100)) {
      uVar19 = (uVar11 >> 6) + 1;
    }
    *DAT_80025b00 = uVar19;
    puVar15 = DAT_80025b08;
    uVar11 = *puVar16;
    *DAT_80025b08 = uVar11;
    if (uVar27 < uVar11) {
      *puVar15 = (ushort)uVar27;
    }
  }
  else {
    if ((*(char *)(DAT_80025460 + 0x3a) != '\x01') && (*PTR_DAT_80025464 != '\x02')) {
      FUN_80025468();
      iVar18 = DAT_80021bd4;
      uVar14 = DAT_80021bd0;
      pcVar7 = DAT_80021bcc;
      if (*DAT_80021bcc != '\0') {
        if ((byte)DAT_80021bcc[10] < 0xb) {
          iVar13 = 100;
          iVar21 = 600;
        }
        else {
          iVar13 = 200;
          iVar21 = 0x4b0;
        }
        uVar28 = 0;
        iVar29 = 0;
        puVar16 = (ushort *)(DAT_80021bd8 + iVar13 * 2);
        uVar27 = iVar21 - iVar13 & 0xffff;
        uVar25 = DAT_80021bd0;
        do {
          uVar24 = (uint)*puVar16;
          puVar16 = puVar16 + 1;
          if (uVar28 < uVar24) {
            uVar28 = uVar24;
          }
          iVar29 = iVar29 + uVar24;
          if (uVar24 < uVar25) {
            uVar25 = uVar24;
          }
          uVar27 = uVar27 - 1 & 0xffff;
        } while (uVar27 != 0);
        uVar10 = FUN_80000dc4(iVar29);
        *(short *)(iVar18 + 0xe4) = (short)uVar28;
        *(short *)(iVar18 + 0xe6) = (short)uVar25;
        *(short *)(iVar18 + 0xea) = (short)(uVar28 + uVar25 >> 1);
        *(short *)(iVar18 + 0xe8) = (short)uVar28 - (short)uVar25;
        *(undefined2 *)(iVar18 + 0xec) = uVar10;
        FUN_80004a50();
        FUN_8000519c();
      }
      if (pcVar7[0xc] == '\0') {
        return;
      }
      uVar27 = 0;
      if ((byte)pcVar7[10] < 0xb) {
        iVar13 = 100;
        iVar21 = 600;
      }
      else {
        iVar13 = 200;
        iVar21 = 0x4b0;
      }
      puVar16 = (ushort *)(DAT_80021bdc + iVar13 * 2);
      iVar29 = 0;
      uVar25 = iVar21 - iVar13 & 0xffff;
      do {
        uVar28 = (uint)*puVar16;
        if (uVar27 < uVar28) {
          uVar27 = uVar28;
        }
        if (uVar28 < uVar14) {
          uVar14 = uVar28;
        }
        uVar25 = uVar25 - 1 & 0xffff;
        iVar29 = iVar29 + uVar28;
        puVar16 = puVar16 + 1;
      } while (uVar25 != 0);
      uVar10 = FUN_80000dc4(iVar29);
      *(short *)(iVar18 + 0xee) = (short)uVar27;
      *(short *)(iVar18 + 0xf0) = (short)uVar14;
      *(short *)(iVar18 + 0xf4) = (short)(uVar27 + uVar14 >> 1);
      *(short *)(iVar18 + 0xf2) = (short)uVar27 - (short)uVar14;
      *(undefined2 *)(iVar18 + 0xf6) = uVar10;
      FUN_800077c4();
      iVar21 = DAT_8000855c;
      iVar13 = DAT_80008558;
      iVar18 = DAT_80008554;
      uVar27 = (uint)*(ushort *)(DAT_8000855c + 0xfc);
      uVar25 = (uint)*(ushort *)(DAT_8000855c + 0xfe);
      uVar11 = *(ushort *)(DAT_8000855c + 0xee);
      uVar14 = 0;
      if (*(byte *)(DAT_80008554 + 10) < 0xb) {
        uVar28 = 2;
      }
      else {
        uVar28 = 10;
      }
      uVar20 = 0;
      uVar19 = *(ushort *)(DAT_8000855c + 0xf0);
      uVar2 = *(ushort *)(DAT_8000855c + 0xf2);
      uVar24 = uVar27;
      if (uVar27 < uVar25) {
        do {
          uVar30 = (uint)*(ushort *)(DAT_80008558 + uVar24 * 2);
          uVar24 = uVar24 + 1 & 0xfffeffff;
          if (uVar30 < *(ushort *)(DAT_80008554 + 0x12)) {
            uVar20 = uVar20 + (*(ushort *)(DAT_80008554 + 0x12) - uVar30);
          }
          else {
            uVar14 = uVar14 + (uVar30 - *(ushort *)(DAT_80008554 + 0x12));
          }
        } while (uVar24 < uVar25);
        if (uVar20 <= uVar14) goto LAB_80007fac;
        iVar29 = uVar20 - uVar14;
        *(undefined *)(DAT_8000855c + 0x1e3) = 1;
      }
      else {
LAB_80007fac:
        iVar29 = uVar14 - uVar20;
        *(undefined *)(DAT_8000855c + 0x1e3) = 0;
      }
      uVar14 = FUN_80000dc4(iVar29,uVar25 - uVar27);
      if (uVar2 < 0x28) {
        *(undefined2 *)(iVar21 + 0xfc) = 0x32;
        *(undefined2 *)(iVar21 + 0xfe) = 0x3b6;
      }
      iVar29 = 0;
      uVar27 = (uint)*(ushort *)(iVar21 + 0xfc);
      while (uVar27 < *(ushort *)(iVar21 + 0xfe)) {
        uVar25 = (uint)*(ushort *)(iVar13 + uVar27 * 2);
        uVar27 = uVar27 + 1 & 0xfffeffff;
        if (uVar25 < *(ushort *)(iVar18 + 0x12)) {
          iVar17 = *(ushort *)(iVar18 + 0x12) - uVar25;
        }
        else {
          iVar17 = uVar25 - *(ushort *)(iVar18 + 0x12);
        }
        iVar29 = iVar29 + iVar17 * iVar17;
      }
      iVar13 = FUN_80000dc4(iVar29,(uint)*(ushort *)(iVar21 + 0xfe) -
                                   (uint)*(ushort *)(iVar21 + 0xfc));
      piVar5 = DAT_80008564;
      puVar6 = PTR_DAT_80008560;
      uVar27 = (uint)(byte)PTR_DAT_80008560[3];
      DAT_80008564[uVar27] = (uint)uVar11;
      piVar5[uVar27 + 0x1e] = (uint)uVar19;
      piVar5[uVar27 + 0x3c] = iVar13;
      uVar25 = uVar27 + 1 & 0xff;
      piVar5[uVar27 + 0x5a] = uVar14 & 0xffff;
      puVar6[3] = (char)uVar25;
      if (uVar25 < uVar28) goto LAB_800084c8;
      iVar17 = uVar28 - 1;
      iVar29 = 0;
      puVar6[3] = 0;
      iVar13 = iVar17 >> 1;
      if (0 < iVar17) {
        iVar29 = *piVar5;
        iVar31 = piVar5[1];
        iVar26 = 0;
        piVar4 = piVar5;
        iVar23 = iVar13;
        while (iVar23 != 0) {
          iVar29 = iVar29 + iVar31;
          iVar31 = piVar4[3];
          iVar23 = iVar23 + -1;
          iVar26 = iVar26 + piVar4[2];
          piVar4 = piVar4 + 2;
        }
        iVar29 = iVar29 + iVar26;
      }
      if (-1 < iVar17) {
        iVar29 = iVar29 + piVar5[iVar17];
      }
      uVar14 = FUN_80000dc4(iVar29,uVar28);
      uVar14 = uVar14 & 0xffff;
      iVar29 = 0;
      if (0 < iVar17) {
        iVar29 = *(int *)(DAT_80008568 + 4);
        iVar31 = *(int *)(DAT_80008568 + 8);
        iVar26 = 0;
        piVar5 = (int *)(DAT_80008568 + 4);
        iVar23 = iVar13;
        while (iVar23 != 0) {
          iVar29 = iVar29 + iVar31;
          iVar31 = piVar5[3];
          iVar23 = iVar23 + -1;
          iVar26 = iVar26 + piVar5[2];
          piVar5 = piVar5 + 2;
        }
        iVar29 = iVar29 + iVar26;
      }
      if (-1 < (int)(uVar28 - 1)) {
        iVar29 = iVar29 + *(int *)(DAT_8000856c + (uVar28 - 1) * 4);
      }
      uVar27 = FUN_80000dc4(iVar29,uVar28);
      cVar1 = *(char *)(iVar18 + 0x23);
      uVar27 = uVar27 & 0xffff;
      bVar32 = cVar1 == '\x01';
      if (bVar32) {
        cVar1 = *(char *)(iVar18 + 0x21);
      }
      if ((bVar32 && cVar1 == '\0') && (*(char *)(DAT_80008570 + 4) != '\0')) {
        *(short *)(iVar18 + 0x26) = (short)(uVar14 + uVar27 >> 1);
        FUN_800267c4();
      }
      iVar29 = 0;
      if (0 < iVar17) {
        iVar29 = *(int *)(DAT_80008574 + 4);
        iVar31 = *(int *)(DAT_80008574 + 8);
        iVar26 = 0;
        piVar5 = (int *)(DAT_80008574 + 4);
        iVar23 = iVar13;
        while (iVar23 != 0) {
          iVar29 = iVar29 + iVar31;
          iVar31 = piVar5[3];
          iVar23 = iVar23 + -1;
          iVar26 = iVar26 + piVar5[2];
          piVar5 = piVar5 + 2;
        }
        iVar29 = iVar29 + iVar26;
      }
      if (-1 < (int)(uVar28 - 1)) {
        iVar29 = iVar29 + *(int *)(DAT_80008578 + (uVar28 - 1) * 4);
      }
      uVar25 = FUN_80000dc4(iVar29,uVar28);
      iVar29 = 0;
      if (0 < iVar17) {
        iVar29 = *(int *)(DAT_8000857c + 4);
        iVar17 = *(int *)(DAT_8000857c + 8);
        iVar31 = 0;
        piVar5 = (int *)(DAT_8000857c + 4);
        while (iVar13 != 0) {
          iVar29 = iVar29 + iVar17;
          iVar17 = piVar5[3];
          iVar13 = iVar13 + -1;
          iVar31 = iVar31 + piVar5[2];
          piVar5 = piVar5 + 2;
        }
        iVar29 = iVar29 + iVar31;
      }
      if (-1 < (int)(uVar28 - 1)) {
        iVar29 = iVar29 + *(int *)(DAT_80008580 + (uVar28 - 1) * 4);
      }
      uVar12 = FUN_80000dc4(iVar29,uVar28);
      iVar13 = DAT_8000858c;
      switch(*(undefined *)(iVar18 + 0xf)) {
      case 0:
        unaff_r4 = DAT_80008584;
        break;
      case 1:
        unaff_r4 = DAT_80008588;
        break;
      case 2:
        unaff_r4 = 1000;
        break;
      case 3:
        unaff_r4 = 500;
        break;
      case 4:
        unaff_r4 = 200;
        break;
      case 5:
        unaff_r4 = 100;
        break;
      case 6:
        unaff_r4 = 0x32;
      }
      if (uVar14 < *(ushort *)(iVar18 + 0x12)) {
        *(undefined *)(iVar21 + 0x1c3) = 1;
        iVar29 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (*(ushort *)(iVar18 + 0x12) - uVar14))) >> 0x20);
        *(int *)(iVar21 + 0x1c4) = (iVar29 >> 4) - (iVar29 >> 0x1f);
      }
      else {
        *(undefined *)(iVar21 + 0x1c3) = 0;
        iVar29 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (uVar14 - *(ushort *)(iVar18 + 0x12)))) >> 0x20);
        *(int *)(iVar21 + 0x1c4) = (iVar29 >> 4) - (iVar29 >> 0x1f);
      }
      if (uVar27 < *(ushort *)(iVar18 + 0x12)) {
        *(undefined *)(iVar21 + 0x1d3) = 1;
        iVar29 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (*(ushort *)(iVar18 + 0x12) - uVar27))) >> 0x20);
        *(int *)(iVar21 + 0x1d4) = (iVar29 >> 4) - (iVar29 >> 0x1f);
      }
      else {
        *(undefined *)(iVar21 + 0x1d3) = 0;
        iVar29 = (int)((ulonglong)
                       ((longlong)iVar13 *
                       (longlong)(int)(unaff_r4 * (uVar27 - *(ushort *)(iVar18 + 0x12)))) >> 0x20);
        *(int *)(iVar21 + 0x1d4) = (iVar29 >> 4) - (iVar29 >> 0x1f);
      }
      uVar34 = FUN_800397d0(unaff_r4);
      FUN_800397d0(uVar12);
      uVar33 = FUN_80036618();
      uVar34 = FUN_80039890((int)uVar33,(int)((ulonglong)uVar33 >> 0x20),(int)uVar34,
                            (int)((ulonglong)uVar34 >> 0x20));
      FUN_800393ec((int)uVar34,(int)((ulonglong)uVar34 >> 0x20),0,DAT_80008590);
      iVar29 = FUN_8003972c();
      *(int *)(iVar21 + 500) = iVar29;
      iVar13 = (int)((ulonglong)((longlong)iVar13 * (longlong)(int)(unaff_r4 * (uVar25 & 0xffff)))
                    >> 0x20);
      iVar13 = (iVar13 >> 4) - (iVar13 >> 0x1f);
      *(int *)(iVar21 + 0x1e4) = iVar13;
      cVar1 = *(char *)(iVar21 + 0x1c3);
      if (cVar1 == *(char *)(iVar21 + 0x1d3)) {
        if (cVar1 != '\0') {
          iVar17 = *(int *)(iVar21 + 0x1d4);
          iVar31 = *(int *)(iVar21 + 0x1c4);
        }
        else {
          iVar17 = *(int *)(iVar21 + 0x1c4);
          iVar31 = *(int *)(iVar21 + 0x1d4);
        }
        iVar17 = iVar17 - iVar31;
        if (cVar1 == '\0') goto LAB_800083f8;
        *(int *)(iVar21 + 0x204) = iVar17;
      }
      else {
        iVar17 = *(int *)(iVar21 + 0x1c4) + *(int *)(iVar21 + 0x1d4);
LAB_800083f8:
        *(int *)(iVar21 + 0x204) = iVar17;
      }
      uVar14 = *(uint *)(iVar21 + 0x1d4);
      uVar27 = *(uint *)(iVar21 + 0x1c4);
      if (uVar27 < uVar14) {
        *(uint *)(iVar21 + 0x214) = uVar14;
      }
      else {
        *(uint *)(iVar21 + 0x214) = uVar27;
      }
      if (*(char *)(iVar18 + 0xe) == '\x01') {
        *(uint *)(iVar21 + 0x1d4) = uVar14 * 10;
        *(int *)(iVar21 + 0x1e4) = iVar13 * 10;
        *(uint *)(iVar21 + 0x1c4) = uVar27 * 10;
        *(int *)(iVar21 + 500) = iVar29 * 10;
        *(int *)(iVar21 + 0x204) = *(int *)(iVar21 + 0x204) * 10;
        iVar13 = *(int *)(iVar21 + 0x214) * 10;
      }
      else {
        if (*(char *)(iVar18 + 0xe) != '\x02') goto LAB_800084c8;
        *(uint *)(iVar21 + 0x1d4) = uVar14 * 100;
        *(uint *)(iVar21 + 0x1c4) = uVar27 * 100;
        *(int *)(iVar21 + 500) = iVar29 * 100;
        *(int *)(iVar21 + 0x1e4) = iVar13 * 100;
        *(int *)(iVar21 + 0x204) = *(int *)(iVar21 + 0x204) * 100;
        iVar13 = *(int *)(iVar21 + 0x214) * 100;
      }
      *(int *)(iVar21 + 0x214) = iVar13;
LAB_800084c8:
      if (*(char *)(iVar18 + 0xf) == '\x06') {
        uVar11 = 0xf;
      }
      else {
        uVar11 = 7;
      }
      if (*(ushort *)(iVar21 + 0xf2) < uVar11) {
        *(undefined4 *)(iVar21 + 0x204) = 0;
      }
      if (0x13 < *(ushort *)(iVar21 + 0xf2)) {
        return;
      }
      *(undefined4 *)(iVar21 + 0x204) = 0;
      if (*(ushort *)(iVar18 + 0x12) + 5 <= (uint)*(ushort *)(iVar21 + 0xf4)) {
        return;
      }
      if (*(ushort *)(iVar21 + 0xf4) + 5 <= (uint)*(ushort *)(iVar18 + 0x12)) {
        return;
      }
      *(undefined4 *)(iVar21 + 500) = 0;
      *(undefined4 *)(iVar21 + 0x1c4) = 0;
      *(undefined4 *)(iVar21 + 0x1d4) = 0;
      *(undefined4 *)(iVar21 + 0x1e4) = 0;
      *(undefined4 *)(iVar21 + 0x214) = 0;
      return;
    }
  }
  pcVar7 = DAT_8002b64c;
  puVar6 = PTR_DAT_8002b648;
  cVar1 = *PTR_DAT_8002b648;
  if ((cVar1 == '\x02') && ((DAT_8002b64c[0x21] != '\x01' || (DAT_8002b64c[0x3a] == '\x01')))) {
    DAT_8002b64c[0x18] = '\x01';
    pcVar7[0x17] = '\x01';
  }
  puVar8 = PTR_DAT_8002b65c;
  iVar21 = DAT_8002b658;
  iVar13 = DAT_8002b654;
  iVar18 = DAT_8002b650;
  iVar29 = DAT_8002b654 + 2000;
  if (8 < (byte)pcVar7[10]) {
    if (pcVar7[0x18] != '\0') {
      FUN_80017760();
      FUN_80019704(0);
      FUN_80018f6c(2,0x2f,iVar18,iVar18 + -0xfb);
      FUN_80009af4();
    }
    if (pcVar7[0x17] == '\0') goto LAB_8002b414;
    FUN_8001b424(pcVar7 + 0x1a,pcVar7 + 0x1c);
    if (*pcVar7 != '\0') {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02')) {
        *(undefined2 *)(puVar8 + 0x12) = 400;
      }
      FUN_8000410c();
      cVar1 = pcVar7[0x21];
      bVar32 = cVar1 != '\0';
      if (bVar32) {
        cVar1 = pcVar7[0x21];
      }
      if (((!bVar32 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) &&
         ((pcVar7[0x23] == '\x01' || (pcVar7[9] != '\0')))) {
        FUN_8000583c();
      }
      if (*(char *)(iVar21 + 7) == '\0') {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b654);
      }
    }
    if (pcVar7[0xc] == '\0') {
LAB_8002b2e8:
      if (*(char *)(iVar21 + 7) != '\0') goto LAB_8002b2f4;
    }
    else {
      if ((pcVar7[0x3a] == '\0') && (*puVar6 != '\x02')) {
        *(undefined2 *)(puVar8 + 0x14) = 400;
      }
      FUN_80006f28();
      cVar1 = pcVar7[0x21];
      bVar32 = cVar1 != '\0';
      if (bVar32) {
        cVar1 = pcVar7[0x21];
      }
      if (((!bVar32 || cVar1 == '\x02') && (0x1a < (byte)pcVar7[10])) &&
         ((pcVar7[0x23] == '\0' || (pcVar7[0x15] != '\0')))) {
        FUN_80008594();
      }
      if (*(char *)(iVar21 + 7) == '\0') {
        FUN_80012a64(*(undefined2 *)(pcVar7 + 0x1a),0,*(undefined2 *)(pcVar7 + 0x1c),DAT_8002b668);
        goto LAB_8002b2e8;
      }
LAB_8002b2f4:
      FUN_80017760();
      FUN_80019704(DAT_8002b66c);
      if (*(ushort *)(pcVar7 + 0x1c) < 2) {
        *(undefined2 *)(pcVar7 + 0x1c) = 2;
      }
      uVar14 = 1;
      if (1 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2)) {
        do {
          puVar16 = (ushort *)(iVar13 + uVar14 * 2);
          puVar22 = (undefined2 *)(iVar29 + uVar14 * 2);
          FUN_80018d30(*puVar16 + 0x96,*puVar22,puVar16[1] + 0x96,puVar22[1]);
          uVar14 = uVar14 + 1 & 0xfffeffff;
        } while ((int)uVar14 < (int)(*(ushort *)(pcVar7 + 0x1c) - 2));
      }
    }
    cVar1 = pcVar7[4];
    bVar32 = cVar1 != '\0';
    if (bVar32) {
      cVar1 = *pcVar7;
    }
    if (bVar32 && cVar1 != '\0') {
      FUN_800043e4();
    }
    cVar1 = pcVar7[0x10];
    bVar32 = cVar1 != '\0';
    if (bVar32) {
      cVar1 = pcVar7[0xc];
    }
    if (bVar32 && cVar1 != '\0') {
      FUN_80019704(0);
      FUN_80018f6c(3,0x81,0x2d5);
      FUN_800075dc();
      FUN_80019704(DAT_8002b670);
      puVar22 = DAT_8002b674;
      uVar14 = 0;
      *DAT_8002b674 = DAT_8002b674[1];
      do {
        puVar16 = puVar22 + uVar14;
        if (0x50 < *puVar16) {
          *puVar16 = 0x50;
        }
        FUN_80018ef4(uVar14 + 3,(0x50 - *puVar16 & 0xffff) + 0x81,0xd1);
        uVar14 = uVar14 + 1 & 0xfffeffff;
      } while (uVar14 < 0x2d3);
    }
LAB_8002b414:
    iVar18 = DAT_8002b678;
    if (pcVar7[0x18] == '\0') {
      return;
    }
    if (*(char *)(DAT_8002b678 + 0x292) != '\0') {
      FUN_8000eb10();
    }
    if (*(char *)(iVar18 + 0x29a) != '\0') {
      FUN_8000eb84();
    }
    cVar1 = *(char *)(iVar18 + 0x292);
    bVar32 = cVar1 == '\0';
    if (bVar32) {
      cVar1 = *(char *)(iVar18 + 0x29a);
    }
    if (!bVar32 || cVar1 != '\0') {
      FUN_8000ebf8();
    }
    FUN_8000b5cc();
    FUN_80021810();
    uVar14 = DAT_8002b67c;
    iVar13 = DAT_8001cd30;
    iVar18 = DAT_8001cd2c;
    uVar27 = 0x2e;
    iVar21 = DAT_8002b67c + 0xf6;
    if (DAT_8002b67c < 0x2f) {
      return;
    }
    do {
      iVar29 = uVar27 * 800 + 2;
      FUN_80000608(iVar13 + iVar29 * 2,iVar18 + iVar29 * 2,iVar21);
      uVar27 = uVar27 + 1;
    } while (uVar27 < uVar14);
    return;
  }
  uVar11 = (ushort)(byte)pcVar7[0x3a];
  if (uVar11 != 0) {
                    // WARNING: Could not recover jumptable at 0x8002b490. Too many branches
                    // WARNING: Treating indirect jump as call
    (*UNRECOVERED_JUMPTABLE_00)();
    return;
  }
  if (cVar1 != '\x02') {
    uVar11 = *(ushort *)PTR_DAT_8002b65c;
  }
  else {
    *(undefined2 *)PTR_DAT_8002b65c = 0;
  }
  if (cVar1 == '\x02' || uVar11 == 0) {
    FUN_80017760();
    FUN_80019704(0);
    uVar14 = DAT_8002b67c;
    FUN_80018f6c(2,0x2f,iVar18,DAT_8002b67c);
    FUN_80009af4();
    FUN_8000b5cc();
    FUN_8001cccc(2,0x2e,uVar14 + 0xf7,uVar14);
    FUN_80017778();
  }
  iVar18 = DAT_8002b680;
  if (*pcVar7 != '\0') {
    FUN_80017778();
    iVar17 = iVar18 - (uint)*DAT_8002b684;
    *(short *)(puVar8 + 0x16) = (short)iVar17;
    iVar17 = iVar17 * 0x10000 >> 0x10;
    if (iVar17 < 0x2f) {
      iVar17 = 0x2f;
    }
    else {
      if (0x1c0 < iVar17) {
        iVar17 = 0x1c0;
      }
    }
    *(short *)(puVar8 + 0x16) = (short)iVar17;
    if (*(char *)(iVar21 + 7) == '\0') {
      FUN_800067ac();
    }
  }
  if (pcVar7[0xc] == '\0') {
LAB_8002b590:
    if (*(char *)(iVar21 + 7) == '\0') goto LAB_8002b624;
  }
  else {
    FUN_80017778();
    iVar18 = iVar18 - (uint)*DAT_8002b688;
    *(short *)(puVar8 + 0x18) = (short)iVar18;
    iVar18 = iVar18 * 0x10000 >> 0x10;
    if (iVar18 < 0x2f) {
      iVar18 = 0x2f;
    }
    else {
      if (0x1c0 < iVar18) {
        iVar18 = 0x1c0;
      }
    }
    *(short *)(puVar8 + 0x18) = (short)iVar18;
    if (*(char *)(iVar21 + 7) == '\0') {
      FUN_800094f8();
      goto LAB_8002b590;
    }
  }
  if (*(short *)puVar8 == 0) {
    *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);
    *(undefined2 *)(puVar8 + 4) = *(undefined2 *)(puVar8 + 0x18);
  }
  FUN_80019704(DAT_8002b66c);
  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x96,*(undefined2 *)(puVar8 + 4),
               *(ushort *)(puVar8 + 0x16) + 0x96,*(undefined2 *)(puVar8 + 0x18));
  FUN_80018d30(*(ushort *)(puVar8 + 2) + 0x97,*(ushort *)(puVar8 + 4) + 1,
               *(ushort *)(puVar8 + 0x16) + 0x97,*(ushort *)(puVar8 + 0x18) + 1);
  *(undefined2 *)(puVar8 + 2) = *(undefined2 *)(puVar8 + 0x16);
  uVar10 = *(undefined2 *)(puVar8 + 0x18);
  *(undefined2 *)(puVar8 + 4) = uVar10;
  uVar11 = *(ushort *)puVar8;
  *(undefined2 *)(iVar13 + (uint)uVar11 * 2) = *(undefined2 *)(puVar8 + 0x16);
  *(undefined2 *)(iVar29 + (uint)uVar11 * 2) = uVar10;
LAB_8002b624:
  sVar3 = *(short *)puVar8;
  *(ushort *)puVar8 = sVar3 + 1U;
  if (0x2cf < (ushort)(sVar3 + 1U)) {
    *(undefined2 *)puVar8 = 0;
  }
                    // WARNING: Could not recover jumptable at 0x8002b644. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}

