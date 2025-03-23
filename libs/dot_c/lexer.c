#include "c:/queue_c_compiler/libs/dot_h/lexer.h"
#include <string.h>

extern long unknown_lex_offset;

const _lexer_result
lexer(FILE* ifp, _token** m_token){
    string word = NULL_STR;
    char c;
    
    *m_token = create_empty_token();
    if(!m_token)
        return _LEX_CANT_ALLOCATE_MEM;


    while((c = getc(ifp)) != EOF){
        if(isspace(c)){
            _lexemes lexeme = define_lexeme(word);
            if(lexeme == LEX_UNDEF) 
                goto unknown_lexeme;

            if((*m_token)->lex == LEX_UNDEF){
                (*m_token)->data = _strdup(word);
                (*m_token)->lex = lexeme;
            }
            else{
                _token* new_token = create_token(word, lexeme, NULL);
                add(*m_token, new_token);
            }

            if(isspec(c)){
                const string c_str = c_concat_c(c, '\0');
                lexeme = define_lexeme(c_str);

                _token* new_tok = create_token(word, lexeme, NULL);
                add(*m_token, new_tok);
            }
            if(word && !comp(word, NULL_STR))
                free(word);

            word = NULL_STR;
            continue;
        }

        string new_word = concat_c(word, c);
        if(word && !comp(word, NULL_STR))
            free(word);
        word = new_word;
    }

    if(word && !comp(word, NULL_STR)){
        _lexemes lexeme = define_lexeme(word);
        if(lexeme == LEX_UNDEF)
            goto unknown_lexeme;

        _token* new_token = create_token(word, lexeme, NULL);
        add(*m_token, new_token);
    }

    
    return _LEX_SUCCESS;

unknown_lexeme:
    unknown_lex_offset = ftell(ifp);
    unknown_lex_offset -= strlen(word) - 1;
    return _LEX_UNKNOWN_LEXEME;
}