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

void handle_view_mode_touch(void);       //need to finish this function (delete and return from item view) Check the comments!!

void handle_picture_view_touch(void);    //Need to finish this function (delete, previous and next item)

int32 handle_confirm_delete(void);       //See if different font needed for yes and no, or even the confirm text. Check on positions!!!!

//----------------------------------------------------------------------------------------------------------------------------------

void close_open_sub_menus(void);

//----------------------------------------------------------------------------------------------------------------------------------

void move_trigger_point_position(void);

void change_channel_1_offset(void);
void change_channel_2_offset(void);

void change_trigger_level_offset(void);

void move_left_time_cursor_position(void);
void move_right_time_cursor_position(void);

void move_top_volt_cursor_position(void);
void move_bottom_volt_cursor_position(void);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* STATEMACHINE_H */

