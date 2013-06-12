#ifndef _PARSER_H_
#define _PARSER_H_

#include "token.h"
#include "lexer.h"

#define T_EOF 0
class Parser
{

public:
  Parser(Lexer* lexer);
  bool parse();
};

int yyparse();

#endif
