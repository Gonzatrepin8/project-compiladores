%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"
%}

%token PROGRAM EXTERN BOOL_TYPE ELSE THEN FALSE IF INTEGER_TYPE RETURN TRUE VOID WHILE
%token EQ AND OR

%union {
    int ival;
    int bval;
    char* sval;
}

%token <ival> INT_LIT
%token <bval> BOOL_LIT
%token <sval> ID

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
    : PROGRAM '{' var_decls method_decls '}'
    | PROGRAM '{' var_decls '}'
    | PROGRAM '{' method_decls '}'
    | PROGRAM '{' '}'
    ;

var_decls
    : var_decl
    | var_decls var_decl
    ;

var_decl
    : type ID '=' expr ';'
    ;

method_decls
    : method_decl
    | method_decls method_decl
    ;

method_decl
    : type ID '(' param_list_opt ')' method_body
    | VOID ID '(' param_list_opt ')' method_body
    ;

param_list_opt
    : /* empty */
    | param_list
    ;

param_list
    : type ID
    | param_list ',' type ID
    ;

method_body
    : block
    | EXTERN ';'
    ;

block
    : '{' var_decls stmt_list '}'
    | '{' stmt_list '}'
    ;

stmt_list
    : /* empty */
    | stmt_list stmt
    ;

stmt
    : ID '=' expr ';'
    | method_call ';'
    | IF '(' expr ')' THEN block op_else
    | WHILE expr block
    | RETURN return_body ';'
    | ';'
    | block
    ;

op_else
    : /* empty */
    | ELSE block
    ;

method_call
    : ID '(' arg_list_opt ')'
    ;

arg_list_opt
    : /* empty */
    | arg_list
    ;

arg_list
    : expr
    | arg_list ',' expr
    ;

return_body
    : /* empty */
    | expr
    ;

type
    : INTEGER_TYPE
    | BOOL_TYPE
    ;

expr
    : ID
    | method_call
    | literal
    | expr '+' expr
    | expr '-' expr
    | expr '*' expr
    | expr '/' expr
    | expr '%' expr
    | expr '<' expr
    | expr '>' expr
    | expr EQ expr
    | expr AND expr
    | expr OR expr
    | '-' expr %prec UMINUS
    | '!' expr
    | '(' expr ')'
    ;

literal
    : INT_LIT
    | BOOL_LIT
    ;
%%

int main(void) { return yyparse(); }

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

