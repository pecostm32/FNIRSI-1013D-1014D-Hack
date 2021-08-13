//----------------------------------------------------------------------------------------------------------------------------------

#ifndef STATEMACHINE_H
#define STATEMACHINE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

void touch_handler(void);

void scan_for_touch(void);

void handle_main_menu_touch(void);
void handle_channel1_menu_touch(void);
void handle_channel2_menu_touch(void);
void handle_trigger_menu_touch(void);

void handle_right_basic_menu_touch(void);
void handle_right_volts_div_menu_touch(void);

void handle_measures_menu_touch(void);

void close_open_sub_menus(void);

//----------------------------------------------------------------------------------------------------------------------------------

void move_trigger_point_position(void);

void change_channel_1_x_offset(void);
void change_channel_1_y_offset(void);
void change_channel_2_y_offset(void);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* STATEMACHINE_H */

