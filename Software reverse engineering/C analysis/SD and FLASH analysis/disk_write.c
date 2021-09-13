//disk read????

uint disk_write(undefined4 param_1,void *param_2,undefined4 param_3,int param_4)

{
  uint *dest;
  int iVar1;
  uint unaff_r4;
  
  switch(param_1)
  {
  case 0:
    //buffer on a word boundry
    if (((uint)param_2 & 3) == 0)
    {
      iVar1 = FUN_80024730(0,param_3,param_4,param_2);

      if (iVar1 == 0)
      {
        return 0;
      }
    }
    else
    {
      //Get a very big buffer and copy the data into that??????
      dest = malloc(param_4 << 9);  //*512

      if (dest != (uint *)0x0)
      {
        memcpy(dest,param_2,param_4 << 9);

        iVar1 = FUN_80024730(0,param_3,param_4,dest);

        FUN_8000022e(dest);

        return (uint)(iVar1 != 0);
      }
    }

    unaff_r4 = 1;
    break;

  case 1:
  case 2:
  case 3:
  case 4:
    break;

  default:
    unaff_r4 = 4;
  }
  return unaff_r4;
}




int disk_write(int pdrv,byte *buff,int sector,uint count)

{
  uint *buffer;
  int iVar1;
  uint unaff_r4;
  
  switch(pdrv)
  {
  case 0:
    if (((uint)buff & 3) == 0) {
      iVar1 = sd_card_write(0,sector,count,buff);
      if (iVar1 == 0) {
        return 0;
      }
    }
    else {
      buffer = malloc(count << 9);
      if (buffer != NULL) {
        memcpy(buffer,buff,count << 9);
        iVar1 = sd_card_write(0,sector,count,(byte *)buffer);
        free(buffer);
        return (uint)(iVar1 != 0);
      }
    }
    unaff_r4 = 1;
    break;

  case 1:
  case 2:
  case 3:
  case 4:
    break;

  default:
    unaff_r4 = 4;
  }
  return unaff_r4;
}


