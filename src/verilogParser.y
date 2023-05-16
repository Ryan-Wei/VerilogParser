%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

extern int yylex();
void yyerror(const char *msg);
%}

%union 
{
    struct port_list_t 
    {
        struct port_t *ports;
        int count;
    } *port_list;

    struct port_t 
    {
        char *name;
        char *type;
    } port;

    char* strval;
}

%token <strval> MODULE 
%token <strval> ENDMODULE 
%token <strval> INPUT 
%token <strval> OUTPUT 
%token <strval> WIRE 
%token <strval> REG
%token <strval> IDENTIFIER 
%token <strval> NUMBER

%type <port_list> port_list
%type <port> port_declaration
%type <strval> verilog_file
%type <strval> module_declaration_list

%{

static void print_json_string(const char *str);
static void print_json_indent(int depth);
static bool first_item = true;
static int json_depth = 0;

static void print_json_object_start(int depth) 
{
    putchar('\n');
    print_json_indent(depth - 1); 
    putchar('{');
    //putchar('\n');
    //print_json_indent(depth);
    //if (!first_item) 
    //{
    //    putchar(',');
    //}
    first_item = true;
 
}

static void print_json_object_end(int depth) 
{
    putchar('\n');
    print_json_indent(depth);
    putchar('}');
}

static void print_json_indent(int depth) 
{
    for (int i = 0; i < depth; i++) 
    {
        putchar('\t');
    }
}

static void print_json_key_value(const char *key, const char *value, int depth) 
{
    if (!first_item) 
    {
        putchar(',');
    }
    first_item = false;
    putchar('\n');
    print_json_indent(depth);
    print_json_string(key);
    putchar(':');
    print_json_string(value);
}

static void print_json_string(const char *str) 
{
    putchar('"');
    for (const char *p = str; *p; p++) 
    {
        switch (*p) 
        {
            case '"': printf("\\\""); break;
            case '\\': printf("\\\\"); break;
            case '/': printf("\\/"); break;
            case '\b': printf("\\b"); break;
            case '\f': printf("\\f"); break;
            case '\n': printf("\\n"); break;
            case '\r': printf("\\r"); break;
            case '\t': printf("\\t"); break;
            default: putchar(*p); break;
        }
    }
    putchar('"');
}

static void json_start_object(const char *key, const char *value) 
{
    print_json_key_value(key, value, json_depth++);
    print_json_object_start(json_depth);
}

static void json_end_object() 
{
    print_json_object_end(--json_depth);
}

static void json_add_string(const char *key, const char *value) 
{
    print_json_key_value(key, value, json_depth);
}

static void json_add_number(const char *key, const char *value) 
{
    print_json_key_value(key, value, json_depth);
}

static void json_add_boolean(const char *key, bool value) 
{
    print_json_key_value(key, value ? "true" : "false", json_depth);
}

static void json_add_null(const char *key) 
{
    print_json_key_value(key, "null", json_depth);
}

%}



%%
verilog_file    : module_declaration_list
                {
                    json_end_object();
                }

module_declaration_list     : module_declaration
                            | module_declaration_list module_declaration { }


module_declaration  : MODULE IDENTIFIER '(' port_list ')' ';' ENDMODULE 
                    {
                        json_start_object("module", $2);
                        //json_add_string("name", $2);
                        json_start_object("ports", "port_list");
                        for (int i = 0; i < $4 -> count; i++) 
                        {
                            json_start_object("port", "port_declaration");
                            //json_add_string("tag", "port_declaration");
                            json_add_string("name", $4 -> ports[i].name);
                            json_add_string("type", $4 -> ports[i].type);
                            json_end_object();
                        }
                        json_end_object();
                        json_end_object();
                     }

port_list   : port_declaration 
            {
                $$ = (struct port_list_t *)malloc(sizeof(struct port_list_t));
                $$ -> ports = (struct port_t *)malloc(sizeof(struct port_t));
                $$ -> ports[0] = $1;
                $$ -> count = 1;
            }
            | port_list ',' port_declaration
            {
                $$ = $1;
                $$ -> ports = (struct port_t *)realloc($$ -> ports, sizeof(struct port_t) * ($1 -> count + 1));
                $$ -> ports[$1 -> count] = $3;
                $$ -> count = $1 -> count + 1;
            }

port_declaration    : INPUT IDENTIFIER 
                    {
                        $$.name = $2;
                        $$.type = "input";
                    }
                    | OUTPUT IDENTIFIER
                    {
                        $$.name = $2;
                        $$.type = "output";
                    }
                    | WIRE IDENTIFIER
                    {
                        $$.name = $2;
                        $$.type = "wire";
                    }
                    | REG IDENTIFIER
                    {
                        $$.name = $2;
                        $$.type = "reg";
                    }

%%

void yyerror(const char *msg)
{
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

int main (int argc, char** argv) 
{
    json_start_object("parsing from...", *argv);
    yyparse();
    return 0;
}
