%{

#include <stdio.h>
#include <stdlib.h>

extern int yylex();
extern int yyparse();
extern FILE* yyin;

void yyerror(const char* s);
%}

%union {
	int num;
	char name[80];
}

%token<num> T_NUM
%token<name> T_ID
%token T_PRINT
%token T_ASSIGN
%token T_PLUS T_MINUS T_MULTIPLY T_DIVIDE T_MOD
%token T_LEFT T_RIGHT
%token T_NEWLINE
%left T_PLUS T_MINUS
%left T_MULTIPLY T_DIVIDE T_MOD

%start start

%%

start: 	
	| start line
;

line: 	T_NEWLINE
    	| stmt T_NEWLINE
;

stmt:	T_ID T_ASSIGN {printf("lvalue %s\n", $1);} expr {printf(":=\n");}
	| T_PRINT T_ID {printf("print %s\n", $2);}
;

expr: 	T_NUM			{ printf("push %d\n", $1); }
	| T_ID			{ printf("rvalue %s\n", $1); }
	| expr T_PLUS expr	{ printf("+\n"); }
	| expr T_MINUS expr	{ printf("-\n"); }
	| expr T_MULTIPLY expr	{ printf("*\n"); }
	| expr T_DIVIDE expr	{ printf("/\n"); }
	| expr T_MOD expr	{ printf("%%\n"); }
	| T_LEFT expr T_RIGHT
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

	return 0;
}

void yyerror(const char* s) {
	fprintf(stderr, "Parse error: %s\n", s);
	exit(1);
}
