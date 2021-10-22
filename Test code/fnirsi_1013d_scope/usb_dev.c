//----------------------------------------------------------------------------------------------------------------------------------

#include "usb.h"
#include "usb_dev.h"
#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

//Add the fnirsi interrupt setup to usb_device_init
//modify this function to separate the usb initialization from the connection initialization (See Ghidra source)

//Change the interrupt handler to just handle endpoint one in and out

//Setup descriptors

//----------------------------------------------------------------------------------------------------------------------------------

static uint8 current_usb_type = USB_TYPE_DISCONNECT;
uint8 current_speed = USB_SPEED_UNKNOWN;
uint32 usb_connect = 0;
int32 usb_ep0_state = EP0_IDLE;
uint8 usb_addr = 0;
uint8 usb_xfer_type = NONE_REQ;

//static uint32  is_controller_alive = 0;

enum sunxi_udc_cmd_e
{
  SW_UDC_P_ENABLE = 1, //Pull-up enable       
  SW_UDC_P_DISABLE = 2, //Pull-up disable      
  SW_UDC_P_RESET = 3, //UDC reset, in case of
};

static int32 ep_max_len[3] = {64, 512, 512};
uint8 usb_tx_buf[512];
int32 usb_tx_buf_len = 0;
int32 usb_tx_pos = 0;
uint8 usb_rx_buf[512];
int32 usb_rx_buf_len = 0;
int32 usb_rx_pos = 0;

static uint32 fifo_offset = 0; // global

//----------------------------------------------------------------------------------------------------------------------------------

int32 usb_device_write_data_ep_pack(int32 ep, uint8 * databuf, int32 len)
{
  memcpy(usb_tx_buf, databuf, len);

  usb_tx_buf_len = len;

  if(len > ep_max_len[ep])
  {
    USBC_WritePacket(USBC_SelectFIFO(ep), ep_max_len[ep], databuf);
    USBC_Dev_WriteDataStatus(ep == 0 ? USBC_EP_TYPE_EP0 : USBC_EP_TYPE_TX, 0);
    usb_tx_pos = 64;
  }
  else
  {
    USBC_WritePacket(USBC_SelectFIFO(ep), len, databuf);
    USBC_Dev_WriteDataStatus(ep == 0 ? USBC_EP_TYPE_EP0 : USBC_EP_TYPE_TX, 1);
    usb_tx_pos = 0;
  }
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 usb_device_read_data_ep_pack(int32 ep, uint8 * databuf, int32 len)
{
  USBC_ReadPacket(USBC_SelectFIFO(ep), len, databuf);
  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_send_nullpack_ep0(void)
{
  USBC_Dev_WriteDataStatus(USBC_EP_TYPE_EP0, 1);
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_read_data_status_ep0(uint8 is_complete)
{
  USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, is_complete);
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 usb_device_write_data(int32 ep, uint8 * databuf, int32 len)
{
  int32 length = len;
  volatile int32 Timeout = 10000000;
  int32 pack_len = ep_max_len[ep];
  int32 data_pos = 0;
  if(usb_connect)
  {
    void * fifo = USBC_SelectFIFO(ep);
    USBC_SelectActiveEp(ep);
    while(length > pack_len)
    {
      while((USBC_Dev_IsWriteDataReady(USBC_EP_TYPE_TX))&&(--Timeout)); //�ȴ����д��־
      USBC_WritePacket(fifo, pack_len, databuf + data_pos);
      USBC_Dev_WriteDataStatus(USBC_EP_TYPE_TX, 1);
      data_pos += pack_len;
      length -= pack_len;

      if(Timeout == 0)
      {
        return -1;
      }
      Timeout = 10000000;
    }
    while((USBC_Dev_IsWriteDataReady(USBC_EP_TYPE_TX))&&(Timeout--)); //�ȴ����д��־
    USBC_WritePacket(fifo, length, databuf + data_pos);
    USBC_Dev_WriteDataStatus(USBC_EP_TYPE_TX, 1);
    return 0;
  }
  else
  {
    return -1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 usb_device_read_data(int32 ep, uint8 * databuf, int32 len)
{
  return -1;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_clear_setup_end(void)
{
  USBC_Dev_Ctrl_ClearSetupEnd();
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_set_address(uint8 addr)
{
  USBC_Dev_SetAddress(addr);
  usb_addr = addr;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_set_ep0_state(enum ep0_state state)
{
  usb_ep0_state = state;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_set_xfer_type(enum usb_xfer_type_req type)
{
  usb_xfer_type = type;
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 usb_dev_bsp_init(void)
{
  //spinlock_t lock;

  //open usb lock
  usb_phy_open_clock(); //need to open otg and phy clk

  //USBC_EnhanceSignal(sunxi_udc_io->usb_bsp_hdle); //no use
  USBC_PhyConfig();
  USBC_ConfigFIFO_Base();
  USBC_EnableDpDmPullUp();
  USBC_EnableIdPullUp();
  //USBC_DisableDpDmPullUp();

  USBC_ForceId(USBC_ID_TYPE_DEVICE);
  USBC_ForceVbusValid(USBC_VBUS_TYPE_HIGH);

  USBC_SelectBus(USBC_IO_TYPE_PIO, 0, 0);

  return 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

static void clear_all_irq(void)
{
  USBC_INT_ClearEpPendingAll(USBC_EP_TYPE_TX);
  USBC_INT_ClearEpPendingAll(USBC_EP_TYPE_RX);
  USBC_INT_ClearMiscPendingAll();
}

//----------------------------------------------------------------------------------------------------------------------------------
//mask the useless irq, save disconect, reset, resume, suspend

static uint32 filtrate_irq_misc(uint32 irq_misc)
{
  uint32 irq = irq_misc;

  irq &= ~(USBC_INTUSB_VBUS_ERROR | USBC_INTUSB_SESSION_REQ | USBC_INTUSB_CONNECT | USBC_INTUSB_SOF);
  USBC_INT_ClearMiscPending(USBC_INTUSB_VBUS_ERROR);
  USBC_INT_ClearMiscPending(USBC_INTUSB_SESSION_REQ);
  USBC_INT_ClearMiscPending(USBC_INTUSB_CONNECT);
  USBC_INT_ClearMiscPending(USBC_INTUSB_SOF);

  return irq;
}

//----------------------------------------------------------------------------------------------------------------------------------

static void usbd_start_work(void)
{
  //enable_irq_udc(); //no use
  USBC_Dev_ConectSwitch(USBC_DEVICE_SWITCH_ON);
  //GH_USB_set_DevCtl_W(0x01);
}

//----------------------------------------------------------------------------------------------------------------------------------

static void usbd_stop_work(void)
{
  //disable_irq_udc();//no use
  USBC_Dev_ConectSwitch(USBC_DEVICE_SWITCH_OFF); // default is pulldown
}

//----------------------------------------------------------------------------------------------------------------------------------

static void cfg_udc_command(enum sunxi_udc_cmd_e cmd)
{
  switch(cmd)
  {
  case SW_UDC_P_ENABLE:
    usbd_start_work();
    break;

  case SW_UDC_P_DISABLE:
    usbd_stop_work();
    break;

  case SW_UDC_P_RESET:
    break;

  default:
    break;
  }

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

void sunxi_udc_disable(void)
{
  //Disable all interrupts
  USBC_INT_DisableUsbMiscAll();
  USBC_INT_DisableEpAll(USBC_EP_TYPE_RX);
  USBC_INT_DisableEpAll(USBC_EP_TYPE_TX);

  //Clear the interrupt registers
  clear_all_irq();
  cfg_udc_command(SW_UDC_P_DISABLE);

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_handle_ep0(void)
{
  int32 len;
  uint8 databuf[8];
  USBC_SelectActiveEp(0);

  //clear stall status
  if(USBC_Dev_IsEpStall(USBC_EP_TYPE_EP0))
  {
    USBC_Dev_EpClearStall(USBC_EP_TYPE_EP0);
    usb_ep0_state = EP0_IDLE;
    return;
  }
  //clear setup end
  if(USBC_Dev_Ctrl_IsSetupEnd())
  {
    USBC_Dev_Ctrl_ClearSetupEnd();
    usb_ep0_state = EP0_IDLE;
  }

  if(USBC_Dev_IsReadDataReady(USBC_EP_TYPE_EP0)) //if that is setup data ,turn to idle state
  {
    usb_ep0_state = EP0_IDLE;
  }

  switch(usb_ep0_state)
  {
  case EP0_IDLE:
  {
    if(!USBC_Dev_IsReadDataReady(USBC_EP_TYPE_EP0))
    {
      return;
    }

    len = USBC_ReadLenFromFifo(USBC_EP_TYPE_EP0);

    if(len != 8)
    {
      int32 timeout = 16;
      while((timeout--)&&(len != 8))
      {
        len = USBC_ReadLenFromFifo(USBC_EP_TYPE_EP0);
      }
    }

    if(len == 8)
    {
      usb_device_read_data_ep_pack(0, databuf, len);
      usb_device_read_data_status_ep0(0);
      //GD_USB_Set_CSR0L(0x40);
      if(databuf[0]&0x80)
      {
        usb_ep0_state = EP0_IN_DATA_PHASE;
      }
      else
      {
        usb_ep0_state = EP0_OUT_DATA_PHASE;
      }


      //Modify here for msc class


      if(current_usb_type == USB_TYPE_USB_HID)
      {
        //						usb_hid_setup_handle(databuf,len);
      }
      else if(current_usb_type == USB_TYPE_USB_COM)
      {
        //						usb_cdc_setup_handle(databuf,len);
      }





    }
    else
    {
      USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 0);
      USBC_Dev_EpSendStall(USBC_EP_TYPE_EP0);
      return;
    }
  }
    break;

  case EP0_IN_DATA_PHASE:
    if(!usb_tx_pos)
    {
      //sunxi_udc_write_fifo(ep, req);
      usb_ep0_state = EP0_IDLE;
    }
    else
    {
      if(usb_tx_buf_len - usb_tx_pos > 64)
      {
        USBC_WritePacket(USBC_SelectFIFO(0), ep_max_len[0], usb_tx_buf + usb_tx_pos);
        USBC_Dev_WriteDataStatus(USBC_EP_TYPE_EP0, 0);
      }
      else
      {
        USBC_WritePacket(USBC_SelectFIFO(0), usb_tx_buf_len - usb_tx_pos, usb_tx_buf + usb_tx_pos);
        USBC_Dev_WriteDataStatus(USBC_EP_TYPE_EP0, 1);
        usb_tx_pos = 0;
        usb_ep0_state = EP0_IDLE;
      }
    }
    break;

  case EP0_OUT_DATA_PHASE:
    if(!USBC_Dev_IsReadDataReady(USBC_EP_TYPE_EP0))
    {
      return;
    }

    len = USBC_ReadLenFromFifo(USBC_EP_TYPE_EP0);
    usb_device_read_data_ep_pack(0, databuf, len);
    usb_device_read_data_status_ep0(0);
    usb_ep0_state = EP0_IDLE;
    break;

  case EP0_END_XFER:
    if(usb_xfer_type == SET_ADDR)//no use
    {
      //USBC_SelectActiveEp(0);
      //USB_DEV_PRINTF("usb_xfer_type:SET_ADDR0x%02x\n",usb_addr);

      //USBC_Dev_Ctrl_ClearSetupEnd();
      //USBC_Dev_SetAddress(usb_addr);
      //				usb_device_send_nullpack_ep0();

    }
    else if(usb_xfer_type == SET_CONFIG)
    {

    }

    usb_xfer_type = NONE_REQ;
    usb_ep0_state = EP0_IDLE;
    break;

  default:
    usb_ep0_state = EP0_IDLE;
    break;
  }

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_handle_epn_in(int32 ep)
{
  uint32 old_ep_idx;
  uint32 idx = ep;

  old_ep_idx = USBC_GetActiveEp();
  USBC_SelectActiveEp(idx);

  if(USBC_Dev_IsEpStall(USBC_EP_TYPE_TX))
  {
    USBC_Dev_EpClearStall(USBC_EP_TYPE_TX);
  }
  if(!USBC_Dev_IsWriteDataReady(USBC_EP_TYPE_TX))
  {


    //Modify for msc here


    if(current_usb_type == USB_TYPE_USB_HID)
    {
      //			usb_hid_in_ep_callback();
      //USBC_Dev_WriteDataStatus(USBC_EP_TYPE_TX,1);
      //sunxi_udc_write_fifo(ep, req);
    }
  }
  USBC_SelectActiveEp(old_ep_idx);
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_handle_epn_out(int32 ep)
{
  uint32 old_ep_idx;
  uint32 idx = ep;
  uint32 len;

  old_ep_idx = USBC_GetActiveEp();
  USBC_SelectActiveEp(idx);

  if(USBC_Dev_IsEpStall(USBC_EP_TYPE_RX))
  {
    USBC_Dev_EpClearStall(USBC_EP_TYPE_RX);
  }
  if(USBC_Dev_IsReadDataReady(USBC_EP_TYPE_RX))
  {
    len = USBC_ReadLenFromFifo(USBC_EP_TYPE_RX);

    usb_device_read_data_ep_pack(idx, usb_rx_buf, len);

    usb_rx_buf_len = len;

    //Modify for msc handling

    if(current_usb_type == USB_TYPE_USB_HID)
    {
      //			usb_hid_out_ep_callback(usb_rx_buf,usb_rx_buf_len);
    }
    else if(current_usb_type == USB_TYPE_USB_COM)
    {
      //			usb_cdc_out_ep_callback(usb_rx_buf,usb_rx_buf_len);
    }



    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_RX, 1);
    //		USB_DEV_PRINTF("rx ep(%d) data ready data[0]:%d!\n", idx,usb_rx_buf[0]);
    //		usb_device_write_data_ep_pack(idx,usb_rx_buf,usb_rx_buf_len);

  }

  USBC_SelectActiveEp(old_ep_idx);
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_irq_handle(int32 arg)
{
  int32 usb_irq = 0;
  int32 tx_irq = 0;
  int32 rx_irq = 0;
  int32 i = 0;
  uint32 old_ep_idx = 0;

  //Save index
  old_ep_idx = USBC_GetActiveEp();

  //Read status registers
  usb_irq = USBC_INT_MiscPending();
  tx_irq = USBC_INT_EpPending(USBC_EP_TYPE_TX);
  rx_irq = USBC_INT_EpPending(USBC_EP_TYPE_RX);

  usb_irq = filtrate_irq_misc(usb_irq);

  //Now, handle interrupts. There's two types :
  // - Reset, Resume, Suspend coming -> usb_int_reg
  // - EP -> ep_int_reg

  //RESET
  if(usb_irq & USBC_INTUSB_RESET)
  {
    USBC_INT_ClearMiscPending(USBC_INTUSB_RESET);
    clear_all_irq();
    usb_connect = 1;
    usb_ep0_state = EP0_IDLE;
    USBC_SelectActiveEp(0);
    USBC_Dev_SetAddress_default();
    return;
  }

  //RESUME
  if(usb_irq & USBC_INTUSB_RESUME)
  {
    //clear interrupt
    USBC_INT_ClearMiscPending(USBC_INTUSB_RESUME);
  }

  //SUSPEND
  if(usb_irq & USBC_INTUSB_SUSPEND)
  {
    //clear interrupt
    USBC_INT_ClearMiscPending(USBC_INTUSB_SUSPEND);
    usb_connect = 0;
    usb_ep0_state = EP0_IDLE;
  }

  //DISCONNECT
  if(usb_irq & USBC_INTUSB_DISCONNECT)
  {
    USBC_INT_ClearMiscPending(USBC_INTUSB_DISCONNECT);
    usb_ep0_state = EP0_IDLE;
    usb_connect = 0;
  }

  //		//SOF
  //		if (usb_irq & USBC_INTUSB_SOF)
  //		{
  //			USB_DEV_PRINTF("IRQ: start of frame intr\n");
  //			USBC_INT_ClearMiscPending( USBC_INTUSB_SOF);
  //		}

  //EP
  //control traffic
  //check on ep0csr != 0 is not a good idea as clearing in_pkt_ready  generate an interrupt

  if(tx_irq & USBC_INTTx_FLAG_EP0)
  {
    //Clear the interrupt bit by setting it to 1
    USBC_INT_ClearEpPending(USBC_EP_TYPE_TX, 0);
    if(current_speed == USB_SPEED_UNKNOWN)
    {
      if(USBC_Dev_QueryTransferMode() == USBC_TS_MODE_HS)
      {
        current_speed = USB_SPEED_HIGH;
        ep_max_len[1] = 512;
        ep_max_len[2] = 512;
      }
      else
      {
        current_speed = USB_SPEED_FULL;
        ep_max_len[1] = 64;
        ep_max_len[2] = 64;
      }
    }

    usb_handle_ep0();
    //USB_OUT_Intr_handle_Ep0();
  }

  //firstly to get data

  //rx endpoint data transfers
  for(i = 1; i <= SW_UDC_EPNUMS; i++)
  {
    uint32 tmp = 1 << i;
    if(rx_irq & tmp)
    {

      //USB_DEV_PRINTF("USB rx ep%d irq\n", i);
      //Clear the interrupt bit by setting it to 1
      USBC_INT_ClearEpPending(USBC_EP_TYPE_RX, i);
      //sunxi_udc_handle_ep(&dev->ep[ep_fifo_out[i]]);
      usb_handle_epn_out(i);

    }
  }

  //tx endpoint data transfers
  for(i = 1; i <= SW_UDC_EPNUMS; i++)
  {
    uint32 tmp = 1 << i;
    if(tx_irq & tmp)
    {

      //USB_DEV_PRINTF("USB tx ep%d irq\n", i);
      //Clear the interrupt bit by setting it to 1
      USBC_INT_ClearEpPending(USBC_EP_TYPE_TX, i);
      //sunxi_udc_handle_ep(&dev->ep[ep_fifo_in[i]]);
      usb_handle_epn_in(i);
    }
  }

  //Restore old index
  USBC_SelectActiveEp(old_ep_idx);
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_config_ep_in(int32 epidx, int32 maxpack, int32 type)
{
  uint32 old_ep_idx = 0;
  if(epidx)
  {
    //Save index
    old_ep_idx = USBC_GetActiveEp();
    USBC_SelectActiveEp(epidx);
    uint32 fifo_size = maxpack * 2; // double buffer
    USBC_Dev_ConfigEp(type, USBC_EP_TYPE_TX, 1, maxpack);
    USBC_ConfigFifo(USBC_EP_TYPE_TX, 1, fifo_size, fifo_offset);
    fifo_offset += fifo_size;
    USBC_INT_EnableEp(USBC_EP_TYPE_TX, epidx);
    USBC_SelectActiveEp(old_ep_idx);
    ep_max_len[epidx] = maxpack;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_config_ep_out(int32 epidx, int32 maxpack, int32 type)
{
  uint32 old_ep_idx = 0;
  if(epidx)
  {
    //Save index
    old_ep_idx = USBC_GetActiveEp();
    USBC_SelectActiveEp(epidx);
    uint32 fifo_size = maxpack * 2; // double buffer
    USBC_Dev_ConfigEp(type, USBC_EP_TYPE_RX, 1, maxpack);
    USBC_ConfigFifo(USBC_EP_TYPE_RX, 1, fifo_size, fifo_offset);
    fifo_offset += fifo_size;
    USBC_INT_EnableEp(USBC_EP_TYPE_RX, epidx);
    USBC_SelectActiveEp(old_ep_idx);
    ep_max_len[epidx] = maxpack;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_clear_ep_halt(int32 epaddr)
{
  int32 old_ep_idx;
  int32 ep = epaddr & 0x7f;

  //Save index
  old_ep_idx = USBC_GetActiveEp();
  USBC_SelectActiveEp(ep);
  if(epaddr & 0x80)
  {
    USBC_Clear_Feature_HALT(USBC_EP_TYPE_TX);
  }
  else
  {
    USBC_Clear_Feature_HALT(USBC_EP_TYPE_RX);
  }
  USBC_SelectActiveEp(old_ep_idx);
}

//----------------------------------------------------------------------------------------------------------------------------------

void sunxi_udc_enable(void)
{
  current_speed = USB_SPEED_UNKNOWN;

  USBC_Dev_ConfigTransferMode(USBC_TS_TYPE_BULK, USBC_TS_MODE_HS);

  //Enable reset and suspend interrupt interrupts
  USBC_INT_EnableUsbMiscUint(USBC_BP_INTUSB_SUSPEND);
  USBC_INT_EnableUsbMiscUint(USBC_BP_INTUSB_RESUME);
  USBC_INT_EnableUsbMiscUint(USBC_BP_INTUSB_RESET);
  USBC_INT_EnableUsbMiscUint(USBC_BP_INTUSB_DISCONNECT);
  //USBC_INT_EnableUsbMiscUint( USBC_INTUSB_SOF);
  
  //Enable ep0 interrupt
  USBC_INT_EnableEp(USBC_EP_TYPE_TX, 0);

  cfg_udc_command(SW_UDC_P_ENABLE);

  return;
}

//----------------------------------------------------------------------------------------------------------------------------------

int32 usb_device_init(uint8 type)
{
  int32 retval = 0;
  if(current_usb_type != type)
  {
    current_usb_type = type;
    retval = usb_dev_bsp_init();
    if(retval != 0)
    {
      return -1;
    }

    sunxi_udc_disable();

//Need to use the fnirsi interrupt setup here    
//    retval = request_irq(IRQ_USBOTG, usb_irq_handle, 0);
    
    if(retval != 0)
    {
      retval = -1;
      //goto err;
    }
    
    sunxi_udc_enable();

    return retval;
  }
  return retval;
}

//----------------------------------------------------------------------------------------------------------------------------------
