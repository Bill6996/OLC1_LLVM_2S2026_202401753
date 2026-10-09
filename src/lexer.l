%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"

int errores_lexicos = 0;
static int col = 1;

#define YY_USER_ACTION \
    yylloc.first_line = yylineno; yylloc.first_column = col; \
    yylloc.last_line  = yylineno; yylloc.last_column  = col + yyleng - 1; \
    col += yyleng;
%}

%option noyywrap nounput noinput yylineno nodefault

DIGITO   [0-9]
LETRA    [a-zA-Z_]

%%
"let"                       { return LET; }
"print"                     { return PRINT; }
{DIGITO}+"."{DIGITO}+       { yylval.dval = atof(yytext); return DECIMAL; }
{DIGITO}+                   { yylval.ival = atol(yytext); return ENTERO; }
{LETRA}({LETRA}|{DIGITO})*  { yylval.str = strdup(yytext); return ID; }
"+"|"-"|"*"|"/"|"="|";"|"("|")"  { return yytext[0]; }
[ \t\r]+                    { /* ignorar */ }
\n                          { col = 1; }
.                           { fprintf(stderr, "ERROR LEXICO (linea %d, columna %d): "
                                      "caracter no reconocido '%s'\n",
                                      yylineno, yylloc.first_column, yytext);
                              errores_lexicos++; }
%%
