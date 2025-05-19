#ifndef _CMD_H
#define _CMD_H

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#ifdef _WIN32
static inline const char __fastcall
file_exists(const char* file_name){
    FILE* f = fopen(file_name, "r");
    if(!f) return 0;
    fclose(f);
    return 1; }
#else
#include <unistd.h>
#endif // _WIN32

typedef enum Results: int {
    _SUCCESS = 0,
    _SUCCESS_BUT_WO_OTP = 1,
    _HELP = 2,
    _NO_INP_FILE = -1,
    _NO_OTP_FILE = -2,
    _TOO_FEW_ARGS = -3,
    _MULTI_OTP_FLAG = -4,
    _INPUT_FILE_NOT_FOUND = -5
} _results;

/**
 * @brief парсит строку вызова компилятора
 * 
 * @return const _results 
 */
const _results 
parse(int, int*, int*, char**, bool);

#endif