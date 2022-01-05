//----------------------------------------------------------------------------------------------------------------------------------

#ifndef CH340_CLASS_H
#define CH340_CLASS_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "usb_interface.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define CONFIG_CH340_DESCRIPTOR_LEN   (sizeof(USB_ConfigDescriptor) + sizeof(USB_InterfaceDescriptor) + (sizeof(USB_EndPointDescriptor) * 3))

//----------------------------------------------------------------------------------------------------------------------------------

extern const USB_DeviceDescriptor CH340_DevDesc;

extern const CH340_Descriptor CH340_ConfDesc;

extern const uint8 StringLangID[4];
extern const uint8 StringVendor[38];
extern const uint8 StringProduct[28];
extern const uint8 StringSerial[28];

extern const uint8 vendorVersion[2];
extern const uint8 vendorAttach[2];
extern const uint8 vendorStatus[2];

//----------------------------------------------------------------------------------------------------------------------------------

int16 ch340Receive(void);
void  ch340Send(uint8 c);

//----------------------------------------------------------------------------------------------------------------------------------

void usb_ch340_out_ep_callback(void *fifo, int length);

void usb_ch340_in_ep_callback(void);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* CH340_CLASS_H */

