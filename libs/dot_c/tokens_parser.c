#include "c:/queue_c_compiler/libs/dot_h/tokens_parser.h"

void
tokens_parser(_token* tokens){
    _token* current_token = tokens;
    while(current_token){
        switch(current_token->lex){
            case LEX_INT:
            case LEX_LONG:
            case LEX_SHORT:
            case LEX_CHAR:
            case LEX_BOOL:
            case LEX_FLT:
                Node* obj_node;
                _lexemes cur_lex = current_token->lex;
                current_token = current_token->next_token;
                switch(cur_lex){
                    case LEX_FLT:
                        obj_node = make_flt_literal_const(
                            current_token->data, 
                            atof(current_token->next_token->next_token->data)
                        ); break;
                    case LEX_INT:
                        obj_node = make_int_literal_const(
                            current_token->data,
                            atoi(current_token->next_token->next_token->data)
                        ); break;
                    case LEX_CHAR:
                        obj_node = make_char_literal_const(
                            current_token->data,
                            current_token->next_token->next_token->data[1]
                        ); break;
                    case LEX_BOOL:
                        obj_node = make_bool_literal_const(
                            current_token->data,
                            (comp(current_token->next_token->next_token->data, "true") ? true : false)
                        ); break;
                    case LEX_LONG:
                        obj_node = make_long_literal_const(
                            current_token->data,
                            atol(current_token->next_token->next_token->data)
                        ); break;
                    case LEX_SHORT:
                        obj_node = make_short_literal_const(
                            current_token->data,
                            atosh(current_token->next_token->next_token->data)
                        ); break;
                    default: break;
                }
                break;
        }
    }
}