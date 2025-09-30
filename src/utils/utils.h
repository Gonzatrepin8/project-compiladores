#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include "../ast/ast.h"
#include "../symbol_table/symtab.h"

void function_params(AST *node);
void print_info(const Info *info);
#endif