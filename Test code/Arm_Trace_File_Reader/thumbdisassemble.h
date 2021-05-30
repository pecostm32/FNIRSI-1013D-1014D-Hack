//----------------------------------------------------------------------------------------------------------------------------------

#ifndef THUMBDISASSEMBLE_H
#define THUMBDISASSEMBLE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include <sys/types.h>

//----------------------------------------------------------------------------------------------------------------------------------

typedef union  tagARM_THUMB_INSTRUCTION  ARM_THUMB_INSTRUCTION;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagARM_INSTR_THUMB_BASE   ARM_INSTR_THUMB_BASE;
typedef struct tagARM_INSTR_THUMB_SHIFT0 ARM_INSTR_THUMB_SHIFT0;
typedef struct tagARM_INSTR_THUMB_SHIFT2 ARM_INSTR_THUMB_SHIFT2;
typedef struct tagARM_INSTR_THUMB_DPI0   ARM_INSTR_THUMB_DPI0;
typedef struct tagARM_INSTR_THUMB_DPR0   ARM_INSTR_THUMB_DPR0;
typedef struct tagARM_INSTR_THUMB_DP1    ARM_INSTR_THUMB_DP1;
typedef struct tagARM_INSTR_THUMB_DP2    ARM_INSTR_THUMB_DP2;
typedef struct tagARM_INSTR_THUMB_DP2S   ARM_INSTR_THUMB_DP2S;
typedef struct tagARM_INSTR_THUMB_LS2I   ARM_INSTR_THUMB_LS2I;
typedef struct tagARM_INSTR_THUMB_LS2R   ARM_INSTR_THUMB_LS2R;
typedef struct tagARM_INSTR_THUMB_LS3    ARM_INSTR_THUMB_LS3;
typedef struct tagARM_INSTR_THUMB_LSM    ARM_INSTR_THUMB_LSM;
typedef struct tagARM_INSTR_THUMB_B2     ARM_INSTR_THUMB_B2;
typedef struct tagARM_INSTR_THUMB_B6     ARM_INSTR_THUMB_B6;
typedef struct tagARM_INSTR_THUMB_B7     ARM_INSTR_THUMB_B7;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARM_INSTR_THUMB_BASE
{
  u_int32_t data:6;       //Instruction data
  u_int32_t op2:5;        //Extended opcode
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_SHIFT0
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rm:3;         //Source register
  u_int32_t sa:5;         //5 bits shift amount
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_SHIFT2
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rs:3;         //Shift amount register
  u_int32_t op2:5;        //Extra opcode
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_DPI0
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t im:3;         //3 bits immediate data
  u_int32_t op2:2;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_DPR0
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t rm:3;         //Second source register
  u_int32_t op2:2;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_DP1
{
  u_int32_t im:8;         //Immediate data
  u_int32_t rd:3;         //Destination register
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_DP2
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rm:3;         //Source register
  u_int32_t op2:5;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_DP2S
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rm:4;         //Source register
  u_int32_t h:1;          //High bit of rd
  u_int32_t op2:3;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_LS2I
{
  u_int32_t im:8;         //Immediate data
  u_int32_t rd:3;         //Destination register
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_LS2R
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t rm:3;         //Second source register
  u_int32_t op2:2;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_LS3
{
  u_int32_t rd:3;         //Destination register
  u_int32_t rn:3;         //Source register
  u_int32_t im:5;         //5 bit immediate index
  u_int32_t l:1;          //Load / store bit
  u_int32_t b:1;          //byte / word bit
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_LSM
{
  u_int32_t rl:8;         //Register list
  u_int32_t rn:3;         //Base register
  u_int32_t l:1;          //Load / store bit
  u_int32_t nu:1;         //Not used
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_B2
{
  u_int32_t sbz:3;        //Should be zero
  u_int32_t rm:4;         //Register holding target address
  u_int32_t op2:4;        //Extra opcode for some type of instructions
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_B6
{
  u_int32_t im:8;         //signed immediate
  u_int32_t cond:4;       //Condition for execute
  u_int32_t op1:1;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

struct tagARM_INSTR_THUMB_B7
{
  u_int32_t im:11;        //signed immediate
  u_int32_t op1:2;        //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagARM_THUMB_INSTRUCTION
{
  u_int16_t              instr;       //Instruction register
  ARM_INSTR_THUMB_BASE   base;        //Base type for decoding
  ARM_INSTR_THUMB_SHIFT0 shift0;      //Instruction data for type 0 shift instructions
  ARM_INSTR_THUMB_SHIFT2 shift2;      //Instruction data for type 2 shift instructions
  ARM_INSTR_THUMB_DPI0   dpi0;        //Instruction data for type 0 immediate data processing instructions
  ARM_INSTR_THUMB_DPR0   dpr0;        //Instruction data for type 0 register data processing instructions
  ARM_INSTR_THUMB_DP1    dp1;         //Instruction data for type 1 data processing instructions
  ARM_INSTR_THUMB_DP2    dp2;         //Instruction data for type 2 data processing instructions
  ARM_INSTR_THUMB_DP2S   dp2s;        //Instruction data for type 2 special data processing instructions
  ARM_INSTR_THUMB_LS2I   ls2i;        //Instruction data for type 2 load store immediate indexed based instructions
  ARM_INSTR_THUMB_LS2R   ls2r;        //Instruction data for type 2 load store register based instructions
  ARM_INSTR_THUMB_LS3    ls3;         //Instruction data for type 3 load store instructions
  ARM_INSTR_THUMB_LSM    lsm;         //Instruction data for load store multiple instructions
  ARM_INSTR_THUMB_B2     b2;          //Instruction data for type 2 branch instructions
  ARM_INSTR_THUMB_B6     b6;          //Instruction data for type 6 branch instructions
  ARM_INSTR_THUMB_B7     b7;          //Instruction data for type 7 branch instructions
};

//----------------------------------------------------------------------------------------------------------------------------------
//Additional processing opcodes to allow for different flag handling

#define ARM_THUMB_TYPE_MASK           0x0000000F
#define ARM_OPCODE_THUMB_CLR_CV       0x00000010
#define ARM_OPCODE_THUMB_NO_FLAGS     0x00000020
#define ARM_OPCODE_THUMB_NEG          0x00000100
#define ARM_OPCODE_THUMB_MUL          0x00000200

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_THUMB_LOAD_FLAG           0x00010000

#define ARM_THUMB_SIGN_EXTEND         0x00100000

//----------------------------------------------------------------------------------------------------------------------------------

void ThumbDisassemble(char *instrstr, u_int32_t strsize, u_int32_t program_counter, ARM_THUMB_INSTRUCTION thumb_instruction);

void ThumbShiftImmediate(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbShiftRegister(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbShift(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr, u_int32_t type, char *op2);

void ThumbDP0(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbDP1(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbDP2(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbDP2S(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbDP(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr, u_int32_t type, u_int32_t rd, char *op2);

void ThumbLS2I(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbLS2R(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbLS3(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbLS4(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbLS(char *instrstr, u_int32_t type, u_int32_t rd, char *op2);

void ThumbPrintRegisterList(ARM_THUMB_INSTRUCTION thumb_instruction, char *ptr);
void ThumbLSMIA(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbPOP(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbPUSH(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);

void ThumbBranch2(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbBranch6(u_int32_t program_counter, ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);
void ThumbBranch7(u_int32_t program_counter, ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr);

//----------------------------------------------------------------------------------------------------------------------------------

#endif /* THUMBDISASSEMBLE_H */

