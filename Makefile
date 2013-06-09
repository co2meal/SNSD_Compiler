all: interpreter.exe

clean:
	rm y.tab.c lex.yy.c

interpreter.exe: y.tab.c lex.yy.c value.c node.c evaluate.c value.h node.h function.h function.c frame.c frame.h
	gcc y.tab.c lex.yy.c value.c node.c function.c evaluate.c frame.c -o interpreter.exe

y.tab.c: interpreter.y
	bison interpreter.y -d -b y

lex.yy.c: interpreter.l
	flex interpreter.l

value.c: value.h

node.c: node.h

