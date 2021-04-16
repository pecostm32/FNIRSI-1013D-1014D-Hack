//Function to read bytes from GT911 registers

//param_1 ==> register address
//param_2 ==> pointer to where to put the bytes
//param_3 ==> number of bytes to read

void FUN_80017ad4(uint param_1,int param_2,uint param_3)
{
  bool bVar1;
  byte bVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  FUN_80009a6c();                                       //Send I2C start condition
  FUN_80039144(0x28);                                   //Send touch panel slave address for write
  FUN_800099e4();                                       //Clock the acknowledge bit
  FUN_80039144((param_1 << 0x10) >> 0x18);              //Send high byte of register address
  FUN_800099e4();                                       //Clock the acknowledge bit
  FUN_80039144(param_1 & 0xff);                         //Send low byte of register address
  FUN_800099e4();                                       //Clock the acknowledge bit
  FUN_80009a6c();                                       //Send I2C re-start condition
  FUN_80039144(0x29);                                   //Send touch panel slave address for read
  FUN_800099e4();                                       //Clock the acknowledge bit
  uVar3 = DAT_80017cdc;                                 //0x01C20800. Port A config register base address
  uVar6 = 0;

  if (param_3 != 0)                                     //Check if bytes need to be received
  {
    do
    {
      uVar5 = 0;
      FUN_8001764c(uVar3,2,0);                          //Set SDA as input
      FUN_80017738(uVar3,3);                            //Set SCL low
      FUN_8000bc34(10);                                 //Delay 10
      bVar2 = 0;
      do
      {
        FUN_8001774c(uVar3,3);                          //Set SCL high
        FUN_8000bc34(10);                               //Delay 10

        uVar5 = (uVar5 << 0x19) >> 0x18;                //Shift bits 1 position left
        iVar4 = FUN_80017724(uVar3,2);                  //Read SDA

        if (iVar4 != 0)                                 //Check if a 1 is received
        {
          uVar5 = uVar5 | 1;                            //If so add it to the byte being received
        }

        FUN_80017738(uVar3,3);                          //Set SCL low
        FUN_8000bc34(10);                               //Delay 10
        bVar2 = bVar2 + 1;                              //One more bit done
      } while (bVar2 < 8);                              //Read 8 bits

      FUN_8001764c(uVar3,2,1);                          //Set SDA as output
      *(char *)(param_2 + uVar6) = (char)uVar5;         //Put the byte in the receive buffer
      if (uVar6 == param_3 - 1)                         //Check if this was the last byte
      {
        FUN_8001764c(uVar3,2,1);                        //Set SDA as output
        FUN_8001764c(uVar3,3,1);                        //Set SCL as output
        FUN_8001774c(uVar3,2);                          //Set SDA high. Send a NACK
        FUN_8000bc34(10);                               //Delay 10
        FUN_80017738(uVar3,3);                          //Set SCL low
        FUN_8000bc34(10);                               //Delay 10
        FUN_8001774c(uVar3,3);                          //Set SCL high
        FUN_8000bc34(10);                               //Delay 10
        FUN_80017738(uVar3,3);                          //Set SCL low
        FUN_8000bc34(10);                               //Delay 10
      }
      else 
      {
        FUN_800099e4();                                 //Clock the acknowledge bit. Send ACK to indicate more bytes need to be received
      }

      uVar6 = uVar6 + 1 & 0xff;                         //Add one to the received byte count.
    } while (uVar6 < param_3);                          //Keep on reading bytes until done
  }

  FUN_8001764c(uVar3,3,1);                              //Set SCL as output
  FUN_8001764c(uVar3,2,1);                              //Set SDA as output
  FUN_80017738(uVar3,2);                                //Set SDA low
  FUN_8000bc34(10);                                     //Delay 10
  FUN_8001774c(uVar3,3);                                //Set SCL high
  FUN_8000bc34(10);                                     //Delay 10
  FUN_8001774c(uVar3,2);                                //Set SDA high. Send stop condition


  //This part is FUN_8000BC34, which is delay
  uVar3 = FUN_8003a370(10);                             //Delay 10
  FUN_8003a44c(uVar3,DAT_8000bcb4);
  uVar6 = FUN_8003a31c();
  uVar5 = 0;
  while (uVar5 < uVar6) {
    bVar1 = false;
    while (!bVar1) {
      bVar1 = true;
    }
    uVar5 = uVar5 + 1;
  }
  return;
}

