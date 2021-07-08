//----------------------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdarg.h>
#include <stdint.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <getopt.h>

//----------------------------------------------------------------------------------------------------------------------------------

#define LOWER_CASE_CONVERT  0x5F     //Used to convert lower case to upper case by anding

//----------------------------------------------------------------------------------------------------------------------------------


//----------------------------------------------------------------------------------------------------------------------------------


int main(int argc, char **argv)
{
  char *outfile  = NULL;
  char *infile   = NULL;
  char *location = NULL;
  
  int  numberbase = 10;
  int  length = 0;
  char curchar;
  int  writelocation = 0;
  
  while(1)
  {
    int c;
    int option_index;

    static struct option long_options[] =
    {
      { "out_file",     required_argument, 0, 'o' },
      { "in_file",      required_argument, 0, 'i' },
      { "location",     required_argument, 0, 'l' },
      { "help",         no_argument,       0, 'h' },      
      { 0,              0,                 0, 0   }
    };

    c = getopt_long(argc, argv, "o:i:l:h", long_options, &option_index);
    
    if(c == -1)
      break;
    
    switch(c)
    {
      default:
        printf("\n invalid option given\n\n");
        exit(0);
        break;
        
      case 'o':
        outfile = optarg;
        break;
        
      case 'i':
        infile = optarg;
        break;
        
      case 'l':
        location = optarg;
        break;
        
      case 'h':
        printf("\nUsage: %s <options>\n\n"
          "Options:\n"
          "  --out_file=filename    (-o) File to write the input file to\n"
          "  --in_file=filename     (-i) File to add to the output file at location given with --location\n"
          "  --location=location    (-l) Location in the output file where to write input file data\n\n"
          "When output file exists it will be loaded first and data will be written from given location\n"
          "If it does not exist it will be created and filled with zeros up to given location.",
          argv[0]);
        
        exit(0);
        break;
    }
  }

  if(outfile == NULL)
  {
    printf("\nError: No output file specified\n\n");
    exit(0);
  }

  if(infile == NULL)
  {
    printf("\nError: No input file specified\n\n");
    exit(0);
  }
  
  if(location == NULL)
  {
    printf("\nError: No location specified\n\n");
    exit(0);
  }
  
  while(*location)
  {
    curchar = *location++;
    
    //Check if lower case input
    if((curchar >= 'a') && (curchar <= 'z'))
    {
      //If so make uppercase
      curchar &= LOWER_CASE_CONVERT;
    }
    
    //Check which number base is being used
    if(numberbase == 10)
    {
      //Check if hexadecimal number being input
      if((length == 1) && (writelocation == 0) && (curchar == 'X'))
      {
        //Set the number base accordingly
        numberbase = 16;
      }
      //If not hexadecimal check if valid digit for decimal base
      else if((curchar >= '0') && (curchar <= '9'))
      {
        //Shift the result based on the number base and add the value of the current character
        writelocation *= 10;
        writelocation += curchar - '0';
      }
      else
      {
        //Error in location field
        printf("\nError: Invalid decimal location given\n\n");
        exit(0);
      }
    }
    else if(numberbase == 16)
    {
      //Check if digit in valid range
      if((curchar >= '0') && (curchar <= '9'))
      {
        //Shift the result based on the number base
        writelocation *= 16;

        //Digits give 0 to 9 for the addition
        writelocation += curchar - '0';
      }
      else if((curchar >= 'A') && (curchar <= 'F'))
      {
        //Shift the result based on the number base
        writelocation *= 16;

        //Alpha give 10 to 15 for the addition. (55 = 'A' - 10)
        writelocation += curchar - 55;
      }
      else
      {
        //Error in location field
        printf("\nError: Invalid hexadecimal location given\n\n");
        exit(0);
      }
    }
    
    length++;
  }
  

  FILE *ipf = fopen(infile, "rb");
  FILE *opf = fopen(outfile, "rb");
  int opflen;
  int ipflen;
  unsigned char *buffer;


  if(ipf)
  {
    fseek(ipf, 0, SEEK_END);
    ipflen = ftell(ipf);
  }
  else
  {
    exit(0);
  }
  
  if(opf)
  {
    fseek(opf, 0, SEEK_END);
    opflen = ftell(opf);
  }
  else
  {
    fclose(ipf);
    exit(0);
  }

  length = writelocation + ipflen;
  buffer = malloc(writelocation + ipflen);
  
  if(buffer)
  {
    memset(buffer, 0, length);
  
    fseek(opf, 0, SEEK_SET);
    
    if(opflen > writelocation)
      opflen = writelocation;
    
    fread(buffer, 1, opflen, opf);

    fseek(ipf, 0, SEEK_SET);
    
    fread(&buffer[writelocation], 1, ipflen, ipf);
  
    fclose(opf);
    
    opf = fopen(outfile, "wb");
    
    fwrite(buffer, 1, length, opf);
    
    free(buffer);
  }
    
  fclose(ipf);
  fclose(opf);
  
  return 0;
}
