
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>

#include "../../FNIRSI-1013D/Arm_Trace_File_Reader/armtracedata.h"
#include "../../FNIRSI-1013D/Arm_Trace_File_Reader/armdisassemble.h"

const char *trregnames[37] = 
{
  "r0:",
  "r1:",
  "r2:",
  "r3:",
  "r4:",
  "r5:",
  "r6:",
  "r7:",
  "r8_usr:",  "r8_fiq:",
  "r9_usr:",  "r9_fiq:",
  "r10_usr:", "r10_fiq:",
  "r11_usr:", "r11_fiq:",
  "r12_usr:", "r12_fiq:",
  "r13_usr:", "r13_fiq:", "r13_irq:", "r13_svc:", "r13_abt:", "r13_und:",
  "r14_usr:", "r14_fiq:", "r14_irq:", "r14_svc:", "r14_abt:", "r14_und:",
  "r15:",
  "cpsr:",
  "spsr_fiq:", "spsr_irq:", "spsr_svc:", "spsr_abt:", "spsr_und:",
};

const char *memsizetext[4] = { "word ", "short", "byte ", "dword" };
const char *dirtext[2] = { "down", "up  " };

int listitems = 0;

//The emulator writes max 25000 lines per file
ARMV5TL_TRACE_ENTRY tracelist[25100];

int main(int argc, char** argv)
{
  //For now just a single file opened here
  FILE *fp = fopen("../../FNIRSI-1013D/Scope_emulator/test_trace_000088.bin", "rb");
  
  if(fp)  
  {
    int size = fread(tracelist, 1, sizeof(tracelist) , fp);
    
    listitems = size / sizeof(ARMV5TL_TRACE_ENTRY);
    
    fclose(fp);
  }

  fp = fopen("test_trace_000088.txt", "w");
  
  if(fp)
  {
    int i,r;
    int spaces;
    
    u_int32_t *rptr;
    
    char exetext[4][4] = { "NO ", "YES", "   ", "   " };

    char displaytext[128];
    char disassemtext[94];

    for(i=0;i<listitems;i++)
    {
      spaces = 110;

      memset(disassemtext, 0x20, sizeof(disassemtext));
      disassemtext[0] = 0;

      ArmDisassemble(disassemtext, sizeof(disassemtext), tracelist[i].instruction_address, (ARM_INSTRUCTION)tracelist[i].instruction_word);

      spaces -= fprintf(fp, "pa:0x%08X  0x%08X  %s       %s", tracelist[i].instruction_address, tracelist[i].instruction_word, exetext[tracelist[i].execution_status & 3], disassemtext);
      
      while(spaces)
      {
        fprintf(fp, " ");
        spaces--;
      }
      
      rptr = &tracelist[i].registers.r0;
      
      for(r=0;r<37;r++)
      {
        fprintf(fp, "%s0x%08X  ", trregnames[r], *rptr++);
      }
      
      if(tracelist[i].data_count)
      {
        fprintf(fp, "  memory:0x%08X  type:%s  count:%2d  dir:%s  ", tracelist[i].memory_address, memsizetext[tracelist[i].data_width], tracelist[i].data_count, dirtext[tracelist[i].memory_direction]);
        
        for(r=0;r<tracelist[i].data_count;r++)
        {
          fprintf(fp, "0x%08X  ", tracelist[i].data[r]);
        }
      }
      
      fprintf(fp, "\n");
    }
    
    fclose(fp);
  }
}

