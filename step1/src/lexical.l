/* 词法分析flex源码，识别token */

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

