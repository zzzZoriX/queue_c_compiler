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
Node*
tokens_parser(_token**);

#define make_auto_type_litcnst_node(n, v) _Generic((v),\
    short   : make_short_literal_const,\
    int     : make_int_literal_const,\
    long    : make_long_literal_const,\
    bool    : make_bool_literal_const,\
    char    : make_char_literal_const,\
    float   : make_flt_literal_const,\
)(n, v)

#endif