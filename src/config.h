#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "ASTnode.h"
#include "token.h"

//#define DEBUG	0x0001			    /*switches debug mode off and on*/

#define PARSER_MESSAGE 0x0000       /*turns on and off the parsing success/failure message*/
#define SEMANTIC_MESSAGE 0x0001     /*turns on and off the semantic success/failure message*/
		
#define	STDIN_INPUT 0x0001			/*reading from standard input*/
#define FILE_INPUT 0x0002			/*reading from file*/

#define KEYWORD_SIZE 45
#define PUNCTUATIONS_SIZE 22

#define SYSTEM_BLOCK_SIZE 1024

static char* g_KeyWords[KEYWORD_SIZE] = {"ARRAY","BEGIN","BY","CASE","CONST" \
					 ,"DIV","DO","ELSE","ELSIF","END" \
					 ,"EXIT","FOR","IF","IMPORT","IN" \
					 ,"IS","LOOP","MOD","MODULE","NIL" \
					 ,"OF","OR","POINTER","PROCEDURE" \
					 ,"RECORD","REPEAT","RETURN","THEN" \
					 ,"TO","TYPE","UNTIL","VAR","WHILE" \
					 ,"WITH","BOOLEAN","CHAR","FALSE" \
					 ,"INTEGER","NEW","REAL","TRUE" \
					 ,"READ","WRITE","NL","PROGRAM"};

static int g_KeyWordCodes[KEYWORD_SIZE] = {T_ARRAY,T_BEGIN,T_BY,T_CASE, \
					   T_CONST,T_DIV,T_DO,T_ELSE,T_ELSIF, \
					   T_END,T_EXIT,T_FOR,T_IF,T_IMPORT, \
					   T_IN,T_IS,T_LOOP,T_MOD,T_MODULE, \
					   T_NIL,T_OF,T_OR,T_POINTER, \
					   T_PROCEDURE,T_RECORD,T_REPEAT, \
					   T_RETURN,T_THEN,T_TO,T_TYPE, \
					   T_UNTIL,T_VAR,T_WHILE,T_WITH, \
					   T_BOOLEAN,T_CHAR,T_FALSE, \
					   T_INTEGER,T_NEW,T_REAL,T_TRUE, \
					   T_READ,T_WRITE,T_NL,T_PROGRAM};

static char* g_Punctuations[PUNCTUATIONS_SIZE] = {"&","^",":","=","|",",", \
						   ".",">","{","[","(","<", \
						   "-","#","+","}","]",")", \
						   ";","~","/","*"};
static int 
g_PuncTypes[PUNCTUATIONS_SIZE] = {T_AMPERSAND,T_ARROW,T_COLON,T_EQU,T_BAR \
				 ,T_COMMA,T_DOT,T_GT,T_LBRACE,T_LBRACKET \
				 ,T_LPAREN,T_LT,T_MINUS,T_NEQ,T_PLUS,T_RBRACE \
				 ,T_RBRACKET,T_RPAREN,T_SEMI,T_TILDE,T_SLASH \
				 ,T_STAR};
 

#endif


