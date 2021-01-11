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
start:libraries classes global KEYWORD_TYPE MAIN '{' program '}' {printf("programul este acceptat\n");}
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

class:KEYWORD_CLASS ID'{'class_declarations class_functions'}'          {AfisareFunctii("metode clasa");}
     |KEYWORD_TYPE ID':'':'ID'('')''{'function_declarations'}'
     |KEYWORD_TYPE ID':'':'ID'('function_parameters')''{'function_declarations'}'
     ;     

class_declarations:class_declarations class_declaration                 {AfisareVariabile("clasa");}
                  |class_declaration
                  ;

class_declaration:KEYWORD_CLASS_TYPE':'class_dec 
                 ;

class_dec:class_dec dec
         |dec
         |KEYWORD_TYPE ID ASSIGN NR {declarare_variabila($2, $1, $4, "NU");}
         ;

dec:ID ASSIGN KEYWORD_TYPE                      {declarare_variabila_fara_init($1, $3,"NU");}
   |ID ASSIGN type                              {declarare_variabila_fara_init($1, $3,"DA");}
   |ID'['NR']''['NR']' ASSIGN KEYWORD_TYPE      { declarare_variabila_fara_init($1,$9,"NU");}
   |ID'['NR']' ASSIGN KEYWORD_TYPE              { declarare_variabila_fara_init($1,$6,"NU");}
   |type ID ASSIGN NR                           {declarare_variabila($2, $1, $4, "DA");}
   |ID ASSIGN NR                                {identificare_variabila($1);Asignare($1,$3);}
   ; 

type:KEYWORD_CONST KEYWORD_TYPE                 {strcat($1," ");strcat($1,$2);$$=$1;}
    ;

class_functions:class_functions class_function
                |class_function
                ;

class_function:KEYWORD_CLASS_TYPE':' KEYWORD_TYPE ID'('function_parameters')''{'function_declarations'}'    {declarare_functie($3,$4,$6);AfisareVariabile("in interiorul unei functii");}
              |KEYWORD_TYPE ID'('function_parameters')''{'function_declarations'}'                          {declarare_functie($1,$2,$4);AfisareVariabile("in interiorul unei functii");}
              |KEYWORD_TYPE ID function_parameter                                                           {declarare_functie($1,$2,$3);}
              |KEYWORD_TYPE ID function_parameter '{'function_declarations'}'                               {declarare_functie($1,$2,$3);AfisareVariabile("in interiorul unei functii");}
              |KEYWORD_TYPE ID '('function_parameters')'                                                    {declarare_functie($1,$2,$4);}
              ; 

function_parameters:function_parameters',' function_parameter       {strcat($3,";");strcat($3,$1);$$=$3;}
                   |function_parameter                              {strcat($1,";");}
                   ;   

function_parameter: ID ASSIGN KEYWORD_TYPE                          {declarare_variabila_fara_init($1,$3,"NU");$$=$3;}
                  |ID ASSIGN type                                   {declarare_variabila_fara_init($1,$3,"DA");$$=$3;}
                  |ID'['']' ASSIGN KEYWORD_TYPE                     {declarare_variabila_fara_init($1,$5,"NU"); $$=$5;}      
                  |ID'['']''['']' ASSIGN KEYWORD_TYPE               {declarare_variabila_fara_init($1,$7,"NU");$$=$7;}
                  |ID'['NR']' ASSIGN KEYWORD_TYPE                   {declarare_variabila_fara_init($1,$6,"NU");$$=$6;}
                  |'&' ID ASSIGN KEYWORD_TYPE                       {declarare_variabila_fara_init($2,$4,"NU"); $$=$4;}
                  |'*' ID ASSIGN KEYWORD_TYPE                       {declarare_variabila_fara_init($2,$4,"NU"); $$=$4;}
                  |function_call                                     {$$=0;}
                  |'('')'                                           {$$=0;}
                  ;

function_call:ID ASSIGN ID '(' ids ')'                               {identificare_variabila($1); identificare_functie($3,$5);}
            |ID '(' ids ')'                                        {identificare_functie($1,$3);}
            ;

ids:ids','ID                                                  {strcat($3,";");strcat($3,$1);$$=$3;}
    |ids','NR                                                  {$$=strdup("int;");strcat($$,$1);}
    |ID                                                           {strcat($1,";");$$=$1;}
    |NR                                                           {$$=strdup("int;");}
    ; 

op:ID                                                               {identificare_variabila($1);}
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

global:global expression                        {AfisareVariabile("global");}
      |global global_function                   {AfisareFunctii("global");}
      |expression 
      |global_function
      ;

global_function:KEYWORD_TYPE ID'('function_parameters')''{'function_declarations'}'       {declarare_functie($1,$2,$4);AfisareVariabile("in interiorul unei functii");}
               |KEYWORD_TYPE ID function_parameter '{'function_declarations'}'            {declarare_functie($1,$2,$3);AfisareVariabile("in interiorul unei functii");}   
               ;

program:declarations /*liniile de cod*/             {AfisareVariabile("main");Afisare_expresie();}
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
           |EVAL'('expr')'                          {Adaugare_argument($3);}
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

content:KEYWORD_TYPE ID ASSIGN NR';'cond';'ID INC               {declarare_variabila($2,$1,$4,"NU");identificare_variabila($2);}
        |KEYWORD_TYPE ID ASSIGN NR';'cond';'ID DEC              {declarare_variabila($2,$1,$4,"NU");identificare_variabila($2);}
        |ID ASSIGN NR ';'cond';'ID DEC                          {identificare_variabila($1);identificare_variabila($7);}
        |ID ASSIGN NR ';'cond';'ID INC                          {identificare_variabila($1);identificare_variabila($7);}
        ;

cond:   ID '>''=' expr                              {identificare_variabila($1);Asignare($1,$4 + 1); }
        |ID '<''=' expr                             {identificare_variabila($1);Asignare($1,$4 + 1);} 
        |ID '!''=' expr                             {identificare_variabila($1);Asignare($1, $4);} 
        |ID'<'expr                                  {identificare_variabila($1);Asignare($1,$3);} 
        |ID'>'expr                                  {identificare_variabila($1);Asignare($1,$3);} 
        ;                            

instructions:instructions instruction
            |instruction
            ;  

instruction:declaration
            |return 
            ;

string_function:STRLEN'('ID')'                       {identificare_variabila($3);}
               |STRCPY'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
               |STRSTR'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
               |STRCMP'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
               |STRCHR'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
               |STRCAT'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
               ;

expression:ID ASSIGN expr                                   {identificare_variabila($1);Asignare($1,$3);}
        |ID'('array')'  /* apelul pt functii void */
        |ID DEC                                             {identificare_variabila($1);decrementare($1);}
        |ID INC                                             {identificare_variabila($1);incrementare($1);}
        |ID ASSIGN KEYWORD_TYPE                             {declarare_variabila_fara_init($1, $3,"NU");}
        |ID ASSIGN type                                     {declarare_variabila_fara_init($1, $3, "DA");} 
        |KEYWORD_TYPE ID ASSIGN NR                          {declarare_variabila($2, $1, $4, "NU");}
        |ID '['NR']'ASSIGN KEYWORD_TYPE                     {declarare_variabila_fara_init($1,$6,"NU");}
        |ID '['NR']'ASSIGN'/''/'array'/''/'                {identificare_variabila($1);}
        |ID '['NR']''['NR']'ASSIGN KEYWORD_TYPE             {declarare_variabila_fara_init($1,$9,"NU");}
        |ID '['NR']''['NR']'ASSIGN'/''/'matrix'/''/'
        |type ID ASSIGN NR                                  {declarare_variabila($2, $1, $4,"DA");}
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
    |ID                     {identificare_variabila($1);verificare_initializare($1);$$=returnare_valoare($1);}
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

elem_printing:elem_printing',' ID         {identificare_variabila($3);}
           |ID                          {identificare_variabila($1);}
           ;
%%

int yywrap(void) {
    return 1;
}

int yyerror(char * s){
printf("eroare: %s la linia:%d\n",s,yylineno);
}

int main(int argc, char** argv){

 if (argc > 1) yyin = fopen(argv[1], "r");
 FILE* s;
 if(NULL == (s = fopen("symbol_table.txt","w")))
    {
        perror("Eroare la deschiderea fisierului de prelucrat!\n");
        exit(1);
    }
    else {printf("S-a creat cu succes\n");}
          
 fclose(s);  
   
yyparse();
} 