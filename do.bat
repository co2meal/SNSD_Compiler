flex interpreter.l
bison interpreter.y -d -b y
cl lex.yy.c y.tab.c /Feinter
inter.exe