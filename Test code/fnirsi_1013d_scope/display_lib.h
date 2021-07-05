//----------------------------------------------------------------------------------------------------------------------------------

#ifndef DISPLAY_LIB_H
#define DISPLAY_LIB_H

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagDisplayData   DISPLAYDATA,  *PDISPLAYDATA;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagDisplayData
{
  uint16     fg_color;
  uint16     bg_color;
  uint16    *screenbuffer;
  PFONTDATA  font;
  uint16     xpos;
  uint16     ypos;
};

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_position(PDISPLAYDATA display, uint16 xpos, uint16 ypos);
void display_set_font(PDISPLAYDATA display, PFONTDATA font);
void display_set_fg_color(PDISPLAYDATA display, uint32 color);
void display_set_bg_color(PDISPLAYDATA display, uint32 color);
void display_set_screen_buffer(PDISPLAYDATA display, uint16 *screen);

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rect(PDISPLAYDATA display, uint16 xpos, uint16 ypos, uint16 width, uint16 height);

//----------------------------------------------------------------------------------------------------------------------------------

void display_text(PDISPLAYDATA display, uint16 xpos, uint16 ypos, int8 *text);

//----------------------------------------------------------------------------------------------------------------------------------
//Variable width font handling functions

void draw_vw_character(PDISPLAYDATA display, uint16 character);

PFONTINFORMATION check_char_in_vw_font(PFONTINFORMATION info, uint16 character);

//----------------------------------------------------------------------------------------------------------------------------------
//Fixed width font handling functions

void draw_fw_character(PDISPLAYDATA display, uint16 character);
void render_fw_character(PDISPLAYDATA display, uint16 character);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* DISPLAY_LIB_H */
