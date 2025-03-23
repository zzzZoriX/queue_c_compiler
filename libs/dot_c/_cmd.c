#include "c:/queue_c_compiler/libs/dot_h/_cmd.h"


const _results
parse(int argc, int* start, int* end, char** args){
    if(argc < 2)
        return _TOO_FEW_ARGS;
    else if(strcmp(args[1], "-otp") == 0)
        return _NO_INP_FILE;
    else if(strcmp(args[argc - 1], "-otp") == 0)
        return _NO_OTP_FILE;

    *start = 1; // второй аргумент
    int file = 1;
    while(strcmp(args[file], "-otp") != 0)
        ++file;

    *end = file;

    return _SUCCESS;
}