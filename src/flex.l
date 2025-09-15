%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "parser.tab.h"

int debug_mode = 0;
%}


%option noyywrap
%option yylineno

letra   [a-zA-Z]      
digito  [0-9]

%%

"extern"            { if (debug_mode) printf("TOKEN: EXTERN\n"); return EXTERN; }
"program"           { if (debug_mode) printf("TOKEN: PROGRAM\n"); return PROGRAM; }
"else"              { if (debug_mode) printf("TOKEN: ELSE\n"); return ELSE; }
"then"              { if (debug_mode) printf("TOKEN: THEN\n"); return THEN; }
"if"                { if (debug_mode) printf("TOKEN: IF\n"); return IF; }
"return"            { if (debug_mode) printf("TOKEN: RETURN\n"); return RETURN; }
"void"              { if (debug_mode) printf("TOKEN: VOID\n"); return VOID; }
"integer"           { if (debug_mode) printf("TOKEN: INTEGER_TYPE\n"); return INTEGER_TYPE; }
"bool"              { if (debug_mode) printf("TOKEN: BOOL_TYPE\n"); return BOOL_TYPE; }
"while"             { if (debug_mode) printf("TOKEN: WHILE\n"); return WHILE; }
"true"  {
    yylval.bval = 1;
    if (debug_mode) printf("TOKEN: BOOL_LIT (true)\n");
    return BOOL_LIT;
}
"false" {
    yylval.bval = 0;
    if (debug_mode) printf("TOKEN: BOOL_LIT (false)\n");
    return BOOL_LIT;
}
{digito}+ {
    yylval.ival = atoi(yytext);
    if (debug_mode) printf("TOKEN: INT_LIT (%d)\n", yylval.ival);
    return INT_LIT;
}

{letra}({letra}|{digito}|_)* {
    yylval.sval = strdup(yytext);
    if (debug_mode) printf("TOKEN: ID (%s)\n", yylval.sval);
    return ID;
}
 
"//".* { }
"/*"([^*]|\n|(\*+[^*/]))*"*/" { }

"&&"                { if (debug_mode) printf("TOKEN: AND\n"); return AND; }
"||"                { if (debug_mode) printf("TOKEN: OR\n");  return OR; }
"=="                { if (debug_mode) printf("TOKEN: EQ\n");  return EQ; }

[+-/*%!<>=]         { if (debug_mode) printf("TOKEN: OPERATOR (%s)\n", yytext); return *yytext; }
[;(){}]             { if (debug_mode) printf("TOKEN: SYMBOL (%s)\n", yytext);   return *yytext; }



[ \t\r\n]+ ;

. {
fprintf(stderr, "Lexical Error at line %d: Unrecognized character '%s'\n", yylineno, yytext);
}

%%
