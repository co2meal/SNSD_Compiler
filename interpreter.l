%option noyywrap



%{
#include "y.tab.h"
#include <math.h>
extern double vbltable[26];
extern char idx2stringtable[1000][100];
extern int n_of_idx2stringtable;


#define YY_INPUT(buf,result,max_size) result = get_input(buf, max_size);

static int get_input(char *buf, int size)
{
  char line[100];
  if (feof(yyin))
    return YY_NULL;
  printf("?- ");
  gets(line);

  if (!line)
    return YY_NULL;

  if (strlen(line) > size - 2) {
    print_error("input line too long");
    return YY_NULL;
  }

  strcpy(buf, line);
  strcat(buf, "\n");

  return strlen(buf);
}


%}
%%
([0-9]+|([0-9]*\.[0-9]+)) {
yylval.dval = atof(yytext); return NUMBER;
}
[ \t\n] ; /* ignore white space */

"<="     { return(LE_OP); }
">="     { return(GE_OP); }
"=="     { return(EQ_OP); }
"!="     { return(NE_OP); }
"<"      { return(L_OP); }
">"      { return(G_OP); }
"+"      { return(PLUS); }
"-"      { return(MINUS); }
"*"      { return(MULTIPLY); }
"/"      { return(DIVIDE); }
"="      { return(ASSIGN); }
"("      { return(LPAREN); }
")"      { return(RPAREN); }
";"      { return(SEMICOLON); }
"else"   {  return(ELSE); }
"if"     { return(IF); }
"return" { return(RETURN); }
"while"	 { return(WHILE); }
"$"      { return 0; /* end of input */ }
[_A-Za-z][_A-Za-z0-9]* { yylval.vblno = string2idx(yytext); return NAME; }
. {print_error("lexical error"); }
%%
