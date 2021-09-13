
int sd_card_check_switchable_function(int param_1,sd_cmd *param_2)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  sd_data local_30;
  
  uVar2 = DAT_80009ff8;     //0x00FFFF01
  pcVar1 = DAT_80009ff4;    //0x80736000

  local_30.blocks = 1;
  local_30.blocksize = 0x40;
  local_30.data = DAT_80009ff4;    //0x80736000
  local_30.flags = 1;

  param_2->cmdidx = 6;                  //Check switchable function command
  param_2->resp_type = 5;
  param_2->cmdarg = uVar2;
  iVar3 = sd_card_send_command(param_1,param_2,&local_30);

  uVar2 = DAT_80009ffc;   //0x80FFFF01

  if (iVar3 != 0)
  {
    return iVar3;
  }


  //Bytes are orred together
  if ((CONCAT11(*pcVar1,pcVar1[1]) != 0) && (CONCAT11(pcVar1[0x1c],pcVar1[0x1d]) == 0))
  {
    local_30.blocks = 1;
    local_30.blocksize = 0x40;
    local_30.data = pcVar1;
    local_30.flags = 1;

    param_2->cmdidx = 6;
    param_2->resp_type = 5;
    param_2->cmdarg = uVar2;
    iVar3 = sd_card_send_command(param_1,param_2,&local_30);

    if (iVar3 != 0)
    {
      return iVar3;
    }

    if (CONCAT11(*pcVar1,pcVar1[1]) != 0)
    {
      if (CONCAT11(pcVar1[0x1c],pcVar1[0x1d]) == 0)
      {
        uart_printf(s_switch_into_high_speed_mode_!!!_8000a000);
      }
      return 0;
    }
  }

  return 1;
}

