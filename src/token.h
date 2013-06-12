
/*--------------------------------------------------------------------

	token.h

	Defines the token object to be returned by GetToken ()

--------------------------------------------------------------------*/
#ifndef token_h
#define token_h



/*
 *	y.tab.h contains the list of legal values for nCode
 */
#include "y.tab.h"



struct Token
{
	int 		nCode;
	char		csLexeme[81];
};

#endif

