%{
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
%type<str> type function_parameter function_parameters ids
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
         |KEYWORD_TYPE ID ASSIGN NR {var_declaring($2, $1, $4, "NOPE");}
         ;

dec:ID ASSIGN KEYWORD_TYPE                      {var_declaring_without_init($1, $3,"NOPE");}
   |ID ASSIGN type                              {var_declaring_without_init($1, $3,"YES");}
   |ID'['NR']''['NR']' ASSIGN KEYWORD_TYPE      { var_declaring_without_init($1,$9,"NOPE");}
   |ID'['NR']' ASSIGN KEYWORD_TYPE              { var_declaring_without_init($1,$6,"NOPE");}
   |type ID ASSIGN NR                           {var_declaring($2, $1, $4, "YES");}
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

function_parameter: ID ASSIGN KEYWORD_TYPE                          {var_declaring_without_init($1,$3,"NOPE");$$=$3;}
                  |ID ASSIGN type                                   {var_declaring_without_init($1,$3,"YES");$$=$3;}
                  |ID'['']' ASSIGN KEYWORD_TYPE                     {var_declaring_without_init($1,$5,"NOPE"); $$=$5;}      
                  |ID'['']''['']' ASSIGN KEYWORD_TYPE               {var_declaring_without_init($1,$7,"NOPE");$$=$7;}
                  |ID'['NR']' ASSIGN KEYWORD_TYPE                   {var_declaring_without_init($1,$6,"NOPE");$$=$6;}
                  |'&' ID ASSIGN KEYWORD_TYPE                       {var_declaring_without_init($2,$4,"NOPE"); $$=$4;}
                  |'*' ID ASSIGN KEYWORD_TYPE                       {var_declaring_without_init($2,$4,"NOPE"); $$=$4;}
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

content:KEYWORD_TYPE ID ASSIGN NR';'cond';'ID INC               {var_declaring($2,$1,$4,"NOPE");var_verification($2);incr($1);}
        |KEYWORD_TYPE ID ASSIGN NR';'cond';'ID DEC              {var_declaring($2,$1,$4,"NOPE");var_verification($2);decr($1);}
        |ID ASSIGN NR ';'cond';'ID DEC                          {var_verification($1);var_verification($7);Assign($1,$3);decr($1);}
        |ID ASSIGN NR ';'cond';'ID INC                          {var_verification($1);var_verification($7);Assign($1,$3);incr($1);}
        ;

cond:   ID '>''=' expr                              {var_verification($1); }
        |ID '<''=' expr                             {var_verification($1); }  
        |ID '!''=' expr                             {var_verification($1); } 
        |ID'<'expr                                  {var_verification($1); } 
        |ID'>'expr                                  {var_verification($1); } 
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

expression:ID ASSIGN expr                                   {var_verification($1);Assign($1,$3);}
        |ID'('array')'  /* apelul pt functii void */
        |ID DEC                                             {var_verification($1);decr($1);}
        |ID INC                                             {var_verification($1);incr($1);}
        |ID ASSIGN KEYWORD_TYPE                             {var_declaring_without_init($1, $3,"NOPE");}
        |ID ASSIGN type                                     {var_declaring_without_init($1, $3, "YES");} 
        |KEYWORD_TYPE ID ASSIGN NR                          {var_declaring($2, $1, $4, "NOPE");}
        |ID '['NR']'ASSIGN KEYWORD_TYPE                     {var_declaring_without_init($1,$6,"NOPE");}
        |ID '['NR']'ASSIGN'{'array'}'                 {var_verification($1);}
        |ID '['NR']''['NR']'ASSIGN KEYWORD_TYPE             {var_declaring_without_init($1,$9,"NOPE");}
        |ID '['NR']''['NR']'ASSIGN'{'matrix'}'
        |type ID ASSIGN NR                                  {var_declaring($2, $1, $4,"YES");}
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
    |string_function        {$$=0;}
    |ID'['op']'             {$$=0;}
    |ID'['op']''['op']'     {$$=0;}
    |'+'expr                {$$ =$$ + $2;}
    |'-'expr                {$$ =$$ - $2;}
    |'*'expr                {$$ =$$ * $2;}
    |':'expr                {$$ =$$ /$2;}
    |function_call          {$$=1;}
    |ID'.'ID                {$$=0;}
    |ID'.'function_call     {$$=0;}
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