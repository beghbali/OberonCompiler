#ifndef _MACHINE_H_
#define _MACHINE_H_
#include <iostream>
#include <fstream>
#include "registerbank.h"
#include "stack.h"

class ConstVarSym;
class ProcSym;
class VarSym;
class Symbol;

class Machine
{
 protected: 
  ofstream* outputTarget; 

  virtual int getIntWidth() { return 4; }
  virtual int getBoolWidth() { return 1; }
  virtual int getPointersWidth() { return 4; }
  virtual int getFloatWidth() { return 4; }
  virtual int getCharsWidth() { return 1; }
 public:
  static Machine* machine;
  Machine(void) {}
  void incompatibleMachineError();
  void setOutput(ofstream* output_);
  virtual char* getMachineName() { return "Generic"; }
  virtual bool isSparc() { return false; }
  static void setCurrentMachine(Machine* currentMachine);
  static int getIntegerWidth();
  static int getBooleanWidth();
  static int getPointerWidth();
  static int getRealWidth();
  static int getCharWidth();
  inline virtual Register* getReg() { return NULL; } 
  inline virtual void freeReg(Register* reg) {}
  inline virtual Register* getOutputReg() { return NULL;}
  inline virtual void freeOutputReg(Register* reg) {}
  inline virtual void emitProcedureHeader(char* procName,int numparams,Symbol** params) { }
  inline virtual void emitProcedureFooter(char* procName,int stacksave){}
  inline virtual Register* getGlobalPointer() { return NULL;}
  inline virtual Register* getStackPointer() { return NULL;}
  inline virtual Register* getFramePointer() { return NULL;}
  inline virtual void emitLoad(ConstVarSym* loc, Register* reg) {}
  inline virtual void emitLoadAddress(ConstVarSym* loc, Register* reg) {}
  inline virtual void emitStore( Register* reg, ConstVarSym* loc) {}
  inline virtual char* emitBinaryOp(int op, Register* reg1, Register* reg2, Register* reg3) {}
  inline virtual void emitMove(int value, Register* reg) {}
  inline virtual void emitMove(Register* reg1, Register* reg2){}
  inline virtual void emitSet(int value, Register* reg) {}
  inline virtual void emitSet(char* value, Register* reg) {}
  inline virtual void emitGlobal(char* globalsym, int size, int alignment){}
  inline virtual void emitComment(char* comment, int width = 20);
  inline virtual void emitSaveArgument(ConstVarSym* arg){}
  inline virtual void emitSaveReferenceArgument(ConstVarSym* arg){}
  inline virtual void emitSaveBoolArgumentAsString(ConstVarSym* arg){}
  inline virtual void emitProcedureCall(ProcSym* proc,VarSym* result){}
  inline virtual void addArgumentRegister(Register* reg) {}
  inline virtual void emitSaveString(char* label, char* string){}
  inline virtual void emitReadOnlyDataSection(){}
  inline virtual void emitTextSection(){}
  inline virtual void emitReturn(ConstVarSym* expr) {}
  inline virtual void emitCompare(Register* reg1, Register* reg2){}
  inline virtual void emitIfBegin(ConstVarSym* expr) {}
  inline virtual void emitIfEnd() {}
  inline virtual void emitElseBegin() {}
  inline virtual void emitElseEnd() {}
  inline virtual void emitLabel(char* label) {}
  inline virtual char* emitBranch(char* branch, char* label) {}
  inline virtual void emitClear(Register* reg) {} 
  inline virtual void emitNeg(Register* reg) {}
  inline virtual void emitNot(Register* reg) {}
  inline virtual void emitWhileBegin() { }
  inline virtual void emitWhileMiddle(ConstVarSym* expr) { }
  inline virtual void emitWhileEnd() {}
  inline virtual void emitExit() {}
  inline virtual void emitOrBegin(ConstVarSym* sym1) {}
  inline virtual void emitOrEnd(ConstVarSym* sym2, ConstVarSym* result) {}
  inline virtual void emitAndBegin(ConstVarSym* sym1) {}
  inline virtual void emitAndEnd(ConstVarSym* sym2, ConstVarSym* result) {}
  inline virtual ProcSym* getMemoryAllocatorRoutine() {}
  inline virtual ProcSym* getMemoryCopyRoutine(){}
};

class Sparc : public Machine
{
 private:
  RegisterBank* registerbank;
  RegisterBank* outputregisters;
  RegisterBank* inputregisters;
  Register* argRegs[NUMBER_OF_OUTPUT_REGISTERS];
  Register* inputRegs[NUMBER_OF_INPUT_REGISTERS];
  Register* ONE;
  Register* ZERO;
  Register* o0;
  Register* l7;
  PointerStack* ifLabels;
  PointerStack* whileBeginLabels;
  PointerStack* whileEndLabels;
  int nextarg;
  int nextiarg;
  ProcSym* MUL;
  ProcSym* DIV;
  ProcSym* REM;
  ProcSym* CALLOC;
  ProcSym* MEMCPY;
  char* getSign(ConstVarSym* x);
  void freeArgumentRegisters()
    {
      for(int i = nextarg-1; i >= 0  ; i--)
	outputregisters->freeReg(argRegs[i]);
      nextarg = 0;
    }
  void freeInputRegisters()
    {
      for(int i = nextiarg-1; i >= 0  ; i--)
	inputregisters->freeReg(inputRegs[i]);
      nextiarg = 0;
    }
 public:
  Sparc(RegisterBank* registerbank_, RegisterBank* outputregisters_,RegisterBank* inputregisters_);
  char* getMachineName() { return "SPARC"; }
  bool isSparc() { return true; }
  void emitProcedureHeader(char* procName,int numparams, Symbol** params);
  void emitProcedureFooter(char* procName, int spsave);
  inline int getIntWidth() { return 4; }
  inline int getBoolWidth() { return 1; }
  inline int getPointersWidth() { return 4; }
  inline int getFloatWidth() { return 4; }
  inline int getCharsWidth() { return 1; }
  inline Register* getReg() { return registerbank->getReg(); }
  inline void freeReg(Register* reg) { registerbank->freeReg(reg); }
  inline Register* getOutputReg() { return outputregisters->getReg();}
  inline void freeOutputReg(Register* reg) { outputregisters->freeReg(reg);}
  inline Register* getInputReg() { return inputregisters->getReg();}
  inline void freeInputReg(Register* reg) { inputregisters->freeReg(reg);}
  inline Register* getGlobalPointer() { return registerbank->getGP();}
  inline Register* getStackPointer() { return registerbank->getSP();}
  inline Register* getFramePointer() { return registerbank->getFP();}
  void emitLoad(ConstVarSym* loc, Register* reg);
  void emitLoadAddress(ConstVarSym* loc, Register* reg);
  void emitStore(Register* reg, ConstVarSym* loc);
  char* emitBinaryOp(int op, Register* reg1, Register* reg2, Register* reg3);
  void emitMove(int value, Register* reg);
  void emitMove(Register* reg1, Register* reg2);
  void emitSet(int value, Register* reg);
  void emitSet(char* value, Register* reg);
  void emitGlobal(char* globalsym, int size, int alignment);
  void emitSaveArgument(ConstVarSym* arg);
  void emitSaveReferenceArgument(ConstVarSym* arg);
  void emitSaveBoolArgumentAsString(ConstVarSym* arg);
  void emitProcedureCall(ProcSym* proc, VarSym* result);
  void addArgumentRegister(Register* reg) { argRegs[nextarg++] = reg;}
  void addInputRegister(Register* reg) { inputRegs[nextiarg++] = reg;}
  void emitSaveString(char* label, char* string);
  void emitReadOnlyDataSection();
  void emitTextSection();
  void emitReturn(ConstVarSym* expr);
  void emitCompare(Register* reg1, Register* reg2);
  char* getLabel(char* labelbase, int labelid);
  int getNextLabelId() { static int id = 0; return id++;}
  void emitIfBegin(ConstVarSym* expr);
  void emitIfEnd();
  void emitElseBegin();
  void emitElseEnd();
  void emitLabel(char* label);
  char* emitBranch(char* branch, char* label);
  void emitSaveArgumentsMacroCall(Register* reg1, Register* reg2);
  void emitClear(Register* reg);
  void emitNeg(Register* reg);
  void emitNot(Register* reg);
  void emitAnd(Register* reg1, Register* reg2, Register* reg3);
  void emitOr(Register* reg1, Register* reg2, Register* reg3);
  char* emitOrEnd();
  void emitWhileBegin();
  void emitWhileMiddle(ConstVarSym* expr);
  void emitWhileEnd();
  void emitExit();
  void emitOrBegin(ConstVarSym* sym1);
  void emitOrEnd(ConstVarSym* sym2, ConstVarSym* result);
  void emitAndBegin(ConstVarSym* sym1);
  void emitAndEnd(ConstVarSym* sym2, ConstVarSym* result);
  ProcSym* getMemoryAllocatorRoutine() { return CALLOC;}
  ProcSym* getMemoryCopyRoutine() { return MEMCPY;}
};

#endif
