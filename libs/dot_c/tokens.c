#include "c:/queue_c_compiler/libs/dot_h/tokens.h"


_token*
create_token(char* data, _lexemes lex, _token* next_token){
    _token* new_token = (_token*)malloc(sizeof(_token));
    if(!new_token)
        return NULL;

    new_token->next_token = next_token;
    new_token->lex = lex;
    new_token->data = _strdup(data);
    if(!data){
        free(new_token);
        return NULL;
    }

    return new_token;
}

_token*
create_empty_token(){
    _token* new_token = (_token*)malloc(sizeof(_token));
    if(!new_token)
        return NULL;

    new_token->next_token = NULL;
    new_token->data = NULL;
    new_token->lex = LEX_UNDEF;

    return new_token;
}

void
add(_token* head, _token* to_add){
    _token* cur = head;
    while(cur->next_token)
        cur = cur->next_token;

    cur->next_token = to_add;
}

void
release(_token* head){
    _token* temp;
    while(head){
        temp = head->next_token;
        
        free(head->data);
        free(head);

        head = temp;
    }
}