//----------------------------------------------------------------------------------------------------------------------------------

#ifndef FNIRSI_1013D_FIRMWARE_RESTORE_H
#define FNIRSI_1013D_FIRMWARE_RESTORE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

#define SCREEN_SIZE     (SCREEN_WIDTH * SCREEN_HEIGHT)

//----------------------------------------------------------------------------------------------------------------------------------

void setup_display_lib(void);

void draw_startup_screen(void);

void draw_progress_bar(uint32 xpos, uint32 ypos, uint32 progress);

int32 restore_flash_data(char *filename, uint32 address);

//----------------------------------------------------------------------------------------------------------------------------------


#endif /* FNIRSI_1013D_FIRMWARE_RESTORE_H */

