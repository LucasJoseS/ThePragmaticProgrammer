%{
  #include <stdio.h>
  #include <ctype.h>
  #include <stdlib.h>

  int yylex(void);
  void yyerror(char const*);
%}

%token NUM
%token AMPM

%%
time:
 time '\n'                { printf("VALID FORMAT. Total minutes  %d\n", $1); exit(0);}
 ;

time:
 hour AMPM               { if($1 >= 12) yyerror("time exceed the limits"); $$ = $1 + $2; }
 | hour ':' minutes      { if($1 >= 24*60 || $3 >= 60) yyerror("time exceed the limits");  $$ = $1 + $3; }
 | hour ':' minutes AMPM { if($1 >= 12*60 || $3 >= 60) yyerror("time exceed the limits");  $$ = $1 + $3 + $4; }
 ;

hour:
 NUM                     { $$ = $1 * 60; }
 | NUM NUM               { $$ = ($1 * 10 + $2) * 60; }
 ;

minutes:
 NUM NUM                 { $$ = $1 * 10 + $2; } 
 ;
%%

int yylex() {
  int c = getchar();

  while(c == ' ') {
    c = getchar();
  }

  if(isdigit(c)) {
    yylval = c - '0';
    return NUM;
  }

  if(c == 'a' || c == 'p') {
    if(c == 'a')
      yylval = 0;
    else
      yylval = 12 * 60;

    getchar();
    
    return AMPM;
  }

  return c;
}

void yyerror(char const *s) {
  printf("INVALID FORMAT, %s\n", s);
  exit(1);
}

int main() {
  return yyparse();
}
