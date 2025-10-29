#include "const_prop.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void const_prop(AST *n) {
    if (!n) return;

    switch (n->type) {

    case NODE_BINOP:
        const_prop(n->left);
        const_prop(n->right);

        if (n->left->type == NODE_INT && n->right->type == NODE_INT) {
            int lf = n->left->info->ival;
            int rg = n->right->info->ival;

            if (strcmp(n->info->op, "+") == 0) {
                n->info->ival = lf + rg;
                n->type = NODE_INT;
            }
            else if (strcmp(n->info->op, "-") == 0) {
                n->info->ival = lf - rg;
                n->type = NODE_INT;
            }
            else if (strcmp(n->info->op, "*") == 0) {
                n->info->ival = lf * rg;
                n->type = NODE_INT;
            }
            else if (strcmp(n->info->op, "/") == 0) {
                if (rg != 0) {
                    n->info->ival = lf / rg;
                    n->type = NODE_INT;
                }
            }
            else if (strcmp(n->info->op, "%") == 0) {
                if (rg != 0) {
                    n->info->ival = lf % rg;
                    n->type = NODE_INT;
                }
            }
            else if (strcmp(n->info->op, "<") == 0) {
                n->info->bval = (lf < rg);
                n->type = NODE_BOOL;
            }
            else if (strcmp(n->info->op, ">") == 0) {
                n->info->bval = (lf > rg);
                n->type = NODE_BOOL;
            }
            else if (strcmp(n->info->op, "==") == 0) {
                n->info->bval = (lf == rg);
                n->type = NODE_BOOL;
            }

            free(n->left);
            free(n->right);
            n->left = n->right = NULL;
        }

        else if (n->left->type == NODE_BOOL && n->right->type == NODE_BOOL) {
            int lf = n->left->info->bval;
            int rg = n->right->info->bval;

            if (strcmp(n->info->op, "&&") == 0) {
                n->info->bval = lf && rg;
                n->type = NODE_BOOL;
            }
            else if (strcmp(n->info->op, "||") == 0) {
                n->info->bval = lf || rg;
                n->type = NODE_BOOL;
            }

            free(n->left);
            free(n->right);
            n->left = n->right = NULL;
        }

        break;

    case NODE_UNOP:
        const_prop(n->left);

        if (strcmp(n->info->op, "-") == 0 && n->left->type == NODE_INT) {
            n->info->ival = -n->left->info->ival;
            n->type = NODE_INT;
        }
        else if (strcmp(n->info->op, "!") == 0 && n->left->type == NODE_BOOL) {
            n->info->bval = !n->left->info->bval;
            n->type = NODE_BOOL;
        }

        free(n->left);
        n->left = NULL;
        break;

    default:
        if (n->left) const_prop(n->left);
        if (n->right) const_prop(n->right);
        if (n->next) const_prop(n->next);
        break;
    }
}
