#include "c:/queue_c_compiler/libs/dot_h/tokens_parser.h"

Node*
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
            
            if(!is_data_type((*token)->data)) exit(1);

            const string type = _strdup((*token)->data);
            *token = NEXT_TOKEN(*token);

            Node* lit_const = make_corr_type_litcnst((*token)->data, type);
            
            *token = NEXT_TOKEN(*token);

            char bin_op = (*token)->data[0];

            *token = NEXT_TOKEN(*token);

            return make_bin_operation(
                lit_const, 
                tokens_parser(token), 
                bin_op
            );

        case LEX_LPAREN:
        case LEX_DIGIT:
        case LEX_FLOAT:
        case LEX_CHAR_VAL:
        case LEX_OBJ_NAME:
            return make_expr_node(token);

        default: break;
    }

    return tokens_parser(&(*token)->next_token);
}

Node*
make_corr_type_litcnst(const string name, const string type){
    if(comp(type, "bool"))      return make_bool_literal_const(name, false);
    if(comp(type, "flt"))       return make_flt_literal_const(name, 0);
    if(comp(type, "short"))     return make_short_literal_const(name, 0);
    if(comp(type, "long"))      return make_long_literal_const(name, 0);
    if(comp(type, "char"))      return make_char_literal_const(name, 0);
    
    return make_int_literal_const(name, 0);
}