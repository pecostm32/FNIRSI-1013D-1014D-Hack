
//Read data from the I2C parameter storage.
void FUN_80024e18(void)

{
  undefined *puVar1;
  undefined uVar2;
  uint uVar3;
  
  puVar1 = DAT_80024ed8;                   //0x8035ec04. A buffer in DRAM


  FUN_800169f8(0x64);

  FUN_800169f8(0x64);

  FUN_8000bc34(0x14);

  FUN_800169f8(0x66);

  do
 {
    FUN_800169f8(0x67);

    uVar3 = FUN_80016850();

  } while ((uVar3 & 1) == 0);

  FUN_800169f8(0x68);

  uVar2 = FUN_80016850();

  puVar1[0] = uVar2;

  FUN_800169f8(0x69);

  uVar2 = FUN_80016850();

  puVar1[1] = uVar2;

  FUN_800169f8(0x6a);

  uVar2 = FUN_80016850();

  puVar1[2] = uVar2;

  FUN_800169f8(0x6b);

  uVar2 = FUN_80016850();

  puVar1[3] = uVar2;

  FUN_800169f8(0x6c);

  uVar2 = FUN_80016850();

  puVar1[4] = uVar2;

  FUN_800169f8(0x6d);

  uVar2 = FUN_80016850();

  puVar1[5] = uVar2;

  FUN_800169f8(0x6e);

  uVar2 = FUN_80016850();

  puVar1[6] = uVar2;

  *PTR_DAT_80024edc = DAT_80024ed8[3];     //*0x80192eea = MSB of read data

  return;
}

