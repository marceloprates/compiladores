#ifndef lint
static const char yysccsid[] = "@(#)yaccpar	1.9 (Berkeley) 02/21/93";
#endif

#define YYBYACC 1
#define YYMAJOR 1
#define YYMINOR 9
#define YYPATCH 20120115

#define YYEMPTY        (-1)
#define yyclearin      (yychar = YYEMPTY)
#define yyerrok        (yyerrflag = 0)
#define YYRECOVERING() (yyerrflag != 0)

#define YYPREFIX "yy"

#define YYPURE 0

#line 2 "parser.y"
	/* Lucas Martinelli Tabajara, Marcelo de Oliveira Rosa Prates*/

	#include <stdlib.h>
	#include <stdio.h>
	#include <string.h>
	#include "hash.h"
	#include "ast.h"

	AST* root;
#line 15 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ linkedList_t* symbol; AST* ast; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 38 "y.tab.c"

/* compatibility with bison */
#ifdef YYPARSE_PARAM
/* compatibility with FreeBSD */
# ifdef YYPARSE_PARAM_TYPE
#  define YYPARSE_DECL() yyparse(YYPARSE_PARAM_TYPE YYPARSE_PARAM)
# else
#  define YYPARSE_DECL() yyparse(void *YYPARSE_PARAM)
# endif
#else
# define YYPARSE_DECL() yyparse(void)
#endif

/* Parameters sent to lex. */
#ifdef YYLEX_PARAM
# define YYLEX_DECL() yylex(void *YYLEX_PARAM)
# define YYLEX yylex(YYLEX_PARAM)
#else
# define YYLEX_DECL() yylex(void)
# define YYLEX yylex()
#endif

/* Parameters sent to yyerror. */
#ifndef YYERROR_DECL
#define YYERROR_DECL() yyerror(const char *s)
#endif
#ifndef YYERROR_CALL
#define YYERROR_CALL(msg) yyerror(msg)
#endif

extern int YYPARSE_DECL();

#define KW_WORD 257
#define KW_BOOL 258
#define KW_BYTE 259
#define KW_IF 260
#define KW_THEN 261
#define KW_ELSE 262
#define KW_LOOP 263
#define KW_INPUT 264
#define KW_RETURN 265
#define KW_OUTPUT 266
#define OPERATOR_LE 267
#define OPERATOR_GE 268
#define OPERATOR_EQ 269
#define OPERATOR_NE 270
#define OPERATOR_AND 271
#define OPERATOR_OR 272
#define TK_IDENTIFIER 273
#define LIT_INTEGER 274
#define LIT_FALSE 275
#define LIT_TRUE 276
#define LIT_CHAR 277
#define LIT_STRING 278
#define TOKEN_ERROR 279
#define IFX 280
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    1,    1,    2,    3,    3,    4,    4,    5,    6,
    6,    7,    7,    8,    8,    8,    9,    9,    9,    9,
   10,   10,   11,   12,   12,   13,   14,   14,   15,   15,
   16,   16,   17,   17,   18,   18,   19,   20,   20,   21,
   21,   21,   21,   21,   21,   21,   22,   23,   23,   23,
   24,   25,   26,   26,   27,   27,   28,   28,   29,   30,
   30,   30,   30,   30,   30,   30,   30,   30,   30,   30,
   30,   30,   30,   30,   30,   30,   30,
};
static const short yylen[] = {                            2,
    1,    2,    0,    1,    2,    1,    1,    6,    2,    2,
    0,    3,    4,    1,    1,    1,    1,    1,    1,    1,
    2,    0,    3,    3,    0,    5,    1,    4,    1,    0,
    4,    2,    1,    0,    3,    1,    3,    3,    0,    1,
    1,    1,    1,    1,    1,    0,    3,    6,    8,    5,
    2,    2,    1,    1,    1,    0,    3,    1,    2,    1,
    4,    1,    3,    3,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    2,    2,
};
static const short yydefred[] = {                         3,
    0,    0,   14,   15,   16,    2,    0,    7,    0,    6,
   25,    5,    4,    0,    0,    0,    0,    0,    0,    0,
   12,   39,    0,    0,   23,   13,    0,   17,   18,   19,
   20,    9,    0,    0,    0,    0,   24,    0,    0,   32,
   26,    0,    0,    0,    0,    0,    0,   37,    0,    0,
   45,    0,   40,   41,   42,   43,   44,   22,    8,    0,
    0,    0,   51,    0,    0,    0,    0,   62,   60,    0,
   53,   58,   52,    0,    0,    0,    0,   38,    0,   31,
    0,    0,   77,    0,   76,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   21,    0,    0,   63,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   66,   67,
   57,   28,    0,   50,   61,    0,    0,    0,    0,   49,
};
static const short yydgoto[] = {                          1,
    2,   67,    6,    7,   21,   59,    8,    9,   68,   79,
   10,   16,   11,   69,   34,   35,  106,  107,   51,   36,
   52,   53,   54,   55,   56,   72,   73,   74,   57,   75,
};
static const short yysindex[] = {                         0,
    0, -196,    0,    0,    0,    0,  -44,    0,  -27,    0,
    0,    0,    0, -253,    2,  -74,   -1, -243, -252, -196,
    0,    0,    5,  -27,    0,    0,  -39,    0,    0,    0,
    0,    0, -253,   35,   41,  167,    0,   -1,   21,    0,
    0, -196,   47,   48, -253,  -32,  -38,    0,    4,   36,
    0,   37,    0,    0,    0,    0,    0,    0,    0, -253,
  -32,  -32,    0,  -32,  -32,  -32,  -21,    0,    0,  149,
    0,    0,    0,   54,  149,  -32,  -32,    0, -252,    0,
   30,   39,    0,   61,    0,  -32,  -32,  -32,  -32,  -32,
  -32,  -32,  -32,  -32,  -32,  -32,  -32,  -32,  -38,  128,
  149,    0, -156,  181,    0,   66,   67,  149,   77,   77,
   77,   77,  156,  156,   77,   77,  -29,  -29,    0,    0,
    0,    0,  181,    0,    0,  -32, -147,  149,  181,    0,
};
static const short yyrindex[] = {                         0,
    0,  118,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   84,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   86,   69,    0,    0,   71,    0,
    0,    0,    0,    0,    0,    0,  -56,    0,   74,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,  -15,    0,    0,  -54,
    0,    0,    0,  -52,  -43,    0,    0,    0,   79,    0,
    0,    0,    0,    0,    0,   95,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -48,    0,    0,  -47,    0,    0,  100,   -8,   50,   72,
   85,   96,   24,  109,  107,  120,   -4,    7,    0,    0,
    0,    0,  -47,    0,    0,    0,   83,   -6,  -47,    0,
};
static const short yygindex[] = {                         0,
    0,  425,    0,    0,  129,    0,  133,    1,   -5,    0,
    0,    0,    0,   10,    0,    0,    0,    0,  136,    0,
  -70,    0,    0,    0,    0,   55,    0,    0,    0,  402,
};
#define YYTABLESIZE 554
static const short yytable[] = {                         66,
   54,   65,   56,   64,   59,   66,   55,   65,   14,   64,
   47,   46,   97,   32,   12,   54,   24,   98,   86,   13,
   33,   28,   29,   30,   31,   27,   27,   27,   27,   27,
   27,   27,   36,  124,   35,   36,   64,   35,   64,   64,
   64,   20,   60,   27,   27,   50,   27,   65,   22,   65,
   65,   65,  127,   39,   64,   64,   19,   64,  130,   19,
    3,    4,    5,   37,   74,   65,   65,   74,   65,   76,
  103,   97,   95,  102,   96,   41,   98,   27,   58,  104,
   97,   95,   74,   96,   42,   98,   61,   62,   64,   93,
   70,   94,   18,   70,   76,   78,   77,   99,   93,   65,
   94,  105,   97,   95,  123,   96,  125,   98,   70,   70,
  126,   70,   71,   50,  129,   71,   74,    1,   97,   95,
   93,   96,   94,   98,   30,   72,   29,   46,   72,   11,
   71,   71,   50,   71,   27,   34,   73,   10,   50,   73,
   33,   48,   70,   72,   72,   26,   72,   68,   23,   75,
   68,   25,   75,  121,   73,   73,    0,   73,    0,    0,
   69,    0,    0,   69,   71,   68,   68,   75,   68,   97,
   95,    0,   96,    0,   98,    0,    0,   72,   69,   69,
    0,   69,    3,    4,    5,    0,    0,   93,   73,   94,
   97,   95,    0,   96,    0,   98,    0,   97,   95,   68,
   96,   75,   98,    0,    0,   56,    0,   59,   93,   55,
   94,    0,   69,   47,   46,   93,    0,   94,   54,    0,
  122,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   13,   28,   29,   30,   31,   71,
   13,   28,   29,   30,   31,   13,   27,    0,    0,    0,
    0,   27,   27,   27,   27,   27,   27,   64,    0,    0,
    0,    0,   64,   64,   64,   64,   64,   64,   65,    0,
    0,    0,    0,   65,   65,   65,   65,   65,   65,    0,
    0,    0,    0,    0,    0,   74,    0,    0,    0,   22,
    0,   48,    0,    0,   74,   74,   87,   88,   89,   90,
   91,   92,    0,   22,    0,   87,   88,   89,   90,   91,
   92,   70,    0,    0,    0,    0,   70,   70,   70,   70,
   70,   70,    0,    0,    0,    0,    0,   87,   88,   89,
   90,   91,   92,   71,    0,    0,    0,    0,   71,   71,
   71,   71,   71,   71,    0,    0,   72,    0,    0,    0,
    0,   72,   72,   72,   72,   72,   72,   73,    0,    0,
    0,    0,   73,   73,   73,   73,   73,   73,   68,    0,
   75,    0,    0,   68,   68,   68,   68,   68,   68,   75,
   75,   69,    0,    0,    0,    0,   69,   69,   69,   69,
   69,   69,    0,    0,   87,   88,   89,   90,   91,   92,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,   87,   88,   89,   90,   91,
   92,    0,   87,   88,   89,   90,   43,    0,    0,   44,
   45,   46,   47,   15,    0,    0,    0,    0,   17,   13,
   43,    0,    0,   44,   45,   46,   47,   70,   38,    0,
    0,    0,    0,   13,    0,    0,    0,   40,    0,    0,
   49,    0,   81,   82,    0,   83,   84,   85,    0,   63,
    0,    0,    0,    0,    0,    0,    0,  100,  101,    0,
    0,    0,    0,    0,   80,    0,    0,  108,  109,  110,
  111,  112,  113,  114,  115,  116,  117,  118,  119,  120,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  128,   49,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   49,    0,    0,
    0,    0,    0,   49,
};
static const short yycheck[] = {                         38,
   44,   40,   59,   42,   59,   38,   59,   40,   36,   42,
   59,   59,   42,   19,   59,   59,   16,   47,   40,  273,
   20,  274,  275,  276,  277,   41,   42,   43,   44,   45,
  274,   47,   41,  104,   41,   44,   41,   44,   43,   44,
   45,   40,   42,   59,   60,   36,   62,   41,  123,   43,
   44,   45,  123,   93,   59,   60,   58,   62,  129,   58,
  257,  258,  259,   59,   41,   59,   60,   44,   62,   91,
   41,   42,   43,   79,   45,   41,   47,   93,   58,   41,
   42,   43,   59,   45,   44,   47,   40,   40,   93,   60,
   41,   62,   91,   44,   91,   59,   61,   44,   60,   93,
   62,   41,   42,   43,  261,   45,   41,   47,   59,   60,
   44,   62,   41,  104,  262,   44,   93,    0,   42,   43,
   60,   45,   62,   47,   41,   41,   41,   59,   44,   59,
   59,   60,  123,   62,   61,   41,   41,   59,  129,   44,
   41,   59,   93,   59,   60,   17,   62,   41,   16,   41,
   44,   16,   44,   99,   59,   60,   -1,   62,   -1,   -1,
   41,   -1,   -1,   44,   93,   59,   60,   59,   62,   42,
   43,   -1,   45,   -1,   47,   -1,   -1,   93,   59,   60,
   -1,   62,  257,  258,  259,   -1,   -1,   60,   93,   62,
   42,   43,   -1,   45,   -1,   47,   -1,   42,   43,   93,
   45,   93,   47,   -1,   -1,  262,   -1,  262,   60,  262,
   62,   -1,   93,  262,  262,   60,   -1,   62,  262,   -1,
   93,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,  273,  274,  275,  276,  277,  278,
  273,  274,  275,  276,  277,  273,  262,   -1,   -1,   -1,
   -1,  267,  268,  269,  270,  271,  272,  262,   -1,   -1,
   -1,   -1,  267,  268,  269,  270,  271,  272,  262,   -1,
   -1,   -1,   -1,  267,  268,  269,  270,  271,  272,   -1,
   -1,   -1,   -1,   -1,   -1,  262,   -1,   -1,   -1,  123,
   -1,  125,   -1,   -1,  271,  272,  267,  268,  269,  270,
  271,  272,   -1,  123,   -1,  267,  268,  269,  270,  271,
  272,  262,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,   -1,   -1,   -1,   -1,   -1,  267,  268,  269,
  270,  271,  272,  262,   -1,   -1,   -1,   -1,  267,  268,
  269,  270,  271,  272,   -1,   -1,  262,   -1,   -1,   -1,
   -1,  267,  268,  269,  270,  271,  272,  262,   -1,   -1,
   -1,   -1,  267,  268,  269,  270,  271,  272,  262,   -1,
  262,   -1,   -1,  267,  268,  269,  270,  271,  272,  271,
  272,  262,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,   -1,   -1,  267,  268,  269,  270,  271,  272,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,  267,  268,  269,  270,  271,
  272,   -1,  267,  268,  269,  270,  260,   -1,   -1,  263,
  264,  265,  266,    9,   -1,   -1,   -1,   -1,   14,  273,
  260,   -1,   -1,  263,  264,  265,  266,   46,   24,   -1,
   -1,   -1,   -1,  273,   -1,   -1,   -1,   33,   -1,   -1,
   36,   -1,   61,   62,   -1,   64,   65,   66,   -1,   45,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   76,   77,   -1,
   -1,   -1,   -1,   -1,   60,   -1,   -1,   86,   87,   88,
   89,   90,   91,   92,   93,   94,   95,   96,   97,   98,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  126,  104,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,   -1,
   -1,   -1,   -1,  129,
};
#define YYFINAL 1
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 280
#if YYDEBUG
static const char *yyname[] = {

"end-of-file",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,"'$'",0,"'&'",0,"'('","')'","'*'","'+'","','","'-'",0,"'/'",0,0,0,0,0,0,0,0,
0,0,"':'","';'","'<'","'='","'>'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,"'['",0,"']'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,"'{'",0,"'}'",0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,"KW_WORD","KW_BOOL","KW_BYTE","KW_IF",
"KW_THEN","KW_ELSE","KW_LOOP","KW_INPUT","KW_RETURN","KW_OUTPUT","OPERATOR_LE",
"OPERATOR_GE","OPERATOR_EQ","OPERATOR_NE","OPERATOR_AND","OPERATOR_OR",
"TK_IDENTIFIER","LIT_INTEGER","LIT_FALSE","LIT_TRUE","LIT_CHAR","LIT_STRING",
"TOKEN_ERROR","IFX",
};
static const char *yyrule[] = {
"$accept : S",
"S : program",
"program : program item",
"program :",
"identifier : TK_IDENTIFIER",
"item : global_dec ';'",
"item : fun_def",
"global_dec : local_dec",
"global_dec : type identifier '[' LIT_INTEGER ']' array_init",
"scalar_init : ':' literal",
"array_init : ':' literal_list",
"array_init :",
"local_dec : type identifier scalar_init",
"local_dec : type '$' identifier scalar_init",
"type : KW_WORD",
"type : KW_BOOL",
"type : KW_BYTE",
"literal : LIT_INTEGER",
"literal : LIT_FALSE",
"literal : LIT_TRUE",
"literal : LIT_CHAR",
"literal_list : literal_list literal",
"literal_list :",
"fun_def : header local_type_decs block",
"local_type_decs : local_type_decs local_dec ';'",
"local_type_decs :",
"header : type identifier '(' parameter_list ')'",
"variable : identifier",
"variable : identifier '[' expr ']'",
"parameter_list : nonempty_parameter_list",
"parameter_list :",
"nonempty_parameter_list : nonempty_parameter_list ',' type identifier",
"nonempty_parameter_list : type identifier",
"argument_list : nonempty_argument_list",
"argument_list :",
"nonempty_argument_list : nonempty_argument_list ',' expr",
"nonempty_argument_list : expr",
"block : '{' command_list '}'",
"command_list : command_list command ';'",
"command_list :",
"command : atr",
"command : flow_control",
"command : input",
"command : output",
"command : return",
"command : block",
"command :",
"atr : variable '=' expr",
"flow_control : KW_IF '(' expr ')' KW_THEN command",
"flow_control : KW_IF '(' expr ')' KW_THEN command KW_ELSE command",
"flow_control : KW_LOOP '(' expr ')' command",
"input : KW_INPUT identifier",
"output : KW_OUTPUT element_list",
"element : LIT_STRING",
"element : expr",
"element_list : nonempty_element_list",
"element_list :",
"nonempty_element_list : nonempty_element_list ',' element",
"nonempty_element_list : element",
"return : KW_RETURN expr",
"expr : variable",
"expr : identifier '(' argument_list ')'",
"expr : literal",
"expr : '(' expr ')'",
"expr : expr '+' expr",
"expr : expr '-' expr",
"expr : expr '*' expr",
"expr : expr '/' expr",
"expr : expr '<' expr",
"expr : expr '>' expr",
"expr : expr OPERATOR_LE expr",
"expr : expr OPERATOR_GE expr",
"expr : expr OPERATOR_EQ expr",
"expr : expr OPERATOR_NE expr",
"expr : expr OPERATOR_AND expr",
"expr : expr OPERATOR_OR expr",
"expr : '&' expr",
"expr : '*' expr",

};
#endif

int      yydebug;
int      yynerrs;

int      yyerrflag;
int      yychar;
YYSTYPE  yyval;
YYSTYPE  yylval;

/* define the initial stack-sizes */
#ifdef YYSTACKSIZE
#undef YYMAXDEPTH
#define YYMAXDEPTH  YYSTACKSIZE
#else
#ifdef YYMAXDEPTH
#define YYSTACKSIZE YYMAXDEPTH
#else
#define YYSTACKSIZE 500
#define YYMAXDEPTH  500
#endif
#endif

#define YYINITSTACKSIZE 500

typedef struct {
    unsigned stacksize;
    short    *s_base;
    short    *s_mark;
    short    *s_last;
    YYSTYPE  *l_base;
    YYSTYPE  *l_mark;
} YYSTACKDATA;
/* variables for the parser stack */
static YYSTACKDATA yystack;
#line 251 "parser.y"

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}
#line 434 "y.tab.c"

#if YYDEBUG
#include <stdio.h>		/* needed for printf */
#endif

#include <stdlib.h>	/* needed for malloc, etc */
#include <string.h>	/* needed for memset */

/* allocate initial stack or double stack size, up to YYMAXDEPTH */
static int yygrowstack(YYSTACKDATA *data)
{
    int i;
    unsigned newsize;
    short *newss;
    YYSTYPE *newvs;

    if ((newsize = data->stacksize) == 0)
        newsize = YYINITSTACKSIZE;
    else if (newsize >= YYMAXDEPTH)
        return -1;
    else if ((newsize *= 2) > YYMAXDEPTH)
        newsize = YYMAXDEPTH;

    i = data->s_mark - data->s_base;
    newss = (short *)realloc(data->s_base, newsize * sizeof(*newss));
    if (newss == 0)
        return -1;

    data->s_base = newss;
    data->s_mark = newss + i;

    newvs = (YYSTYPE *)realloc(data->l_base, newsize * sizeof(*newvs));
    if (newvs == 0)
        return -1;

    data->l_base = newvs;
    data->l_mark = newvs + i;

    data->stacksize = newsize;
    data->s_last = data->s_base + newsize - 1;
    return 0;
}

#if YYPURE || defined(YY_NO_LEAKS)
static void yyfreestack(YYSTACKDATA *data)
{
    free(data->s_base);
    free(data->l_base);
    memset(data, 0, sizeof(*data));
}
#else
#define yyfreestack(data) /* nothing */
#endif

#define YYABORT  goto yyabort
#define YYREJECT goto yyabort
#define YYACCEPT goto yyaccept
#define YYERROR  goto yyerrlab

int
YYPARSE_DECL()
{
    int yym, yyn, yystate;
#if YYDEBUG
    const char *yys;

    if ((yys = getenv("YYDEBUG")) != 0)
    {
        yyn = *yys;
        if (yyn >= '0' && yyn <= '9')
            yydebug = yyn - '0';
    }
#endif

    yynerrs = 0;
    yyerrflag = 0;
    yychar = YYEMPTY;
    yystate = 0;

#if YYPURE
    memset(&yystack, 0, sizeof(yystack));
#endif

    if (yystack.s_base == NULL && yygrowstack(&yystack)) goto yyoverflow;
    yystack.s_mark = yystack.s_base;
    yystack.l_mark = yystack.l_base;
    yystate = 0;
    *yystack.s_mark = 0;

yyloop:
    if ((yyn = yydefred[yystate]) != 0) goto yyreduce;
    if (yychar < 0)
    {
        if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, reading %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
    }
    if ((yyn = yysindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: state %d, shifting to state %d\n",
                    YYPREFIX, yystate, yytable[yyn]);
#endif
        if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
        {
            goto yyoverflow;
        }
        yystate = yytable[yyn];
        *++yystack.s_mark = yytable[yyn];
        *++yystack.l_mark = yylval;
        yychar = YYEMPTY;
        if (yyerrflag > 0)  --yyerrflag;
        goto yyloop;
    }
    if ((yyn = yyrindex[yystate]) && (yyn += yychar) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yychar)
    {
        yyn = yytable[yyn];
        goto yyreduce;
    }
    if (yyerrflag) goto yyinrecovery;

    yyerror("syntax error");

    goto yyerrlab;

yyerrlab:
    ++yynerrs;

yyinrecovery:
    if (yyerrflag < 3)
    {
        yyerrflag = 3;
        for (;;)
        {
            if ((yyn = yysindex[*yystack.s_mark]) && (yyn += YYERRCODE) >= 0 &&
                    yyn <= YYTABLESIZE && yycheck[yyn] == YYERRCODE)
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: state %d, error recovery shifting\
 to state %d\n", YYPREFIX, *yystack.s_mark, yytable[yyn]);
#endif
                if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
                {
                    goto yyoverflow;
                }
                yystate = yytable[yyn];
                *++yystack.s_mark = yytable[yyn];
                *++yystack.l_mark = yylval;
                goto yyloop;
            }
            else
            {
#if YYDEBUG
                if (yydebug)
                    printf("%sdebug: error recovery discarding state %d\n",
                            YYPREFIX, *yystack.s_mark);
#endif
                if (yystack.s_mark <= yystack.s_base) goto yyabort;
                --yystack.s_mark;
                --yystack.l_mark;
            }
        }
    }
    else
    {
        if (yychar == 0) goto yyabort;
#if YYDEBUG
        if (yydebug)
        {
            yys = 0;
            if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
            if (!yys) yys = "illegal-symbol";
            printf("%sdebug: state %d, error recovery discards token %d (%s)\n",
                    YYPREFIX, yystate, yychar, yys);
        }
#endif
        yychar = YYEMPTY;
        goto yyloop;
    }

yyreduce:
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: state %d, reducing by rule %d (%s)\n",
                YYPREFIX, yystate, yyn, yyrule[yyn]);
#endif
    yym = yylen[yyn];
    if (yym)
        yyval = yystack.l_mark[1-yym];
    else
        memset(&yyval, 0, sizeof yyval);
    switch (yyn)
    {
case 1:
#line 81 "parser.y"
	{ root = yystack.l_mark[0].ast; }
break;
case 2:
#line 85 "parser.y"
	{ yyval.ast = CreateAST2(PROGRAM, NULL, yystack.l_mark[-1].ast, yystack.l_mark[0].ast); }
break;
case 3:
#line 86 "parser.y"
	{ yyval.ast = CreateAST0(PROGRAM, NULL); }
break;
case 4:
#line 90 "parser.y"
	{ yyval.ast = CreateAST0(IDENTIFIER, yystack.l_mark[0].symbol); }
break;
case 8:
#line 100 "parser.y"
	{ yyval.ast = CreateAST4(ARRAYDECLARATION, NULL, yystack.l_mark[-5].ast, yystack.l_mark[-4].ast, CreateAST0(LITERAL, yystack.l_mark[-2].symbol), yystack.l_mark[0].ast); }
break;
case 9:
#line 104 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 10:
#line 108 "parser.y"
	{ yyval.ast = CreateAST1(LITERALLIST, NULL, yystack.l_mark[0].ast); }
break;
case 11:
#line 109 "parser.y"
	{ yyval.ast = NULL; }
break;
case 12:
#line 113 "parser.y"
	{ yyval.ast = CreateAST3(DECLARATION, NULL, yystack.l_mark[-2].ast, yystack.l_mark[-1].ast, yystack.l_mark[0].ast); }
break;
case 13:
#line 114 "parser.y"
	{ yyval.ast = CreateAST3(POINTERDECLARATION, NULL, yystack.l_mark[-3].ast, yystack.l_mark[-1].ast, yystack.l_mark[0].ast); }
break;
case 14:
#line 118 "parser.y"
	{ yyval.ast = CreateAST0(TYPEWORD, NULL); }
break;
case 15:
#line 119 "parser.y"
	{ yyval.ast = CreateAST0(TYPEBOOL, NULL); }
break;
case 16:
#line 120 "parser.y"
	{ yyval.ast = CreateAST0(TYPEBYTE, NULL); }
break;
case 17:
#line 124 "parser.y"
	{ yyval.ast = CreateAST0(LITERAL, yystack.l_mark[0].symbol); }
break;
case 18:
#line 125 "parser.y"
	{ yyval.ast = CreateAST0(LITERAL, yystack.l_mark[0].symbol); }
break;
case 19:
#line 126 "parser.y"
	{ yyval.ast = CreateAST0(LITERAL, yystack.l_mark[0].symbol); }
break;
case 20:
#line 127 "parser.y"
	{ yyval.ast = CreateAST0(LITERAL, yystack.l_mark[0].symbol); }
break;
case 21:
#line 131 "parser.y"
	{ yyval.ast = CreateAST2(LITERALLIST, NULL, yystack.l_mark[-1].ast, yystack.l_mark[0].ast); }
break;
case 22:
#line 132 "parser.y"
	{ yyval.ast = CreateAST0(LITERALLIST, NULL); }
break;
case 23:
#line 136 "parser.y"
	{ yyval.ast = CreateAST3(FUNCTIONDEFINITION, NULL, yystack.l_mark[-2].ast, yystack.l_mark[-1].ast, yystack.l_mark[0].ast); }
break;
case 24:
#line 140 "parser.y"
	{ yyval.ast = CreateAST2(DECLARATIONLIST, NULL, yystack.l_mark[-2].ast, yystack.l_mark[-1].ast); }
break;
case 25:
#line 141 "parser.y"
	{ yyval.ast = CreateAST0(DECLARATIONLIST, NULL); }
break;
case 26:
#line 145 "parser.y"
	{ yyval.ast = CreateAST3(FUNCTIONHEADER, NULL, yystack.l_mark[-4].ast, yystack.l_mark[-3].ast, yystack.l_mark[-1].ast); }
break;
case 28:
#line 150 "parser.y"
	{ yyval.ast = CreateAST2(ARRAYACCESS, NULL, yystack.l_mark[-3].ast, yystack.l_mark[-1].ast); }
break;
case 30:
#line 155 "parser.y"
	{ yyval.ast = CreateAST0(PARAMETERLIST, NULL); }
break;
case 31:
#line 159 "parser.y"
	{ yyval.ast = CreateAST3(PARAMETERLIST, NULL, yystack.l_mark[-3].ast, yystack.l_mark[-1].ast, yystack.l_mark[0].ast); }
break;
case 32:
#line 160 "parser.y"
	{ yyval.ast = CreateAST2(PARAMETERLIST, NULL, yystack.l_mark[-1].ast, yystack.l_mark[0].ast); }
break;
case 34:
#line 165 "parser.y"
	{ yyval.ast = CreateAST0(ARGUMENTLIST, NULL); }
break;
case 35:
#line 169 "parser.y"
	{ yyval.ast = CreateAST2(ARGUMENTLIST, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 36:
#line 170 "parser.y"
	{ yyval.ast = CreateAST1(ARGUMENTLIST, NULL, yystack.l_mark[0].ast); }
break;
case 37:
#line 174 "parser.y"
	{ yyval.ast = CreateAST1(BLOCK, NULL, yystack.l_mark[-1].ast); }
break;
case 38:
#line 178 "parser.y"
	{ yyval.ast = CreateAST2(COMMANDLIST, NULL, yystack.l_mark[-2].ast, yystack.l_mark[-1].ast); }
break;
case 39:
#line 179 "parser.y"
	{ yyval.ast = CreateAST0(COMMANDLIST, NULL); }
break;
case 46:
#line 189 "parser.y"
	{ yyval.ast = NULL; }
break;
case 47:
#line 193 "parser.y"
	{ yyval.ast = CreateAST2(ASSIGNMENT, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 48:
#line 197 "parser.y"
	{ yyval.ast = CreateAST2(IFTHEN, NULL, yystack.l_mark[-3].ast, yystack.l_mark[0].ast); }
break;
case 49:
#line 198 "parser.y"
	{ yyval.ast = CreateAST3(IFTHENELSE, NULL, yystack.l_mark[-5].ast, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 50:
#line 199 "parser.y"
	{ yyval.ast = CreateAST2(LOOP, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 51:
#line 203 "parser.y"
	{ yyval.ast = CreateAST1(INPUT, NULL, yystack.l_mark[0].ast); }
break;
case 52:
#line 207 "parser.y"
	{ yyval.ast = CreateAST1(OUTPUT, NULL, yystack.l_mark[0].ast); }
break;
case 53:
#line 211 "parser.y"
	{ yyval.ast = CreateAST0(LITERAL, yystack.l_mark[0].symbol); }
break;
case 54:
#line 212 "parser.y"
	{ yyval.ast = yystack.l_mark[0].ast; }
break;
case 56:
#line 217 "parser.y"
	{ yyval.ast = CreateAST0(ELEMENTLIST, NULL); }
break;
case 57:
#line 221 "parser.y"
	{ yyval.ast = CreateAST2(ELEMENTLIST, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 58:
#line 222 "parser.y"
	{ yyval.ast = CreateAST1(ELEMENTLIST, NULL, yystack.l_mark[0].ast); }
break;
case 59:
#line 226 "parser.y"
	{ yyval.ast = CreateAST1(RETURN, NULL, yystack.l_mark[0].ast); }
break;
case 61:
#line 231 "parser.y"
	{ yyval.ast = CreateAST2(FUNCTIONCALL, NULL, yystack.l_mark[-3].ast, yystack.l_mark[-1].ast); }
break;
case 63:
#line 233 "parser.y"
	{ yyval.ast = yystack.l_mark[-1].ast; }
break;
case 64:
#line 234 "parser.y"
	{ yyval.ast = CreateAST2(ADDITION, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 65:
#line 235 "parser.y"
	{ yyval.ast = CreateAST2(SUBTRACTION, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 66:
#line 236 "parser.y"
	{ yyval.ast = CreateAST2(MULTIPLICATION, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 67:
#line 237 "parser.y"
	{ yyval.ast = CreateAST2(DIVISION, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 68:
#line 238 "parser.y"
	{ yyval.ast = CreateAST2(LESSERTHAN, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 69:
#line 239 "parser.y"
	{ yyval.ast = CreateAST2(GREATERTHAN, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 70:
#line 240 "parser.y"
	{ yyval.ast = CreateAST2(LESSEREQUAL, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 71:
#line 241 "parser.y"
	{ yyval.ast = CreateAST2(GREATEREQUAL, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 72:
#line 242 "parser.y"
	{ yyval.ast = CreateAST2(EQUAL, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 73:
#line 243 "parser.y"
	{ yyval.ast = CreateAST2(NOTEQUAL, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 74:
#line 244 "parser.y"
	{ yyval.ast = CreateAST2(AND, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 75:
#line 245 "parser.y"
	{ yyval.ast = CreateAST2(OR, NULL, yystack.l_mark[-2].ast, yystack.l_mark[0].ast); }
break;
case 76:
#line 246 "parser.y"
	{ yyval.ast = CreateAST1(REF, NULL, yystack.l_mark[0].ast); }
break;
case 77:
#line 247 "parser.y"
	{ yyval.ast = CreateAST1(DEREF, NULL, yystack.l_mark[0].ast); }
break;
#line 888 "y.tab.c"
    }
    yystack.s_mark -= yym;
    yystate = *yystack.s_mark;
    yystack.l_mark -= yym;
    yym = yylhs[yyn];
    if (yystate == 0 && yym == 0)
    {
#if YYDEBUG
        if (yydebug)
            printf("%sdebug: after reduction, shifting from state 0 to\
 state %d\n", YYPREFIX, YYFINAL);
#endif
        yystate = YYFINAL;
        *++yystack.s_mark = YYFINAL;
        *++yystack.l_mark = yyval;
        if (yychar < 0)
        {
            if ((yychar = YYLEX) < 0) yychar = 0;
#if YYDEBUG
            if (yydebug)
            {
                yys = 0;
                if (yychar <= YYMAXTOKEN) yys = yyname[yychar];
                if (!yys) yys = "illegal-symbol";
                printf("%sdebug: state %d, reading %d (%s)\n",
                        YYPREFIX, YYFINAL, yychar, yys);
            }
#endif
        }
        if (yychar == 0) goto yyaccept;
        goto yyloop;
    }
    if ((yyn = yygindex[yym]) && (yyn += yystate) >= 0 &&
            yyn <= YYTABLESIZE && yycheck[yyn] == yystate)
        yystate = yytable[yyn];
    else
        yystate = yydgoto[yym];
#if YYDEBUG
    if (yydebug)
        printf("%sdebug: after reduction, shifting from state %d \
to state %d\n", YYPREFIX, *yystack.s_mark, yystate);
#endif
    if (yystack.s_mark >= yystack.s_last && yygrowstack(&yystack))
    {
        goto yyoverflow;
    }
    *++yystack.s_mark = (short) yystate;
    *++yystack.l_mark = yyval;
    goto yyloop;

yyoverflow:
    yyerror("yacc stack overflow");

yyabort:
    yyfreestack(&yystack);
    return (1);

yyaccept:
    yyfreestack(&yystack);
    return (0);
}
