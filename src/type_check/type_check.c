#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "type_check.h"

bool type_check_error = false;

TypeInfo check_types(AST* n, SymTab *st) {

    if (!n) return TYPE_UNKNOWN;

    TypeInfo result = TYPE_UNKNOWN;

    printf("CHECK TYPE: %d\n", n->type);

    switch (n->type) {
        case NODE_PROG:
                if (n->left) check_types(n->left, st);
                if (n->right) check_types(n->right, st);
            break;

        case NODE_INT:
            n->info->eval_type = TYPE_INT;
            result = TYPE_INT;
            break;

        case NODE_BOOL:
            n->info->eval_type = TYPE_BOOL;
            result = TYPE_BOOL;
            break;

        case NODE_ID: {
            TypeInfo t = symtab_lookup(st, n->info->name);
            int found;
            int value = symtab_get_value(st, n->info->name, &found);
            if (found) {
                if (n->info->eval_type == TYPE_INT) {
                    n->info->ival = value;
                } else if (n->info->eval_type == TYPE_BOOL) {
                    n->info->bval = value;
                }
            }
            n->info->eval_type = t;
            result = t;
            break;
        }


        case NODE_BINOP: {
            TypeInfo lt = check_types(n->left, st);
            TypeInfo rt = check_types(n->right, st);
            if (strcmp(n->info->op, "+") == 0
                    || strcmp(n->info->op, "-") == 0
                    || strcmp(n->info->op, "*") == 0
                    || strcmp(n->info->op, ">") == 0
                    || strcmp(n->info->op, "<") == 0
                    ) {
                if (lt!=TYPE_INT || rt!=TYPE_INT) {
                    fprintf(stderr,"Type error: arithmetic needs int\n");
                    type_check_error = true;
                }
                n->info->eval_type = TYPE_INT;
                result = TYPE_INT;
            } else if (strcmp(n->info->op, "/") == 0) { // controlar division por 0
                    if ((lt!=TYPE_INT || rt!=TYPE_INT)) {
                        fprintf(stderr,"Type error: arithmetic needs int\n");
                        type_check_error = true;
                    }
                } else {
                    if (lt!=TYPE_BOOL || rt!=TYPE_BOOL) {
                        fprintf(stderr,"Type error: logical needs bool\n");
                        type_check_error = true;
                    }
                    n->info->eval_type = TYPE_BOOL;
                    result = TYPE_BOOL;
                }
                break;
        }

        case NODE_UNOP: {
            TypeInfo et = check_types(n->left, st);
            if (strcmp(n->info->op, "!") == 0 && et!=TYPE_BOOL) {
                fprintf(stderr,"Type error: ! needs bool\n");
                type_check_error = true;
            }
            if (strcmp(n->info->op, "-") == 0 && et!=TYPE_INT) {
                fprintf(stderr,"Type error: - needs integer\n");
                type_check_error = true;
            }
            if (et == TYPE_BOOL) {
                n->info->eval_type = strcmp(n->info->op, "!") ? TYPE_BOOL : et;
                result = TYPE_BOOL;
            } else {
                n->info->eval_type = strcmp(n->info->op, "-") ? TYPE_INT : et;
                result = TYPE_INT;
            }
            break;
        }

        case NODE_ASSIGN: {
            TypeInfo lhs = check_types(n->left, st);
            TypeInfo rhs = check_types(n->right, st);
            if (lhs == TYPE_ERROR && n->left->type == NODE_ID) {
                lhs = symtab_lookup(st, n->left->info->name);
            }
            if (lhs != rhs) {
                fprintf(stderr,"Type error: assignment mismatch\n");
                type_check_error = true;
            }

            if (n->left && n->left->type == NODE_ID) {
                if (n->left->info->eval_type == TYPE_INT) {
                    symtab_set_value(st, n->left->info->name, n->right->info->ival);
                } else if (n->left->info->eval_type == TYPE_BOOL) {
                    symtab_set_value(st, n->left->info->name, n->right->info->bval);
                }
            }

            n->info->eval_type = lhs;
            result = lhs;
            break;
        }

          case NODE_VAR_DECL:
            if (n->info->name) {
                TypeInfo t = symtab_scope(st, n->info->name);
                if (t == TYPE_ERROR) {
                    symtab_insert(st, n->info);
                    if (n->right) {
                        check_types(n->right, st);
                    } else {
                        printf("%s: Unmatching type.\n", n->info->name);
                        type_check_error = true;
                    }
                } else {
                    printf("%s: variable already declared.\n", n->info->name);
                    type_check_error = true;
                }
            }
            result = TYPE_UNKNOWN;
            break;

            case NODE_RETURN: {
                TypeInfo ret_type = check_types(n->left, st);
                result = ret_type;
                break;
            }

          case NODE_FUNCTION: {
            TypeInfo function_type = n->info->eval_type;
            check_types(n->left, st);
            check_types(n->right, st);
            break;
        }

          case NODE_BLOCK: {
            check_types(n->left, st);
            check_types(n->right, st);
            break;
        }


        default:
            result = TYPE_UNKNOWN;
    }

    if (n->next) check_types(n->next, st);

    return result;
}
