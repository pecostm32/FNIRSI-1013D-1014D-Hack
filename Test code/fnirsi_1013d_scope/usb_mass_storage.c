#include "usb.h"
#include "usb_dev.h"
#include "mass_storage_class.h"
#include <string.h>

//Wireshark filter (usb.dst == "1.12.0") || (usb.src == "1.12.0") 
//reject mouse !(usb.dst == "1.2.2")  && !(usb.src == "1.2.2")  && !(usb.dst == "1.2.3")  && !(usb.src == "1.2.3") 
//!(usb.dst == "1.2.1")  && !(usb.src == "1.2.1")  &&!(usb.dst == "1.2.2")  && !(usb.src == "1.2.2")  && !(usb.dst == "1.2.3")  && !(usb.src == "1.2.3") 

//USB types, the second of three bRequestType fields

#define USB_TYPE_MASK                   0x60

extern uint32 cardsectorsize;
extern uint32 cardsectors;

uint8 scsi_capacity[8];

uint32 msc_state = MSC_WAIT_COMMAND;

MSC_Status_Wrapper csw;

static USB_DeviceRequest usb_setup_request;

static USB_DeviceDescriptor Mass_Storage_DevDesc =
{
  sizeof (USB_DeviceDescriptor),
  DEVICE_DESCRIPTOR, //1
  0x0200,  //Version 2.0
  0x00,
  0x00,
  0x00,
  64,      //Ep0 FIFO size
  0x0483,  //STM
  0x5720,  //Mass storage device
  0x0200,  //Release version
  0x01,    //iManufacturer
  0x02,    //iProduct
  0x00,    //ISerial
  0x01
};


#define CONFIG_MASS_STORAGE_DESCRIPTOR_LEN   (sizeof(USB_ConfigDescriptor) + sizeof(USB_InterfaceDescriptor) + (sizeof(USB_EndPointDescriptor) * 2))

typedef struct
{
  USB_ConfigDescriptor configuration_descriptor;
  USB_InterfaceDescriptor interface_descritor;
  USB_EndPointDescriptor endpoint_descriptor[2];
} __attribute__ ((packed)) Mass_Storage_Descriptor;


static Mass_Storage_Descriptor Mass_Storage_ConfDesc =
{
  {
    sizeof (USB_ConfigDescriptor),
    CONFIGURATION_DESCRIPTOR,
    CONFIG_MASS_STORAGE_DESCRIPTOR_LEN, //Total length of the Configuration descriptor
    0x01, //NumInterfaces
    0x01, //Configuration Value
    0x00, //Configuration Description String Index
    0xC0, //Self Powered, no remote wakeup
    0x32 //Maximum power consumption 500 mA
  },
  {
    sizeof (USB_InterfaceDescriptor),
    INTERFACE_DESCRIPTOR,
    0x00, //bInterfaceNumber
    0x00, //bAlternateSetting
    0x02, //ep number
    0x08, //Interface Class    (Mass storage interface)
    0x06, //Interface Subclass
    0x50, //Interface Protocol (Bulk only transport)
    0x04  //Interface Description String Index
  },
  {
    {
      sizeof (USB_EndPointDescriptor),
      ENDPOINT_DESCRIPTOR,
      0x81, //endpoint 1 IN
      2,    //bulk
      512,  //IN EP FIFO size  512 bytes
      0
    },
    {
      sizeof (USB_EndPointDescriptor),
      ENDPOINT_DESCRIPTOR,
      0x01, //endpoint 1 OUT
      2,    //bulk
      512,  //OUT EP FIFO size  512 bytes
      0
    }
  }
};

//USB String Descriptors
const uint8 StringLangID[] =
{
  0x04,
  0x03,
  0x09,
  0x04 // LangID = 0x0409: U.S. English
};

const uint8 StringVendor[] =
{
  0x3E, // Size of Vendor string
  0x03, // bDescriptorType
  0x48, 0x00, 0x65, 0x00, 0x72, 0x00, 0x6F, 0x00, 0x4A, 0x00, 0x65, 0x00, 0x20, 0x00, 0x53, 0x00,
  0x63, 0x00, 0x61, 0x00, 0x6E, 0x00, 0x6E, 0x00, 0x65, 0x00, 0x72, 0x00, 0x73, 0x00, 0x20, 0x00,
  0x44, 0x00, 0x72, 0x00, 0x69, 0x00, 0x76, 0x00, 0x65, 0x00, 0x73, 0x00, 0x20, 0x00, 0x2D, 0x00,
  0x20, 0x00, 0x48, 0x00, 0x32, 0x00, 0x37, 0x00, 0x35, 0x00, 0x30, 0x00, 
};

const uint8 StringProduct[] =
{
  0x26, // bLength
  0x03, // bDescriptorType
  0x48, 0x00, 0x32, 0x00, 0x37, 0x00, 0x35, 0x00, 0x30, 0x00, 0x20, 0x00, 0x20, 0x00,
  0x55, 0x00, 0x73, 0x00, 0x62, 0x00, 0x20, 0x00, 0x44, 0x00, 0x65, 0x00, 0x76, 0x00, 0x69, 0x00,
  0x63, 0x00, 0x65, 0x00, 0x73, 0x00, 
};

const uint8 StringSerial[] =
{
  0x1E, // bLength
  0x03, // bDescriptorType
  0x43, 0x00, 0x44, 0x00, 0x43, 0x00, 0x20, 0x00, 0x41, 0x00, 0x43, 0x00, 0x4D, 0x00, 0x20, 0x00, 
  0x63, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x69, 0x00, 0x67, 0x00, 
};

const uint8 StringInterface[] =
{
  0x1E, // bLength
  0x03, // bDescriptorType
  0x43, 0x00, 0x44, 0x00, 0x43, 0x00, 0x20, 0x00, 0x41, 0x00, 0x43, 0x00, 0x4D, 0x00, 0x20, 0x00, 
  0x63, 0x00, 0x6F, 0x00, 0x6E, 0x00, 0x66, 0x00, 0x69, 0x00, 0x67, 0x00, 
};



const uint8 scsi_inquiry_string[] =
{
  0x00, 0x80, 0x02, 0x02, 0x20, 0x00, 0x00, 0x00, 0x46, 0x31, 0x43, 0x31, 0x30, 0x30, 0x53, 0x20, 
  0x20, 0x58, 0x69, 0x61, 0x6F, 0x54, 0x61, 0x6F, 0x51, 0x69, 0x20, 0x20, 0x44, 0x69, 0x73, 0x6B, 
  0x20, 0x31, 0x2E, 0x30
};

const uint8 scsi_sense_data[] =
{
  0x03, 0x00, 0x00, 0x00
};

static void usb_get_device_descriptor(USB_DeviceRequest *req_data)
{
  unsigned int len = req_data->wLength;

  //Limit the length to what is available
  if(len > sizeof(USB_DeviceDescriptor))
  {
    len = sizeof(USB_DeviceDescriptor);
  }
  
  usb_device_write_data_ep_pack(0, (unsigned char *) &Mass_Storage_DevDesc, len);
}

static void usb_get_cfg_descriptor(USB_DeviceRequest *req_data)
{
  unsigned int len = req_data->wLength;

  //Limit the length to what is available
  if(len > sizeof(Mass_Storage_ConfDesc))
  {
    len = sizeof(Mass_Storage_ConfDesc);
  }

  usb_device_write_data_ep_pack(0, (unsigned char *) &Mass_Storage_ConfDesc, len);
}

static inline void udp_get_dev_descriptor_string(USB_DeviceRequest *dreq)
{
  int32        len = dreq->wLength;
  int32        index = dreq->wValue & 0xff;
  const uint8 *sptr;

  switch(index)
  {
    case 0:
      sptr = StringLangID;

      if(len > sizeof(StringLangID))
      {
        len = sizeof(StringLangID);
      }
      break;

    case 1:
    case 3:
    case 0xEE:
      sptr = StringVendor;
      
      if(len >= sizeof(StringVendor))
      {
        len = sizeof(StringVendor);
      }
      break;

    case 2:
      sptr = StringProduct;
      
      if(len >= 38)
      {
        len = 38;
      }
      break;

    case 4:
      sptr = StringInterface;
      
      if(len >= sizeof(StringInterface))
      {
        len = sizeof(StringInterface);
      }
      break;
      
    default:
      sptr = StringSerial;
      
      if(len >= sizeof(StringSerial))
      {
        len = sizeof(StringSerial);
      }
      break;
  }
  
  usb_device_write_data_ep_pack(0, (uint8 *)sptr, len);
}

static void usb_descriptor_request(USB_DeviceRequest* req_data)
{
  unsigned char wValue = req_data->wValue >> 8;
  
  switch(wValue)
  {
    case DEVICE_DESCRIPTOR:                   //1
      usb_get_device_descriptor(req_data);
      break;
      
    case CONFIGURATION_DESCRIPTOR:            //2
      usb_get_cfg_descriptor(req_data);
      break;
      
    case STRING_DESCRIPTOR:                   //3
      udp_get_dev_descriptor_string(req_data);
      break;
      
    default:
      //In the scope code there is something extra, where if the wValue not is 0x22 they send 0x23 (35) bytes coming from 0x80188FCC
      //Not sure if this is needed
      
      
      
      USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
      break;
  }
}

static void set_address(unsigned char addr)
{
  usb_device_clear_setup_end();   //This is not done in the scope code

  usb_device_set_address(addr);
  
  USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);

  usb_device_set_ep0_state(EP0_IDLE);
}

static void set_configuration(void)
{
  usb_config_ep_out(1, 512, USBC_TS_TYPE_BULK);
  usb_config_ep_in(1, 512, USBC_TS_TYPE_BULK);
  
  USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  usb_device_clear_setup_end();
  usb_device_send_nullpack_ep0();
  usb_device_set_ep0_state(EP0_IDLE);
}

static void standard_setup_request(USB_DeviceRequest *req_data)
{
  unsigned char bRequest = req_data->bRequest;

  if(bRequest == USB_REQ_GET_DESCRIPTOR)
  {
    usb_descriptor_request(req_data);
  }
  else if(bRequest == USB_REQ_SET_CONFIGURATION)
  {
    set_configuration();
  }
  else if(bRequest == USB_REQ_GET_CONFIGURATION)
  {
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  }
  else if(bRequest == USB_REQ_SET_INTERFACE)
  {
    //not supported
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  }
  else if(bRequest == USB_REQ_GET_INTERFACE)
  {
    //not supported
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  }
  else if(bRequest == USB_REQ_SET_ADDRESS)
  {
    //Not a good thing to do in an USB interrupt. Better way to deal with this is a flag to signal address needs to be set, and set the address on an end of setup interrupt??
    volatile int time_dly = 100000;

    while(time_dly--); //delay wait zero out pack ok
    
    //In the scope the delay is sd_card_delay(1);
    
    set_address(req_data->wValue & 0x7f);
  }
  else if(bRequest == USB_REQ_SET_DESCRIPTOR)
  {
    //not supported
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  }
  else if(bRequest == USB_REQ_SYNCH_FRAME)
  {
    //not supported
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  }
  else if(bRequest == USB_REQ_CLEAR_FEATURE)
  {
    //Might need more filtering. Looking at tinyusb project things are done differently
    //This is extra in the scope. Not sure if it is really needed
    usb_device_clear_ep_halt(req_data->wIndex);
  }
  else
  {
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
    //other command process by controller
  }
}

static void class_setup_request(USB_DeviceRequest* req_data)
{
  //Only one logical unit
  uint8 max_lun = 0;
  
  //Need to respond to max lun request
  if(req_data->bRequest == 0xFE)
  {
    if(req_data->wLength > 1)
    {
      req_data->wLength = 1;
    }
    
    usb_device_write_data_ep_pack(0, &max_lun, req_data->wLength);
  }
  else if(req_data->bRequest == 0xFF)
  {
    //Mass storage reset might also be needed
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  }
  else
  {
    USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
  }
}

void usb_mass_storage_setup_handle(unsigned char *dat, int len)
{
  if(len == 8)
  {
    memcpy(&usb_setup_request, dat, len); //usb is big endian

    if((usb_setup_request.bRequestType & USB_TYPE_MASK) == USB_TYPE_STANDARD)
    {
      standard_setup_request(&usb_setup_request);
    }
    else if((usb_setup_request.bRequestType & USB_TYPE_MASK) == USB_TYPE_CLASS)
    {
      class_setup_request(&usb_setup_request);
    }
    else if((usb_setup_request.bRequestType & USB_TYPE_MASK) == USB_TYPE_VENDOR)
    {
      USBC_Dev_ReadDataStatus(USBC_EP_TYPE_EP0, 1);
    }
  }
}


void usb_mass_storage_out_ep_callback(unsigned char *pdat, int len)
{
  //usb_handle_mass_storage_write in Ghidra

  
  //Data coming from the host contains a CBW and needs to be handled here

  
  //Need a state machine to handle the data from the host. On startup the system is in an idle state
  //When data is received in this state it should be a CBW that needs to be checked
  
  //State_Command
    //Check if the length is that of a CBW
    //Check if the signature matches
    //When invalid stall the endpoints and switch to need reset stage
  
    //When valid setup a CSW for the response
    //Handle the command given in the CBW


  
  //Handle host data based on the current state
  switch(msc_state)
  {
    case MSC_WAIT_COMMAND:
      {
        //Make the data accessible as a command block wrapper
        MSC_Command_Wrapper *cbw = (MSC_Command_Wrapper *)pdat;

        //Check if the data is valid
        if((len == MSC_CBW_LENGTH) && (cbw->signature == MSC_CBW_SIGNATURE))
        {
          //If so process the command

          //First 
          //Copy the tag to the csw and set the csw signature (can be done in a setup routine)
          csw.signature    = MSC_CSW_SIGNATURE;
          csw.tag          = cbw->tag;
          csw.data_residue = 0;
          csw.status       = MSC_CSW_STATUS_OK;
            
          //Parse the command
          switch(cbw->command[0])
          {
            case SCSI_CMD_INQUIRY:
              usb_device_write_data_ep_pack(1, (uint8 *)scsi_inquiry_string, sizeof(scsi_inquiry_string));
              
              //Switch to status state (No more data to send)
              msc_state = MSC_SEND_STATUS;
              break;

            //Ignore these commands for now
            case SCSI_CMD_TEST_UNIT_READY:
            case SCSI_CMD_PREVENT_ALLOW_MEDIUM_REMOVAL:
            case SCSI_CMD_START_STOP_UNIT:
              //Needs to be done here since the data needs to be ready before the in request is send from the host
              //Send the ok status
              usb_device_write_data_ep_pack(1, (uint8 *)&csw, MSC_CSW_LENGTH);

              //Switch to wait for command state
              msc_state = MSC_WAIT_COMMAND;
              break;
              
            case SCSI_CMD_READ_CAPACITY_10:
              //Need to return the last logical block address and the block size
              scsi_capacity[0] = cardsectors >> 24;
              scsi_capacity[1] = cardsectors >> 16;
              scsi_capacity[2] = cardsectors >> 8;
              scsi_capacity[3] = cardsectors;

              scsi_capacity[4] = cardsectorsize >> 24;
              scsi_capacity[5] = cardsectorsize >> 16;
              scsi_capacity[6] = cardsectorsize >> 8;
              scsi_capacity[7] = cardsectorsize;

              usb_device_write_data_ep_pack(1, scsi_capacity, sizeof(scsi_capacity));
              
              //Switch to status state (No more data to send)
              msc_state = MSC_SEND_STATUS;
              break;
              
            case SCSI_CMD_MODE_SENSE_6:
              usb_device_write_data_ep_pack(1, (uint8 *)scsi_inquiry_string, sizeof(scsi_inquiry_string));
              
              //Switch to status state (No more data to send)
              msc_state = MSC_SEND_STATUS;
              break;
              
            case SCSI_CMD_READ_10:
              //This requires a bit more checking!!!!!
              break;
          }
          
          //LUN should be zero since this device only supports the single unit
          
          //The direction bit tells if the host will send data or the device needs to send data
          
          //Command length needs to be from 1 to 16, otherwise it is an error
          
          
          //Switch to data state
          
          
          //Send zero byte data
          
        }
        else
        {
          //Not a valid command block wrapper then stall the endpoints
          USBC_Dev_EpSendStall(USBC_EP_TYPE_TX);
          USBC_Dev_EpSendStall(USBC_EP_TYPE_RX);
        }
      }
      break;
      
  }
  
  
  
}

void usb_mass_storage_in_ep_callback(void)
{
  //This will only need to handle data transfer to the host when there is a lot of data requested. > 512 bytes
  //or a data packet has been send and the csw needs to follow

  switch(msc_state)
  {
    case MSC_SEND_DATA:
      //Need check on if more data needs to be send!!!!
      
      //No data to send then fall through to status
      
    case MSC_SEND_STATUS:
      //If not send status state
      usb_device_write_data_ep_pack(1, (uint8 *)&csw, MSC_CSW_LENGTH);
      
      //switch to wait for command state
      msc_state = MSC_WAIT_COMMAND;
      break;
  }
  
}

