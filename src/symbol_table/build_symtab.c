#include <stdio.h>
#include "../ast.h"
#include "build_symtab.h"

static void build_symtab_list(AST *n, SymTab *st) {
    while (n) {
        build_symtab(n, st);
        n = n->next;
    }
}

static void build_block(AST *blockNode, SymTab *parent) {
    SymTab *child = symtab_new();
    child->parent = parent;
    child->level  = parent->level + 1;

    //if (blockNode->left)  build_symtab_list(blockNode->left, child);
    //if (blockNode->right) build_symtab_list(blockNode->right, child);
    symtab_print(child);
}

TypeInfo build_symtab(AST *n, SymTab *st) {
    if (!n) return TYPE_UNKNOWN;

    switch (n->type) {
        case NODE_PROG:
            if (n->left)  build_symtab_list(n->left, st);  // var_decls
            if (n->right) build_symtab_list(n->right, st); // method_decls
            break;

        case NODE_BLOCK:
            if(n->right) build_block(n->right, st);
            break;

        case NODE_FUNCTION: {
            if (symtab_scope(st, n->info->name) != TYPE_ERROR) {
                fprintf(stderr, "Error: función '%s' ya declarada en este scope.\n", n->info->name);
            } else {
                symtab_insert(st, n->info);
            }

            SymTab *fnScope = symtab_new();
            fnScope->parent = st;
            fnScope->level  = st->level + 1;

            if (n->left) build_symtab_list(n->left, fnScope);  // param_list
            if (n->right) build_symtab(n->right, fnScope);

            break;
        }

        case NODE_PARAM:
            if (symtab_scope(st, n->info->name) != TYPE_ERROR) {
                fprintf(stderr, "Error: parámetro '%s' ya declarado en este scope.\n", n->info->name);
            } else {
                symtab_insert(st, n->info);
            }
            break;

        case NODE_VAR_DECL:
            printf("NODE VAR DECL");
            if (symtab_scope(st, n->info->name) != TYPE_ERROR) {
                fprintf(stderr,
                        "Error: variable '%s' ya declarada en este scope.\n",
                        n->info->name);
            } else {
                symtab_insert(st, n->info);
            }
            if (n->right) build_symtab(n->right, st);
            break;

        case NODE_ASSIGN:
            if (n->left && n->left->info && symtab_lookup(st, n->left->info->name) == TYPE_ERROR) {
                fprintf(stderr, "Error: asignación a variable no declarada '%s'.\n", n->left->info->name);
            }
            if (n->right) build_symtab(n->right, st);
            break;

        default:
            if (n->left)  build_symtab(n->left, st);
            if (n->right) build_symtab(n->right, st);
            break;
    }

    if (n->next) build_symtab(n->next, st);

    return TYPE_UNKNOWN;
}
