/* 语法分析器源码 */

%{
#include <string>
#include "ast.hpp"
Module *rootNode; /* the top level root node of AST */

extern int yylex();
void yyerror(const char *s) { std::printf("Error: %s\n", s); std::exit(1);}
%}


/* 将yylval定义为union数据类型，union成员和%uion内部声明相同。
   在flex源码中，可以通过yylval.string形式存储token的值。
   用yylval联合内的成员名称，可以通过%type指令为语法规则指定数据类型
*/
%union {
    Module *root;
    Node *node;
    NIdentifier *ident;
    NInteger *integer;
    
    std::string *string;
    int token;
}

/* 定义token，<>中表示数据（好像没有起作用），引用union内变量名 */
%token <string> IDENTIFIER INT
%token <token> ADD SUB ASSIGN
%token <token> EOL

/* 定义语法规则数据类型，与union中的变量名对应 */
%type <root> program exprs
%type <node> expr assign binaryOP var
%type <ident> ident
%type <integer> integer

%start program

%%
program: exprs { rootNode = $1;}
    ;

exprs:
    expr { $$ = new Module(); $$->nodes.push_back($1);}
    | exprs expr { $1->nodes.push_back($2); }
    ;

expr: assign
    | binaryOP
    ;

assign:
    ident ASSIGN integer { $$ = new NAssignment(*$1, *$3); }
    ;

binaryOP:
    var ADD var { $$ = new NBinaryOperator(*$1, $2, *$3); }
    | var SUB var { $$ = new NBinaryOperator(*$1, $2, *$3); }
    ;

var: ident
    | integer
    ;

ident:
    IDENTIFIER { $$ = new NIdentifier(*$1); delete $1; }
    ;

integer:
    INT { $$ = new NInteger(atoi($1->c_str()));  delete $1;}
    ;
%%

