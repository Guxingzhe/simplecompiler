/* 语法分析器源码 */

%{
#include "ast.hpp"
Node* stmt; 

extern int yylex();
extern void runcode();
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
%type <node> program stmt expr


%%
program: stmt
| program stmt
| program "q" {return 0;}
;

stmt: expr EOL{ stmt = $1; runcode();}
;

expr:
  INTEGER { $$ = new NInteger(atoi($1)); }
| expr ADD expr { $$ = new NBinaryOperate(*$1, $2, *$3);}
| expr SUB expr { $$ = new NBinaryOperate(*$1, $2, *$3); }
;
%%

