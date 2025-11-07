#include "opt.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../utils/utils.h"
/*
bool OPT_DEAD_CODE = true;
bool OPT_CONSTANT_FOLDING = false;
bool OPT_SHORT_CIRCUIT_EVALUATION = false;
bool OPT_PEEPHOLE = false;
*/
void dead_code(AST *n) {
    if (!n) return;

    if (n->left)  dead_code(n->left);
    if (n->right) dead_code(n->right);
    if (n->next)  dead_code(n->next);

    if (n->type == NODE_IF && n->left && n->left->type == NODE_BOOL) {
        int cond = n->left->info->bval;
        AST *keep = NULL;

        if (cond) {
            keep = n->right;
        } else {
            if (n->right && n->right->next)
                keep = n->right->next;
        }

        free(n->left);
        n->left = NULL;

        if (keep) {
            AST *next_backup = n->next;
            *n = *keep;
            n->next = next_backup;
        } else {
            n->type = NODE_BLOCK;
            n->left = n->right = NULL;
            if (n->info) {
                free(n->info->name);
                free(n->info->op);
                free(n->info);
            }
            n->info = calloc(1, sizeof(Info));
        }
    }

    else if (n->type == NODE_WHILE && n->left && n->left->type == NODE_BOOL) {
        int cond = n->left->info->bval;
        if (!cond) {
            free(n->left);
            n->left = n->right = NULL;
            n->type = NODE_BLOCK;
            if (n->info) {
                free(n->info->name);
                free(n->info->op);
                free(n->info);
            }
            n->info = calloc(1, sizeof(Info));
        }
    }

    if (n->type == NODE_RETURN && n->next) {
        n->next = NULL;
    }
}

void const_prop(AST *n) {
    if (!n) return;

    switch (n->type) {

    case NODE_BINOP:
        const_prop(n->left);
        const_prop(n->right);

        if (n->left->type == NODE_INT && n->right->type == NODE_INT) {
            int lf = n->left->info->ival;
            int rg = n->right->info->ival;

            if (strcmp(n->info->op, "<") == 0) {
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
                    } else {
                        printf("Error division por cero inválida.\n");
                    }
                }
                else if (strcmp(n->info->op, "%") == 0) {
                    if (rg != 0) {
                        n->info->ival = lf % rg;
                        n->type = NODE_INT;
                    }
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

void optimize_bool_operators(AST *n) {
    if (!n) return;

    switch (n->type) {

    case NODE_BINOP:
        optimize_bool_operators(n->left);
        optimize_bool_operators(n->right);
        //print_info(n->info);

        if (n->left->type == NODE_BOOL){
            int lf = n->left->info->bval;
            if (strcmp(n->info->op, "&&") == 0){
                if (lf == 1){
                    AST *next_backup = n->next;
                    *n = *n->right;
                    n->next = next_backup;
                    break;
                } else {
                    n->type = TYPE_BOOL;
                    n->info->bval = 0;
                    n->left = NULL;
                    n->right = NULL;

                    break;
                }
            } else if (strcmp(n->info->op, "||") == 0){
                if (lf == 0){
                    printf("hola");
                    AST *next_backup = n->next;
                    *n = *n->right;
                    n->next = next_backup;
                    break;
                } else {
                    printf("hola");
                    n->type = TYPE_BOOL;
                    n->info->bval = 1;
                    n->left = NULL;
                    n->right = NULL;

                    break;
                }
            }

        } else if(n->right->type == NODE_BOOL) {
            int rg = n->right->info->bval;
            if (strcmp(n->info->op, "&&")){
                if (rg == 1){
                    printf("hola");
                    AST *next_backup = n->next;
                    *n = *n->left;
                    n->next = next_backup;
                    break;
                } else {
                    printf("hola");
                    n->type = TYPE_BOOL;
                    n->info->bval = 0;
                    n->left = NULL;
                    n->right = NULL;

                    break;
                }
            } else if (strcmp(n->info->op, "||")){
                if (rg == 0){
                    printf("hola");
                    AST *next_backup = n->next;
                    *n = *n->left;
                    n->next = next_backup;
                    break;
                } else {
                    printf("hola");
                    n->type = TYPE_BOOL;
                    n->info->bval = 1;
                    n->left = NULL;
                    n->right = NULL;

                    break;
                }
            }

        }

        break;
    default:
        if (n->left) optimize_bool_operators(n->left);
        if (n->right) optimize_bool_operators(n->right);
        if (n->next) optimize_bool_operators(n->next);
        break;
    }
}

