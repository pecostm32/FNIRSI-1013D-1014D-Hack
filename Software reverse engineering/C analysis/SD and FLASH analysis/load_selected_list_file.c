//Load list file for either pictures or waveforms

void load_selected_list_file(void)

{
  undefined *puVar1;
  uint count;
  int iVar2;
  undefined auStack568 [556];
  
  puVar1 = PTR_DAT_8001be98;   //0x80192ee2

  if(*PTR_DAT_8001be98 == '\0')
  {
    iVar2 = f_open(auStack568,s__piclist_sys_8001beb0,1);   //Open file for reading
  }
  else
  {
    iVar2 = f_open(auStack568,s__wavelist_sys_8001be9c,1);
  }

  count = DAT_8001beac;  //0x00061A80  = 400000 bytes

  //Check on file not found
  if(iVar2 == 4)
  {
    f_close(auStack568);  //Not needed since file was not opened!!!!!

    if (*puVar1 == '\0')
    {
      f_open(auStack568,s__piclist_sys_8001beb0,7);   //Create file for reading and writing
      f_stat();  //f_stat
    }
    else
    {
      f_open(auStack568,s__wavelist_sys_8001be9c,7);
      f_stat();
    }

    f_stat();

    memclear((uint)DAT_8001bec0,count);    //0x802F19CE

    f_lseek(auStack568,0);

    f_write(auStack568,DAT_8001bec0,count,(uint *)0x0);
  }

  f_lseek(auStack568,0);

  f_read(auStack568,DAT_8001bec0,count,(uint *)0x0);

  f_close(auStack568);
  return;
}

