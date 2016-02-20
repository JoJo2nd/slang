%{
#include <stdlib.h>
//#define YY_DECL extern "C" int yylex()
%}
%%
[ \t\n]         ;
[0-9]+\.[0-9]+  { printf("Found a floating-point number: %s\n", yytext); }
[0-9]+          { printf("Found an integer: %s\n", yytext); }
[a-zA-Z0-9]+    { printf("Found a string: %s\n", yytext); }
%%
void yyerror (char const *s) {
  fprintf (stderr, "%s\n", s);
}
int yywrap() {
   // open next reference or source file and start scanning
   //if((yyin = compiler->getNextFile()) != NULL) {
   //   line = 0; // reset line counter for next source file
   //   return 0;
   //}
   return 1;
}

int main(int argc, char** argv) {
	// lex through the input:
	yylex();
}