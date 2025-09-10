CC = gcc
CFLAGS = -Wno-error=implicit-function-declaration
SRCDIR = src
TESTDIR = tests

LEX_SRC = $(SRCDIR)/flex.l
YACC_SRC = $(SRCDIR)/parser.y

LEX_OBJ = $(SRCDIR)/lex.yy.c
YACC_OBJ = $(SRCDIR)/parser.tab.c
YACC_H = $(SRCDIR)/parser.tab.h
EXEC = c-tds

all: $(EXEC)

$(LEX_OBJ): $(LEX_SRC)
	flex -o $@ $<

$(YACC_OBJ) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_OBJ) $(YACC_SRC)

$(EXEC): $(LEX_OBJ) $(YACC_OBJ)
	$(CC) $(LEX_OBJ) $(YACC_OBJ) $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(LEX_OBJ) $(YACC_OBJ) $(YACC_H) $(EXEC)

.PHONY: test
test: $(EXEC)
	@echo "Running tests..."
	@for testfile in $(TESTDIR)/*; do \
		if [ -f $$testfile ]; then \
			echo "Running test: $$testfile"; \
			./$(EXEC) < $$testfile; \
		fi \
	done
