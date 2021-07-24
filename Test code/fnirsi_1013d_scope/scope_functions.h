//----------------------------------------------------------------------------------------------------------------------------------

#ifndef SCOPE_FUNCTIONS_H
#define SCOPE_FUNCTIONS_H

//----------------------------------------------------------------------------------------------------------------------------------

#define SCREEN_WIDTH    800
#define SCREEN_HEIGHT   480

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_display_lib(void);

void scope_setup_main_screen(void);
  
//----------------------------------------------------------------------------------------------------------------------------------

void scope_right_control_menu(void);

//----------------------------------------------------------------------------------------------------------------------------------
// Right side bar functions
//----------------------------------------------------------------------------------------------------------------------------------
  
void scope_control_button(int mode);
void scope_run_stop_button(int mode);
void scope_auto_set_button(int mode);
void scope_page_up_button(int mode);
void scope_page_down_button(int mode);
void scope_t_cursor_button(int mode);
void scope_v_cursor_button(int mode);
void scope_measures_button(int mode);
void scope_save_picture_button(int mode);
void scope_save_wave_button(int mode);
void scope_delete_wave_button(int mode);
void scope_50_percent_trigger_button(int mode);
void scope_show_grid_button(int mode);
void scope_ch1_sensitivity_control(int type,int mode);
void scope_ch2_sensitivity_control(int type,int mode);

//----------------------------------------------------------------------------------------------------------------------------------
// Top bar functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_menu_button(int mode);
void scope_main_return_button(int mode);
void scope_run_stop_text(int mode);
void scope_channel1_settings(int mode);
void scope_channel2_settings(int mode);
void scope_time_div_setting(void);
void scope_move_speed(int mode);
void scope_trigger_settings(int mode);
void scope_battery_status(void);

//----------------------------------------------------------------------------------------------------------------------------------
// Menu functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_main_menu(void);

void scope_open_channel1_menu(void);
void scope_channel1_enable_select(void);
void scope_channel1_fft_show(void);
void scope_channel1_coupling_select(void);
void scope_channel1_probe_magnification_select(void);

void scope_open_channel2_menu(void);
void scope_channel2_enable_select(void);
void scope_channel2_fft_show(void);
void scope_channel2_coupling_select(void);
void scope_channel2_probe_magnification_select(void);

void scope_open_trigger_menu(void);
void scope_trigger_mode_select(void);
void scope_trigger_edge_select(void);
void scope_trigger_channel_select(void);

//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------

#endif /* SCOPE_FUNCTIONS_H */
