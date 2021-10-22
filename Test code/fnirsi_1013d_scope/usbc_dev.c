//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "usb_bsp.h"

//----------------------------------------------------------------------------------------------------------------------------------
//select the usb transfer type, eg control/iso/interrupt/bulk transfer
 
static void USBC_Dev_TsType_default(void)
{
	//disable all transfer type
	USBC_REG_clear_bit_b(USBC_BP_POWER_D_ISO_UPDATE_EN, USBC_REG_PCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_TsType_Ctrl(void)
{
	//--<1>--disable other transfer type
	USBC_REG_clear_bit_b(USBC_BP_POWER_D_ISO_UPDATE_EN, USBC_REG_PCTL(USBC0_BASE));

	//--<2>--select Ctrl type
	//do not need config
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_TsType_Iso(void)
{
	//--<1>--disable other transfer type
	//do not need config

	//--<2>--select Ctrl type
	USBC_REG_set_bit_b(USBC_BP_POWER_D_ISO_UPDATE_EN, USBC_REG_PCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_TsType_Int(void)
{
	//--<1>--disable other transfer type
	USBC_REG_clear_bit_b(USBC_BP_POWER_D_ISO_UPDATE_EN, USBC_REG_PCTL(USBC0_BASE));

	//--<2>--select Ctrl type
	//do not need config
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_TsType_Bulk(void)
{
	//--<1>--disable other transfer type
	USBC_REG_clear_bit_b(USBC_BP_POWER_D_ISO_UPDATE_EN, USBC_REG_PCTL(USBC0_BASE));

	//--<2>--select Ctrl type
	//do not need config
}

//----------------------------------------------------------------------------------------------------------------------------------
//select the usb speed type, eg high/full/low

static void USBC_Dev_TsMode_default(void)
{
	USBC_REG_clear_bit_b(USBC_BP_POWER_D_HIGH_SPEED_EN, USBC_REG_PCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_TsMode_Hs(void)
{
	USBC_REG_set_bit_b(USBC_BP_POWER_D_HIGH_SPEED_EN, USBC_REG_PCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_TsMode_Fs(void)
{
	USBC_REG_clear_bit_b(USBC_BP_POWER_D_HIGH_SPEED_EN, USBC_REG_PCTL(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_TsMode_Ls(void)
{
	// hw not support ls, so default select fs
	USBC_Dev_TsMode_Fs();
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_ConfigEp0_Default(void)
{
	USBC_Writew(1<<USBC_BP_CSR0_D_FLUSH_FIFO, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_ConfigEp0(void)
{
	USBC_Writew(1<<USBC_BP_CSR0_D_FLUSH_FIFO, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_ep0_IsReadDataReady(void)
{
	return USBC_REG_test_bit_w(USBC_BP_CSR0_D_RX_PKT_READY, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_ep0_IsWriteDataReady(void)
{
	return USBC_REG_test_bit_w(USBC_BP_CSR0_D_TX_PKT_READY, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_ReadDataHalf(void)
{
	USBC_Writew(1<<USBC_BP_CSR0_D_SERVICED_RX_PKT_READY, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_ReadDataComplete(void)
{
	USBC_Writew((1<<USBC_BP_CSR0_D_SERVICED_RX_PKT_READY) | (1<<USBC_BP_CSR0_D_DATA_END),	USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_WriteDataHalf(void)
{
	USBC_Writew(1<<USBC_BP_CSR0_D_TX_PKT_READY, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_WriteDataComplete(void)
{
	USBC_Writew((1<<USBC_BP_CSR0_D_TX_PKT_READY) | (1<<USBC_BP_CSR0_D_DATA_END), USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_ep0_IsEpStall(void)
{
	return USBC_REG_test_bit_w(USBC_BP_CSR0_D_SENT_STALL, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_SendStall(void)
{
	USBC_REG_set_bit_w(USBC_BP_CSR0_D_SEND_STALL, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_ClearStall(void)
{
	USBC_REG_clear_bit_w(USBC_BP_CSR0_D_SEND_STALL, USBC_REG_CSR0(USBC0_BASE));
	USBC_REG_clear_bit_w(USBC_BP_CSR0_D_SENT_STALL, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_ep0_IsSetupEnd(void)
{
	return USBC_REG_test_bit_w(USBC_BP_CSR0_D_SETUP_END, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_ClearSetupEnd(void)
{
	USBC_REG_set_bit_w(USBC_BP_CSR0_D_SERVICED_SETUP_END, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_EnableIsoEp(void)
{
	USBC_REG_set_bit_w(USBC_BP_TXCSR_D_ISO, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_EnableIntEp(void)
{
	USBC_REG_clear_bit_w(USBC_BP_TXCSR_D_ISO, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_EnableBulkEp(void)
{
	USBC_REG_clear_bit_w(USBC_BP_TXCSR_D_ISO, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_ConfigEp_Default(void)
{
	//--<1>--clear tx csr
	USBC_Writew(0x00, USBC_REG_TXCSR(USBC0_BASE));

	//--<2>--clear tx ep max packet
	USBC_Writew(0x00, USBC_REG_TXMAXP(USBC0_BASE));

	//--<3>--config ep transfer type
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_ConfigEp(uint32 ts_type, uint32 is_double_fifo, uint32 ep_MaxPkt)
{
	uint16 reg_val = 0;
	uint16 temp = 0;

	//--<1>--config tx csr
	reg_val = (1 << USBC_BP_TXCSR_D_MODE);
	reg_val |= (1 << USBC_BP_TXCSR_D_CLEAR_DATA_TOGGLE);
	reg_val |= (1 << USBC_BP_TXCSR_D_FLUSH_FIFO);
	USBC_Writew(reg_val, USBC_REG_TXCSR(USBC0_BASE));

	if (is_double_fifo) {
		USBC_Writew(reg_val, USBC_REG_TXCSR(USBC0_BASE));
	}

	//--<2>--config tx ep max packet
	reg_val = USBC_Readw(USBC_REG_TXMAXP(USBC0_BASE));
	temp    = ep_MaxPkt & ((1 << USBC_BP_TXMAXP_PACKET_COUNT) - 1);
	reg_val |= temp;
	USBC_Writew(reg_val, USBC_REG_TXMAXP(USBC0_BASE));

	//--<3>--config ep transfer type
	switch(ts_type) {
	case USBC_TS_TYPE_ISO:
		USBC_Dev_Tx_EnableIsoEp();
		break;

	case USBC_TS_TYPE_INT:
		USBC_Dev_Tx_EnableIntEp();
		break;

	case USBC_TS_TYPE_BULK:
		USBC_Dev_Tx_EnableBulkEp();
		break;

	default:
		USBC_Dev_Tx_EnableBulkEp();
	}
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_ConfigEpDma(void)
{
	uint16 ep_csr = 0;

	//auto_set, tx_mode, dma_tx_en, mode1
	ep_csr = USBC_Readb(USBC_REG_TXCSR(USBC0_BASE) + 1);
	ep_csr |= (1 << USBC_BP_TXCSR_D_AUTOSET) >> 8;
	ep_csr |= (1 << USBC_BP_TXCSR_D_MODE) >> 8;
	ep_csr |= (1 << USBC_BP_TXCSR_D_DMA_REQ_EN) >> 8;
	ep_csr |= (1 << USBC_BP_TXCSR_D_DMA_REQ_MODE) >> 8;
	USBC_Writeb(ep_csr, (USBC_REG_TXCSR(USBC0_BASE) + 1));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_ClearEpDma(void)
{
	uint16 ep_csr = 0;

	//auto_set, dma_tx_en, mode1
	ep_csr = USBC_Readb(USBC_REG_TXCSR(USBC0_BASE) + 1);
	ep_csr &= ~((1 << USBC_BP_TXCSR_D_AUTOSET) >> 8);
	ep_csr &= ~((1 << USBC_BP_TXCSR_D_DMA_REQ_EN) >> 8);
	USBC_Writeb(ep_csr, (USBC_REG_TXCSR(USBC0_BASE) + 1));

	//DMA_REQ_EN and DMA_REQ_MODE cannot be cleared in the same cycle
	ep_csr = USBC_Readb(USBC_REG_TXCSR(USBC0_BASE) + 1);
	ep_csr &= ~((1 << USBC_BP_TXCSR_D_DMA_REQ_MODE) >> 8);
	USBC_Writeb(ep_csr, (USBC_REG_TXCSR(USBC0_BASE) + 1));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_Tx_IsWriteDataReady(void)
{
	uint32 temp = 0;

	temp = USBC_Readw(USBC_REG_TXCSR(USBC0_BASE));
	temp &= (1 << USBC_BP_TXCSR_D_TX_READY);

	return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_Tx_IsWriteDataReady_FifoEmpty(void)
{
	uint32 temp = 0;

	temp = USBC_Readw(USBC_REG_TXCSR(USBC0_BASE));
	temp &= (1 << USBC_BP_TXCSR_D_TX_READY) | (1 << USBC_BP_TXCSR_D_FIFO_NOT_EMPTY);

	return temp;
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_WriteDataHalf(void)
{
	uint16 ep_csr = 0;

	ep_csr = USBC_Readw(USBC_REG_TXCSR(USBC0_BASE));
	ep_csr |= 1 << USBC_BP_TXCSR_D_TX_READY;
	ep_csr &= ~(1 << USBC_BP_TXCSR_D_UNDER_RUN);
	USBC_Writew(ep_csr, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_WriteDataComplete(void)
{
	uint16 ep_csr = 0;

	ep_csr = USBC_Readw(USBC_REG_TXCSR(USBC0_BASE));
	ep_csr |= 1 << USBC_BP_TXCSR_D_TX_READY;
	ep_csr &= ~(1 << USBC_BP_TXCSR_D_UNDER_RUN);
	USBC_Writew(ep_csr, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_SendStall(void)
{
	//send stall, and fifo is flushed automaticly
	USBC_REG_set_bit_w(USBC_BP_TXCSR_D_SEND_STALL, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_Tx_IsEpStall(void)
{
	return USBC_REG_test_bit_w(USBC_BP_TXCSR_D_SENT_STALL, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_ClearStall(void)
{
	uint32 reg_val;

	reg_val = USBC_Readw(USBC_REG_TXCSR(USBC0_BASE));
	reg_val &= ~((1 << USBC_BP_TXCSR_D_SENT_STALL)|(1 << USBC_BP_TXCSR_D_SEND_STALL));
	USBC_Writew(reg_val, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 __USBC_Dev_Tx_IsEpIncomp(void)
{
	return USBC_REG_test_bit_w(USBC_BP_TXCSR_D_INCOMPLETE, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void __USBC_Dev_Tx_ClearIncomp(void)
{
	USBC_REG_clear_bit_w(USBC_BP_TXCSR_D_INCOMPLETE, USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_EnableIsoEp(void)
{
	USBC_REG_set_bit_w(USBC_BP_RXCSR_D_ISO, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_EnableIntEp(void)
{
	USBC_REG_clear_bit_w(USBC_BP_RXCSR_D_ISO, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_EnableBulkEp(void)
{
	USBC_REG_clear_bit_w(USBC_BP_RXCSR_D_ISO, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_ConfigEp_Default(void)
{
	//--<1>--clear tx csr
	USBC_Writew(0x00, USBC_REG_RXCSR(USBC0_BASE));

	//--<2>--clear tx ep max packet
	USBC_Writew(0x00, USBC_REG_RXMAXP(USBC0_BASE));

	//--<3>--config ep transfer type
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_ConfigEp(uint32 ts_type, uint32 is_double_fifo, uint32 ep_MaxPkt)
{
	uint16 reg_val = 0;
	uint16 temp = 0;

	//--<1>--config tx csr
	USBC_Writew((1 << USBC_BP_RXCSR_D_CLEAR_DATA_TOGGLE) | (1 << USBC_BP_RXCSR_D_FLUSH_FIFO),
	USBC_REG_RXCSR(USBC0_BASE));

	if (is_double_fifo)
  {
		USBC_Writew((1 << USBC_BP_RXCSR_D_CLEAR_DATA_TOGGLE) | (1 << USBC_BP_RXCSR_D_FLUSH_FIFO),
		USBC_REG_RXCSR(USBC0_BASE));
	}

	//--<2>--config tx ep max packet
	reg_val = USBC_Readw(USBC_REG_RXMAXP(USBC0_BASE));
	temp    = ep_MaxPkt & ((1 << USBC_BP_RXMAXP_PACKET_COUNT) - 1);
	reg_val |= temp;
	USBC_Writew(reg_val, USBC_REG_RXMAXP(USBC0_BASE));

	//--<3>--config ep transfer type
	switch(ts_type)
  {
    case USBC_TS_TYPE_ISO:
      USBC_Dev_Rx_EnableIsoEp();
      break;

    case USBC_TS_TYPE_INT:
      USBC_Dev_Rx_EnableIntEp();
      break;

    case USBC_TS_TYPE_BULK:
      USBC_Dev_Rx_EnableBulkEp();
      break;

    default:
      USBC_Dev_Rx_EnableBulkEp();
	}
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_ConfigEpDma(void)
{
	uint16 ep_csr = 0;

	//auto_clear, dma_rx_en, mode0
	ep_csr = USBC_Readb(USBC_REG_RXCSR(USBC0_BASE) + 1);
	ep_csr |= ((1 << USBC_BP_RXCSR_D_DMA_REQ_MODE) >> 8);
	USBC_Writeb(ep_csr, (USBC_REG_RXCSR(USBC0_BASE) + 1));

	ep_csr = USBC_Readb(USBC_REG_RXCSR(USBC0_BASE) + 1);
	ep_csr |= ((1 << USBC_BP_RXCSR_D_AUTO_CLEAR) >> 8);
	ep_csr |= ((1 << USBC_BP_RXCSR_D_DMA_REQ_EN) >> 8);
	USBC_Writeb(ep_csr, (USBC_REG_RXCSR(USBC0_BASE) + 1));

	ep_csr = USBC_Readb(USBC_REG_RXCSR(USBC0_BASE) + 1);
	ep_csr &= ~((1 << USBC_BP_RXCSR_D_DMA_REQ_MODE) >> 8);
	USBC_Writeb(ep_csr, (USBC_REG_RXCSR(USBC0_BASE) + 1));

	ep_csr = USBC_Readb(USBC_REG_RXCSR(USBC0_BASE) + 1);
	ep_csr |= ((1 << USBC_BP_RXCSR_D_DMA_REQ_MODE) >> 8);
	USBC_Writeb(ep_csr, (USBC_REG_RXCSR(USBC0_BASE) + 1));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_ClearEpDma(void)
{
	uint16 ep_csr = 0;

	//auto_clear, dma_rx_en, mode0
	ep_csr = USBC_Readb(USBC_REG_RXCSR(USBC0_BASE) + 1);

	ep_csr &= ~((1 << USBC_BP_RXCSR_D_AUTO_CLEAR) >> 8);
	ep_csr &= ~((1 << USBC_BP_RXCSR_D_DMA_REQ_MODE) >> 8);
	ep_csr &= ~((1 << USBC_BP_RXCSR_D_DMA_REQ_EN) >> 8);
	USBC_Writeb(ep_csr, (USBC_REG_RXCSR(USBC0_BASE) + 1));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_Rx_IsReadDataReady(void)
{
	return USBC_REG_test_bit_w(USBC_BP_RXCSR_D_RX_PKT_READY, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_ReadDataHalf(void)
{
	uint32 reg_val = 0;

	//overrun, dataerr is used in iso transfer
	reg_val = USBC_Readw(USBC_REG_RXCSR(USBC0_BASE));
	reg_val &= ~(1 << USBC_BP_RXCSR_D_RX_PKT_READY);
	reg_val &= ~(1 << USBC_BP_RXCSR_D_OVERRUN);
	reg_val &= ~(1 << USBC_BP_RXCSR_D_DATA_ERROR);
	USBC_Writew(reg_val, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_ReadDataComplete(void)
{
	uint32 reg_val = 0;

	//overrun, data error is used in iso transfer
	reg_val = USBC_Readw(USBC_REG_RXCSR(USBC0_BASE));
	reg_val &= ~(1 << USBC_BP_RXCSR_D_RX_PKT_READY);
	reg_val &= ~(1 << USBC_BP_RXCSR_D_OVERRUN);
	reg_val &= ~(1 << USBC_BP_RXCSR_D_DATA_ERROR);
	USBC_Writew(reg_val, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_SendStall(void)
{
	USBC_REG_set_bit_w(USBC_BP_RXCSR_D_SEND_STALL, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static uint32 USBC_Dev_Rx_IsEpStall(void)
{
	return USBC_REG_test_bit_w(USBC_BP_RXCSR_D_SENT_STALL, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_ClearStall(void)
{
	USBC_REG_clear_bit_w(USBC_BP_RXCSR_D_SEND_STALL, USBC_REG_RXCSR(USBC0_BASE));
	USBC_REG_clear_bit_w(USBC_BP_RXCSR_D_SENT_STALL, USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ClearDma_Trans(void)
{
	//in 1667 1673 and later ic, this bit is fix to 1, set when drv initialize;
	//in 1667 1673 former ic, we do not use inner dma, so this bit should be 0

#if 1
	uint32 reg_val;

	reg_val  = USBC_Readl(USBC0_BASE + USBC_REG_o_PCTL);
	reg_val &= ~(1 << 24);
	USBC_Writel(reg_val, USBC0_BASE + USBC_REG_o_PCTL);
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ConfigDma_Trans(void)
{
	//in 1667 and later ic, this bit is fix to 1, set when drv initialize, so do not set here;
	//in 1667 former ic(eg A23), we do not use inner dma(use cpu or outer dma),
	//this bit should be 0, so cannot set here
  
#if 1
	uint32 reg_val;

	reg_val  = USBC_Readl(USBC0_BASE + USBC_REG_o_PCTL);
	reg_val |= (1 << 24);
	USBC_Writeb(reg_val, USBC0_BASE + USBC_REG_o_PCTL);
#endif
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear the address allocated by host for device
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_Dev_SetAddress_default(void)
{
	USBC_Writeb(0x00, USBC_REG_FADDR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------
//set the address
//@hUSB: handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_Dev_SetAddress(uint8 address)
{
	USBC_Writeb(address, USBC_REG_FADDR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_Dev_QueryTransferMode(void)
{

	if (USBC_REG_test_bit_b(USBC_BP_POWER_D_HIGH_SPEED_FLAG, USBC_REG_PCTL(USBC0_BASE))) {
		return USBC_TS_MODE_HS;
	} else {
		return USBC_TS_MODE_FS;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------
//config the device's transfer type and speed mode
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ts_type:    transfer type
//@speed_mode: speed mode
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_Dev_ConfigTransferMode(uint8 ts_type, uint8 speed_mode)
{
	//--<1>--select the transfer type
	//default bulk transfer
	switch(ts_type)
  {
    case USBC_TS_TYPE_CTRL:
      USBC_Dev_TsType_Ctrl();
      break;

    case USBC_TS_TYPE_ISO:
      USBC_Dev_TsType_Iso();
      break;

    case USBC_TS_TYPE_INT:
      USBC_Dev_TsType_Int();
      break;

    case USBC_TS_TYPE_BULK:
      USBC_Dev_TsType_Bulk();
      break;

    default:
      USBC_Dev_TsType_default();
	}

	//--<2>--select the transfer speed
	switch(speed_mode)
  {
    case USBC_TS_MODE_HS:
      USBC_Dev_TsMode_Hs();
      break;

    case USBC_TS_MODE_FS:
      USBC_Dev_TsMode_Fs();
      break;

    case USBC_TS_MODE_LS:
      USBC_Dev_TsMode_Ls();
      break;

    default:
      USBC_Dev_TsMode_default();
	}
}

//----------------------------------------------------------------------------------------------------------------------------------
//the switch to communicate with PC
//@hUSB:     handle return by USBC_open_otg, include the key data which USBC need
//@is_on:    1 - open the switch, 0 - close the switch
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_Dev_ConectSwitch(uint32 is_on)
{
	if (is_on == USBC_DEVICE_SWITCH_ON)
  {
		USBC_REG_set_bit_b(USBC_BP_POWER_D_SOFT_CONNECT, USBC_REG_PCTL(USBC0_BASE));
	} else
  {
		USBC_REG_clear_bit_b(USBC_BP_POWER_D_SOFT_CONNECT, USBC_REG_PCTL(USBC0_BASE));
	}
}

//----------------------------------------------------------------------------------------------------------------------------------
//query current device's status, eg reset, resume, suspend, etc.
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_Dev_QueryPowerStatus(void)
{
	return (USBC_Readb(USBC_REG_PCTL(USBC0_BASE)) & 0x0f);
}

//----------------------------------------------------------------------------------------------------------------------------------
//config EP, include double fifo, max packet size, etc.
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    transfer type
//@is_double_fifo: speed mode
//@ep_MaxPkt:  max packet size
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_ConfigEp(uint32 ts_type, uint32 ep_type, uint32 is_double_fifo, uint32 ep_MaxPkt)
{
	switch(ep_type)
  {
    case USBC_EP_TYPE_EP0:
      USBC_Dev_ep0_ConfigEp0();
      break;

    case USBC_EP_TYPE_TX:
      USBC_Dev_Tx_ConfigEp(ts_type, is_double_fifo,  ep_MaxPkt);
      break;

    case USBC_EP_TYPE_RX:
      USBC_Dev_Rx_ConfigEp(ts_type, is_double_fifo, ep_MaxPkt);
      break;

    default:
      return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//release all Ep resources, excpet irq
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_ConfigEp_Default(uint32 ep_type)
{
	switch(ep_type)
  {
    case USBC_EP_TYPE_EP0:
      USBC_Dev_ep0_ConfigEp0_Default();
      break;

    case USBC_EP_TYPE_TX:
      USBC_Dev_Tx_ConfigEp_Default();
      break;

    case USBC_EP_TYPE_RX:
      USBC_Dev_Rx_ConfigEp_Default();
      break;

    default:
      return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//config  Ep's dma
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_ConfigEpDma(uint32 ep_type)
{
	switch(ep_type)
  {
    case USBC_EP_TYPE_EP0:
      //not support
      return -1;
      //break;

    case USBC_EP_TYPE_TX:
      USBC_Dev_Tx_ConfigEpDma();
      USBC_Dev_ConfigDma_Trans();
    break;

    case USBC_EP_TYPE_RX:
      USBC_Dev_Rx_ConfigEpDma();
      USBC_Dev_ConfigDma_Trans();
    break;

    default:
      return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear  Ep's dma configuration
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_ClearEpDma(uint32 ep_type)
{
	switch(ep_type)
  {
    case USBC_EP_TYPE_EP0:
      //not support
      return -1;
      //break;

    case USBC_EP_TYPE_TX:
      USBC_Dev_Tx_ClearEpDma();
      USBC_Dev_ClearDma_Trans();
      break;

    case USBC_EP_TYPE_RX:
      USBC_Dev_Rx_ClearEpDma();
      USBC_Dev_ClearDma_Trans();
      break;

    default:
      return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//check if ep is stalled
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_IsEpStall(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		USBC_Dev_ep0_IsEpStall();
		break;

	case USBC_EP_TYPE_TX:
		USBC_Dev_Tx_IsEpStall();
		break;

	case USBC_EP_TYPE_RX:
		USBC_Dev_Rx_IsEpStall();
		break;

	default:
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//let ep enter stall status
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_EpSendStall(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		USBC_Dev_ep0_SendStall();
		break;

	case USBC_EP_TYPE_TX:
		USBC_Dev_Tx_SendStall();
		break;

	case USBC_EP_TYPE_RX:
		USBC_Dev_Rx_SendStall();
		break;

	default:
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear the ep's stall status
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_EpClearStall(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		USBC_Dev_ep0_ClearStall();
		break;

	case USBC_EP_TYPE_TX:
		USBC_Dev_Tx_ClearStall();
		break;

	case USBC_EP_TYPE_RX:
		USBC_Dev_Rx_ClearStall();
		break;

	default:
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//check if ep0 is SetupEnd
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_Dev_Ctrl_IsSetupEnd(void)
{
	return USBC_Dev_ep0_IsSetupEnd();
}

//----------------------------------------------------------------------------------------------------------------------------------
//clear the ep0's SetupEnd status
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//
//----------------------------------------------------------------------------------------------------------------------------------

void USBC_Dev_Ctrl_ClearSetupEnd(void)
{
	USBC_Dev_ep0_ClearSetupEnd();
}

//----------------------------------------------------------------------------------------------------------------------------------

static int32 USBC_Dev_WriteDataHalf(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		USBC_Dev_ep0_WriteDataHalf();
		break;

	case USBC_EP_TYPE_TX:
		USBC_Dev_Tx_WriteDataHalf();
		break;

	case USBC_EP_TYPE_RX:
		//not support
		return -1;
		//break;

	default:
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

static int32 USBC_Dev_WriteDataComplete(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		USBC_Dev_ep0_WriteDataComplete();
		break;

	case USBC_EP_TYPE_TX:
		USBC_Dev_Tx_WriteDataComplete();
		break;

	case USBC_EP_TYPE_RX:
		//not support
		return -1;
		//break;

	default:
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

static int32 USBC_Dev_ReadDataHalf(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		USBC_Dev_ep0_ReadDataHalf();
		break;

	case USBC_EP_TYPE_TX:
		//not support
		return -1;
		//break;

	case USBC_EP_TYPE_RX:
		USBC_Dev_Rx_ReadDataHalf();
		break;

	default:
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

static int32 USBC_Dev_ReadDataComplete(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		USBC_Dev_ep0_ReadDataComplete();
		break;

	case USBC_EP_TYPE_TX:
		//not support
		return -1;
		//break;

	case USBC_EP_TYPE_RX:
		USBC_Dev_Rx_ReadDataComplete();
		break;

	default:
		return -1;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//get the write status, eg write over or not
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//@complete:   if all data has been written over.
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_WriteDataStatus(uint32 ep_type, uint32 complete)
{
	if (complete) {
		return USBC_Dev_WriteDataComplete( ep_type);
	} else {
		return USBC_Dev_WriteDataHalf( ep_type);
	}
}

//----------------------------------------------------------------------------------------------------------------------------------
//get the read status, eg write over or not
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//@complete:   if all data has been read over.
//
//return: 0 - success, !0 - failed
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_ReadDataStatus(uint32 ep_type, uint32 complete)
{
	if (complete) {
		return USBC_Dev_ReadDataComplete(ep_type);
	} else {
		return USBC_Dev_ReadDataHalf(ep_type);
	}
}

//----------------------------------------------------------------------------------------------------------------------------------
//check if the data ready for reading
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_Dev_IsReadDataReady(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		return USBC_Dev_ep0_IsReadDataReady();

	case USBC_EP_TYPE_TX:
		//not support
		break;

	case USBC_EP_TYPE_RX:
		return USBC_Dev_Rx_IsReadDataReady();

	default:
		break;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//check if the data ready for writting
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//@ep_type:    ep type
//
//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_Dev_IsWriteDataReady(uint32 ep_type)
{
	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		return USBC_Dev_ep0_IsWriteDataReady();

	case USBC_EP_TYPE_TX:
		return USBC_Dev_Tx_IsWriteDataReady();

	case USBC_EP_TYPE_RX:
		//not support
		break;

	default:
		break;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

uint32 USBC_Dev_IsWriteDataReady_FifoEmpty(uint32 ep_type)
{

	switch(ep_type) {
	case USBC_EP_TYPE_EP0:
		return USBC_Dev_ep0_IsWriteDataReady();

	case USBC_EP_TYPE_TX:
		return USBC_Dev_Tx_IsWriteDataReady_FifoEmpty();

	case USBC_EP_TYPE_RX:
		//not support
		break;

	default:
		break;
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//configure the device's transfer type and speed mode.
//@hUSB:       handle return by USBC_open_otg, include the key data which USBC need
//----------------------------------------------------------------------------------------------------------------------------------

int32 USBC_Dev_IsoUpdateEnable(void)
{
	USBC_Dev_TsType_Iso();
	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_ep0_FlushFifo(void)
{
	USBC_Writew(1 << USBC_BP_CSR0_D_FLUSH_FIFO, USBC_REG_CSR0(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Tx_FlushFifo(void)
{
	USBC_Writew((1 << USBC_BP_TXCSR_D_CLEAR_DATA_TOGGLE) | (1 << USBC_BP_TXCSR_D_FLUSH_FIFO),
	USBC_REG_TXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

static void USBC_Dev_Rx_FlushFifo(void)
{
	USBC_Writew((1 << USBC_BP_RXCSR_D_CLEAR_DATA_TOGGLE) | (1 << USBC_BP_RXCSR_D_FLUSH_FIFO),
	USBC_REG_RXCSR(USBC0_BASE));
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_Dev_FlushFifo(uint32 ep_type)
{
	switch(ep_type){
		case USBC_EP_TYPE_EP0:
			USBC_Dev_ep0_FlushFifo();
		break;

		case USBC_EP_TYPE_TX:
			USBC_Dev_Tx_FlushFifo();
		break;

		case USBC_EP_TYPE_RX:
			USBC_Dev_Rx_FlushFifo();
		break;

		default:
		break;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------

void USBC_Clear_Feature_HALT(uint32 ep_type)
{
	int reg_val;
	switch(ep_type)
	{
		case USBC_EP_TYPE_EP0:
			//
			break;
		case USBC_EP_TYPE_TX:
			reg_val = (1 << USBC_BP_TXCSR_D_MODE);
			reg_val |= (1 << USBC_BP_TXCSR_D_CLEAR_DATA_TOGGLE);
			reg_val |= (1 << USBC_BP_TXCSR_D_FLUSH_FIFO);
			USBC_Writew(reg_val, USBC_REG_TXCSR(USBC0_BASE));
			break;

		case USBC_EP_TYPE_RX:
			USBC_Writew((1 << USBC_BP_RXCSR_D_CLEAR_DATA_TOGGLE) | (1 << USBC_BP_RXCSR_D_FLUSH_FIFO),
			USBC_REG_RXCSR(USBC0_BASE));
			break;

		default:
			break;
	}
}

//----------------------------------------------------------------------------------------------------------------------------------
