#ifndef BUILDSYMTAB_H
#define BUILDSYMTAB_H

#include "../ast/ast.h"
#include "symtab.h"
#include "../utils/utils.h"
#include <stdio.h>
#include <stdbool.h>

extern bool semantic_error;

static void build_block(AST *blockNode, SymTab *parent, FILE *stream);
TypeInfo build_symtab(AST *n, SymTab *st, FILE *stream);

#endif