#ifndef _LEXER_H_
#define _LEXER_H_

#include "config.h"
#include "inputStruct.h"
#include <stack>
#include "lib.h"
#include "lexerlib.h"
#include "buffer.h"


#define NDFA_0  0x00
#define NDFA_1  0x01    //int accept
#define NDFA_2  0x02    //char accept
#define NDFA_3  0x03    //int accept
#define NDFA_4  0x04    //int accept
#define NDFA_5  0x05    //int accept
#define NDFA_6  0x06    //real accept
#define NDFA_7  0x07    //char accept
#define NDFA_8  0x08
#define NDFA_9  0x09
#define NDFA_10 0x0A
#define NDFA_11 0x0B
#define NDFA_12 0x0C    //real accept
#define NDFA_13 0x0D

class Lexer
{
public:
  Lexer(int argc, char* argv[]);   /*takes args from main and sets up the 
				   *environment as well as the files to be 
				   *read
				   */
  ~Lexer();
  Token* GetToken();
  inputStruct* Lexer::getInputStruct();
private:
  HASHTABLE  h_VisitedFilesTable;
  Keywords* keywords;
  Punctuations* punctuations;
  Buffer* buffer; 
  stack<inputStruct*> s_files;	  /*holds the list of files to compile*/
  inputStruct* last_fileinfo;

  Token* getTokenInternal();
  void parseParameters(int argc, char* argv[]);
  void processOptions(const char* option);
  bool isDuplicateFile(const char* filename);
  char* lookupFile(const char* filename);

  Token* process_numeric(char trans);
  Token* process_identifiers();
  Token* process_punctuations(char trans);
  Token* process_strings(char trans);
  Token* process_comments();
};

#endif

