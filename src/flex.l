%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"
#include "ast.h"

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
"true"              { yylval.bval = 1; return BOOL_LIT; }
"false"             { yylval.bval = 0; return BOOL_LIT; }
{digito}+           { yylval.ival = atoi(yytext); return INT_LIT; } 
{letra}({letra}|{digito}|_)*  { yylval.sval = strdup(yytext); return ID; }
 
"//".* { }
"/*"([^*]|\n|(\*+[^*/]))*"*/" { }

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
