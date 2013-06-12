#include <iostream>
#include <cstring>
#include <cstdlib>
#include "symbol.h"
#include "ASTnode.h"
#include "symboltable.h"
#include "type.h"
#include "semchecker.h"

#define NULL_INITIALIZER 0x00000000
extern bool GEN_INCSYMTABLE;
extern SemanticChecker* semchecker;

SymbolTable::SymbolTable(int capacity_, float loadFactor_): capacity(capacity_), loadFactor(loadFactor_), size(0), inmodule(false)
{
  table = new ChainNode*[capacity_];
  memset(table, NULL_INITIALIZER,capacity*sizeof(ChainNode*));
}


void SymbolTable::insert(Symbol* sym)
{
  if(!sym->getName())
    return;
  insert(sym, INSERT);
}

int SymbolTable::insert(Symbol* sym, int op)
{
  int index = hash_func(sym->getName()) % capacity;
  ChainNode* new_node = new ChainNode();
  new_node->data = sym;
  
  if(size >= capacity*loadFactor || size == capacity-1)
    {
      rehash();
      return insert(sym, INSERT);
    }

  while(table[index] && strcmp(sym->getName(), table[index]->data->getName()) != 0)
    index = ++index%capacity;
  if(table[index] == NULL)
    {
     
      new_node->next = NULL;
      table[index] = new_node;
      if(op == INSERT)
	size++;
    }
  else
    {
      new_node->next = table[index];
      table[index] = new_node;
    }

  if(op == INSERT)
    { 
      scopes.push(index);
    }

  return index;
}

void SymbolTable::remove(Symbol* sym)      
{
  remove(table, sym, INSERT);
}

void SymbolTable::remove(ChainNode** table, Symbol* sym, int op)
{
  int index = hash_func(sym->getName()) % capacity;
  ChainNode* deleted_node;
  while(table[index] && strcmp(sym->getName(), table[index]->data->getName()) != 0)
    index = ++index%capacity;
  if(!table[index])
    return;
  deleted_node = table[index];
  table[index] = deleted_node->next;
  deleted_node->next = NULL;
  delete deleted_node;
  if(op == INSERT)
    size--;
}


Symbol* SymbolTable::find(char* key)
{
  int index = hash_func(key) % capacity;
  
  while(table[index] && strcmp(key, table[index]->data->getName()) != 0)
    index = ++index % capacity;
  
  if(!table[index])
    return NULL;

  return table[index]->data;
}

void SymbolTable::rehash()
{
  int peek;
  ChainNode* mover;
  ChainNode** old_table = table;
  int old_capacity = capacity;
  capacity *= 2;
  table = new ChainNode*[capacity];
  memset(table, NULL_INITIALIZER, capacity*sizeof(ChainNode*));
  scopes.resetPeek(BOTTOM);
  while((peek = scopes.peekNext()) != -999)
    {
      int temp;
      if(peek < 0)
	continue;
      scopes.set(scopes.getPeekIndex(BOTTOM), (temp = insert(old_table[peek]->data, REHASH)));
      remove(old_table, old_table[peek]->data, REHASH);
    }

  for(int i = 0; i < old_capacity; i++)
    delete old_table[i];
  delete [] old_table;
}

int SymbolTable::hash_func(char* key)
{ 
  int  hash, i;
  int len = strlen(key);

  for (hash=0, i=0; i<len; ++i)
    {
      hash += key[i];
      hash += (hash << 10);
      hash ^= (hash >> 6);
    }
  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
 
  return hash < 0 ? -hash : hash;
}  
 
Symbol* SymbolTable::lookup(char* key)
{
  return find(key);
}

bool SymbolTable::exists(char* key)
{
  return find(key) ? true : false;
}

void SymbolTable::begin_scope()
{
  scopes.push(-1);
}

void SymbolTable::end_scope()
{
  int index;
  if(GEN_INCSYMTABLE)
    printTable();
  while((index = scopes.top()) != -1)
    { 
      remove(table[index]->data);
      scopes.pop();
    }

  scopes.pop();
}

void SymbolTable::printTable()
{
  int counter = 0;
  int space = 0;
  ChainNode* mover = NULL;
  VarSym* param;
  char* scopename = semchecker->currentProcedure ? semchecker->currentProcedure->getName() : (char*)"global";
  cout<<"COUNT\tADDRESS\t\tSCOPE\tNAME\t\tSYMTYPE\t\tTYPE\t\t\t\tBASE\tOFFSET"<<endl;
  for(int i = 0; i < (20-strlen(scopename))/2 ; i++)
    cout<<"-";
  printf("---------------------------------------------%s",scopename);
  for(int i = 0; i < (20-strlen(scopename))/2 ; i++)
    cout<<"-";
  cout<<"------------------------------------------------"<<endl;
  for(int i = 0; i < capacity; i++)
    {
      mover = table[i];
      while(mover)
	{
	  space = 11-strlen(mover->data->getName());
	  printf("%d\t%#.8x",counter,&(mover->data));
	  cout<<"\t"<<(mover->data->isGlobal() ? "GLOBAL\t" : "LOCAL\t")<<mover->data->getName();
	  for(int j = 0; j < space; j++)
	    cout<<" ";
	  cout<<"\t"<<mover->data->toString();
	  space = 11-strlen(mover->data->toString());
	  for(int j = 0; j < space; j++)
	    cout<<" ";
	  if(mover->data->isProc())
	    { 
	      int k;
	      char buff[128];
	      char tempbuff[60];
	      strcpy(buff,"\t(");
	      for(k = 0; k <((ProcSym*)mover->data)->getParamListSize()-1; k++)
		{
		  param = (VarSym*)((ProcSym*)mover->data)->getParams()[k];
		  sprintf(tempbuff, "%s%s,",param->getType()->toString(),param->isReference()?"*":"");
		  strcat(buff, tempbuff);
		}
	      if(((ProcSym*)mover->data)->getParamListSize() > 0)
		{
		  param = (VarSym*)((ProcSym*)mover->data)->getParams()[k];
		  sprintf(tempbuff, "%s%s",param->getType()->toString(),param->isReference()?"*":"");
		  strcat(buff, tempbuff);
		}
	      sprintf(tempbuff,")->%s",((ProcType*)mover->data->getType())->getReturnType()->toString());
	      if(strlen(buff) > 12)
		printf("%-.15s%-s%-12.13s", buff,"...", tempbuff);
	      else
		printf("%-2.15s%-12.13s", buff, tempbuff);
	      if(((ProcSym*)mover->data)->getParamListSize() == 0)
		cout<<"\t";
	    }
	  else
	    {
	      if(strlen(mover->data->getType()->toString()) > 15)
		printf("\t%-.25s%-s%-s",mover->data->getType()->toString(), mover->data->isVar() && ((VarSym*)mover->data)->isReference() ? "*" :"","...");
	      else
		printf("\t%-.25s%-s",mover->data->getType()->toString(), mover->data->isVar() && ((VarSym*)mover->data)->isReference() ? "*" :"");
	      if(strlen(mover->data->getType()->toString()) < 8 && !(mover->data->isVar() && ((VarSym*)mover->data)->isReference()))
		cout<<"\t";
	    }
	  if((!mover->data->isProc() && strlen(mover->data->getType()->toString())<12))
	    cout<<"\t\t";
	  else if((mover->data->isProc() && ((ProcSym*)mover->data)->getParamListSize() == 0))
	    cout<<"\t";
	  if(mover->data->isConstVar())
	    cout<<"\t"<<((ConstVarSym*)mover->data)->getBase()->toString()<<"\t"<<((ConstVarSym*)mover->data)->getOffset()<<endl;
	  else 
	    cout<<"\t---\t---"<<endl;
	  counter++;
	  mover = mover->next;
	}
    }
  cout<<"-----------------------------------------------------------------------------------------------------------------"<<endl;
}

Symbol** SymbolTable::getSymbolsInCurrentScope(int* listsize)
{
  int p;
  int size;
  int i = 0;
  Symbol** symlist; 
  scopes.resetPeek(TOP);
  size = scopes.getPeekIndex(TOP);
  symlist = (Symbol**) malloc(sizeof(Symbol*) * size);
  while((p = scopes.peekPrevious()) != -999 && p > 0)
    symlist[i++] = table[p]->data;
  *listsize = size;

  return symlist;
}
/*
void main (int argc, char* argv[])
{
char* names[5] = {"x", "X", "y", "bashir", "ELSE"};
SymbolTable* symtable = new SymbolTable(5);
symtable->begin_scope();
for(int i = 0; i < 5; i++)
symtable->insert(new Symbol(names[i], TypeValues::INTEGER_TYPE));
cout<<"global scope"<<endl;
symtable->printTable();

cout<<"me exists="<<symtable->exists("me")<<endl;
cout<<"bashir exists="<<symtable->exists("bashir")<<endl;
cout<<"x exists="<<symtable->exists("x")<<endl;
cout<<"ELSE exists="<<symtable->exists("ELSE")<<endl;
  
cout<<"proc1 scope/global scope"<<endl;

symtable->begin_scope();
symtable->insert(new Symbol("bashir", TypeValues::INTEGER_TYPE ));
symtable->insert(new Symbol("N", TypeValues::INTEGER_TYPE));
  
symtable->printTable();
  
cout<<"bashir exists="<<symtable->exists("bashir")<<endl;
cout<<"ELSE exists="<<symtable->exists("ELSE")<<endl;
cout<<"N exists="<<symtable->exists("N")<<endl;
cout<<"M exists="<<symtable->exists("M")<<endl;
  
symtable->end_scope();

cout<<"global scope"<<endl;
symtable->printTable();

cout<<"N exists="<<symtable->exists("N")<<endl;
cout<<"x exists="<<symtable->exists("x")<<endl;
  
symtable->end_scope();
  
symtable->printTable();
  
}
*/
