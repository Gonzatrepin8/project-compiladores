CC = gcc
CFLAGS = -Wno-error=implicit-function-declaration -Wno-format-truncation
SRCDIR = src
TESTDIR = tests

LEX_SRC = $(SRCDIR)/flex.l
YACC_SRC = $(SRCDIR)/parser.y
AST_SRC = $(SRCDIR)/ast/ast.c
SYMTAB_SRC = $(SRCDIR)/symbol_table/symtab.c
BUILDSYMTAB_SRC = $(SRCDIR)/symbol_table/build_symtab.c
UTILS_SRC = $(SRCDIR)/utils/utils.c
TYPECHECK_SRC = $(SRCDIR)/type_check/type_check.c
THREE_ADDRESS_SRC = $(SRCDIR)/three_address/three_address.c
ASSEMBLY_SRC = $(SRCDIR)/assembly/assembly_gen.c
PLATFORM_SRC = $(SRCDIR)/assembly/platform.c
OPT_SRC = $(SRCDIR)/opt/opt.c
MAIN_SRC = $(SRCDIR)/main.c

LEX_OBJ = $(SRCDIR)/lex.yy.c
YACC_OBJ = $(SRCDIR)/parser.tab.c
YACC_H   = $(SRCDIR)/parser.tab.h
AST_OBJ = $(SRCDIR)/ast/ast.o
SYMTAB_OBJ = $(SRCDIR)/symbol_table/symtab.o
BUILDSYMTAB_OBJ = $(SRCDIR)/symbol_table/build_symtab.o
UTILS_OBJ = $(SRCDIR)/utils/utils.o
TYPECHECK_OBJ = $(SRCDIR)/type_check/type_check.o
THREE_ADDRESS_OBJ = $(SRCDIR)/three_address/three_address.o
ASSEMBLY_OBJ = $(SRCDIR)/assembly/assembly_gen.o
PLATFORM_OBJ = $(SRCDIR)/assembly/platform.o
OPT_OBJ = $(SRCDIR)/opt/opt.o
MAIN_OBJ = $(SRCDIR)/main.o
EXEC = c-tds

all: $(EXEC)

$(LEX_OBJ): $(LEX_SRC)
	flex -o $@ $<

$(YACC_OBJ) $(YACC_H): $(YACC_SRC)
	bison -d -o $(YACC_OBJ) $(YACC_SRC)

$(AST_OBJ): $(AST_SRC)
	$(CC) -c $(AST_SRC) $(CFLAGS) -o $@

$(SYMTAB_OBJ): $(SYMTAB_SRC)
	$(CC) -c $(SYMTAB_SRC) $(CFLAGS) -o $@

$(BUILDSYMTAB_OBJ): $(BUILDSYMTAB_SRC)
	$(CC) -c $(BUILDSYMTAB_SRC) $(CFLAGS) -o $@

$(UTILS_OBJ): $(UTILS_SRC)
	$(CC) -c $(UTILS_SRC) $(CFLAGS) -o $@

$(TYPECHECK_OBJ): $(TYPECHECK_SRC)
	$(CC) -c $(TYPECHECK_SRC) $(CFLAGS) -o $@

$(THREE_ADDRESS_OBJ): $(THREE_ADDRESS_SRC)
	$(CC) -c $(THREE_ADDRESS_SRC) $(CFLAGS) -o $@

$(ASSEMBLY_OBJ): $(ASSEMBLY_SRC)
	$(CC) -c $(ASSEMBLY_SRC) $(CFLAGS) -Isrc/assembly -o $@

$(PLATFORM_OBJ): $(PLATFORM_SRC)
	$(CC) -c $(PLATFORM_SRC) $(CFLAGS) -o $@

$(OPT_OBJ): $(OPT_SRC)
	$(CC) -c $(OPT_SRC) $(CFLAGS) -o $@

$(MAIN_OBJ): $(MAIN_SRC)
	$(CC) -c $(MAIN_SRC) $(CFLAGS) -o $@

$(EXEC): $(LEX_OBJ) $(YACC_OBJ) $(AST_OBJ) $(SYMTAB_OBJ) $(BUILDSYMTAB_OBJ) $(TYPECHECK_OBJ) $(THREE_ADDRESS_OBJ) $(ASSEMBLY_OBJ) $(PLATFORM_OBJ) $(MAIN_OBJ) $(UTILS_OBJ) $(OPT_OBJ)
	$(CC) $(LEX_OBJ) $(YACC_OBJ) $(AST_OBJ) $(SYMTAB_OBJ) $(BUILDSYMTAB_OBJ) $(TYPECHECK_OBJ) $(UTILS_OBJ) $(THREE_ADDRESS_OBJ) $(ASSEMBLY_OBJ) $(PLATFORM_OBJ) $(MAIN_OBJ) $(OPT_OBJ) $(CFLAGS) -o $@

.PHONY: clean
clean:
	rm -f $(LEX_OBJ) $(YACC_OBJ) $(YACC_H) $(OPT_OBJ) $(AST_OBJ) $(BUILDSYMTAB_OBJ) $(SYMTAB_OBJ) $(UTILS_OBJ) $(TYPECHECK_OBJ) $(THREE_ADDRESS_OBJ) $(ASSEMBLY_OBJ) $(PLATFORM_OBJ) $(MAIN_OBJ) $(EXEC)

.PHONY: test
test: $(EXEC)
	@printf "=========================================\n"
	@printf "           RUNNING ALL TESTS\n"
	@printf "=========================================\n"
	@failed=0; \
	\
	printf "\n--- Running tests that SHOULD PASS ---\n"; \
	for testfile in $(TESTDIR)/pasan/*; do \
		if [ -f $$testfile ]; then \
			printf "Testing $$testfile... "; \
			if ! ./$(EXEC) -target assembly $$testfile > /dev/null 2>&1; then \
				printf "\033[0;31m[FAIL]\033[0m\n"; \
				echo "       > ERROR: This test was expected to pass, but the compiler failed."; \
				failed=1; \
			else \
				printf "\033[0;32m[OK]\033[0m\n"; \
			fi; \
		fi; \
	done; \
	\
	printf "\n--- Running tests that SHOULD FAIL ---\n"; \
	for testfile in $(TESTDIR)/noPasan/*; do \
		if [ -f $$testfile ]; then \
			printf "Testing $$testfile... "; \
			if ./$(EXEC) -target assembly $$testfile > /dev/null 2>&1; then \
				printf "\033[0;31m[FAIL]\033[0m\n"; \
				echo "       > ERROR: This test was expected to fail, but the compiler succeeded."; \
				failed=1; \
			else \
				printf "\033[0;32m[OK]\033[0m\n"; \
			fi; \
		fi; \
	done; \
	\
	printf "\n=========================================\n"; \
	if [ "$$failed" -eq 0 ]; then \
		printf "         \033[0;32mALL TESTS PASSED!\033[0m\n"; \
	else \
		printf "       \033[0;31mSOME TESTS FAILED\033[0m\n"; \
	fi; \
	printf "=========================================\n"; \
	exit $$failed
