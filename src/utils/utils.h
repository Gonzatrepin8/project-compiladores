#ifndef UTILS_H
#define UTILS_H

#include "../ast/ast.h"
#include "../symbol_table/symtab.h"
#include <stdio.h>

void function_params(AST *node);
void print_info(const Info *info);
#endif