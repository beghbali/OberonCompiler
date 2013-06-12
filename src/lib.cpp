#include <stdio.h>
#include <math.h>
#include <cstdlib>

char* itoa(int i)
{
  if(i == 0)
    return "0";
  char* a = (char*)malloc((int)(log(i)/log(2))+1);
  sprintf(a, "%d", i);
  return a;
}

