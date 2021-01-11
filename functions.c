#include "functions.h"

// struct variable
// {
//       int value;
//       char* name;
//       char* data_type;
//       char* constant_value;
//       char* initialization;

// };
// struct variable var[1000];

// int var_counter=0,new_var_counter=0;
// int function_counter=0,new_function_counter=0;


// struct function 
// {
//       char* type;
//       char* name;
//       int nr_parametrii;
//       char * parameters;
 
// };
// struct function funct[1000];

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
{for(int i=0;i<var_counter;i++)
  {if(strcmp(var[i].name,name)==0) 
       {return i; }
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

int expression[1000],exp=0;
void add_arg(int ex)
{
   expression[exp]=ex;
   exp++;
}

void show_exp()
{
      for(int i=0;i<exp;i++)
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
      { if(strcmp(var[verify_if_declared(name)].data_type,"int")==0) var[verify_if_declared(name)].value--;
      }
}