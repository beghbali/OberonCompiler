#include "buffer.h"
#include <iostream>
#include <fstream>
#include <exception>
#include "debug.h"
#include "lib.h"

#undef DEBUG

Buffer::~Buffer()
{
}

Buffer::Buffer(stack<inputStruct*>* s_files)
{
  end = &buffer[SYSTEM_BLOCK_SIZE+1];
  forward = end;      //to triger the correct buffer read
  backward = buffer;
  mid = &buffer[SYSTEM_BLOCK_SIZE/2];
  *end = EOF;
  *mid = EOF;
  lastChar = 'X';    //arbitrary
  files = s_files;
  if(!files->empty())
    currentFile = files->top()->file;

  fillHalf();
}

char Buffer::getChar()
{
  char x = *forward;  
  
  if(*forward == EOF)
    { 
      if(!fillHalf())
	return EOF;     
      x = *forward;
    }
  forward++;

  return x;
} 

char Buffer::putChar()
{
  if(forward == buffer)
    forward = end-1;
  if(*forward == EOF && lastChar == EOF)
    {
      lastChar = 'X';
      return *(forward-1);
    }
  if(*(--forward) == EOF)
    forward--;
 
  return *(forward-1);
}

char* Buffer::getLexeme()
{
  char* lexeme;
  if(forward < backward)          //wraps around
    {
      int temp,temp1;
      temp = end-backward;
      temp1 = forward-buffer;
      lexeme = new char[temp+temp1+2];   //one extra for 'H'|'X' added +'\0'
      memset(lexeme,'\0',temp+temp1+2);
      memcpy(lexeme,backward,temp);
      strncat(lexeme,buffer,temp1);
      
      return lexeme;
    }
  if(backward < mid && forward > mid)
    {
      lexeme = new char[forward-backward+1];   //an implicit 1 from EOF
      memset(lexeme,'\0',forward-backward+1);
      memcpy(lexeme, backward, mid-backward);
      strncat(lexeme,mid+1,forward-mid-1);
 
      return lexeme;
    }

  lexeme = new char[forward-backward+2];
  memset(lexeme, '\0',forward-backward+2);
  strncat(lexeme, backward, forward-backward);

  return lexeme;
}

void Buffer::resetLexeme()
{
  if(forward > buffer)
    backward = forward-1;
  if(*forward == EOF && lastChar == EOF)
    backward = forward;
}

bool Buffer::fillHalf()
{
  static bool parity = false;

  if(lastChar == EOF)
    return false;
 
  if(currentFile->eof() && *forward == EOF)
    {
      if(currentFile != &cin)
      	(dynamic_cast<ifstream*>(files->top()->file))->close();
      if(files->size() > 1)
	files->pop();
      else
	{
	  lastChar = EOF;
	  return false;
	}
    }

  currentFile = files->top()->file;        //pointing to the top file on stack
 
  if(currentFile->eof())
    currentFile->clear();

  if(forward == end)
    {
      currentFile->read(buffer, SYSTEM_BLOCK_SIZE/2);
      forward = buffer;
      buffer[currentFile->gcount()]=EOF;
    }
  else
    {
      if(forward == mid)
	forward++;     //skip EOF
      

      currentFile->read(forward,SYSTEM_BLOCK_SIZE/2);//firstEOF(forward+1)-forward);
      *(forward+currentFile->gcount()) = EOF;
    }

  return true;
}

inline void Buffer::saveContext()
{
  /*  if(currentFile == &cin)
    {
      for(int i = 0; i < (firstEOF(forward)-forward);i++)
	currentFile->unget();
    }*/
  if(lastChar == EOF)
    return;
  else
    currentFile->seekg(-(firstEOF(forward)-forward),ios::cur);
}

void Buffer::resetFile()
{
  saveContext();        //save the context of the current file being read from
  currentFile = files->top()->file;
  lastChar = 'X';
  fillHalf();
}

