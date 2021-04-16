void FUN_8000b4d4(undefined4 param_1,uint param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  undefined uVar4;
  uint uVar5;
  
  iVar3 = DAT_8000b5c4;
  if (*(char *)(DAT_8000b5c4 + 0x23) == '\0') {
    cVar1 = *(char *)(DAT_8000b5c4 + 3);
    uVar2 = *(ushort *)(DAT_8000b5c4 + 6);
  }
  else {
    cVar1 = *(char *)(DAT_8000b5c4 + 0xf);
    uVar2 = *(ushort *)(DAT_8000b5c4 + 0x12);
  }
  uVar5 = (uint)uVar2;
  switch(cVar1) {
  case '\0':
    param_2 = (uint)*DAT_8000b5c8;
    break;
  case '\x01':
    param_2 = (uint)DAT_8000b5c8[1];
    break;
  case '\x02':
    param_2 = (uint)DAT_8000b5c8[2];
    break;
  case '\x03':
    param_2 = (uint)DAT_8000b5c8[3];
    break;
  case '\x04':
    param_2 = (uint)DAT_8000b5c8[4];
    break;
  case '\x05':
    param_2 = (uint)DAT_8000b5c8[5];
    break;
  case '\x06':
    param_2 = (uint)DAT_8000b5c8[6];
LAB_8000b578:
    if (*(ushort *)(DAT_8000b5c4 + 0x26) < uVar5) {
      uVar4 = FUN_8000090c((uVar5 - (int)(uVar5 - *(ushort *)(DAT_8000b5c4 + 0x26)) / 2) * 100,
                           param_2);
      *(undefined *)(iVar3 + 0x28) = uVar4;
      return;
    }
    uVar4 = FUN_8000090c((uVar5 + (int)(*(ushort *)(DAT_8000b5c4 + 0x26) - uVar5) / 2) * 100,param_2
                        );
    goto LAB_8000b570;
  default:
    if (cVar1 == '\x06') goto LAB_8000b578;
  }
  uVar4 = FUN_80000dc4((uint)*(ushort *)(DAT_8000b5c4 + 0x26) * 100,param_2);
LAB_8000b570:
  *(undefined *)(iVar3 + 0x28) = uVar4;
  return;
}

