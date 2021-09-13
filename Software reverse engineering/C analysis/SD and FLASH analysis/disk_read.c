
int disk_read(int pdrv,byte *buff,int sector,uint count)

{
  uint *buffer;
  int iVar1;
  
  if (pdrv == 0)
  {
    if (((uint)buff & 3) == 0)
    {
      iVar1 = sd_card_read(0,sector,count,buff);

      if (iVar1 == 0)
      {
        return 0;
      }
    }
    else
    {
      buffer = malloc(count << 9);

      if (buffer != NULL)
      {
        iVar1 = sd_card_read(0,sector,count,(byte *)buffer);

        memcpy(buff,buffer,count << 9);

        free(buffer);

        return (uint)(iVar1 != 0);
      }
    }

    count = 1;
  }

  return count;
}


