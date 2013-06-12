#include "lexer.h"
#include "parser.h"
#include "parserlib.h"
#include "config.h"

Lexer* g_Lexer;
bool g_parserError;

Parser::Parser(Lexer* lexer)
{
  g_Lexer = lexer;
  g_parserError = false;
}


bool Parser::parse()
{
  return !yyparse() && !g_parserError;
}

int yylex(void)
{
  static Token* previous = NULL;
  if(!previous)
    delete(previous);
  Token* token = g_Lexer->GetToken();
  previous = token;
  if(!token)
    {
      yylval.sval = "";
      return T_EOF;
    }
  yylval.sval = token->csLexeme;
  int code = token->nCode;
 
  return code;
}




