#ifndef TOKENS_PARSER_H
#define TOKENS_PARSER_H

#include "ast.h"
#include "tokens.h"
#include "lexeme.h"
#include "str.h"

#include <ctype.h>

/**
 * @brief парсит токены и превращает их в узлы ast
 * 
 */
void
tokens_parser(_token*);

#endif