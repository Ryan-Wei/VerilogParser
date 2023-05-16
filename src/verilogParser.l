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

"always" { return ALWAYS; }
"begin" { return BEGIN_TOKEN; }
"end" { return END_TOKEN; }
"if" { return IF; }
"else" { return ELSE; }
"case" { return CASE; }
"default" { return DEFAULT; }
"assign" { return ASSIGN; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.strval = strdup(yytext); return IDENTIFIER; }
[0-9]+ { yylval.intval = atoi(yytext); return NUMBER; }
[ \t\r\n]+ { ; } /* ignore whitespace */
"//".* { ; } /* ignore comments */
. { return yytext[0]; } /* return all other characters */
%%

int yywrap() { return 1; }
