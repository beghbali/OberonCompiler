
/*---------------------------------------------------------------------------------------------------------------
 * debug.h -- debug functions should go here. The test harness should be the
 *            only file including this unless you want to do temporary 
 *            debugging in another file
 *
 * September 2001  Bashir Eghbali
 *
 * Copyright 2001, Bashir Eghbali, Ravi Singh
 *---------------------------------------------------------------------------------------------------------------
 */

#ifndef _DEBUG_H_
#define _DEBUG_H_

/*C includes*/
#include <stdio.h>
/*end C includes*/

#include <stack>
#include <hash_set>
#include <iterator>
#include "lib.h"
#include "inputStruct.h"
#include "buffer.h"
#include "ASTnode.h"

typedef hash_set<const char*, hash<const char*>, eqstr> HASHTABLE;

void dumpStack(stack<inputStruct*> s);
void dumpHashTable(HASHTABLE table);
void dumpBuffer(char* buff, int size);
void print(inputStruct* x);
void traceAST(ASTNode* node);
#endif
