%{
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"
#include <sys/stat.h>
#include <sys/types.h>
#include "ast.h"
#include "symbol_table/symtab.h"
#include "symbol_table/build_symtab.h"

extern int debug_mode;
int yylex(void);
void yyerror(const char *s);

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
        if (strcmp((char*)$1, "integer") == 0) {
            $$->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)$1, "bool") == 0) {
            $$->info->eval_type = TYPE_BOOL;
        }
        free($2);
    }
    | param_list ',' type ID {
        AST* new_param = make_node(NODE_PARAM, $4, 0, 0, NULL, NULL, NULL);
        if (strcmp((char*)$3, "integer") == 0) {
            new_param->info->eval_type = TYPE_INT;
        } else if (strcmp((char*)$3, "bool") == 0) {
            new_param->info->eval_type = TYPE_BOOL;
        }
        free($4);

        AST* tail = $1;
        while (tail->next){
            tail = tail->next;
        }
        tail->next = new_param;

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

extern FILE *yyin;
extern FILE *lexout;
FILE *semout;
FILE *sintout;
char lex_filename[256];
char sint_filename[256];
char sent_filename[256];

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
    snprintf(sent_filename, sizeof(sent_filename), "output/%s.sem", base);

    lexout = fopen(lex_filename, "w");
    sintout = fopen(sint_filename, "w");
    semout = fopen(sent_filename, "w");

    if (!lexout || !sintout || !semout) {
        perror("fopen");
        return 1;
    }

    int result = yyparse();

    if (result == 0) {
        fprintf(sintout, "Parser: SUCCESS\n");
        if (root) {
            print_ast(root, 0, 1);
        }
    } else {
        fprintf(sintout, "Parser: FAILED\n");
    }

    fclose(yyin);
    fclose(lexout);
    fclose(sintout);
    fclose(semout);

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

        f = fopen(sent_filename, "r");
        if(f) {
            printf("---- AST (%s) ----\n", sent_filename);
            char c;
            while((c = fgetc(f)) != EOF) putchar(c);
            fclose(f);
        }
        
        SymTab *global = symtab_new();

        TypeInfo result = build_symtab(root, global);
        symtab_print(global);
        
        if (result == TYPE_UNKNOWN) {
            printf("Create symbol table success.\n");
        } else {
            printf("Failed to create symbol table.\n");
        }
    }

    return result;
}

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}
