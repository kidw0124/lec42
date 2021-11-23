%{

#include <stdio.h>
#include <stdlib.h>

FILE* yyin;

int yylex(void);
void yyerror(const char* s);
%}

%%
F:
	| F L
;

L:	S '\n'		{ printf("Value = %d\n", $1); }

S: 	S B 		{ $$ = $1 * 2 + $2; }
	| B		{ $$ = $1; }
;

B: 	'0'		{ $$ = 0; }
	| '1'		{ $$ = 1; }
;

%%

int main(int argc, char **argv) {
	if(argc < 2) {
		printf("An input program is required\n");
		exit(0);
	}
	if(!(yyin = fopen(argv[1], "r"))) {
		printf("File not open: %s\n", argv[1]);
		exit(0);
	}

	do {
		yyparse();
	} while(!feof(yyin));

	fclose(yyin);

	return 0;
}

int yylex(void)
{
	return fgetc(yyin);
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
