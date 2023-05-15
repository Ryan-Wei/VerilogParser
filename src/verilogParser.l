%{
#include "y.tab.h"
%}

%%
"module" { return MODULE; }
"endmodule" { return ENDMODULE; }
"input" { return INPUT; }
"output" { return OUTPUT; }
"wire" { return WIRE; }
"reg" { return REG; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.strval = strdup(yytext); return IDENTIFIER; }
[0-9]+ { yylval.strval = strdup(yytext); return NUMBER; }
[ \t\r\n]+ { } /* ignore whitespace */
"//".* { } /* ignore comments */
. { return yytext[0]; }
%%

int yywrap() { return 1; }
