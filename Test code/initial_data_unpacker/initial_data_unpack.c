#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Initialization_data.h"

typedef unsigned char uchar;
typedef unsigned int  uint;

void do_some_initial_byte_handling(uchar *source,uchar *dest,uint count);


int main(int argc, char** argv)
{
  uchar dest[65536];
  
  do_some_initial_byte_handling(hexData, dest, 42756);
  
  FILE *fp = fopen("initial_scope_data.bin", "wb");
  
  if(fp)
  {
    fwrite(dest, 1, 42756, fp);
    
    fclose(fp);
  }
  
  
}

//Code from Ghidra with small mod to make it work
void do_some_initial_byte_handling(uchar *source,uchar *dest,uint count)
{
  uchar bVar1;
  uchar *pbVar2;
  uchar *pbVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  
  pbVar3 = dest + count;

  do
  {
    uVar4 = (uint)*source;
    pbVar2 = source + 1;
    uVar5 = uVar4 & 7;

    if ((*source & 7) == 0)
    {
      uVar5 = (uint)*pbVar2;
      pbVar2 = source + 2;
    }

    uVar6 = (int)uVar4 >> 4;
    source = pbVar2;

    if (uVar6 == 0) 
    {
      uVar6 = (uint)*pbVar2;
      source = pbVar2 + 1;
    }

    while (uVar5 = uVar5 - 1, uVar5 != 0)
    {
      *dest = *source;
      dest = dest + 1;
      source = source + 1;
    }

    if ((int)(uVar4 << 0x1c) < 0)
    {
      bVar1 = *source;
      source = source + 1;
      pbVar2 = dest - bVar1;
      iVar7 = uVar6 + 1;

      do
      {
        bVar1 = *pbVar2;
        pbVar2 = pbVar2 + 1;
        *dest = bVar1;
        dest = dest + 1;
        iVar7 = iVar7 - 1;
      } while (-1 < iVar7);
    }
    else
    {
      uVar5 = uVar6;

      if (uVar6 != 0)
      {
        do
        {
          uVar5 = uVar5 - 1;
          dest[uVar5] = 0;
        } while (uVar5 != 0);

        dest = dest + uVar6;
      }
    }
  } while (dest < pbVar3);
  return;
}

