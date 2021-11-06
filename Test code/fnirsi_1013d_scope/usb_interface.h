//----------------------------------------------------------------------------------------------------------------------------------

#ifndef USB_INTERFACE_H
#define USB_INTERFACE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define USBC_REG_FADDR        ((volatile uint8  *)(0x01c13098))
#define USBC_REG_PCTL         ((volatile uint8  *)(0x01c13040))
#define USBC_REG_INTTX        ((volatile uint16 *)(0x01c13044))
#define USBC_REG_INTRX        ((volatile uint16 *)(0x01c13046))
#define USBC_REG_INTTXE       ((volatile uint16 *)(0x01c13048))
#define USBC_REG_INTRXE       ((volatile uint16 *)(0x01c1304A))
#define USBC_REG_INTUSB       ((volatile uint8  *)(0x01c1304C))
#define USBC_REG_INTUSBE      ((volatile uint8  *)(0x01c13050))
#define USBC_REG_FRNUM        ((volatile uint32 *)(0x01c13054))
#define USBC_REG_EPIND        ((volatile uint8  *)(0x01c13042))
#define USBC_REG_TMCTL        ((volatile uint32 *)(0x01c1307C))

#define USBC_REG_TXMAXP       ((volatile uint32 *)(0x01c13080))
#define USBC_REG_CSR0         ((volatile uint16 *)(0x01c13082))
#define USBC_REG_TXCSR        ((volatile uint16 *)(0x01c13082))
#define USBC_REG_RXMAXP       ((volatile uint32 *)(0x01c13084))
#define USBC_REG_RXCSR        ((volatile uint32 *)(0x01c13086))
#define USBC_REG_COUNT0       ((volatile uint16 *)(0x01c13088))
#define USBC_REG_RXCOUNT      ((volatile uint16 *)(0x01c13088))
#define USBC_REG_EP0TYPE      ((volatile uint32 *)(0x01c1308C))
#define USBC_REG_TXTYPE       ((volatile uint32 *)(0x01c1308C))
#define USBC_REG_NAKLIMIT0    ((volatile uint32 *)(0x01c1308D))
#define USBC_REG_TXINTERVAL   ((volatile uint32 *)(0x01c1308D))
#define USBC_REG_RXTYPE       ((volatile uint32 *)(0x01c1308E))
#define USBC_REG_RXINTERVAL   ((volatile uint32 *)(0x01c1308F))

#define USBC_REG_CONFIGDATA   ((volatile uint32 *)(0x01c130c0))

#define USBC_REG_EPFIFO0      ((volatile uint32 *)(0x01c13000))
#define USBC_REG_EPFIFO1      ((volatile uint32 *)(0x01c13004))
#define USBC_REG_EPFIFO2      ((volatile uint32 *)(0x01c13008))
#define USBC_REG_EPFIFO3      ((volatile uint32 *)(0x01c1300C))
#define USBC_REG_EPFIFO4      ((volatile uint32 *)(0x01c13010))
#define USBC_REG_EPFIFO5      ((volatile uint32 *)(0x01c13014))

#define USBC_REG_DEVCTL       ((volatile uint32 *)(0x01c13041))

#define USBC_REG_TXFIFOSZ     ((volatile uint32 *)(0x01c13090))
#define USBC_REG_RXFIFOSZ     ((volatile uint32 *)(0x01c13094))
#define USBC_REG_TXFIFOAD     ((volatile uint32 *)(0x01c13092))
#define USBC_REG_RXFIFOAD     ((volatile uint32 *)(0x01c13096))

#define USBC_REG_VEND0        ((volatile uint8 *)(0x01c13043))
#define USBC_REG_VEND1        ((volatile uint32 *)(0x01c1307D))
#define USBC_REG_VEND3        ((volatile uint32 *)(0x01c1307E))

#define USBC_REG_EPINFO       ((volatile uint32 *)(0x01c13078))
#define USBC_REG_RAMINFO      ((volatile uint32 *)(0x01c13079))
#define USBC_REG_LINKINFO     ((volatile uint32 *)(0x01c1307A))
#define USBC_REG_VPLEN        ((volatile uint32 *)(0x01c1307B))
#define USBC_REG_HSEOF        ((volatile uint32 *)(0x01c1307C))
#define USBC_REG_FSEOF        ((volatile uint32 *)(0x01c1307D))
#define USBC_REG_LSEOF        ((volatile uint32 *)(0x01c1307E))

#define USBC_REG_RPCOUNT      ((volatile uint32 *)(0x01c1308A))

//new
#define USBC_REG_ISCR         ((volatile uint32 *)(0x01c13400))
#define USBC_REG_PHYCTL       ((volatile uint32 *)(0x01c13404))
#define USBC_REG_PHYBIST      ((volatile uint32 *)(0x01c13408))
#define USBC_REG_PHYTUNE      ((volatile uint32 *)(0x01c1340c))

#define USBC_REG_CSR          ((volatile uint32 *)(0x01c13410))

#define USBC_REG_PMU_IRQ      ((volatile uint32 *)(0x01c13800))

//----------------------------------------------------------------------------------------------------------------------------------

#define SYS_CNTRL             ((volatile uint32 *)(0x01c00000))
#define SYS_CNTRL_USB_FIFO    ((volatile uint32 *)(0x01c00004))

//----------------------------------------------------------------------------------------------------------------------------------

#define USB_SPEED_UNKNOWN                  0
#define USB_SPEED_LOW                      1       //usb 1.1
#define USB_SPEED_FULL                     2       //usb 1.1
#define USB_SPEED_HIGH                     3       //usb 2.0

//----------------------------------------------------------------------------------------------------------------------------------

#define EP0_IDLE                           0
#define EP0_IN_DATA_PHASE                  1
#define EP0_OUT_DATA_PHASE                 2
#define EP0_END_XFER                       3
#define EP0_STALL                          4

//----------------------------------------------------------------------------------------------------------------------------------

#define USB_TYPE_MASK                      0x60

#define USB_TYPE_STANDARD                  0x00
#define USB_TYPE_CLASS                     0x20
#define USB_TYPE_VENDOR                    0x40
#define USB_TYPE_RESERVED                  0x60

//----------------------------------------------------------------------------------------------------------------------------------

#define USBC_BP_ISCR_DPDM_CHANGE_DETECT    0x00000010
#define USBC_BP_ISCR_ID_CHANGE_DETECT      0x00000020
#define USBC_BP_ISCR_VBUS_CHANGE_DETECT    0x00000040

#define USBC_BP_ISCR_VBUS_VALID_SRC        0x00000C00
#define USBC_BP_ISCR_FORCE_VBUS_VALID      0x00003000
#define USBC_BP_ISCR_FORCE_ID              0x0000C000
#define USBC_BP_ISCR_DPDM_PULLUP_EN        0x00010000
#define USBC_BP_ISCR_ID_PULLUP_EN          0x00020000

//----------------------------------------------------------------------------------------------------------------------------------
//USB Power Control for device only
#define USBC_BP_POWER_D_ISO_UPDATE_EN     0x80
#define USBC_BP_POWER_D_SOFT_CONNECT      0x40
#define USBC_BP_POWER_D_HIGH_SPEED_EN     0x20
#define USBC_BP_POWER_D_HIGH_SPEED_FLAG   0x10
#define USBC_BP_POWER_D_RESET_FLAG        0x08
#define USBC_BP_POWER_D_RESUME            0x04
#define USBC_BP_POWER_D_SUSPEND           0x02 
#define USBC_BP_POWER_D_ENABLE_SUSPENDM   0x01

//----------------------------------------------------------------------------------------------------------------------------------
//USB interrupt
#define USBC_BP_INTUSB_VBUS_ERROR         0x80
#define USBC_BP_INTUSB_SESSION_REQ        0x40
#define USBC_BP_INTUSB_DISCONNECT         0x20
#define USBC_BP_INTUSB_CONNECT            0x10
#define USBC_BP_INTUSB_SOF                0x08
#define USBC_BP_INTUSB_RESET              0x04
#define USBC_BP_INTUSB_RESUME             0x02
#define USBC_BP_INTUSB_SUSPEND            0x01

//----------------------------------------------------------------------------------------------------------------------------------
//Control and Status Register for EP0 for device only
#define USBC_BP_CSR0_D_FLUSH_FIFO               0x0100
#define USBC_BP_CSR0_D_SERVICED_SETUP_END       0x0080
#define USBC_BP_CSR0_D_SERVICED_RX_PKT_READY    0x0040
#define USBC_BP_CSR0_D_SEND_STALL               0x0020
#define USBC_BP_CSR0_D_SETUP_END                0x0010
#define USBC_BP_CSR0_D_DATA_END                 0x0008
#define USBC_BP_CSR0_D_SENT_STALL               0x0004
#define USBC_BP_CSR0_D_TX_PKT_READY             0x0002
#define USBC_BP_CSR0_D_RX_PKT_READY             0x0001

//----------------------------------------------------------------------------------------------------------------------------------

#define USBC_INTTX_FLAG_EP5               0x20
#define USBC_INTTX_FLAG_EP4               0x10
#define USBC_INTTX_FLAG_EP3               0x08
#define USBC_INTTX_FLAG_EP2               0x04
#define USBC_INTTX_FLAG_EP1               0x02
#define USBC_INTTX_FLAG_EP0               0x01

//----------------------------------------------------------------------------------------------------------------------------------

#define USBC_INTRX_FLAG_EP5               0x20
#define USBC_INTRX_FLAG_EP4               0x10
#define USBC_INTRX_FLAG_EP3               0x08
#define USBC_INTRX_FLAG_EP2               0x04
#define USBC_INTRX_FLAG_EP1               0x02

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bRequestType;
  uint8  bRequest;
  uint16 wValue;
  uint16 wIndex;
  uint16 wLength;
} __attribute__ ((packed)) USB_Setup_Packet;

//----------------------------------------------------------------------------------------------------------------------------------

void usb_device_init(void);


void usb_device_disable(void);

void usb_device_enable(void);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* USB_INTERFACE_H */

