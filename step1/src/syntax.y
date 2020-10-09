/* 语法和语义分析Bison源码，生成语法树 */

%{
#include "syntax.tab.h"
%}

%%
[0-9]+ { return NUM; }
[a-zA-Z] { return ID; }
"+" { return ADD; }
"-" { return SUB; }
"=" { return ASIGN; }
%%

