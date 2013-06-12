
%{
  #include "ASTnode.h"
%}

%union {
    char*        sval;
    int         ival;
    float        fval;
    ASTNode*      AST;
}

%token T_ARRAY      
%token T_BEGIN
%token T_BY
%token T_CASE       
%token T_CONST      
%token <sval>T_DIV        
%token T_DO        
%token <sval>T_ELSE       
%token <sval>T_ELSIF      
%token T_END        
%token T_EXIT       
%token T_FOR        
%token <sval>T_IF         
%token T_IMPORT     
%token <sval>T_IN         
%token <sval>T_IS         
%token T_LOOP       
%token <sval>T_MOD        
%token T_MODULE     
%token <sval>T_NIL         
%token <sval>T_OF         
%token <sval>T_OR         
%token T_POINTER    
%token T_PROCEDURE  
%token T_RECORD
%token T_REPEAT
%token T_RETURN     
%token <sval>T_THEN       
%token T_TO       
%token T_TYPE
%token T_UNTIL        
%token T_VAR        
%token T_WHILE    
%token T_WITH    

%token <sval>T_AMPERSAND 
%token <sval>T_ARROW 
%token <sval>T_ASSIGN
%token T_BAR
%token T_COLON      
%token <sval>T_COMMA      
%token <sval>T_DOTDOT     
%token <sval>T_DOT        
%token <sval>T_EQU      
%token <sval>T_GT
%token <sval>T_GTE        
%token <sval>T_LBRACE     
%token <sval>T_LBRACKET     
%token <sval>T_LPAREN     
%token <sval>T_LT   
%token <sval>T_LTE        
%token <sval>T_MINUS
%token <sval>T_NEQ        
%token <sval>T_PLUS       
%token <sval>T_RBRACE     
%token <sval>T_RBRACKET     
%token <sval>T_RPAREN     
%token <sval>T_SEMI
%token <sval>T_TILDE
%token <sval>T_SLASH      
%token <sval>T_STAR       

%token <sval>T_BOOLEAN
%token <sval>T_CHAR
%token <sval>T_FALSE
%token <sval>T_INTEGER
%token T_NEW
%token <sval>T_REAL
%token <sval>T_TRUE

%token <sval> T_ID
%token <sval> T_INT_LITERAL
%token <sval> T_STR_LITERAL
%token <sval> T_REAL_LITERAL
%token <sval> T_CHAR_LITERAL

%token T_PROGRAM
%token T_READ
%token T_WRITE
%token <sval>T_NL

%{
#ifdef __cplusplus
#include <iostream>
#include "assembly.h"
extern ASTNode* ASTree;
extern char* concat(char*, char*);
extern void suppressError();
#endif
%}

%start Program   
  %type <AST> IdentDef       
  %type <AST> QualIdent      
  %type <AST> OptQualIdent   
  %type <AST> IdentList      
  %type <AST> Designator2     
  %type <AST> Designator     
  %type <AST> MulOp          
  %type <AST> AddOp           
  %type <AST> Relation       
  %type <AST> Element        
  %type <AST> ElementList    
  %type <AST> OptElementList 
  %type <AST> Set            
  %type <AST> Factor          
  %type <AST> OptSign        
  %type <AST> Exprk                      
  %type <AST> Expr3          
  %type <AST> Expr2          
  %type <AST> Expr1          
  %type <AST> Expr           
  %type <AST> ExprList2      
  %type <AST> ExprList      
  %type <AST> ConstExpr      
  %type <AST> Guard          
  %type <AST> ReturnStmt     
  %type <AST> ExitStmt       
  %type <AST> GuardList      
  %type <AST> WithStmt       
  %type <AST> LoopStmt       
  %type <AST> OptBy          
  %type <AST> ForStmt        
  %type <AST> RepeatStmt     
  %type <AST> WhileStmt      
  %type <AST> CaseLabels     
  %type <AST> CaseLabelsList 
  %type <AST> Case           
  %type <AST> CaseList       
  %type <AST> CaseStmt       
  %type <AST> OptElse        
  %type <AST> OptElsifs      
  %type <AST> IfStmt         
  %type <AST> OptExprList    
  %type <AST> ProcCall       
  %type <AST> AssignStmt     
  %type <AST> OutputItems    
  %type <AST> OutputStmt     
  %type <AST> InputStmt   
  %type <AST> NewStmt
  %type <AST> Stmt           
  %type <AST> StmtList       
  %type <AST> FieldList      
  %type <AST> FieldsList     
  %type <AST> BasicType      
  %type <AST> Type           
  %type <AST> OptReceiver    
  %type <AST> OptReturnType  
  %type <AST> IdList         
  %type <AST> ParamDecl      
  %type <AST> ParamList      
  %type <AST> OptParamList   
  %type <AST> FormalParams   
  %type <AST> OptFormalParams
  %type <AST> FwdProcDecl    
  %type <AST> OptStmts       
  %type <AST> ProcDecl       
  %type <AST> VarDecl        
  %type <AST> VarDeclList2   
  %type <AST> VarDeclList    
  %type <AST> TypeDecl       
  %type <AST> TypeDeclList   
  %type <AST> ConstDecl      
  %type <AST> ConstDeclList  
  %type <AST> CTDecl         
  %type <AST> CVTDecl        
  %type <AST> ProcDeclList2  
  %type <AST> ProcDeclList   
  %type <AST> CTDeclList     
  %type <AST> CVTDeclList    
  %type <AST> DeclSeq        
  %type <AST> ImportList     
  %type <AST> ImportDecl     
  %type <AST> OptImportDecl  
  %type <AST> Module         
  %type <AST> ModuleList     
  %type <AST> DeclarationList
  %type <AST> DeclarationsSection 
  %type <AST> MainStmtsSection  
  %type <AST> Program 
  %type <AST> Expr11
  %type <AST> OptVar
%%


Program:            DeclarationsSection MainStmtsSection
{
  ASTree = new ASTNode(NULL, AST_Program, 2);
  ASTree->addChild($1);
  ASTree->addChild($2);
}
    |               MainStmtsSection
{
  ASTree = new ASTNode(NULL, AST_Program, 1);
  ASTree->addChild($1);
}
    |               DeclarationsSection
{
  ASTree = new ASTNode(NULL, AST_Program, 1);
  ASTree->addChild($1);
}
    ;

MainStmtsSection:   T_PROGRAM T_ID VarDeclList2 
                    T_BEGIN
                    StmtList
                    T_END T_DOT
{
  $$ = new ASTNode(NULL, AST_MainStmtsSection, 3);
  $$->addChild($2, AST_ID);
  $$->addChild($3);
  $$->addChild($5);
}
    ;
                     

DeclarationsSection:DeclarationsSection DeclarationList
{
  $$ = new ASTNode(NULL, AST_DeclarationsSection, 2);
  $$->addChild($1);
  $$->addChild($2);
}
    |               DeclarationList
{
  $$ = new ASTNode(NULL, AST_DeclarationsSection, 1);
  $$->addChild($1);
}
    ;

DeclarationList:    CTDeclList
{
  $$ = new ASTNode(NULL, AST_DeclarationList, 1);
  $$->addChild($1);
}
    |               ProcDeclList2
{
  $$ = new ASTNode(NULL, AST_DeclarationList, 1);
  $$->addChild($1);
}
    |               ModuleList
{
  $$ = new ASTNode(NULL, AST_DeclarationList, 1);
  $$->addChild($1);
}
    |               VarDeclList
{
  $$ = new ASTNode(NULL, AST_DeclarationList, 1);
  $$->addChild($1);
}
    ;

ModuleList:         Module
{
  $$ = new ASTNode(NULL, AST_ModuleList, 1);
  $$->addChild($1);
}
    ;

Module:             T_MODULE T_ID T_SEMI 
                    OptImportDecl DeclSeq OptStmts
                    T_END T_ID T_DOT
{
  $$ = new ASTNode(NULL, AST_Module, 5);
  $$->addChild($2, AST_ID);
  $$->addChild($4);
  $$->addChild($5);
  $$->addChild($6);
  $$->addChild($8, AST_ID);
}
    ;


OptImportDecl:      ImportDecl
{
  $$ = new ASTNode(NULL, AST_OptImportDecl, 1);
  $$->addChild($1);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


ImportDecl:         T_IMPORT ImportList T_SEMI
{
  $$ = new ASTNode(NULL, AST_ImportDecl, 1);
  $$->addChild($2);
}
    ;


ImportList:         T_ID 
{
  $$ = new ASTNode(NULL, AST_ImportList,1);
  $$->addChild($1, AST_ID);
}
    |               T_ID T_ASSIGN T_ID
{
  $$ = new ASTNode(NULL, AST_ImportList, 2);
  $$->addChild($1, AST_ID);
  $$->addChild($3, AST_ID);
}
    |               ImportList T_COMMA T_ID
{
  $$ = new ASTNode(NULL, AST_ImportList, 2);
  $$->addChild($1);
  $$->addChild($3, AST_ID);
}
    |               ImportList T_COMMA T_ID T_ASSIGN T_ID
{
  $$ = new ASTNode(NULL, AST_ImportList, 3);
  $$->addChild($1);
  $$->addChild($3, AST_ID);
  $$->addChild($5, AST_ID);
}
    ;


DeclSeq:            CVTDeclList ProcDeclList
{
  $$ = new ASTNode(NULL, AST_DeclSeq, 2);
  $$->addChild($1);
  $$->addChild($2);
}
    ;


CVTDeclList:        CVTDeclList CVTDecl
{
  $$ = new ASTNode(NULL, AST_CVTDeclList, 2);
  $$->addChild($1);
  $$->addChild($2);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;

CTDeclList:         CTDecl
{
  $$ = new ASTNode(NULL, AST_CTDeclList, 1);
  $$->addChild($1);
}
    ;

ProcDeclList:       ProcDeclList ProcDecl T_SEMI
{
  $$ = new ASTNode(NULL, AST_ProcDeclList, 2);
  $$->addChild($1);
  $$->addChild($2);
}
    |               ProcDeclList FwdProcDecl T_SEMI
{
  $$ = new ASTNode(NULL, AST_ProcDeclList, 2);
  $$->addChild($1);
  $$->addChild($2);
}
    |               /*empty*/
{
  $$ = NULL;
}
    ;

ProcDeclList2:      ProcDecl T_SEMI
{
  $$ = new ASTNode(NULL, AST_ProcDeclList2, 1);
  $$->addChild($1);
}
    |               FwdProcDecl T_SEMI
{
  $$ = new ASTNode(NULL, AST_ProcDeclList2, 1);
  $$->addChild($1);
}
    ;

CVTDecl:            CTDecl
{
  $$ = new ASTNode(NULL, AST_CVTDecl, 1);
  $$->addChild($1);
}
    |               VarDeclList
{
  $$ = new ASTNode(NULL, AST_CVTDecl, 1);
  $$->addChild($1);
}
    ;

CTDecl:             ConstDeclList
{
  $$ = new ASTNode(NULL, AST_CTDecl, 1);
  $$->addChild($1);
}
    |               TypeDeclList
{
  $$ = new ASTNode(NULL, AST_CTDecl, 1);
  $$->addChild($1);
}
    ;

ConstDeclList:      T_CONST ConstDecl
{
  $$ = new ASTNode(NULL, AST_ConstDeclList, 1);
  $$->addChild($2);
}
    ;


ConstDecl:          ConstDecl IdentDef T_EQU ConstExpr T_SEMI
{
  $$ = new ASTNode(NULL, AST_ConstDecl, 3);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($4);
}
    |               ConstDecl IdentDef {suppressError();}error ConstExpr T_SEMI
{
  $$ = new ASTNode(NULL, AST_ConstDecl, 3);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($5);
  yyerror("missing = in constant declaration.");
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


TypeDeclList:       T_TYPE TypeDecl
{
  $$ = new ASTNode(NULL, AST_TypeDeclList, 1);
  $$->addChild($2);
}
    ;


TypeDecl:           TypeDecl IdentDef T_EQU Type T_SEMI
{
  $$ = new ASTNode(NULL, AST_TypeDecl, 3);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($4);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


VarDeclList:        T_VAR VarDecl
{
  $$ = new ASTNode(NULL, AST_VarDeclList, 1);
  $$->addChild($2);
}
    ;

VarDeclList2:       VarDeclList2 VarDeclList
{
  $$ = new ASTNode(NULL, AST_VarDeclList2, 2);
  $$->addChild($1);
  $$->addChild($2);
}
    |               /*empty*/
{
  $$ = NULL;
}
    ;

VarDecl:            VarDecl IdentList T_COLON Type T_SEMI
{
  $$ = new ASTNode(NULL, AST_VarDecl, 3);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($4);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


ProcDecl:           T_PROCEDURE OptReceiver IdentDef 
					OptFormalParams T_SEMI
                    DeclSeq OptStmts T_END T_ID
{
  $$ = new ASTNode(NULL, AST_ProcDecl, 6);
  $$->addChild($2);
  $$->addChild($3);
  $$->addChild($4);
  $$->addChild($6);
  $$->addChild($7);
  $$->addChild($9, AST_ID);
}
    ;


OptStmts:           T_BEGIN StmtList
{
  $$ = new ASTNode(NULL, AST_OptStmts, 1);
  $$->addChild($2);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


FwdProcDecl:        T_PROCEDURE T_ARROW OptReceiver IdentDef OptFormalParams
{
  $$ = new ASTNode(NULL, AST_FwdProcDecl, 3);
  $$->addChild($3);
  $$->addChild($4);
  $$->addChild($5);
}
    ;


OptFormalParams:    FormalParams
{
  $$ = new ASTNode(NULL, AST_OptFormalParams, 1);
  $$->addChild($1);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


FormalParams:       T_LPAREN OptParamList T_RPAREN OptReturnType
{
  $$ = new ASTNode(NULL, AST_FormalParams, 2);
  $$->addChild($2);
  $$->addChild($4);
}
    ;


OptParamList:       ParamList
{
  $$ = new ASTNode(NULL, AST_OptParamList, 1);
  $$->addChild($1); 
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


ParamList:          ParamDecl
{
  $$ = new ASTNode(NULL, AST_ParamList, 1);
  $$->addChild($1);
}
    |               ParamList T_SEMI ParamDecl
{
  $$ = new ASTNode(NULL, AST_ParamList, 1);
  $$->addChildrenOf($1);
  $$->addChild($3);
  delete $1;
}
    ;


ParamDecl:          OptVar IdList T_COLON Type
{
  $$ = new ASTNode(NULL, AST_ParamDecl, 3);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($4);
}
    ;


OptVar:             T_VAR
{
  $$ = new ASTNode(NULL, AST_OptVar, 0);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


IdList:             T_ID
{
  $$ = new ASTNode(NULL, AST_IdList, 1);
  $$->addChild($1, AST_ID);
}
    |               IdList T_COMMA T_ID
{
  $$ = new ASTNode(NULL, AST_IdList, 1);
  $$->addChildrenOf($1);
  $$->addChild($3, AST_ID);
  delete $1;
}
    ;


OptReturnType:      T_COLON QualIdent
{
  $$ = new ASTNode(NULL, AST_OptReturnType, 1);
  $$->addChild($2);
}
    |               T_COLON BasicType
{
  $$ = new ASTNode(NULL, AST_OptReturnType, 1);
  $$->addChild($2);
}
    |               QualIdent
{
  $$ = new ASTNode(NULL, AST_OptReturnType, 1);
  $$->addChild($1);
  yyerror("missing : in procedure declaration.");
}
    |               BasicType
{
  $$ = new ASTNode(NULL, AST_OptReturnType, 1);
  $$->addChild($1);
  yyerror("missing : in procedure declaration.");
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


OptReceiver:        T_LPAREN OptVar T_ID T_COLON T_ID T_RPAREN
{
  $$ = new ASTNode(NULL, AST_OptReceiver, 3);
  $$->addChild($2);
  $$->addChild($3, AST_ID);
  $$->addChild($5, AST_ID);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


Type:               QualIdent
{
  $$ = new ASTNode(NULL, AST_Type, 1);
  $$->addChild($1);
}
    |               BasicType
{
  $$ = new ASTNode(NULL, AST_Type, 1);
  $$->addChild($1);
}
    |               T_ARRAY OptExprList T_OF Type
{
  $$ = new ASTNode(NULL, AST_Type, 2);
  $$->addChild($2);
  $$->addChild($4);
}
    |               T_RECORD OptQualIdent FieldsList T_END
{
  $$ = new ASTNode(NULL, AST_Type, 2);
  $$->addChild($2);
  $$->addChild($3);
}
    |               T_POINTER T_TO Type
{
  $$ = new ASTNode(NULL, AST_Type, 1);
  $$->addChild($3);
}
    |               T_PROCEDURE OptFormalParams
{
  $$ = new ASTNode(NULL, AST_Type, 1);
  $$->addChild($2);
}
    ;


BasicType:          T_INTEGER
{
  $$ = new ASTNode(NULL, AST_BasicType | INTEGER, 1);
  $$->addChild(new ASTNode(new TypeSym($1, TypeValues::INTEGER_TYPE), notype));
}
    |               T_REAL
{
  $$ = new ASTNode(NULL, AST_BasicType | REAL, 1);
  $$->addChild(new ASTNode(new TypeSym($1, TypeValues::REAL_TYPE), notype));
}
    |               T_BOOLEAN
{
  $$ = new ASTNode(NULL, AST_BasicType | BOOLEAN, 1);
  $$->addChild(new ASTNode(new TypeSym($1, TypeValues::BOOLEAN_TYPE), notype));
}
    |               T_CHAR
{
  $$ = new ASTNode(NULL, AST_BasicType | CHAR, 1);
  $$->addChild(new ASTNode(new TypeSym($1, TypeValues::CHAR_TYPE), notype));
}
    ;


FieldsList:         FieldList
{
  $$ = new ASTNode(NULL, AST_FieldsList, 1);
  $$->addChild($1);
}
    |               FieldsList T_SEMI FieldList
{
  $$ = new ASTNode(NULL, AST_FieldsList, 1);
  $$->addChildrenOf($1);
  $$->addChild($3);
  delete $1;
}
    ;


FieldList:          IdList T_COLON Type
{
  $$ = new ASTNode(NULL, AST_FieldList, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


StmtList:           Stmt
{
  $$ = new ASTNode(NULL, AST_StmtList, 1);
  $$->addChild($1);
}
    |               StmtList T_SEMI Stmt
{
  $$ = new ASTNode(NULL, AST_StmtList,2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


Stmt:               AssignStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
  Assembly::getNextNumber(-1);
} 
    |               ProcCall
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               IfStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               CaseStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               WhileStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               RepeatStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               ForStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               LoopStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               WithStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               ExitStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               ReturnStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               InputStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               OutputStmt
{
  $$ = new ASTNode(NULL, AST_Stmt, 1);
  $$->addChild($1);
}
    |               NewStmt
{
   $$ = new ASTNode(NULL, AST_Stmt, 1);
   $$->addChild($1);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;

NewStmt:            T_NEW T_LPAREN Designator T_RPAREN
{
    $$ = new ASTNode(NULL, AST_NewStmt, 1);
    $$->addChild($3);
}
    ;

InputStmt:          T_READ Designator
{
  $$ = new ASTNode(NULL, AST_InputStmt, 1);
  $$->addChild($2);
}
    ;

OutputStmt:         T_WRITE OutputItems
{
  $$ = new ASTNode(NULL, AST_OutputStmt, 1);
  $$->addChild($2);
}
    ;

OutputItems:        ExprList2
{
  $$ = new ASTNode(NULL, AST_OutputItems, 1);
  $$->addChild($1);
}
    ;
   
AssignStmt:         Designator T_ASSIGN Expr
{
  $$ = new ASTNode(NULL, AST_AssignStmt, 2);
  $$->addChild($1);
  $$->addChild($3);
  Assembly::genAssignStmt($1->getName(),$3->getName());
}
    ;


ProcCall:           Designator
{
  $$ = new ASTNode(NULL, AST_ProcCall, 1);
  $$->addChild($1);
}
    |               Designator T_LPAREN OptExprList T_RPAREN
{
  $$ = new ASTNode(NULL, AST_ProcCall, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


OptExprList:        ExprList
{
  $$ = $1;
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


IfStmt:             T_IF Expr {Assembly::genIFtop($2->getName());}T_THEN StmtList OptElsifs OptElse T_END
{
  $$ = new ASTNode(NULL, AST_IfStmt, 4);
  $$->addChild($2);
  $$->addChild($5);
  $$->addChild($6);
  $$->addChild($7);
  Assembly::getIFbottom();
}
    
    |               T_IF Expr{suppressError();Assembly::genIFtop($2->getName());} error StmtList OptElsifs OptElse T_END
{
  $$ = new ASTNode(NULL, AST_IfStmt, 4);
  $$->addChild($2);
  $$->addChild($5);
  $$->addChild($6);
  $$->addChild($7);
  Assembly::getIFbottom();
  yyerror("missing THEN in IF statement.");
}
    ;


OptElsifs:          OptElsifs T_ELSIF Expr T_THEN StmtList
{
  $$ = new ASTNode(NULL, AST_OptElsifs, 3);
  $$->addChild($1);
  $$->addChild($3);
  $$->addChild($5);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


OptElse:            T_ELSE StmtList
{
  $$ = new ASTNode(NULL, AST_OptElse, 1);
  $$->addChild($2);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


CaseStmt:           T_CASE Expr T_OF CaseList OptElse T_END
{
  $$ = new ASTNode(NULL, AST_CaseStmt, 3);
  $$->addChild($2);
  $$->addChild($4);
  $$->addChild($5);
}
    ;


CaseList:           Case
{
  $$ = new ASTNode(NULL, AST_CaseList, 1);
  $$->addChild($1);
}
    |               CaseList T_BAR Case
{
  $$ = new ASTNode(NULL, AST_CaseList, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


Case:               CaseLabelsList T_COLON StmtList
{
  $$ = new ASTNode(NULL, AST_Case, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


CaseLabelsList:     CaseLabels
{
  $$ = new ASTNode(NULL, AST_CaseLabelsList, 1);
  $$->addChild($1);
}
    |               CaseLabelsList T_COMMA CaseLabels
{
  $$ = new ASTNode(NULL, AST_CaseLabelsList, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


CaseLabels:         ConstExpr
{
  $$ = new ASTNode(NULL, AST_CaseLabels, 1);
  $$->addChild($1);
}
    |               ConstExpr T_DOTDOT ConstExpr
{
  $$ = new ASTNode(NULL, AST_CaseLabels, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


WhileStmt:          T_WHILE Expr T_DO StmtList T_END
{
  $$ = new ASTNode(NULL, AST_WhileStmt, 2);
  $$->addChild($2);
  $$->addChild($4);
}
    ;


RepeatStmt:         T_REPEAT StmtList T_UNTIL Expr
{
  $$ = new ASTNode(NULL, AST_RepeatStmt, 2);
  $$->addChild($2);
  $$->addChild($4);
}
  ;


ForStmt:            T_FOR T_ID T_ASSIGN Expr T_TO Expr OptBy 
                    T_DO StmtList T_END
{
  $$ = new ASTNode(NULL, AST_ForStmt, 5);
  $$->addChild($2, AST_ID);
  $$->addChild($4);
  $$->addChild($6);
  $$->addChild($7);
  $$->addChild($9);
}
    ;


OptBy:              T_BY ConstExpr
{
  $$ = $2;
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


LoopStmt:           T_LOOP {Assembly::genLoopTop();}StmtList T_END
{
  $$ = new ASTNode(NULL, AST_LoopStmt, 1);
  $$->addChild($3);
  Assembly::genLoopBottom();
}
    ;


WithStmt:           T_WITH GuardList OptElse T_END
{
  $$ = new ASTNode(NULL, AST_WithStmt, 2);
  $$->addChild($2);
  $$->addChild($3);
}
    ;


GuardList:          Guard T_DO StmtList
{
  $$ = new ASTNode(NULL, AST_GuardList, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    |               GuardList T_BAR Guard T_DO StmtList
{
  $$ = new ASTNode(NULL, AST_GuardList, 3);
  $$->addChild($1);
  $$->addChild($3);
  $$->addChild($5);
}
    ;


ExitStmt:           T_EXIT
{
  $$ = new ASTNode(NULL, AST_ExitStmt, 0);
  Assembly::genExitStmt();
}
    ;


ReturnStmt:         T_RETURN
{
  $$ = new ASTNode(NULL, AST_ReturnStmt, 0);
}
    |               T_RETURN Expr
{
  $$ = new ASTNode(NULL, AST_ReturnStmt, 1);
  $$->addChild($2);
}
    ;


Guard:              QualIdent T_COLON QualIdent
{
  $$ = new ASTNode(NULL, AST_Guard, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


ConstExpr:          Expr
{
  $$ = new ASTNode(NULL, AST_ConstExpr, 1);
  $$->addChild($1);
}
    ;


ExprList:           Expr
{
  $$ = new ASTNode(NULL, AST_ExprList, 1);
  $$->addChild($1);
}
    |               ExprList T_COMMA Expr
{
  $$ = new ASTNode(NULL, AST_ExprList, 1);
  $$->addChildrenOf($1);
  $$->addChild($3);
  delete $1;
}
    ;

ExprList2:          Exprk
{
  $$ = new ASTNode(NULL, AST_ExprList2, 1);
  $$->addChild($1);
}
    |               ExprList2 T_COMMA Exprk
{
  $$ = new ASTNode(NULL, AST_ExprList2, 1);
  $$->addChildrenOf($1);
  $$->addChild($3);
  delete $1;
}
    ;

Expr:              Expr11 Expr1 Relation Expr11 Expr1
{
  $$ = new ASTNode(Assembly::genIntegerExpr($2->getName(),$3->getName(),$5->getName()), AST_Expr, 5);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($3);
  $$->addChild($4);
  $$->addChild($5);
}
    |               Expr11 Expr1
{
  $$ = new ASTNode($2->getName(), AST_Expr, 2);
  $$->addChild($1);
  $$->addChild($2);
}
    ;            
 
Expr11:             OptSign 
{
  $$ = $1;
  Assembly::setSeenOpSign($1?$1->getName():(char*)"");
}
    ;

Expr1:              Expr1 AddOp Expr2
{
  $$ =  new ASTNode(Assembly::genIntegerExpr($1->getName(),$2->getName(),$3->getName()), AST_Expr1, 3);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($3);
}

    |               Expr2
{
  $$ =  new ASTNode($1->getName(), AST_Expr1, 1);
  $$->addChild($1);
}
    ;

Expr2:              Expr2 MulOp Expr3
{
  $$ = new ASTNode(Assembly::genIntegerExpr($1->getName(),$2->getName(),$3->getName()), AST_Expr2, 3);
  $$->addChild($1);
  $$->addChild($2);
  $$->addChild($3);
}
    |               Expr3
{
  $$ = new ASTNode($1->getName(), AST_Expr2, 1);
  $$->addChild($1);
}
    ;

Expr3:              Factor
{
  $$ = new ASTNode($1->getName(), AST_Expr3, 1);
  $$->addChild($1);
}
    ;

Exprk:              Expr
{
  $$ = $1;
}
    |               T_NL
{
  $$ = new ASTNode($1, AST_NL, 0);
}
    ;

OptSign:            T_PLUS
{
  $$ = new ASTNode($1, AST_OptSign | PLUS, 0);
}
    |               T_MINUS
{
  $$ = new ASTNode($1, AST_OptSign | MINUS, 0);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


Factor:             Designator
{
  $$ = new ASTNode($1->getName(), AST_Factor, 1);
  $$->addChild($1);
}
    |               Designator T_LPAREN OptExprList T_RPAREN
{
  $$ = new ASTNode($1->getName(), AST_Factor, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    |               T_INT_LITERAL
{
  if(Assembly::seenOpSign() != OPSIGN_NONE)
    {
      $$ = new ASTNode(Assembly::genIntegerExpr(Assembly::opSignToString(), $1, ""), AST_Factor, 1);
      
      Assembly::setSeenOpSign("");
    }
  else 
    $$ = new ASTNode($1, AST_Factor, 1);
  $$->addChild(new ASTNode(new ConstSym($1, TypeValues::INTEGER_TYPE,
					new Value(Value::parseInt($1)),NULL,0), AST_INT_LITERAL));
}
    |               T_REAL_LITERAL
{
  if(Assembly::seenOpSign() != OPSIGN_NONE)
    {
      $$ = new ASTNode(Assembly::genIntegerExpr(Assembly::opSignToString(), $1, ""), AST_Factor, 1);
      Assembly::setSeenOpSign("");
    }
  else 
    $$ = new ASTNode($1, AST_Factor, 1);
  $$->addChild(new ASTNode(new ConstSym($1, TypeValues::REAL_TYPE, new Value(Value::parseReal($1)),NULL,0), AST_REAL_LITERAL));
}
    |               T_CHAR_LITERAL
{
  $$ = new ASTNode($1, AST_Factor, 1);
  $$->addChild(new ASTNode(new ConstSym($1, TypeValues::CHAR_TYPE, new Value(Value::parseChar($1)),NULL,0), AST_CHAR_LITERAL));
}
    |               T_STR_LITERAL
{
  $$ = new ASTNode($1, AST_Factor, 1);
  $$->addChild(new ASTNode(new ConstSym($1, TypeValues::STR_TYPE,new Value($1),NULL,0), AST_STR_LITERAL));
}
    |               T_TRUE
{
  $$ = new ASTNode($1, AST_Factor, 1);
  $$->addChild(new ASTNode(new ConstSym($1, TypeValues::BOOLEAN_TYPE,
					new Value(true),NULL,0), AST_TRUE));
}
    |               T_FALSE
{
  $$ = new ASTNode($1, AST_Factor, 1);
  $$->addChild(new ASTNode(new ConstSym($1, TypeValues::BOOLEAN_TYPE,
					new Value(false),NULL,0), AST_FALSE));
}
    |               T_NIL
{
  $$ = new ASTNode($1, AST_Factor, 1);
  $$->addChild(new ASTNode(new ConstSym($1, TypeValues::NIL_TYPE,new Value(0),NULL,0), AST_NIL));
}
    |               Set
{
  $$ = new ASTNode($1->getName(), AST_Factor, 1);
  $$->addChild($1);
}
    |               Lparen Expr T_RPAREN
{
  if(!parens.empty())
    {
      if(strcmp(parens.top(), "") != 0)
	$$ = new ASTNode(Assembly::genIntegerExpr(Assembly::genOpSignParenBottom($2->getName()), "", ""), AST_Factor, 1);
      else
	$$ = new ASTNode(Assembly::genOpSignParenBottom($2->getName()), AST_Factor, 1);
    }
  else
    $$ = new ASTNode($2->getName(), AST_Factor, 1);
  $$->addChild($2);
}
|               T_TILDE Factor
{
  $$ = new ASTNode(concat($1,$2->getName()), AST_Factor, 2);
  $$->addChild($1, AST_TILDE); 
  $$->addChild($2);
}
    ;

Lparen:             T_LPAREN 
{
	Assembly::genOpSignParenTop(); 
	Assembly::setSeenOpSign("");
}
   ;

Set:                T_LBRACE OptElementList T_RBRACE
{
  $$ = new ASTNode($2->getName(), AST_Set, 1);
  $$->addChild($2);
}
   ;


OptElementList:     ElementList
{
  $$ = new ASTNode($1->getName(), AST_OptElementList, 1);
  $$->addChild($1);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


ElementList:        Element
{
  $$ = new ASTNode($1->getName(), AST_ElementList, 1);
  $$->addChild($1);
}
    |               ElementList T_COMMA Element
{
  $$ = new ASTNode(NULL, AST_ElementList, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


Element:            Expr
{
  $$ = new ASTNode($1->getName(), AST_Element, 1);
  $$->addChild($1);
}
    |               Expr T_DOTDOT Expr
{
  $$ = new ASTNode(concat(concat($1->getName(),$2),$3->getName()), AST_Element, 2);
  $$->addChild($1);
  $$->addChild($3);
}
    ;


Relation:           T_EQU
{
  $$ = new ASTNode($1, AST_Relation | EQU, 0);
}
    |               T_NEQ
{
  $$ = new ASTNode($1, AST_Relation | NEQ, 0);
}
    |               T_LT
{
  $$ = new ASTNode($1, AST_Relation | LT, 0);
}
    |               T_GT
{
  $$ = new ASTNode($1, AST_Relation | GT, 0);
}
    |               T_LTE
{
  $$ = new ASTNode($1, AST_Relation | LTE, 0);
}
    |               T_GTE
{
  $$ = new ASTNode($1, AST_Relation | GTE, 0);
}
    |               T_IN
{
  $$ = new ASTNode($1, AST_Relation | IN, 0);
}
    |               T_IS
{
  $$ = new ASTNode($1, AST_Relation | IS, 0);
}
    ;


AddOp:              T_PLUS
{
  $$ = new ASTNode($1, AST_AddOp | PLUS, 0);
}
    |               T_MINUS
{
  $$ = new ASTNode($1, AST_AddOp | MINUS, 0);
}
    |               T_OR
{
  $$ = new ASTNode($1, AST_AddOp | OR, 0);
}
    ;


MulOp:              T_STAR
{
  $$ = new ASTNode($1, AST_MulOp | MULTIPLY, 0);  
}
    |               T_SLASH
{
  $$ = new ASTNode($1, AST_MulOp | SLASH, 0);  
}
    |               T_DIV
{
  $$ = new ASTNode($1, AST_MulOp | DIVIDE, 0);  
}
    |               T_MOD
{
  $$ = new ASTNode($1, AST_MulOp | MOD, 0);  
}
    |               T_AMPERSAND
{
  $$ = new ASTNode($1, AST_MulOp | AND, 0);  
}
    ;


Designator:         Designator2
{
  $$ = $1;
  if(Assembly::seenOpSign() != OPSIGN_NONE)
    {
      $$->setName(Assembly::genIntegerExpr(Assembly::opSignToString(), $1->getName(), "")); 
      Assembly::setSeenOpSign("");
    }
  else 
    $$->setName($1->getName());
}         
    ;


Designator2:        Designator2 T_LBRACKET ExprList T_RBRACKET
{
  $$ = new ASTNode(NULL, AST_Designator2, 1);
  $$->addChildrenOf($1);
  $$->addChild($3);
  delete $1;
}
    |               Designator2 T_ARROW 
{
  $$ = new ASTNode(NULL, AST_Designator2, 0);
  $$->addChildrenOf($1);
  delete $1;
}
    |               Designator2 T_DOT T_ID
{
  $$ = new ASTNode(NULL, AST_Designator2, 1);
  $$->addChildrenOf($1);
  $$->addChild($3, AST_ID);
  delete $1;
}
    |               T_ID
{
  $$ = new ASTNode("", AST_Designator2, 1);
  $$->addChild($1, AST_ID);
}
    ;


IdentList:          IdentDef
{
  $$ = new ASTNode(NULL, AST_IdentList, 0);
  $$->addChildrenOf($1);
  delete $1;
}
    |               IdentList T_COMMA IdentDef
{
  $$ = new ASTNode(NULL, AST_IdentList, 0);
  $$->addChildrenOf($1);
  $$->addChildrenOf($3);
  delete $1;
  delete $3;
}
    |               IdentList IdentDef
{
  $$ = new ASTNode(NULL, AST_IdentList, 0);
  $$->addChildrenOf($1);
  $$->addChildrenOf($2);
  delete $1;
  delete $2;
  yyerror("missing comma in identifier list.");
}
    ;


OptQualIdent:       T_LPAREN QualIdent T_RPAREN
{
  $$ = new ASTNode(NULL, AST_OptQualIdent, 1);
  $$->addChild($2);
}
    |               /* empty */
{
  $$ = NULL;
}
    ;


QualIdent:          T_ID
{
  $$ = new ASTNode(NULL, AST_QualIdent, 1);
  $$->addChild($1, AST_ID);
}
    |               T_ID T_DOT T_ID
{
  $$ = new ASTNode(concat($1, concat($2, $3)), AST_QualIdent, 2);
  $$->addChild($1, AST_ID);
  $$->addChild($3, AST_ID);
}
    ;

IdentDef:           T_ID
{ 
  $$ = new ASTNode(NULL, AST_IdentDef, 1);
  $$->addChild($1, AST_ID);
}
    |               T_ID T_STAR
{
  $$ = new ASTNode(NULL, AST_IdentDef, 1);
  $$->addChild($1, AST_ID | EXPORTABLE);
}
    |               T_ID T_MINUS
{
  $$ = new ASTNode(NULL, AST_IdentDef, 1);
  $$->addChild($1, AST_ID | READONLY | EXPORTABLE);
}
    ;

%%



