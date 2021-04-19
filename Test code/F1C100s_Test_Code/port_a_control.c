#include "port_a_control.h"

void port_a_init(void)
{
  //Setup all port A pint for output
  *PORT_A_CFG_REG = (*PORT_A_CFG_REG & 0xFFFF0000) | 0x00001111;
}

void port_a_output(unsigned char data)
{
  *PORT_A_DATA_REG = (*PORT_A_DATA_REG & 0xFFFFFFF0) | (data & 0x0000000F);
}

