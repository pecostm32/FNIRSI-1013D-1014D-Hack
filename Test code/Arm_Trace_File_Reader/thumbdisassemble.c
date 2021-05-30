//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "armdisassemble.h"
#include "thumbdisassemble.h"

//----------------------------------------------------------------------------------------------------------------------------------

extern const char *regnames[16];
extern const char *condnames[16];
extern const char *dstext[4];
extern const char *setext[2];
extern const char *shifttext[4];
extern const char *dprtext[16];
extern const char *lstext[2];
extern const char *lsmtext[2];

//----------------------------------------------------------------------------------------------------------------------------------

u_int32_t templinkregister;      //For disassembling bl blx prefix sequence

//----------------------------------------------------------------------------------------------------------------------------------

void ThumbDisassemble(char *instrstr, u_int32_t strsize, u_int32_t program_counter, ARM_THUMB_INSTRUCTION thumb_instruction)
{
  //Need a string pointer and it has to have adequate size
  if((instrstr == NULL) || (strsize < 60))
    return;
    
  //Decode based on the type bits
  switch(thumb_instruction.base.type)
  {
    case 0:
      //Check on instruction opcode
      if(thumb_instruction.base.op1 == 3)
      {
        //op1:3 ADD(3), SUB(3), ADD(1), MOV(2), SUB(1)
        ThumbDP0(thumb_instruction, instrstr);
      }
      else
      {
        //LSL(1) op1:0, LSR(1) op1:1, ASR(1) op1:2
        ThumbShiftImmediate(thumb_instruction, instrstr);
      }
      break;

    case 1:
      //MOV(1), CMP(1), ADD(2), SUB(2)
      ThumbDP1(thumb_instruction, instrstr);
      break;

    case 2:
      //Check if data processing or load / store instructions
      if(thumb_instruction.base.op1 == 0)
      {
        //Separate the shift instructions
        if((thumb_instruction.base.op2 == 2) || (thumb_instruction.base.op2 == 3) || (thumb_instruction.base.op2 == 4) || (thumb_instruction.base.op2 == 7))
        {
          //LSL(2) op2:2, LSR(2) op2:3, ASR(2) op2:4, ROR op2:7
          ThumbShiftRegister(thumb_instruction, instrstr);
        }
        //Get the other data processing functions except CMP(3), ADD(4), CPY and MOV(3)
        else if(thumb_instruction.base.op2 < 16)
        {
          //AND, EOR, ADC, SBC, TST, NEG, CMP(2), CMN, OR, BIC, MVN, MUL
          ThumbDP2(thumb_instruction, instrstr);
        }
        //Filter out the branch instructions
        else if((thumb_instruction.base.op2 & 0x1C) == 0x1C)
        {
          //BLX(2), BX
          ThumbBranch2(thumb_instruction, instrstr);
        }
        //The remainder are the special data processing functions
        else
        {
          //CMP(3), ADD(4), CPY and MOV(3)
          ThumbDP2S(thumb_instruction, instrstr);
        }
      }
      //Filter out the load immediate indexed instruction LDR(3)
      else if(thumb_instruction.base.op1 == 1)
      {
        //LDR(3)
        ThumbLS2I(thumb_instruction, instrstr);
      }
      else
      {
        //STR(2), STRH(2), STRB(2), LDR(2), LDRH(2), LDRB(2), LDRSB, LDRSH          
        ThumbLS2R(thumb_instruction, instrstr);
      }
      break;

    case 3:
      //STR(1), LDR(1), STRB(1), LDRB(1)
      ThumbLS3(thumb_instruction, instrstr);
      break;

    case 4:
      //Check if load / store short immediate offset
      if((thumb_instruction.base.op1 & 2) == 0)
      {
        //STRH(1), LDRH(1) (instruction decoding basically the same as type 3 so using same function here. Type 4 indicates short)
        ThumbLS3(thumb_instruction, instrstr);
      }
      //Load / store to / from stack
      else
      {
        //STR(3), LDR(4)
        ThumbLS4(thumb_instruction, instrstr);
      }
      break;

    case 5:
      //Filter out the add pc, sp plus immediate instructions
      if((thumb_instruction.base.op1 & 2) == 0)
      {
      //ADD(5)   101 00 ddd iiiiiiii
      //ADD(6)   101 01 ddd iiiiiiii
//        ArmUndefinedInstruction(thumb_instruction, instrstr);

      }
      //Filter out the ADD(7) and SUB(4) instructions
      else if((thumb_instruction.base.op2 & 0x1C) == 0)
      {
      //ADD(7)   101 10 0000 iiiiiii
      //SUB(4)   101 10 0001 iiiiiii
//        ArmUndefinedInstruction(thumb_instruction, instrstr);

      }
      //Filter out POP and PUSH
      else if((thumb_instruction.base.op2 & 0x18) == 0x10)
      {
        //POP, PUSH. base register is sp (13) and bit 2 of op2 signals that the program counter or link register is included in the list
        if(thumb_instruction.base.op1 == 2)
        {
          //op1:2 is PUSH
          ThumbPUSH(thumb_instruction, instrstr);
        }
        else
        {
          //op1:3 is POP
          ThumbPOP(thumb_instruction, instrstr);
        }
      }
      //Filter out the REV and XT instructions
      else if((thumb_instruction.base.op2 & 0x18) == 0x08)
      {
      //REV      101 11 01000 nnn ddd
      //REV16    101 11 01001 nnn ddd
      //REVSH    101 11 01011 nnn ddd

      //SXTB     101 10 01001 mmm ddd
      //SXTH     101 10 01000 mmm ddd
      //UXTB     101 10 01011 mmm ddd
      //UXTH     101 10 01010 mmm ddd
//        ArmUndefinedInstruction(thumb_instruction, instrstr);

      }
      //Leaves the BKPT, CPS and SETEND
      else
      {
      //BKPT     101 11 110 iiiiiiii

      //CPS      101 10 1100 11 m 0 a i f

      //SETEND   101 10 11001 01 e zzz

//        ArmUndefinedInstruction(thumb_instruction, instrstr);

      }
      break;

    case 6:
      //Filter out the load and store multiple instructions
      if(thumb_instruction.b6.op1 == 0)
      {
        //STMIA, LDMIA
        ThumbLSMIA(thumb_instruction, instrstr);
      }
      else
      {
        //Filter out undefined instruction
        if(thumb_instruction.b6.cond == 14)
        {
          //UI
//          ArmUndefinedInstruction(thumb_instruction, instrstr);
        }
        //Filter out software interrupt
        else if(thumb_instruction.b6.cond == 15)
        {
          //SWI   110 1 1111 iiiiiiii
//          ArmUndefinedInstruction(thumb_instruction, instrstr);
        }
        //Leaves conditional branches
        else
        {
          //B(1)
          ThumbBranch6(program_counter, thumb_instruction, instrstr);
        }
      }
      break;

    case 7:
      //B(2), BLX(1), BL
      ThumbBranch7(program_counter, thumb_instruction, instrstr);
      break;
  }
}


//----------------------------------------------------------------------------------------------------------------------------------
//Immediate shift
void ThumbShiftImmediate(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  u_int32_t sa = thumb_instruction.shift0.sa;
  u_int32_t type;
  char      op2[32];
  
  //LSL(1) op1:0, LSR(1) op1:2, ASR(1) op1:2
  //Other values are filtered out in the decode stage
  switch(thumb_instruction.shift0.op1)
  {
    case 0:
      type = ARM_SHIFT_MODE_LSL;
      break;
      
    case 1:
      type = ARM_SHIFT_MODE_LSR;
      
      //Check if intended shift is 32. Shift amount in instruction is 0
      if(sa == 0)
        sa = 32;
      break;
      
    case 2:
      type = ARM_SHIFT_MODE_ASR;
      
      //Check if intended shift is 32. Shift amount in instruction is 0
      if(sa == 0)
        sa = 32;
      break;
  }
  
  //Print the second operand
  sprintf(op2, "%s, #%d", regnames[thumb_instruction.shift0.rm], sa);
  
  //Print the actual instruction
  ThumbShift(thumb_instruction, instrstr, type, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Register shift
void ThumbShiftRegister(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  char      op2[32];
  u_int32_t type;
  
  //LSL(2) op2:2, LSR(2) op2:3, ASR(2) op2:4, ROR op2:7
  //Other values are filtered out in the decode stage
  switch(thumb_instruction.shift2.op2)
  {
    case 2:
      type = ARM_SHIFT_MODE_LSL;
      break;
      
    case 3:
      type = ARM_SHIFT_MODE_LSR;
      break;
      
    case 4:
      type = ARM_SHIFT_MODE_ASR;
      break;
      
    case 7:
      type = ARM_SHIFT_MODE_ROR;
      break;
  }
  
  //Print the second operand
  sprintf(op2, "%s", regnames[thumb_instruction.shift2.rs]);
  
  //Print the actual instruction
  ThumbShift(thumb_instruction, instrstr, type, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Shift
void ThumbShift(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr, u_int32_t type, char *op2)
{
  //Print the instruction name and operands
  sprintf(instrstr, "%s         %s, %s", shifttext[type], regnames[thumb_instruction.shift0.rd], op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 0
void ThumbDP0(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  //Get the input data. For rd and vn there is no difference between dpi0 and dpr0
  u_int32_t rd = thumb_instruction.dpi0.rd;
  u_int32_t type;
  char      op2[32];
  
  //For op2 both dpr0 and dpi0 are the same
  switch(thumb_instruction.dpr0.op2)
  {
    //ADD(3)
    case 0:
      type = ARM_OPCODE_ADD;

      //Print the second operand
      sprintf(op2, "%s, %s", regnames[thumb_instruction.dpr0.rn], regnames[thumb_instruction.dpr0.rm]);
      break;

    //SUB(3)
    case 1:
      type = ARM_OPCODE_SUB;

      //Print the second operand
      sprintf(op2, "%s, %s", regnames[thumb_instruction.dpr0.rn], regnames[thumb_instruction.dpr0.rm]);
      break;
    
    //ADD(1), MOV(2)
    case 2:
      //Check if add or mov instruction
      if(thumb_instruction.dpi0.im)
      {
        //For a non zero immediate value it is an add
        type = ARM_OPCODE_ADD;

        //Print the second operand
        sprintf(op2, "%s, #%d", regnames[thumb_instruction.dpr0.rn], thumb_instruction.dpi0.im);
      }
      else
      {
        //For a zero immediate value it is move
        type = ARM_OPCODE_MOV;
        
        //Print the second operand
        sprintf(op2, "%s", regnames[thumb_instruction.dpi0.rn]);
      }
      break;

    //SUB(1)
    case 3:
      //Use the immediate value for the second operand
      type = ARM_OPCODE_SUB;

      //Print the second operand
      sprintf(op2, "%s, #%d", regnames[thumb_instruction.dpr0.rn], thumb_instruction.dpi0.im);
      break;
  }
  
  //Print the actual instruction
  ThumbDP(thumb_instruction, instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 1
void ThumbDP1(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  //Get the input data.
  u_int32_t rd = thumb_instruction.dp1.rd;
  u_int32_t type;
  char      op2[32];
  
  //For type 1 the op1 is the select for the type of function to perform
  switch(thumb_instruction.dp1.op1)
  {
    //MOV(1)
    case 0:
      type = ARM_OPCODE_MOV;
      break;

    //CMP(1)
    case 1:
      type = ARM_OPCODE_CMP;
      break;
    
    //ADD(2)
    case 2:
      type = ARM_OPCODE_ADD;
      break;

    //SUB(2)
    case 3:
      type = ARM_OPCODE_SUB;
      break;
  }

  //Print the second operand
  sprintf(op2, "#%d", thumb_instruction.dp1.im);
  
  //Print the actual instruction
  ThumbDP(thumb_instruction, instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 2
void ThumbDP2(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  //Get the input data.
  u_int32_t rd = thumb_instruction.dp2.rd;
  u_int32_t type;
  char      op2[32];
  
  //For type 2 dp2 op2 tells which function to perform. Some have already been filtered out in the decoding process.
  switch(thumb_instruction.dp2.op2)
  {
    //AND
    case 0:
      type = ARM_OPCODE_AND;
      break;

    //EOR
    case 1:
      type = ARM_OPCODE_EOR;
      break;
    
    //ADC
    case 5:
      type = ARM_OPCODE_ADC;
      break;

    //SBC
    case 6:
      type = ARM_OPCODE_SBC;
      break;
      
    //TST
    case 8:
      type = ARM_OPCODE_TST;
      break;
      
    //NEG
    case 9:
      type = ARM_OPCODE_THUMB_NEG;
      break;
      
    //CMP(2)
    case 10:
      type = ARM_OPCODE_CMP;
      break;

    //CMN
    case 11:
      type = ARM_OPCODE_CMN;
      break;

    //ORR
    case 12:
      type = ARM_OPCODE_ORR;
      break;

    //MUL
    case 13:
      type = ARM_OPCODE_THUMB_MUL;
      break;

    //BIC
    case 14:
      type = ARM_OPCODE_BIC;
      break;

    //MVN
    case 15:
      type = ARM_OPCODE_MVN;
      break;
  }

  //Print the second operand
  sprintf(op2, "%s", regnames[thumb_instruction.dp2.rm]);
  
  //Print the actual instruction
  ThumbDP(thumb_instruction, instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 2 special
void ThumbDP2S(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
 //Get the input data. rd is a combination of the h (high) bit and the three rd bits
  u_int32_t rd = thumb_instruction.dp2s.rd | (thumb_instruction.dp2s.h << 3);
  u_int32_t type;
  char      op2[32];
  
  //For type 2 dp2s op2 tells which function to perform. Most have already been filtered out in the decoding process.
  switch(thumb_instruction.dp2s.op2)
  {
    //ADD(4)
    case 4:
      type = ARM_OPCODE_ADD;
      break;

    //CMP(3)
    case 5:
      type = ARM_OPCODE_CMP;
      break;

    //CPY, MOV(3)
    case 6:
      type = ARM_OPCODE_MOV;
      break;
  }
  
  //Print the second operand
  sprintf(op2, "%s", regnames[thumb_instruction.dp2s.rm]);
  
  //Print the actual instruction
  ThumbDP(thumb_instruction, instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Actual data processing handling
void ThumbDP(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr, u_int32_t type, u_int32_t rd, char *op2)
{
  const char *opcode;
  
  //Check NEG opcode given
  if(type & ARM_OPCODE_THUMB_NEG)
  {
    //If so the opcode is neg
    opcode = "neg";
  }
  //Otherwise check if it is a MUL opcode
  else if(type & ARM_OPCODE_THUMB_MUL)
  {
    //If so the opcode is mul
    opcode = "mul";
  }
  //None of the above so normal ones
  else
  {
    //Otherwise the opcode is based on the type
    opcode = dprtext[type];
  }
  
  //Print the instruction name and operands
  sprintf(instrstr, "%s         %s, %s", opcode, regnames[rd], op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 2 immediate indexed based instructions
void ThumbLS2I(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
 //Get the input data
  u_int32_t rd = thumb_instruction.ls2i.rd;
  u_int32_t type;
  char      op2[32];

  //Signal loading of a word
  type = ARM_MEMORY_WORD | ARM_THUMB_LOAD_FLAG;
  
  //Print the second operand
  sprintf(op2, "[pc, #%d]", thumb_instruction.ls2i.im * 4);
  
  //Go and print the actual load or store
  ThumbLS(instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 2 register based instructions
void ThumbLS2R(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
 //Get the input data
  u_int32_t rd = thumb_instruction.ls2r.rd;
  u_int32_t type;
  char      op2[32];
  
  //Check if sign extend instructions
  if(thumb_instruction.ls2r.op2 == 3)
  {
    //Check on which size the instruction needs to work
    if(thumb_instruction.ls2r.op1 == 2)
    {
      //LDRSB
      type = ARM_MEMORY_BYTE;
    }
    else
    {
      //LDRSH
      type = ARM_MEMORY_SHORT;
    }
    
    //Signal load and sign extend
    type |= (ARM_THUMB_LOAD_FLAG | ARM_THUMB_SIGN_EXTEND);
  }
  //Normal load store instructions
  else
  {
    //Set the data size in the type
    type = thumb_instruction.ls2r.op2;
    
    //Check if load instructions
    if(thumb_instruction.ls2r.op1 == 3)
    {
      //Signal load functionality
      type |= ARM_THUMB_LOAD_FLAG;
    }
  }
  
  //Print the second operand
  sprintf(op2, "[%s, %s]", regnames[thumb_instruction.ls2r.rn], regnames[thumb_instruction.ls2r.rm]);
  
  //Go and print the actual load or store
  ThumbLS(instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 3 immediate indexed based instructions
void ThumbLS3(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
 //Get the input data
  u_int32_t rd = thumb_instruction.ls3.rd;
  u_int32_t type;
  char      op2[32];

  //Set the correct size for the given instruction
  if(thumb_instruction.ls3.type == 4)
  {
    //For type 4 instructions it is short
    type = ARM_MEMORY_SHORT;
  }
  else if(thumb_instruction.ls3.b)
  {
    //For b == 1 it is byte
    type = ARM_MEMORY_BYTE;
  }
  else
  {
    //For b == 0 it is word
    type = ARM_MEMORY_WORD;
  }
  
  //Check if load or store
  if(thumb_instruction.ls3.l)
  {
    //Signal load is requested
    type |= ARM_THUMB_LOAD_FLAG;
  }
  
  //Print the second operand
  sprintf(op2, "[%s, #%d]", regnames[thumb_instruction.ls3.rn], thumb_instruction.ls3.im * 4);
  
  //Go and print the actual load or store
  ThumbLS(instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 4 immediate indexed based instructions
void ThumbLS4(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
 //Get the input data. Instruction format is the same as for type 2 immediate indexed so reusing it here
  u_int32_t rd = thumb_instruction.ls2i.rd;
  u_int32_t type = ARM_MEMORY_WORD;
  char      op2[32];
  
  //Check if load or store
  if(thumb_instruction.ls2i.op1 == 3)
  {
    //Signal loading
    type |= ARM_THUMB_LOAD_FLAG;
  }
  
  //Print the second operand
  sprintf(op2, "[sp, #%d]", thumb_instruction.ls2i.im * 4);
  
  //Go and print the actual load or store
  ThumbLS(instrstr, type, rd, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store instruction handling
void ThumbLS(char *instrstr, u_int32_t type, u_int32_t rd, char *op2)
{
  //Print the instruction name, data mode and data size
  sprintf(instrstr, "%s%s%s           ", lstext[(type & ARM_THUMB_LOAD_FLAG) >> 16], setext[(type & ARM_THUMB_SIGN_EXTEND) >> 20], dstext[type & ARM_MEMORY_MASK]);
   
  //Print the remainder of the instruction
  sprintf(&instrstr[12], "%s, %s", regnames[rd], op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Print register list
void ThumbPrintRegisterList(ARM_THUMB_INSTRUCTION thumb_instruction, char *ptr)
{
  u_int32_t reglist = thumb_instruction.instr & 0x000000FF;
  int       i;
  
  //Check the register list for which registers need to be printed
  for(i=0;i<16;i++)
  {
    //Check if register included
    if(reglist & 1)
    {
      //Add the register to the list
      ptr += sprintf(ptr, "%s ", regnames[i]);
    }

    //Select next register
    reglist >>= 1;
  }
  
  //Check if pc or sp needs to be included
  switch(thumb_instruction.instr & 0xFE00)
  {
    //Include lr (push)
    case 0xB400:
      ptr += sprintf(ptr, "lr ");
      break;
      
    //Include pc (pop)
    case 0xBC00:
      ptr += sprintf(ptr, "pc ");
      break;
  }

  //Finish the disassembly of this instruction
  sprintf(ptr, "}");
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store multiple instruction handling
void ThumbLSMIA(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  int length;
  
  //Print the instruction name and base register
  length = sprintf(instrstr, "%sia       %s!, ", lsmtext[thumb_instruction.lsm.l], regnames[thumb_instruction.lsm.rn]);
  
  //Point to start of register list space and print it
  ThumbPrintRegisterList(thumb_instruction, &instrstr[length]);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Pop instruction handling
void ThumbPOP(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  int length;
  
  //Print the instruction name and base register
  length = sprintf(instrstr, "pop         { ");
  
  //Point to start of register list space and print it
  ThumbPrintRegisterList(thumb_instruction, &instrstr[length]);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Push instruction handling
void ThumbPUSH(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  int length;
  
  //Print the instruction name and base register
  length = sprintf(instrstr, "push        { ");
  
  //Point to start of register list space and print it
  ThumbPrintRegisterList(thumb_instruction, &instrstr[length]);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Type 2 instructions branch handling
void ThumbBranch2(ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  char * opcode;
  //Check if BLX instruction
  if(thumb_instruction.b2.op2 == 15)
  {
    opcode = "blx";
  }
  else
  {
    opcode = "bx ";
  }

  //Print the instruction name and operands
  sprintf(instrstr, "%s         %s", opcode, regnames[thumb_instruction.b2.rm]);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Type 6 instructions branch handling
void ThumbBranch6(u_int32_t program_counter, ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  int32_t address = thumb_instruction.b6.im << 1;
  
  //Print the instruction name (base name and condition)
  sprintf(instrstr, "b%s             ", condnames[thumb_instruction.b6.cond]);
  
  //Check if negative address given
  if(address & 0x0100)
  {
    //Extend the sign if so
    address |= 0xFFFFFFE00;
  }

  //Calculate the new address. The actual pc point to instruction address plus 4
  program_counter += (4 + address);

  //Add the target address
  sprintf(&instrstr[12], "0x%08X", program_counter);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Type 7 instructions branch handling
void ThumbBranch7(u_int32_t program_counter, ARM_THUMB_INSTRUCTION thumb_instruction, char *instrstr)
{
  u_int32_t  address;
  char      *opcode;

  //Check on unconditional branch
  if(thumb_instruction.b7.op1 == 0)
  {
    //Get the value to index the program counter
    address = thumb_instruction.b7.im << 1;
    
    //Check if negative address given
    if(address & 0x0800)
    {
      //Extend the sign if so
      address |= 0xFFFFFF000;
    }

    //Calculate the new address. The actual pc point to instruction address plus 4
    program_counter += (4 + address);

    //Print the instruction with target address
    sprintf(instrstr, "b           0x%08X", program_counter);
  }
  //Check if this is a branch link prefix instruction
  else if(thumb_instruction.b7.op1 == 2)
  {
    //Setup the prefix address
    address = thumb_instruction.b7.im << 12;
    
    //Check if negative address given
    if(address & 0x00400000)
    {
      //Extend the sign if so
      address |= 0xFF800000;
    }
    
    //Use the link register as temporary storage
    templinkregister = program_counter + 2 + address;
    
    //Print the instruction with target address
    sprintf(instrstr, "bl          0x%08X", templinkregister);
  }
  //Either second BL or BLX instruction
  else
  {
    //Set the program counter to the new address
    program_counter = templinkregister + (thumb_instruction.b7.im << 1);
    
    //Check if it is a BLX(1) instruction
    if(thumb_instruction.b7.op1 == 1)
    {
      opcode = "blx";
    }
    else
    {
      opcode = "bl ";
    }
      
    //Print the instruction with target address
    sprintf(instrstr, "%s         0x%08X", opcode, program_counter);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
