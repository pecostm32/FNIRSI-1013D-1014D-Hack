void FUN_80025468(void)

{
  ushort uVar1;
  char *pcVar2;
  char *pcVar3;
  ushort *puVar4;
  ushort *puVar5;
  undefined4 *puVar6;
  undefined *puVar7;
  undefined uVar8;
  ushort uVar9;
  undefined4 *puVar10;
  undefined *puVar11;
  uint uVar12;
  undefined4 *puVar13;
  ushort *puVar14;
  uint uVar15;
  ushort *puVar16;
  undefined4 *puVar17;
  uint uVar18;
  int iVar19;
  uint uVar20;
  undefined4 *puVar21;
  undefined4 *puVar22;
  undefined4 *unaff_r4;
  undefined4 *puVar23;
  uint uVar24;
  bool bVar25;
  bool bVar26;
  int local_30;
  
  iVar19 = DAT_80025710;
  bVar25 = false;
  uVar15 = DAT_80025714;
  switch(*(undefined *)(DAT_80025710 + 10))
  {
    case 9:
    case 10:
      uVar15 = 800;
      break;

    case 0xb:
      uVar15 = DAT_80025734;
      break;

    case 0xc:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
      uVar15 = DAT_80025730;
      break;

    case 0x11:
      uVar15 = DAT_8002572c;
      break;

    case 0x12:
      uVar15 = DAT_80025728;
      break;

    case 0x13:
      uVar15 = DAT_80025724;
      break;

    case 0x14:
    case 0x15:
      uVar15 = DAT_80025720;
      break;

    case 0x16:
      uVar15 = DAT_8002571c;
      break;

    case 0x17:
      uVar15 = DAT_80025718;
      break;
  }

  if ((*(byte *)(DAT_80025710 + 10) < 0x1c) || (*(char *)(DAT_80025710 + 0x21) != '\0'))
  {
    FUN_800267c4();                     //Write command 0x17 and do some data processing
  }

  FUN_800169f8(0xe);                    //Write command 0x0E
  FUN_800168fc(uVar15 >> 0x18);         //Write 32 bits data
  FUN_800168fc(uVar15 >> 0x10);
  FUN_800168fc(uVar15 >> 8);
  FUN_800168fc(uVar15);

  FUN_800169f8(0xf);                    //Write command 0x0F
  FUN_800168fc(0);                      //Write data 0x00

  FUN_800169f8(0x28);                   //Write command 0x28
  FUN_800168fc(0);                      //write data 0x00

  FUN_800169f8(1);                      //Write command 0x01
  FUN_800168fc(1);                      //Write data 0x01

  FUN_800169f8(5);                      //Write command 0x05

  do
  {
    uVar15 = FUN_80016850();            //Read data from the fpga
  } while ((uVar15 & 1) == 0);          //Wait until it is finished

  do 
  {
    uVar15 = FUN_80016850();            //Read data from the fpga. Why a second time round?
  } while ((uVar15 & 1) == 0);          //Wait until it is finished

  FUN_800169f8(1);                      //Write command 0x01
  FUN_800168fc(0);                      //Write data 0x00

  puVar7 = PTR_DAT_8002573c;
  puVar11 = PTR_DAT_80025738;
  *(undefined *)(iVar19 + 0xb) = *(undefined *)(iVar19 + 10);
  *(ushort *)puVar11 = (ushort)*(byte *)(iVar19 + 3);
  *(ushort *)puVar7 = (ushort)*(byte *)(iVar19 + 0xf);
  pcVar2 = PTR_DAT_8002574c;
  pcVar3 = PTR_DAT_80025748;

  if (*(char *)(iVar19 + 0x37) != '\0')
  {
    *(undefined *)(iVar19 + 0x37) = 0;
    FUN_80017760();
    FUN_80019704(0);
    FUN_80018f6c(2,0x2f,DAT_80025740 + 0xfb);
    FUN_80009af4();
    FUN_8000b5cc();
    FUN_8001cccc(2,0x2e,0x2d8,DAT_80025744);
    pcVar2 = PTR_DAT_8002574c;
    pcVar3 = PTR_DAT_80025748;
  }

  do {
    FUN_800169f8(10);
    uVar15 = FUN_80016850();
    if ((uVar15 & 1) != 0) break;
    FUN_800177c4();
    if (*pcVar3 != '\0') {
      bVar25 = true;
      break;
    }
  } while (*pcVar2 != '\x02');
  FUN_800169f8(0xf);
  FUN_800168fc(1);
  if (*(char *)(iVar19 + 0x21) != '\0') {
    if (bVar25) {
      *(undefined *)(iVar19 + 0x18) = 1;
      bVar25 = *(char *)(iVar19 + 0x21) != '\x01';
      if (bVar25) {
        if (*(char *)(iVar19 + 0x36) == '\0') {
          bVar25 = false;
        }
      }
      else {
        *(bool *)(iVar19 + 0x36) = bVar25;
      }
      *(bool *)(iVar19 + 0x17) = bVar25;
      return;
    }
    if (*(char *)(iVar19 + 0x21) == '\x01') {
      *(undefined *)(iVar19 + 0x3a) = 1;
      FUN_80010944();
      *(ushort *)puVar11 = (ushort)*(byte *)(iVar19 + 3);
      *(ushort *)puVar7 = (ushort)*(byte *)(iVar19 + 0xf);
    }
    *(undefined *)(iVar19 + 0x36) = 1;
  }
  local_30 = 0;
  puVar10 = (undefined4 *)FUN_8001bec4();
  puVar6 = DAT_8000b270;
  puVar13 = DAT_8000b268;
  if ((byte)DAT_8000b264[10] < 0x19) {
    if ((byte)DAT_8000b264[10] < 0xb) {
      uVar15 = 10;
      goto LAB_8000a894;
    }
    if (puVar10 < DAT_8000b268) {
      uVar15 = (uint)((int)puVar10 + 0xd11) & 0xfffeffff;
      goto LAB_8000a894;
    }
    puVar11 = (undefined *)((int)puVar10 + -0x2ee);
  }
  else {
    switch(DAT_8000b264[10]) {
    case '\x19':
      unaff_r4 = DAT_8000b26c;
      break;
    case '\x1a':
      unaff_r4 = (undefined4 *)0xaa;
      break;
    case '\x1b':
      unaff_r4 = (undefined4 *)0x55;
      break;
    case '\x1c':
      unaff_r4 = (undefined4 *)0x2f;
      break;
    case '\x1d':
      unaff_r4 = (undefined4 *)&NotUsed;
    }
    if (unaff_r4 <= puVar10) {
      uVar15 = (uint)((int)puVar10 - (int)unaff_r4) & 0xffff;
      goto LAB_8000a894;
    }
    puVar11 = (undefined *)(-0xf001 - (int)((int)unaff_r4 - (int)puVar10));
  }
  uVar15 = (uint)puVar11 & 0xffff;
LAB_8000a894:
  puVar10 = DAT_8000b270 + 0xfa;
  if (*DAT_8000b264 != '\0') {
    FUN_800169f8(0x1f);
    FUN_800168fc();
    FUN_800168fc(uVar15);
    puVar22 = puVar6;
    if ((byte)DAT_8000b264[10] < 0xb) {
      puVar22 = puVar13;
    }
    uVar8 = FUN_800248f8(0xc,DAT_8000b264[0x23]);
    FUN_800169f8(uVar8);
    FUN_800167a0();
    puVar17 = DAT_8000b274;
    FUN_80017738(DAT_8000b274,9);
    FUN_80017738(puVar17,10);
    puVar23 = (undefined4 *)0x0;
    if (puVar22 != (undefined4 *)0x0) {
      do {
        FUN_80017738(puVar17,8);
        FUN_8001774c(puVar17,8);
        puVar14 = DAT_8000b278 + (int)puVar23;
        puVar23 = (undefined4 *)((uint)((int)puVar23 + 1) & 0xfffeffff);
        *puVar14 = (ushort)puVar17[4] & 0xff;
      } while (puVar23 < puVar22);
    }
    pcVar2 = DAT_8000b264;
    *DAT_8000b278 = DAT_8000b278[1];
    if (pcVar2[0x23] == '\0') {
      local_30 = FUN_800291e0();
    }
    if (pcVar2[10] == '\x19') {
      FUN_8001363c(DAT_8000b278,0);
    }
    if (pcVar2[10] == '\x1a') {
      FUN_800141c8(DAT_8000b278,0);
    }
    if (pcVar2[10] == '\x1b') {
      FUN_800130c4(DAT_8000b278,0);
    }
    if ((DAT_8000b264[10] == '\x1c') || (DAT_8000b264[10] == '\x1d')) {
      FUN_800169f8(0x1f);
      FUN_800168fc(uVar15 >> 8);
      FUN_800168fc(uVar15);
      puVar22 = puVar6;
      if ((byte)DAT_8000b264[10] < 0xb) {
        puVar22 = puVar13;
      }
      FUN_800169f8(0x21);
      FUN_800167a0();
      FUN_80017738(puVar17,9);
      FUN_80017738(puVar17,10);
      puVar23 = puVar17;
      if (puVar22 != (undefined4 *)0x0) {
        puVar23 = DAT_8000b27c;
      }
      puVar21 = (undefined4 *)0x0;
      if (puVar22 != (undefined4 *)0x0) {
        do {
          FUN_80017738(puVar17,8);
          FUN_8001774c(puVar17,8);
          iVar19 = (int)puVar21 * 2;
          puVar21 = (undefined4 *)((uint)((int)puVar21 + 1) & 0xfffeffff);
          *(ushort *)(DAT_8000b280 + iVar19) = (ushort)*puVar23 & 0xff;
        } while (puVar21 < puVar22);
      }
      FUN_8000460c();
      FUN_800062bc();
    }
    puVar22 = puVar10;
    if (((byte)DAT_8000b264[10] < 0x19) && (puVar22 = puVar6, (byte)DAT_8000b264[10] < 9)) {
      puVar22 = puVar13;
    }
    uVar12 = FUN_800248f8(0xb,DAT_8000b264[3]);
    uVar18 = DAT_8000b288;
    pcVar2 = DAT_8000b264;
    puVar14 = DAT_8000b278;
    puVar16 = DAT_8000b284;
    puVar4 = DAT_8000b284;
    puVar5 = DAT_8000b290;
    while (DAT_8000b264 = pcVar2, DAT_8000b284 = puVar4, DAT_8000b290 = puVar5,
          puVar22 != (undefined4 *)0x0) {
      uVar20 = (uVar12 & 0xffff) * (uint)*puVar14 & 0xffff;
      uVar1 = (ushort)(DAT_8000b28c * uVar20 + DAT_8000b28c >> 0x10);
      uVar9 = uVar1 >> 6;
      if (0x32 < (int)(uVar20 + (uint)((ulonglong)uVar20 * (ulonglong)uVar18 >> 0x25) * -100)) {
        uVar9 = (uVar1 >> 6) + 1;
      }
      puVar22 = (undefined4 *)((int)puVar22 + -1);
      *puVar16 = uVar9;
      pcVar2 = DAT_8000b264;
      puVar14 = puVar14 + 1;
      puVar16 = puVar16 + 1;
      puVar4 = DAT_8000b284;
      puVar5 = DAT_8000b290;
    }
    puVar22 = puVar10;
    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar6, (byte)pcVar2[10] < 9)) {
      puVar22 = puVar13;
    }
    puVar14 = puVar4 + -1;
    puVar16 = puVar5 + -1;
    if (((uint)puVar22 & 1) == 0) {
      *puVar5 = *puVar4;
      puVar14 = puVar4;
      puVar16 = puVar5;
    }
    uVar9 = puVar14[1];
    iVar19 = (int)puVar22 + -1 >> 1;
    while (iVar19 != 0) {
      uVar1 = puVar14[2];
      puVar16[1] = uVar9;
      uVar9 = puVar14[3];
      iVar19 = iVar19 + -1;
      puVar16 = puVar16 + 2;
      *puVar16 = uVar1;
      puVar14 = puVar14 + 2;
    }
    iVar19 = (int)puVar22 + -1;
    if (-1 < iVar19) {
      puVar5[iVar19] = puVar4[iVar19];
    }
    puVar22 = puVar10;
    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar6, (byte)pcVar2[10] < 9)) {
      puVar22 = puVar13;
    }
    puVar14 = DAT_8000b290;
    puVar17 = puVar10;
    uVar18 = DAT_8000b294;
    if ((pcVar2[3] == '\x06') && (puVar22 != (undefined4 *)0x0)) {
      puVar14 = puVar5 + -1;
      if (((uint)puVar22 & 1) != 0) {
        *puVar5 = *puVar5 << 1;
        puVar14 = puVar5;
      }
      uVar18 = (uint)puVar22 >> 1;
      while (uVar18 != 0) {
        puVar16 = puVar14 + 2;
        uVar18 = uVar18 - 1;
        puVar14[1] = puVar14[1] << 1;
        *puVar16 = *puVar16 << 1;
        puVar14 = puVar16;
      }
      puVar23 = (undefined4 *)0x0;
      puVar14 = DAT_8000b290;
      uVar18 = DAT_8000b294;
      if (puVar22 != (undefined4 *)0x0) {
        do {
          puVar14 = puVar5 + (int)puVar23;
          if (*puVar14 < *(ushort *)(pcVar2 + 6)) {
            *puVar14 = 0;
          }
          else {
            *puVar14 = *puVar14 - *(short *)(pcVar2 + 6);
          }
          puVar23 = (undefined4 *)((uint)((int)puVar23 + 1) & 0xfffeffff);
          puVar14 = DAT_8000b290;
          uVar18 = DAT_8000b294;
        } while (puVar23 < puVar22);
      }
    }
    do {
      if (uVar18 < *puVar14) {
        *puVar14 = (ushort)uVar18;
      }
      puVar17 = (undefined4 *)((int)puVar17 + -1);
      puVar14 = puVar14 + 1;
    } while (puVar17 != (undefined4 *)0x0);
    puVar14 = DAT_8000b290;
    iVar19 = DAT_8000b298;
    if ((byte)pcVar2[10] < 0x19) {
      do {
        uVar18 = (uint)*puVar14;
        uVar20 = (uint)puVar14[1];
        uVar12 = (uint)puVar14[2];
        uVar24 = uVar18 + 6;
        bVar26 = uVar24 <= uVar20;
        bVar25 = uVar20 == uVar24;
        if (bVar26 && !bVar25) {
          uVar24 = uVar12 + 6;
        }
        if (bVar26 && !bVar25) {
          bVar26 = uVar24 <= uVar20;
          bVar25 = uVar20 == uVar24;
        }
        if (bVar26 && !bVar25) {
          puVar14[1] = (ushort)(uVar18 + uVar12 >> 1);
        }
        if (uVar20 + 6 < uVar18 && uVar20 + 6 < uVar12) {
          puVar14[1] = (ushort)(uVar18 + uVar12 >> 1);
        }
        iVar19 = iVar19 + -1;
        puVar14 = puVar14 + 1;
      } while (iVar19 != 0);
    }
    FUN_800049a0();
    FUN_80006654();
    if (pcVar2[0x48] == '\0') {
      FUN_80003ec8();
    }
  }
  if (DAT_8000b264[0xc] != '\0') {
    FUN_800169f8(0x1f);
    FUN_800168fc();
    FUN_800168fc(uVar15);
    puVar22 = puVar6;
    if ((byte)DAT_8000b264[10] < 0xb) {
      puVar22 = puVar13;
    }
    uVar8 = FUN_800248f8(0xd,DAT_8000b264[0x23]);
    FUN_800169f8(uVar8);
    FUN_800167a0();
    puVar23 = DAT_8000b274;
    FUN_80017738(DAT_8000b274,9);
    FUN_80017738(puVar23,10);
    puVar14 = DAT_8000b29c;
    puVar17 = (undefined4 *)0x0;
    if (puVar22 != (undefined4 *)0x0) {
      do {
        FUN_80017738(puVar23,8);
        FUN_8001774c(puVar23,8);
        puVar16 = puVar14 + (int)puVar17;
        puVar17 = (undefined4 *)((uint)((int)puVar17 + 1) & 0xfffeffff);
        *puVar16 = (ushort)*DAT_8000b27c & 0xff;
      } while (puVar17 < puVar22);
    }
    pcVar2 = DAT_8000b264;
    *puVar14 = puVar14[1];
    if (pcVar2[0x23] == '\x01') {
      local_30 = FUN_800291e0();
    }
    if (pcVar2[10] == '\x19') {
      FUN_8001363c(DAT_8000b29c,0,puVar10);
    }
    if (pcVar2[10] == '\x1a') {
      FUN_800141c8(DAT_8000b29c,0,puVar10);
    }
    if (pcVar2[10] == '\x1b') {
      FUN_800130c4(DAT_8000b29c,0,puVar10);
    }
    if ((DAT_8000b264[10] == '\x1c') || (DAT_8000b264[10] == '\x1d')) {
      FUN_800169f8(0x1f);
      FUN_800168fc(uVar15 >> 8);
      FUN_800168fc(uVar15);
      puVar22 = puVar6;
      if ((byte)DAT_8000b264[10] < 0xb) {
        puVar22 = puVar13;
      }
      FUN_800169f8(0x23);
      FUN_800167a0();
      FUN_80017738(puVar23,9);
      FUN_80017738(puVar23,10);
      if (puVar22 != (undefined4 *)0x0) {
        puVar14 = DAT_8000b2a0;
        puVar17 = DAT_8000b27c;
      }
      puVar21 = (undefined4 *)0x0;
      if (puVar22 != (undefined4 *)0x0) {
        do {
          FUN_80017738(puVar23,8);
          FUN_8001774c(puVar23,8);
          puVar16 = puVar14 + (int)puVar21;
          puVar21 = (undefined4 *)((uint)((int)puVar21 + 1) & 0xfffeffff);
          *puVar16 = (ushort)*puVar17 & 0xff;
        } while (puVar21 < puVar22);
      }
      FUN_80007380();
      FUN_80009018();
    }
    pcVar2 = DAT_8000b264;
    puVar22 = puVar10;
    if (((byte)DAT_8000b264[10] < 0x19) && (puVar22 = puVar6, (byte)DAT_8000b264[10] < 9)) {
      puVar22 = puVar13;
    }
    uVar18 = FUN_800248f8(0xb,DAT_8000b264[0xf]);
    uVar15 = DAT_8000b288;
    puVar14 = DAT_8000b29c;
    puVar16 = DAT_8000b2a4;
    puVar4 = DAT_8000b2a4;
    puVar5 = DAT_8000b2a8;
    while (DAT_8000b2a4 = puVar4, DAT_8000b2a8 = puVar5, puVar22 != (undefined4 *)0x0) {
      uVar12 = (uVar18 & 0xffff) * (uint)*puVar14 & 0xffff;
      uVar1 = (ushort)(DAT_8000b28c * uVar12 + DAT_8000b28c >> 0x10);
      uVar9 = uVar1 >> 6;
      if (0x32 < (int)(uVar12 + (uint)((ulonglong)uVar12 * (ulonglong)uVar15 >> 0x25) * -100)) {
        uVar9 = (uVar1 >> 6) + 1;
      }
      puVar22 = (undefined4 *)((int)puVar22 + -1);
      *puVar16 = uVar9;
      puVar14 = puVar14 + 1;
      puVar16 = puVar16 + 1;
      puVar4 = DAT_8000b2a4;
      puVar5 = DAT_8000b2a8;
    }
    puVar22 = puVar10;
    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar6, (byte)pcVar2[10] < 9)) {
      puVar22 = puVar13;
    }
    puVar14 = puVar4 + -1;
    puVar16 = puVar5 + -1;
    if (((uint)puVar22 & 1) == 0) {
      *puVar5 = *puVar4;
      puVar14 = puVar4;
      puVar16 = puVar5;
    }
    uVar9 = puVar14[1];
    iVar19 = (int)puVar22 + -1 >> 1;
    while (iVar19 != 0) {
      uVar1 = puVar14[2];
      puVar16[1] = uVar9;
      uVar9 = puVar14[3];
      iVar19 = iVar19 + -1;
      puVar16 = puVar16 + 2;
      *puVar16 = uVar1;
      puVar14 = puVar14 + 2;
    }
    iVar19 = (int)puVar22 + -1;
    if (-1 < iVar19) {
      puVar5[iVar19] = puVar4[iVar19];
    }
    puVar22 = puVar10;
    if (((byte)pcVar2[10] < 0x19) && (puVar22 = puVar13, 8 < (byte)pcVar2[10])) {
      puVar22 = puVar6;
    }
    puVar14 = DAT_8000b2a8;
    uVar15 = DAT_8000b294;
    if ((pcVar2[0xf] == '\x06') && (puVar22 != (undefined4 *)0x0)) {
      puVar14 = puVar5 + -1;
      if (((uint)puVar22 & 1) != 0) {
        *puVar5 = *puVar5 << 1;
        puVar14 = puVar5;
      }
      uVar15 = (uint)puVar22 >> 1;
      while (uVar15 != 0) {
        puVar16 = puVar14 + 2;
        uVar15 = uVar15 - 1;
        puVar14[1] = puVar14[1] << 1;
        *puVar16 = *puVar16 << 1;
        puVar14 = puVar16;
      }
      puVar13 = (undefined4 *)0x0;
      puVar14 = DAT_8000b2a8;
      uVar15 = DAT_8000b294;
      if (puVar22 != (undefined4 *)0x0) {
        do {
          puVar14 = puVar5 + (int)puVar13;
          if (*puVar14 < *(ushort *)(pcVar2 + 0x12)) {
            *puVar14 = 0;
          }
          else {
            *puVar14 = *puVar14 - *(short *)(pcVar2 + 0x12);
          }
          puVar13 = (undefined4 *)((uint)((int)puVar13 + 1) & 0xfffeffff);
          puVar14 = DAT_8000b2a8;
          uVar15 = DAT_8000b294;
        } while (puVar13 < puVar22);
      }
    }
    do {
      if (uVar15 < *puVar14) {
        *puVar14 = (ushort)uVar15;
      }
      puVar10 = (undefined4 *)((int)puVar10 + -1);
      puVar14 = puVar14 + 1;
    } while (puVar10 != (undefined4 *)0x0);
    puVar14 = DAT_8000b2a8;
    iVar19 = DAT_8000b298;
    if ((byte)pcVar2[10] < 0x19) {
      do {
        uVar18 = (uint)*puVar14;
        uVar15 = (uint)puVar14[1];
        uVar12 = (uint)puVar14[2];
        uVar20 = uVar18 + 6;
        bVar26 = uVar20 <= uVar15;
        bVar25 = uVar15 == uVar20;
        if (bVar26 && !bVar25) {
          uVar20 = uVar12 + 6;
        }
        if (bVar26 && !bVar25) {
          bVar26 = uVar20 <= uVar15;
          bVar25 = uVar15 == uVar20;
        }
        if (bVar26 && !bVar25) {
          puVar14[1] = (ushort)(uVar18 + uVar12 >> 1);
        }
        if (uVar15 + 6 < uVar18 && uVar15 + 6 < uVar12) {
          puVar14[1] = (ushort)(uVar18 + uVar12 >> 1);
        }
        iVar19 = iVar19 + -1;
        puVar14 = puVar14 + 1;
      } while (iVar19 != 0);
    }
    FUN_80007714();
    FUN_800093ac();
    if (pcVar2[0x48] == '\0') {
      FUN_80006ce8();
    }
  }
  pcVar2 = DAT_8000b264;
  if (0x18 < (byte)DAT_8000b264[10]) {
    if (DAT_8000b264[0x23] == '\0') {
      if (*DAT_8000b264 != '\0') {
        FUN_80006a94(*(undefined2 *)(DAT_8000b264 + 0x26));
        FUN_80005080();
      }
      if (pcVar2[0xc] != '\0') {
        FUN_80008fac();
        FUN_80007df4();
      }
    }
    else {
      if (DAT_8000b264[0xc] != '\0') {
        FUN_800097e0(*(undefined2 *)(DAT_8000b264 + 0x26));
        FUN_80007df4();
      }
      if (*pcVar2 != '\0') {
        FUN_80006250();
        FUN_80005080();
      }
    }
  }
  if (local_30 == 0) {
    pcVar2[0x1e] = '\0';
    pcVar2[0x18] = '\x01';
    pcVar2[0x17] = '\x01';
  }
  else {
    pcVar2[0x1e] = '\x01';
    pcVar2[0x18] = '\0';
    pcVar2[0x17] = '\0';
  }
  return;
}



uint FUN_80025b0c(void)

{
  uint uVar1;
  
  FUN_800169f8(10);
  uVar1 = FUN_80016850();
  return uVar1 & 1;
}

