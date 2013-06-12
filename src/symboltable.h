#ifndef _SYMBOLTABLE_H_
#define _SYMBOLTABLE_H_

#include "symbol.h"
#include "stack.h"
#include "chainnode.h"

#define INSERT 1
#define REHASH 2

class SymbolTable
{
private:
  int capacity;
  int size;
  float loadFactor;
  ChainNode** table;
  Stack scopes;
  bool inmodule;
  int insert(Symbol* sym, int op);
  void remove(ChainNode**, Symbol*, int);
  Symbol* find(char* key);
  void rehash();
  int hash_func(char* key);
public:
  SymbolTable(int capacity_ = 100, float loadFactor_ = 0.85);
  void remove(Symbol* key);
  void insert(Symbol* sym);
  Symbol* lookup(char* key);
  bool exists(char* key);
  void begin_scope();
  void end_scope();
  void printTable();
  Symbol** getSymbolsInCurrentScope(int* listsize);
};

#endif


