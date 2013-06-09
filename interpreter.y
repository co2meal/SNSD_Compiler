%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "value.h"
#include "node.h"
extern FILE* yyin;
extern int yylineno;

int statement_depth = 0;
%}

%union {
  Node* pNode;
  char* string;
}

%token<string> IDENTIFIER INTEGER DOUBLE
%token IF ELSE WHILE END
%token RETURN SEMICOLON ASSIGN
%token PLUS MINUS DIVIDE MULTIPLY
%token LPAREN RPAREN
%token L_OP G_OP LE_OP GE_OP EQ_OP NE_OP

%right ASSIGN
%left L_OP G_OP LE_OP GE_OP EQ_OP NE_OP
%left MINUS PLUS
%left MULTIPLY DIVIDE
%nonassoc UMINUS

%type <pNode> expression statement identifier statement_list if_statement while_statement
%%

program
: statement { Value value; evaluate($1, &value); printf(" type of value = %d\n", value.type);print_value(&value); }
| program statement { Value value; evaluate($2, &value); print_value(&value); }
;

statement_list
: statement { init_node(&$$, NTSTATEMENTLIST); push_child_node($$, $1); }
| statement_list statement { $$ = $1; push_child_node($$, $2); }
;

statement
: start_of_statement expression SEMICOLON end_of_statement { init_node(&$$, NTSTATEMENT); push_child_node($$, $2); }
| start_of_statement if_statement end_of_statement { $$ = $2; }
| start_of_statement while_statement end_of_statement { $$ = $2;}
| error SEMICOLON { print_error("syntax error"); statement_depth = 0;}
| SEMICOLON {}
;

start_of_statement
: { statement_depth ++;}

end_of_statement
: { statement_depth --;}

expression
: expression PLUS expression { printf("add operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = PLUS; push_child_node($$, $1); push_child_node($$, $3);}
| expression MINUS expression { printf("sub operator reduced.\n");init_node(&$$, NTBINARYOPERATOR); $$->op_token = MINUS; push_child_node($$, $1); push_child_node($$, $3); }
| expression MULTIPLY expression { printf("mul operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = MULTIPLY; push_child_node($$, $1); push_child_node($$, $3);}
| expression DIVIDE expression {  printf("div operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = DIVIDE; push_child_node($$, $1); push_child_node($$, $3);}
| identifier ASSIGN expression { printf("assignement reduced!\n");init_node(&$$, NTASSIGNMENT); push_child_node($$, $1); push_child_node($$, $3);}
| MINUS expression %prec UMINUS { }
| LPAREN expression RPAREN { }
| INTEGER { init_node(&$$, NTINTEGER); $$->value.type = INTVALUE; $$->value.intValue = atoi($1); free($1); printf("$$->value.intValue: %d\n", $$->value.intValue);}
| DOUBLE { init_node(&$$, NTDOUBLE); $$->value.type = DOUBLEVALUE; $$->value.doubleValue = atof($1); free($1); printf("$$->value.doubleValue: %lf\n", $$->value.doubleValue);}
| identifier
| expression G_OP expression {  printf("compare operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = G_OP; push_child_node($$, $1); push_child_node($$, $3);}
| expression L_OP expression {  printf("compare operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = L_OP; push_child_node($$, $1); push_child_node($$, $3);}
| expression LE_OP expression {  printf("compare operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = LE_OP; push_child_node($$, $1); push_child_node($$, $3);}
| expression GE_OP expression {  printf("compare operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = GE_OP; push_child_node($$, $1); push_child_node($$, $3);}
| expression EQ_OP expression {  printf("compare operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = EQ_OP; push_child_node($$, $1); push_child_node($$, $3);}
| expression NE_OP expression {  printf("compare operator reduced.\n"); init_node(&$$, NTBINARYOPERATOR); $$->op_token = NE_OP; push_child_node($$, $1); push_child_node($$, $3);}
;

identifier
: IDENTIFIER { printf("identifier reduced!\n");init_node(&$$, NTIDENTIFIER); strcpy($$->name, $1); free($1); }

if_statement
: IF LPAREN expression RPAREN statement_list END { init_node(&$$, NTIFSTATEMENT); push_child_node($$, $3); push_child_node($$, $5); }
| IF LPAREN expression RPAREN statement_list ELSE statement_list END

while_statement
: WHILE LPAREN expression RPAREN statement_list END { init_node(&$$, NTWHILESTATEMENT); push_child_node($$, $3); push_child_node($$, $5); }

%%

int main()
{
  printf("%d\n", (int)sizeof(Node));
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

