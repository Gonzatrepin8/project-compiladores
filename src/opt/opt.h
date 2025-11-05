#ifndef OPT_H
#define OPT_H

#include "../ast/ast.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>

typedef enum {
    BINOP_SUM,
    BINOP_SUB,
    BINOP_MULT,
    BINOP_DIV,
    BINOP_MOD,
    BINOP_LESS,
    BINOP_GREATER,
    BINOP_EQ,
    BINOP_OR,
    BINOP_AND
} binops;

bool OPT_DEAD_CODE = false;
bool OPT_CONSTANT_FOLDING = false;
bool OPT_SHORT_CIRCUIT_EVALUATION = false;
bool OPT_PEEPHOLE = false;

void dead_code(AST *n);
void const_prop(AST *n);
int optimize_int_operators(int a, int b, binops op);
bool optimize_bool_operators(int a, int b, binops op);

#endif