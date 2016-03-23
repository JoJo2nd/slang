#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "getopt.h"
#include "slang.h"
#include "slang.tab.h"

#define YYSTYPE SLANG_STYPE
#define YYLTYPE SLANG_LTYPE

#include "slang.yy.h"

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
        switch (c) {
        case 'v': verbose = 1; break;
        case '?':
            if (strchr(argopts, optopt))
                fprintf(stderr, "Option -%c requires an argument.\n", optopt);
            else if (isalpha(optopt))
                fprintf(stderr, "Unknown option `-%c'.\n", optopt);
            else
                fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
            exit(-1);
        }
    }

    slang_parse_context_t context = {0};

    slang_lex_init(&context.scanner);
    // For any remaining command line arguments (not options). 
    while (optind < argc) {
        context.fin = fopen(argv[optind], "rb");
        break;
    }

    if (!context.fin) {
        fprintf(stderr, "Cannot open input file %s", argv[optind]);
        exit(-2);
    }

    slang_set_in(context.fin, context.scanner);

    // parse through the input until there is no more:
    do {
        slang_parse(&context);
    } while (!feof(context.fin));

    fclose(context.fin);

    if (context.root) {
        slang_node_t* fake_root = new_slang_node(TRANSLATION_UNIT);
        slang_node_attach_child(fake_root, context.root);
        FILE* f_out = fopen("out.a", "wb");
        if (f_out) {
            print_slang_AST(fake_root, f_out);
            fclose(f_out);
        }
    }
}