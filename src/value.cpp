#include <string>
#include <limits.h>
#include <cstdlib>
#include <stdio.h>
#include <errno.h>
#include "value.h"
#include "errorhandler.h"

int Value::parseInt(char* str) 
{ 
  char* error;
  int value = 0;

  if(strcmp(strtok(str, "ABCDEF"), str) == 0)
    value = (int)strtol(str, &error, 10);
  else
    value = (int)strtol(str, &error, 16);
  if(errno)
    {
      char message[50];
      sprintf(message, "The number %s is out of range for integer space, range[%d-%d]", str, LONG_MIN, LONG_MAX);
      ErrorHandler::fatalError(message);
    }
  return value; 
}   

double Value::parseReal(char* str)
{
  char* exponent;
  char* error;
  double value;
  if((exponent = strchr(str, 'D')))
    *exponent = 'E';
  value = strtod(str, &error);
  if(errno)
    {
      char message[50];
      sprintf(message, "The real literal %s could not be converted. Illegal format/Out of range", str);
      ErrorHandler::fatalError(message);
    }
  return value;
}

char Value::parseChar(char* str)
{
  int value;
  *strchr(str,'X') = '\0';
  value = parseInt(str);
  if(value > 255)
    {
      char message[30];
      sprintf(message, "The character %s is not an ASCII character", str);
      ErrorHandler::warning(message);
    }
  return (char)value;
}

char* Value::boolToString(bool value)
{
  return value ? (char*)"TRUE" : (char*)"FALSE";
}
