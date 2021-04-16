//Function to read a sum of data bytes from the FPGA after command 0x24 has been send to it

// param_1 ==> byte count

undefined FUN_8001b058(uint param_1)
{
  int iVar1;
  undefined uVar2;
  uint uVar3;
  uint uVar4;
  
  uVar4 = 0;
  FUN_800169f8(0x24);                    //Write command 0x24 to FPGA
  FUN_800167a0();                        //Set databus as input
  iVar1 = DAT_8001b0f0;                  //0x01C20890. Port E config register base address
  FUN_80017738(DAT_8001b0f0,9);          //PE09 low (read)
  FUN_80017738(iVar1,10);                //PE10 low (data)
  uVar3 = 0;

  if (param_1 != 0)                      //Only when param_1 count not 0
  {
    do
    {
      FUN_80017738(iVar1,8);             //PE08 low (clock pulse)
      FUN_8001774c(iVar1,8);             //PE08 high
      uVar3 = uVar3 + 1 & 0xfffeffff;    //Add one to the count done

      //Get the byte and add it to the total
      uVar4 = (*(uint *)(iVar1 + 0x10) & 0xff) + uVar4 & 0xfffeffff;
    } while (uVar3 < param_1);           //Repeat untill param_1 count
  }

  uVar2 = FUN_80000dc4(uVar4,param_1);   //Some calculations done on the data
  return uVar2;
}

