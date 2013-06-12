#include <cstdlib>
#include "stack.h"

Stack::Stack(int size_):size(size_), current(-1), peek(-1)
{
  list = new int[size];
}

bool Stack::empty()
{
  return (current < 0 ? true : false);
}

void Stack::push(int x)
{
  if(current == size-1)
    resize();
  list[++current] = x;
}

int Stack::pop()
{
  if(current == -1)
    return 0;
  
  return list[current--];
}

int Stack::top()
{
  return list[current];
}

void Stack::resetPeek(int pos)
{
  if(pos == TOP)
    peek = current;
  else if(pos == BOTTOM)
    peek = -1;
}

int Stack::peekNext()
{
  return peek < current ? list[++peek] : -999;
}

int Stack::peekPrevious()
{
  return peek >= 0 ? list[peek--] : -999;
}

int Stack::getPeekIndex(int pos)
{
  return peek;
}

void Stack::resize()
{
  size *= 2;
  list = (int*)realloc(list, size*sizeof(int));
}

void Stack::set(int index, int value)
{
  list[index] = value;
}
