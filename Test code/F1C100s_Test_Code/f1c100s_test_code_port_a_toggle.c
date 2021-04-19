#include "port_a_control.h"

int main(void)
{
  int i;
  
  port_a_init();
  
  for(i=0;i<100;i++);
  
  while(1)
  {
    port_a_output(0x00);
    
    for(i=0;i<100;i++);
    
    port_a_output(0x0F);
    
    for(i=0;i<100;i++);
  }
}