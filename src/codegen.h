#ifndef _CODEGEN_H_
#define _CODEGEN_H_
#include <iostream>
#include <fstream>
#include "machine.h"
#include "symbol.h"
#include "stack.h"

#define NOT_IN_RECORD -1
#define BEGIN_RECORD  -2

class CodeGenerator
{
 private:
  Machine* machine;
  char* target;
  ofstream outputTarget;
  Register* scopePointer;
  int scopeOffset;
  int globalOffset;
  int recordOffset;
  int base;
  bool newline_generated;
  Stack* records;
  void processBinaryOperatorsPostMortum(Register* rr, VarSym* result, int op, char* label);
 
public:
  Stack* lastObj;
  CodeGenerator(Machine* machine_, char* output_target) : machine(machine_), target(output_target), scopeOffset(0),globalOffset(0),newline_generated(false),base(0)
    { 
      scopePointer = machine->getFramePointer();
      recordOffset = NOT_IN_RECORD;
      lastObj = new Stack();
      records = new Stack();
    }
  ofstream* getOutputStream() { return &outputTarget; }
  void beginCodeGen();
  void endCodeGen();
  void abortCodeGen();
  char* getIdentity() { return "Oberon Copyright 2002, Bashir Eghbali"; }
  inline void emitHeader();
  inline void emitFooter();
  void emitBinaryOperation(VarSym* result, ConstVarSym* arg1, int op, ConstVarSym* arg2);
  void emitConstant(ConstSym* constant);
  Register* getScopePointer() { return scopePointer; }
  void setScopePointer(Register* scopePointer_) 
    { 
      if(scopePointer->isGlobal())
	globalOffset += scopeOffset;
      scopePointer = scopePointer_; 
      scopeOffset = 0;
    }
  inline Register* getGlobalPointer() { return machine->getGlobalPointer();}
  inline Register* getStackPointer() { return machine->getStackPointer();}
  inline Register* getFramePointer() { return machine->getFramePointer();}
  inline int getScopeOffset() { return scopeOffset; }
  inline void setScopeOffset(int offset) { scopeOffset = offset; }
  inline void incrementScopeOffset(int increment) { scopeOffset += increment; }
  inline int getCurrentRecordOffset() { return records->top(); }
  addr_type getAndSetCurrentRecordOffset(addr_type width);
  inline void setCurrentRecordOffset(int offset) { records->pop(); records->push(offset); }
  inline bool inRecord() { return !records->empty();}
  inline void openRecord() { records->push(BEGIN_RECORD);}
  inline void closeRecord() { records->pop();}
  addr_type calcAndSetOffset(addr_type width);
  inline void emitProcedureHeader(char* procName,int numparams,Symbol** params){ machine->emitProcedureHeader(procName,numparams,params); }
  inline void emitProcedureFooter(char* procName, int spsave){machine->emitProcedureFooter(procName,spsave);}
  void emitGlobals(Symbol** global_list, int listsize);
  void emitAssignment(VarSym* lhs, ConstVarSym* rhs);
  inline void emitSaveArgument(ConstVarSym* arg) { machine->emitSaveArgument(arg);}
  inline void emitSaveReferenceArgument(ConstVarSym* arg) { machine->emitSaveReferenceArgument(arg); }
  void emitSaveProcedureArgument(ConstVarSym* arg, VarSym* param,bool fromprintf=false);
  inline void emitProcedureCall(ProcSym* proc,VarSym* result) { machine->emitProcedureCall(proc,result);}
  int getNextLabelId() { static int id = 0; return id++;}
  char* getLabel(char* labelbase, int labelid)
    {
      char* label = new char[strlen(labelbase+10)];
      sprintf(label, "%s%d", labelbase, labelid);
      return label;
    }
  char* freeLabel(char* label) { delete label;}
  void emitSaveStringArgument(char* string);
  char* emitSaveString(char* string);
  inline void emitReadOnlyDataSection(){machine->emitReadOnlyDataSection();}
  inline void emitTextSection(){machine->emitTextSection();}
  inline int getTempStorageWidth() { return 8; }
  inline void emitReturn(ConstVarSym* expr) { machine->emitReturn(expr);}
  inline void emitIfBegin(ConstVarSym* expr) { machine->emitIfBegin(expr); }
  inline void emitIfEnd() { machine->emitIfEnd(); }
  inline void emitElseBegin() { machine->emitElseBegin(); }
  inline void emitElseEnd() { machine->emitElseEnd(); }
  void emitNegation(ConstVarSym* expr, ConstVarSym* result);
  inline void emitWhileBegin() { machine->emitWhileBegin(); }
  inline void emitWhileMiddle(ConstVarSym* expr) { machine->emitWhileMiddle(expr); }
  inline void emitWhileEnd() { machine->emitWhileEnd(); }
  inline void emitExit() { machine->emitExit(); }
  inline void emitOrBegin(ConstVarSym* sym1) { machine->emitOrBegin(sym1); }
  inline void emitOrEnd(ConstVarSym* sym2, ConstVarSym* result){ machine->emitOrEnd(sym2,result); }
  inline void emitAndBegin(ConstVarSym* sym1){ machine->emitAndBegin(sym1); }
  inline void emitAndEnd(ConstVarSym* sym2, ConstVarSym* result) { machine->emitAndEnd(sym2,result); }
  void emitArray(ConstVarSym* index, addr_type elemsize, VarSym* arraybase, VarSym* result, bool onedim=false);
  void emitNew(VarSym* ptr);
  void emitPointerReference(VarSym* base, VarSym* field, VarSym* result);
};
#endif
