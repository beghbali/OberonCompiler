#include "binaryexpr.h"
#include "errorhandler.h"
#include "semchecker.h"
#include "codegen.h"

extern CodeGenerator* codegen;

Symbol* BinaryExpr::processNumericNumeric(ASTNode* node, Symbol* sym1,
					int op, Symbol* sym2)
{
  Type* type = TypeValues::REAL_TYPE;
  if(!sym1->getType()->isNumeric() || !sym2->getType()->isNumeric())
    {
      ErrorHandler::error1n_Expr(node->fileinfo, !sym1->getType()->isNumeric() ?
				 sym1->getType() : sym2->getType(), op);

      type = REAL_OR_NULL(node);
    }
  else if(sym1->getType()->isInt() && sym2->getType()->isInt())
    {
      if(!ISSLASH(node->nodetype))
	type = TypeValues::INTEGER_TYPE;
    }

  if(sym1->isConst() && sym2->isConst())
    return new ConstSym(SemanticChecker::getTempSym(), type, evaluate((ConstSym*)sym1, op,(ConstSym*)sym2),codegen->getScopePointer(), 0);
  return new VarSym(SemanticChecker::getTempSym(), type, codegen->getScopePointer(), codegen->calcAndSetOffset(type->getWidth()),false);
}
 
Symbol* BinaryExpr::processBooleanEquivalence(ASTNode* node, Symbol*
					    sym1, int op, Symbol* sym2)
{
  if(!sym1->getType()->isBool() || !sym2->getType()->isBool())
      ErrorHandler::error1w_Expr(node->fileinfo,!sym1->getType()->isBool() ?
				 sym1->getType() : sym2->getType(), op,
				 TypeValues::BOOLEAN_TYPE);

  if(sym1->isConst() && sym2->isConst())
    return new ConstSym(SemanticChecker::getTempSym(),TypeValues::BOOLEAN_TYPE, evaluate((ConstSym*)sym1, op, (ConstSym*)sym2),codegen->getScopePointer(), 0);
  return new VarSym(SemanticChecker::getTempSym(),TypeValues::BOOLEAN_TYPE, codegen->getScopePointer(), codegen->calcAndSetOffset(TypeValues::BOOLEAN_TYPE->getWidth()),false);
}


Symbol* BinaryExpr::processIntegerEquivalence(ASTNode* node, Symbol*
					    sym1, int op, Symbol* sym2)
{
  if(!sym1->getType()->isInt() || !sym2->getType()->isInt())
      ErrorHandler::error1w_Expr(node->fileinfo,!sym1->getType()->isInt() ?
				 sym1->getType() : sym2->getType(), op,
				 TypeValues::INTEGER_TYPE);

  if(sym1->isConst() && sym2->isConst())
    return new ConstSym(SemanticChecker::getTempSym(),TypeValues::INTEGER_TYPE, evaluate((ConstSym*)sym1, op, (ConstSym*)sym2),codegen->getScopePointer(), 0);
  return new VarSym(SemanticChecker::getTempSym(),TypeValues::INTEGER_TYPE, codegen->getScopePointer(), codegen->calcAndSetOffset(TypeValues::INTEGER_TYPE->getWidth()),false);
}

Symbol* BinaryExpr::processNumericBoolean(ASTNode* node, Symbol* sym1,
					int op, Symbol* sym2)
{
  if(!sym1->getType()->isNumeric() || !sym2->getType()->isNumeric())
      ErrorHandler::error1n_Expr(node->fileinfo,!sym1->getType()->isNumeric() ?
				 sym1->getType() : sym2->getType(), op);

  if(sym1->isConst() && sym2->isConst())
    return new ConstSym(SemanticChecker::getTempSym(),TypeValues::BOOLEAN_TYPE, evaluate((ConstSym*)sym1, op, (ConstSym*)sym2),codegen->getScopePointer(), 0);
  return new VarSym(SemanticChecker::getTempSym(),TypeValues::BOOLEAN_TYPE, codegen->getScopePointer(), codegen->calcAndSetOffset(TypeValues::BOOLEAN_TYPE->getWidth()),false);
}

Symbol* BinaryExpr::processBothBooleanOrNumeric(ASTNode* node, Symbol* sym1, int
				     op, Symbol* sym2)
{
  if(sym1->getType()->isPointer() || sym2->getType()->isPointer())
    {
      if(!(sym1->getType()->isSameAs(sym2->getType())))
	ErrorHandler::error19_Expr(node->fileinfo,op,sym1->getType(),sym2->getType());
    }
  else if(!((sym1->getType()->isBool() && sym2->getType()->isBool()) 
       || (sym1->getType()->isNumeric() && sym2->getType()->isNumeric())))
    ErrorHandler::error1b_Expr(node->fileinfo,sym1->getType(),op,sym2->getType());
  
  if(sym1->isConst() && sym2->isConst())
    return new ConstSym(SemanticChecker::getTempSym(),TypeValues::BOOLEAN_TYPE, evaluate((ConstSym*)sym1, op, (ConstSym*)sym2),codegen->getScopePointer(), 0);
  
 return new VarSym(SemanticChecker::getTempSym(),TypeValues::BOOLEAN_TYPE, codegen->getScopePointer(), codegen->calcAndSetOffset(TypeValues::BOOLEAN_TYPE->getWidth()),false);
}

Value* BinaryExpr::evaluate(ConstSym* first, int op, ConstSym* second)
{
  if(first->getType()->isReal())
    { 
      if(second->getType()->isReal())
	return new Value(evaluate(first->getValue()->getRealValue(),op, second->getValue()->getRealValue()));
      else if(second->getType()->isInt())
	return new Value(evaluate(first->getValue()->getRealValue(),op, second->getValue()->getIntValue()));
    }
  else if(first->getType()->isInt())
    {
      if(second->getType()->isReal())
	return new Value(evaluate(first->getValue()->getIntValue(),op, second->getValue()->getRealValue()));
      else if(second->getType()->isInt())
	return new Value(evaluate(first->getValue()->getIntValue(),op, second->getValue()->getIntValue()));
    }
  else if(first->getType()->isBool())
    {
      if(second->getType()->isBool())
	return new Value(evaluate(first->getValue()->getBoolValue(),op, second->getValue()->getBoolValue()));
    }
  return NULL;
}

int BinaryExpr::evaluate(int a, int op, int b)
{
  switch(op)
    {
    case MULTIPLY: return a*b;
      break;
    case PLUS: return a+b;
      break;
    case MINUS: return a-b;
      break;
    case SLASH: return a/b;
      break;
    case DIVIDE: return (int)(a/b);
      break;
    case MOD: return a%b;
      break;
    case LT: return a < b;
      break;
    case GT: return a > b;
      break;
    case LTE: return a <= b;
      break;
    case GTE: return a >= b;
      break;
    case EQU: return a==b;
      break;
    case NEQ: return a != b;
      break;
    default:
      return -1;
    }
}

double BinaryExpr::evaluate(double a, int op, double b)
{
  switch(op)
    {
    case MULTIPLY: return a*b;
      break;
    case PLUS: return a+b;
      break;
    case MINUS: return a-b;
      break;
    case SLASH: return a/b;
      break;
    case LT: return a < b;
      break;
    case GT: return a > b;
      break;
    case LTE: return a <= b;
      break;
    case GTE: return a >= b;
      break;
    case EQU: return a==b;
      break;
    case NEQ: return a != b;
      break;
    default:
      return -1.0;
    }
}

double BinaryExpr::evaluate(int a, int op, double b)
{
  return evaluate((double)a, op, b);
}

double BinaryExpr::evaluate(double a, int op, int b)
{
  return evaluate(a, op, (double)b);
}

bool BinaryExpr::evaluate(bool a, int op, bool b)
{
  switch(op)
    {
    case OR: return a || b;
      break;
    case AND: return a && b;
      break;
    case EQU: return a == b;
      break;
    case NEQ: return a != b;
      break;
    default:
      return false;
    }
}
