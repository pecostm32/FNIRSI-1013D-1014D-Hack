//--------------------------------------------------------------------------------

ushort calib_average_samples(ushort *buffer)

{
  ushort uVar1;
  ushort *puVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  
  uVar3 = (uint)buffer[10];     //Sample from buffer index 10
  uVar1 = buffer[0xb];          //Sample from buffer index 11
  iVar4 = 0;                    //0
  puVar2 = buffer + 10;         //Point to index 10 in the buffer
  iVar5 = DAT_8001b41c;         //0x000002DE  ==> 734 loops

  do
  {
    uVar3 = uVar3 + uVar1;           //Add the first two samples add the odd samples
    uVar1 = puVar2[3];               //Get sample  13, 15, 17  
    iVar5 = iVar5 + -1;              //one sample done
    iVar4 = iVar4 + (uint)puVar2[2]; //Add sample 12 to ivar4  add the even samples
    puVar2 = puVar2 + 2;             //skip two samples
  } while (iVar5 != 0);

  //Sum the samples and multiply with some big number and shift it down
  //                                                             1479                 0xB25449D7
  return (ushort)(uint)((ulonglong)(uVar3 + iVar4 + (uint)buffer[0x5c7]) * (ulonglong)DAT_8001b420 >> 0x2a);

  //Sum of samples times 2991868375 >> 42
  //Equals to sum / 1470
}

//--------------------------------------------------------------------------------

