#include "three_address.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int tmp_counter = 0;
static int label_counter = 0;

TAC *tac_head = NULL;
static TAC *tac_tail = NULL;

static char *new_temp(void) {
    char buf[32];
    snprintf(buf, sizeof(buf), "t%d", tmp_counter++);
    return strdup(buf);
}
static char *new_label(void) {
    char buf[32];
    snprintf(buf, sizeof(buf), "L%d", label_counter++);
    return strdup(buf);
}

static TAC *emit_tac(operation op, const char *arg1, const char *arg2, const char *target) {
    TAC *node = malloc(sizeof(TAC));
    node->op = op;
    node->arg1 = arg1 ? strdup(arg1) : NULL;
    node->arg2 = arg2 ? strdup(arg2) : NULL;
    node->target = target ? strdup(target) : NULL;
    node->next = NULL;

    if (!tac_head)
        tac_head = node;
    else
        tac_tail->next = node;

    tac_tail = node;
    return node;
}

static void print_tac_list(FILE *out, TAC *head) {
    while (head) {
        switch (head->op) {
        case TAC_ASSIGN:
            fprintf(out, "%s = %s\n", head->target, head->arg1);
            break;
        case TAC_SUM:
            fprintf(out, "%s = %s + %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_MINUS:
            fprintf(out, "%s = %s - %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_MUL:
            fprintf(out, "%s = %s * %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_DIV:
            fprintf(out, "%s = %s / %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_MOD:
            fprintf(out, "%s = %s %% %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_GREATER:
            fprintf(out, "%s = %s > %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_LESS:
            fprintf(out, "%s = %s < %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_NEG:
            fprintf(out, "%s = -%s\n", head->target, head->arg1);
            break;
        case TAC_NOT:
            fprintf(out, "%s = !%s\n", head->target, head->arg1);
            break;
        case TAC_AND:
            fprintf(out, "%s = %s && %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_EQ:
            fprintf(out, "%s = %s == %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_OR:
            fprintf(out, "%s = %s || %s\n", head->target, head->arg1, head->arg2);
            break;
        case TAC_LABEL:
            fprintf(out, "%s:\n", head->target);
            break;
        case TAC_IFZ:
            fprintf(out, "ifz %s goto %s\n", head->arg1, head->target);
            break;
        case TAC_GOTO:
            fprintf(out, "goto %s\n", head->target);
            break;
        case TAC_CALL:
            fprintf(out, "%s = call %s, %s\n", head->target, head->arg1, head->arg2 ? head->arg2 : "0");
            break;
        case TAC_PARAM:
            fprintf(out, "PARAM %s\n", head->arg1);
            break;
        case TAC_RETURN:
            if (head->arg1)
                fprintf(out, "return %s\n", head->arg1);
            else
                fprintf(out, "return\n");
            break;
        case TAC_WHILE:
            fprintf(out, "%s:\n", head->target);
            break;
        case TAC_DEFUNC:
            fprintf(out, "\nfunction %s:\n", head->target);
            break;
        case TAC_ENDFUNC:
            fprintf(out, "end function\n");
            break;
        case TAC_EXTERN:
            fprintf(out, "extern %s:\n", head->target);
            break;
        default:
            fprintf(out, "%s = ?(%d)\n", head->target ? head->target : "?", head->op);
            break;
        }
        head = head->next;
    }
}

static char *gen_expr(AST *n, FILE *out);
static void gen_stmt(AST *n, FILE *out);

static void gen_stmt_list(AST *n, FILE *out) {
    while (n) {
        gen_stmt(n, out);
        n = n->next;
    }
}

static char *gen_expr(AST *n, FILE *out) {
    if (!n)
        return NULL;

    switch (n->type) {
    case NODE_INT: {
        char *t = new_temp();
        char buf[32];
        snprintf(buf, sizeof(buf), "%d", n->info->ival);
        emit_tac(TAC_ASSIGN, buf, NULL, t);
        return t;
    }
    case NODE_BOOL: {
        char *t = new_temp();
        emit_tac(TAC_ASSIGN, n->info->bval ? "1" : "0", NULL, t);
        return t;
    }
    case NODE_ID:
        return strdup(n->info->name ? n->info->name : "(unknown)");

    case NODE_BINOP: {
        char *left = gen_expr(n->left, out);
        char *right = gen_expr(n->right, out);
        char *res = new_temp();

        if (strcmp(n->info->op, "+") == 0)
            emit_tac(TAC_SUM, left, right, res);
        else if (strcmp(n->info->op, "-") == 0)
            emit_tac(TAC_MINUS, left, right, res);
        else if (strcmp(n->info->op, "*") == 0)
            emit_tac(TAC_MUL, left, right, res);
        else if (strcmp(n->info->op, "/") == 0)
            emit_tac(TAC_DIV, left, right, res);
        else if (strcmp(n->info->op, "%") == 0)
            emit_tac(TAC_MOD, left, right, res);
        if (strcmp(n->info->op, ">") == 0)
            emit_tac(TAC_GREATER, left, right, res);
        if (strcmp(n->info->op, "<") == 0)
            emit_tac(TAC_LESS, left, right, res);
        if (strcmp(n->info->op, "==") == 0)
            emit_tac(TAC_EQ, left, right, res);
        if (strcmp(n->info->op, "||") == 0)
            emit_tac(TAC_OR, left, right, res);
        if (strcmp(n->info->op, "&&") == 0)
            emit_tac(TAC_AND, left, right, res);

        free(left);
        free(right);
        return res;
    }

     case NODE_UNOP: {
        char *operand = gen_expr(n->left, out);
        char *res = new_temp();
        const char *op = n->info->op ? n->info->op : "(uop)";

        if (strcmp(n->info->op, "-") == 0)
            emit_tac(TAC_MINUS, operand, NULL, res);
        else if (strcmp(n->info->op, "!") == 0)
            emit_tac(TAC_NOT, operand, NULL, res);

        free(operand);
        return res;
    }
    case NODE_CALL: {
        AST *arg = n->left;
        int argnum = 0;
        while (arg) {
            char *a = gen_expr(arg, out);
            emit_tac(TAC_PARAM, a, NULL, NULL);
            free(a);
            arg = arg->next;
            argnum++;
        }
        char *res = new_temp();
        char num_params[16];
        snprintf(num_params, sizeof(num_params), "%d", argnum);
        emit_tac(TAC_CALL, n->info->name, num_params, res);
        return res;
    }

    default:
        return strdup("(unknown)");
    }
}

static void gen_stmt(AST *n, FILE *out) {
    if (!n)
        return;

    switch (n->type) {
    case NODE_ASSIGN: {
        char *lhs = strdup(n->left->info->name);
        char *rhs = gen_expr(n->right, out);
        emit_tac(TAC_ASSIGN, rhs, NULL, lhs);
        free(rhs);
        free(lhs);
        break;
    }

    case NODE_IF: {
        char *cond = gen_expr(n->left, out);
        char *Lelse = new_label();
        char *Lend = new_label();

        emit_tac(TAC_IFZ, cond, NULL, Lelse);
        gen_stmt(n->right, out);
        emit_tac(TAC_GOTO, NULL, NULL, Lend);

        emit_tac(TAC_LABEL, NULL, NULL, Lelse);
        if (n->right->next) gen_stmt(n->right->next, out);
        emit_tac(TAC_LABEL, NULL, NULL, Lend);

        free(cond); free(Lelse); free(Lend);
        break;
    }

      case NODE_WHILE: {
        char *Lstart = new_label();
        char *Lend = new_label();

        emit_tac(TAC_WHILE, NULL, NULL, Lstart);
        char *cond = gen_expr(n->left, out);
        emit_tac(TAC_IFZ, cond, NULL, Lend);

        gen_stmt(n->right, out);
        emit_tac(TAC_GOTO, NULL, NULL, Lstart);
        emit_tac(TAC_WHILE, NULL, NULL, Lend);

        free(cond); free(Lstart); free(Lend);
        break;
    }

    case NODE_RETURN: {
        if (!n->left) {
            emit_tac(TAC_RETURN, NULL, NULL, NULL);
        } else {
            char *r = gen_expr(n->left, out);
            emit_tac(TAC_RETURN, r, NULL, NULL);
            free(r);
        }
        break;
    }

      case NODE_FUNCTION: {
        const char *fname = n->info && n->info->name ? n->info->name : "(func)";
        if (n->right->type == NODE_EXTERN){
            emit_tac(TAC_EXTERN, NULL, NULL, fname);
        } else {
        
            emit_tac(TAC_DEFUNC, NULL, NULL, fname);
        
            if (n->left) {
                AST *p = n->left;
                int i = 0;
                while (p) {
                    emit_tac(TAC_PARAM, p->info->name, NULL, NULL);
                    p = p->next;
                }
            }

            if (n->right) gen_stmt(n->right, out);
            emit_tac(TAC_ENDFUNC, NULL, NULL, NULL);
        }
        break;
    }

    case NODE_BLOCK: {
        if (n->left)
            gen_stmt_list(n->left, out);
        if (n->right)
            gen_stmt_list(n->right, out);
        break;
    }

    case NODE_CALL: {
        char *ret = gen_expr(n, out);
        free(ret);
        break;
    }

    case NODE_PROG: {
        if (n->left)
            gen_stmt_list(n->left, out);
        if (n->right)
            gen_stmt_list(n->right, out);
        break;
    }

    default:
        if (n->left)
            gen_stmt(n->left, out);
        if (n->right)
            gen_stmt(n->right, out);
        break;
    }
}

void generate_tac(AST *root, FILE *out) {
    tmp_counter = 0;
    label_counter = 0;
    tac_head = tac_tail = NULL;

    if (!root)
        return;

    gen_stmt(root, out);

    print_tac_list(out, tac_head);
}
