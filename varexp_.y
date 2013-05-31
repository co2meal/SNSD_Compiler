%{
#include <stdio.h>
#include <string.h>
extern char yytext[];	// a string of current token
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
%token IF ELSE WHILE RETURN
%left '-' '+'
%left '*' '/'
%right '='
%nonassoc UMINUS
%type <dval> expression
%%

statement_list: statement '\n'
| statement_list statement '\n'
;
statement: NAME '=' expression { vbltable[$1] = $3; printf("= %g\n", $3);}
| expression { printf("= %g\n", $1); }
;
expression: expression '+' expression { $$ = $1 + $3; }
| expression '-' expression { $$ = $1 - $3; }
| expression '*' expression { $$ = $1 * $3; }
| expression '/' expression
{ if($3 == 0.0)
yyerror("divide by zero");
else
$$ = $1 / $3;
}
| '-' expression %prec UMINUS { $$ = -$2; }
| '(' expression ')' { $$ = $2; }
| NUMBER
| NAME { $$ = vbltable[$1]; }
;
%%
int main()
{
	yyparse();
	
	return 0;
}
int yyerror(char *msg) 
{
	printf("%s\n",msg);

	return -1;
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