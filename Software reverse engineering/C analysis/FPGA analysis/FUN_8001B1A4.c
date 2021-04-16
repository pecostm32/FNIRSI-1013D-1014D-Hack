//Another function to read bytes from the FPGA

void FUN_8001b1a4(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined uVar4;
  uint uVar5;
  uint uVar6;
  code *UNRECOVERED_JUMPTABLE_00;
  
  uVar6 = DAT_8001b250;                         //1500 bytes

  if (*(byte *)(DAT_8001b24c + 10) < 0xb)       //0x8019D5A0 + 10. Global variable indicating to use another count
  {
    uVar6 = DAT_8001b254;                       //750 bytes
  }

  //Get the fpga command. Input 0x0D and data from 0x8019D5A0 + 0x23, some global variable
  uVar4 = FUN_800248f8(0xd,*(undefined *)(DAT_8001b24c + 0x23));

  FUN_800169f8(uVar4);                          //Write command given in uVar4 to the fpga
  FUN_800167a0();                               //Set databus for input
  iVar2 = DAT_8001b258;                         //0x01C20890. Port E config register base address
  FUN_80017738(DAT_8001b258,9);                 //PE09 low (read)
  FUN_80017738(iVar2,10);                       //PE10 low (data)
  iVar3 = DAT_8001b25c;                         //0x801A04CA. Buffer in DRAM
  uVar5 = 0;

  if (uVar6 != 0)                               //Only when there is a count
  {
    do
    {
      FUN_80017738(iVar2,8);                    //PE08 low (clock pulse)
      FUN_8001774c(iVar2,8);                    //PE08 high
      iVar1 = uVar5 * 2;                        //Count times 2 as an index
      uVar5 = uVar5 + 1 & 0xfffeffff;           //Add one to the count

      //Write the byte read from the FPGA as 16bits value into the DRAM buffer
      *(ushort *)(iVar3 + iVar1) = (ushort)*(undefined4 *)(iVar2 + 0x10) & 0xff;
    } while (uVar5 < uVar6);                    //Do untill all bytes are handled

    return;
  }

  return;
}

