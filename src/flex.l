%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"

int debug_mode = 0;
FILE *lexout;
%}


%option noyywrap
%option yylineno

letra   [a-zA-Z]      
digito  [0-9]

%%

"extern"            { fprintf(lexout, "TOKEN: EXTERN\n"); return EXTERN; }
"program"           { fprintf(lexout, "TOKEN: PROGRAM\n"); return PROGRAM; }
"else"              { fprintf(lexout, "TOKEN: ELSE\n"); return ELSE; }
"then"              { fprintf(lexout, "TOKEN: THEN\n"); return THEN; }
"if"                { fprintf(lexout, "TOKEN: IF\n"); return IF; }
"return"            { fprintf(lexout, "TOKEN: RETURN\n"); return RETURN; }
"void"              { fprintf(lexout, "TOKEN: VOID\n"); return VOID; }
"integer"           { fprintf(lexout, "TOKEN: INTEGER_TYPE\n"); return INTEGER_TYPE; }
"bool"              { fprintf(lexout, "TOKEN: BOOL_TYPE\n"); return BOOL_TYPE; }
"while"             { fprintf(lexout, "TOKEN: WHILE\n"); return WHILE; }
"true"  {
    yylval.bval = 1;
    fprintf(lexout, "TOKEN: BOOL_LIT (true)\n");
    return BOOL_LIT;
}
"false" {
    yylval.bval = 0;
    fprintf(lexout, "TOKEN: BOOL_LIT (false)\n");
    return BOOL_LIT;
}
{digito}+ {
    yylval.ival = atoi(yytext);
    fprintf(lexout, "TOKEN: INT_LIT (%d)\n", yylval.ival);
    return INT_LIT;
}

{letra}({letra}|{digito}|_)* {
    yylval.sval = strdup(yytext);
    fprintf(lexout, "TOKEN: ID (%s)\n", yylval.sval);
    return ID;
}
 
"//".* { }
"/*"([^*]|\n|(\*+[^*/]))*"*/" { }

"&&"                { fprintf(lexout, "TOKEN: AND\n"); return AND; }
"||"                { fprintf(lexout, "TOKEN: OR\n");  return OR; }
"=="                { fprintf(lexout, "TOKEN: EQ\n");  return EQ; }

[+-/*%!<>=]         { fprintf(lexout, "TOKEN: OPERATOR (%s)\n", yytext); return *yytext; }
[;(){}]             { fprintf(lexout, "TOKEN: SYMBOL (%s)\n", yytext);   return *yytext; }



[ \t\r\n]+ ;

. {
fprintf(stderr, "Lexical Error at line %d: Unrecognized character '%s'\n", yylineno, yytext);
}

%%
