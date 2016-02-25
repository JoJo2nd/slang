%{
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "getopt.h"

// stuff from flex that bison needs to know about:
extern int yylex();
extern int yyparse();
extern void yyerror(char const *);
extern FILE *yyin;

struct slang_node* g_slang_root;

%}

%type <struct slang_node *> root


%token TRANSLATION_UNIT

%%


root        : { g_slang_root = new_slang_node(TRANSLATION_UNIT, NULL); };

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
    static const char argopts[] = "v";
    struct option long_options[] = {
        { "verbose", no_argument, NULL, (int)'v' },
        { NULL, 0, NULL, 0 }
    };
    int verbose = 0;
    int option_index = 0;
    int c;
    while ((c = gop_getopt_long(argc, argv, argopts, long_options, &option_index)) != -1) {
        switch(c) {
        case 'v': verbose = 1; break;
        case '?':
            if (strchr(argopts, optopt))
                fprintf (stderr, "Option -%c requires an argument.\n", optopt);
            else if (isalpha(optopt))
                fprintf (stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf (stderr, "Unknown option character `\\x%x'.\n", optopt);
            exit(-1);
        }
    }

    /* For any remaining command line arguments (not options). */
    while (optind < argc) {
        yyin = fopen(argv[optind], "rb");
        break;
        //out_opts->inputFiles_.push_back(argv[optind++]);
    }

    if (!yyin) {
        fprintf(stderr, "Cannot open input file %s", argv[optind]);
        exit(-2);
    }

    // parse through the input until there is no more:
    do {
        yyparse();
    } while (!feof(yyin));

    fclose(yyin);
}