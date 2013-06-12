
# line 3 "oberon.y"
  #include "ASTnode.h"

# line 6 "oberon.y"
typedef union
#ifdef __cplusplus
	YYSTYPE
#endif
 {
    char*        sval;
    int         ival;
    float        fval;
    ASTNode*      AST;
} YYSTYPE;
# define T_ARRAY 257
# define T_BEGIN 258
# define T_BY 259
# define T_CASE 260
# define T_CONST 261
# define T_DIV 262
# define T_DO 263
# define T_ELSE 264
# define T_ELSIF 265
# define T_END 266
# define T_EXIT 267
# define T_FOR 268
# define T_IF 269
# define T_IMPORT 270
# define T_IN 271
# define T_IS 272
# define T_LOOP 273
# define T_MOD 274
# define T_MODULE 275
# define T_NIL 276
# define T_OF 277
# define T_OR 278
# define T_POINTER 279
# define T_PROCEDURE 280
# define T_RECORD 281
# define T_REPEAT 282
# define T_RETURN 283
# define T_THEN 284
# define T_TO 285
# define T_TYPE 286
# define T_UNTIL 287
# define T_VAR 288
# define T_WHILE 289
# define T_WITH 290
# define T_AMPERSAND 291
# define T_ARROW 292
# define T_ASSIGN 293
# define T_BAR 294
# define T_COLON 295
# define T_COMMA 296
# define T_DOTDOT 297
# define T_DOT 298
# define T_EQU 299
# define T_GT 300
# define T_GTE 301
# define T_LBRACE 302
# define T_LBRACKET 303
# define T_LPAREN 304
# define T_LT 305
# define T_LTE 306
# define T_MINUS 307
# define T_NEQ 308
# define T_PLUS 309
# define T_RBRACE 310
# define T_RBRACKET 311
# define T_RPAREN 312
# define T_SEMI 313
# define T_TILDE 314
# define T_SLASH 315
# define T_STAR 316
# define T_BOOLEAN 317
# define T_CHAR 318
# define T_FALSE 319
# define T_INTEGER 320
# define T_NEW 321
# define T_REAL 322
# define T_TRUE 323
# define T_ID 324
# define T_INT_LITERAL 325
# define T_STR_LITERAL 326
# define T_REAL_LITERAL 327
# define T_CHAR_LITERAL 328
# define T_PROGRAM 329
# define T_READ 330
# define T_WRITE 331
# define T_NL 332

# line 95 "oberon.y"
#ifdef __cplusplus
#include <iostream>
#include "assembly.h"
extern ASTNode* ASTree;
extern char* concat(char*, char*);
extern void suppressError();
#endif

#ifdef __STDC__
#include <stdlib.h>
#include <string.h>
#else
#include <malloc.h>
#include <memory.h>
#endif

#include <values.h>

#ifdef __cplusplus

#ifndef yyerror
	void yyerror(const char *);
#endif

#ifndef yylex
#ifdef __EXTERN_C__
	extern "C" { int yylex(void); }
#else
	int yylex(void);
#endif
#endif
	int yyparse(void);

#endif
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
YYSTYPE yylval;
YYSTYPE yyval;
typedef int yytabelem;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
#if YYMAXDEPTH > 0
int yy_yys[YYMAXDEPTH], *yys = yy_yys;
YYSTYPE yy_yyv[YYMAXDEPTH], *yyv = yy_yyv;
#else	/* user does initial allocation */
int *yys;
YYSTYPE *yyv;
#endif
static int yymaxdepth = YYMAXDEPTH;
# define YYERRCODE 256

# line 1565 "oberon.y"




static const yytabelem yyexca[] ={
-1, 1,
	0, -1,
	-2, 0,
-1, 53,
	324, 59,
	-2, 54,
-1, 87,
	264, 136,
	265, 136,
	266, 136,
	287, 136,
	294, 136,
	313, 136,
	-2, 156,
-1, 96,
	277, 108,
	-2, 156,
-1, 128,
	312, 108,
	-2, 156,
-1, 129,
	284, 109,
	-2, 111,
-1, 189,
	310, 172,
	-2, 156,
-1, 255,
	312, 108,
	-2, 156,
	};
# define YYNPROD 208
# define YYLAST 491
static const yytabelem yyact[]={

    62,   185,    80,   122,   204,   121,   320,   270,   118,    86,
    83,    79,   318,   162,    96,    84,    19,    46,    47,   294,
   126,   293,   100,   235,    82,    87,   234,   189,   144,   190,
    18,    81,    85,   223,   220,    17,    98,    99,    97,   188,
   212,    20,    92,    14,   184,   163,    36,   133,   183,    92,
   179,   182,   180,   181,   116,   103,   104,    36,   101,    55,
   102,    30,   100,    90,    23,   171,    92,   117,   347,    50,
   313,   285,    88,    89,   103,   104,   274,   101,    49,   102,
   201,   100,   170,   132,     5,   125,   296,   295,   129,   130,
   131,   252,   103,   104,   262,   101,   138,   102,   143,   100,
   192,   173,   160,   253,   149,   152,   126,   106,    41,    25,
    24,   322,   244,   245,   214,   126,   269,   126,   286,   248,
   254,   302,   248,   126,   288,   281,   263,   229,   159,   282,
   303,   191,   126,   267,   325,   203,   195,   152,    78,   260,
   238,   241,   243,   255,   251,   250,   240,   242,   247,   239,
   246,   247,   122,   246,   121,   152,   147,    53,   127,    28,
   154,   145,   148,    29,   174,    61,   231,   146,    59,   128,
   319,    29,   193,   157,   312,   310,   311,   208,   305,   287,
   228,   227,   228,   304,   214,   209,   206,   206,   112,   297,
   202,   172,    93,    40,    19,    44,   256,   216,   261,   314,
   155,   271,   344,   264,    17,   213,   199,   277,   278,    58,
   272,   273,   341,   339,   206,   335,   309,   205,   143,    20,
   327,    14,   289,   284,   275,    14,   230,   139,   342,   315,
   207,   200,   338,   165,   150,   265,   123,   176,   175,   142,
   119,    95,    94,   177,   136,    11,    12,   109,   164,   151,
    63,     9,    10,   217,   124,   113,   110,    51,   178,    35,
    27,   187,   134,   198,   152,   306,   307,     3,   197,     4,
    21,   308,    22,    60,     2,     8,    13,    56,    57,   115,
   114,     6,   166,     7,   210,    45,    39,    37,   167,    38,
    15,    42,    43,    31,    48,    16,    32,    33,    54,    26,
    52,   107,   108,   222,   215,    77,    75,   105,    76,   140,
    64,   329,   111,   261,   324,    65,   333,    66,    67,   266,
   331,   268,    68,   332,    69,    70,   337,   178,   137,    71,
   334,   336,    72,   135,    73,    74,   141,   120,   186,   258,
   259,   236,   237,   345,   340,   346,   343,   249,   219,    91,
    34,   153,     1,     0,     0,     0,     0,   156,     0,     0,
     0,     0,   158,   196,   161,     0,   169,   168,     0,     0,
     0,     0,     0,     0,     0,     0,   178,   194,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   178,     0,
     0,     0,     0,     0,     0,     0,   211,   218,     0,     0,
     0,   225,   224,     0,     0,     0,   283,   221,   226,     0,
     0,     0,   232,   233,     0,     0,     0,     0,     0,     0,
   292,     0,     0,     0,     0,     0,     0,     0,   330,     0,
     0,     0,   257,     0,     0,     0,     0,   178,     0,     0,
     0,     0,   326,   328,   323,     0,     0,     0,   137,   280,
   276,   279,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   321,     0,   291,   290,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   299,   298,     0,     0,
   317,     0,     0,     0,   316,     0,     0,   300,     0,     0,
   301 };
static const yytabelem yypact[]={

  -245,-10000000,  -245,-10000000,-10000000,  -260,-10000000,-10000000,-10000000,-10000000,
-10000000,  -203,  -204,-10000000,-10000000,-10000000,-10000000,  -133,  -263,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -267,  -267,  -141,   -95,
  -205,  -267,  -267,   -63,  -278,-10000000,  -238,  -147,  -267,  -265,
-10000000,   -61,  -131,  -134,  -258,-10000000,  -243,  -267,-10000000,-10000000,
-10000000,  -206,-10000000,   -95,  -147,  -107,-10000000,-10000000,  -270,  -155,
   -20,  -243,  -181,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -135,  -155,
  -155,  -155,  -258,  -277,-10000000,  -302,-10000000,  -155,  -282,  -304,
  -143,  -136,-10000000,  -209,-10000000,-10000000,  -155,  -144,   -85,  -147,
  -125,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -184,  -211,-10000000,
  -311,-10000000,  -279,   -25,   -67,  -231,  -102,  -212,-10000000,  -275,
-10000000,-10000000,-10000000,  -155,  -213,  -126,  -258,  -155,  -155,-10000000,
   -71,   -32,  -207,  -103,  -258,   -77,   -33,  -118,-10000000,-10000000,
-10000000,  -111,-10000000,-10000000,-10000000,  -282,  -155,-10000000,  -284,-10000000,
   -72,  -112,-10000000,  -311,  -302,  -243,-10000000,  -290,   -25,  -262,
   -95,  -114,-10000000,  -185,   -40,  -258,   -76,-10000000,-10000000,-10000000,
-10000000,  -298,  -301,-10000000,  -159,  -171,-10000000,-10000000,  -161,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -155,  -275,  -155,
-10000000,  -219,-10000000,-10000000,-10000000,-10000000,  -186,   -81,   -21,  -155,
  -258,  -155,  -155,  -190,   -42,  -302,  -258,  -258,  -302,  -304,
  -187,  -182,-10000000,  -243,  -155,  -195,-10000000,  -116,  -188,-10000000,
-10000000,   -44,-10000000,  -225,-10000000,-10000000,-10000000,  -243,  -303,-10000000,
  -305,  -293,  -226,  -227,  -104,-10000000,  -155,  -275,-10000000,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -275,
-10000000,-10000000,-10000000,-10000000,-10000000,  -155,  -191,-10000000,  -180,  -113,
-10000000,  -119,-10000000,-10000000,  -258,  -258,   -78,-10000000,  -120,-10000000,
  -123,  -196,-10000000,   -86,-10000000,-10000000,   -34,  -293,  -293,-10000000,
-10000000,-10000000,-10000000,-10000000,-10000000,-10000000,  -311,  -243,-10000000,  -312,
-10000000,-10000000,-10000000,-10000000,  -128,-10000000,-10000000,  -318,  -275,  -171,
-10000000,  -201,-10000000,-10000000,  -155,  -155,  -293,  -293,   -46,  -155,
  -258,  -155,  -155,-10000000,  -155,  -258,-10000000,-10000000,-10000000,-10000000,
-10000000,  -156,-10000000,-10000000,-10000000,   -50,   -50,-10000000,-10000000,  -293,
-10000000,-10000000,   -27,  -293,   -53,  -155,   -54,   -35,  -155,-10000000,
   -82,-10000000,  -258,-10000000,  -258,  -198,  -293,-10000000 };
static const yytabelem yypgo[]={

     0,   352,   259,   242,   351,   350,   349,   138,   347,   342,
   341,   139,   340,   339,   338,   243,   337,   239,   237,   238,
   164,     8,   336,   249,     7,   244,   335,   334,   333,   332,
   329,   326,   325,   324,   322,   116,   321,   133,   319,   318,
     4,   134,   317,   234,   315,   310,   309,   308,   306,   305,
   250,     0,   197,   304,   241,   192,   260,   303,   253,   247,
   302,   301,   300,   257,   246,   248,   245,   299,   297,   251,
   296,   295,   293,   290,   252,   288,   283,   282,   281,   280,
   255,   279,   278,   277,   276,   275,   269,   274,   267,   240,
   256,   273,   268,   263,   262,   261 };
static const yytabelem yyr1[]={

     0,     1,     1,     1,    88,    87,    87,    86,    86,    86,
    86,    85,    84,    83,    83,    82,    81,    81,    81,    81,
    80,    79,    79,    78,    77,    77,    77,    76,    76,    75,
    75,    74,    74,    73,    72,    91,    72,    72,    71,    70,
    70,    69,    68,    68,    67,    67,    66,    65,    65,    64,
    63,    63,    62,    61,    61,    60,    60,    59,    90,    90,
    58,    58,    57,    57,    57,    57,    57,    56,    56,    55,
    55,    55,    55,    55,    55,    54,    54,    54,    54,    53,
    53,    52,    52,    51,    51,    50,    50,    50,    50,    50,
    50,    50,    50,    50,    50,    50,    50,    50,    50,    50,
    49,    48,    47,    46,    45,    44,    44,    43,    43,    92,
    42,    93,    42,    41,    41,    40,    40,    39,    38,    38,
    37,    36,    36,    35,    35,    34,    33,    32,    31,    31,
    94,    30,    29,    28,    28,    27,    26,    26,    25,    24,
    23,    23,    22,    22,    21,    21,    89,    20,    20,    19,
    19,    18,    17,    17,    16,    16,    16,    15,    15,    15,
    15,    15,    15,    15,    15,    15,    15,    15,    15,    95,
    14,    13,    13,    12,    12,    11,    11,    10,    10,    10,
    10,    10,    10,    10,    10,     9,     9,     9,     8,     8,
     8,     8,     8,     7,     6,     6,     6,     6,     5,     5,
     5,     4,     4,     3,     3,     2,     2,     2 };
static const yytabelem yyr2[]={

     0,     5,     3,     3,    15,     5,     3,     3,     3,     3,
     3,     3,    19,     3,     1,     7,     3,     7,     7,    11,
     5,     5,     1,     3,     7,     7,     1,     5,     5,     3,
     3,     3,     3,     5,    11,     1,    13,     1,     5,    11,
     1,     5,     5,     1,    11,     1,    19,     5,     1,    11,
     3,     1,     9,     3,     1,     3,     7,     9,     3,     1,
     3,     7,     5,     5,     3,     3,     1,    13,     1,     3,
     3,     9,     9,     7,     5,     3,     3,     3,     3,     3,
     7,     7,     1,     3,     7,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
     9,     5,     5,     3,     7,     3,     9,     3,     1,     1,
    17,     1,    17,    11,     1,     5,     1,    13,     3,     7,
     7,     3,     7,     3,     7,    11,     9,    21,     5,     1,
     1,     9,     9,     7,    11,     3,     3,     5,     7,     3,
     3,     7,     3,     7,    11,     5,     3,     7,     3,     7,
     3,     3,     3,     3,     3,     3,     1,     3,     9,     3,
     3,     3,     3,     3,     3,     3,     3,     7,     5,     3,
     7,     3,     1,     3,     7,     3,     7,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     9,     5,     7,     3,     3,     7,
     5,     7,     1,     3,     7,     3,     5,     5 };
static const yytabelem yychk[]={

-10000000,    -1,   -87,   -88,   -86,   329,   -78,   -76,   -85,   -69,
   -74,   -66,   -64,   -84,   288,   -73,   -71,   280,   275,   261,
   286,   -88,   -86,   324,   313,   313,   -67,   -56,   292,   304,
   324,   -72,   -70,   -68,    -5,    -2,   324,    -2,   -56,   -90,
   288,   313,    -2,    -2,   258,   -69,   295,   296,    -2,   316,
   307,   -63,   -62,   304,    -2,   324,   -83,   -82,   270,   299,
   -91,   299,   -51,   -50,   -45,   -44,   -42,   -39,   -34,   -33,
   -32,   -30,   -29,   -27,   -26,   -48,   -47,   -49,    -7,   269,
   260,   289,   282,   268,   273,   290,   267,   283,   330,   331,
   321,    -6,   324,   -55,    -3,   -54,   257,   281,   279,   280,
   324,   320,   322,   317,   318,    -2,   313,   -61,   -60,   -59,
   -90,   -63,   295,   -80,   -79,   -81,   324,   -24,   -21,   -89,
   -16,   309,   307,   256,   -55,   266,   313,   293,   304,   -21,
   -21,   -21,   -51,   324,   -94,   -28,   -25,    -3,   -21,    -7,
   -46,   -22,   -17,   -21,   332,   304,   303,   292,   298,   313,
   -43,   -23,   -21,    -4,   304,   285,   -63,   298,   -80,   312,
   313,   -58,   324,   324,   -65,   258,   -77,   -75,   -74,   -69,
   313,   296,   293,   313,   -20,   -19,   -18,   -15,    -7,   325,
   327,   328,   326,   323,   319,   276,   -14,   -95,   314,   302,
   304,   -24,   313,   298,   -50,   -21,   -43,   -92,   -93,   277,
   263,   287,   293,   -51,   -40,   294,   264,   263,   295,   296,
    -7,   -23,   324,   277,   296,   -53,   -52,   -58,    -3,   -55,
   324,   -65,   -57,   295,    -3,   -54,   -59,   295,   296,   312,
   266,   -51,   -66,   -64,   324,   324,   -10,    -9,   299,   308,
   305,   300,   306,   301,   271,   272,   309,   307,   278,    -8,
   316,   315,   262,   274,   291,   304,   -21,   -15,   -13,   -12,
   -11,   -21,   313,   312,   284,   256,   -38,   -37,   -36,   -35,
   -24,   -51,   -21,   -21,   266,   266,   -25,   -51,   -51,    -3,
   -17,   312,   311,   -55,   -21,   266,   313,   295,   312,   266,
    -3,   -54,   -55,   324,   324,   313,   313,   293,   -89,   -19,
   -18,   -43,   312,   310,   296,   297,   -51,   -51,   -40,   294,
   295,   296,   297,   266,   285,   263,   -52,   -55,   324,   298,
   324,   -20,   312,   -11,   -21,   -41,   -41,   266,   -37,   -51,
   -35,   -24,   -21,   -51,   -40,   265,   -40,   -31,   259,   266,
   -21,   266,   263,   -24,   284,   -51,   -51,   266 };
static const yytabelem yydef[]={

     0,    -2,     3,     2,     6,     0,     7,     8,     9,    10,
    23,     0,     0,    11,    45,    31,    32,    68,     0,    37,
    40,     1,     5,    43,    27,    28,    41,     0,    68,    59,
     0,    33,    38,     0,     0,   198,   205,    51,     0,     0,
    58,    14,    35,     0,    99,    42,     0,     0,   200,   206,
   207,     0,    50,    -2,    51,     0,    22,    13,     0,   156,
     0,     0,     0,    83,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    95,    96,    97,    98,   105,   156,
   156,   156,    99,     0,   130,     0,   135,    -2,     0,   156,
     0,   193,   197,     0,    69,    70,    -2,   202,     0,    51,
   203,    75,    76,    77,    78,   199,    22,     0,    53,    55,
     0,    49,     0,    48,    26,     0,    16,     0,   139,     0,
   146,   154,   155,   156,     0,     0,    99,   156,    -2,    -2,
     0,     0,     0,     0,    99,   116,     0,     0,   137,   101,
   102,   103,   142,   152,   153,     0,   156,   195,     0,    44,
     0,   107,   140,    82,     0,     0,    74,     0,    48,    66,
    59,     0,    60,     0,     0,    99,    20,    21,    29,    30,
    15,     0,     0,    34,   145,   148,   150,   151,   157,   159,
   160,   161,   162,   163,   164,   165,   166,   156,     0,    -2,
   169,     0,    39,     4,    84,   104,     0,     0,     0,   156,
    99,   156,   156,     0,     0,     0,    99,    99,     0,   156,
     0,     0,   196,     0,   156,     0,    79,     0,     0,    73,
   204,     0,    52,     0,    64,    65,    56,     0,     0,    67,
     0,    47,     0,     0,    18,    17,   156,     0,   177,   178,
   179,   180,   181,   182,   183,   184,   185,   186,   187,     0,
   188,   189,   190,   191,   192,    -2,     0,   168,     0,   171,
   173,   175,    36,   106,    99,    99,   116,   118,     0,   121,
   123,     0,   126,     0,   131,   132,     0,   115,   133,   138,
   143,   100,   194,    71,   141,    72,    82,     0,   201,     0,
    62,    63,    57,    61,     0,    24,    25,     0,     0,   147,
   149,     0,   167,   170,   156,   156,   114,   114,     0,   156,
    99,   156,   156,   125,   156,    99,    80,    81,    46,    12,
    19,   144,   158,   174,   176,   116,   116,   117,   119,   120,
   122,   124,   129,   134,     0,   156,     0,     0,   156,   110,
     0,   112,    99,   128,    99,     0,   113,   127 };
typedef struct
#ifdef __cplusplus
	yytoktype
#endif
{ char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"T_ARRAY",	257,
	"T_BEGIN",	258,
	"T_BY",	259,
	"T_CASE",	260,
	"T_CONST",	261,
	"T_DIV",	262,
	"T_DO",	263,
	"T_ELSE",	264,
	"T_ELSIF",	265,
	"T_END",	266,
	"T_EXIT",	267,
	"T_FOR",	268,
	"T_IF",	269,
	"T_IMPORT",	270,
	"T_IN",	271,
	"T_IS",	272,
	"T_LOOP",	273,
	"T_MOD",	274,
	"T_MODULE",	275,
	"T_NIL",	276,
	"T_OF",	277,
	"T_OR",	278,
	"T_POINTER",	279,
	"T_PROCEDURE",	280,
	"T_RECORD",	281,
	"T_REPEAT",	282,
	"T_RETURN",	283,
	"T_THEN",	284,
	"T_TO",	285,
	"T_TYPE",	286,
	"T_UNTIL",	287,
	"T_VAR",	288,
	"T_WHILE",	289,
	"T_WITH",	290,
	"T_AMPERSAND",	291,
	"T_ARROW",	292,
	"T_ASSIGN",	293,
	"T_BAR",	294,
	"T_COLON",	295,
	"T_COMMA",	296,
	"T_DOTDOT",	297,
	"T_DOT",	298,
	"T_EQU",	299,
	"T_GT",	300,
	"T_GTE",	301,
	"T_LBRACE",	302,
	"T_LBRACKET",	303,
	"T_LPAREN",	304,
	"T_LT",	305,
	"T_LTE",	306,
	"T_MINUS",	307,
	"T_NEQ",	308,
	"T_PLUS",	309,
	"T_RBRACE",	310,
	"T_RBRACKET",	311,
	"T_RPAREN",	312,
	"T_SEMI",	313,
	"T_TILDE",	314,
	"T_SLASH",	315,
	"T_STAR",	316,
	"T_BOOLEAN",	317,
	"T_CHAR",	318,
	"T_FALSE",	319,
	"T_INTEGER",	320,
	"T_NEW",	321,
	"T_REAL",	322,
	"T_TRUE",	323,
	"T_ID",	324,
	"T_INT_LITERAL",	325,
	"T_STR_LITERAL",	326,
	"T_REAL_LITERAL",	327,
	"T_CHAR_LITERAL",	328,
	"T_PROGRAM",	329,
	"T_READ",	330,
	"T_WRITE",	331,
	"T_NL",	332,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
	"Program : DeclarationsSection MainStmtsSection",
	"Program : MainStmtsSection",
	"Program : DeclarationsSection",
	"MainStmtsSection : T_PROGRAM T_ID VarDeclList2 T_BEGIN StmtList T_END T_DOT",
	"DeclarationsSection : DeclarationsSection DeclarationList",
	"DeclarationsSection : DeclarationList",
	"DeclarationList : CTDeclList",
	"DeclarationList : ProcDeclList2",
	"DeclarationList : ModuleList",
	"DeclarationList : VarDeclList",
	"ModuleList : Module",
	"Module : T_MODULE T_ID T_SEMI OptImportDecl DeclSeq OptStmts T_END T_ID T_DOT",
	"OptImportDecl : ImportDecl",
	"OptImportDecl : /* empty */",
	"ImportDecl : T_IMPORT ImportList T_SEMI",
	"ImportList : T_ID",
	"ImportList : T_ID T_ASSIGN T_ID",
	"ImportList : ImportList T_COMMA T_ID",
	"ImportList : ImportList T_COMMA T_ID T_ASSIGN T_ID",
	"DeclSeq : CVTDeclList ProcDeclList",
	"CVTDeclList : CVTDeclList CVTDecl",
	"CVTDeclList : /* empty */",
	"CTDeclList : CTDecl",
	"ProcDeclList : ProcDeclList ProcDecl T_SEMI",
	"ProcDeclList : ProcDeclList FwdProcDecl T_SEMI",
	"ProcDeclList : /* empty */",
	"ProcDeclList2 : ProcDecl T_SEMI",
	"ProcDeclList2 : FwdProcDecl T_SEMI",
	"CVTDecl : CTDecl",
	"CVTDecl : VarDeclList",
	"CTDecl : ConstDeclList",
	"CTDecl : TypeDeclList",
	"ConstDeclList : T_CONST ConstDecl",
	"ConstDecl : ConstDecl IdentDef T_EQU ConstExpr T_SEMI",
	"ConstDecl : ConstDecl IdentDef",
	"ConstDecl : ConstDecl IdentDef error ConstExpr T_SEMI",
	"ConstDecl : /* empty */",
	"TypeDeclList : T_TYPE TypeDecl",
	"TypeDecl : TypeDecl IdentDef T_EQU Type T_SEMI",
	"TypeDecl : /* empty */",
	"VarDeclList : T_VAR VarDecl",
	"VarDeclList2 : VarDeclList2 VarDeclList",
	"VarDeclList2 : /* empty */",
	"VarDecl : VarDecl IdentList T_COLON Type T_SEMI",
	"VarDecl : /* empty */",
	"ProcDecl : T_PROCEDURE OptReceiver IdentDef OptFormalParams T_SEMI DeclSeq OptStmts T_END T_ID",
	"OptStmts : T_BEGIN StmtList",
	"OptStmts : /* empty */",
	"FwdProcDecl : T_PROCEDURE T_ARROW OptReceiver IdentDef OptFormalParams",
	"OptFormalParams : FormalParams",
	"OptFormalParams : /* empty */",
	"FormalParams : T_LPAREN OptParamList T_RPAREN OptReturnType",
	"OptParamList : ParamList",
	"OptParamList : /* empty */",
	"ParamList : ParamDecl",
	"ParamList : ParamList T_SEMI ParamDecl",
	"ParamDecl : OptVar IdList T_COLON Type",
	"OptVar : T_VAR",
	"OptVar : /* empty */",
	"IdList : T_ID",
	"IdList : IdList T_COMMA T_ID",
	"OptReturnType : T_COLON QualIdent",
	"OptReturnType : T_COLON BasicType",
	"OptReturnType : QualIdent",
	"OptReturnType : BasicType",
	"OptReturnType : /* empty */",
	"OptReceiver : T_LPAREN OptVar T_ID T_COLON T_ID T_RPAREN",
	"OptReceiver : /* empty */",
	"Type : QualIdent",
	"Type : BasicType",
	"Type : T_ARRAY OptExprList T_OF Type",
	"Type : T_RECORD OptQualIdent FieldsList T_END",
	"Type : T_POINTER T_TO Type",
	"Type : T_PROCEDURE OptFormalParams",
	"BasicType : T_INTEGER",
	"BasicType : T_REAL",
	"BasicType : T_BOOLEAN",
	"BasicType : T_CHAR",
	"FieldsList : FieldList",
	"FieldsList : FieldsList T_SEMI FieldList",
	"FieldList : IdList T_COLON Type",
	"FieldList : /* empty */",
	"StmtList : Stmt",
	"StmtList : StmtList T_SEMI Stmt",
	"Stmt : AssignStmt",
	"Stmt : ProcCall",
	"Stmt : IfStmt",
	"Stmt : CaseStmt",
	"Stmt : WhileStmt",
	"Stmt : RepeatStmt",
	"Stmt : ForStmt",
	"Stmt : LoopStmt",
	"Stmt : WithStmt",
	"Stmt : ExitStmt",
	"Stmt : ReturnStmt",
	"Stmt : InputStmt",
	"Stmt : OutputStmt",
	"Stmt : NewStmt",
	"Stmt : /* empty */",
	"NewStmt : T_NEW T_LPAREN Designator T_RPAREN",
	"InputStmt : T_READ Designator",
	"OutputStmt : T_WRITE OutputItems",
	"OutputItems : ExprList2",
	"AssignStmt : Designator T_ASSIGN Expr",
	"ProcCall : Designator",
	"ProcCall : Designator T_LPAREN OptExprList T_RPAREN",
	"OptExprList : ExprList",
	"OptExprList : /* empty */",
	"IfStmt : T_IF Expr",
	"IfStmt : T_IF Expr T_THEN StmtList OptElsifs OptElse T_END",
	"IfStmt : T_IF Expr",
	"IfStmt : T_IF Expr error StmtList OptElsifs OptElse T_END",
	"OptElsifs : OptElsifs T_ELSIF Expr T_THEN StmtList",
	"OptElsifs : /* empty */",
	"OptElse : T_ELSE StmtList",
	"OptElse : /* empty */",
	"CaseStmt : T_CASE Expr T_OF CaseList OptElse T_END",
	"CaseList : Case",
	"CaseList : CaseList T_BAR Case",
	"Case : CaseLabelsList T_COLON StmtList",
	"CaseLabelsList : CaseLabels",
	"CaseLabelsList : CaseLabelsList T_COMMA CaseLabels",
	"CaseLabels : ConstExpr",
	"CaseLabels : ConstExpr T_DOTDOT ConstExpr",
	"WhileStmt : T_WHILE Expr T_DO StmtList T_END",
	"RepeatStmt : T_REPEAT StmtList T_UNTIL Expr",
	"ForStmt : T_FOR T_ID T_ASSIGN Expr T_TO Expr OptBy T_DO StmtList T_END",
	"OptBy : T_BY ConstExpr",
	"OptBy : /* empty */",
	"LoopStmt : T_LOOP",
	"LoopStmt : T_LOOP StmtList T_END",
	"WithStmt : T_WITH GuardList OptElse T_END",
	"GuardList : Guard T_DO StmtList",
	"GuardList : GuardList T_BAR Guard T_DO StmtList",
	"ExitStmt : T_EXIT",
	"ReturnStmt : T_RETURN",
	"ReturnStmt : T_RETURN Expr",
	"Guard : QualIdent T_COLON QualIdent",
	"ConstExpr : Expr",
	"ExprList : Expr",
	"ExprList : ExprList T_COMMA Expr",
	"ExprList2 : Exprk",
	"ExprList2 : ExprList2 T_COMMA Exprk",
	"Expr : Expr11 Expr1 Relation Expr11 Expr1",
	"Expr : Expr11 Expr1",
	"Expr11 : OptSign",
	"Expr1 : Expr1 AddOp Expr2",
	"Expr1 : Expr2",
	"Expr2 : Expr2 MulOp Expr3",
	"Expr2 : Expr3",
	"Expr3 : Factor",
	"Exprk : Expr",
	"Exprk : T_NL",
	"OptSign : T_PLUS",
	"OptSign : T_MINUS",
	"OptSign : /* empty */",
	"Factor : Designator",
	"Factor : Designator T_LPAREN OptExprList T_RPAREN",
	"Factor : T_INT_LITERAL",
	"Factor : T_REAL_LITERAL",
	"Factor : T_CHAR_LITERAL",
	"Factor : T_STR_LITERAL",
	"Factor : T_TRUE",
	"Factor : T_FALSE",
	"Factor : T_NIL",
	"Factor : Set",
	"Factor : Lparen Expr T_RPAREN",
	"Factor : T_TILDE Factor",
	"Lparen : T_LPAREN",
	"Set : T_LBRACE OptElementList T_RBRACE",
	"OptElementList : ElementList",
	"OptElementList : /* empty */",
	"ElementList : Element",
	"ElementList : ElementList T_COMMA Element",
	"Element : Expr",
	"Element : Expr T_DOTDOT Expr",
	"Relation : T_EQU",
	"Relation : T_NEQ",
	"Relation : T_LT",
	"Relation : T_GT",
	"Relation : T_LTE",
	"Relation : T_GTE",
	"Relation : T_IN",
	"Relation : T_IS",
	"AddOp : T_PLUS",
	"AddOp : T_MINUS",
	"AddOp : T_OR",
	"MulOp : T_STAR",
	"MulOp : T_SLASH",
	"MulOp : T_DIV",
	"MulOp : T_MOD",
	"MulOp : T_AMPERSAND",
	"Designator : Designator2",
	"Designator2 : Designator2 T_LBRACKET ExprList T_RBRACKET",
	"Designator2 : Designator2 T_ARROW",
	"Designator2 : Designator2 T_DOT T_ID",
	"Designator2 : T_ID",
	"IdentList : IdentDef",
	"IdentList : IdentList T_COMMA IdentDef",
	"IdentList : IdentList IdentDef",
	"OptQualIdent : T_LPAREN QualIdent T_RPAREN",
	"OptQualIdent : /* empty */",
	"QualIdent : T_ID",
	"QualIdent : T_ID T_DOT T_ID",
	"IdentDef : T_ID",
	"IdentDef : T_ID T_STAR",
	"IdentDef : T_ID T_MINUS",
};
#endif /* YYDEBUG */
# line	1 "/usr/ccs/bin/yaccpar"
/*
 * Copyright (c) 1993 by Sun Microsystems, Inc.
 */

#pragma ident	"@(#)yaccpar	6.14	97/01/16 SMI"

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	return(0)
#define YYABORT		return(1)
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#define YYNEW(type)	malloc(sizeof(type) * yynewmax)
#define YYCOPY(to, from, type) \
	(type *) memcpy(to, (char *) from, yymaxdepth * sizeof (type))
#define YYENLARGE( from, type) \
	(type *) realloc((char *) from, yynewmax * sizeof(type))
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-10000000)

/*
** global variables used by the parser
*/
YYSTYPE *yypv;			/* top of value stack */
int *yyps;			/* top of state stack */

int yystate;			/* current state */
int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */
int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */



#ifdef YYNMBCHARS
#define YYLEX()		yycvtok(yylex())
/*
** yycvtok - return a token if i is a wchar_t value that exceeds 255.
**	If i<255, i itself is the token.  If i>255 but the neither 
**	of the 30th or 31st bit is on, i is already a token.
*/
#if defined(__STDC__) || defined(__cplusplus)
int yycvtok(int i)
#else
int yycvtok(i) int i;
#endif
{
	int first = 0;
	int last = YYNMBCHARS - 1;
	int mid;
	wchar_t j;

	if(i&0x60000000){/*Must convert to a token. */
		if( yymbchars[last].character < i ){
			return i;/*Giving up*/
		}
		while ((last>=first)&&(first>=0)) {/*Binary search loop*/
			mid = (first+last)/2;
			j = yymbchars[mid].character;
			if( j==i ){/*Found*/ 
				return yymbchars[mid].tvalue;
			}else if( j<i ){
				first = mid + 1;
			}else{
				last = mid -1;
			}
		}
		/*No entry in the table.*/
		return i;/* Giving up.*/
	}else{/* i is already a token. */
		return i;
	}
}
#else/*!YYNMBCHARS*/
#define YYLEX()		yylex()
#endif/*!YYNMBCHARS*/

/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
#if defined(__STDC__) || defined(__cplusplus)
int yyparse(void)
#else
int yyparse()
#endif
{
	register YYSTYPE *yypvt = 0;	/* top of value stack for $vars */

#if defined(__cplusplus) || defined(lint)
/*
	hacks to please C++ and lint - goto's inside
	switch should never be executed
*/
	static int __yaccpar_lint_hack__ = 0;
	switch (__yaccpar_lint_hack__)
	{
		case 1: goto yyerrlab;
		case 2: goto yynewstate;
	}
#endif

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

#if YYMAXDEPTH <= 0
	if (yymaxdepth <= 0)
	{
		if ((yymaxdepth = YYEXPAND(0)) <= 0)
		{
			yyerror("yacc initialization error");
			YYABORT;
		}
	}
#endif

	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */
	goto yystack;	/* moved from 6 lines above to here to please C++ */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			/*
			** reallocate and recover.  Note that pointers
			** have to be reset, or bad things will happen
			*/
			int yyps_index = (yy_ps - yys);
			int yypv_index = (yy_pv - yyv);
			int yypvt_index = (yypvt - yyv);
			int yynewmax;
#ifdef YYEXPAND
			yynewmax = YYEXPAND(yymaxdepth);
#else
			yynewmax = 2 * yymaxdepth;	/* double table size */
			if (yymaxdepth == YYMAXDEPTH)	/* first time growth */
			{
				char *newyys = (char *)YYNEW(int);
				char *newyyv = (char *)YYNEW(YYSTYPE);
				if (newyys != 0 && newyyv != 0)
				{
					yys = YYCOPY(newyys, yys, int);
					yyv = YYCOPY(newyyv, yyv, YYSTYPE);
				}
				else
					yynewmax = 0;	/* failed */
			}
			else				/* not first time */
			{
				yys = YYENLARGE(yys, int);
				yyv = YYENLARGE(yyv, YYSTYPE);
				if (yys == 0 || yyv == 0)
					yynewmax = 0;	/* failed */
			}
#endif
			if (yynewmax <= yymaxdepth)	/* tables not expanded */
			{
				yyerror( "yacc stack overflow" );
				YYABORT;
			}
			yymaxdepth = yynewmax;

			yy_ps = yys + yyps_index;
			yy_pv = yyv + yypv_index;
			yypvt = yyv + yypvt_index;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			printf( "Received token " );
			if ( yychar == 0 )
				printf( "end-of-file\n" );
			else if ( yychar < 0 )
				printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = YYLEX() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				printf( "Received token " );
				if ( yychar == 0 )
					printf( "end-of-file\n" );
				else if ( yychar < 0 )
					printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register const int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
			skip_init:
				yynerrs++;
				/* FALLTHRU */
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					printf( "Error recovery discards " );
					if ( yychar == 0 )
						printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 1:
# line 199 "oberon.y"
{
  ASTree = new ASTNode(NULL, AST_Program, 2);
  ASTree->addChild(yypvt[-1].AST);
  ASTree->addChild(yypvt[-0].AST);
} break;
case 2:
# line 205 "oberon.y"
{
  ASTree = new ASTNode(NULL, AST_Program, 1);
  ASTree->addChild(yypvt[-0].AST);
} break;
case 3:
# line 210 "oberon.y"
{
  ASTree = new ASTNode(NULL, AST_Program, 1);
  ASTree->addChild(yypvt[-0].AST);
} break;
case 4:
# line 220 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_MainStmtsSection, 3);
  yyval.AST->addChild(yypvt[-5].sval, AST_ID);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-2].AST);
} break;
case 5:
# line 230 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_DeclarationsSection, 2);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 6:
# line 236 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_DeclarationsSection, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 7:
# line 243 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_DeclarationList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 8:
# line 248 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_DeclarationList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 9:
# line 253 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_DeclarationList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 10:
# line 258 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_DeclarationList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 11:
# line 265 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ModuleList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 12:
# line 274 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Module, 5);
  yyval.AST->addChild(yypvt[-7].sval, AST_ID);
  yyval.AST->addChild(yypvt[-5].AST);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].sval, AST_ID);
} break;
case 13:
# line 286 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptImportDecl, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 14:
# line 291 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 15:
# line 298 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ImportDecl, 1);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 16:
# line 306 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ImportList,1);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 17:
# line 311 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ImportList, 2);
  yyval.AST->addChild(yypvt[-2].sval, AST_ID);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 18:
# line 317 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ImportList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 19:
# line 323 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ImportList, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-2].sval, AST_ID);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 20:
# line 333 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_DeclSeq, 2);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 21:
# line 342 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CVTDeclList, 2);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 22:
# line 348 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 23:
# line 354 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CTDeclList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 24:
# line 361 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ProcDeclList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 25:
# line 367 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ProcDeclList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 26:
# line 373 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 27:
# line 379 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ProcDeclList2, 1);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 28:
# line 384 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ProcDeclList2, 1);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 29:
# line 391 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CVTDecl, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 30:
# line 396 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CVTDecl, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 31:
# line 403 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CTDecl, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 32:
# line 408 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CTDecl, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 33:
# line 415 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ConstDeclList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 34:
# line 423 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ConstDecl, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 35:
# line 429 "oberon.y"
{suppressError();} break;
case 36:
# line 430 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ConstDecl, 3);
  yyval.AST->addChild(yypvt[-5].AST);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  yyerror("missing = in constant declaration.");
} break;
case 37:
# line 438 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 38:
# line 445 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_TypeDeclList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 39:
# line 453 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_TypeDecl, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 40:
# line 460 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 41:
# line 467 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_VarDeclList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 42:
# line 474 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_VarDeclList2, 2);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 43:
# line 480 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 44:
# line 486 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_VarDecl, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 45:
# line 493 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 46:
# line 502 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ProcDecl, 6);
  yyval.AST->addChild(yypvt[-7].AST);
  yyval.AST->addChild(yypvt[-6].AST);
  yyval.AST->addChild(yypvt[-5].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 47:
# line 515 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptStmts, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 48:
# line 520 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 49:
# line 527 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_FwdProcDecl, 3);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 50:
# line 537 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptFormalParams, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 51:
# line 542 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 52:
# line 549 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_FormalParams, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 53:
# line 558 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptParamList, 1);
  yyval.AST->addChild(yypvt[-0].AST); 
} break;
case 54:
# line 563 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 55:
# line 570 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ParamList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 56:
# line 575 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ParamList, 1);
  yyval.AST->addChildrenOf(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
  delete yypvt[-2].AST;
} break;
case 57:
# line 585 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ParamDecl, 3);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 58:
# line 595 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptVar, 0);
} break;
case 59:
# line 599 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 60:
# line 606 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IdList, 1);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 61:
# line 611 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IdList, 1);
  yyval.AST->addChildrenOf(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
  delete yypvt[-2].AST;
} break;
case 62:
# line 621 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptReturnType, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 63:
# line 626 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptReturnType, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 64:
# line 631 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptReturnType, 1);
  yyval.AST->addChild(yypvt[-0].AST);
  yyerror("missing : in procedure declaration.");
} break;
case 65:
# line 637 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptReturnType, 1);
  yyval.AST->addChild(yypvt[-0].AST);
  yyerror("missing : in procedure declaration.");
} break;
case 66:
# line 643 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 67:
# line 650 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptReceiver, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-3].sval, AST_ID);
  yyval.AST->addChild(yypvt[-1].sval, AST_ID);
} break;
case 68:
# line 657 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 69:
# line 664 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Type, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 70:
# line 669 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Type, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 71:
# line 674 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Type, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 72:
# line 680 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Type, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 73:
# line 686 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Type, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 74:
# line 691 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Type, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 75:
# line 699 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_BasicType | INTEGER, 1);
  yyval.AST->addChild(new ASTNode(new TypeSym(yypvt[-0].sval, TypeValues::INTEGER_TYPE), notype));
} break;
case 76:
# line 704 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_BasicType | REAL, 1);
  yyval.AST->addChild(new ASTNode(new TypeSym(yypvt[-0].sval, TypeValues::REAL_TYPE), notype));
} break;
case 77:
# line 709 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_BasicType | BOOLEAN, 1);
  yyval.AST->addChild(new ASTNode(new TypeSym(yypvt[-0].sval, TypeValues::BOOLEAN_TYPE), notype));
} break;
case 78:
# line 714 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_BasicType | CHAR, 1);
  yyval.AST->addChild(new ASTNode(new TypeSym(yypvt[-0].sval, TypeValues::CHAR_TYPE), notype));
} break;
case 79:
# line 722 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_FieldsList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 80:
# line 727 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_FieldsList, 1);
  yyval.AST->addChildrenOf(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
  delete yypvt[-2].AST;
} break;
case 81:
# line 737 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_FieldList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 82:
# line 743 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 83:
# line 750 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_StmtList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 84:
# line 755 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_StmtList,2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 85:
# line 764 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
  Assembly::getNextNumber(-1);
} break;
case 86:
# line 770 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 87:
# line 775 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 88:
# line 780 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 89:
# line 785 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 90:
# line 790 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 91:
# line 795 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 92:
# line 800 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 93:
# line 805 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 94:
# line 810 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 95:
# line 815 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 96:
# line 820 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 97:
# line 825 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 98:
# line 830 "oberon.y"
{
   yyval.AST = new ASTNode(NULL, AST_Stmt, 1);
   yyval.AST->addChild(yypvt[-0].AST);
} break;
case 99:
# line 835 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 100:
# line 841 "oberon.y"
{
    yyval.AST = new ASTNode(NULL, AST_NewStmt, 1);
    yyval.AST->addChild(yypvt[-1].AST);
} break;
case 101:
# line 848 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_InputStmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 102:
# line 855 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OutputStmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 103:
# line 862 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OutputItems, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 104:
# line 869 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_AssignStmt, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
  Assembly::genAssignStmt(yypvt[-2].AST->getName(),yypvt[-0].AST->getName());
} break;
case 105:
# line 879 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ProcCall, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 106:
# line 884 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ProcCall, 2);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 107:
# line 893 "oberon.y"
{
  yyval.AST = yypvt[-0].AST;
} break;
case 108:
# line 897 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 109:
# line 903 "oberon.y"
{Assembly::genIFtop(yypvt[-0].AST->getName());} break;
case 110:
# line 904 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IfStmt, 4);
  yyval.AST->addChild(yypvt[-6].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  Assembly::getIFbottom();
} break;
case 111:
# line 913 "oberon.y"
{suppressError();Assembly::genIFtop(yypvt[-0].AST->getName());} break;
case 112:
# line 914 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IfStmt, 4);
  yyval.AST->addChild(yypvt[-6].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  Assembly::getIFbottom();
  yyerror("missing THEN in IF statement.");
} break;
case 113:
# line 927 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptElsifs, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 114:
# line 934 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 115:
# line 941 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptElse, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 116:
# line 946 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 117:
# line 953 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CaseStmt, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 118:
# line 963 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CaseList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 119:
# line 968 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CaseList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 120:
# line 977 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Case, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 121:
# line 986 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CaseLabelsList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 122:
# line 991 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CaseLabelsList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 123:
# line 1000 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CaseLabels, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 124:
# line 1005 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_CaseLabels, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 125:
# line 1014 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_WhileStmt, 2);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 126:
# line 1023 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_RepeatStmt, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 127:
# line 1033 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ForStmt, 5);
  yyval.AST->addChild(yypvt[-8].sval, AST_ID);
  yyval.AST->addChild(yypvt[-6].AST);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 128:
# line 1045 "oberon.y"
{
  yyval.AST = yypvt[-0].AST;
} break;
case 129:
# line 1049 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 130:
# line 1055 "oberon.y"
{Assembly::genLoopTop();} break;
case 131:
# line 1056 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_LoopStmt, 1);
  yyval.AST->addChild(yypvt[-1].AST);
  Assembly::genLoopBottom();
} break;
case 132:
# line 1065 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_WithStmt, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 133:
# line 1074 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_GuardList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 134:
# line 1080 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_GuardList, 3);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 135:
# line 1090 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ExitStmt, 0);
  Assembly::genExitStmt();
} break;
case 136:
# line 1098 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ReturnStmt, 0);
} break;
case 137:
# line 1102 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ReturnStmt, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 138:
# line 1110 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Guard, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 139:
# line 1119 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ConstExpr, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 140:
# line 1127 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ExprList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 141:
# line 1132 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ExprList, 1);
  yyval.AST->addChildrenOf(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
  delete yypvt[-2].AST;
} break;
case 142:
# line 1141 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ExprList2, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 143:
# line 1146 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ExprList2, 1);
  yyval.AST->addChildrenOf(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
  delete yypvt[-2].AST;
} break;
case 144:
# line 1155 "oberon.y"
{
  yyval.AST = new ASTNode(Assembly::genIntegerExpr(yypvt[-3].AST->getName(),yypvt[-2].AST->getName(),yypvt[-0].AST->getName()), AST_Expr, 5);
  yyval.AST->addChild(yypvt[-4].AST);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 145:
# line 1164 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_Expr, 2);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 146:
# line 1172 "oberon.y"
{
  yyval.AST = yypvt[-0].AST;
  Assembly::setSeenOpSign(yypvt[-0].AST?yypvt[-0].AST->getName():(char*)"");
} break;
case 147:
# line 1179 "oberon.y"
{
  yyval.AST =  new ASTNode(Assembly::genIntegerExpr(yypvt[-2].AST->getName(),yypvt[-1].AST->getName(),yypvt[-0].AST->getName()), AST_Expr1, 3);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 148:
# line 1187 "oberon.y"
{
  yyval.AST =  new ASTNode(yypvt[-0].AST->getName(), AST_Expr1, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 149:
# line 1194 "oberon.y"
{
  yyval.AST = new ASTNode(Assembly::genIntegerExpr(yypvt[-2].AST->getName(),yypvt[-1].AST->getName(),yypvt[-0].AST->getName()), AST_Expr2, 3);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 150:
# line 1201 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_Expr2, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 151:
# line 1208 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_Expr3, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 152:
# line 1215 "oberon.y"
{
  yyval.AST = yypvt[-0].AST;
} break;
case 153:
# line 1219 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_NL, 0);
} break;
case 154:
# line 1225 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_OptSign | PLUS, 0);
} break;
case 155:
# line 1229 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_OptSign | MINUS, 0);
} break;
case 156:
# line 1233 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 157:
# line 1240 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_Factor, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 158:
# line 1245 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-3].AST->getName(), AST_Factor, 2);
  yyval.AST->addChild(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 159:
# line 1251 "oberon.y"
{
  if(Assembly::seenOpSign() != OPSIGN_NONE)
    {
      yyval.AST = new ASTNode(Assembly::genIntegerExpr(Assembly::opSignToString(), yypvt[-0].sval, ""), AST_Factor, 1);
      
      Assembly::setSeenOpSign("");
    }
  else 
    yyval.AST = new ASTNode(yypvt[-0].sval, AST_Factor, 1);
  yyval.AST->addChild(new ASTNode(new ConstSym(yypvt[-0].sval, TypeValues::INTEGER_TYPE,
					new Value(Value::parseInt(yypvt[-0].sval)),NULL,0), AST_INT_LITERAL));
} break;
case 160:
# line 1264 "oberon.y"
{
  if(Assembly::seenOpSign() != OPSIGN_NONE)
    {
      yyval.AST = new ASTNode(Assembly::genIntegerExpr(Assembly::opSignToString(), yypvt[-0].sval, ""), AST_Factor, 1);
      Assembly::setSeenOpSign("");
    }
  else 
    yyval.AST = new ASTNode(yypvt[-0].sval, AST_Factor, 1);
  yyval.AST->addChild(new ASTNode(new ConstSym(yypvt[-0].sval, TypeValues::REAL_TYPE, new Value(Value::parseReal(yypvt[-0].sval)),NULL,0), AST_REAL_LITERAL));
} break;
case 161:
# line 1275 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Factor, 1);
  yyval.AST->addChild(new ASTNode(new ConstSym(yypvt[-0].sval, TypeValues::CHAR_TYPE, new Value(Value::parseChar(yypvt[-0].sval)),NULL,0), AST_CHAR_LITERAL));
} break;
case 162:
# line 1280 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Factor, 1);
  yyval.AST->addChild(new ASTNode(new ConstSym(yypvt[-0].sval, TypeValues::STR_TYPE,new Value(yypvt[-0].sval),NULL,0), AST_STR_LITERAL));
} break;
case 163:
# line 1285 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Factor, 1);
  yyval.AST->addChild(new ASTNode(new ConstSym(yypvt[-0].sval, TypeValues::BOOLEAN_TYPE,
					new Value(true),NULL,0), AST_TRUE));
} break;
case 164:
# line 1291 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Factor, 1);
  yyval.AST->addChild(new ASTNode(new ConstSym(yypvt[-0].sval, TypeValues::BOOLEAN_TYPE,
					new Value(false),NULL,0), AST_FALSE));
} break;
case 165:
# line 1297 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Factor, 1);
  yyval.AST->addChild(new ASTNode(new ConstSym(yypvt[-0].sval, TypeValues::NIL_TYPE,new Value(0),NULL,0), AST_NIL));
} break;
case 166:
# line 1302 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_Factor, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 167:
# line 1307 "oberon.y"
{
  if(!parens.empty())
    {
      if(strcmp(parens.top(), "") != 0)
	yyval.AST = new ASTNode(Assembly::genIntegerExpr(Assembly::genOpSignParenBottom(yypvt[-1].AST->getName()), "", ""), AST_Factor, 1);
      else
	yyval.AST = new ASTNode(Assembly::genOpSignParenBottom(yypvt[-1].AST->getName()), AST_Factor, 1);
    }
  else
    yyval.AST = new ASTNode(yypvt[-1].AST->getName(), AST_Factor, 1);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 168:
# line 1320 "oberon.y"
{
  yyval.AST = new ASTNode(concat(yypvt[-1].sval,yypvt[-0].AST->getName()), AST_Factor, 2);
  yyval.AST->addChild(yypvt[-1].sval, AST_TILDE); 
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 169:
# line 1328 "oberon.y"
{
	Assembly::genOpSignParenTop(); 
	Assembly::setSeenOpSign("");
} break;
case 170:
# line 1335 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-1].AST->getName(), AST_Set, 1);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 171:
# line 1343 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_OptElementList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 172:
# line 1348 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 173:
# line 1355 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_ElementList, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 174:
# line 1360 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_ElementList, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 175:
# line 1369 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].AST->getName(), AST_Element, 1);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 176:
# line 1374 "oberon.y"
{
  yyval.AST = new ASTNode(concat(concat(yypvt[-2].AST->getName(),yypvt[-1].sval),yypvt[-0].AST->getName()), AST_Element, 2);
  yyval.AST->addChild(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].AST);
} break;
case 177:
# line 1383 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | EQU, 0);
} break;
case 178:
# line 1387 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | NEQ, 0);
} break;
case 179:
# line 1391 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | LT, 0);
} break;
case 180:
# line 1395 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | GT, 0);
} break;
case 181:
# line 1399 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | LTE, 0);
} break;
case 182:
# line 1403 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | GTE, 0);
} break;
case 183:
# line 1407 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | IN, 0);
} break;
case 184:
# line 1411 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_Relation | IS, 0);
} break;
case 185:
# line 1418 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_AddOp | PLUS, 0);
} break;
case 186:
# line 1422 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_AddOp | MINUS, 0);
} break;
case 187:
# line 1426 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_AddOp | OR, 0);
} break;
case 188:
# line 1433 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_MulOp | MULTIPLY, 0);  
} break;
case 189:
# line 1437 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_MulOp | SLASH, 0);  
} break;
case 190:
# line 1441 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_MulOp | DIVIDE, 0);  
} break;
case 191:
# line 1445 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_MulOp | MOD, 0);  
} break;
case 192:
# line 1449 "oberon.y"
{
  yyval.AST = new ASTNode(yypvt[-0].sval, AST_MulOp | AND, 0);  
} break;
case 193:
# line 1456 "oberon.y"
{
  yyval.AST = yypvt[-0].AST;
  if(Assembly::seenOpSign() != OPSIGN_NONE)
    {
      yyval.AST->setName(Assembly::genIntegerExpr(Assembly::opSignToString(), yypvt[-0].AST->getName(), "")); 
      Assembly::setSeenOpSign("");
    }
  else 
    yyval.AST->setName(yypvt[-0].AST->getName());
} break;
case 194:
# line 1470 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Designator2, 1);
  yyval.AST->addChildrenOf(yypvt[-3].AST);
  yyval.AST->addChild(yypvt[-1].AST);
  delete yypvt[-3].AST;
} break;
case 195:
# line 1477 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Designator2, 0);
  yyval.AST->addChildrenOf(yypvt[-1].AST);
  delete yypvt[-1].AST;
} break;
case 196:
# line 1483 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_Designator2, 1);
  yyval.AST->addChildrenOf(yypvt[-2].AST);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
  delete yypvt[-2].AST;
} break;
case 197:
# line 1490 "oberon.y"
{
  yyval.AST = new ASTNode("", AST_Designator2, 1);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 198:
# line 1498 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IdentList, 0);
  yyval.AST->addChildrenOf(yypvt[-0].AST);
  delete yypvt[-0].AST;
} break;
case 199:
# line 1504 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IdentList, 0);
  yyval.AST->addChildrenOf(yypvt[-2].AST);
  yyval.AST->addChildrenOf(yypvt[-0].AST);
  delete yypvt[-2].AST;
  delete yypvt[-0].AST;
} break;
case 200:
# line 1512 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IdentList, 0);
  yyval.AST->addChildrenOf(yypvt[-1].AST);
  yyval.AST->addChildrenOf(yypvt[-0].AST);
  delete yypvt[-1].AST;
  delete yypvt[-0].AST;
  yyerror("missing comma in identifier list.");
} break;
case 201:
# line 1524 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_OptQualIdent, 1);
  yyval.AST->addChild(yypvt[-1].AST);
} break;
case 202:
# line 1529 "oberon.y"
{
  yyval.AST = NULL;
} break;
case 203:
# line 1536 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_QualIdent, 1);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 204:
# line 1541 "oberon.y"
{
  yyval.AST = new ASTNode(concat(yypvt[-2].sval, concat(yypvt[-1].sval, yypvt[-0].sval)), AST_QualIdent, 2);
  yyval.AST->addChild(yypvt[-2].sval, AST_ID);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 205:
# line 1549 "oberon.y"
{ 
  yyval.AST = new ASTNode(NULL, AST_IdentDef, 1);
  yyval.AST->addChild(yypvt[-0].sval, AST_ID);
} break;
case 206:
# line 1554 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IdentDef, 1);
  yyval.AST->addChild(yypvt[-1].sval, AST_ID | EXPORTABLE);
} break;
case 207:
# line 1559 "oberon.y"
{
  yyval.AST = new ASTNode(NULL, AST_IdentDef, 1);
  yyval.AST->addChild(yypvt[-1].sval, AST_ID | READONLY | EXPORTABLE);
} break;
# line	531 "/usr/ccs/bin/yaccpar"
	}
	goto yystack;		/* reset registers in driver code */
}

