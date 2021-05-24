//----------------------------------------------------------------------------------------------------------------------------------

#ifndef ARMV5TL_H
#define ARMV5TL_H

//----------------------------------------------------------------------------------------------------------------------------------

#include <sys/types.h>

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagARMV5TL_REGS              ARMV5TL_REGS;
typedef struct tagARMV5TL_TRACE_ENTRY       ARMV5TL_TRACE_ENTRY;

//----------------------------------------------------------------------------------------------------------------------------------
//The complete arm register set
struct tagARMV5TL_REGS
{
  u_int32_t r0;
  u_int32_t r1;
  u_int32_t r2;
  u_int32_t r3;
  u_int32_t r4;
  u_int32_t r5;
  u_int32_t r6;
  u_int32_t r7;
  u_int32_t r8[2];
  u_int32_t r9[2];
  u_int32_t r10[2];
  u_int32_t r11[2];
  u_int32_t r12[2];
  u_int32_t r13[6];
  u_int32_t r14[6];
  u_int32_t r15;
  u_int32_t cpsr;
  u_int32_t spsr[5];
};

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARMV5TL_TRACE_ENTRY
{
  u_int32_t    instruction_address;    //Address of the traced instruction
  u_int32_t    instruction_word;       //Instruction word for arm, half word for thumb
  u_int32_t    execution_status;       //Information about if the arm instruction has been executed or not
  ARMV5TL_REGS registers;              //The 37 registers
  u_int32_t    memory_address;         //Depending on the type of instruction this is set with the targeted memory address
  u_int32_t    memory_direction;       //For load or store multiple instructions this signals if the given address is incremented or decremented
  u_int32_t    data_width;             //For instructions that load or store half words or bytes this will reflect this, otherwise word width
  u_int32_t    data_count;             //The number of words read or written by the instruction
  u_int32_t    data[16];               //The data read or written. Single instruction can do a max of 16 words
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* ARMV5TL_H */

