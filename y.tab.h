/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INC = 258,
    DEC = 259,
    OR = 260,
    AND = 261,
    ASSIGN = 262,
    KEYWORD_IF = 263,
    KEYWORD_WHILE = 264,
    KEYWORD_ELSE = 265,
    KEYWORD_FOR = 266,
    KEYWORD_CLASS = 267,
    MAIN = 268,
    GHI = 269,
    LIBRARY = 270,
    EQUAL = 271,
    KEYWORD_INCLUDE = 272,
    KEYWORD_RETURN = 273,
    READ = 274,
    WRITE = 275,
    NR = 276,
    ID = 277,
    KEYWORD_TYPE = 278,
    KEYWORD_CLASS_TYPE = 279,
    KEYWORD_CONST = 280,
    STRCAT = 281,
    STRSTR = 282,
    STRCHR = 283,
    STRCMP = 284,
    STRLEN = 285,
    STRCPY = 286,
    EVAL = 287
  };
#endif
/* Tokens.  */
#define INC 258
#define DEC 259
#define OR 260
#define AND 261
#define ASSIGN 262
#define KEYWORD_IF 263
#define KEYWORD_WHILE 264
#define KEYWORD_ELSE 265
#define KEYWORD_FOR 266
#define KEYWORD_CLASS 267
#define MAIN 268
#define GHI 269
#define LIBRARY 270
#define EQUAL 271
#define KEYWORD_INCLUDE 272
#define KEYWORD_RETURN 273
#define READ 274
#define WRITE 275
#define NR 276
#define ID 277
#define KEYWORD_TYPE 278
#define KEYWORD_CLASS_TYPE 279
#define KEYWORD_CONST 280
#define STRCAT 281
#define STRSTR 282
#define STRCHR 283
#define STRCMP 284
#define STRLEN 285
#define STRCPY 286
#define EVAL 287

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 290 "lexer.y"

      int nr;
      char* str;

#line 126 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
