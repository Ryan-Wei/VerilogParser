%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(char *msg);
%}

%union {
  float f;
}

%token <f> NUMB
%type <f> E T F 

%%
S : E         { printf(" = %f\n", $1); }
  ;

E : E '+' T   { $$ = $1 + $3; printf("001: %f\n", $$); }
  | E '-' T   { $$ = $1 - $3; printf("002: %f\n", $$); }
  | T         { $$ = $1;   printf("003: %f\n", $$); }
  ;

T : T '*' F   { $$ = $1 * $3; printf("004: %f\n", $$); }
  | T '/' F   { $$ = $1 / $3; printf("005: %f\n", $$); }
  | F         { $$ = $1;  printf("006: %f\n", $$); }
  ; 

F : '(' E ')' { $$ = $2; printf("007: %f\n", $$); }
  | '-' F     { $$ = -$2; printf("008: %f\n", $$); }
  | NUMB      { $$ = $1; printf("009: %f\n", $$); }
  ;
%%

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit (1);
}

int main()
{
  yyparse();
  return 0;
}

