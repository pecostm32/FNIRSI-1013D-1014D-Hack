void FUN_800118f4(void)

{
  char cVar1;
  undefined *puVar2;
  int *piVar3;
  ushort uVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  ushort *puVar8;
  uint uVar9;
  uint uVar10;
  
  cVar1 = *(char *)(DAT_80011c24 + 1);
  uVar4 = FUN_800232b4(DAT_80011c28);
  uVar9 = 0xe;
  uVar5 = FUN_800232b4(DAT_80011c2c);
  piVar3 = Global_Frame_Buffer_Pointer;
  puVar2 = PTR_DAT_80011c30;
  if (cVar1 == '\x01') {
    do {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);
      uVar6 = uVar10 + 9 & 0xfffeffff;
      if (uVar6 < uVar10 + 0xeb) {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0x2e);
    return;
  }
  if (cVar1 == '\x02') {
    uVar9 = 0x47;
    do {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);
      uVar6 = uVar10 + 9 & 0xfffeffff;
      if (uVar6 < uVar10 + 0xeb) {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0x69);
    return;
  }
  if (cVar1 == '\x03') {
    uVar9 = 0x82;
    do {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);
      uVar6 = uVar10 + 9 & 0xfffeffff;
      if (uVar6 < uVar10 + 0xeb) {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0xa4);
    return;
  }
  if (cVar1 == '\x04') {
    uVar9 = 0xbd;
    do {
      uVar10 = (uint)*(ushort *)(puVar2 + 4);
      uVar6 = uVar10 + 9 & 0xfffeffff;
      if (uVar6 < uVar10 + 0xeb) {
        uVar10 = (uVar10 - uVar6) + 0xeb & 0xffff;
        puVar8 = (ushort *)(*piVar3 + (uVar6 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
        do {
          if (*puVar8 == uVar5) {
            *puVar8 = uVar4;
          }
          else {
            *puVar8 = ~*puVar8;
          }
          uVar10 = uVar10 - 1 & 0xffff;
          puVar8 = puVar8 + 1;
        } while (uVar10 != 0);
      }
      uVar9 = uVar9 + 1 & 0xfffeffff;
    } while (uVar9 < 0xde);
    return;
  }
  if (cVar1 != '\x05') {
    return;
  }
  uVar9 = 0xf7;
  uVar10 = DAT_80011c38 - 0xe;
  do {
    uVar6 = (uint)*(ushort *)(puVar2 + 4);
    uVar7 = uVar6 + 9 & 0xfffeffff;
    if (uVar7 < uVar6 + 0xeb) {
      uVar6 = (uVar6 - uVar7) + 0xeb & 0xffff;
      puVar8 = (ushort *)(*piVar3 + (uVar7 + (*(ushort *)(puVar2 + 6) + uVar9) * 800) * 2);
      do {
        if (*puVar8 == uVar5) {
          *puVar8 = uVar4;
        }
        else {
          *puVar8 = ~*puVar8;
        }
        uVar6 = uVar6 - 1 & 0xffff;
        puVar8 = puVar8 + 1;
      } while (uVar6 != 0);
    }
    uVar9 = uVar9 + 1 & 0xfffeffff;
  } while (uVar9 < uVar10);
  return;
}

