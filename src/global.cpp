#include "type.h" 
#include "errorhandler.h"
#include "semchecker.h"
#include "stack.h"
#include "machine.h"

/*static members from TypeValues*/  
Type* TypeValues::INTEGER_TYPE = new IntegerType();
Type* TypeValues::REAL_TYPE = new RealType();
Type* TypeValues::BOOLEAN_TYPE = new BooleanType();
Type* TypeValues::CHAR_TYPE = new CharType();
Type* TypeValues::STR_TYPE = new StringType();
Type* TypeValues::NIL_TYPE = new NilType();
Type* TypeValues::ERROR_TYPE = new ErrorType();
Type* TypeValues::NO_TYPE = new NoType();
Type* TypeValues::POINTER_TYPE = new PointerType(TypeValues::NO_TYPE);
/*static members from ErrorHandler*/
bool ErrorHandler::status = true;

/*static members of Symbol*/
ErrorSym* Symbol::ERROR_SYM =  new ErrorSym("ERROR", TypeValues::ERROR_TYPE);

Type* Type::recursiveType = TypeValues::NO_TYPE;
Machine* Machine::machine = NULL;
