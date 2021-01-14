/* A Bison parser, made by GNU Bison 3.5.1.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

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


#line 340 "y.tab.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 461 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */



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
#endif


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
#define YYLAST   820

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  44
/* YYNRULES -- Number of rules.  */
#define YYNRULES  155
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  417

#define YYUNDEFTOK  2
#define YYMAXUTOK   287


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    23,    24,    25,     2,     2,    51,     2,
      13,    14,     8,     5,     3,     6,    53,    52,     2,     2,
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
static const yytype_int16 yyrline[] =
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
  "STRCPY", "EVAL", "'&'", "'/'", "'.'", "$accept", "start", "libraries",
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
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,    44,    59,    43,    45,    58,    42,   258,
     259,   260,   261,    40,    41,   123,   125,    91,    93,   262,
      60,    62,    61,    33,    34,    35,   263,   264,   265,   266,
     267,   268,   269,   270,   271,   272,   273,   274,   275,   276,
     277,   278,   279,   280,   281,   282,   283,   284,   285,   286,
     287,    38,    47,    46
};
# endif

#define YYPACT_NINF (-249)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -12,    -9,    31,     5,  -249,    21,  -249,    33,    47,  -249,
     111,  -249,    76,   155,   107,   137,    19,   122,   154,  -249,
     135,    89,  -249,  -249,   177,   185,   165,   207,  -249,  -249,
     142,   204,   248,  -249,   238,    67,  -249,   239,    84,  -249,
    -249,  -249,  -249,   279,   218,  -249,   250,  -249,  -249,  -249,
      78,   290,   433,   433,   433,   433,   433,   282,  -249,    35,
    -249,   306,   322,   346,   351,   366,   385,  -249,  -249,  -249,
     347,    20,   365,     4,   291,    52,   370,   393,  -249,   386,
     409,   126,   196,   402,   374,  -249,   117,  -249,   432,   142,
    -249,   310,   389,   389,  -249,  -249,   259,   416,   362,   142,
     410,   411,   412,   413,   417,   418,   426,   427,   433,   433,
     433,   433,   435,   142,   437,   454,  -249,    88,  -249,  -249,
       1,   241,   450,   743,  -249,   768,   317,   430,   106,  -249,
     431,    85,   283,  -249,   468,  -249,    43,  -249,   444,    56,
    -249,  -249,  -249,  -249,   114,   470,   463,    82,  -249,   486,
     487,   488,   489,   479,   494,   389,   389,  -249,  -249,  -249,
    -249,   473,   129,   500,   341,   491,  -249,  -249,   475,   504,
     505,   508,   506,   142,   495,   501,   502,   527,   458,  -249,
    -249,  -249,  -249,  -249,  -249,  -249,   528,   768,  -249,   522,
     233,   524,  -249,   526,     4,   534,   529,   525,   552,   162,
     550,  -249,   518,   364,  -249,   554,   362,   134,   535,   547,
     553,   555,  -249,   556,  -249,  -249,   743,   574,   560,   575,
    -249,   179,   179,   743,   377,  -249,  -249,   594,  -249,   610,
     599,   433,  -249,  -249,  -249,  -249,   601,  -249,  -249,  -249,
     581,   582,   169,   743,   197,   583,   743,   607,   608,   142,
    -249,  -249,   142,   175,  -249,   625,   630,   631,   632,   633,
     484,   629,  -249,   612,  -249,  -249,   293,  -249,   182,  -249,
     338,   342,   189,  -249,  -249,   510,  -249,   646,   609,   656,
     634,   635,   263,   349,  -249,  -249,   657,   536,   129,   658,
     562,   743,   156,    11,   655,  -249,  -249,  -249,  -249,  -249,
    -249,  -249,   638,  -249,   678,   682,   297,   433,   683,  -249,
     367,   293,  -249,   675,   677,   679,  -249,   433,   685,  -249,
    -249,   684,   686,   702,  -249,  -249,  -249,   687,   681,   743,
    -249,   201,  -249,   588,  -249,   672,   673,  -249,  -249,  -249,
     342,   743,   293,  -249,   713,  -249,  -249,  -249,   347,   743,
     727,   704,   743,   730,  -249,   614,   734,  -249,   737,  -249,
     433,   640,   738,  -249,   666,   711,   749,   692,   741,  -249,
     743,   142,    12,   307,  -249,  -249,  -249,   368,   753,   711,
    -249,   732,   718,  -249,   217,   761,   723,  -249,   387,   415,
     754,   742,   773,  -249,  -249,   142,  -249,   142,  -249,   433,
     347,   433,   347,   433,   420,   745,  -249,   237,   347,   347,
     347,  -249,  -249,   434,  -249,  -249,  -249
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
       0,   117,     0,     0,    44,   139,     0,     0,     0,     0,
       0,     0,   104,     0,    40,    32,     0,     0,     0,     0,
      39,     0,     0,     0,     0,    55,   152,   150,   155,   153,
       0,     0,    61,    51,     2,    63,     0,    23,    18,    19,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      46,    45,     0,     0,   148,     0,     0,     0,     0,     0,
       0,     0,    36,     0,    89,    88,     0,    90,     0,    78,
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
    -249,  -249,  -249,   775,  -249,   788,  -249,   755,  -249,   674,
     -22,  -249,   714,  -128,   -19,   -31,   595,   -88,  -209,  -176,
    -214,  -249,   782,  -249,  -249,  -119,   585,  -221,   464,  -225,
    -249,   440,  -103,  -248,  -120,   242,   561,  -249,   423,   -32,
    -249,  -249,  -249,  -249
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
      70,   137,   233,   182,    78,   182,   188,   260,   199,   273,
      67,   145,    72,     1,    89,   385,    77,   115,   116,   164,
      92,    93,    94,    95,    96,   160,     5,   320,    28,    29,
       1,     6,    30,   112,   287,     7,    31,   290,    32,   113,
     165,    12,    78,   310,    75,   305,     8,   310,    98,   312,
      78,    72,    99,    13,   100,    76,   115,   198,   182,    33,
     130,   273,    77,   336,   386,    98,   242,   182,   235,   120,
     148,   121,    34,    14,    27,    72,   155,   156,   157,   158,
      73,    89,   333,    75,   233,   225,    74,    15,   101,   343,
     344,   162,    90,    72,    76,   207,   182,   201,   194,   167,
      78,   100,   163,   182,   274,    78,   130,    75,   202,    24,
     130,   233,   195,   320,   233,    80,   320,   203,    76,   320,
     355,   362,    26,   182,    81,    75,   182,   273,   204,    16,
      38,    78,    18,   133,    72,   273,    76,    72,   273,    73,
     182,     7,   115,   215,    27,    74,   126,   273,   254,    18,
     273,    16,    17,   273,    18,   182,   274,   233,    83,   134,
     331,   382,    35,    78,   294,   162,    75,   182,   239,    75,
     182,   182,   162,   142,   143,    37,   247,    76,   203,   233,
      76,    47,    48,   286,    52,    53,    54,    55,    25,   295,
     264,   265,   266,   264,   265,    36,   308,   334,    41,   282,
     264,   265,   267,   318,   162,   309,   233,    43,   335,   182,
     288,    57,   309,   182,    46,   356,   240,    42,    58,    59,
     395,   182,   274,    61,    62,    63,    64,    65,    66,   182,
     274,   396,   182,   274,   306,   182,   126,   127,   361,    18,
     395,   182,   274,    51,   182,   274,   364,   182,   274,   367,
     182,   414,    23,    52,    53,    54,    55,    78,    79,    83,
      84,    56,   182,    40,   108,   109,   110,   111,   108,   109,
     110,   111,   237,   140,   238,   340,    18,   326,    71,   306,
      57,   146,   166,   383,    18,   348,    82,    58,    59,    60,
      88,    18,    61,    62,    63,    64,    65,    66,    52,    53,
      54,    55,   108,   109,   110,   111,    56,   406,    91,   383,
     306,   140,   108,   109,   110,   111,   304,   313,   314,   102,
     315,   387,    97,   126,   196,    57,    18,   138,   373,   139,
     119,   316,    58,    59,   189,   103,   190,    61,    62,    63,
      64,    65,    66,    52,    53,    54,    55,   108,   109,   110,
     111,   311,   108,   109,   110,   111,   400,   402,   217,   104,
     218,   304,   313,   314,   105,   315,   327,   408,   328,   409,
      57,   410,    52,    53,    54,    55,   316,    58,    59,   106,
     342,   132,    61,    62,    63,    64,    65,    66,   388,   389,
     304,   390,    52,    53,    54,    55,   110,   111,   107,    57,
      56,   142,   143,   250,   251,   114,    58,    59,   123,   399,
     122,    61,    62,    63,    64,    65,    66,   277,   278,    57,
      52,    53,    54,    55,   125,   124,    58,    59,    56,   411,
     412,    61,    62,    63,    64,    65,    66,   401,    52,    53,
      54,    55,   131,   415,   416,   136,    56,    57,   141,   159,
     146,   147,   149,   150,    58,    59,   161,   151,   152,    61,
      62,    63,    64,    65,    66,    57,   153,   154,   116,   168,
     191,   193,    58,    59,   232,   197,   206,    61,    62,    63,
      64,    65,    66,   200,   169,   170,   171,   172,   205,   208,
     209,   210,   211,   212,   173,   174,   175,   213,    16,   176,
     301,    18,    61,    62,    63,    64,    65,    66,   177,   219,
     169,   170,   171,   172,   214,   216,   220,   221,   222,   224,
     173,   174,   175,   223,    16,   176,   319,    18,    61,    62,
      63,    64,    65,    66,   177,   226,   169,   170,   171,   172,
     231,   228,   230,   240,   234,   241,   173,   174,   175,   243,
      16,   176,   330,    18,    61,    62,    63,    64,    65,    66,
     177,   236,   169,   170,   171,   172,   245,   246,   248,   244,
     249,   252,   173,   174,   175,   255,    16,   176,   332,    18,
      61,    62,    63,    64,    65,    66,   177,   256,   169,   170,
     171,   172,   261,   257,   263,   258,   259,   280,   173,   174,
     175,   262,    16,   176,   357,    18,    61,    62,    63,    64,
      65,    66,   177,   281,   169,   170,   171,   172,    74,   283,
     284,   285,   291,   289,   173,   174,   175,   292,    16,   176,
     369,    18,    61,    62,    63,    64,    65,    66,   177,   296,
     169,   170,   171,   172,   297,   298,   299,   300,   302,   322,
     173,   174,   175,   303,    16,   176,   374,    18,    61,    62,
      63,    64,    65,    66,   177,   321,   169,   170,   171,   172,
     323,   288,   329,   337,   324,   325,   173,   174,   175,   338,
      16,   176,   376,    18,    61,    62,    63,    64,    65,    66,
     177,   307,   169,   170,   171,   172,   339,   345,   341,   346,
     349,   347,   173,   174,   175,   351,    16,   176,   380,    18,
      61,    62,    63,    64,    65,    66,   177,   352,   169,   170,
     171,   172,   354,   350,   358,   359,   353,   363,   173,   174,
     175,   365,    16,   176,   394,    18,    61,    62,    63,    64,
      65,    66,   177,   366,   169,   170,   171,   172,   368,   370,
     371,   377,   375,   379,   173,   174,   175,   391,    16,   176,
     381,    18,    61,    62,    63,    64,    65,    66,   177,   169,
     170,   171,   172,   393,   397,   398,   403,   405,     9,   173,
     174,   175,   404,    16,   176,   413,    18,    61,    62,    63,
      64,    65,    66,   177,   169,   170,   171,   172,    19,    85,
     135,   253,   192,    39,   360,   174,   175,   272,    16,   176,
     293,    18,    61,    62,    63,    64,    65,    66,   177,   392,
     407
};

static const yytype_int16 yycheck[] =
{
      32,    89,   178,   123,    35,   125,   125,   216,   136,   223,
      32,    99,     8,    25,     3,     3,    35,    13,    14,    18,
      52,    53,    54,    55,    56,   113,    35,   275,     9,    10,
      25,     0,    13,    13,   243,    30,    17,   246,    19,    19,
      39,    20,    73,   268,    40,   266,    41,   272,    13,   270,
      81,     8,    17,    32,    19,    51,    13,    14,   178,    40,
      82,   275,    81,    52,    52,    13,   194,   187,   187,    17,
     101,    19,    53,    40,     7,     8,   108,   109,   110,   111,
      13,     3,   291,    40,   260,   173,    19,    40,    53,   310,
     311,     3,    14,     8,    51,    13,   216,    41,    13,   121,
     131,    19,    14,   223,   223,   136,   128,    40,    52,    33,
     132,   287,   131,   361,   290,    31,   364,     3,    51,   367,
     329,   342,    15,   243,    40,    40,   246,   341,    14,    40,
      41,   162,    43,    16,     8,   349,    51,     8,   352,    13,
     260,    30,    13,   162,     7,    19,    40,   361,    14,    43,
     364,    40,    41,   367,    43,   275,   275,   333,    41,    42,
     288,   370,    40,   194,   252,     3,    40,   287,   190,    40,
     290,   291,     3,    39,    40,    40,    14,    51,     3,   355,
      51,    39,    40,    14,     5,     6,     7,     8,    33,    14,
      11,    12,    13,    11,    12,    41,    14,    41,    21,   231,
      11,    12,    23,    14,     3,    23,   382,    42,    52,   329,
      13,    32,    23,   333,     7,    14,    19,    32,    39,    40,
       3,   341,   341,    44,    45,    46,    47,    48,    49,   349,
     349,    14,   352,   352,   266,   355,    40,    41,   341,    43,
       3,   361,   361,    39,   364,   364,   349,   367,   367,   352,
     370,    14,    10,     5,     6,     7,     8,   288,    19,    41,
      42,    13,   382,    21,     5,     6,     7,     8,     5,     6,
       7,     8,    39,    14,    41,   307,    43,    14,    40,   311,
      32,    40,    41,   371,    43,   317,     7,    39,    40,    41,
      40,    43,    44,    45,    46,    47,    48,    49,     5,     6,
       7,     8,     5,     6,     7,     8,    13,   395,    18,   397,
     342,    14,     5,     6,     7,     8,    23,    20,    21,    13,
      23,    14,    40,    40,    41,    32,    43,    17,   360,    19,
      39,    34,    39,    40,    17,    13,    19,    44,    45,    46,
      47,    48,    49,     5,     6,     7,     8,     5,     6,     7,
       8,    13,     5,     6,     7,     8,   388,   389,    17,    13,
      19,    23,    20,    21,    13,    23,    17,   399,    19,   401,
      32,   403,     5,     6,     7,     8,    34,    39,    40,    13,
      13,     7,    44,    45,    46,    47,    48,    49,    20,    21,
      23,    23,     5,     6,     7,     8,     7,     8,    13,    32,
      13,    39,    40,    39,    40,    40,    39,    40,    15,    22,
      40,    44,    45,    46,    47,    48,    49,    40,    41,    32,
       5,     6,     7,     8,    15,    39,    39,    40,    13,     9,
      10,    44,    45,    46,    47,    48,    49,    22,     5,     6,
       7,     8,    40,     9,    10,    13,    13,    32,    32,    14,
      40,    40,    40,    40,    39,    40,    19,    40,    40,    44,
      45,    46,    47,    48,    49,    32,    40,    40,    14,    19,
      40,    40,    39,    40,    16,     7,    13,    44,    45,    46,
      47,    48,    49,    39,    26,    27,    28,    29,    18,     3,
       3,     3,     3,    14,    36,    37,    38,     3,    40,    41,
      16,    43,    44,    45,    46,    47,    48,    49,    50,    18,
      26,    27,    28,    29,    41,    15,    41,    13,    13,    13,
      36,    37,    38,    15,    40,    41,    16,    43,    44,    45,
      46,    47,    48,    49,    50,    40,    26,    27,    28,    29,
      13,    40,    40,    19,    16,    19,    36,    37,    38,    15,
      40,    41,    16,    43,    44,    45,    46,    47,    48,    49,
      50,    39,    26,    27,    28,    29,    41,    15,    18,    40,
      52,    17,    36,    37,    38,    40,    40,    41,    16,    43,
      44,    45,    46,    47,    48,    49,    50,    40,    26,    27,
      28,    29,    18,    40,    19,    40,    40,     3,    36,    37,
      38,    41,    40,    41,    16,    43,    44,    45,    46,    47,
      48,    49,    50,     3,    26,    27,    28,    29,    19,    18,
      39,    39,    15,    40,    36,    37,    38,    19,    40,    41,
      16,    43,    44,    45,    46,    47,    48,    49,    50,    14,
      26,    27,    28,    29,    14,    14,    14,    14,    19,    40,
      36,    37,    38,    41,    40,    41,    16,    43,    44,    45,
      46,    47,    48,    49,    50,    19,    26,    27,    28,    29,
      14,    13,    15,    18,    40,    40,    36,    37,    38,    41,
      40,    41,    16,    43,    44,    45,    46,    47,    48,    49,
      50,    13,    26,    27,    28,    29,    14,    22,    15,    22,
      15,    22,    36,    37,    38,    19,    40,    41,    16,    43,
      44,    45,    46,    47,    48,    49,    50,    15,    26,    27,
      28,    29,    41,    39,    52,    52,    39,    14,    36,    37,
      38,     4,    40,    41,    16,    43,    44,    45,    46,    47,
      48,    49,    50,    39,    26,    27,    28,    29,    18,    15,
      13,    40,    14,     4,    36,    37,    38,     4,    40,    41,
      19,    43,    44,    45,    46,    47,    48,    49,    50,    26,
      27,    28,    29,    41,    13,    52,    22,     4,     3,    36,
      37,    38,    40,    40,    41,    40,    43,    44,    45,    46,
      47,    48,    49,    50,    26,    27,    28,    29,    10,    44,
      86,   206,   128,    21,   340,    37,    38,   222,    40,    41,
     249,    43,    44,    45,    46,    47,    48,    49,    50,   379,
     397
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    55,    56,    57,    35,     0,    30,    41,    57,
      58,    59,    20,    32,    40,    40,    40,    41,    43,    59,
      64,    75,    76,    89,    33,    33,    15,     7,     9,    10,
      13,    17,    19,    40,    53,    40,    41,    40,    41,    76,
      89,    21,    32,    42,    60,    61,     7,    39,    40,    71,
      90,    39,     5,     6,     7,     8,    13,    32,    39,    40,
      41,    44,    45,    46,    47,    48,    49,    64,    69,    88,
      93,    40,     8,    13,    19,    40,    51,    68,    69,    19,
      31,    40,     7,    41,    42,    61,    65,    66,    40,     3,
      14,    18,    93,    93,    93,    93,    93,    40,    13,    17,
      19,    53,    13,    13,    13,    13,    13,    13,     5,     6,
       7,     8,    13,    19,    40,    13,    14,    67,    68,    39,
      17,    19,    40,    15,    39,    15,    40,    41,    62,    63,
      64,    40,     7,    16,    42,    66,    13,    71,    17,    19,
      14,    32,    39,    40,    70,    71,    40,    40,    69,    40,
      40,    40,    40,    40,    40,    93,    93,    93,    93,    14,
      71,    19,     3,    14,    18,    39,    41,    64,    19,    26,
      27,    28,    29,    36,    37,    38,    41,    50,    72,    73,
      74,    79,    88,    89,    94,    96,    77,    78,    79,    17,
      19,    40,    63,    40,    13,    68,    41,     7,    14,    67,
      39,    41,    52,     3,    14,    18,    13,    13,     3,     3,
       3,     3,    14,     3,    41,    68,    15,    17,    19,    18,
      41,    13,    13,    15,    13,    71,    40,    95,    40,    97,
      40,    13,    16,    73,    16,    79,    39,    39,    41,    64,
      19,    19,    67,    15,    40,    41,    15,    14,    18,    52,
      39,    40,    17,    70,    14,    40,    40,    40,    40,    40,
      72,    18,    41,    19,    11,    12,    13,    23,    80,    81,
      83,    93,    80,    74,    79,    86,    87,    40,    41,    84,
       3,     3,    93,    18,    39,    39,    14,    72,    13,    40,
      72,    15,    19,    90,    71,    14,    14,    14,    14,    14,
      14,    16,    19,    41,    23,    81,    93,    13,    14,    23,
      83,    13,    81,    20,    21,    23,    34,    82,    14,    16,
      87,    19,    40,    14,    40,    40,    14,    17,    19,    15,
      16,    67,    16,    72,    41,    52,    52,    18,    41,    14,
      93,    15,    13,    81,    81,    22,    22,    22,    93,    15,
      39,    19,    15,    39,    41,    72,    14,    16,    52,    52,
      82,    86,    81,    14,    86,     4,    39,    86,    18,    16,
      15,    13,    91,    93,    16,    14,    16,    40,    85,     4,
      16,    19,    72,    71,    92,     3,    52,    14,    20,    21,
      23,     4,    85,    41,    16,     3,    14,    13,    52,    22,
      93,    22,    93,    22,    40,     4,    71,    92,    93,    93,
      93,     9,    10,    40,    14,     9,    10
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


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
          return 1;
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
yy_lac (yy_state_t *yyesa, yy_state_t **yyes,
        YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, int yytoken)
{
  yy_state_t *yyes_prev = yyssp;
  yy_state_t *yyesp = yyes_prev;
  YYDPRINTF ((stderr, "LAC: checking lookahead %s:", yytname[yytoken]));
  if (yytoken == YYUNDEFTOK)
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
          yyrule = yydefact[+*yyesp];
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
        YYPTRDIFF_T yylen = yyr2[yyrule];
        YYDPRINTF ((stderr, " R%d", yyrule - 1));
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
                yylen -= yysize;
                yyesp = yyes_prev;
              }
          }
        if (yylen)
          yyesp = yyes_prev -= yylen;
      }
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
                return 2;
              }
            YY_IGNORE_USELESS_CAST_BEGIN
            *++yyesp = YY_CAST (yy_state_t, yystate);
            YY_IGNORE_USELESS_CAST_END
          }
        YYDPRINTF ((stderr, " G%d", yystate));
      }
    }
}


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyesa, yy_state_t **yyes,
                YYPTRDIFF_T *yyes_capacity, yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
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
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

    yy_state_t yyesa[20];
    yy_state_t *yyes;
    YYPTRDIFF_T yyes_capacity;

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
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  yyes = yyesa;
  yyes_capacity = 20;
  if (YYMAXDEPTH < yyes_capacity)
    yyes_capacity = YYMAXDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
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
# undef YYSTACK_RELOCATE
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
  case 2:
#line 300 "lexer.y"
                                                                 {printf("The program is accepted\n");}
#line 2223 "y.tab.c"
    break;

  case 9:
#line 315 "lexer.y"
                                                                        {PrintFunct("Class Methods");}
#line 2229 "y.tab.c"
    break;

  case 12:
#line 320 "lexer.y"
                                                                        {PrintVar("Class");}
#line 2235 "y.tab.c"
    break;

  case 17:
#line 329 "lexer.y"
                                    {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "NOPE");}
#line 2241 "y.tab.c"
    break;

  case 18:
#line 332 "lexer.y"
                                                {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"NOPE");}
#line 2247 "y.tab.c"
    break;

  case 19:
#line 333 "lexer.y"
                                                {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"YES");}
#line 2253 "y.tab.c"
    break;

  case 20:
#line 334 "lexer.y"
                                                { var_declaring_without_init((yyvsp[-8].str),(yyvsp[0].str),"NOPE");}
#line 2259 "y.tab.c"
    break;

  case 21:
#line 335 "lexer.y"
                                                { var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");}
#line 2265 "y.tab.c"
    break;

  case 22:
#line 336 "lexer.y"
                                                {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "YES");}
#line 2271 "y.tab.c"
    break;

  case 23:
#line 337 "lexer.y"
                                                {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2277 "y.tab.c"
    break;

  case 24:
#line 340 "lexer.y"
                                                {strcat((yyvsp[-1].str)," ");strcat((yyvsp[-1].str),(yyvsp[0].str));(yyval.str)=(yyvsp[-1].str);}
#line 2283 "y.tab.c"
    break;

  case 27:
#line 347 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2289 "y.tab.c"
    break;

  case 28:
#line 348 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2295 "y.tab.c"
    break;

  case 29:
#line 349 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-2].str),(yyvsp[-1].str),(yyvsp[0].str));}
#line 2301 "y.tab.c"
    break;

  case 30:
#line 350 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-5].str),(yyvsp[-4].str),(yyvsp[-3].str));PrintVar("the function");}
#line 2307 "y.tab.c"
    break;

  case 31:
#line 351 "lexer.y"
                                                                                                            {declaring_function((yyvsp[-4].str),(yyvsp[-3].str),(yyvsp[-1].str));}
#line 2313 "y.tab.c"
    break;

  case 32:
#line 354 "lexer.y"
                                                                    {strcat((yyvsp[0].str),";");strcat((yyvsp[0].str),(yyvsp[-2].str));(yyval.str)=(yyvsp[0].str);}
#line 2319 "y.tab.c"
    break;

  case 33:
#line 355 "lexer.y"
                                                                    {strcat((yyvsp[0].str),";");}
#line 2325 "y.tab.c"
    break;

  case 34:
#line 358 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2331 "y.tab.c"
    break;

  case 35:
#line 359 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"YES");(yyval.str)=(yyvsp[0].str);}
#line 2337 "y.tab.c"
    break;

  case 36:
#line 360 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-4].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2343 "y.tab.c"
    break;

  case 37:
#line 361 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-6].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2349 "y.tab.c"
    break;

  case 38:
#line 362 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");(yyval.str)=(yyvsp[0].str);}
#line 2355 "y.tab.c"
    break;

  case 39:
#line 363 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2361 "y.tab.c"
    break;

  case 40:
#line 364 "lexer.y"
                                                                    {var_declaring_without_init((yyvsp[-2].str),(yyvsp[0].str),"NOPE"); (yyval.str)=(yyvsp[0].str);}
#line 2367 "y.tab.c"
    break;

  case 41:
#line 365 "lexer.y"
                                                                     {(yyval.str)=0;}
#line 2373 "y.tab.c"
    break;

  case 42:
#line 366 "lexer.y"
                                                                    {(yyval.str)=0;}
#line 2379 "y.tab.c"
    break;

  case 43:
#line 369 "lexer.y"
                                                                     {var_verification((yyvsp[-5].str)); identify_function((yyvsp[-3].str),(yyvsp[-1].str));}
#line 2385 "y.tab.c"
    break;

  case 44:
#line 370 "lexer.y"
                                                                   {identify_function((yyvsp[-3].str),(yyvsp[-1].str));}
#line 2391 "y.tab.c"
    break;

  case 45:
#line 373 "lexer.y"
                                                              {strcat((yyvsp[0].str),";");strcat((yyvsp[0].str),(yyvsp[-2].str));(yyval.str)=(yyvsp[0].str);}
#line 2397 "y.tab.c"
    break;

  case 46:
#line 374 "lexer.y"
                                                               {(yyval.str)=strdup("int;");strcat((yyval.str),(yyvsp[-2].str));}
#line 2403 "y.tab.c"
    break;

  case 47:
#line 375 "lexer.y"
                                                                  {strcat((yyvsp[0].str),";");(yyval.str)=(yyvsp[0].str);}
#line 2409 "y.tab.c"
    break;

  case 48:
#line 376 "lexer.y"
                                                                  {(yyval.str)=strdup("int;");}
#line 2415 "y.tab.c"
    break;

  case 49:
#line 379 "lexer.y"
                                                                    {var_verification((yyvsp[0].str));}
#line 2421 "y.tab.c"
    break;

  case 56:
#line 394 "lexer.y"
                                                {PrintVar("global");}
#line 2427 "y.tab.c"
    break;

  case 57:
#line 395 "lexer.y"
                                                {PrintFunct("global");}
#line 2433 "y.tab.c"
    break;

  case 60:
#line 400 "lexer.y"
                                                                                          {declaring_function((yyvsp[-7].str),(yyvsp[-6].str),(yyvsp[-4].str));PrintVar("the function");}
#line 2439 "y.tab.c"
    break;

  case 61:
#line 401 "lexer.y"
                                                                                          {declaring_function((yyvsp[-5].str),(yyvsp[-4].str),(yyvsp[-3].str));PrintVar("the function");}
#line 2445 "y.tab.c"
    break;

  case 62:
#line 404 "lexer.y"
                                                    {PrintVar("main");show_exp();}
#line 2451 "y.tab.c"
    break;

  case 73:
#line 419 "lexer.y"
                                                    {add_arg((yyvsp[-1].nr));}
#line 2457 "y.tab.c"
    break;

  case 91:
#line 447 "lexer.y"
                                                                {var_declaring((yyvsp[-7].str),(yyvsp[-8].str),(yyvsp[-5].nr),"NOPE");var_verification((yyvsp[-7].str));incr((yyvsp[-8].str));}
#line 2463 "y.tab.c"
    break;

  case 92:
#line 448 "lexer.y"
                                                                {var_declaring((yyvsp[-7].str),(yyvsp[-8].str),(yyvsp[-5].nr),"NOPE");var_verification((yyvsp[-7].str));decr((yyvsp[-8].str));}
#line 2469 "y.tab.c"
    break;

  case 93:
#line 449 "lexer.y"
                                                                {var_verification((yyvsp[-7].str));var_verification((yyvsp[-1].str));Assign((yyvsp[-7].str),(yyvsp[-5].nr));decr((yyvsp[-7].str));}
#line 2475 "y.tab.c"
    break;

  case 94:
#line 450 "lexer.y"
                                                                {var_verification((yyvsp[-7].str));var_verification((yyvsp[-1].str));Assign((yyvsp[-7].str),(yyvsp[-5].nr));incr((yyvsp[-7].str));}
#line 2481 "y.tab.c"
    break;

  case 95:
#line 453 "lexer.y"
                                                    {var_verification((yyvsp[-3].str)); }
#line 2487 "y.tab.c"
    break;

  case 96:
#line 454 "lexer.y"
                                                    {var_verification((yyvsp[-3].str)); }
#line 2493 "y.tab.c"
    break;

  case 97:
#line 455 "lexer.y"
                                                    {var_verification((yyvsp[-3].str)); }
#line 2499 "y.tab.c"
    break;

  case 98:
#line 456 "lexer.y"
                                                    {var_verification((yyvsp[-2].str)); }
#line 2505 "y.tab.c"
    break;

  case 99:
#line 457 "lexer.y"
                                                    {var_verification((yyvsp[-2].str)); }
#line 2511 "y.tab.c"
    break;

  case 104:
#line 468 "lexer.y"
                                                     {var_verification((yyvsp[-1].str));}
#line 2517 "y.tab.c"
    break;

  case 105:
#line 469 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2523 "y.tab.c"
    break;

  case 106:
#line 470 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2529 "y.tab.c"
    break;

  case 107:
#line 471 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2535 "y.tab.c"
    break;

  case 108:
#line 472 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2541 "y.tab.c"
    break;

  case 109:
#line 473 "lexer.y"
                                                     {var_verification((yyvsp[-3].str));var_verification((yyvsp[-1].str));}
#line 2547 "y.tab.c"
    break;

  case 110:
#line 476 "lexer.y"
                                                            {var_verification((yyvsp[-2].str));Assign((yyvsp[-2].str),(yyvsp[0].nr));}
#line 2553 "y.tab.c"
    break;

  case 112:
#line 478 "lexer.y"
                                                            {var_verification((yyvsp[-1].str));decr((yyvsp[-1].str));}
#line 2559 "y.tab.c"
    break;

  case 113:
#line 479 "lexer.y"
                                                            {var_verification((yyvsp[-1].str));incr((yyvsp[-1].str));}
#line 2565 "y.tab.c"
    break;

  case 114:
#line 480 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str),"NOPE");}
#line 2571 "y.tab.c"
    break;

  case 115:
#line 481 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-2].str), (yyvsp[0].str), "YES");}
#line 2577 "y.tab.c"
    break;

  case 116:
#line 482 "lexer.y"
                                                            {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr), "NOPE");}
#line 2583 "y.tab.c"
    break;

  case 117:
#line 483 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-5].str),(yyvsp[0].str),"NOPE");}
#line 2589 "y.tab.c"
    break;

  case 118:
#line 484 "lexer.y"
                                                            {var_verification((yyvsp[-9].str));}
#line 2595 "y.tab.c"
    break;

  case 119:
#line 485 "lexer.y"
                                                            {var_declaring_without_init((yyvsp[-8].str),(yyvsp[0].str),"NOPE");}
#line 2601 "y.tab.c"
    break;

  case 121:
#line 487 "lexer.y"
                                                            {var_declaring((yyvsp[-2].str), (yyvsp[-3].str), (yyvsp[0].nr),"YES");}
#line 2607 "y.tab.c"
    break;

  case 131:
#line 506 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) + (yyvsp[0].nr);}
#line 2613 "y.tab.c"
    break;

  case 132:
#line 507 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) - (yyvsp[0].nr);}
#line 2619 "y.tab.c"
    break;

  case 133:
#line 508 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) * (yyvsp[0].nr);}
#line 2625 "y.tab.c"
    break;

  case 134:
#line 509 "lexer.y"
                            {(yyval.nr) = (yyvsp[-2].nr) / (yyvsp[0].nr);}
#line 2631 "y.tab.c"
    break;

  case 135:
#line 510 "lexer.y"
                            {(yyval.nr) =(yyvsp[-1].nr);}
#line 2637 "y.tab.c"
    break;

  case 136:
#line 511 "lexer.y"
                            {(yyval.nr)=(yyvsp[0].nr);}
#line 2643 "y.tab.c"
    break;

  case 137:
#line 512 "lexer.y"
                            {var_verification((yyvsp[0].str));initialization_verify((yyvsp[0].str));(yyval.nr)=return_value((yyvsp[0].str));}
#line 2649 "y.tab.c"
    break;

  case 138:
#line 513 "lexer.y"
                             {(yyval.nr)=0;}
#line 2655 "y.tab.c"
    break;

  case 139:
#line 514 "lexer.y"
                            {(yyval.nr)=0;}
#line 2661 "y.tab.c"
    break;

  case 140:
#line 515 "lexer.y"
                            {(yyval.nr)=0;}
#line 2667 "y.tab.c"
    break;

  case 141:
#line 516 "lexer.y"
                            {(yyval.nr) =(yyval.nr) + (yyvsp[0].nr);}
#line 2673 "y.tab.c"
    break;

  case 142:
#line 517 "lexer.y"
                            {(yyval.nr) =(yyval.nr) - (yyvsp[0].nr);}
#line 2679 "y.tab.c"
    break;

  case 143:
#line 518 "lexer.y"
                            {(yyval.nr) =(yyval.nr) * (yyvsp[0].nr);}
#line 2685 "y.tab.c"
    break;

  case 144:
#line 519 "lexer.y"
                            {(yyval.nr) =(yyval.nr) /(yyvsp[0].nr);}
#line 2691 "y.tab.c"
    break;

  case 145:
#line 520 "lexer.y"
                             {(yyval.nr)=1;}
#line 2697 "y.tab.c"
    break;

  case 146:
#line 521 "lexer.y"
                            {(yyval.nr)=0;}
#line 2703 "y.tab.c"
    break;

  case 147:
#line 522 "lexer.y"
                             {(yyval.nr)=0;}
#line 2709 "y.tab.c"
    break;

  case 148:
#line 523 "lexer.y"
                            {(yyval.nr)=0;}
#line 2715 "y.tab.c"
    break;

  case 149:
#line 524 "lexer.y"
                            {(yyval.nr)=0;}
#line 2721 "y.tab.c"
    break;

  case 154:
#line 537 "lexer.y"
                                          {var_verification((yyvsp[0].str));}
#line 2727 "y.tab.c"
    break;

  case 155:
#line 538 "lexer.y"
                                        {var_verification((yyvsp[0].str));}
#line 2733 "y.tab.c"
    break;


#line 2737 "y.tab.c"

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
                  yystos[+*yyssp], yyvsp);
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
#line 540 "lexer.y"




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
