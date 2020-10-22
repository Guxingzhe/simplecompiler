/* 词法分析源码 */

%{
#include <string>
#include "ast.hpp" 
//parser.hpp需要ast.hpp内的定义
// parser.hpp是bison编译parser.y生成的头文件，内含token声明和yylval声明。
#include "parser.hpp"

#define SAVE_TOKEN  yylval.string = new std::string(yytext, yyleng)
#define TOKEN(t)    (yylval.token = t)
%}

%option noyywrap

%%
[0-9]+ { SAVE_TOKEN; return INTEGER; }
[a-zA-Z] { SAVE_TOKEN; return IDENTIFIER; }
"=" { return TOKEN(ASSIGN); }
"+" { return TOKEN(ADD); }
"-" { return TOKEN(SUB); }
[\r]|[\n]|[\r\n] { return TOKEN(EOL); }
%%

