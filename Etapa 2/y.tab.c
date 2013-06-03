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
#define YYERRCODE 256
static const short yylhs[] = {                           -1,
    0,    0,    1,    1,    2,    5,    5,    6,    6,    7,
    8,    8,   11,   12,   12,    4,    4,    4,    9,   10,
   10,    3,   14,   14,   13,   17,   17,   17,   16,   16,
   19,   19,   20,   20,   21,   21,   15,   22,   22,   23,
   23,   23,   23,   23,   23,   24,   29,   29,   25,   25,
   25,   30,   31,   26,   27,   33,   33,   32,   34,   34,
   28,   18,   18,   18,   18,   18,   18,   18,   35,   35,
   36,   36,   36,   36,   36,   36,   36,   36,   36,   36,
   36,   36,
};
static const short yylen[] = {                            2,
    2,    0,    2,    1,    2,    2,    3,    1,    4,    2,
    2,    0,    2,    2,    3,    1,    1,    1,    4,    2,
    0,    3,    3,    0,    5,    1,    4,    1,    3,    0,
    4,    0,    2,    0,    3,    0,    3,    3,    0,    1,
    1,    1,    1,    1,    1,    2,    2,    5,    1,    1,
    5,    6,    8,    2,    2,    1,    1,    2,    2,    0,
    2,    2,    4,    1,    3,    3,    2,    2,    3,    0,
    1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
    1,    1,
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
    0,    0,    0,    0,   62,    0,    0,    0,   77,   78,
   79,   80,   81,   82,   75,   76,   71,   72,   73,   74,
    0,    0,   58,    0,    0,   38,   15,    0,   11,   19,
    0,    0,    0,    0,    0,   28,    0,    0,   65,    0,
   59,    0,   20,    0,    0,   51,   69,    0,    0,   33,
   63,    0,   31,    0,    0,    0,    0,    0,   27,   35,
   53,
};
static const short yydgoto[] = {                          4,
    5,    6,    7,    8,   14,   19,   20,   77,   63,  109,
   24,   50,    9,   15,   38,   30,  117,   66,   80,  118,
  130,   39,   40,   41,   42,   43,   44,   45,   71,   46,
   47,   67,   68,  103,   85,  101,
};
static const short yysindex[] = {                      -131,
    0,    0,    0,    0, -131,  -42,    0,  -35,    0,    0,
    0,   33, -248,    0, -109, -244, -240, -131,    0,    0,
  -16, -108,  -31,  -22,    0,  -40, -218,    0, -176,   59,
    0,   70,   72, -158,  -30,  -38,   -1,    0,    4,   71,
    0,    0,    0,    0,    0,    0,    0,  -16, -142,    0,
    0,   75, -141,   90,    0,  -30,  -30,    0,   -4,  -30,
  -30,  -30,    0,   39,    0,   39,    0,   92,  -30,  -30,
    0,    0, -108,    0,  -16, -240,    0, -140, -131,    0,
  -14,    2,  -30, -185,    0, -154,    9,   39,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
  -30,  -38,    0,   16,   39,    0,    0, -240,    0,    0,
 -135, -122, -108,   23,   49,    0,   97,  101,    0,   39,
    0,   82,    0,   90, -108,    0,    0,  -30, -185,    0,
    0,  -30,    0, -118,   32,   97,   39, -108,    0,    0,
    0,
};
static const short yyrindex[] = {                       151,
    0,    0,    0,    0,  151,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,  112,    0,    0,
    0,   34,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,  102,    0,  119,    0,    0,    0,    0,  -21,    0,
    0,    0,    0,  -53,    0,  -41,    0,  -52,    0,    0,
    0,    0,   34,    0,    0,  103,    0,    0,    0,    0,
    0,    0,    0,  122,    0,   61,    0,   52,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,    0,  -50,    0,    0,  103,    0,    0,
    0,    0,    0,    0,   -9,    0,  123,    0,    0,   54,
    0,    0,    0,  119,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  107,    0,  123,  -48,    0,    0,    0,
    0,
};
static const short yygindex[] = {                       164,
    0,    0,    0,    1,    0,    0,   -8,    0,   38,   62,
    0,    0,    0,    0,  156,    0,   43,  133,   50,    0,
   37,  104,   -6,    0,    0,    0,    0,    0,    0,    0,
    0,   73,    0,    0,    0,    0,
};
#define YYTABLESIZE 331
static const short yytable[] = {                         62,
   13,   61,   57,   60,   49,   61,   60,   62,   47,   61,
   48,   60,   31,   22,   22,   23,   11,   57,   29,   70,
   70,   70,   70,   70,   21,   70,  112,   99,   97,   26,
   98,   26,  100,   27,   26,   84,   51,   70,   70,   74,
   70,   17,  113,   99,   97,   95,   98,   96,  100,  119,
   99,   97,   52,   98,   28,  100,   53,   99,   97,   70,
   98,   95,  100,   96,   99,   97,  107,   98,   95,  100,
   96,   70,   18,   99,   97,   95,   98,   96,  100,  111,
   99,   97,   95,   98,   96,  100,   83,  115,   27,   69,
   17,   95,   67,   96,   66,   67,   54,   66,   95,   55,
   96,   68,   68,   68,   68,   68,  126,   68,  122,   56,
   67,   57,   66,  108,   58,  127,   93,   94,  134,   68,
   68,  116,   68,   16,  139,    1,    2,    3,   72,   73,
   75,  141,   76,   79,   78,  102,  110,  124,  125,  128,
  129,  131,  132,  138,   67,  108,   66,    1,    2,    3,
    2,   32,   30,   68,   33,   34,   35,   36,   39,   32,
   12,   21,   34,   36,   37,   52,  116,   64,   10,  123,
   25,  136,  140,  133,  121,    0,  106,    0,    0,    0,
    0,    0,    0,    0,    0,    0,    0,    0,   81,   82,
    0,    0,   86,   87,   88,    0,    0,    0,    0,    0,
    0,  104,  105,    0,    0,    0,    0,    0,   61,   60,
    0,   47,    0,   48,    0,  114,    0,    0,    0,    0,
   57,    0,    0,    0,    0,    0,    0,    0,    0,    0,
    0,    0,    0,  120,   59,   27,    0,   12,    0,   65,
   70,   48,   59,   27,    0,   70,   70,   70,   70,   70,
   70,    0,   89,   90,   91,   92,   93,   94,    0,    0,
  135,    0,    0,    0,  137,    0,    0,    0,   89,   90,
   91,   92,   93,   94,    0,   89,   90,   91,   92,   93,
   94,    0,   89,   90,   91,   92,   93,   94,    0,   89,
   90,   91,   92,   93,   94,    0,    0,    0,   89,   90,
   91,   92,   93,   94,    0,   89,   90,   91,   92,   93,
   94,    0,    0,   67,    0,   66,    0,    0,    0,    0,
    0,    0,   68,    0,    0,    0,    0,   68,   68,   68,
   68,
};
static const short yycheck[] = {                         38,
   36,   40,   44,   42,   36,   59,   59,   38,   59,   40,
   59,   42,   21,  123,  123,   15,   59,   59,   18,   41,
   42,   43,   44,   45,  273,   47,   41,   42,   43,  274,
   45,   41,   47,  274,   44,   40,   59,   59,   60,   48,
   62,   58,   41,   42,   43,   60,   45,   62,   47,   41,
   42,   43,   93,   45,   17,   47,  275,   42,   43,   61,
   45,   60,   47,   62,   42,   43,   75,   45,   60,   47,
   62,   93,   40,   42,   43,   60,   45,   62,   47,   79,
   42,   43,   60,   45,   62,   47,   91,  273,  274,   91,
   58,   60,   41,   62,   41,   44,  273,   44,   60,   41,
   62,   41,   42,   43,   44,   45,  113,   47,   93,   40,
   59,   40,   59,   76,  273,   93,  271,  272,  125,   59,
   60,   84,   62,   91,   93,  257,  258,  259,  125,   59,
  273,  138,   58,   44,  276,   44,  277,  273,  261,   91,
   44,   41,   61,  262,   93,  108,   93,  257,  258,  259,
    0,  260,   41,   93,  263,  264,  265,  266,  125,   41,
   59,   59,   41,   41,  273,   59,  129,   35,    5,  108,
   15,  129,  136,  124,  102,   -1,   73,   -1,   -1,   -1,
   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   56,   57,
   -1,   -1,   60,   61,   62,   -1,   -1,   -1,   -1,   -1,
   -1,   69,   70,   -1,   -1,   -1,   -1,   -1,  262,  262,
   -1,  262,   -1,  262,   -1,   83,   -1,   -1,   -1,   -1,
  262,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,
   -1,   -1,   -1,  101,  273,  274,   -1,  273,   -1,  278,
  262,  273,  273,  274,   -1,  267,  268,  269,  270,  271,
  272,   -1,  267,  268,  269,  270,  271,  272,   -1,   -1,
  128,   -1,   -1,   -1,  132,   -1,   -1,   -1,  267,  268,
  269,  270,  271,  272,   -1,  267,  268,  269,  270,  271,
  272,   -1,  267,  268,  269,  270,  271,  272,   -1,  267,
  268,  269,  270,  271,  272,   -1,   -1,   -1,  267,  268,
  269,  270,  271,  272,   -1,  267,  268,  269,  270,  271,
  272,   -1,   -1,  262,   -1,  262,   -1,   -1,   -1,   -1,
   -1,   -1,  262,   -1,   -1,   -1,   -1,  267,  268,  269,
  270,
};
#define YYFINAL 4
#ifndef YYDEBUG
#define YYDEBUG 0
#endif
#define YYMAXTOKEN 279
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
"TOKEN_ERROR",
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
"expr : expr op expr",
"expr : '&' expr",
"expr : '*' expr",
"access : '[' expr ']'",
"access :",
"op : '+'",
"op : '-'",
"op : '*'",
"op : '/'",
"op : '<'",
"op : '>'",
"op : OPERATOR_LE",
"op : OPERATOR_GE",
"op : OPERATOR_EQ",
"op : OPERATOR_NE",
"op : OPERATOR_AND",
"op : OPERATOR_OR",

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
#line 239 "parser.y"

yyerror(s)
char *s;
{
  fprintf(stderr, "%s in line %d\n",s,getLineNumber());

  exit(3);
}
#line 401 "y.tab.c"

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
