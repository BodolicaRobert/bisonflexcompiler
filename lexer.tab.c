/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "lexer.y" /* yacc.c:339  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
extern int yyerror(char * syntaxerror);


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
        else 
         if(strcmp(var[verify_if_declared(name)].data_type,"float")==0 && value != 0)
          {var[verify_if_declared(name)].initialization=strdup("YES");  }
        else 
         if(strcmp(var[verify_if_declared(name)].data_type,"double")==0 && value != 0)
          {var[verify_if_declared(name)].initialization=strdup("YES");  }
        else 
         if(strcmp(var[verify_if_declared(name)].data_type,"bool")==0 && ( value == 0 || value==1))
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


#line 336 "lexer.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "lexer.tab.h".  */
#ifndef YY_YY_LEXER_TAB_H_INCLUDED
# define YY_YY_LEXER_TAB_H_INCLUDED
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

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 290 "lexer.y" /* yacc.c:355  */

      int nr;
      char* str;

#line 414 "lexer.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_LEXER_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 431 "lexer.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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
#endif


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   822

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  413

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   287

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,    24,    25,     2,     2,    51,     2,
      13,    14,     8,     5,     3,     6,    52,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     7,     4,
      20,    22,    21,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    17,     2,    18,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    15,     2,    16,     2,     2,     2,     2,
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
       2,     2,     2,     2,     2,     2,     1,     2,     9,    10,
      11,    12,    19,    26,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   300,   300,   303,   304,   307,   308,   311,   312,   315,
     316,   317,   320,   321,   324,   327,   328,   329,   332,   333,
     334,   335,   336,   337,   340,   343,   344,   347,   348,   349,
     350,   351,   354,   355,   358,   359,   360,   361,   362,   363,
     364,   365,   366,   369,   370,   373,   374,   375,   376,   379,
     380,   383,   384,   387,   388,   391,   394,   395,   396,   397,
     400,   401,   404,   407,   408,   411,   412,   413,   414,   415,
     416,   417,   418,   419,   422,   423,   424,   425,   426,   427,
     430,   431,   434,   435,   436,   437,   438,   439,   442,   443,
     444,   447,   448,   449,   450,   453,   454,   455,   456,   457,
     460,   461,   464,   465,   468,   469,   470,   471,   472,   473,
     476,   477,   478,   479,   480,   481,   482,   483,   484,   485,
     486,   487,   488,   489,   490,   494,   495,   498,   499,   502,
     503,   506,   507,   508,   509,   510,   511,   512,   513,   514,
     515,   516,   517,   518,   519,   520,   521,   522,   523,   524,
     527,   530,   531,   534,   537,   538
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "','", "';'", "'+'", "'-'", "':'", "'*'",
  "INC", "DEC", "OR", "AND", "'('", "')'", "'{'", "'}'", "'['", "']'",
  "ASSIGN", "'<'", "'>'", "'='", "'!'", "'\"'", "'#'", "KEYWORD_IF",
  "KEYWORD_WHILE", "KEYWORD_ELSE", "KEYWORD_FOR", "KEYWORD_CLASS", "MAIN",
  "GHI", "LIBRARY", "EQUAL", "KEYWORD_INCLUDE", "KEYWORD_RETURN", "READ",
  "WRITE", "NR", "ID", "KEYWORD_TYPE", "KEYWORD_CLASS_TYPE",
  "KEYWORD_CONST", "STRCAT", "STRSTR", "STRCHR", "STRCMP", "STRLEN",
  "STRCPY", "EVAL", "'&'", "'.'", "$accept", "start", "libraries",
  "library", "classes", "class", "class_declarations", "class_declaration",
  "class_dec", "dec", "type", "class_functions", "class_function",
  "function_parameters", "function_parameter", "function_call", "ids",
  "op", "function_declarations", "function_declaration", "return",
  "global", "global_function", "program", "declarations", "declaration",
  "conditions", "condition", "arithmetic_operator", "logic_operator",
  "content", "cond", "instructions", "instruction", "string_function",
  "expression", "array", "matrix", "matrix_elements", "expr", "reading",
  "elem_reading", "printing", "elem_printing", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,    44,    59,    43,    45,    58,    42,   258,
     259,   260,   261,    40,    41,   123,   125,    91,    93,   262,
      60,    62,    61,    33,    34,    35,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,    38,    46
};
# endif

#define YYPACT_NINF -253

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-253)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      58,    72,   111,    67,  -253,   101,  -253,    88,   118,  -253,
     173,  -253,   130,   132,   135,   171,    28,   145,   156,  -253,
     162,   230,  -253,  -253,   226,   236,   232,   252,  -253,  -253,
      -8,   238,   294,  -253,   271,    21,  -253,   262,   140,  -253,
    -253,  -253,  -253,   310,    49,  -253,   280,  -253,  -253,  -253,
      12,   342,   463,   463,   463,   463,   463,   284,  -253,     0,
    -253,   355,   357,   363,   376,   378,   383,  -253,  -253,  -253,
     323,   117,   296,    35,   315,   188,   365,   402,  -253,   364,
     403,    31,   254,   384,   418,  -253,    82,  -253,   416,    -8,
    -253,   241,   246,   246,  -253,  -253,   258,   398,   183,    -8,
     404,   405,   406,   413,   425,   426,   432,   433,   463,   463,
     463,   463,   424,    -8,   420,   442,  -253,   124,  -253,  -253,
      45,   318,   458,   747,  -253,   772,   291,   438,   108,  -253,
     447,    22,   361,  -253,   482,  -253,    80,  -253,   451,     1,
    -253,  -253,  -253,  -253,   143,   473,   479,   224,  -253,   490,
     491,   493,   494,   484,   496,   246,   246,  -253,  -253,  -253,
    -253,   459,    92,   486,   306,   487,  -253,  -253,   472,   505,
     506,   507,   508,    -8,   466,   480,   483,   526,   146,  -253,
    -253,  -253,  -253,  -253,  -253,  -253,   511,   772,  -253,   509,
     239,   525,  -253,   527,    35,   530,   513,   524,   532,   197,
     531,    -8,  -253,   247,  -253,   553,   183,   102,   533,   534,
     535,   539,  -253,   551,  -253,  -253,   747,   554,   555,   552,
    -253,   244,   244,   747,   341,  -253,  -253,   594,  -253,   595,
     580,   463,  -253,  -253,  -253,  -253,   582,  -253,  -253,  -253,
     562,   578,   201,   747,   227,   565,   747,   607,   604,    53,
    -253,  -253,    -8,   214,  -253,   610,   611,   612,   613,   617,
     488,   624,  -253,   608,  -253,  -253,   339,  -253,   133,  -253,
     367,   343,   165,  -253,  -253,   514,  -253,   629,   634,   636,
     635,   637,   308,   336,  -253,  -253,   638,   540,    92,   639,
     566,   747,    55,  -253,   633,  -253,  -253,  -253,  -253,  -253,
    -253,  -253,   616,  -253,   656,   662,   298,   463,   663,  -253,
     387,   339,  -253,   657,   661,   673,  -253,   463,   685,  -253,
    -253,   664,   682,   687,  -253,  -253,  -253,   665,   668,   747,
    -253,   217,  -253,   592,   692,  -253,  -253,  -253,  -253,   343,
     747,   339,  -253,   707,  -253,  -253,  -253,   323,   747,   723,
     689,   747,   708,  -253,   618,   714,  -253,    -8,   110,   463,
     644,   716,  -253,   670,   691,   731,   696,   728,  -253,   747,
    -253,   218,   739,  -253,   444,  -253,  -253,  -253,   465,   749,
     691,  -253,   713,   722,    -8,  -253,    -8,  -253,   415,   435,
     733,   717,   752,  -253,  -253,  -253,   221,   463,   323,   463,
     323,   463,   388,   721,  -253,   323,   323,   323,  -253,  -253,
     399,  -253,  -253
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       0,     0,     0,     0,     4,     0,     1,     0,     0,     3,
       0,     8,     0,     0,     0,     0,     0,     0,     0,     7,
       0,     0,    59,    58,     0,     0,     0,     0,   113,   112,
       0,     0,     0,   122,     0,     0,    24,     0,     0,    57,
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
       0,     0,   117,     0,    44,   139,     0,     0,     0,     0,
       0,     0,   104,     0,    40,    32,     0,     0,     0,     0,
      39,     0,     0,     0,     0,    55,   152,   150,   155,   153,
       0,     0,    61,    51,     2,    63,     0,    23,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    45,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,    36,     0,    89,    88,     0,    90,     0,    78,
       0,     0,     0,   103,   102,     0,   101,     0,     0,     0,
       0,     0,     0,     0,    17,    22,    31,     0,     0,     0,
       0,     0,     0,   118,     0,    43,   109,   106,   108,   107,
     105,    60,     0,    38,     0,     0,     0,     0,     0,    90,
       0,     0,    76,    86,    85,     0,    87,     0,     0,    66,
     100,     0,     0,     0,   151,   154,    73,     0,     0,     0,
      30,     0,    10,     0,     0,   119,   140,    37,    79,     0,
       0,     0,    74,     0,    83,    82,    84,    80,     0,     0,
       0,     0,     0,    21,     0,     0,    11,     0,     0,     0,
       0,     0,    77,     0,     0,     0,     0,     0,    28,     0,
     130,     0,     0,   120,     0,    65,    75,    68,     0,     0,
       0,    67,     0,     0,     0,   128,     0,    81,     0,     0,
       0,     0,     0,    20,    27,   129,     0,     0,    98,     0,
      99,     0,     0,     0,   127,    96,    95,    97,    94,    93,
       0,    91,    92
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -253,  -253,  -253,   761,  -253,   767,  -253,   734,  -253,   651,
     -22,  -253,   694,  -127,   -28,   -27,   575,   -88,  -210,  -173,
    -211,  -253,   765,  -253,  -253,  -122,   560,  -252,   450,  -217,
    -253,   422,  -142,  -248,  -121,   215,   602,  -253,   419,   -32,
    -253,  -253,  -253,  -253
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,     2,     3,     4,    10,    11,    44,    45,   128,   129,
      20,    86,    87,   117,   118,    68,   144,    49,   178,   179,
     180,    21,    22,   186,   187,   181,   268,   269,   317,   270,
     279,   379,   275,   276,    69,   183,    50,   358,   371,   271,
     184,   227,   185,   229
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint16 yytable[] =
{
      70,   137,   182,   188,   182,   233,   260,    77,    78,   199,
      67,   145,   273,    98,   305,    89,   201,    99,   312,   100,
      92,    93,    94,    95,    96,   160,    90,   320,    27,    72,
      72,    47,    48,   287,    73,   194,   290,    28,    29,    72,
      74,    30,   202,    72,    73,    31,    78,    32,   115,   116,
      74,   310,   101,    77,    78,   310,    89,   182,   342,   343,
     130,    75,    75,   164,   273,   235,   182,   242,    33,   293,
     334,    75,    76,    76,   148,    75,   155,   156,   157,   158,
      34,   333,    76,     1,   165,   225,    76,   233,    72,   361,
      83,    84,     1,   115,   198,   182,   335,     7,   133,   167,
      72,   274,   182,   195,    78,   115,   130,     5,     8,    78,
     130,     6,   320,   372,   233,   320,   254,   233,   320,   354,
      75,    12,   182,    83,   134,   182,   373,   162,    14,   273,
     112,    76,    75,    13,   215,    78,   113,   273,   163,   182,
     273,   142,   143,    76,   264,   265,   203,   308,   126,   273,
      26,    18,   273,   274,   182,   273,   309,   204,    15,   383,
     233,   331,   232,    24,   294,    25,   182,    78,   239,   182,
     182,    80,   169,   170,   171,   172,   264,   265,    27,   318,
      81,   233,   173,   174,   175,    35,    16,   176,   309,    18,
      61,    62,    63,    64,    65,    66,   177,    36,   360,   282,
     162,    98,    37,     7,   162,   120,   363,   121,   182,   366,
     233,   247,   182,    16,    17,   286,    18,   203,   274,   182,
     162,   384,   142,   143,   384,    23,   274,   182,   295,   274,
     182,   355,   385,   182,   306,   404,    40,   207,   274,   182,
     288,   274,   182,   100,   274,   182,   240,    41,   182,    52,
      53,    54,    55,   110,   111,   264,   265,   266,   138,    46,
     139,    78,   182,   108,   109,   110,   111,   267,    42,   370,
      16,    38,   140,    18,    43,   339,    57,    51,   237,   306,
     238,    79,    18,    58,    59,   347,   250,   251,    61,    62,
      63,    64,    65,    66,   126,   127,   395,    18,   370,    52,
      53,    54,    55,   108,   109,   110,   111,    56,   189,   306,
     190,    71,   140,   108,   109,   110,   111,    82,   313,   314,
      88,   315,   326,   217,    97,   218,    57,   374,   108,   109,
     110,   111,   316,    58,    59,    60,   114,    18,    61,    62,
      63,    64,    65,    66,    52,    53,    54,    55,   108,   109,
     110,   111,    56,   327,   119,   328,   398,   400,   146,   166,
      91,    18,   304,   313,   314,   405,   315,   406,   102,   407,
     103,    57,    52,    53,    54,    55,   104,   316,    58,    59,
     311,   277,   278,    61,    62,    63,    64,    65,    66,   105,
     304,   106,    52,    53,    54,    55,   107,   408,   409,    57,
     341,   126,   196,   124,    18,   122,    58,    59,   411,   412,
     304,    61,    62,    63,    64,    65,    66,   123,   125,    57,
      52,    53,    54,    55,   131,   132,    58,    59,    56,   136,
     141,    61,    62,    63,    64,    65,    66,   397,   159,   161,
      52,    53,    54,    55,   146,   147,   149,    57,    56,   108,
     109,   110,   111,   150,    58,    59,   116,   399,   387,    61,
      62,    63,    64,    65,    66,   151,   152,    57,    52,    53,
      54,    55,   153,   154,    58,    59,    56,   168,   191,    61,
      62,    63,    64,    65,    66,   388,   389,   193,   390,   197,
     200,   205,   206,   208,   209,    57,   210,   211,   212,   213,
     214,   216,    58,    59,   301,   219,   226,    61,    62,    63,
      64,    65,    66,   220,   169,   170,   171,   172,   221,   222,
     228,   224,   223,   230,   173,   174,   175,   234,    16,   176,
     319,    18,    61,    62,    63,    64,    65,    66,   177,   231,
     169,   170,   171,   172,   240,   243,   241,   246,   236,   248,
     173,   174,   175,   244,    16,   176,   330,    18,    61,    62,
      63,    64,    65,    66,   177,   245,   169,   170,   171,   172,
     252,   263,   261,   255,   256,   257,   173,   174,   175,   258,
      16,   176,   332,    18,    61,    62,    63,    64,    65,    66,
     177,   259,   169,   170,   171,   172,   262,   280,   281,    74,
     283,   284,   173,   174,   175,   289,    16,   176,   356,    18,
      61,    62,    63,    64,    65,    66,   177,   285,   169,   170,
     171,   172,   291,   292,   296,   297,   298,   299,   173,   174,
     175,   300,    16,   176,   368,    18,    61,    62,    63,    64,
      65,    66,   177,   302,   169,   170,   171,   172,   321,   303,
     323,   336,   288,   329,   173,   174,   175,   337,    16,   176,
     375,    18,    61,    62,    63,    64,    65,    66,   177,   307,
     169,   170,   171,   172,   322,   324,   338,   325,   340,   344,
     173,   174,   175,   345,    16,   176,   377,    18,    61,    62,
      63,    64,    65,    66,   177,   346,   169,   170,   171,   172,
     348,   350,   351,   349,   352,   357,   173,   174,   175,   353,
      16,   176,   381,    18,    61,    62,    63,    64,    65,    66,
     177,   362,   169,   170,   171,   172,   367,   364,   365,   369,
     376,   378,   173,   174,   175,   380,    16,   176,   394,    18,
      61,    62,    63,    64,    65,    66,   177,   382,   169,   170,
     171,   172,   386,   391,   393,   401,   403,   402,   173,   174,
     175,   410,    16,   176,     9,    18,    61,    62,    63,    64,
      65,    66,   177,   169,   170,   171,   172,    19,    85,   192,
     135,   253,   272,   173,   174,   175,    39,    16,   176,   359,
      18,    61,    62,    63,    64,    65,    66,   177,   169,   170,
     171,   172,   392,   249,     0,   396,     0,     0,     0,   174,
     175,     0,    16,   176,     0,    18,    61,    62,    63,    64,
      65,    66,   177
};

static const yytype_int16 yycheck[] =
{
      32,    89,   123,   125,   125,   178,   216,    35,    35,   136,
      32,    99,   223,    13,   266,     3,    15,    17,   270,    19,
      52,    53,    54,    55,    56,   113,    14,   275,     7,     8,
       8,    39,    40,   243,    13,    13,   246,     9,    10,     8,
      19,    13,    41,     8,    13,    17,    73,    19,    13,    14,
      19,   268,    52,    81,    81,   272,     3,   178,   310,   311,
      82,    40,    40,    18,   275,   187,   187,   194,    40,    16,
      15,    40,    51,    51,   101,    40,   108,   109,   110,   111,
      52,   291,    51,    25,    39,   173,    51,   260,     8,   341,
      41,    42,    25,    13,    14,   216,    41,    30,    16,   121,
       8,   223,   223,   131,   131,    13,   128,    35,    41,   136,
     132,     0,   360,     3,   287,   363,    14,   290,   366,   329,
      40,    20,   243,    41,    42,   246,    16,     3,    40,   340,
      13,    51,    40,    32,   162,   162,    19,   348,    14,   260,
     351,    39,    40,    51,    11,    12,     3,    14,    40,   360,
      15,    43,   363,   275,   275,   366,    23,    14,    40,   369,
     333,   288,    16,    33,   252,    33,   287,   194,   190,   290,
     291,    31,    26,    27,    28,    29,    11,    12,     7,    14,
      40,   354,    36,    37,    38,    40,    40,    41,    23,    43,
      44,    45,    46,    47,    48,    49,    50,    41,   340,   231,
       3,    13,    40,    30,     3,    17,   348,    19,   329,   351,
     383,    14,   333,    40,    41,    14,    43,     3,   340,   340,
       3,     3,    39,    40,     3,    10,   348,   348,    14,   351,
     351,    14,    14,   354,   266,    14,    21,    13,   360,   360,
      13,   363,   363,    19,   366,   366,    19,    21,   369,     5,
       6,     7,     8,     7,     8,    11,    12,    13,    17,     7,
      19,   288,   383,     5,     6,     7,     8,    23,    32,   357,
      40,    41,    14,    43,    42,   307,    32,    39,    39,   311,
      41,    19,    43,    39,    40,   317,    39,    40,    44,    45,
      46,    47,    48,    49,    40,    41,   384,    43,   386,     5,
       6,     7,     8,     5,     6,     7,     8,    13,    17,   341,
      19,    40,    14,     5,     6,     7,     8,     7,    20,    21,
      40,    23,    14,    17,    40,    19,    32,   359,     5,     6,
       7,     8,    34,    39,    40,    41,    40,    43,    44,    45,
      46,    47,    48,    49,     5,     6,     7,     8,     5,     6,
       7,     8,    13,    17,    39,    19,   388,   389,    40,    41,
      18,    43,    23,    20,    21,   397,    23,   399,    13,   401,
      13,    32,     5,     6,     7,     8,    13,    34,    39,    40,
      13,    40,    41,    44,    45,    46,    47,    48,    49,    13,
      23,    13,     5,     6,     7,     8,    13,     9,    10,    32,
      13,    40,    41,    39,    43,    40,    39,    40,     9,    10,
      23,    44,    45,    46,    47,    48,    49,    15,    15,    32,
       5,     6,     7,     8,    40,     7,    39,    40,    13,    13,
      32,    44,    45,    46,    47,    48,    49,    22,    14,    19,
       5,     6,     7,     8,    40,    40,    40,    32,    13,     5,
       6,     7,     8,    40,    39,    40,    14,    22,    14,    44,
      45,    46,    47,    48,    49,    40,    40,    32,     5,     6,
       7,     8,    40,    40,    39,    40,    13,    19,    40,    44,
      45,    46,    47,    48,    49,    20,    21,    40,    23,     7,
      39,    18,    13,     3,     3,    32,     3,     3,    14,     3,
      41,    15,    39,    40,    16,    18,    40,    44,    45,    46,
      47,    48,    49,    41,    26,    27,    28,    29,    13,    13,
      40,    13,    15,    40,    36,    37,    38,    16,    40,    41,
      16,    43,    44,    45,    46,    47,    48,    49,    50,    13,
      26,    27,    28,    29,    19,    15,    19,    15,    39,    18,
      36,    37,    38,    40,    40,    41,    16,    43,    44,    45,
      46,    47,    48,    49,    50,    41,    26,    27,    28,    29,
      17,    19,    18,    40,    40,    40,    36,    37,    38,    40,
      40,    41,    16,    43,    44,    45,    46,    47,    48,    49,
      50,    40,    26,    27,    28,    29,    41,     3,     3,    19,
      18,    39,    36,    37,    38,    40,    40,    41,    16,    43,
      44,    45,    46,    47,    48,    49,    50,    39,    26,    27,
      28,    29,    15,    19,    14,    14,    14,    14,    36,    37,
      38,    14,    40,    41,    16,    43,    44,    45,    46,    47,
      48,    49,    50,    19,    26,    27,    28,    29,    19,    41,
      14,    18,    13,    15,    36,    37,    38,    41,    40,    41,
      16,    43,    44,    45,    46,    47,    48,    49,    50,    13,
      26,    27,    28,    29,    40,    40,    14,    40,    15,    22,
      36,    37,    38,    22,    40,    41,    16,    43,    44,    45,
      46,    47,    48,    49,    50,    22,    26,    27,    28,    29,
      15,    19,    15,    39,    39,    13,    36,    37,    38,    41,
      40,    41,    16,    43,    44,    45,    46,    47,    48,    49,
      50,    14,    26,    27,    28,    29,    18,     4,    39,    15,
      14,    40,    36,    37,    38,     4,    40,    41,    16,    43,
      44,    45,    46,    47,    48,    49,    50,    19,    26,    27,
      28,    29,    13,     4,    41,    22,     4,    40,    36,    37,
      38,    40,    40,    41,     3,    43,    44,    45,    46,    47,
      48,    49,    50,    26,    27,    28,    29,    10,    44,   128,
      86,   206,   222,    36,    37,    38,    21,    40,    41,   339,
      43,    44,    45,    46,    47,    48,    49,    50,    26,    27,
      28,    29,   380,   201,    -1,   386,    -1,    -1,    -1,    37,
      38,    -1,    40,    41,    -1,    43,    44,    45,    46,    47,
      48,    49,    50
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    25,    54,    55,    56,    35,     0,    30,    41,    56,
      57,    58,    20,    32,    40,    40,    40,    41,    43,    58,
      63,    74,    75,    88,    33,    33,    15,     7,     9,    10,
      13,    17,    19,    40,    52,    40,    41,    40,    41,    75,
      88,    21,    32,    42,    59,    60,     7,    39,    40,    70,
      89,    39,     5,     6,     7,     8,    13,    32,    39,    40,
      41,    44,    45,    46,    47,    48,    49,    63,    68,    87,
      92,    40,     8,    13,    19,    40,    51,    67,    68,    19,
      31,    40,     7,    41,    42,    60,    64,    65,    40,     3,
      14,    18,    92,    92,    92,    92,    92,    40,    13,    17,
      19,    52,    13,    13,    13,    13,    13,    13,     5,     6,
       7,     8,    13,    19,    40,    13,    14,    66,    67,    39,
      17,    19,    40,    15,    39,    15,    40,    41,    61,    62,
      63,    40,     7,    16,    42,    65,    13,    70,    17,    19,
      14,    32,    39,    40,    69,    70,    40,    40,    68,    40,
      40,    40,    40,    40,    40,    92,    92,    92,    92,    14,
      70,    19,     3,    14,    18,    39,    41,    63,    19,    26,
      27,    28,    29,    36,    37,    38,    41,    50,    71,    72,
      73,    78,    87,    88,    93,    95,    76,    77,    78,    17,
      19,    40,    62,    40,    13,    67,    41,     7,    14,    66,
      39,    15,    41,     3,    14,    18,    13,    13,     3,     3,
       3,     3,    14,     3,    41,    67,    15,    17,    19,    18,
      41,    13,    13,    15,    13,    70,    40,    94,    40,    96,
      40,    13,    16,    72,    16,    78,    39,    39,    41,    63,
      19,    19,    66,    15,    40,    41,    15,    14,    18,    89,
      39,    40,    17,    69,    14,    40,    40,    40,    40,    40,
      71,    18,    41,    19,    11,    12,    13,    23,    79,    80,
      82,    92,    79,    73,    78,    85,    86,    40,    41,    83,
       3,     3,    92,    18,    39,    39,    14,    71,    13,    40,
      71,    15,    19,    16,    70,    14,    14,    14,    14,    14,
      14,    16,    19,    41,    23,    80,    92,    13,    14,    23,
      82,    13,    80,    20,    21,    23,    34,    81,    14,    16,
      86,    19,    40,    14,    40,    40,    14,    17,    19,    15,
      16,    66,    16,    71,    15,    41,    18,    41,    14,    92,
      15,    13,    80,    80,    22,    22,    22,    92,    15,    39,
      19,    15,    39,    41,    71,    14,    16,    13,    90,    81,
      85,    80,    14,    85,     4,    39,    85,    18,    16,    15,
      70,    91,     3,    16,    92,    16,    14,    16,    40,    84,
       4,    16,    19,    71,     3,    14,    13,    14,    20,    21,
      23,     4,    84,    41,    16,    70,    91,    22,    92,    22,
      92,    22,    40,     4,    14,    92,    92,    92,     9,    10,
      40,     9,    10
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    56,    56,    57,    57,    58,
      58,    58,    59,    59,    60,    61,    61,    61,    62,    62,
      62,    62,    62,    62,    63,    64,    64,    65,    65,    65,
      65,    65,    66,    66,    67,    67,    67,    67,    67,    67,
      67,    67,    67,    68,    68,    69,    69,    69,    69,    70,
      70,    71,    71,    72,    72,    73,    74,    74,    74,    74,
      75,    75,    76,    77,    77,    78,    78,    78,    78,    78,
      78,    78,    78,    78,    79,    79,    79,    79,    79,    79,
      80,    80,    81,    81,    81,    81,    81,    81,    82,    82,
      82,    83,    83,    83,    83,    84,    84,    84,    84,    84,
      85,    85,    86,    86,    87,    87,    87,    87,    87,    87,
      88,    88,    88,    88,    88,    88,    88,    88,    88,    88,
      88,    88,    88,    88,    88,    89,    89,    90,    90,    91,
      91,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      92,    92,    92,    92,    92,    92,    92,    92,    92,    92,
      93,    94,    94,    95,    96,    96
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
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
       3,     4,     2,     2,     3,     3,     4,     6,     8,     9,
      11,     4,     2,     5,     5,     1,     3,     5,     3,     3,
       1,     3,     3,     3,     3,     3,     1,     1,     1,     4,
       7,     2,     2,     2,     2,     1,     3,     3,     5,     3,
       2,     3,     1,     2,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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
   required.  Return 1 if memory is exhausted.  */
static int
yy_lac_stack_realloc (YYSIZE_T *yycapacity, YYSIZE_T yyadd,
#if YYDEBUG
                      char const *yydebug_prefix,
                      char const *yydebug_suffix,
#endif
                      yytype_int16 **yybottom,
                      yytype_int16 *yybottom_no_free,
                      yytype_int16 **yytop, yytype_int16 *yytop_empty)
{
  YYSIZE_T yysize_old =
    *yytop == yytop_empty ? 0 : *yytop - *yybottom + 1;
  YYSIZE_T yysize_new = yysize_old + yyadd;
  if (*yycapacity < yysize_new)
    {
      YYSIZE_T yyalloc = 2 * yysize_new;
      yytype_int16 *yybottom_new;
      /* Use YYMAXDEPTH for maximum stack size given that the stack
         should never need to grow larger than the main state stack
         needs to grow without LAC.  */
      if (YYMAXDEPTH < yysize_new)
        {
          YYDPRINTF ((stderr, "%smax size exceeded%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
        }
      if (YYMAXDEPTH < yyalloc)
        yyalloc = YYMAXDEPTH;
      yybottom_new =
        (yytype_int16*) YYSTACK_ALLOC (yyalloc * sizeof *yybottom_new);
      if (!yybottom_new)
        {
          YYDPRINTF ((stderr, "%srealloc failed%s", yydebug_prefix,
                      yydebug_suffix));
          return 1;
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
#define YY_LAC_ESTABLISH                                         \
do {                                                             \
  if (!yy_lac_established)                                       \
    {                                                            \
      YYDPRINTF ((stderr,                                        \
                  "LAC: initial context established for %s\n",   \
                  yytname[yytoken]));                            \
      yy_lac_established = 1;                                    \
      {                                                          \
        int yy_lac_status =                                      \
          yy_lac (yyesa, &yyes, &yyes_capacity, yyssp, yytoken); \
        if (yy_lac_status == 2)                                  \
          goto yyexhaustedlab;                                   \
        if (yy_lac_status == 1)                                  \
          goto yyerrlab;                                         \
      }                                                          \
    }                                                            \
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
      if (yydebug)                                                       \
        YYFPRINTF (stderr, "LAC: initial context discarded due to "      \
                   Event "\n");                                          \
      yy_lac_established = 0;                                            \
    }                                                                    \
} while (0)
#else
# define YY_LAC_DISCARD(Event) yy_lac_established = 0
#endif

/* Given the stack whose top is *YYSSP, return 0 iff YYTOKEN can
   eventually (after perhaps some reductions) be shifted, return 1 if
   not, or return 2 if memory is exhausted.  As preconditions and
   postconditions: *YYES_CAPACITY is the allocated size of the array to
   which *YYES points, and either *YYES = YYESA or *YYES points to an
   array allocated with YYSTACK_ALLOC.  yy_lac may overwrite the
   contents of either array, alter *YYES and *YYES_CAPACITY, and free
   any old *YYES other than YYESA.  */
static int
yy_lac (yytype_int16 *yyesa, yytype_int16 **yyes,
        YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  yytype_int16 *yyes_prev = yyssp;
  yytype_int16 *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
    {
      YYDPRINTF ((stderr, " Always Err\n"));
      return 1;
    }
  while (1)
    {
      int yyrule = yypact[*yyesp];
      if (yypact_value_is_default (yyrule)
          || (yyrule += yytoken) < 0 || YYLAST < yyrule
          || yycheck[yyrule] != yytoken)
        {
          yyrule = yydefact[*yyesp];
          if (yyrule == 0)
            {
              YYDPRINTF ((stderr, " Err\n"));
              return 1;
            }
        }
      else
        {
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
      {
        YYSIZE_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
        if (yyesp != yyes_prev)
          {
            YYSIZE_T yysize = yyesp - *yyes + 1;
            if (yylen < yysize)
              {
                yyesp -= yylen;
                yylen = 0;
              }
            else
              {
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
      {
        int yystate;
        {
          int yylhs = yyr1[yyrule] - YYNTOKENS;
          yystate = yypgoto[yylhs] + *yyesp;
          if (yystate < 0 || YYLAST < yystate
              || yycheck[yystate] != *yyesp)
            yystate = yydefgoto[yylhs];
          else
            yystate = yytable[yystate];
        }
        if (yyesp == yyes_prev)
          {
            yyesp = *yyes;
            *yyesp = yystate;
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
                return 2;
              }
            *++yyesp = yystate;
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
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
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
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
            /* Fall through.  */
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

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.  In order to see if a particular token T is a
   valid looakhead, invoke yy_lac (YYESA, YYES, YYES_CAPACITY, YYSSP, T).

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store or if
   yy_lac returned 2.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyesa, yytype_int16 **yyes,
                YYSIZE_T *yyes_capacity, yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
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
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      YYDPRINTF ((stderr, "Constructing syntax error message\n"));
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          int yyx;

          for (yyx = 0; yyx < YYNTOKENS; ++yyx)
            if (yyx != YYTERROR && yyx != YYUNDEFTOK)
              {
                {
                  int yy_lac_status = yy_lac (yyesa, yyes, yyes_capacity,
                                              yyssp, yyx);
                  if (yy_lac_status == 2)
                    return 2;
                  if (yy_lac_status == 1)
                    continue;
                }
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
# if YYDEBUG
      else if (yydebug)
        YYFPRINTF (stderr, "No expected tokens.\n");
# endif
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
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
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

    yytype_int16 yyesa[20];
    yytype_int16 *yyes;
    YYSIZE_T yyes_capacity;

  int yy_lac_established = 0;
  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = sizeof yyesa / sizeof *yyes;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  YY_LAC_DISCARD ("shift");

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
          case 2:
#line 300 "lexer.y" /* yacc.c:1646  */
    {printf("The program is accepted\n");}
#line 2092 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 315 "lexer.y" /* yacc.c:1646  */
    {PrintFunct("Class Methods");}
#line 2098 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 320 "lexer.y" /* yacc.c:1646  */
    {PrintVar("Class");}
#line 2104 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 329 "lexer.y" /* yacc.c:1646  */
    {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "NOPE");}
#line 2110 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 332 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"NOPE");}
#line 2116 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 333 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"YES");}
#line 2122 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 334 "lexer.y" /* yacc.c:1646  */
    { var_declaring_without_init((yyvsp[-8].str),(yyvsp[0].str),"NOPE");}
#line 2128 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 335 "lexer.y" /* yacc.c:1646  */
    { var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");}
#line 2134 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 336 "lexer.y" /* yacc.c:1646  */
    {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "YES");}
#line 2140 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 337 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2146 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 340 "lexer.y" /* yacc.c:1646  */
    {strcat((yyvsp[-1].str)," ");strcat((yyvsp[-1].str),(yyvsp[0].str));(yyval.str)=(yyvsp[-1].str);}
#line 2152 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 347 "lexer.y" /* yacc.c:1646  */
    {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2158 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 348 "lexer.y" /* yacc.c:1646  */
    {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2164 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 349 "lexer.y" /* yacc.c:1646  */
    {declaring_function((yyvsp[-2].str),(yyvsp[-1].str),(yyvsp[0].str));}
#line 2170 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 350 "lexer.y" /* yacc.c:1646  */
    {declaring_function((yyvsp[-5].str),(yyvsp[-4].str),(yyvsp[-3].str));PrintVar("the function");}
#line 2176 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 351 "lexer.y" /* yacc.c:1646  */
    {declaring_function((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str));}
#line 2182 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 354 "lexer.y" /* yacc.c:1646  */
    {strcat((yyvsp[0].str),";");strcat((yyvsp[0].str),(yyvsp[-2].str));(yyval.str)=(yyvsp[0].str);}
#line 2188 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 355 "lexer.y" /* yacc.c:1646  */
    {strcat((yyvsp[0].str),";");}
#line 2194 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 358 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2200 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 359 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"YES");(yyval.str)=(yyvsp[0].str);}
#line 2206 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 360 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-4].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2212 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 361 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-6].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2218 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 362 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2224 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 363 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2230 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 364 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2236 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 365 "lexer.y" /* yacc.c:1646  */
    {(yyval.str)=0;}
#line 2242 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 366 "lexer.y" /* yacc.c:1646  */
    {(yyval.str)=0;}
#line 2248 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 369 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-5].str)); identify_function((yyvsp[-3].str),(yyvsp[-1].str));}
#line 2254 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 370 "lexer.y" /* yacc.c:1646  */
    {identify_function((yyvsp[-3].str),(yyvsp[-1].str));}
#line 2260 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 373 "lexer.y" /* yacc.c:1646  */
    {strcat((yyvsp[0].str),";");strcat((yyvsp[0].str),(yyvsp[-2].str));(yyval.str)=(yyvsp[0].str);}
#line 2266 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 374 "lexer.y" /* yacc.c:1646  */
    {(yyval.str)=strdup("int;");strcat((yyval.str),(yyvsp[-2].str));}
#line 2272 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 375 "lexer.y" /* yacc.c:1646  */
    {strcat((yyvsp[0].str),";");(yyval.str)=(yyvsp[0].str);}
#line 2278 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 376 "lexer.y" /* yacc.c:1646  */
    {(yyval.str)=strdup("int;");}
#line 2284 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 379 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[0].str));}
#line 2290 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 394 "lexer.y" /* yacc.c:1646  */
    {PrintVar("global");}
#line 2296 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 395 "lexer.y" /* yacc.c:1646  */
    {PrintFunct("global");}
#line 2302 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 400 "lexer.y" /* yacc.c:1646  */
    {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2308 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 401 "lexer.y" /* yacc.c:1646  */
    {declaring_function((yyvsp[-5].str),(yyvsp[-4].str),(yyvsp[-3].str));PrintVar("the function");}
#line 2314 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 404 "lexer.y" /* yacc.c:1646  */
    {PrintVar("main");show_exp();}
#line 2320 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 419 "lexer.y" /* yacc.c:1646  */
    {add_arg((yyvsp[-1].nr));}
#line 2326 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 91:
#line 447 "lexer.y" /* yacc.c:1646  */
    {var_declaring((yyvsp[-7].str),(yyvsp[-8].str),(yyvsp[-5].nr),"NOPE");var_verification((yyvsp[-7].str));incr((yyvsp[-8].str));}
#line 2332 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 92:
#line 448 "lexer.y" /* yacc.c:1646  */
    {var_declaring((yyvsp[-7].str),(yyvsp[-8].str),(yyvsp[-5].nr),"NOPE");var_verification((yyvsp[-7].str));decr((yyvsp[-8].str));}
#line 2338 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 93:
#line 449 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-7].str));var_verification((yyvsp[-1].str));Assign((yyvsp[-7].str),(yyvsp[-5].nr));decr((yyvsp[-7].str));}
#line 2344 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 94:
#line 450 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-7].str));var_verification((yyvsp[-1].str));Assign((yyvsp[-7].str),(yyvsp[-5].nr));incr((yyvsp[-7].str));}
#line 2350 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 95:
#line 453 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str)); }
#line 2356 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 96:
#line 454 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str)); }
#line 2362 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 97:
#line 455 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str)); }
#line 2368 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 98:
#line 456 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-2].str)); }
#line 2374 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 99:
#line 457 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-2].str)); }
#line 2380 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 104:
#line 468 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-1].str));}
#line 2386 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 105:
#line 469 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2392 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 106:
#line 470 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2398 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 107:
#line 471 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2404 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 108:
#line 472 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2410 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 109:
#line 473 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2416 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 110:
#line 476 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2422 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 112:
#line 478 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-1].str));decr((yyvsp[-1].str));}
#line 2428 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 113:
#line 479 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-1].str));incr((yyvsp[-1].str));}
#line 2434 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 114:
#line 480 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"NOPE");}
#line 2440 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 115:
#line 481 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str), "YES");}
#line 2446 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 116:
#line 482 "lexer.y" /* yacc.c:1646  */
    {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "NOPE");}
#line 2452 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 117:
#line 483 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");}
#line 2458 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 118:
#line 484 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[-7].str));}
#line 2464 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 119:
#line 485 "lexer.y" /* yacc.c:1646  */
    {var_declaring_without_init((yyvsp[-8].str),(yyvsp[0].str),"NOPE");}
#line 2470 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 121:
#line 487 "lexer.y" /* yacc.c:1646  */
    {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr),"YES");}
#line 2476 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 131:
#line 506 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) = (yyvsp[-2].nr) + (yyvsp[0].nr);}
#line 2482 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 132:
#line 507 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) = (yyvsp[-2].nr) - (yyvsp[0].nr);}
#line 2488 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 133:
#line 508 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) = (yyvsp[-2].nr) * (yyvsp[0].nr);}
#line 2494 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 134:
#line 509 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) = (yyvsp[-2].nr) / (yyvsp[0].nr);}
#line 2500 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 135:
#line 510 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) =(yyvsp[-1].nr);}
#line 2506 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 136:
#line 511 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=(yyvsp[0].nr);}
#line 2512 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 137:
#line 512 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[0].str));initialization_verify((yyvsp[0].str));(yyval.nr)=return_value((yyvsp[0].str));}
#line 2518 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 138:
#line 513 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=0;}
#line 2524 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 139:
#line 514 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=0;}
#line 2530 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 140:
#line 515 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=0;}
#line 2536 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 141:
#line 516 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) =(yyval.nr) + (yyvsp[0].nr);}
#line 2542 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 142:
#line 517 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) =(yyval.nr) - (yyvsp[0].nr);}
#line 2548 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 143:
#line 518 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) =(yyval.nr) * (yyvsp[0].nr);}
#line 2554 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 144:
#line 519 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr) =(yyval.nr) /(yyvsp[0].nr);}
#line 2560 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 145:
#line 520 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=1;}
#line 2566 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 146:
#line 521 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=0;}
#line 2572 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 147:
#line 522 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=0;}
#line 2578 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 148:
#line 523 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=0;}
#line 2584 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 149:
#line 524 "lexer.y" /* yacc.c:1646  */
    {(yyval.nr)=0;}
#line 2590 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 154:
#line 537 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[0].str));}
#line 2596 "lexer.tab.c" /* yacc.c:1646  */
    break;

  case 155:
#line 538 "lexer.y" /* yacc.c:1646  */
    {var_verification((yyvsp[0].str));}
#line 2602 "lexer.tab.c" /* yacc.c:1646  */
    break;


#line 2606 "lexer.tab.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyesa, &yyes, &yyes_capacity, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        if (yychar != YYEMPTY)
          YY_LAC_ESTABLISH;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
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
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

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
  /* Fall through.  */
#endif

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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  if (yyes != yyesa)
    YYSTACK_FREE (yyes);
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 540 "lexer.y" /* yacc.c:1906  */


int yyerror(char * s){
printf("error: %s at line:%d\n",s,yylineno);
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
