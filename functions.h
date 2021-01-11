#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

// functions
int is_declared(char* name) // we check if a variable exists or not in the vector of variables
void var_declaring(char* name, char* data_type, int value, char* const_var) //we insert variables with initialization into the vector of variables
void var_declaring_without_init(char* name, char* data_type, char* const_var) // inserare variable dar fara initialization
int verify_if_declared(char* name) // we search if the variable was declared or not and if it was declared we return the position
void var_verification(char* name) // we verify if the variable was declared or not 
void initialization_verify(char* name)  // we check if the right side of an expression is initialized
int return_value(char * name)
void Assign(char* name,int value)
int already_declared_function(char* name,char * parameters)
void declaring_function(char* type,char* name,char * parameters)
int verifyIF_functionDEFINED(char* name)/// we verify if the the function was identified
void identify_function(char* name,char * parameters) // we identify the function when it is called
void PrintVar( char* type)
void PrintFunct(char* type)
void add_arg(int ex)
void show_exp()
void incr(char* name)
void decr(char* name)