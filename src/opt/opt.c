#include "opt.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

bool opt_dead_code_enabled = false;
bool opt_constant_folding_enabled = false;
bool opt_short_circuit_enabled = false;
bool opt_peephole_enabled = false;

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
            
            if (opt_peephole_enabled) {
                if (strcmp(n->info->op, "+") == 0) {
                    n->info->ival = optimize_int_operators(lf, rg, BINOP_SUM);
                    n->type = NODE_INT;
                }
                else if (strcmp(n->info->op, "-") == 0) {
                    n->info->ival = optimize_int_operators(lf, rg, BINOP_SUB);
                    n->type = NODE_INT;
                }
                else if (strcmp(n->info->op, "*") == 0) {
                    n->info->ival = optimize_int_operators(lf, rg, BINOP_MULT);
                    n->type = NODE_INT;
                }
                else if (strcmp(n->info->op, "/") == 0) {
                    if (rg != 0) {
                        n->info->ival = optimize_int_operators(lf, rg, BINOP_DIV);
                        n->type = NODE_INT;
                    } else {
                        fprintf(stderr, "Error: division por cero inválida.\n");
                    }
                }
                else if (strcmp(n->info->op, "%") == 0) {
                    if (rg != 0) {
                        n->info->ival = optimize_int_operators(lf, rg, BINOP_MOD);
                        n->type = NODE_INT;
                    }
                }
            } else {
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
            }
            
            free(n->left);
            free(n->right);
            n->left = n->right = NULL;
        }

        else if (n->left->type == NODE_BOOL && n->right->type == NODE_BOOL) {
            int lf = n->left->info->bval;
            int rg = n->right->info->bval;

            if (opt_short_circuit_enabled) {
                if (strcmp(n->info->op, "&&") == 0) {
                    n->info->bval = optimize_bool_operators(lf, rg, BINOP_AND);
                    n->type = NODE_BOOL;
                }
                else if (strcmp(n->info->op, "||") == 0) {
                    n->info->bval = optimize_bool_operators(lf, rg, BINOP_OR);
                    n->type = NODE_BOOL;
                }
            } else {
                if (strcmp(n->info->op, "&&") == 0) {
                    n->info->bval = lf && rg;
                    n->type = NODE_BOOL;
                }
                else if (strcmp(n->info->op, "||") == 0) {
                    n->info->bval = lf || rg;
                    n->type = NODE_BOOL;
                }
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

int optimize_int_operators(int a, int b, binops op) {
    switch (op)
    {
    case BINOP_SUM:
        if (a == 0) {
            return b;
        } else if (b == 0) {
            return a;
        } else {
            return a+b;
        }
        break;
    case BINOP_SUB:
        if (a == b) {
            return 0;
        } else if (b == 0) {
        return a;
        } else if (a == 0) {
            return -b;
        } else {
            return a-b;
        }
        break;
    case BINOP_DIV:
        if (b == 1) {
            return a;
        } else if (b == -1) {
            return -a;
        } else if (a == b) {
            return 1;
        } else if (b > a) {
            return 0;
        } else if (a == 0){
            return 0;
        } else {
            return a/b;
        }
        break;
    case BINOP_MULT:
        if (a == 1) {
            return b;
        } else if (b == 1) {
            return a;
        } else if (a == -1) {
            return -b;
        } else if (b == -1) {
            return -a;
        } else if (a == 0 || b == 0) {
            return 0;
        } else {
            return a*b;
        }
        break;
    case BINOP_MOD:
        if (abs(a) == abs(b) || abs(b) == 1 || a == 0) {
            return 0;
        } else {
            return a%b;
        }
        break;
    default:
        break;
    }
}

bool optimize_bool_operators(int a, int b, binops op) {
    switch (op)
    {
    case BINOP_OR:
        if (a == 1) {
            return true;
        } else {
            return b;
        }
        break;

    case BINOP_AND:
        if (a == 0) {
            return false;
        } else {
            return b;
        }
    
    default:
        break;
    }
}
