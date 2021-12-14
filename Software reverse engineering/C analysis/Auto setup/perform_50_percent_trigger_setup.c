//--------------------------------------------------------------------------------

void perform_50_percent_trigger_setup(void)

{
  byte bVar1;
  uint *port;
  char *pcVar2;
  int iVar3;
  undefined2 uVar4;
  int iVar5;
  uint uVar6;
  ushort *puVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  bool bVar11;
  bool bVar12;
  bool bVar13;
  
  pcVar2 = DAT_800294ac;     //Settings base

  if ((*DAT_800294ac == '\0') || (DAT_800294ac[0xc] != '\0'))
  {
    if ((DAT_800294ac[0xc] != '\0') && (*DAT_800294ac == '\0'))  //Channel 2 is on and channel 1 is off
    {
      DAT_800294ac[0x23] = '\x01';
      display_trigger_settings(0);

      fpga_write_cmd('\x15');          //Select trigger channel
      fpga_write_data(pcVar2[0x23]);
    }
  }
  else
  {
    DAT_800294ac[0x23] = '\0';
    display_trigger_settings(0);
    fpga_write_cmd('\x15');
    fpga_write_data(pcVar2[0x23]);
  }


  iVar3 = DAT_800294b4;
  iVar8 = DAT_800294b0;
  uVar9 = 0;

  //Get a range of samples on varying sample intervals
  do
  {
    iVar5 = (uVar9 * 0x14 & 0xffe0ffff) - 1;

    //Same delay setup as for auto set
    do
    {
      bVar13 = SCARRY4(iVar5,1);
      bVar11 = iVar5 + 1 < 0;
      bVar12 = iVar5 != -1;
      if (bVar12 && bVar11 == bVar13)
      {
        iVar5 = iVar5 + -1;
      }
    } while (bVar12 && bVar11 == bVar13);

    uVar4 = get_channel_1_avg_sample(1);

    *(undefined2 *)(iVar8 + uVar9 * 2) = uVar4;

    uVar4 = get_channel_2_avg_sample(1);

    iVar5 = uVar9 * 2;
    uVar9 = uVar9 + 1 & 0xfffeffff;
    *(undefined2 *)(iVar3 + iVar5) = uVar4;
  } while (uVar9 < 1000);


  uVar10 = DAT_800294b8;  //0x0000FFFF

  if (pcVar2[0x23] == '\0')   //Check if trigger set on channel 1
  {
    calib_adjust_channel_1_samples();
    calib_copy_ch1_buf3_to_buf4();
    double_channel1_samples();
    calib_ch1_limit_samples_on_401();

    uVar9 = 0;
    iVar8 = 1000;
    puVar7 = DAT_800294c0;

    //Loop through the samples to get a min and max???
    do
    {
      uVar6 = (uint)*puVar7;
      puVar7 = puVar7 + 1;

      if (uVar9 < uVar6)
      {
        uVar9 = uVar6;
      }

      if (uVar6 < uVar10)
      {
        uVar10 = uVar6;
      }

      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);

    *(short *)(pcVar2 + 0x26) = (short)(uVar9 + uVar10 >> 1);  //Trigger level on screen  (min + max) / 2 ????
  }
  else
  {
    //Use channel 2 data
    calib_adjust_channel_2_samples();
    calib_copy_ch2_buf3_to_buf4();
    double_channel2_samples();
    calib_ch2_limit_samples_on_401();

    uVar9 = 0;
    iVar8 = 1000;
    puVar7 = DAT_800294bc;

    do
    {
      uVar6 = (uint)*puVar7;
      puVar7 = puVar7 + 1;

      if (uVar9 < uVar6)
      {
        uVar9 = uVar6;
      }

      if (uVar6 < uVar10)
      {
        uVar10 = uVar6;
      }

      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);

    *(short *)(pcVar2 + 0x26) = (short)(uVar9 + uVar10 >> 1);
  }

  calculate_trigger_level();

  fpga_write_cmd('\x17');
  fpga_write_data(pcVar2[0x28]);   //Trigger level
}

//--------------------------------------------------------------------------------
