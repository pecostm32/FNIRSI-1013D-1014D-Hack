//Initialization function based on input parameters

//param_1 ==> ID of parameter
//param_2 ==> Value of parameter

void FUN_80024ee0(int param_1,uint param_2)
{
  char cVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  byte bVar5;
  uint uVar6;
  
  pcVar4 = DAT_80025094;                       //0x8035EC04. pcVar4 = pointer to data in DRAM
  *DAT_80025094 = *PTR_DAT_80025098;           //*0x8035EC04 = *0x80192eea (0x09). pcVar4[0] = 0x09

  pcVar4[1] = (char)(param_1 << 2);            //param_1 = 0x10 for brightness. pcVar4[1] = 0x40
  cVar3 = (char)param_2;                       //?????
  bVar5 = 0;
  cVar1 = (char)((param_2 << 8) >> 0x18);      //????? param_2 >> 0x10
  cVar2 = (char)((param_2 << 0x10) >> 0x18);   //????? param_2 >> 0x08

  if (param_2 < 0x1000000)
  {
    if (param_2 < 0x10000)
    {
      if (param_2 < 0x100)
      {
        pcVar4[3] = 0x69;                      //1 byte parameter. msb = 0x69
        pcVar4[4] = 0x96;                      //0x96
        pcVar4[5] = 0x99;                      //0x99
        pcVar4[6] = cVar3;                     //param_2 lsb
      }
      else                                     //When param_2 >= 0x100
      {
        bVar5 = 1;                             //2 byte parameter
        pcVar4[3] = 0x69;                      //msb = 0x69
        pcVar4[4] = 0x96;                      //0x96
        pcVar4[5] = cVar2;                     //(>> 8)
        pcVar4[6] = cVar3;                     //param_2 lsb
      }
    }
    else                                       //When param_2 >= 0x10000
    {
      bVar5 = 2;                               //3 byte parameter
      pcVar4[3] = 0x69;                        //msb = 0x69
      pcVar4[4] = cVar1;                       //(>>16)
      pcVar4[5] = cVar2;                       //(>>8)
      pcVar4[6] = cVar3;                       //param_2 lsb
    }
  }
  else                                         //When param_2 >= 0x1000000
  {
    bVar5 = 3;                                 //4 byte parameter
    pcVar4[3] = (char)(param_2 >> 0x18);       //param_2 msb (>>24)
    pcVar4[4] = cVar1;                         //(>> 16)
    pcVar4[5] = cVar2;                         //(>> 8)
    pcVar4[6] = cVar3;                         //param_2 lsb
  }

  pcVar4[1] = bVar5 | pcVar4[1];               //Mix the number of bytes with the parameter id
  FUN_80024c7c();                              //Do something with data in 0x8035EC04 (pcVar4) buffer in DRAM

  //Calculate some checksum????
  pcVar4[2] = pcVar4[6] + pcVar4[3] + pcVar4[4] + pcVar4[1] + pcVar4[0] + pcVar4[5];

  FUN_800169f8(0x65);              //Send command 0x65
  FUN_800169f8(0x65);              //Send command 0x65

  cVar1 = pcVar4[0];
  FUN_800169f8(0x68);              //Send command 0x68
  FUN_800168fc(cVar1);             //Write data byte

  cVar1 = pcVar4[1];
  FUN_800169f8(0x69);              //Send command 0x69
  FUN_800168fc(cVar1);             //Write data byte

  cVar1 = pcVar4[2];
  FUN_800169f8(0x6a);              //Send command 0x6A
  FUN_800168fc(cVar1);             //Write data byte

  cVar1 = pcVar4[3];
  FUN_800169f8(0x6b);              //Send command 0x6B
  FUN_800168fc(cVar1);             //Write data byte

  cVar1 = pcVar4[4];
  FUN_800169f8(0x6c);              //Send command 0x6C
  FUN_800168fc(cVar1);             //Write data byte

  cVar1 = pcVar4[5];
  FUN_800169f8(0x6d);              //Send command 0x6D
  FUN_800168fc(cVar1);             //Write data byte

  cVar1 = pcVar4[6];
  FUN_800169f8(0x6e);              //Send command 0x6E
  FUN_800168fc(cVar1);             //Write data byte

  FUN_800169f8(0x66);              //Send command 0x66. Start I2C transmission

  do 
  {
    FUN_800169f8(0x67);            //Send command 0x67
    uVar6 = FUN_80016850();        //Read byte from fpga
  } while ((uVar6 & 1) == 0);      //Wait till fpga ready
  return;
}

