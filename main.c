/*
    комманда компиляции исходников:
    gcc main.c ./libs/dot_c/debug_ast.c ./libs/dot_c/parse_ast.c ./libs/dot_c/ast.c ./libs/dot_c/tokens_parser.c ./libs/dot_c/_cmd.c ./libs/dot_c/obj.c ./libs/dot_c/lexeme.c ./libs/dot_c/lexer.c ./libs/dot_c/str.c ./libs/dot_c/tokens.c -o que
*/
#define LEX_DEBUG 0
#define AST_DEBUG 0


#include "./libs/main_header.h"

FILE* otp_file = NULL;
long unknown_lex_offset = 0, row = 1, column = 1;
static string otp_file_name = NULL_STR;

int
main(int argc, char** argv){
    int start_inp = 0, end_inp = 0;
    bool scc_flag = false;

    const _results res = parse(argc, &start_inp, &end_inp, argv, &scc_flag);
    switch(res){
        case _TOO_FEW_ARGS:
            fprintf(stderr, "to few arguments. correct use: que <input_file> -otp <output_file>\n\tor\nque <input_file>\n");
            return __ERROR;

        case _NO_INP_FILE:
            fprintf(stderr, "input file(-s) don't pointed\n");
            return __ERROR;

        case _NO_OTP_FILE:
            fprintf(stderr, "output file don't pointed\n");
            return __ERROR;

        case _MULTI_OTP_FLAG:
            fprintf(stderr, "-otp flag has been writted too many times\n");
            return __ERROR;

        case _INPUT_FILE_NOT_FOUND:
            fprintf(stderr, "cant find an input files\n");
            return __ERROR;

        case _SUCCESS_BUT_WO_OTP:
            otp_file_name = concat(__DEFAULT_OTP_FILE_NAME, ".c");
            break;

        case _HELP:
            printf(
                "\tflags:\n"
                "  -otp - set output file. use:\n"
                "\tque <input_file> -otp <output_file_name>\n\n"
                "  -help - print info of compiler\n\n"
                "  -scc - determines whether the C file will be printed or not. use:\n"
                "\tque <input_file> -scc\n\n"
                "  -version - print current version of your compiler\n"
            );
            return 0;

        case _VERSION:
            printf("%s\n", __QUEUE_VERSION__);
            return 0;

        case _SUCCESS:
        default:
            otp_file_name = concat(argv[argc - 1], ".c");
            break;
    }

    otp_file = fopen(otp_file_name, "w");
    if(!otp_file){
        fprintf(stderr, "can't open output file\n");
        return __ERROR;
    }
    
    for(int inp_file_num = start_inp; inp_file_num < end_inp; ++inp_file_num){
        FILE* curr_ifp = fopen(argv[inp_file_num], "r");
        if(!curr_ifp){
            fprintf(stderr, "Can't open input file - %s\n", argv[inp_file_num]);
            return __ERROR;
        }

// лексер

        _token* current_ifp_tokens_header;
        _lexer_result lexer_result = lexer(curr_ifp, &current_ifp_tokens_header);
        switch(lexer_result){
            case _LEX_UNKNOWN_LEXEME:
                fseek(curr_ifp, unknown_lex_offset, SEEK_SET);
                const string word = _read_one_word_from_stream(curr_ifp, ' ');
                fprintf(stderr, "%ld.%ld: unknown lexeme - \"%s\"\n", row, column, word);
                
                free(word);
                release(current_ifp_tokens_header);
                fclose(curr_ifp);
                fclose(otp_file);

                return __ERROR;

            case _LEX_CANT_ALLOCATE_MEM:
                fprintf(stderr, "can't allocate memory for lexical analisys\n");
                return __ERROR;

            case _LEX_SUCCESS:
            default: break;
        }

        add(
            current_ifp_tokens_header, 
            create_token(
                NULL_STR,
                LEX_END,
                NULL
            )
        );

// парсер
#if LEX_DEBUG == 1
        const _token* c = current_ifp_tokens_header;
        while (c) {
            printf("%s\t|\t%d\n", c->data, c->lex);
            c = c->next_token;
        }
#endif


        Node* head = make_stmt_node(&current_ifp_tokens_header);

#if AST_DEBUG == 1
        traverse_ast(head, 0);
#endif

        code_gen(head, otp_file);
    }

    fclose(otp_file);

    string name = c_concat_c(otp_file_name[0], '\0');
    for (int i = 1; i < strlen(otp_file_name); ++i) {
        if (otp_file_name[i] == '.') {
            name = concat_c(name, otp_file_name[i]);
            break;
        }
        name = concat_c(name, otp_file_name[i]);
    }

    string otp_exe_file_name = concat(name, "exe");
    free(name);

    string command = concat("gcc ", concat(otp_file_name, concat(" -o ", otp_exe_file_name)));
    system(command);

    if (!scc_flag) {
#ifdef __WIN32
        DeleteFile(otp_file_name);
#else
        unlink(otp_file_name);
#endif
    }

    fprintf(stdout, "the output file - %s was created\n", otp_exe_file_name);

    return __SUCCESS;
}