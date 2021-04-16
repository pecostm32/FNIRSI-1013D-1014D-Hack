//Function to send a start condition

void FUN_80009a6c(void)
{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  uint uStack24;
  
  uVar2 = DAT_80009af0;                      //0x01C20800
  FUN_8001764c(DAT_80009af0,3,1);            //Setup SCL (PA3) as output
  FUN_8001764c(uVar2,2,1);                   //Setup SDA (PA2) as output
  FUN_8001774c(uVar2,2);                     //Set SDA high.
  FUN_8000bc34(10);                          //Delay  10
  FUN_8001774c(uVar2,3);                     //Set SCL high
  FUN_8000bc34(10);                          //Delay  10
  FUN_80017738(uVar2,2);                     //Set SDA low. This is a start condition
  FUN_8000bc34(10);                          //Delay  10
  FUN_80017738(uVar2,3);                     //Set SCL low

  //This part is FUN_8000BC34, which is delay
  uVar2 = FUN_8003a370(10);                  //Delay 10
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

