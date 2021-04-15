//Function to send a single byte on the i2c bus

//param_1 ==> byte to be send

void FUN_80039144(uint param_1)
{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  byte bVar4;
  uint uStack24;
  
  uVar2 = DAT_800391ec;                      //0x01C20800
  FUN_8001764c(DAT_800391ec,2,1);            //Setup SDA (PA2) as output
  FUN_8001764c(uVar2,3,1);                   //Setup SCL (PA3) as output
  bVar4 = 0;

  do
  {
    if ((param_1 & 0x80) == 0)               //Check on current MSB
    {
      FUN_80017738(uVar2,2);                 //Set SDA low
    }
    else
    {
      FUN_8001774c(uVar2,2);                 //Set SDA high
    }

    FUN_8000bc34(10);                        //Delay  10 (~1,25uS per tick)
    FUN_8001774c(uVar2,3);                   //Set SCL high
    FUN_8000bc34(10);                        //Delay 10
    FUN_80017738(uVar2,3);                   //Set SCL low
    FUN_8000bc34(10);                        //Delay 10
    bVar4 = bVar4 + 1;                       //Done one bit
    param_1 = (param_1 << 0x19) >> 0x18;     //Shift left one position
  } while (bVar4 < 8);                       //Send 8 bits

  //This part is FUN_8000BC34, which is delay
  uVar2 = FUN_8003a370(10);                  //Delay  10
  FUN_8003a44c(uVar2,DAT_8000bcb4);
  uVar3 = FUN_8003a31c();
  uStack24 = 0;
  while (uStack24 < uVar3) {
    bVar1 = false;
    while (!bVar1) {
      bVar1 = true;
    }
    uStack24 = uStack24 + 1;
  }
  return;
}

//Function returns with both SCL and SDA as output.
//SCL == low
//SDA == x  (depends on last bit send)

