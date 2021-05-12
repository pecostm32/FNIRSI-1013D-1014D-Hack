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
        //Shift by immediate
        //Add / subtract register
        //Add / subtract immediate
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
