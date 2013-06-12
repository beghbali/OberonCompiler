
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
extern YYSTYPE yylval;
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
