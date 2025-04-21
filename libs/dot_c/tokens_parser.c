#include "c:/queue_c_compiler/libs/dot_h/tokens_parser.h"

void
tokens_parser(_token** token){
    switch ((*token)->lex){
        case LEX_INT:
        case LEX_LONG:
        case LEX_SHORT:
        case LEX_CHAR:
        case LEX_BOOL:
        case LEX_FLT:
        case LEX_POINTER:
            while(*token && !is_data_type((*token)->data))
                *token = (*token)->next_token;
            

        default: break;
    }

    return tokens_parser(&(*token)->next_token);
}

_data_type
data_type_str_to_enum(const string str){
    string cmp_str = tolower_str(str);

    if(comp(cmp_str, "short"))  return TYPE_SHORT;
    if(comp(cmp_str, "long"))   return TYPE_LONG;
    if(comp(cmp_str, "char"))   return TYPE_CHAR;
    if(comp(cmp_str, "bool"))   return TYPE_BOOL;
    if(comp(cmp_str, "flt"))    return TYPE_FLT;

    return TYPE_INT;
}