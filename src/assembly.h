#ifndef _ASSEMBLY_H_
#define _ASSEMBLY_H_
#include <iostream>
#include <stack>
#include <cstdlib>
#include "parserlib.h"


static const int OPSIGN_NONE  = 0;
static const int OPSIGN_PLUS  = 1;
static const int OPSIGN_MINUS = 2;

extern bool GEN_ASSEMBLY;
extern char* itoa(int i);

static int gen_id(int seed = 0)
{
  static int id = 0;
  if(seed == -1)
    id = -1;
  return id++;
}

static int gen_id1(int seed = 0)
{
  static int id1 = 0;
  if(seed == -1)
    id1 = -1;
  return id1++;
}

stack<char*> labels;
stack<char*> exits;
stack<char*> parens;

int opsign_state = OPSIGN_NONE;
         
class Assembly
{
public:
  static char* genIntegerExpr(char* Expr1, char* op, char* Expr2);
  static void genAssignStmt(char* ID, char* Expr);
  static char* getNextNumber(int seed = 0);
  static char* getNextNumber1(int seed = 0);
  static void genIFtop(char* ID);
  static void getIFbottom();
  static void genLoopTop();
  static void genLoopBottom();
  static void genExitStmt();
  static void genOpSignParenTop();
  static char* genOpSignParenBottom(char* expr);
  static void setSeenOpSign(char* state);
  static int seenOpSign();
  static char* opSignToString();
};

char* Assembly::genIntegerExpr(char* Expr1, char* op, char* Expr2)
{
  if(GEN_ASSEMBLY)
    {
      if(strcmp(op, "DIV") == 0)
	op = "/";
      else if(strcmp(op, "MOD") == 0)
	op = "%";

      char* t = concat("T",Assembly::getNextNumber());
      cout<<t<<" := "<<Expr1<<op<<Expr2<<endl;
      return t;
    }
  return NULL;
}

void Assembly::genAssignStmt(char* ID, char* Expr)
{
  if(GEN_ASSEMBLY)
    cout<<ID<<" := "<<Expr<<endl;
}

char* Assembly::getNextNumber(int seed = 0)
{ 
  if(seed == -1)
    {
      gen_id(seed);
      return NULL;
    }
  return itoa(gen_id(seed));
}

char* Assembly::getNextNumber1(int seed = 0)
{ 
  if(seed == -1)
    {
      gen_id(seed);
      return NULL;
    }
  return itoa(gen_id1(seed));
}

void Assembly::genIFtop(char* ID)
{
  if(!GEN_ASSEMBLY)
    return;
  char* label = getNextNumber1();
  cout<<"if not "<<ID<<" goto L"<<label<<endl;
  labels.push(label);
}

void Assembly::getIFbottom()
{
  if(!GEN_ASSEMBLY || labels.empty())
    return;
  cout<<concat(concat("L",labels.top()),":")<<endl;
  labels.pop();
}

void Assembly::genLoopTop()
{
  if(GEN_ASSEMBLY)
    {
      char* label = getNextNumber1();
      cout<<"L"<<label<<":"<<endl;
      labels.push(label);   //for Ln
      exits.push(getNextNumber1());     //for Lm
    }
}

void Assembly::genLoopBottom()
{
  if(GEN_ASSEMBLY)
    {
	  if(labels.empty() || exits.empty())
		  return;
      cout<<"goto L"<<labels.top()<<endl;
      labels.pop();
      cout<<"L"<<exits.top()<<":"<<endl;
      exits.pop();
    }
}

void Assembly::genExitStmt()
{
  if(GEN_ASSEMBLY && !exits.empty())
    {
      cout<<"goto L"<<exits.top()<<endl;
    }
}

void Assembly::genOpSignParenTop()
{
  parens.push(opSignToString());
}

char* Assembly::genOpSignParenBottom(char* expr)
{
  if(parens.empty())
	  return expr;
  
  char* temp = ((strcmp(parens.top(), "") == 0) ? expr : concat(parens.top(), expr?expr:(char*)""));
  parens.pop();
  return temp;
}

void Assembly::setSeenOpSign(char* cstate)
{
  if(strcmp(cstate, "+") == 0)
    opsign_state = OPSIGN_PLUS;
  else if (strcmp(cstate, "-") == 0)
    opsign_state = OPSIGN_MINUS;
  else
    opsign_state = OPSIGN_NONE;
}

int Assembly::seenOpSign()
{
  return opsign_state;
}

char* Assembly::opSignToString()
{
  char* sign = new char[2];
  if(opsign_state == OPSIGN_PLUS)
   strcpy(sign,"+");
  else if (opsign_state == OPSIGN_MINUS)
    strcpy(sign,"-");
  else
    strcpy(sign,"");
  return sign;
}
#endif
