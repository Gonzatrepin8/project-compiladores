%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"
#include "ast.h"

void yyerror(const char *s);
int yylex(void);
extern int yylineno;
extern FILE *yyin;

AST *root = NULL;
%}

%union {
    int ival;
    int bval;
    char* sval;
    struct AST *ast;
}

%token PROGRAM EXTERN BOOL_TYPE ELSE THEN FALSE IF INTEGER_TYPE RETURN TRUE VOID WHILE
%token EQ AND OR

%token <ival> INT_LIT
%token <bval> BOOL_LIT
%token <sval> ID

%type <ast> program expr literal var_decls var_decl stmt stmt_list
%type <ast> method_decls method_decl block return_body
%type <ast> op_else method_call arg_list_opt arg_list
%type <ast> param_list_opt param_list method_body
%type <sval> type

%left OR
%left AND
%left EQ
%left '<' '>'
%left '+' '-'
%left '*' '/' '%'
%right '!'
%right UMINUS


%%

program
    : PROGRAM '{' var_decls method_decls '}' {
        $$ = make_node(NODE_PROG, NULL, 0, 0, NULL, $3, $4);
        root = $$;
    }
    | PROGRAM '{' var_decls '}' {
        $$ = make_node(NODE_PROG, NULL, 0, 0, NULL, $3, NULL);
        root = $$;
    }
    | PROGRAM '{' method_decls '}' {
        $$ = make_node(NODE_PROG, NULL, 0, 0, NULL, NULL, $3);
        root = $$;
    }
    | PROGRAM '{' '}' {
        $$ = make_node(NODE_PROG, NULL, 0, 0, NULL, NULL, NULL);
        root = $$;
    }
    ;

var_decls
    : var_decl {
        $$ = $1;
    }
    | var_decls var_decl {
        AST *temp = $1;
        if(temp) {
            while(temp->next) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    ;

var_decl
    : type ID '=' expr ';' {
        AST* id_node = make_node(NODE_ID, $2, 0, 0, NULL, NULL, NULL);
        AST* assign_node = make_node(NODE_ASSIGN, NULL, 0, 0, NULL, id_node, $4);
        $$ = make_node(NODE_VAR_DECL, $2, 0, 0, NULL, NULL, assign_node);
        if (strcmp((char*)$1, "integer") == 0) {
            $$->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)$1, "bool") == 0) {
            $$->info->eval_type = TYPE_BOOL;
        }
        free($2);
    }
    ;

method_decls
    : method_decl {
        $$ = $1;
    }
    | method_decls method_decl {
        AST *temp = $1;
        if (temp) {
            while(temp->next) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        } else {
            $$ = $2;
        }
    }
    ;

method_decl
    : type ID '(' param_list_opt ')' method_body {
        $$ = make_node(NODE_FUNCTION, $2, 0, 0, NULL, $4, $6);
        if (strcmp((char*)$1, "integer") == 0) {
            $$->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)$1, "bool") == 0) {
            $$->info->eval_type = TYPE_BOOL;
        }
        free($2);
    }
    | VOID ID '(' param_list_opt ')' method_body {
        $$ = make_node(NODE_FUNCTION, $2, 0, 0, NULL, $4, $6);
        $$->info->eval_type = TYPE_VOID;
        free($2);
    }
    ;

method_body
    : block {
        $$ = $1;
    }
    | EXTERN ';' {
        $$ = make_node(NODE_ID, "EXTERN", 0, 0, NULL, NULL, NULL);
    }
    ;

param_list_opt
    : /* empty */ {
        $$ = NULL;
    }
    | param_list {
        $$ = $1;
    }
    ;

param_list
    : type ID {
        $$ = make_node(NODE_PARAM, $2, 0, 0, NULL, NULL, NULL);
        free($2);
    }
    | param_list ',' type ID {
        AST* new_param = make_node(NODE_PARAM, $4, 0, 0, NULL, NULL, NULL);
        free($4);
        $1->next = new_param;
        $$ = $1;
    }
    ;


block
    : '{' var_decls stmt_list '}' {
        $$ = make_node(NODE_BLOCK, NULL, 0, 0, NULL, $2, $3);
    }
    | '{' stmt_list '}' {
        $$ = make_node(NODE_BLOCK, NULL, 0, 0, NULL, NULL, $2);
    }
    ;

stmt_list
    : /* empty */ {
        $$ = NULL;
    }
    | stmt_list stmt {
        if ($1 == NULL) {
            $$ = $2;
        } else if ($2 != NULL) {
            AST *temp = $1;
            while(temp->next) temp = temp->next;
            temp->next = $2;
            $$ = $1;
        } else {
            $$ = $1;
        }
    }
    ;

stmt
    : ID '=' expr ';' {
        $$ = make_node(NODE_ASSIGN, NULL, 0, 0, NULL, make_node(NODE_ID, $1, 0, 0, NULL, NULL, NULL), $3);
        free($1);
    }
    | method_call ';' {
        $$ = $1;
    }
    | IF '(' expr ')' THEN block op_else {
        $$ = make_node(NODE_IF, NULL, 0, 0, NULL, $3, $6);
        if ($6) $6->next = $7;
    }
    | WHILE expr block {
        $$ = make_node(NODE_WHILE, NULL, 0, 0, NULL, $2, $3);
    }
    | RETURN return_body ';' {
        $$ = make_node(NODE_RETURN, NULL, 0, 0, NULL, $2, NULL);
    }
    | ';' {
        $$ = NULL;
    }
    | block {
        $$ = $1;
    }
    ;

op_else
    : /* empty */ {
        $$ = NULL;
    }
    | ELSE block {
        $$ = $2;
    }
    ;

method_call
    : ID '(' arg_list_opt ')' {
        $$ = make_node(NODE_CALL, $1, 0, 0, NULL, $3, NULL);
        free($1);
    }
    ;

arg_list_opt
    : /* empty */ {
        $$ = NULL;
    }
    | arg_list {
        $$ = $1;
    }
    ;

arg_list
    : expr {
        $$ = $1;
    }
    | arg_list ',' expr {
        $1->next = $3;
        $$ = $1;
    }
    ;

return_body
    : /* empty */ {
        $$ = NULL;
    }
    | expr {
        $$ = $1;
    }
    ;

type
    : INTEGER_TYPE { $$ = strdup("integer"); }
    | BOOL_TYPE    { $$ = strdup("bool"); }


expr
    : ID {
        $$ = make_node(NODE_ID, $1, 0, 0, NULL, NULL, NULL);
        free($1);
    }
    | method_call {
        $$ = $1;
    }
    | literal {
        $$ = $1;
    }
    | expr '+' expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "+", $1, $3);
    }
    | expr '-' expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "-", $1, $3);
    }
    | expr '*' expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "*", $1, $3);
    }
    | expr '/' expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "/", $1, $3);
    }
    | expr '%' expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "%", $1, $3);
    }
    | expr '<' expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "<", $1, $3);
    }
    | expr '>' expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, ">", $1, $3);
    }
    | expr EQ expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "==", $1, $3);
    }
    | expr AND expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "&&", $1, $3);
    }
    | expr OR expr {
        $$ = make_node(NODE_BINOP, NULL, 0, 0, "||", $1, $3);
    }
    | '-' expr %prec UMINUS {
        $$ = make_node(NODE_UNOP, NULL, 0, 0, "-", $2, NULL);
    }
    | '!' expr {
        $$ = make_node(NODE_UNOP, NULL, 0, 0, "!", $2, NULL);
    }
    | '(' expr ')' {
        $$ = $2;
    }
    ;

literal
    : INT_LIT {
        $$ = make_node(NODE_INT, NULL, $1, 0, NULL, NULL, NULL);
    }
    | BOOL_LIT {
        $$ = make_node(NODE_BOOL, NULL, 0, $1, NULL, NULL, NULL);
    }
    ;
%%

int main(int argc, char **argv) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            perror(argv[1]);
            return 1;
        }
        yyin = file;
    } else {
        printf("Uso: %s <archivo_de_entrada>\n", argv[0]);
        return 1;
    }

    if (yyparse() == 0) {
        printf("Parsing completado con éxito.\n");
        printf("\n--- Abstract Syntax Tree ---\n");
        print_ast(root, 0, 1);
    } else {
        printf("\nParsing fallido.\n");
    }

    return 0;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

