#ifndef LEXEME_H
#define LEXEME_H

#include "str.h"
#include "obj.h"

#include <stdbool.h>

#define    _VAR "var"
#define    _ARR "arr"
#define    _FUNC "fun"
#define    _STRUCT "struct"
#define    _RET "ret"
#define    _OUT "out"
#define    _IN "in"
#define    _IF "if"
#define    _ELIF "else if"
#define    _ELSE "else"
#define    _FOR "for"
#define    _WHILE "while"
#define    _DO "do"
#define    _SHORT "short"
#define    _INT "int"
#define    _LONG "long"
#define    _CHAR "char"
#define    _FLT "flt"
#define    _BOOL "bool"
#define    _UNSIGN "unsign"
#define    _POINTER "pointer"
#define    _POINTER_DEREF "@"
#define    _GET_ADDR "&"
#define    _TRUE "true"
#define    _FALSE "false"
#define    _ASSIGN "="
#define    _ADD_ASSIGN "+="
#define    _REDUCE_ASSIGN "-="
#define    _MUL_ASSIGN "*="
#define    _DIV_ASSIGN "/="
#define    _REM_ASSIGN "%="
#define    _SEMIC ";"
#define    _DOT "."
#define    _COMMA ","
#define    _QUOTES "'"
#define    _COMMENT_START "/-"
#define    _COMMENT_END "-/"
#define    _PLUS "+"
#define    _MINUS "-"
#define    _MUL "*"
#define    _DIV "/"
#define    _REM "%"
#define    _LE "<="
#define    _L "<"
#define    _EQ "=="
#define    _GE "=>"
#define    _G ">"
#define    _NEQ "!="
#define    _AND "&&"
#define    _OR "||"
#define    _INC "++"
#define    _DEC "--"
#define    _LPAREN "("
#define    _RPAREN ")"
#define    _LQPAREN "["
#define    _RQPAREN "]"
#define    _LFPAREN "{"
#define    _RFPAREN "}"
#define    _NULL_VALUE "?"
#define    _DBL_TWO_DOTS "::"
#define    _INST_POINTER "->"
#define    _CALL "call"


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
    LEX_POINTER = 22,

    LEX_POINTER_DEREF = 23,
    LEX_GET_ADDR = 24,

    LEX_TRUE = 25,
    LEX_FALSE = 26,
    LEX_ASSIGN = 27,
    LEX_ADD_ASSIGN = 28,
    LEX_REDUCE_ASSIGN = 29,
    LEX_MUL_ASSIGN = 30,
    LEX_DIV_ASSIGN = 31,
    LEX_REM_ASSIGN = 32,
    LEX_SEMIC = 33,
    LEX_DOT = 34,
    LEX_COMMA = 35,
    
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
    LEX_POST_INC = 53,
    LEX_POST_DEC = 54,

    LEX_LPAREN = 55,
    LEX_RPAREN = 56,
    LEX_LQPAREN = 57,
    LEX_RQPAREN = 58,
    LEX_LFPAREN = 59,
    LEX_RFPAREN = 60,

    LEX_NULL_VALUE = 61,
    LEX_OBJ_NAME = 62,

    LEX_DIGIT = 63,
    LEX_FLOAT = 64,
    LEX_CHAR_VAL = 65,
    LEX_DBL_TWO_DOTS = 66,
    LEX_INST_POINTER = 67,

    LEX_CALL = 68,
    LEX_STRING = 69,

    LEX_UNDEF = -1
} _lexemes;


/**
 * @brief определяет лексему по слову
 * 
 * @return _lexemes 
 */
_lexemes
define_lexeme(const string, _lexemes*, const string);

/**
 * @brief парсит строку, превращая все спец символы моего языка в спец символы языка С 
 * 
 * @return string 
 */
string
parse_string(const string);


/**
 * @brief проверяет является ли передаваемая строка только числами
 * 
 * @return const char 
 */
const char
is_digits(const string);

/**
 * @brief проверяет является ли передаваемая строка валидным значением для чисел с плавающей точкой
 * 
 * @return const char 
 */
const char
is_float(const string);

/**
 * @brief проверяет символ на то, является ли он спец. символом (.;,:_ и т.д.)
 * 
 * @return const char 
 */
 const char
 isspec(const char);

/**
 * @brief проверяет, является ли строка специальной(->, :: и т.д.)
 * 
 * @return const char 
 */
const char
is_spec_str(const string);

#endif 