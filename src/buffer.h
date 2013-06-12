#ifndef _BUFFER_H_
#define _BUFFER_H_

#include <stack>
#include "config.h"
#include <iostream>
#include "inputStruct.h"

class Buffer
{
private:
  char buffer[SYSTEM_BLOCK_SIZE+2];
  char* forward;
  char* backward;
  char* end;
  char* mid;
  istream* currentFile;
  char lastChar;
  stack<inputStruct*>* files;
  bool fillHalf();
  inline void saveContext();
public:
  ~Buffer();
  Buffer(stack<inputStruct*>* s_files);
  char getChar();
  char putChar();
  char* getLexeme();
  void resetLexeme();
  void resetFile();
};

#endif

