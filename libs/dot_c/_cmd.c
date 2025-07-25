#include "./dot_h/_cmd.h"

#include "dot_h/str.h"


const _results
parse(int argc, int* start, int* end, char** args, bool* flags){
    if(argc < 2)
        return _TOO_FEW_ARGS;
    else if(strcmp(args[1], "-otp") == 0)
        return _NO_INP_FILE;
    else if (strcmp(args[1], "-help") == 0)
        return _HELP;
    else if (strcmp(args[1], "-version") == 0)
        return _VERSION;

    *start = 1;

    int otp_flag_pos = -1;
    for(int i = 1; i < argc; ++i){
        if(!strcmp(args[i], "-otp")){
            if(i == argc - 1) return _NO_OTP_FILE;
            if(flags[1]) return _MULTI_OTP_FLAG;

            flags[1] = true;
            otp_flag_pos = i;
        }
        if (!strcmp(args[i], "-scc")) {
            flags[0] = true;
            *end = i;
        }
    }
    if (*end == 0 || (*end > otp_flag_pos && flags[1]))
        *end = !flags[1] ? argc : otp_flag_pos;

    for(int i = *start; i < *end; ++i){
#ifdef _WIN32
    if(!file_exists(args[i])) return _INPUT_FILE_NOT_FOUND; 
#else
    if(access(args[i], F_OK) != 0) return _INPUT_FILE_NOT_FOUND;
#endif
    }

    return _SUCCESS;
}

char*
parse_otp_file(char* s) {
    const char* dot_pos = strchr(s, '.');

    if (!dot_pos)
        return s;
    else {
        const long name_length = dot_pos - s;

        char* only_name = NULL_STR;

        for (long i = 0; i < name_length; ++i)
            only_name = concat_c(only_name, s[i]);

        return only_name;
    }
}