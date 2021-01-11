%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "functions.h"

%}

%define parse.lac full 
%define parse.error verbose

%left ',' ';'
%left '+''-' 
%left ':''*'
%left INC DEC
%left OR
%left AND
%left '(' ')'
%left '{' '}'
%left '[' ']'
%left ASSIGN
%left '<' '>' '=' '!' 
%left '"' '#'

%start start
%token KEYWORD_IF KEYWORD_WHILE KEYWORD_ELSE KEYWORD_FOR AND OR ASSIGN KEYWORD_CLASS MAIN GHI LIBRARY EQUAL KEYWORD_INCLUDE KEYWORD_RETURN READ WRITE 

%union {
      int nr;
      char* str;
}

%token<nr> NR 
%token<str> ID KEYWORD_TYPE KEYWORD_CLASS_TYPE KEYWORD_CONST INC DEC STRCAT STRSTR STRCHR STRCMP STRLEN STRCPY EVAL 
%type<nr> expr
%type<str> type class_method function_parameter function_parameters ids
%%
start:libraries classes global KEYWORD_TYPE MAIN '{' program '}' {printf("The program is accepted\n");}
     ;

libraries:libraries library
          |library
          ;

library:'#'KEYWORD_INCLUDE'<'LIBRARY'>'  
          |'#'KEYWORD_INCLUDE GHI LIBRARY GHI
          ;        

classes:classes class 
     |class
     ;

class:KEYWORD_CLASS ID'{'class_declarations class_functions'}'          {PrintFunct("Class Methods");}
     |KEYWORD_TYPE ID':'':'ID'('')''{'function_declarations'}'
     |KEYWORD_TYPE ID':'':'ID'('function_parameters')''{'function_declarations'}'
     ;     

class_declarations:class_declarations class_declaration                 {PrintVar("Class");}
                  |class_declaration
                  ;

class_declaration:KEYWORD_CLASS_TYPE':'class_dec 
                 ;

class_dec:class_dec dec
         |dec
         |KEYWORD_TYPE ID ASSIGN NR {var_declaring($2, $1, $4, "NU");}
         ;

dec:ID ASSIGN KEYWORD_TYPE                      {var_declaring_without_init($1, $3,"NU");}
   |ID ASSIGN type                              {var_declaring_without_init($1, $3,"DA");}
   |ID'['NR']''['NR']' ASSIGN KEYWORD_TYPE      { var_declaring_without_init($1,$9,"NU");}
   |ID'['NR']' ASSIGN KEYWORD_TYPE              { var_declaring_without_init($1,$6,"NU");}
   |type ID ASSIGN NR                           {var_declaring($2, $1, $4, "DA");}
   |ID ASSIGN NR                                {var_verification($1);Assign($1,$3);}
   ; 

type:KEYWORD_CONST KEYWORD_TYPE                 {strcat($1," ");strcat($1,$2);$$=$1;}
    ;

class_functions:class_functions class_function
                |class_function
                ;

class_function:KEYWORD_CLASS_TYPE':' KEYWORD_TYPE ID'('function_parameters')''{'function_declarations'}'    {declaring_function($3,$4,$6);PrintVar("the function");}
              |KEYWORD_TYPE ID'('function_parameters')''{'function_declarations'}'                          {declaring_function($1,$2,$4);PrintVar("the function");}
              |KEYWORD_TYPE ID function_parameter                                                           {declaring_function($1,$2,$3);}
              |KEYWORD_TYPE ID function_parameter '{'function_declarations'}'                               {declaring_function($1,$2,$3);PrintVar("the function");}
              |KEYWORD_TYPE ID '('function_parameters')'                                                    {declaring_function($1,$2,$4);}
              ; 

function_parameters:function_parameters',' function_parameter       {strcat($3,";");strcat($3,$1);$$=$3;}
                   |function_parameter                              {strcat($1,";");}
                   ;   

function_parameter: ID ASSIGN KEYWORD_TYPE                          {var_declaring_without_init($1,$3,"NU");$$=$3;}
                  |ID ASSIGN type                                   {var_declaring_without_init($1,$3,"DA");$$=$3;}
                  |ID'['']' ASSIGN KEYWORD_TYPE                     {var_declaring_without_init($1,$5,"NU"); $$=$5;}      
                  |ID'['']''['']' ASSIGN KEYWORD_TYPE               {var_declaring_without_init($1,$7,"NU");$$=$7;}
                  |ID'['NR']' ASSIGN KEYWORD_TYPE                   {var_declaring_without_init($1,$6,"NU");$$=$6;}
                  |'&' ID ASSIGN KEYWORD_TYPE                       {var_declaring_without_init($2,$4,"NU"); $$=$4;}
                  |'*' ID ASSIGN KEYWORD_TYPE                       {var_declaring_without_init($2,$4,"NU"); $$=$4;}
                  |function_call                                     {$$=0;}
                  |'('')'                                           {$$=0;}
                  ;

function_call:ID ASSIGN ID '(' ids ')'                               {var_verification($1); identify_function($3,$5);}
            |ID '(' ids ')'                                        {identify_function($1,$3);}
            ;

ids:ids','ID                                                  {strcat($3,";");strcat($3,$1);$$=$3;}
    |ids','NR                                                  {$$=strdup("int;");strcat($$,$1);}
    |ID                                                           {strcat($1,";");$$=$1;}
    |NR                                                           {$$=strdup("int;");}
    ; 

op:ID                                                               {var_verification($1);}
  |NR 
  ;   

function_declarations:function_declarations function_declaration 
                     |function_declaration
                     ; 

function_declaration:declaration
            |return 
            ;

return:KEYWORD_RETURN op
      ;

global:global expression                        {PrintVar("global");}
      |global global_function                   {PrintFunct("global");}
      |expression 
      |global_function
      ;

global_function:KEYWORD_TYPE ID'('function_parameters')''{'function_declarations'}'       {declaring_function($1,$2,$4);PrintVar("the function");}
               |KEYWORD_TYPE ID function_parameter '{'function_declarations'}'            {declaring_function($1,$2,$3);PrintVar("the function");}   
               ;

program:declarations /*liniile de cod*/             {PrintVar("main");show_exp();}
       ;

declarations:declarations declaration
          |declaration
          ;

declaration:KEYWORD_IF'('conditions')' '{'instructions'}'
           |KEYWORD_ELSE'{'instructions'}'
           |KEYWORD_FOR'('content')''{'instructions'}'
           |KEYWORD_WHILE'('conditions')''{'instructions'}'
           |reading
           |printing
           |string_function 
           |expression
           |EVAL'('expr')'                          {add_arg($3);}
           ;
         
conditions:conditions logic_operator condition
          |conditions logic_operator '('condition')'
          |logic_operator condition
          |logic_operator'('condition')'
          |condition
          |'('condition')'
          ;

condition:expr arithmetic_operator expr
         |'!' '('expr arithmetic_operator expr')'
         ;

arithmetic_operator:'>''='   
                   |'<''='
                   |'!''='
                   |'>'
                   |'<' 
                   |EQUAL
                   ;

logic_operator:AND  
              |OR
              |'!'
              ;   

content:KEYWORD_TYPE ID ASSIGN NR';'cond';'ID INC               {var_declaring($2,$1,$4,"NU");var_verification($2);}
        |KEYWORD_TYPE ID ASSIGN NR';'cond';'ID DEC              {var_declaring($2,$1,$4,"NU");var_verification($2);}
        |ID ASSIGN NR ';'cond';'ID DEC                          {var_verification($1);var_verification($7);}
        |ID ASSIGN NR ';'cond';'ID INC                          {var_verification($1);var_verification($7);}
        ;

cond:   ID '>''=' expr                              {var_verification($1);Asignare($1,$4 + 1); }
        |ID '<''=' expr                             {var_verification($1);Asignare($1,$4 + 1);} 
        |ID '!''=' expr                             {var_verification($1);Asignare($1, $4);} 
        |ID'<'expr                                  {var_verification($1);Asignare($1,$3);} 
        |ID'>'expr                                  {var_verification($1);Asignare($1,$3);} 
        ;                            

instructions:instructions instruction
            |instruction
            ;  

instruction:declaration
            |return 
            ;

string_function:STRLEN'('ID')'                       {var_verification($3);}
               |STRCPY'('ID','ID')'                  {var_verification($3);var_verification($5);}
               |STRSTR'('ID','ID')'                  {var_verification($3);var_verification($5);}
               |STRCMP'('ID','ID')'                  {var_verification($3);var_verification($5);}
               |STRCHR'('ID','ID')'                  {var_verification($3);var_verification($5);}
               |STRCAT'('ID','ID')'                  {var_verification($3);var_verification($5);}
               ;

expression:ID ASSIGN expr                                   {var_verification($1);Asignare($1,$3);}
        |ID'('array')'  /* apelul pt functii void */
        |ID DEC                                             {var_verification($1);decr($1);}
        |ID INC                                             {var_verification($1);incr($1);}
        |ID ASSIGN KEYWORD_TYPE                             {var_declaring_without_init($1, $3,"NU");}
        |ID ASSIGN type                                     {var_declaring_without_init($1, $3, "DA");} 
        |KEYWORD_TYPE ID ASSIGN NR                          {var_declaring($2, $1, $4, "NU");}
        |ID '['NR']'ASSIGN KEYWORD_TYPE                     {var_declaring_without_init($1,$6,"NU");}
        |ID '['NR']'ASSIGN'/''/'array'/''/'                {var_verification($1);}
        |ID '['NR']''['NR']'ASSIGN KEYWORD_TYPE             {var_declaring_without_init($1,$9,"NU");}
        |ID '['NR']''['NR']'ASSIGN'/''/'matrix'/''/'
        |type ID ASSIGN NR                                  {var_declaring($2, $1, $4,"DA");}
        |ID ID
        |ID'.'ID'('')'
        |ID'.'ID ASSIGN op

         ;
       
array:op
     |array',' op
     ;
    
matrix:matrix',''(' matrix_elements')'
       |'('matrix_elements')'
       ;       

matrix_elements:matrix_elements','op
                |op
                ;

expr:expr'+'expr            {$$ = $1 + $3;}
    |expr'-'expr            {$$ = $1 - $3;}
    |expr'*'expr            {$$ = $1 * $3;}
    |expr':'expr            {$$ = $1 / $3;}
    |'('expr')'             {$$ =$2;}
    |NR                     {$$=$1;}
    |ID                     {var_verification($1);initialization_verify($1);$$=return_value($1);}
    |string_function         {$$=0;}
    |ID'['op']'             {$$=0;}
    |ID'['op']''['op']'     {$$=0;}
    |'+'expr                {$$ =$$ + $2;}
    |'-'expr                {$$ =$$ - $2;}
    |'*'expr                {$$ =$$ * $2;}
    |':'expr                {$$ =$$ /$2;}
    |function_call           {$$=1;}
    |ID'.'ID                {$$=0;}
    |ID'.'function_call      {$$=0;}
    |ID'.'ID'('')'          {$$=0;}
    |GHI ID GHI             {$$=0;}
    ;

reading:READ elem_reading
      ;

elem_reading:elem_reading',' ID
           |ID
           ;      

printing:WRITE elem_printing
      ;

elem_printing:elem_printing',' ID         {var_verification($3);}
           |ID                          {var_verification($1);}
           ;
%%

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