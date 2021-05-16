//----------------------------------------------------------------------------------------------------------------------------------

#ifndef F1C100S_STRUCTS_H
#define F1C100S_STRUCTS_H

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagF1C100S_CCU        F1C100S_CCU;
typedef struct tagF1C100S_DRAMC      F1C100S_DRAMC;

//----------------------------------------------------------------------------------------------------------------------------------

typedef union tagF1C100S_MEMORY      F1C100S_MEMORY;

//----------------------------------------------------------------------------------------------------------------------------------

union tagF1C100S_MEMORY
{
  u_int32_t  m_32bit;
  u_int16_t  m_16bit[2];
  u_int8_t   m_8bit[4];
};

//----------------------------------------------------------------------------------------------------------------------------------
//The clock control register set
struct tagF1C100S_CCU
{
  F1C100S_MEMORY pll_cpu_ctrl;
  F1C100S_MEMORY pll_audio_ctrl;
  F1C100S_MEMORY pll_video_ctrl;
  F1C100S_MEMORY pll_ve_ctrl;
  F1C100S_MEMORY pll_ddr_ctrl;
  F1C100S_MEMORY pll_periph_ctrl;
  F1C100S_MEMORY cpu_clk_src;
  F1C100S_MEMORY ahb_apb_cfg;
  F1C100S_MEMORY bus_clk_gate0;
  F1C100S_MEMORY bus_clk_gate1;
  F1C100S_MEMORY bus_clk_gate2;
  F1C100S_MEMORY sdmmc0_clk;
  F1C100S_MEMORY sdmmc1_clk;
  F1C100S_MEMORY daudio_clk;
  F1C100S_MEMORY spdif_clk;
  F1C100S_MEMORY i2s_clk;
  F1C100S_MEMORY usbphy_cfg;
  F1C100S_MEMORY dram_clk_gate;
  F1C100S_MEMORY debe_clk;
  F1C100S_MEMORY defe_clk;
  F1C100S_MEMORY lcd_clk;
  F1C100S_MEMORY deinterlace_clk;
  F1C100S_MEMORY tve_clk;
  F1C100S_MEMORY tvd_clk;
  F1C100S_MEMORY csi_clk;
  F1C100S_MEMORY ve_clk;
  F1C100S_MEMORY adda_clk;
  F1C100S_MEMORY avs_clk;
  F1C100S_MEMORY pll_stable_time0;
  F1C100S_MEMORY pll_stable_time1;
  F1C100S_MEMORY pll_cpu_bias;
  F1C100S_MEMORY pll_audio_bias;
  F1C100S_MEMORY pll_video_bias;
  F1C100S_MEMORY pll_ve_bias;
  F1C100S_MEMORY pll_ddr0_bias;
  F1C100S_MEMORY pll_periph_bias;
  F1C100S_MEMORY pll_cpu_tun;
  F1C100S_MEMORY pll_ddr_tun;
  F1C100S_MEMORY pll_audio_pat;
  F1C100S_MEMORY pll_video_pat;
  F1C100S_MEMORY pll_ddr0_pat;
  F1C100S_MEMORY bus_soft_rst0;
  F1C100S_MEMORY bus_soft_rst1;
  F1C100S_MEMORY bus_soft_rst2;
};

//----------------------------------------------------------------------------------------------------------------------------------
//The clock control register set
struct tagF1C100S_DRAMC
{
  F1C100S_MEMORY sconr;
  F1C100S_MEMORY stmg0r;
  F1C100S_MEMORY stmg1r;
  F1C100S_MEMORY sctlr;
  F1C100S_MEMORY srefr;
  F1C100S_MEMORY sextmr;
  F1C100S_MEMORY ddlyr;
  F1C100S_MEMORY dadrr;
  F1C100S_MEMORY dvalr;
  F1C100S_MEMORY drptr0;
  F1C100S_MEMORY drptr1;
  F1C100S_MEMORY drptr2;
  F1C100S_MEMORY drptr3;
  F1C100S_MEMORY sefr;
  F1C100S_MEMORY mae;
  F1C100S_MEMORY aspr;
  F1C100S_MEMORY sdly0;
  F1C100S_MEMORY sdly1;
  F1C100S_MEMORY sdly2;
  F1C100S_MEMORY mcr0;
  F1C100S_MEMORY mcr1;
  F1C100S_MEMORY mcr2;
  F1C100S_MEMORY mcr3;
  F1C100S_MEMORY mcr4;
  F1C100S_MEMORY mcr5;
  F1C100S_MEMORY mcr6;
  F1C100S_MEMORY mcr7;
  F1C100S_MEMORY mcr8;
  F1C100S_MEMORY mcr9;
  F1C100S_MEMORY mcr10;
  F1C100S_MEMORY mcr11;
  F1C100S_MEMORY bwcr;
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* F1C100S_STRUCTS_H */

