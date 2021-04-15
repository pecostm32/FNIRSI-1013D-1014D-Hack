//param_1  ==  Some register base address

//Called with 0x01C20800, 3, 1, 0 (Parameter mis match???)

//Function to set the pin configuration of port pins
//First parameter is the base address of the register
//Second is the pin number
//Third is a flag to tell what to do. 0 ==> set as input, 1 ==> set as output


//Four bits per pin for configuring its use (only 3 bits actualy used)

//Pin 0:
//bits 3:0      0x0000000F

//Pin 1:
//bits 7:4      0x000000F0

//Pin 2:
//bits 11:8     0x00000F00

//Pin 3:
//bits 15:12    0x0000F000

//Eight pins per register
//4 bits per pin

void FUN_8001764c(int param_1, uint param_2, uint param_3)
{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  uVar1 = param_2 >> 3;                   //uVar1 = 0 (Pin number divided by eight)
  uVar2 = (param_2 << 0x1d) >> 0x1b;
  bVar3 = param_3 == 0;

  //Clear the configuration bits for the given pin in the configuration register
  *(uint *)(param_1 + uVar1 * 4) = *(uint *)(param_1 + uVar1 * 4) & ~(0xf << uVar2);  //basreg[(pin >> 3) * 4] &= ~(0x0F << ((pin & 0x07) << 2))

  if(bVar3)         //If param_3 is 0 on entry do this
  {
    param_3 = *(uint *)(param_1 + uVar1 * 4); //Read from the register again
    param_3 = param_3 & ~(1 << uVar2);        //Only clearing the one bit for returning to input mode. Not really needed since already cleared above
  }
  else
  {
    if (param_3 == 1)
    {
      *(uint *)(param_1 + uVar1 * 4) = *(uint *)(param_1 + uVar1 * 4) | 1 << uVar2;  //Setting one bit for making it output mode
      return;
    }

    //Setting the given configuration to param_3
    param_3 = param_3 << uVar2 | *(uint *)(param_1 + uVar1 * 4);

  }

  //Write the modified configuration
  *(uint *)(param_1 + uVar1 * 4) = param_3;

  return;
}



