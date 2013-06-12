#include "lexerlib.h"
#include <iostream>
#include <fstream>
#include "errorhandler.h"
#include "config.h"
#include <stdio.h>

/*definitions for members/functions of Keywords class*/

Keywords::~Keywords()
{
}

Keywords::Keywords(char** keywordlist, int* keywordCodes, int size)
{
  for(int i = 0; i < size; i++)
    {
      keywordTable[keywordlist[i]] = (char)(keywordCodes[i]-256);
    }
}


int Keywords::lookupKeyword(char* keyword)
{
  int code = (int)(lookup(keywordTable, keyword)+256);
  return (code == 256 ? NULL : code);
}

bool Keywords::isKeyword(char* keyword)
{
  return lookup(keywordTable, keyword) ? true : false;
}

/*End of definition for Keywords*/


/*definitions for members/functions of Punctuations class*/

Punctuations::~Punctuations()
{
}

Punctuations::Punctuations(char** punclist, int* puncTypelist, int size)
{
  for(int i = 0; i < size; i++)
    {
      puncTable[punclist[i]] = (char)(puncTypelist[i]-256);
    }
}

int Punctuations::lookupPunc(char punc)
{
  char temp[] = {punc,'\0'};
  int code = (int)(lookup(puncTable, temp)+256);
  return (code == 256 ? NULL : code);
}

/*End of definition for Punctuations*/

inputStruct* createInputStruct(const char* filen,int linenum, istream* file_p)
{
  inputStruct* varname; 
  varname = new inputStruct;
  const char* temp;
  
  if(!file_p)
    { 
    ifstream* temp = new ifstream(filen); 
    if(!temp->is_open())
      {
	ERROR(cannotOpenFile, NULL , filen); 
	return NULL;
      }
    else
      varname->file = temp; 
    } 
  else 
    varname->file = file_p; 
  //  temp = strrchr(filen, '/');	/*to remove pathname and get filename*/
  //if(temp)
  //  filen = temp+1;   
  
  varname->filename = (char*)malloc(strlen(filen)+1); 
  strcpy(varname->filename, filen); 
  varname->line = linenum;  
  return varname;
}

