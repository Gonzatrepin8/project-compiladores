%{
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"
#include <sys/stat.h>
#include <sys/types.h>

extern int debug_mode;
int yylex(void);
void yyerror(const char *s);
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

extern FILE *yyin;
extern FILE *lexout;
FILE *sintout;
char lex_filename[256];
char sint_filename[256];

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s [-debug] <sourcefile>\n", argv[0]);
        return 1;
    }

    int argi = 1;
    if (strcmp(argv[1], "-debug") == 0) {
        debug_mode = 1;
        argi++;
    }

    if (argi >= argc) {
        fprintf(stderr, "No input file given.\n");
        return 1;
    }

    yyin = fopen(argv[argi], "r");
    if (!yyin) {
        perror("fopen");
        return 1;
    }

    const char *inputfile = argv[argi];

    struct stat st = {0};
    if (stat("output", &st) == -1) {
        if (mkdir("output", 0700) != 0) {
            perror("mkdir");
            return 1;
        }
    }

    char base[256];
    strncpy(base, basename((char *)inputfile), sizeof(base) - 1);
    base[sizeof(base) - 1] = '\0';

    char *dot = strrchr(base, '.');
    if (dot) *dot = '\0';

    snprintf(lex_filename, sizeof(lex_filename), "output/%s.lex", base);
    snprintf(sint_filename, sizeof(sint_filename), "output/%s.sint", base);

    lexout = fopen(lex_filename, "w");
    sintout = fopen(sint_filename, "w");

    if (!lexout || !sintout) {
        perror("fopen");
        return 1;
    }

    int result = yyparse();

    if (result == 0) {
        fprintf(sintout, "Parser: SUCCESS\n");
    } else {
        fprintf(sintout, "Parser: FAILED\n");
    }

    fclose(yyin);
    fclose(lexout);
    fclose(sintout);

    if (debug_mode) {
        FILE *f = fopen(lex_filename, "r");
        if (f) {
            printf("---- Lexer Output (%s) ----\n", lex_filename);
            char c;
            while ((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }

        f = fopen(sint_filename, "r");
        if (f) {
            printf("---- Parser Output (%s) ----\n", sint_filename);
            char c;
            while ((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }
    }

    return result;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

