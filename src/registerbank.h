#ifndef _REGISTERBANK_H_
#define _REGISTERBANK_H_
#include <iostream.h>
#include "register.h"
#include "stack.h"
#include "architecture.h"

class RegisterBank
{
 private:
  PointerStack* registers;
  Register* gp;
  Register* sp;
  Register* fp;
  Register* errreg;
 public:
  RegisterBank(char** registerNames, int numberOfRegisters_, int type)
    {
      registers = new PointerStack(NULL, numberOfRegisters_);
      
      for(int i = 0; i < numberOfRegisters_; i++)
	{
	  registers->push((int)(new Register(registerNames[i], type)));
	}
      errreg = new Register("ERR",GLOBAL);
    }
  Register* getReg()
    {
      if(!registers->empty())
	{ 
	  return (Register*)registers->pop();
	}
      /*put code for spilling achregisters on stack and freeing up a register*/

      cout<<"ERROR: out of registers. " <<endl;
 
      return errreg;
    }
  void freeReg(Register* reg_to_be_freed)
    {
      registers->push((int)reg_to_be_freed);
    }
  inline void setGlobalPointer(Register* gp_) { gp = gp_; }
  inline void setStackPointer(Register* sp_) { sp = sp_; }
  inline void setFramePointer(Register* fp_) { fp = fp_; }
  inline Register* getGP() { return gp; }
  inline Register* getSP() { return sp; }
  inline Register* getFP() { return fp; }
};

#endif
