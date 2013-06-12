#ifndef _STACK_H_
#define _STACK_H_

#include <iostream>

#define TOP    1
#define BOTTOM 2

typedef bool (*COMP_FUNC) (int, int); 

class Stack
{
private:
  int* list;
  int  size;
  int current;
  int peek;

  void resize();
public:
  Stack(int size_ = 100);
  bool empty();
  void push(int x);
  int pop();
  int top();
  void resetPeek(int pos);
  int peekNext();
  int peekPrevious();
  int getPeekIndex(int pos);
  void set(int, int);
};

class PointerStack : public Stack
{
public:
  COMP_FUNC comp_func;
  PointerStack(COMP_FUNC comp_func_, int size_ = 5) : Stack(size_), comp_func(comp_func_){}
  
  int find(int p)
    {
      int peek1;
      resetPeek(TOP);
      while((peek1 = peekPrevious()) != -999)
	  {
	    if(comp_func(peek1, p))
	      return peek1;
	  }
      return 0;
    }
};

#endif
