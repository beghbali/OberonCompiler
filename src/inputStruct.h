#ifndef _INPUTSTRUCT_H_
#define _INPUTSTRUCT_H_

#include <iostream.h>

class inputStruct
{
public:
  char* filename;
  istream* file;
  int line;
  inputStruct()
    {
      filename = NULL;
      file = NULL;
      line = 0;
    }
};

#endif

