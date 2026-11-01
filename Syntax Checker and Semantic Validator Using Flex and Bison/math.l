%{
#include "math.tab.h"
#include <cstdlib>
%}

%%
[0-9]+       { yylval.num = atoi(yytext); return NUMBER; }
"+"          { return '+'; }
"-"          { return '-'; }
"*"          { return '*'; }
"/"          { return '/'; }
"("          { return '('; }
")"          { return ')'; }
[ \t\n]+     ;
.            { return INVALID; }
%%

int yywrap() {
    return 1;
}
