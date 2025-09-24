#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../ast/ast.h"
#include "../symbol_table/symtab.h"

void function_params(AST *node) {
    if (!node || !node->left) return;

    Params *head = NULL;
    Params *tail = NULL;      

    for (AST *current = node->left; current != NULL; current = current->next) {
        Params *p = malloc(sizeof(Params));

        p->param_name = strdup(current->info->name);
        p->param_type = current->info->eval_type;
        p->next = NULL;

        if (!head) {
            head = p;
            tail = p;
        } else {
            tail->next = p;
            tail = p;
        }
    }

    node->info->params = head;
}
