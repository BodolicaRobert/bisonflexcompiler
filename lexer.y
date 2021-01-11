%{
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

extern FILE* yyin;
extern char* yytext;
extern int yylineno;
extern int yylex();
extern int yyerror(char* syntaxerror);

struct variabila
{
      int valoare;
      char* nume;
      char* tip_data;
      char* constanta;
      char* initializare;

};
struct variabila var[1000];

int contor_variabila=0,contor_variabila_nou=0;
int contor_functie=0,contor_functie_nou=0;


struct functie 
{
      char* tip;
      char* nume;
      int nr_parametrii;
      char * parametrii;
 
};
struct functie fnct[1000];


int deja_declarat(char* nume) // verificam daca o variabila exista sau nu in vectorul de variabile
{
  for(int i=0;i<contor_variabila;i++)
  {
    if(strcmp(var[i].nume,nume)==0) 
       {
             return i; 
       }
  }

  return -1;
  
}


void declarare_variabila(char* nume, char* tip_data, int valoare, char* const_var) //insereaza variabile cu initializare in vectorul de variabile
{
   if(deja_declarat(nume)==-1)
  {
    var[contor_variabila].nume = strdup(nume);
    var[contor_variabila].tip_data=strdup(tip_data);
    var[contor_variabila].valoare=valoare;
    var[contor_variabila].constanta = strdup(const_var);
    var[contor_variabila].initializare="DA";
    contor_variabila++;
  }
  else
  {     
        char mesaj[256];
        sprintf(mesaj,"Variabila '%s' este deja declarata",nume);
        yyerror(mesaj);
        exit(0);
  }
}

void declarare_variabila_fara_init(char* nume, char* tip_data, char* const_var) // inserare variabila dar fara initializare
{
  if(deja_declarat(nume)==-1)
  {
    var[contor_variabila].nume=strdup(nume);
    var[contor_variabila].tip_data=strdup(tip_data);
    var[contor_variabila].valoare=0;
    var[contor_variabila].constanta = strdup(const_var);
    var[contor_variabila].initializare="NU";
    contor_variabila++;

  }
     else
  {
        char mesaj[256];
        sprintf(mesaj,"Variabila '%s' este deja declarata",nume);
        yyerror(mesaj);
        exit(0);
  }

}

int identificare_variabila_verificare(char* nume) // cauta daca variabila a fost declarata sau nu -> returneaza pozitia
{
   for(int i=0;i<contor_variabila;i++)
       {
       if(strcmp(var[i].nume,nume)==0) return i;

       }
  return -1;                                       
}
void identificare_variabila(char* nume) // verifica daca a fost declarata sau nu
{

      if(identificare_variabila_verificare(nume)==-1)
                 {char mesaj[256];
                     sprintf(mesaj,"Variabila '%s' nu a fost declarata",nume);
                     yyerror(mesaj);
                     exit(0);

                 } 

       
}

void verificare_initializare(char*nume)  // verifica daca partea dr a unei expresii este initializata
{
     for(int i=0;i<contor_variabila;i++)
      if(strcmp(var[i].nume,nume)==0)
         if(strcmp(var[i].initializare,"NU")==0)  {char mesaj[256];
                                                   sprintf(mesaj,"Variabila '%s' nu a fost initializata",nume);
                                                   yyerror(mesaj);
                                                   exit(0);

                                                    }   

}

int returnare_valoare(char * nume)
{
      for(int i=0;i<contor_variabila;i++)
      if(strcmp(var[i].nume,nume)==0)
         if(strcmp(var[i].initializare,"NU")!=0 && (strcmp(var[i].tip_data,"int")==0 || strcmp(var[i].tip_data,"const int")==0)) return var[i].valoare ;
           else return 0;  

}

void Asignare(char* nume,int valoare)
{
        if(strcmp(var[identificare_variabila_verificare(nume)].constanta,"DA")==0){char mesaj[256];
                                                                                   sprintf(mesaj,"Variabila constanta %s nu poate sta in partea stanga a unei atribuiri.",nume);
                                                                                   yyerror(mesaj);
                                                                                   exit(0);}

        if(strcmp(var[identificare_variabila_verificare(nume)].tip_data,"int")==0 && valoare != 0)                                                                            
        {var[identificare_variabila_verificare(nume)].valoare=valoare;
        var[identificare_variabila_verificare(nume)].initializare=strdup("DA");  
        }
        else
        if(strcmp(var[identificare_variabila_verificare(nume)].tip_data,"float")==0 && valoare != 0)
          {var[identificare_variabila_verificare(nume)].initializare=strdup("DA");  }
        else
        if(strcmp(var[identificare_variabila_verificare(nume)].tip_data,"double")==0 && valoare != 0)
          {var[identificare_variabila_verificare(nume)].initializare=strdup("DA");  }
        else
        if(strcmp(var[identificare_variabila_verificare(nume)].tip_data,"bool")==0 && ( valoare == 0 || valoare==1))
          {var[identificare_variabila_verificare(nume)].initializare=strdup("DA");
          }
        else
        if(strcmp(var[identificare_variabila_verificare(nume)].tip_data,"char")==0 && valoare == 0)
        {var[identificare_variabila_verificare(nume)].initializare=strdup("DA");  }
        else 
        {
            char mesaj[256];
            sprintf(mesaj,"Variabilei %s nu i se poate atribui o variabila/valoare de alt tip.",nume);
            yyerror(mesaj);
            exit(0);
        
        }
       
}

/*

void Verificare_asignare(char *nume_variabila)
{

   char *tip;
   strcpy(tip,var[identificare_variabila_verificare(nume_variabila)].tip_data); //tipul variabilei din partea stanga

    
    char *p=malloc(100);
    p=strtok(argumente_asignate,"+-:*");
    int ok=1;  
      while(p!=NULL)
      {     
            char* tip_argument;
            strcpy(tip_argument,var[identificare_variabila_verificare(p)].tip_data);

            if(strcmp(tip,tip_argument)!=0) ok=-1;

            p=strtok(NULL,"+-:*");
      }


    if(ok==-1){char mesaj[256];
              sprintf(mesaj,"Partea dreapta a atribuirii nu are acelasi tip cu variabila %s din partea stanga.",nume_variabila);
              yyerror(mesaj);
              exit(0);

              }

}
*/
int deja_declarat_functie(char* nume,char * parametrii)
{
    for(int i=0;i<contor_functie;i++)
    {    
          if(strcmp(fnct[i].nume,nume)==0)
                     return i;                                 
    }  
    return -1;
}


void declarare_functie(char* tip,char* nume,char * parametrii)
{    
      if(deja_declarat_functie(nume,tip)==-1)
         {fnct[contor_functie].tip=tip;
          fnct[contor_functie].nume=nume;
          fnct[contor_functie].parametrii=parametrii;
          contor_functie++;
      
         }
        else {char mesaj[256];
              sprintf(mesaj,"Functia '%s' a fost deja declarata",nume);
              yyerror(mesaj);
              exit(0);

              }  
}

int identificare_functie_verificare(char* nume)
{
   for(int i=0;i<contor_functie;i++)
       {
       if(strcmp(fnct[i].nume,nume)==0) return i;
       
       }
  return -1;                                       
}
void identificare_functie(char* nume,char * parametrii) // pt apelurile de functie
{   
      
       if(identificare_functie_verificare(nume)==-1)
                 {char mesaj[256];
                     sprintf(mesaj,"Functia '%s' nu a fost declarata",nume);
                     yyerror(mesaj);
                     exit(0);

                 }    


      char argumente[1000]="";
      char *p=malloc(100);
      p=strtok(parametrii,";");
      
      while(p!=NULL)
      {     
            if(strcmp(p,"int")==0) {strcat(argumente,"int;");}
            else    
               {if(identificare_variabila_verificare(p)!=-1) {strcat(argumente,var[identificare_variabila_verificare(p)].tip_data);
                                                             strcat(argumente,";");
                                                            }
               }

            p=strtok(NULL,";");
      }
      
      if(strcmp(fnct[identificare_functie_verificare(nume)].parametrii,argumente)!=0){char mesaj[256];
                                                                                      sprintf(mesaj,"Parametrii apelului functiei %s nu au acelasi tip ca in definitia functiei.",nume);
                                                                                      yyerror(mesaj);
                                                                                      exit(0);}       
}

void AfisareVariabile( char* tip)
{
  FILE* s = fopen("symbol_table.txt", "a");

  fprintf(s,"\n In '%s' se pot regasi urmatoarele declaratii de variabile:\n",tip);
  
 
  for(int i=contor_variabila_nou;i<contor_variabila;i++)
  {
      fprintf(s,"NUME: '%s' ,TIP:'%s' , VALOARE: '%d' ,CONSTANTA: '%s' \n",var[i].nume,var[i].tip_data,var[i].valoare,var[i].constanta);
      
  }
  contor_variabila_nou=contor_variabila;
  fclose(s);
} 

void AfisareFunctii(char * tip)
{
  FILE* s=fopen("symbol_table.txt","a");

  fprintf(s,"\n In '%s' se pot regasi urmatoarele functii:\n",tip);
   
  for(int j=contor_functie_nou;j<contor_functie;j++)
  {
      fprintf(s,"NUME: '%s' ,TIP:'%s'  ,Parametrii: %s \n" ,fnct[j].nume,fnct[j].tip,fnct[j].parametrii);
       
  }
  
  contor_functie_nou=contor_functie;
  fclose(s);

}

int expresie[1000],expr=0;
void Adaugare_argument(int ex)
{
   expresie[expr]=ex;
   expr++;
}

void Afisare_expresie()
{
      for(int i=0;i<expr;i++)
      {
            printf("Valoarea expresiei cu numarul %d este :%d\n",i+1,expresie[i]);
      }
}

void incrementare(char * nume)
{
      if(deja_declarat(nume)!=-1)
      {
            if(strcmp(var[identificare_variabila_verificare(nume)].tip_data,"int")==0) var[identificare_variabila_verificare(nume)].valoare++;
      }
}

void decrementare(char * nume)
{
      if(deja_declarat(nume)!=-1)
      {
            if(strcmp(var[identificare_variabila_verificare(nume)].tip_data,"int")==0) var[identificare_variabila_verificare(nume)].valoare--;
      }
}

%}
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
%token KEYWORD_IF KEYWORD_WHILE KEYWORD_ELSE KEYWORD_FOR AND OR ASSIGN KEYWORD_CLASS MAIN GHI LIBRARY EQUAL INCLUDE KEYWORD_RETURN READ WRITE 

%union {
      int nr;
      char* str;
}

%token<nr> NR 
%token<str> ID KEYWORD_TYPE KEYWORD_CLASS_TYPE KEYWORD_CONST INC DEC STRCAT STRSTR STRCHR STRCMP STRLEN STRCPY EVAL 
%type<nr> expr
%type<str> type class_method function_parameter function_parameters ids
%%
start:biblioteci clase global KEYWORD_TYPE MAIN '{' program '}' {printf("programul este acceptat\n");}
     ;

libraries:libraries library
          |library
          ;

library:'#'INCLUDE'<'LIBRARY'>'  
          |'#'INCLUDE GHI LIBRARY GHI
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
   |ID'['NR']''['NR']' ASSIGN KEYWORD_TYPEP     { declarare_variabila_fara_init($1,$9,"NU");}
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
                  |ID ASSIGN tip                                    {declarare_variabila_fara_init($1,$3,"DA");$$=$3;}
                  |ID'['']' ASSIGN TIP                              {declarare_variabila_fara_init($1,$5,"NU"); $$=$5;}      
                  |ID'['']''['']' ASSIGN TIP                        {declarare_variabila_fara_init($1,$7,"NU");$$=$7;}
                  |ID'['NR']' ASSIGN TIP                            {declarare_variabila_fara_init($1,$6,"NU");$$=$6;}
                  |'&' ID ASSIGN TIP                                {declarare_variabila_fara_init($2,$4,"NU"); $$=$4;}
                  |'*' ID ASSIGN TIP                                {declarare_variabila_fara_init($2,$4,"NU"); $$=$4;}
                  |apel_functie                                     {$$=0;}
                  |'('')'                                           { $$=0;}
                  ;

apel_functie:ID ASSIGN ID '(' id_uri ')'                            {identificare_variabila($1); identificare_functie($3,$5);}
            |ID '(' id_uri ')'                                      {identificare_functie($1,$3);}
            ;

id_uri:id_uri','ID                                                  {strcat($3,";");strcat($3,$1);$$=$3;}
      |id_uri','NR                                                  {$$=strdup("int;");strcat($$,$1);}
      |ID                                                           {strcat($1,";");$$=$1;}
      |NR                                                           {$$=strdup("int;");}
      ; 

op:ID                                                               {identificare_variabila($1);}
  |NR 
  ;   

function_declarations:function_declarations declaratieFC 
                     |declaratieFC
                     ; 

declaratieFC:declaratie
            |return 
            ;

return:RET op
      ;

global:global expresie                          {AfisareVariabile("global");}
      |global functie_global                    {AfisareFunctii("global");}
      |expresie 
      |functie_global
      ;

functie_global:TIP ID'('function_parameters')''{'function_declarations'}'       {declarare_functie($1,$2,$4);AfisareVariabile("in interiorul unei functii");}
              |TIP ID function_parameter '{'function_declarations'}'            {declarare_functie($1,$2,$3);AfisareVariabile("in interiorul unei functii");}   
              ;

program:declaratii /*liniile de cod*/           {AfisareVariabile("main");Afisare_expresie();}
       ;

declaratii:declaratii declaratie
          |declaratie
          ;

declaratie:IF'('conditii')' '{'instructiuni'}'
          |ELSE'{'instructiuni'}'
          |FOR'('continut')''{'instructiuni'}'
          |WHILE'('conditii')''{'instructiuni'}'
          |citire
          |afisare
          |functie_siruri 
          |expresie
          |EVAL'('expr')' {Adaugare_argument($3);}
          ;
         
conditii:conditii operator_logic conditie
        |conditii operator_logic '('conditie')'
        |operator_logic conditie
        |operator_logic'('conditie')'
        |conditie
        |'('conditie')'
        ;

conditie:expr operator_artimetic expr
        |'!' '('expr operator_artimetic expr')'
        ;

operator_artimetic:'>''='   
                  |'<''='
                  |'!''='
                  |'>'
                  |'<' 
                  |EQUAL
                  ;

operator_logic:AND  
              |OR
              |'!'
              ;   

continut:TIP ID ASSIGN NR';'cond';'ID INC           {declarare_variabila($2,$1,$4,"NU");identificare_variabila($2);}
        |TIP ID ASSIGN NR';'cond';'ID DEC           {declarare_variabila($2,$1,$4,"NU");identificare_variabila($2);}
        |ID ASSIGN NR ';'cond';'ID DEC              {identificare_variabila($1);identificare_variabila($7);}
        |ID ASSIGN NR ';'cond';'ID INC              {identificare_variabila($1);identificare_variabila($7);}
        ;

cond:   ID '>''=' expr                              {identificare_variabila($1);Asignare($1,$4 + 1); }
        |ID '<''=' expr                             {identificare_variabila($1);Asignare($1,$4 + 1);} 
        |ID '!''=' expr                             {identificare_variabila($1);Asignare($1, $4);} 
        |ID'<'expr                                  {identificare_variabila($1);Asignare($1,$3);} 
        |ID'>'expr                                  {identificare_variabila($1);Asignare($1,$3);} 
        ;                            

instructiuni:instructiuni instructiune
            |instructiune
            ;  

instructiune:declaratie
            |return 
            ;

functie_siruri:STRLEN'('ID')'                       {identificare_variabila($3);}
              |STRCPY'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
              |STRSTR'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
              |STRCMP'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
              |STRCHR'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
              |STRCAT'('ID','ID')'                  {identificare_variabila($3);identificare_variabila($5);}
              ;
expresie:ID ASSIGN expr                             {identificare_variabila($1);Asignare($1,$3);}
        |ID'('vector')'  /* apelul pt functii void */
        |ID DEC                                     {identificare_variabila($1);decrementare($1);}
        |ID INC                                     {identificare_variabila($1);incrementare($1);}
        |ID ASSIGN TIP                              {declarare_variabila_fara_init($1, $3,"NU");}
        |ID ASSIGN tip                              {declarare_variabila_fara_init($1, $3, "DA");} 
        |TIP ID ASSIGN NR                           {declarare_variabila($2, $1, $4, "NU");}
        |ID '['NR']'ASSIGN TIP                      {declarare_variabila_fara_init($1,$6,"NU");}
        |ID '['NR']'ASSIGN'/''/'vector'/''/'        {identificare_variabila($1);}
        |ID '['NR']''['NR']'ASSIGN TIP              {declarare_variabila_fara_init($1,$9,"NU");}
        |ID '['NR']''['NR']'ASSIGN'/''/'matrice'/''/'
        |tip ID ASSIGN NR                           {declarare_variabila($2, $1, $4,"DA");}
        |ID ID
        |ID'.'ID'('')'
        |ID'.'ID ASSIGN op

         ;
       
vector:op
      |vector',' op
      ;
    
matrice:matrice',''(' elemente_matrice')'
       |'('elemente_matrice')'
       ;       

elemente_matrice:elemente_matrice','op
                |op
                ;

expr:expr'+'expr            {$$ = $1 + $3;}
    |expr'-'expr            {$$ = $1 - $3;}
    |expr'*'expr            {$$ = $1 * $3;}
    |expr':'expr            {$$ = $1 / $3;}
    |'('expr')'             {$$ =$2;}
    |NR                     {$$=$1;}
    |ID                     {identificare_variabila($1);verificare_initializare($1);$$=returnare_valoare($1);}
    |functie_siruri         {$$=0;}
    |ID'['op']'             {$$=0;}
    |ID'['op']''['op']'     {$$=0;}
    |'+'expr                {$$ =$$ + $2;}
    |'-'expr                {$$ =$$ - $2;}
    |'*'expr                {$$ =$$ * $2;}
    |':'expr                {$$ =$$ /$2;}
    |apel_functie           {$$=1;}
    |ID'.'ID                {$$=0;}
    |ID'.'apel_functie      {$$=0;}
    |ID'.'ID'('')'          {$$=0;}
    |GHI ID GHI             {$$=0;}
    ;

citire:READ elem_citire
      ;

elem_citire:elem_citire',' ID
           |ID
           ;      

afisare:WRITE elem_afisare
      ;

elem_afisare:elem_afisare',' ID         {identificare_variabila($3);}
           |ID                          {identificare_variabila($1);}
           ;
%%

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