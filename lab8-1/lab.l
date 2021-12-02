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

%%
