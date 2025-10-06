#ifndef THREE_ADDR_H
#define THREE_ADDR_H

#include "../ast/ast.h"
#include <stdio.h>

static char *gen_expr(AST *n, FILE *out);
static void gen_stmt(AST *n, FILE *out);
void generate_tac(AST *root, FILE *out);

#endif
