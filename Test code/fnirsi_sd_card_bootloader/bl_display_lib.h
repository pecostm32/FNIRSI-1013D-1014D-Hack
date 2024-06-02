//----------------------------------------------------------------------------------------------------------------------------------

#ifndef BL_DISPLAY_LIB_H
#define BL_DISPLAY_LIB_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"
#include "bl_font_structs.h"

//----------------------------------------------------------------------------------------------------------------------------------

#define DISPLAY_DRAW_CLOCK_WISE             0
#define DISPLAY_DRAW_COUNTER_CLOCK_WISE     1

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagDisplayData   DISPLAYDATA,  *PDISPLAYDATA;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagDisplayData
{
  PFONTDATA  font;
  uint16     fg_color;
  uint16    *screenbuffer;
  uint16    *linepointer;
  uint32     xpos;
  uint32     ypos;
  uint32     width;
  uint32     height;
  uint32     pixelsperline;
};

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_dimensions(uint32 width, uint32 height);
void display_set_fg_color(uint32 color);
void display_set_font(PFONTDATA font);
void display_set_screen_buffer(uint16 *buffer);

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_line(uint32 xstart, uint32 ystart, uint32 xend, uint32 yend);
void display_draw_horz_line(uint32 ypos, uint32 xstart, uint32 xend);
void display_draw_vert_line(uint32 xpos, uint32 ystart, uint32 yend);
void display_draw_rect(uint32 xpos, uint32 ypos, uint32 width, uint32 height);

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rect(uint32 xpos, uint32 ypos, uint32 width, uint32 height);

///----------------------------------------------------------------------------------------------------------------------------------

void display_hex(uint32 xpos, uint32 ypos, uint32 digits, int32 value);
void display_decimal(uint32 xpos, uint32 ypos, int32 value);
void display_character(uint32 xpos, uint32 ypos, int8 text);
void display_text(uint32 xpos, uint32 ypos, const char *text);

//----------------------------------------------------------------------------------------------------------------------------------
//Variable width font handling functions

void draw_vw_character(uint16 character);

PFONTINFORMATION check_char_in_vw_font(PFONTINFORMATION info, uint16 character);

//----------------------------------------------------------------------------------------------------------------------------------
//Fixed width font handling functions

void draw_fw_character(uint16 character);
void render_fw_character(uint16 character);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* BL_DISPLAY_LIB_H */

//----------------------------------------------------------------------------------------------------------------------------------
