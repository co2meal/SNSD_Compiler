all: interpreter.exe

interpreter.exe: y.tab.c lex.yy.c
	gcc y.tab.c lex.yy.c -o interpreter.exe

y.tab.c: interpreter.y
	bison interpreter.y -d -b y

lex.yy.c: interpreter.l
	flex interpreter.l
