#include "c:/queue_c_compiler/libs/dot_h/_cmd.h"


const _results
parse(int argc, int* start, int* end, char** args){
    if(argc < 2)
        return _TOO_FEW_ARGS;
    else if(strcmp(args[1], "-otp") == 0)
        return _NO_INP_FILE;

    *start = 1;

    int otp_flag_pos = -1;
    for(int i = 1; i < argc; ++i){
        if(!strcmp(args[i], "-otp")){
            if(i == argc - 1) return _NO_OTP_FILE;
            if(otp_flag_pos != -1) return _MULTI_OTP_FLAG;

            otp_flag_pos = i;
        }
    }

    *end = otp_flag_pos == -1 ? argc : otp_flag_pos;

    for(int i = *start; i < *end; ++i){
#ifdef _WIN32
    if(!file_exists(args[i])) return _INPUT_FILE_NOT_FOUND; 
#else
    if(access(args[i], F_OK) != 0) return _INPUT_FILE_NOT_FOUND;
#endif
    }

    return otp_flag_pos == -1 ? _SUCCESS_BUT_WO_OTP : _SUCCESS;
}