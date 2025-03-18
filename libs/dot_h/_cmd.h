#ifndef _CMD_H
#define _CMD_H

#include <stdio.h>
#include <string.h>

typedef enum Results: int {
    _SUCCESS = 0,
    _NO_INP_FILE = -1,
    _NO_OTP_FILE = -2,
    _TOO_FEW_ARGS = 1
} _results;

/**
 * @brief парсит строку вызова компилятора
 * 
 * @return const _results 
 */
const _results 
parse(int, int, int, char**);

#endif