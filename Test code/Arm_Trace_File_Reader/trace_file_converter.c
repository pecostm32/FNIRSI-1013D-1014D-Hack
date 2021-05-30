
#include <stdio.h>      // standard input / output functions
#include <stdlib.h>
#include <string.h>

#include "../../FNIRSI-1013D/Arm_Trace_File_Reader/armtracedata.h"
#include "../../FNIRSI-1013D/Arm_Trace_File_Reader/armdisassemble.h"
#include "../../FNIRSI-1013D/Arm_Trace_File_Reader/thumbdisassemble.h"

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

#define TRACE_FILE_NAME         "screen_buf_clear"

int main(int argc, char** argv)
{
  int n;
  char tracefilename[128];

  for(n=0;n<3;n++)
  {
//    snprintf(tracefilename, 128, "../../FNIRSI-1013D/Scope_emulator/setup_display_lib_trace/%s_%06d.bin", TRACE_FILE_NAME, n);
    snprintf(tracefilename, 128, "../../FNIRSI-1013D/Scope_emulator/%s_%06d.bin", TRACE_FILE_NAME, n);
    FILE *fp = fopen(tracefilename, "rb");

    if(fp)  
    {
      int size = fread(tracelist, 1, sizeof(tracelist) , fp);

      listitems = size / sizeof(ARMV5TL_TRACE_ENTRY);

      fclose(fp);

      snprintf(tracefilename, 128, "%s_%06d.txt", TRACE_FILE_NAME, n);
      fp = fopen(tracefilename, "w");

      if(fp)
      {
        int i,r;
        int spaces;

        u_int32_t *rptr;

        char exetext[4][4] = { "NO ", "YES", "T  ", "   " };

        char disassemtext[94];

        for(i=0;i<listitems;i++)
        {
          spaces = 110;

          memset(disassemtext, 0x20, sizeof(disassemtext));
          disassemtext[0] = 0;

          if(tracelist[i].execution_status != ARM_INSTRUCTION_THUMB)
            ArmDisassemble(disassemtext, sizeof(disassemtext), tracelist[i].instruction_address, (ARM_INSTRUCTION)tracelist[i].instruction_word);
          else
            ThumbDisassemble(disassemtext, sizeof(disassemtext), tracelist[i].instruction_address, (ARM_THUMB_INSTRUCTION)(u_int16_t)tracelist[i].instruction_word);

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
            //Add memory read or write info (tracelist[i].data_width & ARM_MEM_TRACE_WRITE) true then write else read
            fprintf(fp, "  memory:0x%08X  type:%s  count:%2d  dir:%s  ", tracelist[i].memory_address, memsizetext[(tracelist[i].data_width & ARM_MEMORY_MASK)], tracelist[i].data_count, dirtext[tracelist[i].memory_direction]);

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
  }
}

