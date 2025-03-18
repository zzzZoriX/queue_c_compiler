/*
    комманда компиляции исходников:
    gcc main.c ./libs/dot_c/_cmd.c -o que
*/


#include "./libs/main_header.h"

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

        case _SUCCESS:
        default:
            break;
    }

    return __SUCCESS;
}