/*
    комманда компиляции исходников:
    gcc main.c ./libs/dot_c/_cmd.c ./libs/dot_c/obj.c ./libs/dot_c/lexeme.c ./libs/dot_c/lexer.c ./libs/dot_c/str.c ./libs/dot_c/tokens.c -o que
*/


#include "./libs/main_header.h"

FILE* otp_file = NULL;
long unknown_lex_offset = 0;

int
main(int argc, char** argv){
    int start_inp = 0, end_inp = 0;

    const _results res = parse(argc, &start_inp, &end_inp, argv); 
    switch(res){
        case _TOO_FEW_ARGS:
            fprintf(stderr, "to few arguments. correct use: que <input_file> -otp <output_file>\n");
            return __ERROR;

        case _NO_INP_FILE:
            fprintf(stderr, "input file(-s) don't pointed\n");
            return __ERROR;

        case _NO_OTP_FILE:
            fprintf(stderr, "output file don't pointed\n");
            return __ERROR;

        case _SUCCESS_BUT_WO_OTP:
            otp_file = fopen(__DEFAULT_OTP_FILE_NAME, "w");
            if(!otp_file){
                fprintf(stderr, "can't open output file\n");
                return __ERROR;
            }

        case _SUCCESS:
        default:
            break;
    }

    if(!otp_file){
        otp_file = fopen(argv[argc - 1], "w");
        if(!otp_file){
            fprintf(stderr, "can't open output file\n");
            return __ERROR;
        }
    }
    
    for(int inp_file_num = start_inp; inp_file_num < end_inp; ++inp_file_num){
        FILE* curr_ifp = fopen(argv[inp_file_num], "r");
        if(!curr_ifp){
            fprintf(stderr, "Can't open input file - %s\n", argv[inp_file_num]);
            return __ERROR;
        }

        _token* current_ifp_tokens_header;
        _lexer_result lexer_result = lexer(curr_ifp, &current_ifp_tokens_header);
        fprintf(stdout, "%d\n", lexer_result);
        switch(lexer_result){
            case _LEX_UNKNOWN_LEXEME:
                fprintf(stdout, "%ld\n", unknown_lex_offset);
                fseek(curr_ifp, unknown_lex_offset, SEEK_SET);
                const string word = _read_one_word_from_stream(curr_ifp, ' ');
                fprintf(stderr, "unknown lexeme - \"%s\"\n", word);
                
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

    return __SUCCESS;
}