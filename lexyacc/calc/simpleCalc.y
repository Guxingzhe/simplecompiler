/*简单计算器*/
%{
#include <stdio.h>
%}

/* declare tokens */
%token NUMBER
%token ADD SUB MUL DIV ABS
%token EOL

%%
calclist: /*空规则*/  /* 从收入开头进行匹配 */
  | calclist exp EOL { printf("= %d\n", $2); }  /* EOL 代表一个表达式的结束 */
  | calclist EOL { printf("> "); } /* blank line or a comment */
  ;

exp: factor /* default $$ = $1 */
  | exp ADD factor { $$ = $1 + $2; }
  | exp SUB factor { $$ = $1 - $2; }
  ; 

factor: term { $$ = $1; }
  | factor MUL term { $$ = $1 * $2; }
  | factor DIV term { $$ = $1 / $2; }
  ;

term: NUMBER
  | ABS term { $$ = $2>=0? $2:-$2; }
  ;
%%

int main()
{
  printf("> "); 
  yyparse();
}

int yyerror(char *s)
{
  fprintf(stderr, "error: %s\n", s);
}
