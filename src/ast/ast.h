#ifndef AST_H
#define AST_H

#include <stdio.h>
#include "../parser.tab.h"

typedef enum {
    NODE_INT,
    NODE_BOOL,
    NODE_ID,
    NODE_BINOP,
    NODE_UNOP,
    NODE_ASSIGN,
    NODE_RETURN,
    NODE_IF,
    NODE_WHILE,
    NODE_FUNCTION,
    NODE_VAR_DECL,
    NODE_BLOCK,
    NODE_PROG,
    NODE_CALL,
    NODE_PARAM,
} NodeType;

typedef enum {
    TYPE_INT,
    TYPE_BOOL,
    TYPE_VOID,
    TYPE_UNKNOWN,
    TYPE_ERROR
} TypeInfo;

typedef struct Params{
    char* param_name;
    TypeInfo param_type;
    struct Params *next;
} Params;

typedef struct Info {
    char* name;
    int ival;
    int bval;
    int scope;
    char* op;
    TypeInfo eval_type;
    int is_function;
    Params *params;
} Info;

typedef struct AST {
    NodeType type;
    struct Info *info;
    struct AST *left;
    struct AST *right;
    struct AST *next;
} AST;

AST *make_node(NodeType type, char *name, int ival, int bval,
               char* op, AST *left, AST *right);

void print_ast(AST *n, int depth, int is_last);

const char* type_to_string(TypeInfo t);

#endif
