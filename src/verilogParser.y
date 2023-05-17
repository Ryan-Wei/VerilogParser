%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Declare external functions
extern int yylex();
void yyerror(const char *msg);
%}

// Define the union type for semantic values
%union 
{
    // Struct for module_body
    struct module_body_t 
    {
        struct internal_port_list_t *internal_port_list; // Internal port list
        struct always_list_t *always_list; // List of always blocks
        struct assign_list_t *assign_list; // List of assign statements
    } *module_body;

    // Struct for port_list
    struct port_list_t 
    {
        struct port_t *ports; // Array of ports
        int count; // Number of ports
    } *port_list;

    // Struct for internal_port_list
    struct internal_port_list_t 
    {
        struct port_t *ports; // Array of internal ports
        int count; // Number of internal ports
    } *internal_port_list;

    // Struct for port
    struct port_t 
    {
        char *name; // Port name
        char *type; // Port type
        int width; // Port width
    } port;

    // Struct for always_block
    struct always_block_t 
    {
        char *condition; // Condition of the always block
        struct statement_t *statement; // Statement of the always block
    } always_block;

    // Struct for always_list
    struct always_list_t 
    {
        struct always_block_t *always_block; // Array of always blocks
        int count; // Number of always blocks
    } *always_list;

    // Struct for statement
    struct statement_t 
    {
        struct statement_t *head; // Head statement
        struct statement_t *tail; // Tail statement
        char *expression; // Expression of the statement
        int flag; // Flag indicating the type of statement node
        char *type; // Type of the statement
        char *condition; // Condition of the statement
    } *statement;

    // Struct for assign_list
    struct assign_list_t 
    {
        struct assign_statement_t *assign_statement; // Array of assign statements
        int count; // Number of assign statements
    } *assign_list;

    // Struct for assign_statement
    struct assign_statement_t 
    {
        char *left; // Left-hand side of the assign statement
        char *right; // Right-hand side of the assign statement
        char *type; // Type of the assign statement
    } assign_statement;

    char* strval; // String value
    int intval; // Integer value
}

// Define tokens
%token <strval> MODULE 
%token <strval> ENDMODULE 
%token <strval> INPUT 
%token <strval> OUTPUT 
%token <strval> WIRE 
%token <strval> REG
%token <strval> INTEGER
%token <strval> IDENTIFIER 
%token <intval> NUMBER
%token <strval> NUMBER_EXPR
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

// Define non-terminals
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

// Function to print a JSON string
static void print_json_string(const char *str);

// Function to print indentation based on depth
static void print_json_indent(int depth);

// Variable to track if it's the first item in the JSON object
static bool first_item = true;

// Variable to track the depth of the JSON object
static int json_depth = 0;

// Function to print the start of a JSON object
static void print_json_object_start(int depth) 
{
    putchar('\n');
    print_json_indent(depth - 1); // Print indentation
    putchar('{');
    first_item = true;
}

// Function to print the end of a JSON object
static void print_json_object_end(int depth) 
{
    putchar('\n');
    print_json_indent(depth);
    putchar('}');
}

// Function to print indentation based on depth
static void print_json_indent(int depth) 
{
    for (int i = 0; i < depth; i++) 
    {
        putchar('\t');
    }
}

// Function to print a key-value pair in the JSON object
static void print_json_key_value(const char *key, const char *value, int depth) 
{
    if (!first_item) 
    {
        putchar(','); // Print comma if it's not the first item
    }
    first_item = false;
    putchar('\n');
    print_json_indent(depth); // Print indentation
    print_json_string(key); // Print key
    putchar(':');
    print_json_string(value); // Print value
}

// Function to print a JSON string with proper escaping
static void print_json_string(const char *str) 
{
    putchar('"');
    for (const char *p = str; *p; p++) 
    {
        switch (*p) 
        {
            case '"': printf("\\\""); break; // Escape double quote
            case '\\': printf("\\\\"); break; // Escape backslash
            case '/': printf("\\/"); break; // Escape forward slash
            case '\b': printf("\\b"); break; // Escape backspace
            case '\f': printf("\\f"); break; // Escape form feed
            case '\n': printf("\\n"); break; // Escape newline
            case '\r': printf("\\r"); break; // Escape carriage return
            case '\t': printf("\\t"); break; // Escape tab
            default: putchar(*p); break;
        }
    }
    putchar('"');
}

// Function to start a JSON object with a key-value pair
static void json_start_object(const char *key, const char *value) 
{
    print_json_key_value(key, value, json_depth++);
    print_json_object_start(json_depth);
}

// Function to end the current JSON object
static void json_end_object() 
{
    print_json_object_end(--json_depth);
}

// Function to add a string to the JSON object
static void json_add_string(const char *key, const char *value) 
{
    print_json_key_value(key, value, json_depth);
}

// Function to add a number to the JSON object
static void json_add_number(const char *key, const int value) 
{
    char str[64];
    sprintf(str, "%d", value);
    print_json_key_value(key, str, json_depth);
}

// Function to add a boolean to the JSON object
static void json_add_boolean(const char *key, bool value) 
{
    print_json_key_value(key, value ? "true" : "false", json_depth);
}

// Function to add a null value to the JSON object
static void json_add_null(const char *key) 
{
    print_json_key_value(key, "null", json_depth);
}

// Function to print a statement
static void print_statement(struct statement_t *p) 
{
    if (!p) 
        return;

    if (p->flag) 
    {
        // Print expression
        json_add_string("expression", p->expression);
        print_statement(p->tail);
    }
    else 
    {
        // Start a new statement object
        json_start_object("statement", p->type);

        if (p->condition) 
        {
            // Print condition
            json_add_string("condition", p->condition);
        }

        print_statement(p->head);
        
        // End the statement object
        json_end_object();

        print_statement(p->tail);
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
                        json_start_object("module", $2); // Start module object
                            //json_add_string("name", $2);
                            json_start_object("ports", "port_list"); // Start ports object
                                for (int i = 0; i < $4 -> count; i++) 
                                {
                                    json_start_object("port", "port_declaration"); // Start port object
                                    //json_add_string("tag", "port_declaration");
                                    json_add_string("name", $4 -> ports[i].name); // Add port name
                                    json_add_string("type", $4 -> ports[i].type); // Add port type
                                    json_add_number("width", $4 -> ports[i].width); // Add port width
                                    json_end_object(); // End port object
                                }
                            json_end_object(); // End ports object

                            json_start_object("module_body", "module_body"); // Start module body object
                                if ($7 -> internal_port_list) 
                                {
                                    json_start_object("internal_ports", "internal_port_list"); // Start internal ports object
                                        //printf("internal port count: %d\n", $7 -> internal_port_list -> count);
                                        for (int i = 0; i < $7 -> internal_port_list -> count; i++) 
                                        {
                                            json_start_object("port", "port_declaration"); // Start port object
                                                //json_add_string("tag", "port_declaration");
                                                json_add_string("name", $7 -> internal_port_list -> ports[i].name); // Add port name
                                                json_add_string("type", $7 -> internal_port_list -> ports[i].type); // Add port type
                                                json_add_number("width", $7 -> internal_port_list -> ports[i].width); // Add port width
                                            json_end_object(); // End port object
                                        }
                                    json_end_object(); // End internal ports object
                                }

                                if ($7 -> always_list) 
                                {
                                    json_start_object("always_blocks", "always_list"); // Start always blocks object
                                        for (int i = 0; i < $7 -> always_list -> count; i++) 
                                        {
                                            json_start_object("always_block", "always_definition"); // Start always block object
                                                json_add_string("condition", $7 -> always_list -> always_block[i].condition); // Add always block condition
                                                json_start_object("statement", $7 -> always_list -> always_block[i].statement -> type); // Start statement object
                                                    print_statement($7 -> always_list -> always_block[i].statement); // Print statement
                                                json_end_object(); // End statement block
                                            json_end_object(); // End always block object
                                        }
                                    json_end_object(); // End always blocks object
                                }

                                if($7 -> assign_list) 
                                {
                                    json_start_object("assign_statements", "assign_list"); // Start assign statements object
                                        for (int i = 0; i < $7 -> assign_list -> count; i++) 
                                        {
                                            json_start_object("assign_statement", "assign_statement"); // Start assign statement object
                                                json_add_string("left_hand_side", $7 -> assign_list -> assign_statement[i].left); // Add left-hand side
                                                json_add_string("right_hand_side", $7 -> assign_list -> assign_statement[i].right); // Add right-hand side
                                            json_end_object(); // End assign statement object
                                        }
                                    json_end_object(); // End assign statements object
                                }
                            json_end_object(); // End module body object
                        json_end_object(); // End module object
                    }


port_list           : port_declaration 
                    {
                        // Allocate memory for a new port list and set its count to 1.
                        $$ = (struct port_list_t *)malloc(sizeof(struct port_list_t));
                        $$ -> ports = (struct port_t *)malloc(sizeof(struct port_t));
                        $$ -> ports[0] = $1;
                        $$ -> count = 1;
                    }
                    | port_list ',' port_declaration
                    {
                        // Add a new port to an existing port list and update its count.
                        $$ = $1;
                        $$ -> ports = (struct port_t *)realloc($$ -> ports, sizeof(struct port_t) * ($1 -> count + 1));
                        $$ -> ports[$1 -> count] = $3;
                        $$ -> count = $1 -> count + 1;
                    }


internal_port_list  : port_declaration ';'
                    {
                        // Allocate memory for a new internal port list and set its count to 1.
                        $$ = (struct internal_port_list_t *)malloc(sizeof(struct internal_port_list_t));
                        $$ -> ports = (struct port_t *)malloc(sizeof(struct port_t));
                        $$ -> ports[0] = $1;
                        $$ -> count = 1;
                    }
                    | internal_port_list port_declaration ';'
                    {
                        // Add a new port to an existing internal port list and update its count.
                        $$ = $1;
                        $$ -> ports = (struct port_t *)realloc($$ -> ports, sizeof(struct port_t) * ($1 -> count + 1));
                        $$ -> ports[$1 -> count] = $2;
                        $$ -> count = $1 -> count + 1;
                    }


port_declaration    : INPUT IDENTIFIER 
                    {
                        // Set up a new port declaration for an input with a width of 1.
                        $$.name = $2;
                        $$.type = "input";
                        $$.width = 1;
                    }
                    | OUTPUT IDENTIFIER
                    {
                        // Set up a new port declaration for an output with a width of 1.
                        $$.name = $2;
                        $$.type = "output";
                        $$.width = 1;
                    }
                    | WIRE IDENTIFIER
                    {
                        // Set up a new port declaration for a wire with a width of 1.
                        $$.name = $2;
                        $$.type = "wire";
                        $$.width = 1;
                    }
                    | REG IDENTIFIER
                    {
                        // Set up a new port declaration for a register with a width of 1.
                        $$.name = $2;
                        $$.type = "reg";
                        $$.width = 1;
                    }
                    | INPUT '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        // Set up a new port declaration for an input with a variable width.
                        $$.name = $7;
                        $$.type = "input";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | OUTPUT '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        // Set up a new port declaration for an output with a variable width.
                        $$.name = $7;
                        $$.type = "output";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | WIRE '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        // Set up a new port declaration for a wire with a variable width.
                        $$.name = $7;
                        $$.type = "wire";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | REG '[' NUMBER ':' NUMBER ']' IDENTIFIER
                    {
                        // Set up a new port declaration for a register with a variable width.
                        $$.name = $7;
                        $$.type = "reg";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | IDENTIFIER
                    {
                        // Set up a new port declaration for an identifier representing a wire with a width of 1.
                        $$.name = $1;
                        $$.type = "wire";
                        $$.width = 1;
                    }
                    | IDENTIFIER '[' NUMBER ':' NUMBER ']'
                    {
                        // Set up a new port declaration for an identifier representing a wire with a variable width.
                        $$.name = $1;
                        $$.type = "wire";
                        $$.width = abs($3 - $5) + 1;
                    }
                    | INTEGER expression
                    {
                        // Set up a new port declaration for an integer with a width of 32.
                        $$.name = $2;
                        $$.type = "integer";
                        $$.width = 32;
                    }


module_body     : internal_port_list always_list assign_list
                {
                    // Create a new module body and assign the provided internal port list, always list, and assign list.
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = $2;
                    $$ -> assign_list = $3;
                }
                | internal_port_list always_list
                {
                    // Create a new module body with only the internal port list and always list.
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = $2;
                    $$ -> assign_list = NULL;
                }
                | internal_port_list assign_list
                {
                    // Create a new module body with only the internal port list and assign list.
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = NULL;
                    $$ -> assign_list = $2;
                }
                | internal_port_list
                {
                    // Create a new module body with only the internal port list.
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = $1;
                    $$ -> always_list = NULL;
                    $$ -> assign_list = NULL;
                }
                | always_list assign_list
                {
                    // Create a new module body with only the always list and assign list.
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = NULL;
                    $$ -> always_list = $1;
                    $$ -> assign_list = $2;
                }
                | always_list
                {
                    // Create a new module body with only the always list.
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = NULL;
                    $$ -> always_list = $1;
                    $$ -> assign_list = NULL;
                }
                | assign_list
                {
                    // Create a new module body with only the assign list.
                    $$ = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    $$ -> internal_port_list = NULL;
                    $$ -> always_list = NULL;
                    $$ -> assign_list = $1;
                }


always_list     : always_block
                {
                    // Create a new always list with a single always block.
                    $$ = (struct always_list_t *)malloc(sizeof(struct always_list_t));
                    $$ -> always_block = (struct always_block_t *)malloc(sizeof(struct always_block_t));
                    $$ -> always_block[0] = $1;
                    $$ -> count = 1;
                }
                | always_list always_block
                {
                    // Add a new always block to an existing always list.
                    $$ = $1;
                    $$ -> always_block = (struct always_block_t *)realloc($$ -> always_block, sizeof(struct always_block_t) * ($1 -> count + 1));
                    $$ -> always_block[$1 -> count] = $2;
                    $$ -> count = $1 -> count + 1;
                }


always_block    : ALWAYS '@' '(' expression ')' statement_block
                {
                    // Create a new always block with the provided condition and statement block.
                    $$.condition = $4;
                    $$.statement = $6;
                }


statement_block     : BEGIN_TOKEN statement_list END_TOKEN
                    {
                        // Assign the provided statement list to the statement block.
                        $$ = $2;
                    }


statement_list      : statement
                    {
                        // Set the statement list to a single statement.
                        $$ = $1;
                    }
                    | statement_list statement
                    {
                        // Add a new statement to an existing statement list.
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
                // Create a new statement with the provided expression as an ordinary statement.
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
                // Create a new statement with the provided statement block as an ordinary statement.
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
                // Create a new statement with the if condition and statement as an if statement.
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
                // Create a new statement with the if condition and corresponding statements as an if-else statement.
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
                // Create a new assign list with a single assign statement.
                $$ = (struct assign_list_t *)malloc(sizeof(struct assign_list_t));
                $$ -> assign_statement = (struct assign_statement_t *)malloc(sizeof(struct assign_statement_t));
                $$ -> assign_statement[0] = $1;
                $$ -> count = 1;
            }
            | assign_list assign_statement
            {
                // Add a new assign statement to an existing assign list.
                $$ = $1;
                $$ -> assign_statement = (struct assign_statement_t *)realloc($$ -> assign_statement, sizeof(struct assign_statement_t) * ($1 -> count + 1));
                $$ -> assign_statement[$1 -> count] = $2;
                $$ -> count = $1 -> count + 1;
            }




assign_statement    : ASSIGN IDENTIFIER '=' expression ';'
                    {
                        // Create a new assign statement with blocking assignment.
                        $$.left = $2;
                        $$.right = $4;
                        $$.type = "blocking assignment";
                    }
                    | ASSIGN IDENTIFIER LE expression ';'
                    {
                        // Create a new assign statement with non-blocking assignment.
                        $$.left = $2;
                        $$.right = $4;
                        $$.type = "non-blocking assignment";
                    }


expression  : IDENTIFIER
            {
                // Assign the identifier to the expression.
                $$ = $1;
            }
            | NUMBER
            {
                // Convert the number to a string and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%d", $1);
                $$ = str;
            }
            | NUMBER_EXPR
            {
                // Assign the number expression to the expression.
                $$ = $1;
            }
            | expression '=' expression
            {
                // Create a string representation of the assignment expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s = %s", $1, $3);
                $$ = str;
            }
            | expression '+' expression
            {
                // Create a string representation of the addition expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s + %s", $1, $3);
                $$ = str;
            }
            | expression '-' expression
            {
                // Create a string representation of the subtraction expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s - %s", $1, $3);
                $$ = str;
            }
            | expression '*' expression
            {
                // Create a string representation of the multiplication expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s * %s", $1, $3);
                $$ = str;
            }
            | expression '/' expression
            {
                // Create a string representation of the division expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s / %s", $1, $3);
                $$ = str;
            }
            | expression '%' expression
            {
                // Create a string representation of the modulo expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s %% %s", $1, $3);
                $$ = str;
            }
            | expression '&' expression
            {
                // Create a string representation of the bitwise AND expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s & %s", $1, $3);
                $$ = str;
            }
            | expression '|' expression
            {
                // Create a string representation of the bitwise OR expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s | %s", $1, $3);
                $$ = str;
            }
            | expression '^' expression
            {
                // Create a string representation of the bitwise XOR expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s ^ %s", $1, $3);
                $$ = str;
            }
            |'~' expression
            {
                // Create a string representation of the bitwise complement expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "~%s", $2);
                $$ = str;
            }
            | '!' expression
            {
                // Create a string representation of the logical NOT expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "!%s", $2);
                $$ = str;
            }
            | expression '<' expression
            {
                // Create a string representation of the less than expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s < %s", $1, $3);
                $$ = str;
            }
            | expression '>' expression
            {
                // Create a string representation of the greater than expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s > %s", $1, $3);
                $$ = str;
            }
            | expression LE expression
            {
                // Create a string representation of the less than or equal to expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s <= %s", $1, $3);
                $$ = str;
            }
            | expression EQ expression
            {
                // Create a string representation of the equal to expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s == %s", $1, $3);
                $$ = str;
            }
            | expression NE expression
            {
                // Create a string representation of the not equal to expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s != %s", $1, $3);
                $$ = str;
            }
            | expression AND expression
            {
                // Create a string representation of the logical AND expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s && %s", $1, $3);
                $$ = str;
            }
            | expression OR expression
            {
                // Create a string representation of the logical OR expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s || %s", $1, $3);
                $$ = str;
            }
            | expression NAND expression
            {
                // Create a string representation of the logical NAND expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s !& %s", $1, $3);
                $$ = str;
            }
            | expression NOR expression
            {
                // Create a string representation of the logical NOR expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s !| %s", $1, $3);
                $$ = str;
            }
            | expression XOR expression
            {
                // Create a string representation of the logical XOR expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s ^| %s", $1, $3);
                $$ = str;
            }
            | expression XNOR expression
            {
                // Create a string representation of the logical XNOR expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s ^& %s", $1, $3);
                $$ = str;
            }
            | '(' expression ')'
            {
                // Assign the expression inside parentheses to the expression.
                $$ = $2;
            }
            | expression '?' expression ':' expression
            {
                // Create a string representation of the ternary expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s ? %s : %s", $1, $3, $5);
                $$ = str;
            }
            | expression '[' expression ']'
            {
                // Create a string representation of the array indexing expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s[%s]", $1, $3);
                $$ = str;
            }
            | expression '[' expression ':' expression ']'
            {
                // Create a string representation of the sliced array expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s[%s:%s]", $1, $3, $5);
                $$ = str;
            }
            | POSEDGE expression
            {
                // Create a string representation of the positive edge-triggered expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "posedge %s", $2);
                $$ = str;
            }
            | NEGEDGE expression
            {
                // Create a string representation of the negative edge-triggered expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "negedge %s", $2);
                $$ = str;
            }
            | NEGEDGE expression OR_WORD POSEDGE expression
            {
                // Create a string representation of the combined edge-triggered expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "negedge %s or posedge %s", $2, $5);
                $$ = str;
            }
            | POSEDGE expression OR_WORD NEGEDGE expression
            {
                // Create a string representation of the combined edge-triggered expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "posedge %s or negedge %s", $2, $5);
                $$ = str;
            }
            | '{' expression '}'
            {
                // Create a string representation of the expression enclosed in curly braces and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "{%s}", $2);
                $$ = str;
            }
            | expression ',' expression
            {
                // Create a string representation of the comma-separated expression and assign it to the expression.
                char *str = (char *)malloc(sizeof(char) * 64);
                sprintf(str, "%s , %s", $1, $3);
                $$ = str;
            }

%%
    

void yyerror(const char *msg)
{
    // Print an error message to the standard error stream.
    fprintf(stderr, "Error: %s\n", msg);
    
    // Terminate the program with a non-zero exit code.
    exit(1);
}

int main (int argc, char** argv) 
{
    // Start a JSON object with a key "parsing from..." and the value of the command line argument.
    json_start_object("parsing from...", *argv);
    
    // Invoke the parser function.
    yyparse();
    
    // Return 0 to indicate successful execution.
    return 0;
}
