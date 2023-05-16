/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.1"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/verilogParser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

extern int yylex();
void yyerror(const char *msg);

#line 81 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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


#line 234 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */

/* Second part of user prologue.  */
#line 133 "src/verilogParser.y"


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



#line 376 "y.tab.c"


#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))

/* Stored state numbers (used for stacks). */
typedef yytype_int8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  6
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   231

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  41
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  14
/* YYNRULES -- Number of rules.  */
#define YYNRULES  57
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  125

#define YYUNDEFTOK  2
#define YYMAXUTOK   273


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    39,     2,     2,     2,    31,    32,     2,
      19,    20,    29,    27,    22,    28,     2,    30,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,    24,    21,
      36,    38,    37,    40,    26,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    23,     2,    25,    34,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,    33,     2,    35,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   262,   262,   268,   269,   272,   323,   330,   338,   345,
     353,   359,   365,   371,   377,   383,   389,   395,   401,   407,
     415,   421,   429,   436,   446,   453,   458,   462,   473,   483,
     493,   503,   534,   538,   544,   545,   546,   547,   548,   549,
     550,   551,   552,   553,   554,   555,   556,   557,   558,   559,
     560,   561,   562,   563,   569,   573,   579,   585
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "MODULE", "ENDMODULE", "INPUT", "OUTPUT",
  "WIRE", "REG", "IDENTIFIER", "NUMBER", "BEGIN_TOKEN", "END_TOKEN",
  "ALWAYS", "IF", "ELSE", "CASE", "DEFAULT", "ASSIGN", "'('", "')'", "';'",
  "','", "'['", "':'", "']'", "'@'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "'&'", "'|'", "'^'", "'~'", "'<'", "'>'", "'='", "'!'", "'?'", "$accept",
  "verilog_file", "module_declaration_list", "module_declaration",
  "port_list", "internal_port_list", "port_declaration", "module_body",
  "always_list", "always_block", "statement_block", "statement_list",
  "statement", "expression", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,    40,
      41,    59,    44,    91,    58,    93,    64,    43,    45,    42,
      47,    37,    38,   124,    94,   126,    60,    62,    61,    33,
      63
};
# endif

#define YYPACT_NINF (-66)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      -2,    -4,     6,    -2,   -66,     4,   -66,   -66,   180,   169,
     171,   172,   173,     1,   -18,   -66,   -66,    16,   -66,    17,
     -66,    18,   -66,    34,    39,    45,   180,    41,    46,    62,
      65,    66,   180,   -66,    58,    59,    78,    98,   115,   210,
     105,   138,   119,   135,   137,   154,   177,   157,   140,   194,
     -66,   -66,   -66,   203,   204,   212,   213,   -66,   205,   -66,
     -66,   -66,   -66,   -66,   -66,   201,   -66,   -66,   201,     2,
      23,   214,   201,   201,   201,   201,   201,   201,   201,   201,
     201,   201,   201,   201,   201,   201,   201,   -66,   195,   -66,
      82,   136,   136,   136,   136,   136,   136,   136,   136,   136,
     136,   136,   136,   136,   100,   207,   -66,   189,   -66,    64,
     201,   -66,   201,   201,   -66,   -66,   -66,   118,   136,    44,
     -66,   195,   215,   195,   -66
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,     0,     2,     3,     0,     1,     4,     0,     0,
       0,     0,     0,    18,     0,     6,    10,     0,    11,     0,
      12,     0,    13,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     7,     0,     0,     0,     0,     0,    21,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    20,
      22,     8,     5,     0,     0,     0,     0,    19,     0,     9,
      23,    14,    15,    16,    17,     0,    32,    33,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    54,     0,    24,
       0,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    48,    49,     0,     0,    29,     0,    26,     0,
       0,    56,     0,     0,    25,    27,    28,     0,    55,     0,
      57,     0,    30,     0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -66,   -66,   -66,   224,   -66,   -66,   158,   -66,   -66,   179,
     160,   -66,    70,   -65
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     2,     3,     4,    14,    39,    15,    41,    49,    50,
     106,   107,   108,   109
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      69,     1,    25,    70,    26,     5,     6,    90,    91,    92,
      93,    94,    95,    96,    97,    98,    99,   100,   101,   102,
     103,   104,    71,     8,    24,    72,    27,    28,    29,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    87,    30,   117,    72,   118,   119,    31,
      73,    74,    75,    76,    77,    78,    79,    80,    81,    82,
      83,    84,    85,    86,   121,    34,    32,    72,    42,    43,
      35,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,   116,    36,    72,    44,    37,
      38,    73,    74,    75,    76,    77,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    72,   110,   111,    45,    73,
      74,    75,    76,    77,    78,    79,    80,    81,    82,    83,
      84,    85,    86,    72,   112,    46,    51,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    83,    84,    85,
      86,    72,    52,   120,    53,    73,    74,    75,    76,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    72,
      54,    59,    55,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    82,    83,    84,    85,    86,   115,    16,    56,
      18,    20,    22,    58,    33,     9,    10,    11,    12,    13,
      40,   122,    17,   124,    19,    21,    23,    48,    66,    67,
      88,   114,    57,   105,    66,    67,    88,    47,    68,   105,
      66,    67,    61,    62,    68,     9,    10,    11,    12,    13,
      68,    63,    64,    47,    65,    88,   113,     7,    60,     0,
     123,    89
};

static const yytype_int8 yycheck[] =
{
      65,     3,    20,    68,    22,     9,     0,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    20,    19,    23,    23,    10,    10,    10,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    20,    10,   110,    23,   112,   113,    10,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    20,    24,    21,    23,    10,    10,
      24,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    21,    24,    23,    10,    24,
      24,    27,    28,    29,    30,    31,    32,    33,    34,    35,
      36,    37,    38,    39,    40,    23,    24,    25,    10,    27,
      28,    29,    30,    31,    32,    33,    34,    35,    36,    37,
      38,    39,    40,    23,    24,    10,    21,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    23,     4,    25,    25,    27,    28,    29,    30,    31,
      32,    33,    34,    35,    36,    37,    38,    39,    40,    23,
      25,    21,    25,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,   107,     9,    25,
       9,     9,     9,    26,    26,     5,     6,     7,     8,     9,
      32,   121,    23,   123,    23,    23,    23,    39,     9,    10,
      11,    12,    25,    14,     9,    10,    11,    13,    19,    14,
       9,    10,     9,     9,    19,     5,     6,     7,     8,     9,
      19,     9,     9,    13,    19,    11,    19,     3,    49,    -1,
      15,    71
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,    42,    43,    44,     9,     0,    44,    19,     5,
       6,     7,     8,     9,    45,    47,     9,    23,     9,    23,
       9,    23,     9,    23,    23,    20,    22,    10,    10,    10,
      10,    10,    21,    47,    24,    24,    24,    24,    24,    46,
      47,    48,    10,    10,    10,    10,    10,    13,    47,    49,
      50,    21,     4,    25,    25,    25,    25,    25,    26,    21,
      50,     9,     9,     9,     9,    19,     9,    10,    19,    54,
      54,    20,    23,    27,    28,    29,    30,    31,    32,    33,
      34,    35,    36,    37,    38,    39,    40,    20,    11,    51,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    14,    51,    52,    53,    54,
      24,    25,    24,    19,    12,    53,    21,    54,    54,    54,
      25,    20,    53,    15,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    41,    42,    43,    43,    44,    45,    45,    46,    46,
      47,    47,    47,    47,    47,    47,    47,    47,    47,    47,
      48,    48,    49,    49,    50,    51,    52,    52,    53,    53,
      53,    53,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     1,     2,     8,     1,     3,     2,     3,
       2,     2,     2,     2,     7,     7,     7,     7,     1,     6,
       2,     1,     1,     2,     6,     3,     1,     2,     2,     1,
       5,     7,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     5,     4,     6
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            else
              goto append;

          append:
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 263 "src/verilogParser.y"
                {
                    // started by main()
                    json_end_object(); // end parsing from
                }
#line 1639 "y.tab.c"
    break;

  case 4:
#line 269 "src/verilogParser.y"
                                                                         { }
#line 1645 "y.tab.c"
    break;

  case 5:
#line 273 "src/verilogParser.y"
                    {
                        json_start_object("module", (yyvsp[-6].strval));
                            //json_add_string("name", $2);
                            json_start_object("ports", "port_list");
                                for (int i = 0; i < (yyvsp[-4].port_list) -> count; i++) 
                                {
                                    json_start_object("port", "port_declaration");
                                    //json_add_string("tag", "port_declaration");
                                    json_add_string("name", (yyvsp[-4].port_list) -> ports[i].name);
                                    json_add_string("type", (yyvsp[-4].port_list) -> ports[i].type);
                                    json_add_number("width", (yyvsp[-4].port_list) -> ports[i].width);
                                    json_end_object();
                                }
                            json_end_object(); // end external ports

                            json_start_object("module_body", "module_body");
                                if ((yyvsp[-1].module_body) -> internal_port_list) 
                                {
                                    json_start_object("internal_ports", "internal_port_list");
                                        //printf("internal port count: %d\n", $7 -> internal_port_list -> count);
                                        for (int i = 0; i < (yyvsp[-1].module_body) -> internal_port_list -> count; i++) 
                                        {
                                            json_start_object("port", "port_declaration");
                                                //json_add_string("tag", "port_declaration");
                                                json_add_string("name", (yyvsp[-1].module_body) -> internal_port_list -> ports[i].name);
                                                json_add_string("type", (yyvsp[-1].module_body) -> internal_port_list -> ports[i].type);
                                                json_add_number("width", (yyvsp[-1].module_body) -> internal_port_list -> ports[i].width);
                                            json_end_object();
                                        }
                                    json_end_object(); // end internal ports
                                }

                                if ((yyvsp[-1].module_body) -> always_list) 
                                {
                                    json_start_object("always_blocks", "always_list");
                                        for (int i = 0; i < (yyvsp[-1].module_body) -> always_list -> count; i++) 
                                        {
                                            json_start_object("always_block", "always_definition");
                                                json_add_string("condition", (yyvsp[-1].module_body) -> always_list -> always_block[i].condition);
                                                json_start_object("statement", (yyvsp[-1].module_body) -> always_list -> always_block[i].statement -> type);
                                                    print_statement((yyvsp[-1].module_body) -> always_list -> always_block[i].statement);
                                                json_end_object(); // end statement block
                                            json_end_object();
                                        }
                                    json_end_object(); // end always blocks
                                }
                            json_end_object(); // end module body
                        json_end_object(); // end module
                     }
#line 1699 "y.tab.c"
    break;

  case 6:
#line 324 "src/verilogParser.y"
                    {
                        (yyval.port_list) = (struct port_list_t *)malloc(sizeof(struct port_list_t));
                        (yyval.port_list) -> ports = (struct port_t *)malloc(sizeof(struct port_t));
                        (yyval.port_list) -> ports[0] = (yyvsp[0].port);
                        (yyval.port_list) -> count = 1;
                    }
#line 1710 "y.tab.c"
    break;

  case 7:
#line 331 "src/verilogParser.y"
                    {
                        (yyval.port_list) = (yyvsp[-2].port_list);
                        (yyval.port_list) -> ports = (struct port_t *)realloc((yyval.port_list) -> ports, sizeof(struct port_t) * ((yyvsp[-2].port_list) -> count + 1));
                        (yyval.port_list) -> ports[(yyvsp[-2].port_list) -> count] = (yyvsp[0].port);
                        (yyval.port_list) -> count = (yyvsp[-2].port_list) -> count + 1;
                    }
#line 1721 "y.tab.c"
    break;

  case 8:
#line 339 "src/verilogParser.y"
                    {
                        (yyval.internal_port_list) = (struct internal_port_list_t *)malloc(sizeof(struct internal_port_list_t));
                        (yyval.internal_port_list) -> ports = (struct port_t *)malloc(sizeof(struct port_t));
                        (yyval.internal_port_list) -> ports[0] = (yyvsp[-1].port);
                        (yyval.internal_port_list) -> count = 1;
                    }
#line 1732 "y.tab.c"
    break;

  case 9:
#line 346 "src/verilogParser.y"
                    {
                        (yyval.internal_port_list) = (yyvsp[-2].internal_port_list);
                        (yyval.internal_port_list) -> ports = (struct port_t *)realloc((yyval.internal_port_list) -> ports, sizeof(struct port_t) * ((yyvsp[-2].internal_port_list) -> count + 1));
                        (yyval.internal_port_list) -> ports[(yyvsp[-2].internal_port_list) -> count] = (yyvsp[-1].port);
                        (yyval.internal_port_list) -> count = (yyvsp[-2].internal_port_list) -> count + 1;
                    }
#line 1743 "y.tab.c"
    break;

  case 10:
#line 354 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "input";
                        (yyval.port).width = 1;
                    }
#line 1753 "y.tab.c"
    break;

  case 11:
#line 360 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "output";
                        (yyval.port).width = 1;
                    }
#line 1763 "y.tab.c"
    break;

  case 12:
#line 366 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "wire";
                        (yyval.port).width = 1;
                    }
#line 1773 "y.tab.c"
    break;

  case 13:
#line 372 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "reg";
                        (yyval.port).width = 1;
                    }
#line 1783 "y.tab.c"
    break;

  case 14:
#line 378 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "input";
                        (yyval.port).width = abs((yyvsp[-4].intval) - (yyvsp[-2].intval)) + 1;
                    }
#line 1793 "y.tab.c"
    break;

  case 15:
#line 384 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "output";
                        (yyval.port).width = abs((yyvsp[-4].intval) - (yyvsp[-2].intval)) + 1;
                    }
#line 1803 "y.tab.c"
    break;

  case 16:
#line 390 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "wire";
                        (yyval.port).width = abs((yyvsp[-4].intval) - (yyvsp[-2].intval)) + 1;
                    }
#line 1813 "y.tab.c"
    break;

  case 17:
#line 396 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "reg";
                        (yyval.port).width = abs((yyvsp[-4].intval) - (yyvsp[-2].intval)) + 1;
                    }
#line 1823 "y.tab.c"
    break;

  case 18:
#line 402 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[0].strval);
                        (yyval.port).type = "wire";
                        (yyval.port).width = 1;
                    }
#line 1833 "y.tab.c"
    break;

  case 19:
#line 408 "src/verilogParser.y"
                    {
                        (yyval.port).name = (yyvsp[-5].strval);
                        (yyval.port).type = "wire";
                        (yyval.port).width = abs((yyvsp[-3].intval) - (yyvsp[-1].intval)) + 1;
                    }
#line 1843 "y.tab.c"
    break;

  case 20:
#line 416 "src/verilogParser.y"
                {
                    (yyval.module_body) = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    (yyval.module_body) -> internal_port_list = (yyvsp[-1].internal_port_list);
                    (yyval.module_body) -> always_list = (yyvsp[0].always_list);
                }
#line 1853 "y.tab.c"
    break;

  case 21:
#line 422 "src/verilogParser.y"
                {
                    (yyval.module_body) = (struct module_body_t *)malloc(sizeof(struct module_body_t));
                    (yyval.module_body) -> internal_port_list = (yyvsp[0].internal_port_list);
                    (yyval.module_body) -> always_list = NULL;
                }
#line 1863 "y.tab.c"
    break;

  case 22:
#line 430 "src/verilogParser.y"
                {
                    (yyval.always_list) = (struct always_list_t *)malloc(sizeof(struct always_list_t));
                    (yyval.always_list) -> always_block = (struct always_block_t *)malloc(sizeof(struct always_block_t));
                    (yyval.always_list) -> always_block[0] = (yyvsp[0].always_block);
                    (yyval.always_list) -> count = 1;
                }
#line 1874 "y.tab.c"
    break;

  case 23:
#line 437 "src/verilogParser.y"
                {
                    (yyval.always_list) = (yyvsp[-1].always_list);
                    (yyval.always_list) -> always_block = (struct always_block_t *)realloc((yyval.always_list) -> always_block, sizeof(struct always_block_t) * ((yyvsp[-1].always_list) -> count + 1));
                    (yyval.always_list) -> always_block[(yyvsp[-1].always_list) -> count] = (yyvsp[0].always_block);
                    (yyval.always_list) -> count = (yyvsp[-1].always_list) -> count + 1;
                }
#line 1885 "y.tab.c"
    break;

  case 24:
#line 447 "src/verilogParser.y"
                {
                    (yyval.always_block).condition = (yyvsp[-2].strval);
                    (yyval.always_block).statement = (yyvsp[0].statement);
                }
#line 1894 "y.tab.c"
    break;

  case 25:
#line 454 "src/verilogParser.y"
                    {
                        (yyval.statement) = (yyvsp[-1].statement);
                    }
#line 1902 "y.tab.c"
    break;

  case 26:
#line 459 "src/verilogParser.y"
                    {
                        (yyval.statement) = (yyvsp[0].statement);
                    }
#line 1910 "y.tab.c"
    break;

  case 27:
#line 463 "src/verilogParser.y"
                    {
                        (yyval.statement) = (yyvsp[-1].statement);
                        struct statement_t *p = (yyval.statement);
                        while (p -> tail) 
                        {
                            p = p -> tail;
                        }
                        p -> tail = (yyvsp[0].statement);
                    }
#line 1924 "y.tab.c"
    break;

  case 28:
#line 474 "src/verilogParser.y"
            {
                (yyval.statement) = (struct statement_t *)malloc(sizeof(struct statement_t));
                (yyval.statement) -> head = NULL;
                (yyval.statement) -> tail = NULL;
                (yyval.statement) -> expression = (yyvsp[-1].strval);
                (yyval.statement) -> flag = 1;
                (yyval.statement) -> type = "ordinary_statement";
                (yyval.statement) -> condition = NULL;
            }
#line 1938 "y.tab.c"
    break;

  case 29:
#line 484 "src/verilogParser.y"
            {
                (yyval.statement) = (struct statement_t *)malloc(sizeof(struct statement_t));
                (yyval.statement) -> head = (yyvsp[0].statement);
                (yyval.statement) -> tail = NULL;
                (yyval.statement) -> expression = NULL;
                (yyval.statement) -> flag = 0;
                (yyval.statement) -> type = "ordinary_statement";
                (yyval.statement) -> condition = NULL;
            }
#line 1952 "y.tab.c"
    break;

  case 30:
#line 494 "src/verilogParser.y"
            {
                (yyval.statement) = (struct statement_t *)malloc(sizeof(struct statement_t));
                (yyval.statement) -> head = (yyvsp[0].statement);
                (yyval.statement) -> tail = NULL;
                (yyval.statement) -> expression = NULL;
                (yyval.statement) -> flag = 0;
                (yyval.statement) -> type = "if_statement";
                (yyval.statement) -> condition = (yyvsp[-2].strval);
            }
#line 1966 "y.tab.c"
    break;

  case 31:
#line 504 "src/verilogParser.y"
            {
                (yyval.statement) = (struct statement_t *)malloc(sizeof(struct statement_t));
                (yyval.statement) -> head = (yyvsp[-2].statement);

                (yyval.statement) -> tail = (struct statement_t *)malloc(sizeof(struct statement_t));
                (yyval.statement) -> tail -> head = (yyvsp[0].statement);
                (yyval.statement) -> tail -> tail = NULL;
                (yyval.statement) -> tail -> expression = NULL;
                (yyval.statement) -> tail -> flag = 0;
                (yyval.statement) -> tail -> type = "else_statement";
                (yyval.statement) -> tail -> condition = NULL;

                (yyval.statement) -> expression = NULL;
                (yyval.statement) -> flag = 0;
                (yyval.statement) -> type = "if_statement";
                (yyval.statement) -> condition = (yyvsp[-4].strval);
            }
#line 1988 "y.tab.c"
    break;

  case 32:
#line 535 "src/verilogParser.y"
            {
                (yyval.strval) = (yyvsp[0].strval);
            }
#line 1996 "y.tab.c"
    break;

  case 33:
#line 539 "src/verilogParser.y"
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%d", (yyvsp[0].intval));
                (yyval.strval) = str;
            }
#line 2006 "y.tab.c"
    break;

  case 53:
#line 564 "src/verilogParser.y"
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s != %s", (yyvsp[-2].strval), (yyvsp[0].strval));
                (yyval.strval) = str;
            }
#line 2016 "y.tab.c"
    break;

  case 54:
#line 570 "src/verilogParser.y"
            {
                (yyval.strval) = (yyvsp[-1].strval);
            }
#line 2024 "y.tab.c"
    break;

  case 55:
#line 574 "src/verilogParser.y"
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s ? %s : %s", (yyvsp[-4].strval), (yyvsp[-2].strval), (yyvsp[0].strval));
                (yyval.strval) = str;
            }
#line 2034 "y.tab.c"
    break;

  case 56:
#line 580 "src/verilogParser.y"
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s[%s]", (yyvsp[-3].strval), (yyvsp[-1].strval));
                (yyval.strval) = str;
            }
#line 2044 "y.tab.c"
    break;

  case 57:
#line 586 "src/verilogParser.y"
            {
                char *str = (char *)malloc(sizeof(char) * 32);
                sprintf(str, "%s[%s:%s]", (yyvsp[-5].strval), (yyvsp[-3].strval), (yyvsp[-1].strval));
                (yyval.strval) = str;
            }
#line 2054 "y.tab.c"
    break;


#line 2058 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;


#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 593 "src/verilogParser.y"


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
