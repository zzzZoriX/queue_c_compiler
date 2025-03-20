#include "c:/queue_c_compiler/libs/dot_h/lexeme.h"

_lexemes
define_lexeme(const string word){
    if(comp(word, _VAR))           return LEX_VAR;
    if(comp(word, _ARR))           return LEX_ARR;
    if(comp(word, _FUNC))          return LEX_FUNC;
    if(comp(word, _STRUCT))        return LEX_STRUCT;
    if(comp(word, _RET))           return LEX_RET;
    if(comp(word, _OUT))           return LEX_OUT;
    if(comp(word, _IN))            return LEX_IN;
    if(comp(word, _IF))            return LEX_IF;
    if(comp(word, _ELIF))          return LEX_ELIF;
    if(comp(word, _ELSE))          return LEX_ELSE;
    if(comp(word, _FOR))           return LEX_FOR;
    if(comp(word, _WHILE))         return LEX_WHILE;
    if(comp(word, _DO))            return LEX_DO;
    if(comp(word, _SHORT))         return LEX_SHORT;
    if(comp(word, _INT))           return LEX_INT;
    if(comp(word, _LONG))          return LEX_LONG;
    if(comp(word, _CHAR))          return LEX_CHAR;
    if(comp(word, _FLT))           return LEX_FLT;
    if(comp(word, _BOOL))          return LEX_BOOL;
    if(comp(word, _UNSIGN))        return LEX_UNSIGN;
    if(comp(word, _CONST))         return LEX_CONST;
    if(comp(word, _POINTER))       return LEX_POINTER;
    if(comp(word, _POINTER_DEREF)) return LEX_POINTER_DEREF;
    if(comp(word, _GET_ADDR))      return LEX_GET_ADDR;

    return LEX_UNDEF;
}