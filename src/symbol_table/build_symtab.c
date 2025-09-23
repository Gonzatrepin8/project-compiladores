#include <stdio.h>
#include <stdbool.h>
#include "../ast.h"
#include "build_symtab.h"

static void build_symtab_list(AST *n, SymTab *st) {
    while (n) {
        build_symtab(n, st);
        n = n->next;
    }
}

static void build_block(AST *blockNode, SymTab *parent) {
    SymTab *target;
    // Si el scope padre es una función, usamos ese mismo scope para el bloque
    // actual (el cuerpo de la función) y desactivamos el flag para futuros
    // bloques anidados.
    if (parent->is_function) {
        target = parent;
        parent->is_function = false;
    } else {
        // Si no es el bloque principal de una función, es un bloque anidado
        // o global, por lo que creamos un nuevo scope.
        target = symtab_new();
        target->parent = parent;
        target->level  = parent->level + 1;
    }

    if (blockNode->left)  build_symtab_list(blockNode->left, target);
    if (blockNode->right) build_symtab_list(blockNode->right, target);

    symtab_print(target);                                                                                                   
}

TypeInfo build_symtab(AST *n, SymTab *st) {
    if (!n) return TYPE_UNKNOWN;

    switch (n->type) {
        case NODE_PROG:
            if (n->left)  build_symtab_list(n->left, st);
            if (n->right) build_symtab_list(n->right, st);
            break;

        case NODE_BLOCK:
            build_block(n, st);
            break;

        case NODE_FUNCTION: {
            // Comprobar si la función ya existe en el scope actual
            if (symtab_scope(st, n->info->name) != TYPE_ERROR) {
                fprintf(stderr,
                        "Error: función '%s' ya declarada en este scope.\n",
                        n->info->name);
            } else {
                symtab_insert(st, n->info);
            }

            // Crear el scope propio de la función
            SymTab *fnScope = symtab_new();
            fnScope->parent = st;
            fnScope->level  = st->level + 1;
            fnScope->is_function = true;

            // insertar parametros en el mismo scope
            if (n->left) build_symtab_list(n->left, fnScope);   // param list

            // procesar el cuerpo: como fnScope->is_function = true,
            // build_block NO crea un hijo exrta y las variables locales
            // queda en fnScope directamente
            if (n->right) build_symtab(n->right, fnScope);

            break;
        }


        case NODE_PARAM:
            if (symtab_scope(st, n->info->name) != TYPE_ERROR)
                fprintf(stderr, "Error: parámetro '%s' ya declarado.\n", n->info->name);
            else
                symtab_insert(st, n->info);
            break;

        case NODE_VAR_DECL:
            if (symtab_scope(st, n->info->name) != TYPE_ERROR)
                fprintf(stderr, "Error: variable '%s' ya declarada.\n", n->info->name);
            else
                symtab_insert(st, n->info);
            if (n->right) build_symtab(n->right, st);
            break;

        case NODE_ASSIGN:
            if (n->left && n->left->info &&
                symtab_lookup(st, n->left->info->name) == TYPE_ERROR)
                fprintf(stderr, "Error: asignación a variable no declarada '%s'.\n",
                        n->left->info->name);
            if (n->right) build_symtab(n->right, st);
            break;

        default:
            if (n->left)  build_symtab(n->left, st);
            if (n->right) build_symtab(n->right, st);
            break;
    }

    return TYPE_UNKNOWN;
}
