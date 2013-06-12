#ifndef _REGISTER_H_
#define _REGISTER_H_
#include "architecture.h"

class Register
{
 private:
  char* name;
  addr_type value;
  int type;
 public:
  Register(char* name_, int type_) : name(name_), type(type_),value(0){}
  Register(char* name_, int type_, addr_type value_) : name(name_), type(type_),value(value_){}
  char* toString(){ return name; }
  addr_type getValue() { return value; }
  bool isGlobal() { return type == GLOBAL; }
  bool isLocal() { return type == LOCAL; }
  bool isOutput() { return type == OUTPUT; }
  bool isFramePtr() { return type == FRAME; }
  bool isStackPtr() { return type == STACK; }
};

#endif
