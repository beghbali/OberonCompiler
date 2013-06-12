#ifndef _SYMBOL_H_
#define _SYMBOL_H_
#include "stack.h"
#include "value.h"
#include "type.h" 
#include "architecture.h"

enum SYMTYPE_
{
  notype             = 0x00,
  AST_ID             = 0x01,
  AST_IdentDef       = 0x02,
  AST_QualIdent      = 0x03,
  AST_OptQualIdent   = 0x04,
  AST_IdentList      = 0x05,
  AST_Designator2    = 0x06, 
  AST_Designator     = 0x07,
  AST_MulOp          = 0x08,
  AST_AddOp          = 0x09, 
  AST_Relation       = 0x0A,
  AST_Element        = 0x0B,
  AST_ElementList    = 0x0C,
  AST_OptElementList = 0x0D,
  AST_Set            = 0x0E,
  AST_Factor         = 0x0F,
  AST_TILDE          = 0x10,
  AST_NIL            = 0x11,
  AST_FALSE          = 0x12,
  AST_TRUE           = 0x13,
  AST_STR_LITERAL    = 0x14,
  AST_CHAR_LITERAL   = 0x15,
  AST_REAL_LITERAL   = 0x16,
  AST_INT_LITERAL    = 0x17,
  AST_OptSign        = 0x18,
  AST_Exprk          = 0x19,
  AST_NL             = 0x1A,
  AST_Expr3          = 0x1B,
  AST_Expr2          = 0x1C,
  AST_Expr1          = 0x1D,
  AST_Expr           = 0x1E,
  AST_ExprList2      = 0x1F,
  AST_ExprList      = 0x20,
  AST_ConstExpr      = 0x21,
  AST_Guard          = 0x22,
  AST_ReturnStmt     = 0x23,
  AST_ExitStmt       = 0x24,
  AST_GuardList      = 0x25,
  AST_WithStmt       = 0x26,
  AST_LoopStmt       = 0x27,
  AST_OptBy          = 0x28,
  AST_ForStmt        = 0x29,
  AST_RepeatStmt     = 0x2A,
  AST_WhileStmt      = 0x2B,
  AST_CaseLabels     = 0x2C,
  AST_CaseLabelsList = 0x2D,
  AST_Case           = 0x2E,
  AST_CaseList       = 0x2F,
  AST_CaseStmt       = 0x30,
  AST_OptElse        = 0x31,
  AST_OptElsifs      = 0x32,
  AST_IfStmt         = 0x33,
  AST_OptExprList    = 0x34,
  AST_ProcCall       = 0x35,
  AST_AssignStmt     = 0x36,
  AST_OutputItems    = 0x37,
  AST_OutputStmt     = 0x38,
  AST_InputStmt      = 0x39,
  AST_Stmt           = 0x3A,
  AST_StmtList       = 0x3B,
  AST_FieldList      = 0x3C,
  AST_FieldsList     = 0x3D,
  AST_BasicType      = 0x3E,
  AST_Type           = 0x3F,
  AST_OptReceiver    = 0x40,
  AST_OptReturnType  = 0x41,
  AST_IdList         = 0x42,
  AST_ParamDecl      = 0x43,
  AST_ParamList      = 0x44,
  AST_OptParamList   = 0x45,
  AST_FormalParams   = 0x46,
  AST_OptFormalParams= 0x47,
  AST_FwdProcDecl    = 0x48,
  AST_OptStmts       = 0x49,
  AST_ProcDecl       = 0x4A,
  AST_VarDecl        = 0x4B,
  AST_VarDeclList2   = 0x4C,
  AST_VarDeclList    = 0x4D,
  AST_TypeDecl       = 0x4E,
  AST_TypeDeclList   = 0x4F,
  AST_ConstDecl      = 0x50,
  AST_ConstDeclList  = 0x51,
  AST_CTDecl         = 0x52,
  AST_CVTDecl        = 0x53,
  AST_ProcDeclList2  = 0x54,
  AST_ProcDeclList   = 0x55,
  AST_CTDeclList     = 0x56,
  AST_CVTDeclList    = 0x57,
  AST_DeclSeq        = 0x58,
  AST_ImportList     = 0x59,
  AST_ImportDecl     = 0x5A,
  AST_OptImportDecl  = 0x5B,
  AST_Module         = 0x5C,
  AST_ModuleList     = 0x5D,
  AST_DeclarationList= 0x5E,
  AST_DeclarationsSection = 0x5F,
  AST_MainStmtsSection    = 0x60,
  AST_Program        = 0x61, 
  AST_OptVar         = 0x62,
  AST_NewStmt        = 0x63
};

typedef enum SYMTYPE_ SYMTYPE;

class ErrorSym;

class Symbol
{
private:
  char* name;
  Type* type;
  bool isglobal;
public:
  static ErrorSym* ERROR_SYM;
  Symbol(char* name_, Type* type_): name(name_), type(type_), isglobal(true)
    {
      if(!type)
	type = TypeValues::ERROR_TYPE; 
    } 
  char* getName() { return name; }
  Type* getType() { return type; }
  void setName(char* name_){ name = name_; }
  void setType(Type* type_){ type = type_; }
  void setGlobal(bool global) { isglobal = global; }
  bool isGlobal() { return isglobal; }
  addr_type getWidth() { return type->getWidth(); }
  addr_type getAlignment() { return type->getBaseType()->getWidth();} //XXX
  virtual bool isErrorSym() { return false; }
  virtual Symbol* getMember(char* membername) { return NULL; }
  virtual bool isMember(char* membername) { return false; }
  virtual bool isExportable() { return false;}
  virtual bool isVar() { return false; }
  virtual bool isConst() { return false; }
  virtual bool isType() { return false; }
  virtual bool isProc() { return false; }
  virtual bool isModule() { return false; }
  virtual bool isConstVar() { return false; }
  virtual bool isAddressable() { return false; }
  virtual bool isAssignable(Symbol* other) 
    { 
      return type->isAssignable(other->type);
    }
  virtual const char* toString() { return "Symbol";}
};


class ErrorSym : public Symbol
{
 public:
  ErrorSym(char* name_, Type* type_): Symbol(name_,type_){}
  virtual bool isErrorSym() { return true; }
  virtual bool isExportable() { return true;}
  virtual bool isVar() { return true; }
  virtual bool isConst() { return true; }
  virtual bool isType() { return true; }
  virtual bool isProc() { return true; }
  virtual bool isModule() { return true; }
  virtual bool isAddressable() { return true; }
};

class ConstVarSym : public Symbol
{
 protected:
  Value* value;
  addr_type offset;
  Register* base;
 public:
  ConstVarSym(char* name_, Type* type_, Register* base_, int offset_): Symbol(name_,type_),base(base_),offset(offset_){ value = new Value(-1);}
  ConstVarSym(char* name_, Type* type_, Value* value_, Register* base_, int offset_): Symbol(name_,type_),base(base_),offset(offset_){value = value_;}
  const char* toString() { return "ConstVarSym";}
  bool isConstVar() { return true; }
  Value* getValue() { return value; }
  Register* getBase() { return base; }
  void setBase(Register* base_) { base = base_; }
  addr_type getOffset() { return offset; }
  void setOffset(addr_type offset_) { offset = offset_; }
  void setValue(Value* value_) 
    {
      if(value_)
	{ 
	  delete value;
	  value = value_;
	} 
    }
};

class VarSym : public ConstVarSym
{
 private: 
  bool addressable;
  bool isvarparam;
  bool isreference;
 public:
  VarSym(char* name_, Type* type_, Register* base_, int offset_,bool addressable_ = true): ConstVarSym(name_,type_,base_,offset_), addressable(addressable_),isvarparam(false),isreference(false){}
  VarSym(char* name_, Type* type_, Register* base_, int offset_,Value* value_): ConstVarSym(name_,type_,value_,base_,offset_), addressable(false),isvarparam(false),isreference(false){}
  void set(VarSym* other)
    {
      this->addressable = other->isAddressable();
      this->isvarparam = other->isVarParam();
      this->setName(other->getName());
      this->setType(other->getType());
    }
  bool isVar() { return true; }
  bool isAddressable() { return addressable; }
  bool isVarParam() { return isvarparam; }
  bool setVarParam(bool value) { isvarparam = value; }
  bool isReference() { return isreference;}
  void setReference(bool value) { isreference = value; }
  const char* toString() { return "VarSym";}
};

class TempVarSym : public VarSym
{
 private: 
  bool addressable;
 public:
  TempVarSym(char* name_, Type* type_, Register* base_, int offset_,bool addressable_ = true): VarSym(name_,type_, base_,offset_,addressable_){}
  TempVarSym(char* name_, Type* type_, Register* base_, int offset_,Value* value_): VarSym(name_,type_,base_,offset_,value_){}

  const char* toString() { return "TempVarSym";}
};

class ConstSym : public ConstVarSym
{
public:
  ConstSym(char* name_, Type* type_,Register* base_, int offset_):ConstVarSym(name_, type_, base_, offset_){}
  ConstSym(char* name_, Type* type_, Value* value_, Register* base_, int offset_): ConstVarSym(name_,type_,value_,base_, offset_){}
  bool isConst() { return true; }
  const char* toString() { return "ConstSym";}
};

class TypeSym : public Symbol
{
public:
  TypeSym(char* name_, Type* type_):Symbol(name_, type_){}
  bool isType() { return true; }
  const char* toString() { return "TypeSym";}
};

class FieldSym : public Symbol
{
 private:
  PointerStack* field_list; 
 public:
  FieldSym(char* name_, Type* type_, PointerStack* field_list_): Symbol(name_, type_), field_list(field_list_){}
  bool isMember(char* membername) { return field_list->find((int)membername) ? true : false; }
  Symbol* getMember(char* membername) { (Symbol*)field_list->find((int)membername); }
};

class ModuleSym : public FieldSym
{
 public:
  ModuleSym(char* name_, Type* type_, PointerStack* export_list_): FieldSym(name_, type_,export_list_){}
  bool isExported(char* membername){ return isMember(membername);}    
  Symbol* getExportSym(char* membername){ return getMember(membername); }
  bool isModule() { return true; }
  const char* toString() { return "ModuleSym";}
};
     
class ProcSym : public Symbol
{
 private:
  Symbol** params;
  int sizeofparams;
  bool typebound;
 public:
  ProcSym(char* name_, Type* type_, int sizeofparams_, Symbol** params_, bool typebound_ = false) : Symbol(name_,type_) , params(params_), sizeofparams(sizeofparams_), typebound(typebound_){}
  bool isProc() { return true; }
  const char* toString() { return "ProcSym";}
  Symbol** getParams() { return params; }
  void setParams(Symbol** params_) { params = params_; }
  int getParamListSize() { return sizeofparams; }
  void setParamListSize(int size_) { sizeofparams = size_; }
  void printParamList()
    {
      int i;
      for(i = 0; i < sizeofparams-1; i++)
	cout<<params[i]->getName()<<"("<<params[i]->getType()->toString()<<"),";
      cout<<params[i]->getName()<<"("<<params[i]->getType()->toString()<<")";
    }
  bool isTypeBound() { return typebound; }
  void setTypeBound(bool value) { typebound = value; }
};


#endif










