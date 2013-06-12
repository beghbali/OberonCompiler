#include "type.h"
#include "symbol.h"

char* RecordType::getFieldTypesToString()
{
  int index;
  char* result = "";
  Symbol* sym;
  if(!fieldlist)
    return result;
  fieldlist->resetPeek(BOTTOM);
  
  bool isbase = false;
  if(Type::recursiveType == TypeValues::NO_TYPE)
    {
      Type::recursiveType = this;
      isbase = true;
    }
  while((index = fieldlist->peekNext()) != -999)
    {
      sym = ((Symbol*)index); 
      if(this->isRecord() && sym->getType()->isPointer() && sym->getType()->getBaseType() == Type::recursiveType)
	result = concat(result, "POINTER TO RECORD");
      else if(this->isPointer() && this->getBaseType()->isRecord() && sym->getType() == Type::recursiveType)
	result = concat(result, "POINTER TO RECORD");
      else if(this->isRecord() && sym->getType() == Type::recursiveType)
	result = concat(result, "RECORD");
      else
	result = concat(result,	(char*)((Symbol*)index)->getType()->toString());
     
      result = concat(result, ";");
    }
  if(result != "")
    result[strlen(result)-1] = '\0';   ///killing the last ; char
  if(isbase)
    Type::recursiveType = TypeValues::NO_TYPE;
  return result;
}

Symbol* RecordType::getField(char* fieldname) 
{ 
  return (Symbol*)fieldlist->find((int)fieldname);
}

RecordType::RecordType(char* name_, PointerStack* field_list_): name(name_), fieldlist(field_list_),width(0)
{
  VarSym* last;
  if(!field_list_)
    return;
  last = (VarSym*)field_list_->top();
  width = last->getOffset() + last->getWidth();
}
