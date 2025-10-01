#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "type_check.h"
#include "../ast/ast.h"

bool type_check_error = false;
static TypeInfo func_type = TYPE_ERROR;

void check_types(AST* n) {
    if (!n) return;

    switch (n->type) {
        case NODE_PROG:
                if (n->left) check_types(n->left);
                if (n->right) check_types(n->right);
            break;

        case NODE_BINOP: {
            if (n->left) check_types(n->left);
            if (n->right) check_types(n->right);
            TypeInfo left_expr_type = n->left->info->eval_type;
            TypeInfo right_expr_type = n->right->info->eval_type;
            
            if(left_expr_type != right_expr_type){
                fprintf(stderr,"Type error: types %s and %s do not match\n",
                        type_to_string(left_expr_type),
                        type_to_string(right_expr_type));
                type_check_error = true;
            }
            
            if (strcmp(n->info->op, "==") == 0
             || strcmp(n->info->op, ">") == 0
             || strcmp(n->info->op, "<") == 0
             ) {
                n->info->eval_type = TYPE_BOOL;
            } else if (strcmp(n->info->op, "+") == 0
                    || strcmp(n->info->op, "-") == 0
                    || strcmp(n->info->op, "*") == 0
                    || strcmp(n->info->op, "/") == 0
                    || strcmp(n->info->op, "%") == 0
                    ) { 
                
                if (left_expr_type != TYPE_INT) {
                    fprintf(stderr,"Type error: arithmetic needs int\n");
                    type_check_error = true;
                }
                
                n->info->eval_type = TYPE_INT;
    
            } else {
                if (left_expr_type != TYPE_BOOL) {
                        fprintf(stderr,"Type error: logical needs bool\n");
                        type_check_error = true;
                    }
                    n->info->eval_type = TYPE_BOOL;
            }
            break;
        }

        case NODE_UNOP: {
            if (n->left) check_types(n->left);
            TypeInfo expr_type = n->left->info->eval_type;

            if (strcmp(n->info->op, "!") == 0 && expr_type != TYPE_BOOL) {
                fprintf(stderr,"Type error: ! needs bool\n");
                type_check_error = true;
            }
            if (strcmp(n->info->op, "-") == 0 && expr_type != TYPE_INT) {
                fprintf(stderr,"Type error: - needs integer\n");
                type_check_error = true;
            }
            
            n->info->eval_type = expr_type;
            
            break;
        }

        case NODE_ASSIGN: {
            if (n->right) check_types(n->right);
            if (n->next) check_types(n->next);
            
            TypeInfo id_type = n->left->info->eval_type;
            TypeInfo expr_type = n->right->info->eval_type;

            if (id_type != expr_type) {
                fprintf(stderr,"Type error: assignment mismatch\n");
                type_check_error = true;
            }
            
            n->info->eval_type = id_type;
            break;
        }

        case NODE_VAR_DECL:
            check_types(n->right);
            break;

        case NODE_RETURN: {
            if (!n->left) {
                n->info->eval_type = TYPE_VOID;
                if (func_type != TYPE_VOID) {
                    fprintf(stderr,"Type error: function expects %d but returns void\n" , func_type);
                    type_check_error = true;
                }
            } else {
                check_types(n->left);
                n->info->eval_type = n->left->info->eval_type;
                if (n->info->eval_type != func_type) {
                    fprintf(stderr,"Type error: function expects %d but returns %d\n",
                            func_type,
                            n->info->eval_type);
                    type_check_error = true;
                }
            }
            break;
        }

        case NODE_FUNCTION: {
            func_type = n->info->eval_type;
            if(n->left) check_types(n->left);
            if(n->right) check_types(n->right);
            break;
        }

        case NODE_BLOCK: {
            if(n->left) check_types(n->left);
            if(n->right) check_types(n->right);
            break;
        }

        case NODE_IF: {
            if(n->left) check_types(n->left);
            if(n->right) check_types(n->right);
            TypeInfo expr_type = n->left->info->eval_type;
            if(expr_type != TYPE_BOOL){
                fprintf(stderr,"Type error: not boolean condition\n");
                type_check_error = true;
            }
            break;
        }

        case NODE_WHILE: {
            if(n->left) check_types(n->left);
            if(n->right) check_types(n->right);
            TypeInfo expr_type = n->left->info->eval_type;
            if(expr_type != TYPE_BOOL){
                fprintf(stderr,"Type error: not boolean condition\n");
                type_check_error = true;
            }
            break;
        }

        case NODE_CALL: {
            if (n->left)  check_types(n->left);
            AST *arg = n->left;
            while (arg) {
                check_types(arg);
                arg = arg->next;
            }
            if (n->next) check_types(n->next);

            AST  *actual_params = n->left;
            Params *formal_params = n->info->params;

            while (formal_params != NULL && actual_params != NULL) {
                if (formal_params->param_type != actual_params->info->eval_type) {
                    fprintf(stderr,
                            "Type error in call to %s: expected type %s but got type %s.\n",
                            n->info->name,
                            type_to_string(formal_params->param_type),
                            type_to_string(actual_params->info->eval_type));
                    type_check_error = true;
                }
                formal_params = formal_params->next;
                actual_params = actual_params->next;
            }

            if (formal_params != NULL) {
                fprintf(stderr,
                        "Error in call to %s: missing parameters.\n",
                        n->info->name);
                type_check_error = true;
            }

            if (actual_params != NULL) {
                fprintf(stderr,
                        "Error in call to %s: too many parameters.\n",
                        n->info->name);
                type_check_error = true;
            }

            break;
        }

        default:
            return;
    }

    if (n->next) check_types(n->next);
}
