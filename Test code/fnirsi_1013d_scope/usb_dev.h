//----------------------------------------------------------------------------------------------------------------------------------

#ifndef DRIVER_INCLUDE_USB_DEV_H_
#define DRIVER_INCLUDE_USB_DEV_H_

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

enum ep0_state
{
  EP0_IDLE,
  EP0_IN_DATA_PHASE,
  EP0_OUT_DATA_PHASE,
  EP0_END_XFER,
  EP0_STALL,
};

enum usb_device_speed
{
  USB_SPEED_UNKNOWN = 0,      //enumerating
  USB_SPEED_LOW,              //usb 1.1
  USB_SPEED_FULL,             //usb 1.1
  USB_SPEED_HIGH              //usb 2.0
};

enum usb_xfer_type_req 
{
  NONE_REQ,
  SET_ADDR,
  SET_CONFIG,
};

//----------------------------------------------------------------------------------------------------------------------------------

//usb transfer type 
#define  USBC_TS_TYPE_IDLE                  0
#define  USBC_TS_TYPE_CTRL                  1
#define  USBC_TS_TYPE_ISO                   2
#define  USBC_TS_TYPE_INT                   3
#define  USBC_TS_TYPE_BULK                  4

//----------------------------------------------------------------------------------------------------------------------------------

extern uint32 usb_connect;

//----------------------------------------------------------------------------------------------------------------------------------

extern int32 usb_ep0_state;

//----------------------------------------------------------------------------------------------------------------------------------


void usb_dev_bsp_init(void);

void usb_setup_interrupt(void);

void usb_udc_disable(void);

//----------------------------------------------------------------------------------------------------------------------------------


int32 usb_device_write_data(int32 ep, uint8 * databuf, int32 len);
int32 usb_device_write_data_ep_pack(int32 ep, uint8 * databuf, int32 len);
void  usb_device_send_nullpack_ep0(void);
void  usb_device_read_data_status_ep0(uint8 is_complete);
void  usb_device_clear_setup_end(void);
void  usb_device_set_address(uint8 addr);
void  usb_device_set_ep0_state(enum ep0_state state);
void  usb_device_set_xfer_type(enum usb_xfer_type_req type);
void  usb_config_ep_out(int32 epidx, int32 maxpack, int32 type);
void  usb_config_ep_in(int32 epidx, int32 maxpack, int32 type);
void  usb_device_clear_ep_halt(int32 epaddr);

//----------------------------------------------------------------------------------------------------------------------------------

void usb_mass_storage_setup_handle(uint8 *dat, int len);

void usb_mass_storage_in_ep_callback(void);

void usb_mass_storage_out_ep_callback(uint8 *pdat, int len);


//----------------------------------------------------------------------------------------------------------------------------------

#endif //DRIVER_INCLUDE_USB_DEV_H_
