#include <stdio.h>
#include <stdbool.h>
#include "../ast.h"
#include "build_symtab.h"

static void build_symtab_list(AST *n, SymTab *st, FILE *stream) {
    while (n) {
        build_symtab(n, st, stream);
        n = n->next;
    }
}

static void build_block(AST *blockNode, SymTab *parent, FILE *stream) {
    SymTab *target;
    if (parent->is_function) {
        target = parent;
        parent->is_function = false;
    } else {
        target = symtab_new();
        target->parent = parent;
        target->level  = parent->level + 1;
    }

    if (blockNode->left)  build_symtab_list(blockNode->left, target, stream);
    if (blockNode->right) build_symtab_list(blockNode->right, target, stream);

    symtab_print(target, stream);                                                                                                   
}

TypeInfo build_symtab(AST *n, SymTab *st, FILE *stream) {
    if (!n) return TYPE_UNKNOWN;

    switch (n->type) {
        case NODE_PROG:
            if (n->left)  build_symtab_list(n->left, st, stream);
            if (n->right) build_symtab_list(n->right, st, stream);
            break;

        case NODE_BLOCK:
            build_block(n, st, stream);
            break;

        case NODE_FUNCTION: {
            if (symtab_scope(st, n->info->name) != TYPE_ERROR) {
                fprintf(stderr,
                        "Error: función '%s' ya declarada en este scope.\n",
                        n->info->name);
            } else {
                symtab_insert(st, n->info);
            }

            SymTab *fnScope = symtab_new();
            fnScope->parent = st;
            fnScope->level  = st->level + 1;
            fnScope->is_function = true;

            if (n->left) build_symtab_list(n->left, fnScope, stream);
            if (n->right) build_symtab(n->right, fnScope, stream);

            break;
        }

        case NODE_IF:
            if (n->left) build_symtab(n->left, st, stream);

            if (n->right) build_symtab(n->right, st, stream);

            if (n->right && n->right->next) {
                build_symtab(n->right->next, st, stream);
            }
            break;

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

            if (n->left) build_symtab(n->left, st, stream);
            if (n->right) build_symtab(n->right, st, stream);
            break;

        case NODE_ASSIGN:
            if (n->left && n->left->info &&
                symtab_lookup(st, n->left->info->name) == TYPE_ERROR)
                fprintf(stderr, "Error: asignación a variable no declarada '%s'.\n",
                        n->left->info->name);            
            if (n->left)  build_symtab(n->left, st, stream);
            if (n->right) build_symtab(n->right, st, stream);
            break;
        
        case NODE_ID:
            symtab_label_nodes(st, n->info->name, n);
            break;
        
        case NODE_CALL:
            symtab_label_nodes(st, n->info->name, n);
            break;

        default:
            if (n->left)  build_symtab(n->left, st, stream);
            if (n->right) build_symtab(n->right, st, stream);
            break;
    }

    return TYPE_UNKNOWN;
}
