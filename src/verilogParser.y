%{
#include <stdio.h>
#include <stdlib.h>
extern char* yytext;
extern int yylval;
extern FILE* yyin;
int yylex();
void yyerror(char const* s);
%}

%token MODULE INPUT OUTPUT WIRE REG
%token IDENTIFIER NUMBER

%%

verilog_file : module_declaration { printf("Parsed a module declaration\n"); }

module_declaration : MODULE IDENTIFIER '(' port_list ')' ';' { printf("Parsed a module declaration with port list\n"); }
                   | MODULE IDENTIFIER ';' { printf("Parsed a module declaration without port list\n"); }

port_list : port { printf("Parsed a single port\n"); }
          | port_list ',' port { printf("Parsed a list of ports\n"); }

port : INPUT IDENTIFIER { printf("Parsed an input port\n"); }
     | OUTPUT IDENTIFIER { printf("Parsed an output port\n"); }
     | WIRE IDENTIFIER { printf("Parsed a wire\n"); }
     | REG IDENTIFIER { printf("Parsed a register\n"); }

%%

void yyerror(char const* s) {
    printf("Error: %s\n", s);
    exit(1);
}
