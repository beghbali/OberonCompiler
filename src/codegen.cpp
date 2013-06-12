#include <iostream>
#include "codegen.h"
#include "ASTnode.h"
#include <math.h>

extern ostream& tab(ostream& o);

void CodeGenerator::beginCodeGen()
{
  outputTarget.open(target,ios::out);
  if(!outputTarget.is_open())
    {
      cout<<"unable to open target file '"<<target<<"'."<<endl;
      abortCodeGen();
    }
  else
    emitHeader();
}

void CodeGenerator::endCodeGen()
{
  emitFooter();
  if(outputTarget && outputTarget.is_open())
    outputTarget.close();
}

void CodeGenerator::abortCodeGen()
{
  char systemcommand[30];
  cout<<"Aborting Code Generation"<<endl;
  if(outputTarget)
    outputTarget.close();
  if(machine->isSparc())
    sprintf(systemcommand, "rm -f %s", target);
  else
    machine->incompatibleMachineError();
  system(systemcommand);
}

void CodeGenerator::emitHeader() 
{
  outputTarget << tab << ".file \"" << target << "\"" <<endl;
  outputTarget << "oberon1_compiled.:" <<endl;
  outputTarget << ".section\t\".rodata\"" << endl;
  outputTarget << ".TRUE:\t.asciz\t\"TRUE\"" << endl;
  outputTarget << ".FALSE:\t.asciz\t\"FALSE\"" << endl;
}

void CodeGenerator::emitFooter()
{
  outputTarget << tab << ".ident\t\"" << getIdentity() << "\"" <<endl;
}

void CodeGenerator::emitBinaryOperation(VarSym* result, ConstVarSym* arg1, int op, ConstVarSym* arg2)
{
  Register* r1, *r2, *rr;
  char* label;
  r1 = machine->getOutputReg();
  r2 = machine->getOutputReg();
  rr = machine->getOutputReg();
  machine->emitLoad(arg1, r1);
  machine->emitLoad(arg2, r2);
  label = machine->emitBinaryOp(op, r1,r2,rr);
  processBinaryOperatorsPostMortum(rr, result, op, label);
  machine->freeOutputReg(rr);
  machine->freeOutputReg(r2);
  machine->freeOutputReg(r1);
}

void CodeGenerator::processBinaryOperatorsPostMortum(Register* rr, VarSym* result,int op, char* label)
{
  Register* l7 = new Register("%l7", LOCAL);
  if(op >= EQU && op <= GTE)   //relation operations
    {
      machine->emitMove(1, l7);
      
      machine->emitLabel(label);
      machine->emitStore(l7, result);
      machine->emitClear(l7);
    }
  else
    {
      machine->emitStore(rr, result);
    }
  delete l7;
}

void CodeGenerator::emitConstant(ConstSym* constant)
{
  Register* rr = machine->getReg();
  machine->emitMove(constant->getValue()->getIntValue(), rr);
  machine->emitStore(rr, constant); 
  machine->freeReg(rr);
}

void CodeGenerator::emitGlobals(Symbol** global_list, int listsize)
{
  for(int i = 0; i < listsize ; i++)
    { 
      if(global_list[i]->isVar())
	machine->emitGlobal(global_list[i]->getName(), global_list[i]->getWidth(), global_list[i]->getAlignment());
    }
} 

void CodeGenerator::emitAssignment(VarSym* lhs, ConstVarSym* rhs)
{
  Register* rr;
  
  if(lhs->getType()->isArray() && rhs->getType()->isArray())
    {
      machine->emitSaveReferenceArgument(lhs);
      machine->emitSaveReferenceArgument(rhs);
      machine->emitSaveArgument(new ConstSym("",TypeValues::INTEGER_TYPE, new Value(rhs->getType()->getWidth()),NULL,0));
      machine->emitProcedureCall(machine->getMemoryCopyRoutine(),NULL);
    }
  else
    {
      rr = machine->getReg();
      machine->emitLoad(rhs, rr);
      machine->emitStore(rr, lhs);  
      machine->freeReg(rr);
    }
}

addr_type CodeGenerator::calcAndSetOffset(addr_type width)
{
  static int align = machine->getPointerWidth();
  int offset;
  if(getScopeOffset() == 0)
    align = machine->getPointerWidth();

  if(width < machine->getPointerWidth() && (align - width) >= 0)
    {
      offset = (getScopeOffset() + width);
      setScopeOffset(offset);
      align = abs((align-width)%machine->getPointerWidth());
    }
  else 
    {
      setScopeOffset((getScopeOffset() + (align == machine->getPointerWidth() ? 0 : align)) + width);
      align = machine->getPointerWidth() - (width % 4);
      offset = getScopeOffset();
    }

  return offset;
}

int CodeGenerator::getAndSetCurrentRecordOffset(addr_type width)
{
  static int align = machine->getPointerWidth();
  int offset;
  if(getCurrentRecordOffset() == BEGIN_RECORD)
    {
      align = machine->getPointerWidth();
      setCurrentRecordOffset(width);
      return 0;
    }
  if(width < machine->getPointerWidth() && (align - width) >= 0)
    {
      offset = (getCurrentRecordOffset() + width);
      setCurrentRecordOffset(offset);
      align = abs((align-width)%machine->getPointerWidth());
    }
  else 
    {
      setCurrentRecordOffset((getCurrentRecordOffset() + (align == machine->getPointerWidth() ? 0 : align)) + width);
      align = machine->getPointerWidth() - (width % 4);
      offset = getCurrentRecordOffset();
    }

  return offset;
}

void CodeGenerator::emitSaveStringArgument(char* string)
{
  Register* rr = machine->getOutputReg();
  machine->emitSet(string, rr);

  machine->addArgumentRegister(rr);
}

char* CodeGenerator::emitSaveString(char* string)
{
  char* label;
  if(strcmp(string, "\n") == 0)
    {
      if(newline_generated)
	return ".NEWLINE";
      label = ".NEWLINE";
      newline_generated = true;
    }
  else
    label = getLabel(".LLC",getNextLabelId());
  machine->emitSaveString(label, string);
  return label;
}

void CodeGenerator::emitNegation(ConstVarSym* expr, ConstVarSym* result)
{
  Register* reg = machine->getReg();
  machine->emitLoad(expr, reg);
  if(expr->getType()->isBool())
    machine->emitNot(reg);
  else
    machine->emitNeg(reg);
  machine->emitStore(reg, result);
  machine->freeReg(reg);
}

void CodeGenerator::emitArray(ConstVarSym* index, addr_type elemsize,
			      VarSym* arraybase, VarSym* result, bool onedim)
{
  Register* r1,*r2,*r3;
  r1 = machine->getOutputReg();
  r2 = machine->getOutputReg();
  r3 = machine->getOutputReg();
  machine->emitMove(elemsize, r1);
  machine->emitLoad(index, r2);
  machine->emitBinaryOp(MULTIPLY, r1,r2,r2);  //r2 holds elemsize*index
  machine->emitLoadAddress(arraybase, r1);
  machine->emitBinaryOp(PLUS, r1, r2, r3);
  if(!onedim)
    result->setReference(false);
  machine->emitStore(r3, result);
  if(!onedim)
     result->setReference(true);
  machine->freeOutputReg(r3);    
  machine->freeOutputReg(r2);    
  machine->freeOutputReg(r1);    
}

void CodeGenerator::emitNew(VarSym* ptr)
{
  machine->emitSaveArgument(new ConstSym("",TypeValues::INTEGER_TYPE, new Value(1), NULL, 0));
  machine->emitSaveArgument(new ConstSym("", TypeValues::INTEGER_TYPE, new Value(ptr->getType()->getBaseType()->getWidth()),NULL,0));
  machine->emitProcedureCall(machine->getMemoryAllocatorRoutine(), ptr);
}

void CodeGenerator::emitPointerReference(VarSym* base, VarSym* field, VarSym* result)
{
  Register* basereg,*fieldOffsetReg;
  basereg = machine->getReg();
  fieldOffsetReg = machine->getReg();
  machine->emitLoad(base, basereg);
  machine->emitMove(field->getOffset(), fieldOffsetReg);
  machine->emitBinaryOp(PLUS, basereg, fieldOffsetReg, basereg);
  Type* temptype = result->getType();
  result->setType(TypeValues::POINTER_TYPE); //to overrride the address instead of dereferencing it
  result->setReference(false);
  machine->emitStore(basereg, result);
  result->setReference(true);
  result->setType(temptype);
  machine->freeReg(fieldOffsetReg);
  machine->freeReg(basereg);
}

void CodeGenerator::emitSaveProcedureArgument(ConstVarSym* arg, VarSym* param, bool fromprintf)
{
  if(param && param->isReference())
    machine->emitSaveReferenceArgument(arg);
  else if(arg->getType()->isBool() && fromprintf)
    machine->emitSaveBoolArgumentAsString(arg);
  else
    emitSaveArgument(arg);
}
