/* 词法分析源码 */

%{
#include "ast.hpp"  //parser.hpp需要ast.hpp内的定义
#include "parser.hpp"// parser.hpp是bison编译parser.y生成的头文件，内含token声明和yylval声明。
%}

%option noyywrap
/*//只能处理一个文件，noyywrap可以不需要链接fl库。c++不能连接fl库*/
/*%option interactive*/

%%
[0-9]+ { yylval.str=yytext; return INTEGER; }
"+" {  yylval.token = ADD; return ADD; }
"-" {  yylval.token = SUB; return SUB; }
[\r]|[\n]|[\r\n] { return EOL; }
%%

