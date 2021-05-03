void copy_frame_to_screen(void)

{
  copy_byte(Start_Of_Screen_Mem,Screen_Frame_Buffer,number_of_pixels << 1);
  return;
}

