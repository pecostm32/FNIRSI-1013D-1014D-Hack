//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "armv5tl.h"
#include "armv5tl_thumb.h"

#define MY_BREAK_POINT 0x0B3C

//----------------------------------------------------------------------------------------------------------------------------------

pthread_t arm_core_thread;

int quit_armcore_thread_on_zero = 0;

ARMV5TL_CORE arm_core;

//----------------------------------------------------------------------------------------------------------------------------------

int startarmcore(void)
{
  //Setup for keeping the arm ui window thread running
  quit_armcore_thread_on_zero = 1;
  
  //Start up the led blink thread
  return(pthread_create(&arm_core_thread, NULL, armcorethread, NULL));
}

//----------------------------------------------------------------------------------------------------------------------------------

void stoparmcore(void)
{
  //Stop the arm ui window thread
  quit_armcore_thread_on_zero = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void *armcorethread(void *arg)
{
  //Initialize the core
  ArmV5tlSetup(&arm_core);
  
  //Keep running the core until stopped
  while(quit_armcore_thread_on_zero)
  {
    ArmV5tlCore(&arm_core);
  }
  
  //Exit the thread the way it is supposed to
  pthread_exit(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlSetup(PARMV5TL_CORE core)
{
  int i,b,r;
  
  if(core == NULL)
    return;
  
  core->current_mode = ARM_MODE_SUPERVISOR;
  core->current_bank = ARM_REG_BANK_SUPERVISOR;
  
  core->regs.cpsr = 0x000000D3;
  core->regs.r15 = 0x00000000;
  
  //Reset the un-banked registers. Not done in the actual core but cleaner.
  core->regs.r0 = 0;
  core->regs.r1 = 0;
  core->regs.r2 = 0;
  core->regs.r3 = 0;
  core->regs.r4 = 0;
  core->regs.r5 = 0;
  core->regs.r6 = 0;
  core->regs.r7 = 0;
  
  //Reset the basic banked registers. Not done in the actual core but cleaner.
  core->regs.r8[0] = 0;
  core->regs.r8[1] = 0;
  core->regs.r9[0] = 0;
  core->regs.r9[1] = 0;
  core->regs.r10[0] = 0;
  core->regs.r10[1] = 0;
  core->regs.r11[0] = 0;
  core->regs.r11[1] = 0;
  core->regs.r12[0] = 0;
  core->regs.r12[1] = 0;

  //Reset the sp, lr banked registers. Not done in the actual core but cleaner.
  for(i=0;i<6;i++)
  {
    core->regs.r13[i] = 0;
    core->regs.r14[i] = 0;
  }

  //Reset the saved program status banked registers. Not done in the actual core but cleaner.
  for(i=0;i<5;i++)
  {
    core->regs.spsr[i] = 0;
  }
  
  //Setup the register pointers
  for(b=0;b<6;b++)
  {
    //The un-banked registers are the same for all modes
    core->registers[b][0] = &core->regs.r0;
    core->registers[b][1] = &core->regs.r1;
    core->registers[b][2] = &core->regs.r2;
    core->registers[b][3] = &core->regs.r3;
    core->registers[b][4] = &core->regs.r4;
    core->registers[b][5] = &core->regs.r5;
    core->registers[b][6] = &core->regs.r6;
    core->registers[b][7] = &core->regs.r7;
    
    //The first 5 banked registers are the same for most modes
    if(b != ARM_REG_BANK_FIQ)
      r = 0;  //So use the user and system set when not in FIQ mode
    else
      r = 1;  //Otherwise use the FIQ set
    
    core->registers[b][8] = &core->regs.r8[r];
    core->registers[b][9] = &core->regs.r9[r];
    core->registers[b][10] = &core->regs.r10[r];
    core->registers[b][11] = &core->regs.r11[r];
    core->registers[b][12] = &core->regs.r12[r];
    
    //The sp and lr banked registers have separate versions per bank
    core->registers[b][13] = &core->regs.r13[b];
    core->registers[b][14] = &core->regs.r14[b];
    
    //The pc and the cpsr are the same for all modes
    core->registers[b][15] = &core->regs.r15;
    core->registers[b][16] = &core->regs.cpsr;
    
    //The saved program status registers are only available in the exception modes
    if(b == ARM_REG_BANK_USER)
      core->registers[b][ARM_REG_SPSR_IDX] = NULL;
    else
      core->registers[b][ARM_REG_SPSR_IDX] = &core->regs.spsr[b-1];
  }
  
  //For easy access of important registers
  core->status = (ARMV5TL_STATUS *)&core->regs.cpsr;
  core->program_counter = &core->regs.r15;
  
  //On startup no interrupts set
  core->reset = 0;
  core->irq = 0;
  core->fiq = 0;
  
  //No exceptions either
  core->undefinedinstruction = 0;
  
  //No instructions yet
  core->arm_instruction.instr = 0;
  core->thumb_instruction.instr = 0;
  
  //Test tracing
  core->TraceFilePointer = fopen("test_trace.txt", "w");
  
  //On startup processor is running
  core->run = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlCore(PARMV5TL_CORE core)
{
  u_int32_t *memorypointer;
  u_int32_t  execute = 0;
  
  //Check if running. Do nothing when stopped
  if((core == NULL) && (core->run == 0))
    return;
  
  //Handle one instruction per call

  //Check reset
  if(core->reset == 1)
  {
    //Reset the core by just initializing again
    ArmV5tlSetup(core);
  }
  
  //Check if undefined instruction needs to be handled
  if(core->undefinedinstruction)
  {
    //Handle the undefined instruction
    //For now just freeze the system and return
    core->run = 0;
    return;
  }
  
  //Check interrupt on enabled and active
  if((core->status->flags.I == 0) && (core->irq == 1))
  {
    //Handle the interrupt
  }
  
  //Check fast interrupt on enabled and active
  if((core->status->flags.F == 0) && (core->fiq == 1))
  {
    //Handle the interrupt
  }
  
  //Breakpoint
  if(*core->program_counter == MY_BREAK_POINT)
  {
    memorypointer = NULL;
  }
  
  //Check on which execution state the core is in
  if(core->status->flags.T)
  {
    //Assume program counter needs to be incremented for thumb instructions
    core->pcincrvalue = 2;
    
    //Initial tracing just the pc sequence
    if(core->TraceFilePointer)
    {
      fprintf(core->TraceFilePointer, "pc: 0x%08X  T\n", *core->program_counter);
      fflush(core->TraceFilePointer);
    }
    
    //Handle thumb instructions
    ArmV5tlHandleThumb(core);
  }
  else if(core->status->flags.J)
  {
    //Handle jazelle instructions
    ArmV5tlUndefinedInstruction(core);
  }
  else
  {
    //Assume program counter needs to be incremented for arm instructions
    core->pcincrvalue = 4;
    
    //Instruction fetch for arm state
    memorypointer = (u_int32_t *)ArmV5tlGetMemoryPointer(core, *core->program_counter, ARM_MEMORY_WORD);

    //Check if a valid address is found
    if(memorypointer)
    {
      //get the current instruction
      core->arm_instruction.instr = (u_int32_t)*memorypointer;
    
      //Check the condition bits against the status bits to decide if the instruction needs to be executed
      switch(core->arm_instruction.base.cond)
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

        case ARM_COND_ALWAYS:
          //Always means always
          execute = 1;
          break;

        case ARM_COND_SPECIAL:
          //Unconditional instructions
          execute = 1;
          break;
      }

      //Initial tracing just the pc sequence
      if(core->TraceFilePointer)
      {
        fprintf(core->TraceFilePointer, "pc: 0x%08X  exec: %d\n", *core->program_counter, execute);
        fflush(core->TraceFilePointer);
      }

      //Check if instruction needs to be executed
      if(execute)
      {
        //Check on unconditional instructions
        if(core->arm_instruction.base.cond == 15)
        {
          //Decode the unconditional instructions
          switch(core->arm_instruction.base.type)
          {
            case 0:
              //Change processor state and set endianness
              ArmV5tlUndefinedInstruction(core);
              break;

            case 1:
              //Not used
              //Undefined instruction exception
              ArmV5tlUndefinedInstruction(core);
              break;

            case 2:
            case 3:
              //Cache preload
              ArmV5tlUndefinedInstruction(core);
              break;

            case 4:
              //Save return state and return from exception
              ArmV5tlUndefinedInstruction(core);
              break;

            case 5:
              //Branch with link and change to thumb
              ArmV5tlBranchLinkExchange1(core);
              break;

            case 6:
              //Additional coprocessor register transfer
              ArmV5tlUndefinedInstruction(core);
              break;

            case 7:
              //Additional coprocessor register transfer and undefined instruction
              ArmV5tlUndefinedInstruction(core);
              break;
          }        
        }
        else
        {
          //Decode the type bits
          switch(core->arm_instruction.base.type)
          {
            case 0:
              //Check for multiply and extra load and store instructions. Both bit7 and bit4 are set
              if((core->arm_instruction.type0.it1) && (core->arm_instruction.type0.it2))
              {
                //Check if Multiplies (type is extended to 4 bits)
                if((core->arm_instruction.mul.type == 0) && (core->arm_instruction.mul.nu == 0x09))
                {
                  //Handle multiplies
                  ArmV5tlUndefinedInstruction(core);
                }
                //Check on swap instructions
                else if((core->arm_instruction.instr & 0x0FB00FF0) == 0x01000090)
                {
                  //Handle swaps
                  ArmV5tlUndefinedInstruction(core);
                }
                //Check on load store exclusive (not implemented in V5)
                else if((core->arm_instruction.instr & 0x0FE00FFF) == 0x01800F9F)
                {
                  //Handle load store exclusive
                  ArmV5tlUndefinedInstruction(core);
                }
                //Check if extra load store immediate instructions
                else if(core->arm_instruction.lsx.i)
                {
                  //Handle extra load and store instructions
                  ArmV5tlLSExtraImmediate(core);
                }
                //Leaves the extra load store register instructions
                else
                {
                  ArmV5tlLSExtraRegister(core);
                }
              }
              //Check for miscellaneous instructions. Bit20 (s) needs to be cleared and opcode bit3 is set and bit2 is cleared (So opcodes 8,9,10 and 11)
              else if((core->arm_instruction.type0.s == 0) && ((core->arm_instruction.type0.opcode & 0x0C) == 0x08))
              {
                //Check if move status register instructions
                if(core->arm_instruction.msrr.sbz == 0)
                {
                  //Check if MSR or MRS instruction
                  if(core->arm_instruction.msrr.d)
                  {
                    //Move register to status register
                    ArmV5tlMSRRegister(core);
                  }
                  else
                  {
                    //Move status register to register
                    ArmV5tlMRS(core);
                  }
                }
                else
                {
                  //Decode the miscellaneous instructions
                  //First check on branch instructions
                  if((core->arm_instruction.misc0.op1 == 1) && ((core->arm_instruction.misc0.op2 & 0x0C) == 0x00))
                  {
                    switch(core->arm_instruction.misc0.op2 & 3)
                    {
                      case 0:
                        //Undefined instruction
                        ArmV5tlUndefinedInstruction(core);
                        break;

                      case 1:
                        //Branch and exchange instruction set thumb
                        ArmV5tlBranchExchangeT(core);
                        break;

                      case 2:
                        //Branch and exchange instruction set java (jazelle)
                        //ArmV5tlBranchExchangeJ(core);
                        ArmV5tlUndefinedInstruction(core);
                        break;

                      case 3:
                        //Branch and link / exchange instruction set thumb
                        ArmV5tlBranchLinkExchange2(core);
                        break;
                    }
                  }
                  else
                  {
                    //Count leading zeros
                    //Saturating add / subtract
                    //Software breakpoint
                    //Signed multiplies (type 2)
                    ArmV5tlUndefinedInstruction(core);
                  }
                }
              }
              else
              {
                //Data processing with shift instructions
                ArmV5tlDPRShift(core);
              }
              break;

            case 1:
              //Check for undefined instruction. Bit20 (s) needs to be cleared and opcode bit3 is set and bit2 and bit0 are cleared (So opcodes 8 and 10)
              if((core->arm_instruction.type1.s == 0) && ((core->arm_instruction.type1.opcode & 0x0D) == 0x08))
              {
                //Undefined instruction
                ArmV5tlUndefinedInstruction(core);
              }
              //Check for move immediate to status register. Bit20 (s) needs to be cleared and opcode bit3 and bit0 are set and bit2 is cleared (So opcodes 9 and 11)
              else if((core->arm_instruction.type1.s == 0) && ((core->arm_instruction.type1.opcode & 0x0D) == 0x09))
              {
                //Move immediate to status register
                ArmV5tlMSRImmediate(core);
              }
              else
              {
                //Data processing immediate
                ArmV5tlDPRImmediate(core);
              }
              break;

            case 2:
              //Load / store immediate offset instructions
              ArmV5tlLSImmediate(core);
              break;

            case 3:
              //Check for architecturally undefined instruction
              if((core->arm_instruction.instr & 0x01F000F0) == 0x01F000F0)
              {
                //Architecturally undefined
                ArmV5tlUndefinedInstruction(core);
              }
              //Check on media instructions. Bit4 needs to be set
              else if(core->arm_instruction.type3.it1)
              {
                //Media instructions
                //ARMV6 and above
                ArmV5tlUndefinedInstruction(core);
              }
              else
              {
                //Load / store register offset instructions
                ArmV5tlLSRegister(core);
              }
              break;

            case 4:
              //Load / store multiple instructions
              ArmV5tlLSM(core);
              break;

            case 5:
              //Branch instructions
              ArmV5tlBranch(core);
              break;

            case 6:
              //Coprocessor load / store instruction
              ArmV5tlUndefinedInstruction(core);

              //LDC, MCRR and MRRC instructions
              break;

            case 7:
              //Check if software interrupt
              if(core->arm_instruction.type7.it2)
              {
                //Software interrupt
                ArmV5tlUndefinedInstruction(core);
              }
              else
              {
                //Check on coprocessor register transfer or data processing instructions
                if(core->arm_instruction.type7.it1)
                {
                  //Coprocessor register transfer instructions
                  ArmV5tlMRCMCR(core);
                }
                else
                {
                  //Coprocessor data processing instructions
                  ArmV5tlUndefinedInstruction(core);

                  //CDP

                }
              }
              break;
          }
        }
      }
    }
    //Invalid memory pointer handling
    else
    {
      //Some exception needs to be generated here. Undefined Instruction most likely
      ArmV5tlUndefinedInstruction(core);
    }
  }
  
  //Point to next instruction when needed. When the previous instruction had the program counter as target the increment value is set to zero.
  *core->program_counter += core->pcincrvalue;
}

//----------------------------------------------------------------------------------------------------------------------------------

//Here the specific memory map is programmed
ARMV5TL_ADDRESS_MAP address_map[] = 
{
  { 0x00000000, 0x00007FFF, ArmV5tlSram1 },   //SRAM1
  { 0x00010000, 0x00019FFF, ArmV5tlSram2 },   //SRAM2
  { 0x01C00000, 0x01C00FFF, NULL         },   //System Controller
  { 0x01C01000, 0x01C01FFF, NULL         },   //DRAMC
  { 0x01C02000, 0x01C02FFF, NULL         },   //DMA
  { 0x01C05000, 0x01C05FFF, NULL         },   //SPI0
  { 0x01C06000, 0x01C06FFF, NULL         },   //SPI1
  { 0x01C0A000, 0x01C0AFFF, NULL         },   //TVE
  { 0x01C0B000, 0x01C0BFFF, NULL         },   //TVD
  { 0x01C0C000, 0x01C0CFFF, NULL         },   //TCON
  { 0x01C0E000, 0x01C0EFFF, NULL         },   //VE
  { 0x01C0F000, 0x01C0FFFF, NULL         },   //SD/MMC0
  { 0x01C10000, 0x01C10FFF, NULL         },   //SD/MMC1
  { 0x01C13000, 0x01C13FFF, NULL         },   //USB-OTG
  { 0x01C20000, 0x01C203FF, NULL         },   //CCU
  { 0x01C20400, 0x01C207FF, NULL         },   //INTC
  { 0x01C20800, 0x01C20BFF, NULL         },   //PIO
  { 0x01C20C00, 0x01C20FFF, NULL         },   //TIMER
  { 0x01C21000, 0x01C213FF, NULL         },   //PWM
  { 0x01C21400, 0x01C217FF, NULL         },   //OWA
  { 0x01C21800, 0x01C21BFF, NULL         },   //RSB
  { 0x01C22000, 0x01C223FF, NULL         },   //DAUDIO
  { 0x01C22C00, 0x01C22FFF, NULL         },   //CIR
  { 0x01C23400, 0x01C237FF, NULL         },   //KEYADC
  { 0x01C23C00, 0x01C23FFF, NULL         },   //Audio Codec
  { 0x01C24800, 0x01C24BFF, NULL         },   //TP
  { 0x01C25000, 0x01C253FF, NULL         },   //UART0
  { 0x01C25400, 0x01C257FF, NULL         },   //UART1
  { 0x01C25800, 0x01C25BFF, NULL         },   //UART2
  { 0x01C27000, 0x01C273FF, NULL         },   //TWI0
  { 0x01C27400, 0x01C277FF, NULL         },   //TWI1
  { 0x01C27800, 0x01C27BFF, NULL         },   //TWI2
  { 0x01CB0000, 0x01CB0FFF, NULL         },   //CSI
  { 0x01CE0000, 0x01CE1FFF, NULL         },   //DEFE
  { 0x01CE6000, 0x01CE6FFF, NULL         },   //DEBE
  { 0x01CE7000, 0x01CE7FFF, NULL         },   //DE Interlace
  { 0x80000000, 0x81FFFFFF, NULL         },   //DRAM 32MB
};

//----------------------------------------------------------------------------------------------------------------------------------

void *ArmV5tlGetMemoryPointer(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  int i;
  
  //Need to check on word or short alignment here when in that mode
  //Raise an exception and return NULL pointer
  
  //MMU needs to be implemented here
  
  //Check all the entries in the address map
  for(i=0;i<sizeof(address_map)/sizeof(ARMV5TL_ADDRESS_MAP);i++)
  {
    //Check if the given address is in range of this map item
    if((address >= address_map[i].start) && (address <= address_map[i].end))
    {
      //If so check if it has a function coupled and call it if so
      //Also adjust the address to start from 0 based on the start address in the memory map
      if(address_map[i].function)
        return(address_map[i].function(core, address - address_map[i].start, mode));
      else
        return(NULL);
    }
  }
  
  //Nothing found then return a null address
  return(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Memory and peripheral handlers
void *ArmV5tlSram1(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  u_int32_t idx = address >> 2;
  
  switch(mode)
  {
    case ARM_MEMORY_WORD:
      //Return the word aligned data
      return(&core->sram1[idx].m_32bit);

    case ARM_MEMORY_SHORT:
      //Return the short aligned data
      return(&core->sram1[idx].m_16bit[(address & 2) >> 1]);
      
    case ARM_MEMORY_BYTE:
      //Return the byte aligned data
      return(&core->sram1[idx].m_8bit[address & 3]);
  }
}

void *ArmV5tlSram2(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  u_int32_t idx = address >> 2;
  
  switch(mode)
  {
    case ARM_MEMORY_WORD:
      //Return the word aligned data
      return(&core->sram2[idx].m_32bit);
      
    case ARM_MEMORY_SHORT:
      //Return the short aligned data
      return(&core->sram1[idx].m_16bit[(address & 2) >> 1]);
      
    case ARM_MEMORY_BYTE:
      //Return the byte aligned data
      return(&core->sram1[idx].m_8bit[address & 3]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Undefined instruction
void ArmV5tlUndefinedInstruction(PARMV5TL_CORE core)
{
  //Signal an undefined instruction
  core->undefinedinstruction = 1;
  
  //Do not increment the pc to be able to track the wrong instruction
  core->pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Data processing immediate and register shift
void ArmV5tlDPRShift(PARMV5TL_CORE core)
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
//Load and store immediate instruction handling
void ArmV5tlLSImmediate(PARMV5TL_CORE core)
{
  //Get the input data. Assume target is a word
  u_int32_t mode = ARM_MEMORY_WORD;
  u_int32_t vn = *core->registers[core->current_bank][core->arm_instruction.lsi.rn];
  u_int32_t addr;
  
  //Amend the value when r15 (pc) is used
  if(core->arm_instruction.lsi.rn == 15)
  {
    vn += 8;
  }
  
  //Check on pre or post indexed
  if(core->arm_instruction.lsi.p == 0)
  {
    //Do post indexed
    addr = vn;
    
    //Update rn
    if(core->arm_instruction.lsi.u)
    {
      //When u = 1 add the offset
      *core->registers[core->current_bank][core->arm_instruction.lsi.rn] += core->arm_instruction.lsi.of;
    }
    else
    {
      //When u = 0 subtract the offset
      *core->registers[core->current_bank][core->arm_instruction.lsi.rn] -= core->arm_instruction.lsi.of;
    }
  }
  else
  {
    //Immediate offset or pre-indexed
    if(core->arm_instruction.lsi.u)
    {
      //When u = 1 add the offset
      addr = vn + core->arm_instruction.lsi.of;
    }
    else
    {
      //When u = 0 subtract the offset
      addr = vn - core->arm_instruction.lsi.of;
    }
    
    //Check if rn needs to be updated
    if(core->arm_instruction.lsi.w)
      *core->registers[core->current_bank][core->arm_instruction.lsi.rn] = addr;
  }
  
  //Check if action needs to be done on a byte
  if(core->arm_instruction.lsi.b)
  {
    //Switch target to byte
    mode = ARM_MEMORY_BYTE;
  }
  
  //Do the actual processing
  ArmV5tlLS(core, addr, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store register instruction handling
void ArmV5tlLSRegister(PARMV5TL_CORE core)
{
  //Get the input data. Assume target is a word
  u_int32_t mode = ARM_MEMORY_WORD;
  u_int32_t vm = *core->registers[core->current_bank][core->arm_instruction.lsr.rm];
  u_int32_t vn = *core->registers[core->current_bank][core->arm_instruction.lsr.rn];
  u_int32_t addr;
  u_int32_t sa;

  //Amend the values when r15 (pc) is used
  if(core->arm_instruction.lsr.rn == 15)
  {
    vn += 8;
  }

  //Same for the to be shifted register
  if(core->arm_instruction.lsr.rm == 15)
  {
    vm += 8;
  }
  
  //shifting is only done when scaled mode bits11:4 not zero
  if(core->arm_instruction.lsrn.ns != 0)
  {
    //Get the immediate shift amount
    sa = core->arm_instruction.lsr.sa;

    //Take action based on the shift mode
    switch(core->arm_instruction.lsr.sm)
    {
      case ARM_SHIFT_MODE_LSL:
        //For lsl shifting is always done since sa can't be zero
        vm <<= sa;
        break;

      case ARM_SHIFT_MODE_LSR:
        //Check if an actual shift amount is given
        if(sa == 0)
        {
          //When not, it is treated as 32
          vm = 0;
        }
        else
        {
          //Normal lsr shifting is done
          vm >>= sa;
        }
        break;

      case ARM_SHIFT_MODE_ASR:
        //Check if an actual shift amount is given
        if(sa == 0)
        {
          //When not, it is treated as 32
          if((vm & 0x80000000) == 0)
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
          //Check if sign needs to be extended
          if((vm & 0x80000000) == 0)
          {
            //No so normal shift right does the trick
            vm >>= sa;
          }
          else
          {
            //Otherwise inversions before and after shifting does the trick
            vm = ~(~vm >> sa);
          }
        }
        break;

      case ARM_SHIFT_MODE_ROR:
        if(sa == 0)
        {
          //Special case here where the shift amount is 0. Rotate right with extend. Carry is an extra bit
          vm = (core->status->flags.C << 31) | (vm >> 1);
        }
        else
        {
          //rotate the bits
          vm = (vm >> sa) | (vm << (32 - sa));
        }
        break;
    }
  }
  
  //Check on pre or post indexed
  if(core->arm_instruction.lsr.p == 0)
  {
    //Do post indexed
    addr = vn;
    
    //Update rn
    if(core->arm_instruction.lsr.u)
    {
      //When u = 1 add the offset
      *core->registers[core->current_bank][core->arm_instruction.lsr.rn] += vm;
    }
    else
    {
      //When u = 0 subtract the offset
      *core->registers[core->current_bank][core->arm_instruction.lsr.rn] -= vm;
    }
  }
  else
  {
    //Immediate offset or pre-indexed
    if(core->arm_instruction.lsr.u)
    {
      //When u = 1 add the offset
      addr = vn + vm;
    }
    else
    {
      //When u = 0 subtract the offset
      addr = vn - vm;
    }
    
    //Check if rn needs to be updated
    if(core->arm_instruction.lsr.w)
      *core->registers[core->current_bank][core->arm_instruction.lsr.rn] = addr;
  }
   
  //Check if action needs to be done on a byte
  if(core->arm_instruction.lsr.b)
  {
    //Switch target to byte
    mode = ARM_MEMORY_BYTE;
  }
  
  //Do the actual processing
  ArmV5tlLS(core, addr, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store extra immediate instruction handling
void ArmV5tlLSExtraImmediate(PARMV5TL_CORE core)
{
  //The offset is constructed by shifting the high part 4 positions and oring the low part. (rs = immedH, rm = immedL)
  u_int32_t of = (core->arm_instruction.lsx.rs << 4) | core->arm_instruction.lsx.rm;
  u_int32_t vn = *core->registers[core->current_bank][core->arm_instruction.lsx.rn];
  u_int32_t mode = ARM_MEMORY_WORD;
  u_int32_t addr;
  
  //Amend the value when r15 (pc) is used
  if(core->arm_instruction.lsx.rn == 15)
  {
    vn += 8;
  }
  
  //Check on pre or post indexed
  if(core->arm_instruction.lsx.p == 0)
  {
    //Do post indexed
    addr = vn;
    
    //Update rn
    if(core->arm_instruction.lsx.u)
    {
      //When u = 1 add the offset
      *core->registers[core->current_bank][core->arm_instruction.lsx.rn] += of;
    }
    else
    {
      //When u = 0 subtract the offset
      *core->registers[core->current_bank][core->arm_instruction.lsx.rn] -= of;
    }
  }
  else
  {
    //Immediate offset or pre-indexed
    if(core->arm_instruction.lsx.u)
    {
      //When u = 1 add the offset
      addr = vn + of;
    }
    else
    {
      //When u = 0 subtract the offset
      addr = vn - of;
    }
    
    //Check if rn needs to be updated
    if(core->arm_instruction.lsx.w)
      *core->registers[core->current_bank][core->arm_instruction.lsx.rn] = addr;
  }
  
  //Check if normal half word instructions
  if(core->arm_instruction.lsx.op1 == 1)
  {
    //Set mode to short for half word
    mode = ARM_MEMORY_SHORT;
  }
  //Check if sign extend instructions
  else if(core->arm_instruction.lsx.l)
  {
    //Check if short or byte
    if(core->arm_instruction.lsx.op1 & 1)
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
    core->arm_instruction.lsx.l = ~(core->arm_instruction.lsx.op1 & 1);

    //Make sure rd is even
    core->arm_instruction.lsx.rd &= 0x0E;
    
    //Process the first word
    ArmV5tlLS(core, addr, mode);
    
    //Add 4 to the address for the next word
    addr += 4;
    
    //Select the next register
    core->arm_instruction.lsx.rd++;
  }
  
  //Do the actual processing
  ArmV5tlLS(core, addr, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store extra immediate instruction handling
void ArmV5tlLSExtraRegister(PARMV5TL_CORE core)
{
  //Get the input data. Assume target is a word
  u_int32_t mode = ARM_MEMORY_WORD;
  u_int32_t vm = *core->registers[core->current_bank][core->arm_instruction.lsx.rm];
  u_int32_t vn = *core->registers[core->current_bank][core->arm_instruction.lsx.rn];
  u_int32_t addr;

  //Amend the values when r15 (pc) is used
  if(core->arm_instruction.lsx.rn == 15)
  {
    vn += 8;
  }

  //Same for the to be shifted register
  if(core->arm_instruction.lsx.rm == 15)
  {
    vm += 8;
  }
  
  //Check on pre or post indexed
  if(core->arm_instruction.lsx.p == 0)
  {
    //Do post indexed
    addr = vn;
    
    //Update rn
    if(core->arm_instruction.lsx.u)
    {
      //When u = 1 add the offset
      *core->registers[core->current_bank][core->arm_instruction.lsx.rn] += vm;
    }
    else
    {
      //When u = 0 subtract the offset
      *core->registers[core->current_bank][core->arm_instruction.lsx.rn] -= vm;
    }
  }
  else
  {
    //Immediate offset or pre-indexed
    if(core->arm_instruction.lsx.u)
    {
      //When u = 1 add the offset
      addr = vn + vm;
    }
    else
    {
      //When u = 0 subtract the offset
      addr = vn - vm;
    }
    
    //Check if rn needs to be updated
    if(core->arm_instruction.lsx.w)
      *core->registers[core->current_bank][core->arm_instruction.lsx.rn] = addr;
  }

  //Check if normal half word instructions
  if(core->arm_instruction.lsx.op1 == 1)
  {
    //Set mode to short for half word
    mode = ARM_MEMORY_SHORT;
  }
  //Check if sign extend instructions
  else if(core->arm_instruction.lsx.l)
  {
    //Check if short or byte
    if(core->arm_instruction.lsx.op1 & 1)
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
    core->arm_instruction.lsx.l = ~(core->arm_instruction.lsx.op1 & 1);

    //Make sure rd is even
    core->arm_instruction.lsx.rd &= 0x0E;
    
    //Process the first word
    ArmV5tlLS(core, addr, mode);
    
    //Add 4 to the address for the next word
    addr += 4;
    
    //Select the next register
    core->arm_instruction.lsx.rd++;
  }
  
  //Do the actual processing
  ArmV5tlLS(core, addr, mode);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store instruction handling
void ArmV5tlLS(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  void *memory;
  u_int32_t memtype = mode & ARM_MEMORY_MASK;
    
  //Get a pointer to the given address based on the mode
  memory = ArmV5tlGetMemoryPointer(core, address, memtype);

  //Check if address is valid
  if(memory)
  {
    //Perform the requested action on the requested size mode
    switch(memtype)  
    {
      case ARM_MEMORY_WORD:
        //Check if a load or a store is requested
        if(core->arm_instruction.lsr.l)
        {
          //Load from found memory address
          *core->registers[core->current_bank][core->arm_instruction.lsr.rd] = *(u_int32_t *)memory;
        }
        else
        {
          //Store to found memory address
          *(u_int32_t *)memory = *core->registers[core->current_bank][core->arm_instruction.lsr.rd];
        }
        break;
        
      case ARM_MEMORY_SHORT:
        //Check if a load or a store is requested
        if(core->arm_instruction.lsr.l)
        {
          //Load from found memory address
          *core->registers[core->current_bank][core->arm_instruction.lsr.rd] = *(u_int16_t *)memory;
          
          //Sign extend here when needed
          if((mode & ARM_SIGN_EXTEND) && (*(u_int16_t *)memory & 0x8000))
          {
            *core->registers[core->current_bank][core->arm_instruction.lsr.rd] |= 0xFFFF0000;
          }
        }
        else
        {
          //Store to found memory address
          *(u_int16_t *)memory = *core->registers[core->current_bank][core->arm_instruction.lsr.rd];
        }
        break;
        
      case ARM_MEMORY_BYTE:
        //Check if a load or a store is requested
        if(core->arm_instruction.lsr.l)
        {
          //Load from found memory address
          *core->registers[core->current_bank][core->arm_instruction.lsr.rd] = *(u_int8_t *)memory;
          
          //Sign extend here when needed
          if((mode & ARM_SIGN_EXTEND) && (*(u_int8_t *)memory & 0x80))
          {
            *core->registers[core->current_bank][core->arm_instruction.lsr.rd] |= 0xFFFFFF00;
          }
        }
        else
        {
          //Store to found memory address
          *(u_int8_t *)memory = (u_int8_t)*core->registers[core->current_bank][core->arm_instruction.lsr.rd];
        }
        break;
    }

    //Check if program counter used as target
    if((core->arm_instruction.lsr.l) && (core->arm_instruction.lsr.rd == 15))
    {
      //Signal no increment if so
      core->pcincrvalue = 0;
    }
  }
  else
  {
    //Need exception here
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store multiple instruction handling
void ArmV5tlLSM(PARMV5TL_CORE core)
{
  u_int32_t address = *core->registers[core->current_bank][core->arm_instruction.type4.rn];
  u_int32_t *memory;
  u_int32_t reglist = core->arm_instruction.instr & 0x0000FFFF;
  int       numregs = 0;
  int       bank = core->current_bank;
  int       i;
  
  //Check if S bit is set. Needed to determine which register bank is used.
  if(core->arm_instruction.type4.s)
  {
    //Check if r15 is included in the list and it is a load instruction
    if((core->arm_instruction.type4.r15) && (core->arm_instruction.type4.l))
    {
      //Need to restore cpsr from spsr
      //Check if there is a saved status register for the current register bank
      if(core->registers[core->current_bank][ARM_REG_SPSR_IDX])
      {
        //Copy the spsr if available
        *core->registers[core->current_bank][core->arm_instruction.mrs.rd] = *core->registers[core->current_bank][ARM_REG_SPSR_IDX];
      }
      
      //Handle the possible mode change
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
      //For all stores and the loads without r15 the user mode registers are used
      bank = ARM_REG_BANK_USER;
    }
  }
  
  //Check if base address not included in the range (Increment / decrement before)
  if(core->arm_instruction.type4.p)
  {
    //Not includes so check if range is below or above the base address
    if(core->arm_instruction.type4.u)
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
  
  //Lowest register needs to be in lowest address, so list is walked through different for increment or decrement
  //Check if increment or decrement
  if(core->arm_instruction.type4.u)
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
          if(core->arm_instruction.type4.l)
          {
            //Load the register with the data from memory
            *core->registers[bank][i] = *memory;
          }
          else
          {
            //Store the register to memory
            *memory = *core->registers[bank][i];
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
          if(core->arm_instruction.type4.l)
          {
            //Load the register with the data from memory
            *core->registers[bank][i] = *memory;
          }
          else
          {
            //Store the register to memory
            *memory = *core->registers[bank][i];
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
  if(core->arm_instruction.type4.w)
  {
    //Check if increment or decrement
    if(core->arm_instruction.type4.u)
    {
      //Increment the base address
      *core->registers[core->current_bank][core->arm_instruction.type4.rn] += (numregs * 4);
    }
    else
    {
      //Decrement the base address
      *core->registers[core->current_bank][core->arm_instruction.type4.rn] -= (numregs * 4);
    }
  }
  
  //Check if r15 is included in the list and it is a load instruction
  if((core->arm_instruction.type4.r15) && (core->arm_instruction.type4.l))
  {
    //Check if thumb state bit needs to be updated
    if(core->arm_instruction.type4.s == 0)
    {
      //When s == 1 this is already done by restoring cpsr from spsr. For s == 0 it needs to be taken from the pc
      core->status->flags.T = *core->program_counter & 1;
    }
    
    //Make sure the program counter is not on an invalid byte boundary
    *core->program_counter &= 0xFFFFFFFE;
    
    //Signal no increment of pc if so
    core->pcincrvalue = 0;
  }  
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move immediate to status register
void ArmV5tlMSRImmediate(PARMV5TL_CORE core)
{
  //Get the input data
  u_int32_t vm = core->arm_instruction.msri.im;
  u_int32_t ri = core->arm_instruction.msri.ri << 1;
  
  //Check if rotation is needed
  if(ri)
  {
    //rotate the bits
    vm = (vm >> ri) | (vm << (32 - ri));
  }
  
  //Go and do the actual processing
  ArmV5tlMSR(core, vm);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move register to status register
void ArmV5tlMSRRegister(PARMV5TL_CORE core)
{
  u_int32_t vm = *core->registers[core->current_bank][core->arm_instruction.msrr.rm];
  
  //Go and do the actual processing
  ArmV5tlMSR(core, vm);
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move to status register
void ArmV5tlMSR(PARMV5TL_CORE core, u_int32_t data)
{
  u_int32_t bytemask = 0x00000000;
  
  //Setup the byte mask based on the field mask bits
  //Control field
  if(core->arm_instruction.msri.c)
    bytemask |= 0x000000FF;
  
  //Extension field
  if(core->arm_instruction.msri.x)
    bytemask |= 0x0000FF00;
  
  //Status field
  if(core->arm_instruction.msri.s)
    bytemask |= 0x00FF0000;
  
  //Flags field
  if(core->arm_instruction.msri.f)
    bytemask |= 0xFF000000;
  
  //Check if current mode is privileged or user mode
  if(core->current_mode != ARM_MODE_USER)
  {
    //privileged mode so make sure the correct fields are available
    bytemask &= (ARM_USER_MASK | ARM_PRIVILEGED_MASK);
  }
  else
  {
    //User mode so only user bits can be changed
    bytemask &= ARM_USER_MASK;
  }
  
  //Check which register is the destination
  if(core->arm_instruction.msri.r == 0)
  {
    //Save to cpsr
    core->status->word = (core->status->word & ~bytemask) | (data & bytemask);
    
    //Handle the possible mode change
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
    //Check if there is a saved status register for the current register bank
    if(core->registers[core->current_bank][ARM_REG_SPSR_IDX])
    {
      //Mask the not allowed bits
      bytemask &= (ARM_USER_MASK | ARM_PRIVILEGED_MASK | ARM_STATE_MASK);
      
      //Save to spsr
      *core->registers[core->current_bank][ARM_REG_SPSR_IDX] = (*core->registers[core->current_bank][ARM_REG_SPSR_IDX] & ~bytemask) | (data & bytemask);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move status register to register
void ArmV5tlMRS(PARMV5TL_CORE core)
{
  //Check if the cpsr or the spsr is the source
  if(core->arm_instruction.mrs.r == 0)
  {
    //Copy the cpsr into the destination register
    *core->registers[core->current_bank][core->arm_instruction.mrs.rd] = core->status->word;
  }
  else
  {
    //Check if there is a saved status register for the current register bank
    if(core->registers[core->current_bank][ARM_REG_SPSR_IDX])
    {
      //Copy the spsr if available
      *core->registers[core->current_bank][core->arm_instruction.mrs.rd] = *core->registers[core->current_bank][ARM_REG_SPSR_IDX];
    }
  }

  //Check if program counter used as destination
  if(core->arm_instruction.mrs.rd == 15)
  {
    //Signal no increment if so
    core->pcincrvalue = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Move register to coprocessor or coprocessor to register
void ArmV5tlMRCMCR(PARMV5TL_CORE core)
{
//  u_int32_t cpn = core->arm_instruction.mrcmcr.cpn;
//  u_int32_t crm = core->arm_instruction.mrcmcr.crm;
//  u_int32_t crn = core->arm_instruction.mrcmcr.crn;
  
  //For now only coprocessor 15 read is implemented
  if((core->arm_instruction.mrcmcr.cpn == 15) && (core->arm_instruction.mrcmcr.d))
  {
    //Clear destination register to indicate MMU is disabled and vectors are in low memory
    *core->registers[core->current_bank][core->arm_instruction.mrcmcr.rd] = 0;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch instructions
void ArmV5tlBranch(PARMV5TL_CORE core)
{
  int32_t address = core->arm_instruction.type5.offset << 2;
  
  //Check if negative address given
  if(address & 0x02000000)
  {
    //Extend the sign if so
    address |= 0xFC000000;
  }
  
  //Check if link register needs to be set
  if(core->arm_instruction.type5.l)
  {
    //Load the address after this instruction to the link register r14
    *core->registers[core->current_bank][14] = *core->program_counter + 4;
  }

  //Calculate the new address. The actual pc point to instruction address plus 8
  *core->program_counter += (8 + address);

  //Signal no increment of the pc
  core->pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with link and exchange instructions
void ArmV5tlBranchLinkExchange1(PARMV5TL_CORE core)
{
  int32_t address = core->arm_instruction.type5.offset << 2;
  
  //Check if negative address given
  if(address & 0x02000000)
  {
    //Extend the sing if so
    address |= 0xFC000000;
  }
  
  //Load the address after this instruction to the link register r14
  *core->registers[core->current_bank][14] = *core->program_counter + 4;

  //Merge the H bit into the address (is l bit from type5 instruction)
  address |= (core->arm_instruction.type5.l << 1);
  
  //Calculate the new address. The actual pc point to instruction address plus 8
  *core->program_counter += (8 + address);

  //Signal the processor to continue in thumb state
  core->status->flags.T = 1;
  
  //Signal no increment of the pc
  core->pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with link and exchange instructions
void ArmV5tlBranchLinkExchange2(PARMV5TL_CORE core)
{
  u_int32_t address = *core->registers[core->current_bank][core->arm_instruction.misc0.rm];
  
  //Load the address after this instruction to the link register r14
  *core->registers[core->current_bank][14] = *core->program_counter + 4;

  //Set the new address. Needs to be on a thumb boundary
  *core->program_counter = address & 0xFFFFFFFE;

  //Signal the processor to continue in either thumb or arm state
  core->status->flags.T = address & 1;
  
  //Signal no increment of the pc
  core->pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Handle branch with exchange instructions
void ArmV5tlBranchExchangeT(PARMV5TL_CORE core)
{
  u_int32_t address = *core->registers[core->current_bank][core->arm_instruction.misc0.rm];
  
  //Set the new address. Needs to be on a thumb boundary
  *core->program_counter = address & 0xFFFFFFFE;

  //Signal the processor to continue in either thumb or arm state
  core->status->flags.T = address & 1;
  
  //Signal no increment of the pc
  core->pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

//Handle branch with exchange instructions
void ArmV5tlBranchExchangeJ(PARMV5TL_CORE core)
{
  u_int32_t address = *core->registers[core->current_bank][core->arm_instruction.misc0.rm];
  
  //This is not correct and needs system info to do the correct things
  
  //Set the new address. Needs to be on a thumb boundary
  *core->program_counter = address & 0xFFFFFFFE;

  //Signal the processor to continue in either jazelle or arm state
  core->status->flags.J = address & 1;
  
  //Signal no increment of the pc
  core->pcincrvalue = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------
