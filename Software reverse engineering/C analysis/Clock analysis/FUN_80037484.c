//Part of initialization

void FUN_80037484(void)

{
  undefined4 uVar1;
  
  uVar1 = DAT_80037548;                                                     //0x80730000.
  FUN_80035478(DAT_80037548,0x80000000,0,0,0,0,0x80000000,0,0);
  FUN_80035478(uVar1,0,0x80000000,0,0x80000000,0,0x80000000,0,0);
  FUN_80035478(uVar1,0x80000000,0x80000000,0,0x80000000,0,0x2000000,0,3);

  //Some MMU coprocessor setup
  FUN_80031e18(uVar1);
  FUN_80031e04();
  FUN_80031dc4(1);
  FUN_80031de4();
  FUN_80031dcc();
  FUN_80031dac();
  return;
}

