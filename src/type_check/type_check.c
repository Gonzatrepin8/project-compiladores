#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "type_check.h"
#include "../ast/ast.h"

bool type_check_error = false;
static TypeInfo func_type = TYPE_ERROR;

static bool has_return(AST *n) {
    if (!n) return false;

    if (n->type == NODE_RETURN) return true;

    if (n->left && has_return(n->left)) return true;
    if (n->right && has_return(n->right)) return true;
    if (n->next && has_return(n->next)) return true;

    return false;
}

void check_types(AST* n) {
    if (!n) return;

    switch (n->type) {
        case NODE_PROG:
                if (n->left) check_types(n->left);
                if (n->right) check_types(n->right);
            break;

        case NODE_ID:
            if (n->info && n->info->is_function) {
                n->info->eval_type = TYPE_ERROR;
                type_check_error = true;
            }
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
                    fprintf(stderr,"Type error: function expects %s but returns void\n" , type_to_string(func_type));
                    type_check_error = true;
                }
            } else {
                check_types(n->left);
                n->info->eval_type = n->left->info->eval_type;
                if (n->info->eval_type != func_type) {
                    fprintf(stderr,"Type error: function expects %s but returns %s\n",
                            type_to_string(func_type),
                            type_to_string(n->info->eval_type));
                    type_check_error = true;
                }
            }
            break;
        }

        case NODE_FUNCTION: {
            func_type = n->info->eval_type;
            if(n->left) check_types(n->left);
            if(n->right) check_types(n->right);

            if (func_type != TYPE_VOID) {
                bool is_extern = (n->right && n->right->type == NODE_ID &&
                                  n->right->info && n->right->info->name &&
                                  strcmp(n->right->info->name, "EXTERN") == 0);

                if (!is_extern && !has_return(n->right)) {
                    fprintf(stderr,
                            "Type error: function '%s' declared as %s but has no return statement.\n",
                            (n->info && n->info->name) ? n->info->name : "(unknown)",
                            type_to_string(func_type));
                    type_check_error = true;
                }
            }

            func_type = TYPE_ERROR;
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
            if (n->left) check_types(n->left);
            if (n->next) check_types(n->next);

            AST  *actual_params = n->left;
            Params *formal_params = n->info->params;

            while (formal_params != NULL && actual_params != NULL) {
                check_types(actual_params);
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
