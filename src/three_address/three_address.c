#include "three_address.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int tmp_counter = 0;
static int label_counter = 0;

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

static void emit(FILE *out, const char *fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    vfprintf(out, fmt, ap);
    va_end(ap);
    fprintf(out, "\n");
}

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
        emit(out, "%s = %d", t, n->info->ival);
        return t;
    }
    case NODE_BOOL: {
        char *t = new_temp();
        emit(out, "%s = %s", t, n->info->bval ? "1" : "0");
        return t;
    }
    case NODE_ID: {
        return strdup(n->info->name ? n->info->name : "(unknown)");
    }
    case NODE_BINOP: {
        char *left = gen_expr(n->left, out);
        char *right = gen_expr(n->right, out);

        char *res = new_temp();
        const char *op = n->info->op ? n->info->op : "(op)";

        emit(out, "%s = %s %s %s", res, left, op, right);

        free(left);
        free(right);
        return res;
    }
    case NODE_UNOP: {
        char *operand = gen_expr(n->left, out);
        char *res = new_temp();
        const char *op = n->info->op ? n->info->op : "(uop)";

        emit(out, "%s = %s %s", res, op, operand);

        free(operand);
        return res;
    }
    case NODE_CALL: {
        AST *arg = n->left;
        int argnum = 0;
        while (arg) {
            char *a = gen_expr(arg, out);
            emit(out, "param %s", a);
            free(a);
            arg = arg->next;
            argnum++;
        }
        char *res = new_temp();
        emit(out, "%s = call %s, %d", res,
             n->info->name ? n->info->name : "(unknown)", argnum);
        return res;
    }
    default:
        if (n->left) {
            char *r = gen_expr(n->left, out);
            return r;
        }
        if (n->right) {
            char *r = gen_expr(n->right, out);
            return r;
        }
        return strdup("(unknown)");
    }
}

static void gen_stmt(AST *n, FILE *out) {
    if (!n)
        return;

    switch (n->type) {
    case NODE_VAR_DECL:
        if (n->right)
            gen_stmt(n->right, out);
        break;

    case NODE_ASSIGN: {
        char *lhs = NULL;
        if (n->left && n->left->type == NODE_ID && n->left->info &&
            n->left->info->name) {
            lhs = strdup(n->left->info->name);
        } else {
            lhs = gen_expr(n->left, out);
        }

        char *rhs = gen_expr(n->right, out);
        emit(out, "%s = %s", lhs, rhs);

        free(lhs);
        free(rhs);

        break;
    }

    case NODE_IF: {
        char *cond = gen_expr(n->left, out);

        char *Lelse = new_label();
        char *Lend = new_label();

        emit(out, "if False %s goto %s", cond, Lelse);
        free(cond);

        gen_stmt(n->right, out);

        emit(out, "goto %s", Lend);

        emit(out, "%s:", Lelse);
        if (n->right && n->right->next) {
            gen_stmt(n->right->next, out);
        }

        emit(out, "%s:", Lend);
        free(Lelse);
        free(Lend);
        break;
    }

    case NODE_WHILE: {
        char *Lstart = new_label();
        char *Lend = new_label();

        emit(out, "%s:", Lstart);
        char *cond = gen_expr(n->left, out);
        emit(out, "if False %s goto %s", cond, Lend);
        free(cond);

        gen_stmt(n->right, out);
        emit(out, "goto %s", Lstart);
        emit(out, "%s:", Lend);

        free(Lstart);
        free(Lend);
        break;
    }

    case NODE_RETURN: {
        if (!n->left) {
            emit(out, "return");
        } else {
            char *r = gen_expr(n->left, out);
            emit(out, "return %s", r);
            free(r);
        }
        break;
    }

    case NODE_FUNCTION: {
        const char *fname = n->info && n->info->name ? n->info->name : "(func)";
        emit(out, "func %s:", fname);

        if (n->left) {
            AST *p = n->left;
            int i = 0;
            while (p) {
                emit(out, "  # param %d -> %s", i++,
                     p->info && p->info->name ? p->info->name : "(p)");
                p = p->next;
            }
        }

        if (n->right)
            gen_stmt(n->right, out);

        emit(out, "endfunc");
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

    if (n->next)
        gen_stmt(n->next, out);
}

void generate_tac(AST *root, FILE *out) {
    tmp_counter = 0;
    label_counter = 0;

    if (!root)
        return;

    emit(out, "# Three-address code generated");
    gen_stmt(root, out);
}
