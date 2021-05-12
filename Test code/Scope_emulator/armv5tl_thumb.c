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
    switch(core->arm_instruction.base.type)
    {
      case 0:
        //Shift by immediate              ASR(1) op: 2  LSL(1) op: 0  LSR (1) op: 1
        //Add / subtract register         ADD (1)(3) op 3: SUB (1)(3) op 3:
        //Add / subtract immediate        MOV (2) op 3:
        
        //i = immediate, n = rn, d = rd, m=rm
        //LSL(1) 000 00 ii iii mmm ddd
        //LSR(1) 000 01 ii iii mmm ddd
        //ASR(1) 000 10 ii iii mmm ddd
        //ADD(3) 000 11 00 mmm nnn ddd
        //SUB(3) 000 11 01 mmm nnn ddd
        //ADD(1) 000 11 10 iii nnn ddd
        //MOV(2) 000 11 10 000 nnn ddd
        //SUB(1) 000 11 11 iii nnn ddd
        
        break;

      case 1:
        //Add / subtract / compare / move immediate
        break;

      case 2:
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


//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate and register shift
void ArmV5tlThumbDataProcessing(PARMV5TL_CORE core)
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
  
  //Take action based on the shift mode
  switch(core->arm_instruction.dpsi.sm)
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
        if(core->arm_instruction.type0.it1 == 0)
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
        if(core->arm_instruction.type0.it1 == 0)
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
        if(core->arm_instruction.type0.it1 == 0)
        {
          //Special case here where the shift amount is 0. Rotate right with extend. Carry is an extra bit
          c = vm & 1;
          vm = (core->status->flags.C << 31) | (vm >> 1);
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
void ArmV5tlDPR(PARMV5TL_CORE core, u_int32_t vn, u_int32_t vm, u_int32_t c)
{
  u_int64_t vd;
  u_int32_t update = 1;
  u_int32_t docandv = ARM_FLAGS_UPDATE_CV_NO;
  
  //Perform the correct action based on the opcode
  switch(core->arm_instruction.type0.opcode)
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
