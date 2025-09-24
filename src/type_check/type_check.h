#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "../ast/ast.h"
#include "../symbol_table/symtab.h"

TypeInfo check_types(AST* n, SymTab *st);

#endif
