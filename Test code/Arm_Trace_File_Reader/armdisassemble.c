//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "armdisassemble.h"

//----------------------------------------------------------------------------------------------------------------------------------

const char *regnames[16]  = { "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "sp", "lr", "pc" };
const char *condnames[16] = { "eq", "ne", "cs", "cc", "mi", "pl", "vs", "vc", "hi", "ls", "ge", "lt", "gt", "le", "", "" };
const char *signtext[2]   = { "-", "" };
const char *savetext[2]   = { "", "!" };
const char *ictext[2]     = { "", "^" };
const char *shifttext[4]  = { "lsl", "lsr", "asr", "ror" };
const char *lstext[2]     = { "str", "ldr" };
const char *lsmtext[2]    = { "stm", "ldm" };
const char *amtext[4]     = { "da", "db", "ia", "ib" };
const char *dstext[4]     = { "", "h", "b", "d" };
const char *setext[2]     = { "", "s" };
const char *ttext[2]      = { "", "t" };
const char *dprtext[16]   = { "and", "eor", "sub", "rsb", "add", "adc", "sbc", "rsc", "tst", "teq", "cmp", "cmn", "orr", "mov", "bic", "mvn" }; 
const char *bltext[2]     = { "b", "bl" };
const char *mctext[4]     = { "mcr", "mrc", "mcr2", "mrc2" };

//----------------------------------------------------------------------------------------------------------------------------------

void ArmDisassemble(char *instrstr, u_int32_t strsize, u_int32_t program_counter, ARM_INSTRUCTION arm_instruction)
{
  //Need a string pointer and it has to have adequate size
  if((instrstr == NULL) || (strsize < 90))
    return;
  
  //Filter the unconditional instructions
  if(arm_instruction.base.cond == ARM_COND_SPECIAL)
  {
    //Decode the unconditional instructions
    switch(arm_instruction.base.type)
    {
      case 0:
        //Change processor state and set endianness
        //CPS
        //SETEND
        break;

      case 1:
        //Not used
        //???
        break;

      case 2:
      case 3:
        //Cache preload
        //PLD
        break;

      case 4:
        //Save return state and return from exception
        //RFE
        //SRS
        break;

      case 5:
        //Branch with link and change to thumb
        ArmBranchLinkExchange1(program_counter, arm_instruction, instrstr);
        break;

      case 6:
        //Additional coprocessor register transfer
        //MCRR2
        //MRRC2
        //STC2
        //LDC2
        break;

      case 7:
        //Additional coprocessor register transfer and undefined instruction
        //CDP2
        //MCR2
        //MRC2
        break;
    }        
  }
  else
  {
    //Decode the conditional instructions
    switch(arm_instruction.base.type)
    {
      case 0:
        //Check for multiply and extra load and store instructions. Both bit7 and bit4 are set
        if((arm_instruction.type0.it1) && (arm_instruction.type0.it2))
        {
          //Check if Multiplies (type is extended to 4 bits)
          if((arm_instruction.mul.type == 0) && (arm_instruction.mul.nu == 0x09))
          {
            //Handle multiplies (MUL, MULS, MLA, MLAS, UMULL, UMULLS, UMLAL, UMLALS, SMULL, SMULLS, SMLAL, SMLALS)
//            ArmV5tlMUL(core);
          }
          //Check on swap instructions
          else if((arm_instruction.instr & 0x0FB00FF0) == 0x01000090)
          {
            //Handle swaps
//            ArmV5tlUndefinedInstruction(core);
          }
          //Check on load store exclusive (not implemented in V5)
          else if((arm_instruction.instr & 0x0FE00FFF) == 0x01800F9F)
          {
            //Handle load store exclusive
//            ArmV5tlUndefinedInstruction(core);
          }
          //Check if extra load store immediate instructions
          else if(arm_instruction.lsx.i)
          {
            //Handle extra load and store immediate instructions
            ArmLSExtraImmediate(arm_instruction, instrstr);
          }
          //Leaves the extra load store register instructions
          else
          {
            ArmLSExtraRegister(arm_instruction, instrstr);
          }
        }
        //Check for miscellaneous instructions. Bit20 (s) needs to be cleared and opcode bit3 is set and bit2 is cleared (So opcodes 8,9,10 and 11)
        else if((arm_instruction.type0.s == 0) && ((arm_instruction.type0.opcode & 0x0C) == 0x08))
        {
          //Check if move status register instructions
          if(arm_instruction.msrr.sbz == 0)
          {
            //Check if MSR or MRS instruction
            if(arm_instruction.msrr.d)
            {
              //Move register to status register
              ArmMSRRegister(arm_instruction, instrstr);
            }
            else
            {
              //Move status register to register
              ArmMRS(arm_instruction, instrstr);
            }
          }
          else
          {
            //Decode the miscellaneous instructions
            //First check on branch instructions
            if((arm_instruction.misc0.op1 == 1) && ((arm_instruction.misc0.op2 & 0x0C) == 0x00))
            {
              switch(arm_instruction.misc0.op2 & 3)
              {
                case 0:
                  //Undefined instruction
//                  ArmV5tlUndefinedInstruction(core);
                  break;

                case 1:
                  //Branch and exchange instruction set thumb
                  ArmBranchExchangeT(arm_instruction, instrstr);
                  break;

                case 2:
                  //Branch and exchange instruction set java (jazelle)
                  ArmBranchExchangeJ(arm_instruction, instrstr);
                  break;

                case 3:
                  //Branch and link / exchange instruction set thumb
                  ArmBranchLinkExchange2(arm_instruction, instrstr);
                  break;
              }
            }
            else
            {
              //Count leading zeros
              //Saturating add / subtract
              //Software breakpoint
              //Signed multiplies (type 2)
//              ArmV5tlUndefinedInstruction(core);
            }
          }
        }
        else
        {
          //Data processing with shift instructions
          ArmDPRShift(arm_instruction, instrstr);
        }
        
        break;

      case 1:
        //Check for undefined instruction. Bit20 (s) needs to be cleared and opcode bit3 is set and bit2 and bit0 are cleared (So opcodes 8 and 10)
        if((arm_instruction.type1.s == 0) && ((arm_instruction.type1.opcode & 0x0D) == 0x08))
        {
          //Undefined instruction
  //        ArmV5tlUndefinedInstruction(core);
        }
        //Check for move immediate to status register. Bit20 (s) needs to be cleared and opcode bit3 and bit0 are set and bit2 is cleared (So opcodes 9 and 11)
        else if((arm_instruction.type1.s == 0) && ((arm_instruction.type1.opcode & 0x0D) == 0x09))
        {
          //Move immediate to status register
          ArmMSRImmediate(arm_instruction, instrstr);
        }
        else
        {
          //Data processing immediate
          ArmDPRImmediate(arm_instruction, instrstr);
        }
        break;

      case 2:
        //Load / store immediate offset instructions
        ArmLSImmediate(arm_instruction, instrstr);
        break;
        
      case 3:
        //Check for architecturally undefined instruction
        if((arm_instruction.instr & 0x01F000F0) == 0x01F000F0)
        {
          //Architecturally undefined
//          ArmV5tlUndefinedInstruction(core);
        }
        //Check on media instructions. Bit4 needs to be set
        else if(arm_instruction.type3.it1)
        {
          //Media instructions
          //ARMV6 and above
//          ArmV5tlUndefinedInstruction(core);
        }
        else
        {
          //Load / store register offset instructions
          ArmLSRegister(arm_instruction, instrstr);
        }
        break;

      case 4:
        //Load / store multiple instructions
        ArmLSM(arm_instruction, instrstr);
        break;

      case 5:
        //Branch instructions
        ArmBranch(program_counter, arm_instruction, instrstr);
        break;

      case 6:
        //Coprocessor load / store instruction
//        ArmV5tlUndefinedInstruction(core);

        //LDC, MCRR and MRRC instructions
        break;

      case 7:
        //Check if software interrupt
        if(arm_instruction.type7.it2)
        {
          //Software interrupt
//          ArmV5tlUndefinedInstruction(core);
        }
        else
        {
          //Check on coprocessor register transfer or data processing instructions
          if(arm_instruction.type7.it1)
          {
            //Coprocessor register transfer instructions
            ArmMRCMCR(arm_instruction, instrstr);
          }
          else
          {
            //Coprocessor data processing instructions
//            ArmV5tlUndefinedInstruction(core);
            //CDP
          }
        }
        break;
    }        
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store immediate instruction handling
void ArmLSImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Get the input data. Assume target is a word
  u_int32_t mode = ARM_MEMORY_WORD;
  char      op2[32];
  
  //Check on pre or post indexed
  if(arm_instruction.lsi.p == 0)
  {
    //Post indexed ==> [rn], #+/-offset_12
    sprintf(op2, "[%s], #%s%d", regnames[arm_instruction.lsi.rn], signtext[arm_instruction.lsi.u], arm_instruction.lsi.of);
  }
  else
  {
    //Immediate offset or pre-indexed ==> [rn, #+/-offset_12]{!}
    sprintf(op2, "[%s, #%s%d]%s", regnames[arm_instruction.lsi.rn], signtext[arm_instruction.lsi.u], arm_instruction.lsi.of, savetext[arm_instruction.lsi.w]);
  }
  
  //Check if action needs to be done on a byte
  if(arm_instruction.lsi.b)
  {
    //Switch target to byte
    mode = ARM_MEMORY_BYTE;
  }
  
  //Decode the actual instruction
  ArmLS(arm_instruction, mode, instrstr, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store register instruction handling
void ArmLSRegister(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Get the input data. Assume target is a word
  u_int32_t mode = ARM_MEMORY_WORD;
  char      op2[32];
  
  //Check on pre or post indexed
  if(arm_instruction.lsr.p == 0)
  {
    //See if without shift
    if(arm_instruction.lsrn.ns == 0)
    {
      //Post indexed no shift ==> [rn], +/-rm
      sprintf(op2, "[%s], %s%s", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm]);
    }
    else
    {
      //Post indexed shift ==> [rn], +/-rm, shift #shift_imm
      sprintf(op2, "[%s], %s%s, %s #%d", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm], shifttext[arm_instruction.lsr.sm], arm_instruction.lsr.sa);
    }
  }
  else
  {
    //See if without shift
    if(arm_instruction.lsrn.ns == 0)
    {
      //Offset or pre indexed no shift ==> [rn, +/-rm]{!}
      sprintf(op2, "[%s, %s%s]%s", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm], savetext[arm_instruction.lsr.w]);
    }
    else
    {
      //Offset or pre indexed shift ==> [rn], +/-rm, shift #shift_imm
      sprintf(op2, "[%s, %s%s, %s #%d]%s", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm], shifttext[arm_instruction.lsr.sm], arm_instruction.lsr.sa, savetext[arm_instruction.lsr.w]);
    }
  }
   
  //Check if action needs to be done on a byte
  if(arm_instruction.lsr.b)
  {
    //Switch target to byte
    mode = ARM_MEMORY_BYTE;
  }
  
  //Decode the actual instruction
  ArmLS(arm_instruction, mode, instrstr, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store extra immediate instruction handling
void ArmLSExtraImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //The offset is constructed by shifting the high part 4 positions and oring the low part. (rs = immedH, rm = immedL)
  u_int32_t of = (arm_instruction.lsx.rs << 4) | arm_instruction.lsx.rm;
  u_int32_t mode = ARM_MEMORY_WORD;
  char      op2[32];
  
  //Check on pre or post indexed
  if(arm_instruction.lsx.p == 0)
  {
    //Post indexed ==> [rn], #+/-offset_8
    sprintf(op2, "[%s], #%s%d", regnames[arm_instruction.lsx.rn], signtext[arm_instruction.lsx.u], of);
  }
  else
  {
    //Immediate offset or pre-indexed ==> [rn, #+/-offset_8]{!}
    sprintf(op2, "[%s, #%s%d]%s", regnames[arm_instruction.lsx.rn], signtext[arm_instruction.lsx.u], of, savetext[arm_instruction.lsx.w]);
  }
  
  //Check if normal half word instructions
  if(arm_instruction.lsx.op1 == 1)
  {
    //Set mode to short for half word
    mode = ARM_MEMORY_SHORT;
  }
  //Check if sign extend instructions
  else if(arm_instruction.lsx.l)
  {
    //Check if short or byte
    if(arm_instruction.lsx.op1 & 1)
    {
      //Set mode to short for half word
      mode = ARM_MEMORY_SHORT | ARM_SIGN_EXTEND;
    }
    else
    {
      //Set mode to byte
      mode = ARM_MEMORY_BYTE | ARM_SIGN_EXTEND;
    }
  }
  //Leaves the double word instructions
  else
  {
    //Set the load store bit for the handling function to work
    arm_instruction.lsx.l = ~(arm_instruction.lsx.op1 & 1);

    //Set mode to double word
    mode = ARM_MEMORY_DWORD;
  }
  
  //Decode the actual instruction
  ArmLS(arm_instruction, mode, instrstr, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store extra immediate instruction handling
void ArmLSExtraRegister(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Get the input data. Assume target is a word
  u_int32_t mode = ARM_MEMORY_WORD;
  char      op2[32];
  
  //Check on pre or post indexed
  if(arm_instruction.lsx.p == 0)
  {
    //Post indexed ==> [rn], +/-rm
    sprintf(op2, "[%s], %s%s", regnames[arm_instruction.lsx.rn], signtext[arm_instruction.lsx.u], regnames[arm_instruction.lsx.rm]);
  }
  else
  {
    //Offset or pre indexed ==> [rn, +/-rm]{!}
    sprintf(op2, "[%s, %s%s]%s", regnames[arm_instruction.lsx.rn], signtext[arm_instruction.lsx.u], regnames[arm_instruction.lsx.rm], savetext[arm_instruction.lsx.w]);
  }

  //Check if normal half word instructions
  if(arm_instruction.lsx.op1 == 1)
  {
    //Set mode to short for half word
    mode = ARM_MEMORY_SHORT;
  }
  //Check if sign extend instructions
  else if(arm_instruction.lsx.l)
  {
    //Check if short or byte
    if(arm_instruction.lsx.op1 & 1)
    {
      //Set mode to short for half word
      mode = ARM_MEMORY_SHORT | ARM_SIGN_EXTEND;
    }
    else
    {
      //Set mode to byte
      mode = ARM_MEMORY_BYTE | ARM_SIGN_EXTEND;
    }
  }
  //Leaves the double word instructions
  else
  {
    //Set the load store bit for the handling function to work
    arm_instruction.lsx.l = ~(arm_instruction.lsx.op1 & 1);

    //Set mode to double word
    mode = ARM_MEMORY_DWORD;
  }
  
  //Decode the actual instruction
  ArmLS(arm_instruction, mode, instrstr, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store instruction handling
void ArmLS(ARM_INSTRUCTION arm_instruction, u_int32_t mode, char *instrstr, const char *op2)
{
  u_int32_t memtype = mode & ARM_MEMORY_MASK;
  u_int32_t signextend = 0;
  u_int32_t translate = 0;
  
  //Check if sign extend function
  if(mode & ARM_SIGN_EXTEND)
  {
    signextend = 1;
  }
  
  //Print the instruction name (base name, sign extend, data size, translation and condition)
  sprintf(instrstr, "%s%s%s%s%s         ", lstext[arm_instruction.lsr.l], setext[signextend], dstext[memtype], ttext[translate], condnames[arm_instruction.base.cond]);
  
  //Print the remainder of the instruction
  sprintf(&instrstr[12], "%s, %s", regnames[arm_instruction.lsr.rd], op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move immediate to status register
void ArmMSRImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Get the input data
  u_int32_t vm = arm_instruction.msri.im;
  u_int32_t ri = arm_instruction.msri.ri << 1;
  char op2[32];
  
  //Check if rotation is needed
  if(ri)
  {
    //rotate the bits
    vm = (vm >> ri) | (vm << (32 - ri));
  }

  //Setup the immediate operand string
  snprintf(op2, sizeof(op2), "#%d", vm);
   
  //Decode the actual instruction
  ArmMSR(arm_instruction, instrstr, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move register to status register
void ArmMSRRegister(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Decode the actual instruction
  ArmMSR(arm_instruction, instrstr, regnames[arm_instruction.msrr.rm]);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move to status register
void ArmMSR(ARM_INSTRUCTION arm_instruction, char *instrstr, const char *op2)
{
  char cpsrfield[12];
  char *ptr = &cpsrfield[5];

  //Check which register is the destination
  if(arm_instruction.msri.r == 0)
  {
    //target is cpsr
    sprintf(cpsrfield, "cpsr_");
  }
  else
  {
    //Target is spsr
    sprintf(cpsrfield, "spsr_");
  }

  //Fill in the field mask  
  //Control field
  if(arm_instruction.msri.c)
    *ptr++ = 'c';
  
  //Extension field
  if(arm_instruction.msri.x)
    *ptr++ = 'x';
  
  //Status field
  if(arm_instruction.msri.s)
    *ptr++ = 's';
  
  //Flags field
  if(arm_instruction.msri.f)
    *ptr++ = 'f';
  
  //Terminate the string
  *ptr++ = 0;

  //Print the instruction name (base name and condition)
  sprintf(instrstr, "msr%s            ", condnames[arm_instruction.base.cond]);
  
  //Add the cpsr field plus the rest of the operands
  sprintf(&instrstr[12], "%s, %s", cpsrfield, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move status register to register
void ArmMRS(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  char *op2;
  
  //Check if the cpsr or the spsr is the source
  if(arm_instruction.mrs.r == 0)
  {
    op2 = "cpsr";
  }
  else
  {
    op2 = "spsr";
  }

  //Print the instruction name (base name and condition)
  sprintf(instrstr, "mrs%s            ", condnames[arm_instruction.base.cond]);
  
  //Add the rd plus the rest of the operands
  sprintf(&instrstr[12], "%s, %s", regnames[arm_instruction.mrs.rd], op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate and register shift
void ArmDPRShift(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  char op2[32];
 
  //Fill in the register which is used as operand
  sprintf(op2, "%s", regnames[arm_instruction.dpsi.rm]);
  
  //Check if rotate right with extend instruction
  if((arm_instruction.instr & 0x00000FF0) == 0x00000060)
  {
    sprintf(&op2[2], ", rrx");
  }
  //Otherwise check if shifting selected
  else if(arm_instruction.instr & 0x00000FF0)
  {
    sprintf(&op2[2], ", %s ", shifttext[arm_instruction.dpsi.sm]);
    
    //Check if immediate shift or register shift. For immediate shift bit4 is cleared
    if(arm_instruction.type0.it1 == 0)
    {
      //Data processing immediate shift
      sprintf(&op2[8], "#%d", arm_instruction.dpsi.sa);
    }
    else
    {
      //Data processing register shift
      sprintf(&op2[8], "%s", regnames[arm_instruction.dpsr.rs]);
    }
  }
  
  //Go and do the actual decoding
  ArmDPR(arm_instruction, instrstr, op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate
void ArmDPRImmediate(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Get the input data
  u_int32_t vm = arm_instruction.dpi.im;
  u_int32_t ri = arm_instruction.dpi.ri << 1;
  char      op2[32];
  
  //Check if rotation is needed
  if(ri)
  {
    //rotate the bits
    vm = (vm >> ri) | (vm << (32 - ri));
  }

  //Print the operand
  sprintf(op2, "#%d", vm);
  
  //Go and do the actual decoding
  ArmDPR(arm_instruction, instrstr, op2);
}  
  
//----------------------------------------------------------------------------------------------------------------------------------
//Actual data processing handling
void ArmDPR(ARM_INSTRUCTION arm_instruction, char *instrstr, char *op2)
{
  //Print the remainder of the instruction based on it's opcode
  switch(arm_instruction.type0.opcode)
  {
    case ARM_OPCODE_AND:
    case ARM_OPCODE_EOR:
    case ARM_OPCODE_SUB:
    case ARM_OPCODE_RSB:
    case ARM_OPCODE_ADD:
    case ARM_OPCODE_ADC:
    case ARM_OPCODE_SBC:
    case ARM_OPCODE_RSC:
    case ARM_OPCODE_ORR:
    case ARM_OPCODE_BIC:
      //Print the instruction name (base name, condition and status update)
      sprintf(instrstr, "%s%s%s         ", dprtext[arm_instruction.type0.opcode], condnames[arm_instruction.base.cond], setext[arm_instruction.type0.s]);
  
      //These use both rd and rn plus the rest of the operands
      sprintf(&instrstr[12], "%s, %s, %s", regnames[arm_instruction.lsr.rd], regnames[arm_instruction.lsr.rn], op2);
      break;

    case ARM_OPCODE_TST:
    case ARM_OPCODE_TEQ:
    case ARM_OPCODE_CMP:
    case ARM_OPCODE_CMN:
      //Print the instruction name (base name, condition) These instructions always update the status
      sprintf(instrstr, "%s%s          ", dprtext[arm_instruction.type0.opcode], condnames[arm_instruction.base.cond]);
  
      //These use only rn plus the rest of the operands
      sprintf(&instrstr[12], "%s, %s", regnames[arm_instruction.lsr.rn], op2);
      break;

    case ARM_OPCODE_MOV:
    case ARM_OPCODE_MVN:
      //Print the instruction name (base name, condition and status update)
      sprintf(instrstr, "%s%s%s         ", dprtext[arm_instruction.type0.opcode], condnames[arm_instruction.base.cond], setext[arm_instruction.type0.s]);
  
      //These use only rd plus the rest of the operands
      sprintf(&instrstr[12], "%s, %s", regnames[arm_instruction.lsr.rd], op2);
      break;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store multiple instruction handling
void ArmLSM(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  u_int32_t reglist = arm_instruction.instr & 0x0000FFFF;
  int       i;
  int       length;
  char     *ptr;

  //Print the instruction name (base name, direction and condition)
  sprintf(instrstr, "%s%s%s         ", lsmtext[arm_instruction.type4.l], amtext[(arm_instruction.type4.u << 1) | arm_instruction.type4.p], condnames[arm_instruction.base.cond]);

  //Add the base register plus update flag if needed
  length = sprintf(&instrstr[12], "%s%s, { ", regnames[arm_instruction.type4.rn], savetext[arm_instruction.type4.w]) + 12;
  
  //Point to start of register list space
  ptr = &instrstr[length];
  
  //Check the register list for which registers need to be loaded
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

  //Finish the disassembly of this instruction with the possible inclusion of the psr flag
  sprintf(ptr, "}%s", ictext[arm_instruction.type4.s]);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch instructions
void ArmBranch(u_int32_t program_counter, ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  int32_t address = arm_instruction.type5.offset << 2;
  
  //Print the instruction name (base name and condition)
  sprintf(instrstr, "%s%s            ", bltext[arm_instruction.type5.l], condnames[arm_instruction.base.cond]);
  
  //Check if negative address given
  if(address & 0x02000000)
  {
    //Extend the sign if so
    address |= 0xFC000000;
  }

  //Calculate the new address. The actual pc point to instruction address plus 8
  program_counter += (8 + address);

  //Add the target address
  sprintf(&instrstr[12], "0x%08X", program_counter);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with link and exchange instructions
void ArmBranchLinkExchange1(u_int32_t program_counter, ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  int32_t address = arm_instruction.type5.offset << 2;
  
  //Check if negative address given
  if(address & 0x02000000)
  {
    //Extend the sing if so
    address |= 0xFC000000;
  }

  //Merge the H bit into the address (is l bit from type5 instruction)
  address |= (arm_instruction.type5.l << 1);
  
  //Calculate the new address. The actual pc point to instruction address plus 8
  program_counter += (8 + address);

  //Print the instruction name (base name and condition)
  sprintf(instrstr, "blx         0x%08X", program_counter);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with link and exchange instructions
void ArmBranchLinkExchange2(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Print the instruction name (base name and condition)
  sprintf(instrstr, "blx%s             ", condnames[arm_instruction.base.cond]);
  
  //Add the register holding the target  address
  sprintf(&instrstr[12], "%s", regnames[arm_instruction.misc0.rm]);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with exchange instructions
void ArmBranchExchangeT(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Print the instruction name (base name and condition)
  sprintf(instrstr, "bx%s              ", condnames[arm_instruction.base.cond]);
  
  //Add the register holding the target  address
  sprintf(&instrstr[12], "%s", regnames[arm_instruction.misc0.rm]);
}

//----------------------------------------------------------------------------------------------------------------------------------

//Handle branch with exchange instructions
void ArmBranchExchangeJ(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  //Print the instruction name (base name and condition)
  sprintf(instrstr, "bxj%s             ", condnames[arm_instruction.base.cond]);
  
  //Add the register holding the target  address
  sprintf(&instrstr[12], "%s", regnames[arm_instruction.misc0.rm]);
}

/*
//----------------------------------------------------------------------------------------------------------------------------------
//Multiply instruction handling
//MUL, MULS, MLA, MLAS, UMULL, UMULLS, UMLAL, UMLALS, SMULL, SMULLS, SMLAL, SMLALS  
void ArmV5tlMUL(PARMV5TL_CORE core)
{
  u_int32_t rm = *registers[current_bank][arm_instruction.mul.rm];
  u_int32_t rs = *registers[current_bank][arm_instruction.mul.rs];
  int64_t vd;
  int64_t va;
  
  //Check if signed or unsigned multiply needed (SMULL op1:6, SMLAL op1:7)
  if((arm_instruction.mul.op1 == 6) || (arm_instruction.mul.op1 == 7))
  {
    //Do multiply with signed inputs
    vd = (int32_t)rs * (int32_t)rm;
  }
  else
  {
    //Do multiply with unsigned inputs
    vd = rs * rm;
  }
  
  //Check if 64 bit accumulate needed (UMLAL op1:5, SMLAL op1:7)
  if((arm_instruction.mul.op1 == 5) || (arm_instruction.mul.op1 == 7))
  {
    //Get the value to add from the two destination registers. rd holds high part, rn holds low part.
    va  = (u_int64_t)*registers[current_bank][arm_instruction.mul.rd] << 32;
    va |= *registers[current_bank][arm_instruction.mul.rn];
    
    //Do the summation
    vd += va;
  }
  //Check if 32 bit accumulation needed (MLA op1:1)
  else if(arm_instruction.mul.op1 == 1)
  {
    //Add the value held in rn to the result
    vd += *registers[current_bank][arm_instruction.mul.rn];
  }
  
  //Check if 32 bit result instruction (MUL op1:0, MLA op1:1)
  if((arm_instruction.mul.op1 == 0) || (arm_instruction.mul.op1 == 1))
  {
    //Store the 32 bit result back to rd
    *registers[current_bank][arm_instruction.mul.rd] = (u_int32_t)vd;
    
    //Check if status flags need to be updated
    if(arm_instruction.mul.s)
    {
        //Update the negative bit
        status->flags.N = (vd >> 31) & 1;

        //Update the zero bit (only the lower 32 bits count)
        status->flags.Z = ((vd & 0xFFFFFFFF) == 0);
    }
  }
  //Leaves 64 bit result instructions
  else
  {
    //Store the 64 bit result back to register pair. rd holds high part, rn holds low part.
    *registers[current_bank][arm_instruction.mul.rd] = (u_int32_t)(vd >> 32);
    *registers[current_bank][arm_instruction.mul.rn] = (u_int32_t)vd;
    
    //Check if status flags need to be updated
    if(arm_instruction.mul.s)
    {
        //Update the negative bit
        status->flags.N = (vd >> 63) & 1;

        //Update the zero bit (only the lower 32 bits count)
        status->flags.Z = (vd == 0);
    }
  }
}
*/

//----------------------------------------------------------------------------------------------------------------------------------
//Move register to coprocessor or coprocessor to register
void ArmMRCMCR(ARM_INSTRUCTION arm_instruction, char *instrstr)
{
  int in = arm_instruction.mrcmcr.d;
  
  //Check if mcr2 or mrc2 instructions
  if(arm_instruction.base.cond == 15)
  {
    in |= 0x02;
  }
    
  //Print the instruction name (base name and condition)
  sprintf(instrstr, "%s%s             ", mctext[in], condnames[arm_instruction.base.cond]);

  //Add the register holding the target  address
  sprintf(&instrstr[12], "p%d, %d, %s, cr%d, cr%d, %d", arm_instruction.mrcmcr.cpn, arm_instruction.mrcmcr.op1, regnames[arm_instruction.mrcmcr.rd], arm_instruction.mrcmcr.crn, arm_instruction.mrcmcr.crm, arm_instruction.mrcmcr.op2);
}

//----------------------------------------------------------------------------------------------------------------------------------
