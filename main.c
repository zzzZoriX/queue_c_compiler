/*
    комманда компиляции исходников:
    gcc main.c ./libs/dot_c/_cmd.c ./libs/dot_c/lexeme.c ./libs/dot_c/lexer.c ./libs/dot_c/str.c ./libs/dot_c/tokens.c -o que
*/


#include "./libs/main_header.h"
#include "libs/dot_h/_cmd.h"

FILE* otp_file = NULL;

int
main(int argc, char** argv){
    int start_inp = 0, end_inp = 0;

    const _results res = parse(argc, start_inp, end_inp, argv); 
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
        
    }

    return __SUCCESS;
}