//Initialization function based on input parameters

//param_1
//param_2

void FUN_80024ee0(int param_1,uint param_2)
{
  char cVar1;
  char cVar2;
  char cVar3;
  char *pcVar4;
  byte bVar5;
  uint uVar6;
  
  pcVar4 = DAT_80025094;               //0x8035EC04. pcVar4 = pointer to data in DRAM
  *DAT_80025094 = *PTR_DAT_80025098;   //*0x8035EC04 = *0x80192eea (0x09)

  pcVar4[1] = (char)(param_1 << 2);
  cVar3 = (char)param_2;
  bVar5 = 0;
  cVar1 = (char)((param_2 << 8) >> 0x18);
  cVar2 = (char)((param_2 << 0x10) >> 0x18);

  if (param_2 < 0x1000000)
  {
    if (param_2 < 0x10000)
    {
      if (param_2 < 0x100)
      {
        pcVar4[3] = 'i';
        pcVar4[4] = -0x6a;
        pcVar4[5] = -0x67;
        pcVar4[6] = cVar3;
      }
      else
      {
        pcVar4[3] = 'i';
        bVar5 = 1;
        pcVar4[4] = -0x6a;
        pcVar4[5] = cVar2;
        pcVar4[6] = cVar3;
      }
    }
    else
    {
      bVar5 = 2;
      pcVar4[3] = 'i';
      pcVar4[4] = cVar1;
      pcVar4[5] = cVar2;
      pcVar4[6] = cVar3;
    }
  }
  else
  {
    bVar5 = 3;
    pcVar4[3] = (char)(param_2 >> 0x18);
    pcVar4[4] = cVar1;
    pcVar4[5] = cVar2;
    pcVar4[6] = cVar3;
  }

  pcVar4[1] = bVar5 | pcVar4[1];
  FUN_80024c7c();                   //Do something with data in 0x8035EC04 (pcVar4) buffer in DRAM

  pcVar4[2] = pcVar4[6] + pcVar4[3] + pcVar4[4] + pcVar4[1] + *pcVar4 + pcVar4[5];

  FUN_800169f8(0x65);              //Send command 0x65
  FUN_800169f8(0x65);              //Send command 0x65

  cVar1 = pcVar4[0];
  FUN_800169f8(0x68);              //Send command 0x68
  FUN_800168fc(cVar1);             //Write data byte

  cVar1 = pcVar4[1];
  FUN_800169f8(0x69);              //Send command 0x69
  FUN_800168fc(cVar1);

  cVar1 = pcVar4[2];
  FUN_800169f8(0x6a);              //Send command 0x6A
  FUN_800168fc(cVar1);

  cVar1 = pcVar4[3];
  FUN_800169f8(0x6b);              //Send command 0x6B
  FUN_800168fc(cVar1);

  cVar1 = pcVar4[4];
  FUN_800169f8(0x6c);              //Send command 0x6C
  FUN_800168fc(cVar1);

  cVar1 = pcVar4[5];
  FUN_800169f8(0x6d);              //Send command 0x6D
  FUN_800168fc(cVar1);

  cVar1 = pcVar4[6];
  FUN_800169f8(0x6e);              //Send command 0x6E
  FUN_800168fc(cVar1);

  FUN_800169f8(0x66);              //Send command 0x66

  do 
  {
    FUN_800169f8(0x67);            //Send command 0x67
    uVar6 = FUN_80016850();        //Read byte from fpga
  } while ((uVar6 & 1) == 0);      //Wait till fpga ready
  return;
}

