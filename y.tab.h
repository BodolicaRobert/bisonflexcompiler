/* A Bison parser, made by GNU Bison 3.7.3.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    KEYWORD_IF = 258,              /* KEYWORD_IF  */
    KEYWORD_WHILE = 259,           /* KEYWORD_WHILE  */
    KEYWORD_ELSE = 260,            /* KEYWORD_ELSE  */
    KEYWORD_FOR = 261,             /* KEYWORD_FOR  */
    AND = 262,                     /* AND  */
    OR = 263,                      /* OR  */
    ASSIGN = 264,                  /* ASSIGN  */
    KEYWORD_CLASS = 265,           /* KEYWORD_CLASS  */
    MAIN = 266,                    /* MAIN  */
    GHI = 267,                     /* GHI  */
    LIBRARY = 268,                 /* LIBRARY  */
    EQUAL = 269,                   /* EQUAL  */
    KEYWORD_INCLUDE = 270,         /* KEYWORD_INCLUDE  */
    KEYWORD_RETURN = 271,          /* KEYWORD_RETURN  */
    READ = 272,                    /* READ  */
    WRITE = 273,                   /* WRITE  */
    NR = 274,                      /* NR  */
    ID = 275,                      /* ID  */
    KEYWORD_TYPE = 276,            /* KEYWORD_TYPE  */
    KEYWORD_CLASS_TYPE = 277,      /* KEYWORD_CLASS_TYPE  */
    KEYWORD_CONST = 278,           /* KEYWORD_CONST  */
    INC = 279,                     /* INC  */
    DEC = 280,                     /* DEC  */
    STRCAT = 281,                  /* STRCAT  */
    STRSTR = 282,                  /* STRSTR  */
    STRCHR = 283,                  /* STRCHR  */
    STRCMP = 284,                  /* STRCMP  */
    STRLEN = 285,                  /* STRLEN  */
    STRCPY = 286,                  /* STRCPY  */
    EVAL = 287                     /* EVAL  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define KEYWORD_IF 258
#define KEYWORD_WHILE 259
#define KEYWORD_ELSE 260
#define KEYWORD_FOR 261
#define AND 262
#define OR 263
#define ASSIGN 264
#define KEYWORD_CLASS 265
#define MAIN 266
#define GHI 267
#define LIBRARY 268
#define EQUAL 269
#define KEYWORD_INCLUDE 270
#define KEYWORD_RETURN 271
#define READ 272
#define WRITE 273
#define NR 274
#define ID 275
#define KEYWORD_TYPE 276
#define KEYWORD_CLASS_TYPE 277
#define KEYWORD_CONST 278
#define INC 279
#define DEC 280
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
#line 363 "lexer.y"

      int nr;
      char* str;

#line 135 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
