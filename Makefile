CC = gcc
CFLAGS = -Wno-error=implicit-function-declaration
SRCDIR = src
TESTDIR = tests

LEX_SRC = $(SRCDIR)/flex.l
YACC_SRC = $(SRCDIR)/parser.y
AST_SRC = $(SRCDIR)/ast.c

LEX_OBJ = $(SRCDIR)/lex.yy.c
YACC_OBJ = $(SRCDIR)/parser.tab.c
YACC_H = $(SRCDIR)/parser.tab.h
AST_OBJ = $(SRCDIR)/ast.o
EXEC = c-tds

all: $(EXEC)

$(LEX_OBJ): $(LEX_SRC)
	flex -o $@ $<

$(YACC_OBJ) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_OBJ) $(YACC_SRC)

$(AST_OBJ): $(AST_SRC)
	$(CC) -c $(AST_SRC) $(CFLAGS) -o $@

$(EXEC): $(LEX_OBJ) $(YACC_OBJ) $(AST_OBJ)
	$(CC) $(LEX_OBJ) $(YACC_OBJ) $(AST_OBJ) $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(LEX_OBJ) $(YACC_OBJ) $(YACC_H) $(AST_OBJ) $(EXEC)

.PHONY: test
test: $(EXEC)
	@echo "Running tests..."
	@failed=0; \
	for testfile in $(TESTDIR)/*; do \
		if [ -f $$testfile ]; then \
			echo "Running test: $$testfile"; \
			if ! ./$(EXEC) $$testfile; then \
				echo "Test failed: $$testfile"; \
				failed=1; \
			fi; \
		fi; \
	done; \
	exit $$failed

