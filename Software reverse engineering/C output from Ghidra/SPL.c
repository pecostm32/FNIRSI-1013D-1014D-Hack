typedef unsigned char   undefined;

typedef unsigned char    uchar;
typedef unsigned int    uint;
typedef unsigned char    undefined1;
typedef unsigned int    undefined4;



void Reset(void)

{
  undefined *puVar1;
  uint uVar2;
  undefined4 uVar3;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  
  puVar1 = PTR_DAT_0000008c;
  uVar2 = coproc_movefrom_Control();
  coproc_moveto_Control(uVar2 & 0xffffdfff);
  uVar2 = coproc_movefrom_Control();
  puVar10 = (undefined4 *)PTR_H_Reset_00000090;
  if ((uVar2 & 0x2000) == 0) {
    puVar10 = (undefined4 *)0x0;
  }
  uVar3 = *(undefined4 *)(PTR_DAT_0000008c + 4);
  uVar4 = *(undefined4 *)(PTR_DAT_0000008c + 8);
  uVar5 = *(undefined4 *)(PTR_DAT_0000008c + 0xc);
  uVar6 = *(undefined4 *)(PTR_DAT_0000008c + 0x10);
  uVar7 = *(undefined4 *)(PTR_DAT_0000008c + 0x14);
  uVar8 = *(undefined4 *)(PTR_DAT_0000008c + 0x18);
  uVar9 = *(undefined4 *)(PTR_DAT_0000008c + 0x1c);
  puVar11 = (undefined4 *)(PTR_DAT_0000008c + 0x20);
  *puVar10 = *(undefined4 *)PTR_DAT_0000008c;
  puVar10[1] = uVar3;
  puVar10[2] = uVar4;
  puVar10[3] = uVar5;
  puVar10[4] = uVar6;
  puVar10[5] = uVar7;
  puVar10[6] = uVar8;
  puVar10[7] = uVar9;
  uVar3 = *(undefined4 *)(puVar1 + 0x24);
  uVar4 = *(undefined4 *)(puVar1 + 0x28);
  uVar5 = *(undefined4 *)(puVar1 + 0x2c);
  uVar6 = *(undefined4 *)(puVar1 + 0x30);
  uVar7 = *(undefined4 *)(puVar1 + 0x34);
  uVar8 = *(undefined4 *)(puVar1 + 0x38);
  uVar9 = *(undefined4 *)(puVar1 + 0x3c);
  puVar10[8] = *puVar11;
  puVar10[9] = uVar3;
  puVar10[10] = uVar4;
  puVar10[0xb] = uVar5;
  puVar10[0xc] = uVar6;
  puVar10[0xd] = uVar7;
  puVar10[0xe] = uVar8;
  puVar10[0xf] = uVar9;
  FUN_0000009c(puVar1 + 0x40,puVar10 + 0x10);
  FUN_0000010c();
  puVar1 = PTR_FUN_000000d0;
  puVar10 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar10 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar10,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



void FUN_0000009c(void)

{
  undefined *puVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined4 *puVar2;
  
  puVar1 = PTR_FUN_000000d0;
  puVar2 = (undefined4 *)(PTR_FUN_000000d0 + 0xd0);
  if (puVar2 == (undefined4 *)(DAT_000000d4 + 0xd0)) {
    FUN_0000010c();
  }
  UNRECOVERED_JUMPTABLE = *(code **)(puVar1 + 0xdc);
                    // WARNING: Could not recover jumptable at 0x000000c8. Too many branches
                    // WARNING: Treating indirect jump as call
  if (((uint)UNRECOVERED_JUMPTABLE & 1) != 0) {
    (*(code *)(puVar1 + (0xcf - (int)UNRECOVERED_JUMPTABLE)))();
    return;
  }
                    // WARNING: Could not recover jumptable at 0x000000cc. Too many branches
                    // WARNING: Treating indirect jump as call
  (*UNRECOVERED_JUMPTABLE)(*puVar2,*(undefined4 *)(puVar1 + 0xd4),*(undefined4 *)(puVar1 + 0xd8));
  return;
}



undefined8 FUN_00000104(undefined4 param_1,undefined4 param_2)

{
  return CONCAT44(param_2,param_1);
}



void FUN_00000108(void)

{
  return;
}



// WARNING: Control flow encountered bad instruction data

void FUN_0000010c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  undefined4 uVar1;
  
  uVar1 = FUN_00000768();
  FUN_00000104(uVar1,param_3);
  (*(code *)(DAT_0000013c + 0x124))();
  FUN_00002f38();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



void FUN_00000140(undefined4 param_1,undefined4 param_2)

{
  FUN_00000108();
  FUN_00000758(param_1,param_2);
  Config_GPIO_Pin(PORT_E_CFG,0,0);
  Config_GPIO_Pin(PORT_E_CFG,1,0);
  Config_GPIO_Pin(PORT_E_CFG,2,0);
  Config_GPIO_Pin(PORT_E_CFG,3,0);
  Config_GPIO_Pin(PORT_E_CFG,4,0);
  Config_GPIO_Pin(PORT_E_CFG,5,0);
  Config_GPIO_Pin(PORT_E_CFG,6,0);
  Config_GPIO_Pin(PORT_E_CFG,7,0);
  return;
}



void FPGA_Bus_Dir_In(void)

{
  Config_GPIO_Pin(PORT_E_CFG,0,0);
  Config_GPIO_Pin(PORT_E_CFG,1,0);
  Config_GPIO_Pin(PORT_E_CFG,2,0);
  Config_GPIO_Pin(PORT_E_CFG,3,0);
  Config_GPIO_Pin(PORT_E_CFG,4,0);
  Config_GPIO_Pin(PORT_E_CFG,5,0);
  Config_GPIO_Pin(PORT_E_CFG,6,0);
  Config_GPIO_Pin(PORT_E_CFG,7,0);
  return;
}



void FPGA_Bus_Dir_Out(void)

{
  Config_GPIO_Pin(PORT_E_CFG,0,1);
  Config_GPIO_Pin(PORT_E_CFG,1,1);
  Config_GPIO_Pin(PORT_E_CFG,2,1);
  Config_GPIO_Pin(PORT_E_CFG,3,1);
  Config_GPIO_Pin(PORT_E_CFG,4,1);
  Config_GPIO_Pin(PORT_E_CFG,5,1);
  Config_GPIO_Pin(PORT_E_CFG,6,1);
  Config_GPIO_Pin(PORT_E_CFG,7,1);
  return;
}



void FPGA_Ctrl_Init(void)

{
  Config_GPIO_Pin(PORT_E_CFG,9,1);
  Config_GPIO_Pin(PORT_E_CFG,10,1);
  Config_GPIO_Pin(PORT_E_CFG,8,1);
  Set_GPIO_Pin_High(PORT_E_CFG,8);
  FPGA_Bus_Dir_In();
  return;
}



uchar FPGA_Read_Data(void)

{
  FPGA_Bus_Dir_In();
  Set_GPIO_Pin_Low(PORT_E_CFG,9);
  Set_GPIO_Pin_Low(PORT_E_CFG,10);
  Set_GPIO_Pin_Low(PORT_E_CFG,8);
  Set_GPIO_Pin_High(PORT_E_CFG,8);
  return (uchar)*PORT_E_DATA;
}



uchar FPGA_Read_Command(void)

{
  FPGA_Bus_Dir_In();
  Set_GPIO_Pin_Low(PORT_E_CFG,9);
  Set_GPIO_Pin_High(PORT_E_CFG,10);
  Set_GPIO_Pin_Low(PORT_E_CFG,8);
  Set_GPIO_Pin_High(PORT_E_CFG,8);
  return (uchar)*PORT_E_DATA;
}



void FPGA_Write_Data(uchar data)

{
  FPGA_Bus_Dir_Out();
  Set_GPIO_Pin_High(PORT_E_CFG,9);
  Set_GPIO_Pin_Low(PORT_E_CFG,10);
  *PORT_E_DATA = *PORT_E_DATA & 0xffffff00 | (uint)data;
  Set_GPIO_Pin_Low(PORT_E_CFG,8);
  Set_GPIO_Pin_High(PORT_E_CFG,8);
  return;
}



void FPGA_Write_Command(uchar data)

{
  FPGA_Bus_Dir_Out();
  Set_GPIO_Pin_High(PORT_E_CFG,9);
  Set_GPIO_Pin_High(PORT_E_CFG,10);
  *PORT_E_DATA = *PORT_E_DATA & 0xffffff00 | (uint)data;
  Set_GPIO_Pin_Low(PORT_E_CFG,8);
  Set_GPIO_Pin_High(PORT_E_CFG,8);
  return;
}



void Set_Default_Brightness(void)

{
  FPGA_Write_Command('8');
  FPGA_Write_Data(-0x16);
  FPGA_Write_Data((uchar)DAT_0000072c);
  return;
}



void FPGA_Init(void)

{
  FPGA_Ctrl_Init();
  return;
}



void display_bitmap(uint xpos,uint ypos,uint xsize,uint ysize,uint *source)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = 0;
  while (iVar2 < (int)ysize) {
    iVar3 = *(int *)PTR_DAT_00000730;
    iVar1 = 0;
    while (iVar1 < (int)xsize) {
      *(undefined2 *)(iVar3 + (ypos + iVar2) * 0x640 + xpos * 2 + iVar1 * 2) = *(undefined2 *)source
      ;
      iVar1 = iVar1 + 1;
      source = (uint *)((int)source + 2);
    }
    iVar2 = iVar2 + 1;
  }
  return;
}



// WARNING: Globals starting with '_' overlap smaller symbols at the same address

void main(void)

{
  int iVar1;
  undefined auStack48 [4];
  char acStack44 [12];
  byte local_20;
  byte local_1f;
  byte local_1e;
  byte local_1d;
  ushort local_16;
  ushort local_14;
  undefined4 local_10;
  undefined4 uStack12;
  undefined4 local_8;
  undefined4 uStack4;
  
  local_8 = s_eGON_BMPeGON_EXE_00000734._0_4_;
  uStack4 = s_eGON_BMPeGON_EXE_00000734._4_4_;
  local_10 = s_eGON_BMPeGON_EXE_00000734._8_4_;
  uStack12 = s_eGON_BMPeGON_EXE_00000734._12_4_;
  sys_dram_init();
  sys_clock_init();
  sys_spi_flash_init();
  UART0_Init();
  sys_spi_flash_read(0x13000,auStack48,0x20);
  sys_spi_flash_read(iRam00000748,(void *)0x81000000,
                     ((uint)local_1d << 0x18 | (uint)local_1e << 0x10 | (uint)local_1f << 8 |
                     (uint)local_20) - 0x28);
  delay(0x4b0);
  FPGA_Init();
  *(undefined4 *)PTR_DAT_00000730 = 0x81b00000;
  iVar1 = iRam0000074c;
  while (-1 < iVar1) {
    *(undefined4 *)(iVar1 * 4 + -0x7e500000) = 0;
    iVar1 = iVar1 + -1;
  }
  sys_init_display(800,0x1e0,0x81b00000,0x81b00000);
  display_bitmap(800 - local_16 >> 1,0x1e0 - local_14 >> 1,(uint)local_16,(uint)local_14,
                 (uint *)0x81000000);
  Set_Default_Brightness();
  sys_spi_flash_read(0x27000,auStack48,0x20);
  iVar1 = 0;
  while ((iVar1 < 8 && (acStack44[iVar1] == *(char *)((int)&local_10 + iVar1)))) {
    iVar1 = iVar1 + 1;
  }
  if (iVar1 == 8) {
    sys_spi_flash_read(iRam00000750,(void *)0x80000000,
                       ((uint)local_1d << 0x18 | (uint)local_1e << 0x10 | (uint)local_1f << 8 |
                       (uint)local_20) - 0x20);
    delay(100);
    (*(code *)0x80000000)();
  }
  else {
    sys_spi_flash_read(0x6000,auStack48,0x20);
    iVar1 = 0;
    while ((iVar1 < 8 && (acStack44[iVar1] == *(char *)((int)&local_10 + iVar1)))) {
      iVar1 = iVar1 + 1;
    }
    if (iVar1 == 8) {
      sys_spi_flash_read(iRam00000754,(void *)0x80000000,
                         ((uint)local_1d << 0x18 | (uint)local_1e << 0x10 | (uint)local_1f << 8 |
                         (uint)local_20) - 0x20);
      delay(100);
      (*(code *)0x80000000)();
    }
  }
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



void FUN_00000758(void)

{
  do {
                    // WARNING: Do nothing block with infinite loop
  } while( true );
}



undefined8 FUN_00000768(undefined4 param_1,undefined4 param_2)

{
  return CONCAT44(param_2,DAT_00000794);
}



undefined FUN_00000798(undefined *param_1)

{
  return *param_1;
}



undefined2 FUN_000007a8(undefined2 *param_1)

{
  return *param_1;
}



uint read32(uint *ptr)

{
  return *ptr;
}



undefined8 FUN_000007c8(undefined8 *param_1)

{
  return *param_1;
}



void FUN_000007d8(undefined *param_1,undefined4 param_2,undefined param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_000007e0(undefined2 *param_1,undefined4 param_2,undefined2 param_3)

{
  *param_1 = param_3;
  return;
}



void write32(uint *prt,uint data)

{
  *prt = data;
  return;
}



void FUN_000007f0(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  *param_1 = param_3;
  param_1[1] = param_4;
  return;
}



void wait_pll_stable(uint base)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = DAT_00000a90;
  do {
    uVar1 = read32((uint *)base);
    iVar2 = iVar2 + -1;
    if (iVar2 == 0) {
      return;
    }
  } while ((uVar1 & 0x10000000) == 0);
  return;
}



void clock_set_pll_cpu(uint clk)

{
  uint uVar1;
  uint uVar2;
  int extraout_r1;
  int extraout_r1_00;
  int extraout_r1_01;
  int iVar3;
  int iVar4;
  
  divide();
  if (extraout_r1 == 0) {
    uVar1 = divide();
    iVar4 = uVar1 - 1;
    iVar3 = 0;
    uVar1 = 0;
  }
  else {
    divide();
    if (extraout_r1_00 == 0) {
      uVar1 = 1;
      uVar2 = divide();
      divide();
      if (extraout_r1_01 == 0) {
        iVar3 = 2;
      }
      else {
        if ((uVar2 & 3) == 0) {
          iVar3 = 3;
        }
        else {
          iVar3 = 1;
        }
      }
      uVar2 = divide();
      iVar4 = uVar2 - 1;
    }
    else {
      uVar1 = divide();
      iVar4 = uVar1 - 1;
      iVar3 = 0;
      uVar1 = 0;
    }
  }
  uVar2 = read32(PLL_CPU_CTRL_REG);
  write32(PLL_CPU_CTRL_REG,uVar2 & DAT_00000aa4 | iVar4 << 8 | 0x80000000U | iVar3 << 4 | uVar1);
  wait_pll_stable((uint)PLL_CPU_CTRL_REG);
  return;
}



void sys_clock_init(void)

{
  uint uVar1;
  
  write32(PLL_STABLE_TIME_REG0,DAT_00000aa8);
  write32(PLL_STABLE_TIME_REG1,DAT_00000aa8);
  uVar1 = read32(CPU_CLK_SRC_REG);
  write32(CPU_CLK_SRC_REG,uVar1 & 0xfffcffff | 0x10000);
  sdelay(100);
  write32(PLL_VIDEO_CTRL_REG,DAT_00000ab8);
  sdelay(100);
  write32(PLL_PERIPH_CTRL_REG,DAT_00000ac0);
  sdelay(100);
  write32(AHB_APB_HCLKC_CFG_REG,0x3180);
  sdelay(100);
  uVar1 = read32(DRAM_GATING_REG);
  write32(DRAM_GATING_REG,uVar1 | 0x5000000);
  sdelay(100);
  clock_set_pll_cpu(DAT_00000ad0);
  uVar1 = read32(CPU_CLK_SRC_REG);
  write32(CPU_CLK_SRC_REG,uVar1 & 0xfffcffff | 0x20000);
  sdelay(100);
  return;
}



void sdelay(int loops)

{
  int iVar1;
  
  iVar1 = 0;
  while (iVar1 < 300) {
    iVar1 = iVar1 + 1;
  }
  return;
}



undefined FUN_00000ad4(undefined *param_1)

{
  return *param_1;
}



undefined2 FUN_00000ae4(undefined2 *param_1)

{
  return *param_1;
}



uint get_data(uint *ptr)

{
  return *ptr;
}



void set_data(uint *ptr,uint data)

{
  *ptr = data;
  return;
}



void dram_delay(int ms)

{
  int iVar1;
  
  iVar1 = 0;
  while (iVar1 < 300) {
    iVar1 = iVar1 + 1;
  }
  return;
}



void dramc_setup(void)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 0xffffff;
  uVar1 = get_data(DRAMC_SCTLR);
  set_data(DRAMC_SCTLR,uVar1 | 1);
  while( true ) {
    uVar1 = get_data(DRAMC_SCTLR);
    if ((uVar1 & 1) == 0) {
      return;
    }
    bVar3 = iVar2 == 0;
    iVar2 = iVar2 + -1;
    if (bVar3) break;
    if (iVar2 == 0) {
      return;
    }
  }
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

undefined4 dramc_setup2(void)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  iVar2 = 0xffffff;
  uVar1 = get_data(DRAMC_DDLYR);
  set_data(DRAMC_DDLYR,uVar1 | 1);
  while ((uVar1 = get_data(DRAMC_DDLYR), (uVar1 & 1) != 0 &&
         (bVar3 = iVar2 != 0, iVar2 = iVar2 + -1, bVar3))) {
    if (iVar2 == 0) {
      return 0;
    }
  }
  return 1;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void dramc_setup3(void)

{
  uint in_r0;
  uint uVar1;
  uint data;
  
  data = 0;
  uVar1 = get_data(DRAMC_SCONR);
  uVar1 = (uVar1 & 0x1e0) >> 5;
  if (uVar1 == 0xc) {
    if (in_r0 < DAT_000016f4) {
      data = in_r0 * DAT_000016fc >> 6;
    }
    else {
      uVar1 = in_r0 + (in_r0 >> 3) + (in_r0 >> 4) + (in_r0 >> 5);
      while (DAT_000016f8 <= uVar1) {
        uVar1 = uVar1 - DAT_000016f8;
        data = data + 1;
      }
    }
  }
  else {
    if (uVar1 == 0xb) {
      if (in_r0 < DAT_000016f4) {
        data = in_r0 * DAT_000016fc >> 5;
      }
      else {
        uVar1 = in_r0 + (in_r0 >> 3) + (in_r0 >> 4) + (in_r0 >> 5);
        while (DAT_00001704 <= uVar1) {
          uVar1 = uVar1 + DAT_00001700;
          data = data + 1;
        }
      }
    }
  }
  set_data(DRAMC_SREFR,data);
  return;
}



int dram_para_setup(int *para)

{
  uint uVar1;
  uint *puVar2;
  
  if (*(char *)(para + 6) == '\0') {
    uVar1 = (uint)para[7] >> 5;
  }
  else {
    uVar1 = (uint)para[7] >> 4;
  }
  set_data(DRAMC_SCONR,
           para[5] | 2U | ((uint)para[10] >> 2) << 3 | ((uint)para[4] >> 1) << 4 |
           (para[9] + -1) * 0x20 | (para[8] + -1) * 0x200 | uVar1 << 0xd | para[3] << 0xf |
           (uint)*(byte *)(para + 6) << 0x10);
  uVar1 = get_data(DRAMC_SCTLR);
  puVar2 = DRAMC_SCTLR;
  set_data(DRAMC_SCTLR,uVar1 | 0x80000);
  dramc_setup();
  return (int)puVar2;
}



// WARNING: Unknown calling convention yet parameter storage is locked

int dramc_setup5(void)

{
  int in_r0;
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  
  iVar4 = 0;
  uVar5 = 0;
  if (in_r0 == 0x10) {
    uVar1 = 4;
  }
  else {
    uVar1 = 2;
  }
  uVar2 = 0;
  while (uVar2 < uVar1) {
    if (uVar2 == 0) {
      uVar5 = get_data(DRAMC_DRPTR0);
    }
    else {
      if (uVar2 == 1) {
        uVar5 = get_data(DRAMC_DRPTR1);
      }
      else {
        if (uVar2 == 2) {
          uVar5 = get_data(DRAMC_DRPTR2);
        }
        else {
          if (uVar2 == 3) {
            uVar5 = get_data(DRAMC_DRPTR3);
          }
        }
      }
    }
    uVar3 = 0;
    while (uVar3 < 0x20) {
      if ((uVar5 & 1) != 0) {
        iVar4 = iVar4 + 1;
      }
      uVar5 = uVar5 >> 1;
      uVar3 = uVar3 + 1;
    }
    uVar2 = uVar2 + 1;
  }
  return iVar4;
}



undefined4 FUN_00000e90(void)

{
  uint uVar1;
  uint uVar2;
  
  uVar2 = 0;
  while (uVar2 < 0x20) {
    set_data((uint *)(uVar2 * 4 + -0x80000000),uVar2);
    uVar2 = uVar2 + 1;
  }
  uVar2 = 0;
  while( true ) {
    if (0x1f < uVar2) {
      return 1;
    }
    uVar1 = get_data((uint *)(uVar2 * 4 + -0x80000000));
    if (uVar1 != uVar2) break;
    uVar2 = uVar2 + 1;
  }
  return 0;
}



// WARNING: Unknown calling convention yet parameter storage is locked

uint dramc_setup5(void)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  while( true ) {
    if (7 < uVar3) {
      return 0;
    }
    uVar1 = get_data(DRAMC_SCTLR);
    set_data(DRAMC_SCTLR,uVar1 & 0xfffffe3f | uVar3 << 6);
    iVar2 = FUN_00000e90();
    if (iVar2 != 0) break;
    uVar3 = uVar3 + 1;
  }
  return uVar3;
}



// WARNING: Unknown calling convention yet parameter storage is locked

bool dramc_setup6(void)

{
  int in_r0;
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = 0;
  uVar2 = 0;
  while (uVar2 < 8) {
    uVar1 = get_data(DRAMC_SCTLR);
    set_data(DRAMC_SCTLR,uVar1 & 0xfffffe3f | uVar2 << 6);
    dramc_setup2();
    uVar1 = get_data(DRAMC_DDLYR);
    if ((uVar1 & 0x30) != 0) {
      iVar3 = iVar3 + 1;
    }
    uVar2 = uVar2 + 1;
  }
  if (iVar3 != 8) {
    *(undefined *)(in_r0 + 0x18) = 1;
  }
  else {
    *(undefined *)(in_r0 + 0x18) = 0;
  }
  return iVar3 != 8;
}



uint dram_scan_readpipe(int *para)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint local_38 [8];
  
  uVar4 = 0;
  uVar5 = 0;
  if (*(char *)(para + 6) == '\x01') {
    uVar3 = 0;
    while (uVar3 < 8) {
      uVar1 = get_data(DRAMC_SCTLR);
      set_data(DRAMC_SCTLR,uVar1 & 0xfffffe3f | uVar3 << 6);
      dramc_setup2();
      local_38[uVar3] = 0;
      uVar1 = get_data(DRAMC_DDLYR);
      if (((uVar1 >> 4 & 3) == 0) && (uVar1 = get_data(DRAMC_DDLYR), (uVar1 >> 4 & 1) == 0)) {
        uVar1 = dramc_setup5();
        local_38[uVar3] = uVar1;
      }
      if (uVar5 < local_38[uVar3]) {
        uVar5 = local_38[uVar3];
        uVar4 = uVar3;
      }
      uVar3 = uVar3 + 1;
    }
    uVar5 = get_data(DRAMC_SCTLR);
    set_data(DRAMC_SCTLR,uVar5 & 0xfffffe3f | uVar4 << 6);
    dramc_setup2();
  }
  else {
    uVar4 = get_data(DRAMC_SCONR);
    set_data(DRAMC_SCONR,uVar4 & 0xfffe9fff);
    iVar2 = dramc_setup5();
    uVar4 = get_data(DRAMC_SCTLR);
    set_data(DRAMC_SCTLR,uVar4 & 0xfffffe3f | iVar2 << 6);
  }
  return 0;
}



uint dram_get_dram_size(int *para)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  uVar1 = 0;
  iVar3 = 0;
  para[8] = 10;
  para[9] = 0xd;
  dram_para_setup(para);
  dram_scan_readpipe(para);
  while (iVar4 = DAT_0000171c, uVar1 < 0x20) {
    *(int *)(&DAT_80000200 + uVar1) = DAT_0000171c;
    *(int *)(&DAT_80000600 + uVar1) = iVar4 << 1;
    uVar1 = uVar1 + 1;
  }
  uVar1 = 0;
  while (uVar1 < 0x20) {
    if (*(int *)(&DAT_80000200 + uVar1) == DAT_00001720) {
      iVar3 = iVar3 + 1;
    }
    uVar1 = uVar1 + 1;
  }
  if (iVar3 == 0x20) {
    iVar3 = 9;
  }
  else {
    iVar3 = 10;
  }
  iVar4 = 0;
  para[8] = iVar3;
  para[9] = 0xd;
  dram_para_setup(para);
  if (iVar3 == 10) {
    uVar5 = DAT_00001724 | DAT_00001724 << 1;
    uVar1 = DAT_00001724;
  }
  else {
    uVar5 = DAT_00001728 | DAT_00001728 << 1;
    uVar1 = DAT_00001728;
  }
  uVar2 = 0;
  while (uVar2 < 0x20) {
    *(undefined4 *)(uVar1 + uVar2) = DAT_0000172c;
    *(int *)(uVar5 + uVar2) = DAT_00001730;
    uVar2 = uVar2 + 1;
  }
  uVar5 = 0;
  while (uVar5 < 0x20) {
    if (*(int *)(uVar1 + uVar5) == DAT_00001730) {
      iVar4 = iVar4 + 1;
    }
    uVar5 = uVar5 + 1;
  }
  if (iVar4 == 0x20) {
    iVar4 = 0xc;
  }
  else {
    iVar4 = 0xd;
  }
  para[8] = iVar3;
  para[9] = iVar4;
  if (para[9] == 0xd) {
    if (para[8] == 10) {
      para[1] = 0x40;
    }
    else {
      para[1] = 0x20;
    }
  }
  else {
    para[1] = 0x10;
  }
  dramc_setup3();
  para[3] = 0;
  dram_para_setup(para);
  return 0;
}



int dram_init(int *para)

{
  uint uVar1;
  uint data;
  
  uVar1 = get_data(PORT_B_CFG);
  set_data(PORT_B_CFG,uVar1 | 0x7000);
  dram_delay(5);
  if (((uint)para[0xb] >> 3 & 1) != 0) {
    uVar1 = get_data(SDR_PAD_PUL);
    set_data(SDR_PAD_PUL,uVar1 | 0xc00000);
  }
  if ((0x8f < (uint)para[2]) && ((uint)para[2] < 0xb5)) {
    set_data(SDR_PAD_DRV,DAT_0000173c);
  }
  if (0xb3 < (uint)para[2]) {
    set_data(SDR_PAD_DRV,DAT_00001744);
  }
  if ((uint)para[2] < 0x61) {
    uVar1 = divide();
    uVar1 = (uVar1 - 1) * 0x100 | 1;
  }
  else {
    uVar1 = divide();
    uVar1 = (uVar1 - 1) * 0x100;
  }
  data = uVar1 | 0x80000000;
  if ((*(byte *)(para + 0xb) & 0x10) == 0) {
    if ((*(byte *)(para + 0xb) & 0x20) == 0) {
      if ((*(byte *)(para + 0xb) & 0x40) == 0) {
        if ((*(byte *)(para + 0xb) & 0x80) != 0) {
          set_data(PLL_DDR_PAT_CTRL_REG,DAT_00001758);
        }
      }
      else {
        set_data(PLL_DDR_PAT_CTRL_REG,DAT_00001754);
      }
    }
    else {
      set_data(PLL_DDR_PAT_CTRL_REG,DAT_00001750);
    }
  }
  else {
    set_data(PLL_DDR_PAT_CTRL_REG,DAT_00001748);
  }
  if ((*(byte *)(para + 0xb) & 0xf0) != 0) {
    data = uVar1 | 0x81000000;
  }
  set_data(PLL_DDR_CTRL_REG,data);
  uVar1 = get_data(PLL_DDR_CTRL_REG);
  set_data(PLL_DDR_CTRL_REG,uVar1 | 0x100000);
  do {
    uVar1 = get_data(PLL_DDR_CTRL_REG);
  } while ((uVar1 & 0x10000000) == 0);
  dram_delay(5);
  uVar1 = get_data(BUS_CLK_GATING_REG0);
  set_data(BUS_CLK_GATING_REG0,uVar1 | 0x4000);
  uVar1 = get_data(BUS_SOFT_RST_REG0);
  set_data(BUS_SOFT_RST_REG0,uVar1 & 0xffffbfff);
  uVar1 = 0;
  while (uVar1 < 10) {
    uVar1 = uVar1 + 1;
  }
  uVar1 = get_data(BUS_SOFT_RST_REG0);
  set_data(BUS_SOFT_RST_REG0,uVar1 | 0x4000);
  uVar1 = get_data(SDR_PAD_PUL);
  if (*(char *)(para + 6) == '\x01') {
    uVar1 = uVar1 | 0x10000;
  }
  else {
    uVar1 = uVar1 & 0xfffeffff;
  }
  set_data(SDR_PAD_PUL,uVar1);
  set_data(DRAMC_STMG0R,DAT_00001768);
  set_data(DRAMC_STMG1R,DAT_00001770);
  dram_para_setup(para);
  dramc_setup6();
  uVar1 = get_data(SDR_PAD_PUL);
  if (*(char *)(para + 6) == '\x01') {
    uVar1 = uVar1 | 0x10000;
  }
  else {
    uVar1 = uVar1 & 0xfffeffff;
  }
  set_data(SDR_PAD_PUL,uVar1);
  dramc_setup3();
  dram_scan_readpipe(para);
  dram_get_dram_size(para);
  uVar1 = 0;
  while (uVar1 < 0x80) {
    *(uint *)(*para + uVar1 * 4) = uVar1 * 4 + *para;
    uVar1 = uVar1 + 1;
  }
  uVar1 = 0;
  while( true ) {
    if (0x7f < uVar1) {
      return 1;
    }
    if (*(int *)(*para + uVar1 * 4) != uVar1 * 4 + *para) break;
    uVar1 = uVar1 + 1;
  }
  return 0;
}



void sys_dram_init(void)

{
  int local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  undefined4 local_24;
  undefined local_20;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  local_38 = -0x80000000;
  local_34 = 0x20;
  local_30 = 0x9c;
  local_2c = 1;
  local_28 = 1;
  local_24 = 0;
  local_20 = 1;
  local_1c = 0x10;
  local_18 = 10;
  local_14 = 0xd;
  local_10 = 4;
  local_c = 3;
  dram_init(&local_38);
  return;
}



undefined FUN_00001778(undefined *param_1)

{
  return *param_1;
}



undefined2 FUN_00001788(undefined2 *param_1)

{
  return *param_1;
}



undefined4 FUN_00001798(undefined4 *param_1)

{
  return *param_1;
}



undefined8 FUN_000017a8(undefined8 *param_1)

{
  return *param_1;
}



void FUN_000017b8(undefined *param_1,undefined4 param_2,undefined param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_000017c0(undefined2 *param_1,undefined4 param_2,undefined2 param_3)

{
  *param_1 = param_3;
  return;
}



void FUN_000017c8(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



void store_64(int *ptr,int msw,int lsw)

{
  *ptr = lsw;
  ptr[1] = msw;
  return;
}



void Config_GPIO_Pin(undefined4 *Port,uint Pin,int Mode)

{
  int in_r3;
  
  Port[Pin >> 3] = Port[Pin >> 3] & ~(0xf << ((Pin << 0x1d) >> 0x1b));
  if (Mode == 0) {
    Port[Pin >> 3] = Port[Pin >> 3] & ~(1 << ((Pin << 0x1d) >> 0x1b));
  }
  else {
    if (Mode == 1) {
      Port[Pin >> 3] = Port[Pin >> 3] | 1 << ((Pin << 0x1d) >> 0x1b);
    }
    else {
      Port[Pin >> 3] = Port[Pin >> 3] | Mode << ((Pin << 0x1d) >> 0x1b);
    }
  }
  Port[(Pin >> 4) + 7] = Port[(Pin >> 4) + 7] & ~(3 << ((Pin << 0x1c) >> 0x1b));
  Port[(Pin >> 4) + 7] = Port[(Pin >> 4) + 7] | in_r3 << ((Pin << 0x1c) >> 0x1b);
  return;
}



void Set_GPIO_Pin_High(undefined4 *Port,uint Pin)

{
  Port[4] = Port[4] | 1 << (Pin & 0xff);
  return;
}



void Set_GPIO_Pin_Low(undefined4 *Port,uint Pin)

{
  Port[4] = Port[4] & ~(1 << (Pin & 0xff));
  return;
}



undefined4 FUN_00001930(undefined4 *param_1)

{
  return *param_1;
}



void FUN_00001960(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  *param_1 = param_3;
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void UART0_Init(void)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  
  uVar1 = divide();
  Config_GPIO_Pin(DAT_00001fd4,0,5);
  Config_GPIO_Pin(DAT_00001fd4,1,5);
  iVar3 = DAT_00001fd8;
  uVar2 = FUN_00001930(DAT_00001fd8,0);
  FUN_00001960(iVar3,0,uVar2 | 0x100000);
  iVar3 = iVar3 + 0x268;
  uVar2 = FUN_00001930(iVar3,0);
  FUN_00001960(iVar3,0,uVar2 | 0x100000);
  iVar3 = DAT_00001fdc;
  FUN_00001960(DAT_00001fdc + 4,0);
  FUN_00001960(iVar3 + 8,0,0xf7);
  FUN_00001960(iVar3 + 0x10,0);
  uVar2 = FUN_00001930(iVar3 + 0xc,0);
  FUN_00001960(iVar3 + 0xc,0,uVar2 | 0x80);
  FUN_00001960(iVar3,0,uVar1 >> 4 & 0xff);
  FUN_00001960(iVar3 + 4,0,((uVar1 >> 4) << 0x10) >> 0x18);
  uVar1 = FUN_00001930(iVar3 + 0xc,0);
  FUN_00001960(iVar3 + 0xc,0,uVar1 & 0xffffff7f);
  uVar1 = FUN_00001930(iVar3 + 0xc,0);
  FUN_00001960(iVar3 + 0xc,0,uVar1 & 0xffffffe0 | 3);
  return;
}



void FUN_00001ad0(undefined4 param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = DAT_00001fdc;
  do {
    uVar2 = FUN_00001930(iVar1 + 0x7c,0);
  } while ((uVar2 & 2) == 0);
  FUN_00001960(iVar1,0,param_1);
  return;
}



void FUN_00001b0c(char *param_1)

{
  while (*param_1 != '\0') {
    FUN_00001ad0(*param_1);
    param_1 = param_1 + 1;
  }
  return;
}



void FUN_00001b34(undefined4 param_1,int param_2)

{
  bool bVar1;
  
  while (bVar1 = param_2 != 0, param_2 = param_2 + -1, bVar1) {
    FUN_00001ad0(param_1);
  }
  return;
}



void FUN_00001b5c(int param_1,int param_2)

{
  while (0 < param_2) {
    FUN_00001ad0(*(undefined *)(param_1 + param_2 + -1));
    param_2 = param_2 + -1;
  }
  return;
}



void FUN_00001b84(uint param_1,int param_2,int param_3,int param_4)

{
  bool bVar1;
  char cVar2;
  uint extraout_r1;
  int iVar3;
  int iVar4;
  uint uVar5;
  bool bVar6;
  char local_4c [40];
  
  iVar3 = 0;
  bVar1 = false;
  if (param_4 == 0) {
    param_4 = 0x20;
  }
  bVar6 = -1 < param_3;
  if (!bVar6) {
    param_3 = -param_3;
  }
  if ((param_3 < 0) || (0x50 < param_3)) {
    param_3 = 0;
  }
  if ((param_2 < 0) && (param_2 = -param_2, (int)param_1 < 0)) {
    bVar1 = true;
    param_1 = -param_1;
  }
  do {
    if (param_2 == 0x10) {
      uVar5 = param_1 & 0xf;
      param_1 = param_1 >> 4;
    }
    else {
      divide();
      uVar5 = extraout_r1 & 0xffff;
      param_1 = divide();
    }
    if (uVar5 < 10) {
      cVar2 = '0';
    }
    else {
      cVar2 = '7';
    }
    local_4c[iVar3] = cVar2 + (char)uVar5;
    iVar4 = iVar3 + 1;
    if (((param_1 != 0) && (param_2 == 10)) &&
       ((iVar4 == 3 || ((iVar4 == 7 || (iVar4 == 0xb || iVar4 == 0xf)))))) {
      iVar4 = iVar3 + 2;
      local_4c[iVar3 + 1] = ',';
    }
    iVar3 = iVar4;
  } while (param_1 != 0);
  if (bVar1) {
    local_4c[iVar4] = '-';
    iVar4 = iVar4 + 1;
  }
  if (iVar4 < param_3) {
    if (bVar6) {
      FUN_00001b34(param_4,param_3 - iVar4);
    }
    FUN_00001b5c(local_4c,iVar4);
    if (!bVar6) {
      FUN_00001b34(param_4,param_3 - iVar4);
    }
  }
  else {
    FUN_00001b5c(local_4c,iVar4);
  }
  return;
}



byte * FUN_00001d44(byte *param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  byte *pbVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  
  uVar2 = 0;
  bVar1 = false;
  iVar5 = 0;
  uVar6 = 0x20;
  if (*param_1 == 0x30) {
    uVar6 = 0x30;
  }
  do {
    pbVar3 = param_1 + 1;
    uVar4 = (uint)*param_1;
    if (uVar4 == 0) break;
    if ((uVar4 < 0x30) || (0x39 < uVar4)) {
      if (uVar4 == 100) {
LAB_00001ed4:
        iVar5 = -10;
      }
      else {
        if (uVar4 < 0x65) {
          if (uVar4 == 0x2d) {
            bVar1 = true;
          }
          else {
            if (uVar4 < 0x2e) {
              if (uVar4 == 0) {
                return param_1;
              }
              if (uVar4 == 0x25) {
                FUN_00001ad0(0x25);
                return pbVar3;
              }
            }
            else {
              if (uVar4 == 0x58) {
                iVar5 = 0x10;
                goto LAB_00001f1c;
              }
              if (uVar4 == 99) {
                if (bVar1) {
                  FUN_00001ad0(param_2 & 0x7f);
                }
                if (0 < (int)uVar2) {
                  FUN_00001b34(uVar6,uVar2 - 1);
                }
                if (bVar1) {
                  return pbVar3;
                }
                FUN_00001ad0(param_2 & 0x7f);
                return pbVar3;
              }
            }
LAB_00001f0c:
            iVar5 = 3;
          }
        }
        else {
          if (uVar4 == 0x73) {
            if (bVar1) {
              FUN_00001b0c(param_2);
            }
            uVar4 = FUN_00002d78(param_2);
            if (uVar4 < uVar2) {
              iVar5 = FUN_00002d78(param_2);
              FUN_00001b34(uVar6,uVar2 - iVar5);
            }
            if (bVar1) {
              return pbVar3;
            }
            FUN_00001b0c(param_2);
            return pbVar3;
          }
          if (uVar4 < 0x74) {
            if (uVar4 == 0x69) goto LAB_00001ed4;
            if (uVar4 != 0x6f) goto LAB_00001f0c;
            iVar5 = 8;
          }
          else {
            if (uVar4 == 0x75) {
              iVar5 = 10;
            }
            else {
              if (uVar4 != 0x78) goto LAB_00001f0c;
              iVar5 = 0x10;
            }
          }
        }
      }
    }
    else {
      uVar2 = (uVar4 - 0x30) + uVar2 * 10;
    }
LAB_00001f1c:
    param_1 = pbVar3;
  } while (iVar5 == 0);
  if (bVar1) {
    uVar2 = -uVar2;
  }
  FUN_00001b84(param_2,iVar5,uVar2,uVar6);
  return pbVar3;
}



void delay(uint loops)

{
  uint local_c;
  uint local_8;
  
  local_8 = 0;
  while (local_8 < loops * 0x42) {
    local_c = 0;
    while (local_c < 0x14) {
      local_c = local_c + 1;
    }
    local_8 = local_8 + 1;
  }
  return;
}



void FUN_00002040(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  bool bVar1;
  uint uVar2;
  undefined8 uVar3;
  uint uVar4;
  
  FUN_000032d8(param_1);
  uVar3 = FUN_00003274();
  FUN_00003034((int)uVar3,(int)((ulonglong)uVar3 >> 0x20),DAT_000020c4,DAT_000020c8,param_2,param_3,
               param_4);
  uVar2 = FUN_00002fc4();
  uVar4 = 0;
  while (uVar4 < uVar2) {
    bVar1 = false;
    while (!bVar1) {
      bVar1 = true;
    }
    uVar4 = uVar4 + 1;
  }
  return;
}



uchar read8(uchar *ptr)

{
  return *ptr;
}



undefined2 FUN_000020dc(undefined2 *param_1)

{
  return *param_1;
}



uint read_32(uint *ptr)

{
  return *ptr;
}



undefined8 FUN_000020fc(undefined8 *param_1)

{
  return *param_1;
}



void write8(uchar *ptr,uchar data)

{
  uchar in_r2;
  
  *ptr = in_r2;
  return;
}



void FUN_00002114(undefined2 *param_1,undefined4 param_2,undefined2 param_3)

{
  *param_1 = param_3;
  return;
}



void write_32(uint *ptr,uint data)

{
  *ptr = data;
  return;
}



// WARNING: Unknown calling convention yet parameter storage is locked

void sys_spi_flash_init(void)

{
  int iVar1;
  uint uVar2;
  uint *puVar3;
  
  puVar3 = PC_CFG0;
  uVar2 = read_32(PC_CFG0);
  write_32(puVar3,uVar2 & 0xfffffff0 | 2);
  uVar2 = read_32(puVar3);
  write_32(puVar3,uVar2 & 0xffffff0f | 0x20);
  uVar2 = read_32(puVar3);
  write_32(puVar3,uVar2 & 0xfffff0ff | 0x200);
  uVar2 = read_32(puVar3);
  write_32(puVar3,uVar2 & 0xffff0fff | 0x2000);
  puVar3 = BUS_SOFT_RST_REG0;
  uVar2 = read_32(BUS_SOFT_RST_REG0);
  write_32(puVar3,uVar2 | 0x100000);
  puVar3 = puVar3 + -0x98;
  uVar2 = read_32(puVar3);
  write_32(puVar3,uVar2 | 0x100000);
  iVar1 = SPI0_BASE;
  write_32((uint *)(SPI0_BASE + 0x24),DAT_00002608);
  uVar2 = read_32((uint *)(iVar1 + 4));
  write_32((uint *)(iVar1 + 4),uVar2 | 0x80000083);
  do {
    uVar2 = read_32((uint *)(iVar1 + 4));
  } while ((uVar2 & 0x80000000) != 0);
  uVar2 = read_32((uint *)(iVar1 + 8));
  write_32((uint *)(iVar1 + 8),uVar2 & 0xfffffffc | 0x44);
  uVar2 = read_32((uint *)(iVar1 + 0x18));
  write_32((uint *)(iVar1 + 0x18),uVar2 | 0x80008000);
  return;
}



void sys_spi_flash_exit(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = SPI0_BASE;
  uVar2 = read_32((uint *)(SPI0_BASE + 4));
  write_32((uint *)(iVar1 + 4),uVar2 & 0xfffffffc);
  return;
}



void sys_spi_select(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = SPI0_BASE;
  uVar2 = read_32((uint *)(SPI0_BASE + 8));
  write_32((uint *)(iVar1 + 8),uVar2 & 0xffffff4f);
  return;
}



void sys_spi_deselect(void)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = SPI0_BASE;
  uVar2 = read_32((uint *)(SPI0_BASE + 8));
  write_32((uint *)(iVar1 + 8),uVar2 & 0xffffff4f | 0x80);
  return;
}



void sys_spi_write_txbuf(uchar *buf,int len)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = SPI0_BASE;
  if (buf == (uchar *)0x0) {
    len = 0;
  }
  write_32((uint *)(SPI0_BASE + 0x34),len & 0xffffff);
  write_32((uint *)(uVar1 + 0x38),len & 0xffffff);
  iVar2 = 0;
  while (iVar2 < len) {
    write8((uchar *)(uVar1 + 0x200),0xfffffdff < uVar1);
    iVar2 = iVar2 + 1;
  }
  return;
}



int sys_spi_transfer(void *txbuf,void *rxbuf,int len)

{
  int iVar1;
  uchar uVar2;
  uint data;
  uint uVar3;
  uint uVar4;
  uchar *puVar5;
  int local_34;
  
  iVar1 = SPI0_BASE;
  uVar4 = len;
  while (0 < (int)uVar4) {
    data = uVar4;
    if (0x40 < (int)uVar4) {
      data = 0x40;
    }
    write_32((uint *)(iVar1 + 0x30),data);
    sys_spi_write_txbuf((uchar *)txbuf,data);
    uVar3 = read_32((uint *)(iVar1 + 8));
    write_32((uint *)(iVar1 + 8),uVar3 | 0x80000000);
    do {
      uVar3 = read_32((uint *)(iVar1 + 0x1c));
    } while ((uVar3 & 0xff) < data);
    local_34 = 0;
    while (local_34 < (int)data) {
      uVar2 = read8((uchar *)(iVar1 + 0x300));
      puVar5 = (uchar *)rxbuf;
      if ((uchar *)rxbuf != (uchar *)0x0) {
        puVar5 = (uchar *)((int)rxbuf + 1);
        *(uchar *)rxbuf = uVar2;
      }
      local_34 = local_34 + 1;
      rxbuf = puVar5;
    }
    if ((uchar *)txbuf != (uchar *)0x0) {
      txbuf = (void *)((int)txbuf + data);
    }
    uVar4 = uVar4 - data;
  }
  return len;
}



int sys_spi_write_then_read(void *txbuf,int txlen,void *rxbuf,int rxlen)

{
  int iVar1;
  
  iVar1 = sys_spi_transfer(txbuf,(void *)0x0,txlen);
  if (iVar1 == txlen) {
    iVar1 = sys_spi_transfer((void *)0x0,rxbuf,rxlen);
    if (iVar1 == rxlen) {
      iVar1 = 0;
    }
    else {
      iVar1 = -1;
    }
  }
  else {
    iVar1 = -1;
  }
  return iVar1;
}



// WARNING: Could not reconcile some variable overlaps

void sys_spi_flash_read(int addr,void *buf,int count)

{
  undefined4 local_18;
  
  local_18 = CONCAT13((char)addr,
                      CONCAT12((char)((uint)(addr << 0x10) >> 0x18),
                               CONCAT11((char)((uint)(addr << 8) >> 0x18),3)));
  sys_spi_select();
  sys_spi_write_then_read(&local_18,4,buf,count);
  sys_spi_deselect();
  return;
}



undefined FUN_0000260c(undefined *param_1)

{
  return *param_1;
}



undefined2 FUN_0000261c(undefined2 *param_1)

{
  return *param_1;
}



undefined4 FUN_0000262c(undefined4 *param_1)

{
  return *param_1;
}



void write__32(uint *ptr,uint data)

{
  *ptr = data;
  return;
}



void FUN_0000266c(int param_1)

{
  int iVar1;
  uint uVar2;
  uint *ptr;
  int iVar3;
  
  iVar1 = DAT_00002d54;
  iVar3 = DAT_00002d54 + -5;
  ptr = *(uint **)(param_1 + 0x10);
  uVar2 = FUN_0000262c(PLL_VIDEO_CTRL_REG,0);
  write__32(PLL_VIDEO_CTRL_REG,uVar2 & 0x7fffffff);
  write__32(PLL_VIDEO_CTRL_REG,0x3004003);
  uVar2 = FUN_0000262c(PLL_VIDEO_CTRL_REG,0);
  write__32(PLL_VIDEO_CTRL_REG,uVar2 | 0x80000000);
  delay(1);
  uVar2 = FUN_0000262c(BUS_CLK_GATING_REG1,0);
  write__32(BUS_CLK_GATING_REG1,uVar2 | 0x10);
  uVar2 = FUN_0000262c(TCON_CLK_REG,0);
  write__32(TCON_CLK_REG,uVar2 | 0x80000000);
  uVar2 = FUN_0000262c(BUS_SOFT_RST_REG1,0);
  write__32(BUS_SOFT_RST_REG1,uVar2 | 0x10);
  delay(1);
  uVar2 = FUN_0000262c(ptr,0);
  write__32(ptr,uVar2 & 0xfffffffe);
  write__32(ptr + 0x10,
            (uint)((*(int *)(param_1 + 0x50) + *(int *)(param_1 + 0x54) + *(int *)(param_1 + 0x58))
                  * 0x8000000) >> 0x17 | 0x80000000);
  write__32(ptr + 0x11,0xf0000006);
  write__32(ptr + 0x12,*(int *)(param_1 + 0x20) - 1U | (*(ushort *)(param_1 + 0x1c) - 1) * 0x10000);
  write__32(ptr + 0x13,(iVar1 + -1) * 0x10000 | 0x44);
  write__32(ptr + 0x14,iVar3 * 0x10000 | 0x17);
  write__32(ptr + 0x15,0x160000);
  write__32(ptr + 0x16,0);
  write__32(ptr + 0x18,0);
  uVar2 = 0x10000000;
  if (*(int *)(param_1 + 0x5c) == 0) {
    uVar2 = 0x12000000;
  }
  if (*(int *)(param_1 + 0x60) == 0) {
    uVar2 = uVar2 | 0x1000000;
  }
  if (*(int *)(param_1 + 100) == 0) {
    uVar2 = uVar2 | 0x8000000;
  }
  if (*(int *)(param_1 + 0x68) == 0) {
    uVar2 = uVar2 | 0x4000000;
  }
  write__32(ptr + 0x22,uVar2);
  write__32(ptr + 0x23,0);
  return;
}



void FUN_000028e4(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 8);
  uVar1 = FUN_0000262c(BUS_CLK_GATING_REG1,0);
  write__32(BUS_CLK_GATING_REG1,uVar1 | 0x1000);
  uVar1 = FUN_0000262c(BUS_SOFT_RST_REG1,0);
  write__32(BUS_SOFT_RST_REG1,uVar1 | 0x1000);
  delay(1);
  uVar1 = FUN_0000262c(iVar2 + 0x800,0);
  write__32((uint *)(iVar2 + 0x800),uVar1 | 1);
  write__32((uint *)(iVar2 + 0x808),
            *(int *)(param_1 + 0x1c) - 1U | (*(ushort *)(param_1 + 0x20) - 1) * 0x10000);
  write__32((uint *)(iVar2 + 0x810),
            *(int *)(param_1 + 0x1c) - 1U | (*(ushort *)(param_1 + 0x20) - 1) * 0x10000);
  write__32((uint *)(iVar2 + 0x840),*(int *)(param_1 + 0x1c) << 4);
  write__32((uint *)(iVar2 + 0x850),*(int *)(param_1 + 0x38) << 3);
  write__32((uint *)(iVar2 + 0x860),*(uint *)(param_1 + 0x38) >> 0x1d);
  write__32((uint *)(iVar2 + 0x8a0),0x500);
  uVar1 = FUN_0000262c(iVar2 + 0x800,0);
  write__32((uint *)(iVar2 + 0x800),uVar1 | 0x100);
  uVar1 = FUN_0000262c(iVar2 + 0x870,0);
  write__32((uint *)(iVar2 + 0x870),uVar1 | 1);
  uVar1 = FUN_0000262c(iVar2 + 0x800,0);
  write__32((uint *)(iVar2 + 0x800),uVar1 | 2);
  return;
}



void FUN_00002a5c(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 8);
  write__32((uint *)(iVar1 + 0x850),param_2 << 3);
  write__32((uint *)(iVar1 + 0x860),param_2 >> 0x1d);
  return;
}



void FUN_00002a90(int param_1)

{
  uint uVar1;
  uint *ptr;
  
  ptr = *(uint **)(param_1 + 0x10);
  uVar1 = FUN_0000262c(ptr,0);
  write__32(ptr,uVar1 | 0x80000000);
  return;
}



void FUN_00002ac4(int param_1)

{
  uint uVar1;
  uint *ptr;
  
  ptr = *(uint **)(param_1 + 0x10);
  write__32(ptr,0);
  write__32(ptr + 1,0);
  uVar1 = FUN_0000262c(ptr + 0x11,0);
  write__32(ptr + 0x11,uVar1 & 0xfffffff);
  write__32(ptr + 0x23,0xffffffff);
  write__32(ptr + 0x3d,0xffffffff);
  return;
}



void init_debe(uint xsize,uint ysize,uint p1,uint p2)

{
  int iVar1;
  int iVar2;
  
  *(undefined **)PTR_DAT_00002d6c = PTR_DAT_00002d68;
  iVar2 = DEBE_BASE;
  iVar1 = *(int *)PTR_DAT_00002d6c;
  *(undefined4 *)(iVar1 + 0xc) = 0;
  *(int *)(iVar1 + 8) = iVar2;
  iVar1 = *(int *)PTR_DAT_00002d6c;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(int *)(iVar1 + 0x10) = iVar2 + -0x254000;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x18) = 1;
  *(uint *)(*(int *)PTR_DAT_00002d6c + 0x1c) = xsize;
  *(uint *)(*(int *)PTR_DAT_00002d6c + 0x20) = ysize;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x2c) = 0x10;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x44) = 0xd2;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x48) = 0x2e;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x4c) = 0x14;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x50) = 0x16;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x54) = 0x17;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x58) = 10;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x5c) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x60) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 100) = 1;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x68) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x34) = 0;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x30) = 2;
  *(uint *)(*(int *)PTR_DAT_00002d6c + 0x38) = p1;
  *(undefined4 *)(*(int *)PTR_DAT_00002d6c + 0x3c) = 0;
  iVar2 = 0x800;
  while (iVar2 < 0x1000) {
    write__32((uint *)(iVar2 + 0x1e60000),0);
    iVar2 = iVar2 + 4;
  }
  FUN_00002ac4(*(undefined4 *)PTR_DAT_00002d6c);
  FUN_000028e4(*(undefined4 *)PTR_DAT_00002d6c);
  FUN_0000266c(*(undefined4 *)PTR_DAT_00002d6c);
  FUN_00002a90(*(undefined4 *)PTR_DAT_00002d6c);
  return;
}



void setup_display_pins(void)

{
  int Pin;
  
  Pin = 0;
  while (Pin < 0x16) {
    Config_GPIO_Pin(PD_CFG0,Pin,2);
    Pin = Pin + 1;
  }
  return;
}



void sys_init_display(uint xsize,uint ysize,uint p1,uint p2)

{
  setup_display_pins();
  init_debe(xsize,ysize,p1,p2);
  return;
}



uint * FUN_00002d78(uint *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  pcVar3 = (char *)((int)param_1 + 1);
  while (((uint)param_1 & 3) != 0) {
    cVar1 = *(char *)param_1;
    param_1 = (uint *)((int)param_1 + 1);
    if (cVar1 == '\0') {
      return (uint *)((int)param_1 - (int)pcVar3);
    }
  }
  do {
    uVar2 = *param_1;
    param_1 = param_1 + 1;
    uVar2 = uVar2 - DAT_00002db8 & ~uVar2 & DAT_00002db8 << 7;
  } while (uVar2 == 0);
  param_1 = (uint *)((int)param_1 - (int)pcVar3);
  if ((uVar2 & 0xff) != 0) {
    return (uint *)((int)param_1 + -3);
  }
  if ((uVar2 & 0xffff) == 0) {
    if ((uVar2 & 0xffffff) != 0) {
      return (uint *)((int)param_1 + -1);
    }
  }
  else {
    param_1 = (uint *)((int)param_1 + -2);
  }
  return param_1;
}



// WARNING: Removing unreachable block (ram,0x00002f18)
// WARNING: Removing unreachable block (ram,0x00002f24)
// WARNING: Removing unreachable block (ram,0x00002f14)

longlong FUN_00002f38(undefined4 param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  bool bVar9;
  longlong lVar10;
  
  lVar10 = FUN_00000140(param_1);
  uVar3 = (uint)((ulonglong)lVar10 >> 0x20);
  uVar1 = (uint)lVar10;
  iVar4 = 0;
  if (uVar3 <= uVar1 >> 2) {
    if (uVar3 <= uVar1 >> 5) {
      if (uVar3 <= uVar1 >> 8) {
        uVar2 = uVar3 << 6;
        iVar4 = -0x4000000;
        if (uVar1 >> 8 < uVar2) goto LAB_00002eac;
        uVar2 = uVar3 << 0xc;
        iVar4 = -0x100000;
        if (uVar1 >> 8 < uVar2) goto LAB_00002eac;
        uVar2 = uVar3 << 0x12;
        iVar4 = -0x4000;
        if (uVar2 <= uVar1 >> 8) {
          uVar2 = uVar3 << 0x18;
          iVar4 = -0x100;
        }
        bVar5 = uVar2 == 0;
        if (!bVar5) {
          do {
            if (bVar5) {
              uVar2 = uVar2 >> 6;
            }
LAB_00002eac:
            bVar5 = uVar2 <= uVar1 >> 7;
            if (bVar5) {
              uVar1 = uVar1 + uVar2 * -0x80;
            }
            bVar6 = uVar2 <= uVar1 >> 6;
            if (bVar6) {
              uVar1 = uVar1 + uVar2 * -0x40;
            }
            bVar7 = uVar2 <= uVar1 >> 5;
            if (bVar7) {
              uVar1 = uVar1 + uVar2 * -0x20;
            }
            bVar8 = uVar2 <= uVar1 >> 4;
            if (bVar8) {
              uVar1 = uVar1 + uVar2 * -0x10;
            }
            bVar9 = uVar2 <= uVar1 >> 3;
            if (bVar9) {
              uVar1 = uVar1 + uVar2 * -8;
            }
            uVar3 = ((((iVar4 * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 + (uint)bVar7) * 2 +
                    (uint)bVar8) * 2 + (uint)bVar9;
            bVar6 = uVar2 <= uVar1 >> 2;
            if (bVar6) {
              uVar1 = uVar1 + uVar2 * -4;
            }
            bVar5 = !bVar6 && CARRY4(uVar3,uVar3) || bVar6 && uVar3 * 2 + 1 <= uVar3;
            iVar4 = uVar3 * 2 + (uint)bVar6;
          } while (bVar5);
          bVar5 = uVar2 <= uVar1 >> 1;
          if (bVar5) {
            uVar1 = uVar1 + uVar2 * -2;
          }
          uVar3 = uVar1 - uVar2;
          if (uVar2 > uVar1) {
            uVar3 = uVar1;
          }
          return CONCAT44(uVar3,(iVar4 * 2 + (uint)bVar5) * 2 + (uint)(uVar2 <= uVar1));
        }
        return lVar10 << 0x20;
      }
      bVar5 = uVar3 <= uVar1 >> 7;
      if (bVar5) {
        uVar1 = uVar1 + uVar3 * -0x80;
      }
      bVar6 = uVar3 <= uVar1 >> 6;
      if (bVar6) {
        uVar1 = uVar1 + uVar3 * -0x40;
      }
      bVar7 = uVar3 <= uVar1 >> 5;
      if (bVar7) {
        uVar1 = uVar1 + uVar3 * -0x20;
      }
      iVar4 = ((uint)bVar5 * 2 + (uint)bVar6) * 2 + (uint)bVar7;
    }
    bVar5 = uVar3 <= uVar1 >> 4;
    if (bVar5) {
      uVar1 = uVar1 + uVar3 * -0x10;
    }
    bVar6 = uVar3 <= uVar1 >> 3;
    if (bVar6) {
      uVar1 = uVar1 + uVar3 * -8;
    }
    bVar7 = uVar3 <= uVar1 >> 2;
    if (bVar7) {
      uVar1 = uVar1 + uVar3 * -4;
    }
    iVar4 = ((iVar4 * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 + (uint)bVar7;
  }
  bVar5 = uVar3 <= uVar1 >> 1;
  if (bVar5) {
    uVar1 = uVar1 + uVar3 * -2;
  }
  uVar2 = uVar1 - uVar3;
  if (uVar3 > uVar1) {
    uVar2 = uVar1;
  }
  return CONCAT44(uVar2,(iVar4 * 2 + (uint)bVar5) * 2 + (uint)(uVar3 <= uVar1));
}



// WARNING: Removing unreachable block (ram,0x00002f18)
// WARNING: Removing unreachable block (ram,0x00002f24)
// WARNING: Removing unreachable block (ram,0x00002f14)
// WARNING: Unknown calling convention yet parameter storage is locked

uint divide(void)

{
  uint in_r0;
  uint uVar1;
  uint in_r1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  bool bVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  
  iVar3 = 0;
  if (in_r1 <= in_r0 >> 2) {
    if (in_r1 <= in_r0 >> 5) {
      if (in_r1 <= in_r0 >> 8) {
        uVar1 = in_r1 << 6;
        iVar3 = -0x4000000;
        if (in_r0 >> 8 < uVar1) goto LAB_00002eac;
        uVar1 = in_r1 << 0xc;
        iVar3 = -0x100000;
        if (in_r0 >> 8 < uVar1) goto LAB_00002eac;
        uVar1 = in_r1 << 0x12;
        iVar3 = -0x4000;
        if (uVar1 <= in_r0 >> 8) {
          uVar1 = in_r1 << 0x18;
          iVar3 = -0x100;
        }
        bVar4 = uVar1 == 0;
        if (!bVar4) {
          do {
            if (bVar4) {
              uVar1 = uVar1 >> 6;
            }
LAB_00002eac:
            bVar4 = uVar1 <= in_r0 >> 7;
            if (bVar4) {
              in_r0 = in_r0 + uVar1 * -0x80;
            }
            bVar5 = uVar1 <= in_r0 >> 6;
            if (bVar5) {
              in_r0 = in_r0 + uVar1 * -0x40;
            }
            bVar6 = uVar1 <= in_r0 >> 5;
            if (bVar6) {
              in_r0 = in_r0 + uVar1 * -0x20;
            }
            bVar7 = uVar1 <= in_r0 >> 4;
            if (bVar7) {
              in_r0 = in_r0 + uVar1 * -0x10;
            }
            bVar8 = uVar1 <= in_r0 >> 3;
            if (bVar8) {
              in_r0 = in_r0 + uVar1 * -8;
            }
            uVar2 = ((((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6) * 2 +
                    (uint)bVar7) * 2 + (uint)bVar8;
            bVar5 = uVar1 <= in_r0 >> 2;
            if (bVar5) {
              in_r0 = in_r0 + uVar1 * -4;
            }
            bVar4 = !bVar5 && CARRY4(uVar2,uVar2) || bVar5 && uVar2 * 2 + 1 <= uVar2;
            iVar3 = uVar2 * 2 + (uint)bVar5;
          } while (bVar4);
          bVar4 = uVar1 <= in_r0 >> 1;
          if (bVar4) {
            in_r0 = in_r0 + uVar1 * -2;
          }
          return (iVar3 * 2 + (uint)bVar4) * 2 + (uint)(uVar1 <= in_r0);
        }
        return 0;
      }
      bVar4 = in_r1 <= in_r0 >> 7;
      if (bVar4) {
        in_r0 = in_r0 + in_r1 * -0x80;
      }
      bVar5 = in_r1 <= in_r0 >> 6;
      if (bVar5) {
        in_r0 = in_r0 + in_r1 * -0x40;
      }
      bVar6 = in_r1 <= in_r0 >> 5;
      if (bVar6) {
        in_r0 = in_r0 + in_r1 * -0x20;
      }
      iVar3 = ((uint)bVar4 * 2 + (uint)bVar5) * 2 + (uint)bVar6;
    }
    bVar4 = in_r1 <= in_r0 >> 4;
    if (bVar4) {
      in_r0 = in_r0 + in_r1 * -0x10;
    }
    bVar5 = in_r1 <= in_r0 >> 3;
    if (bVar5) {
      in_r0 = in_r0 + in_r1 * -8;
    }
    bVar6 = in_r1 <= in_r0 >> 2;
    if (bVar6) {
      in_r0 = in_r0 + in_r1 * -4;
    }
    iVar3 = ((iVar3 * 2 + (uint)bVar4) * 2 + (uint)bVar5) * 2 + (uint)bVar6;
  }
  bVar4 = in_r1 <= in_r0 >> 1;
  if (bVar4) {
    in_r0 = in_r0 + in_r1 * -2;
  }
  return (iVar3 * 2 + (uint)bVar4) * 2 + (uint)(in_r1 <= in_r0);
}



// WARNING: Control flow encountered bad instruction data

uint FUN_00002fc4(uint param_1,uint param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  bool bVar5;
  
  iVar2 = (param_2 >> 0x14) - 0x400;
  bVar5 = SBORROW4(0x1e,iVar2);
  iVar1 = -iVar2;
  uVar3 = iVar1 + 0x1e;
  uVar4 = uVar3;
  if (iVar2 < 0x1f) {
    bVar5 = SBORROW4(0x20,uVar3);
    uVar4 = 0x20 - uVar3;
  }
  if ((int)uVar4 < 0 == bVar5) {
    return (param_2 << 0xb | 0x80000000 | param_1 >> 0x15) >> (uVar3 & 0xff);
  }
  if ((int)param_2 < 0) {
    return 0;
  }
  if (0x10 < (int)uVar3) {
    param_1 = 0;
  }
  if (uVar3 != 0x10 && iVar1 + 0xe < 0 == SBORROW4(uVar3,0x10)) {
    return param_1;
  }
  if (iVar1 != -0x3ff) {
    return 0xffffffff;
  }
  FUN_000031ac();
                    // WARNING: Bad instruction - Truncating control flow here
  halt_baddata();
}



longlong FUN_00003034(uint param_1,uint param_2,uint param_3,uint param_4)

{
  longlong lVar1;
  byte bVar2;
  uint uVar3;
  uint extraout_r1;
  int iVar4;
  uint uVar5;
  uint unaff_r5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  bool bVar13;
  bool bVar14;
  undefined4 in_cr0;
  undefined4 in_cr1;
  undefined4 in_cr9;
  
  bVar2 = (byte)(param_2 >> 3);
  uVar10 = DAT_000031a0 & param_2 >> 4;
  bVar14 = uVar10 == 0;
  if (!bVar14) {
    bVar2 = (byte)(param_4 >> 3);
    unaff_r5 = DAT_000031a0 & param_4 >> 4;
    bVar14 = unaff_r5 == 0;
  }
  bVar13 = (bool)(bVar2 & 1);
  if (!bVar14) {
    bVar14 = uVar10 == DAT_000031a0;
  }
  if (!bVar14) {
    bVar14 = unaff_r5 == DAT_000031a0;
  }
  if (bVar14) {
    if (uVar10 != DAT_000031a0 && (DAT_000031a0 & param_4 >> 4) != DAT_000031a0) {
      return (ulonglong)((param_2 ^ param_4) & 0x80000000) << 0x20;
    }
    FUN_000031ac();
    if (!bVar13) {
      coprocessor_function(0,0,4,in_cr0,in_cr1,in_cr9);
    }
    param_4 = extraout_r1 ^ param_4;
  }
  else {
    uVar3 = param_2 & ~(DAT_000031a0 << 5) | 0x100000;
    uVar5 = param_4 & ~(DAT_000031a0 << 5) | 0x100000;
    iVar11 = (uVar10 | (param_2 ^ param_4) >> 0x1f) + unaff_r5;
    lVar1 = (ulonglong)param_3 * (ulonglong)uVar3;
    uVar10 = (uint)lVar1;
    uVar9 = (uint)((ulonglong)lVar1 >> 0x20);
    lVar1 = (ulonglong)uVar5 * (ulonglong)param_1;
    uVar8 = (uint)lVar1;
    uVar6 = (uint)((ulonglong)lVar1 >> 0x20);
    iVar12 = iVar11 + -0x3fc0000;
    bVar14 = CARRY4(uVar8,uVar10);
    uVar8 = uVar8 + uVar10;
    uVar7 = uVar6 + uVar9 + (uint)bVar14;
    lVar1 = (ulonglong)uVar5 * (ulonglong)uVar3;
    uVar10 = (uint)lVar1;
    uVar3 = (uint)((ulonglong)param_3 * (ulonglong)param_1 >> 0x20);
    bVar13 = CARRY4(uVar8,uVar3);
    uVar8 = uVar8 + uVar3;
    uVar3 = uVar7 + uVar10 + (uint)bVar13;
    uVar10 = (int)((ulonglong)lVar1 >> 0x20) +
             (uint)(bVar14 == false && CARRY4(uVar6,uVar9) ||
                   bVar14 == true && uVar6 + uVar9 + 1 <= uVar6) +
             (uint)(bVar13 == false && CARRY4(uVar7,uVar10) ||
                   bVar13 == true && uVar7 + uVar10 + 1 <= uVar7);
    if ((int)((ulonglong)param_3 * (ulonglong)param_1) != 0) {
      uVar8 = uVar8 | 1;
    }
    if ((uVar10 & 0x200) == 0) {
      uVar5 = uVar8 << 0xc;
      uVar6 = uVar10 * 0x1000 | uVar3 >> 0x14;
      uVar10 = uVar3 * 0x1000 | uVar8 >> 0x14;
      iVar4 = -4;
    }
    else {
      uVar5 = uVar8 << 0xb;
      uVar6 = uVar10 * 0x800 | uVar3 >> 0x15;
      uVar10 = uVar3 * 0x800 | uVar8 >> 0x15;
      iVar4 = -3;
    }
    uVar3 = iVar4 + (iVar12 >> 0x10);
    param_4 = uVar6 + uVar3 * 0x100000 ^ iVar11 * -0x80000000;
    if (uVar5 != 0) {
      bVar2 = -(char)((int)uVar5 >> 0x1f);
      if ((uVar5 & 0x7fffffff) != 0) {
        uVar5 = 0;
      }
      param_4 = param_4 + (bVar2 == 1 && uVar10 + 1 <= uVar10);
      uVar10 = uVar10 + bVar2 & ~(uVar5 >> 0x1f);
    }
    if (uVar3 < DAT_000031a4) {
      return CONCAT44(param_4,uVar10);
    }
    if (0x3ffffff < iVar12) {
      param_4 = param_4 + 0xa0000000;
    }
    if (iVar11 + -0x7fc0000 < 0 != SBORROW4(iVar12,0x4000000)) {
      return (ulonglong)(param_4 + 0x60000000 & 0x80000000) << 0x20;
    }
  }
  return (ulonglong)(param_4 & 0x80000000 | 0x7ff00000) << 0x20;
}



undefined8 FUN_000031ac(int param_1,uint param_2,int param_3,uint param_4)

{
  uint unaff_r5;
  uint uVar1;
  uint *in_lr;
  bool bVar2;
  bool bVar3;
  undefined8 uVar4;
  
  if ((((int)*in_lr < 0) || (unaff_r5 = param_4 * 2 + (uint)(param_3 != 0), unaff_r5 < 0xffe00001))
     && (uVar1 = param_2 * 2 + (uint)(param_1 != 0), uVar1 < 0xffe00001)) {
    if (uVar1 == 0xffe00000) {
      uVar1 = ((int)param_2 >> 0x1f) * -3 + 2;
      if (unaff_r5 == 0xffe00000) {
        uVar1 = (uVar1 - ((int)param_4 >> 0x1f)) + (uint)(0xffdfffff < unaff_r5);
      }
    }
    else {
      uVar1 = param_4 >> 0x1f;
    }
  }
  else {
    uVar1 = 8;
  }
  uVar1 = *in_lr >> uVar1 * 3 & 7;
  switch(uVar1) {
  case 4:
    break;
  case 5:
    param_3 = param_1;
    param_4 = param_2;
    break;
  case 6:
  case 7:
    return 0x7ff8000000000000;
  default:
                    // WARNING: Could not recover jumptable at 0x0000321c. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar4 = (*(code *)(in_lr + uVar1 + 1))();
    return uVar4;
  }
  bVar2 = param_3 != 0;
  bVar3 = !bVar2 && CARRY4(param_4,param_4) || bVar2 && param_4 * 2 + 1 <= param_4;
  uVar1 = param_4 * 2 + (uint)bVar2;
  bVar2 = uVar1 != 0;
  if (bVar2) {
    bVar3 = uVar1 < 0x200001;
  }
  if (bVar3 && (bVar2 && uVar1 != 0x200000)) {
    param_3 = 0;
  }
  if (bVar3 && (bVar2 && uVar1 != 0x200000)) {
    param_4 = param_4 & 0x80000000;
  }
  return CONCAT44(param_4,param_3);
}



longlong FUN_00003274(uint param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  byte extraout_var;
  byte bVar3;
  uint uVar4;
  bool bVar5;
  bool bVar6;
  
  uVar1 = param_1 & 0x80000000;
  uVar2 = (param_1 << 1) >> 4;
  uVar4 = param_1 << 1 ^ param_1;
  bVar5 = uVar4 == 0;
  if (!bVar5) {
    param_1 = param_1 << 0x1d;
    param_2 = (uVar1 | uVar2) + 0x38000000;
    bVar5 = (uVar4 & 0x7f000000) == 0;
  }
  if (bVar5) {
    bVar6 = false;
    bVar5 = (uVar2 & 0x8000000) == 0;
    if (!bVar5) {
      FUN_00003308(uVar1 | param_1 >> 0x1d | uVar2 << 3);
      bVar3 = extraout_var;
      if (!bVar6 || bVar5) {
        bVar3 = 0;
      }
      return (ulonglong)((uint)(bVar3 >> 7) << 0x1f | 0x7ff00000) << 0x20;
    }
    return (ulonglong)uVar1 << 0x20;
  }
  return CONCAT44(param_2,param_1);
}



uint FUN_000032d8(uint param_1)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  
  uVar2 = param_1 & 0x80000000;
  if ((int)uVar2 < 0) {
    param_1 = -param_1;
  }
  uVar3 = count_leading_zeroes(param_1);
  uVar1 = param_1 << (uVar3 & 0xff);
  if (uVar1 == 0) {
    return param_1;
  }
  bVar4 = (bool)((byte)(uVar1 >> 7) & 1);
  uVar2 = (uVar2 | (0x9d - uVar3) * 0x800000) + (uVar1 >> 8) + (uint)bVar4;
  if (!bVar4) {
    return uVar2;
  }
  if ((uVar1 & 0x7f) == 0) {
    uVar2 = uVar2 & 0xfffffffe;
  }
  return uVar2;
}



uint FUN_00003308(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint *in_lr;
  bool bVar2;
  
  if ((((int)*in_lr < 0) || (param_3 = param_2 * 2, param_3 < 0xff000001)) &&
     (param_1 * 2 < 0xff000001)) {
    if (param_1 * 2 == 0xff000000) {
      uVar1 = ((int)param_1 >> 0x1f) * -3 + 2;
      if (param_3 == 0xff000000) {
        uVar1 = (uVar1 - ((int)param_2 >> 0x1f)) + (uint)(0xfeffffff < param_3);
      }
    }
    else {
      uVar1 = param_2 >> 0x1f;
    }
  }
  else {
    uVar1 = 8;
  }
  uVar1 = *in_lr >> uVar1 * 3 & 7;
  switch(uVar1) {
  case 4:
    break;
  case 5:
    param_2 = param_1;
    break;
  case 6:
  case 7:
    return 0x7fc00000;
  default:
                    // WARNING: Could not recover jumptable at 0x00003370. Too many branches
                    // WARNING: Treating indirect jump as call
    uVar1 = (*(code *)(in_lr + uVar1 + 1))();
    return uVar1;
  }
  bVar2 = SUB41(param_2 >> 0x1f,0);
  uVar1 = param_2 * 2;
  if (uVar1 != 0) {
    bVar2 = uVar1 < 0x1000001;
  }
  if (bVar2 && (uVar1 != 0 && uVar1 != 0x1000000)) {
    param_2 = param_2 & 0x80000000;
  }
  return param_2;
}


