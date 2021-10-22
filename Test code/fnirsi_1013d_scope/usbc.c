//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "usb_bsp.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define USBC_MAX_OPEN_NUM 1

//static __usbc_otg_t usbc_otg_array[USBC_MAX_OPEN_NUM];  //usbc internal use, in charge of USB port
//static __fifo_info_t usbc_info_g;

//----------------------------------------------------------------------------------------------------------------------------------
//get vbus current state
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//
//return the current VBUS state
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_GetVbusStatus(void)
{
  uint8 reg_val = 0;
  reg_val = USBC_Readb(USBC_REG_DEVCTL(USBC0_BASE));

  reg_val = reg_val >> USBC_BP_DEVCTL_VBUS;

  switch(reg_val & 0x03)
  {
  case 0x00:
    return USBC_VBUS_STATUS_BELOW_SESSIONEND;
    //break;
  case 0x01:
    return USBC_VBUS_STATUS_ABOVE_SESSIONEND_BELOW_AVALID;
    //break;
  case 0x02:
    return USBC_VBUS_STATUS_ABOVE_AVALID_BELOW_VBUSVALID;
    //break;
  case 0x03:
    return USBC_VBUS_STATUS_ABOVE_VBUSVALID;
    //break;
  default:
    return USBC_VBUS_STATUS_BELOW_SESSIONEND;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//select the function type, now is for host, or device
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_OTG_SelectMode(uint32 mode)
{
  if(mode == USBC_OTG_HOST)
  {

  }
  else
  {

  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//get the length of data that can be read from current FIFO
//@hUSB:     handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:  ep type, tx or rx
//
//return the data length that can be current read
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_ReadLenFromFifo(uint32 ep_type)
{

  switch(ep_type)
  {
  case USBC_EP_TYPE_EP0:
    return USBC_Readw(USBC_REG_COUNT0(USBC0_BASE));
    //break;
  case USBC_EP_TYPE_TX:
    return 0;
    //break;
  case USBC_EP_TYPE_RX:
    return USBC_Readw(USBC_REG_RXCOUNT(USBC0_BASE));
    //break;
  default:
    return 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//write data packet to fifo
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//@fifo: fifo address
//@cnt:  data length
//@buff: store the data to be written
//
//return the length that successfully written
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_WritePacket(void *fifo, uint32 cnt, void *buff)
{
  uint32 len = 0;
  uint32 i32 = 0;
  uint32 i8 = 0;
  uint8 *buf8 = 0;
  uint32 *buf32 = 0;

  //--<1>-- adjust data
  buf32 = buff;
  len = cnt;

  i32 = len >> 2;
  i8 = len & 0x03;

  //--<2>-- deal with 4byte part
  while(i32--)
  {

    USBC_Writel(*buf32++, fifo);
  }

  //--<3>-- deal with no 4byte part
  buf8 = (uint8 *) buf32;

  while(i8--)
  {
    USBC_Writeb(*buf8++, fifo);
  }

  return (len);
}

//----------------------------------------------------------------------------------------------------------------------------------
//read data from fifo
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//@fifo: fifo address
//@cnt:  data length
//@buff: store the data that will be read
//
//return the lenght that successfully read
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_ReadPacket(void *fifo, uint32 cnt, void *buff)
{

  uint32 len = 0;
  uint32 i32 = 0;
  uint32 i8 = 0;
  uint8 *buf8 = 0;
  uint32 *buf32 = 0;

  //--<1>-- adjust data
  buf32 = buff;
  len = cnt;

  i32 = len >> 2;
  i8 = len & 0x03;

  //--<2>-- deal with 4byte part
  while(i32--)
  {
    *buf32++ = USBC_Readl(fifo);
  }

  //--<3>-- deal with no 4byte part
  buf8 = (uint8 *) buf32;

  while(i8--)
  {
    *buf8++ = USBC_Readb(fifo);
  }

  return (len);
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_ConfigFIFO_Base(void)
{
  uint32 reg_value;

  //config usb fifo, 8kb mode
  reg_value = USBC_Readl(SUNXI_SRAMC_BASE + 0x04);
  reg_value &= ~(0x03 << 0);
  reg_value |= (1 << 0);
  USBC_Writel(reg_value, SUNXI_SRAMC_BASE + 0x04);
}

//----------------------------------------------------------------------------------------------------------------------------------

void *USBC_SelectFIFO(uint32 ep_index)
{
  return (void*) USBC_REG_EPFIFOx(USBC0_BASE, ep_index);
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ConfigFifo_TxEp_Default(void)
{
  USBC_Writew(0x00, USBC_REG_TXFIFOAD(USBC0_BASE));
  USBC_Writeb(0x00, USBC_REG_TXFIFOSZ(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//set tx ep's fifo address and size
//@hUSB:           handle return by USBC_open_otg, include the key data which USBC need
//@is_double_fifo: if use hardware double fifo
//@fifo_size:      fifo size = 2 ^ fifo_size
//@fifo_addr:      fifo start addr = fifo_addr//8
//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ConfigFifo_TxEp(uint32 is_double_fifo, uint32 fifo_size, uint32 fifo_addr)
{
  uint32 temp = 0;
  uint32 size = 0; //fifo_size = 2^ (size + 3)
  uint32 addr = 0; //fifo_addr = addr//8

  //--<1>-- 512 align
  temp = fifo_size + 511;
  temp &= ~511;
  temp >>= 3;
  temp >>= 1;
  while(temp)
  {
    size++;
    temp >>= 1;
  }

  //--<2>-- calculate addr
  addr = fifo_addr >> 3;

  //--<3>--config fifo addr
  USBC_Writew(addr, USBC_REG_TXFIFOAD(USBC0_BASE));

  //--<4>--config fifo size
  USBC_Writeb((size & 0x0f), USBC_REG_TXFIFOSZ(USBC0_BASE));
  if(is_double_fifo)
  {
    USBC_REG_set_bit_b(USBC_BP_TXFIFOSZ_DPB, USBC_REG_TXFIFOSZ(USBC0_BASE));
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ConfigFifo_RxEp_Default(void)
{
  USBC_Writew(0x00, USBC_REG_RXFIFOAD(USBC0_BASE));
  USBC_Writeb(0x00, USBC_REG_RXFIFOSZ(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//set rx ep's fifo address and size
//@hUSB:           handle return by USBC_open_otg, include the key data which USBC need
//@is_double_fifo: if use hardware double fifo
//@fifo_size:      fifo size = 2 ^ fifo_size
//@fifo_addr:      fifo start addr = fifo_addr//8
//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ConfigFifo_RxEp(uint32 is_double_fifo, uint32 fifo_size, uint32 fifo_addr)
{
  uint32 temp = 0;
  uint32 size = 0; //fifo_size = 2 ^ (size + 3)
  uint32 addr = 0; //fifo_addr = addr//8

  //--<1>-- 512 align
  temp = fifo_size + 511;
  temp &= ~511;
  temp >>= 3;
  temp >>= 1;
  while(temp)
  {
    size++;
    temp >>= 1;
  }

  //--<2>--calculate addr
  addr = fifo_addr >> 3;

  //--<3>--config fifo addr
  USBC_Writew(addr, USBC_REG_RXFIFOAD(USBC0_BASE));

  //--<2>--config fifo size
  USBC_Writeb((size & 0x0f), USBC_REG_RXFIFOSZ(USBC0_BASE));
  if(is_double_fifo)
  {
    USBC_REG_set_bit_b(USBC_BP_RXFIFOSZ_DPB, USBC_REG_RXFIFOSZ(USBC0_BASE));
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//config ep's fifo addr and size
//@hUSB:     handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:  ep type
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_ConfigFifo_Default(uint32 ep_type)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_EP0:
    //not support
    break;
  case USBC_EP_TYPE_TX:
    USBC_ConfigFifo_TxEp_Default();
    break;
  case USBC_EP_TYPE_RX:
    USBC_ConfigFifo_RxEp_Default();
    break;
  default:
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//config ep's fifo addr and size
//@hUSB:           handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:        ep type
//@is_double_fifo: if use hardware double fifo
//@fifo_size:      fifo size = 2 ^ fifo_size
//@fifo_addr:      fifo start addr = fifo_addr//8
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_ConfigFifo(uint32 ep_type, uint32 is_double_fifo, uint32 fifo_size, uint32 fifo_addr)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_EP0:
    //not support
    USBC_ConfigFifo_TxEp(is_double_fifo, fifo_size, fifo_addr);
    USBC_ConfigFifo_RxEp(is_double_fifo, fifo_size, fifo_addr);
    break;
  case USBC_EP_TYPE_TX:
    USBC_ConfigFifo_TxEp(is_double_fifo, fifo_size, fifo_addr);
    break;
  case USBC_EP_TYPE_RX:
    USBC_ConfigFifo_RxEp(is_double_fifo, fifo_size, fifo_addr);
    break;
  default:
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//get the last frma number
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_GetLastFrameNumber(void)
{
  return USBC_Readl(USBC_REG_FRNUM(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//get status of DP
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_GetStatus_Dp(void)
{
  uint32 temp = 0;
  temp = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  temp = (temp >> USBC_BP_ISCR_EXT_DP_STATUS) & 0x01;

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------
//get status of DM
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_GetStatus_Dm(void)
{
  uint32 temp = 0;

  temp = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  temp = (temp >> USBC_BP_ISCR_EXT_DM_STATUS) & 0x01;

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------
//get status of DpDm
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_GetStatus_DpDm(void)
{
  uint32 temp = 0;
  uint32 dp = 0;
  uint32 dm = 0;


  temp = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  dp = (temp >> USBC_BP_ISCR_EXT_DP_STATUS) & 0x01;
  dm = (temp >> USBC_BP_ISCR_EXT_DM_STATUS) & 0x01;
  return ((dp << 1) | dm);

}

//----------------------------------------------------------------------------------------------------------------------------------
//get current OTG mode from vendor0's id
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//
//return USBC_OTG_DEVICE / USBC_OTG_HOST
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_GetOtgMode_Form_ID(void)
{
  uint32 mode = 0;

  mode = USBC_REG_test_bit_l(USBC_BP_ISCR_MERGED_ID_STATUS, USBC_REG_ISCR(USBC0_BASE));
  if(mode)
  {
    return USBC_OTG_DEVICE;
  }
  else
  {
    return USBC_OTG_HOST;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//get current OTG mode from OTG Device's B-Device
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//
//return USBC_OTG_DEVICE / USBC_OTG_HOST
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_GetOtgMode_Form_BDevice(void)
{
  uint32 mode = 0;

  mode = USBC_REG_test_bit_b(USBC_BP_DEVCTL_B_DEVICE, USBC_REG_DEVCTL(USBC0_BASE));
  if(mode)
  {
    return USBC_OTG_DEVICE;
  }
  else
  {
    return USBC_OTG_HOST;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//otg and hci0 Controller Shared phy in SUN50I
//select 1:to device,0:hci
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_SelectPhyToDevice(void)
{
  int reg_value = 0;
  reg_value = USBC_Readl(USBC0_BASE + 0x420);
  reg_value |= (0x01);
  USBC_Writel(reg_value, (USBC0_BASE + 0x420));
}

//----------------------------------------------------------------------------------------------------------------------------------
//select the bus way for data transfer
//@hUSB:     handle return by USBC_open_otg, include the key data which USBC need
//@io_type:  bus type, pio or dma
//@ep_type:  ep type, rx or tx
//@ep_index: ep index
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_SelectBus(uint32 io_type, uint32 ep_type, uint32 ep_index)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readb(USBC_REG_VEND0(USBC0_BASE));
  if(io_type == USBC_IO_TYPE_DMA)
  {
    if(ep_type == USBC_EP_TYPE_TX)
    {
      reg_val |= ((ep_index - 0x01) << 1) << USBC_BP_VEND0_DRQ_SEL; //drq_sel
      reg_val |= 0x1 << USBC_BP_VEND0_BUS_SEL; //io_dma
    }
    else
    {
      reg_val |= ((ep_index << 1) - 0x01) << USBC_BP_VEND0_DRQ_SEL;
      reg_val |= 0x1 << USBC_BP_VEND0_BUS_SEL;
    }
  }
  else
  {
    //reg_val &= ~(0x1 << USBC_BP_VEND0_DRQ_SEL);  //clear drq_sel, select pio
    reg_val &= 0x00; // clear drq_sel, select pio
  }

  //in 1667 1673 and later ic, FIFO_BUS_SEL bit(bit24 of reg0x40 for host/device)
  //is fixed to 1, the hw guarantee that it's ok for cpu/inner_dma/outer_dma transfer

  //	reg_val |= 0x1<<USBC_BP_VEND0_BUS_SEL;  //for 1663 set 1: enable dma, set 0: enable fifo

  USBC_Writeb(reg_val, USBC_REG_VEND0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//get tx ep's interrupt flag

static uint32 USBC_INT_TxPending(void)
{
  return (USBC_Readw(USBC_REG_INTTx(USBC0_BASE)));
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear tx ep's interrupt flag

static void USBC_INT_ClearTxPending(uint8 ep_index)
{
  USBC_Writew((1 << ep_index), USBC_REG_INTTx(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear all the tx ep's interrupt flag

static void USBC_INT_ClearTxPendingAll(void)
{
  USBC_Writew(0xffff, USBC_REG_INTTx(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//get rx ep's interrupt flag

static uint32 USBC_INT_RxPending(void)
{
  return (USBC_Readw(USBC_REG_INTRx(USBC0_BASE)));
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear rx ep's interrupt flag

static void USBC_INT_ClearRxPending(uint8 ep_index)
{
  USBC_Writew((1 << ep_index), USBC_REG_INTRx(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear all the rx ep's interrupt flag

static void USBC_INT_ClearRxPendingAll(void)
{
  USBC_Writew(0xffff, USBC_REG_INTRx(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//open a tx ep's interrupt

static void USBC_INT_EnableTxEp(uint8 ep_index)
{
  USBC_REG_set_bit_w(ep_index, USBC_REG_INTTxE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//open a rx ep's interrupt

static void USBC_INT_EnableRxEp(uint8 ep_index)
{
  USBC_REG_set_bit_w(ep_index, USBC_REG_INTRxE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//close a tx ep's interrupt

static void USBC_INT_DisableTxEp(uint8 ep_index)
{
  USBC_REG_clear_bit_w(ep_index, USBC_REG_INTTxE(USBC0_BASE));
}

//close a rx ep's interrupt

static void USBC_INT_DisableRxEp(uint8 ep_index)
{
  USBC_REG_clear_bit_w(ep_index, USBC_REG_INTRxE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//close all tx ep's interrupt

static void USBC_INT_DisableTxAll(void)
{
  USBC_Writew(0, USBC_REG_INTTxE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//close all rx ep's interrupt

static void USBC_INT_DisableRxAll(void)
{
  USBC_Writew(0, USBC_REG_INTRxE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//get ep's interrupt flag

uint32 USBC_INT_EpPending(uint32 ep_type)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_EP0:
  case USBC_EP_TYPE_TX:
    return USBC_INT_TxPending();

  case USBC_EP_TYPE_RX:
    return USBC_INT_RxPending();

  default:
    return 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear ep's interrupt flag

void USBC_INT_ClearEpPending(uint32 ep_type, uint8 ep_index)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_EP0:
  case USBC_EP_TYPE_TX:
    USBC_INT_ClearTxPending(ep_index);
    break;

  case USBC_EP_TYPE_RX:
    USBC_INT_ClearRxPending(ep_index);
    break;

  default:
    break;
  }

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear ep's interrupt flag

void USBC_INT_ClearEpPendingAll(uint32 ep_type)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_EP0:
  case USBC_EP_TYPE_TX:
    USBC_INT_ClearTxPendingAll();
    break;

  case USBC_EP_TYPE_RX:
    USBC_INT_ClearRxPendingAll();
    break;

  default:
    break;
  }

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------
//get usb misc's interrupt flag

uint32 USBC_INT_MiscPending(void)
{
  return (USBC_Readb(USBC_REG_INTUSB(USBC0_BASE)));
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear usb misc's interrupt flag

void USBC_INT_ClearMiscPending(uint32 mask)
{
  USBC_Writeb(mask, USBC_REG_INTUSB(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear all the usb misc's interrupt flag

void USBC_INT_ClearMiscPendingAll(void)
{
  USBC_Writeb(0xff, USBC_REG_INTUSB(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//open a ep's interrupt

void USBC_INT_EnableEp(uint32 ep_type, uint8 ep_index)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_TX:
    USBC_INT_EnableTxEp(ep_index);
    break;

  case USBC_EP_TYPE_RX:
    USBC_INT_EnableRxEp(ep_index);
    break;

  default:
    break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//open a usb misc's interrupt

void USBC_INT_EnableUsbMiscUint(uint32 mask)
{
  uint32 reg_val;
  reg_val = USBC_Readb(USBC_REG_INTUSBE(USBC0_BASE));
  reg_val |= mask;
  USBC_Writeb(reg_val, USBC_REG_INTUSBE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//close a ep's interrupt

void USBC_INT_DisableEp(uint32 ep_type, uint8 ep_index)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_TX:
    USBC_INT_DisableTxEp(ep_index);
    break;

  case USBC_EP_TYPE_RX:
    USBC_INT_DisableRxEp(ep_index);
    break;

  default:
    break;
  }

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------
//close a usb misc's interrupt

void USBC_INT_DisableUsbMiscUint(uint32 mask)
{
  uint32 reg_val;
  reg_val = USBC_Readb(USBC_REG_INTUSBE(USBC0_BASE));
  reg_val &= ~mask;
  USBC_Writeb(reg_val, USBC_REG_INTUSBE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//close all ep's interrupt

void USBC_INT_DisableEpAll(uint32 ep_type)
{
  switch(ep_type)
  {
  case USBC_EP_TYPE_TX:
    USBC_INT_DisableTxAll();
    break;

  case USBC_EP_TYPE_RX:
    USBC_INT_DisableRxAll();
    break;

  default:
    break;
  }

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------
//close all usb misc's interrupt

void USBC_INT_DisableUsbMiscAll(void)
{
  USBC_Writeb(0, USBC_REG_INTUSBE(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//get current active ep

uint32 USBC_GetActiveEp(void)
{

  return USBC_Readb(USBC_REG_EPIND(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//set the active ep

void USBC_SelectActiveEp(uint8 ep_index)
{
  USBC_Writeb(ep_index, USBC_REG_EPIND(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enhance usb transfer signal

void USBC_EnhanceSignal(void)
{
  return;
}

//----------------------------------------------------------------------------------------------------------------------------------
//enter TestPacket mode

void USBC_EnterMode_TestPacket(void)
{
  USBC_REG_set_bit_b(USBC_BP_TMCTL_TEST_PACKET, USBC_REG_TMCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enter Test_K mode

void USBC_EnterMode_Test_K(void)
{
  USBC_REG_set_bit_b(USBC_BP_TMCTL_TEST_K, USBC_REG_TMCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enter Test_J mode

void USBC_EnterMode_Test_J(void)
{
  USBC_REG_set_bit_b(USBC_BP_TMCTL_TEST_J, USBC_REG_TMCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enter Test_SE0_NAK mode

void USBC_EnterMode_Test_SE0_NAK(void)
{
  USBC_REG_set_bit_b(USBC_BP_TMCTL_TEST_SE0_NAK, USBC_REG_TMCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear all test mode

void USBC_EnterMode_Idle(void)
{
  USBC_REG_clear_bit_b(USBC_BP_TMCTL_TEST_PACKET, USBC_REG_TMCTL(USBC0_BASE));
  USBC_REG_clear_bit_b(USBC_BP_TMCTL_TEST_K, USBC_REG_TMCTL(USBC0_BASE));
  USBC_REG_clear_bit_b(USBC_BP_TMCTL_TEST_J, USBC_REG_TMCTL(USBC0_BASE));
  USBC_REG_clear_bit_b(USBC_BP_TMCTL_TEST_SE0_NAK, USBC_REG_TMCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//vbus, id, dpdm, these bit is set 1 to clear, so we clear these bit when operate other bits

static uint32 USBC_WakeUp_ClearChangeDetect(uint32 reg_val)
{
  uint32 temp = reg_val;

  temp &= ~(1 << USBC_BP_ISCR_VBUS_CHANGE_DETECT);
  temp &= ~(1 << USBC_BP_ISCR_ID_CHANGE_DETECT);
  temp &= ~(1 << USBC_BP_ISCR_DPDM_CHANGE_DETECT);

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_SetWakeUp_Default(void)
{
  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_EnableIdPullUp(void)
{
  uint32 reg_val = 0;

  //vbus, id, dpdm, these bit is set 1 to clear, so we clear these bit when operate other bits
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val |= (1 << USBC_BP_ISCR_ID_PULLUP_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_DisableIdPullUp(void)
{
  uint32 reg_val = 0;

  //vbus, id, dpdm, these bit is set 1 to clear, so we clear these bit when operate other bits
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(1 << USBC_BP_ISCR_ID_PULLUP_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_EnableDpDmPullUp(void)
{
  uint32 reg_val = 0;

  //vbus, id, dpdm, these bit is set 1 to clear, so we clear these bit when operate other bits
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val |= (1 << USBC_BP_ISCR_DPDM_PULLUP_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_DisableDpDmPullUp(void)
{
  uint32 reg_val = 0;

  //vbus, id, dpdm, these bit is set 1 to clear, so we clear these bit when operate other bits
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(1 << USBC_BP_ISCR_DPDM_PULLUP_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ForceIdDisable(void)
{
  uint32 reg_val = 0;

  //vbus, id, dpdm, these bit is set 1 to clear, so we clear these bit when operate other bits
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_ID);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ForceIdToLow(void)
{
  uint32 reg_val = 0;

  //first write 00, then write 10
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_ID);
  reg_val |= (0x02 << USBC_BP_ISCR_FORCE_ID);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ForceIdToHigh(void)
{
  uint32 reg_val = 0;

  //first write 00, then write 10
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  //reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_ID);
  reg_val |= (0x03 << USBC_BP_ISCR_FORCE_ID);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//force id to (id_type)

void USBC_ForceId(uint32 id_type)
{

  switch(id_type)
  {
  case USBC_ID_TYPE_HOST:
    USBC_ForceIdToLow();
    break;

  case USBC_ID_TYPE_DEVICE:
    USBC_ForceIdToHigh();
    break;

  default:
    USBC_ForceIdDisable();
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ForceVbusValidDisable(void)
{
  uint32 reg_val = 0;

  //first write 00, then write 10
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_VBUS_VALID);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ForceVbusValidToLow(void)
{
  uint32 reg_val = 0;

  //first write 00, then write 10
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_VBUS_VALID);
  reg_val |= (0x02 << USBC_BP_ISCR_FORCE_VBUS_VALID);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_ForceVbusValidToHigh(void)
{
  uint32 reg_val = 0;

  //first write 00, then write 11
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(0x03 << USBC_BP_ISCR_FORCE_VBUS_VALID);
  reg_val |= (0x03 << USBC_BP_ISCR_FORCE_VBUS_VALID);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//force vbus valid to (id_type)

void USBC_ForceVbusValid(uint32 vbus_type)
{
  switch(vbus_type)
  {
  case USBC_VBUS_TYPE_LOW:
    USBC_ForceVbusValidToLow();
    break;

  case USBC_VBUS_TYPE_HIGH:
    USBC_ForceVbusValidToHigh();
    break;

  default:
    USBC_ForceVbusValidDisable();
  }

}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_A_valid_InputSelect(uint32 source)
{
  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_EnableUsbLineStateBypass(void)
{
  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_DisableUsbLineStateBypass(void)
{
  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_EnableHosc(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val |= 1 << USBC_BP_ISCR_HOSC_EN;
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//forbidden Hosc

void USBC_DisableHosc(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(1 << USBC_BP_ISCR_HOSC_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//check if vbus irq occur

uint32 USBC_IsVbusChange(void)
{
  uint32 reg_val = 0;
  uint32 temp = 0;

  // when read the volatile bit, write 1 clear it synchronously.
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));

  temp = reg_val & (1 << USBC_BP_ISCR_VBUS_CHANGE_DETECT);

  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  reg_val |= 1 << USBC_BP_ISCR_VBUS_CHANGE_DETECT;
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------
//check if id irq occur

uint32 USBC_IsIdChange(void)
{
  uint32 reg_val = 0;
  uint32 temp = 0;

  // when read the volatile bit, write 1 clear it synchronously.
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));

  temp = reg_val & (1 << USBC_BP_ISCR_ID_CHANGE_DETECT);

  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  reg_val |= 1 << USBC_BP_ISCR_ID_CHANGE_DETECT;
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------
//check if dpdm irq occur

uint32 USBC_IsDpDmChange(void)
{
  uint32 reg_val = 0;
  uint32 temp = 0;

  // when read the volatile bit, write 1 clear it synchronously.
  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));

  temp = reg_val & (1 << USBC_BP_ISCR_DPDM_CHANGE_DETECT);

  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  reg_val |= 1 << USBC_BP_ISCR_DPDM_CHANGE_DETECT;
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));

  return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------
//disable wake irq

void USBC_DisableWakeIrq(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(1 << USBC_BP_ISCR_IRQ_ENABLE);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//disable vbus irq

void USBC_DisableVbusChange(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(1 << USBC_BP_ISCR_VBUS_CHANGE_DETECT_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//disable id irq

void USBC_DisableIdChange(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(1 << USBC_BP_ISCR_ID_CHANGE_DETECT_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//disable dpdm irq

void USBC_DisableDpDmChange(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val &= ~(1 << USBC_BP_ISCR_DPDM_CHANGE_DETECT_EN);
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enable wake irq

void USBC_EnableWakeIrq(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val |= 1 << USBC_BP_ISCR_IRQ_ENABLE;
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enable vbus irq

void USBC_EnableVbusChange(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val |= 1 << USBC_BP_ISCR_VBUS_CHANGE_DETECT_EN;
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enable id irq

void USBC_EnableIdChange(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val |= 1 << USBC_BP_ISCR_ID_CHANGE_DETECT_EN;
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//enable dmdp irq

void USBC_EnableDpDmChange(void)
{
  uint32 reg_val = 0;

  reg_val = USBC_Readl(USBC_REG_ISCR(USBC0_BASE));
  reg_val |= 1 << USBC_BP_ISCR_DPDM_CHANGE_DETECT_EN;
  reg_val = USBC_WakeUp_ClearChangeDetect(reg_val);
  USBC_Writel(reg_val, USBC_REG_ISCR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//test mode, get the reg value

uint32 USBC_TestMode_ReadReg(uint32 offset, uint32 reg_width)
{
  uint32 reg_val = 0;

  if(reg_width == 8)
  {
    reg_val = USBC_Readb(USBC0_BASE + offset);
  }
  else if(reg_width == 16)
  {
    reg_val = USBC_Readw(USBC0_BASE + offset);
  }
  else if(reg_width == 32)
  {
    reg_val = USBC_Readl(USBC0_BASE + offset);
  }
  else
  {
    reg_val = 0;
  }

  return reg_val;
}

//----------------------------------------------------------------------------------------------------------------------------------
