#ifndef TOKENS_H
#define TOKENS_H

#include "lexeme.h"

typedef struct _token {
    char* data;
    _lexemes lex;
    struct _token* next_token;
} _token;


/**
 * @brief создает объект токена
 * 
 * @return _token* 
 */
_token*
create_token(char*, _lexemes, _token*);

/**
 * @brief создает объект пустого токена
 * 
 * @return _token* 
 */
_token*
create_empty_token();

#endif