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
  int  lastbyte = 0;
  char curchar;
  int  writelocation = 0;
  
  int checkdata[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 } ;
  int index;
  int bit;
  
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
  unsigned char byte;
  unsigned char bitflag;

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

  //Add 72 bytes to make room for the check data
  lastbyte = writelocation + ipflen;
  length = lastbyte + 72;
  buffer = malloc(length);
  
  if(buffer)
  {
    //Clear the buffer so gaps in the data are zero
    memset(buffer, 0, length);
  
    //Get the output file data from the start
    fseek(opf, 0, SEEK_SET);
    
    //Don't go beyond the new write location
    if(opflen > writelocation)
    {
      opflen = writelocation;
    }
    
    //Load the output file data to the buffer
    fread(buffer, 1, opflen, opf);

    //Get the input file data from the start
    fseek(ipf, 0, SEEK_SET);
    
    //Load the input file data to the buffer starting from write location
    fread(&buffer[writelocation], 1, ipflen, ipf);

    //Calculate the check data
    //Go through all the data bytes
    for(index=0;index<lastbyte;index++)
    {
      //Get the current byte
      byte = buffer[index];
      
      //Calculate the sum of all the data bytes
      checkdata[0] += byte;
      
      //Calculate a index dependent occurrence of the individual bits
      for(bit=1,bitflag=0x80;bit<9;bit++)
      {
        //Check if the current bit is set
        if(byte & bitflag)
        {
          //If so add to the counter for this bit
          checkdata[bit] += index;
        }
        
        //Select the next bit to check
        bitflag >>=1;
      }
    }
    
    //Add the check data to the buffer
    index = length - 36;
    
    //Copy the data in byte by byte
    for(bit=0;bit<9;bit++)
    {
      buffer[index++] = checkdata[bit] >> 24;
      buffer[index++] = checkdata[bit] >> 16;
      buffer[index++] = checkdata[bit] >> 8;
      buffer[index++] = checkdata[bit];
    }
 
    fclose(opf);
    
    //Need to reopen the output file for writing
    opf = fopen(outfile, "wb");
    
    //Make sure it is opened again
    if(opf)
    {
      //Write the data including the check bytes to the output file
      fwrite(buffer, 1, length, opf);
    }
    
    free(buffer);
  }
    
  fclose(ipf);
  fclose(opf);
  
  return 0;
}
