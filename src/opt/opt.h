#ifndef OPT_H
#define OPT_H

#include "../ast/ast.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>

void dead_code(AST *n);
void const_prop(AST *n);

#endif