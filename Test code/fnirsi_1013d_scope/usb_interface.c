//----------------------------------------------------------------------------------------------------------------------------------

#include "ccu_control.h"
#include "usb_interface.h"
#include "interrupt.h"

#include <string.h>

//----------------------------------------------------------------------------------------------------------------------------------

//Rename the defines to be better readable!!!

//----------------------------------------------------------------------------------------------------------------------------------

void usb_irq_handle(void);

void usb_device_irq_handler(void);

void usb_mass_storage_standard_request(void *dat);

//----------------------------------------------------------------------------------------------------------------------------------

//Move to variables!!!!
extern uint8 current_speed;

extern uint32 usb_connect;
extern int32 usb_ep0_state;

extern int32 ep_max_len[];

extern uint8 usb_tx_buf[512];
extern int32 usb_tx_buf_len;
extern int32 usb_tx_pos;

extern uint8 usb_rx_buf[512];
extern int32 usb_rx_buf_len;
extern int32 usb_rx_pos;

union
{
  uint32           data[2];
  USB_Setup_Packet packet;
} usb_setup_packet;

//----------------------------------------------------------------------------------------------------------------------------------
//In original code the register is written as byte, which might be wrong since some data is shifted 8 bits to the left
//So using 32 bit register here
static void usb_phy_setup(int32 addr, int32 data, int32 len)
{
  int32 j;

  //Clear the clock bit
  *USBC_REG_CSR &= 0xFFFFFFFE;
  
  for(j=0;j<len;j++)
  {
    //set the bit address to be written
    *USBC_REG_CSR &= 0xFFFF00FF;
    *USBC_REG_CSR |= ((addr + j) << 8);
    
    //set or clear data bit
    if(data & 0x1)
    {
      *USBC_REG_CSR |= 0x00000080;
    }
    else
    {
      *USBC_REG_CSR &= 0xFFFFFF7F;
    }

    //Create some sort of clock pulse
    *USBC_REG_CSR |= 0x00000001;
    *USBC_REG_CSR &= 0xFFFFFFFE;
    
    //Next data bit
    data >>= 1;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_init(void)
{
  //Enable and clock the USB PHY
  *CCU_USBPHY_CFG |= (CCU_USBPHY_CFG_RST | CCU_USBPHY_CFG_GAT);
  
  //Enable the clock to the USB interface
  *CCU_BUS_CLK_GATE0 |= CCU_BCGR1_USBOTG_EN;
  
  //Lift the reset of the USB interface
  *CCU_BUS_SOFT_RST0 |= CCU_BSRR1_USBOTG_EN;
  
  //Regulation 45 ohms
  usb_phy_setup(0x0c, 0x01, 1);

  //adjust PHY's magnitude and rate
  usb_phy_setup(0x20, 0x14, 5);

  //threshold adjustment disconnect
  usb_phy_setup(0x2a, 3, 2);
  
  //Configurate the FIFO base
  *SYS_CNTRL_USB_FIFO = (*SYS_CNTRL_USB_FIFO & 0xFFFFFFFC) | 0x00000001;
  
  //Enable pull up resistors and force id high and bus valid.
  *USBC_REG_ISCR = USBC_BP_ISCR_DPDM_PULLUP_EN | USBC_BP_ISCR_ID_PULLUP_EN | USBC_BP_ISCR_FORCE_ID | USBC_BP_ISCR_FORCE_VBUS_VALID;  //Original code has 0x0C00 also set (USBC_BP_ISCR_VBUS_VALID_SRC)
  
  //Set interface to pio mode and use fifo
  *USBC_REG_VEND0 = 0x00;

  //Disable the device and it's interrupts
  usb_device_disable();
  
  //Setup the interrupt handler for the USB interface
  //setup_interrupt(USB_IRQ_NUM, usb_irq_handle, 2);
  setup_interrupt(USB_IRQ_NUM, usb_device_irq_handler, 2);
  
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_enable(void)
{
  //Start with unknown speed
  current_speed = USB_SPEED_UNKNOWN;

  //Setup for bulk by clearing the iso bit
  *USBC_REG_PCTL &= ~USBC_BP_POWER_D_ISO_UPDATE_EN;
  
  //Enable the high speed mode
  *USBC_REG_PCTL |= USBC_BP_POWER_D_HIGH_SPEED_EN;

  //Enable the needed interrupts
  *USBC_REG_INTUSBE = USBC_BP_INTUSB_SUSPEND | USBC_BP_INTUSB_RESUME | USBC_BP_INTUSB_RESET | USBC_BP_INTUSB_DISCONNECT;

  //Enable EP0 interrupt
  *USBC_REG_INTTXE = 1;

  //Switch the interface on
  *USBC_REG_PCTL |= USBC_BP_POWER_D_SOFT_CONNECT;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_disable(void)
{
  //Disable all miscellaneous interrupts
  *USBC_REG_INTUSBE = 0;
  
  //Disable all receive interrupts
  *USBC_REG_INTRXE = 0;

  //Disable all transmit interrupts
  *USBC_REG_INTTXE = 0;

  //Clear all pending miscellaneous interrupts
  *USBC_REG_INTUSB = 0xFF;
  
  //Clear all pending receive interrupts
  *USBC_REG_INTRX = 0xFFFF;
  
  //Clear all pending transmit interrupts
  *USBC_REG_INTTX = 0xFFFF;
  
  //Switch the interface off
  *USBC_REG_PCTL &= ~USBC_BP_POWER_D_SOFT_CONNECT;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_irq_handler(void)
{
  //Reading these registers clear all the active interrupt bits, but they still need active clearing
  //So using the registers directly in the if statements does not work
  register uint32 usbirq = *USBC_REG_INTUSB;
  register uint32 txirq  = *USBC_REG_INTTX;
  register uint32 rxirq  = *USBC_REG_INTRX;
  
  //Check on a RESET interrupt
  if(usbirq & USBC_BP_INTUSB_RESET)
  {
    //Clear all pending miscellaneous interrupts
    *USBC_REG_INTUSB = 0xFF;
    
    //Clear all pending receive interrupts
    *USBC_REG_INTRX = 0xFFFF;

    //Clear all pending transmit interrupts
    *USBC_REG_INTTX = 0xFFFF;
    
    //Need to check if this needs to be this way
    usb_connect = 1;
    
    usb_ep0_state = EP0_IDLE;
    
    //Set EP0 as active one
    *USBC_REG_EPIND = 0;
    
    //Switch to default device address
    *USBC_REG_FADDR = 0;
    
    return;
  }

  //Check on a RESUME interrupt
  if(usbirq & USBC_BP_INTUSB_RESUME)
  {
    //Clear the interrupt
    *USBC_REG_INTUSB = USBC_BP_INTUSB_RESUME;
    
    //Back to connected state
    usb_connect = 1;
    usb_ep0_state = EP0_IDLE;
  }

  //Check on a SUSPEND interrupt
  if(usbirq & USBC_BP_INTUSB_SUSPEND)
  {
    //Clear the interrupt
    *USBC_REG_INTUSB = USBC_BP_INTUSB_SUSPEND;
    
    //No longer connected
    usb_connect = 0;
    usb_ep0_state = EP0_IDLE;
  }

  //Check on a DISCONNECT interrupt
  if(usbirq & USBC_BP_INTUSB_DISCONNECT)
  {
    //Clear the interrupt
    *USBC_REG_INTUSB = USBC_BP_INTUSB_DISCONNECT;

    //No longer connected
    usb_connect = 0;
    usb_ep0_state = EP0_IDLE;
    
    //Need to add code here to force the scope to go back to its normal mode
    //Use a flag that is checked in the touch scan for the usb on/off
  }

  //Check on an EP0 interrupt
  if(txirq & USBC_INTTX_FLAG_EP0)
  {
    //Clear the interrupt
    *USBC_REG_INTTX = USBC_INTTX_FLAG_EP0;

    //When speed not previously set check what is negotiated by the host
    if(current_speed == USB_SPEED_UNKNOWN)
    {
      //Check the speed negotiated by the host
      if(*USBC_REG_PCTL & USBC_BP_POWER_D_HIGH_SPEED_FLAG)
      {
        //Only need to do this for one endpoint
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
    
    //Set EP0 as active one
    *USBC_REG_EPIND = 0;

    //Clear stall status if needed
    if(*USBC_REG_CSR0 & USBC_BP_CSR0_D_SENT_STALL)
    {
      //Clear the stall state. Is the only bit cleared when a 0 is written to it.
      *USBC_REG_CSR0 = 0x00;

      usb_ep0_state = EP0_IDLE;
    }
    else
    {
      //Clear setup end when needed
      if(*USBC_REG_CSR0 & USBC_BP_CSR0_D_SETUP_END)
      {
        *USBC_REG_CSR0 = USBC_BP_CSR0_D_SERVICED_SETUP_END;

        usb_ep0_state = EP0_IDLE;
      }

      //Handle the data based on the current state
      switch(usb_ep0_state)
      {
        case EP0_IDLE:
          //Check if a packet has been received
          if(*USBC_REG_CSR0 & USBC_BP_CSR0_D_RX_PKT_READY)
          {
            //Count is only valid when receive packet ready bit is set
            if(*USBC_REG_COUNT0 == 8)
            {
              //Get 8 bytes of data from the fifo.
              usb_setup_packet.data[0] = *USBC_REG_EPFIFO0;
              usb_setup_packet.data[1] = *USBC_REG_EPFIFO0;
              
              //Signal packet has been serviced
              *USBC_REG_CSR0 = USBC_BP_CSR0_D_SERVICED_RX_PKT_READY;
              
              //Need to check if this needs to be done here or after further decoding of the packet
              //Check on the direction of the next data
              if(usb_setup_packet.packet.bRequestType & 0x80)
              {
                usb_ep0_state = EP0_IN_DATA_PHASE;
              }
              else
              {
                usb_ep0_state = EP0_OUT_DATA_PHASE;
              }
              
              //Handle the packet based on the type
              switch(usb_setup_packet.packet.bRequestType & USB_TYPE_MASK)
              {
                case USB_TYPE_STANDARD:
                  usb_mass_storage_standard_request(&usb_setup_packet);
                  break;
                  
                case USB_TYPE_CLASS:
                  //For mass storage check if this is a max LUN request
                  if(usb_setup_packet.packet.bRequest == 0xFE)
                  {
                    //If so check if host allows for the needed data
                    if(usb_setup_packet.packet.wLength >= 1)
                    {
                      //Device has only one logical unit so send a zero
                      *(uint8 *)USBC_REG_EPFIFO0 = 0;
                      
                      //Signal data send and done with this packet
                      *USBC_REG_CSR0 = USBC_BP_CSR0_D_TX_PKT_READY | USBC_BP_CSR0_D_DATA_END;
                    }
                  }
                  else if(usb_setup_packet.packet.bRequest == 0xFF)
                  {
                    //Mass storage reset might also be needed
                    //Signal done with this packet
                    *USBC_REG_CSR0 = USBC_BP_CSR0_D_DATA_END;
                  }
                  else
                  {
                    //Not a mass storage class request then just signal done with this packet
                    *USBC_REG_CSR0 = USBC_BP_CSR0_D_DATA_END;
                  }
                  break;

                case USB_TYPE_VENDOR:
                  //Signal done with this packet
                  *USBC_REG_CSR0 = USBC_BP_CSR0_D_DATA_END;
                  break;
              }
            }
            else
            {
              //Signal packet has been serviced and stall the end point
              *USBC_REG_CSR0 = USBC_BP_CSR0_D_SERVICED_RX_PKT_READY | USBC_BP_CSR0_D_SEND_STALL;
            }
          }
          break;

        case EP0_IN_DATA_PHASE:
          if(!usb_tx_pos)
          {
            usb_ep0_state = EP0_IDLE;
          }
          else
          {
            //Since basically all data send here is constant a setup with a pointer and a count can be used. Also allows for much larger data to be send
            if((usb_tx_buf_len - usb_tx_pos) > 64)
            {
              //Copy the data to the fifo
              memcpy((void *)USBC_REG_EPFIFO0, (void *)(usb_tx_buf + usb_tx_pos), 64);
              
              //Signal packet has been send
              *USBC_REG_CSR0 = USBC_BP_CSR0_D_TX_PKT_READY;
              
              usb_tx_pos += 64;
            }
            else
            {
              //Copy the data to the fifo
              memcpy((void *)USBC_REG_EPFIFO0, (void *)(usb_tx_buf + usb_tx_pos), usb_tx_buf_len - usb_tx_pos);
              
              //Signal packet has been send and that it was the last one
              *USBC_REG_CSR0 = USBC_BP_CSR0_D_TX_PKT_READY | USBC_BP_CSR0_D_DATA_END;
              
              usb_tx_pos = 0;
              usb_ep0_state = EP0_IDLE;
            }
          }
          break;

        case EP0_OUT_DATA_PHASE:
          //This state will most likely not be used
          //Check if a packet has been received
          if(*USBC_REG_CSR0 & USBC_BP_CSR0_D_RX_PKT_READY)
          {
//          len = USBC_ReadLenFromFifo(USBC_EP_TYPE_EP0);
//          USBC_ReadPacket(USBC_SelectFIFO(0), len, databuf);
            
            //Just flush the fifo for now
            *USBC_REG_CSR0 = USBC_BP_CSR0_D_FLUSH_FIFO;

            //Needs proper handling of the data
            //Signal packet has been received and that it was the last one
            *USBC_REG_CSR0 = USBC_BP_CSR0_D_RX_PKT_READY | USBC_BP_CSR0_D_DATA_END;
          
            usb_ep0_state = EP0_IDLE;
          }
          break;

        default:
          usb_ep0_state = EP0_IDLE;
          break;
      }
    }
  }    
    
    
    
    
    
 
  
//----------------  

  //Check on data received for EP1
  if(rxirq & USBC_INTRX_FLAG_EP1)
  {
    //Clear the interrupt
    *USBC_REG_INTRX = USBC_INTTX_FLAG_EP1;
    
    usb_handle_epn_out(1);
  }
  
  //Check on data transmitted for EP1
  if(txirq & USBC_INTTX_FLAG_EP1)
  {
    //Clear the interrupt
    *USBC_REG_INTTX = USBC_INTTX_FLAG_EP1;
    
    usb_handle_epn_in(1);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
