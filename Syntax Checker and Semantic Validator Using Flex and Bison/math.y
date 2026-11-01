%{
#include <stdio.h>
#include <stdlib.h>

int yylex();
void yyerror(const char *s);
%}

%union {
    int num;
}

%token <num> NUMBER
%token INVALID

%type <num> expr

%left '+' '-'
%left '*' '/'
%right UMINUS

%%

input:
    expr
    {
        printf("Result = %d\n", $1);
        printf("Expression is Valid\n");
    }
    ;

expr:
    NUMBER
    {
        $$ = $1;
    }
    |
    expr '+' expr
    {
        $$ = $1 + $3;
    }
    |
    expr '-' expr
    {
        $$ = $1 - $3;
    }
    |
    expr '*' expr
    {
        $$ = $1 * $3;
    }
    |
    expr '/' expr
    {
        if ($3 == 0) {
            yyerror("Division by zero");
            YYABORT;
        }
        $$ = $1 / $3;
    }
    |
    '-' expr %prec UMINUS
    {
        $$ = -$2;
    }
    |
    '(' expr ')'
    {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s) {
    printf("Invalid Expression: %s\n", s);
}

int main() {
    printf("Enter arithmetic expression:\n");
    yyparse();
    return 0;
}
