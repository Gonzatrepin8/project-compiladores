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

void print_info(const Info *info) {
    if (!info) {
        printf("Info: (null)\n");
        return;
    }

    printf("Info {\n");
    printf("  name       : %s\n",   info->name ? info->name : "(null)");
    printf("  ival       : %d\n",   info->ival);
    printf("  bval       : %d\n",   info->bval);
    printf("  scope      : %d\n",   info->scope);
    printf("  op         : %s\n",   info->op ? info->op : "(null)");
    printf("  eval_type  : %s\n",   type_to_string(info->eval_type));
    printf("  is_function: %d\n",   info->is_function);
    
    printf("  params     : ");
    if (!info->params) {
        printf("(none)\n");
    } else {
        printf("\n");
        const Params *p = info->params;
        while (p) {
            printf("    - %s : %s\n",
                   p->param_name ? p->param_name : "(null)",
                   type_to_string(p->param_type));
            p = p->next;
        }
    }
    printf("}\n");
}