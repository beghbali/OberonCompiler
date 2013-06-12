#include "parserlib.h"
#include <cstdlib>
#include <string>
#include <fstream>
#include "symbol.h"

char* concat(char* a, char* b)
{
  if(!a)
    a = "";
  if(!b)
    b = "";
  char* result = (char*)malloc(strlen(a)+strlen(b)+1);
  strcpy(result, a);
  strcat(result, b);
  return result;
}



/*used for export list implementation of Module-with PointerStack
  class and for the implementation of record fields*/
bool eql_func (int a, int b)
{
  return strcmp(((Symbol*)a)->getName(),(char*)b) == 0 ? true : false;
}

ostream& tab(ostream& o) { o << "\t"; return o ; } 
