//----------------------------------------------------------------------------------------------------------------------------------

#ifndef SCOPE_FUNCTIONS_H
#define SCOPE_FUNCTIONS_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "fnirsi_1013d_scope.h"
#include "variables.h"

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_display_lib(void);

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_main_screen(void);

void scope_setup_view_screen(void);

void scope_setup_usb_screen(void);

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_right_control_menu(void);

void scope_setup_right_file_menu(void);

//----------------------------------------------------------------------------------------------------------------------------------

void scope_setup_bottom_file_menu(int mode);

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
void scope_ch1_sensitivity_control(int type, int mode);
void scope_ch2_sensitivity_control(int type, int mode);

void scope_select_all_button(int mode);
void scope_select_button(int mode);

//----------------------------------------------------------------------------------------------------------------------------------
// Top bar functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_menu_button(int mode);
void scope_main_return_button(int mode);
void scope_run_stop_text(void);
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
void scope_main_menu_system_settings(int mode);
void scope_main_menu_picture_view(int mode);
void scope_main_menu_waveform_view(int mode);
void scope_main_menu_usb_connection(int mode);

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

void scope_open_system_settings_menu(void);    //Add notification confirmation option!!
void scope_system_settings_screen_brightness_item(int mode);
void scope_system_settings_screen_brightness_value(void);
void scope_system_settings_grid_brightness_item(int mode);
void scope_system_settings_grid_brightness_value(void);
void scope_system_settings_trigger_50_item(void);
void scope_system_settings_calibration_item(int mode);
void scope_system_settings_x_y_mode_item(void);
void scope_system_settings_confirmation_item(void);

void scope_open_calibration_start_text(void);
void scope_show_calibrating_text(void);
void scope_show_calibration_done_text(void);

void scope_open_measures_menu(void);
void scope_measures_menu_item(int channel, int item);

//----------------------------------------------------------------------------------------------------------------------------------

void scope_open_slider(uint16 xpos, uint16 ypos, uint8 position);
void scope_display_slider(uint16 xpos, uint16 ypos, uint8 position);
int scope_move_slider(uint16 xpos, uint16 ypos, uint8 *position);

void scope_display_slide_button(uint16 xpos, uint16 ypos, uint8 state);

void scope_display_ok_button(uint16 xpos, uint16 ypos, uint8 mode);

//----------------------------------------------------------------------------------------------------------------------------------

void scope_adjust_timebase(void);

//----------------------------------------------------------------------------------------------------------------------------------
// Grid and cursor functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_draw_grid(void);
void scope_draw_pointers(void);
void scope_draw_time_cursors(void);
void scope_draw_volt_cursors(void);

//----------------------------------------------------------------------------------------------------------------------------------
// Signal data processing functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_process_trace_data(void);

void scope_get_long_timebase_data(void);

void scope_get_short_timebase_data(void);

void scope_adjust_data(uint16 *destination, uint16 *source, uint32 count, uint8 voltperdiv);
void scope_offset_data(uint16 *buffer, uint32 count, uint32 offset);
void scope_limit_data(uint16 *buffer, uint32 count);
void scope_filter_data(uint16 *buffer, uint32 count);
void scope_double_data(uint16 *buffer, uint32 count);


uint32 scope_process_trigger(void);

void scope_up_sample_x_2(uint16 *buffer, uint32 count);
void scope_up_sample_x_2_5(uint16 *buffer, uint32 count);
void scope_up_sample_x_4(uint16 *buffer, uint32 count);
void scope_up_sample_x_5(uint16 *buffer, uint32 count);
void scope_up_sample_x_10(uint16 *buffer, uint32 count);
void scope_up_sample_x_25(uint16 *buffer, uint32 count);

void scope_interleave_samples(uint16 *buffer1, uint16 *buffer2, PADC2CALIBRATIONDATA calibration);   //scope_pre_process_ch1_25ns_data

void scope_calculate_min_max_avg(uint16 *buffer, PMEASUREMENTS measurements);
void scope_evaluate_trace_data(uint16 *buffer, PMEASUREMENTS measurements, uint32 voltperdiv, uint32 screenoffset);

void scope_determine_sample_buffer_indexes(void);

uint32 scope_do_baseline_calibration(void);
uint32 scope_do_trace_offset_calibration(void);
uint32 scope_do_adc1_adc2_difference_calibration(void);

void scope_do_50_percent_trigger_setup(void);

void scope_do_auto_setup(void);

//----------------------------------------------------------------------------------------------------------------------------------
// Signal data display functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_display_trace_data(void);          //Needs work on long time base to fix problem when enabling a channel. previous y position is then wrong.

void scope_display_channel_trace(uint16 *buffer, uint16 xpos, uint16 count, uint32 color);

void scope_display_cursor_measurements(void);

void scope_display_measurements(void);

void scope_print_value(char *buffer, uint32 value, uint32 scale, char *header, char *sign);

char *scope_print_decimal(char *buffer, uint32 value, uint32 decimalplace);

//----------------------------------------------------------------------------------------------------------------------------------
// File display functions
//----------------------------------------------------------------------------------------------------------------------------------

//These two functions are for save guarding the operational settings when switched to a view mode
//This differs from the original code where they save more data and prepare it for writing to file
void scope_save_setup(PSCOPESETTINGS settings);
void scope_restore_setup(PSCOPESETTINGS settings);

//These two functions are for the system settings, preparing for and restoring from file
void scope_prepare_setup_for_file(void);
void scope_restore_setup_from_file(void);

void scope_print_file_name(uint32 filenumber);

void scope_load_list_files(void);                      //Add error handling!!
void scope_save_list_files(void);                      //Add error handling!!

void scope_save_view_item_file(int32 type);

void scope_remove_item_from_lists(uint32 delete);

int32 scope_load_trace_data(void);                     //Need to finish this one. Trace data displaying!!!

void scope_sync_list_files(void);

void scope_count_and_display_thumbnails(void);

void scope_display_thumbnails(void);                   //Add displaying the file number or name to this function

void scope_display_thumbnail_data(uint32 xpos, uint32 ypos, PTHUMBNAILDATA thumbnaildata, uint32 channel);

void scope_create_thumbnail(uint32 filenumber, PTHUMBNAILDATA thumbnaildata);

int32 scope_display_picture_item(void);

void scope_display_selected_signs(void);

void scope_display_file_status_message(int32 msgid, int32 alwayswait);

//----------------------------------------------------------------------------------------------------------------------------------
// Configuration data functions
//----------------------------------------------------------------------------------------------------------------------------------

void scope_load_configuration_data(void);
void scope_save_configuration_data(void);

void scope_reset_config_data(void);
void scope_save_config_data(void);
void scope_restore_config_data(void);

//----------------------------------------------------------------------------------------------------------------------------------

#ifndef USE_TP_CONFIG
void save_tp_config(void);
#endif

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* SCOPE_FUNCTIONS_H */
