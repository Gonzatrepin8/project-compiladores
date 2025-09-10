CC = gcc
CFLAGS = -Wno-error=implicit-function-declaration

all: lex.yy.c parser.tab.c compiler

lex.yy.c: flex.l
	flex flex.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

compiler: lex.yy.c parser.tab.c
	$(CC) lex.yy.c parser.tab.c $(CFLAGS) -o compiler

clean:
	rm -f lex.yy.c parser.tab.c compiler
