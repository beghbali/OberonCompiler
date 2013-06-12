#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include "semchecker.h"
#include "errorhandler.h"
#include "message.h"
#include "debug.h"
#include "config.h"
#include "type.h"
#include "binaryexpr.h"
//#define DEBUG 1
extern char** predeclared_procs;
extern bool GEN_SYMTABLE;

SemanticChecker::SemanticChecker(SymbolTable* symtable_, ASTNode* ast_, CodeGenerator* codegen_):symtable(symtable_), ast(ast_), codegen(codegen_),inMain(false)
{
  /* for(int i = 0; i < PREDECLARED_SIZE; i++)
    predeclared->insert(new ProcSym(predeclared_procs[i], ));
  */
  loops = 0;
}

bool SemanticChecker::check()
{
  int globalsize;
  symtable->begin_scope();
  codegen->setScopePointer(codegen->getGlobalPointer());
  check(ast);
  if(GEN_SYMTABLE)
    symtable->printTable();
  codegen->emitGlobals(symtable->getSymbolsInCurrentScope(&globalsize),globalsize);
  symtable->end_scope();
  return ErrorHandler::getStatus();
}

Symbol* SemanticChecker::check(ASTNode* node)
{ 
#ifdef DEBUG
  traceAST(node);
#endif  
  Symbol* returnsym;
  int type;

  if(!node)
    return Symbol::ERROR_SYM;

  type = GETTYPE(node->nodetype); 
  returnsym = node->sym;
  
  if(type == AST_MainStmtsSection)
    {
      check_mainStmt(node);
    }
  else if(type == AST_ConstDecl)
    {
      check((*node)[0]);
      Symbol* constexpr = check((*node)[2]);
      if(constexpr->getType()->isError())
	((ConstSym*)constexpr)->setValue(new Value(-1));
      insertCVTSymbols((*node)[1], CONSTTYPE,constexpr);
      checkKnownAtCompileTime((*node)[2], (*(*node)[1])[0]->sym,constexpr);
    }
  else if(type == AST_TypeDecl) 
    {
      check_typeDecl(node);
    }
  else if(type == AST_VarDecl) 
    {
      check((*node)[0]);
      insertCVTSymbols((*node)[1], VARTYPE,check((*node)[2]));
    }
  else if(type == AST_ProcDecl) 
    {
      check_procDecl(node);
    }
  else if(type == AST_ParamList)
    {
      returnsym = combineParamList(node);
    }
  else if(type == AST_ParamDecl) 
    {
      check((*node)[0]);
      returnsym = new ProcSym(NULL, new ProcType(TypeValues::NO_TYPE),
	(*node)[1]->size,insertIdSymbols((*node)[1],check((*node)[2])->getType(),(*node)[0] ? true : false));
    }
  else if(type == AST_FieldList)
    {
      returnsym = new ProcSym(NULL, new ProcType(TypeValues::NO_TYPE),
	(*node)[0]->size,insertIdSymbols((*node)[0],check((*node)[1])->getType(), true, false));
    }
  else if(type == AST_ExprList || type == AST_OptFormalParams || type ==
	  AST_OptParamList || type == AST_OptReturnType || type ==
	  AST_ConstExpr || type == AST_Expr3 || type == AST_Exprk)
    {
      return check((*node)[0]);
    }
  else if(type == AST_ExprList2)
    {
      process_write(node);
    }
  else if(type == AST_InputStmt)
    {
      process_read((*node)[0]);
    }
  else if(type == AST_BasicType)
    {
      returnsym = (*node)[0]->sym;
    }
  else if(type == AST_FormalParams)
    {
      if((*node)[0])
	returnsym = check((*node)[0]);
      else
	returnsym = new ProcSym(NULL, NULL, 0, NULL);
      if(!(*node)[1])
	((ProcType*)returnsym->getType())->setReturnType(TypeValues::NO_TYPE);
      else
	((ProcType*)returnsym->getType())->setReturnType(check((*node)[1])->getType());
    }
  else if(type == AST_OptReceiver)
    {
      return check_optReceiver(node);
    }
  else if(type == AST_Type)
    {
      if((*node)[0] && GETTYPE((*node)[0]->nodetype) == AST_Type)  //pointer
	return check_pointerDecl(node, check((*node)[0]));
      else if((*node)[1] && GETTYPE((*node)[1]->nodetype) == AST_Type)     //array
	return check_arrayDecl(node, check((*node)[0]), check((*node)[1]));
      else if((*node)[1] && GETTYPE((*node)[1]->nodetype) == AST_FieldsList)  //record
	return check_recordDecl((*node)[0], (*node)[1]);
      
      return check((*node)[0]);  //QualIdent, BasicType
    }
  else if(type == AST_FieldsList)
    {
      returnsym = combineFieldsList(node);
    }
  else if(type == AST_AssignStmt)
    {
      Symbol* result = check((*node)[0]);
      checkAssignment(node, result, check((*node)[1]));
    }
  else if(type == AST_ReturnStmt)
    {
      check_returnStmt(node, currentProcedure);
    }
  else if(type == AST_ProcCall)
    {
      Symbol* proc = check((*node)[0]);
      check_procCall(node, proc, (*node)[1]);
      codegen->emitProcedureCall((ProcSym*)proc,NULL);
    }
  else if(type == AST_IfStmt)
    {
      Symbol* expr = check((*node)[0]);
      checkIfWhileRepeat((*node)[0], expr->getType());
      codegen->emitIfBegin((ConstVarSym*)expr);
      traverse(node, &SemanticChecker::check, 1,2);
      if((*node)[3])   //has else
	{
	  codegen->emitElseBegin();
	  traverse(node, &SemanticChecker::check, 3);
	  codegen->emitElseEnd();
	}
      else
	codegen->emitIfEnd();
      
    }
  else if(type == AST_WhileStmt)
    {
      codegen->emitWhileBegin();
      Symbol* expr = check((*node)[0]);
      openLoopScope();
      checkIfWhileRepeat((*node)[0], expr->getType());
      codegen->emitWhileMiddle((ConstVarSym*)expr);
      traverse(node, &SemanticChecker::check, 1);
      codegen->emitWhileEnd();
      closeLoopScope();
    }
  else if(type == AST_RepeatStmt)
    {
      openLoopScope();
      traverse(node, &SemanticChecker::check, 0,0);
      checkIfWhileRepeat((*node)[1], check((*node)[1])->getType());
      closeLoopScope();
    }
  else if(type == AST_ForStmt)
    {
      openLoopScope();
      checkTypeConflictInForLoop(node, (*node)[0]->sym,
				 check((*node)[1]),
				 check((*node)[2]),
				 check((*node)[3]));
      check((*node)[4]);
      closeLoopScope();
    }
  else if(type == AST_LoopStmt)
    {
      openLoopScope();
      traverse(node, &SemanticChecker::check);
      closeLoopScope();
    }
  else if(type == AST_ExitStmt)
    {
      checkExitInLoop(node);
    }
  else if(type == AST_NewStmt)
    {
      check_newStmt(node);
    }
  else if(type == AST_Expr)
    {
      return check_expr(node);
    }
  else if(type == AST_Expr1) 
    {
      if((*node)[1])
	returnsym = evalAddOpExprType((*node)[1],check((*node)[0]), (*node)[2]);
      else
	returnsym = check((*node)[0]);
    }
  else if(type == AST_Expr2) 
    {
      if((*node)[1])
	returnsym = evalMulOpExprType((*node)[1],check((*node)[0]), (*node)[2]);
      else
	returnsym = check((*node)[0]);
    }
  else if(type == AST_Factor) 
    {
      returnsym = check_factor(node);
      if(GETTYPE((*node)[0]->nodetype) == AST_Designator2)
	check_procCall(node, returnsym, (*node)[1]);
      if(returnsym->isProc())
	{
	  ProcSym* proc= (ProcSym*)returnsym;
	  returnsym = new VarSym(returnsym->getName(),((ProcSym*)returnsym)->getType(),codegen->getScopePointer(), codegen->calcAndSetOffset(((ProcType*)((ProcSym*)returnsym)->getType())->getWidth()));
	  codegen->emitProcedureCall(proc,(VarSym*)returnsym);
	}
    }
  else if(type == AST_Set || type == AST_OptElementList || type == AST_Element)
    {
      returnsym->setType(check((*node)[0])->getType());
    }
  else if(type == AST_Designator2)
    {
      returnsym = check_designator(node);
    }
  else if(type == AST_QualIdent)
    {
      returnsym = check_qualIdent(node);
    }
  else
    {
      traverse(node, &SemanticChecker::check);  
    }
  return returnsym;
}

Symbol* SemanticChecker::evalUnaryOpExprType(ASTNode* node, Symbol* sym1)
{
  ConstVarSym* result = NULL;
  if(GETTYPE(node->nodetype) == AST_TILDE)
    {
      if(!sym1->getType()->isBool())
	ErrorHandler::error1u_Expr(node->fileinfo,sym1->getType(),TILDE,TypeValues::BOOLEAN_TYPE);
    }
 
  if(sym1->isConst() && sym1->getType()->isBool() && ((ConstSym*)sym1)->getValue())	
    result = new ConstSym(getTempSym(),TypeValues::BOOLEAN_TYPE, new Value(!((ConstSym*)sym1)->getValue()->getBoolValue()),NULL,0);

  else
    result = (ConstVarSym*)sym1;
  if(currentProcedure)    //only generate code if inside a procedure/main
    {
      if(!result->isConst())
	{
	  ConstVarSym* resulttemp = new VarSym(getTempSym(),TypeValues::BOOLEAN_TYPE, codegen->getScopePointer(), codegen->calcAndSetOffset(TypeValues::BOOLEAN_TYPE->getWidth()),false);
	  codegen->emitNegation(result, resulttemp);
	  return resulttemp;
	}
    }

  return result;
}
  
Symbol* SemanticChecker::evalRelationExprType(ASTNode* node, Symbol* sym1, Symbol* sym2)
{
  ConstVarSym* result = NULL;
  if(ISLT(node->nodetype) || ISGT(node->nodetype) ||
     ISLTE(node->nodetype) || ISGTE(node->nodetype))
    result = (ConstVarSym*)BinaryExpr::processNumericBoolean(node, sym1, GETOP(node->nodetype), sym2);
  else if(ISEQU(node->nodetype) || ISNEQ(node->nodetype))
    result = (ConstVarSym*)BinaryExpr::processBothBooleanOrNumeric(node, sym1,GETOP(node->nodetype), sym2); 
  
  if(currentProcedure)    //only generate code if inside a procedure/main
    {
      if(!result->isConst())
	codegen->emitBinaryOperation((VarSym*)result, (ConstVarSym*)sym1, GETOP(node->nodetype), (ConstVarSym*)sym2);
    }

  return result;
} 


Symbol* SemanticChecker::evalAddOpExprType(ASTNode* node, Symbol* sym1, ASTNode* nodesym2)
{
  ConstVarSym* result; 
  Symbol* sym2 = NULL;
  if(ISOR(node->nodetype)) 
    {
      codegen->emitOrBegin((ConstVarSym*)sym1);
      sym2 = check(nodesym2);
      result = (ConstVarSym*)BinaryExpr::processBooleanEquivalence(node, sym1,GETOP(node->nodetype), sym2);
      //  if(!sym1->isConst() || !sym2->isConst())
	codegen->emitOrEnd((ConstVarSym*)sym2,(ConstVarSym*)result);

      return result;
    }
  else
    result = (ConstVarSym*)BinaryExpr::processNumericNumeric(node, sym1,GETOP(node->nodetype), (sym2=check(nodesym2)));
  if(currentProcedure)    //only generate code if inside a procedure/main
    {
      if(!result->isConst())
	codegen->emitBinaryOperation((VarSym*)result, (ConstVarSym*)sym1, GETOP(node->nodetype), (ConstVarSym*)sym2);
    }
  return result;
}

Symbol* SemanticChecker::evalMulOpExprType(ASTNode* node, Symbol* sym1, ASTNode* nodesym2)
{ 
  Type* type = TypeValues::ERROR_TYPE;
  Symbol* sym2;
  ConstVarSym* result = NULL;
  if(ISMULTIPLY(node->nodetype))
    result = (ConstVarSym*)BinaryExpr::processNumericNumeric(node, sym1,GETOP(node->nodetype), sym2= check(nodesym2));
  
  else if(ISDIVIDE(node->nodetype) || ISMOD(node->nodetype))  
    result = (ConstVarSym*)BinaryExpr::processIntegerEquivalence(node, sym1,GETOP(node->nodetype), sym2 = check(nodesym2));
  
  else if(ISAND(node->nodetype)) 
    {  
      codegen->emitAndBegin((ConstVarSym*)sym1);
      sym2 = check(nodesym2);
      result = (ConstVarSym*)BinaryExpr::processBooleanEquivalence(node, sym1,GETOP(node->nodetype), sym2);
      // if(!sym1->isConst() || !sym2->isConst())
	codegen->emitAndEnd((ConstVarSym*)sym2,(ConstVarSym*)result);
      return result;
    }
  else if(ISSLASH(node->nodetype))
     result = (ConstVarSym*)BinaryExpr::processNumericNumeric(node,sym1,GETOP(node->nodetype),sym2 = check(nodesym2));

  if(currentProcedure)    //only generate code if inside a procedure/main
    {
      if(!result->isConst())
	codegen->emitBinaryOperation((VarSym*)result, (ConstVarSym*)sym1, GETOP(node->nodetype), (ConstVarSym*)sym2);
    }
  
  return result;
}

void SemanticChecker::traverse(ASTNode* node, Symbol*
			       (SemanticChecker::*traverse_func)
			       (ASTNode*), int startindex, int endindex)
{
  if(endindex == 0)
    endindex = node->size;

  for(int i = startindex; i <= endindex; i++)
    {
      if((*node)[i])
	(this->*traverse_func)((*node)[i]);
    }
}

Symbol* SemanticChecker::check_designator(ASTNode* node)
{
  Symbol* base;
  Type* basetype;
  bool indexed = false;  //to know if the array is being indexed
  base = checkUndeclared((*node)[0], (*node)[0]->getName());
  basetype = base->getType();
  Symbol* expr;
  VarSym* arraybase;
  bool onedim = true;
  if((*node)[1] && GETTYPE((*node)[1]->nodetype) == AST_ExprList)
    check_isArrayVar((*node)[1], base);

  codegen->lastObj->push((int)(VarSym*)base);
  for(int i = 1; i < node->size && (*node)[i]; i++)
    {
       if(GETTYPE((*node)[i]->nodetype) == AST_ID)
	{ 
	  base = check_pointerReference((*node)[i], base, basetype, (*node)[i]->sym);
	  if(!base)
	    return Symbol::ERROR_SYM;

	  if((*node)[i+1] && GETTYPE((*node)[i+1]->nodetype) == AST_ExprList)
	    check_isArrayVar((*node)[i], base);
	  indexed = false;
	  basetype = base->getType();
	  if(!base->isProc())
	    {
	      codegen->lastObj->pop();
	      codegen->lastObj->push((int)(VarSym*)base);
	    }
	}
       else  //constExpr
	{
	  expr = check((*node)[i]);
	  check_arrayIndex((*node)[i], expr);
	  indexed = true;
	  if(GETTYPE((*node)[i-1]->nodetype) == AST_ExprList)
	    check_isArrayVar((*node)[i], new VarSym("", basetype,NULL,0));
	  basetype = basetype->getBaseType();
	  if(onedim)
	    {
	      arraybase = new VarSym(getTempSym(),TypeValues::INTEGER_TYPE,
				     codegen->getScopePointer(),
				     codegen->calcAndSetOffset(TypeValues::INTEGER_TYPE->getWidth()));
	      onedim = false;
	      codegen->emitArray((ConstVarSym*)expr, basetype->getWidth(), (VarSym*)base, arraybase, true);
	    }
	  else
	    {
	      arraybase->setReference(true);
	      codegen->emitArray((ConstVarSym*)expr, basetype->getWidth(), arraybase,arraybase,false);
	    }
	  codegen->lastObj->pop();
	  codegen->lastObj->push((int)arraybase);
	}
    }
  
  if(base->getType()->isArray() && indexed)
    {
      arraybase->setType(basetype);
      VarSym* returnsym = new VarSym(base->getName(), basetype, arraybase->getBase(),arraybase->getOffset());
      returnsym->setReference(true);
     
      return returnsym;
    }
  if(base->getType()->isProc())
    return new ProcSym(base->getName(),
		       ((ProcType*)base->getType())->getReturnType(),
		       ((ProcSym*)base)->getParamListSize(), ((ProcSym*)base)->getParams(),((ProcSym*)base)->isTypeBound());
  
  codegen->lastObj->pop();
  return base;
}

void SemanticChecker::check_mainStmt(ASTNode* node)
{
  inMain = true;
  currentProcedure = insertProcSymbols(node, (*node)[0]->getName(),
				       (*node)[0]->getName(), node);
  procedureHasReturn = false;
  codegen->setScopePointer(codegen->getFramePointer());
  symtable->begin_scope();
  traverse(node, &SemanticChecker::check, 1, 1);
  codegen->emitProcedureHeader("main",currentProcedure->getParamListSize(),currentProcedure->getParams());
  traverse(node, &SemanticChecker::check, 2);
  symtable->end_scope();
  check_returnInFunction((*node)[2], procedureHasReturn, currentProcedure);
  procedureHasReturn = false;
  currentProcedure = NULL;
  codegen->emitProcedureFooter("main", codegen->getScopeOffset()+codegen->getTempStorageWidth());
  codegen->setScopePointer(codegen->getGlobalPointer());
  inMain = false;
}

void SemanticChecker::check_procDecl(ASTNode* node)
{
  ProcSym* procsym;
  procedureHasReturn = false;
  Symbol** parameters = NULL;
  int parameterSize = 0;
  ProcSym* procedure = insertProcSymbols((*node)[1],
					 (*(*node)[1])[0]->getName(),
					 (*node)[5]->getName(),
					 (*node)[5], (*node)[0] ? true : false);
  currentProcedure = procedure;
  codegen->setScopePointer(codegen->getFramePointer());
  symtable->begin_scope();
  Symbol* record = check((*node)[0]);
  procsym = (ProcSym*)check((*node)[2]); //REVISIT
  parameters = procsym->getParams();
  parameterSize = procsym->getParamListSize();
  if(parameterSize > 0)
    parameters = (Symbol**)realloc(parameters, sizeof(Symbol*)*(parameterSize+1));
  else
    parameters = (Symbol**)malloc(sizeof(Symbol*));
  if(!record->isErrorSym())
    { 
      if(!check_duplicateRecordField((*node)[0], ((RecordType*)record->getType()->getBaseType())->getFieldsList(), procedure))
	((RecordType*)record->getType()->getBaseType())->addField(procedure);
      parameters[parameterSize++] = record;
      procedure->setTypeBound(true);
    }
  if(!(*node)[2])
    {
      procedure->setParams(parameters);
      procedure->setParamListSize(parameterSize);
      ((ProcType*)procedure->getType())->setReturnType(TypeValues::NO_TYPE);
    }
  else
    {
      procedure->setParams(parameters);
      procedure->setParamListSize(parameterSize);
      ((ProcType*)procedure->getType())->setReturnType(((ProcType*)procsym->getType())->getReturnType());
    }

  traverse(node, &SemanticChecker::check, 3, 3);
  codegen->emitProcedureHeader(currentProcedure->getName(),currentProcedure->getParamListSize(),currentProcedure->getParams());
  traverse(node, &SemanticChecker::check, 4);
  symtable->end_scope();
  check_returnInFunction((*node)[4], procedureHasReturn, procedure);
  codegen->emitProcedureFooter(currentProcedure->getName(),codegen->getScopeOffset()+codegen->getTempStorageWidth());
  codegen->setScopePointer(codegen->getGlobalPointer());
  currentProcedure = NULL;
  procedureHasReturn = false;
}

void SemanticChecker::check_procCall(ASTNode* node, Symbol* proc, ASTNode* exprlist)				     
{
  if(!proc || !proc->isProc() || proc->isErrorSym())
    return;
  
  Symbol* param;
  Symbol* expr;
  ProcType* procedure = (ProcType*)proc->getType();
  Symbol** params = ((ProcSym*)proc)->getParams();
  int exprlistsize = exprlist ? exprlist->size : 0;
  Symbol* expressions[exprlistsize];
  if(((ProcSym*)proc)->getParamListSize() != (((ProcSym*)proc)->isTypeBound() ? 1+exprlistsize : exprlistsize))
    {
      ErrorHandler::error6n_Call(exprlist ? exprlist->fileinfo : node->fileinfo, exprlistsize, ((ProcSym*)proc)->getParamListSize());
    }

  for(int i=0; i < ((ProcSym*)proc)->getParamListSize() && i < exprlistsize; i++)
    {
      expr = check((*exprlist)[i]);
      expressions[i] = expr;
      if(params[i]->isAddressable())
	{
	   if(!expr->getType()->isSameAs(params[i]->getType()))
	     ErrorHandler::error6v_Call(exprlist->fileinfo,
					expr->getType(),
					params[i],
					params[i]->getType());
	   if(!expr->isAddressable())
	     ErrorHandler::error6c_Call(exprlist->fileinfo,
					expr->getType(),
					params[i],
					params[i]->getType());
	}
      else
	{
	  if(!expr->getType()->isAssignable(params[i]->getType()))
	    ErrorHandler::error6a_Call(exprlist->fileinfo,
				       expr->getType(),
				       params[i], params[i]->getType());
	}
    }
  int j;
  for(j = 0; j < exprlistsize; j++)
    codegen->emitSaveProcedureArgument((ConstVarSym*)expressions[j], (VarSym*)params[j]);
  
  if(((ProcSym*)proc)->isTypeBound())
    codegen->emitSaveProcedureArgument((VarSym*)codegen->lastObj->pop(), (VarSym*)params[j]);
}
    
Symbol* SemanticChecker::check_qualIdent(ASTNode* node)
{
   Symbol* sym;
   
   sym = checkUndeclared((*node)[0], (*node)[0]->getName());
   if(!sym)
     sym = Symbol::ERROR_SYM;
   else if((*node)[1])
     sym = sym->getMember((*node)[1]->getName());
 
  return sym;
}

Symbol* SemanticChecker::check_factor(ASTNode* node)
{
  Symbol* returnsym = node->sym;
  returnsym = check((*node)[0]);

  if((*node)[1] && GETTYPE((*node)[0]->nodetype) == AST_TILDE)
    returnsym = evalUnaryOpExprType((*node)[0],check((*node)[1]));

  return returnsym;
}

Symbol* SemanticChecker::lookupSymtable(char* symbol)
{
  if(symbol)
    return symtable->lookup(symbol);
  
  return NULL;
}

void SemanticChecker::insertIntoSymtable(ASTNode* node, Symbol* symbol)
{
  if(!checkRedeclared(node, symbol->getName()))
   {
     symtable->insert(symbol);
     if(currentProcedure)
       symbol->setGlobal(false);
   }
}

Symbol* SemanticChecker::checkUndeclared(ASTNode* node, char* symbol)
{
  Symbol* returnsym = NULL;
  if(symbol)
    returnsym = lookupSymtable(symbol);
  if(!returnsym)    //symbol is undeclared
    {
      ErrorHandler::semanticError1(CASE1, node->fileinfo, symbol);
      returnsym = new Symbol(symbol,TypeValues::ERROR_TYPE);
      insertIntoSymtable(node, returnsym);
    }
  return returnsym;
}

bool SemanticChecker::checkRedeclared(ASTNode* node, char* symbol)
{
  Symbol* returnsym = NULL;
  if(symbol)
    returnsym = lookupSymtable(symbol);

  if(returnsym && !returnsym->isErrorSym() && (returnsym->isGlobal()&& currentProcedure == NULL || !returnsym->isGlobal() && currentProcedure != NULL))    //symbol is redeclared
    {
      ErrorHandler::semanticError1(CASE2, node->fileinfo, symbol);
      return true;
    }
  return false;
}


void SemanticChecker::insertCVTSymbols(ASTNode* node, int symtype,
				      Symbol* type)
{
  char* id;
  for(int i = 0; i < node->size && (*node)[i] ; i++)
    {
      id = (*node)[i]->getName();

      if(symtype == VARTYPE)
	insertIntoSymtable((*node)[i], new VarSym(id,type->getType(),codegen->getScopePointer(), codegen->calcAndSetOffset(type->getWidth())));
      else if(symtype == TYPETYPE)
	insertIntoSymtable((*node)[i], new TypeSym(id, type->getType()));
      else //const
	insertIntoSymtable((*node)[i], new ConstSym(id, type->getType(), ((ConstSym*)type)->getValue(),codegen->getScopePointer(), 0));
    }
}

ProcSym* SemanticChecker::insertProcSymbols(ASTNode* proc, char*
					    proc1, char* proc2,
					    ASTNode* procend, bool isBounded)
{ 
  ProcSym* procedure = new ProcSym(proc1,new ProcType(TypeValues::NO_TYPE), 0, NULL);
  if(!isBounded)
    insertIntoSymtable(proc, procedure);

  if(strcmp(proc1, proc2) != 0)
    ErrorHandler::semanticError1(CASE10, procend->fileinfo, proc2);
  return procedure;
}
  
Symbol** SemanticChecker::insertIdSymbols(ASTNode* id, Type* type,
					  bool isVar, bool insert)
{ 
  Symbol** params = new Symbol*[id->size];
  Symbol* param;

  for(int i = 0; i < id->size && (*id)[i]; i++)
    {
      param = new VarSym((*id)[i]->getName(),type,
			 codegen->getScopePointer(),
			 codegen->inRecord() ?
			 codegen->getAndSetCurrentRecordOffset(type->getWidth()) : codegen->calcAndSetOffset((isVar && !codegen->inRecord())?Machine::getPointerWidth():type->getWidth()),isVar);
     
      if(isVar && currentProcedure && !inMain)  //if we are processing proc params
	{
	  ((VarSym*)param)->setVarParam(true);
	  ((VarSym*)param)->setReference(true);
	}
      if(insert)
	insertIntoSymtable((*id)[i], param);
      params[i] = param;
    }

  return params;
}

void SemanticChecker::checkAssignment(ASTNode* node, Symbol* left,
				      Symbol* right)
{
  /*checking left side to be a variable*/
  if(!left->isVar())
    ErrorHandler::error2_Assign(node->fileinfo, left);
  /*check for assignability of left and right side*/
  else if(!right->isAssignable(left))
    ErrorHandler::error3_Assign(node->fileinfo, right->getType(), left->getType());
  else
    {
      codegen->emitAssignment((VarSym*)left, (ConstVarSym*)right);
    }
}

void SemanticChecker::checkIfWhileRepeat(ASTNode* node, Type* exprtype)
{
  if(!exprtype->isBool())
    ErrorHandler::error4_Test(node->fileinfo, exprtype);
}


void SemanticChecker::checkTypeConflictInForLoop(ASTNode* node,
						 Symbol* index, Symbol*
						 startExpr, Symbol*
						 endExpr, Symbol*
						 incrementExpr)
{
  index = checkUndeclared(node, index->getName());
  if(!index)
    index = Symbol::ERROR_SYM;
  if(!index->isVar())
    ErrorHandler::error5v_FOR((*node)[0]->fileinfo,index);
  if(!index->getType()->isInt())
    ErrorHandler::error5c_FOR((*node)[0]->fileinfo, index->getType());
  if(!startExpr->getType()->isInt())
    ErrorHandler::error5l_FOR((*node)[1]->fileinfo, startExpr->getType());
  if(!endExpr->getType()->isInt())
    ErrorHandler::error5u_FOR((*node)[2]->fileinfo, endExpr->getType());
  if(!incrementExpr->getType()->isInt())
    ErrorHandler::error5i_FOR((*node)[3]->fileinfo,incrementExpr->getType());
}

Symbol* SemanticChecker::combineParamList(ASTNode* paramlist)
{
  int completeParamSize = 0;
  int index = 0;

  ProcSym* temp;
  Symbol** completeparam = NULL;
  Symbol** otherparamlist = NULL;
  for(int i = 0; i < paramlist->size; i++)
    {
      temp = (ProcSym*)check((*paramlist)[i]);
      if(temp->isErrorSym())
	continue;

      otherparamlist = temp->getParams();
      completeParamSize += temp->getParamListSize();
      if(!completeparam)
	completeparam = (Symbol**)malloc(sizeof(Symbol*)*completeParamSize);
      else
	completeparam = (Symbol**)realloc(completeparam,
					 sizeof(Symbol*)*completeParamSize);
      for(int j = 0;index < completeParamSize; index++, j++)
	completeparam[index] = otherparamlist[j];
    }
 
  return new ProcSym(NULL, TypeValues::NO_TYPE, completeParamSize, completeparam);
}

Symbol* SemanticChecker::combineFieldsList(ASTNode* fieldslist)
{
  PointerStack* fields = new PointerStack(&eql_func, fieldslist->size);
  ProcSym* temp;
  Symbol** otherfieldlist = NULL;
  for(int i = 0; i < fieldslist->size; i++)
    {
      temp = (ProcSym*)check((*fieldslist)[i]);
      if(temp->isErrorSym())
	continue;

      otherfieldlist = temp->getParams();
      for(int j = 0; j < temp->getParamListSize(); j++)
	{
	  if(!check_duplicateRecordField((*fieldslist)[i], fields, otherfieldlist[j]))
	    fields->push((int)otherfieldlist[j]);
	}
    }

 return new TypeSym(NULL,  new RecordType("",fields));
}

void SemanticChecker::check_returnStmt(ASTNode* returnstmt, ProcSym* procedure)
{
  if(procedure)   //within body of procedure
    {
      if(returnstmt->size == 0)   //e.g. RETURN;
	{
	  if(!((ProcType*)procedure->getType())->getReturnType()->isNoType())
	    ErrorHandler::error7a_RETURN(returnstmt->fileinfo);
	  else
	    codegen->emitReturn(NULL);
	}
      else  //e.g. RETURN expr;
	{
	  Symbol* expr = check((*returnstmt)[0]);
	  if(((ProcType*)procedure->getType())->getReturnType()->isNoType())
	    ErrorHandler::error7b_RETURN(returnstmt->fileinfo, expr->getType());
	  else if(!expr->getType()->isAssignable(((ProcType*)procedure->getType())->getReturnType()))
	    ErrorHandler::error7b_RETURN_type(returnstmt->fileinfo,
					      expr->getType(),((ProcType*)procedure->getType())->getReturnType());
	  else
	    codegen->emitReturn((ConstVarSym*)expr);
	}
    }
  procedureHasReturn = true;
}

void SemanticChecker::check_returnInFunction(ASTNode* node, bool
					     hadReturn, ProcSym* proc)
{
  if(!((ProcType*)proc->getType())->getReturnType()->isNoType() && !hadReturn)
    ErrorHandler::error8_RETURN(node->fileinfo);
}


void SemanticChecker::checkKnownAtCompileTime(ASTNode* node, Symbol* constsym,
					      Symbol* constExpr)
{
  if(!constExpr->isConst())
    ErrorHandler::error9_CONST(node->fileinfo, constsym);
}

Symbol* SemanticChecker::check_arrayDecl(ASTNode* node, Symbol*
					 exprlist, Symbol* type)
{
  Type* returntype = TypeValues::ERROR_TYPE;
  
  if(exprlist->isErrorSym())
    returntype = new ArrayType(-1,type->getType());
  else if(exprlist->isConst())
    returntype = new ArrayType(((ConstSym*)exprlist)->getValue() ?
			       ((ConstSym*)exprlist)->getValue()->getIntValue() : -1,type->getType());
  if(!exprlist->getType()->isInt())
    {
      ErrorHandler::error10i_ARRAY(node->fileinfo, exprlist->getType());
      returntype = new ArrayType(-1, type->getType());
    }
  else if(!exprlist->isConst())
    {
      ErrorHandler::error10c_ARRAY(node->fileinfo);
      returntype = new ArrayType(-1, type->getType());
    }

  if(!type->isType())
    {
      /*cancelled 
      ErrorHandler::error10t_ARRAY(node->fileinfo, type);
      */
      returntype = new ArrayType((exprlist->isConst() && ((ConstSym*)exprlist)->getValue()? ((ConstSym*)exprlist)->getValue()->getIntValue() : -1), TypeValues::ERROR_TYPE);
    }
  
  return new TypeSym("", returntype);
}

void SemanticChecker::check_isArrayVar(ASTNode* node, Symbol* sym)
{
  if(!sym->isVar())
    ErrorHandler::error11v_ArrExp(node->fileinfo);
  else if(!sym->getType()->isArray())
    ErrorHandler::error11t_ArrExp(node->fileinfo, sym->getType());
}

void SemanticChecker::check_arrayIndex(ASTNode* node, Symbol* index)
{
  if(!index->getType()->isInt())
    ErrorHandler::error11i_ArrExp(node->fileinfo, index->getType());
}

Symbol* SemanticChecker::check_recordDecl(ASTNode* recordname, ASTNode* fields) 
{
  codegen->openRecord();
  Symbol* returnsym = check(fields);
  codegen->closeRecord();
  if(recordname)
    ((RecordType*)returnsym->getType())->setName(recordname->getName());

  return returnsym;
}

Symbol* SemanticChecker::check_pointerDecl(ASTNode* node, Symbol* basetype) 
{
  if(!basetype->getType()->isRecord())
    {
      ErrorHandler::error14_POINTER(node->fileinfo, basetype->getType());
      return new TypeSym("", TypeValues::ERROR_TYPE);
    }
  return new TypeSym("", new PointerType(basetype->getType()));
}

void SemanticChecker::openLoopScope()
{
  loops++;
}

void SemanticChecker::closeLoopScope()
{
  loops--;
}

void SemanticChecker::checkExitInLoop(ASTNode* node)
{
  if(loops == 0)
    ErrorHandler::error13_EXIT(node->fileinfo);
  else
    codegen->emitExit();
}

Symbol* SemanticChecker::check_pointerReference(ASTNode* node, Symbol*
						base, Type* basetype, Symbol* field)
{
  bool error = false;
  VarSym* returnsym = NULL;

  if(!base->isVar())
    {
      ErrorHandler::error15v_RecExp(node->fileinfo);
      error = true;
    }
  if(!basetype->isPointer() || !basetype->getBaseType()->isRecord())
   {
     ErrorHandler::error15t_RecExp(node->fileinfo, basetype);
     error = true;
   }
  if(!error)
    {
      Symbol* tfield = ((RecordType*)((PointerType*)basetype)->getBaseType())->getField(field->getName());
      if(!tfield)
	ErrorHandler::error15f_RecExp(node->fileinfo, field, basetype);
      if(tfield->isProc())
	return tfield;
      returnsym = new VarSym("",NULL,codegen->getScopePointer(), 0,((VarSym*)tfield)->getValue());
      returnsym->set((VarSym*)tfield);
      returnsym->setOffset(codegen->calcAndSetOffset(TypeValues::POINTER_TYPE->getWidth()));
      returnsym->setReference(true);
      codegen->emitPointerReference((VarSym*)codegen->lastObj->top(), (VarSym*)tfield, returnsym);
    }

  return returnsym;
}

bool SemanticChecker::check_duplicateRecordField(ASTNode* node,
						 PointerStack* fields, 
						 Symbol* field)
{
  if(fields->find((int)field->getName()))
    { 
      ErrorHandler::error16_RECORD(node->fileinfo, field);
      return true;
    }
  return false;
}

Symbol* SemanticChecker::check_optReceiver(ASTNode* node)
{
  ASTNode* fakeNode = new ASTNode("", AST_ParamDecl, 1);
  fakeNode->addChild((*node)[1]);
  fakeNode->fileinfo->filename = node->fileinfo->filename;
  fakeNode->fileinfo->line = node->fileinfo->line;
  TypeSym* type = (TypeSym*)lookupSymtable((*node)[2]->getName());
 
  if(!type->getType()->isPointer() || !type->getType()->getBaseType()->isRecord())
    {
      Symbol* returnsym = new ErrorSym((*node)[1]->getName(), type->getType());
      ErrorHandler::error17_Receiver(node->fileinfo, type->getType());
      insertIntoSymtable(fakeNode, returnsym);
      return returnsym;
    }  
  VarSym* objptr = new VarSym((*node)[1]->getName(),type->getType(),
			      codegen->getScopePointer(),
			      codegen->calcAndSetOffset(type->getType()->getWidth()),true);
  
  insertIntoSymtable(fakeNode, objptr);

return objptr;
}

void SemanticChecker::check_newStmt(ASTNode* node)
{
  Symbol* designator = check((*node)[0]);
  if(!designator->isVar() || !designator->getType()->isPointer())
    ErrorHandler::error18_NEW(node->fileinfo, designator->getType());
  else
    codegen->emitNew((VarSym*)designator);
}

void SemanticChecker::check_typeDecl(ASTNode* node)
{
  check((*node)[0]);
  if((*(*node)[2])[1] && GETTYPE((*(*node)[2])[1]->nodetype) == AST_FieldsList)  //record
    {
      insertCVTSymbols((*node)[1], TYPETYPE, new TypeSym("",new RecordType("",NULL)));
      Symbol* recordtype = check((*node)[2]);
      lookupSymtable((*(*node)[1])[0]->getName())->getType()->set(recordtype->getType());
    }
  else if((*(*node)[2])[1] && GETTYPE((*(*node)[2])[1]->nodetype) == AST_Type)  //array
    {
      insertCVTSymbols((*node)[1], TYPETYPE, new TypeSym("",new ArrayType(0,NULL)));
      Symbol* arraytype = check((*node)[2]);
      lookupSymtable((*(*node)[1])[0]->getName())->getType()->set(arraytype->getType());
    }
  else if(GETTYPE((*(*node)[2])[0]->nodetype) == AST_Type)  //pointer
    {
      insertCVTSymbols((*node)[1], TYPETYPE, new TypeSym("", new PointerType(TypeValues::NIL_TYPE)));
      Symbol* recordtype = check((*(*node)[2])[0]);
      check_pointerDecl((*(*node)[2])[0], recordtype);
      lookupSymtable((*(*node)[1])[0]->getName())->getType()->set(new PointerType(recordtype->getType()));
    }
  else
    insertCVTSymbols((*node)[1], TYPETYPE, check((*node)[2]));
  
}

char* SemanticChecker::getTempSym()
{
  static int counter = 0;
  char* temp = new char[10];
  sprintf(temp, "$t%d", counter++);
  return temp;
}

void SemanticChecker::process_write(ASTNode* outputitems)
{
  int i, non_const_args = 0;
  int stringsize = 1;  //for \0
  char* stringlabel;
  Symbol* expr;
 
  for(i = 0; i < outputitems->size && (*outputitems)[i]; i++)
    {
      if((*outputitems)[i]->sym->isConst())
	stringsize += strlen((*outputitems)[i]->sym->getName());
      else 
	{
	  if((*outputitems)[i]->sym->getType()->isPointer())
	    stringsize += 3;
	  else
	    stringsize += 2;  //%something for every variable or const 
	  non_const_args++;
	}
    }
  char string[stringsize];     
  VarSym* exprlist[non_const_args];
  string[0] = '\0';

  for(i = 0, non_const_args = 0; i < outputitems->size && (*outputitems)[i]; i++)
    {
      if(GETTYPE((*outputitems)[i]->nodetype) == AST_NL)
	strcat(string, "\\n");
      else 
	{
	  expr = check((*outputitems)[i]);
	  if(expr->isConst())
	    {
	      char buff[11];
	      if(expr->getType()->isBool())
		strcat(string, Value::boolToString(((ConstVarSym*)expr)->getValue()->getBoolValue()));
	      else if(expr->getType()->isInt())
		{
		  sprintf(buff, "%d", ((ConstVarSym*)expr)->getValue()->getIntValue());
		  strcat(string, buff);
		}
	      else if(expr->getType()->isReal())
		{
		  sprintf(buff, "%f", ((ConstVarSym*)expr)->getValue()->getRealValue());
		  strcat(string, buff);
		}
	       else if(expr->getType()->isChar())
		{
		  sprintf(buff, "%c", ((ConstVarSym*)expr)->getValue()->getCharValue());
		  strcat(string, buff);
		}
	      else if(expr->getType()->isNil())
		strcat(string, "NIL");
	      else
		strcat(string, ((ConstVarSym*)expr)->getValue()->getStringValue());
	    }
	  else 
	    {
	      if(expr->getType()->isInt())
		strcat(string, "%d");
	      else if(expr->getType()->isPointer())
		strcat(string, "%#x");
	      else if(expr->getType()->isBool())
		strcat(string, "%s");
	      else if(expr->getType()->isChar())
		strcat(string, "%c");
	      exprlist[non_const_args++] = (VarSym*)expr;
	    }
	}
    }
  codegen->emitReadOnlyDataSection();
  stringlabel = codegen->emitSaveString(string);
  codegen->emitTextSection();
  codegen->emitSaveStringArgument(stringlabel);
  for(i = 0; i < non_const_args; i++)
    {
      codegen->emitSaveProcedureArgument(exprlist[i], NULL,true);
    }
   
  codegen->emitProcedureCall(new ProcSym("printf", TypeValues::NO_TYPE, i, NULL),NULL);
}


Symbol* SemanticChecker::check_expr(ASTNode* node)
{
  Symbol* returnsym;
  ConstVarSym* expr1,*expr2, *expr11, *expr21;
  expr1 = (ConstVarSym*)check((*node)[1]);
  expr2 = (ConstVarSym*)check((*node)[4]);
  if((*node)[0] && GETOP((*node)[0]->nodetype) == MINUS)
    {
      if(expr1->isConst())
	expr1 = new ConstSym(getTempSym(), expr1->getType(), new
			     Value(-expr1->getValue()->getIntValue()), 
			     codegen->getScopePointer(), codegen->calcAndSetOffset(expr1->getType()->getWidth()));
      else
	{
	  expr11 = new VarSym(getTempSym(), expr1->getType(), 
			     codegen->getScopePointer(), codegen->calcAndSetOffset(expr1->getType()->getWidth()));
	  codegen->emitNegation(expr1, expr11);
	  expr1 = expr11;
	}    
    }
  if((*node)[3] && GETOP((*node)[3]->nodetype) == MINUS)
    {
      if(expr2->isConst())
	expr2 = new ConstSym(getTempSym(), expr2->getType(), new
			     Value(-expr2->getValue()->getIntValue()), 
			     codegen->getScopePointer(), codegen->calcAndSetOffset(expr2->getType()->getWidth()));
      else
	{
	  expr21 = new VarSym(getTempSym(), expr2->getType(), 
			     codegen->getScopePointer(), codegen->calcAndSetOffset(expr2->getType()->getWidth()));
	  codegen->emitNegation(expr2, expr21);
	  expr2 = expr21;
	}   
    }
  if((*node)[2])
    returnsym = evalRelationExprType((*node)[2], expr1, expr2);
  else
    returnsym = expr1;

  return returnsym;
}


void SemanticChecker::process_read(ASTNode* designator)
{
  Symbol* des = check(designator);
  char* stringlabel;
  char string[3];

  if(!des->isVar())
    return;
  if(des->getType()->isInt())
    strcpy(string,"%d");
  
  codegen->emitReadOnlyDataSection();
  stringlabel = codegen->emitSaveString(string);
  codegen->emitTextSection();
  codegen->emitSaveStringArgument(stringlabel);
  if(((VarSym*)des)->isReference())
    {
      codegen->emitSaveReferenceArgument((ConstVarSym*)des);
    }
  else
    codegen->emitSaveReferenceArgument((ConstVarSym*)des);
  codegen->emitProcedureCall(new ProcSym("scanf", TypeValues::NO_TYPE, 1, NULL),NULL);
}
