%{

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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
"false"             { return FALSE; }
"if"                { return IF; }
"integer"           { return INTEGER; }
"return"            { return RETURN; }
"true"              { return TRUE; }
"void"              { return VOID; }
"while"             { return WHILE; }

"&&"                { return AND; }
"||"                { return OR; }
"=="                { return EQ; }

[+-/*%!<>]          { return *yytext; }

[;(){}]             { return *yytext; }

"//".* ;
"/\*.*\*/";

[ \t\r\n]+ ;

. {
fprintf(stderr, "Lexical Error at line %d: Unrecognized character '%s'\n", yylineno, yytext);
}

%%

void yyerror(const char *s) {
    // Empty
}

int main(int argc,char *argv[]){
    ++argv,--argc;
    if (argc > 0)
        yyin = fopen(argv[0],"r");
    else
        yyin = stdin;

    if (yyparse() == 0) {
        // Empty
    }
    return 0;
}
