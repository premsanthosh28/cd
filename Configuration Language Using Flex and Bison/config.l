%{
#include "config.tab.h"
#include <cstdlib>
%}

%%
[0-9]+(\.[0-9]+)?    { yylval.num = atof(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { return ID; }
"print"               { return PRINT; }
"="                   { return '='; }
"+"                   { return '+'; }
"-"                   { return '-'; }
"*"                   { return '*'; }
"/"                   { return '/'; }
"("                   { return '('; }
")"                   { return ')'; }
";"                   { return ';'; }
[ \t\n]+              ;
.                     { return INVALID; }
%%

int yywrap() {
    return 1;
}
