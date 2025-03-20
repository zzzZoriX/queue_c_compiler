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
    if(comp(word, _TRUE))          return LEX_TRUE;
    if(comp(word, _FALSE))         return LEX_FALSE;
    if(comp(word, _ASSIGN))        return LEX_ASSIGN;
    if(comp(word, _ADD_ASSIGN))    return LEX_ADD_ASSIGN;
    if(comp(word, _REDUCE_ASSIGN)) return LEX_REDUCE_ASSIGN;
    if(comp(word, _MUL_ASSIGN))    return LEX_MUL_ASSIGN;
    if(comp(word, _DIV_ASSIGN))    return LEX_DIV_ASSIGN;
    if(comp(word, _REM_ASSIGN))    return LEX_REM_ASSIGN;
    if(comp(word, _SEMIC))         return LEX_SEMIC;
    if(comp(word, _DOT))           return LEX_DOT;
    if(comp(word, _COMMA))         return LEX_COMMA;
    if(comp(word, _QUOTES))        return LEX_QUOTES;
    if(comp(word, _COMMENT_START)) return LEX_COMMENT_START;
    if(comp(word, _COMMENT_END))   return LEX_COMMENT_END;
    if(comp(word, _PLUS))          return LEX_PLUS;
    if(comp(word, _MINUS))         return LEX_MINUS;
    if(comp(word, _MUL))           return LEX_MUL;
    if(comp(word, _DIV))           return LEX_DIV;
    if(comp(word, _REM))           return LEX_REM;
    if(comp(word, _LE))            return LEX_LE;
    if(comp(word, _L))             return LEX_L;
    if(comp(word, _EQ))            return LEX_EQ;
    if(comp(word, _GE))            return LEX_GE;
    if(comp(word, _G))             return LEX_G;
    if(comp(word, _NEQ))           return LEX_NEQ;
    if(comp(word, _AND))           return LEX_AND;
    if(comp(word, _OR))            return LEX_OR;
    /*
        надо написать определение для постфиксного и префиксного декримента и инкремента
    */
    if(comp(word, _LPAREN))        return LEX_LPAREN;
    if(comp(word, _RPAREN))        return LEX_RPAREN;
    if(comp(word, _LSPAREN))       return LEX_LSPAREN;
    if(comp(word, _RSPAREN))       return LEX_RSPAREN;
    if(comp(word, _LPFAREN))       return LEX_LFPAREN;
    if(comp(word, _RPFAREN))       return LEX_RFPAREN;
    if(comp(word, _NULL_VALUE))    return LEX_NULL_VALUE;

    return LEX_UNDEF;
}