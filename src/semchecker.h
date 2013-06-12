#ifndef _SEMCHECKER_H_
#define _SEMCHECKER_H_
#include "ASTnode.h"
#include "symboltable.h"
#include "stack.h"
#include "codegen.h"

/*masks*/
#define UNCHANGED     0x0000
#define ALL_BUT_TYPE  0xFF80

#define PREDECLARED_SIZE 20

#define MAX_CHILDREN 7

class SemanticChecker
{
  friend class SymbolTable;
private:
  ASTNode* ast;
  SymbolTable* symtable;
  SymbolTable* predeclared;
  ProcSym* currentProcedure;
  bool procedureHasReturn;
  bool inMain;
  int loops;
  CodeGenerator* codegen;
  Symbol* check(ASTNode* root);

  /*functions for handling semantic type errors*/
  Symbol* checkUndeclared(ASTNode* node, char* symbol);
  bool checkRedeclared(ASTNode* node, char* symbol);
  void checkAssignment(ASTNode* node, Symbol* left, Symbol* right);
  void checkIfWhileRepeat(ASTNode* node, Type* exprtype);
  void checkTypeConflictInForLoop(ASTNode* node,Symbol* index, Symbol*
				  startExpr, Symbol*endExpr, Symbol*
				  incrementExpr);
  void checkKnownAtCompileTime(ASTNode* node, Symbol* constsym, Symbol* constExpr);
  void check_isArrayVar(ASTNode* node, Symbol* sym);
  void check_arrayIndex(ASTNode* node, Symbol* index);
  void checkExitInLoop(ASTNode* node);
  bool check_duplicateRecordField(ASTNode* node, PointerStack* fields,
				  Symbol* field);
  Symbol* check_optReceiver(ASTNode* node);

  /*functions for handling type checking*/
  Symbol* evalUnaryOpExprType(ASTNode* node, Symbol* sym1);
  Symbol* evalRelationExprType(ASTNode* node, Symbol* sym1, Symbol* sym2);
  Symbol* evalAddOpExprType(ASTNode* node, Symbol* sym1, ASTNode* sym2);
  Symbol* evalMulOpExprType(ASTNode* node, Symbol* sym1, ASTNode* sym2);

  /*functions for traversal of AST */
  void traverse(ASTNode* node, Symbol*
		(SemanticChecker::*traverse_func) (ASTNode*), int
		startindex = 0, int endindex = 0);
  
  /*functions for handling scoping and declaration semantic errors*/
  Symbol* check_designator(ASTNode* node);
  Symbol* check_qualIdent(ASTNode* node);
  Symbol* check_factor(ASTNode* node);
  void check_procDecl(ASTNode* node);
  void check_procCall(ASTNode* node, Symbol* proc, ASTNode* exprlist);
  void check_mainStmt(ASTNode* node);
  void check_returnStmt(ASTNode* returnstmt, ProcSym* procedure);
  void check_returnInFunction(ASTNode* node, bool hadReturn, ProcSym* proc);
  Symbol* check_arrayDecl(ASTNode* node, Symbol* exprlist, Symbol* type);
  Symbol* check_recordDecl(ASTNode* recordname, ASTNode* fields) ;
  Symbol* check_pointerDecl(ASTNode* node, Symbol* basetype); 
  Symbol* combineParamList(ASTNode* paramlist);
  Symbol* combineFieldsList(ASTNode* fieldlists);
  void openLoopScope();
  void closeLoopScope();
  Symbol* check_pointerReference(ASTNode* node, Symbol* base, Type*
				 basetype, Symbol* field);
  void check_newStmt(ASTNode* node);
  void check_typeDecl(ASTNode* node);
  Symbol* check_expr(ASTNode* node);
  /*symbol table manipulation functions*/
  Symbol* lookupSymtable(char* symbol);
  void insertIntoSymtable(ASTNode* node, Symbol* symbol);
  void insertCVTSymbols(ASTNode* node, int symtype, Symbol* type);
  ProcSym* insertProcSymbols(ASTNode* proc, char* proc1, char* proc2, ASTNode* procend , bool isBounded = false);
  Symbol** insertIdSymbols(ASTNode* id, Type* type, bool isVar, bool
			   insert = true);
  /*codegen related functions*/
  void process_write(ASTNode* outputitems);
  void process_read(ASTNode* designator);
public:
  SemanticChecker(SymbolTable* symtable_, ASTNode* ast_, CodeGenerator* codegen_);
  bool check();
  static char* getTempSym();
  void printSymbolTable() {symtable->printTable();}
};

#endif
