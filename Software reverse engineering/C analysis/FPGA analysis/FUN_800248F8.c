//Function to determine a command to send to the fpga and do some initialization of the fpga

uint FUN_800248f8(undefined4 param_1,undefined4 param_2)
{
  bool bVar1;
  undefined *puVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  byte bVar6;
  byte bVar7;
  uint uVar8;
  
  pcVar3 = DAT_80024b10;              //0x8035EC04. Some buffer in DRAM that holds 7 fpga configuration parameters
  puVar2 = PTR_DAT_80024b0c;          //0x80192eea. Some data from ROM in DRAM
  bVar7 = 0;
  do
  {
    FUN_80024ee0(param_1,param_2);    //Write configuration parameters to fpga
    FUN_8000bc34(500);                //Delay
    bVar6 = 0;

    do
    {
      FUN_8000bc34(100);              //Delay
      pcVar4 = DAT_80024b10;          //0x8035EC04. Some buffer in DRAM
      FUN_800169f8(0x64);             //Write command 0x64 twice to fpga
      FUN_800169f8(0x64);
      FUN_8000bc34(0x14);             //Delay
      FUN_800169f8(0x66);             //Write command 0x66

      do 
      {
        FUN_800169f8(0x67);           //Write command 0x67
        uVar8 = FUN_80016850();       //Read data byte
      } while ((uVar8 & 1) == 0);     //Wait until FPGA ready

      FUN_800169f8(0x68);             //Write command 0x68
      cVar5 = FUN_80016850();         //Read configuration byte
      pcVar4[0] = cVar5;

      FUN_800169f8(0x69);             //Write command 0x69
      cVar5 = FUN_80016850();         //Read configuration byte
      pcVar4[1] = cVar5;

      FUN_800169f8(0x6a);             //Write command 0x6A
      cVar5 = FUN_80016850();         //Read configuration byte
      pcVar4[2] = cVar5;

      FUN_800169f8(0x6b);             //Write command 0x6B
      cVar5 = FUN_80016850();         //Read configuration byte
      pcVar4[3] = cVar5;

      FUN_800169f8(0x6c);             //Write command 0x6C
      cVar5 = FUN_80016850();         //Read configuration byte
      pcVar4[4] = cVar5;

      FUN_800169f8(0x6d);             //Write command 0x6D
      cVar5 = FUN_80016850();         //Read configuration byte
      pcVar4[5] = cVar5;

      FUN_800169f8(0x6e);             //Write command 0x6E
      cVar5 = FUN_80016850();         //Read configuration byte
      pcVar4[6] = cVar5;

      FUN_80024b14();                 //Do something with the data

      *puVar2 = *pcVar3;
      if (pcVar3[1] == 'U')
      {
        uVar8 = (uint)(byte)pcVar3[6];
      }
      else 
      {
        if (pcVar3[1] == 'Z')
        {
          uVar8 = (uint)CONCAT11(pcVar3[5],pcVar3[6]);
        }
        else 
        {
          if (pcVar3[1] == -0x5b)
          {
            uVar8 = (uint)CONCAT21(CONCAT11(pcVar3[4],pcVar3[5]),pcVar3[6]);
          }
          else
          {
            if (pcVar3[1] == -0x56)
            {
              uVar8 = CONCAT31(CONCAT21(CONCAT11(pcVar3[3],pcVar3[4]),pcVar3[5]),pcVar3[6]);
            }
            else 
            {
              uVar8 = 0;
            }
          }
        }
      }

      cVar5 = pcVar3[1];
      bVar1 = true;

      if ((cVar5 != 'U' && cVar5 != 'Z') && (cVar5 != -0x5b && cVar5 != -0x56))
      {
        bVar1 = false;
      }

      if (((char)(*pcVar3 + pcVar3[1] + pcVar3[3] + pcVar3[4] + pcVar3[5] + pcVar3[6]) == pcVar3[2]) && (bVar1))
      {
        return uVar8;
      }

      bVar6 = bVar6 + 1;
    } while (bVar6 < 0x32);             //Do the above 50 times

    FUN_8000bc34(10);                   //Delay

    bVar7 = bVar7 + 1;

    if (5 < bVar7)                      //Exit when bVar7 == 6
    {
      return uVar8;                     //Return the command byte for the next 1500/750 bytes read session
    }

  } while( true );                      //Repeat the above 6 times
}

