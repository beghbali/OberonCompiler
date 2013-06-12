#include <stdio.h>
#include <iostream>
#include "config.h"
#include "errorhandler.h"
#include "inputStruct.h"
#include "codegen.h"

#define BUFFER_SIZE  500
extern CodeGenerator* codegen;
void ErrorHandler::handleError(Error error, inputStruct* fileinfo,const char* arg)
{
  char* error_detail = new char[BUFFER_SIZE];
  memset(error_detail, '\0', BUFFER_SIZE);
  switch(error)
    {
    case unknownCharacter: 
      strcat(error_detail,"unknown character '");
      strcat(error_detail,arg);
      strcat(error_detail,"'");
      break;
    case newlineInStringLiteral: 
      strcat(error_detail,"newline in string literal");
      break;
    case EOFInStringLiteral: 
      strcat(error_detail,"EOF in string literal");
      break;
    case unterminatedComment:
      strcat(error_detail,"unterminated comment");
      break;
    case identifierTooLong:
      strcat(error_detail,"identifier too long");
      break;
    case stringLiteralTooLong:
      strcat(error_detail,"string literal too long");
      break;
    case integerLiteralTooLong:
      strcat(error_detail,"integer literal too long");
      break;
    case realLiteral_M_TooLong:
      strcat(error_detail,"real literal (mantissa) too long");
      break;
    case realLiteral_E_TooLong:
      strcat(error_detail,"real literal (exponent) too long");
      break;
    case characterLiteralTooLong:
      strcat(error_detail,"character literal too long");
      break;
    case illegalHexIntegerLiteral:
      strcat(error_detail,"illegal hex integer literal \"");
      strcat(error_detail, arg);
      strcat(error_detail,"\"");
      break;
    case cannotOpenFile:
      strcat(error_detail,"cannot open file \"");
      strcat(error_detail, arg);
      strcat(error_detail, "\"");
      break;
    case illegalIncludeDirective:
      strcat(error_detail,"illegal include directive \"");
      strcat(error_detail, arg);
      strcat(error_detail,"\"");
      break;
    case badIncludeFile:
      strcat(error_detail,"bad include file \"");
      strcat(error_detail,arg);
      strcat(error_detail,"\"");
      break;
    case multiplyIncludedFile:
      strcat(error_detail,"multiply included file \"");
      strcat(error_detail,arg);
      strcat(error_detail,"\"");
      break;
    case unterminatedStringLiteral:
      strcat(error_detail,"unterminated string literal");
      break;
    default:
      strcat(error_detail,arg);
      break;
    }
  printError(fileinfo, error_detail);
}

void ErrorHandler::semanticError1(int error_case, inputStruct* fileinfo, char* arg)
{
  char* message = new char[BUFFER_SIZE];
  memset(message, '\0', BUFFER_SIZE);
  char* temp = NULL;
  bool first = false;
  int mask;
  
  switch(error_case)
    {
    case CASE1: 
      strcpy(message,"undeclared identifier '");
      break;
      
    case CASE2:
      strcpy(message,"redeclared identifier '");
      break;
      
    case CASE3:        
      first = true;
      strcpy(message,"' is not a procedure.");
      break;
      
    case CASE4:        
      first = true;
      strcpy(message,"' is not valid in an expression.");
      break;
      
    case CASE5:        //also CASE6C
      first = true;
      strcpy(message,"' is not a type.");
      break;
      
    case CASE6A:
      first = true;
      strcpy(message,"' is not a module.");
      break;
	
    case CASE6B:        //also CASE7BB
      first = true;
      strcpy(message,"' is not exported.");
      break;
      
    case CASE7A:         //also CASE7BC
      first = true;
      strcpy(message,"' is neither a constant, variable, nor procedure.");
      break;
      
    case CASE7BA:
      first = true;
      strcpy(message,"' is neither a module nor a variable.");
      break;
      
    case CASE8:
      first = true;
      strcpy(message,"' cannot be exported.");
      break;
      
    case CASE9:
      first = true;
      strcpy(message,"' cannot be imported.");
      break;
      
    case CASE10:
      strcpy(message,"improper procedure end ID '");
      break;

    case CASE11:
      strcpy(message,"illegal assignment to non-variable '");
      break;
      
    default:
      ;
    }
  
  if(first)
    {	  
      temp = new char[strlen(message)+strlen(arg)+4];
      strcpy(temp, "'");
      strcat(temp, arg);
      strcat(temp, message);
      ERROR(semanticError, fileinfo, temp);
    }
  else
    {
      message = (char*)realloc(message,strlen(message)+strlen(arg)+3);
      strcat(message, arg);
      strcat(message, "'.");
      ERROR(semanticError, fileinfo, message);
    }
}

void ErrorHandler::getOptoString(char* opout, int opin)
 {
   switch(opin)
     {
     case EQU: strcpy(opout, "="); break;
     case PLUS: strcpy(opout, "+"); break;
     case MINUS: strcpy(opout, "-"); break;
     case MULTIPLY: strcpy(opout, "*"); break;
     case SLASH: strcpy(opout, "/"); break;
     case NEQ: strcpy(opout, "#"); break;
     case DIVIDE: strcpy(opout, "DIV"); break;
     case MOD: strcpy(opout, "MOD"); break;
     case LT: strcpy(opout, "<"); break;
     case GT: strcpy(opout, ">"); break;
     case LTE: strcpy(opout, "<="); break;
     case GTE: strcpy(opout, ">="); break;
     case IN: strcpy(opout, "IN"); break;
     case IS: strcpy(opout, "IS"); break;
     case TILDE: strcpy(opout, "~"); break;
     case AND: strcpy(opout, "&"); break;
     case OR: strcpy(opout, "OR"); break;     
     }
 }

void ErrorHandler::printError(inputStruct* file_struct, char* error_detail)
{  
  /*when two same files are read from command line.*/
  if(!file_struct || strcmp(file_struct->filename,"") == 0)
    cout<<error_detail<<endl;
  else if(file_struct->file == &cin)
    cout << "Error, ("<<file_struct->filename<<"), line "<<file_struct->line<<":\n  "<<error_detail<<endl;
  else
    cout << "Error, \""<<file_struct->filename<<"\", line "<<file_struct->line<<":\n  "<<error_detail<<endl;

  if(codegen)
    codegen->abortCodeGen();
  ErrorHandler::status = false;
}

void ErrorHandler::fatalError(char* message)
{
  cout<<"FATAL ERROR: "<<message<<endl;
}

void ErrorHandler::warning(char* message)
{
  cout<<"Warning: " << message<<endl;
}

void ErrorHandler::error1n_Expr(inputStruct* fileinfo, Type* type, int 
op_)
{
  char message[BUFFER_SIZE];
  char op[4];
  ErrorHandler::getOptoString(op, op_);
  sprintf(message, "Incompatible type %s to binary operator %s, numeric expected.", type->toString(), op);
  printError(fileinfo, message);
}
 
void ErrorHandler::error1w_Expr(inputStruct* fileinfo, Type* type1, int 
op_, Type* type2)
{
  char message[BUFFER_SIZE];
  char op[4];
  ErrorHandler::getOptoString(op, op_);
  sprintf(message, "Incompatible type %s to binary operator %s, equivalent to %s expected.", type1->toString(), op, type2->toString());
 printError(fileinfo, message);
}

void ErrorHandler::error1u_Expr(inputStruct* fileinfo, Type* type1, int 
op_, Type* type2)
{
  char message[BUFFER_SIZE];
  char op[4];
  ErrorHandler::getOptoString(op, op_);
  sprintf(message, "Incompatible type %s to unary operator %s, equivalent to %s expected.", type1->toString(), op, type2->toString());
 printError(fileinfo, message);
}

void ErrorHandler::error1b_Expr(inputStruct* fileinfo, Type* type1, int 
op_, Type* type2)
{
  char message[BUFFER_SIZE];
  char op[4];
  ErrorHandler::getOptoString(op, op_);
  sprintf(message, "Incompatible types to operator: %s %s %s;\n  both must be numeric, or both equivalent to BOOLEAN.",type1->toString(), op, type2->toString());
  printError(fileinfo, message);
}     

void ErrorHandler::error2_Assign(inputStruct* fileinfo, Symbol* sym)
{
  char message[BUFFER_SIZE];
  sprintf(message, "%s is not assignable (not a variable).", sym->getName());
  printError(fileinfo, message);
} 
 
void ErrorHandler::error3_Assign(inputStruct* fileinfo, Type* type1,
				 Type* type2)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Value of type %s not assignable to variable of type %s.", type1->toString(), type2->toString());
 printError(fileinfo, message);
} 

void ErrorHandler::error4_Test(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "BOOLEAN required for conditional test, %s found.", type->toString());
  printError(fileinfo, message);
} 
 
void ErrorHandler::error5c_FOR(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "INTEGER control variable required in FOR loop, %s found.", type->toString());
  printError(fileinfo, message);
} 

void ErrorHandler::error5v_FOR(inputStruct* fileinfo, Symbol* sym)
{
  char message[BUFFER_SIZE];
  sprintf(message, "FOR loop index %s is not assignable (not a variable).", sym->getName());
  printError(fileinfo, message);
} 

void ErrorHandler::error5l_FOR(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "INTEGER value required in FOR loop lower bound, %s found.", type->toString());
  printError(fileinfo, message);
} 

void ErrorHandler::error5u_FOR(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "INTEGER value required in FOR loop upper bound, %s found.", type->toString());
  printError(fileinfo, message);
}
 
void ErrorHandler::error5i_FOR(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "INTEGER value required in FOR loop increment, %s found.", type->toString());
  printError(fileinfo, message);
} 

void ErrorHandler::error6n_Call(inputStruct* fileinfo, int narg,
				int nparam)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Number of arguments (%d) differs from number of parameters (%d).", narg, nparam);
  printError(fileinfo, message);
}

void ErrorHandler::error6a_Call(inputStruct* fileinfo, Type* type1,
				Symbol* sym, Type* type2)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Argument of type %s not assignable to value parameter %s, of type %s.", type1->toString(), sym->getName(),
	  type2->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error6v_Call(inputStruct* fileinfo, Type* type1,
				Symbol* sym, Type* type2)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Argument of type %s not equivalent to VAR parameter %s, of type %s.", type1->toString(), sym->getName(),
	  type2->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error6c_Call(inputStruct* fileinfo, Type* type1,
				Symbol* sym, Type* type2)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Non-addressable argument (type %s) passed to VAR parameter %s (type %s).", type1->toString(), sym->getName(),
	  type2->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error7a_RETURN(inputStruct* fileinfo)
{
  char message[BUFFER_SIZE];
  strcpy(message, "RETURN in function requires a result expression, none found.");
  printError(fileinfo, message);
}

void ErrorHandler::error7b_RETURN(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "RETURN with result expression (type %s), not allowed in pure procedure.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error7b_RETURN_type(inputStruct* fileinfo, Type*
				       type1, Type* type2)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Type of RETURN expression (%s), not assignment compatible with procedure's return type (%s).", type1->toString(), type2->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error8_RETURN(inputStruct* fileinfo)
{
  char message[BUFFER_SIZE];
  strcpy(message, "RETURN required in function, none found.");
  printError(fileinfo, message);
}

void ErrorHandler::error9_CONST(inputStruct* fileinfo, Symbol* sym)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Value of declared constant %s not known at compile time.",sym->getName());
  printError(fileinfo, message);
}

void ErrorHandler::error10i_ARRAY(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Index expression type (%s) in ARRAY declaration not equivalent to INTEGER.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error10c_ARRAY(inputStruct* fileinfo)
{
  char message[BUFFER_SIZE];
  strcpy(message, "Value of index expression not known at compile time.");
  printError(fileinfo, message);
}

void ErrorHandler::error10t_ARRAY(inputStruct* fileinfo, Symbol* sym)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Declared element type of ARRAY does not denote a type (%s).", sym->getName());
  printError(fileinfo, message);
}

void ErrorHandler::error11v_ArrExp(inputStruct* fileinfo)
{
  char message[BUFFER_SIZE];
  strcpy(message, "Expression referenced by array subscript is not a variable.");
  printError(fileinfo, message);
}

void ErrorHandler::error11t_ArrExp(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Type of expression referenced by array subscript (%s) is not of ARRAY type.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error11i_ArrExp(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Type of index expression in array reference (%s) not equivalent to INTEGER.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error13_EXIT(inputStruct* fileinfo)
{
  char message[BUFFER_SIZE];
  strcpy(message, "EXIT does not occur in a loop.");
  printError(fileinfo, message);
}

void ErrorHandler::error14_POINTER(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Type in POINTER must be RECORD, %s found.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error15v_RecExp(inputStruct* fileinfo)
{
  char message[BUFFER_SIZE];
  strcpy(message, "Expression referenced by \".\" is not a variable.");
  printError(fileinfo, message);
}

void ErrorHandler::error15t_RecExp(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Type of expression referenced by \".\" (%s) is not a RECORD or POINTER TO RECORD.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error15f_RecExp(inputStruct* fileinfo, Symbol* sym, 
				   Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Referenced field %s not found in type %s.", sym->getName(), type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error16_RECORD(inputStruct* fileinfo, Symbol* sym)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Field %s declared second time in RECORD.", sym->getName());
  printError(fileinfo, message);
}

void ErrorHandler::error17_Receiver(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Type of receiver variable of type-bound procedure must be POINTER TO RECORD, %s found.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error18_NEW(inputStruct* fileinfo, Type* type)
{
  char message[BUFFER_SIZE];
  sprintf(message, "Type of NEW'd variable must be POINTER TO RECORD, %s found.", type->toString());
  printError(fileinfo, message);
}

void ErrorHandler::error19_Expr(inputStruct* fileinfo, int op_, Type*
				type1, Type* type2)
{
  char message[BUFFER_SIZE];
  char op[4];
  ErrorHandler::getOptoString(op, op_); 
  sprintf(message, "Incompatible types to operator %s:\n    %s,\n     %s;\n  both must be of equivalent POINTER type, or both of equivalent RECORD type.", op, type1->toString(), type2->toString());
  printError(fileinfo, message);
}
