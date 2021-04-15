//This is the function that sets up the configuration for the touch panel

undefined4 FUN_8001794c(void)
{
  char *pcVar1;
  undefined4 uVar2;
  byte bVar3;
  uint uVar4;
  undefined4 in_r3;
  int iVar5;
  undefined4 local_10;
  
  uVar2 = DAT_80017ab4;                         //0x01C20800. Base register address for Port A
  local_10 = in_r3;
  FUN_8001764c(DAT_80017ab4,3,1,0);             //Setup SCL (PA3) as output
  FUN_8001764c(uVar2,2,1,0);                    //Setup SDA (PA2) as output
  FUN_8001774c(uVar2,3);                        //Set SCL high
  FUN_8001774c(uVar2,2);                        //Set SDA high
  FUN_8001764c(uVar2,0,1);                      //Setup RESET (PA0) as output. Start of slave address init of touch panel
  FUN_8001764c(uVar2,1,1,0);                    //Setup INT (PA1) as output
  FUN_80017738(uVar2,0);                        //Set RESET low
  FUN_80017738(uVar2,1);                        //Set INT low
  FUN_8000bc34(100);                            //Delay function.    100
  FUN_8001774c(uVar2,1);                        //Set INT high. Sequence for selecting 0x14 as slave address (0x28/0x29, write/read bytes)
  FUN_8000bc34(DAT_80017ab8);                   //Delay again.     20000 (Should be 100uS)
  FUN_8001774c(uVar2,0);                        //Set RESET high
  FUN_8000bc34(DAT_80017abc);                   //Delay again.     10000
  FUN_8001764c(uVar2,1,0);                      //Set INT as input
  FUN_8000bc34(DAT_80017ac0);                   //Wait again.     100000
  uVar2 = DAT_80017ac4;                         //0x00008040
  local_10._0_1_ = 2;
  FUN_80017d2c(DAT_80017ac4,&local_10,1);       //Write 0x02 to register address 0x8040. Touch Panel command (read diff data or raw data)
  bVar3 = 0;
  uVar4 = 0;

  do
  {
    pcVar1 = (char *)(DAT_80017ac8 + uVar4);    //There is a buffer at 0x8019CF82 in RAM where it calculates the checksum for the config of the touch panel
    iVar5 = DAT_80017ac8 + uVar4;
    uVar4 = uVar4 + 2 & 0xfffeffff;
    bVar3 = *(char *)(iVar5 + 1) + bVar3 + *pcVar1;
  } while (uVar4 < 0xb8);

  *(byte *)(DAT_80017ac8 + 0xb8) = ~bVar3 + 1;

  FUN_80017d2c(DAT_80017acc,DAT_80017ac8,0xba); //Write the configuration data the the touch panel starting from register address 0x8047

  FUN_8000bc34(DAT_80017ad0);                   //Wait again.  200000
  local_10 = (uint)local_10._1_3_ << 8;
  FUN_80017d2c(uVar2,&local_10,1);              //Write 0x00 to register address 0x8040. Touch Panel command (read coordinate status)
  return 0;
}

