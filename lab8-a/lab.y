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
%token T_NEWLINE
%token T_ADD
%token T_SUB
%token T_MUL
%token T_DIV
%token T_MOD
%token T_LEFTP
%token T_RIGHTP
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

expr:	term moreterms
;

moreterms:
	| T_ADD term {puts("+");} moreterms
	| T_SUB term {puts("-");} moreterms
;

term:	factor morefactors
;

morefactors:
	| T_MUL factor {puts("*");} morefactors
	| T_DIV factor {puts("/");} morefactors
	| T_MOD factor {puts("%");} morefactors
;

factor: T_LEFTP expr T_RIGHTP
	| T_NUM {printf("push %d\n", $1);}
	| T_ID {printf("rvalue %s\n", $1);}
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
