#include "c:/queue_c_compiler/libs/dot_h/lexeme.h"

_lexemes
define_lexeme(const string word, _lexemes* last_lexeme, const string last_word){
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
    if(comp(word, _LPAREN))        return LEX_LPAREN;
    if(comp(word, _RPAREN))        return LEX_RPAREN;
    if(comp(word, _LQPAREN))       return LEX_LQPAREN;
    if(comp(word, _RQPAREN))       return LEX_RQPAREN;
    if(comp(word, _LFPAREN))       return LEX_LFPAREN;
    if(comp(word, _RFPAREN))       return LEX_RFPAREN;
    if(comp(word, _NULL_VALUE))    return LEX_NULL_VALUE;
    if(comp(word, _DBL_TWO_DOTS))  return LEX_DBL_TWO_DOTS;
    if(comp(word, _INST_POINTER))  return LEX_INST_POINTER;
    if(comp(word, _CALL))          return LEX_CALL;

    if(
        word[0] == '\'' && 
        word[strlen(word) - 1] == '\'' && 
        strlen(word) == 3
    ) return LEX_CHAR_VAL;

    if(*last_lexeme == LEX_OBJ_NAME){
        if(comp(word, _INC)) return LEX_POST_INC;
        if(comp(word, _DEC)) return LEX_POST_DEC;
    }
    if(comp(word, _INC))           return LEX_PREF_INC;
    if(comp(word, _DEC))           return LEX_PREF_DEC;
    
    if(comp(word, _INC))           return LEX_PREF_INC;
    if(comp(word, _DEC))           return LEX_PREF_DEC;

    if(is_valid_obj_name(word))    return LEX_OBJ_NAME;

    if(is_digits(word))            return LEX_DIGIT;
    if(is_float(word))             return LEX_FLOAT;
    
    return LEX_UNDEF;
}

const char
is_digits(const string word){
    if(!word) return 0;

    for(size_t i = 0; i < strlen(word); ++i)
        if(!isdigit(word[i])) return 0;

    return 1;
}

const char
is_float(const string word){
    if(word[strlen(word) - 1] != 'f') return 0;
    char has_dot = 0, has_f = 1;

    for(size_t i = 0; i < strlen(word) - 1; ++i){
        if(word[i] == '.'){
            if(has_dot) return 0;
            has_dot = 1;
        }
        else if(!isdigit(word[i])) return 0;
    }

    return has_dot || has_f;
}

const char
isspec(const char c){
    return (
        c == ';' ||
        c == '(' ||
        c == ')' ||
        c == '{' ||
        c == '}' ||
        c == '[' ||
        c == ']' ||
        c == '?' ||
        c == '>' ||
        c == '<' ||
        c == '=' ||
        c == ',' ||
        c == '&' ||
        c == '@'
    );
}

const char
is_spec_str(const string str){
    return (
        comp(str, _ADD_ASSIGN)      ||
        comp(str, _REDUCE_ASSIGN)   ||
        comp(str, _MUL_ASSIGN)      ||
        comp(str, _DIV_ASSIGN)      ||
        comp(str, _REM_ASSIGN)      ||
        comp(str, _LE)              ||
        comp(str, _EQ)              ||
        comp(str, _GE)              ||
        comp(str, _NEQ)             ||
        comp(str, _AND)             ||
        comp(str, _OR)              ||
        comp(str, _DBL_TWO_DOTS)    ||
        comp(str, _INST_POINTER)
    );
}