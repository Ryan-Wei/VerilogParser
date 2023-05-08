%{
#include "y.tab.h"
%}

%%
"module" { return MODULE; }
"input" { return INPUT; }
"output" { return OUTPUT; }
"wire" { return WIRE; }
"reg" { return REG; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval = strdup(yytext); return IDENTIFIER; }
[0-9]+ { yylval = atoi(yytext); return NUMBER; }
[ \t\n]+ /* ignore whitespace */
. { return yytext[0]; }
%%

int yywrap() { return 1; }
