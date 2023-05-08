%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex();
void yyerror(char *msg);
%}

%union {
    char* strval;
}


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

void yyerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
  exit (1);
}

int main (int argc, char** argv) 
{
    yyparse();
    return 0;
}