//----------------------------------------------------------------------------------------------------------------------------------

#ifndef ARMV5TL_H
#define ARMV5TL_H

//----------------------------------------------------------------------------------------------------------------------------------

#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/types.h>

#include "armv5tl_thumb_structs.h"
#include "f1c100s_structs.h"

//----------------------------------------------------------------------------------------------------------------------------------
//Key for sharing the memory between the threads
#define SHARED_MEMORY_KEY   0x72A5F31E

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagARMV5TL_ADDRESS_MAP       ARMV5TL_ADDRESS_MAP;
typedef struct tagARMV5TL_INSTR_BASE        ARMV5TL_INSTR_BASE;
typedef struct tagARMV5TL_INSTR_MISC0       ARMV5TL_INSTR_MISC0;     //Miscellaneous instructions
typedef struct tagARMV5TL_INSTR_TYPE0       ARMV5TL_INSTR_TYPE0;
typedef struct tagARMV5TL_INSTR_TYPE1       ARMV5TL_INSTR_TYPE1;
typedef struct tagARMV5TL_INSTR_TYPE2       ARMV5TL_INSTR_TYPE2;
typedef struct tagARMV5TL_INSTR_TYPE3       ARMV5TL_INSTR_TYPE3;
typedef struct tagARMV5TL_INSTR_TYPE4       ARMV5TL_INSTR_TYPE4;
typedef struct tagARMV5TL_INSTR_TYPE5       ARMV5TL_INSTR_TYPE5;
typedef struct tagARMV5TL_INSTR_TYPE6       ARMV5TL_INSTR_TYPE6;
typedef struct tagARMV5TL_INSTR_TYPE7       ARMV5TL_INSTR_TYPE7;
typedef struct tagARMV5TL_INSTR_MUL         ARMV5TL_INSTR_MUL;        //Multiply instructions
typedef struct tagARMV5TL_INSTR_SMULXY      ARMV5TL_INSTR_SMULXY;     //Signed multiply
typedef struct tagARMV5TL_INSTR_ELS         ARMV5TL_INSTR_ELS;        //Extra load and store instructions
typedef struct tagARMV5TL_INSTR_DPSI        ARMV5TL_INSTR_DPSI;       //Data processing shift immediate instructions
typedef struct tagARMV5TL_INSTR_DPSR        ARMV5TL_INSTR_DPSR;       //Data processing shift register instructions
typedef struct tagARMV5TL_INSTR_DPI         ARMV5TL_INSTR_DPI;        //Data processing immediate instructions
typedef struct tagARMV5TL_INSTR_LSI         ARMV5TL_INSTR_LSI;        //Load and store immediate instructions
typedef struct tagARMV5TL_INSTR_LSR         ARMV5TL_INSTR_LSR;        //Load and store register instructions
typedef struct tagARMV5TL_INSTR_LSRN        ARMV5TL_INSTR_LSRN;       //Load and store register no scaling instructions
typedef struct tagARMV5TL_INSTR_LSX         ARMV5TL_INSTR_LSX;        //Load and store register extra instructions
typedef struct tagARMV5TL_INSTR_MSRI        ARMV5TL_INSTR_MSRI;       //Move immediate to status register instructions
typedef struct tagARMV5TL_INSTR_MSRR        ARMV5TL_INSTR_MSRR;       //Move register to status register instructions
typedef struct tagARMV5TL_INSTR_MRS         ARMV5TL_INSTR_MRS;        //Move status register to register instructions
typedef struct tagARMV5TL_INSTR_MRCMCR      ARMV5TL_INSTR_MRCMCR;     //Move register to coprocessor or coprocessor to register instructions
typedef struct tagARMV5TL_INSTR_CLZ         ARMV5TL_INSTR_CLZ;        //Count leading zero instruction

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagARMV5TL_FLAGS             ARMV5TL_FLAGS;
typedef struct tagARMV5TL_REGS              ARMV5TL_REGS;
typedef struct tagARMV5TL_CORE              ARMV5TL_CORE, *PARMV5TL_CORE;

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct tagARMV5TL_TRACE_ENTRY       ARMV5TL_TRACE_ENTRY;

//----------------------------------------------------------------------------------------------------------------------------------

typedef union tagARMV5TL_STATUS             ARMV5TL_STATUS, *PARMV5TL_STATUS;
typedef union tagARMV5TL_ARM_INSTRUCTION    ARMV5TL_ARM_INSTRUCTION;
typedef union tagARMV5TL_MEMORY             ARMV5TL_MEMORY;

//----------------------------------------------------------------------------------------------------------------------------------

typedef void *(*PERIPHERALCHECK)(PARMV5TL_CORE core, uint32_t address, uint32_t mode);

typedef void (*PERIPHERALFUNC)(PARMV5TL_CORE core);

typedef void (*PERIPHERALREAD)(PARMV5TL_CORE core, uint32_t address, uint32_t mode);
typedef void (*PERIPHERALWRITE)(PARMV5TL_CORE core, uint32_t address, uint32_t mode);

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARMV5TL_ADDRESS_MAP
{
  uint32_t       start;
  uint32_t       end;
  PERIPHERALCHECK function;
  PERIPHERALREAD  read;
  PERIPHERALWRITE write;
};

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARMV5TL_INSTR_BASE
{
  uint32_t data:12;      //Addressing data
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t s:1;          //Update status bit
  uint32_t opcode:4;     //Actual opcode for some type of instructions
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_MUL
{
  uint32_t rm:4;         //Register m
  uint32_t nu:4;         //Fixed value
  uint32_t rs:4;         //Register s
  uint32_t rn:4;         //Register n
  uint32_t rd:4;         //Destination register
  uint32_t s:1;          //Status update flag
  uint32_t op1:3;        //Opcode for type of multiply
  uint32_t type:4;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_SMULXY
{
  uint32_t rm:4;         //Register m
  uint32_t nu2:1;        //Fixed value
  uint32_t x:1;          //mss or lss indicator for rm
  uint32_t y:1;          //mss or lss indicator for rs
  uint32_t nu1:1;        //Fixed value
  uint32_t rs:4;         //Register s
  uint32_t rn:4;         //Register n
  uint32_t rd:4;         //Destination register
  uint32_t s:1;          //Status update flag
  uint32_t op1:3;        //Opcode for type of multiply
  uint32_t type:4;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_ELS
{
  uint32_t rm:4;         //Register
  uint32_t nu1:1;        //Always one
  uint32_t opcode:2;     //Opcode
  uint32_t nu2:1;        //Always one
  uint32_t rs:4;         //Register
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //
  uint32_t w:1;          //
  uint32_t b:1;          //
  uint32_t u:1;          //
  uint32_t p:1;          //
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_LSI
{
  uint32_t of:12;        //Offset
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //Load or store. 1: Load. 0: Store.
  uint32_t w:1;          //For offset addressing this is the write back to base indicator.
  uint32_t b:1;          //Unsigned byte mode
  uint32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  uint32_t p:1;          //Pre indexed addressing. Combined with W bit
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_LSR
{
  uint32_t rm:4;        //Offset
  uint32_t nu:1;         //Not used
  uint32_t sm:2;         //Shift mode
  uint32_t sa:5;         //Shift amount
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //Load or store. 1: Load. 0: Store.
  uint32_t w:1;          //For offset addressing this is the write back to base indicator.
  uint32_t b:1;          //Unsigned byte mode
  uint32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  uint32_t p:1;          //Pre indexed addressing. Combined with W bit
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_LSRN
{
  uint32_t rm:4;         //Register m
  uint32_t ns:8;         //No scaling when zero
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //Load or store. 1: Load. 0: Store.
  uint32_t w:1;          //For offset addressing this is the write back to base indicator.
  uint32_t b:1;          //Unsigned byte mode
  uint32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  uint32_t p:1;          //Pre indexed addressing. Combined with W bit
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_LSX
{
  uint32_t rm:4;         //Register m
  uint32_t sbo2:1;       //Should be one
  uint32_t op1:2;        //Extra opcode
  uint32_t sbo1:1;       //Should be one
  uint32_t rs:4;         //Register s
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Register n
  uint32_t l:1;          //Load or store. 1: Load. 0: Store.
  uint32_t w:1;          //For offset addressing this is the write back to base indicator.
  uint32_t i:1;          //Immediate offset / index or register offset / index
  uint32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  uint32_t p:1;          //Pre indexed addressing. Combined with W bit
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_DPSI
{
  uint32_t rm:4;         //Register
  uint32_t t1:1;         //Shift type
  uint32_t sm:2;         //Shift mode
  uint32_t sa:5;         //Shift amount
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t opcode:4;     //Opcode for type of multiply
  uint32_t type:4;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_DPSR
{
  uint32_t rm:4;         //Register
  uint32_t t1:1;         //Shift type
  uint32_t sm:2;         //Shift mode
  uint32_t nu:1;         //Always 0
  uint32_t rs:4;         //Shift amount register
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t opcode:4;     //Opcode for type of data processing
  uint32_t type:4;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_DPI
{
  uint32_t im:8;         //Immediate value
  uint32_t ri:4;         //Rotate immediate
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t opcode:4;     //Opcode for type of data processing
  uint32_t type:4;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_MSRI
{
  uint32_t im:8;         //Immediate value
  uint32_t ri:4;         //Rotate immediate
  uint32_t sbo:4;        //Should be one
  uint32_t c:1;          //Control field mask
  uint32_t x:1;          //Extension field mask
  uint32_t s:1;          //Status field mask
  uint32_t f:1;          //Flags field mask
  uint32_t nu1:2;        //Not used after decoding
  uint32_t r:1;          //Target register select 0: cpsr. 1: spsr.
  uint32_t nu2:5;        //Not used after decoding
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_MSRR
{
  uint32_t rm:4;         //Register holding the data
  uint32_t sbz:8;        //Should be zero
  uint32_t sbo:4;        //Should be one
  uint32_t c:1;          //Control field mask
  uint32_t x:1;          //Extension field mask
  uint32_t s:1;          //Status field mask
  uint32_t f:1;          //Flags field mask
  uint32_t nu1:1;        //Not used after decoding
  uint32_t d:1;          //Move direction bit
  uint32_t r:1;          //Target register select 0: cpsr. 1: spsr.
  uint32_t nu2:5;        //Not used after decoding
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_MRS
{
  uint32_t sbz:12;       //Should be zero
  uint32_t rd:4;         //Destination register
  uint32_t sbo:4;        //Should be one
  uint32_t nu1:2;        //Not used after decoding
  uint32_t r:1;          //Source register select 0: cpsr. 1: spsr.
  uint32_t nu2:5;        //Not used after decoding
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_MRCMCR
{
  uint32_t crm:4;        //Coprocessor register m
  uint32_t nu:1;         //Not used after decoding
  uint32_t op2:3;        //Coprocessor opcode 2
  uint32_t cpn:4;        //Coprocessor number
  uint32_t rd:4;         //Destination register
  uint32_t crn:4;        //Coprocessor register n
  uint32_t d:1;          //Data direction bit
  uint32_t op1:3;        //Coprocessor opcode 1
  uint32_t type:4;       //Type bits
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_MISC0
{
  uint32_t rm:4;         //Register
  uint32_t op2:4;        //Opcode 2
  uint32_t rs:4;         //Multiply register
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t s:1;          //Update status bit
  uint32_t op1:2;        //Opcode 1
  uint32_t type:5;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_CLZ
{
  uint32_t rm:4;         //Register
  uint32_t nu2:4;        //Not used
  uint32_t sbo:4;        //Should be one
  uint32_t rd:4;         //Destination register
  uint32_t nu1:12;       //Not used
  uint32_t cond:4;       //Condition bits
};

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARMV5TL_INSTR_TYPE0
{
  uint32_t rm:4;         //Register
  uint32_t it1:1;        //Instruction type
  uint32_t sm:2;         //Shift mode
  uint32_t it2:1;        //Instruction type
  uint32_t rs:4;         //Register
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t s:1;          //Update status bit
  uint32_t opcode:4;     //Actual opcode for some type of instructions
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_TYPE1
{
  uint32_t im:8;         //Immediate
  uint32_t r:4;          //Rotate
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t s:1;          //Update status bit
  uint32_t opcode:4;     //Actual opcode for some type of instructions
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_TYPE2
{
  uint32_t im:12;        //Immediate data
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //Load or store. 1: Load. 0: Store.
  uint32_t w:1;          //For offset addressing this is the write back to base indicator.
  uint32_t b:1;          //Unsigned byte mode
  uint32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  uint32_t p:1;          //Pre indexed addressing. Combined with W bit
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_TYPE3
{
  uint32_t rm:4;         //Register
  uint32_t it1:1;        //Instruction type
  uint32_t sm:2;         //Shift mode
  uint32_t sa:5;         //Shift amount
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //Load or store. 1: Load. 0: Store.
  uint32_t w:1;          //For offset addressing this is the write back to base indicator.
  uint32_t b:1;          //Unsigned byte mode
  uint32_t u:1;          //Offset use mode 1: Add to base. 0: Subtract from base
  uint32_t p:1;          //Pre indexed addressing. Combined with W bit
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_TYPE4
{
  uint32_t r0:1;         //Include r0
  uint32_t r1:1;         //Include r1
  uint32_t r2:1;         //Include r2
  uint32_t r3:1;         //Include r3
  uint32_t r4:1;         //Include r4
  uint32_t r5:1;         //Include r5
  uint32_t r6:1;         //Include r6
  uint32_t r7:1;         //Include r7
  uint32_t r8:1;         //Include r8
  uint32_t r9:1;         //Include r9
  uint32_t r10:1;        //Include r10
  uint32_t r11:1;        //Include r11
  uint32_t r12:1;        //Include r12
  uint32_t r13:1;        //Include r13
  uint32_t r14:1;        //Include r14
  uint32_t r15:1;        //Include r15
  uint32_t rn:4;         //Register holding the base address
  uint32_t l:1;          //Load or store. 1: Load. 0: Store.
  uint32_t w:1;          //Update base register after transfer
  uint32_t s:1;          //Restore cpsr from spsr when r15 included
  uint32_t u:1;          //Direction. 1: Add to base. 0: Subtract from base
  uint32_t p:1;          //Range base included or not
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_TYPE5
{
  uint32_t offset:24;    //Signed offset
  uint32_t l:1;          //Update link register
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_TYPE6
{
  uint32_t of:8;         //Offset
  uint32_t cp:4;         //Coprocessor number
  uint32_t crd:4;        //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //
  uint32_t w:1;          //
  uint32_t n:1;          //
  uint32_t u:1;          //
  uint32_t p:1;          //
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

struct tagARMV5TL_INSTR_TYPE7
{
  uint32_t rm:4;         //Register
  uint32_t it1:1;        //Type of instruction bit
  uint32_t sm:2;         //Shift mode
  uint32_t sa:5;         //Shift amount
  uint32_t rd:4;         //Destination register
  uint32_t rn:4;         //Second operand register
  uint32_t l:1;          //
  uint32_t w:1;          //
  uint32_t b:1;          //
  uint32_t u:1;          //
  uint32_t it2:1;        //Type of instruction bit
  uint32_t type:3;       //Type of instructions
  uint32_t cond:4;       //Condition bits
};

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARMV5TL_FLAGS
{
  uint32_t M:5;         //Mode bits
  uint32_t T:1;         //Thumb execution state flag
  uint32_t F:1;         //Fast Interrupt disable flag
  uint32_t I:1;         //Interrupt disable flag
  uint32_t R1:8;        //Reserved bits
  uint32_t GE:4;        //Greater then or equal flags
  uint32_t R2:4;        //Reserved bits
  uint32_t J:1;         //Jazelle execution state flag
  uint32_t R3:2;        //Reserved bits
  uint32_t Q:1;         //DSP overflow / saturation flag
  uint32_t V:1;         //Overflow flag
  uint32_t C:1;         //Carry flag
  uint32_t Z:1;         //Zero flag
  uint32_t N:1;         //Negative flag
};

//----------------------------------------------------------------------------------------------------------------------------------

union tagARMV5TL_STATUS
{
  uint32_t     word;            //Word register
  ARMV5TL_FLAGS flags;          //Bit flags
};                                        

union tagARMV5TL_ARM_INSTRUCTION
{
  uint32_t                instr;       //Instruction register
  ARMV5TL_INSTR_BASE       base;       //Base for instruction decoding
  ARMV5TL_INSTR_MISC0      misc0;      //Miscellaneous instructions
  ARMV5TL_INSTR_TYPE0      type0;      //For type 0 instruction decoding
  ARMV5TL_INSTR_TYPE1      type1;      //For type 1 instruction decoding
  ARMV5TL_INSTR_TYPE2      type2;      //For type 2 instruction decoding
  ARMV5TL_INSTR_TYPE3      type3;      //For type 3 instruction decoding
  ARMV5TL_INSTR_TYPE4      type4;      //For type 4 instruction decoding
  ARMV5TL_INSTR_TYPE5      type5;      //For type 5 instruction decoding
  ARMV5TL_INSTR_TYPE6      type6;      //For type 6 instruction decoding
  ARMV5TL_INSTR_TYPE7      type7;      //For type 7 instruction decoding
  ARMV5TL_INSTR_MUL        mul;        //For multiply instructions
  ARMV5TL_INSTR_SMULXY     smulxy;     //For signed multiply instruction
  ARMV5TL_INSTR_ELS        els;        //For extra load and store instructions
  ARMV5TL_INSTR_DPSI       dpsi;       //For data processing immediate shift instructions
  ARMV5TL_INSTR_DPSR       dpsr;       //For data processing register shift instructions
  ARMV5TL_INSTR_DPI        dpi;        //For data processing immediate instructions
  ARMV5TL_INSTR_LSI        lsi;        //For load and store immediate instructions
  ARMV5TL_INSTR_LSR        lsr;        //For load and store register instructions
  ARMV5TL_INSTR_LSRN       lsrn;       //For load and store register no scaling instructions
  ARMV5TL_INSTR_LSX        lsx;        //For load and store register extra instructions
  ARMV5TL_INSTR_MSRI       msri;       //Move immediate to status register instructions
  ARMV5TL_INSTR_MSRR       msrr;       //Move register to status register instructions
  ARMV5TL_INSTR_MRS        mrs;        //Move status register to register instructions
  ARMV5TL_INSTR_MRCMCR     mrcmcr;     //Move register to coprocessor or coprocessor to register instructions
  ARMV5TL_INSTR_CLZ        clz;        //Count leading zero instruction
};                                        

union tagARMV5TL_MEMORY
{
  uint32_t  m_32bit;
  uint16_t  m_16bit[2];
  uint8_t   m_8bit[4];
};

//----------------------------------------------------------------------------------------------------------------------------------
//The complete arm register set
struct tagARMV5TL_REGS
{
  uint32_t r0;
  uint32_t r1;
  uint32_t r2;
  uint32_t r3;
  uint32_t r4;
  uint32_t r5;
  uint32_t r6;
  uint32_t r7;
  uint32_t r8[2];
  uint32_t r9[2];
  uint32_t r10[2];
  uint32_t r11[2];
  uint32_t r12[2];
  uint32_t r13[6];
  uint32_t r14[6];
  uint32_t r15;
  uint32_t cpsr;
  uint32_t spsr[5];
};

//----------------------------------------------------------------------------------------------------------------------------------

struct tagARMV5TL_TRACE_ENTRY
{
  uint32_t    instruction_address;     //Address of the traced instruction
  uint32_t    instruction_word;        //Instruction word for arm, half word for thumb
  uint32_t    execution_status;        //Information about if the arm instruction has been executed or not
  ARMV5TL_REGS registers;              //The 37 registers
  uint32_t    memory_address;          //Depending on the type of instruction this is set with the targeted memory address
  uint32_t    memory_direction;        //For load or store multiple instructions this signals if the given address is incremented or decremented
  uint32_t    data_width;              //For instructions that load or store half words or bytes this will reflect this, otherwise word width
  uint32_t    data_count;              //The number of words read or written by the instruction
  uint32_t    data[16];                //The data read or written. Single instruction can do a max of 16 words
};

//----------------------------------------------------------------------------------------------------------------------------------
//The core main struct
struct tagARMV5TL_CORE
{
  uint32_t                *registers[6][18];          //The ARM core has banked register sets. In different modes some of the registers are not available or are the un_banked user mode ones. Pointers are used to emulate this.
  
  uint32_t                 current_mode;              //The mode the core is running in.
  uint32_t                 current_bank;              //The register bank currently in use.
  
  ARMV5TL_ARM_INSTRUCTION   arm_instruction;          //The arm instruction loaded for the current cycle. Only when in arm state
  ARMV5TL_THUMB_INSTRUCTION thumb_instruction;        //The thumb instruction loaded for the current cycle. Only when in thumb state
  
  uint32_t                 pcincrvalue;               //Value the program counter needs to be incremented with
  
  uint64_t                 cpu_cycles;                //Counter for counting the cpu instruction cycles. Used for timing peripherals
  
  int                      *program_counter;          //For more direct control a pointer to the program counter here
  ARMV5TL_STATUS           *status;                   //Same for the status word
  
  uint32_t                 reset;                     //Processor reset flag
  uint32_t                 irq;                       //Processor irg flag
  uint32_t                 fiq;                       //Processor fast interrupt flag
  uint32_t                 undefinedinstruction;      //Flag to signal undefined instruction encountered
  
  uint32_t                 run;                       //Processor run flag
  
  ARMV5TL_MEMORY            sram1[8192];              //32K core startup memory located at address 0x00000000
  ARMV5TL_MEMORY            sram2[10240];             //40K core static memory located at address 0x00010000
  
  ARMV5TL_MEMORY            dram[8388608];            //32M of DDR memory

  ARMV5TL_REGS              regs;                     //The actual register bank
  
  //F1C100s section
  F1C100S_PERIPH_STATUS     f1c100s_periph_status;    //Status of the F1C100s peripheral reset states
          
  //F1C100s peripherals
  F1C100S_CCU               f1c100s_ccu;              //The clock control registers
  F1C100S_DRAMC             f1c100s_dramc;            //The dram control registers
  F1C100S_INTC              f1c100s_intc;             //Interrupt controller registers
  F1C100S_TIMER             f1c100s_timer;            //Timer control registers
  
  F1C100S_UART              f1c100s_uart[3];          //UART 0-2 control registers
  F1C100S_SPI               f1c100s_spi[2];           //SPI 0-1 control registers
  
  F1C100S_TCON              f1c100s_tcon;             //LCD timing control registers
  F1C100S_DEBE              f1c100s_debe;             //Display engine back end control registers
  
  F1C100S_PIO_PORT          f1c100s_port[6];          //Port A-F registers
  F1C100S_PIO_INT           f1c100s_port_int[3];      //Port D-F interrupt registers
  F1C100S_PIO_DDR           f1c100s_port_ddr;         //DDR port registers
  
  //Function pointers for handling peripherals
  PERIPHERALREAD            periph_read_func;         //Pointer to a function to call before a read
  PERIPHERALWRITE           periph_write_func;        //Pointer to a function to call after a write
  
  PERIPHERALFUNC            peripheralfunction;       //Pointer to function for handling the peripherals. When not used set to NULL
  
  //Storage for display and flash memory handling
  DISPLAY_MEMORY            displaymemory;            //Display memory handling data
  FLASH_MEMORY              flashmemory;              //Flash memory handling data
  TOUCH_PANEL_DATA          touchpaneldata;           //Touch panel handling data
  FPGA_DATA                 fpgadata;                 //FPGA handling data
  
  //Flash file pointer
  FILE                     *FlashFilePointer;         //Null if no file selected
 
  //Debug and tracing support
  FILE                     *TraceFilePointer;         //Null if tracing is disabled
  
  uint32_t                 breakpointaddress;         //Instruction address for breakpoint
  
  uint32_t                 tracetriggeraddress;       //Instruction address to start tracing on
  uint32_t                 tracetriggered;            //Flag to signal tracing has been triggered
  uint32_t                 tracecount;                //Counter for limiting trace files to 256K Lines
  uint32_t                 tracefileindex;            //Index counter for the trace file name
  uint32_t                 tracebufferenabled;        //Flag to signal writing into the trace buffer is enabled
  uint32_t                 traceindex;                //Index into the trace buffer
  ARMV5TL_TRACE_ENTRY       tracebuffer[4096];        //A trace buffer to be able to get pre trace trigger info
};

//----------------------------------------------------------------------------------------------------------------------------------

//The processor modes
#define ARM_MODE_USER            0x10
#define ARM_MODE_FIQ             0x11
#define ARM_MODE_IRQ             0x12
#define ARM_MODE_SUPERVISOR      0x13
#define ARM_MODE_ABORT           0x17
#define ARM_MODE_UNDEFINED       0x1B
#define ARM_MODE_SYSTEM          0x1F

//The processor register banks
#define ARM_REG_BANK_USER          0
#define ARM_REG_BANK_FIQ           1
#define ARM_REG_BANK_IRQ           2
#define ARM_REG_BANK_SUPERVISOR    3
#define ARM_REG_BANK_ABORT         4
#define ARM_REG_BANK_UNDEFINED     5
#define ARM_REG_BANK_SYSTEM        0


#define ARM_REG_SPSR_IDX          17

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

#define ARM_SIGN_EXTEND          0x0010
#define ARM_NO_MEM_TRACE         0x0020
#define ARM_MEM_TRACE_DOUBLE     0x0040
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
//Thread functions
int startarmcore(void);
void stoparmcore(void);

void *armcorethread(void *arg);

//----------------------------------------------------------------------------------------------------------------------------------
//Main core functions
void ArmV5tlSetup(PARMV5TL_CORE core);

void ArmV5tlCore(PARMV5TL_CORE core);

//----------------------------------------------------------------------------------------------------------------------------------
//General memory handler
void *ArmV5tlGetMemoryPointer(PARMV5TL_CORE core, uint32_t address, uint32_t mode);

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlSetMemoryTraceData(PARMV5TL_CORE core, uint32_t address, uint32_t mode, uint32_t count, uint32_t direction);

//----------------------------------------------------------------------------------------------------------------------------------

//Undefined instruction
void ArmV5tlUndefinedInstruction(PARMV5TL_CORE core);

//Data processing immediate or register shift instruction handling
void ArmV5tlDPRShift(PARMV5TL_CORE core);

//Data processing immediate instruction handling
void ArmV5tlDPRImmediate(PARMV5TL_CORE core);

//Data processing instruction handling
void ArmV5tlDPR(PARMV5TL_CORE core, uint32_t vn, uint32_t vm, uint32_t c);

//Load and store immediate instruction handling
void ArmV5tlLSImmediate(PARMV5TL_CORE core);

//Load and store register instruction handling
void ArmV5tlLSRegister(PARMV5TL_CORE core);

//Load and store extra immediate instruction handling
void ArmV5tlLSExtraImmediate(PARMV5TL_CORE core);

//Load and store extra register instruction handling
void ArmV5tlLSExtraRegister(PARMV5TL_CORE core);

//Load and store instruction handling
void ArmV5tlLS(PARMV5TL_CORE core, uint32_t address, uint32_t mode);

//Load and store multiple instruction handling
void ArmV5tlLSM(PARMV5TL_CORE core);

//Multiply instruction handling
void ArmV5tlMUL(PARMV5TL_CORE core);
void ArmV5tlSMULxy(PARMV5TL_CORE core);

//Move immediate to status register
void ArmV5tlMSRImmediate(PARMV5TL_CORE core);

//Move register to status register
void ArmV5tlMSRRegister(PARMV5TL_CORE core);

//Move to status register
void ArmV5tlMSR(PARMV5TL_CORE core, uint32_t data);

//Move status register to register
void ArmV5tlMRS(PARMV5TL_CORE core);

//Move register to coprocessor or coprocessor to register
void ArmV5tlMRCMCR(PARMV5TL_CORE core);

//Handle branch instructions
void ArmV5tlBranch(PARMV5TL_CORE core);

//Handle branch with link and exchange instructions
void ArmV5tlBranchLinkExchange1(PARMV5TL_CORE core);

//Handle branch with link and exchange instructions
void ArmV5tlBranchLinkExchange2(PARMV5TL_CORE core);

//Handle branch with exchange instructions
void ArmV5tlBranchExchangeT(PARMV5TL_CORE core);

//Handle branch with exchange instructions
void ArmV5tlBranchExchangeJ(PARMV5TL_CORE core);

//Handle count leading zeros
void ArmV5tlCLZ(PARMV5TL_CORE core);


#endif /* ARMV5TL_H */

