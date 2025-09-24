#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"

extern FILE *semout;

AST *make_node(NodeType type, char *name, int ival, int bval,
               char* op, AST *left, AST *right) {
    AST *n = malloc(sizeof(AST));
    if (!n) {
        fprintf(stderr, "Error: malloc failed in make_node\n");
        exit(EXIT_FAILURE);
    }

    n->type = type;
    n->info = malloc(sizeof(Info));
    if (!n->info) {
        fprintf(stderr, "Error: malloc failed for info struct\n");
        exit(EXIT_FAILURE);
    }

    n->info->name = name ? strdup(name) : NULL;
    n->info->ival = ival;
    n->info->bval = bval;
    n->info->op = op ? strdup(op) : NULL;
    n->info->is_function = 0;    
    n->info->eval_type = TYPE_UNKNOWN;
    n->info->params = NULL;

    n->left = left;
    n->right = right;
    n->next = NULL;

    return n;
}

void print_ast(AST *node, int depth, int is_last) {
    if (!node) return;

    for (int i = 0; i < depth-1; i++) fprintf(semout, "│   ");
    if (depth > 0) fprintf(semout, is_last ? "└── " : "├── ");

    switch (node->type) {
        case NODE_INT:      fprintf(semout, "INT(%d)\n", node->info->ival); break;
        case NODE_BOOL:     fprintf(semout, "BOOL(%s)\n", (node->info->bval) ? "TRUE" : "FALSE"); break;
        case NODE_ID:       fprintf(semout, "ID(%s)\n", node->info->name); break;
        case NODE_BINOP:    fprintf(semout, "BINOP(%s)\n", node->info->op); break;
        case NODE_UNOP:     fprintf(semout, "UNOP(%s)\n", node->info->op); break;
        case NODE_VAR_DECL: fprintf(semout, "VAR_DECL(%s)\n", node->info->name); break;
        case NODE_ASSIGN:   fprintf(semout, "ASSIGN\n"); break;
        case NODE_RETURN:   fprintf(semout, "RETURN\n"); break;
        case NODE_IF:       fprintf(semout, "IF\n"); break;
        case NODE_WHILE:    fprintf(semout, "WHILE\n"); break;
        case NODE_FUNCTION: fprintf(semout, "FUNCTION(%s)\n", node->info->name); break;
        case NODE_BLOCK:    fprintf(semout, "BLOCK\n"); break;
        case NODE_PROG:     fprintf(semout, "PROGRAM\n"); break;
        case NODE_CALL:     fprintf(semout, "CALL(%s)\n", node->info->name); break;
        case NODE_PARAM:    fprintf(semout, "PARAM(%s, %s)\n", type_to_string(node->info->eval_type), node->info->name); break;
        default:            fprintf(semout, "UKNOWN_NODE(%d)\n", node->type);
    }

    AST* children[2] = {node->left, node->right};
    int n_children = 0;
    if (node->left) n_children++;
    if (node->right) n_children++;

    int count = 0;
    if (node->left) print_ast(node->left, depth + 1, ++count == n_children);
    if (node->right) print_ast(node->right, depth + 1, ++count == n_children);

    if (node->next) print_ast(node->next, depth, is_last);
}

const char* type_to_string(TypeInfo t) {
    switch (t) {
        case TYPE_INT: return "integer";
        case TYPE_BOOL: return "bool";
        case TYPE_VOID: return "void";
        case TYPE_UNKNOWN: return "unknown";
        case TYPE_ERROR: return "error";
        default: return "invalid";
    }
}
