//----------------------------------------------------------------------------------------------------------------------------------

#ifndef SCOPE_FUNCTIONS_H
#define SCOPE_FUNCTIONS_H

//----------------------------------------------------------------------------------------------------------------------------------

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

//----------------------------------------------------------------------------------------------------------------------------------

void setup_display_lib(void);

void setup_main_screen(void);
  
//----------------------------------------------------------------------------------------------------------------------------------

void display_right_control_menu(void);

//----------------------------------------------------------------------------------------------------------------------------------
// Right side bar functions
//----------------------------------------------------------------------------------------------------------------------------------
  
void display_control_button(int mode);
void display_run_stop_button(int mode);
void display_auto_set_button(int mode);
void display_page_up_button(int mode);
void display_page_down_button(int mode);
void display_t_cursor_button(int mode);
void display_v_cursor_button(int mode);
void display_measures_button(int mode);
void display_save_picture_button(int mode);
void display_save_wave_button(int mode);
void display_delete_wave_button(int mode);
void display_50_percent_trigger_button(int mode);
void display_show_grid_button(int mode);
void display_ch1_sensitivity_control(int type,int mode);
void display_ch2_sensitivity_control(int type,int mode);

//----------------------------------------------------------------------------------------------------------------------------------
// Top bar function
//----------------------------------------------------------------------------------------------------------------------------------

void display_menu_button(int mode);
void display_main_return_button(int mode);
void display_run_stop_text(int mode);
void display_channel1_settings(int mode);
void display_channel2_settings(int mode);
void display_time_div_setting(void);
void display_move_speed(int mode);
void display_trigger_settings(int mode);
void display_battery_status(void);

//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------

#endif /* SCOPE_FUNCTIONS_H */
