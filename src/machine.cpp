#include <iostream>
#include "machine.h"
#include "symbol.h"
#include "ASTnode.h"

extern ostream& tab(ostream& o);

Sparc::Sparc(RegisterBank* registerbank_, RegisterBank* outputregisters_,
      RegisterBank* inputregisters_) : registerbank(registerbank_),outputregisters(outputregisters_),inputregisters(inputregisters_)
{
  nextarg = nextiarg = 0;
  ONE = new Register("%g2", GLOBAL); 
  ZERO = new Register("%g0", GLOBAL);
  ifLabels = new PointerStack(NULL);
  whileBeginLabels = new PointerStack(NULL);
  whileEndLabels = new PointerStack(NULL);
  MUL = new ProcSym(".mul", TypeValues::NO_TYPE, 2,NULL);
  DIV = new ProcSym(".div", TypeValues::NO_TYPE, 2, NULL);
  REM = new ProcSym(".rem", TypeValues::NO_TYPE, 2, NULL);
  MEMCPY = new ProcSym("memcpy", TypeValues::NO_TYPE, 3, NULL);
  CALLOC = new ProcSym("calloc", TypeValues::NO_TYPE, 1, NULL);
  o0 = new Register("%o0", OUTPUT);
  l7 = new Register("%l7", LOCAL);
}

/*start of static method definitions*/
void Machine::setCurrentMachine(Machine* currentMachine) { machine = currentMachine; }

int Machine::getIntegerWidth() { return machine->getIntWidth(); }
int Machine::getBooleanWidth() { return machine->getBoolWidth(); }
int Machine::getPointerWidth() { return machine->getPointersWidth(); }
int Machine::getRealWidth() { return machine->getFloatWidth(); }
int Machine::getCharWidth() { return machine->getCharsWidth(); }

/*start of member functions*/
/*Machine*/
void Machine::setOutput(ofstream* output_) { outputTarget = output_; }
void Machine::incompatibleMachineError() 
{ 
  cout<<"incompatible machine architecture"; 
  exit(1);
}

void Machine::emitComment(char* comment, int width)
{
  for(int i = 0; i < strlen(comment); i++)
    {
      if(i % width == 0 )
	*outputTarget << endl << "! ";
      *outputTarget << comment[i];
    }
}

/*Sparc*/
void Sparc::emitProcedureHeader(char* procName, int numparams,
				Symbol** params)
{
  Register *param;
  Register* inputs[NUMBER_OF_INPUT_REGISTERS];
  *outputTarget << ".section\t \".text\"" <<endl;
  *outputTarget << tab << ".global " << procName <<endl;
  *outputTarget << tab << ".type\t " << procName << ", #function " <<endl;
  *outputTarget << procName << ":" <<endl;
  *outputTarget << tab << "!#PROLOGUE# 0" <<endl;
  *outputTarget << tab << "save" << tab << "%sp, " << procName << "_space" << ", %sp" <<endl;
  *outputTarget << tab << "!#PROLOGUE# 1" <<endl;
  if(strcmp(procName, "main") == 0)
    emitMove(1, ONE);
  freeInputRegisters();
  for(int i = 0; i < numparams; i++)
    {
      param = getInputReg();
      if(((VarSym*)params[i])->isReference())
	*outputTarget << tab <<"st\t" << param->toString() << ",[" << ((VarSym*)params[i])->getBase()->toString() << getSign((VarSym*)params[i])<< ((VarSym*)params[i])->getOffset() << "]" << tab<<"! saving to " << params[i]->getName() << endl;
      else
	emitStore(param,(ConstVarSym*)params[i]);
      addInputRegister(param);
    }
    freeInputRegisters();
    emitClear(l7);
}

void Sparc::emitProcedureFooter(char* procName, int spsave)
{
  *outputTarget << tab << procName <<"_space = " << (-(92+spsave)&-8) <<endl;
  *outputTarget << tab << "ret" << endl;
  *outputTarget << tab << "restore" << endl;
}

void Sparc::emitLoadAddress(ConstVarSym* loc, Register* reg)
{
  if(loc->getBase()->isGlobal())
    emitSet(loc->getName(), reg);
  else
    {
      if(((VarSym*)loc)->isReference())
	*outputTarget << tab << "ld\t[" << loc->getBase()->toString() << getSign(loc)<< loc->getOffset() << "]," << reg->toString() << tab << "! load address: " << loc->getName()<<endl;
      else
	*outputTarget << tab << "add" << tab << loc->getBase()->toString() << ",-" << loc->getOffset() << "," <<reg->toString() << tab << "! load address: " << loc->getName()<<endl;
    }
}

void Sparc::emitLoad(ConstVarSym* loc, Register* reg)
{
  char load[5] = "ld";
  if(loc->getType()->getWidth() == getBoolWidth())
    strcpy(load, "ldub");
  if(loc->isConst())
    {
      emitMove(loc->getValue()->getIntValue(), reg);
    }
  else
    {
      if(loc->getBase()->isGlobal())
	{
	  emitSet(loc->getName(), reg);
	  *outputTarget << tab << load <<"\t[" << reg->toString() << "]," << reg->toString();
	  *outputTarget << tab << "! load value of global: "<<loc->getName()<<endl;
	}
      else //local
	{ 
	  if(((VarSym*)loc)->isReference())
	    {
	      *outputTarget << tab << "ld\t[" << loc->getBase()->toString() << getSign(loc)<< loc->getOffset() << "]," << reg->toString()<< tab << "! load reference: " << loc->getName() << endl;
	      *outputTarget << tab << load << tab << "[" << reg->toString() << "]," << reg->toString() << endl;
	    }
	  else  // non reference
	    {
	      *outputTarget << tab << load << tab << "[" <<loc->getBase()->toString() << getSign(loc)<< loc->getOffset() << "]," << reg->toString() << tab << "! load: " << loc->getName() << endl;
	    }
	}
    }
}

void Sparc::emitStore(Register* reg, ConstVarSym* loc)
{
  if(loc->isConst())
    return;
  char store[4] = "st";
  if(loc->getType()->getWidth() == getBoolWidth())
    strcpy(store, "stb");
  Register* greg = getReg();

  if(loc->getBase()->isGlobal())
    {
      emitSet(loc->getName(), greg);
      *outputTarget << tab << store <<"\t" << reg->toString() << ",[" << greg->toString() << "]" << tab<<"! saving to global: " << loc->getName() << endl;
    }
  else 
    {
      if(((VarSym*)loc)->isReference())
	{
	  *outputTarget << tab << "ld\t[" << loc->getBase()->toString() << getSign(loc)<< loc->getOffset() << "]," << greg->toString()<< tab << "! load reference: " << loc->getName() << endl;
	  *outputTarget << tab << store <<"\t" << reg->toString() << ",[" << greg->toString() << "]" << tab<<"! saving ref param: "<<loc->getName()<<endl;
	}
      else //non-reference
	*outputTarget<< tab << store <<"\t" << reg->toString() << ",[" << loc->getBase()->toString() << getSign(loc)<< loc->getOffset() << "]" << tab<<"! saving to " << loc->getName() << endl;
    }
  
  freeReg(greg);
}

char* Sparc::emitBinaryOp(int op, Register* reg1, Register* reg2, Register* reg3)
{
  char* label = NULL;

  switch(op)
    {
    case MULTIPLY:
      emitProcedureCall(MUL,NULL);
      emitMove(o0, reg3);
      break;
    case PLUS:
      *outputTarget << tab << "add" << tab << reg1->toString() << "," << reg2->toString() << "," <<reg3->toString() << endl;
      break;
    case MINUS: 
      *outputTarget << tab << "sub" << tab << reg1->toString() << "," << reg2->toString() << "," <<reg3->toString() << endl;
      break;
    case SLASH: 
      emitProcedureCall(DIV,NULL);
      emitMove(o0, reg3);
      break;
    case DIVIDE:
      emitProcedureCall(DIV,NULL);
      emitMove(o0, reg3);
      break;
    case MOD: 
      emitProcedureCall(REM,NULL);
      emitMove(o0, reg3);
      break;
    case LT: 
      emitCompare(reg1, reg2);
      emitBranch("bge", (label = getLabel(".LL", getNextLabelId())));
      break;
    case GT:
      emitCompare(reg1, reg2);
      emitBranch("ble", (label = getLabel(".LL", getNextLabelId())));
      break;
    case LTE:
      emitCompare(reg1, reg2);
      emitBranch("bg", (label = getLabel(".LL", getNextLabelId())));
      break;
    case GTE:
      emitCompare(reg1, reg2);
      emitBranch("bl", (label = getLabel(".LL", getNextLabelId())));
      break;
    case EQU:
      emitCompare(reg1, reg2);
      emitBranch("bne", (label = getLabel(".LL", getNextLabelId())));
      break;
    case NEQ:
      emitCompare(reg1, reg2);
      emitBranch("be", (label = getLabel(".LL", getNextLabelId())));
      break;
    default:
      ;
    }
  return label;
}

void Sparc::emitOrBegin(ConstVarSym* sym1)
{
  char* label;
  Register* reg = getOutputReg();
  emitLoad(sym1,reg);
  emitCompare(reg, ONE);
  emitBranch("be", (label = getLabel(".OR", getNextLabelId())));
  ifLabels->push((int)label);
  freeOutputReg(reg);
}

void Sparc::emitOrEnd(ConstVarSym* sym2, ConstVarSym* result)
{
  char* label;
  Register* reg = getOutputReg();
  emitLoad(sym2,reg);
  emitCompare(reg, ONE);
  emitBranch("bne", (label = getLabel(".NOTOR", getNextLabelId()))); //second one false skip over setting to 1
  freeOutputReg(reg);
  emitLabel((char*)ifLabels->pop());
  emitMove(1, l7);             //either expr1,expr2 or both are true
  emitLabel(label);            //both conditions false  
  machine->emitStore(l7, result);
  machine->emitClear(l7);
}

void Sparc::emitAndBegin(ConstVarSym* sym1)
{
  char* label;
  Register* reg = getOutputReg();
  emitLoad(sym1,reg);
  emitCompare(reg, ZERO);
  emitBranch("be", (label = getLabel(".NOTAND", getNextLabelId())));
  ifLabels->push((int)label);
  freeOutputReg(reg);
}

void Sparc::emitAndEnd(ConstVarSym* sym2, ConstVarSym* result)
{
  char* label;
  Register* reg = getOutputReg();
  emitLoad(sym2,reg);
  emitCompare(reg, ZERO);
  emitBranch("be", (char*)ifLabels->top()); //second one also false skip over setting to 1
  freeOutputReg(reg);
  emitMove(1, l7);       //expr1,expr2 are both true
  emitLabel((char*)ifLabels->pop());            
  machine->emitStore(l7, result);
  machine->emitClear(l7);
}

void Sparc::emitMove(int value, Register* reg)
{
  if(WITHIN_MOV_IM_RANGE(value))
    {
      *outputTarget << tab << "mov\t" << value << "," << reg->toString();
      *outputTarget << tab << tab << "! " << reg->toString() << "=" << value << endl;
    }
  else
    emitSet(value, reg);
}

void Sparc::emitMove(Register* reg1, Register* reg2)
{
  if(strcmp(reg1->toString(), reg2->toString()) == 0)
    return;
  *outputTarget << tab << "mov\t" << reg1->toString() << "," << reg2->toString();
  *outputTarget << tab << tab << "! " << reg1->toString() << "=" << reg2->toString() << endl;
}

void Sparc::emitSet(int value, Register* reg)
{
  *outputTarget << tab << "set\t" << value << "," << reg->toString();
  *outputTarget << tab << tab << "! " << reg->toString() << "=" << value << endl;
}

void Sparc::emitSet(char* value, Register* reg)
{
  *outputTarget << tab << "set\t" << value << "," << reg->toString();
  *outputTarget << tab << "! " << reg->toString() << "=" << value << endl;
}

void Sparc::emitGlobal(char* globalsym, int size, int alignment)
{
  *outputTarget << tab << ".common\t" << globalsym << "," << size << "," << alignment << endl;
}

void Sparc::emitSaveArgument(ConstVarSym* arg) //loads the value,dereference
{
  Register* reg = getOutputReg();
  
  if(arg->isConst())
    emitMove(arg->getValue()->getIntValue(), reg);
  else
    emitLoad(arg, reg);  

  addArgumentRegister(reg);
}

void Sparc::emitSaveReferenceArgument(ConstVarSym* arg)  //add fp ,offset
{
  Register* reg = getOutputReg();
  emitLoadAddress(arg, reg);  

  addArgumentRegister(reg);
}

void Sparc::emitSaveBoolArgumentAsString(ConstVarSym* arg)
{
  Register* reg = getOutputReg();
  emitIfBegin(arg);
  emitSet(".TRUE",reg);
  emitElseBegin();
  emitSet(".FALSE",reg);
  emitElseEnd();
  addArgumentRegister(reg);
}

void Sparc::emitProcedureCall(ProcSym* procedure, VarSym* result)
{
  freeArgumentRegisters();
  if(procedure->getParamListSize() == -1)
    *outputTarget << tab << "call\t" << procedure->getName() << endl;
  else
    *outputTarget << tab << "call\t" << procedure->getName() << "," <<procedure->getParamListSize() << endl;
  *outputTarget << tab << "nop" <<endl;
  if(result)
    emitStore(o0,result);
    
}

char* Sparc::getSign(ConstVarSym* x) 
{
  char* sign = " + ";
  if(strcmp(x->getBase()->toString(),FRAME_POINTER) == 0)
    sign = " - ";
  return sign;
}

void Sparc::emitSaveString(char* label, char* string)
{
  *outputTarget << label << ":" << endl;
  *outputTarget << tab << ".asciz" << tab << "\"" << string << "\"" << endl;
}

void Sparc::emitReadOnlyDataSection()
{
  *outputTarget << ".section" << tab << "\".rodata\"" <<endl;
}

void Sparc::emitTextSection()
{
  *outputTarget << ".section" << tab << "\".text\"" <<endl;
}

void Sparc::emitReturn(ConstVarSym* expr)
{
  if(expr)  
    emitLoad(expr, new Register("%i0", LOCAL));
  *outputTarget << tab << "ret" << tab << endl;
  *outputTarget << tab << "restore" << endl;
}

void Sparc::emitCompare(Register* reg1, Register* reg2)
{
  *outputTarget << tab << "cmp" << tab << reg1->toString() << "," << reg2->toString() << endl;
}

char* Sparc::getLabel(char* labelbase, int labelid)
{
  char* label = new char[strlen(labelbase)+10];
  sprintf(label, "%s%d", labelbase, labelid);
  return label;
}

char* Sparc::emitBranch(char* branch, char* label)
{
  *outputTarget << tab << branch << tab << label << endl;
  *outputTarget << tab << "nop" << endl;
}

void Sparc::emitIfBegin(ConstVarSym* expr)
{
  Register* reg = getReg();
  char* label;
  emitLoad(expr, reg);
  emitCompare(reg, ONE);
  label = getLabel(".IF", getNextLabelId());
  ifLabels->push((int)label);
  emitBranch("bne", label);
  freeReg(reg);
}

void Sparc::emitIfEnd()
{
  emitLabel((char*)ifLabels->pop());
}

void Sparc::emitElseBegin()
{
  char* label;
  label = getLabel(".ELSE", getNextLabelId());
  emitBranch("b", label);
  emitIfEnd();
  ifLabels->push((int)label);
}

void Sparc::emitElseEnd()
{
  emitLabel((char*)ifLabels->pop());
}

void Sparc::emitLabel(char* label)
{
  *outputTarget << label << ":" << endl;
}

void Sparc::emitSaveArgumentsMacroCall(Register* reg1, Register* reg2)
{
  addArgumentRegister(reg1);
  addArgumentRegister(reg2);
}

void Sparc::emitClear(Register* reg)
{
  *outputTarget << tab << "clr\t" << reg->toString() << endl;
}

void Sparc::emitNeg(Register* reg)
{
  *outputTarget << tab << "neg\t" << reg->toString() << tab << tab << "! negating" <<endl;
}

void Sparc::emitNot(Register* reg)
{
  *outputTarget << tab << "xor\t" << reg->toString() << "," << ONE->toString() << "," << reg->toString() << tab << "! negating" <<endl;
}

void Sparc::emitWhileBegin()
{
  char* label;
  
  whileBeginLabels->push((int)(label = getLabel(".BEGWHILE", getNextLabelId())));
  emitLabel(label);
}

void Sparc::emitWhileMiddle(ConstVarSym* expr)
{
  Register* reg = getReg();
  char* label;
  emitLoad(expr, reg);
  emitCompare(reg, ZERO);
  whileEndLabels->push((int)(label = getLabel(".ENDWHILE", getNextLabelId())));
  emitBranch("be", (char*)whileEndLabels->top());
  freeReg(reg);
}

void Sparc::emitWhileEnd()
{
  emitBranch("b",(char*)whileBeginLabels->pop());
  emitLabel((char*)whileEndLabels->top());
  whileEndLabels->pop();
}

void Sparc::emitExit() 
{
  emitBranch("b",(char*)whileEndLabels->top());
}

