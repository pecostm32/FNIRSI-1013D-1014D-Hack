//Write to the FPGA with PE09 high (read/write) and PE10 low (data/command select)
//So target is data register

//param_1 ==> byte to write

void FUN_800168fc(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_800169f4;
  FUN_8001764c(DAT_800169f4,0,1);   //Port E 0:7 as outputs
  FUN_8001764c(iVar1,1,1);
  FUN_8001764c(iVar1,2,1);
  FUN_8001764c(iVar1,3,1);
  FUN_8001764c(iVar1,4,1);
  FUN_8001764c(iVar1,5,1);
  FUN_8001764c(iVar1,6,1);
  FUN_8001764c(iVar1,7,1);
  FUN_8001774c(iVar1,9);            //PE09 high  (write)
  FUN_80017738(iVar1,10);           //PE10 low   (data)

  //Output param_1 on the bus
  *(uint *)(iVar1 + 0x10) = param_1 & 0xff | *(uint *)(iVar1 + 0x10) & 0xffffff00;

  FUN_80017738(iVar1,8);            //PE08 low  (clock pulse)
  FUN_8001774C(iVar1,8);            //PE08 high
  return;
}

