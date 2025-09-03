CC = gcc
CFLAGS = -Wno-error=implicit-function-declaration

all: lex.yy.c compiler

lex.yy.c: flex.l
	flex flex.l

compiler: lex.yy.c
	$(CC) lex.yy.c $(CFLAGS) -o compiler

clean:
	rm -f lex.yy.c compiler
