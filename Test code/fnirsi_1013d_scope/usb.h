//----------------------------------------------------------------------------------------------------------------------------------

#ifndef  __USB_H__
#define  __USB_H__

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "usb_bsp.h"

//----------------------------------------------------------------------------------------------------------------------------------

int usb_device_init(unsigned char type);

//----------------------------------------------------------------------------------------------------------------------------------

#define USB_TYPE_DISCONNECT 0
#define USB_TYPE_USB_HID 1
#define USB_TYPE_USB_COM 2

//----------------------------------------------------------------------------------------------------------------------------------
//Standard requests

#define USB_REQ_GET_STATUS          0x00
#define USB_REQ_CLEAR_FEATURE       0x01
//0x02 is reserved
#define USB_REQ_SET_FEATURE         0x03
//0x04 is reserved 
#define USB_REQ_SET_ADDRESS         0x05
#define USB_REQ_GET_DESCRIPTOR      0x06
#define USB_REQ_SET_DESCRIPTOR      0x07
#define USB_REQ_GET_CONFIGURATION   0x08
#define USB_REQ_SET_CONFIGURATION   0x09
#define USB_REQ_GET_INTERFACE       0x0A
#define USB_REQ_SET_INTERFACE       0x0B
#define USB_REQ_SYNCH_FRAME         0x0C

#define USB_TYPE_STANDARD           (0x00 << 5)
#define USB_TYPE_CLASS              (0x01 << 5)
#define USB_TYPE_VENDOR             (0x02 << 5)
#define USB_TYPE_RESERVED           (0x03 << 5)

#define USB_RECIP_DEVICE            0x00
#define USB_RECIP_INTERFACE         0x01
#define USB_RECIP_ENDPOINT          0x02
#define USB_RECIP_OTHER             0x03

//----------------------------------------------------------------------------------------------------------------------------------
// Descriptor types ... USB 2.0 spec table 9.5

#define USB_DT_DEVICE                  0x01
#define USB_DT_CONFIG                  0x02
#define USB_DT_STRING                  0x03
#define USB_DT_INTERFACE               0x04
#define USB_DT_ENDPOINT                0x05
#define USB_DT_DEVICE_QUALIFIER        0x06
#define USB_DT_OTHER_SPEED_CONFIG      0x07
#define USB_DT_INTERFACE_POWER         0x08

//these are from a minor usb 2.0 revision (ECN)
#define USB_DT_OTG                     0x09
#define USB_DT_DEBUG                   0x0A
#define USB_DT_INTERFACE_ASSOCIATION   0x0B

#define USB_DT_REPORT                  0x21

#define USB_DT_DEVICE_SIZE               18
#define USB_DT_CONFIG_SIZE                9

//----------------------------------------------------------------------------------------------------------------------------------

#define USB_DT_CS_INTERFACE  (USB_TYPE_CLASS | USB_DT_INTERFACE)

//----------------------------------------------------------------------------------------------------------------------------------
//identification values and masks to identify request types 
#define USB_REQUEST_CLASS_MASK              (0x60)
#define USB_REQUEST_CLASS_STRD              (0x00)
#define USB_REQUEST_CLASS_CLASS             (0x20)
#define USB_REQUEST_CLASS_VENDOR            (0x40)

#define USB_FUNCTION_VENDOR_ID            (0x0525)                //Vendor  ID
#define USB_FUNCTION_PRODUCT_ID           (0xa4a7)                //DATAPIPE Product ID
#define USB_FUNCTION_SERIAL_PRODUCT_ID    (0x8206)                //SERIAL Product ID
#define USB_FUNCTION_HID_PRODUCT_ID       (0x8203)                //HID KBW Product ID
#define USB_FUNCTION_UPOS_PRODUCT_ID      (0x8210)                //HID POS Product ID
#define USB_FUNCTION_RELEASE_NO           (0x0310)                //Release Number

//----------------------------------------------------------------------------------------------------------------------------------

typedef enum
{
  ENDPOINT_TYPE_CONTROL,
          
  //Typically used to configure a device when attached to the host.
  //It may also be used for other device specific purposes, including
  //control of other pipes on the device.
  
  ENDPOINT_TYPE_ISOCHRONOUS,
  //Typically used for applications which need guaranteed speed.
  //Isochronous transfer is fast but with possible data loss. A typical
  //use is audio data which requires a constant data rate.
  
  ENDPOINT_TYPE_BULK,
  //Typically used by devices that generate or consume data in relatively
  //large and bursty quantities. Bulk transfer has wide dynamic latitude
  //in transmission constraints. It can use all remaining available bandwidth,
  //but with no guarantees on bandwidth or latency. Since the USB bus is
  //normally not very busy, there is typically 90% or more of the bandwidth
  //available for USB transfers.
  
  ENDPOINT_TYPE_INTERRUPT
  //Typically used by devices that need guaranteed quick responses
  //(bounded latency)
} USB_ENDPOINT_TYPE;

//----------------------------------------------------------------------------------------------------------------------------------

enum USB_STANDARD_REQUEST_CODE
{
  GET_STATUS,
  CLEAR_FEATURE,
  SET_FEATURE = 3,
  SET_ADDRESS = 5,
  GET_DESCRIPTOR,
  SET_DESCRIPTOR,
  GET_CONFIGURATION,
  SET_CONFIGURATION,
  GET_INTERFACE,
  SET_INTERFACE,
  SYNCH_FRAME
};

//----------------------------------------------------------------------------------------------------------------------------------

enum USB_DESCRIPTOR_TYPE
{
  DEVICE_DESCRIPTOR = 1,
  CONFIGURATION_DESCRIPTOR,
  STRING_DESCRIPTOR,
  INTERFACE_DESCRIPTOR,
  ENDPOINT_DESCRIPTOR,
  DEVICE_QUALIFIER_DESCRIPTOR,
  OTHER_SPEED_CONFIGURATION_DESCRIPTOR,
  INTERFACE_POWER1_DESCRIPTOR,
  INTERFACE_ASSOC_DESCRIPTOR = 11,
  HID_DESCRIPTOR_TYPE = 0x21,
  REPORT_DESCRIPTOR = 0x22
};

//----------------------------------------------------------------------------------------------------------------------------------

enum USB_FEATURE_SELECTOR
{
  ENDPOINT_HALT,
  DEVICE_REMOTE_WAKEUP,
  TEST_MODE
};

//----------------------------------------------------------------------------------------------------------------------------------

enum USB_CLASS_CODE
{
  CLASS_DEVICE,
  CLASS_AUDIO,
  CLASS_COMM_AND_CDC_CONTROL,
  CLASS_HID,
  CLASS_PHYSICAL = 0x05,
  CLASS_STILL_IMAGING,
  CLASS_PRINTER,
  CLASS_MASS_STORAGE,
  CLASS_HUB,
  CLASS_CDC_DATA,
  CLASS_SMART_CARD,
  CLASS_CONTENT_SECURITY = 0x0d,
  CLASS_VIDEO,
  CLASS_DIAGNOSTIC_DEVICE = 0xdc,
  CLASS_WIRELESS_CONTROLLER = 0xe0,
  CLASS_MISCELLANEOUS = 0xef,
  CLASS_APP_SPECIFIC = 0xfe,
  CLASS_VENDOR_SPECIFIC = 0xff
};

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bRequestType;
  uint8  bRequest;
  uint16 wValue;
  uint16 wIndex;
  uint16 wLength;
} __attribute__ ((packed)) USB_DeviceRequest;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bLength;
  uint8  bDescriptorType;
  uint16 bcdUSB;
  uint8  bDeviceClass;
  uint8  bDeviceSubClass;
  uint8  bDeviceProtocol;
  uint8  bMaxPacketSize0;
  uint16 idVendor;
  uint16 idProduct;
  uint16 bcdDevice;
  uint8  iManufacturer;
  uint8  iProduct;
  uint8  iSerialNumber;
  uint8  bNumConfigurations;
} __attribute__ ((packed)) USB_DeviceDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bLength;
  uint8  bDescriptorType;
  uint16 bcdUSB;
  uint8  bDeviceClass;
  uint8  bDeviceSubClass;
  uint8  bDeviceProtocol;
  uint8  bMaxPacketSize0;
  uint8  bNumConfigurations;
  uint8  bReserved;
} __attribute__ ((packed)) USB_DeviceQualifierDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bLength;
  uint8  bDescriptorType;
  uint16 wTotalLength;
  uint8  bNumInterfaces;
  uint8  bConfigurationValue;
  uint8  iConfiguration;
  uint8  bmAttributes;
  uint8  MaxPower;
} __attribute__ ((packed)) USB_ConfigDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bLength;
  uint8  bDescriptorType;
  uint16 wTotalLength;
  uint8  bNumInterfaces;
  uint8  bConfigurationValue;
  uint8  iConfiguration;
  uint8  bmAttributes;
  uint8  bMaxPower;
} __attribute__ ((packed)) USB_OtherSpeedConfigDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 bLength;
  uint8 bDescriptorType;
  uint8 bInterfaceNumber;
  uint8 bAlternateSetting;
  uint8 bNumEndpoints;
  uint8 bInterfaceClass;
  uint8 bInterfaceSubClass;
  uint8 bInterfaceProtocol;
  uint8 iInterface;
} __attribute__ ((packed)) USB_InterfaceDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bLegth;
  uint8  bDescriptorType;
  uint8  bEndpointAddress;
  uint8  bmAttributes;
  uint16 wMaxPacketSize;
  uint8  bInterval;
} __attribute__ ((packed)) USB_EndPointDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 bLength;
  uint8 bDescriptorType;
  uint16 SomeDesriptor[1];
} __attribute__ ((packed)) USB_StringDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 bLength;
  uint8 bDescriptorType;
  uint8 bFirstInterface;
  uint8 bInterfaceCount;
  uint8 bFunctionClass;
  uint8 bFunctionSubClass;
  uint8 bFunctionProtocol;
  uint8 iFunction;
} __attribute__ ((packed)) USB_InterfaceAssocDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 bLength;
  uint8 bDescriptorType;
  uint8 bDescriptorSubType;
  uint16 bcdCDC;
} __attribute__ ((packed)) USB_CDC_HeaderDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 bLength;
  uint8 bDescriptorType;
  uint8 bDescriptorSubType;
  uint8 bmCapabilities;
  uint8 bDataInterface;
} __attribute__ ((packed)) USB_CDC_CallMgmtDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 bLength;
  uint8 bDescriptorType;
  uint8 bDescriptorSubType;
  uint8 bmCapabilities;
} __attribute__ ((packed)) USB_CDC_AcmDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8 bLength;
  uint8 bDescriptorType;
  uint8 bDescriptorSubType;
  uint8 bMasterInterface0;
  uint8 bSlaveInterface0;
} __attribute__ ((packed)) USB_CDC_UnionDescriptor;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint32 dwDTERate;
  uint8  bCharFormat;
  uint8  bParityType;
  uint8  bDataBits;
} __attribute__ ((packed)) USB_CDC_LineCoding;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
  uint8  bLength;
  uint8  bDescriptorType;
  uint16 bcdHID;
  uint8  bCountryCode;
  uint8  bNumDescriptors;
  uint8  next_bDescriptorType;
  uint16 wDescriptorLength;
} __attribute__ ((packed)) USB_HID_Descriptor;

//----------------------------------------------------------------------------------------------------------------------------------

#endif   //__USB_H__
