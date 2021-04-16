//Set port E pins 0:7 as input
void FUN_800167a0(void)
{
  uint *puVar1;
  
  puVar1 = DAT_8001684c;             //0x01C20890. Port E configuration register (FPGA)
  FUN_8001764c(DAT_8001684c,0,0);    //Set pin PE0 as input
  FUN_8001764c(puVar1,1,0);          //Set pin PE1 as input
  FUN_8001764c(puVar1,2,0);          //Set pin PE2 as input
  FUN_8001764c(puVar1,3,0);          //Set pin PE3 as input
  FUN_8001764c(puVar1,4,0);          //Set pin PE4 as input
  FUN_8001764c(puVar1,5,0);          //Set pin PE5 as input
  FUN_8001764c(puVar1,6,0);          //Set pin PE6 as input
  FUN_8001764c(puVar1,7,0);          //Set pin PE7 as input
  return;
}

