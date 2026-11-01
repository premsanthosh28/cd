%{
#include <stdio.h>
%}

%%
"=="|"!="|"<="|">="|"++"|"--"|"&&"|"||" {
    printf("%-15s Operator\n", yytext);
}

"="|"+"|"-"|"*"|"/"|"%"|"<"|">" {
    printf("%-15s Operator\n", yytext);
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("%-15s Identifier\n", yytext);
}

[0-9]+(\.[0-9]+)? {
    printf("%-15s Number\n", yytext);
}

[;,(){}] {
    printf("%-15s Special Symbol\n", yytext);
}

[ \t\n]+ ;

. {
    printf("%-15s Invalid Token\n", yytext);
}
%%

int main() {
    printf("Enter the expression:\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}

compile:flex maximal.l
gcc lex.yy.c -o maximal -lfl
./maximal
