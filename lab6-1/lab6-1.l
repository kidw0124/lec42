%{
#include <stdio.h>

int count0;
int count1;
%}

%%
"\n"		;
"0"		{ printf("zero\n"); count0++; }
"1"		{ printf("one\n"); count1++; }
"q"		{ printf("0: %d, 1: %d\n", count0, count1); exit(0); }
.		;
%%

void main(int argc, char** argv)
{
	count0 = 0;
	count1 = 0;
	if(argc>1)
		yyin = fopen(argv[1], "r");
	else	yyin = stdin;

	yylex();
}
