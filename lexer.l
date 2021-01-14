%{
#include <stdio.h>
#include "y.tab.h"
%}
%option noyywrap
%%
"/*"(.|\n)+"*/" ;

"if" 			{ return KEYWORD_IF; }
"while" 		{ return KEYWORD_WHILE; }
"else" 			{ return KEYWORD_ELSE; }
"for" 			{ return KEYWORD_FOR; }

"++" 			{ return INC; }
"--" 			{ return DEC; }
"&&" 			{ return AND; }
"||" 			{ return OR; }
"<-" 			{ return ASSIGN; }
"==" 			{ return EQUAL; }

"class" 										{ return KEYWORD_CLASS; }
"const" 										{ yylval.str=strdup(yytext);return KEYWORD_CONST; }
"int"|"float"|"double"|"char"|"bool"|"void" 	{ yylval.str=strdup(yytext);return KEYWORD_TYPE; }

"main()" 		{ return MAIN; }
"include" 		{ return KEYWORD_INCLUDE; }
"stdio.h"|"string.h"|"stdlib.h"|"math.h"|"netinet/in.h"|"errno.h"|"unistd.h"|"iostream"|"sys/types.h"|"sys/socket.h" { return LIBRARY; }

\" {return GHI;}

"private"|"public"|"protected" { return KEYWORD_CLASS_TYPE; }
"read" 		{ return READ; }
"write" 	{ return WRITE; }
"return" 	{ return KEYWORD_RETURN; }
"length" 	{ return STRLEN; }
"copy" 		{ return STRCPY; }
"concat" 	{ return STRCAT; }
"char_at" 	{ return STRCHR; }
"substr" 	{ return STRSTR; }
"cmp" 		{ return STRCMP; }
"Eval" 		{ yylval.str=strdup(yytext); return EVAL; }

[A-Za-z][A-Za-z0-9]* 	{ yylval.str=strdup(yytext); return ID; }
[1-9][0-9]*|0 			{ yylval.nr = atoi(yytext); return NR; }
[ \t] ;
\n {yylineno++;}
. {return yytext[0];}
