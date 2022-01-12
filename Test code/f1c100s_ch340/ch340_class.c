//----------------------------------------------------------------------------------------------------------------------------------

#include"types.h"
#include "ch340_class.h"

//----------------------------------------------------------------------------------------------------------------------------------

//Global memory assignment for USB device
uint8 usb_rx[1024];                      //Buffer for USB receive data
uint32 volatile usb_rx_in_idx = 0;       //Index for putting data into the USB receive buffer
uint32 volatile usb_rx_out_idx = 0;      //Index for taking data from the USB receive buffer. Set volatile since it changes in interrupt routine.

uint8 usb_tx[1024];                      //Buffer for USB transmit data
uint32 volatile usb_tx_in_idx = 0;       //Index for putting data into the USB transmit buffer
uint32 volatile usb_tx_out_idx = 0;      //Index for taking data from the USB transmit buffer. Set volatile since it changes in interrupt routine.

uint32 volatile fifobuffer[128];         //Buffer to read FIFO data in on EP2 out

uint32 volatile EP2DisableTX = 0;        //Flag to disable the endpoint 2 transmission function.

//----------------------------------------------------------------------------------------------------------------------------------

const USB_DeviceDescriptor CH340_DevDesc =
{
  sizeof (USB_DeviceDescriptor),
  DEVICE_DESCRIPTOR,
  0x0200,                 //Version 2.0
  0x00,
  0x00,
  0x00,
  USB_EP0_FIFO_SIZE,      //Ep0 FIFO size
  0x1A86,                 //Vendor id
  0x7523,                 //Device id
  0x0263,                 //Release version
  0x01,                   //iManufacturer
  0x02,                   //iProduct
  0x00,                   //ISerial
  0x01                    //Number of configurations
};

const CH340_Descriptor CH340_ConfDesc =
{
  {
    sizeof (USB_ConfigDescriptor),
    CONFIGURATION_DESCRIPTOR,
    CONFIG_CH340_DESCRIPTOR_LEN, //Total length of the Configuration descriptor
    0x01, //NumInterfaces
    0x01, //Configuration Value
    0x00, //Configuration Description String Index
    0x80, //Self Powered, no remote wakeup
    0x32  //Maximum power consumption 500 mA
  },
  {
    sizeof (USB_InterfaceDescriptor),
    INTERFACE_DESCRIPTOR,
    0x00, //bInterfaceNumber
    0x00, //bAlternateSetting
    0x03, //ep number
    0xFF, //Interface Class
    0x01, //Interface Subclass
    0x02, //Interface Protocol
    0x00  //Interface Description String Index
  },
  {
    {
      sizeof (USB_EndPointDescriptor),
      ENDPOINT_DESCRIPTOR,
      0x82, //endpoint 2 IN
      2,    //bulk
      512,  //IN EP FIFO size  512 bytes
      0
    },
    {
      sizeof (USB_EndPointDescriptor),
      ENDPOINT_DESCRIPTOR,
      0x02, //endpoint 1 OUT
      2,    //bulk
      512,  //OUT EP FIFO size  512 bytes
      0
    },
    {
      sizeof (USB_EndPointDescriptor),
      ENDPOINT_DESCRIPTOR,
      0x81, //endpoint 1 IN
      3,    //interrupt
      8,    //IN EP FIFO size  8 bytes
      1
    }
  }
};

//USB String Descriptors
const uint8 StringLangID[4] =
{
  0x04,
  0x03,
  0x09,
  0x04 // LangID = 0x0409: U.S. English
};

const uint8 StringVendor[38] =
{
  0x26, // Size of Vendor string
  0x03, // bDescriptorType
  // Manufacturer: "STMicroelectronics"
  'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
  'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
  'c', 0, 's', 0
};


const uint8 StringProduct[28] =
{
  0x1C, // bLength
  0x03, // bDescriptorType
  // Serial name: "USB 2.0-Serial"
  'U', 0, 'S', 0, 'B', 0, '2', 0, '.', 0, '0', 0, '-', 0,
  'S', 0, 'e', 0, 'r', 0, 'i', 0, 'a', 0, 'l', 0
};

const uint8 StringSerial[28] =
{
  0x1C, // bLength
  0x03, // bDescriptorType
  // Serial name: "USB 2.0-Serial"
  'U', 0, 'S', 0, 'B', 0, '2', 0, '.', 0, '0', 0, '-', 0,
  'S', 0, 'e', 0, 'r', 0, 'i', 0, 'a', 0, 'l', 0
};

//Vendor specifics
const uint8 vendorVersion[2] = { 0x31, 0x00 };
const uint8 vendorAttach[2]  = { 0xC3, 0x00 };
const uint8 vendorStatus[2]  = { 0xFF, 0xEE };

//----------------------------------------------------------------------------------------------------------------------------------

//Function for getting a character from the USB receive buffer
int16 ch340Receive(void)
{
  uint8 c;

  //See if there is any data in the buffer
  if(usb_rx_out_idx == usb_rx_in_idx)
    return -1;

  //Get available character
  c = usb_rx[usb_rx_out_idx++];

  //Keep index in valid range
  usb_rx_out_idx %= sizeof(usb_rx);

  return c;
}

//----------------------------------------------------------------------------------------------------------------------------------

//Function for putting a character in the USB transmit buffer
void ch340Send(uint8 c)
{
  uint32 charsfree;

  //Wait until there is room in the transmit buffer
  do
  {
    //Calculate the number of free bytes minus one. Need one byte free because indexes being the same means empty buffer.
    charsfree = usb_tx_out_idx - usb_tx_in_idx - 1;

    //When the in index is higher than the out index the result is negative so add the size of the buffer to get the
    //number of free bytes. Otherwise the result is already positive
    if(usb_tx_in_idx >= usb_tx_out_idx)
      charsfree += sizeof(usb_tx);

    //When charsfree is 0 the buffer is full so calculate again till space comes available
  } while(charsfree == 0);

  //Disable transmission while putting character in the buffer
  EP2DisableTX = 1;

  //Put the character in the transmit buffer and move to next free location
  usb_tx[usb_tx_in_idx++] = c;

  //Keep index in range of buffer size
  usb_tx_in_idx %= sizeof(usb_tx);

  //Enable transmission when done
  EP2DisableTX = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_ch340_out_ep_callback(void *fifo, int length)
{
  uint8 *ptr;
  
  //Not the most elegant solution but will do for now.
  
  //Read the data from the USB FIFO into the DRAM FIFO buffer
  usb_read_from_fifo(fifo, (void *)fifobuffer, length);
  
  //Put the bytes in the receive buffer
  ptr = (uint8 *)fifobuffer;
  
  //Copy the data from the FIFO buffer to the receive buffer
  while(length--)
  {
    //Put the byte in the receive buffer
    usb_rx[usb_rx_in_idx++] = *ptr++;
    usb_rx_in_idx %= sizeof(usb_rx);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void usb_ch340_in_ep_callback(void)
{
  uint32 count;
  uint32 bytes;
  uint8 *ptr;
  
  //Check if transmission has been disabled
  if(EP2DisableTX == 1)
    return;

  //Check if there is data to send to the host
  //Calculate the number of bytes available in the buffer
  if((count = usb_tx_in_idx - usb_tx_out_idx) != 0)
  {
    //When out index bigger then in index data has a rollover in the buffer so need to add the size of the buffer to get the right number
    if(usb_tx_out_idx > usb_tx_in_idx)
      count += sizeof(usb_tx);

    //Check if available number of characters more then the USB buffer size. If so limit the number to be copied
    if(count > 512)
      count = 512;
    
    //Not the most elegant solution but will do for now.
    //Direct to USB FIFO writing would be quicker, but needs lower level code.

    //Set number of bytes to copy to the FIFO buffer
    bytes = count;

    //Put the bytes in the transmit buffer
    ptr = (uint8 *)fifobuffer;
    
    //Copy all the needed bytes to the FIFO buffer
    while(bytes--)
    {
      //Put first byte in low part of the temporary storage for making 16 bits data
      *ptr++ = (usb_tx[usb_tx_out_idx++]);

      //Check if out index needs to rollover back to start of buffer
      usb_tx_out_idx %= sizeof(usb_tx);
    }
    
    //Write the data to the USB device
    usb_write_ep2_data((void *)fifobuffer, count);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
