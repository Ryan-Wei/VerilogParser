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
S : E { printf("%f\n", $1); br}
  ;

E : T '+' E { $$ = $1 + $3; }
  | T '-' E { $$ = $1 - $3; }
  | T { $$ = $1; }
  ;

T : T '*' F { $$ = $1 * $3; }
  | T '/' F { $$ = $1 / $3; }
  | F { $$ = $1; }
  ;

F : '(' E ')' { $$ = $2; }
  | '-' F { $$ = -$2; }
  | NUMB { $$ = $1; }
  ;
%%

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

int main()
{
yyparse();
return 0;
}
