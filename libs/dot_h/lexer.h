#ifndef LEXER_H
#define LEXER_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "str.h"
#include "lexeme.h"
#include "tokens.h"


typedef enum _lexer_result: int {
    _LEX_SUCCESS = -1,
    _LEX_UNKNOWN_LEXEME = -2,
    _LEX_CANT_ALLOCATE_MEM = -3
} _lexer_result;

typedef enum _state {
    _NORMAL_,
    _IN_COMMENT_,
    _IN_FLOAT_,
    _IN_UN_OP_, // унарный оператор ( ++ или -- )
    _IN_SPEC_STR_ // ->, ::, <=, && и т.д.
} _state;


/**
 * @brief функция лексера
 * 
 * @return const _lexer_result 
 */
const _lexer_result
lexer(FILE*, _token**);

/**
 * @brief устанавливает состояние(state переменную)
 * 
 */
void
set_state(const string, const char, const char); 

#endif