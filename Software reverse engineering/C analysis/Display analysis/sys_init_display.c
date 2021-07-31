//Rewrite to readable C and identify the memory used and try to find the functions that make use of that

//0x8019CF60 ==> 0x803849A0 == video memory. Write here to display stuff. Two bytes per pixel, 800 pixels per row. 5 bits red, 6 bits green, 5 bits blue.
//0x8019CF64 ==> 0x805B71B8 == display info structure. Holds settings for the display.

//0x803847A0 ?? Address used for data concerning the video system

//0x8036B7A0 ?? also for the video system

//0x804FB9B4 seems also te be used for screen memory. Might be that it is used to setup a screen and that with a single function it is copied to the actual screen

//0x805B7228 yet another screen buffer?? Looks like the screen is copied to this location
//This address is only used three times in the code
//In function FUN_80022DD4 it is cleared based on an input setting

//In FUN_80022BC8 it is used twice. A) used as input to function FUN_8001D4EC. B) get the screen memory copied in it.


//0x804401B4 is also used as some screen buffer. It is used in 7 functions.

void sys_init_display(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  uint *puVar6;
  int iVar7;
  int *piVar8;
  
  puVar5 = PORT_D_CFG0;
  iVar7 = 0;
  *DAT_8001d628 = DAT_8001d624;             //0x8019CF60  = 0x803849A0

  do {
    gpio_config_pin(puVar5,iVar7,2);        //Setup port D0:21 pins for LCD
    uVar4 = DAT_8001d624;
    iVar3 = DAT_800164e0;
    iVar2 = DAT_800164dc;
    iVar1 = DEBE_BASE;
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x16);


 //Function jumps into FUN_800163CC init_debe() r0=0x320 == 800, r1=0x1E0 == 480, r2=0x803849A0, r3=0x803849A0

  iVar7 = DEBE_BASE + -0x254000;                       //0x01E60000 - 0x254000

  piVar8 = (int *)(DAT_800164e0 + 8);                  //0x805B71B8 + 8

  *(int *)(DAT_800164dc + 4) = DAT_800164e0;           //(0x8019CF60 + 4) = 0x805B71B8

  *piVar8 = iVar1;

  *(undefined4 *)(iVar3 + 0xc) = 0;
  *(int *)(iVar3 + 0x10) = iVar7;
  *(undefined4 *)(iVar3 + 0x1c) = 800;
  *(undefined4 *)(iVar3 + 0x20) = 0x1e0;
  *(undefined4 *)(iVar3 + 0x2c) = 0x10;
  *(undefined4 *)(iVar3 + 0x4c) = 0x14;
  *(undefined4 *)(iVar3 + 0x50) = 0x16;
  *(undefined4 *)(iVar3 + 0x58) = 10;
  *(undefined4 *)(iVar3 + 0x5c) = 0;
  *(undefined4 *)(iVar3 + 0x18) = 1;
  *(undefined4 *)(iVar3 + 0x54) = 0x17;
  *(undefined4 *)(iVar3 + 0x44) = 0xd2;
  *(undefined4 *)(iVar3 + 0x48) = 0x2e;
  *(undefined4 *)(iVar3 + 0x14) = 0;
  *(undefined4 *)(iVar3 + 0x60) = 0;
  *(undefined4 *)(iVar3 + 100) = 1;
  *(undefined4 *)(iVar3 + 0x68) = 0;
  *(undefined4 *)(iVar3 + 0x30) = 2;
  *(undefined4 *)(iVar3 + 0x34) = 0;
  *(undefined4 *)(iVar3 + 0x38) = uVar4;
  iVar7 = 0x800;
  *(undefined4 *)(iVar3 + 0x3c) = 0;

  do
  {
    *(undefined4 *)(DEBE_BASE + iVar7) = 0;
    iVar7 = iVar7 + 4;
  } while (iVar7 < 0x1000);

  puVar5 = *(undefined4 **)(iVar3 + 0x10);
  *puVar5 = 0;
  puVar5[1] = 0;
  puVar5[0x11] = puVar5[0x11] & 0xfffffff;
  puVar5[0x23] = 0xffffffff;
  puVar5[0x3d] = 0xffffffff;

  debe_enable(*(uint *)(iVar2 + 4));

  init_video_clock(*(uint *)(iVar2 + 4));

  puVar6 = *(uint **)(*(int *)(iVar2 + 4) + 0x10);
  *puVar6 = *puVar6 | 0x80000000;
  return;
}

//---------------------------------------------------------------------------------------------------------
//Only jumped to from sys_init_display and as such by Ghidra integrated in that function

void init_debe(ushort xsize,ushort ysize,uint address)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  uint *puVar4;
  int iVar5;
  int iVar6;
  int *piVar7;
  
  iVar2 = DAT_800164e0;                            //0x805B71B8        Base address of struct in memory
  iVar1 = DAT_800164dc;                            //0x8019CF60        Base address of struct in memory
  iVar6 = DEBE_BASE;                               //0x01E60000        DEBE register base
  iVar5 = DEBE_BASE - 0x254000;                    //0x01C0C000        TCON register base


  piVar7 = (int *)(DAT_800164e0 + 8);              //0x805B71B8 + 8

  *(int *)(DAT_800164dc + 4) = DAT_800164e0;       //0x8019CF60 + 4 = 0x805B71B8

  *piVar7 = iVar6;                                 //0x805B71C0 = 0x01E60000

  *(undefined4 *)(iVar2 + 0xc) = 0;                //0x805B71B8 + 0x0C = 0
  *(int *)(iVar2 + 0x10) = iVar5;                  //0x805B71B8 + 0x10 = 0x01C0C000
  *(uint *)(iVar2 + 0x1c) = (uint)xsize;           //0x805B71B8 + 0x1C = xsize
  *(uint *)(iVar2 + 0x20) = (uint)ysize;           //0x805B71B8 + 0x20 = ysize
  *(undefined4 *)(iVar2 + 0x2c) = 0x10;
  *(undefined4 *)(iVar2 + 0x4c) = 0x14;
  *(undefined4 *)(iVar2 + 0x50) = 0x16;
  *(undefined4 *)(iVar2 + 0x58) = 10;
  *(undefined4 *)(iVar2 + 0x5c) = 0;
  *(undefined4 *)(iVar2 + 0x18) = 1;
  *(undefined4 *)(iVar2 + 0x54) = 0x17;
  *(undefined4 *)(iVar2 + 0x44) = 0xd2;
  *(undefined4 *)(iVar2 + 0x48) = 0x2e;
  *(undefined4 *)(iVar2 + 0x14) = 0;
  *(undefined4 *)(iVar2 + 0x60) = 0;
  *(undefined4 *)(iVar2 + 0x64) = 1;
  *(undefined4 *)(iVar2 + 0x68) = 0;
  *(undefined4 *)(iVar2 + 0x30) = 2;
  *(undefined4 *)(iVar2 + 0x34) = 0;
  *(uint *)(iVar2 + 0x38) = address;
  *(undefined4 *)(iVar2 + 0x3c) = 0;

  iVar6 = 0x800;
  do {
    *(undefined4 *)(DEBE_BASE + iVar6) = 0;
    iVar6 = iVar6 + 4;
  } while (iVar6 < 0x1000);

  puVar3 = *(undefined4 **)(iVar2 + 0x10);          //puVar3 = 0x01C0C000. TCON

  *puVar3 = 0;                                      //TCON_CTRL = 0;

  puVar3[1] = 0;                                    //TCON_INT0 = 0;

  puVar3[0x11] = puVar3[0x11] & 0xfffffff;          //TCON_CLK_CTRL |= 0x0FFFFFFF;

  puVar3[0x23] = 0xffffffff;                        //TCON0_IO_CTRL1 = 0xFFFFFFFF;
  puVar3[0x3d] = 0xffffffff;                        //TCON1_IO_CTRL1 = 0xFFFFFFFF;

  debe_enable(*(uint *)(iVar1 + 4));                //Pointer to struct 0x805B71B8
  init_video_clock(*(uint *)(iVar1 + 4));

  puVar4 = *(uint **)(*(int *)(iVar1 + 4) + 0x10);
  *puVar4 = *puVar4 | 0x80000000;                   //  *TCON_CTRL |= TCON_CTRL_MODULE_EN;
  return;
}


//---------------------------------------------------------------------------------------------------------

void debe_enable(uint addr)

{
  uint *puVar1;
  int iVar2;
  
  puVar1 = BUS_CLK_GATING_REG1;

  iVar2 = *(int *)(addr + 8);

  *BUS_CLK_GATING_REG1 = *BUS_CLK_GATING_REG1 | 0x1000;           //  *CCU_BUS_CLK_GATE1 |= CCU_BCGR1_DEBE_EN;

  puVar1[0x98] = puVar1[0x98] | 0x1000;                           //  *CCU_BUS_SOFT_RST1 |= CCU_BSRR1_DEBE_RST;


  delay_2(1);

  puVar1 = (uint *)(iVar2 + 0x800);                               //0x01E60000 DEBE_BASE

  *(uint *)(iVar2 + 0x800) = *(uint *)(iVar2 + 0x800) | 1;        //  *DEBE_MODE_CTRL |= DEBE_MODE_CTRL_EN;


  *(uint *)(iVar2 + 0x808) = *(int *)(addr + 0x1c) - 1U | (*(ushort *)(addr + 0x20) - 1) * 0x10000;   //   *DEBE_LAY_SIZE  = ((xsize - 1) & 0x07FF) | (((ysize - 1) & 0x07FF) << 16);
  *(uint *)(iVar2 + 0x810) = *(int *)(addr + 0x1c) - 1U | (*(ushort *)(addr + 0x20) - 1) * 0x10000;   //   *DEBE_LAY0_SIZE = *DEBE_LAY_SIZE;

  *(int *)(iVar2 + 0x840) = *(int *)(addr + 0x1c) << 4;           //  *DEBE_LAY0_LINEWIDTH = xsize * 16;

  *(int *)(iVar2 + 0x850) = *(int *)(addr + 0x38) << 3;           //  *DEBE_LAY0_FB_ADDR1 = address << 3;
  *(uint *)(iVar2 + 0x860) = *(uint *)(addr + 0x38) >> 0x1d;      //  *DEBE_LAY0_FB_ADDR2 = address >> 29;

  *(undefined4 *)(iVar2 + 0x8a0) = 0x500;                         //  *DEBE_LAY0_ATT_CTRL1 = DEBE_LAY0_ATT_CTRL1_RGB565;

  *puVar1 = *puVar1 | 0x100;                                      //  *DEBE_MODE_CTRL |= DEBE_MODE_CTRL_LAYER0_EN;

  *(uint *)(iVar2 + 0x870) = *(uint *)(iVar2 + 0x870) | 1;        //  *DEBE_REGBUFF_CTRL |= DEBE_REGBUFF_CTRL_LOAD;

  *puVar1 = *puVar1 | 2;                                          //  *DEBE_MODE_CTRL |= DEBE_MODE_CTRL_START;
  return;
}

//---------------------------------------------------------------------------------------------------------

void init_video_clock(uint addr)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint *puVar4;
  
  puVar3 = PLL_VIDEO_CTRL_REG;
  puVar4 = *(uint **)(addr + 0x10);

  *PLL_VIDEO_CTRL_REG = *PLL_VIDEO_CTRL_REG & 0x7fffffff;
  *puVar3 = DAT_80028328;             //0x03004003
  *puVar3 = *puVar3 | 0x80000000;                                      //  *CCU_PLL_VIDEO_CTRL = CCU_PLL_ENABLE | CCU_PLL_VIDEO_MODE_SEL_INT | CCU_PLL_VIDEO_FACTOR_N(65) | CCU_PLL_VIDEO_PREDIV_M(4);

  delay_2(1);


  puVar3 = BUS_CLK_GATING_REG1;
  *BUS_CLK_GATING_REG1 = *BUS_CLK_GATING_REG1 | 0x10;                  //  *CCU_BUS_CLK_GATE1 |= CCU_BCGR1_LCD_EN;

  puVar2 = puVar3 + 0x2d;
  *puVar2 = *puVar2 | 0x80000000;                                      //  *CCU_LCD_CLK |= CCU_LCD_CLK_EN;

  puVar3 = puVar3 + 0x98;
  *puVar3 = *puVar3 | 0x10;                                            //  *CCU_BUS_SOFT_RST1 |= CCU_BSRR1_LCD_RST;

  delay_2(1);

  *puVar4 = *puVar4 & 0xfffffffe;                                      //  *TCON_CTRL &= TCON_CTRL_IO_MAP_SEL_TCON0;

//                                       0x16  +                        0x17  +                        0x0A
  puVar4[0x10] = ((uint)*(byte *)(addr + 0x50) + (uint)*(byte *)(addr + 0x54) + (uint)*(byte *)(addr + 0x58) & 0x1f) << 4 | 0x80000000;   //  *TCON0_CTRL = 0x80000170;

  puVar4[0x11] = 0xf0000006;                                           //  *TCON_CLK_CTRL = 0xF0000006;

  puVar4[0x12] = *(int *)(addr + 0x20) - 1U | (*(ushort *)(addr + 0x1c) - 1) * 0x10000;  //  *TCON0_BASIC_TIMING0  = ((ysize - 1) & 0x07FF) | (((xsize - 1) & 0x07FF) << 16);

  puVar4[0x13] = DAT_80028330;  //0x041E004A      *TCON0_BASIC_TIMING1 = 0x41E0044; //There is a difference here?? Horizontal Back Porch

  puVar4[0x14] = DAT_80028334;  //0x041A0017      *TCON0_BASIC_TIMING2 = 0x41A0017;

  puVar4[0x15] = 0x160000;                    //  *TCON0_BASIC_TIMING3 = 0x160000;
  puVar4[0x16] = 0;                           //  *TCON0_HV_TIMING = 0;
  puVar4[0x18] = 0;                           //  *TCON0_CPU_IF = 0;

  uVar1 = 0x10000000;

  if (*(int *)(addr + 0x5c) == 0) // = 0
  {
    uVar1 = 0x12000000;
  }

  if (*(int *)(addr + 0x60) == 0) // = 0
  {
    uVar1 = uVar1 | 0x1000000;
  }

  if (*(int *)(addr + 0x64) == 0) // = 1
  {
    uVar1 = uVar1 | 0x8000000;
  }

  if (*(int *)(addr + 0x68) == 0) // = 0
  {
    uVar1 = uVar1 | 0x4000000;
  }

  puVar4[0x22] = uVar1;  // 0x12000000 | 0x1000000 | 0x4000000    *TCON0_IO_CTRL0 = 0x17000000;

  puVar4[0x23] = 0;             //                                *TCON0_IO_CTRL1 = 0;

  return;
}


