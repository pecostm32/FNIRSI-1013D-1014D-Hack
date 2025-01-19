//----------------------------------------------------------------------------------------------------------------------------------

#ifndef VARIABLES_H
#define VARIABLES_H

//----------------------------------------------------------------------------------------------------------------------------------

#include <string.h>

#include "types.h"
#include "font_structs.h"
#include "fnirsi_1013d_firmware_restore.h"
#include "ff.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Defines
//----------------------------------------------------------------------------------------------------------------------------------

#define VIEW_NOT_ACTIVE                   0
#define VIEW_ACTIVE                       1

#define VIEW_ITEM_XSTART                  2
#define VIEW_ITEM_YSTART                  0
#define VIEW_ITEM_WIDTH                 182
#define VIEW_ITEM_HEIGHT                120

#define VIEW_ITEM_XNEXT                 182
#define VIEW_ITEM_YNEXT                 120

#define VIEW_ITEM_XLAST                 720

#define VIEW_THUMBNAIL_DATA_SIZE     400000
#define VIEW_FILE_NUMBER_DATA_SIZE     2000
#define VIEW_SETUP_DATA_SIZE           1000

#define VIEW_MAX_ITEMS                 1000

#define VIEW_ITEMS_PER_PAGE              16

#define VIEW_TYPE_MASK                    1

#define VIEW_TYPE_PICTURE                 0
#define VIEW_TYPE_WAVEFORM                1

#define VIEW_ITEM_SELECTED_XSTART        77
#define VIEW_ITEM_SELECTED_YSTART        45

//States for displaying the selected signs
#define VIEW_ITEM_NOT_SELECTED            0
#define VIEW_ITEM_SELECTED_NOT_DISPLAYED  1
#define VIEW_ITEM_SELECTED_DISPLAYED      2
#define VIEW_ITEM_NOT_SELECTED_DISPLAYED  3

//States for select mode
#define VIEW_SELECT_NONE                  0
#define VIEW_SELECT_ALL                   1
#define VIEW_SELECT_INDIVIDUAL            2

//States for bottom file menu displaying
#define VIEW_BOTTON_MENU_INIT             3     //This is a combination of init and show, so show needs to be 1
#define VIEW_BOTTON_MENU_SHOW             1     //Needs to be 1 / 0 for the show and hide since an exor is used to toggle the modes
#define VIEW_BOTTON_MENU_HIDE             0

#define VIEW_TRACE_LOAD_OK                0
#define VIEW_TRACE_LOAD_ERROR             1

#define VIEW_CONFIRM_DELETE_NO            1
#define VIEW_CONFIRM_DELETE_YES           2

#define PICTURE_DATA_SIZE                 (800 * 480 * 2)                              //trace data
#define PICTURE_PIXEL_OFFSET              (70 + 15000)                                 //Bitmap header + trace data
#define PICTURE_FILE_SIZE                 (PICTURE_PIXEL_OFFSET + PICTURE_DATA_SIZE)   //Bitmap header + trace data + pixel data

#define MESSAGE_SAVE_SUCCESSFUL           0
#define MESSAGE_FILE_CREATE_FAILED        1
#define MESSAGE_FILE_OPEN_FAILED          2
#define MESSAGE_FILE_WRITE_FAILED         3
#define MESSAGE_FILE_READ_FAILED          4
#define MESSAGE_FILE_SEEK_FAILED          5


#define FLASH_COPY_BUFFER_SIZE            8192

//----------------------------------------------------------------------------------------------------------------------------------
//Linker variables
//----------------------------------------------------------------------------------------------------------------------------------

extern uint8 BSS_START;
extern uint8 BSS_END;

//----------------------------------------------------------------------------------------------------------------------------------
//Touch data
//----------------------------------------------------------------------------------------------------------------------------------

extern uint8 tp_config_data[186];

//----------------------------------------------------------------------------------------------------------------------------------
//File data
//----------------------------------------------------------------------------------------------------------------------------------

extern FATFS fs;

extern uint32 massstoragedata[100000];

extern uint32 flashbuffer[FLASH_COPY_BUFFER_SIZE];

extern uint32 fwcheckdata[9];

//----------------------------------------------------------------------------------------------------------------------------------
//Display data
//----------------------------------------------------------------------------------------------------------------------------------

//This first buffer is defined as 32 bits to be able to write it to file
extern uint32 maindisplaybuffer[SCREEN_SIZE / 2];

extern uint16 displaybuffer[SCREEN_SIZE];

extern uint16 gradientbuffer[SCREEN_HEIGHT];

//----------------------------------------------------------------------------------------------------------------------------------
//Fonts
//----------------------------------------------------------------------------------------------------------------------------------

extern FONTDATA font_5;
extern FONTDATA font_7;

//----------------------------------------------------------------------------------------------------------------------------------
//Icons
//----------------------------------------------------------------------------------------------------------------------------------

extern const uint8 letter_c_icon[];
extern const uint8 letter_e_icon[];
extern const uint8 letter_o_icon[];
extern const uint8 letter_p_icon[];
extern const uint8 letter_s_icon[];

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* VARIABLES_H */

