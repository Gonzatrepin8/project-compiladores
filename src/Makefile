CC = gcc
CFLAGS = -Wno-error=implicit-function-declaration -g

TARGET = compiler

OBJS = lex.yy.o parser.tab.o ast.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

lex.yy.o: lex.yy.c parser.tab.h ast.h
	$(CC) $(CFLAGS) -c lex.yy.c -o lex.yy.o

parser.tab.o: parser.tab.c ast.h
	$(CC) $(CFLAGS) -c parser.tab.c -o parser.tab.o

ast.o: ast.c ast.h
	$(CC) $(CFLAGS) -c ast.c -o ast.o

lex.yy.c: flex.l
	flex -o lex.yy.c flex.l

parser.tab.c parser.tab.h: parser.y
	bison -d parser.y

clean:
	rm -f $(TARGET) $(OBJS) lex.yy.c parser.tab.c parser.tab.h