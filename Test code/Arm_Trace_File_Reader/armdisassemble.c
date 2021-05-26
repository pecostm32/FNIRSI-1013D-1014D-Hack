//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "armdisassemble.h"

//----------------------------------------------------------------------------------------------------------------------------------

const char *regnames[16] = 
{
  "r0",
  "r1",
  "r2",
  "r3",
  "r4",
  "r5",
  "r6",
  "r7",
  "r8",
  "r9",
  "r10",
  "r11",
  "r12",
  "sp",
  "lr",
  "pc"
};

const char *condnames[16] = 
{
  "eq",
  "ne",
  "cs",
  "cc",
  "mi",
  "pl",
  "vs",
  "vc",
  "hi",
  "ls",
  "ge",
  "lt",
  "gt",
  "le",
  "  ",
  "  "
};

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlDisassemble(char *instrstr, u_int32_t strsize, ARM_INSTRUCTION arm_instruction)
{
  u_int32_t idx = 0;
  
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
        //This one is actually used!!!!!!!
        //BLX
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
//                  ArmV5tlBranchExchangeT(core);
                  break;

                case 2:
                  //Branch and exchange instruction set java (jazelle)
                  //ArmV5tlBranchExchangeJ(core);
//                  ArmV5tlUndefinedInstruction(core);
                  break;

                case 3:
                  //Branch and link / exchange instruction set thumb
//                  ArmV5tlBranchLinkExchange2(core);
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
//          ArmV5tlDPRShift(core);
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
  //        ArmV5tlDPRImmediate(core);
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
//        ArmV5tlLSM(core);
        break;

      case 5:
        //Branch instructions
//        ArmV5tlBranch(core);
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
//            ArmV5tlMRCMCR(core);
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

const char signtext[2][2]  = { "-", "" };
const char savetext[2][2]  = { "", "!" };
const char shifttext[4][4] = { "lsl", "lsr", "asr", "ror" };
const char lstext[2][4]    = { "str", "ldr" };
const char dstext[4][2]    = { "", "h", "b", "d" };
const char setext[2][2]    = { "", "s" };
const char ttext[2][2]     = { "", "t" };

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
      sprintf(op2, "[%s], #%s%s", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm]);
    }
    else
    {
      //Post indexed shift ==> [rn], +/-rm, shift #shift_imm
      sprintf(op2, "[%s], #%s%s, %s #%d", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm], shifttext[arm_instruction.lsr.sm], arm_instruction.lsr.sa);
    }
  }
  else
  {
    //See if without shift
    if(arm_instruction.lsrn.ns == 0)
    {
      //Offset or pre indexed no shift ==> [rn, +/-rm]{!}
      sprintf(op2, "[%s, #%s%s]%s", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm], savetext[arm_instruction.lsr.w]);
    }
    else
    {
      //Offset or pre indexed shift ==> [rn], +/-rm, shift #shift_imm
      sprintf(op2, "[%s, #%s%s, %s #%d]%s", regnames[arm_instruction.lsr.rn], signtext[arm_instruction.lsr.u], regnames[arm_instruction.lsr.rm], shifttext[arm_instruction.lsr.sm], arm_instruction.lsr.sa, savetext[arm_instruction.lsr.w]);
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
    sprintf(op2, "[%s], #%s%s", regnames[arm_instruction.lsx.rn], signtext[arm_instruction.lsx.u], regnames[arm_instruction.lsx.rm]);
  }
  else
  {
    //Offset or pre indexed ==> [rn, +/-rm]{!}
    sprintf(op2, "[%s, #%s%s]%s", regnames[arm_instruction.lsx.rn], signtext[arm_instruction.lsx.u], regnames[arm_instruction.lsx.rm], savetext[arm_instruction.lsx.w]);
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

  //Print the instruction
  sprintf(instrstr, "msr%s       %s, %s", condnames[arm_instruction.base.cond], cpsrfield, op2);
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

  sprintf(instrstr, "mrs%s       %s, %s", condnames[arm_instruction.base.cond], regnames[arm_instruction.mrs.rd], op2);
}

/*  

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate and register shift
void ArmV5tlDPRShift(PARMV5TL_CORE core)
{
  //Get the input data
  u_int32_t vm = *registers[current_bank][arm_instruction.dpsi.rm];
  u_int32_t vn = *registers[current_bank][arm_instruction.dpsi.rn];
  u_int32_t sa;
  u_int32_t c = status->flags.C;

  //Amend the values when r15 (pc) is used
  if(arm_instruction.dpsi.rn == 15)
  {
    vn += 8;
  }

  //Same for the to be shifted register
  if(arm_instruction.dpsi.rm == 15)
  {
    vm += 8;
  }
  
  //Check if immediate shift or register shift. For immediate shift bit4 is cleared
  if(arm_instruction.type0.it1 == 0)
  {
    //Data processing immediate shift
    //Get the immediate shift amount
    sa = arm_instruction.dpsi.sa;
  }
  else
  {
    //Data processing register shift
    //Get the register shift amount.
    sa = *registers[current_bank][arm_instruction.dpsr.rs] & 0x000000FF;
  }
  
  //Take action based on the shift mode
  switch(arm_instruction.dpsi.sm)
  {
    case ARM_SHIFT_MODE_LSL:
      if((sa > 0) && (sa < 32))
      {
        //When the shift is less then 32 the carry is the last bit shifted out and vm is shifted sa times
        c = (vm >> (32 - sa)) & 1;
        vm <<= sa;
      }
      else if(sa == 32)
      {
        //When the shift is 32 the carry is bit0 of vm and vm is set to zero
        c = vm & 1;
        vm = 0;
      }
      else if(sa > 32)
      {
        //when shifting is more then 32 both carry and vm are set to zero
        c = 0;
        vm = 0;
      }
      break;
      
    case ARM_SHIFT_MODE_LSR:
      if(sa == 0)
      {
        //Check on immediate or register shift
        if(arm_instruction.type0.it1 == 0)
        {
          //In immediate mode shifter 0 equals to 32
          c = vm >> 31;
          vm = 0;
        }
      }
      else if(sa < 32)
      {
        //When the shift is less then 32 the carry is the last bit shifted out and vm is shifted sa times
        c = (vm >> (sa - 1)) & 1;
        vm >>= sa;
      }
      else if(sa == 32)
      {
        //When the shift is 32 the carry is bit0 of vm and vm is set to zero
        c = vm >> 31;
        vm = 0;
      }
      else
      {
        //when shifting is more then 32 both carry and vm are set to zero
        c = 0;
        vm = 0;
      }
      break;
      
    case ARM_SHIFT_MODE_ASR:
      if(sa == 0)
      {
        //Check on immediate or register shiftPARMV5TL_STATUS
        if(arm_instruction.type0.it1 == 0)
        {
          //In immediate mode shifter 0 equals to 32
          c = vm >> 31;
          
          //Check if sign bit is cleared
          if(c == 0)
          {
            vm = 0;
          }
          else
          {
            vm = 0xFFFFFFFF;
          }
        }
      }
      else if(sa < 32)
      {
        //When the shift is less then 32 the carry is the last bit shifted out and vm is shifted sa times
        c = (vm >> (sa - 1)) & 1;
        
        if((vm & 0x80000000) == 0)
        {
          vm >>= sa;
        }
        else
        {
          vm = ~(~vm >> sa);
        }
      }
      else if(sa == 32)
      {
        //When the shift is 32 the carry is bit0 of vm and vm is set to zero
        c = vm >> 31;
        
        if(c == 0)
        {
          vm = 0;
        }
        else
        {
          vm = 0xFFFFFFFF;
        }
      }
      else
      {
        //when shifting is more then 32 both carry and vm are set to zero
        c = 0;
        vm = 0;
      }
      break;
      
    case ARM_SHIFT_MODE_ROR:
      if(sa == 0)
      {
        //Check on immediate or register shift
        if(arm_instruction.type0.it1 == 0)
        {
          //Special case here where the shift amount is 0. Rotate right with extend. Carry is an extra bit
          c = vm & 1;
          vm = (status->flags.C << 31) | (vm >> 1);
        }
      }
      else if((sa & 0x1F) == 0)
      {
        //When only the lowest 5 bits are zero the carry is bit31
        c = vm >> 31;
      }
      else
      {
        //Make sure upper bits of the number of rotates are cleared
        sa &= 0x1F;
        
        //Get the carry
        c = (vm >> (sa - 1)) & 1;
        
        //rotate the bits
        vm = (vm >> sa) | (vm << (32 - sa));
      }
      break;
  }
  
  //Go and do the actual processing
  ArmV5tlDPR(core, vn, vm, c);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate
void ArmV5tlDPRImmediate(PARMV5TL_CORE core)
{
  //Get the input data
  u_int32_t vm = arm_instruction.dpi.im;
  u_int32_t vn = *registers[current_bank][arm_instruction.dpsi.rn];
  u_int32_t ri = arm_instruction.dpi.ri << 1;
  u_int32_t c = status->flags.C;
  
  //Amend the operand value when r15 (pc) is used
  if(arm_instruction.dpsi.rn == 15)
  {
    vn += 8;
  }
  
  //Check if rotation is needed
  if(ri)
  {
    //rotate the bits
    vm = (vm >> ri) | (vm << (32 - ri));

    //Get the carry if so
    c = vm >> 31;
  }
  
  //Go and do the actual processing
  ArmV5tlDPR(core, vn, vm, c);
}  
  
//----------------------------------------------------------------------------------------------------------------------------------
//Actual data processing handling
void ArmV5tlDPR(PARMV5TL_CORE core, u_int32_t vn, u_int32_t vm, u_int32_t c)
{
  u_int64_t vd;
  u_int32_t update = 1;
  u_int32_t docandv = ARM_FLAGS_UPDATE_CV_NO;
  
  //Perform the correct action based on the opcode
  switch(arm_instruction.type0.opcode)
  {
    case ARM_OPCODE_AND:
      vd = vn & vm;
      break;
      
    case ARM_OPCODE_EOR:
      vd = vn ^ vm;
      break;

    case ARM_OPCODE_SUB:
      vd = (int64_t)vn - (int64_t)vm;
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_NBV;
      break;

    case ARM_OPCODE_RSB:
      vd = (int64_t)vm - (int64_t)vn;
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_NBV;
      break;

    case ARM_OPCODE_ADD:
      vd = (int64_t)vn + (int64_t)vm;
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_CV;
      break;

    case ARM_OPCODE_ADC:
      vd = (int64_t)vn + (int64_t)vm + status->flags.C;
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_CV;
      break;

    case ARM_OPCODE_SBC:
      vd = (int64_t)vn - (int64_t)vm - (status->flags.C ^ 1);
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_NBV;
      break;

    case ARM_OPCODE_RSC:
      vd = (int64_t)vm - (int64_t)vn - (status->flags.C ^ 1);
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_NBV;
      break;

    case ARM_OPCODE_TST:
      vd = vn & vm;
      
      //Do not update the destination register
      update = 0;
      break;

    case ARM_OPCODE_TEQ:
      vd = vn ^ vm;
      
      //Do not update the destination register
      update = 0;
      break;

    case ARM_OPCODE_CMP:
      vd = (int64_t)vn - (int64_t)vm;
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_NBV;

      //Do not update the destination register
      update = 0;
      break;

    case ARM_OPCODE_CMN:
      vd = (int64_t)vn + (int64_t)vm;
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_CV;

      //Do not update the destination register
      update = 0;
      break;

    case ARM_OPCODE_ORR:
      vd = vn | vm;
      break;

    case ARM_OPCODE_MOV:
      vd = vm;
      break;

    case ARM_OPCODE_BIC:
      vd = vn & ~vm;
      break;

    case ARM_OPCODE_MVN:
      vd = ~vm;
      break;
  }
  
  //Check if program status register needs to be updated
  if(arm_instruction.type0.s)
  {
    //Check if destination register needs to be updated, is r15 (pc) and the current mode has a saved program status register
    if((update) && (arm_instruction.dpsi.rd == 15) && (registers[current_bank][ARM_REG_SPSR_IDX]))
    {
      //Load the current status with the saved one if it is available
      status->word = *registers[current_bank][ARM_REG_SPSR_IDX];
      
      //Adjust the current processor state accordingly
      current_mode = status->flags.M;

      //Select the corresponding register bank
      switch(status->flags.M)
      {
        case ARM_MODE_USER:
          current_bank = ARM_REG_BANK_USER;
          break;
          
        case ARM_MODE_FIQ:
          current_bank = ARM_REG_BANK_FIQ;
          break;
          
        case ARM_MODE_IRQ:
          current_bank = ARM_REG_BANK_IRQ;
          break;
          
        case ARM_MODE_SUPERVISOR:
          current_bank = ARM_REG_BANK_SUPERVISOR;
          break;
          
        case ARM_MODE_ABORT:
          current_bank = ARM_REG_BANK_ABORT;
          break;
          
        case ARM_MODE_UNDEFINED:
          current_bank = ARM_REG_BANK_UNDEFINED;
          break;
          
        case ARM_MODE_SYSTEM:
          current_bank = ARM_REG_BANK_SYSTEM;
          break;
      }
    }
    else
    {
      //Update the negative bit
      status->flags.N = (vd >> 31) & 1;

      //Update the zero bit (only the lower 32 bits count)
      status->flags.Z = ((vd & 0xFFFFFFFF) == 0);

      //Check if carry and overflow need to be updated with arithmetic result
      if(docandv != ARM_FLAGS_UPDATE_CV_NO)
      {
        //Handle the carry and overflow according to type of arithmetic
        if(docandv == ARM_FLAGS_UPDATE_CV)
        {
          //Update the overflow bit for additions. When inputs have equal signs the sign of the output should remain the same as the inputs, otherwise there is an overflow
          status->flags.V = (((vn & 0x80000000) == (vm & 0x80000000)) && (vn & 0x80000000) != (vd & 0x80000000));
          
          //Carry from addition.
          status->flags.C = vd >> 32;
        }
        else
        {
          //Update the overflow bit for subtractions. When inputs not have equal signs the sign of the output should be the same as that of the first operand, otherwise there is an overflow
          status->flags.V = (((vn & 0x80000000) != (vm & 0x80000000)) && (vn & 0x80000000) != (vd & 0x80000000));
          
          //Not borrow from subtraction
          status->flags.C = (vd <= 0xFFFFFFFF);
        }
      }
      else
      {
        //When not the carry is the shifter output
        status->flags.C = c;
      }
    }
  }
  
  //Check if destination register needs to be updated
  if(update)
  {
    //Write the result back as a singed 32 bit integer
    *registers[current_bank][arm_instruction.dpsi.rd] = (int32_t)vd;
    
    //Check if program counter used as target
    if(arm_instruction.lsr.rd == 15)
    {
      //Signal no increment if so
      pcincrvalue = 0;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store multiple instruction handling
void ArmV5tlLSM(PARMV5TL_CORE core)
{
  u_int32_t address = *registers[current_bank][arm_instruction.type4.rn];
  u_int32_t traceaddress;
  u_int32_t *memory;
  u_int32_t reglist = arm_instruction.instr & 0x0000FFFF;
  int       numregs = 0;
  int       bank = current_bank;
  int       i;
  
  //Check if S bit is set. Needed to determine which register bank is used.
  if(arm_instruction.type4.s)
  {
    //Check if r15 is included in the list and it is a load instruction
    if((arm_instruction.type4.r15) && (arm_instruction.type4.l))
    {
      //Need to restore cpsr from spsr
      //Check if there is a saved status register for the current register bank
      if(registers[current_bank][ARM_REG_SPSR_IDX])
      {
        //Copy the spsr if available
        *registers[current_bank][arm_instruction.mrs.rd] = *registers[current_bank][ARM_REG_SPSR_IDX];
      }
      
      //Handle the possible mode change
      //Adjust the current processor state accordingly
      current_mode = status->flags.M;

      //Select the corresponding register bank
      switch(status->flags.M)
      {
        case ARM_MODE_USER:
          current_bank = ARM_REG_BANK_USER;
          break;

        case ARM_MODE_FIQ:
          current_bank = ARM_REG_BANK_FIQ;
          break;

        case ARM_MODE_IRQ:
          current_bank = ARM_REG_BANK_IRQ;
          break;

        case ARM_MODE_SUPERVISOR:
          current_bank = ARM_REG_BANK_SUPERVISOR;
          break;

        case ARM_MODE_ABORT:
          current_bank = ARM_REG_BANK_ABORT;
          break;

        case ARM_MODE_UNDEFINED:
          current_bank = ARM_REG_BANK_UNDEFINED;
          break;

        case ARM_MODE_SYSTEM:
          current_bank = ARM_REG_BANK_SYSTEM;
          break;
      }
    }
    else
    {
      //For all stores and the loads without r15 the user mode registers are used
      bank = ARM_REG_BANK_USER;
    }
  }
  
  //Check if base address not included in the range (Increment / decrement before)
  if(arm_instruction.type4.p)
  {
    //Not includes so check if range is below or above the base address
    if(arm_instruction.type4.u)
    {
      //Below so add to the base address
      address += 4;
    }
    else
    {
      //Above so subtract from the base address
      address -= 4;
    }
  }
  
  //Set the trace address
  traceaddress = address;
  
  //Lowest register needs to be in lowest address, so list is walked through different for increment or decrement
  //Check if increment or decrement
  if(arm_instruction.type4.u)
  {
    //Check the register list for which registers need to be loaded
    for(i=0;i<16;i++)
    {
      //Check if register included
      if(reglist & 1)
      {
        //Get the pointer for this address        
        memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_WORD);
        
        //Check if valid memory found
        if(memory)
        {
          //Check if load or store
          if(arm_instruction.type4.l)
          {
            //Check if peripheral read function set for this address
            if(periph_read_func)
            {
              //Call it if so
              periph_read_func(core, address, ARM_MEMORY_WORD);
            }

            //Load the register with the data from memory
            *registers[bank][i] = *memory;
          }
          else
          {
            //Store the register to memory
            *memory = *registers[bank][i];
            
            //Check if peripheral write function set for this address
            if(periph_write_func)
            {
              //Call it if so
              periph_write_func(core, address, ARM_MEMORY_WORD);
            }
          }
        }
        else
        {
          //Signal a data abort exception  
        }
        
        //Select the next address
        address += 4;

        //Add one to the number of registers loaded
        numregs++;
      }
        
      //Select next register
      reglist >>= 1;
    }
  }
  else
  {
    //Check the register list for which registers need to be loaded
    for(i=15;i>=0;i--)
    {
      //Check if register included
      if(reglist & 0x00008000)
      {
        //Get the pointer for this address        
        memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_WORD);
        
        //Check if valid memory found
        if(memory)
        {
          //Check if load or store
          if(arm_instruction.type4.l)
          {
            //Check if peripheral read function set for this address
            if(periph_read_func)
            {
              //Call it if so
              periph_read_func(core, address, ARM_MEMORY_WORD);
            }

            //Load the register with the data from memory
            *registers[bank][i] = *memory;
          }
          else
          {
            //Store the register to memory
            *memory = *registers[bank][i];
            
            //Check if peripheral write function set for this address
            if(periph_write_func)
            {
              //Call it if so
              periph_write_func(core, address, ARM_MEMORY_WORD);
            }
          }
        }
        else
        {
          //Signal a data abort exception  
        }
        
        //Select the next address
        address -= 4;

        //Add one to the number of registers loaded
        numregs++;
      }

      //Select next register
      reglist <<= 1;
    }
  }

  //Check if base register needs to be updated
  if(arm_instruction.type4.w)
  {
    //Check if increment or decrement
    if(arm_instruction.type4.u)
    {
      //Increment the base address
      *registers[current_bank][arm_instruction.type4.rn] += (numregs * 4);
    }
    else
    {
      //Decrement the base address
      *registers[current_bank][arm_instruction.type4.rn] -= (numregs * 4);
    }
  }
  
  //Check if r15 is included in the list and it is a load instruction
  if((arm_instruction.type4.r15) && (arm_instruction.type4.l))
  {
    //Check if thumb state bit needs to be updated
    if(arm_instruction.type4.s == 0)
    {
      //When s == 1 this is already done by restoring cpsr from spsr. For s == 0 it needs to be taken from the pc
      status->flags.T = *program_counter & 1;
    }
    
    //Make sure the program counter is not on an invalid byte boundary
    *program_counter &= 0xFFFFFFFE;
    
    //Signal no increment of pc if so
    pcincrvalue = 0;
  }
  
  //Check if tracing into buffer is enabled.
  if(tracebufferenabled)
  {
    //Set the data in the trace buffer
    ArmV5tlSetMemoryTraceData(core, traceaddress, ARM_MEMORY_WORD, numregs, arm_instruction.type4.u);
  }
}

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


//----------------------------------------------------------------------------------------------------------------------------------
//Move register to coprocessor or coprocessor to register
void ArmV5tlMRCMCR(PARMV5TL_CORE core)
{
//  u_int32_t cpn = arm_instruction.mrcmcr.cpn;
//  u_int32_t crm = arm_instruction.mrcmcr.crm;
//  u_int32_t crn = arm_instruction.mrcmcr.crn;
  
  //For now only coprocessor 15 read is implemented
  if((arm_instruction.mrcmcr.cpn == 15) && (arm_instruction.mrcmcr.d))
  {
    //Clear destination register to indicate MMU is disabled and vectors are in low memory
    *registers[current_bank][arm_instruction.mrcmcr.rd] = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch instructions
void ArmV5tlBranch(PARMV5TL_CORE core)
{
  int32_t address = arm_instruction.type5.offset << 2;
  
  //Check if negative address given
  if(address & 0x02000000)
  {
    //Extend the sign if so
    address |= 0xFC000000;
  }
  
  //Check if link register needs to be set
  if(arm_instruction.type5.l)
  {
    //Load the address after this instruction to the link register r14
    *registers[current_bank][14] = *program_counter + 4;
  }

  //Calculate the new address. The actual pc point to instruction address plus 8
  *program_counter += (8 + address);

  //Signal no increment of the pc
  pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with link and exchange instructions
void ArmV5tlBranchLinkExchange1(PARMV5TL_CORE core)
{
  int32_t address = arm_instruction.type5.offset << 2;
  
  //Check if negative address given
  if(address & 0x02000000)
  {
    //Extend the sing if so
    address |= 0xFC000000;
  }
  
  //Load the address after this instruction to the link register r14
  *registers[current_bank][14] = *program_counter + 4;

  //Merge the H bit into the address (is l bit from type5 instruction)
  address |= (arm_instruction.type5.l << 1);
  
  //Calculate the new address. The actual pc point to instruction address plus 8
  *program_counter += (8 + address);

  //Signal the processor to continue in thumb state
  status->flags.T = 1;
  
  //Signal no increment of the pc
  pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with link and exchange instructions
void ArmV5tlBranchLinkExchange2(PARMV5TL_CORE core)
{
  u_int32_t address = *registers[current_bank][arm_instruction.misc0.rm];
  
  //Load the address after this instruction to the link register r14
  *registers[current_bank][14] = *program_counter + 4;

  //Set the new address. Needs to be on a thumb boundary
  *program_counter = address & 0xFFFFFFFE;

  //Signal the processor to continue in either thumb or arm state
  status->flags.T = address & 1;
  
  //Signal no increment of the pc
  pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with exchange instructions
void ArmV5tlBranchExchangeT(PARMV5TL_CORE core)
{
  u_int32_t address = *registers[current_bank][arm_instruction.misc0.rm];
  
  //Set the new address. Needs to be on a thumb boundary
  *program_counter = address & 0xFFFFFFFE;

  //Signal the processor to continue in either thumb or arm state
  status->flags.T = address & 1;
  
  //Signal no increment of the pc
  pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

//Handle branch with exchange instructions
void ArmV5tlBranchExchangeJ(PARMV5TL_CORE core)
{
  u_int32_t address = *registers[current_bank][arm_instruction.misc0.rm];
  
  //This is not correct and needs system info to do the correct things
  
  //Set the new address. Needs to be on a thumb boundary
  *program_counter = address & 0xFFFFFFFE;

  //Signal the processor to continue in either jazelle or arm state
  status->flags.J = address & 1;
  
  //Signal no increment of the pc
  pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
*/