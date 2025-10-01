#include <stdio.h>
#include <stdbool.h>
#include "build_symtab.h"

bool semantic_error = false;

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
                        "Error: A declaration (variable or function) with the name '%s' already exists in this scope.\n",
                        n->info->name);
                semantic_error = true;
                return TYPE_ERROR;
            } else {
                function_params(n);
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
            if (symtab_scope(st, n->info->name) != TYPE_ERROR) {
                fprintf(stderr, "Error: Parameter '%s' already declared.\n", n->info->name);
                semantic_error = true;
            } else {
                symtab_insert(st, n->info);
            }  
            break;

        case NODE_VAR_DECL:

            if (n->right && n->right->right) {
                build_symtab(n->right->right, st, stream);
            }

            if (symtab_scope(st, n->info->name) != TYPE_ERROR) {
                fprintf(stderr, "Error: Variable '%s' already declared.\n", n->info->name);
                semantic_error = true;
            } else {
                symtab_insert(st, n->info);
            }

            if (n->right && n->right->left) {
                 build_symtab(n->right->left, st, stream);
            }
            break;

        case NODE_ASSIGN:
            if (n->right)  build_symtab(n->right, st, stream);
            if (n->left) build_symtab(n->left, st, stream);
            if (n->next) build_symtab(n->next, st, stream);
            break;
        
        case NODE_ID:
            if (symtab_lookup(st, n->info->name) == TYPE_ERROR) {
                fprintf(stderr, "Error: Variable '%s' has not been declared.\n", n->info->name);
                semantic_error = true;
            } else {
                symtab_label_nodes(st, n->info->name, n);
            }
            break;
        
        case NODE_CALL:
            symtab_label_nodes(st, n->info->name, n);
            AST *arg = n->left;
            while (arg) {
                build_symtab(arg, st, stream);
                arg = arg->next;
            }

            if (n->next) build_symtab(n->next, st, stream);
            break;

        default:
            if (n->left)  build_symtab(n->left, st, stream);
            if (n->right) build_symtab(n->right, st, stream);
            if (n->next) build_symtab(n->next, st, stream);
            break;
    }

    return TYPE_UNKNOWN;
}
