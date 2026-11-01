%{
#include <stdio.h>
%}

%%
"int"|"float"|"char"|"if"|"else"|"while"|"return"  { printf("%-15s Keyword\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]*                             { printf("%-15s Identifier\n", yytext); }
[0-9]+                                             { printf("%-15s Number\n", yytext); }
[0-9]+"."[0-9]+                                    { printf("%-15s Float\n", yytext); }
[+\-*/=<>]                                         { printf("%-15s Operator\n", yytext); }
[;(),{}]                                           { printf("%-15s Special Symbol\n", yytext); }
[ \t\n]+                                           ;
.                                                  { printf("%-15s Invalid\n", yytext); }
%%

int main() {
    printf("Enter source code (Ctrl+D to finish):\n");
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
compile:
flex lexer.l 
gcc lex.yy.c -o lexer -lfl 
./lexer
