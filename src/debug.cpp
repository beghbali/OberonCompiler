#include "debug.h"
#include "symboltable.h"

void dumpStack(stack<inputStruct*> s) 
{
  while(!s.empty())
    {
      inputStruct* top = s.top();
      printf("%s,%d,%#x\n",top->filename, top->line, (top->file ? top->file : 0x0000));
      s.pop();
    }
}

void dumpHashTable(HASHTABLE table)
{
  HASHTABLE::iterator p = table.begin();
  while(p != table.end())
    cout<<*(p++)<<endl;
}

void dumpBuffer(char* buff, int size)
{
  cout<<"[";
  for(int i = 0; i < size; i++)
    cout<<buff[i];
  cout<<"]"<<endl;
}
      
void print(inputStruct* x)
{
  cout<<"("<<x->filename;
  cout<<","<<x->line;
  cout<<","<<x->file<<")"<<endl;
}

void d_printTable(ChainNode** table, int capacity)
{
  for(int i = 0; i < capacity; i++)
    {
      cout<<"["<<i<<"]=";
      if(table[i] == NULL)
	cout<<"NULL"<<endl;
      else
	cout<<table[i]->data->getName()<<endl;
    }
}

void traceAST(ASTNode* node)
{
  if(!node)
    return;
  switch(GETTYPE(node->nodetype))
    {
    case AST_ID             : cout<<"ID "<<endl;break;
    case AST_IdentDef       : cout<<"IdentDef "<<endl;break;
    case AST_QualIdent      : cout<<"QualIdent "<<endl;break;
    case AST_OptQualIdent   : cout<<"OptQualIdent "<<endl;break;
    case AST_IdentList      : cout<<"IdentList "<<endl;break;
    case AST_Designator2    : cout<<"Designator2 "<<endl;break;
    case AST_Designator     : cout<<"Designator "<<endl;break;
    case AST_MulOp          : cout<<"MulOp "<<endl;break;
    case AST_AddOp          : cout<<"AddOp "<<endl;break;
    case AST_Relation       : cout<<"Relation "<<endl;break;
    case AST_Element        : cout<<"Element "<<endl;break;
    case AST_ElementList    : cout<<"ElementList "<<endl;break;
    case AST_OptElementList : cout<<"OptElementList "<<endl;break;
    case AST_Set            : cout<<"Set "<<endl;break;
    case AST_Factor         : cout<<"Factor "<<endl;break;
    case AST_TILDE          : cout<<"TILDE  "<<endl;break;
    case AST_NIL            : cout<<"NIL "<<endl;break;
    case AST_FALSE          : cout<<"FALSE "<<endl;break;
    case AST_TRUE           : cout<<"TRUE "<<endl;break;
    case AST_STR_LITERAL    : cout<<"STR_LITERAL "<<endl;break;
    case AST_CHAR_LITERAL   : cout<<"CHAR_LITERAL "<<endl;break;
    case AST_REAL_LITERAL   : cout<<"REAL_LITERAL "<<endl;break;
    case AST_INT_LITERAL    : cout<<"INT_LITERAL "<<endl;break;
    case AST_OptSign        : cout<<"OptSign "<<endl;break;
    case AST_Exprk          : cout<<"Exprk "<<endl;break;
    case AST_NL             : cout<<"NL "<<endl;break;
    case AST_Expr3          : cout<<"Expr3 "<<endl;break;
    case AST_Expr2          : cout<<"Expr2 "<<endl;break;
    case AST_Expr1          : cout<<"Expr1 "<<endl;break;
    case AST_Expr           : cout<<"Expr "<<endl;break;
    case AST_ExprList2      : cout<<"ExprList2 "<<endl;break;
    case AST_ExprList      : cout<<"ExprList "<<endl;break;
    case AST_ConstExpr      : cout<<"ConstExpr "<<endl;break;
    case AST_Guard          : cout<<"Guard "<<endl;break;
    case AST_ReturnStmt     : cout<<"ReturnStmt "<<endl;break;
    case AST_ExitStmt       : cout<<"ExitStmt "<<endl;break;
    case AST_GuardList      : cout<<"GuardList "<<endl;break;
    case AST_WithStmt       : cout<<"WithStmt "<<endl;break;
    case AST_LoopStmt       : cout<<"LoopStmt "<<endl;break;
    case AST_OptBy          : cout<<"OptBy "<<endl;break;
    case AST_ForStmt        : cout<<"ForStmt "<<endl;break;
    case AST_RepeatStmt     : cout<<"RepeatStmt "<<endl;break;
    case AST_WhileStmt      : cout<<"WhileStmt "<<endl;break;
    case AST_CaseLabels     : cout<<"CaseLabels "<<endl;break;
    case AST_CaseLabelsList : cout<<"CaseLabelsList "<<endl;break;
    case AST_Case           : cout<<"Case "<<endl;break;
    case AST_CaseList       : cout<<"CaseList "<<endl;break;
    case AST_CaseStmt       : cout<<"CaseStmt "<<endl;break;
    case AST_OptElse        : cout<<"OptElse "<<endl;break;
    case AST_OptElsifs      : cout<<"OptElsifs "<<endl;break;
    case AST_IfStmt         : cout<<"IfStmt "<<endl;break;
    case AST_OptExprList    : cout<<"OptExprList "<<endl;break;
    case AST_ProcCall       : cout<<"ProcCall "<<endl;break;
    case AST_AssignStmt     : cout<<"AssignStmt "<<endl;break;
    case AST_OutputItems    : cout<<"OutputItems "<<endl;break;
    case AST_OutputStmt     : cout<<"OutputStmt "<<endl;break;
    case AST_InputStmt      : cout<<"InputStmt "<<endl;break;
    case AST_Stmt           : cout<<"Stmt "<<endl;break;
    case AST_StmtList       : cout<<"StmtList "<<endl;break;
    case AST_FieldList      : cout<<"FieldList "<<endl;break;
    case AST_FieldsList     : cout<<"FieldsList "<<endl;break;
    case AST_BasicType      : cout<<"BasicType "<<endl;break;
    case AST_Type           : cout<<"Type "<<endl;break;
    case AST_OptReceiver    : cout<<"OptReceiver "<<endl;break;
    case AST_OptReturnType  : cout<<"OptReturnType "<<endl;break;
    case AST_IdList         : cout<<"IdList "<<endl;break;
    case AST_ParamDecl      : cout<<"ParamDecl "<<endl;break;
    case AST_ParamList      : cout<<"ParamList "<<endl;break;
    case AST_OptParamList   : cout<<"OptParamList "<<endl;break;
    case AST_FormalParams   : cout<<"FormalParams "<<endl;break;
    case AST_OptFormalParams : cout<<"OptFormalParams "<<endl;break;
    case AST_FwdProcDecl    : cout<<"FwdProcDecl "<<endl;break;
    case AST_OptStmts       : cout<<"OptStmts "<<endl;break;
    case AST_ProcDecl       : cout<<"ProcDecl "<<endl;break;
    case AST_VarDecl        : cout<<"VarDecl "<<endl;break;
    case AST_VarDeclList2   : cout<<"VarDeclList2 "<<endl;break;
    case AST_VarDeclList    : cout<<"VarDeclList "<<endl;break;
    case AST_TypeDecl       : cout<<"TypeDecl "<<endl;break;
    case AST_TypeDeclList   : cout<<"TypeDeclList "<<endl;break;
    case AST_ConstDecl      : cout<<"ConstDecl "<<endl;break;
    case AST_ConstDeclList  : cout<<"ConstDeclList "<<endl;break;
    case AST_CTDecl         : cout<<"CTDecl "<<endl;break;
    case AST_CVTDecl        : cout<<"CVTDecl "<<endl;break;
    case AST_ProcDeclList2  : cout<<"ProcDeclList2 "<<endl;break;
    case AST_ProcDeclList   : cout<<"ProcDeclList "<<endl;break;
    case AST_CTDeclList     : cout<<"CTDeclList "<<endl;break;
    case AST_CVTDeclList    : cout<<"CVTDeclList "<<endl;break;
    case AST_DeclSeq        : cout<<"DeclSeq "<<endl;break;
    case AST_ImportList     : cout<<"ImportList "<<endl;break;
    case AST_ImportDecl     : cout<<"ImportDecl "<<endl;break;
    case AST_OptImportDecl  : cout<<"OptImportDecl "<<endl;break;
    case AST_Module         : cout<<"Module "<<endl;break;
    case AST_ModuleList     : cout<<"ModuleList "<<endl;break;
    case AST_DeclarationList     : cout<<"DeclarationList "<<endl;break;
    case AST_DeclarationsSection : cout<<"DeclarationsSection "<<endl;break;
    case AST_MainStmtsSection    : cout<<"MainStmtsSection "<<endl;break;
    case AST_Program        : cout<<"Program "<<endl;break; 
    case AST_OptVar         : cout<<"OptVar "<<endl;break;
    default:
      cout<<"ERROR NODE"<<GETTYPE(node->nodetype)<<endl;
    }
}
