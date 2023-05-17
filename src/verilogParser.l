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

[a-zA-Z_][a-zA-Z0-9_]* { 
    // Assign the matched identifier to yylval.
    yylval.strval = strdup(yytext);
    // Return the token type IDENTIFIER.
    return IDENTIFIER;
}
[0-9]+ { 
    // Convert the matched number to an integer and assign it to yylval.
    yylval.intval = atoi(yytext);
    // Return the token type NUMBER.
    return NUMBER;
}
[0-9]+'[bodh][a-zA-Z0-9_]+   { 
    // Assign the matched number expression to yylval.
    yylval.strval = strdup(yytext);
    // Return the token type NUMBER_EXPR.
    return NUMBER_EXPR;
}
[ \t\r\n]+ { 
    // Ignore whitespace.
    ; 
}
"//".* { 
    // Ignore comments.
    ; 
}
. { 
    // Return any other character as is.
    return yytext[0]; 
}
%%

int yywrap() { 
    // Indicate the end of input.
    return 1; 
}
