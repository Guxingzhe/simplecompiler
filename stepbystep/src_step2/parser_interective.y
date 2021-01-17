/* 语法分析器源码 */

%{
#include <string>
#include "ast.hpp"
Node* stmt; 

extern int yylex();
extern void runcode();
void yyerror(const char* s) { std::printf("Error: %s\n", s); std::exit(1);}
%}


%union {
    NBlock* block;
    Node* node;
    NIdentifier* ident;
    
    std::string* string;
    int token;
}
/* 定义token，<>中表示数据（好像没有起作用），引用union内变量名 */
%token <string> IDENTIFIER INTEGER
%token <token> ADD SUB MUL DIV ASSIGN EOL
/* 定义语法规则数据类型，与union中的变量名对应 */
%type <block> stmts
%type <node> stmt expr term
%type <ident> ident
/*%start stmts*/

%left ADD SUB
%left MUL DIV


%%
stmts: stmt
| stmts stmt
| stmts "exit" {return 0;}
;

stmt:
  ident ASSIGN expr EOL { $$ = new NAssignment(*$1, *$3); stmt=$$; runcode();}
| expr EOL {$$ = $1; stmt=$$; runcode();}
;

expr:
  term
| expr ADD term { $$ = new NBinaryOperate(*$1, $2, *$3); }
| expr SUB term { $$ = new NBinaryOperate(*$1, $2, *$3); }
| expr MUL term { $$ = new NBinaryOperate(*$1, $2, *$3); }
| expr DIV term { $$ = new NBinaryOperate(*$1, $2, *$3); }
;

term:
  ident { $$ = $1; }
| INTEGER { $$ = new NInteger(std::stoi(*$1));  delete $1;}
;

ident:
  IDENTIFIER { $$ = new NIdentifier(*$1); delete $1;}
;
%%

