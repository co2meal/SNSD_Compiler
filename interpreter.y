%{
#include <stdio.h>
#include <string.h>
extern char yytext[];	// a string of current token
extern FILE* yyin;
extern int yylineno;
double vbltable[1000];
char idx2stringtable[1000][100];
int n_of_idx2stringtable = 0;
%}
%union {
double dval;
int vblno;
}

%token <vblno> NAME
%token <dval> NUMBER
%token IF ELSE WHILE RETURN SEMICOLON PLUS MINUS DIVIDE MULTIPLY LPAREN RPAREN ASSIGN

%left '<' '>'
%left MINUS PLUS
%left MULTIPLY DIVIDE
%right ASSIGN
%nonassoc UMINUS

%type <dval> expression statement
%%

statement_list
: statement
| statement_list statement
;

statement
: expression SEMICOLON { printf(" => %g\n", $1); }
// | if_statement SEMICOLON {}
// | while_statement {} etc...
| {}
| error SEMICOLON { print_error("syntax error"); }
;

expression
: expression PLUS expression { $$ = $1 + $3; }
| expression MINUS expression { $$ = $1 - $3; }
| expression MULTIPLY expression { $$ = $1 * $3; }
| expression DIVIDE expression
{
  if($3 == 0.0) {
    print_error("divide by zero");
  }
  else {
    $$ = $1 / $3;
  }
}
| NAME ASSIGN expression { $$ = vbltable[$1] = $3; }
| MINUS expression %prec UMINUS { $$ = -$2; }
| LPAREN expression RPAREN { $$ = $2; }
| NUMBER
| NAME { $$ = vbltable[$1]; }
| expression '<' expression { $$ = $1 < $3; }
| expression '>' expression { $$ = $1 > $3; }
| expression LE_OP expression { $$ = $1 <= $3; }
| expression GE_OP expression { $$ = $1 >= $3; }
| expression EQ_OP expression { $$ = $1 == $3; }
| expression NE_OP expression { $$ = $1 != $3; }
;

%%

int main()
{
	yyparse();
	
	return 0;
}

int yyerror(char *msg) 
{
	// printf("%s\n",msg);
}

int print_error(char *msg) {
  printf("%s\n",msg);
}

int string2idx(char* str) {
  int i;
  for(i=0;i<n_of_idx2stringtable;i++) {
    if (strcmp(idx2stringtable[i], str) == 0) break;
  }

  if (i == n_of_idx2stringtable) {
    strcpy(idx2stringtable[i], str);
    n_of_idx2stringtable++;
  }

  return i;
}