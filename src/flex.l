%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*

enum yytokentype {
    EXTERN=256, PROGRAM, ELSE, THEN, IF, RETURN, VOID,
    INTEGER_TYPE, BOOL_TYPE, WHILE,
    BOOL_LIT, INT_LIT, ID,
    AND, OR, EQ,
    PLUS, MINUS, MUL, DIV, MOD, LT, GT, ASSIGN, NOT,
    SEMI, LPAREN, RPAREN, LBRACE, RBRACE
};

typedef union {
    int ival;
    int boolean;
    char* sval;
} YYSTYPE;

*/

YYSTYPE yylval;

%}


%option noyywrap
%option yylineno

letra   [a-zA-Z]      
digito  [0-9]

%%

"extern"            { return EXTERN; }
"program"           { return PROGRAM; }
"else"              { return ELSE; }
"then"              { return THEN; }
"if"                { return IF; }
"return"            { return RETURN; }
"void"              { return VOID; }
"integer"           { return INTEGER_TYPE; }
"bool"              { return BOOL_TYPE; }
"while"             { return WHILE; }
"true"              { yylval.boolean = 1; return BOOL_LIT; }
"false"             { yylval.boolean = 0; return BOOL_LIT; }
{digito}+           { yylval.ival = atoi(yytext); return INT_LIT; } 
{letra}({letra}|{digito})*  { yylval.sval = strdup(yytext); return ID; }
 
"//".*;
"/*"([^*]|\n|(\*+[^*/]))*"*/"

"&&"                { return AND; }
"||"                { return OR; }
"=="                { return EQ; }

[+-/*%!<>=]         { return *yytext; }

[;(){}]             { return *yytext; }



[ \t\r\n]+ ;

. {
fprintf(stderr, "Lexical Error at line %d: Unrecognized character '%s'\n", yylineno, yytext);
}

%%

void yyerror(const char *s) {
    // Empty
}

int main() {
    int tok;
    while ((tok = yylex())) {
        printf("Token: %d, lexema: %s\n", tok, yytext);
    }
    return 0;
}

