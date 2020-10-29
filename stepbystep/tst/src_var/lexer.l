/* 词法分析源码 */

%{
#include "ast.hpp"  //parser.hpp需要ast.hpp内的定义
#include "parser.hpp"
#include <string>

#define TOKEN(t)    yylval.token = t;
%}

%option noyywrap

%%
[0-9]+ { yylval.string = new std::string(yytext, yyleng);return INTEGER; }
[a-zA-Z]+ { yylval.string = new std::string(yytext, yyleng);return IDENTIFIER; }
"=" { return TOKEN(ASSIGN); }
[\r]|[\n]|[\r\n] { return TOKEN(EOL); }
%%

