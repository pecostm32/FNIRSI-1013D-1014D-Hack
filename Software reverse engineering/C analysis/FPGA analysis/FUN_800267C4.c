//Do some data processing, write command 0x17 and write a byte to the fpga data register
void FUN_800267c4(void)

{
  byte bVar1;
  int iVar2;
  undefined4 unaff_r4;
  
  FUN_8000b4d4();                               //Do some data processing
  FUN_800169f8(0x17);                           //Write command 0x17

  iVar2 = DAT_800169f4;                         //0x01C20890 Port E base reg addr
  bVar1 = *(byte *)(DAT_800267e4 + 0x28);       //0x8019D5A0 + 0x28

  //Actualy FUN_800168FC from here
  FUN_8001764c(DAT_800169f4,0,1);   //Config IO pin
  FUN_8001764c(iVar2,1,1);
  FUN_8001764c(iVar2,2,1);
  FUN_8001764c(iVar2,3,1);
  FUN_8001764c(iVar2,4,1);
  FUN_8001764c(iVar2,5,1);
  FUN_8001764c(iVar2,6,1);
  FUN_8001764c(iVar2,7,1);
  FUN_8001774c(iVar2,9);
  FUN_80017738(iVar2,10);
  *(uint *)(iVar2 + 0x10) = (uint)bVar1 | *(uint *)(iVar2 + 0x10) & 0xffffff00;
  FUN_80017738(iVar2,8);
  *(uint *)(iVar2 + 0x10) = *(uint *)(iVar2 + 0x10) | 0x100;
  return;
}

