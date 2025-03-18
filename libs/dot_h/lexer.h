#ifndef LEXER_H
#define LEXER_H

typedef enum _lexemes: int {
    LEX_VAR = 0,
    LEX_ARR = 1,
    LEX_FUNC = 2,
    LEX_STRUCT = 3,

    LEX_RET = 4,
    LEX_OUT = 5,
    LEX_IN = 6,
    LEX_IF = 7,
    LEX_ELIF = 8,
    LEX_ELSE = 9,
    LEX_FOR = 10,
    LEX_WHILE = 11,
    LEX_DO = 12,
    
    LEX_SHORT = 13,
    LEX_INT = 14,
    LEX_LONG = 15,
    LEX_CHAR = 16,
    LEX_FLT = 17,
    LEX_BOOL = 18,
    LEX_UNSIGN = 19,
    LEX_CONST = 20,
    LEX_POINTER = 21,

    LEX_POINTER_DEREF = 22,
    LEX_GET_ADDR = 23,

    LEX_TRUE = 24,
    LEX_FALSE = 25,
    LEX_ASSIGN = 26,
    LEX_ADD_ASSIGN = 27,
    LEX_REDUCE_ASSIGN = 28,
    LEX_MUL_ASSIGN = 29,
    LEX_DIV_ASSIGN = 30,
    LEX_REM_ASSIGN = 31,
    LEX_SEMIC = 32,
    LEX_DOT = 33,
    LEX_COMMA = 34,
    LEX_QUOTES = 35,
    
    LEX_COMMENT_START = 36,
    LEX_COMMENT_END = 37,
    
    LEX_PLUS = 38,
    LEX_MINUS = 39,
    LEX_MUL = 40,
    LEX_DIV = 41,
    LEX_REM = 42,

    LEX_LE = 43,
    LEX_L = 44,
    LEX_EQ = 45,
    LEX_GE = 46,
    LEX_G = 47,
    LEX_NEQ = 48,
    
    LEX_AND = 49,
    LEX_OR = 50,

    LEX_PREF_INC = 51,
    LEX_PREF_DEC = 52,
    LEX_POST_INT = 53,
    LEX_POST_DEC = 54
} _lexemes;

#endif