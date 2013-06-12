#include <iostream>
#include "config.h"
#include "parser.h"
#include "lexer.h"
#include "semchecker.h"
#include "symboltable.h"
#include "ASTnode.h"
#include "codegen.h"
#include "registerbank.h"
#include "machine.h"

#define DEFAULT_OUTPUT_TARGET "oberon.s"

bool GEN_ASSEMBLY = false;
bool GEN_SYMTABLE = false;
bool GEN_INCSYMTABLE = false;
ASTNode* ASTree;

char* predeclared_procs[PREDECLARED_SIZE] = {"ABS", "ASH", "CAP", "CHR", \
					    "COPY", "DEC", "ENTIER", "EXCL", \
					    "HALT", "INC", "INCL", "LEN", \
					    "LONG", "MAX", "MIN", "NEW", \
					     "ODD", "ORD", "SHORT",
					     "SIZE"};

char* DEFAULT_REGISTERS[NUMBER_OF_DEFAULT_REGISTERS] ={"%l7","%l6","%l5","%l4","%l3","%l2","%l1","%l0"};
char* OUTPUT_REGISTERS[NUMBER_OF_OUTPUT_REGISTERS] = {"%o5","%o4","%o3","%o2","%o1","%o0"};
char* INPUT_REGISTERS[NUMBER_OF_INPUT_REGISTERS] = {"%i5","%i4","%i3","%i2","%i1","%i0"};
CodeGenerator* codegen;
SemanticChecker* semchecker;

void main(int argc, char* argv[])
{
  Lexer* lexer = new Lexer(argc, argv);
  Parser* parser = new Parser(lexer);
  char* mytemp;
  SymbolTable* symtable;
  char* output_target = DEFAULT_OUTPUT_TARGET;
  Machine* platform;
  if(lexer->getInputStruct()) 
    { 
      int success = parser->parse();
      int sem_success;
      if(success)
	{
	  if(PARSER_MESSAGE)
	    cout<<"Parsing: success"<<endl;
	  symtable = new SymbolTable();
	  RegisterBank* regbank = new RegisterBank(DEFAULT_REGISTERS, NUMBER_OF_DEFAULT_REGISTERS, LOCAL);
	  regbank->setGlobalPointer(new Register(GLOBAL_POINTER, GLOBAL,GLOBAL_POINTER_ADDR));
	  regbank->setStackPointer(new Register(STACK_POINTER, STACK,STACK_POINTER_ADDR));
	  regbank->setFramePointer(new Register(FRAME_POINTER, FRAME,FRAME_POINTER_ADDR));
	  RegisterBank* outputregs = new RegisterBank(OUTPUT_REGISTERS, NUMBER_OF_OUTPUT_REGISTERS, OUTPUT);
	  RegisterBank* inputregs = new RegisterBank(INPUT_REGISTERS, NUMBER_OF_INPUT_REGISTERS, INPUT);
	  platform = new Sparc(regbank,outputregs,inputregs);
	  Machine::setCurrentMachine(platform);
	  codegen = new CodeGenerator(platform, output_target);
	  platform->setOutput(codegen->getOutputStream());
	  codegen->beginCodeGen();
	  semchecker = new SemanticChecker(symtable, ASTree, codegen);
	  sem_success = semchecker->check();
	  codegen->endCodeGen();
	}
      else if(PARSER_MESSAGE)
	cout<<"Parsing: failure"<<endl;
      if(sem_success && SEMANTIC_MESSAGE)
	cout<<"Semantic success."<<endl;
      else
	cout<<"Semantic failure."<<endl;
    }
  delete lexer;
  delete parser;
}
