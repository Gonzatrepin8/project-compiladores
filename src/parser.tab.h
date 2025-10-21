/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     PROGRAM = 258,
     EXTERN = 259,
     BOOL_TYPE = 260,
     ELSE = 261,
     THEN = 262,
     FALSE = 263,
     IF = 264,
     INTEGER_TYPE = 265,
     RETURN = 266,
     TRUE = 267,
     VOID = 268,
     WHILE = 269,
     EQ = 270,
     AND = 271,
     OR = 272,
     INT_LIT = 273,
     BOOL_LIT = 274,
     ID = 275,
     UMINUS = 276
   };
#endif
/* Tokens.  */
#define PROGRAM 258
#define EXTERN 259
#define BOOL_TYPE 260
#define ELSE 261
#define THEN 262
#define FALSE 263
#define IF 264
#define INTEGER_TYPE 265
#define RETURN 266
#define TRUE 267
#define VOID 268
#define WHILE 269
#define EQ 270
#define AND 271
#define OR 272
#define INT_LIT 273
#define BOOL_LIT 274
#define ID 275
#define UMINUS 276




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 13 "src/parser.y"
{
    int ival;
    int bval;
    char* sval;
    struct AST *ast;
}
/* Line 1529 of yacc.c.  */
#line 98 "src/parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

