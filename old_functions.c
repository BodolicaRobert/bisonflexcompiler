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