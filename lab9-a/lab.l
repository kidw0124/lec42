%option noyywrap

%{
#include <stdio.h>
#include <string.h>

#define YY_DECL int yylex()

#include "lab.tab.h"

%}

%%
[ \t]		; // ignore all whitespace
"print"		{return T_PRINT;}
[0-9]+		{yylval.num = atoi(yytext); return T_NUM;}
[A-Za-z]([A-Za-z]|[0-9])*	{strcpy(yylval.name, yytext); return T_ID;}
\n		{return T_NEWLINE;}
":="		{return T_ASSIGN;}
"+"		{return T_PLUS;}
"-"		{return T_MINUS;}
"*"		{return T_MULTIPLY;}
"/"		{return T_DIVIDE;}
"%"		{return T_MOD;}
"("		{return T_LEFT;}
")"		{return T_RIGHT;}
"|"		{return T_OR;}
"^"		{return T_XOR;}
"&"		{return T_AND;}
"=="		{return T_EQ;}
"!="		{return T_NE;}
"<="		{return T_LE;}
"<"		{return T_LT;}
">="		{return T_GE;}
">"		{return T_GT;}
"~"		{return T_NOT;}

%%