#ifndef _ERRORHANDLER_H_
#define _ERRORHANDLER_H_

#include <string>
#include "inputStruct.h"
#include "symbol.h"
#include "type.h"

/*error cases*/
#define CASE1  1
#define CASE2  2
#define CASE3  3
#define CASE4  4
#define CASE5  5
#define CASE6A 6
#define CASE6B 7
#define CASE6C 5
#define CASE7A 8
#define CASE7BA 9
#define CASE7BB 7
#define CASE7BC 8
#define CASE7C 10
#define CASE8  11
#define CASE9  12
#define CASE10 13
#define CASE11 14

enum Error
{
  unknownCharacter         = 0x0000,    //ex: $#@
  newlineInStringLiteral   = 0x0001,    //\n in string literal
  EOFInStringLiteral       = 0x0002,    //EOF in string literal
  unterminatedComment      = 0x0003,    //EOF in comment
  identifierTooLong        = 0x0004,    //too long lexeme, ID
  stringLiteralTooLong     = 0x0005,    //too long lexeme, STRING LITERAL
  integerLiteralTooLong    = 0x0006,    //too long lexeme, INTEGER LITERAL
  realLiteral_M_TooLong    = 0x0007,    //too long lexeme,REAL_LITERAL mantissa
  realLiteral_E_TooLong    = 0x0008,    //too long lexeme,REAL_LITERAL expon.
  characterLiteralTooLong  = 0x0009,    //too long lexeme, CHAR_LITERAL
  illegalHexIntegerLiteral = 0x000A,    //hex INT_LITERAL w/o trailing H:12ABC
  cannotOpenFile           = 0x000B,    //a file from commandline fails to open
  illegalIncludeDirective  = 0x000C,    //INCLUDE followed by non-string lit.
  badIncludeFile           = 0x000D,    //INCLUDE file specified cannot open
  multiplyIncludedFile     = 0x000E,    //circular include
  unterminatedStringLiteral= 0x000F,    //if EOF or '\n' in string
  parserError              = 0x0010,    //parser errors
  semanticError            = 0x0011     //semantic errors
};

typedef enum Error Error;


class ErrorHandler
{
private:
  static bool status;
public:
  static void handleError(Error error, inputStruct*, const char*);
  static void printError(inputStruct*, char* message);
  static bool getStatus(){ return status; }
  static void semanticError1(int error_case, inputStruct* fileinfo, char* arg);
  static void getOptoString(char* opout, int opin);
  static void fatalError(char* message);
  static void warning(char* message);
  /*specific functions for printing errors for Semantic Checker part II*/
  static void error1n_Expr(inputStruct* fileinfo, Type* type, int 
				  op_);
  static void error1w_Expr(inputStruct* fileinfo, Type* type1, int 
				  op_, Type* type2);
  static void error1u_Expr(inputStruct* fileinfo, Type* type1, int 
				  op_, Type* type2);
  static void error1b_Expr(inputStruct* fileinfo, Type* type1, int 
				  op_, Type* type2);
  static void error2_Assign(inputStruct* fileinfo, Symbol* sym);
  static void error3_Assign(inputStruct* fileinfo, Type* type1,
				   Type* type2);
  static void error4_Test(inputStruct* fileinfo, Type* type);
  static void error5c_FOR(inputStruct* fileinfo, Type* type);
  static void error5v_FOR(inputStruct* fileinfo, Symbol* sym);
  static void error5l_FOR(inputStruct* fileinfo, Type* type);
  static void error5u_FOR(inputStruct* fileinfo, Type* type);
  static void error5i_FOR(inputStruct* fileinfo, Type* type);
  static void error6n_Call(inputStruct* fileinfo, int narg,
				  int nparam);
  static void error6a_Call(inputStruct* fileinfo, Type* type1,
				  Symbol* sym, Type* type2);
  static void error6v_Call(inputStruct* fileinfo, Type* type1,
				  Symbol* sym, Type* type2);
  static void error6c_Call(inputStruct* fileinfo, Type* type1,
				  Symbol* sym, Type* type2);
  static void error7a_RETURN(inputStruct* fileinfo);
  static void error7b_RETURN(inputStruct* fileinfo, Type*
				    type);
  static void error7b_RETURN_type(inputStruct* fileinfo, Type*
					 type1, Type* type2);
  static void error8_RETURN(inputStruct* fileinfo);
  static void error9_CONST(inputStruct* fileinfo, Symbol* sym);
  static void error10i_ARRAY(inputStruct* fileinfo, Type*
				    type);
  static void error10c_ARRAY(inputStruct* fileinfo);
  static void error10t_ARRAY(inputStruct* fileinfo, Symbol*
				    sym);
  static void error11v_ArrExp(inputStruct* fileinfo);
  static void error11t_ArrExp(inputStruct* fileinfo, Type*
				     type);
  static void error11i_ArrExp(inputStruct* fileinfo, Type*
				     type);
  static void error13_EXIT(inputStruct* fileinfo);
  static void error14_POINTER(inputStruct* fileinfo, Type*
				     type);
  static void error15v_RecExp(inputStruct* fileinfo);
  static void error15t_RecExp(inputStruct* fileinfo, Type*
				     type);
  static void error15f_RecExp(inputStruct* fileinfo, Symbol* sym, 
				     Type* type);
  static void error16_RECORD(inputStruct* fileinfo, Symbol*
				    sym);
  static void error17_Receiver(inputStruct* fileinfo, Type*
				      type);
  static void error18_NEW(inputStruct* fileinfo, Type* type);
  static void error19_Expr(inputStruct* fileinfo, int op_, Type*
				  type1, Type* type2);
  
};

#define ERROR(type,istruct,arg) ErrorHandler::handleError(type, istruct, arg);

#endif
