%{
#include <stdio.h>
#include <stdlib.h>
#include <map>
#include <string>
using namespace std;

map<string,double> variables;

int yylex();
void yyerror(const char *s);
%}

%union {
    double num;
    char *str;
}

%token <num> NUMBER
%token <str> ID
%token PRINT INVALID

%type <num> expr

%left '+' '-'
%left '*' '/'

%%

program:
    statements
    ;

statements:
    statements statement
    |
    ;

statement:
    ID '=' expr ';'
    {
        variables[$1] = $3;
        printf("%s = %g\n", $1, $3);
        free($1);
    }
    |
    PRINT ID ';'
    {
        if (variables.count($2))
            printf("%s = %g\n", $2, variables[$2]);
        else
            printf("Undefined variable: %s\n", $2);
        free($2);
    }
    ;

expr:
    NUMBER
    {
        $$ = $1;
    }
    |
    ID
    {
        if (variables.count($1))
            $$ = variables[$1];
        else {
            printf("Undefined variable: %s\n", $1);
            $$ = 0;
        }
        free($1);
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
            $$ = 0;
        }
        else
            $$ = $1 / $3;
    }
    |
    '(' expr ')'
    {
        $$ = $2;
    }
    ;

%%

void yyerror(const char *s) {
    printf("Syntax/Error: %s\n", s);
}

int main() {
    printf("Enter configuration statements:\n");
    yyparse();
    printf("Evaluation completed.\n");
    return 0;
}
