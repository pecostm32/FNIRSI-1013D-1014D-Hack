//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "armv5tl.h"
#include "armv5tl_thumb.h"
#include "f1c100s.h"

#include "armthread.h"

//----------------------------------------------------------------------------------------------------------------------------------

//#define MY_BREAK_POINT 0x800306f4
//#define MY_BREAK_POINT 0x8002CF3C      //function called from setup_display_lib
//#define MY_BREAK_POINT 0x8002FAD4      //faulty jump due to missing data
//#define MY_BREAK_POINT 0x800197AC
//#define MY_BREAK_POINT 0x8003534C
//#define MY_BREAK_POINT 0x80035334      //call to sys_init_uart0
//#define MY_BREAK_POINT 0x800182FC      //In this data is multiplied by 0x78
//#define MY_BREAK_POINT 0x80035320      //main
//#define MY_BREAK_POINT  0x80035350   //call to touch panel setup
//#define MY_BREAK_POINT  0x800353d4   //Infinit loop after sd card error


//#define MY_BREAK_POINT  0x8001933C     //Within setup_display_lib function

//#define MY_BREAK_POINT_1  0x8001d0D0
//#define MY_BREAK_POINT_2  0x8001d0D8

//#define MY_BREAK_POINT_1  0x8001cdc8   //Function that calls a function pointer

//#define MY_BREAK_POINT_2  0x8002f028   //Within the function called via the function pointer
//#define MY_BREAK_POINT_1  0x8002f02C   //Function that calls a function pointer


//#define MY_BREAK_POINT_1  0x80023F88   //SD card stuf

//#define MY_BREAK_POINT_1  0x80035444    //Start of endless main loop

//#define MY_BREAK_POINT_1  0x80017AD4     //I2C read after port read

//#define MY_BREAK_POINT_1  0x80017BC0      //I2C after byte read res in r4

//800178e0
//#define MY_BREAK_POINT_1  0x80017868      //After I2C coordinate read r1,r3 x
//#define MY_BREAK_POINT_2  0x800178A8      //r1,r12 y


//#define MY_BREAK_POINT_1  0x80024ED4      //end of init parameter storage
//#define MY_BREAK_POINT_1  0x80025090      //end of write parameter storage

//#define MY_BREAK_POINT_2  0x80024AF8        //end of get setting from parameter storage
//#define MY_BREAK_POINT_1  0x80024A74        //first check on 0x55

//#define MY_BREAK_POINT_1  0x800178B4

//#define MY_BREAK_POINT_1  0x80035350     //Call from main to tp_i2c_setup

//#define MY_BREAK_POINT_1  0x80018c28       //End of display text (Call FUN_80019A6C)

//#define MY_BREAK_POINT_1  0x800193cc       //Something within possible save context function

//#define MY_BREAK_POINT_1  0x800353d4   //endless loop in main

//#define MY_BREAK_POINT_1  0x8000b6f4   //Use of font 0

//#define MY_BREAK_POINT_1  0x80018024  //font function
//#define MY_BREAK_POINT_2  0x80018030  //font function


//#define MY_BREAK_POINT_1  0x8001263c  //End of time div print

#define MY_BREAK_POINT_2  0x80035454  //font function


#define MY_BREAK_POINT_1  0x80035454  //while loop in test code

//----------------------------------------------------------------------------------------------------------------------------------

//#define MY_TRACE_START_POINT    0x8003532c   //Call to some_memory_stuff (now mmu_setup)

//#define MY_TRACE_START_POINT    0x8001933C  //Address where setup_display_lib is called

//#define MY_TRACE_START_POINT    0x8002f028  //Address where setup_display_lib is called
//#define MY_TRACE_STOP_POINT    0x8001933C  //Address where setup_display_lib is called

//#define MY_TRACE_START_POINT    0x80035360   //Address where sd card setup and check is called
//#define MY_TRACE_START_POINT    0x80035444   //Address where the main loop starts

//#define MY_TRACE_START_POINT    0x8003534c     //Address in main from where setup_display lib is called

//#define MY_TRACE_START_POINT    0x80018bf8    //Display text function

//#define MY_TRACE_START_POINT    0x80035390    //Main start of sd error on display

//#define MY_TRACE_START_POINT    0x80012280   //Usage of font 0

//#define MY_TRACE_START_POINT    0x80000658
#define MY_TRACE_START_POINT    0x80035320


//#define TRACE_ENABLED

//----------------------------------------------------------------------------------------------------------------------------------

//#define TRACE_FILE_NAME         "test_trace"
//#define TRACE_FILE_NAME           "mmu_p15_setup"

//#define TRACE_FILE_NAME         "screen_buf_clear"
//#define TRACE_FILE_NAME         "sd_card_check"
//#define TRACE_FILE_NAME         "main_loop_trace_2/main_loop"
//#define TRACE_FILE_NAME         "setup_display_lib_trace/display_setup"

//#define TRACE_FILE_NAME         "display_text_trace/display_text"
//#define TRACE_FILE_NAME         "display_text_test/display_text_test"
#define TRACE_FILE_NAME         "main_startup/main_startup"

//----------------------------------------------------------------------------------------------------------------------------------

pthread_t arm_core_thread;

int quit_armcore_thread_on_zero = 0;

//----------------------------------------------------------------------------------------------------------------------------------

int startarmcore(void)
{
  //Setup for keeping the arm core thread running
  quit_armcore_thread_on_zero = 1;
  
  //Start up the arm core thread
  return(pthread_create(&arm_core_thread, NULL, armcorethread, NULL));
}

//----------------------------------------------------------------------------------------------------------------------------------

void stoparmcore(void)
{
  //Stop the arm core thread
  quit_armcore_thread_on_zero = 0;
}

//----------------------------------------------------------------------------------------------------------------------------------

void *armcorethread(void *arg)
{
  //Setup a key for getting the shared memory
  key_t key = SHARED_MEMORY_KEY;
 
  //Get a handle to the shared memory
  int shmid = shmget(key, sizeof(ARMV5TL_CORE), 0666 | IPC_CREAT); 

  //Check on error shmid == -1.
  if(shmid == -1)
  {
    //On error exit the thread the way it is supposed to
    pthread_exit(NULL);
  }
  
  //Attach to the shared memory
  PARMV5TL_CORE parm_core = (PARMV5TL_CORE)shmat(shmid, (void*)0, 0);
  
  //Initialize the core
  ArmV5tlSetup(parm_core);
  
  //Load a program to arm memory
  FILE *fp = fopen("scope_spl.bin", "rb");
//  FILE *fp = fopen("fnirsi_1013d_bootloader.bin", "rb");
  
  
  
  if(fp)
  {
    fread(parm_core->sram1, 1, 32768, fp);
    
    fclose(fp);
  }

  //Open the flash image
  //parm_core->FlashFilePointer = fopen("W25Q32_scope.bin", "rb");
  parm_core->FlashFilePointer = fopen("scope_test_code.bin", "rb");
  
  //Open the parameter storage file
  parm_core->fpgadata.param_file = fopen("scope_settings.bin", "rb+");
  
  //Keep running the core until stopped
  while(quit_armcore_thread_on_zero)
  {
    ArmV5tlCore(parm_core);
  }

  //Close the files used in the emulator
  if(parm_core->FlashFilePointer)
  {
    fclose(parm_core->FlashFilePointer);
  }
  
  if(parm_core->fpgadata.param_file)
  {
    fclose(parm_core->fpgadata.param_file);
  }
  
  //detach from shared memory  
  shmdt(parm_core);   

  //destroy the shared memory 
  shmctl(shmid, IPC_RMID, NULL); 
  
  //Exit the thread the way it is supposed to
  pthread_exit(NULL);
}

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlSetup(PARMV5TL_CORE core)
{
  int  b,r;
  
  char tracefilename[256];
  
  if(core == NULL)
    return;
  
  //Clear everything
  memset(core, 0, sizeof(ARMV5TL_CORE));
  
  //Switch to the supervisor mode
  core->current_mode = ARM_MODE_SUPERVISOR;
  core->current_bank = ARM_REG_BANK_SUPERVISOR;

  //Set the status register to reflect this mode  
  core->regs.cpsr = 0x000000D3;
  
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
  
  //Set peripheral handler for the F1C100s
  core->peripheralfunction = F1C100sProcess;
  
#ifdef TRACE_ENABLED  
  //Print the trace file name
  snprintf(tracefilename, 64, "%s_%06d.bin", TRACE_FILE_NAME, core->tracefileindex);
  core->TraceFilePointer = fopen(tracefilename, "wb");
  
  //Enable tracing into buffer
  core->tracebufferenabled = 1;
  
  //Start tracing when address is hit
  core->tracetriggeraddress = MY_TRACE_START_POINT;
#endif
  
  core->breakpointaddress = MY_BREAK_POINT_1;
  
  //Setup port handling functions
  core->f1c100s_port[0].porthandler = PortAHandler;
  core->f1c100s_port[0].portdata = &core->touchpaneldata;

  core->f1c100s_port[4].porthandler = PortEHandler;
  core->f1c100s_port[4].portdata = &core->fpgadata;
  
  sprintf(core->fpgadata.file_name, "fpga_trace/fpga_trace_a");
  sprintf(tracefilename, "%s_%06d.txt", core->fpgadata.file_name, core->fpgadata.file_index);
  core->fpgadata.trace_file = fopen(tracefilename, "w");
  
//  core->fpgadata.param_trace = fopen("param_trace/param_trace_3.txt", "w");
  
  core->fpgadata.cmd0x14count[0] = 0x07;
  core->fpgadata.cmd0x14count[1] = 0xD5;
  
  //On startup processor is running
  core->run = 1;
}

//----------------------------------------------------------------------------------------------------------------------------------

void ArmV5tlCore(PARMV5TL_CORE core)
{
  u_int32_t *memorypointer;
  u_int32_t  execute = 0;
  int        i;
  char       tracefilename[64];
  
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
    //Load exception r14 with current pc plus 4. The manual states for entering and returning from interrupt sub r14, r14, #4; stmfd sp!, {r14}; ...; ldmfd sp!, {pc}^
    *core->registers[ARM_REG_BANK_IRQ][14] = *core->program_counter + 4;
    
    //Load exception spsr with current psr
    *core->registers[ARM_REG_BANK_IRQ][ARM_REG_SPSR_IDX] = core->status->word;
      
    //Switch to irq exception mode
    core->status->flags.M = ARM_MODE_IRQ;
    
    //Return to arm execution state
    core->status->flags.T = 0;
    core->status->flags.J = 0;
    
    //Disable interrupts
    core->status->flags.I = 1;
    
    //Clear the interrupt flag to signal it has been handled
    core->irq = 0;
    
    //Load endianness from cp15 (not implemented here since it is not used in the scope)
    
    //Switch the current bank to the irq bank
    core->current_bank = ARM_REG_BANK_IRQ;
    
    //Set the internal mode to irq mode
    core->current_mode = ARM_MODE_IRQ;
    
    //Load pc with the irq vector address. Depending om cp15 it could also be 0xFFFF0018, but not implemented here.
    *core->program_counter = 0x00000018;
  }
  
  //Check fast interrupt on enabled and active
  if((core->status->flags.F == 0) && (core->fiq == 1))
  {
    //Handle the interrupt
  }
  
  //Breakpoint
  if(*core->program_counter == core->breakpointaddress)
  {
    memorypointer = NULL;
  }

  if(*core->program_counter == MY_BREAK_POINT_2)
  {
    memorypointer = NULL;
  }
  
  //Check if trace buffer writing enabled
  if(core->tracebufferenabled)
  {
    //Check on trace trigger address
    if((core->tracetriggeraddress == *core->program_counter) && (core->tracetriggered == 0))
    {
      //Enable trace writing
      core->tracetriggered = 1;
      
      //Check if there is a file to write to
      if(core->TraceFilePointer)
      {
        //Write pre trigger data to the trace file
        for(i=0;i<(sizeof(core->tracebuffer) / sizeof(ARMV5TL_TRACE_ENTRY));i++)
        {
          fwrite(&core->tracebuffer[core->traceindex], 1, sizeof(ARMV5TL_TRACE_ENTRY), core->TraceFilePointer);
          
          //Point to next trace buffer entry and keep it in range of the trace buffer size
          core->traceindex = (core->traceindex + 1) % (sizeof(core->tracebuffer) / sizeof(ARMV5TL_TRACE_ENTRY));
        }

        //Set trace count for file splitting
        core->tracecount = i;
      }
    }
    
    //Clear the memory data in the trace buffer
    core->tracebuffer[core->traceindex].memory_address = 0;
    core->tracebuffer[core->traceindex].data_width = 0;
    core->tracebuffer[core->traceindex].data_count = 0;
    core->tracebuffer[core->traceindex].memory_direction = 0;

    //Clear the data field
    memset(core->tracebuffer[core->traceindex].data, 0, sizeof(core->tracebuffer[core->traceindex].data));
  }
  
  //Check on which execution state the core is in
  if(core->status->flags.T)
  {
    //Assume program counter needs to be incremented for thumb instructions
    core->pcincrvalue = 2;
    
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
          if((core->status->flags.C == 0) || (core->status->flags.Z))
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
          if((core->status->flags.N != core->status->flags.V) || (core->status->flags.Z))
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

      //Check if tracing into buffer is enabled.
      if(core->tracebufferenabled)
      {
        //Setup the trace buffer entry for arm tracing
        core->tracebuffer[core->traceindex].instruction_address = *core->program_counter;
        core->tracebuffer[core->traceindex].instruction_word = core->arm_instruction.instr;
        core->tracebuffer[core->traceindex].execution_status = execute;
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
                  //Handle multiplies (MUL, MULS, MLA, MLAS, UMULL, UMULLS, UMLAL, UMLALS, SMULL, SMULLS, SMLAL, SMLALS)
                  ArmV5tlMUL(core);
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
                  //Check on count leading zeros
                  else if((core->arm_instruction.instr & 0x0FFF0FF0) == 0x016F0F10)
                  {
                    //Handle count leading zeros
                    ArmV5tlCLZ(core);
                  }
                  //Check on signed multiplies (SMULxy)
                  else if((core->arm_instruction.mul.type == 1) && (core->arm_instruction.mul.op1 == 3))
                  {
                    //Go and handle the multiply
                    ArmV5tlSMULxy(core);
                  }
                  else
                  {
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

  //Check if trace buffer writing enabled
  if(core->tracebufferenabled)
  {
    //Copy the registers into the trace buffer
    memcpy(&core->tracebuffer[core->traceindex].registers, &core->regs, sizeof(ARMV5TL_REGS));

    //Check if writing of trace data is enabled
    if((core->tracetriggered) && (core->TraceFilePointer))
    {
      //Write trace data to the trace file
      fwrite(&core->tracebuffer[core->traceindex], 1, sizeof(ARMV5TL_TRACE_ENTRY), core->TraceFilePointer);
      
      //Add on to the trace count for limiting files to 25K lines
      core->tracecount++;

      //Check if limit reached
      if(core->tracecount >= 25000)
      {
        //Reset the count
        core->tracecount = 0;
        
        //Close the current file
        fclose(core->TraceFilePointer);

        //Select next file index
        core->tracefileindex++;

        //Print the new file name
        snprintf(tracefilename, 64, "%s_%06d.bin", TRACE_FILE_NAME, core->tracefileindex);

        //Try to open it
        core->TraceFilePointer = fopen(tracefilename, "wb");
      }
    }

    //Point to next trace buffer entry and keep it in range of the trace buffer size
    core->traceindex = (core->traceindex + 1) % (sizeof(core->tracebuffer) / sizeof(ARMV5TL_TRACE_ENTRY));
  }
  
  //One more cycle done
  core->cpu_cycles++;
  
  //Check if there is a peripheral handler
  if(core->peripheralfunction)
  {
    //Call it before incrementing to the next instruction
    core->peripheralfunction(core);
  }
  
  //Point to next instruction when needed. When the previous instruction had the program counter as target the increment value is set to zero.
  *core->program_counter += core->pcincrvalue;
}

//----------------------------------------------------------------------------------------------------------------------------------
//Here the specific memory map is programmed
ARMV5TL_ADDRESS_MAP address_map[] = 
{
  //     Start,        End, Memory function,     Read function,     Write function
  { 0x00000000, 0x00007FFF,    F1C100sSram1,              NULL,                NULL },   //SRAM1
  { 0x00010000, 0x00019FFF,    F1C100sSram2,              NULL,                NULL },   //SRAM2
  { 0x01C00000, 0x01C00FFF,            NULL,              NULL,                NULL },   //System Controller
  { 0x01C01000, 0x01C01FFF,    F1C100sDRAMC,  F1C100sDRAMCRead,   F1C100sDRAMCWrite },   //DRAMC
  { 0x01C02000, 0x01C02FFF,            NULL,              NULL,                NULL },   //DMA
  { 0x01C05000, 0x01C05FFF,     F1C100sSPI0,   F1C100sSPI0Read,    F1C100sSPI0Write },   //SPI0
  { 0x01C06000, 0x01C06FFF,            NULL,              NULL,                NULL },   //SPI1
  { 0x01C0A000, 0x01C0AFFF,            NULL,              NULL,                NULL },   //TVE
  { 0x01C0B000, 0x01C0BFFF,            NULL,              NULL,                NULL },   //TVD
  { 0x01C0C000, 0x01C0CFFF,     F1C100sTCON,   F1C100sTCONRead,    F1C100sTCONWrite },   //TCON
  { 0x01C0E000, 0x01C0EFFF,            NULL,              NULL,                NULL },   //VE
  { 0x01C0F000, 0x01C0FFFF,            NULL,              NULL,                NULL },   //SD/MMC0
  { 0x01C10000, 0x01C10FFF,            NULL,              NULL,                NULL },   //SD/MMC1
  { 0x01C13000, 0x01C13FFF,            NULL,              NULL,                NULL },   //USB-OTG
  { 0x01C20000, 0x01C203FF,      F1C100sCCU,    F1C100sCCURead,     F1C100sCCUWrite },   //CCU
  { 0x01C20400, 0x01C207FF,     F1C100sINTC,   F1C100sINTCRead,    F1C100sINTCWrite },   //INTC
  { 0x01C20800, 0x01C20BFF,      F1C100sPIO,    F1C100sPIORead,     F1C100sPIOWrite },   //PIO
  { 0x01C20C00, 0x01C20FFF,    F1C100sTimer,  F1C100sTimerRead,   F1C100sTimerWrite },   //TIMER
  { 0x01C21000, 0x01C213FF,            NULL,              NULL,                NULL },   //PWM
  { 0x01C21400, 0x01C217FF,            NULL,              NULL,                NULL },   //OWA
  { 0x01C21800, 0x01C21BFF,            NULL,              NULL,                NULL },   //RSB
  { 0x01C22000, 0x01C223FF,            NULL,              NULL,                NULL },   //DAUDIO
  { 0x01C22C00, 0x01C22FFF,            NULL,              NULL,                NULL },   //CIR
  { 0x01C23400, 0x01C237FF,            NULL,              NULL,                NULL },   //KEYADC
  { 0x01C23C00, 0x01C23FFF,            NULL,              NULL,                NULL },   //Audio Codec
  { 0x01C24800, 0x01C24BFF,            NULL,              NULL,                NULL },   //TP
  { 0x01C25000, 0x01C253FF,    F1C100sUART0,  F1C100sUART0Read,   F1C100sUART0Write },   //UART0
  { 0x01C25400, 0x01C257FF,            NULL,              NULL,                NULL },   //UART1
  { 0x01C25800, 0x01C25BFF,            NULL,              NULL,                NULL },   //UART2
  { 0x01C27000, 0x01C273FF,            NULL,              NULL,                NULL },   //TWI0
  { 0x01C27400, 0x01C277FF,            NULL,              NULL,                NULL },   //TWI1
  { 0x01C27800, 0x01C27BFF,            NULL,              NULL,                NULL },   //TWI2
  { 0x01CB0000, 0x01CB0FFF,            NULL,              NULL,                NULL },   //CSI
  { 0x01E00000, 0x01E1FFFF,            NULL,              NULL,                NULL },   //DEFE
  { 0x01E60000, 0x01E6FFFF,     F1C100sDEBE,   F1C100sDEBERead,    F1C100sDEBEWrite },   //DEBE
  { 0x01E70000, 0x01E7FFFF,            NULL,              NULL,                NULL },   //DE Interlace
  { 0x80000000, 0x81FFFFFF,      F1C100sDDR,              NULL,                NULL },   //DRAM 32MB
};

//----------------------------------------------------------------------------------------------------------------------------------

void *ArmV5tlGetMemoryPointer(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode)
{
  int i;
  
  //Need to check on word or short alignment here when in that mode
  //Raise an exception and return NULL pointer
  
  //MMU needs to be implemented here
  if(address == 0x8038479C)
  {
    i = 20;
  }
  
  
  //Check all the entries in the address map
  for(i=0;i<sizeof(address_map)/sizeof(ARMV5TL_ADDRESS_MAP);i++)
  {
    //Check if the given address is in range of this map item
    if((address >= address_map[i].start) && (address <= address_map[i].end))
    {
      //Set the peripheral function pointers for this map entry
      core->periph_read_func = address_map[i].read;
      core->periph_write_func = address_map[i].write;
      
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

void ArmV5tlSetMemoryTraceData(PARMV5TL_CORE core, u_int32_t address, u_int32_t mode, u_int32_t count, u_int32_t direction)
{
  int i;
  void *memory;
  
  //Add memory data to the trace buffer
  core->tracebuffer[core->traceindex].memory_address = address;
  core->tracebuffer[core->traceindex].data_width = mode;
  core->tracebuffer[core->traceindex].data_count = count;
  core->tracebuffer[core->traceindex].memory_direction = direction;

  //Copy the data from memory to the trace buffer
  for(i=0;i<count;i++)
  {
    //Get a pointer to the given address based on the mode
    memory = ArmV5tlGetMemoryPointer(core, address, mode);

    //Check if valid memory pointer received
    if(memory)
    {
      //Do it based on the given mode
      switch(mode & ARM_MEMORY_MASK)  
      {
        case ARM_MEMORY_WORD:
          core->tracebuffer[core->traceindex].data[i] = *(u_int32_t *)memory;
          break;

        case ARM_MEMORY_SHORT:
          core->tracebuffer[core->traceindex].data[i] = *(u_int16_t *)memory;
          break;

        case ARM_MEMORY_BYTE:
          core->tracebuffer[core->traceindex].data[i] = *(u_int8_t *)memory;
          break;
      }
    }
    
    //Check if memory needs to be incremented or decremented. This is only used for word based actions due to how arm works
    if(direction)
    {
      address += 4;
    }
    else
    {
      address -= 4;
    }
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
      core->status->word = *core->registers[core->current_bank][ARM_REG_SPSR_IDX];
      
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
      core->status->flags.N = (vd >> 31) & 1;

      //Update the zero bit (only the lower 32 bits count)
      core->status->flags.Z = ((vd & 0xFFFFFFFF) == 0);

      //Check if carry and overflow need to be updated with arithmetic result
      if(docandv != ARM_FLAGS_UPDATE_CV_NO)
      {
        //Handle the carry and overflow according to type of arithmetic
        if(docandv == ARM_FLAGS_UPDATE_CV)
        {
          //Update the overflow bit for additions. When inputs have equal signs the sign of the output should remain the same as the inputs, otherwise there is an overflow
          core->status->flags.V = (((vn & 0x80000000) == (vm & 0x80000000)) && (vn & 0x80000000) != (vd & 0x80000000));
          
          //Carry from addition.
          core->status->flags.C = vd >> 32;
        }
        else
        {
          //Update the overflow bit for subtractions. When inputs not have equal signs the sign of the output should be the same as that of the first operand, otherwise there is an overflow
          core->status->flags.V = (((vn & 0x80000000) != (vm & 0x80000000)) && (vn & 0x80000000) != (vd & 0x80000000));
          
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
    
    //Process the first word without memory trace
    ArmV5tlLS(core, addr, mode | ARM_NO_MEM_TRACE);
    
    //Add 4 to the address for the next word
    addr += 4;
    
    //Select the next register
    core->arm_instruction.lsx.rd++;
    
    //Set trace mode to double word
    mode |= ARM_MEM_TRACE_DOUBLE;
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
    
    //Process the first word without memory trace
    ArmV5tlLS(core, addr, mode | ARM_NO_MEM_TRACE);
    
    //Add 4 to the address for the next word
    addr += 4;
    
    //Select the next register
    core->arm_instruction.lsx.rd++;
    
    //Set trace mode to double word
    mode |= ARM_MEM_TRACE_DOUBLE;
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
    //Check if load and peripheral read function set for this address
    if((core->arm_instruction.lsr.l) && (core->periph_read_func))
    {
      //Call it if so
      core->periph_read_func(core, address, memtype);
    }
    
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
            
    //Check if store and peripheral write function set for this address
    if((core->arm_instruction.lsr.l == 0) && (core->periph_write_func))
    {
      //Call it if so
      core->periph_write_func(core, address, memtype);
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
  
  //Check if tracing into buffer is enabled.
  if((core->tracebufferenabled) && ((mode & ARM_NO_MEM_TRACE) == 0))
  {
    //Check on load or store
    if(core->arm_instruction.lsr.l == 0)
    {
      memtype |= ARM_MEM_TRACE_WRITE;
    }
    
    //Check if double word trace
    if(mode & ARM_MEM_TRACE_DOUBLE)
    {
      //Set the data in the trace buffer
      ArmV5tlSetMemoryTraceData(core, address - 4, memtype, 2, 1);
    }
    else
    {
      //Set the data in the trace buffer
      ArmV5tlSetMemoryTraceData(core, address, memtype, 1, 1);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Load and store multiple instruction handling
void ArmV5tlLSM(PARMV5TL_CORE core)
{
  u_int32_t address = *core->registers[core->current_bank][core->arm_instruction.type4.rn];
  u_int32_t traceaddress;
  u_int32_t *memory;
  u_int32_t reglist = core->arm_instruction.instr & 0x0000FFFF;
  u_int32_t mode = ARM_MEMORY_WORD;
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
        core->status->word = *core->registers[core->current_bank][ARM_REG_SPSR_IDX];
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
  
  //Set the trace address
  traceaddress = address;
  
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
        memory = ArmV5tlGetMemoryPointer(core, address, mode);
        
        //Check if valid memory found
        if(memory)
        {
          //Check if load or store
          if(core->arm_instruction.type4.l)
          {
            //Check if peripheral read function set for this address
            if(core->periph_read_func)
            {
              //Call it if so
              core->periph_read_func(core, address, mode);
            }

            //Load the register with the data from memory
            *core->registers[bank][i] = *memory;
          }
          else
          {
            //Store the register to memory
            *memory = *core->registers[bank][i];
            
            //Check if peripheral write function set for this address
            if(core->periph_write_func)
            {
              //Call it if so
              core->periph_write_func(core, address, mode);
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
        memory = ArmV5tlGetMemoryPointer(core, address, mode);
        
        //Check if valid memory found
        if(memory)
        {
          //Check if load or store
          if(core->arm_instruction.type4.l)
          {
            //Check if peripheral read function set for this address
            if(core->periph_read_func)
            {
              //Call it if so
              core->periph_read_func(core, address, mode);
            }

            //Load the register with the data from memory
            *core->registers[bank][i] = *memory;
          }
          else
          {
            //Store the register to memory
            *memory = *core->registers[bank][i];
            
            //Check if peripheral write function set for this address
            if(core->periph_write_func)
            {
              //Call it if so
              core->periph_write_func(core, address, mode);
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
  
  //Check if tracing into buffer is enabled.
  if(core->tracebufferenabled)
  {
    //Check on load or store
    if(core->arm_instruction.type4.l == 0)
    {
      mode |= ARM_MEM_TRACE_WRITE;
    }
    
    //Set the data in the trace buffer
    ArmV5tlSetMemoryTraceData(core, traceaddress, mode, numregs, core->arm_instruction.type4.u);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Multiply instruction handling
//MUL, MULS, MLA, MLAS, UMULL, UMULLS, UMLAL, UMLALS, SMULL, SMULLS, SMLAL, SMLALS  
void ArmV5tlMUL(PARMV5TL_CORE core)
{
  u_int32_t rm = *core->registers[core->current_bank][core->arm_instruction.mul.rm];
  u_int32_t rs = *core->registers[core->current_bank][core->arm_instruction.mul.rs];
  int64_t vd;
  int64_t va;
  
  //Check if signed or unsigned multiply needed (SMULL op1:6, SMLAL op1:7)
  if((core->arm_instruction.mul.op1 == 6) || (core->arm_instruction.mul.op1 == 7))
  {
    //Do multiply with signed inputs
    vd = (int64_t)rs * (int64_t)rm;
  }
  else
  {
    //Do multiply with unsigned inputs
    vd = (u_int64_t)rs * (u_int64_t)rm;
  }
  
  //Check if 64 bit accumulate needed (UMLAL op1:5, SMLAL op1:7)
  if((core->arm_instruction.mul.op1 == 5) || (core->arm_instruction.mul.op1 == 7))
  {
    //Get the value to add from the two destination registers. rd holds high part, rn holds low part.
    va  = (u_int64_t)*core->registers[core->current_bank][core->arm_instruction.mul.rd] << 32;
    va |= *core->registers[core->current_bank][core->arm_instruction.mul.rn];
    
    //Do the summation
    vd += va;
  }
  //Check if 32 bit accumulation needed (MLA op1:1)
  else if(core->arm_instruction.mul.op1 == 1)
  {
    //Add the value held in rn to the result
    vd += *core->registers[core->current_bank][core->arm_instruction.mul.rn];
  }
  
  //Check if 32 bit result instruction (MUL op1:0, MLA op1:1)
  if((core->arm_instruction.mul.op1 == 0) || (core->arm_instruction.mul.op1 == 1))
  {
    //Store the 32 bit result back to rd
    *core->registers[core->current_bank][core->arm_instruction.mul.rd] = (u_int32_t)vd;
    
    //Check if status flags need to be updated
    if(core->arm_instruction.mul.s)
    {
        //Update the negative bit
        core->status->flags.N = (vd >> 31) & 1;

        //Update the zero bit (only the lower 32 bits count)
        core->status->flags.Z = ((vd & 0xFFFFFFFF) == 0);
    }
  }
  //Leaves 64 bit result instructions
  else
  {
    //Store the 64 bit result back to register pair. rd holds high part, rn holds low part.
    *core->registers[core->current_bank][core->arm_instruction.mul.rd] = (u_int32_t)(vd >> 32);
    *core->registers[core->current_bank][core->arm_instruction.mul.rn] = (u_int32_t)vd;
    
    //Check if status flags need to be updated
    if(core->arm_instruction.mul.s)
    {
        //Update the negative bit
        core->status->flags.N = (vd >> 63) & 1;

        //Update the zero bit (only the lower 32 bits count)
        core->status->flags.Z = (vd == 0);
    }
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
//Multiply instruction handling
//SMULxy
void ArmV5tlSMULxy(PARMV5TL_CORE core)
{
  int32_t rm = *core->registers[core->current_bank][core->arm_instruction.smulxy.rm];
  int32_t rs = *core->registers[core->current_bank][core->arm_instruction.smulxy.rs];
  
  //Check which part of rm needs to be used
  if(core->arm_instruction.smulxy.x)
  {
    //Upper half of the word
    rm >>= 16;
  }
  
  //Check if sign extend is needed for this input
  if(rm & 0x00008000)
  {
    //If needed set the upper bits
    rm |= 0xFFFF0000;
  }

  //Check which part of rs needs to be used
  if(core->arm_instruction.smulxy.y)
  {
    //Upper half of the word
    rs >>= 16;
  }
  
  //Check if sign extend is needed for this input
  if(rs & 0x00008000)
  {
    //If needed set the upper bits
    rs |= 0xFFFF0000;
  }
  
  //Do the actual multiplication
  *core->registers[core->current_bank][core->arm_instruction.smulxy.rd] = rm * rs;
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
//Handle count leading zeros
void ArmV5tlCLZ(PARMV5TL_CORE core)
{
  //Get input data
  u_int32_t vm = *core->registers[core->current_bank][core->arm_instruction.clz.rm];
  u_int32_t cnt = 0;
  
  //Check on input being zero
  if(vm == 0)
  {
    //This means 32 zeros
    cnt = 32;
  }
  else
  {
    //count the actual zeros
    while((vm & 0x80000000) == 0)
    {
      //Add one zero to the count
      cnt++;
      
      //Shift the bits to the right
      vm <<= 1;
    }
  }
  
  //Write the result to the destination register
  *core->registers[core->current_bank][core->arm_instruction.clz.rd] = cnt;
}
