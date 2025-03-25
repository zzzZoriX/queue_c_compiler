/*
    комманда компиляции исходников:
    gcc main.c ./libs/dot_c/_cmd.c ./libs/dot_c/obj.c ./libs/dot_c/lexeme.c ./libs/dot_c/lexer.c ./libs/dot_c/str.c ./libs/dot_c/tokens.c -o que
*/


#include "./libs/main_header.h"

FILE* otp_file = NULL;
long unknown_lex_offset = 0, row = 1, column = 1;
static string otp_file_name = NULL_STR;

int
main(int argc, char** argv){
    int start_inp = 0, end_inp = 0;

    const _results res = parse(argc, &start_inp, &end_inp, argv); 
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
            otp_file_name = __DEFAULT_OTP_FILE_NAME;
            break;

        case _SUCCESS:
        default:
            otp_file_name = argv[argc - 1];
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
    }

    fclose(otp_file);

    fprintf(stdout, "the output file - %s was created\n", otp_file_name);

    return __SUCCESS;
}