//Read something from the FPGA

uint FUN_80016850(void)
{
  int iVar1;
  
  FUN_800167a0();                             //Setup port E pins 0:7 for input
  iVar1 = DAT_8001689c;                       //0x01C20890. Port E config register base
  FUN_80017738(DAT_8001689c,9);               //Set pin PE09 low
  FUN_80017738(iVar1,10);                     //Set pin PE10 low
  FUN_80017738(iVar1,8);                      //Set pin PE08 low
  FUN_8001774c(iVar1,8);                      //Set pin PE08 high
  return *(uint *)(iVar1 + 0x10) & 0xff;      //Read a byte from the FPGA (port E data register holds twelve bits)
}

