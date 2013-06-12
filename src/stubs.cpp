#include "token.h"
#include "inputStruct.h"
#include <stack>
#include "buffer.h"
#include "lexerlib.h"

extern int yylex();

/*Please put Drivers and Tester programs below this point
 *The space above is reserved for stubbed functions in the implementation
 */



/*
 * Checks the buffer operations putChar and getChar
 */
void bufferDriver(stack<inputStruct*> s)
{
  char c;
  int counter = 3;
  //checking initializations code
  Buffer* buff = new Buffer(&s);
  char a[1035];
  char b[1035];
  /* for(int i = 0; i < 1035; i++)
    {
      a[i] = buff->getChar();
    }
  
  for(int i = 1034; i >= 0; i--)
    {
      b[i] = buff->putChar();
    }
    */
  /*for(int j = 0; j < 1035; j++)
    if(a[j] != b[j])
      cout<<"("<<a[j]<<","<<b[j];
  //cout<<"("<<a[j]<<","<<b[j]<<")";
  //cout<<endl;
  */
  //checking getChar()
  while((c = buff->getChar()) != EOF)
    {
      cout<<c;
      counter++;
    }
     
  /* //checking putChar at EOF
  cout<<"putChar@EOF="<<buff->putChar()<<endl;
  cout<<"checking 3-4 putback characters"<<endl;
  //checking 3-4 putback characters
  while(counter-- >= 0)
    cout<<"["<<counter<<"]="<<buff->putChar();
  cout<<endl;
  while(counter++ <= 3)
    cout<<"["<<counter<<"]="<<buff->getChar();
  cout<<endl;
  cout<<"checking putChar over the mid buffer"<<endl;
  //checking putChar over the mid buffer
  counter = 1028;
  char after[1028];
  char before[1028];

  while(counter > 0)
    after[--counter] = buff->putChar();
  while(counter < 1028)
    before[counter++] = buff->getChar();
  if(strcmp(after, before) == 0)
    cout<<"putChar()==getChar() across mid buffer"<<endl;
  else
    {
      cout<<"putChar()!=getChar() across mid buffer"<<endl;
      for(int i = 0; i < 2051;i++)
	if(after[i] != before[i])
	  cout<<"["<<i<<"]="<<"("<<after[i]<<","<<before[i]<<")"<<endl;
    }
  
  cout<<"checking putChar at the beginning"<<endl;
  //checking putChar at the beginning
  counter = 2051;
  char after1[2051];
  char before1[2051];

  while(counter > 0)
    after1[--counter] = buff->putChar();
  while(counter < 2051)
    before1[counter++] = buff->getChar();
  if(strcmp(after, before) == 0)
    cout<<"putChar()==getChar() @begining"<<endl;
  else
    {
      cout<<"putChar()!=getChar() @begining"<<endl;
      for(int i = 0; i < 2051; i++)
	if(after1[i] != before1[i])
	  cout<<"["<<i<<"]="<<"("<<after1[i]<<","<<before1[i]<<")"<<endl;

    }  
    */ 
}

/*
 * This is a better test driver. Checks the operations of Keyword class
 */
void hashTableTester(Keywords table, char** testlist, int* testmap, int size)
{
  int error = 0;
  for(int i = 0; i < size; i++)
    {
      if(table.lookupKeyword(testlist[i]) != testmap[i])
	{
	  error++;
	}
    }

  char* nonKeywords[7] = {"Hello", "TOs", "else", "if", "&", "12", "bas234"};
  int error2 = 0;
  for(int i = 0; i < 7; i++)
    {
      if(table.lookupKeyword(nonKeywords[i]))
	{
	  error2++;
	  cout<<table.lookupKeyword(nonKeywords[i])<<endl;
	}
    }
  if(error > 0)
    cout<<"keyword lookup failed for "<<error<<" times"<<endl;
  else
    cout<<"keyword lookup passed successfully"<<endl;
  if(error2 > 0)
    cout<<"non-keyword lookup failed for "<<error2<<" times"<<endl;
  else
    cout<<"non-keyword lookup passed successfully"<<endl;
}

/*
 * Checks the operations of Punctuations class
 */
void hashTableTester(Punctuations table, char** testlist, int* testmap, int size)
{
  int error = 0;
  for(int i = 0; i < size; i++)
    {
      if(table.lookupPunc((char)*testlist[i]) != testmap[i])
	  error++;
    }
 
  char non_punc[11] = "absc3252?_";
  int error2 = 0;
  for(int i = 0; i < 10; i++)
    {
      if(table.lookupPunc(non_punc[i]))
	  error2++;
    }
  if(error > 0)
    cout<<"Punctuations lookup failed for "<<error<<" times"<<endl;
  else
    cout<<"Punctuations lookup passed successfully"<<endl;
  if(error2 > 0)
    cout<<"non-Punctuations lookup failed for "<<error2<<" times"<<endl;
  else
    cout<<"non-Punctuations lookup passed successfully"<<endl;
}

