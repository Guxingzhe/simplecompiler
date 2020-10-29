/* 计算器词法分析器 */
/* 识别出用于计算器的记号并把他们输出 */

%{
#include "simpleCalc.tab.h"
%}

%%
"+" { return ADD; }
"-" { return SUB; }
"*" { return MUL; }
"/" { return DIV; }
"|" { return ABS; }
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
\n { return EOL; }
[ \t] { /* 忽略空白 */}
. { printf("Mystery character %c\n", *yytext); }
%%

