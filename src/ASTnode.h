#ifndef _ASTNODE_H_
#define _ASTNODE_H_

#include <iostream>
#include "inputStruct.h"
#include "symbol.h"

#define READONLY    0x80000000  //(0x0001 << 31)
#define EXPORTABLE  0x40000000  //(0x0001 << 30)

#define ISREADONLY(type) ((type & READONLY))
#define ISEXPORTABLE(type) ((type & EXPORTABLE))

#define VARTYPE   1
#define CONSTTYPE 2
#define TYPETYPE  3
#define PROCTYPE  4
#define MODULETYPE 5

/*multiplex subtypes*/
#define MULTIPLY    (0x0001 << 7)
#define SLASH       (0x0002 << 7)
#define DIVIDE      (0x0003 << 7)
#define MOD         (0x0004 << 7)
#define AND         (0x0005 << 7)

#define PLUS        (0x0006 << 7)
#define MINUS       (0x0007 << 7)
#define OR          (0x0008 << 7)

#define EQU         (0x0009 << 7)
#define NEQ         (0x000A << 7)
#define LT          (0x000B << 7)
#define GT          (0x000C << 7)
#define LTE         (0x000D << 7)
#define GTE         (0x000E << 7)
#define IN          (0x000F << 7)
#define IS          (0x0010 << 7)

#define INTEGER     (0x0011 << 7)
#define REAL        (0x0012 << 7)
#define BOOLEAN     (0x0013 << 7)
#define CHAR        (0x0014 << 7)

#define TILDE       (0x0015 << 7)
        
#define TYPE_ERROR  0x00000005

#define SUBTYPE  ~0xFFFFF07F
#define TYPE     ~0xFFFFFF80 

#define ISMULTIPLY(type) ((type & SUBTYPE) == MULTIPLY)
#define ISSLASH(type) ((type & SUBTYPE) == SLASH)
#define ISDIVIDE(type) ((type & SUBTYPE) == DIVIDE)
#define ISMOD(type) ((type & SUBTYPE) == MOD)
#define ISAND(type) ((type & SUBTYPE) == AND)

#define ISPLUS(type) ((type & SUBTYPE) == PLUS)
#define ISMINUS(type) ((type & SUBTYPE) == MINUS)
#define ISOR(type) ((type & SUBTYPE) == OR)

#define ISADDOP(type) (ISPLUS || ISMINUS || ISOR)
#define ISMULOP(type) (ISSLASH || ISDIVIDE || ISMOD || ISAND)
#define ISRELATION(type) (ISLT || ISGT || ISLTE || ISGTE || ISEQU || ISNEQ)

#define ISEQU(type) ((type & SUBTYPE) == EQU)
#define ISNEQ(type) ((type & SUBTYPE) == NEQ)
#define ISLT(type) ((type & SUBTYPE) == LT)
#define ISGT(type) ((type & SUBTYPE) == GT)
#define ISLTE(type) ((type & SUBTYPE) == LTE)
#define ISGTE(type) ((type & SUBTYPE) == GTE)
#define ISIN(type) ((type & SUBTYPE) == IN)
#define ISIS(type) ((type & SUBTYPE) == IS)

#define ISINTEGER(type) ((type & SUBTYPE) == INTEGER)
#define ISREAL(type) ((type & SUBTYPE) == REAL)
#define ISBOOLEAN(type) ((type & SUBTYPE) == BOOLEAN)
#define ISCHAR(type) ((type & SUBTYPE) == CHAR)

#define SET_TO_REAL(type) (type |= REAL)
#define SET_TO_INTEGER(type) (type |= INTEGER)
#define SET_TO_BOOLEAN(type) (type |= BOOLEAN)
#define SET_TO_CHAR(type) (type |= CHAR)

#define GETTYPE(type) (type & TYPE) 
#define GETOP(type) (type & SUBTYPE)

#define SET(type, arg) (type |= arg) 
#define EQUALS(a,b) ((a) == (b))

class ASTNode
{ 
private:
  int next;
   ASTNode** children;
public:
  Symbol* sym;
  int nodetype;
  inputStruct* fileinfo;
  int size;
  ~ASTNode();
  ASTNode::ASTNode(Symbol* sym_, int nodetype_);
  ASTNode(char* name_, int type_, int size_);
  void init(char* name_, int nodetype_, int size_);
  ASTNode* operator[](int i);
  inline ASTNode* get(int i);
  void addChild(char* name_, int type_);
  void addChild(ASTNode* new_child);
  void addChildrenOf(ASTNode* node);
  char* getName() { return sym->getName(); }
  Type* getType() { return sym->getType(); }
  int getSize() { return size; }
  void setName(char* name_) { sym->setName(name_); }
  void setType(Type* type_) { sym->setType(type_); }
};


#endif
