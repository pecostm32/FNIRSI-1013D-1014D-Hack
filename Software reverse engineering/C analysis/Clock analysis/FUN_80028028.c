//Initialize clock system part
void FUN_80028028(void)
{
  undefined4 uVar1;
  uint *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  uint uVar5;
  
  puVar3 = DAT_80028090;                                     //0x01C20200  PLL Stable time register 0
  uVar1 = DAT_8002808c;                                      //0x000001FF
  *DAT_80028090 = DAT_8002808c;                              //Set PLL stable time register 0 with 0x01FF (PLL_LOCK_TIME)
  puVar3[1] = uVar1;                                         //Set PLL stable time register 1 with 0x01FF (PLL_CPU_LOCK_TIME)
  puVar3 = puVar3 - 0x1B0;                                   //Point to 0x01C20050. CPU clock source register
  *puVar3 = 0x20000;                                         //Set CPU clock source register with 0x20000. Mode 2. PLL_CPU as clock source

  //puVar3 = 0x01C20050
  //0x00012110 >> 14 = 4  (DAT_80028094 >> 0x0E)
  //0x01C20050 | 4 = 0x01C20054

  piVar4 = (int *)((uint)puVar3 | DAT_80028094 >> 0xe);      //piVar4 = 0x01C20054. AHB/APB/HCLKC config register
  *piVar4 = DAT_80028094;                                    //Set AHB/APB/HCLKC config register = 0x00012110.   HCLKC_DIV = /2, AHB_CLK_SRC_SEL = CPUCLK, APB_CLK_RATIO = /2, AHB_PRE_DIV = /1, AHB_CLK_DIV_RATIO = /2
                                                             //HCLKC = 300MHz
                                                             //AHB = 300MHz
                                                             //APB = 300MHz

  uVar5 = DAT_80028098;                                      //0xFFFCE0CC

  puVar2 = (uint *)(piVar4 - 0x54);                          //puVar2 = 0x01C20000. PLL_CPU control register

  *puVar2 = *puVar2 & DAT_80028098 | 0x80001800;             //Set PLL_CPU control register to 0x80001800. PLL enabled and 600MHz

  uVar5 = uVar5 >> 0x14;                                     //0xFFFCE0CC >> 0x14 = 0x0FFF

  do                                                         //Wait loop for PLL to become unlocked with escape if it does not get to it
  {
    uVar5 = uVar5 - 1;

    if (uVar5 == 0) 
    {
      return;
    }
  } while ((*puVar2 & 0x10000000) == 0);                     //Check on PLL locked flag

  return;
}

