/*
 * Copyright 2016 James Moran. All rights reserved.
 * License: https://github.com/JoJo2nd/slang/blob/master/LICENSE
 */
#include "os_calls.h"
#include "getopt.h"
#include "sym_table.h"
#include "slang.h"
#include "slang.tab.h"

#define YYSTYPE SLANG_STYPE
#define YYLTYPE SLANG_LTYPE

#include "slang.yy.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

typedef struct MemBuffer {
    size_t reserve, len;
    uint8_t* ptr;
} mem_buffer_t;

void mem_buffer_init(mem_buffer_t* buf, void* init_data, size_t init_data_size,  size_t initial_reserve) {
    buf->reserve = init_data_size > initial_reserve ? init_data_size : initial_reserve;
    buf->len = init_data ? init_data_size : 0;
    buf->ptr = initial_reserve > 0 ? malloc(buf->reserve) : NULL;
    if (init_data)
        memcpy(buf->ptr, init_data, buf->len);
}

void mem_buffer_destroy(mem_buffer_t* buf) {
    free(buf->ptr);
    mem_buffer_init(buf, NULL, 0, 0);
}

void mem_buffer_append(mem_buffer_t* buf, const void* data, size_t len) {
    if (buf->len + len > buf->reserve) {
        if (buf->reserve == 0) 
            buf->reserve = 1024;
        else
            buf->reserve = (buf->reserve) + buf->reserve/2;
        buf->ptr = realloc(buf->ptr, buf->reserve);
    }
    memcpy(buf->ptr+buf->len, data, len);
    buf->len += len;
}

void mem_buffer_append_str(mem_buffer_t* buf, const char* str) {
    mem_buffer_append(buf, str, strlen(str));
}

int main(int argc, char** argv) {

    static const char argopts[] = "vpPI:D:";
    struct option long_options[] = {
        { "verbose", no_argument, NULL, (int)'v' },
        { NULL, 0, NULL, 0 }
    };
    int verbose = 0;
    int preprocess = 0;
    int leavepreprocess = 0;
    int option_index = 0;
    int c;
    mem_buffer_t mcpp_cmdline;

    mem_buffer_init(&mcpp_cmdline, "mcpp", 4, 2048);

    while ((c = gop_getopt_long(argc, argv, argopts, long_options, &option_index)) != -1) {
        switch (c) {
        case 'v': verbose = 1; break;
        case 'P': preprocess = 1; break;
        case 'p': leavepreprocess = 1; break;
		case 'I': {// Include for mcpp
            int arg_has_whitespace = 0;
            int arg_has_escape = 0;
            size_t len = strlen(optarg);
            for (size_t i=0; i<len && arg_has_escape == 0 && arg_has_whitespace == 0; ++i) {
                if (isspace(optarg[i])) {
                    arg_has_whitespace = 1;
                }
                if (optarg[i] == '"') {
                    arg_has_escape = 1;
                }
            }
            mem_buffer_append_str(&mcpp_cmdline, " -I ");
            if (arg_has_whitespace) {
                mem_buffer_append_str(&mcpp_cmdline, "\"");
            }
            for (size_t i = 0; i<len; ++i) {
                if (optarg[i] == '"')
                    mem_buffer_append_str(&mcpp_cmdline, "\\");
                mem_buffer_append(&mcpp_cmdline, &optarg[i], 1);
            }
            //mem_buffer_append_str(&include_dirs, optarg);
            if (arg_has_whitespace)
                mem_buffer_append_str(&mcpp_cmdline, "\"");
        } break;
		case 'D': {// Define for mcpp
            int arg_has_whitespace = 0;
            int arg_has_escape = 0;
            size_t len = strlen(optarg);
            for (size_t i = 0; i < len && arg_has_escape == 0 && arg_has_whitespace == 0; ++i) {
                if (isspace(optarg[i])) {
                    arg_has_whitespace = 1;
                }
                if (optarg[i] == '"') {
                    arg_has_escape = 1;
                }
            }
            mem_buffer_append_str(&mcpp_cmdline, " -D ");
            if (arg_has_whitespace) {
                mem_buffer_append_str(&mcpp_cmdline, "\"");
            }
            for (size_t i = 0; i < len; ++i) {
                if (optarg[i] == '"')
                    mem_buffer_append_str(&mcpp_cmdline, "\\");
                mem_buffer_append(&mcpp_cmdline, &optarg[i], 1);
            }
            //mem_buffer_append_str(&include_dirs, optarg);
            if (arg_has_whitespace)
                mem_buffer_append_str(&mcpp_cmdline, "\"");
        } break;
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

    slang_init_sym_table();

    slang_parse_context_t context = {0};

    slang_lex_init_extra(&context, &context.scanner);

    if (verbose == 1) {
        slang_set_debug(1, context.scanner);
    }

	if (optind >= argc)
		return -1;


	const char* input_file = argv[optind];

    context.current_file = strdup(input_file);

    char* preprocessed_file = malloc(strlen(input_file)+16);
    strcpy(preprocessed_file, input_file);
    strcat(preprocessed_file, ".pp");

	// run mcpp on input, passing defines and includes
    mem_buffer_append_str(&mcpp_cmdline, " \"");
    mem_buffer_append_str(&mcpp_cmdline, input_file);
    mem_buffer_append_str(&mcpp_cmdline, "\" \"");
    mem_buffer_append_str(&mcpp_cmdline, preprocessed_file);
    mem_buffer_append_str(&mcpp_cmdline, "\"");
    char null_term = 0;
    mem_buffer_append(&mcpp_cmdline, &null_term, sizeof(null_term));

    char* mcpp_stdout = NULL;
    size_t mcpp_stdout_size = 0;
    char* mcpp_stderr = NULL;
    size_t mcpp_stderr_size = 0;
    int mcpp_exit_code = runProcess(mcpp_cmdline.ptr, "", 0, &mcpp_stdout, &mcpp_stdout_size, &mcpp_stderr, &mcpp_stderr_size);
    if (mcpp_stdout) {
        fprintf(stdout, "%*s", mcpp_stdout_size, mcpp_stdout);
    }
    if (mcpp_stderr_size) {
        fprintf(stderr, "%*s", mcpp_stderr_size, mcpp_stderr);
    }
    free(mcpp_stdout);
    free(mcpp_stderr);

    if (mcpp_exit_code != 0) {
        return -3;
    }
    if (preprocess) {
        return 0;
    }

    context.fin = fopen(preprocessed_file, "rb");

    if (!context.fin) {
        fprintf(stderr, "Cannot open preprocessed input file %s", preprocessed_file);
        exit(-2);
    }

    slang_set_in(context.fin, context.scanner);

    // parse through the input until there is no more:
    do {
        slang_parse(&context);
    } while (!feof(context.fin));

    fclose(context.fin);

    for (int i = 0; i < 2 && !leavepreprocess; ++i) {
        if (remove(preprocessed_file) == 0) break;
    }

    if (context.root) {
        slang_node_t* fake_root = context.root;//new_slang_node(TRANSLATION_UNIT);
        //slang_node_attach_child(fake_root, context.root);
        FILE* f_out = fopen("ast.dot", "wb");
        if (f_out) {
            print_slang_AST(fake_root, f_out);
            fclose(f_out);
        }

        uintptr_t hlsl_lib = loadLibrary("../../lib/Debug/slang2hlsl");
        if (hlsl_lib) {
            FILE* hlsl_out = fopen("out.hlsl", "wb");
            int (*hlsl_process_slang_ast)(const slang_node_t*, FILE*) = findProcessAddress(hlsl_lib, "process_slang_ast");
            if (hlsl_process_slang_ast) {
                hlsl_process_slang_ast(fake_root, hlsl_out);
            }
            fclose(hlsl_out);
        }
    }
}