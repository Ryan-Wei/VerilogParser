%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

extern int yylex();
void yyerror(const char *msg);
%}


%union 
{
    struct module_body_t 
    {
        struct internal_port_list_t *internal_port_list;
        struct always_list_t *always_list;
        struct assign_list_t *assign_list;
    } *module_body;

    struct port_list_t 
    {
        struct port_t *ports;
        int count;
    } *port_list;

    struct internal_port_list_t 
    {
        struct port_t *ports;
        int count;
    } *internal_port_list;

    struct port_t 
    {
        char *name;
        char *type;
        int width;
    } port;

    struct always_block_t 
    {
        char *condition;
        struct statement_t *statement;
    } always_block;

    struct always_list_t 
    {
        struct always_block_t *always_block;
        int count;
    } *always_list;

    struct statement_t 
    {
        struct statement_t *head;
        struct statement_t *tail;
        char *expression;
        int flag;
        char *type;
        char *condition;
    } *statement;

    struct assign_list_t 
    {
        struct assign_statement_t *assign_statement;
        int count;
    } *assign_list;

    struct assign_statement_t 
    {
        char *left;
        char *right;
        char *type;
    } assign_statement;

    char* strval;
    int intval;

}

%token <strval> MODULE 
%token <strval> ENDMODULE 
%token <strval> INPUT 
%token <strval> OUTPUT 
%token <strval> WIRE 
%token <strval> REG
%token <strval> IDENTIFIER 
%token <intval> NUMBER
%token <strval> BEGIN_TOKEN
%token <strval> END_TOKEN
%token <strval> ALWAYS
%token <strval> IF
%token <strval> ELSE
%token <strval> ASSIGN
%token <strval> LE
%token <strval> GE
%token <strval> EQ
%token <strval> NE
%token <strval> AND
%token <strval> OR
%token <strval> NAND
%token <strval> NOR
%token <strval> XOR
%token <strval> XNOR
%token <strval> POSEDGE
%token <strval> NEGEDGE
%token <strval> OR_WORD


%type <port_list> port_list
%type <port> port_declaration
%type <strval> verilog_file
%type <strval> module_declaration_list
%type <strval> module_declaration
%type <internal_port_list> internal_port_list
%type <module_body> module_body
%type <always_list> always_list
%type <always_block> always_block
%type <strval> expression
%type <statement> statement
%type <statement> statement_block
%type <statement> statement_list
%type <assign_list> assign_list
%type <assign_statement> assign_statement


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

static void json_add_number(const char *key, const int value) 
{
    char str[32];
    sprintf(str, "%d", value);
    print_json_key_value(key, str, json_depth);
}

static void json_add_boolean(const char *key, bool value) 
{
    print_json_key_value(key, value ? "true" : "false", json_depth);
}

static void json_add_null(const char *key) 
{
    print_json_key_value(key, "null", json_depth);
}

static void print_statement(struct statement_t *p) 
{
    if (!p) 
        return;

    if (p -> flag) 
    {

        json_add_string("expression", p -> expression);
        print_statement(p -> tail);
    }
    else 
    {
        json_start_object("statement", p -> type);
            if (p -> condition) 
            {
                json_add_string("condition", p -> condition);
            }
            print_statement(p -> head);
        json_end_object();
        print_statement(p -> tail);
    }
}


%}



%%
verilog_file    : module_declaration_list
                {
                    // started by main()
                    json_end_object(); // end parsing from
                }

module_declaration_list     : module_declaration
                            | module_declaration_list module_declaration { }


module_declaration  : MODULE IDENTIFIER '(' port_list ')' ';' module_body ENDMODULE 
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
                                    json_add_number("width", $4 -> ports[i].width);
                                    json_end_object();
                                }
                            json_end_object(); // end external ports

                            json_start_object("module_body", "module_body");
                                if ($7 -> internal_port_list) 
                                {
                                    json_start_object("internal_ports", "internal_port_list");
                                        //printf("internal port count: %d\n", $7 -> internal_port_list -> count);
                                        for (int i = 0; i < $7 -> internal_port_list -> count; i++) 
                                        {
                                            json_start_object("port", "port_declaration");
                                                //json_add_string("tag", "port_declaration");
                                                json_add_string("name", $7 -> internal_port_list -> ports[i].name);
                                                json_add_string("type", $7 -> internal_port_list -> ports[i].type);
                                                json_add_number("width", $7 -> internal_port_list -> ports[i].width);
                                            json_end_object();
                                        }
                                    json_end_object(); // end internal ports
                                }

                                if ($7 -> always_list) 
                                {
                                    json_start_object("always_blocks", "always_list");
                                        for (int i = 0; i < $7 -> always_list -> count; i++) 
                                        {
                                            json_start_object("always_block", "always_definition");
                                                json_add_string("condition", $7 -> always_list -> always_block[i].condition);
                                                json_start_object("statement", $7 -> always_list -> always_block[i].statement -> type);
                                                    print_statement($7 -> always_list -> always_block[i].statement);
                                                json_end_object(); // end statement block
                                            json_end_object();
                                        }
                                    json_end_object(); // end always blocks
                                }

                                if($7 -> assign_list) 
                                {
                                    json_start_object("assign_statements", "assign_list");
                                        for (int i = 0; i < $7 -> assign_list -> count; i++) 
                                        {
                                            json_start_object("assign_statement", "assign_statement");
                                                json_add_string("left_hand_side", $7 -> assign_list -> assign_statement[i].left);
                                                json_add_string("right_hand_side", $7 -> assign_list -> assign_statement[i].right);
                                                json_add_string("type", $7 -> assign_list -> assign_statement[i].type);
                                            json_end_object();
                                        }
                                    json_end_object(); // end assign statements
                                }

                            json_end_object(); // end module body
                        json_end_object(); // end module
                     }

port_list           : port_declaration 
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

internal_port_list  : port_declaration ';'
                    {
                        $$ = (struct internal_port_list_t *)malloc(sizeof(struct internal_port_list_t));
                        $$ -> ports = (struct port_t *)malloc(sizeof(struct port_t));
                        $$ -> ports[0] = $1;
                        $$ -> count = 1;
                    }
                    | internal_port_list port_declaration ';'
                    {
                        $$ = $1;
                        $$ -> ports = (struct port_t *)realloc($$ -> ports, sizeof(struct port_t) * ($1 -> count + 1));
                        $$ -> ports[$1 -> count] = $2;
                        $$ -> count = $1 -> count + 1;
                    }

port_declaration    : INPUT IDENTIFIER 
                    {
                        $$.name = $2;
                        $$.type = "input";
                        $$.width = 1;
                    }
                    | OUTPUT IDENTIFIER
                    {
                        $$.name = $2;
                        $$.type = "output";
                        $$.width = 1;
                    }
                    | WIRE IDENTIFIER
                    {
                        $$.name = $2;
                        $$.type = "wire";
                        $$.width = 1;
                    }
                    | REG IDENTIFIER
                    {
                        $$.name = $2;
                        $$.type = "reg";
                        $$.width = 1;
                    }
                    | INPUT '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        $$.name = $7;
                        $$.type = "input";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | OUTPUT '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        $$.name = $7;
                        $$.type = "output";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | WIRE '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        $$.name = $7;
                        $$.type = "wire";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | REG '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        $$.name = $7;
                        $$.type = "reg";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | IDENTIFIER
                    {
                        $$.name = $1;
                        $$.type = "wire";
                        $$.width = 1;
                    }
                    | IDENTIFIER '[' NUMBER ':' NUMBER ']'
                    {
                        $$.name = $1;
                        $$.type = "wire";
                        $$.width = abs($3 - $5) + 1;
                    }


module_body     : internal_port_list always_list assign_list
                {
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = $2;
                    $$ -> assign_list = $3;
                }
                | internal_port_list always_list
                {
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = $2;
                    $$ -> assign_list = NULL;
                }
                | internal_port_list assign_list
                {
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = NULL;
                    $$ -> assign_list = $2;
                }
                | internal_port_list
                {
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = NULL;
                    $$ -> assign_list = NULL;
                }
                | always_list assign_list
                {
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = NULL;
                    $$ -> always_list = $1;
                    $$ -> assign_list = $2;
                }
                | always_list
                {
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = NULL;
                    $$ -> always_list = $1;
                    $$ -> assign_list = NULL;
                }
                | assign_list
                {
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = NULL;
                    $$ -> always_list = NULL;
                    $$ -> assign_list = $1;
                }


always_list     : always_block
                {
                    $$ = (struct always_list_t *)malloc(sizeof(struct always_list_t));
                    $$ -> always_block = (struct always_block_t *)malloc(sizeof(struct always_block_t));
                    $$ -> always_block[0] = $1;
                    $$ -> count = 1;
                }
                | always_list always_block
                {
                    $$ = $1;
                    $$ -> always_block = (struct always_block_t *)realloc($$ -> always_block, sizeof(struct always_block_t) * ($1 -> count + 1));
                    $$ -> always_block[$1 -> count] = $2;
                    $$ -> count = $1 -> count + 1;
                }



always_block    : ALWAYS '@' '(' expression ')' statement_block
                {
                    $$.condition = $4;
                    $$.statement = $6;
                }


statement_block     : BEGIN_TOKEN statement_list END_TOKEN
                    {
                        $$ = $2;
                    }

statement_list      : statement
                    {
                        $$ = $1;
                    }
                    | statement_list statement
                    {
                        $$ = $1;
                        struct statement_t *p = $$;
                        while (p -> tail) 
                        {
                            p = p -> tail;
                        }
                        p -> tail = $2;
                    }

statement   : expression ';'
            {
                $$ = (struct statement_t *)malloc(sizeof(struct statement_t));
                $$ -> head = NULL;
                $$ -> tail = NULL;
                $$ -> expression = $1;
                $$ -> flag = 1;
                $$ -> type = "ordinary_statement";
                $$ -> condition = NULL;
            }
            | statement_block
            {
                $$ = (struct statement_t *)malloc(sizeof(struct statement_t));
                $$ -> head = $1;
                $$ -> tail = NULL;
                $$ -> expression = NULL;
                $$ -> flag = 0;
                $$ -> type = "ordinary_statement";
                $$ -> condition = NULL;
            }
            | IF '(' expression ')' statement
            {
                $$ = (struct statement_t *)malloc(sizeof(struct statement_t));
                $$ -> head = $5;
                $$ -> tail = NULL;
                $$ -> expression = NULL;
                $$ -> flag = 0;
                $$ -> type = "if_statement";
                $$ -> condition = $3;
            }
            | IF '(' expression ')' statement ELSE statement
            {
                $$ = (struct statement_t *)malloc(sizeof(struct statement_t));
                $$ -> head = $5;

                $$ -> tail = (struct statement_t *)malloc(sizeof(struct statement_t));
                $$ -> tail -> head = $7;
                $$ -> tail -> tail = NULL;
                $$ -> tail -> expression = NULL;
                $$ -> tail -> flag = 0;
                $$ -> tail -> type = "else_statement";
                $$ -> tail -> condition = NULL;

                $$ -> expression = NULL;
                $$ -> flag = 0;
                $$ -> type = "if_statement";
                $$ -> condition = $3;
            }

            
assign_list : assign_statement
            {
                $$ = (struct assign_list_t *)malloc(sizeof(struct assign_list_t));
                $$ -> assign_statement = (struct assign_statement_t *)malloc(sizeof(struct assign_statement_t));
                $$ -> assign_statement[0] = $1;
                $$ -> count = 1;
            }
            | assign_list assign_statement
            {
                $$ = $1;
                $$ -> assign_statement = (struct assign_statement_t *)realloc($$ -> assign_statement, sizeof(struct assign_statement_t) * ($1 -> count + 1));
                $$ -> assign_statement[$1 -> count] = $2;
                $$ -> count = $1 -> count + 1;
            }

assign_statement    : ASSIGN IDENTIFIER '=' expression ';'
                    {
                        $$.left = $2;
                        $$.right = $4;
                        $$.type = "blocking assignment";
                    }
                    | ASSIGN IDENTIFIER LE expression ';'
                    {
                        $$.left = $2;
                        $$.right = $4;
                        $$.type = "non-blocking assignment";
                    }


expression  : IDENTIFIER
            {
                $$ = $1;
            }
            | NUMBER
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%d", $1);
                $$ = str;
            }
            | expression '=' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s = %s", $1, $3);
                $$ = str;
            }
            | expression '+' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s + %s", $1, $3);
                $$ = str;
            }
            | expression '-' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s - %s", $1, $3);
                $$ = str;
            }
            | expression '*' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s * %s", $1, $3);
                $$ = str;
            }
            | expression '/' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s / %s", $1, $3);
                $$ = str;
            }
            | expression '%' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s %% %s", $1, $3);
                $$ = str;
            }
            | expression '&' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s & %s", $1, $3);
                $$ = str;
            }
            | expression '|' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s | %s", $1, $3);
                $$ = str;
            }
            | expression '^' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s ^ %s", $1, $3);
                $$ = str;
            }
            |'~' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "~%s", $2);
                $$ = str;
            }
            | expression '<' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s < %s", $1, $3);
                $$ = str;
            }
            | expression '>' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s > %s", $1, $3);
                $$ = str;
            }
            | expression LE expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s <= %s", $1, $3);
                $$ = str;
            }
            | expression EQ expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s == %s", $1, $3);
                $$ = str;
            }
            | expression NE expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s != %s", $1, $3);
                $$ = str;
            }
            | expression AND expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s && %s", $1, $3);
                $$ = str;
            }
            | expression OR expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s || %s", $1, $3);
                $$ = str;
            }
            | expression NAND expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s !& %s", $1, $3);
                $$ = str;
            }
            | expression NOR expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s !| %s", $1, $3);
                $$ = str;
            }
            | expression XOR expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s ^| %s", $1, $3);
                $$ = str;
            }
            | expression XNOR expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s ^& %s", $1, $3);
                $$ = str;
            }
            | '(' expression ')'
            {
                $$ = $2;
            }
            | expression '?' expression ':' expression
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s ? %s : %s", $1, $3, $5);
                $$ = str;
            }
            | expression '[' expression ']'
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s[%s]", $1, $3);
                $$ = str;
            }
            | expression '[' expression ':' expression ']'
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s[%s:%s]", $1, $3, $5);
                $$ = str;
            }
            | POSEDGE IDENTIFIER
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "posedge %s", $2);
                $$ = str;
            }
            | NEGEDGE IDENTIFIER
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "negedge %s", $2);
                $$ = str;
            }
            | NEGEDGE IDENTIFIER OR_WORD POSEDGE IDENTIFIER
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "negedge %s or posedge %s", $2, $5);
                $$ = str;
            }
            | POSEDGE IDENTIFIER OR_WORD NEGEDGE IDENTIFIER
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "posedge %s or negedge %s", $2, $5);
                $$ = str;
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