%{
#include <stdio.h>

%}

%%
"int"		{printf("long");}
"float"		{printf("double");}
%%

void main(int argc, char** argv)
{
	if(argc<=1) {
		printf("Usage: %s <input file>\n", argv[0]);
		exit(0);
	}
	yyin = fopen(argv[1], "r");

	yylex();
}
