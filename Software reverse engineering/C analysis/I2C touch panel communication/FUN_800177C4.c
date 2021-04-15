//Function to read from the touch panel

void FUN_800177c4(void)
{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined *puVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  code *in_lr;
  byte bStack48;
  byte bStack47;
  byte bStack46;
  byte bStack45;
  byte local_24 [4];
  undefined auStack32 [8];
  code *UNRECOVERED_JUMPTABLE;
  
  uVar2 = DAT_80017914;                        //0x0000814E. Status register of GT911
  local_24[0] = 0;
  UNRECOVERED_JUMPTABLE = in_lr;

  FUN_80017ad4(DAT_80017914,local_24,1);        //Function to read bytes from GT911 registers. Output is in local_24. One bye is read here.

  if ((local_24[0] & 0x80) == 0)                //Check if panel is touched
  {
    return;                                     //Return if not
  }

  auStack32[0] = 0;
  FUN_80017d2c(uVar2,auStack32,1);              //If there is touch detected clear the GT911 status register
  puVar4 = PTR_DAT_8001791c;                    //0x80192f02. Some buffers in the DRAM (0x80000000 - 0x82000000) 
  puVar3 = DAT_80017918;                        //0x8036B792.

  if (4 < (local_24[0] & 0xf) - 1)              //If there are 5 or more or no touch points do nothing
  {
    *(undefined2 *)(DAT_80017918 + 2) = 800;    //Store 800 to 0x8036B794  (16 bits)
    *(undefined2 *)(puVar4 + 2) = 800;          //Store 800 to 0x80192f04  (16 bits)
    *(undefined2 *)(puVar3 + 4) = 0x1e0;        //Store 480 to 0x8036B796  (16 bits)
    *(undefined2 *)(puVar4 + 4) = 0x1e0;        //Store 480 to 0x80192f06  (16 bits)
    *puVar3 = 0;                                //Store 0x00 to 0x8036B792 (byte)
    *puVar4 = 0;                                //Store 0x00 to 0x80192f02 (byte)
    return;
  }

  FUN_800169f8(0x41);                           //Write 0x41 to the FPGA
  uVar6 = FUN_80016850();                       //Read a byte from FPGA
  uVar7 = FUN_80016850();                       //Read another byte from FPGA

  //Read 4 bytes from the touch panel from a register address retreived from the FPGA???????
  FUN_80017ad4(uVar7 | (uVar6 & 0xff) << 8,&bStack48,4);

  iVar5 = DAT_80017920;                         //0x8019CF7C. Some buffer in RAM

  //Make x coordinate
  uVar6 = ((uint)bStack48 + (uint)bStack47 * 0x100 & 0xfffeffff) * 100 >> 7;
  *(short *)(DAT_80017920 + 2) = (short)uVar6;  //Store it to 0x8019CF7E (16 bits)

  if (800 < uVar6)                              //Check if out of range
  {
    *(undefined2 *)(iVar5 + 2) = 800;           //If so store 800 to 0x8019CF7E (16 bits)
  }

  uVar6 = DAT_80017924;                         //0x10624DD3. Some number used for coordinate calculation
  uVar1 = *(undefined2 *)(iVar5 + 2);           //Get stored x coordinate
  *(undefined2 *)(puVar3 + 2) = uVar1;          //Store it to 0x8036B794 (16 bits)
  *(undefined2 *)(puVar4 + 2) = uVar1;          //And store it to 0x80192f04 (16 bits)

  //Make y coordinate
  uVar6 = (uint)((ulonglong)(((uint)bStack46 + (uint)bStack45 * 0x100 & 0xfffeffff) * 100) * (ulonglong)uVar6 >> 0x23) & 0xff80ffff;

  *(short *)(iVar5 + 4) = (short)uVar6;         //Store it to 0x8019CF80 (16 bits)

  if (0x1e0 < uVar6)                            //Check if out of range
  {
    *(undefined2 *)(iVar5 + 4) = 0x1e0;         //If so store 480 to 0x8019CF80 (16 bits)
  }

  uVar1 = *(undefined2 *)(iVar5 + 4);           //Get stored y coordinat
  *(undefined2 *)(puVar3 + 4) = uVar1;          //Store it to 0x8036B796 (16 bits)
  *(undefined2 *)(puVar4 + 4) = uVar1;          //And store it to 0x80192f06 (16 bits)
  *puVar3 = 1;                                  //Store 0x01 to 0x8036B792 (byte)
  *puVar4 = 1;                                  //Store 0x00 to 0x80192f02 (byte)
  return;
}

