//Function for sending a bunch of bytes to the i2c interface (bit banged)

//param_1 ==> register address of the touch panel (not the slave address)
//param_2 ==> pointer to the byte(s) to send
//param_3 ==> number of bytes to send

undefined4 FUN_80017d2c(uint param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  FUN_80009a6c();                                       //Setup the bus and send start condition. For clock stretching SCL needs to be an input. I think port A is a push/pull output and not open drain
  FUN_80039144(0x28);                                   //Send single byte to i2c interface
  FUN_800099e4();                                       //Clock the acknowledge bit. SCL and SDA are left low on return of this function
  FUN_80039144((param_1 << 0x10) >> 0x18);              //Send high byte of register address
  FUN_800099e4();                                       //Clock the acknowledge bit
  FUN_80039144(param_1 & 0xff);                         //Send low byte of register address
  FUN_800099e4();                                       //Clock the acknowledge bit

  uVar2 = 0;
  if (param_3 != 0)                                     //As long as there are bytes to send
  {
    do
    {
      FUN_80039144(*(undefined *)(param_2 + uVar2));    //Send single byte to i2c interface
      FUN_800099e4();                                   //Clock the acknowledge bit

      if (uVar2 == param_3)                             //Check on last byte send
      {
        uVar3 = 1;                                      //If so break out of the loop
        break;
      }

      uVar2 = uVar2 + 1 & 0xff;                         //Add 1 to the count done and limit on 256 bytes
    } while (uVar2 < param_3);
  }

  uVar1 = DAT_80017e1c;                                 //0x01C20800. Base register address for Port A
  FUN_8001764c(DAT_80017e1c,3,1);                       //Setup SCL (PA3) as output
  FUN_8001764c(uVar1,2,1);                              //Setup SDA (PA2) as output
  FUN_80017738(uVar1,2);                                //Set SDA low
  FUN_8000bc34(10);                                     //Delay 10
  FUN_8001774c(uVar1,3);                                //Set SCL high
  FUN_8000bc34(10);                                     //Delay 10
  FUN_8001774c(uVar1,2);                                //Set SDA high. Send stop condition
  FUN_8000bc34(10);                                     //Delay 10
  return uVar3;                                         //Return done flag
}

