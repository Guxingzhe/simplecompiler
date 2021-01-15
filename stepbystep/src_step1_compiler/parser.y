/* 语法分析器源码 */

%{
#include "ast.hpp"
Node* astroot; /* the top level root node of AST */

extern int yylex();
void yyerror(const char* s) { std::printf("Error: %s\n", s); std::exit(1);}
%}


/* 定义token和语法规则可以使用的数据类型*/
%union {
    Node* node;/*语法规则使用的语法树节点类型*/
    
    char* str;/*token 使用的类型*/
    int token;
}
/* 声明token，并指定类型 */
%token <str> INTEGER
%token <token> ADD SUB EOL
/* 定义语法规则数据类型，与union中的变量名对应 */
%type <node> program expr


%%
program: expr EOL{ astroot = $1;YYACCEPT;} /* 或者return 0; 可以在回车后进行计算*/
;

expr:
  INTEGER { $$ = new NInteger(atoi($1)); }
| expr ADD expr { $$ = new NBinaryOperate(*$1, $2, *$3);}
| expr SUB expr { $$ = new NBinaryOperate(*$1, $2, *$3); }
;
%%

