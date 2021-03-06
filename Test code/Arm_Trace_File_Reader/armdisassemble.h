//----------------------------------------------------------------------------------------------------------------------------------

#ifndef ARMDISASSEMBLE_H
#define ARMDISASSEMBLE_H

//----------------------------------------------------------------------------------------------------------------------------------

#include <sys/types.h>

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagARM_ADDRESS_MAP       ARM_ADDRESS_MAP;
typedef struct tagARM_INSTR_BASE        ARM_INSTR_BASE;
typedef struct tagARM_INSTR_MISC0       ARM_INSTR_MISC0;     //Miscellaneous instructions
typedef struct tagARM_INSTR_TYPE0       ARM_INSTR_TYPE0;
typedef struct tagARM_INSTR_TYPE1       ARM_INSTR_TYPE1;
typedef struct tagARM_INSTR_TYPE2       ARM_INSTR_TYPE2;
typedef struct tagARM_INSTR_TYPE3       ARM_INSTR_TYPE3;
typedef struct tagARM_INSTR_TYPE4       ARM_INSTR_TYPE4;
typedef struct tagARM_INSTR_TYPE5       ARM_INSTR_TYPE5;
typedef struct tagARM_INSTR_TYPE6       ARM_INSTR_TYPE6;
typedef struct tagARM_INSTR_TYPE7       ARM_INSTR_TYPE7;
typedef struct tagARM_INSTR_MUL         ARM_INSTR_MUL;        //Multiply instructions
typedef struct tagARM_INSTR_SMULXY      ARM_INSTR_SMULXY;     //Signed multiply
typedef struct tagARM_INSTR_ELS         ARM_INSTR_ELS;        //Extra load and store instructions
typedef struct tagARM_INSTR_DPSI        ARM_INSTR_DPSI;       //Data processing shift immediate instructions
typedef struct tagARM_INSTR_DPSR        ARM_INSTR_DPSR;       //Data processing shift register instructions
typedef struct tagARM_INSTR_DPI         ARM_INSTR_DPI;        //Data processing immediate instructions
typedef struct tagARM_INSTR_LSI         ARM_INSTR_LSI;        //Load and store immediate instructions
typedef struct tagARM_INSTR_LSR         ARM_INSTR_LSR;        //Load and store register instructions
typedef struct tagARM_INSTR_LSRN        ARM_INSTR_LSRN;       //Load and store register no scaling instructions
typedef struct tagARM_INSTR_LSX         ARM_INSTR_LSX;        //Load and store register extra instructions
typedef struct tagARM_INSTR_MSRI        ARM_INSTR_MSRI;       //Move immediate to status register instructions
typedef struct tagARM_INSTR_MSRR        ARM_INSTR_MSRR;       //Move register to status register instructions
typedef struct tagARM_INSTR_MRS         ARM_INSTR_MRS;        //Move status register to register instructions
typedef struct tagARM_INSTR_MRCMCR      ARM_INSTR_MRCMCR;     //Move register to coprocessor or coprocessor to register instructions
typedef struct tagARM_INSTR_CLZ         ARM_INSTR_CLZ;        //Count leading zero instruction

//----------------------------------------------------------------------------------------------------------------------------------

typedef union tagARM_INSTRUCTION    ARM_INSTRUCTION;

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARM_INSTR_BASE
{
  u_int32_t data:12;      //Addressing data
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t s:1;          //Update status bit
  u_int32_t opcode:4;     //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_MUL
{
  u_int32_t rm:4;         //Register m
  u_int32_t nu:4;         //Fixed value
  u_int32_t rs:4;         //Register s
  u_int32_t rn:4;         //Register n
  u_int32_t rd:4;         //Destination register
  u_int32_t s:1;          //Status update flag
  u_int32_t op1:3;        //Opcode for type of multiply
  u_int32_t type:4;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_SMULXY
{
  u_int32_t rm:4;         //Register m
  u_int32_t nu2:1;        //Fixed value
  u_int32_t x:1;          //mss or lss indicator for rm
  u_int32_t y:1;          //mss or lss indicator for rs
  u_int32_t nu1:1;        //Fixed value
  u_int32_t rs:4;         //Register s
  u_int32_t rn:4;         //Register n
  u_int32_t rd:4;         //Destination register
  u_int32_t s:1;          //Status update flag
  u_int32_t op1:3;        //Opcode for type of multiply
  u_int32_t type:4;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_ELS
{
  u_int32_t rm:4;         //Register
  u_int32_t nu1:1;        //Always one
  u_int32_t opcode:2;     //Opcode
  u_int32_t nu2:1;        //Always one
  u_int32_t rs:4;         //Register
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //
  u_int32_t w:1;          //
  u_int32_t b:1;          //
  u_int32_t u:1;          //
  u_int32_t p:1;          //
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_LSI
{
  u_int32_t of:12;        //Offset
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //Load or store. 1: Load. 0: Store.
  u_int32_t w:1;          //For offset addressing this is the write back to base indicator.
  u_int32_t b:1;          //Unsigned byte mode
  u_int32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  u_int32_t p:1;          //Pre indexed addressing. Combined with W bit
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_LSR
{
  u_int32_t rm:4;        //Offset
  u_int32_t nu:1;         //Not used
  u_int32_t sm:2;         //Shift mode
  u_int32_t sa:5;         //Shift amount
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //Load or store. 1: Load. 0: Store.
  u_int32_t w:1;          //For offset addressing this is the write back to base indicator.
  u_int32_t b:1;          //Unsigned byte mode
  u_int32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  u_int32_t p:1;          //Pre indexed addressing. Combined with W bit
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_LSRN
{
  u_int32_t rm:4;         //Register m
  u_int32_t ns:8;         //No scaling when zero
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //Load or store. 1: Load. 0: Store.
  u_int32_t w:1;          //For offset addressing this is the write back to base indicator.
  u_int32_t b:1;          //Unsigned byte mode
  u_int32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  u_int32_t p:1;          //Pre indexed addressing. Combined with W bit
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_LSX
{
  u_int32_t rm:4;         //Register m
  u_int32_t sbo2:1;       //Should be one
  u_int32_t op1:2;        //Extra opcode
  u_int32_t sbo1:1;       //Should be one
  u_int32_t rs:4;         //Register s
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Register n
  u_int32_t l:1;          //Load or store. 1: Load. 0: Store.
  u_int32_t w:1;          //For offset addressing this is the write back to base indicator.
  u_int32_t i:1;          //Immediate offset / index or register offset / index
  u_int32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  u_int32_t p:1;          //Pre indexed addressing. Combined with W bit
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_DPSI
{
  u_int32_t rm:4;         //Register
  u_int32_t t1:1;         //Shift type
  u_int32_t sm:2;         //Shift mode
  u_int32_t sa:5;         //Shift amount
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t opcode:4;     //Opcode for type of multiply
  u_int32_t type:4;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_DPSR
{
  u_int32_t rm:4;         //Register
  u_int32_t t1:1;         //Shift type
  u_int32_t sm:2;         //Shift mode
  u_int32_t nu:1;         //Always 0
  u_int32_t rs:4;         //Shift amount register
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t opcode:4;     //Opcode for type of data processing
  u_int32_t type:4;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_DPI
{
  u_int32_t im:8;         //Immediate value
  u_int32_t ri:4;         //Rotate immediate
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t opcode:4;     //Opcode for type of data processing
  u_int32_t type:4;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_MSRI
{
  u_int32_t im:8;         //Immediate value
  u_int32_t ri:4;         //Rotate immediate
  u_int32_t sbo:4;        //Should be one
  u_int32_t c:1;          //Control field mask
  u_int32_t x:1;          //Extension field mask
  u_int32_t s:1;          //Status field mask
  u_int32_t f:1;          //Flags field mask
  u_int32_t nu1:2;        //Not used after decoding
  u_int32_t r:1;          //Target register select 0: cpsr. 1: spsr.
  u_int32_t nu2:5;        //Not used after decoding
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_MSRR
{
  u_int32_t rm:4;         //Register holding the data
  u_int32_t sbz:8;        //Should be zero
  u_int32_t sbo:4;        //Should be one
  u_int32_t c:1;          //Control field mask
  u_int32_t x:1;          //Extension field mask
  u_int32_t s:1;          //Status field mask
  u_int32_t f:1;          //Flags field mask
  u_int32_t nu1:1;        //Not used after decoding
  u_int32_t d:1;          //Move direction bit
  u_int32_t r:1;          //Target register select 0: cpsr. 1: spsr.
  u_int32_t nu2:5;        //Not used after decoding
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_MRS
{
  u_int32_t sbz:12;       //Should be zero
  u_int32_t rd:4;         //Destination register
  u_int32_t sbo:4;        //Should be one
  u_int32_t nu1:2;        //Not used after decoding
  u_int32_t r:1;          //Source register select 0: cpsr. 1: spsr.
  u_int32_t nu2:5;        //Not used after decoding
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_MRCMCR
{
  u_int32_t crm:4;        //Coprocessor register m
  u_int32_t nu:1;         //Not used after decoding
  u_int32_t op2:3;        //Coprocessor opcode 2
  u_int32_t cpn:4;        //Coprocessor number
  u_int32_t rd:4;         //Destination register
  u_int32_t crn:4;        //Coprocessor register n
  u_int32_t d:1;          //Data direction bit
  u_int32_t op1:3;        //Coprocessor opcode 1
  u_int32_t type:4;       //Type bits
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_MISC0
{
  u_int32_t rm:4;         //Register
  u_int32_t op2:4;        //Opcode 2
  u_int32_t rs:4;         //Multiply register
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t s:1;          //Update status bit
  u_int32_t op1:2;        //Opcode 1
  u_int32_t type:5;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_CLZ
{
  u_int32_t rm:4;         //Register
  u_int32_t nu2:4;        //Not used
  u_int32_t sbo:4;        //Should be one
  u_int32_t rd:4;         //Destination register
  u_int32_t nu1:12;       //Not used
  u_int32_t cond:4;       //Condition bits
};

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARM_INSTR_TYPE0
{
  u_int32_t rm:4;         //Register
  u_int32_t it1:1;        //Instruction type
  u_int32_t sm:2;         //Shift mode
  u_int32_t it2:1;        //Instruction type
  u_int32_t rs:4;         //Register
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t s:1;          //Update status bit
  u_int32_t opcode:4;     //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_TYPE1
{
  u_int32_t im:8;         //Immediate
  u_int32_t r:4;          //Rotate
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t s:1;          //Update status bit
  u_int32_t opcode:4;     //Actual opcode for some type of instructions
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_TYPE2
{
  u_int32_t im:12;        //Immediate data
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //Load or store. 1: Load. 0: Store.
  u_int32_t w:1;          //For offset addressing this is the write back to base indicator.
  u_int32_t b:1;          //Unsigned byte mode
  u_int32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  u_int32_t p:1;          //Pre indexed addressing. Combined with W bit
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_TYPE3
{
  u_int32_t rm:4;         //Register
  u_int32_t it1:1;        //Instruction type
  u_int32_t sm:2;         //Shift mode
  u_int32_t sa:5;         //Shift amount
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //Load or store. 1: Load. 0: Store.
  u_int32_t w:1;          //For offset addressing this is the write back to base indicator.
  u_int32_t b:1;          //Unsigned byte mode
  u_int32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  u_int32_t p:1;          //Pre indexed addressing. Combined with W bit
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_TYPE4
{
  u_int32_t r0:1;         //Include r0
  u_int32_t r1:1;         //Include r1
  u_int32_t r2:1;         //Include r2
  u_int32_t r3:1;         //Include r3
  u_int32_t r4:1;         //Include r4
  u_int32_t r5:1;         //Include r5
  u_int32_t r6:1;         //Include r6
  u_int32_t r7:1;         //Include r7
  u_int32_t r8:1;         //Include r8
  u_int32_t r9:1;         //Include r9
  u_int32_t r10:1;        //Include r10
  u_int32_t r11:1;        //Include r11
  u_int32_t r12:1;        //Include r12
  u_int32_t r13:1;        //Include r13
  u_int32_t r14:1;        //Include r14
  u_int32_t r15:1;        //Include r15
  u_int32_t rn:4;         //Register holding the base address
  u_int32_t l:1;          //Load or store. 1: Load. 0: Store.
  u_int32_t w:1;          //Update base register after transfer
  u_int32_t s:1;          //Restore cpsr from spsr when r15 included
  u_int32_t u:1;          //Direction. 1: Add to base. 0: Subtract from base
  u_int32_t p:1;          //Range base included or not
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_TYPE5
{
  u_int32_t offset:24;    //Signed offset
  u_int32_t l:1;          //Update link register
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_TYPE6
{
  u_int32_t of:8;         //Offset
  u_int32_t cp:4;         //Coprocessor number
  u_int32_t crd:4;        //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //
  u_int32_t w:1;          //
  u_int32_t n:1;          //
  u_int32_t u:1;          //
  u_int32_t p:1;          //
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

struct tagARM_INSTR_TYPE7
{
  u_int32_t rm:4;         //Register
  u_int32_t it1:1;        //Type of instruction bit
  u_int32_t sm:2;         //Shift mode
  u_int32_t sa:5;         //Shift amount
  u_int32_t rd:4;         //Destination register
  u_int32_t rn:4;         //Second operand register
  u_int32_t l:1;          //
  u_int32_t w:1;          //
  u_int32_t b:1;          //
  u_int32_t u:1;          //
  u_int32_t it2:1;        //Type of instruction bit
  u_int32_t type:3;       //Type of instructions
  u_int32_t cond:4;       //Condition bits
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagARM_INSTRUCTION
{
  u_int32_t            instr;      //Instruction register
  ARM_INSTR_BASE       base;       //Base for instruction decoding
  ARM_INSTR_MISC0      misc0;      //Miscellaneous instructions
  ARM_INSTR_TYPE0      type0;      //For type 0 instruction decoding
  ARM_INSTR_TYPE1      type1;      //For type 1 instruction decoding
  ARM_INSTR_TYPE2      type2;      //For type 2 instruction decoding
  ARM_INSTR_TYPE3      type3;      //For type 3 instruction decoding
  ARM_INSTR_TYPE4      type4;      //For type 4 instruction decoding
  ARM_INSTR_TYPE5      type5;      //For type 5 instruction decoding
  ARM_INSTR_TYPE6      type6;      //For type 6 instruction decoding
  ARM_INSTR_TYPE7      type7;      //For type 7 instruction decoding
  ARM_INSTR_MUL        mul;        //For multiply instructions
  ARM_INSTR_SMULXY     smulxy;     //For signed multiply instruction
  ARM_INSTR_ELS        els;        //For extra load and store instructions
  ARM_INSTR_DPSI       dpsi;       //For data processing immediate shift instructions
  ARM_INSTR_DPSR       dpsr;       //For data processing register shift instructions
  ARM_INSTR_DPI        dpi;        //For data processing immediate instructions
  ARM_INSTR_LSI        lsi;        //For load and store immediate instructions
  ARM_INSTR_LSR        lsr;        //For load and store register instructions
  ARM_INSTR_LSRN       lsrn;       //For load and store register no scaling instructions
  ARM_INSTR_LSX        lsx;        //For load and store register extra instructions
  ARM_INSTR_MSRI       msri;       //Move immediate to status register instructions
  ARM_INSTR_MSRR       msrr;       //Move register to status register instructions
  ARM_INSTR_MRS        mrs;        //Move status register to register instructions
  ARM_INSTR_MRCMCR     mrcmcr;     //Move register to coprocessor or coprocessor to register instructions
  ARM_INSTR_CLZ        clz;        //Count leading zero instruction
};                                        

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_COND_EQUAL             0           //Z set
#define ARM_COND_NOT_EQUAL         1           //Z clear
#define ARM_COND_CARRY_SET         2           //Carry set / unsigned higher or same
#define ARM_COND_CARRY_CLEAR       3           //Carry clear / unsigned lower
#define ARM_COND_MINUS             4           //N set
#define ARM_COND_PLUS              5           //N clear
#define ARM_COND_OVERFLOW          6           //V set
#define ARM_COND_NO_OVERFLOW       7           //V clear
#define ARM_COND_HIGHER            8           //C set and Z clear
#define ARM_COND_LOWER_SAME        9           //C clear or Z set
#define ARM_COND_GREATER_EQUAL    10           //N set and V set or N clear and V clear (N == V)
#define ARM_COND_LESS_THAN        11           //N set and V clear or N clear and V set (N != V)
#define ARM_COND_GREATER_THAN     12           //Z clear and (N set and V set or N clear and V clear) (Z == 0; N == V)
#define ARM_COND_LESS_THAN_EQUAL  13           //Z set and (N set and V clear or N clear and V set) (Z == 1; N != V)
#define ARM_COND_ALWAYS           14           //Always execute
#define ARM_COND_SPECIAL          15

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_OPCODE_AND            0
#define ARM_OPCODE_EOR            1
#define ARM_OPCODE_SUB            2
#define ARM_OPCODE_RSB            3
#define ARM_OPCODE_ADD            4
#define ARM_OPCODE_ADC            5
#define ARM_OPCODE_SBC            6
#define ARM_OPCODE_RSC            7
#define ARM_OPCODE_TST            8
#define ARM_OPCODE_TEQ            9
#define ARM_OPCODE_CMP           10
#define ARM_OPCODE_CMN           11
#define ARM_OPCODE_ORR           12
#define ARM_OPCODE_MOV           13
#define ARM_OPCODE_BIC           14
#define ARM_OPCODE_MVN           15

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_SHIFT_MODE_LSL        0
#define ARM_SHIFT_MODE_LSR        1
#define ARM_SHIFT_MODE_ASR        2
#define ARM_SHIFT_MODE_ROR        3

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_FLAGS_UPDATE_CV_NO    0    //Do not update the carry and overflow
#define ARM_FLAGS_UPDATE_CV       1    //For add the carry is the carry
#define ARM_FLAGS_UPDATE_NBV      2    //For subtract the carry is the not borrow
#define ARM_FLAGS_UPDATE_CV_CLR   3    //Clear both flags

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_MEMORY_MASK          0x0003

#define ARM_MEMORY_WORD          0x0000
#define ARM_MEMORY_SHORT         0x0001
#define ARM_MEMORY_BYTE          0x0002
#define ARM_MEMORY_DWORD         0x0003

#define ARM_SIGN_EXTEND          0x0010
#define ARM_MEM_TRACE_WRITE      0x0080

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_USER_MASK             0xF8000000
#define ARM_STATE_MASK            0x01000020
#define ARM_PRIVILEGED_MASK       0x000000DF

//----------------------------------------------------------------------------------------------------------------------------------

#define ARM_INSTRUCTION_SKIPPED            0
#define ARM_INSTRUCTION_EXECUTED           1
#define ARM_INSTRUCTION_THUMB              2

//----------------------------------------------------------------------------------------------------------------------------------

void ArmDisassemble(char *instrstr, u_int32_t strsize, u_int32_t program_counter, ARM_INSTRUCTION arm_instruction);

//----------------------------------------------------------------------------------------------------------------------------------

void ArmLSImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmLSRegister(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmLSExtraImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmLSExtraRegister(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmLS(ARM_INSTRUCTION arm_instruction, u_int32_t mode, char *instrstr, const char *op2);

void ArmMSRImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmMSRRegister(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmMSR(ARM_INSTRUCTION arm_instruction, char *instrstr, const char *op2);

void ArmMRS(ARM_INSTRUCTION arm_instruction, char *instrstr);

void ArmDPRShift(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmDPRImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmDPR(ARM_INSTRUCTION arm_instruction, char *instrstr, char *op2);

void ArmLSM(ARM_INSTRUCTION arm_instruction, char *instrstr);

void ArmBranch(u_int32_t program_counter, ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmBranchLinkExchange1(u_int32_t program_counter, ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmBranchLinkExchange2(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmBranchExchangeT(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmBranchExchangeJ(ARM_INSTRUCTION arm_instruction, char *instrstr);

void ArmMUL(ARM_INSTRUCTION arm_instruction, char *instrstr);
void ArmSMULxy(ARM_INSTRUCTION arm_instruction, char *instrstr);

void ArmMRCMCR(ARM_INSTRUCTION arm_instruction, char *instrstr);

void ArmCLZ(ARM_INSTRUCTION arm_instruction, char *instrstr);


//----------------------------------------------------------------------------------------------------------------------------------

#endif /* ARMDISASSEMBLE_H */

