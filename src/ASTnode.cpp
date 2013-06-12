#include "ASTnode.h"
#include "lexer.h"
#include "type.h"
#include "symboltable.h"

extern Lexer* g_Lexer;

ASTNode::~ASTNode()
{
  delete [] children;
}

ASTNode::ASTNode(Symbol* sym_, int nodetype_)
{
  init(sym_->getName(), nodetype_, 0);
  Symbol* sym1 = sym;
  sym = sym_;
  delete sym1;
}

ASTNode::ASTNode(char* name_, int nodetype_, int size_)
{
  init(name_, nodetype_, size_);
}

void ASTNode::init(char* name_, int nodetype_, int size_)
{
  size = size_;
  nodetype = nodetype_;
  sym = new Symbol(name_, TypeValues::ERROR_TYPE);
  fileinfo = new inputStruct();
  fileinfo->filename = g_Lexer->getInputStruct()->filename;
  fileinfo->line = g_Lexer->getInputStruct()->line;

  if(size_ == 0)
    children = NULL;
  else
    //children = (ASTNode**)malloc(sizeof(ASTNode*)*size_);
    children = new ASTNode*[size_];
  next = 0;
}

ASTNode* ASTNode::operator[](int i)
{
  return get(i);
}

inline ASTNode* ASTNode::get(int i)
{
  return i < size ? children[i] : NULL;
}

void ASTNode::addChild(char* name_, int nodetype_)
{
  addChild(new ASTNode(name_, nodetype_, 0));
}
void ASTNode::addChild(ASTNode* new_child)
{
  children[next++] = new_child;
}

void ASTNode:: addChildrenOf(ASTNode* node)
{
  //children = (ASTNode**)realloc(children, sizeof(ASTNode*)*(size+node->size));
  ASTNode** temp = children;
  children = new ASTNode*[size+node->size];
  memcpy(children, temp, next*sizeof(ASTNode*));
  size += node->size;
  for(int i = 0 ; i < node->size; i++)
    addChild((*node)[i]);
  
}



