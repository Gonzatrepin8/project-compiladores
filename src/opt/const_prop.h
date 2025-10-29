#ifndef CONST_PROP_H
#define CONST_PROP_H

#include "../ast/ast.h"
#include "../utils/utils.h"
#include <stdbool.h>
#include <stdio.h>

void const_prop(AST *n);

#endif