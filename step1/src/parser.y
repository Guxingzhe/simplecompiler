/* 语法分析器源码 */

%{
#include <string>
#include "ast.hpp"
NodeList* root; /* the top level root node of AST */

extern int yylex();
void yyerror(const char* s) { std::printf("Error: %s\n", s); std::exit(1);}
%}


/* 将yylval定义为union数据类型，union成员和%uion内部声明相同。
   在flex源码中，可以通过yylval.string形式存储token的值。
   用yylval联合内的成员名称，可以通过%type指令为语法规则指定数据类型
*/
%union {
    NodeList* nodeList;
    Node* node;
    NIdentifier* identifier;
    NInteger* integer;
    
    std::string* string;
    int token;
}

/* 定义token，<>中表示数据（好像没有起作用），引用union内变量名 */
%token <string> IDENTIFIER INTEGER
%token <token> ADD SUB ASSIGN
%token <token> EOL

/* 定义语法规则数据类型，与union中的变量名对应 */
%type <nodeList> program stmts
%type <node> stmt expr
%type <identifier> identifier
%type <integer> integer

%start program

%%
integer:
  INTEGER { $$ = new NInteger(std::stoi(*$1));  delete $1;}
;
    
identifier:
  IDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
;

expr:
  integer
| identifier
| expr ADD expr { $$ = new NBinaryOperate(*$1, $2, *$3); }
| expr SUB expr { $$ = new NBinaryOperate(*$1, $2, *$3); }
;

stmt:
  identifier ASSIGN expr EOL { $$ = new NAssignment(*$1, *$3); }
| expr EOL
;

stmts:
  stmt { $$ = new NodeList(); $$->nodes.push_back($1);}
| stmts stmt { $1->nodes.push_back($2); }
;

program: stmts { root = $1;}
%%

