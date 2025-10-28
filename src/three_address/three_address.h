#ifndef THREE_ADDR_H
#define THREE_ADDR_H

#include "../ast/ast.h"
#include <stdio.h>

static char *gen_expr(AST *n, FILE *out);
static void gen_stmt(AST *n, FILE *out);
void generate_tac(AST *root, FILE *out);

typedef enum {
    TAC_LABEL,
    TAC_ASSIGN,
    TAC_GOTO,
    TAC_IFZ,
    TAC_CALL,
    TAC_SUM,
    TAC_MINUS,
    TAC_NEG,
    TAC_DIV,
    TAC_MOD,
    TAC_MUL,
    TAC_LESS,
    TAC_GREATER,
    TAC_EQ,
    TAC_OR,
    TAC_AND,
    TAC_NOT,
    TAC_PARAM,
    TAC_RETURN,
    TAC_WHILE,
    TAC_DEFUNC,
    TAC_ENDFUNC,
    TAC_EXTERN
} operation;

typedef struct TAC {
    operation op;
    char* arg1;
    char* arg2;
    char* target;
    struct TAC* next;
} TAC;

#endif
