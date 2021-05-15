//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "armv5tl_thumb.h"

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlHandleThumb(PARMV5TL_CORE core)
{
  u_int16_t *memorypointer;

  //Instruction fetch for thumb state
  memorypointer = (u_int16_t *)ArmV5tlGetMemoryPointer(core, *core->program_counter, ARM_MEMORY_SHORT);

  //Check if a valid address is found
  if(memorypointer)
  {
    //get the current instruction
    core->thumb_instruction.instr = (u_int16_t)*memorypointer;
    
    //Decode based on the type bits
    switch(core->thumb_instruction.base.type)
    {
      case 0:
        //Check on instruction opcode
        if(core->thumb_instruction.base.op1 == 3)
        {
          //op1:3 ADD(3), SUB(3), ADD(1), MOV(2), SUB(1)
          ArmV5tlThumbDP0(core);
        }
        else
        {
          //LSL(1) op1:0, LSR(1) op1:1, ASR(1) op1:2
          ArmV5tlThumbShiftImmediate(core);
        }
        break;

      case 1:
        //MOV(1), CMP(1), ADD(2), SUB(2)
        ArmV5tlThumbDP1(core);
        break;

      case 2:
        //Check if data processing or load / store instructions
        if(core->thumb_instruction.base.op1 == 0)
        {
          //Separate the shift instructions
          if((core->thumb_instruction.base.op2 == 2) || (core->thumb_instruction.base.op2 == 3) || (core->thumb_instruction.base.op2 == 4) || (core->thumb_instruction.base.op2 == 7))
          {
            //LSL(2) op2:2, LSR(2) op2:3, ASR(2) op2:4, ROR op2:7
            ArmV5tlThumbShiftRegister(core);
          }
          //Get the other data processing functions except CMP(3), ADD(4), CPY and MOV(3)
          else if(core->thumb_instruction.base.op2 < 16)
          {
            //AND, EOR, ADC, SBC, TST, NEG, CMP(2), CMN, OR, BIC, MVN, MUL
            ArmV5tlThumbDP2(core);
          }
          //Filter out the branch instructions
          else if((core->thumb_instruction.base.op2 & 0x1C) == 0x1C)
          {
            //BLX(2), BX
            ArmV5tlThumbBranch2(core);
          }
          //The remainder are the special data processing functions
          else
          {
            //CMP(3), ADD(4), CPY and MOV(3)
            ArmV5tlThumbDP2S(core);
          }
        }
        //Filter out the load immediate indexed instruction LDR(3)
        else if(core->thumb_instruction.base.op1 == 1)
        {
          //LDR(3)
          ArmV5tlThumbLS2I(core);
        }
        else
        {
          //STR(2), STRH(2), STRB(2), LDR(2), LDRH(2), LDRB(2), LDRSB, LDRSH          
          ArmV5tlThumbLS2R(core);
        }
        break;

      case 3:
        //STR(1), LDR(1), STRB(1), LDRB(1)
        ArmV5tlThumbLS3(core);
        break;

      case 4:
        //Check if load / store short immediate offset
        if((core->thumb_instruction.base.op1 & 2) == 0)
        {
          //STRH(1), LDRH(1) (instruction decoding basically the same as type 3 so using same function here. Type 4 indicates short)
          ArmV5tlThumbLS3(core);
        }
        //Load / store to / from stack
        else
        {
          //STR(3), LDR(4)
          ArmV5tlThumbLS4(core);
        }
        break;

      case 5:
        //Filter out the add pc, sp plus immediate instructions
        if((core->thumb_instruction.base.op1 & 2) == 0)
        {
        //ADD(5)   101 00 ddd iiiiiiii
        //ADD(6)   101 01 ddd iiiiiiii
          ArmV5tlUndefinedInstruction(core);

        }
        //Filter out the ADD(7) and SUB(4) instructions
        else if((core->thumb_instruction.base.op2 & 0x1C) == 0)
        {
        //ADD(7)   101 10 0000 iiiiiii
        //SUB(4)   101 10 0001 iiiiiii
          ArmV5tlUndefinedInstruction(core);
          
        }
        //Filter out POP and PUSH
        else if((core->thumb_instruction.base.op2 & 0x18) == 0x10)
        {
          //POP, PUSH. base register is sp (13) and bit 2 of op2 signals that the program counter or link register is included in the list
          if(core->thumb_instruction.base.op1 == 2)
          {
            //op1:2 is PUSH
            ArmV5tlThumbPUSH(core);
          }
          else
          {
            //op1:3 is POP
            ArmV5tlThumbPOP(core);
          }
        }
        //Filter out the REV and XT instructions
        else if((core->thumb_instruction.base.op2 & 0x18) == 0x08)
        {
        //REV      101 11 01000 nnn ddd
        //REV16    101 11 01001 nnn ddd
        //REVSH    101 11 01011 nnn ddd

        //SXTB     101 10 01001 mmm ddd
        //SXTH     101 10 01000 mmm ddd
        //UXTB     101 10 01011 mmm ddd
        //UXTH     101 10 01010 mmm ddd
          ArmV5tlUndefinedInstruction(core);
          
        }
        //Leaves the BKPT, CPS and SETEND
        else
        {
        //BKPT     101 11 110 iiiiiiii
        
        //CPS      101 10 1100 11 m 0 a i f
        
        //SETEND   101 10 11001 01 e zzz
        
          ArmV5tlUndefinedInstruction(core);
          
        }
        break;

      case 6:
        //Filter out the load and store multiple instructions
        if(core->thumb_instruction.b6.op1 == 0)
        {
          //STMIA, LDMIA
          ArmV5tlThumbLSMIA(core);
        }
        else
        {
          //Filter out undefined instruction
          if(core->thumb_instruction.b6.cond == 14)
          {
            //UI
            ArmV5tlUndefinedInstruction(core);
          }
          //Filter out software interrupt
          else if(core->thumb_instruction.b6.cond == 15)
          {
            //SWI   110 1 1111 iiiiiiii
            ArmV5tlUndefinedInstruction(core);
          }
          //Leaves conditional branches
          else
          {
            //B(1)
            ArmV5tlThumbBranch6(core);
          }
        }
        break;

      case 7:
        //B(2), BLX(1), BL
        ArmV5tlThumbBranch7(core);
        break;
    }
  }
  //No memory at current program address
  else
  {
    //Some exception needs to be generated here. Undefined Instruction most likely
    ArmV5tlUndefinedInstruction(core);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Immediate shift
void ArmV5tlThumbShiftImmediate(PARMV5TL_CORE core)
{
  u_int32_t sa = core->thumb_instruction.shift0.sa;
  u_int32_t vm = *core->registers[core->current_bank][core->thumb_instruction.shift0.rm];
  u_int32_t type;
  
  
  switch(core->thumb_instruction.shift0.op1)
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
  
  //Do the actual shifting
  ArmV5tlThumbShift(core, type, sa , vm);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Register shift
void ArmV5tlThumbShiftRegister(PARMV5TL_CORE core)
{
  u_int32_t sa = *core->registers[core->current_bank][core->thumb_instruction.shift2.rs];
  u_int32_t vm = *core->registers[core->current_bank][core->thumb_instruction.shift2.rd];
  u_int32_t type;
  
  //LSL(2) op2:2, LSR(2) op2:3, ASR(2) op2:4, ROR op2:7
  //Other values are filtered out in the decode stage
  switch(core->thumb_instruction.shift2.op2)
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
  
  //Do the actual shifting
  ArmV5tlThumbShift(core, type, sa, vm);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Shift
void ArmV5tlThumbShift(PARMV5TL_CORE core, u_int32_t type, u_int32_t sa, u_int32_t vm)
{
  u_int32_t c = core->status->flags.C;
  
  //Take action based on the shift type
  switch(type)
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
      if((sa > 0) && (sa < 32))
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
      if((sa > 0) && (sa < 32))
      {
        //When the shift is less then 32 the carry is the last bit shifted out and vm is shifted sa times
        c = (vm >> (sa - 1)) & 1;
        
        //When positive normal shifting is ok
        if((vm & 0x80000000) == 0)
        {
          vm >>= sa;
        }
        else
        {
          //For negative numbers invert, shift and invert back
          vm = ~(~vm >> sa);
        }
      }
      else if(sa >= 32)
      {
        //When the shift is 32 or more the carry is bit31
        c = vm >> 31;
        
        //Based on the sign bit of the data the result is either 0 or 0xFFFFFFFF
        if(c == 0)
        {
          vm = 0;
        }
        else
        {
          vm = 0xFFFFFFFF;
        }
      }
      break;
      
    case ARM_SHIFT_MODE_ROR:
      if((sa > 0) && ((sa & 0x1F) == 0))
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
  
  //Store back to rd (For rd both shift0 and shift2 types are the same)
  *core->registers[core->current_bank][core->thumb_instruction.shift0.rd] = vm;
  
  //Update the negative bit
  core->status->flags.N = vm >> 31;

  //Update the zero bit
  core->status->flags.Z = (vm == 0);
  
  //Update the carry
  core->status->flags.C = c;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 0
void ArmV5tlThumbDP0(PARMV5TL_CORE core)
{
  //Get the input data. For rd and vn there is no difference between dpi0 and dpr0
  u_int32_t rd = core->thumb_instruction.dpi0.rd;
  u_int32_t vm;
  u_int32_t vn = *core->registers[core->current_bank][core->thumb_instruction.dpr0.rn];
  u_int32_t type;
  
  //For op2 both dpr0 and dpi0 are the same
  switch(core->thumb_instruction.dpr0.op2)
  {
    //ADD(3)
    case 0:
      //Use the indicated register for the second operand
      vm = *core->registers[core->current_bank][core->thumb_instruction.dpr0.rm];
      type = ARM_OPCODE_ADD;
      break;

    //SUB(3)
    case 1:
      //Use the indicated register for the second operand
      vm = *core->registers[core->current_bank][core->thumb_instruction.dpr0.rm];
      type = ARM_OPCODE_SUB;
      break;
    
    //ADD(1), MOV(2)
    case 2:
      //Check if add or mov instruction
      if(core->thumb_instruction.dpi0.im)
      {
        //For a non zero immediate value it is an add
        //Use the immediate value for the second operand
        vm = core->thumb_instruction.dpi0.im;
        type = ARM_OPCODE_ADD;
      }
      else
      {
        //For a zero immediate value it is move
        //Use the data from the n register as operand
        vm = vn;
        
        //Signal that for this move the carry and overflow flag need to be cleared
        type = ARM_OPCODE_MOV | ARM_OPCODE_THUMB_CLR_CV;
      }
      break;

    //SUB(1)
    case 3:
      //Use the immediate value for the second operand
      vm = core->thumb_instruction.dpi0.im;
      type = ARM_OPCODE_SUB;
      break;
  }
  
  //Go and do the actual processing
  ArmV5tlThumbDP(core, type, rd, vn, vm);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 1
void ArmV5tlThumbDP1(PARMV5TL_CORE core)
{
  //Get the input data.
  u_int32_t rd = core->thumb_instruction.dp1.rd;
  u_int32_t vm = core->thumb_instruction.dp1.im;
  u_int32_t vn = *core->registers[core->current_bank][core->thumb_instruction.dp1.rd];
  u_int32_t type;
  
  //For type 1 the op1 is the select for the type of function to perform
  switch(core->thumb_instruction.dp1.op1)
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
  
  //Go and do the actual processing
  ArmV5tlThumbDP(core, type, rd, vn, vm);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 2
void ArmV5tlThumbDP2(PARMV5TL_CORE core)
{
  //Get the input data.
  u_int32_t rd = core->thumb_instruction.dp2.rd;
  u_int32_t vm = *core->registers[core->current_bank][core->thumb_instruction.dp2.rm];
  u_int32_t vn = *core->registers[core->current_bank][core->thumb_instruction.dp2.rd];
  u_int32_t type;
  
  //For type 2 dp2 op2 tells which function to perform. Some have already been filtered out in the decoding process.
  switch(core->thumb_instruction.dp2.op2)
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
  
  //Go and do the actual processing
  ArmV5tlThumbDP(core, type, rd, vn, vm);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing type 2 special
void ArmV5tlThumbDP2S(PARMV5TL_CORE core)
{
 //Get the input data. rd is a combination of the h (high) bit and the three rd bits
  u_int32_t rd = core->thumb_instruction.dp2s.rd | (core->thumb_instruction.dp2s.h << 3);
  u_int32_t vm = *core->registers[core->current_bank][core->thumb_instruction.dp2s.rm];
  u_int32_t vn = *core->registers[core->current_bank][rd];
  u_int32_t type;
  
  //Not sure about this. Manual does not give enogh info
  //Amend the values when r15 (pc) is used
  if(core->thumb_instruction.dp2s.rm == 15)
  {
    vm += 4;
  }

  //Same for the first operand register
  if(rd == 15)
  {
    vn += 4;
  }
  
  //For type 2 dp2s op2 tells which function to perform. Most have already been filtered out in the decoding process.
  switch(core->thumb_instruction.dp2s.op2)
  {
    //ADD(4)
    case 4:
      type = ARM_OPCODE_ADD | ARM_OPCODE_THUMB_NO_FLAGS;
      break;

    //CMP(3)
    case 5:
      type = ARM_OPCODE_CMP;
      break;

    //CPY, MOV(3)
    case 6:
      type = ARM_OPCODE_MOV | ARM_OPCODE_THUMB_NO_FLAGS;
      break;
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------
//Actual data processing handling
void ArmV5tlThumbDP(PARMV5TL_CORE core, u_int32_t type, u_int32_t  rd, u_int32_t vn, u_int32_t vm)
{
  u_int64_t vd;
  u_int32_t update = 1;
  u_int32_t docandv = ARM_FLAGS_UPDATE_CV_NO;
  
  //Check if NEG
  if(type & ARM_OPCODE_THUMB_NEG)
  {
    vd = 0 - (int64_t)vm;
  }
  //If not check if MUL
  else if(type & ARM_OPCODE_THUMB_MUL)
  {
    vd = (int32_t)vm * (int32_t)vn;
  }
  //If neither do the switch on type
  else
  {
    //Perform the correct action based on the type
    switch(type & ARM_THUMB_TYPE_MASK)
    {
      case ARM_OPCODE_AND:
        vd = vn & vm;
        break;

      case ARM_OPCODE_EOR:
        vd = vn ^ vm;
        break;

      case ARM_OPCODE_SUB:
        vd = (int64_t)vn - (int64_t)vm;
        break;

      case ARM_OPCODE_RSB:
        vd = (int64_t)vm - (int64_t)vn;
        break;

      case ARM_OPCODE_ADD:
        vd = (int64_t)vn + (int64_t)vm;
        break;

      case ARM_OPCODE_ADC:
        vd = (int64_t)vn + (int64_t)vm + core->status->flags.C;
        break;

      case ARM_OPCODE_SBC:
        vd = (int64_t)vn - (int64_t)vm - (core->status->flags.C ^ 1);
        break;

      case ARM_OPCODE_RSC:
        vd = (int64_t)vm - (int64_t)vn - (core->status->flags.C ^ 1);
        break;

      case ARM_OPCODE_TST:
        vd = vn & vm;
        break;

      case ARM_OPCODE_TEQ:
        vd = vn ^ vm;
        break;

      case ARM_OPCODE_CMP:
        vd = (int64_t)vn - (int64_t)vm;
        break;

      case ARM_OPCODE_CMN:
        vd = (int64_t)vn + (int64_t)vm;
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
  }
  
  //Clear the update rd flag for the types that do not save the result
  switch(type & ARM_THUMB_TYPE_MASK)
  {      
    case ARM_OPCODE_TST:
    case ARM_OPCODE_TEQ:
    case ARM_OPCODE_CMP:
    case ARM_OPCODE_CMN:
      update = 0;
      break;
  }
  
  //Check on extra flags in the type
  if(type & ARM_OPCODE_THUMB_CLR_CV)
  {
    //If clear carry and overflow specified set the indicator accordingly
    docandv = ARM_FLAGS_UPDATE_CV_CLR;
  }
  //Check if NEG function requested
  else if(type & ARM_OPCODE_THUMB_NEG)
  {
    docandv = ARM_FLAGS_UPDATE_NBV;
  }
  //If not MUL do the switch on type
  else if((type & ARM_OPCODE_THUMB_MUL) == 0)
  {
    //Set the flag change mode based on the requested type
    switch(type & ARM_THUMB_TYPE_MASK)
    {
      case ARM_OPCODE_ADD:
      case ARM_OPCODE_ADC:
      case ARM_OPCODE_CMN:
        docandv = ARM_FLAGS_UPDATE_CV;
        break;

      case ARM_OPCODE_SUB:
      case ARM_OPCODE_RSB:
      case ARM_OPCODE_SBC:
      case ARM_OPCODE_RSC:
      case ARM_OPCODE_CMP:
        docandv = ARM_FLAGS_UPDATE_NBV;
        break;
    }
  }
  
  //Check if flags can be updated (Some ADD and MOV instructions do not update the flags)
  if((type & ARM_OPCODE_THUMB_NO_FLAGS) == 0)
  {
    //Update the negative bit
    core->status->flags.N = vd >> 31;

    //Update the zero bit
    core->status->flags.Z = (vd == 0);

    //Check if carry and overflow need to be updated with arithmetic result
    if(docandv == ARM_FLAGS_UPDATE_CV_CLR)
    {
      core->status->flags.V = 0;
      core->status->flags.C = 0;
    }
    else if(docandv != ARM_FLAGS_UPDATE_CV_NO)
    {
      //Update the overflow bit
      core->status->flags.V = (((vn & 0x80000000) == (vm & 0x80000000)) && (vn & 0x80000000) != (vd & 0x80000000));

      //Handle the carry according to type of arithmetic
      if(docandv == ARM_FLAGS_UPDATE_CV)
      {
        //Carry from addition
        core->status->flags.C = vd >> 32;
      }
      else
      {
        //Not borrow from subtraction
        core->status->flags.C = (vd <= 0xFFFFFFFF);
      }
    }
  }
  
  //Check if destination register needs to be updated
  if(update)
  {
    //Write the result back as a singed 32 bit integer
    *core->registers[core->current_bank][rd] = (int32_t)vd;
    
    //Check if program counter used as target
    if(rd == 15)
    {
      //Signal no increment if so
      core->pcincrvalue = 0;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 2 immediate indexed based instructions
void ArmV5tlThumbLS2I(PARMV5TL_CORE core)
{
 //Get the input data
  u_int32_t rd = core->thumb_instruction.ls2i.rd;
  u_int32_t vm = core->thumb_instruction.ls2i.im * 4;
  u_int32_t vn = (*core->program_counter + 4) & 0xFFFFFFFC;
  u_int32_t type;
  u_int32_t address = vn + vm;

  //Signal loading of a word
  type = ARM_THUMB_SIZE_WORD | ARM_THUMB_LOAD_FLAG;
  
  //Go and do the actual load or store
  ArmV5tlThumbLS(core, type, rd, address);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 2 register based instructions
void ArmV5tlThumbLS2R(PARMV5TL_CORE core)
{
 //Get the input data
  u_int32_t rd = core->thumb_instruction.ls2r.rd;
  u_int32_t vm = *core->registers[core->current_bank][core->thumb_instruction.ls2r.rm];
  u_int32_t vn = *core->registers[core->current_bank][core->thumb_instruction.ls2r.rn];
  u_int32_t type;
  u_int32_t address = vn + vm;
  
  //Check if sign extend instructions
  if(core->thumb_instruction.ls2r.op2 == 3)
  {
    //Check on which size the instruction needs to work
    if(core->thumb_instruction.ls2r.op1 == 2)
    {
      //LDRSB
      type = ARM_THUMB_SIZE_BYTE;
    }
    else
    {
      //LDRSH
      type = ARM_THUMB_SIZE_SHORT;
    }
    
    //Signal load and sign extend
    type |= (ARM_THUMB_LOAD_FLAG | ARM_THUMB_SIGN_EXTEND);
  }
  //Normal load store instructions
  else
  {
    //Set the data size in the type
    type = core->thumb_instruction.ls2r.op2;
    
    //Check if load instructions
    if(core->thumb_instruction.ls2r.op1 == 3)
    {
      //Signal load functionality
      type |= ARM_THUMB_LOAD_FLAG;
    }
  }
  
  //Go and do the actual load or store
  ArmV5tlThumbLS(core, type, rd, address);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 3 immediate indexed based instructions
void ArmV5tlThumbLS3(PARMV5TL_CORE core)
{
 //Get the input data
  u_int32_t rd = core->thumb_instruction.ls3.rd;
  u_int32_t vm = core->thumb_instruction.ls3.im * 4;
  u_int32_t vn = *core->registers[core->current_bank][core->thumb_instruction.ls3.rn];
  u_int32_t type;
  u_int32_t address = vn + vm;

  //Set the correct size for the given instruction
  if(core->thumb_instruction.ls3.type == 4)
  {
    //For type 4 instructions it is short
    type = ARM_THUMB_SIZE_SHORT;
  }
  else if(core->thumb_instruction.ls3.b)
  {
    //For b == 1 it is byte
    type = ARM_THUMB_SIZE_BYTE;
  }
  else
  {
    //For b == 0 it is word
    type = ARM_THUMB_SIZE_WORD;
  }
  
  //Check if load or store
  if(core->thumb_instruction.ls3.l)
  {
    //Signal load is requested
    type |= ARM_THUMB_LOAD_FLAG;
  }
  
  //Go and do the actual load or store
  ArmV5tlThumbLS(core, type, rd, address);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store handling for type 4 immediate indexed based instructions
void ArmV5tlThumbLS4(PARMV5TL_CORE core)
{
 //Get the input data. Instruction format is the same as for type 2 immediate indexed so reusing it here
  u_int32_t rd = core->thumb_instruction.ls2i.rd;
  u_int32_t vm = core->thumb_instruction.ls2i.im * 4;
  u_int32_t vn = (*core->registers[core->current_bank][13]) & 0xFFFFFFFC;
  u_int32_t type = ARM_THUMB_SIZE_WORD;
  u_int32_t address = vn + vm;

  //Check if load or store
  if(core->thumb_instruction.ls2i.op1 == 3)
  {
    //Signal loading
    type |= ARM_THUMB_LOAD_FLAG;
  }
  
  //Go and do the actual load or store
  ArmV5tlThumbLS(core, type, rd, address);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Thumb load and store instruction handling
void ArmV5tlThumbLS(PARMV5TL_CORE core, u_int32_t type, u_int32_t rd, u_int32_t address)
{
  void *memory;
  
  //Handle data based on the size of it
  switch(type & ARM_THUMB_SIZE_MASK)
  {
    case ARM_THUMB_SIZE_BYTE:
      //Byte access so get a pointer to the given address
      memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_BYTE);

      //Check if the address was valid
      if(memory)
      {
        //Check if a load or a store is requested
        if(type & ARM_THUMB_LOAD_FLAG)
        {
          //Load from memory address
          *core->registers[core->current_bank][rd] = *(u_int8_t *)memory;
          
          //Check if sign extend needed
          if((type & ARM_THUMB_SIGN_EXTEND) && (*core->registers[core->current_bank][rd] & 0x80))
          {
            *core->registers[core->current_bank][rd] |= 0xFFFFFF00;
          }
        }
        else
        {
          //Store to memory address
          *(u_int8_t *)memory = (u_int8_t)*core->registers[core->current_bank][rd];
        }
      }
      break;
      
    case ARM_THUMB_SIZE_SHORT:
      //Short access so get a pointer to the given address
      memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_SHORT);

      //Check if the address was valid
      if(memory)
      {
        //Check if a load or a store is requested
        if(type & ARM_THUMB_LOAD_FLAG)
        {
          //Load from memory address
          *core->registers[core->current_bank][rd] = *(u_int16_t *)memory;
          
          //Check if sign extend needed
          if((type & ARM_THUMB_SIGN_EXTEND) && (*core->registers[core->current_bank][rd] & 0x8000))
          {
            *core->registers[core->current_bank][rd] |= 0xFFFF0000;
          }
        }
        else
        {
          //Store to memory address
          *(u_int16_t *)memory = (u_int16_t)*core->registers[core->current_bank][rd];
        }
      }
      break;
      
    case ARM_THUMB_SIZE_WORD:
      //Word access so get a pointer to the given address
      memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_WORD);
    
      //Check if the address is valid
      if(memory)
      {
        //Check if a load or a store is requested
        if(type & ARM_THUMB_LOAD_FLAG)
        {
          //Load from memory address
          *core->registers[core->current_bank][rd] = *(u_int32_t *)memory;
        }
        else
        {
          //Store to memory address
          *(u_int32_t *)memory = *core->registers[core->current_bank][rd];
        }
      }
      break;
  }
  
  //Check if program counter used as target
  if((type & ARM_THUMB_LOAD_FLAG) && (rd == 15))
  {
    //Signal no increment if so
    core->pcincrvalue = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store multiple instruction handling
void ArmV5tlThumbLSMIA(PARMV5TL_CORE core)
{
  u_int32_t address = *core->registers[core->current_bank][core->thumb_instruction.lsm.rn];
  u_int32_t *memory;
  u_int32_t reglist = core->thumb_instruction.lsm.rl;
  int       numregs = 0;
  int       update = 1;
  int       i;
  
  //Check the register list for which registers need to be loaded or stored
  for(i=0;i<8;i++)
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
        if(core->thumb_instruction.lsm.l)
        {
          //Load the register with the data from memory
          *core->registers[core->current_bank][i] = *memory;
        }
        else
        {
          //Store the register to memory
          *memory = *core->registers[core->current_bank][i];
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

      //Check if base register included in the list. Never the case for a PUSH instruction so only done here
      if(core->thumb_instruction.lsm.rn == i)
      {
        //If so then no update of it
        update = 0;
      }
    }

    //Select next register
    reglist >>= 1;
  }

  //Check if base register needs to be updated
  if(update)
  {
    //Increment the base address
    *core->registers[core->current_bank][core->thumb_instruction.lsm.rn] += (numregs * 4);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Pop instruction handling
void ArmV5tlThumbPOP(PARMV5TL_CORE core)
{
  u_int32_t address = *core->registers[core->current_bank][13];
  u_int32_t *memory;
  u_int32_t reglist = core->thumb_instruction.lsm.rl;
  int       numregs = 0;
  int       i;
  
  //Check the register list for which registers need to be loaded
  for(i=0;i<8;i++)
  {
    //Check if register included
    if(reglist & 1)
    {
      //Get the pointer for this address        
      memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_WORD);

      //Check if valid memory found
      if(memory)
      {
        //Load the register with the data from memory
        *core->registers[core->current_bank][i] = *memory;
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

  //Check if r15 is included in the list
  if(core->thumb_instruction.base.op2 & 4)
  {
    //Get the pointer for current address
    memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_WORD);
        
    //Check if valid memory found
    if(memory)
    {
      //Load the program counter
      *core->program_counter = *memory & 0xFFFFFFFE;

      //Update the thumb bit
      core->status->flags.T = *memory & 1;

      //Signal no increment of pc
      core->pcincrvalue = 0;
    }
    else
    {
      //Signal a data abort exception  
    }
    
    //Signal one more register done
    numregs++;
  }  
  
  //Increment the stack pointer address
  *core->registers[core->current_bank][13] += (numregs * 4);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Push instruction handling
void ArmV5tlThumbPUSH(PARMV5TL_CORE core)
{
  //For a push an extra 4 needs to be subtracted from the start address (decrement before)
  u_int32_t address = *core->registers[core->current_bank][13] - 4;
  u_int32_t *memory;
  u_int32_t reglist = core->thumb_instruction.lsm.rl;
  int       numregs = 0;
  int       i;
  
  //Check if r14 is included in the list
  if(core->thumb_instruction.base.op2 & 4)
  {
    //Get the pointer for current address
    memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_WORD);
        
    //Check if valid memory found
    if(memory)
    {
      //PUSH so store the Link register to memory
      *memory = *core->registers[core->current_bank][14];
    }
    else
    {
      //Signal a data abort exception  
    }
    
    //Point next address
    address -= 4;
    
    //Signal one more register done
    numregs++;
  }  
  
  //Check the register list for which registers need to be stored
  for(i=7;i>=0;i--)
  {
    //Check if register included
    if(reglist & 0x00000080)
    {
      //Get the pointer for this address        
      memory = ArmV5tlGetMemoryPointer(core, address, ARM_MEMORY_WORD);

      //Check if valid memory found
      if(memory)
      {
        //Store the register to memory
        *memory = *core->registers[core->current_bank][i];
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

  //Decrement the stack pointer address
  *core->registers[core->current_bank][13] -= (numregs * 4);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Type 2 instructions branch handling
void ArmV5tlThumbBranch2(PARMV5TL_CORE core)
{
  u_int32_t vm = *core->registers[core->current_bank][core->thumb_instruction.b2.rm];
  
  //When the program counter is used the value needs to be plus 4
  if(core->thumb_instruction.b2.rm == 15)
  {
    vm += 4;
  }
  
  //Bit 0 of the target address given in rm is the T bit for the next instruction
  core->status->flags.T = vm & 1;
  
  //Check if BLX instruction
  if(core->thumb_instruction.b2.op2 == 15)
  {
    //Set the link register for the BLX instruction to point to the next thumb instruction
    *core->registers[core->current_bank][14] = (*core->program_counter + 2) | 1;
  }

  //Update the program counter with the target address without the thumb indicator bit
  *core->program_counter = vm & 0xFFFFFFFE;
  
  //Signal no increment of the pc
  core->pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Type 6 instructions branch handling
void ArmV5tlThumbBranch6(PARMV5TL_CORE core)
{
  u_int32_t vm;
  u_int32_t execute = 0;

  //Check the condition bits against the status bits to decide if the branch needs to be executed
  switch(core->thumb_instruction.b6.cond)
  {
    case ARM_COND_EQUAL:
      //For execute on equal Z needs to be set
      if(core->status->flags.Z)
        execute = 1;
      break;

    case ARM_COND_NOT_EQUAL:
      //For execute on not equal Z needs to be cleared
      if(core->status->flags.Z == 0)
        execute = 1;
      break;

    case ARM_COND_CARRY_SET:
      //For execute on carry set C needs to be set
      if(core->status->flags.C)
        execute = 1;
      break;

    case ARM_COND_CARRY_CLEAR:
      //For execute on carry set C needs to be cleared
      if(core->status->flags.C == 0)
        execute = 1;
      break;

    case ARM_COND_MINUS:
      //For execute on minus N needs to be set
      if(core->status->flags.N)
        execute = 1;
      break;

    case ARM_COND_PLUS:
      //For execute on plus N needs to be cleared
      if(core->status->flags.N == 0)
        execute = 1;
      break;

    case ARM_COND_OVERFLOW:
      //For execute on overflow V needs to be set
      if(core->status->flags.V)
        execute = 1;
      break;

    case ARM_COND_NO_OVERFLOW:
      //For execute on no overflow V needs to be cleared
      if(core->status->flags.V == 0)
        execute = 1;
      break;

    case ARM_COND_HIGHER:
      //For execute on higher C needs to be set and Z needs to be cleared
      if((core->status->flags.C) && (core->status->flags.Z == 0))
        execute = 1;
      break;

    case ARM_COND_LOWER_SAME:
      //For execute on lower or the same C needs to be cleared and Z needs to be set
      if((core->status->flags.C == 0) && (core->status->flags.Z ))
        execute = 1;
      break;

    case ARM_COND_GREATER_EQUAL:
      //For execute on greater or equal N needs to be equal to V
      if(core->status->flags.N == core->status->flags.V)
        execute = 1;
      break;

    case ARM_COND_LESS_THAN:
      //For execute on less than N needs to be not equal to V
      if(core->status->flags.N != core->status->flags.V)
        execute = 1;
      break;

    case ARM_COND_GREATER_THAN:
      //For execute on greater than N needs to be equal to V and Z needs to be cleared
      if((core->status->flags.N == core->status->flags.V) && (core->status->flags.Z == 0))
        execute = 1;
      break;

    case ARM_COND_LESS_THAN_EQUAL:
      //For execute on less than or equal than N needs to be not equal to V and Z needs to be set
      if((core->status->flags.N != core->status->flags.V) && (core->status->flags.Z))
        execute = 1;
      break;
  }

  //Take the branch when needed
  if(execute)
  {
    //Get the value to index the program counter
    vm = core->thumb_instruction.b6.im << 1;
    
    //Check if negative address given
    if(vm & 0x100)
    {
      //Extend the sign if so
      vm |= 0xFFFFFFE00;
    }

    //Calculate the new address. The actual pc point to instruction address plus 4
    *core->program_counter += (4 + vm);
    
    //Signal no increment of the pc
    core->pcincrvalue = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Type 7 instructions branch handling
void ArmV5tlThumbBranch7(PARMV5TL_CORE core)
{
  u_int32_t vm;

  //Check on unconditional branch
  if(core->thumb_instruction.b7.op1 == 0)
  {
    //Get the value to index the program counter
    vm = core->thumb_instruction.b7.im << 1;
    
    //Check if negative address given
    if(vm & 0x800)
    {
      //Extend the sign if so
      vm |= 0xFFFFFF000;
    }

    //Calculate the new address. The actual pc point to instruction address plus 4
    *core->program_counter += (4 + vm);
    
    //Signal no increment of the pc
    core->pcincrvalue = 0;
  }
  //Check if this is a branch link prefix instruction
  else if(core->thumb_instruction.b7.op1 == 2)
  {
    //Setup the prefix address
    vm = core->thumb_instruction.b7.im << 12;
    
    //Check if negative address given
    if(vm & 0x00400000)
    {
      //Extend the sign if so
      vm |= 0xFF800000;
    }
    
    //Use the link register as temporary storage
    *core->registers[core->current_bank][14] = *core->program_counter + 4 + vm;
  }
  //Either second BL or BLX instruction
  else
  {
    //Get the result from the previous BL instruction
    vm = *core->registers[core->current_bank][14];
    
    //Set the link register for the BL or BLX(1) instruction to point to the next thumb instruction
    *core->registers[core->current_bank][14] = (*core->program_counter + 2) | 1;

    //Set the program counter to the new address
    *core->program_counter = vm + (core->thumb_instruction.b7.im << 1);
    
    //Check if it is a BLX(1) instruction
    if(core->thumb_instruction.b7.op1 == 1)
    {
      //Switch back to arm state if so
      core->status->flags.T = 0;
      
      //Make sure the target address is word aligned
      *core->program_counter &= 0xFFFFFFFC;
    }

    //Signal no increment of the pc
    core->pcincrvalue = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
