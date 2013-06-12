#ifndef _CHAINNODE_H_
#define _CHAINNODE_H_
#include "symbol.h"

class ChainNode
{
public:
  Symbol* data;
  ChainNode* next;
  ChainNode()
    {
      data = NULL;
      next = NULL;
    }
};

#endif
