#ifndef _LIB_H_
#define _LIB_H_

#include <string.h>
#include <cctype>
#include "config.h"

#define TOKEN(code, lexeme) \
                            token->nCode = code; \
			    strcpy(token->csLexeme, lexeme);

static int strchrcount(char* str, char c)
{
  int count = 0;

  while(strchr(str,c))
    count++;

  return count;
}

static char* firstEOF(char* buff)
{
  for(int i = 0;;i++)
    {
      if(buff[i] == EOF)
	return &buff[i];
    }
}

static inline bool isXdigit(char c)
{
  return (isxdigit(c) && isupper(c));
}

static inline bool isDXdigit(char c)
{
  return (isXdigit(c) || isdigit(c));
}

struct eqstr
{
  bool operator () (const char* a, const char* b) const
  {
    return strcmp(a,b) == 0;
  }
};

struct eqstr2
{
  bool operator () (const char* a, const char* b) const
  {
    return a[0] == b[0];
  }
};

#endif



