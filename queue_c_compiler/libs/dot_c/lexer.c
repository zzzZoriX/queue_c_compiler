#include "c:/queue_c_compiler/libs/dot_h/lexer.h"
#include <string.h>

extern long unknown_lex_offset;
extern long row;
extern long column;
static _state state = _NORMAL_;

const _lexer_result
lexer(FILE* ifp, _token** m_token){
    _token* last_token = create_empty_token();
    string word = NULL_STR;
    char c;
    
    *m_token = create_empty_token();
    if(!m_token)
        return _LEX_CANT_ALLOCATE_MEM;

    while((c = getc(ifp)) != EOF){
        if(c == '\n'){
            ++row;
            column = 1;
            continue;
        }
        
        const char next = getc(ifp);
        ungetc(next, ifp);
        set_state(word, c, next);
        
        switch(state){
            case _IN_COMMENT_:
                if(word && !comp(word, NULL_STR)){ // удаляю /-
                    free(word);
                    word = NULL_STR;
                } 
                char last_c = '\0';
                while((c = getc(ifp)) != EOF){
                    if(last_c == '-' && c == '/'){
                        state = _NORMAL_;
                        break;
                    }
                    last_c = c;
                }
                
                break;
            
            case _IN_FLOAT_:
                if(!word) word = NULL_STR;

                do{
                    word = concat_c(word, c);
                    c = getc(ifp);
                } while(c != EOF && (isdigit(c) || c == '.' || c == 'F' || c == 'f'));

                if(!is_float(word) && !is_digits(word)) goto unknown_lexeme;
                
                _lexemes lexeme = define_lexeme(word, &last_token->lex, last_token->data);
                if(lexeme == LEX_UNDEF) goto unknown_lexeme;
                
                _token* new_token = create_token(word, lexeme, NULL);
                add(*m_token, new_token);
                last_token = new_token;

                free(word);
                word = NULL_STR;
                state = _NORMAL_;
                ungetc(c, ifp);

                break;

            case _IN_UN_OP_:
                if(word && !comp(word, NULL_STR)){
                    _lexemes lexeme = define_lexeme(word, &last_token->lex, last_token->data);
                    if(lexeme == LEX_UNDEF) goto unknown_lexeme;

                    _token* new_token = create_token(word, lexeme, NULL);
                    add(*m_token, new_token);
                    last_token = new_token;

                    free(word);

                    word = NULL_STR;
                }
                char op[3] = {c, getc(ifp), '\0'};
                _lexemes op_lexeme = define_lexeme(op, &last_token->lex, last_token->data);
                if(op_lexeme == LEX_UNDEF) goto unknown_lexeme;

                _token* new_op_token = create_token(op, op_lexeme, NULL);
                add(*m_token, new_op_token);
                last_token = new_op_token;

                state = _NORMAL_;

                break;

            case _IN_SPEC_STR_:
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
                char spec[3] = {c, getc(ifp), '\0'};
                _lexemes spec_lexeme = define_lexeme(spec, &last_token->lex, last_token->data);
                if(spec_lexeme == LEX_UNDEF)
                    goto unknown_lexeme;

                _token* new_spec_token = create_token(spec, spec_lexeme, NULL);
                add(*m_token, new_spec_token);
                last_token = new_spec_token;

                state = _NORMAL_;
            
                break;

            case _IN_STR_:
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
                string str = c_concat_c(c, '\0');
                while((c = getc(ifp)) != '"' || c != EOF){
                    string new_word = concat_c(str, c);
                    if(!new_word) return _LEX_CANT_ALLOCATE_MEM;

                    if(str && !comp(str, NULL_STR))
                        free(str);
                    str = new_word;
                }

                str = parse_string(str);
                _token* str_token = create_token(str, LEX_STRING, NULL);
                add(*m_token, str_token);
                last_token = str_token;

                state = _NORMAL_;

                break;

            case _NORMAL_:
            default: 
                string word_wo_extr_spcs = dex_spaces(word);
                word = word_wo_extr_spcs;
                
                if(isspace(c)){
                    if(word && !comp(word, NULL_STR)){
                        _lexemes lexeme = define_lexeme(word, &last_token->lex, last_token->data);
                        if(lexeme == LEX_UNDEF) 
                            goto unknown_lexeme;
                    
                        if((*m_token)->lex == LEX_UNDEF){
                            (*m_token)->data = _strdup(word);
                            (*m_token)->lex = lexeme;
                            last_token = *m_token;
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
                    if(!c_str) return _LEX_CANT_ALLOCATE_MEM;

                    _lexemes spec_lexeme = define_lexeme(c_str, &last_token->lex, last_token->data);
                    _token* spec_token = create_token(c_str, spec_lexeme, NULL);
                    add(*m_token, spec_token);
                    last_token = spec_token;
                }
                else {
                    string new_word = concat_c(word, c);
                    if(!new_word) return _LEX_CANT_ALLOCATE_MEM;

                    if(word && !comp(word, NULL_STR))
                        free(word);
                    word = new_word;
                }
                ++column;
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

void
set_state(const string word, const char c, const char next){
    if(comp(word, _COMMENT_START)) state = _IN_COMMENT_;
    else if((isdigit(c) && (isdigit(next) || c == '.')) || (c == '.' && isdigit(c))) state = _IN_FLOAT_;
    else if((c == '+' && next == '+') || (c == '-' && next == '-')) state = _IN_UN_OP_;
    else if(is_spec_str(c_concat_c(c, next))) state = _IN_SPEC_STR_;
    else if(c == '"') state = _IN_STR_;
    else state = _NORMAL_;
}