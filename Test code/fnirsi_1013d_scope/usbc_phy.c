//----------------------------------------------------------------------------------------------------------------------------------

#include "usb_bsp.h"
#include <stdio.h>

//----------------------------------------------------------------------------------------------------------------------------------

//define USB PHY controller reg bit

//Common Control Bits for Both PHYs
#define  USBC_PHY_PLL_BW             0x03
#define  USBC_PHY_RES45_CAL_EN       0x0C

//Private Control Bits for Each PHY
#define  USBC_PHY_TX_AMPLITUDE_TUNE  0x20
#define  USBC_PHY_TX_SLEWRATE_TUNE   0x22
#define  USBC_PHY_VBUSVALID_TH_SEL   0x25
#define  USBC_PHY_PULLUP_RES_SEL     0x27
#define  USBC_PHY_OTG_FUNC_EN        0x28
#define  USBC_PHY_VBUS_DET_EN        0x29
#define  USBC_PHY_DISCON_TH_SEL      0x2A

//----------------------------------------------------------------------------------------------------------------------------------

void usb_phy_open_clock(void)
{
  volatile int i;

  USBC_REG_set_bit_l(USBPHY_CLK_GAT_BIT, USBPHY_CLK_REG);
  USBC_REG_set_bit_l(USBPHY_CLK_RST_BIT, USBPHY_CLK_REG);

  USBC_REG_set_bit_l(BUS_CLK_USB_BIT, BUS_CLK_GATE0_REG);
  USBC_REG_set_bit_l(BUS_RST_USB_BIT, BUS_CLK_RST_REG);
  
  i = 10000;
  while(i--);
}

//----------------------------------------------------------------------------------------------------------------------------------

static void usb_phy_write(int addr, int data, int len)
{
  int j = 0, usbc_bit = 0;
  void *dest = (void *) USBC_REG_CSR(USBC0_BASE);

  usbc_bit = 1 << (0 * 2);
  for(j = 0; j < len; j++)
  {
    //set the bit address to be written
    USBC_ClrBit_Mask_l(dest, 0xff << 8);
    USBC_SetBit_Mask_l(dest, (addr + j) << 8);

    USBC_ClrBit_Mask_l(dest, usbc_bit);
    
    //set data bit
    if(data & 0x1)
      USBC_SetBit_Mask_l(dest, 1 << 7);
    else
      USBC_ClrBit_Mask_l(dest, 1 << 7);

    USBC_SetBit_Mask_l(dest, usbc_bit);

    USBC_ClrBit_Mask_l(dest, usbc_bit);

    data >>= 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_PhyConfig(void)
{
  //Regulation 45 ohms
  usb_phy_write(0x0c, 0x01, 1);

  //adjust PHY's magnitude and rate
  usb_phy_write(0x20, 0x14, 5);

  //threshold adjustment disconnect
  usb_phy_write(0x2a, 3, 2);
}

//----------------------------------------------------------------------------------------------------------------------------------

int USBC_Dev_Read_EP0_CSR(void)
{
  return USBC_Readw(USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

void sun4i_usb_phy_set_squelch_detect(int enabled)
{
  usb_phy_write(0x3c, (enabled == 1) ? 0 : 2, 2);
}

//----------------------------------------------------------------------------------------------------------------------------------
