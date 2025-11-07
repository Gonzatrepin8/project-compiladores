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
/*
extern bool opt_dead_code_enabled;
extern bool opt_constant_folding_enabled;
extern bool opt_short_circuit_enabled;
extern bool opt_peephole_enabled;
*/
void dead_code(AST *n);
void const_prop(AST *n);
//int optimize_int_operators(int a, int b, binops op);
void optimize_bool_operators(AST *n);

#endif
