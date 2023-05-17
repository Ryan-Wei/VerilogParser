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
"integer" { return INTEGER; }

"always" { return ALWAYS; }
"begin" { return BEGIN_TOKEN; }
"end" { return END_TOKEN; }
"if" { return IF; }
"else" { return ELSE; }
"assign" { return ASSIGN; }
"<=" { return LE; }
"==" { return EQ; }
"!=" { return NE; }
">=" { return GE; }
"&&" { return AND; }
"||" { return OR; }
"!&" { return NAND; }
"!|" { return NOR; }
"^|" { return XOR; }
"^&" { return XNOR; }

"posedge" { return POSEDGE; }
"negedge" { return NEGEDGE; }
"or" { return OR_WORD; }

[a-zA-Z_][a-zA-Z0-9_]* { yylval.strval = strdup(yytext); return IDENTIFIER; }
[0-9]+ { yylval.intval = atoi(yytext); return NUMBER; }
[0-9]+'[bodh][a-zA-Z0-9_]+   { yylval.strval = strdup(yytext); return NUMBER_EXPR; }
[ \t\r\n]+ { ; } /* ignore whitespace */

"//".* { ; } /* ignore comments */
. { return yytext[0]; } /* return all other characters */
%%

int yywrap() { return 1; }