/* 语法分析器源码 */

%{
#include <string>
#include "ast.hpp"
NBlock* root; /* the top level root node of AST */

extern int yylex();
void yyerror(const char* s);
%}


%union {
    NBlock* block;
    Node* node;
    NIdentifier* ident;
    
    std::string* string;
    int token;
}

%token <string> IDENTIFIER INTEGER
%token <token> ASSIGN EOL

%type <block> program stmts
%type <node> stmt integer
%type <ident> ident


%%
program: stmts { root = $1;}
       ;

stmts:
  stmt { $$ = new NBlock(); $$->nodes.push_back($1);}
| stmts stmt { $1->nodes.push_back($2); }
;

stmt:
  ident ASSIGN integer EOL { $$ = new NAssignment(*$1, *$3); printf(">");}
| ident EOL {$$ = $1; }
;

integer:
 INTEGER { $$ = new NInteger(std::stoi(*$1));  delete $1;}
;

ident:
  IDENTIFIER { $$ = new NIdentifier(*$1); delete $1;}
;
%%


void yyerror(const char* s) { std::printf("Error: %s\n", s); std::exit(1);}
