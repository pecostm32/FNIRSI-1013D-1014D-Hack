//Function to determine a command to send to the fpga
//But also used to get the brightness setting

//Think this is used to communicate with the I2C chip connected to the FPGA


//For brightness this function is called with 0x10 and data from memory location 0x8036137A. Most likely the current value of the brightness

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
    FUN_80024ee0(param_1,param_2);    //Write parameters to fpga I2C bus
    FUN_8000bc34(500);                //Delay
    bVar6 = 0;

    do
    {
      FUN_8000bc34(100);              //Delay
      pcVar4 = DAT_80024b10;          //0x8035EC04. Some buffer in DRAM
      FUN_800169f8(0x64);             //Write command 0x64 twice to fpga. Prepare I2C read sequence
      FUN_800169f8(0x64);
      FUN_8000bc34(0x14);             //Delay
      FUN_800169f8(0x66);             //Write command 0x66. Start the sequence

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

      FUN_80024b14();                 //Do something with the data. Xor the data with the inverse of the first byte.

      *puVar2 = *pcVar3;              //Set the inversed byte received from command 0x68 in the global variable 0x80192eea

      if (pcVar3[1] == 0x55)          //Check the byte received from command 0x69 on how many bytes need to be returned to the caller
      {
        //When it is 0x55 only use the LSB
        uVar8 = (uint)(byte)pcVar3[6];
      }
      else 
      {
        if (pcVar3[1] == 0x5A)
        {
          //When it is 0x5A return the last two  bytes
          uVar8 = (uint)CONCAT11(pcVar3[5],pcVar3[6]);
        }
        else 
        {
          if (pcVar3[1] == 0xA5)
          {
            //When it is 0xA5 return 24 bits
            uVar8 = (uint)CONCAT21(CONCAT11(pcVar3[4],pcVar3[5]),pcVar3[6]);
          }
          else
          {
            if (pcVar3[1] == 0xAA)
            {
              //When it is 0xAA return 32 bits
              uVar8 = CONCAT31(CONCAT21(CONCAT11(pcVar3[3],pcVar3[4]),pcVar3[5]),pcVar3[6]);
            }
            else 
            {
              //Otherwise use 0
              uVar8 = 0;
            }
          }
        }
      }

      cVar5 = pcVar3[1];
      bVar1 = true;

      //Check if the type specifier is set correctly
      if ((cVar5 != 0x55 && cVar5 != 0x5A) && (cVar5 != 0xA5 && cVar5 != 0xAA))
      {
        //False if not
        bVar1 = false;
      }

      //Check the checksum received in byte 2 with the sum of the other 6 bytes, and if a correct type has been specified
      if (((char)(*pcVar3 + pcVar3[1] + pcVar3[3] + pcVar3[4] + pcVar3[5] + pcVar3[6]) == pcVar3[2]) && (bVar1))
      {
        //Return the received result if so
        return uVar8;
      }

      //Otherwhise repeat the receive process
      bVar6 = bVar6 + 1;
    } while (bVar6 < 0x32);             //Do the above at max 50 times

    FUN_8000bc34(10);                   //Delay

    //When still no valid result try writing again
    bVar7 = bVar7 + 1;

    if (5 < bVar7)                      //Exit when bVar7 == 6
    {
      return uVar8;                     //Return the parameter read from the I2C chip, which at this point is invalid
    }

  } while( true );                      //Repeat the above at max 6 times
}

