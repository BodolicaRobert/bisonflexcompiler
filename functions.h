#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


// De aici vom scrie prototipurile de functii