//----------------------------------------------------------------------------------------------------------------------------------

#ifndef DISPLAY_LIB_H
#define DISPLAY_LIB_H

//----------------------------------------------------------------------------------------------------------------------------------

#define DISPLAY_DRAW_CLOCK_WISE             0
#define DISPLAY_DRAW_COUNTER_CLOCK_WISE     1

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
  uint16     width;
  uint16     height;
};

//----------------------------------------------------------------------------------------------------------------------------------

void display_set_position(PDISPLAYDATA display, uint16 xpos, uint16 ypos);
void display_set_dimensions(PDISPLAYDATA display, uint16 width, uint16 height);
void display_set_font(PDISPLAYDATA display, PFONTDATA font);
void display_set_fg_color(PDISPLAYDATA display, uint32 color);
void display_set_bg_color(PDISPLAYDATA display, uint32 color);
void display_set_screen_buffer(PDISPLAYDATA display, uint16 *screen);

//----------------------------------------------------------------------------------------------------------------------------------

void display_draw_line(PDISPLAYDATA display, uint16 xstart, uint16 ystart, uint16 xend, uint16 yend);
void display_draw_horz_line(PDISPLAYDATA display, uint16 ypos, uint16 xstart, uint16 xend);
void display_draw_vert_line(PDISPLAYDATA display, uint16 xpos, uint16 ystart, uint16 yend);
void display_draw_rect(PDISPLAYDATA display, uint16 xpos, uint16 ypos, uint16 width, uint16 height);
void display_draw_rounded_rect(PDISPLAYDATA display, uint16 xpos, uint16 ypos, uint16 width, uint16 height, uint16 radius);
void display_draw_arc(PDISPLAYDATA display, uint16 xpos, uint16 ypos, uint16 radius, uint16 startangle, uint16 endangle, uint16 direction);

//----------------------------------------------------------------------------------------------------------------------------------

void display_fill_rect(PDISPLAYDATA display, uint16 xpos, uint16 ypos, uint16 width, uint16 height);
void display_fill_rounded_rect(PDISPLAYDATA display, uint16 xpos, uint16 ypos, uint16 width, uint16 height, uint16 radius);

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
