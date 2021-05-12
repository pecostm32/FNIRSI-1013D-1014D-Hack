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
          //Opcode 3 are data processing or mov
          
        //ADD(3) 000 11 00 mmm nnn ddd
        //SUB(3) 000 11 01 mmm nnn ddd
        //ADD(1) 000 11 10 iii nnn ddd
        //MOV(2) 000 11 10 000 nnn ddd
        //SUB(1) 000 11 11 iii nnn ddd
          
        }
        else
        {
          //LSL(1) op1:0, LSR(1) op1:1, ASR(1) op1:2
          ArmV5tlThumbShiftImmediate(core);
        }
        break;

      case 1:
        //Add / subtract / compare / move immediate
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
          else
          {
            
          }
        
        //ADC         010 00 001 01 mmm ddd
        //SBC         010 00 001 10 mmm ddd
        //AND         010 00 000 00 mmm ddd
        //OR          010 00 011 00 mmm ddd
        //EOR         010 00 000 01 mmm ddd
        //BIC         010 00 011 10 mmm ddd
        //MVN         010 00 011 11 mmm ddd
        //NEG         010 00 010 01 mmm ddd

        //MUL         010 00 011 01 mmm ddd
        
        //ADD(4)      010 00 100 hh mmm ddd
        //CPY         010 00 110 hh mmm ddd
        //MOV(3)      010 00 110 hh mmm ddd

        //CMN         010 00 010 11 mmm nnn
        //CMP(2)      010 00 010 10 mmm nnn
        //CMP(3)      010 00 101 hh mmm nnn
        //TST         010 00 010 00 mmm nnn
        
        
        //BLX(2)      010 00 1111 h mmm zzz
        //BX          010 00 1110 h mmm zzz
          
        }
        else
        {
        //LDR(3)      010 01 ddd iiiiiiii
        
        //LDR(2)      010 11 00 mmm nnn ddd
        //LDRB(2)     010 11 10 mmm nnn ddd
        //LDRH(2)     010 11 01 mmm nnn ddd
        //LDRSB       010 10 11 mmm nnn ddd
        //LDRSH       010 11 11 mmm nnn ddd
        //STR(2)      010 10 00 mmm nnn ddd
        //STRB(2)     010 10 10 mmm nnn ddd
        //STRH(2)     010 10 01 mmm nnn ddd
          
        }

        
        
        
        
        
        //Data processing register
        //Special processing
        //Branch / exchange instruction set
        //load from literal pool
        //Load / store register offset
        break;

      case 3:
        //Load / store word / byte  immediate offset
        break;

      case 4:
        //Load / store short immediate offset
        //Load / store to / from stack
        break;

      case 5:
        //Add to sp or pc
        //Miscellaneous
        break;

      case 6:
        //Load / store multiple
        //Conditional branch
        //Undefined instruction
        //Software interrupt
        break;

      case 7:
        //Unconditional branch
        //BLX suffix
        //Undefined instruction
        //BL / BLX prefix
        //BL suffix
        break;
    }
  }
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
  ArmV5tlThumbShift(core, type, sa , vm);
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
  
  //Store back to rd (For rd shift0 and shift2 types are the same)
  *core->registers[core->current_bank][core->thumb_instruction.shift0.rd] = vm;
  
  //Update the negative bit
  core->status->flags.N = vm >> 31;

  //Update the zero bit
  core->status->flags.Z = (vm == 0);
  
  //Update the carry
  core->status->flags.C = c;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate and register shift
void ArmV5tlThumbDPR(PARMV5TL_CORE core)
{
  //Get the input data
  u_int32_t vm = *core->registers[core->current_bank][core->arm_instruction.dpsi.rm];
  u_int32_t vn = *core->registers[core->current_bank][core->arm_instruction.dpsi.rn];
  u_int32_t sa;
  u_int32_t c = core->status->flags.C;

  //Amend the values when r15 (pc) is used
  if(core->arm_instruction.dpsi.rn == 15)
  {
    vn += 8;
  }

  //Same for the to be shifted register
  if(core->arm_instruction.dpsi.rm == 15)
  {
    vm += 8;
  }
  
  //Check if immediate shift or register shift. For immediate shift bit4 is cleared
  if(core->arm_instruction.type0.it1 == 0)
  {
    //Data processing immediate shift
    //Get the immediate shift amount
    sa = core->arm_instruction.dpsi.sa;
  }
  else
  {
    //Data processing register shift
    //Get the register shift amount.
    sa = *core->registers[core->current_bank][core->arm_instruction.dpsr.rs] & 0x000000FF;
  }
  
  
  //Go and do the actual processing
  ArmV5tlDPR(core, vn, vm, c);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate
void ArmV5tlThumbDPI(PARMV5TL_CORE core)
{
  //Get the input data
  u_int32_t vm = core->arm_instruction.dpi.im;
  u_int32_t vn = *core->registers[core->current_bank][core->arm_instruction.dpsi.rn];
  u_int32_t ri = core->arm_instruction.dpi.ri << 1;
  u_int32_t c = core->status->flags.C;
  
  //Amend the operand value when r15 (pc) is used
  if(core->arm_instruction.dpsi.rn == 15)
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
void ArmV5tlThumbDP(PARMV5TL_CORE core, u_int32_t opcode, u_int32_t vn, u_int32_t vm, u_int32_t c)
{
  u_int64_t vd;
  u_int32_t update = 1;
  u_int32_t docandv = ARM_FLAGS_UPDATE_CV_NO;
  
  //Perform the correct action based on the opcode
  switch(opcode)
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
      vd = (int64_t)vn + (int64_t)vm + core->status->flags.C;
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_CV;
      break;

    case ARM_OPCODE_SBC:
      vd = (int64_t)vn - (int64_t)vm - (core->status->flags.C ^ 1);
      
      //Signal how to update the flags
      docandv = ARM_FLAGS_UPDATE_NBV;
      break;

    case ARM_OPCODE_RSC:
      vd = (int64_t)vm - (int64_t)vn - (core->status->flags.C ^ 1);
      
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
  if(core->arm_instruction.type0.s)
  {
    //Check if destination register needs to be updated, is r15 (pc) and the current mode has a saved program status register
    if((update) && (core->arm_instruction.dpsi.rd == 15) && (core->registers[core->current_bank][ARM_REG_SPSR_IDX]))
    {
      //Load the current status with the saved one if it is available
      core->status->word =  ((PARMV5TL_STATUS)core->registers[core->current_bank][ARM_REG_SPSR_IDX])->word;
      
      //Adjust the current processor state accordingly
      core->current_mode = core->status->flags.M;

      //Select the corresponding register bank
      switch(core->status->flags.M)
      {
        case ARM_MODE_USER:
          core->current_bank = ARM_REG_BANK_USER;
          break;
          
        case ARM_MODE_FIQ:
          core->current_bank = ARM_REG_BANK_FIQ;
          break;
          
        case ARM_MODE_IRQ:
          core->current_bank = ARM_REG_BANK_IRQ;
          break;
          
        case ARM_MODE_SUPERVISOR:
          core->current_bank = ARM_REG_BANK_SUPERVISOR;
          break;
          
        case ARM_MODE_ABORT:
          core->current_bank = ARM_REG_BANK_ABORT;
          break;
          
        case ARM_MODE_UNDEFINED:
          core->current_bank = ARM_REG_BANK_UNDEFINED;
          break;
          
        case ARM_MODE_SYSTEM:
          core->current_bank = ARM_REG_BANK_SYSTEM;
          break;
      }
    }
    else
    {
      //Update the negative bit
      core->status->flags.N = vd >> 31;

      //Update the zero bit
      core->status->flags.Z = (vd == 0);

      //Check if carry and overflow need to be updated with arithmetic result
      if(docandv != ARM_FLAGS_UPDATE_CV_NO)
      {
        //Update the overflow bit
        core->status->flags.V = (((vn & 0x80000000) == (vm & 0x80000000)) && (vn & 0x80000000) != (vd & 0x80000000));

        //Handle the carry according to type of arithmetic
        if(docandv == ARM_FLAGS_UPDATE_CV)
        {
          //Carry from addition.
          core->status->flags.C = vd >> 32;
        }
        else
        {
          //Not borrow from subtraction
          core->status->flags.C = (vd <= 0xFFFFFFFF);
        }
      }
      else
      {
        //When not the carry is the shifter output
        core->status->flags.C = c;
      }
    }
  }
  
  //Check if destination register needs to be updated
  if(update)
  {
    //Write the result back as a singed 32 bit integer
    *core->registers[core->current_bank][core->arm_instruction.dpsi.rd] = (int32_t)vd;
    
    //Check if program counter used as target
    if(core->arm_instruction.lsr.rd == 15)
    {
      //Signal no increment if so
      core->pcincrvalue = 0;
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
