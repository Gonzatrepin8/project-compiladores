#ifndef BUILDSYMTAB_H
#define BUILDSYMTAB_H

#include "../ast.h"
#include "symtab.h"

static void build_block(AST *blockNode, SymTab *parent);
TypeInfo build_symtab(AST *n, SymTab *st);

#endif