#ifndef TOKENS_H
#define TOKENS_H

#include "lexeme.h"

typedef struct _token {
    char* data;
    _lexemes lex;
    struct _token* next_token;
} _token;

#define CREATE_STATIC_EMPTY_TOKEN() (&(_token){NULL, LEX_UNDEF, NULL})


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

/**
 * @brief добавляет токен в конец связанного списка
 * 
 */
void
add(_token*, _token*);

/**
 * @brief освобождает память всех токенов
 * 
 */
void
release(_token*);

#endif