//----------------------------------------------------------------------------------------------------------------------------------

#ifndef COMMANDS_H
#define COMMANDS_H

//----------------------------------------------------------------------------------------------------------------------------------

#include "types.h"

//----------------------------------------------------------------------------------------------------------------------------------

//For the FNIRSI 1013D scope several commands can be send over the USB serial port
//Command is terminated with carriage return or linefeed

//----------------------------------------------------------------------------------------------------------------------------------

#define LINE_LENGTH                          64     //Length of the line buffer
#define MAX_TOKENS                            4     //Max allowed number of tokens on a single line

#define LAST_CHARACTER                     0x7E     //Last ASCII character. 0x7F is delete so a control character
#define LOWER_CASE_CONVERT                 0x5F     //Used to convert lower case to upper case by anding

#define TYPE_OPERATOR                         1
#define TYPE_NUMBER                           2
#define TYPE_STRING                           3
#define TYPE_VARIABLE                         4

#define MAX_NUMBER_VALUE             4294967295

#define ERROR_LINE_BUFFER_OVERFLOW            1
#define ERROR_TOKEN_BUFFER_OVERFLOW           2
#define ERROR_OPERATOR_NOT_ALLOWED_HERE       3
#define ERROR_NUMBER_NOT_ALLOWED_HERE         4
#define ERROR_INVALID_DECIMAL_CHARACTER       5
#define ERROR_INVALID_HEXADECIMAL_CHARACTER   6
#define ERROR_INVALID_NUMBER_BASE             7
#define ERROR_NUMBER_OVERFLOW                 8
#define ERROR_STRING_NOT_FOUND                9
#define ERROR_NOT_ENOUGH_TOKENS              10
#define ERROR_NO_VALID_DATA                  11
#define ERROR_DATA_OUT_OF_RANGE              12

//----------------------------------------------------------------------------------------------------------------------------------

#define NULL      ((void *)0)

//----------------------------------------------------------------------------------------------------------------------------------

typedef void (*PROCESSVAR)(void);
typedef void (*OPERATION)(void);

//----------------------------------------------------------------------------------------------------------------------------------

typedef struct
{
           char    *str;
           uint8    length;
           uint32   minvalue;
           uint32   maxvalue;
  volatile uint32  *data;
  PROCESSVAR        processbefore;
  PROCESSVAR        processafter;
} tagVariableData;

typedef struct
{
  char                  *str;
  uint8                  length;
  uint8                  type;
  uint32                 value;
  const tagVariableData *variable;
  OPERATION              operation;
} tagTokenData;

//----------------------------------------------------------------------------------------------------------------------------------

void handleinput();

void senderror(int8 error);
void sendoutput(const tagVariableData *variable);

void terminatetoken();
void parsetokens();
void parsenumber();
void parsestring();

void assign();

//----------------------------------------------------------------------------------------------------------------------------------


#endif /* COMMANDS_H */

