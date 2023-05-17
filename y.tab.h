/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    MODULE = 258,
    ENDMODULE = 259,
    INPUT = 260,
    OUTPUT = 261,
    WIRE = 262,
    REG = 263,
    INTEGER = 264,
    IDENTIFIER = 265,
    NUMBER = 266,
    NUMBER_EXPR = 267,
    BEGIN_TOKEN = 268,
    END_TOKEN = 269,
    ALWAYS = 270,
    IF = 271,
    ELSE = 272,
    ASSIGN = 273,
    LE = 274,
    GE = 275,
    EQ = 276,
    NE = 277,
    AND = 278,
    OR = 279,
    NAND = 280,
    NOR = 281,
    XOR = 282,
    XNOR = 283,
    POSEDGE = 284,
    NEGEDGE = 285,
    OR_WORD = 286
  };
#endif
/* Tokens.  */
#define MODULE 258
#define ENDMODULE 259
#define INPUT 260
#define OUTPUT 261
#define WIRE 262
#define REG 263
#define INTEGER 264
#define IDENTIFIER 265
#define NUMBER 266
#define NUMBER_EXPR 267
#define BEGIN_TOKEN 268
#define END_TOKEN 269
#define ALWAYS 270
#define IF 271
#define ELSE 272
#define ASSIGN 273
#define LE 274
#define GE 275
#define EQ 276
#define NE 277
#define AND 278
#define OR 279
#define NAND 280
#define NOR 281
#define XOR 282
#define XNOR 283
#define POSEDGE 284
#define NEGEDGE 285
#define OR_WORD 286

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "src/verilogParser.y"

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


#line 186 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
