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
#define    _ELIF "elseif"
#define    _ELSE "else"
#define    _FOR "for"
#define    _WHILE "while"
#define    _VOID ".."
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
#define    _STRUCT_VALUE_INIT ":"
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
#define    _PTR_CALL_TO_FIELD ":>"
#define    _INST_POINTER "->"
#define    _CALL "call"


typedef enum _lexemes: int {
    LEX_VAR,
    LEX_ARR,
    LEX_FUNC,
    LEX_STRUCT,

    LEX_RET,
    LEX_OUT,
    LEX_IN,
    LEX_IF,
    LEX_ELIF,
    LEX_ELSE,
    LEX_FOR,
    LEX_WHILE,

    LEX_VOID_TYPE,
    LEX_SHORT,
    LEX_INT,
    LEX_LONG,
    LEX_CHAR,
    LEX_FLT,
    LEX_BOOL,
    LEX_UNSIGN,
    LEX_POINTER,

    LEX_POINTER_DEREF,
    LEX_GET_ADDR,

    LEX_TRUE,
    LEX_FALSE,
    LEX_ASSIGN,
    LEX_ADD_ASSIGN,
    LEX_REDUCE_ASSIGN,
    LEX_MUL_ASSIGN,
    LEX_DIV_ASSIGN,
    LEX_REM_ASSIGN,

    LEX_SEMIC,
    LEX_DOT,
    LEX_COMMA,
    
    LEX_COMMENT_START,
    LEX_COMMENT_END,
    
    LEX_PLUS,
    LEX_MINUS,
    LEX_MUL,
    LEX_DIV,
    LEX_REM,

    LEX_LE,
    LEX_L,
    LEX_EQ,
    LEX_GE,
    LEX_G,
    LEX_NEQ,
    
    LEX_AND,
    LEX_OR,

    LEX_PREF_INC,
    LEX_PREF_DEC,
    LEX_POST_INC,
    LEX_POST_DEC,

    LEX_LPAREN,
    LEX_RPAREN,
    LEX_LQPAREN,
    LEX_RQPAREN,
    LEX_LFPAREN,
    LEX_RFPAREN,

    LEX_NULL_VALUE,
    LEX_OBJ_NAME,

    LEX_STRUCT_VALUE_INIT,
    LEX_DIGIT,
    LEX_FLOAT,
    LEX_CHAR_VAL,
    LEX_HEX_VAL,
    LEX_BIN_VAL,

    LEX_DBL_TWO_DOTS, // ::
    LEX_PTR_CALL_TO_FIELDS, // :>
    LEX_INST_POINTER,

    LEX_CALL,
    LEX_STRING,
    LEX_END,

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

/**
 * @brief проверяет является ли строка типом данных
 * 
 * @return true 
 * @return false 
 */
bool
is_data_type(const string);

/**
 * @brief проверяет является ли лексема оператором
 * 
 * @return true 
 * @return false 
 */
bool
lex_is_operator(const _lexemes);

#endif 