
//Load another file for the picture and waveform handling
void load_selected_system_file(void)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  undefined auStack568 [556];
  
  puVar1 = PTR_DAT_8002c8b8;   //0x80192ee2  view type. 0 is picture 1 is waveform

  if (*PTR_DAT_8002c8b8 == '\0')
  {
    iVar3 = f_open(auStack568,s__pic_system_sys_8002c8d4,1);
  }
  else
  {
    iVar3 = f_open(auStack568,s__wave_system_sys_8002c8bc,1);
  }

  iVar2 = DAT_8002c8d0;    //0x8035A97E

  if (iVar3 == 4)
  {
    f_close(auStack568);

    if (*puVar1 == '\0')
    {
      f_open(auStack568,s__pic_system_sys_8002c8d4,7);
      f_stat();
    }
    else
    {
      f_open(auStack568,s__wave_system_sys_8002c8bc,7);
      f_stat();
    }

    f_stat();

    memclear(iVar2 + 0x1e,2000);

    f_lseek(auStack568,0);

    f_write(auStack568,(void *)(iVar2 + 0x1e),2000,(uint *)0x0);
  }

  f_lseek(auStack568,0);

  f_read(auStack568,(void *)(iVar2 + 0x1e),2000,(uint *)0x0);

  f_close(auStack568);

  return;
}

