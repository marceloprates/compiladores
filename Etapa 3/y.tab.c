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
#line 12 "parser.y"
#ifdef YYSTYPE
#undef  YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
#endif
#ifndef YYSTYPE_IS_DECLARED
#define YYSTYPE_IS_DECLARED 1
typedef union{ linkedList_t* symbol; } YYSTYPE;
#endif /* !YYSTYPE_IS_DECLARED */
#line 35 "y.tab.c"

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
    0,    0,    1,    1,    2,    5,    5,    6,    6,    7,
    8,    8,   11,   12,   12,    4,    4,    4,    9,   10,
   10,    3,   14,   14,   13,   17,   17,   17,   16,   16,
   19,   19,   20,   20,   21,   21,   15,   22,   22,   23,
   23,   23,   23,   23,   23,   24,   29,   29,   25,   25,
   25,   30,   31,   26,   27,   33,   33,   32,   34,   34,
   28,   18,   18,   18,   18,   18,   18,   18,   18,   18,
   18,   18,   18,   18,   18,   18,   18,   18,   18,   35,
   35,
};
static const short yylen[] = {                            2,
    2,    0,    2,    1,    2,    2,    3,    1,    4,    2,
    2,    0,    2,    2,    3,    1,    1,    1,    4,    2,
    0,    3,    3,    0,    5,    1,    4,    1,    3,    0,
    4,    0,    2,    0,    3,    0,    3,    3,    0,    1,
    1,    1,    1,    1,    1,    2,    2,    5,    1,    1,
    5,    6,    8,    2,    2,    1,    1,    2,    2,    0,
    2,    2,    4,    1,    3,    3,    3,    3,    3,    3,
    3,    3,    3,    3,    3,    3,    3,    2,    2,    3,
    0,
};
static const short yydefred[] = {                         0,
   16,   17,   18,    0,    0,    0,    4,    0,   24,    1,
    3,    0,    0,    5,    0,    0,    0,    0,    6,    8,
    0,    0,    0,    0,   22,    0,    0,   10,    0,    0,
    7,    0,    0,    0,    0,    0,    0,   45,    0,    0,
   40,   41,   42,   43,   44,   49,   50,    0,    0,   13,
   23,    0,    0,    0,   25,    0,    0,   54,    0,    0,
    0,    0,   64,    0,   56,    0,   55,    0,    0,    0,
   46,   37,    0,   14,    0,    0,    9,    0,    0,   29,
    0,    0,    0,    0,   62,   79,    0,   78,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   58,    0,    0,   38,   15,    0,   11,   19,    0,
    0,    0,    0,    0,   28,    0,    0,   65,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   68,   69,
   59,    0,   20,    0,    0,   51,   80,    0,    0,   33,
   63,    0,   31,    0,    0,    0,    0,    0,   27,   35,
   53,
};
static const short yydgoto[] = {                          4,
    5,    6,    7,    8,   14,   19,   20,   77,   63,  108,
   24,   50,    9,   15,   38,   30,  116,   66,   80,  117,
  140,   39,   40,   41,   42,   43,   44,   45,   71,   46,
   47,   67,   68,  102,   85,
};
static const short yysindex[] = {                       -57,
    0,    0,    0,    0,  -57,  -50,    0,  -35,    0,    0,
    0,  108, -262,    0,  -80, -261, -259,  -57,    0,    0,
  -39,  164,  -31,  -23,    0,  -46, -238,    0, -233,   12,
    0,   30,   42, -218,  -30,  -38,   -4,    0,  -61,   31,
    0,    0,    0,    0,    0,    0,    0,  -39, -172,    0,
    0,   47, -168,   65,    0,  -30,  -30,    0,  -33,  -30,
  -30,  -30,    0,  150,    0,  150,    0,   68,  -30,  -30,
    0,    0,  164,    0,  -39, -259,    0, -158,  -57,    0,
   24,   33,  -30, -244,    0,    0,   55,    0,  -30,  -30,
  -30,  -30,  -30,  -30,  -30,  -30,  -30,  -30,  -30,  -30,
  -38,    0,  122,  150,    0,    0, -259,    0,    0, -152,
 -137,  164,  144,   36,    0,   85,   89,    0,   71,   71,
   71,   71,  363,  363,   71,   71,   26,   26,    0,    0,
    0,   72,    0,   65,  164,    0,    0,  -30, -244,    0,
    0,  -30,    0, -130,  171,   85,  150,  164,    0,    0,
    0,
};
static const short yyrindex[] = {                       135,
    0,    0,    0,    0,  135,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,   95,    0,    0,
    0,   21,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,   81,    0,  102,    0,    0,    0,    0,  -21,    0,
    0,    0,    0,  -53,    0,  -41,    0,  -45,    0,    0,
    0,    0,   21,    0,    0,   92,    0,    0,    0,    0,
    0,    0,    0,  112,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  -43,    0,    0,   92,    0,    0,    0,
    0,    0,    0,    7,    0,  115,    0,    0,   44,   66,
   79,   90,   18,  103,  101,  114,  -10,    1,    0,    0,
    0,    0,    0,  102,    0,    0,    0,    0,    0,    0,
    0,    0,    0,   98,    0,  115,  -42,    0,    0,    0,
    0,
};
static const short yygindex[] = {                       163,
    0,    0,    0,   10,    0,    0,    6,    0,   15,   63,
    0,    0,    0,    0,  156,    0,   41,  391,   51,    0,
   29,  117,  -56,    0,    0,    0,    0,    0,    0,    0,
    0,   80,    0,    0,    0,
};
#define YYTABLESIZE 633
static const short yytable[] = {                         62,
   13,   61,   57,   60,   49,   61,   84,   62,   11,   61,
   21,   60,   26,   60,   27,   47,   48,   57,   17,   81,
   81,   81,   81,   81,   23,   81,   31,   29,  114,   27,
   66,   28,   66,   66,   66,   51,   53,   81,   81,   54,
   81,   67,   22,   67,   67,   67,   52,   26,   66,   66,
   26,   66,   55,   74,   58,  136,   70,   83,   76,   67,
   67,   76,   67,   72,  111,   99,   97,   99,   98,   56,
  100,   81,  100,  112,   99,   97,   76,   98,  144,  100,
  106,   57,   66,   95,   72,   96,   69,   72,  110,   73,
  107,  151,   95,   67,   96,  118,   99,   97,  115,   98,
   75,  100,   72,   72,   76,   72,   73,   78,   79,   73,
   76,  101,   99,   97,   95,   98,   96,  100,  109,   74,
  134,  107,   74,  135,   73,   73,  138,   73,  139,  141,
   75,  148,  142,   75,    2,   30,   72,   74,   74,   12,
   74,   70,   32,   77,   70,   39,   77,   18,   75,   75,
   21,   75,   34,  115,   71,   36,   52,   71,   73,   70,
   70,   77,   70,   99,   97,   17,   98,   10,  100,  133,
   25,   74,   71,   71,  150,   71,    1,    2,    3,  146,
  131,   95,   75,   96,  143,   99,   97,    0,   98,  105,
  100,   99,   97,   70,   98,   77,  100,    0,   16,    1,
    2,    3,    0,   95,    0,   96,   71,    0,   61,   95,
    0,   96,   99,   97,  132,   98,   60,  100,   47,   48,
   57,    0,    0,    0,    0,    0,    0,    0,    0,    0,
   95,    0,   96,    0,   59,   27,  137,   12,    0,   65,
   81,   48,   59,   27,    0,   81,   81,   81,   81,   81,
   81,   66,    0,    0,    0,    0,   66,   66,   66,   66,
   66,   66,   67,  149,    0,    0,    0,   67,   67,   67,
   67,   67,   67,    0,    0,    0,    0,    0,    0,   76,
    0,    0,    0,    0,    0,    0,   22,    0,   76,   76,
   89,   90,   91,   92,   93,   94,    0,    0,    0,   89,
   90,   91,   92,   93,   94,   72,    0,    0,    0,    0,
   72,   72,   72,   72,   72,   72,    0,    0,    0,    0,
    0,   89,   90,   91,   92,   93,   94,   73,    0,    0,
    0,    0,   73,   73,   73,   73,   73,   73,    0,    0,
   74,    0,    0,    0,    0,   74,   74,   74,   74,   74,
   74,   75,    0,    0,    0,    0,   75,   75,   75,   75,
   75,   75,   70,    0,   77,    0,    0,   70,   70,   70,
   70,   70,   70,   77,   77,   71,    0,    0,    0,    0,
   71,   71,   71,   71,   71,   71,    0,    0,   89,   90,
   91,   92,   93,   94,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,   99,   97,    0,   98,    0,  100,
   89,   90,   91,   92,   93,   94,   89,   90,   91,   92,
   93,   94,   95,   32,   96,   64,   33,   34,   35,   36,
    0,    0,    0,    0,    0,    0,   37,   89,   90,   91,
   92,   93,   94,    0,    0,    0,   81,   82,    0,    0,
   86,   87,   88,    0,    0,    0,    0,    0,    0,  103,
  104,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  113,    0,    0,    0,    0,    0,  119,
  120,  121,  122,  123,  124,  125,  126,  127,  128,  129,
  130,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,  145,    0,
    0,    0,  147,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,   89,
   90,   91,   92,
};
static const short yycheck[] = {                         38,
   36,   40,   44,   42,   36,   59,   40,   38,   59,   40,
  273,   42,  274,   59,  274,   59,   59,   59,   58,   41,
   42,   43,   44,   45,   15,   47,   21,   18,  273,  274,
   41,   17,   43,   44,   45,   59,  275,   59,   60,  273,
   62,   41,  123,   43,   44,   45,   93,   41,   59,   60,
   44,   62,   41,   48,  273,  112,   61,   91,   41,   59,
   60,   44,   62,  125,   41,   42,   43,   42,   45,   40,
   47,   93,   47,   41,   42,   43,   59,   45,  135,   47,
   75,   40,   93,   60,   41,   62,   91,   44,   79,   59,
   76,  148,   60,   93,   62,   41,   42,   43,   84,   45,
  273,   47,   59,   60,   58,   62,   41,  276,   44,   44,
   93,   44,   42,   43,   60,   45,   62,   47,  277,   41,
  273,  107,   44,  261,   59,   60,   91,   62,   44,   41,
   41,  262,   61,   44,    0,   41,   93,   59,   60,   59,
   62,   41,   41,   41,   44,  125,   44,   40,   59,   60,
   59,   62,   41,  139,   41,   41,   59,   44,   93,   59,
   60,   59,   62,   42,   43,   58,   45,    5,   47,  107,
   15,   93,   59,   60,  146,   62,  257,  258,  259,  139,
  101,   60,   93,   62,  134,   42,   43,   -1,   45,   73,
   47,   42,   43,   93,   45,   93,   47,   -1,   91,  257,
  258,  259,   -1,   60,   -1,   62,   93,   -1,  262,   60,
   -1,   62,   42,   43,   93,   45,  262,   47,  262,  262,
  262,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   60,   -1,   62,   -1,  273,  274,   93,  273,   -1,  278,
  262,  273,  273,  274,   -1,  267,  268,  269,  270,  271,
  272,  262,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,  262,   93,   -1,   -1,   -1,  267,  268,  269,
  270,  271,  272,   -1,   -1,   -1,   -1,   -1,   -1,  262,
   -1,   -1,   -1,   -1,   -1,   -1,  123,   -1,  271,  272,
  267,  268,  269,  270,  271,  272,   -1,   -1,   -1,  267,
  268,  269,  270,  271,  272,  262,   -1,   -1,   -1,   -1,
  267,  268,  269,  270,  271,  272,   -1,   -1,   -1,   -1,
   -1,  267,  268,  269,  270,  271,  272,  262,   -1,   -1,
   -1,   -1,  267,  268,  269,  270,  271,  272,   -1,   -1,
  262,   -1,   -1,   -1,   -1,  267,  268,  269,  270,  271,
  272,  262,   -1,   -1,   -1,   -1,  267,  268,  269,  270,
  271,  272,  262,   -1,  262,   -1,   -1,  267,  268,  269,
  270,  271,  272,  271,  272,  262,   -1,   -1,   -1,   -1,
  267,  268,  269,  270,  271,  272,   -1,   -1,  267,  268,
  269,  270,  271,  272,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   42,   43,   -1,   45,   -1,   47,
  267,  268,  269,  270,  271,  272,  267,  268,  269,  270,
  271,  272,   60,  260,   62,   35,  263,  264,  265,  266,
   -1,   -1,   -1,   -1,   -1,   -1,  273,  267,  268,  269,
  270,  271,  272,   -1,   -1,   -1,   56,   57,   -1,   -1,
   60,   61,   62,   -1,   -1,   -1,   -1,   -1,   -1,   69,
   70,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   83,   -1,   -1,   -1,   -1,   -1,   89,
   90,   91,   92,   93,   94,   95,   96,   97,   98,   99,
  100,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  138,   -1,
   -1,   -1,  142,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,  267,
  268,  269,  270,
};
#define YYFINAL 4
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
"$accept : program",
"program : item program",
"program :",
"item : global_type_dec ';'",
"item : fun_def",
"global_type_dec : type global_dec",
"global_dec : TK_IDENTIFIER value_init",
"global_dec : '$' TK_IDENTIFIER scalar_init",
"value_init : scalar_init",
"value_init : '[' LIT_INTEGER ']' array_init",
"scalar_init : ':' literal",
"array_init : ':' literal_list",
"array_init :",
"local_type_dec : type local_dec",
"local_dec : TK_IDENTIFIER scalar_init",
"local_dec : '$' TK_IDENTIFIER scalar_init",
"type : KW_WORD",
"type : KW_BOOL",
"type : KW_BYTE",
"literal : LIT_INTEGER LIT_FALSE LIT_TRUE LIT_CHAR",
"literal_list : literal literal_list",
"literal_list :",
"fun_def : header local_type_decs block",
"local_type_decs : local_type_decs local_type_dec ';'",
"local_type_decs :",
"header : type TK_IDENTIFIER '(' type_parameter_list ')'",
"parameter : TK_IDENTIFIER",
"parameter : TK_IDENTIFIER '[' expr ']'",
"parameter : literal",
"type_parameter_list : type TK_IDENTIFIER type_parameter_list_tail",
"type_parameter_list :",
"type_parameter_list_tail : ',' type TK_IDENTIFIER type_parameter_list_tail",
"type_parameter_list_tail :",
"parameter_list : parameter parameter_list_tail",
"parameter_list :",
"parameter_list_tail : ',' parameter parameter_list_tail",
"parameter_list_tail :",
"block : '{' command_list '}'",
"command_list : command ';' command_list",
"command_list :",
"command : atr",
"command : flow_control",
"command : input",
"command : output",
"command : return",
"command : block",
"atr : TK_IDENTIFIER ass",
"ass : '=' expr",
"ass : '[' expr ']' '=' expr",
"flow_control : if_then",
"flow_control : if_then_else",
"flow_control : KW_LOOP '(' expr ')' command",
"if_then : KW_IF '(' expr ')' KW_THEN command",
"if_then_else : KW_IF '(' expr ')' KW_THEN command KW_ELSE command",
"input : KW_INPUT TK_IDENTIFIER",
"output : KW_OUTPUT element_list",
"element : LIT_STRING",
"element : expr",
"element_list : element element_list_tail",
"element_list_tail : ',' element_list",
"element_list_tail :",
"return : KW_RETURN expr",
"expr : TK_IDENTIFIER access",
"expr : TK_IDENTIFIER '(' parameter_list ')'",
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
"access : '[' expr ']'",
"access :",

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
#line 238 "parser.y"

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}
#line 464 "y.tab.c"

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
