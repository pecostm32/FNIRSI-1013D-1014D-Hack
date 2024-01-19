#ifndef PORT_A_CONTROL_H
#define PORT_A_CONTROL_H

//Port A registers
#define PORT_A_CFG_REG          ((volatile unsigned int *)(0x01C20800))
#define PORT_A_DATA_REG         ((volatile unsigned int *)(0x01C20810))


void toggle_port_a(void);

void port_a_init(void);

void port_a_output(unsigned char data);


#endif /* PORT_A_CONTROL_H */

