%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* yyin;

int yylex(void);
void yyerror(const char* s);
%}

%union {
	struct {
		int x;
		int y;
	} pos;
	struct {
		int dx;
		int dy;
	} dis;
}

%type<pos> S;
%type<dis> I;

%%
F:
	| F L
;

L:	S '\n'		{ printf("Position = %d, %d\n", $1.x, $1.y); }
;

S: 'B'			{ $$.x = 0; $$.y = 0; }
	| S I		{ $$.x = $1.x + $2.dx; $$.y = $1.y+ $2.dy; }
;

I: 'E'			{ $$.dx=1, $$.dy=0; }
	| 'W'		{ $$.dx=-1, $$.dy=0; }
	| 'S'		{ $$.dx=0, $$.dy=-1; }
	| 'N'		{ $$.dx=0, $$.dy=1; }
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
