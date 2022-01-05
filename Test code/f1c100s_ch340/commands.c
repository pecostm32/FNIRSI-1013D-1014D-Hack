//----------------------------------------------------------------------------------------------------------------------------------

#include "commands.h"
#include "ch340_class.h"
#include "fpga_control.h"

//----------------------------------------------------------------------------------------------------------------------------------

char          linebuffer[LINE_LENGTH];
char         *lineptr = linebuffer;
tagTokenData  tokens[MAX_TOKENS];
uint8         tokenindex = 0;           //Index into tokens array
uint8         noftokens = 0;            //Number of tokens
uint8         tokenflag = 0;            //Flag to signal busy with a token
uint8         haderror = 0;             //Flag to signal error has been found
uint8         length;                   //Length of current token
uint8         numberbase = 10;          //Base of the current number. Depends on the input. When 0X then base is 16.

//----------------------------------------------------------------------------------------------------------------------------------

extern volatile uint16 curchar;

//----------------------------------------------------------------------------------------------------------------------------------

void writefpgacommand(void);
void writefpgabyte(void);
void writefpgashort(void);
void writefpgaint(void);

void readfpgabyte(void);
void readfpgashort(void);
void readfpgaint(void);

//----------------------------------------------------------------------------------------------------------------------------------

uint32 fpgacommand;
uint32 fpgawritebyte;
uint32 fpgawriteshort;
uint32 fpgawriteint;
uint32 fpgareadbyte;
uint32 fpgareadshort;
uint32 fpgareadint;

//----------------------------------------------------------------------------------------------------------------------------------

//Simple interpreter based on "setting" = "value"
//"value" is checked against min and max values

const tagVariableData variablelist[] = 
{
  { "WC",                      2,  0,         255, &fpgacommand,             NULL, writefpgacommand },
  { "WB",                      2,  0,         255, &fpgawritebyte,           NULL,    writefpgabyte },
  { "WS",                      2,  0,       65535, &fpgawriteshort,          NULL,   writefpgashort },
  { "WI",                      2,  0,  4294967295, &fpgawriteint,            NULL,     writefpgaint },
  { "RB",                      2,  0,           0, &fpgareadbyte,    readfpgabyte,             NULL },
  { "RS",                      2,  0,           0, &fpgareadshort,  readfpgashort,             NULL },
  { "RI",                      2,  0,           0, &fpgareadint,      readfpgaint,             NULL },
};

//----------------------------------------------------------------------------------------------------------------------------------
// Process functions
//----------------------------------------------------------------------------------------------------------------------------------

void writefpgacommand(void)
{
  fpga_write_cmd(fpgacommand);
}

void writefpgabyte(void)
{
  fpga_write_byte(fpgawritebyte);
}

void writefpgashort(void)
{
  fpga_write_short(fpgawriteshort);
}

void writefpgaint(void)
{
  fpga_write_int(fpgawriteint);
}

void readfpgabyte(void)
{
  fpgareadbyte = fpga_read_byte();
}

void readfpgashort(void)
{
  fpgareadshort = fpga_read_short();
}

void readfpgaint(void)
{
  fpgareadint = fpga_read_int();
}

//----------------------------------------------------------------------------------------------------------------------------------
//Tokenizer and parser functions
//----------------------------------------------------------------------------------------------------------------------------------

void handleinput()
{
  //Check if line buffer still has room for character plus at max two terminators
  if(lineptr >= (linebuffer + (LINE_LENGTH - 3)))
  {
    //Send error message
    senderror(ERROR_LINE_BUFFER_OVERFLOW);
  }
  //Check if space left for more tokens
  else if(tokenindex >= MAX_TOKENS)
  {
    //Send error message
    senderror(ERROR_TOKEN_BUFFER_OVERFLOW);
  }
  //Still room for characters and tokens so handle next character
  else
  {
    //Check if a new line or carriage return is received
    if((curchar == '\n') || (curchar == '\r'))
    {
      //Check if error while processing the input
      if(haderror)
      {
        //Reset and wait for new input
        haderror = 0;

        //Reset for new line of input
        tokenindex = 0;
        noftokens = 0;
        tokenflag = 0;
        length = 0;
        lineptr = linebuffer;
      }
      //If no error go and handle the tokens entered if any
      else if(tokenindex || tokenflag)
      {
        //Terminate the last token if any
        terminatetoken();

        //Set the number of tokens received
        noftokens = tokenindex;

        //Go and handle them
        parsetokens();
      }
    }
    //If not new line or carriage return check if regular or white space character and no error has been detected
    else if((((curchar >= ' ') && (curchar <=  LAST_CHARACTER)) || (curchar == '\t')) && (haderror == 0))
    {
      //Check if space or tab received
      if((curchar == ' ') || (curchar == '\t'))
      {
        //Spaces or tabs are filtered out
        //Check if previous data was for a token and if so then terminate that token and setup for next one
        terminatetoken();
      }
      //Check if assign token received
      else if(curchar == '=')
      {
        //Check if already other token(s) received
        if(tokenindex || tokenflag)
        {
          //Check if previous token needs to be terminated
          terminatetoken();

          //Setup token pointer for pointing to the operator and select next token pointer
          tokens[tokenindex].str = lineptr;
          tokens[tokenindex].length = 1;
          tokens[tokenindex].type = TYPE_OPERATOR;
          tokens[tokenindex].value = 0;
          tokens[tokenindex].variable = 0;
          tokens[tokenindex].operation = assign;

          //Point to the next token entry
          tokenindex++;

          //Add the operator to the line buffer and terminate it
          *lineptr++ = curchar;
          *lineptr++ = '\0';
        }
        else
        {
          //No previous token so send an error
          senderror(ERROR_OPERATOR_NOT_ALLOWED_HERE);
        }
      }
      else
      {
        //Check if first character of a new token
        if(tokenflag == 0)
        {
          //Signal busy with receiving a token
          tokenflag = 1;

          //Setup the token string pointer
          tokens[tokenindex].str = lineptr;

          //Reset the handler
          tokens[tokenindex].operation = 0;

          //Check if first character is a digit. If so mark it as a number
          if((curchar >= '0') && (curchar <= '9'))
          {
            //Check if first token
            if(tokenindex == 0)
            {
              //Number as first token so send an error
              senderror(ERROR_NUMBER_NOT_ALLOWED_HERE);
            }
            else
            {
              //Set type for a number and reset the value. No variable pointer
              tokens[tokenindex].type = TYPE_NUMBER;
              tokens[tokenindex].value = 0;
              tokens[tokenindex].variable = 0;
            }
          }
          else
          {
            //When not a number type is signaled as string
            tokens[tokenindex].type = TYPE_STRING;
          }
        }

        //Check if lower case input
        if((curchar >= 'a') && (curchar <= 'z'))
        {
          //If so make uppercase
          curchar &= LOWER_CASE_CONVERT;
        }

        //Parse current character if token type is number
        if(tokens[tokenindex].type == TYPE_NUMBER)
          parsenumber();

        //Put the received character in the line buffer and add one to the length
        *lineptr++ = curchar;
        length++;
      }
    }    
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Function to parse the current character into a number
void parsenumber()
{
  //Check which number base is being used
  if(numberbase == 10)
  {
    //Check if hexadecimal number being input
    if((length == 1) && (tokens[tokenindex].value == 0) && (curchar == 'X'))
    {
      //Set the number base accordingly
      numberbase = 16;
    }
    //If not hexadecimal check if valid digit for decimal base
    else if((curchar >= '0') && (curchar <= '9'))
    {
      //Shift the result based on the number base and add the value of the current character
      tokens[tokenindex].value *= 10;
      tokens[tokenindex].value += curchar - '0';
    }
    else
    {
      //Send invalid character for a decimal number error
      senderror(ERROR_INVALID_DECIMAL_CHARACTER);
    }
  }
  else if(numberbase == 16)
  {
    //Check if digit in valid range
    if((curchar >= '0') && (curchar <= '9'))
    {
      //Shift the result based on the number base
      tokens[tokenindex].value *= 16;
      
      //Digits give 0 to 9 for the addition
      tokens[tokenindex].value += curchar - '0';
    }
    else if((curchar >= 'A') && (curchar <= 'F'))
    {
      //Shift the result based on the number base
      tokens[tokenindex].value *= 16;
      
      //Alpha give 10 to 15 for the addition. (55 = 'A' - 10)
      tokens[tokenindex].value += curchar - 55;
    }
    else
    {
      //Send invalid character for hexadecimal number error
      senderror(ERROR_INVALID_HEXADECIMAL_CHARACTER);
    }
  }
  else
  {
    //Send invalid number base error.
    senderror(ERROR_INVALID_NUMBER_BASE);
  }
  
  //When no error occurred check on overflow
  if(haderror == 0)
  {
    if(tokens[tokenindex].value > MAX_NUMBER_VALUE)
      senderror(ERROR_NUMBER_OVERFLOW);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

//Function to parse the current string token
void parsestring()
{
  uint16 index = 0;
  uint8  found = 0;
  
  //Search the variable list to see if given string matches any of the defined variables
  while(index < (sizeof(variablelist) / sizeof(tagVariableData)))
  {
    //Check if length of given string matches the current variable list string length
    if(variablelist[index].length == length)
    {
      uint8 idx;
      
      //Length matches so check the characters
      for(idx = 0;idx<length;idx++)
      {
        if(tokens[tokenindex].str[idx] != variablelist[index].str[idx])
          break;
      }
      
      //Check if match has been found
      if(idx == length)
      {
        //If so set the data and type for this variable
        found = 1;
            
        //Fill in the token with the variable properties
        tokens[tokenindex].type = TYPE_VARIABLE;
        tokens[tokenindex].value = *variablelist[index].data;
        tokens[tokenindex].variable = &variablelist[index];
        tokens[tokenindex].operation = 0;
        break;
      }
    }
    
    //Point to next string in the list
    index++;
  }
  
  //Check if string has been found
  if(found == 0)
    senderror(ERROR_STRING_NOT_FOUND);
}

//----------------------------------------------------------------------------------------------------------------------------------

void terminatetoken()
{
  //Only when an actual token is given
  if(tokenflag)
  {
    //Terminate the received token
    *lineptr++ = '\0';

    //Set the length for received token and point to next token
    tokens[tokenindex].length = length;

    //Parse current token if token type is string
    if(tokens[tokenindex].type == TYPE_STRING)
      parsestring();

    //Prepare for next token
    tokenindex++;

    //Reset the length counter
    length = 0;

    //Reset the token flag
    tokenflag = 0;

    //Reset the number base
    numberbase = 10;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void parsetokens()
{
  //Start with the second token, since first token always is a variable
  tokenindex=1;

  //Go through the tokens and process them as long as there are no errors detected12
  while((tokenindex<noftokens) && (haderror == 0))
  {
    //Check if operator and handle it
    if(tokens[tokenindex].type == TYPE_OPERATOR)
    {
      //Perform the operation
      tokens[tokenindex].operation();
    }
    
    tokenindex++;
  }

  //Check if data of first token can be send to output
  if(haderror == 0)
  {
    //Check if reading a variable. Only one token on input
    if(tokenindex == 1)
    {
      if(tokens[0].variable->processbefore)
        tokens[0].variable->processbefore();
    }
    
    //Output the current value of this variable
    sendoutput(tokens[0].variable);
  }

  //Done handling tokens so reset  
  haderror = 0;
  tokenindex = 0;
  noftokens = 0;
  tokenflag = 0;
  length = 0;
  lineptr = linebuffer;
}

//----------------------------------------------------------------------------------------------------------------------------------

//Operation functions
void assign()
{
  uint8 prevtoken = tokenindex - 1;  //Point to previous token as target
  uint8 nexttoken = tokenindex + 1;  //Point to next token as source
  
  int32 value = 0;
    
  const tagVariableData *variable;
    
  //Check if there are more tokens
  if(nexttoken >= noftokens)
  {
    //Not enough tokens
    senderror(ERROR_NOT_ENOUGH_TOKENS);
    return;
  }
  
  //Check if next token is a number or a variable
  if((tokens[nexttoken].type != TYPE_NUMBER) && (tokens[nexttoken].type != TYPE_VARIABLE))
  {
    //No valid data for this operator
    senderror(ERROR_NO_VALID_DATA);
    return;
  }
  
  //Get a pointer to the variable entry
  variable = tokens[prevtoken].variable;
  
  //Get the value to put into the variable
  value = tokens[nexttoken].value;
  
  //Check if input value in range of allowed values
  if((value < variable->minvalue) || (value > variable->maxvalue))
  {
    //Value out of range for this variable
    senderror(ERROR_DATA_OUT_OF_RANGE);
    return;
  }
  
  //Previous and next token are valid so perform the assignment
  *variable->data = value;
  
  //Check if the variable needs additional processing
  if(variable->processafter)
    variable->processafter();
  
  //Skip to next part of the line
  tokenindex++;
}

//----------------------------------------------------------------
//Output section
//----------------------------------------------------------------

void SendString(char *str);
void SendInt(int32 value);

//----------------------------------------------------------------------------------------------------------------------------------

void senderror(int8 error)
{
  //Signal error
  haderror = 1;
  
  SendString("Error ");
  SendInt(error);
  SendString(" occurred\n");
}

//----------------------------------------------------------------------------------------------------------------------------------

void sendoutput(const tagVariableData *variable)
{
  SendString(variable->str);
  SendString("  current=");
  SendInt(*variable->data);
  SendString(", min=");
  SendInt(variable->minvalue);
  SendString(", max=");
  SendInt(variable->maxvalue);
  ch340Send('\n');
}

//----------------------------------------------------------------------------------------------------------------------------------

//Send a string to the USB port
void SendString(char *str)
{
  while(*str)
  {
    ch340Send(*str);
    str++;
  }
}

//----------------------------------------------------------------------------------------------------------------------------------

void SendInt(int32 value)
{
  char    b[12];
  uint32  u = value;
  uint8   i = 11;

  b[11] = 0;
  
  if(value == 0)
  {
    //Value is zero so just send a 0 character
    ch340Send('0');
  }
  else
  {
    //Check if negative value
    if(value < 0)
    {
      //Negate if so
      u = -value;
      
      //And send minus character
      ch340Send('-');
    }

    //Process the digits
    while(u)
    {
      //Set current digit to decreased index
      b[--i] = (u % 10) + '0';

      //Take of the current digit
      u /= 10;
    }
    
    SendString(&b[i]);
  }
}

//----------------------------------------------------------------------------------------------------------------------------------
