#ifndef _BOOLEANEXPR_H_
#define _BOOLEANEXPR_H_
#include "ASTnode.h"
#include "type.h"

#define REAL_OR_NULL(node) (ISSLASH(node->nodetype) ? TypeValues::REAL_TYPE : TypeValues::ERROR_TYPE);

class BinaryExpr
{
public:
  static Symbol* processNumericNumeric(ASTNode* node, Symbol* sym1, int op, Symbol* sym2);
  static Symbol* processBooleanEquivalence(ASTNode* node, Symbol* sym1, int op, Symbol* sym2);
  static Symbol* processIntegerEquivalence(ASTNode* node, Symbol* sym1, int op, Symbol* sym2);
  static Symbol* processNumericBoolean(ASTNode* node, Symbol* sym1, int op, Symbol* sym2);
  static Symbol* processBothNumeric(ASTNode* node, Symbol* sym1, int op, Symbol* sym2);
  static Symbol* processBothBooleanOrNumeric(ASTNode* node, Symbol* sym1, int op, Symbol* sym2);
  static Value* evaluate(ConstSym* first, int op, ConstSym* second);
  static int evaluate(int a, int op, int b);
  static double evaluate(double a, int op, double b);
  static double evaluate(int a, int op, double b);
  static double evaluate(double a, int op, int b);
  static bool evaluate(bool a, int op, bool b);
};

#endif

