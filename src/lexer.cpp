#include "config.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "lexer.h"
#include "errorhandler.h"
#include "debug.h"

#undef DEBUG
static int g_input = STDIN_INPUT; /*if input was read from stdin or file*/
extern bool GEN_ASSEMBLY;
extern bool GEN_SYMTABLE;
extern bool GEN_INCSYMTABLE;

Lexer::~Lexer()
{
  delete keywords;
  delete punctuations;
  delete buffer;
}

Lexer::Lexer(int argc, char** argv)
{			
  last_fileinfo = NULL;
  keywords = new Keywords(g_KeyWords, g_KeyWordCodes, KEYWORD_SIZE);
  punctuations = new Punctuations(g_Punctuations, g_PuncTypes, PUNCTUATIONS_SIZE);
  parseParameters(argc, argv);
}

void Lexer::parseParameters(int argc, char* argv[])
{
  int param = argc;
  const char* temp;
  
  /* 
   * reading command line arguments, processing them via processOptions() and
   * populating the list of files to be compiled
   */
  while(param > 1)
    {
      temp = argv[param-1];

      if(temp[0] == '-')
	processOptions(temp);
      else
	{
 
	  g_input = FILE_INPUT;

	  /*check to see if the file has already been viewed*/
	  if(isDuplicateFile(temp))	
	    {
	      ERROR(multiplyIncludedFile, NULL, temp);
	    }
	  else
	    {
	      inputStruct* x = createInputStruct(temp, 1, NULL);
	      if(x)
		{
		  s_files.push(x);
		  h_VisitedFilesTable.insert(temp);
		}
	    }
	}
      param--;
    }
  if(g_input == STDIN_INPUT)/*push standard input onto the stack to read from*/
    {
      s_files.push(createInputStruct("stdin", 1, &cin));
    }
  if(s_files.empty())
    return;
 buffer = new Buffer(&s_files);
}

void Lexer::processOptions(const char* option)
{
  switch(option[1])
  {
  case 'a':
    GEN_ASSEMBLY = true;
    break;
  case 's':
    if(strcmp(&option[2], "inc") == 0)
      GEN_INCSYMTABLE = true;
    else
      GEN_SYMTABLE = true;
    break;
  default:;
#ifdef DEBUG
		cout<<"OPTION="<<option<<endl;
#endif
    /*cases go here*/
  }
}

bool Lexer::isDuplicateFile(const char* filename)
{
  char* temp1;

  temp1 = strrchr(filename, '/');	/*to remove pathname and get filename*/
  if(temp1)
    filename = temp1+1;

  return (h_VisitedFilesTable.find(filename) == h_VisitedFilesTable.end() ? false : true);
}

char* Lexer::lookupFile(const char* filename)
{
  return lookup(h_VisitedFilesTable, filename);
}

Token* Lexer::GetToken()
{
  if(s_files.empty())
    return NULL;
  Token* token;
  while(true)
    {
      token = getTokenInternal();
  
      if(!token && s_files.size() == 1)
	  {
		  last_fileinfo = (inputStruct*)s_files.top();
		  s_files.pop();
	  }
	  
      if(!token || token->nCode != T_ID || strcmp(token->csLexeme,"INCLUDE") != 0)
	return token;
      
      token = getTokenInternal(); 
      if(!token)
	{
	  ERROR(illegalIncludeDirective,s_files.top(),"");
	  if(s_files.size() == 1)
	  {
		  last_fileinfo = (inputStruct*)s_files.top();
		  s_files.pop();
	  }
	  return token;
	}
      if(token->nCode != T_STR_LITERAL)
      {
	ERROR(illegalIncludeDirective,s_files.top(),token->csLexeme);
	continue;
      }
      
      if(isDuplicateFile(token->csLexeme))	
	{
	  ERROR(multiplyIncludedFile,s_files.top(),token->csLexeme);
	  continue;
	}
      
      ifstream* file = new ifstream(token->csLexeme);
      if(!file->is_open())
	{
	  ERROR(badIncludeFile,s_files.top(),token->csLexeme); 
	  continue;
	}
      inputStruct* x = createInputStruct(token->csLexeme, 1, file);
      h_VisitedFilesTable.insert(token->csLexeme);
      s_files.push(x);
      buffer->resetFile();
    }
}

Token* Lexer::getTokenInternal()
{
  char c;
  int i = 0;

  while((c = buffer->getChar()) != EOF)
    {
      buffer->resetLexeme();
      if(isspace(c))
	{
	  if(c == '\n')
	    s_files.top()->line++; 
	
	  continue;
	}
      else if(isalpha(c))
	return process_identifiers();
      else if(isdigit(c))
	return process_numeric(c);
      else if(punctuations->lookupPunc(c))
	{
	  Token* token = process_punctuations(c);
	  if(!token)
	    continue;
	  
	  return token;
	}
      else if(c == '\'' || c == '\"')
	return process_strings(c);
      else
	{
	  ERROR(unknownCharacter,s_files.top(),(new string(1,c))->data());
	}
    }
  buffer->resetLexeme();
  return NULL;
}

Token* Lexer::process_numeric(char trans)
{
  Token* token = new Token;  //the token to be returned
  int nextState = NDFA_0;    //start state
  bool isReal = true;
  char* lexeme = NULL;
  char* lexemeFragment = NULL;     //used when dealing w/ exponent leading 0's
  int ndfa_4_counter = 0;
  char EorD;                   //keeps track of E/D for later catination
  char PorM = ' ';             //keeps track of +/- for later catination
  char* intLexeme = NULL;
  char* hexLexeme = NULL;
  int leadZero = 0;
  char temp[2];

  while(true)
    {
#ifdef DEBUG
      printf("%#x\n",nextState);  //transition stack trace
#endif
      switch(nextState)
	{
	case NDFA_0:
	  if(trans == '0')     //go to eliminate leading zeros
	    nextState = NDFA_1;
	  else                 //process digits
	    nextState = NDFA_4;
	  break;
	case NDFA_1:      //getting rid of leading zeros
	  while((trans = buffer->getChar()) == '0');  //skip leading zeros

	  if(isDXdigit(trans))  //hex or int digit
	   {
	     if(isalpha(trans))    //checks to see if trans = 'ABCDEF'
	       isReal = false;
	     buffer->resetLexeme();
	     nextState = NDFA_4;
	     break;
	   }
	  
	  buffer->putChar();  
	  buffer->resetLexeme();  //reserve one zero if any
	  trans = buffer->getChar();
	    
	  if(trans == '.')    //real literal
	  {
		leadZero = 1;
	    nextState = NDFA_6;
	  }
	  else if(trans == 'H')    //hex int literal
	    nextState = NDFA_3;
	  else if(trans == 'X')    //char literal
	    nextState = NDFA_2;
	  else   //since an accept state return an int
	    {
	      buffer->putChar();
	      TOKEN(T_INT_LITERAL, buffer->getLexeme());
	      return token;
	    }
	  break;
	case NDFA_2:
	  TOKEN(T_CHAR_LITERAL, buffer->getLexeme());
	  return token;
	case NDFA_3:
	  TOKEN(T_INT_LITERAL, buffer->getLexeme());
	  return token;
	case NDFA_4:
	
	  while(isDXdigit((trans = buffer->getChar())))
	    {  
	      if(isalpha(trans))    //checks to see if trans = 'ABCDEF'
		isReal = false;
	      ndfa_4_counter++;
	      if(ndfa_4_counter == 7)      //save lexeme in case a hex
		{
		  hexLexeme = buffer->getLexeme();
		}
	      else if(ndfa_4_counter == 8)      //save lexeme for real literal
		{
		  lexeme = buffer->getLexeme();
		}
	      else if(ndfa_4_counter == 9)      //save lexeme for int literal
		{
		  intLexeme = buffer->getLexeme();
		}
	    }
	
	  if(trans == '.' && isReal)     //now can only be real literal
	   {
	     if(lexeme)
	       strcat(lexeme, ".");
	     nextState = NDFA_6;
	   }
	  else if(trans == 'H')
	    nextState = NDFA_5;
	  else if(trans == 'X')
	    nextState = NDFA_7;
	  else   //since an accept state return an int
	    {
	      buffer->putChar();   //put back the non int literal char.
	      if(!isReal)
		{
		  if(hexLexeme)
		    {
		      ERROR(illegalHexIntegerLiteral,s_files.top(),hexLexeme);
		      if(ndfa_4_counter > 7)
			{
			  ERROR(integerLiteralTooLong,s_files.top(),"");
			}
		      strcat(hexLexeme, "H");
		      TOKEN(T_INT_LITERAL,hexLexeme);
		      return token;
		    }
		  else
		    {
		      ERROR(illegalHexIntegerLiteral,s_files.top(),buffer->getLexeme());
		      hexLexeme = buffer->getLexeme();
		      strcat(hexLexeme, "H");
		      TOKEN(T_INT_LITERAL,hexLexeme);
		      return token;
		    }
		}
	      if(intLexeme)
		{
		  if(ndfa_4_counter > 9)
		    {
		      ERROR(integerLiteralTooLong,s_files.top(),"");
		    }
		  TOKEN(T_INT_LITERAL,intLexeme);
		  return token;
		}
    
	      TOKEN(T_INT_LITERAL, buffer->getLexeme());
	      return token;
	    }
	  break;
	case NDFA_5:         //accepting hex int literal
	  if(hexLexeme)  //if more than 10 digits then lexeme is saved
	    {
	      hexLexeme = strcat(hexLexeme,"H");
	      TOKEN(T_INT_LITERAL,hexLexeme);  //appends the 'H' 
	    }
	  else
	    {
	      TOKEN(T_INT_LITERAL, buffer->getLexeme());
	    }
	  if(ndfa_4_counter > 7)
	    {
	      ERROR(integerLiteralTooLong,s_files.top(),"");
	    }
	  return token;
	case NDFA_6:
	  for(int i = 8-ndfa_4_counter+leadZero;isdigit(trans = buffer->getChar()) && i > 0; i--);
	  if(trans == 'E' || trans == 'D')  //go to check exponent
	    {
	      EorD = trans;
	
	      if(lexeme && ndfa_4_counter >= 9)
		lexeme = intLexeme;
	
	      nextState = NDFA_9;
	    }
	  else if(isdigit(trans))         //too long
	    {
	      if(ndfa_4_counter < 9)      //up to now it was not too long
		  {
			buffer->putChar();
			lexeme = buffer->getLexeme();   //save lexeme
			buffer->getChar();
		  }
	      else
		lexeme = intLexeme;
	      nextState = NDFA_8;
	    }
	  else   //since an accept state return a real
	    {
	      buffer->putChar();
	      if(lexeme)        //9 real digits
		{
		  if(ndfa_4_counter > 8)
		    {
		      ERROR(realLiteral_M_TooLong,s_files.top(),"");
		    }
		  lexeme[11]= '\0';    //overwrite the 10th digit
		  TOKEN(T_REAL_LITERAL,lexeme);
		  return token;
		}
	
	      TOKEN(T_REAL_LITERAL, buffer->getLexeme());
	      return token;
	    }
	  break;
	case NDFA_7:          //accepting char literal
	  if(ndfa_4_counter > 2)
	    {
	      ERROR(characterLiteralTooLong,s_files.top(),"");
	      if(!lexeme)
		lexeme = new char[5];
	      memcpy(lexeme,buffer->getLexeme(),3);     //copy only 3 chars
	      lexeme[3] = '\0';
	      strcat(lexeme,"X");
	    }
	  else
	      lexeme = buffer->getLexeme();
	    
	  TOKEN(T_CHAR_LITERAL, lexeme);
	  return token;
	case NDFA_8:
	  
	  ERROR(realLiteral_M_TooLong,s_files.top(),"");
	    
	  while(isdigit(trans = buffer->getChar()));
	  if(trans == 'E' || trans == 'D')   //process exponent
	    {
	      EorD = trans;
	      nextState = NDFA_9;
	    }
	  else
	    {
	      buffer->putChar();
	      lexeme[10] = '\0';    //overwrite the 10th digit
	      TOKEN(T_REAL_LITERAL,lexeme);
	      return token;
	    }
	  break;
	case NDFA_9:

	  if((trans = buffer->getChar()) == '+' || trans == '-') 
	    {
	      PorM = trans;
	      nextState = NDFA_10;
	    }
	  else if(trans == '0')
	  {
		if(lexeme)
			strcat(lexeme,&EorD);
	
		nextState = NDFA_11;
	  }
	  else if(isdigit(trans))
	    {
		  if(lexeme)
			  strcat(lexeme,&EorD);
	      nextState = NDFA_12;
	    }
	  else
	    {

	      buffer->putChar();   //put back character
	      buffer->putChar();   //put back E/D

	      if(lexeme)           //for too long case
		{
		  TOKEN(T_REAL_LITERAL,lexeme);
		  return token;
		}
	      TOKEN(T_REAL_LITERAL, buffer->getLexeme());
	      return token;
	    }

	  break;
	case NDFA_10:
	  if(lexeme)     //too long case
	    {
	      /*make room for E/D +/- and 3 exponent digits*/
	      lexeme = (char*)realloc(lexeme, strlen(lexeme)+5+leadZero);	 
	      lexeme[10+leadZero] = EorD;  //adds E/D to the end of Mantissa 
	      if(PorM != ' ')
		{
		  lexeme[11+leadZero] = PorM;  //adds +/-
		  lexeme[12+leadZero] = '\0';
		}
	      else
		lexeme[11+leadZero] = '\0';
	    }
	  if((trans = buffer->getChar()) == '0')
	    nextState = NDFA_11;
	  else if(isdigit(trans))
	    nextState = NDFA_12;
	  else
	    {
	      if((PorM = buffer->putChar()) == '+' || PorM == '-')//put back +/-
		buffer->putChar();    //put back E/D
	      buffer->putChar();
	      if(lexeme)
		{
		  TOKEN(T_REAL_LITERAL, lexeme);
		  return token;
		}
	      TOKEN(T_REAL_LITERAL, buffer->getLexeme());
	      return token;
	    } 
	  break;
	case NDFA_11:           //have seen one leading exponent zero
	  char* tempLexeme;
	  buffer->putChar(); 
	  if(!lexeme)
	    tempLexeme = buffer->getLexeme();
	  while((trans = buffer->getChar()) == '0');
	  if(isdigit(trans))
	    {
		  if(!lexeme)
			lexeme = tempLexeme;

	      nextState = NDFA_12;
	    }
	  else
	    {
	      buffer->putChar();
	      if(lexeme)     //too long case
		{
		  if(PorM != ' ')
		    {
		      lexeme[12+leadZero] = '0';
		      lexeme[13+leadZero] = '\0';
		    }
		  else
		    {
		      lexeme[11+leadZero] = '0';
		      lexeme[12+leadZero] = '\0';
		    }
		  TOKEN(T_REAL_LITERAL,lexeme);
		  return token;
		}
	      strcat(tempLexeme, "0");
	      TOKEN(T_REAL_LITERAL, tempLexeme);
	      return token;
	    }  
	  break;
	case NDFA_12:
	  if(lexeme)
	    {
	      temp[0] = trans;
	      temp[1] = '\0';
	      strcat(lexeme, temp);
	    } 
	 
	  for(int i = 0; isdigit(trans = buffer->getChar()) && i < 2; i++)
	    { 
	      temp[0] = trans;
	      if(lexeme)
		strcat(lexeme, temp);
	    }


	  if(isdigit(trans))    //exponent too long
	    {
	      ERROR(realLiteral_E_TooLong,s_files.top(),"");
	      nextState = NDFA_13;
	    }
	  else
	    {
	      buffer->putChar();
	      if(lexeme)
		{
		  TOKEN(T_REAL_LITERAL,lexeme);
		}
	      else
		{
		  TOKEN(T_REAL_LITERAL, buffer->getLexeme());
		}
	      return token;
	    }
	  break;
	case NDFA_13:         //too long exponent
	  if(!lexeme)
	    {
	      buffer->putChar();
	      lexeme = buffer->getLexeme();
	    }

	  while(isdigit(trans = buffer->getChar()));
	
	  TOKEN(T_REAL_LITERAL, lexeme);
	  buffer->putChar();
	  return token;
	default:
#ifdef DEBUG
	  cout<<"wrong state in NDFA"<<endl;
#else
	  ;
#endif
	}
    }	  
}


Token* Lexer::process_identifiers()
{
  char trans;
  Token* token = new Token;
  char* lexeme = NULL;
  int occurence = 0;
  int code;
  
  while(isalnum(trans = buffer->getChar()))
    {
      if(++occurence == 39)              //too long 1+39=40=MAX
	lexeme = buffer->getLexeme();
    }
  buffer->putChar();
  if(lexeme)          //in too long case
    {
      ERROR(identifierTooLong,s_files.top(),"");
      TOKEN(T_ID, lexeme);
      return token;
    }
    code = keywords->lookupKeyword(buffer->getLexeme());
  if(code)    //known KEYWORD
    {
      TOKEN(code, buffer->getLexeme());
    }
  else        //identifier
    {
      TOKEN(T_ID,buffer->getLexeme());
    }

  return token;
}

Token* Lexer::process_punctuations(char trans)
{
  Token* token = new Token;
  int tempC;
  switch(trans)
    {
    case '.':
      if((trans = buffer->getChar()) == '.')
	tempC = T_DOTDOT;
      else
	{
	  buffer->putChar();
	  tempC = punctuations->lookupPunc('.');
	}
      break;
    case ':':
      if((trans = buffer->getChar()) == '=')
	tempC = T_ASSIGN;
      else
	{
	  buffer->putChar();
	  tempC = punctuations->lookupPunc(':');
	}
      break;
    case '>':
      if((trans = buffer->getChar()) == '=')
	tempC = T_GTE;
      else
	{
	  buffer->putChar();
	  tempC = punctuations->lookupPunc('>');
	}
      break;
    case '<':
       if((trans = buffer->getChar()) == '=')
	tempC = T_LTE;
      else
	{
	  trans = buffer->putChar();
	  tempC = punctuations->lookupPunc('<');
	}
      break;
    case '(':
      if((trans = buffer->getChar()) == '*')
	return process_comments();
      buffer->putChar();
      tempC = punctuations->lookupPunc('('); 
      break;
    default:
      tempC = punctuations->lookupPunc(trans);
    }
  TOKEN(tempC,buffer->getLexeme());
  return token;
}

Token* Lexer::process_strings(char trans)
{
  Token* token = new Token;
  int counter = 0;
  char* lexeme = NULL;
  char quoteType = trans;
  char temp;
  char temp1;
  buffer->getChar();        //skipping " or ' in lexeme
  buffer->resetLexeme();
  buffer->putChar();

  while((trans = buffer->getChar()) != quoteType)
    {
      if(trans == '\n')
	{
	  ERROR(newlineInStringLiteral,s_files.top(),"");
	  break;
	}
      else if(trans == EOF)
	{
	  ERROR(EOFInStringLiteral,s_files.top(),"");
	  break;
	}
      if( ++counter == 81)
	{
	  buffer->putChar();
	  lexeme = buffer->getLexeme();
	  buffer->getChar();
	  ERROR(stringLiteralTooLong,s_files.top(),"");
	}
    }

  buffer->putChar();
  
  if(lexeme)
    {
      TOKEN(T_STR_LITERAL,lexeme);
    }
  else
    {
      TOKEN(T_STR_LITERAL,buffer->getLexeme());
    }
  if(trans == quoteType)
    buffer->getChar();
  return token;
}

Token* Lexer::process_comments()
{
  int counter = 1;    //already have a open comment token
  char trans = buffer->getChar();

  while(counter != 0)
    {
      switch(trans)
	{
	case EOF:
	  ERROR(unterminatedComment,s_files.top(),"");
	  counter = 0;
	  continue;
	case '*':
	  if((trans = buffer->getChar()) == ')')
	    counter--;
	  else
	    continue;
	  break;
	case '(':
	  if((trans = buffer->getChar()) == '*')
	    counter++;
	  else 
	    continue;
	  break;
	case '\n':
	  s_files.top()->line++;
	  break;
	default:
	  break;
	}
	trans = buffer->getChar();
    }
  buffer->putChar();   //read one extra character
return NULL;
}      


inputStruct* Lexer::getInputStruct()
{
  return s_files.empty() ? last_fileinfo :(inputStruct*)s_files.top();
}
