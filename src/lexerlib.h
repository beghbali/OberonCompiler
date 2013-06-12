#ifndef _LEXERLIB_H_
#define _LEXERLIB_H_

#include <hash_set>
#include <hash_map>
#include "lib.h"
#include "inputStruct.h"

typedef hash_set<const char*, hash<const char*>, eqstr> HASHTABLE;
typedef hash_map<const char*, char, hash<const char*>, eqstr> HASHMAP;

static inline char* lookup(HASHTABLE table, const char* key)
{
  return (char*)*(table.find(key));
}

static inline char lookup(HASHMAP map, const char* key)
{
  return (char)(map[key]);
}


class Keywords
{
public:
  ~Keywords();
  Keywords(char** keywordlist, int* keywordCodes, int size);
  int lookupKeyword(char* keyword);
  bool isKeyword(char* keyword);
private:
  HASHMAP keywordTable;
};

class Punctuations
{
public:
  ~Punctuations();
  Punctuations(char** punclist, int* puncTypelist, int size);
  int Punctuations::lookupPunc(char punc);
private:
  HASHMAP puncTable;
};

inputStruct* createInputStruct(const char* filen,int linenum, istream* file_p);
 
#endif
