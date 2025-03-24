#include "c:/queue_c_compiler/libs/dot_h/lexer.h"

extern long unknown_lex_offset;

const _lexer_result
lexer(FILE* ifp, _token** m_token){
    printf("test\n");
    _token* last_token = create_empty_token();
    string word = NULL_STR;
    char c;
    
    *m_token = create_empty_token();
    if(!m_token)
        return _LEX_CANT_ALLOCATE_MEM;

    while((c = getc(ifp)) != EOF){
        if(c == '\n') continue;
        
        if(isspace(c)){
            if(word && !comp(word, NULL_STR)){
                string word_wo_extr_spcs = dex_spaces(word);
                free(word);
                word = word_wo_extr_spcs;

                _lexemes lexeme = define_lexeme(word, &last_token->lex, last_token->data);
                if(lexeme == LEX_UNDEF) 
                    goto unknown_lexeme;

                if((*m_token)->lex == LEX_UNDEF){
                    (*m_token)->data = _strdup(word);
                    (*m_token)->lex = lexeme;
                }
                else{
                    _token* new_token = create_token(word, lexeme, NULL);
                    add(*m_token, new_token);

                    last_token = new_token;
                }

                if(word && !comp(word, NULL_STR))
                    free(word);

                word = NULL_STR;
            }
        }
        else if(isspec(c)){
            if(word && !comp(word, NULL_STR)){
                _lexemes lexeme = define_lexeme(word, &last_token->lex, last_token->data);
                if(lexeme == LEX_UNDEF)
                    goto unknown_lexeme;

                _token* new_token = create_token(word, lexeme, NULL);
                add(*m_token, new_token);
                last_token = new_token;

                free(word);
                word = NULL_STR;
            }

            const string c_str = c_concat_c(c, '\0');
            _lexemes spec_lexeme = define_lexeme(c_str, &last_token->lex, last_token->data);
            _token* spec_token = create_token(c_str, spec_lexeme, NULL);
            add(*m_token, spec_token);
            last_token = spec_token;

            free(c_str);
        }
        else {
            string new_word = concat_c(word, c);
            if(word && !comp(word, NULL_STR))
                free(word);
            word = new_word;
        }
    }

    if(word && !comp(word, NULL_STR)){
        _lexemes lexeme = define_lexeme(word, &last_token->lex, last_token->data);
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