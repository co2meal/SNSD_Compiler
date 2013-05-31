%option noyywrap
%{
#include "y.tab.h"
#include <math.h>
extern double vbltable[26];
extern char idx2stringtable[1000][100];
extern int n_of_idx2stringtable;
%}
%%
([0-9]+|([0-9]*\.[0-9]+)) {
yylval.dval = atof(yytext); return NUMBER;
}
[ \t] ; /* ignore white space */
"else"			{  return(ELSE); }
"if"			{ return(IF); }
"return"			{ return(RETURN); }
"while"			{ return(WHILE); }
"$" { return 0; /* end of input */ }
[_A-Za-z][_A-Za-z0-9]* { yylval.vblno = string2idx(yytext); return NAME; }
\n |
. return yytext[0];
%%