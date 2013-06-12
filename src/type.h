#ifndef _TYPE_H_
#define _TYPE_H_
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
#include "parserlib.h"
#include "machine.h"

class Symbol;  //forward declaration to keep the compiler happy
class VarSym;

class Type
{
 public:
  static Type* recursiveType;
  Type(){}
  virtual bool isInt() { return false;}
  virtual bool isReal() { return false;}
  virtual bool isBool() { return false;}
  virtual bool isChar() { return false;}
  virtual bool isString() { return false;}
  virtual bool isNil() { return false;}
  virtual bool isRecord() { return false;}
  virtual bool isArray() { return false;}
  virtual bool isProc() { return false;}
  virtual bool isPointer() { return false;}
  virtual bool isError() { return false;}
  virtual bool isNoType() { return false;}
  virtual bool isNumeric() { return isReal() || isInt(); }
  virtual bool isCompound() { return false; }
  virtual const char* toString() { return "Type"; }
  virtual bool isSameAs(Type* other) { return false; }
  virtual bool isEqualTo(Type* other) { return false; }
  virtual Type* getBaseType() { return this; }
  virtual void set(Type* other) { return; }
  virtual bool isAssignable(Type* other){ return (isSameAs(other) ||
						  other->includes(this));}
  virtual bool includes(Type* other){ return false;}
  virtual int getWidth() { return 0; }
  virtual int getBaseWidth() { return getWidth(); }
};

class TypeValues
{
public:
  static Type* INTEGER_TYPE;
  static Type* REAL_TYPE;
  static Type* BOOLEAN_TYPE;
  static Type* CHAR_TYPE;
  static Type* STR_TYPE;
  static Type* NIL_TYPE;
  static Type* POINTER_TYPE;
  static Type* ERROR_TYPE;
  static Type* NO_TYPE;
};

class BasicType : public Type
{
public:
  BasicType(){}
  const char* toString() { return "BasicType"; }
};

class IntegerType : public BasicType
{
public:
  IntegerType(){}
  bool isInt() { return true;}
  const char* toString() { return "INTEGER"; }
  bool isSameAs(Type* other) { return other->isInt(); }
  bool isEqualTo(Type* other) { return other->isInt(); }
  bool includes(Type* other){ return other->isInt(); }
  int getWidth() { return Machine::getIntegerWidth(); }
};

class RealType : public BasicType
{
public:
  RealType(){}
  bool isReal() { return true;}
  const char* toString() { return "REAL"; }
  bool isSameAs(Type* other) { return other->isReal(); }
  bool isEqualTo(Type* other) { return other->isReal(); }
  bool includes(Type* other){ return other->isNumeric(); }
  int getWidth() { return Machine::getRealWidth(); }
};

class BooleanType : public BasicType
{
public:
  BooleanType(){}
  bool isBool() { return true;}
  const char* toString() { return "BOOLEAN"; }
  bool isSameAs(Type* other) { return other->isBool(); }
  bool isEqualTo(Type* other) { return other->isBool(); }
  bool includes(Type* other){ return other->isBool(); }
  int getWidth() { return Machine::getBooleanWidth(); }
};

class CharType : public BasicType
{
public:
  CharType(){}
  bool isChar() { return true;}
  const char* toString() { return "CHAR"; }
  bool isSameAs(Type* other) { return other->isChar(); }
  bool isEqualTo(Type* other) { return other->isChar(); }
  bool includes(Type* other){ return other->isChar(); }
  int getWidth() { return Machine::getCharWidth(); }
};

class CompoundType : public Type
{
 protected:
  Type* basetype;
 public:
  CompoundType(Type* basetype_) : basetype(basetype_){}
  bool isCompound() { return true; }
  Type* getBaseType() { return basetype;}//basetype->isCompound() ? basetype->getBaseType() : basetype; }
};

class RecordType : public Type
{
 private:
  char* name;
  PointerStack* fieldlist;
  int width;
    
 public:
  char* getFieldTypesToString();
  RecordType(char* name_, PointerStack* field_list_);
  bool isRecord() { return true;}
  void setName(char* name_) { name = name_; }
  char* getName() { return name; }
  const char* toString() { return concat("RECORD ",getFieldTypesToString()); }
  bool isSameAs(Type* other) { return this == other; }
  bool isEqualTo(Type* other) { return other->isRecord(); }
  bool isField(char* fieldname) { return fieldlist->find((int)fieldname) ? true : false; }
  PointerStack* getFieldsList() { return fieldlist; }
  Symbol* getField(char* fieldname);
  void addField(Symbol* field) { fieldlist->push((int)field); }
  void set(Type* other) 
    { 
      if(other->isRecord())
	{
	  this->name = ((RecordType*)other)->getName();
	  this->fieldlist = ((RecordType*)other)->getFieldsList();
	  this->width = ((RecordType*)other)->getWidth();
	}
    }
  int getWidth() { return width; }  
};

class PointerType : public CompoundType
{
public:
  PointerType(Type* basetype_):CompoundType(basetype_){}
  bool isPointer() { return true;}
  const char* toString() 
    { 
      bool isbase = false;
      if(Type::recursiveType == TypeValues::NO_TYPE)
	{
	  Type::recursiveType = this;
	  isbase = true;
	}
      if(this->getBaseType() == Type::recursiveType || this->getBaseType()->isNil())
	{
	  if(isbase)
	    Type::recursiveType = TypeValues::NO_TYPE;
	  return concat("POINTER TO ", "?");
	}
      if(isbase)
	Type::recursiveType = TypeValues::NO_TYPE;
      return concat("POINTER TO ",(char*)basetype->toString()); 
    }
  bool isSameAs(Type* other) { return other->isPointer() && getBaseType()->isSameAs(other->getBaseType()) || other->isNil(); }
  bool isEqualTo(Type* other) { return other->isPointer(); }
  void set(Type* other) 
    { 
      if(other->isPointer())
	this->basetype = ((PointerType*)other)->getBaseType();
    }
  int getWidth() { return Machine::getPointerWidth(); }
};

class NilType : public PointerType
{
 public:
  NilType(): PointerType(TypeValues::ERROR_TYPE){}
  bool isNil() { return true;}
  const char* toString() { return "NIL"; }
  bool isSameAs(Type* other) { return other->isNil() || other->isPointer(); }
  bool isEqualTo(Type* other) { return other->isNil(); }
  Type* getBaseType() { return basetype; }
  int getWidth() { return Machine::getPointerWidth(); }
};

class ArrayType : public CompoundType
{
private:
  int size;
public:
  ArrayType(int size_, Type* basetype_):size(size_), CompoundType(basetype_){}
  bool isArray() { return true;}
  const char* toString() 
    { 
      bool isbase = false;
      if(Type::recursiveType == TypeValues::NO_TYPE)
	{
	  Type::recursiveType = this;
	  isbase = true;
	}
      char* result = (char*) malloc(17+strlen(basetype->toString()));
      char* basetypetostring;
      if(basetype == Type::recursiveType)
	basetypetostring = "?";
      else 
	basetypetostring = (char*)basetype->toString();
      if(size == -1)
	{
	  if(basetype->isChar())
	    sprintf(result, "ARRAY OF %s", basetypetostring);
	  else
	    sprintf(result, "ARRAY ? OF %s", basetypetostring);
	}
      else
	sprintf(result, "ARRAY %d OF %s", size, basetypetostring); 
      
      if(isbase)
	Type::recursiveType = TypeValues::NO_TYPE;
      return result; 
    }
  bool isSameAs(Type* other) { return this == other || (basetype->isChar() && other->isString()); }
  bool isEqualTo(Type* other) { return other->isArray(); }
  int getSize() { return size; }
  void set(Type* other)
    {
      this->size = ((ArrayType*)other)->getSize();
      this->basetype = other->getBaseType();
    }
  int getWidth() { return size*basetype->getWidth(); }  
  int getBaseWidth() { return basetype->getBaseWidth(); }
};

class ProcType : public Type
{
 private:
  Type* returntype;
 public:
  ProcType(){}
  ProcType(Type* returntype_) : returntype(returntype_) {}
  bool isProc() { return true;}
  const char* toString() { return "PROCEDURE"; }
  bool isSameAs(Type* other){ return returntype->isSameAs(other);}
  bool isEqualTo(Type* other) { return other->isProc(); }
  Type* getReturnType() { return returntype ? returntype : TypeValues::ERROR_TYPE; }
  void setReturnType(Type* returntype_) { returntype = returntype_;}
  int getWidth() { return returntype->getWidth(); }  
};

class StringType : public BasicType
{
public:
  StringType(){}
  bool isString() { return true;}
  const char* toString() { return "ARRAY OF CHAR"; }
  bool isSameAs(Type* other) { return other->isString() ||
				 (other->isArray() && ((ArrayType*)other)->getBaseType()->isChar());}
  bool isEqualTo(Type* other) { return other->isString(); }
  bool includes(Type* other){ return other->isString(); }
  int getWidth() { return Machine::getPointerWidth(); }  
};

class ErrorType : public Type
{
public:
  ErrorType() {}
  bool isInt() { return true;}
  bool isReal() { return false;}
  bool isBool() { return true;}
  bool isChar() { return true;}
  bool isStr() { return true;}
  bool isNil() { return true;}
  bool isArray() { return true;}
  bool isProc() { return false;}  
  bool isPointer() { return true;}
  bool isNumeric() { return true;}
  bool isError() { return true; }
  bool isCompound() { return true;}
  const char* toString() { return "ERROR_TYPE"; }
  bool isSameAs(Type* other) { return true; }
  bool isEqualTo(Type* other) { return other->isError(); }
};

class NoType : public Type
{
public:
  NoType() {}
  const char* toString() { return "NO_TYPE"; }
  bool isSameAs(Type* other) { return false; }
  bool isEqualTo(Type* other) { return false; }
  bool isNoType() { return true; }
  int getWidth() { return Machine::getPointerWidth(); }
};

#endif
