#include "c:/queue_c_compiler/libs/dot_h/lexer.h"


const _lexer_result
lexer(FILE* ifp, _token** m_token){
    *m_token = create_empty_token();
    if(!m_token)
        return _LEX_CANT_ALLOCATE_MEM;

    char c;
    string word = NULL_STR;
    while((c = getc(ifp)) != EOF){
        if(!isspace(c)){
            if(isspec(c)){

            }
        }
    }
    
    return _LEX_SUCCESS;
}