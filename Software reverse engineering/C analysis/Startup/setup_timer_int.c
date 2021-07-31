void setup_timer_int(void)

{
  sys_init_timer();
  setup_some_interrupt(2,0xd);
  more_timer_setup(0);
  enable_interrupt(0x7f);  (change_status_reg_control_bits)
  return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------

void sys_init_timer(void)                                               //Timer is being setup, but not enabled
                                                                        //Timer is using OSC24M.
{
  uint in_r0; = 0x00   //Timer 0 is used here
  uint uVar1;
  int in_r1;  = 0x03E8
  int in_r2;  = 0x01
  
  write32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00),0);                  //0x01C20C10 = 0; TMR0_CTRL_REG


  uVar1 = read32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00));             //Read it back

  write32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00),uVar1);              //Write it with its own value

  uVar1 = read32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00));             //Read it again

  write32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00),uVar1);              //Write it again

  uVar1 = read32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00));             //Read it again

  write32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00),uVar1 | 4);          //Write it orred with 4       (Select OSC24M as source clock)

  uVar1 = read32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00));             //Read it again

  write32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c00),uVar1 | 2);          //Write it orred with 2


  write32((uint *)((in_r0 + 1) * 0x10 + 0x1c20c04),in_r1 * 0x18);       //Write TMR0_INTV_VALUE_REG = 0x18 * 0x03E8 = 24000d ==> 1ms interval

  if (in_r2 == 1)                                                       //Need interrupt?
  {
    uVar1 = read32(TIMER_BASE);                                         //Read TMR_IRQ_EN_REG
    write32(TIMER_BASE,uVar1 | 1 << (in_r0 & 0xff));                    //Enable the first bit since r0 = 0 (timer 0)
  }
  return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//This function is called three times with different parameters (timer 0, power signal, usb)

//r3 = 0x00          prio 0 == lowest
//r2 = 0x800281a4    vector for the interrupt???
//r1 = 0x0D          IRQ13   Timer 0
//r0 = 0x02          type 2

void setup_some_interrupt(uint p1,uint p2)

{
  undefined4 in_r2;
  int in_r3;
  uint *puVar1;
  
  if (*DAT_8001c678 == '\0')    //0x8019CE14. A byte is read from this address and if it is zero a 1 is written to it.
  {                             //Some sort of flag for the interrupt handler to see if it is setup??
    *DAT_8001c678 = '\x01';
  }

//Priority based system here?
  switch(p1)                    //Setup of some funciton pointers??? Vector table???
  {
          case 0:
            *(undefined4 *)(DAT_8001c67c + p2 * 4) = in_r2;    //0x8019CEBC base address
            break;

          case 1:
          case 2:
          case 3:
          case 4:
          case 5:
          case 6:
          case 7:
            *(undefined4 *)(DAT_8001c680 + p2 * 4) = in_r2;   //0x8019CE18 base address. For every IRQ there is a slot in the memory space
  }

  puVar1 = (uint *)(INTC_PRIO_REG0 + (p2 * 0x89 >> 0xb) * 4);                //p2 = 0x0D  (0x00 - 0x0F ==> prio_reg0, 0x10 - 0x1F ==> prio_reg1, etc)

  *puVar1 = *puVar1 | in_r3 << (((uint)((ulonglong)p2 * (ulonglong)DAT_8001c688 >> 0x23) * -0xf + p2) * 2 & 0xff);  //Set the priority (2 bits per interrupt)  0x88888889 >> 0x23

  //ptr = (uint *)(INTC_PRIO_REG0 + ((irq & 0x10) >> 2));
  //*ptr |= (prio & 0x03) << ((irq & 0x0F) << 1);



  puVar1 = (uint *)(INTC_EN_REG0 + (p2 >> 5) * 4);    //0x00 - 0x1F ==> en_reg0, 0x20 - 0x3F en_reg1
  *puVar1 = *puVar1 | 1 << (p2 & 0x1f);               //Enable the interrupt

  //ptr = (uint *)(INTC_EN_REG0 + (irq >> 5) * 4);
  //*ptr |= 1 << (irq & 0x1F);


  return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//Enable timer0
void more_timer_setup(uint p1)

{
  uint uVar1;
  
  uVar1 = read32((uint *)((p1 + 1) * 0x10 + 0x1c20c00));
  write32((uint *)((p1 + 1) * 0x10 + 0x1c20c00),uVar1 | 1);
  return;
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
//Global interrupt enable??
//Does things with the cpsr_c register

longlong FUN_80037424(uint param_1,uint param_2)

{
  bool bVar1;
  bool bVar2;
  bool bVar3;
  bool bVar4;
  byte in_Q;
  
  bVar3 = 0x7f < param_1;

  bVar4 = SBORROW4(param_1,0x80);

  bVar1 = (int)(param_1 - 0x80) < 0;

  bVar2 = param_1 == 0x80;


  if (bVar2)
  {
LAB_80037470:
    param_2 = (uint)(byte)(bVar1 << 4 | bVar2 << 3 | bVar3 << 2 | bVar4 << 1 | in_Q) << 0x1b;
  }
  else
  {
    if ((int)param_1 < 0x81)
    {
      bVar3 = 0x3e < param_1;
      bVar4 = SBORROW4(param_1,0x3f);
      bVar1 = (int)(param_1 - 0x3f) < 0;
      bVar2 = param_1 == 0x3f;

      if (!bVar2)
     {
        bVar3 = 0x3f < param_1;
        bVar4 = SBORROW4(param_1,0x40);
        bVar1 = (int)(param_1 - 0x40) < 0;
        bVar2 = param_1 == 0x40;
        if (bVar2) goto LAB_80037470;
        bVar3 = 0x7e < param_1;
        bVar4 = SBORROW4(param_1,0x7f);
        bVar1 = (int)(param_1 - 0x7f) < 0;
        bVar2 = param_1 == 0x7f;
        if (!bVar2) goto LAB_8003747c;
      }
    }
    else
    {
      bVar3 = 0xbe < param_1;
      bVar4 = SBORROW4(param_1,0xbf);
      bVar1 = (int)(param_1 - 0xbf) < 0;
      bVar2 = param_1 == 0xbf;

      if (!bVar2)
      {
        bVar3 = 0xbf < param_1;
        bVar4 = SBORROW4(param_1,0xc0);
        bVar1 = (int)(param_1 - 0xc0) < 0;
        bVar2 = param_1 == 0xc0;

        if (!bVar2)
          goto LAB_8003747c;

        goto LAB_80037470;
      }
    }

    param_2 = (uint)(byte)(bVar1 << 4 | bVar2 << 3 | bVar3 << 2 | bVar4 << 1 | in_Q) << 0x1b;
  }

LAB_8003747c:
  return (ulonglong)param_2 << 0x20;
}

