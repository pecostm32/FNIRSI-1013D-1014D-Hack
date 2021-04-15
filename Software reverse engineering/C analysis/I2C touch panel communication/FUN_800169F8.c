//Write something to the FPGA
void FUN_800169f8(uint param_1)

{
  int iVar1;
  
  iVar1 = DAT_80016af0;                          //0x01C20890. Port E config register base
  FUN_8001764c(DAT_80016af0,0,1);                //Set port E0:7 pins as outputs
  FUN_8001764c(iVar1,1,1);
  FUN_8001764c(iVar1,2,1);
  FUN_8001764c(iVar1,3,1);
  FUN_8001764c(iVar1,4,1);
  FUN_8001764c(iVar1,5,1);
  FUN_8001764c(iVar1,6,1);
  FUN_8001764c(iVar1,7,1);                       //Down to here
  FUN_8001774c(iVar1,9);                         //Set PE09 high
  FUN_8001774c(iVar1,10);                        //Set PE10 high

  //Write LSB of port E data register with param_1 and keep uper bytes as they were
  *(uint *)(iVar1 + 0x10) = param_1 & 0xff | *(uint *)(iVar1 + 0x10) & 0xffffff00;

  FUN_80017738(iVar1,8);                         //Set PE08 low
  FUN_8001774c(iVar1,8);                         //Set PE08 high
  return;
}

