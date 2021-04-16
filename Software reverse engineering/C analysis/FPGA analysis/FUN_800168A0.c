//Function prepares for working from the FPGA
void FUN_800168a0(void)

{
  uint *puVar1;
  undefined4 uVar2;
  undefined4 unaff_r4;
  undefined4 in_lr;
  
  uVar2 = DAT_800168f8;             //0x01C20890. Port E base register address
  FUN_8001764c(DAT_800168f8,9,1);   //PE09 output
  FUN_8001764c(uVar2,10,1);         //PE10 output
  FUN_8001764c(uVar2,8,1);          //PE08 output
  FUN_8001774c(uVar2,8);            //PE08 high

  //This part is FUN_800167A0, which sets the bus up for input
  puVar1 = DAT_8001684c;
  FUN_8001764c(DAT_8001684c,0,0);
  FUN_8001764c(puVar1,1,0);
  FUN_8001764c(puVar1,2,0);
  FUN_8001764c(puVar1,3,0);
  FUN_8001764c(puVar1,4,0);
  FUN_8001764c(puVar1,5,0);
  FUN_8001764c(puVar1,6,0);
  FUN_8001764c(puVar1,7,0);
  return;
}

