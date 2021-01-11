/* A Bison parser, made by GNU Bison 3.7.3.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.7.3"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "lexer.y"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
extern int yyerror(char* syntaxerror);


int var_counter=0,new_var_counter=0;
int function_counter=0,new_function_counter=0;
struct variable
{
      int value;
      char* data_type;
      char* name;
      char* constant_value;
      char* initialization;

};
struct variable var[1000];

struct function 
{
      char* type;
      char* name;
      char * parameters;
 
};
struct function funct[1000];



int is_declared(char* name) // we check if a variable exists or not in the vector of variables
{
  for (int i = 0; i < var_counter; i++) {
    if(strcmp(var[i].name,name)==0) {
      return i; 
    }
  }
  return -1;
}

void var_declaring(char* name, char* data_type, int value, char* const_var) //we insert variables with initialization into the vector of variables
{
   if(is_declared(name)==-1)
  { var[var_counter].name = strdup(name);
    var[var_counter].data_type=strdup(data_type);
    var[var_counter].value=value;
    var[var_counter].constant_value = strdup(const_var);
    var[var_counter].initialization="YES";
    var_counter++;
  }
  else
  {     char message[256];
        sprintf(message,"variable '%s' is already declared",name);
        yyerror(message);
        exit(0);
  }
}

void var_declaring_without_init(char* name, char* data_type, char* const_var) //we  insert variable w/ initialization
{
  if(is_declared(name)==-1)
  { var[var_counter].name=strdup(name);
    var[var_counter].data_type=strdup(data_type);
    var[var_counter].value=0;
    var[var_counter].constant_value = strdup(const_var);
    var[var_counter].initialization="NOPE";
    var_counter++;
  }
     else
  {     char message[256];
        sprintf(message,"variable '%s' is already declared",name);
        yyerror(message);
        exit(0);
  }
}

int verify_if_declared(char* name) // we search if the variable was declared or not and if it was declared we return the position
{
   for(int i=0;i<var_counter;i++)
       {if(strcmp(var[i].name,name)==0) return i;}
  return -1;                                       
}
void var_verification(char* name) // we verify if the variable was declared or not 
{
      if(verify_if_declared(name)==-1)
                 {char message[256];
                     sprintf(message,"variable '%s' was not declared",name);
                     yyerror(message);
                     exit(0);
                 }       
}

void initialization_verify(char*name)  // we check if the right side of an expression is initialized
{
     for(int i=0;i<var_counter;i++)
      if(strcmp(var[i].name,name)==0)
         if(strcmp(var[i].initialization,"NOPE")==0)  
         {char message[256];
          sprintf(message,"variable '%s' was not initialized",name);
          yyerror(message);
          exit(0);
         }   
}

int return_value(char * name)
{
      for(int i=0;i<var_counter;i++)
      if(strcmp(var[i].name,name)==0)
         if(strcmp(var[i].initialization,"NOPE")!=0 && (strcmp(var[i].data_type,"int")==0 || strcmp(var[i].data_type,"const int")==0)) return var[i].value ;
           else return 0;  
}

void Assign(char* name,int value)
{
        if(strcmp(var[verify_if_declared(name)].constant_value,"YES")==0)
        {char message[256];
          sprintf(message,"The constant variable %s can't be on the left side of an assignment",name);
          yyerror(message);
          exit(0);
        }
        if(strcmp(var[verify_if_declared(name)].data_type,"int")==0 && value != 0)                                                                            
        {var[verify_if_declared(name)].value=value;
        var[verify_if_declared(name)].initialization=strdup("YES");  }
        else if(strcmp(var[verify_if_declared(name)].data_type,"float")==0 && value != 0)
          {var[verify_if_declared(name)].initialization=strdup("YES");  }
        else if(strcmp(var[verify_if_declared(name)].data_type,"double")==0 && value != 0)
          {var[verify_if_declared(name)].initialization=strdup("YES");  }
        else if(strcmp(var[verify_if_declared(name)].data_type,"bool")==0 && ( value == 0 || value==1))
          {var[verify_if_declared(name)].initialization=strdup("YES");}
        else
        if(strcmp(var[verify_if_declared(name)].data_type,"char")==0 && value == 0)
        {var[verify_if_declared(name)].initialization=strdup("YES");  }
        else 
        {   char message[256];
            sprintf(message,"The variable %s can't have another type of variable",name);
            yyerror(message);
            exit(0); 
        }       
}


int already_declared_function(char* name,char * parameters)
{
    for(int i=0;i<function_counter;i++)
    {    if(strcmp(funct[i].name,name)==0)
                     return i;                                 
    }  
    return -1;
}

void declaring_function(char* type,char* name,char * parameters)
{    
      if(already_declared_function(name,type)==-1)
         {funct[function_counter].type=type;
          funct[function_counter].name=name;
          funct[function_counter].parameters=parameters;
          function_counter++;
         }
        else {char message[256];
              sprintf(message,"Function '%s' was already declared",name);
              yyerror(message);
              exit(0);
              }  
}

int verifyIF_functionDEFINED(char* name)/// we verify if the the function was defined
{
   for(int i=0;i<function_counter;i++)
       {if(strcmp(funct[i].name,name)==0) return i;    
       }
  return -1;                                       
}
void identify_function(char* name,char * parameters) // we identify the function when it is called
{   
       if(verifyIF_functionDEFINED(name)==-1)
                 {   char message[256];
                     sprintf(message,"Function '%s' was not declared",name);
                     yyerror(message);
                     exit(0);
                 }    


      char args[1000]="";
      char *p=malloc(100);
      p=strtok(parameters,";");
      while(p!=NULL)
      {     if(strcmp(p,"int")==0) {strcat(args,"int;");}
            else    
               { if(verify_if_declared(p)!=-1) 
                {strcat(args,var[verify_if_declared(p)].data_type);
                 strcat(args,";");
                }
               }
            p=strtok(NULL,";");
      }
      
      if(strcmp(funct[verifyIF_functionDEFINED(name)].parameters,args)!=0)
      {char message[256];
       sprintf(message,"The parameters of the called function %s do not have the same type as in the definition of the function.",name);
       yyerror(message);
       exit(0);}       
}

void PrintVar( char* type)
{
  FILE* s = fopen("symbol_table.txt", "a");
  fprintf(s,"\n Variable statements In '%s':\n",type);
  
  for(int i=new_var_counter;i<var_counter;i++)
  { fprintf(s,"name: '%s' ,type:'%s' , value: '%d' ,constant '%s' \n",var[i].name,var[i].data_type,var[i].value,var[i].constant_value);  
  }
  new_var_counter=var_counter;
  fclose(s);
} 

void PrintFunct(char * type)
{
  FILE* s=fopen("symbol_table.txt","a");
  fprintf(s,"\n Functions in '%s':\n",type);
   
  for(int j=new_function_counter;j<function_counter;j++)
  { fprintf(s,"name: '%s' ,type:'%s'  ,parameters: %s \n" ,funct[j].name,funct[j].type,funct[j].parameters);    
  }
  new_function_counter=function_counter;
  fclose(s);
}

int expression[1000],exprr=0;
void add_arg(int ex)
{
   expression[exprr]=ex;
   exprr++;
}

void show_exp()
{
      for(int i=0;i<exprr;i++)
      {  printf("The value of the  expression  with the number %d is :%d\n",i+1,expression[i]);
      }
}

void incr(char * name)
{
      if(is_declared(name)!=-1)
      { if(strcmp(var[verify_if_declared(name)].data_type,"int")==0) var[verify_if_declared(name)].value++;
      }
}

void decr(char * name)
{
      if(is_declared(name)!=-1)
      { 
        if(strcmp(var[verify_if_declared(name)].data_type,"int")==0)
        {
          var[verify_if_declared(name)].value--;
        }
      }
}


#line 338 "lexer.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif


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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 287 "lexer.y"

      int nr;
      char* str;

#line 422 "lexer.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);


/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_3_ = 3,                         /* ','  */
  YYSYMBOL_4_ = 4,                         /* ';'  */
  YYSYMBOL_5_ = 5,                         /* '+'  */
  YYSYMBOL_6_ = 6,                         /* '-'  */
  YYSYMBOL_7_ = 7,                         /* ':'  */
  YYSYMBOL_8_ = 8,                         /* '*'  */
  YYSYMBOL_9_ = 9,                         /* '('  */
  YYSYMBOL_10_ = 10,                       /* ')'  */
  YYSYMBOL_11_ = 11,                       /* '{'  */
  YYSYMBOL_12_ = 12,                       /* '}'  */
  YYSYMBOL_13_ = 13,                       /* '['  */
  YYSYMBOL_14_ = 14,                       /* ']'  */
  YYSYMBOL_15_ = 15,                       /* '<'  */
  YYSYMBOL_16_ = 16,                       /* '>'  */
  YYSYMBOL_17_ = 17,                       /* '='  */
  YYSYMBOL_18_ = 18,                       /* '!'  */
  YYSYMBOL_19_ = 19,                       /* '"'  */
  YYSYMBOL_20_ = 20,                       /* '#'  */
  YYSYMBOL_KEYWORD_IF = 21,                /* KEYWORD_IF  */
  YYSYMBOL_KEYWORD_WHILE = 22,             /* KEYWORD_WHILE  */
  YYSYMBOL_KEYWORD_ELSE = 23,              /* KEYWORD_ELSE  */
  YYSYMBOL_KEYWORD_FOR = 24,               /* KEYWORD_FOR  */
  YYSYMBOL_AND = 25,                       /* AND  */
  YYSYMBOL_OR = 26,                        /* OR  */
  YYSYMBOL_ASSIGN = 27,                    /* ASSIGN  */
  YYSYMBOL_KEYWORD_CLASS = 28,             /* KEYWORD_CLASS  */
  YYSYMBOL_MAIN = 29,                      /* MAIN  */
  YYSYMBOL_GHI = 30,                       /* GHI  */
  YYSYMBOL_LIBRARY = 31,                   /* LIBRARY  */
  YYSYMBOL_EQUAL = 32,                     /* EQUAL  */
  YYSYMBOL_KEYWORD_INCLUDE = 33,           /* KEYWORD_INCLUDE  */
  YYSYMBOL_KEYWORD_RETURN = 34,            /* KEYWORD_RETURN  */
  YYSYMBOL_READ = 35,                      /* READ  */
  YYSYMBOL_WRITE = 36,                     /* WRITE  */
  YYSYMBOL_NR = 37,                        /* NR  */
  YYSYMBOL_ID = 38,                        /* ID  */
  YYSYMBOL_KEYWORD_TYPE = 39,              /* KEYWORD_TYPE  */
  YYSYMBOL_KEYWORD_CLASS_TYPE = 40,        /* KEYWORD_CLASS_TYPE  */
  YYSYMBOL_KEYWORD_CONST = 41,             /* KEYWORD_CONST  */
  YYSYMBOL_INC = 42,                       /* INC  */
  YYSYMBOL_DEC = 43,                       /* DEC  */
  YYSYMBOL_STRCAT = 44,                    /* STRCAT  */
  YYSYMBOL_STRSTR = 45,                    /* STRSTR  */
  YYSYMBOL_STRCHR = 46,                    /* STRCHR  */
  YYSYMBOL_STRCMP = 47,                    /* STRCMP  */
  YYSYMBOL_STRLEN = 48,                    /* STRLEN  */
  YYSYMBOL_STRCPY = 49,                    /* STRCPY  */
  YYSYMBOL_EVAL = 50,                      /* EVAL  */
  YYSYMBOL_51_ = 51,                       /* '&'  */
  YYSYMBOL_52_ = 52,                       /* '/'  */
  YYSYMBOL_53_ = 53,                       /* '.'  */
  YYSYMBOL_YYACCEPT = 54,                  /* $accept  */
  YYSYMBOL_start = 55,                     /* start  */
  YYSYMBOL_libraries = 56,                 /* libraries  */
  YYSYMBOL_library = 57,                   /* library  */
  YYSYMBOL_classes = 58,                   /* classes  */
  YYSYMBOL_class = 59,                     /* class  */
  YYSYMBOL_class_declarations = 60,        /* class_declarations  */
  YYSYMBOL_class_declaration = 61,         /* class_declaration  */
  YYSYMBOL_class_dec = 62,                 /* class_dec  */
  YYSYMBOL_dec = 63,                       /* dec  */
  YYSYMBOL_type = 64,                      /* type  */
  YYSYMBOL_class_functions = 65,           /* class_functions  */
  YYSYMBOL_class_function = 66,            /* class_function  */
  YYSYMBOL_function_parameters = 67,       /* function_parameters  */
  YYSYMBOL_function_parameter = 68,        /* function_parameter  */
  YYSYMBOL_function_call = 69,             /* function_call  */
  YYSYMBOL_ids = 70,                       /* ids  */
  YYSYMBOL_op = 71,                        /* op  */
  YYSYMBOL_function_declarations = 72,     /* function_declarations  */
  YYSYMBOL_function_declaration = 73,      /* function_declaration  */
  YYSYMBOL_return = 74,                    /* return  */
  YYSYMBOL_global = 75,                    /* global  */
  YYSYMBOL_global_function = 76,           /* global_function  */
  YYSYMBOL_program = 77,                   /* program  */
  YYSYMBOL_declarations = 78,              /* declarations  */
  YYSYMBOL_declaration = 79,               /* declaration  */
  YYSYMBOL_conditions = 80,                /* conditions  */
  YYSYMBOL_condition = 81,                 /* condition  */
  YYSYMBOL_arithmetic_operator = 82,       /* arithmetic_operator  */
  YYSYMBOL_logic_operator = 83,            /* logic_operator  */
  YYSYMBOL_content = 84,                   /* content  */
  YYSYMBOL_cond = 85,                      /* cond  */
  YYSYMBOL_instructions = 86,              /* instructions  */
  YYSYMBOL_instruction = 87,               /* instruction  */
  YYSYMBOL_string_function = 88,           /* string_function  */
  YYSYMBOL_expression = 89,                /* expression  */
  YYSYMBOL_array = 90,                     /* array  */
  YYSYMBOL_matrix = 91,                    /* matrix  */
  YYSYMBOL_matrix_elements = 92,           /* matrix_elements  */
  YYSYMBOL_expr = 93,                      /* expr  */
  YYSYMBOL_reading = 94,                   /* reading  */
  YYSYMBOL_elem_reading = 95,              /* elem_reading  */
  YYSYMBOL_printing = 96,                  /* printing  */
  YYSYMBOL_elem_printing = 97              /* elem_printing  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_int16 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if 1

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
# define YYCOPY_NEEDED 1
#endif /* 1 */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   906

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  417

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    18,    19,    20,     2,     2,    51,     2,
       9,    10,     8,     5,     3,     6,    53,    52,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     7,     4,
      15,    17,    16,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    13,     2,    14,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    11,     2,    12,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,    21,    22,
      23,    24,    25,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   297,   297,   300,   301,   304,   305,   308,   309,   312,
     313,   314,   317,   318,   321,   324,   325,   326,   329,   330,
     331,   332,   333,   334,   337,   340,   341,   344,   345,   346,
     347,   348,   351,   352,   355,   356,   357,   358,   359,   360,
     361,   362,   363,   366,   367,   370,   371,   372,   373,   376,
     377,   380,   381,   384,   385,   388,   391,   392,   393,   394,
     397,   398,   401,   404,   405,   408,   409,   410,   411,   412,
     413,   414,   415,   416,   419,   420,   421,   422,   423,   424,
     427,   428,   431,   432,   433,   434,   435,   436,   439,   440,
     441,   444,   445,   446,   447,   450,   451,   452,   453,   454,
     457,   458,   461,   462,   465,   466,   467,   468,   469,   470,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   491,   492,   495,   496,   499,
     500,   503,   504,   505,   506,   507,   508,   509,   510,   511,
     512,   513,   514,   515,   516,   517,   518,   519,   520,   521,
     524,   527,   528,   531,   534,   535
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if 1
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "','", "';'", "'+'",
  "'-'", "':'", "'*'", "'('", "')'", "'{'", "'}'", "'['", "']'", "'<'",
  "'>'", "'='", "'!'", "'\"'", "'#'", "KEYWORD_IF", "KEYWORD_WHILE",
  "KEYWORD_ELSE", "KEYWORD_FOR", "AND", "OR", "ASSIGN", "KEYWORD_CLASS",
  "MAIN", "GHI", "LIBRARY", "EQUAL", "KEYWORD_INCLUDE", "KEYWORD_RETURN",
  "READ", "WRITE", "NR", "ID", "KEYWORD_TYPE", "KEYWORD_CLASS_TYPE",
  "KEYWORD_CONST", "INC", "DEC", "STRCAT", "STRSTR", "STRCHR", "STRCMP",
  "STRLEN", "STRCPY", "EVAL", "'&'", "'/'", "'.'", "$accept", "start",
  "libraries", "library", "classes", "class", "class_declarations",
  "class_declaration", "class_dec", "dec", "type", "class_functions",
  "class_function", "function_parameters", "function_parameter",
  "function_call", "ids", "op", "function_declarations",
  "function_declaration", "return", "global", "global_function", "program",
  "declarations", "declaration", "conditions", "condition",
  "arithmetic_operator", "logic_operator", "content", "cond",
  "instructions", "instruction", "string_function", "expression", "array",
  "matrix", "matrix_elements", "expr", "reading", "elem_reading",
  "printing", "elem_printing", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,    44,    59,    43,    45,    58,    42,    40,
      41,   123,   125,    91,    93,    60,    62,    61,    33,    34,
      35,   258,   259,   260,   261,   262,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,    38,    47,    46
};
#endif

#define YYPACT_NINF (-251)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      23,    39,    18,     8,  -251,    59,  -251,    50,    55,  -251,
     211,  -251,    67,    98,   120,   151,   110,   129,   161,  -251,
     171,   229,  -251,  -251,   202,   205,   192,   234,   183,   207,
     287,  -251,  -251,  -251,   219,    24,  -251,   239,   -19,  -251,
    -251,  -251,  -251,   269,   216,  -251,   242,  -251,  -251,  -251,
      66,   268,   477,   477,   477,   477,   477,   246,  -251,    37,
    -251,   277,   301,   318,   320,   330,   332,  -251,  -251,  -251,
     314,    21,   285,    32,   270,    82,   313,   346,  -251,   325,
     359,   146,   299,   326,   365,  -251,     5,  -251,   383,   183,
    -251,    81,   267,   267,  -251,  -251,   298,   368,   251,   183,
     357,   361,   362,   364,   366,   367,   369,   384,   477,   477,
     477,   477,   393,   183,   379,   411,  -251,   122,  -251,  -251,
      -2,   315,   397,   826,  -251,   856,    83,   387,   108,  -251,
     388,   126,   322,  -251,   420,  -251,    92,  -251,   391,     0,
    -251,  -251,  -251,  -251,   166,   415,   421,    29,  -251,   428,
     429,   430,   438,   424,   441,   267,   267,  -251,  -251,  -251,
    -251,   406,   136,   435,   113,   433,  -251,  -251,   416,   447,
     448,   449,   450,   183,   432,   434,   443,   458,   496,  -251,
    -251,  -251,  -251,  -251,  -251,  -251,   446,   856,  -251,   436,
     157,   444,  -251,   461,    32,   478,   452,   453,   480,   185,
     479,  -251,   445,   353,  -251,   483,   251,    48,   460,   462,
     471,   472,  -251,   473,  -251,  -251,   826,   485,   474,   489,
    -251,   253,   253,   826,   349,  -251,  -251,   509,  -251,   524,
     501,   477,  -251,  -251,  -251,  -251,   515,  -251,  -251,  -251,
     499,   502,   189,   826,    44,   495,   826,   540,   525,   183,
    -251,  -251,   183,   228,  -251,   543,   544,   545,   546,   547,
     526,   531,  -251,   520,   337,  -251,  -251,  -251,   198,  -251,
     371,   197,   201,  -251,  -251,   556,  -251,   536,   528,   559,
     548,   549,   308,   115,  -251,  -251,   570,   586,   136,   573,
     616,   826,    64,     2,   569,  -251,  -251,  -251,  -251,  -251,
    -251,  -251,   550,  -251,   575,   578,   175,   477,   574,  -251,
     405,   337,  -251,   576,   579,   582,  -251,   477,   600,  -251,
    -251,   577,   585,   602,  -251,  -251,  -251,   580,   584,   826,
    -251,   243,  -251,   646,  -251,   563,   564,  -251,  -251,  -251,
     197,   826,   337,  -251,   608,  -251,  -251,  -251,   314,   826,
     615,   589,   826,   627,  -251,   676,   618,  -251,   633,  -251,
     477,   706,   634,  -251,   736,   605,   641,   766,   619,  -251,
     826,   183,    13,   342,  -251,  -251,  -251,   350,   643,   605,
    -251,   609,   796,  -251,   244,   640,   601,  -251,   431,   457,
     639,   621,   667,  -251,  -251,   183,  -251,   183,  -251,   477,
     314,   477,   314,   477,   351,   635,  -251,   262,   314,   314,
     314,  -251,  -251,   354,  -251,  -251,  -251
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     0,     1,     0,     0,     3,
       0,     8,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,    59,    58,     0,     0,     0,     0,     0,     0,
       0,   122,   113,   112,     0,     0,    24,     0,     0,    57,
      56,     5,     6,     0,     0,    13,     0,    50,    49,   125,
       0,     0,     0,     0,     0,     0,     0,     0,   136,   137,
     114,     0,     0,     0,     0,     0,     0,   115,   145,   138,
     110,     0,     0,     0,     0,     0,     0,     0,    41,     0,
       0,     0,     0,     0,     0,    12,     0,    26,     0,     0,
     111,     0,   141,   142,   144,   143,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    42,     0,    33,   116,
       0,     0,     0,     0,   121,     0,     0,     0,    14,    16,
       0,     0,     0,     9,     0,    25,     0,   126,     0,     0,
     135,   149,    48,    47,     0,     0,     0,   146,   147,     0,
       0,     0,     0,     0,     0,   131,   132,   134,   133,   123,
     124,     0,     0,     0,     0,     0,    34,    35,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    52,
      54,    53,    71,    72,    69,    70,     0,    62,    64,     0,
       0,     0,    15,     0,     0,    29,     0,     0,     0,     0,
       0,   117,     0,     0,    44,   139,     0,     0,     0,     0,
       0,     0,   104,     0,    40,    32,     0,     0,     0,     0,
      39,     0,     0,     0,     0,    55,   152,   150,   155,   153,
       0,     0,    61,    51,     2,    63,     0,    23,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    45,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,    36,     0,     0,    90,    88,    89,     0,    78,
       0,     0,     0,   103,   102,     0,   101,     0,     0,     0,
       0,     0,     0,     0,    17,    22,    31,     0,     0,     0,
       0,     0,     0,     0,     0,    43,   109,   106,   108,   107,
     105,    60,     0,    38,     0,     0,     0,     0,     0,    90,
       0,     0,    76,    86,    85,     0,    87,     0,     0,    66,
     100,     0,     0,     0,   151,   154,    73,     0,     0,     0,
      30,     0,    10,     0,   119,     0,     0,   140,    37,    79,
       0,     0,     0,    74,     0,    83,    82,    84,    80,     0,
       0,     0,     0,     0,    21,     0,     0,    11,     0,   118,
       0,     0,     0,    77,     0,     0,     0,     0,     0,    28,
       0,     0,     0,     0,    65,    75,    68,     0,     0,     0,
      67,     0,     0,   130,     0,     0,     0,    81,     0,     0,
       0,     0,     0,    20,    27,     0,   128,     0,   120,     0,
      98,     0,    99,     0,     0,     0,   129,     0,    96,    95,
      97,    94,    93,     0,   127,    91,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -251,  -251,  -251,   669,  -251,   664,  -251,   631,  -251,   551,
     -15,  -251,   590,  -128,   -26,   -24,   497,   -86,  -209,  -176,
    -202,  -251,   656,  -251,  -251,  -124,   456,  -250,   343,     1,
    -251,   307,  -163,  -246,  -119,   112,   440,  -251,   304,   -30,
    -251,  -251,  -251,  -251
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    10,    11,    44,    45,   128,   129,
      20,    86,    87,   117,   118,    68,   144,    49,   178,   179,
     180,    21,    22,   186,   187,   181,   268,   269,   317,   270,
     279,   378,   275,   276,    69,   183,    50,   372,   384,   271,
     184,   227,   185,   229
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      70,   188,   233,   137,   182,    89,   182,   260,   199,    77,
      80,    78,   164,   145,   305,    67,   385,   133,     6,    81,
     312,   273,    92,    93,    94,    95,    96,   160,     1,   320,
     112,    27,    72,    73,   287,   165,     7,   290,   207,   201,
      72,   115,   116,     1,    83,   134,    98,     8,   113,    78,
      99,    74,   202,   288,   336,    77,   100,    78,   254,   182,
     343,   344,    75,   235,   100,   386,   242,   130,   182,    89,
      75,   240,     5,   273,    12,    76,    90,   148,   155,   156,
     157,   158,   333,    76,   233,   142,   143,   225,    14,    13,
     101,    98,   362,    15,   138,   120,   189,   182,    24,   274,
      72,   115,   198,   334,   182,   195,   167,    78,   139,   121,
     190,   233,    78,   130,   233,   320,   335,   130,   320,    28,
     355,   320,    23,    29,   182,   162,   217,   182,   327,    25,
      75,    26,   163,    40,    72,   194,   215,    30,    78,   273,
     218,   182,   328,    76,    72,   115,   126,   273,    31,    18,
     273,   274,    32,    33,    72,    73,   182,   233,    27,   273,
     331,   382,   273,    34,    75,   273,   294,    35,   182,   203,
      78,   182,   182,    74,    75,   239,   204,    76,   361,   233,
     108,   109,   110,   111,    75,   140,   364,    76,   162,   367,
     313,   314,   162,   315,   237,   247,   238,    76,    18,   286,
      36,   282,   108,   109,   110,   111,   233,   316,   308,    37,
     182,   318,   313,   314,   182,   315,   309,   274,    41,   309,
      47,    48,   182,   266,   267,   274,   266,   267,   274,   316,
     182,   203,    43,   182,   306,    42,   182,   274,   295,     7,
     274,    46,   182,   274,    51,   182,   162,   395,   182,    16,
      17,   182,    18,   356,   396,    83,    84,    71,    52,    53,
      54,    55,   264,   182,    78,   395,    79,    16,    38,   310,
      18,   265,   414,   310,   110,   111,    82,   340,   266,   267,
      88,   306,    91,    57,    97,   383,   102,   348,   142,   143,
      58,    59,    52,    53,    54,    55,    56,    61,    62,    63,
      64,    65,    66,   108,   109,   110,   111,   119,   140,   406,
     103,   383,   306,   108,   109,   110,   111,    57,   326,   108,
     109,   110,   111,   114,    58,    59,    60,   104,    18,   105,
     373,    61,    62,    63,    64,    65,    66,   126,   127,   106,
      18,   107,    52,    53,    54,    55,    56,   108,   109,   110,
     111,   122,   387,   146,   166,   304,    18,   123,   400,   402,
     126,   196,   124,    18,   131,   388,   389,    57,   390,   408,
     125,   409,   132,   410,    58,    59,    52,    53,    54,    55,
     311,    61,    62,    63,    64,    65,    66,   277,   278,   304,
     250,   251,   136,   411,   412,   146,   415,   416,   141,   147,
     149,    57,   150,   159,   151,   152,   161,   153,    58,    59,
      52,    53,    54,    55,   342,    61,    62,    63,    64,    65,
      66,   116,   154,   304,   168,   191,   193,   197,   200,   205,
     206,   208,   209,   210,   212,    57,    52,    53,    54,    55,
      56,   211,    58,    59,   213,   214,   216,   219,   399,    61,
      62,    63,    64,    65,    66,   220,   221,   222,   234,   224,
     223,    57,    52,    53,    54,    55,    56,   231,    58,    59,
     226,   240,   228,   236,   401,    61,    62,    63,    64,    65,
      66,   230,    52,    53,    54,    55,    56,    57,   241,   243,
     244,   246,   245,   248,    58,    59,   252,   249,   255,   261,
     256,    61,    62,    63,    64,    65,    66,    57,   232,   257,
     258,   259,   280,   262,    58,    59,   263,   169,   170,   171,
     172,    61,    62,    63,    64,    65,    66,   281,    74,   283,
     173,   174,   175,   289,    16,   176,   284,    18,   301,   285,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,   291,   292,   296,   297,   298,   299,   300,   302,   303,
     173,   174,   175,   321,    16,   176,   322,    18,   319,   323,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,   329,   288,   337,   307,   341,   324,   325,   339,   338,
     173,   174,   175,   345,    16,   176,   346,    18,   330,   347,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,   349,   351,   352,   350,   358,   359,   353,   363,   365,
     173,   174,   175,   354,    16,   176,   366,    18,   332,   370,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,   368,   371,   377,   375,   379,   381,   391,   393,   397,
     173,   174,   175,   398,    16,   176,   403,    18,   357,   404,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,   405,     9,   413,    19,    85,   135,    39,   272,   192,
     173,   174,   175,   360,    16,   176,   392,    18,   369,   293,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,   407,     0,   253,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,    16,   176,     0,    18,   374,     0,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,    16,   176,     0,    18,   376,     0,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,    16,   176,     0,    18,   380,     0,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,    16,   176,     0,    18,   394,     0,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,    16,   176,     0,    18,     0,     0,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     173,   174,   175,     0,    16,   176,     0,    18,     0,     0,
      61,    62,    63,    64,    65,    66,   177,   169,   170,   171,
     172,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,   175,     0,    16,   176,     0,    18,     0,     0,
      61,    62,    63,    64,    65,    66,   177
};

static const yytype_int16 yycheck[] =
{
      30,   125,   178,    89,   123,     3,   125,   216,   136,    35,
      29,    35,    14,    99,   264,    30,     3,    12,     0,    38,
     270,   223,    52,    53,    54,    55,    56,   113,    20,   275,
       9,     7,     8,     9,   243,    37,    28,   246,     9,    39,
       8,     9,    10,    20,    39,    40,     9,    39,    27,    73,
      13,    27,    52,     9,    52,    81,    27,    81,    10,   178,
     310,   311,    38,   187,    27,    52,   194,    82,   187,     3,
      38,    27,    33,   275,    15,    51,    10,   101,   108,   109,
     110,   111,   291,    51,   260,    37,    38,   173,    38,    30,
      53,     9,   342,    38,    13,    13,    13,   216,    31,   223,
       8,     9,    10,    39,   223,   131,   121,   131,    27,    27,
      27,   287,   136,   128,   290,   361,    52,   132,   364,     9,
     329,   367,    10,    13,   243,     3,    13,   246,    13,    31,
      38,    11,    10,    21,     8,     9,   162,    27,   162,   341,
      27,   260,    27,    51,     8,     9,    38,   349,    38,    41,
     352,   275,    42,    43,     8,     9,   275,   333,     7,   361,
     288,   370,   364,    53,    38,   367,   252,    38,   287,     3,
     194,   290,   291,    27,    38,   190,    10,    51,   341,   355,
       5,     6,     7,     8,    38,    10,   349,    51,     3,   352,
      15,    16,     3,    18,    37,    10,    39,    51,    41,    10,
      39,   231,     5,     6,     7,     8,   382,    32,    10,    38,
     329,    10,    15,    16,   333,    18,    18,   341,    16,    18,
      37,    38,   341,    25,    26,   349,    25,    26,   352,    32,
     349,     3,    40,   352,   264,    30,   355,   361,    10,    28,
     364,     7,   361,   367,    37,   364,     3,     3,   367,    38,
      39,   370,    41,    10,    10,    39,    40,    38,     5,     6,
       7,     8,     9,   382,   288,     3,    27,    38,    39,   268,
      41,    18,    10,   272,     7,     8,     7,   307,    25,    26,
      38,   311,    14,    30,    38,   371,     9,   317,    37,    38,
      37,    38,     5,     6,     7,     8,     9,    44,    45,    46,
      47,    48,    49,     5,     6,     7,     8,    37,    10,   395,
       9,   397,   342,     5,     6,     7,     8,    30,    10,     5,
       6,     7,     8,    38,    37,    38,    39,     9,    41,     9,
     360,    44,    45,    46,    47,    48,    49,    38,    39,     9,
      41,     9,     5,     6,     7,     8,     9,     5,     6,     7,
       8,    38,    10,    38,    39,    18,    41,    11,   388,   389,
      38,    39,    37,    41,    38,    15,    16,    30,    18,   399,
      11,   401,     7,   403,    37,    38,     5,     6,     7,     8,
       9,    44,    45,    46,    47,    48,    49,    38,    39,    18,
      37,    38,     9,    42,    43,    38,    42,    43,    30,    38,
      38,    30,    38,    10,    38,    38,    27,    38,    37,    38,
       5,     6,     7,     8,     9,    44,    45,    46,    47,    48,
      49,    10,    38,    18,    27,    38,    38,     7,    37,    14,
       9,     3,     3,     3,    10,    30,     5,     6,     7,     8,
       9,     3,    37,    38,     3,    39,    11,    14,    17,    44,
      45,    46,    47,    48,    49,    39,     9,     9,    12,     9,
      11,    30,     5,     6,     7,     8,     9,     9,    37,    38,
      38,    27,    38,    37,    17,    44,    45,    46,    47,    48,
      49,    38,     5,     6,     7,     8,     9,    30,    27,    11,
      38,    11,    39,    14,    37,    38,    13,    52,    38,    14,
      38,    44,    45,    46,    47,    48,    49,    30,    12,    38,
      38,    38,     3,    39,    37,    38,    27,    21,    22,    23,
      24,    44,    45,    46,    47,    48,    49,     3,    27,    14,
      34,    35,    36,    38,    38,    39,    37,    41,    12,    37,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    11,    27,    10,    10,    10,    10,    10,    27,    39,
      34,    35,    36,    27,    38,    39,    38,    41,    12,    10,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    11,     9,    14,     9,    11,    38,    38,    10,    39,
      34,    35,    36,    17,    38,    39,    17,    41,    12,    17,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    11,    27,    11,    37,    52,    52,    37,    10,     4,
      34,    35,    36,    39,    38,    39,    37,    41,    12,    11,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    14,     9,    38,    10,     4,    27,     4,    39,     9,
      34,    35,    36,    52,    38,    39,    17,    41,    12,    38,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,     4,     3,    38,    10,    44,    86,    21,   222,   128,
      34,    35,    36,   340,    38,    39,   379,    41,    12,   249,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,   397,    -1,   206,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    12,    -1,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    12,    -1,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    12,    -1,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    12,    -1,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    -1,    38,    39,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50,    21,    22,    23,
      24,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    35,    36,    -1,    38,    39,    -1,    41,    -1,    -1,
      44,    45,    46,    47,    48,    49,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    20,    55,    56,    57,    33,     0,    28,    39,    57,
      58,    59,    15,    30,    38,    38,    38,    39,    41,    59,
      64,    75,    76,    89,    31,    31,    11,     7,     9,    13,
      27,    38,    42,    43,    53,    38,    39,    38,    39,    76,
      89,    16,    30,    40,    60,    61,     7,    37,    38,    71,
      90,    37,     5,     6,     7,     8,     9,    30,    37,    38,
      39,    44,    45,    46,    47,    48,    49,    64,    69,    88,
      93,    38,     8,     9,    27,    38,    51,    68,    69,    27,
      29,    38,     7,    39,    40,    61,    65,    66,    38,     3,
      10,    14,    93,    93,    93,    93,    93,    38,     9,    13,
      27,    53,     9,     9,     9,     9,     9,     9,     5,     6,
       7,     8,     9,    27,    38,     9,    10,    67,    68,    37,
      13,    27,    38,    11,    37,    11,    38,    39,    62,    63,
      64,    38,     7,    12,    40,    66,     9,    71,    13,    27,
      10,    30,    37,    38,    70,    71,    38,    38,    69,    38,
      38,    38,    38,    38,    38,    93,    93,    93,    93,    10,
      71,    27,     3,    10,    14,    37,    39,    64,    27,    21,
      22,    23,    24,    34,    35,    36,    39,    50,    72,    73,
      74,    79,    88,    89,    94,    96,    77,    78,    79,    13,
      27,    38,    63,    38,     9,    68,    39,     7,    10,    67,
      37,    39,    52,     3,    10,    14,     9,     9,     3,     3,
       3,     3,    10,     3,    39,    68,    11,    13,    27,    14,
      39,     9,     9,    11,     9,    71,    38,    95,    38,    97,
      38,     9,    12,    73,    12,    79,    37,    37,    39,    64,
      27,    27,    67,    11,    38,    39,    11,    10,    14,    52,
      37,    38,    13,    70,    10,    38,    38,    38,    38,    38,
      72,    14,    39,    27,     9,    18,    25,    26,    80,    81,
      83,    93,    80,    74,    79,    86,    87,    38,    39,    84,
       3,     3,    93,    14,    37,    37,    10,    72,     9,    38,
      72,    11,    27,    90,    71,    10,    10,    10,    10,    10,
      10,    12,    27,    39,    18,    81,    93,     9,    10,    18,
      83,     9,    81,    15,    16,    18,    32,    82,    10,    12,
      87,    27,    38,    10,    38,    38,    10,    13,    27,    11,
      12,    67,    12,    72,    39,    52,    52,    14,    39,    10,
      93,    11,     9,    81,    81,    17,    17,    17,    93,    11,
      37,    27,    11,    37,    39,    72,    10,    12,    52,    52,
      82,    86,    81,    10,    86,     4,    37,    86,    14,    12,
      11,     9,    91,    93,    12,    10,    12,    38,    85,     4,
      12,    27,    72,    71,    92,     3,    52,    10,    15,    16,
      18,     4,    85,    39,    12,     3,    10,     9,    52,    17,
      93,    17,    93,    17,    38,     4,    71,    92,    93,    93,
      93,    42,    43,    38,    10,    42,    43
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    54,    55,    56,    56,    57,    57,    58,    58,    59,
      59,    59,    60,    60,    61,    62,    62,    62,    63,    63,
      63,    63,    63,    63,    64,    65,    65,    66,    66,    66,
      66,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    68,    69,    69,    70,    70,    70,    70,    71,
      71,    72,    72,    73,    73,    74,    75,    75,    75,    75,
      76,    76,    77,    78,    78,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    80,    80,    80,    80,    80,    80,
      81,    81,    82,    82,    82,    82,    82,    82,    83,    83,
      83,    84,    84,    84,    84,    85,    85,    85,    85,    85,
      86,    86,    87,    87,    88,    88,    88,    88,    88,    88,
      89,    89,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    90,    90,    91,    91,    92,
      92,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      93,    93,    93,    93,    93,    93,    93,    93,    93,    93,
      94,    95,    95,    96,    97,    97
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     8,     2,     1,     5,     5,     2,     1,     6,
      10,    11,     2,     1,     3,     2,     1,     4,     3,     3,
       9,     6,     4,     3,     2,     2,     1,    10,     8,     3,
       6,     5,     3,     1,     3,     3,     5,     7,     6,     4,
       4,     1,     2,     6,     4,     3,     3,     1,     1,     1,
       1,     2,     1,     1,     1,     2,     2,     2,     1,     1,
       8,     6,     1,     2,     1,     7,     4,     7,     7,     1,
       1,     1,     1,     4,     3,     5,     2,     4,     1,     3,
       3,     6,     2,     2,     2,     1,     1,     1,     1,     1,
       1,     9,     9,     8,     8,     4,     4,     4,     3,     3,
       2,     1,     1,     1,     4,     6,     6,     6,     6,     6,
       3,     4,     2,     2,     3,     3,     4,     6,    10,     9,
      13,     4,     2,     5,     5,     1,     3,     5,     3,     3,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     4,
       7,     2,     2,     2,     2,     1,     3,     3,     5,     3,
       2,     3,     1,     2,     3,     1
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        YY_LAC_DISCARD ("YYBACKUP");                              \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
# ifndef YY_LOCATION_PRINT
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yykind < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yykind], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


/* Given a state stack such that *YYBOTTOM is its bottom, such that
   *YYTOP is either its top or is YYTOP_EMPTY to indicate an empty
   stack, and such that *YYCAPACITY is the maximum number of elements it
   can hold without a reallocation, make sure there is enough room to
   store YYADD more elements.  If not, allocate a new stack using
   YYSTACK_ALLOC, copy the existing elements, and adjust *YYBOTTOM,
   *YYTOP, and *YYCAPACITY to reflect the new capacity and memory
   location.  If *YYBOTTOM != YYBOTTOM_NO_FREE, then free the old stack
   using YYSTACK_FREE.  Return 0 if successful or if no reallocation is
   required.  Return YYENOMEM if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYPTRDIFF_T *yycapacity, YYPTRDIFF_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yy_state_t **yybottom,
                      yy_state_t *yybottom_no_free,
                      yy_state_t **yytop, yy_state_t *yytop_empty)
{
  YYPTRDIFF_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYPTRDIFF_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYPTRDIFF_T yyalloc = 2 * yysize_new;
      yy_state_t *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        YY_CAST (yy_state_t *,
                 YYSTACK_ALLOC (YY_CAST (YYSIZE_T,
                                         yyalloc * YYSIZEOF (*yybottom_new))));
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return YYENOMEM;
        }
      if (*yytop != yytop_empty)
        {
          YYCOPY (yybottom_new, *yybottom, yysize_old);
          *yytop = yybottom_new + (yysize_old - 1);
        }
      if (*yybottom != yybottom_no_free)
        YYSTACK_FREE (*yybottom);
      *yybottom = yybottom_new;
      *yycapacity = yyalloc;
    }
  return 0;
}

/* Establish the initial context for the current lookahead if no initial
   context is currently established.

   We define a context as a snapshot of the parser stacks.  We define
   the initial context for a lookahead as the context in which the
   parser initially examines that lookahead in order to select a
   syntactic action.  Thus, if the lookahead eventually proves
   syntactically unacceptable (possibly in a later context reached via a
   series of reductions), the initial context can be used to determine
   the exact set of tokens that would be syntactically acceptable in the
   lookahead's place.  Moreover, it is the context after which any
   further semantic actions would be erroneous because they would be
   determined by a syntactically unacceptable token.

   YY_LAC_ESTABLISH should be invoked when a reduction is about to be
   performed in an inconsistent state (which, for the purposes of LAC,
   includes consistent states that don't know they're consistent because
   their default reductions have been disabled).  Iff there is a
   lookahead token, it should also be invoked before reporting a syntax
   error.  This latter case is for the sake of the debugging output.

   For parse.lac=full, the implementation of YY_LAC_ESTABLISH is as
   follows.  If no initial context is currently established for the
   current lookahead, then check if that lookahead can eventually be
   shifted if syntactic actions continue from the current context.
   Report a syntax error if it cannot.  */
#define YY_LAC_ESTABLISH                                                \
do {                                                                    \
  if (!yy_lac_established)                                              \
    {                                                                   \
      YYDPRINTF ((stderr,                                               \
                  "LAC: initial context established for %s\n",          \
                  yysymbol_name (yytoken)));                            \
      yy_lac_established = 1;                                           \
      switch (yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken))    \
        {                                                               \
        case YYENOMEM:                                                  \
          goto yyexhaustedlab;                                          \
        case 1:                                                         \
          goto yyerrlab;                                                \
        }                                                               \
    }                                                                   \
} while (0)

/* Discard any previous initial lookahead context because of Event,
   which may be a lookahead change or an invalidation of the currently
   established initial context for the current lookahead.

   The most common example of a lookahead change is a shift.  An example
   of both cases is syntax error recovery.  That is, a syntax error
   occurs when the lookahead is syntactically erroneous for the
   currently established initial context, so error recovery manipulates
   the parser stacks to try to find a new initial context in which the
   current lookahead is syntactically acceptable.  If it fails to find
   such a context, it discards the lookahead.  */
#if YYDEBUG
# define YY_LAC_DISCARD(Event)                                           \
do {                                                                     \
  if (yy_lac_established)                                                \
    {                                                                    \
      YYDPRINTF ((stderr, "LAC: initial context discarded due to "       \
                  Event "\n"));                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return YYENOMEM if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, yysymbol_kind_t yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  /* Reduce until we encounter a shift and thereby accept the token.  */
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yysymbol_name (yytoken)));
  if (yytoken == YYSYMBOL_YYUNDEF)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[+*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          /* Use the default action.  */
          yyrule = yydefact[+*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
          /* Use the action from yytable.  */
          yyrule = yytable[yyrule];
          if (yytable_value_is_error (yyrule))
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
          if (0 < yyrule)
            {
              YYDPRINTF ((stderr, " S%d\n", yyrule));
              return 0;
            }
          yyrule = -yyrule;
        }
      /* By now we know we have to simulate a reduce.  */
      YYDPRINTF ((stderr, " R%d", yyrule - 1));
      {
        /* Pop the corresponding number of values from the stack.  */
        YYPTRDIFF_T yylen = yyr2[yyrule];
        /* First pop from the LAC stack as many tokens as possible.  */
        if (yyesp != yyes_prev)
          {
            YYPTRDIFF_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yyesp = yyes_prev;
                yylen -= yysize;
              }
          }
        /* Only afterwards look at the main stack.  */
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      /* Push the resulting state of the reduction.  */
      {
        yy_state_fast_t yystate;
        {
          const int yylhs = yyr1[yyrule] - YYNTOKENS;
          const int yyi = yypgoto[yylhs] + *yyesp;
          yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyesp
                     ? yytable[yyi]
                     : yydefgoto[yylhs]);
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            YY_IGNORE_USELESS_CAST_BEGIN
            *yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        else
          {
            if (yy_lac_stack_realloc (yyes_capacity, 1,
#if YYDEBUG
                                      " (", ")",
#endif
                                      yyes, yyesa, &yyesp, yyes_prev))
              {
                YYDPRINTF ((stderr, "\n"));
                return YYENOMEM;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}

/* Context of a parse error.  */
typedef struct
{
  yy_state_t *yyssp;
  yy_state_t *yyesa;
  yy_state_t **yyes;
  YYPTRDIFF_T *yyes_capacity;
  yysymbol_kind_t yytoken;
} yypcontext_t;

/* Put in YYARG at most YYARGN of the expected tokens given the
   current YYCTX, and return the number of tokens stored in YYARG.  If
   YYARG is null, return the number of expected tokens (guaranteed to
   be less than YYNTOKENS).  Return YYENOMEM on memory exhaustion.
   Return 0 if there are more than YYARGN expected tokens, yet fill
   YYARG up to YYARGN. */
static int
yypcontext_expected_tokens (const yypcontext_t *yyctx,
                            yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;

  int yyx;
  for (yyx = 0; yyx < YYNTOKENS; ++yyx)
    {
      yysymbol_kind_t yysym = YY_CAST (yysymbol_kind_t, yyx);
      if (yysym != YYSYMBOL_YYerror && yysym != YYSYMBOL_YYUNDEF)
        switch (yy_lac (yyctx->yyesa, yyctx->yyes, yyctx->yyes_capacity, yyctx->yyssp, yysym))
          {
          case YYENOMEM:
            return YYENOMEM;
          case 1:
            continue;
          default:
            if (!yyarg)
              ++yycount;
            else if (yycount == yyargn)
              return 0;
            else
              yyarg[yycount++] = yysym;
          }
    }
  if (yyarg && yycount == 0 && 0 < yyargn)
    yyarg[0] = YYSYMBOL_YYEMPTY;
  return yycount;
}




#ifndef yystrlen
# if defined __GLIBC__ && defined _STRING_H
#  define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
# else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
# endif
#endif

#ifndef yystpcpy
# if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#  define yystpcpy stpcpy
# else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
# endif
#endif

#ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;
      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
#endif


static int
yy_syntax_error_arguments (const yypcontext_t *yyctx,
                           yysymbol_kind_t yyarg[], int yyargn)
{
  /* Actual size of YYARG. */
  int yycount = 0;
  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
       In the first two cases, it might appear that the current syntax
       error should have been detected in the previous state when yy_lac
       was invoked.  However, at that time, there might have been a
       different syntax error that discarded a different initial context
       during error recovery, leaving behind the current lookahead.
  */
  if (yyctx->yytoken != YYSYMBOL_YYEMPTY)
    {
      int yyn;
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      if (yyarg)
        yyarg[yycount] = yyctx->yytoken;
      ++yycount;
      yyn = yypcontext_expected_tokens (yyctx,
                                        yyarg ? yyarg + 1 : yyarg, yyargn - 1);
      if (yyn == YYENOMEM)
        return YYENOMEM;
      else if (yyn == 0)
        YYDPRINTF ((stderr, "No expected tokens.\n"));
      else
        yycount += yyn;
    }
  return yycount;
}

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return -1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return YYENOMEM if the
   required number of bytes is too large to store or if
   yy_lac returned YYENOMEM.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                const yypcontext_t *yyctx)
{
  enum { YYARGS_MAX = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  yysymbol_kind_t yyarg[YYARGS_MAX];
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* Actual size of YYARG. */
  int yycount = yy_syntax_error_arguments (yyctx, yyarg, YYARGS_MAX);
  if (yycount == YYENOMEM)
    return YYENOMEM;

  switch (yycount)
    {
#define YYCASE_(N, S)                       \
      case N:                               \
        yyformat = S;                       \
        break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
    }

  /* Compute error message size.  Don't count the "%s"s, but reserve
     room for the terminator.  */
  yysize = yystrlen (yyformat) - 2 * yycount + 1;
  {
    int yyi;
    for (yyi = 0; yyi < yycount; ++yyi)
      {
        YYPTRDIFF_T yysize1
          = yysize + yytnamerr (YY_NULLPTR, yytname[yyarg[yyi]]);
        if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
          yysize = yysize1;
        else
          return YYENOMEM;
      }
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return -1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yytname[yyarg[yyi++]]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}


/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    yy_state_t yyesa[20];
    yy_state_t *yyes = yyesa;
    YYPTRDIFF_T yyes_capacity = 20 < YYMAXDEPTH ? 20 : YYMAXDEPTH;

  /* Whether LAC context is established.  A Boolean.  */
  int yy_lac_established = 0;
  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    {
      YY_LAC_ESTABLISH;
      goto yydefault;
    }
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      YY_LAC_ESTABLISH;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  {
    int yychar_backup = yychar;
    switch (yyn)
      {
  case 2: /* start: libraries classes global KEYWORD_TYPE MAIN '{' program '}'  */
#line 297 "lexer.y"
                                                                 {printf("The program is accepted\n");}
#line 2364 "lexer.tab.c"
    break;

  case 9: /* class: KEYWORD_CLASS ID '{' class_declarations class_functions '}'  */
#line 312 "lexer.y"
                                                                        {PrintFunct("Class Methods");}
#line 2370 "lexer.tab.c"
    break;

  case 12: /* class_declarations: class_declarations class_declaration  */
#line 317 "lexer.y"
                                                                        {PrintVar("Class");}
#line 2376 "lexer.tab.c"
    break;

  case 17: /* class_dec: KEYWORD_TYPE ID ASSIGN NR  */
#line 326 "lexer.y"
                                    {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "NOPE");}
#line 2382 "lexer.tab.c"
    break;

  case 18: /* dec: ID ASSIGN KEYWORD_TYPE  */
#line 329 "lexer.y"
                                                {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"NOPE");}
#line 2388 "lexer.tab.c"
    break;

  case 19: /* dec: ID ASSIGN type  */
#line 330 "lexer.y"
                                                {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"YES");}
#line 2394 "lexer.tab.c"
    break;

  case 20: /* dec: ID '[' NR ']' '[' NR ']' ASSIGN KEYWORD_TYPE  */
#line 331 "lexer.y"
                                                { var_declaring_without_init((yyvsp[-8].str),(yyvsp[0].str),"NOPE");}
#line 2400 "lexer.tab.c"
    break;

  case 21: /* dec: ID '[' NR ']' ASSIGN KEYWORD_TYPE  */
#line 332 "lexer.y"
                                                { var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");}
#line 2406 "lexer.tab.c"
    break;

  case 22: /* dec: type ID ASSIGN NR  */
#line 333 "lexer.y"
                                                {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "YES");}
#line 2412 "lexer.tab.c"
    break;

  case 23: /* dec: ID ASSIGN NR  */
#line 334 "lexer.y"
                                                {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2418 "lexer.tab.c"
    break;

  case 24: /* type: KEYWORD_CONST KEYWORD_TYPE  */
#line 337 "lexer.y"
                                                {strcat((yyvsp[-1].str)," ");strcat((yyvsp[-1].str),(yyvsp[0].str));(yyval.str)=(yyvsp[-1].str);}
#line 2424 "lexer.tab.c"
    break;

  case 27: /* class_function: KEYWORD_CLASS_TYPE ':' KEYWORD_TYPE ID '(' function_parameters ')' '{' function_declarations '}'  */
#line 344 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2430 "lexer.tab.c"
    break;

  case 28: /* class_function: KEYWORD_TYPE ID '(' function_parameters ')' '{' function_declarations '}'  */
#line 345 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2436 "lexer.tab.c"
    break;

  case 29: /* class_function: KEYWORD_TYPE ID function_parameter  */
#line 346 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-2].str),(yyvsp[-1].str),(yyvsp[0].str));}
#line 2442 "lexer.tab.c"
    break;

  case 30: /* class_function: KEYWORD_TYPE ID function_parameter '{' function_declarations '}'  */
#line 347 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-5].str),(yyvsp[-4].str),(yyvsp[-3].str));PrintVar("the function");}
#line 2448 "lexer.tab.c"
    break;

  case 31: /* class_function: KEYWORD_TYPE ID '(' function_parameters ')'  */
#line 348 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str));}
#line 2454 "lexer.tab.c"
    break;

  case 32: /* function_parameters: function_parameters ',' function_parameter  */
#line 351 "lexer.y"
                                                                    {strcat((yyvsp[0].str),";");strcat((yyvsp[0].str),(yyvsp[-2].str));(yyval.str)=(yyvsp[0].str);}
#line 2460 "lexer.tab.c"
    break;

  case 33: /* function_parameters: function_parameter  */
#line 352 "lexer.y"
                                                                    {strcat((yyvsp[0].str),";");}
#line 2466 "lexer.tab.c"
    break;

  case 34: /* function_parameter: ID ASSIGN KEYWORD_TYPE  */
#line 355 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2472 "lexer.tab.c"
    break;

  case 35: /* function_parameter: ID ASSIGN type  */
#line 356 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"YES");(yyval.str)=(yyvsp[0].str);}
#line 2478 "lexer.tab.c"
    break;

  case 36: /* function_parameter: ID '[' ']' ASSIGN KEYWORD_TYPE  */
#line 357 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-4].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2484 "lexer.tab.c"
    break;

  case 37: /* function_parameter: ID '[' ']' '[' ']' ASSIGN KEYWORD_TYPE  */
#line 358 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-6].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2490 "lexer.tab.c"
    break;

  case 38: /* function_parameter: ID '[' NR ']' ASSIGN KEYWORD_TYPE  */
#line 359 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2496 "lexer.tab.c"
    break;

  case 39: /* function_parameter: '&' ID ASSIGN KEYWORD_TYPE  */
#line 360 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2502 "lexer.tab.c"
    break;

  case 40: /* function_parameter: '*' ID ASSIGN KEYWORD_TYPE  */
#line 361 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2508 "lexer.tab.c"
    break;

  case 41: /* function_parameter: function_call  */
#line 362 "lexer.y"
                                                                     {(yyval.str)=0;}
#line 2514 "lexer.tab.c"
    break;

  case 42: /* function_parameter: '(' ')'  */
#line 363 "lexer.y"
                                                                    {(yyval.str)=0;}
#line 2520 "lexer.tab.c"
    break;

  case 43: /* function_call: ID ASSIGN ID '(' ids ')'  */
#line 366 "lexer.y"
                                                                     {var_verification((yyvsp[-5].str)); identify_function((yyvsp[-3].str),(yyvsp[-1].str));}
#line 2526 "lexer.tab.c"
    break;

  case 44: /* function_call: ID '(' ids ')'  */
#line 367 "lexer.y"
                                                                   {identify_function((yyvsp[-3].str),(yyvsp[-1].str));}
#line 2532 "lexer.tab.c"
    break;

  case 45: /* ids: ids ',' ID  */
#line 370 "lexer.y"
                                                              {strcat((yyvsp[0].str),";");strcat((yyvsp[0].str),(yyvsp[-2].str));(yyval.str)=(yyvsp[0].str);}
#line 2538 "lexer.tab.c"
    break;

  case 46: /* ids: ids ',' NR  */
#line 371 "lexer.y"
                                                               {(yyval.str)=strdup("int;");strcat((yyval.str),(yyvsp[-2].str));}
#line 2544 "lexer.tab.c"
    break;

  case 47: /* ids: ID  */
#line 372 "lexer.y"
                                                                  {strcat((yyvsp[0].str),";");(yyval.str)=(yyvsp[0].str);}
#line 2550 "lexer.tab.c"
    break;

  case 48: /* ids: NR  */
#line 373 "lexer.y"
                                                                  {(yyval.str)=strdup("int;");}
#line 2556 "lexer.tab.c"
    break;

  case 49: /* op: ID  */
#line 376 "lexer.y"
                                                                    {var_verification((yyvsp[0].str));}
#line 2562 "lexer.tab.c"
    break;

  case 56: /* global: global expression  */
#line 391 "lexer.y"
                                                {PrintVar("global");}
#line 2568 "lexer.tab.c"
    break;

  case 57: /* global: global global_function  */
#line 392 "lexer.y"
                                                {PrintFunct("global");}
#line 2574 "lexer.tab.c"
    break;

  case 60: /* global_function: KEYWORD_TYPE ID '(' function_parameters ')' '{' function_declarations '}'  */
#line 397 "lexer.y"
                                                                                          {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2580 "lexer.tab.c"
    break;

  case 61: /* global_function: KEYWORD_TYPE ID function_parameter '{' function_declarations '}'  */
#line 398 "lexer.y"
                                                                                          {declaring_function((yyvsp[-5].str),(yyvsp[-4].str),(yyvsp[-3].str));PrintVar("the function");}
#line 2586 "lexer.tab.c"
    break;

  case 62: /* program: declarations  */
#line 401 "lexer.y"
                                                    {PrintVar("main");show_exp();}
#line 2592 "lexer.tab.c"
    break;

  case 73: /* declaration: EVAL '(' expr ')'  */
#line 416 "lexer.y"
                                                    {add_arg((yyvsp[-1].nr));}
#line 2598 "lexer.tab.c"
    break;

  case 91: /* content: KEYWORD_TYPE ID ASSIGN NR ';' cond ';' ID INC  */
#line 444 "lexer.y"
                                                                {var_declaring((yyvsp[-7].str),(yyvsp[-8].str),(yyvsp[-5].nr),"NOPE");var_verification((yyvsp[-7].str));}
#line 2604 "lexer.tab.c"
    break;

  case 92: /* content: KEYWORD_TYPE ID ASSIGN NR ';' cond ';' ID DEC  */
#line 445 "lexer.y"
                                                                {var_declaring((yyvsp[-7].str),(yyvsp[-8].str),(yyvsp[-5].nr),"NOPE");var_verification((yyvsp[-7].str));}
#line 2610 "lexer.tab.c"
    break;

  case 93: /* content: ID ASSIGN NR ';' cond ';' ID DEC  */
#line 446 "lexer.y"
                                                                {var_verification((yyvsp[-7].str));var_verification((yyvsp[-1].str));}
#line 2616 "lexer.tab.c"
    break;

  case 94: /* content: ID ASSIGN NR ';' cond ';' ID INC  */
#line 447 "lexer.y"
                                                                {var_verification((yyvsp[-7].str));var_verification((yyvsp[-1].str));}
#line 2622 "lexer.tab.c"
    break;

  case 95: /* cond: ID '>' '=' expr  */
#line 450 "lexer.y"
                                                    {var_verification((yyvsp[-3].str));Assign((yyvsp[-3].str),(yyvsp[0].nr) + 1); }
#line 2628 "lexer.tab.c"
    break;

  case 96: /* cond: ID '<' '=' expr  */
#line 451 "lexer.y"
                                                    {var_verification((yyvsp[-3].str));Assign((yyvsp[-3].str),(yyvsp[0].nr) + 1);}
#line 2634 "lexer.tab.c"
    break;

  case 97: /* cond: ID '!' '=' expr  */
#line 452 "lexer.y"
                                                    {var_verification((yyvsp[-3].str));Assign((yyvsp[-3].str), (yyvsp[0].nr));}
#line 2640 "lexer.tab.c"
    break;

  case 98: /* cond: ID '<' expr  */
#line 453 "lexer.y"
                                                    {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2646 "lexer.tab.c"
    break;

  case 99: /* cond: ID '>' expr  */
#line 454 "lexer.y"
                                                    {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2652 "lexer.tab.c"
    break;

  case 104: /* string_function: STRLEN '(' ID ')'  */
#line 465 "lexer.y"
                                                     {var_verification((yyvsp[-1].str));}
#line 2658 "lexer.tab.c"
    break;

  case 105: /* string_function: STRCPY '(' ID ',' ID ')'  */
#line 466 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2664 "lexer.tab.c"
    break;

  case 106: /* string_function: STRSTR '(' ID ',' ID ')'  */
#line 467 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2670 "lexer.tab.c"
    break;

  case 107: /* string_function: STRCMP '(' ID ',' ID ')'  */
#line 468 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2676 "lexer.tab.c"
    break;

  case 108: /* string_function: STRCHR '(' ID ',' ID ')'  */
#line 469 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2682 "lexer.tab.c"
    break;

  case 109: /* string_function: STRCAT '(' ID ',' ID ')'  */
#line 470 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2688 "lexer.tab.c"
    break;

  case 110: /* expression: ID ASSIGN expr  */
#line 473 "lexer.y"
                                                            {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2694 "lexer.tab.c"
    break;

  case 112: /* expression: ID DEC  */
#line 475 "lexer.y"
                                                            {var_verification((yyvsp[-1].str));decr((yyvsp[-1].str));}
#line 2700 "lexer.tab.c"
    break;

  case 113: /* expression: ID INC  */
#line 476 "lexer.y"
                                                            {var_verification((yyvsp[-1].str));incr((yyvsp[-1].str));}
#line 2706 "lexer.tab.c"
    break;

  case 114: /* expression: ID ASSIGN KEYWORD_TYPE  */
#line 477 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"NOPE");}
#line 2712 "lexer.tab.c"
    break;

  case 115: /* expression: ID ASSIGN type  */
#line 478 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str), "YES");}
#line 2718 "lexer.tab.c"
    break;

  case 116: /* expression: KEYWORD_TYPE ID ASSIGN NR  */
#line 479 "lexer.y"
                                                            {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "NOPE");}
#line 2724 "lexer.tab.c"
    break;

  case 117: /* expression: ID '[' NR ']' ASSIGN KEYWORD_TYPE  */
#line 480 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");}
#line 2730 "lexer.tab.c"
    break;

  case 118: /* expression: ID '[' NR ']' ASSIGN '/' '/' array '/' '/'  */
#line 481 "lexer.y"
                                                            {var_verification((yyvsp[-9].str));}
#line 2736 "lexer.tab.c"
    break;

  case 119: /* expression: ID '[' NR ']' '[' NR ']' ASSIGN KEYWORD_TYPE  */
#line 482 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-8].str),(yyvsp[0].str),"NOPE");}
#line 2742 "lexer.tab.c"
    break;

  case 121: /* expression: type ID ASSIGN NR  */
#line 484 "lexer.y"
                                                            {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr),"YES");}
#line 2748 "lexer.tab.c"
    break;

  case 131: /* expr: expr '+' expr  */
#line 503 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) + (yyvsp[0].nr);}
#line 2754 "lexer.tab.c"
    break;

  case 132: /* expr: expr '-' expr  */
#line 504 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) - (yyvsp[0].nr);}
#line 2760 "lexer.tab.c"
    break;

  case 133: /* expr: expr '*' expr  */
#line 505 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) * (yyvsp[0].nr);}
#line 2766 "lexer.tab.c"
    break;

  case 134: /* expr: expr ':' expr  */
#line 506 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) / (yyvsp[0].nr);}
#line 2772 "lexer.tab.c"
    break;

  case 135: /* expr: '(' expr ')'  */
#line 507 "lexer.y"
                            {(yyval.nr) =(yyvsp[-1].nr);}
#line 2778 "lexer.tab.c"
    break;

  case 136: /* expr: NR  */
#line 508 "lexer.y"
                            {(yyval.nr)=(yyvsp[0].nr);}
#line 2784 "lexer.tab.c"
    break;

  case 137: /* expr: ID  */
#line 509 "lexer.y"
                            {var_verification((yyvsp[0].str));initialization_verify((yyvsp[0].str));(yyval.nr)=return_value((yyvsp[0].str));}
#line 2790 "lexer.tab.c"
    break;

  case 138: /* expr: string_function  */
#line 510 "lexer.y"
                             {(yyval.nr)=0;}
#line 2796 "lexer.tab.c"
    break;

  case 139: /* expr: ID '[' op ']'  */
#line 511 "lexer.y"
                            {(yyval.nr)=0;}
#line 2802 "lexer.tab.c"
    break;

  case 140: /* expr: ID '[' op ']' '[' op ']'  */
#line 512 "lexer.y"
                            {(yyval.nr)=0;}
#line 2808 "lexer.tab.c"
    break;

  case 141: /* expr: '+' expr  */
#line 513 "lexer.y"
                            {(yyval.nr) =(yyval.nr) + (yyvsp[0].nr);}
#line 2814 "lexer.tab.c"
    break;

  case 142: /* expr: '-' expr  */
#line 514 "lexer.y"
                            {(yyval.nr) =(yyval.nr) - (yyvsp[0].nr);}
#line 2820 "lexer.tab.c"
    break;

  case 143: /* expr: '*' expr  */
#line 515 "lexer.y"
                            {(yyval.nr) =(yyval.nr) * (yyvsp[0].nr);}
#line 2826 "lexer.tab.c"
    break;

  case 144: /* expr: ':' expr  */
#line 516 "lexer.y"
                            {(yyval.nr) =(yyval.nr) /(yyvsp[0].nr);}
#line 2832 "lexer.tab.c"
    break;

  case 145: /* expr: function_call  */
#line 517 "lexer.y"
                             {(yyval.nr)=1;}
#line 2838 "lexer.tab.c"
    break;

  case 146: /* expr: ID '.' ID  */
#line 518 "lexer.y"
                            {(yyval.nr)=0;}
#line 2844 "lexer.tab.c"
    break;

  case 147: /* expr: ID '.' function_call  */
#line 519 "lexer.y"
                             {(yyval.nr)=0;}
#line 2850 "lexer.tab.c"
    break;

  case 148: /* expr: ID '.' ID '(' ')'  */
#line 520 "lexer.y"
                            {(yyval.nr)=0;}
#line 2856 "lexer.tab.c"
    break;

  case 149: /* expr: GHI ID GHI  */
#line 521 "lexer.y"
                            {(yyval.nr)=0;}
#line 2862 "lexer.tab.c"
    break;

  case 154: /* elem_printing: elem_printing ',' ID  */
#line 534 "lexer.y"
                                          {var_verification((yyvsp[0].str));}
#line 2868 "lexer.tab.c"
    break;

  case 155: /* elem_printing: ID  */
#line 535 "lexer.y"
                                        {var_verification((yyvsp[0].str));}
#line 2874 "lexer.tab.c"
    break;


#line 2878 "lexer.tab.c"

        default: break;
      }
    if (yychar_backup != yychar)
      YY_LAC_DISCARD ("yychar change");
  }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      {
        yypcontext_t yyctx
          = {yyssp, yyesa, &yyes, &yyes_capacity, yytoken};
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == -1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *,
                             YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (yymsg)
              {
                yysyntax_error_status
                  = yysyntax_error (&yymsg_alloc, &yymsg, &yyctx);
                yymsgp = yymsg;
              }
            else
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = YYENOMEM;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == YYENOMEM)
          goto yyexhaustedlab;
      }
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  /* If the stack popping above didn't lose the initial context for the
     current lookahead token, the shift below will for sure.  */
  YY_LAC_DISCARD ("error recovery");

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if 1
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturn;
#endif


/*-------------------------------------------------------.
| yyreturn -- parsing is finished, clean up and return.  |
`-------------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
  return yyresult;
}

#line 537 "lexer.y"


int yywrap(void) {
    return 1;
}

int yyerror(char * s){
printf("erorr: %s at line:%d\n",s,yylineno);
}

int main(int argc, char** argv){

 if (argc > 1) yyin = fopen(argv[1], "r");
 FILE* s;
 if(NULL == (s = fopen("symbol_table.txt","w")))
    {
        perror("Error opening file to process!\n");
        exit(1);
    }
    else {printf("It was successfully created\n");}
          
 fclose(s);  
   
yyparse();
} 
