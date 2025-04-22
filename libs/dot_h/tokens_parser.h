#ifndef TOKENS_PARSER_H
#define TOKENS_PARSER_H

#include "ast.h"
#include "tokens.h"
#include "lexeme.h"
#include "str.h"

#include <ctype.h>

#define NEXT_TOKEN(tok) ((tok)->next_token)

/**
 * @brief парсит токены и превращает их в узлы ast
 * 
 */
Node*
tokens_parser(_token**);

/**
 * @brief выбирает нужный тип для создания литеральной константы
 * 
 * @return Node* 
 */
Node*
make_corr_type_litcnst(const string, const string);

#endif