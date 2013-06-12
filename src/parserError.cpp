#include "parserlib.h"
#include "lexer.h"
#include "inputStruct.h"
#include "errorhandler.h"
#include "config.h"

extern Lexer* g_Lexer;
extern bool g_parserError;

static bool suppress_error;

void yyerror(const char* error)
{
  static inputStruct* current;
  if(suppress_error)
    {
      suppress_error = false;
      return;
    }
  current = g_Lexer->getInputStruct();

  if(strcmp(error, "syntax error") == 0)
    {
      char* error1 = (char*)malloc(strlen(error)+50);
      strcpy(error1,error);
      strcat(error1, " near \"");
      strcat(error1, yylval.sval);
      strcat(error1, "\".");
      ERROR(parserError, current, error1);
    }
  else
    {
      ERROR(parserError, current, error);
    }
  g_parserError = true;
}

void suppressError()
{
  suppress_error = true;
}
