//----------------------------------------------------------------------------------------------------------------------------------

#ifndef ARMV5TL_THUMB_STRCUTS_H
#define ARMV5TL_THUMB_STRCUTS_H

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
  u_int32_t data:6;       //Instruction data
  u_int32_t op2:5;        //Extended opcode
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_SHIFT0
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rm:3;         //Source register
  u_int32_t sa:5;         //5 bits shift amount
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_SHIFT2
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rs:3;         //Shift amount register
  u_int32_t op2:5;        //Extra opcode
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DPI0
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t im:3;         //3 bits immediate data
  u_int32_t op2:2;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DPR0
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t rm:3;         //Second source register
  u_int32_t op2:2;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DP1
{
  u_int32_t im:8;         //Immediate data
  u_int32_t rd:3;         //Destination register
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DP2
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rm:3;         //Source register
  u_int32_t op2:5;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_DP2S
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rm:4;         //Source register
  u_int32_t h:1;          //High bit of rd
  u_int32_t op2:3;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LS2I
{
  u_int32_t im:8;         //Immediate data
  u_int32_t rd:3;         //Destination register
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LS2R
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t rm:3;         //Second source register
  u_int32_t op2:2;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LS3
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t im:5;         //5 bit immediate index
  u_int32_t l:1;          //Load / store bit
  u_int32_t b:1;          //byte / word bit
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_LSM
{
  u_int32_t rl:8;         //Register list
  u_int32_t rn:3;         //Base register
  u_int32_t l:1;          //Load / store bit
  u_int32_t nu:1;         //Not used
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_B2
{
  u_int32_t sbz:3;        //Should be zero
  u_int32_t rm:4;         //Register holding target address
  u_int32_t op2:4;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_B6
{
  u_int32_t im:8;         //signed immediate
  u_int32_t cond:4;       //Condition for execute
  u_int32_t op1:1;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARMV5TL_INSTR_THUMB_B7
{
  u_int32_t im:11;        //signed immediate
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagARMV5TL_THUMB_INSTRUCTION
{
  u_int16_t                  instr;       //Instruction register
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
  ARMV5TL_INSTR_THUMB_B6     b7;          //Instruction data for type 7 branch instructions
};

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* ARMV5TL_THUMB_STRCUTS_H */

