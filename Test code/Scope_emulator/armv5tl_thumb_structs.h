//----------------------------------------------------------------------------------------------------------------------------------

#ifndef ARMV5TL_THUMB_STRCUTS_H
#define ARMV5TL_THUMB_STRCUTS_H

#include <stdint.h>

//----------------------------------------------------------------------------------------------------------------------------------

typedef union  tagARMV5TL_THUMB_INSTRUCTION  ARMV5TL_THUMB_INSTRUCTION;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagARMV5TL_INSTR_THUMB_BASE   ARMV5TL_INSTR_THUMB_BASE;
typedef struct tagARMV5TL_INSTR_THUMB_SHIFT0 ARMV5TL_INSTR_THUMB_SHIFT0;
typedef struct tagARMV5TL_INSTR_THUMB_SHIFT2 ARMV5TL_INSTR_THUMB_SHIFT2;
typedef struct tagARMV5TL_INSTR_THUMB_DPI0   ARMV5TL_INSTR_THUMB_DPI0;
typedef struct tagARMV5TL_INSTR_THUMB_DPR0   ARMV5TL_INSTR_THUMB_DPR0;
typedef struct tagARMV5TL_INSTR_THUMB_DP1    ARMV5TL_INSTR_THUMB_DP1;
typedef struct tagARMV5TL_INSTR_THUMB_DP2    ARMV5TL_INSTR_THUMB_DP2;
typedef struct tagARMV5TL_INSTR_THUMB_DP2S   ARMV5TL_INSTR_THUMB_DP2S;
typedef struct tagARMV5TL_INSTR_THUMB_LS2I   ARMV5TL_INSTR_THUMB_LS2I;
typedef struct tagARMV5TL_INSTR_THUMB_LS2R   ARMV5TL_INSTR_THUMB_LS2R;
typedef struct tagARMV5TL_INSTR_THUMB_LS3    ARMV5TL_INSTR_THUMB_LS3;
typedef struct tagARMV5TL_INSTR_THUMB_LSM    ARMV5TL_INSTR_THUMB_LSM;
typedef struct tagARMV5TL_INSTR_THUMB_B2     ARMV5TL_INSTR_THUMB_B2;
typedef struct tagARMV5TL_INSTR_THUMB_B6     ARMV5TL_INSTR_THUMB_B6;
typedef struct tagARMV5TL_INSTR_THUMB_B7     ARMV5TL_INSTR_THUMB_B7;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARMV5TL_INSTR_THUMB_BASE
{
  uint32_t data:6;        //Instruction data
  uint32_t op2:5;         //Extended opcode
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_SHIFT0
{
  uint32_t rd:3;          //Destination register
  uint32_t rm:3;          //Source register
  uint32_t sa:5;          //5 bits shift amount
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_SHIFT2
{
  uint32_t rd:3;          //Destination register
  uint32_t rs:3;          //Shift amount register
  uint32_t op2:5;         //Extra opcode
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DPI0
{
  uint32_t rd:3;          //Destination register
  uint32_t rn:3;          //Source register
  uint32_t im:3;          //3 bits immediate data
  uint32_t op2:2;         //Extra opcode for some type of instructions
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DPR0
{
  uint32_t rd:3;          //Destination register
  uint32_t rn:3;          //Source register
  uint32_t rm:3;          //Second source register
  uint32_t op2:2;         //Extra opcode for some type of instructions
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DP1
{
  uint32_t im:8;          //Immediate data
  uint32_t rd:3;          //Destination register
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DP2
{
  uint32_t rd:3;          //Destination register
  uint32_t rm:3;          //Source register
  uint32_t op2:5;         //Extra opcode for some type of instructions
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DP2S
{
  uint32_t rd:3;          //Destination register
  uint32_t rm:4;          //Source register
  uint32_t h:1;           //High bit of rd
  uint32_t op2:3;         //Extra opcode for some type of instructions
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LS2I
{
  uint32_t im:8;          //Immediate data
  uint32_t rd:3;          //Destination register
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LS2R
{
  uint32_t rd:3;          //Destination register
  uint32_t rn:3;          //Source register
  uint32_t rm:3;          //Second source register
  uint32_t op2:2;         //Extra opcode for some type of instructions
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LS3
{
  uint32_t rd:3;          //Destination register
  uint32_t rn:3;          //Source register
  uint32_t im:5;          //5 bit immediate index
  uint32_t l:1;           //Load / store bit
  uint32_t b:1;           //byte / word bit
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LSM
{
  uint32_t rl:8;          //Register list
  uint32_t rn:3;          //Base register
  uint32_t l:1;           //Load / store bit
  uint32_t nu:1;          //Not used
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_B2
{
  uint32_t sbz:3;         //Should be zero
  uint32_t rm:4;          //Register holding target address
  uint32_t op2:4;         //Extra opcode for some type of instructions
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_B6
{
  uint32_t im:8;          //signed immediate
  uint32_t cond:4;        //Condition for execute
  uint32_t op1:1;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_B7
{
  uint32_t im:11;         //signed immediate
  uint32_t op1:2;         //Actual opcode for some type of instructions
  uint32_t type:3;        //Type of instructions
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagARMV5TL_THUMB_INSTRUCTION
{
  uint16_t                   instr;       //Instruction register
  ARMV5TL_INSTR_THUMB_BASE   base;        //Base type for decoding
  ARMV5TL_INSTR_THUMB_SHIFT0 shift0;      //Instruction data for type 0 shift instructions
  ARMV5TL_INSTR_THUMB_SHIFT2 shift2;      //Instruction data for type 2 shift instructions
  ARMV5TL_INSTR_THUMB_DPI0   dpi0;        //Instruction data for type 0 immediate data processing instructions
  ARMV5TL_INSTR_THUMB_DPR0   dpr0;        //Instruction data for type 0 register data processing instructions
  ARMV5TL_INSTR_THUMB_DP1    dp1;         //Instruction data for type 1 data processing instructions
  ARMV5TL_INSTR_THUMB_DP2    dp2;         //Instruction data for type 2 data processing instructions
  ARMV5TL_INSTR_THUMB_DP2S   dp2s;        //Instruction data for type 2 special data processing instructions
  ARMV5TL_INSTR_THUMB_LS2I   ls2i;        //Instruction data for type 2 load store immediate indexed based instructions
  ARMV5TL_INSTR_THUMB_LS2R   ls2r;        //Instruction data for type 2 load store register based instructions
  ARMV5TL_INSTR_THUMB_LS3    ls3;         //Instruction data for type 3 load store instructions
  ARMV5TL_INSTR_THUMB_LSM    lsm;         //Instruction data for load store multiple instructions
  ARMV5TL_INSTR_THUMB_B2     b2;          //Instruction data for type 2 branch instructions
  ARMV5TL_INSTR_THUMB_B6     b6;          //Instruction data for type 6 branch instructions
  ARMV5TL_INSTR_THUMB_B7     b7;          //Instruction data for type 7 branch instructions
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* ARMV5TL_THUMB_STRCUTS_H */

