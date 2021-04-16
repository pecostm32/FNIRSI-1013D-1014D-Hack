//Send command 0x23 and read bytes from FPGA into memory

void FUN_8001b2fc(void)
{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  code *UNRECOVERED_JUMPTABLE_00;
  
  uVar5 = DAT_8001b39c;                     //0x000005DC (1500)

  if (*(byte *)(DAT_8001b398 + 10) < 0xb)   //0x8019D5A0 + 10. Global variable indicating to use another count
  {
    uVar5 = DAT_8001b3a0;                   //0x000002EE (750)
  }

  FUN_800169f8(0x23);                       //Send command 0x23 to FPGA
  FUN_800167a0();                           //Set databus for input
  iVar2 = DAT_8001b3a4;                     //0x01C20890. Port E config register base address
  FUN_80017738(DAT_8001b3a4,9);             //PE09 low (read)
  FUN_80017738(iVar2,10);                   //PE10 low (data)
  iVar3 = DAT_8001b3a8;                     //0x801A1C3A. Buffer in DRAM memory
  uVar4 = 0;

  if (uVar5 != 0)                           //Only if there is a count
  {
    do
    {
      FUN_80017738(iVar2,8);               //PE08 low (Clock pulse)
      FUN_8001774c(iVar2,8);               //PE08 high
      iVar1 = uVar4 * 2;                   //Count times 2 as an index
      uVar4 = uVar4 + 1 & 0xfffeffff;      //Add one to the count

      //Write the byte read from the FPGA as 16bits value into the DRAM buffer
      *(ushort *)(iVar3 + iVar1) = (ushort)*(undefined4 *)(iVar2 + 0x10) & 0xff;
    } while (uVar4 < uVar5);               //Do until last byte

    return;
  }

  return;
}

