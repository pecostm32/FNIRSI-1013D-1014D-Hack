//Read a given number of bytes from fpga after command 0x26 has been send and sum them together

// param_1 ==> number of bytes to read
undefined FUN_8001b260(uint param_1)
{
  int iVar1;
  undefined uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  FUN_800169f8(0x26);                         //Send command 0x26 to the FPGA
  FUN_800167a0();                             //Set databus for reading
  iVar1 = DAT_8001b2f8;                       //0x01C20890. Port E base register address
  FUN_80017738(DAT_8001b2f8,9);               //PE09 low (read)
  FUN_80017738(iVar1,10);                     //PE10 low (data)
  uVar3 = 0;

  if (param_1 != 0)                           //Only when bytes need to be read
  {
    do
    {
      FUN_80017738(iVar1,8);                  //PE08 low (clock pulse)
      FUN_8001774c(iVar1,8);                  //PE08 high
      uVar3 = uVar3 + 1 & 0xfffeffff;         //Add one to the bytes done count

      //Add the byte to the total sum
      uVar4 = (*(uint *)(iVar1 + 0x10) & 0xff) + uVar4 & 0xfffeffff;
    } while (uVar3 < param_1);                //Do untill last byte handled
  }

  uVar2 = FUN_80000dc4(uVar4,param_1);        //Process the data
  return uVar2;
}


