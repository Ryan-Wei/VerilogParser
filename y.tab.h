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
    IDENTIFIER = 264,
    NUMBER = 265,
    BEGIN_TOKEN = 266,
    END_TOKEN = 267,
    ALWAYS = 268,
    IF = 269,
    ELSE = 270,
    CASE = 271,
    DEFAULT = 272,
    ASSIGN = 273
  };
#endif
/* Tokens.  */
#define MODULE 258
#define ENDMODULE 259
#define INPUT 260
#define OUTPUT 261
#define WIRE 262
#define REG 263
#define IDENTIFIER 264
#define NUMBER 265
#define BEGIN_TOKEN 266
#define END_TOKEN 267
#define ALWAYS 268
#define IF 269
#define ELSE 270
#define CASE 271
#define DEFAULT 272
#define ASSIGN 273

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 14 "src/verilogParser.y"

    struct module_body_t 
    {
        struct internal_port_list_t *internal_port_list;
        struct always_list_t *always_list;
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

    struct caseItemList_t 
    {
        struct caseItem_t *caseItems;
        int count;
    } *caseItemList;

    struct caseItem_t 
    {
        char *type;
        char *value;
    } caseItem;

    char* strval;
    int intval;


#line 158 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
