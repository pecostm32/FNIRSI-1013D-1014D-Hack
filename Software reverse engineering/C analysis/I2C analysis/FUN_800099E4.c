//Is this a function to clock the acknowledge with SDA low, basically making it's own ACK

//SCL is low on entry
//SDA is dependend on last bit send

void FUN_800099e4(void)
{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uStack24;
  
  uVar2 = DAT_80009a68;                 //0x01C20800
  FUN_8001764c(DAT_80009a68,2,1);       //Setup SDA (PA2) as output
  FUN_8001764c(uVar2,3,1);              //Setup SCL (PA3) as output
  FUN_80017738(uVar2,2);                //Set SDA low
  FUN_8000bc34(10);                     //Delay 10
  FUN_80017738(uVar2,3);                //Set SCL low
  FUN_8000bc34(10);                     //Delay 10
  FUN_8001774c(uVar2,3);                //Set SCL high
  FUN_8000bc34(10);                     //Delay 10
  FUN_80017738(uVar2,3);                //Set SCL low

  //This part is FUN_8000BC34, which is delay
  uVar2 = FUN_8003a370(10);            //Delay 10
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
//SDA == low

