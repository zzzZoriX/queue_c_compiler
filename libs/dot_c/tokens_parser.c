#include "c:/queue_c_compiler/libs/dot_h/tokens_parser.h"


static inline bool __fastcall
is_assign(_lexemes lex){
    return 
        lex == LEX_ASSIGN       ||
        lex == LEX_ADD_ASSIGN   ||
        lex == LEX_REDUCE_ASSIGN||
        lex == LEX_DIV_ASSIGN   ||
        lex == LEX_MUL_ASSIGN   ||
        lex == LEX_REM_ASSIGN
    ;
}


Node*
tokens_parser(_token** token){
    switch ((*token)->lex){

/* ------------ литеральные константы ------------ */

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

            return lit_const;

/* ------------ литеральные константы ------------ */

/* ------------ выражения ------------ */

        case LEX_LPAREN:
        case LEX_DIGIT:
        case LEX_FLOAT:
        case LEX_CHAR_VAL:
        case LEX_OBJ_NAME:
            if(
                NEXT_TOKEN(*token)->lex == LEX_POST_INC ||
                NEXT_TOKEN(*token)->lex == LEX_POST_DEC
            ){
                Node* operand = make_empty_literal_const((*token)->data);
                *token = NEXT_TOKEN(*token);

                string op = _strdup((*token)->data);
                *token = NEXT_TOKEN(*token);

                return make_un_operation(
                    operand,
                    op
                );
            }

            return make_expr_node(token);

        case LEX_PREF_INC:
        case LEX_PREF_DEC:
            string op = _strdup((*token)->data);
            *token = NEXT_TOKEN(*token);

            Node* operand = make_expr_node(token);
            return make_un_operation(
                operand,
                op
            );

/* ------------ выражения ------------ */

/* ------------ if-else ------------ */

        case LEX_IF:
        case LEX_ELIF:
        case LEX_ELSE:
            _lexemes if_else_lexeme = (*token)->lex;
            Node
                * condition,
                * _else
            ;

            if((*token)->lex != LEX_ELSE){
                *token = NEXT_TOKEN(*token);

                 condition = make_cond_node(token); // парсим условие
            }
            *token = NEXT_TOKEN(*token);
                
            Node* body = tokens_parser(token); // парсим тело
            *token = NEXT_TOKEN(*token);

            if((*token)->lex == LEX_ELIF || (*token)->lex == LEX_ELSE)
                _else = tokens_parser(token);

            return make_if_else_node(
                if_else_lexeme,
                condition,
                body,
                _else
            );

/* ------------ if-else ------------ */

/* ------------ ввод/вывод ------------ */

        case LEX_IN:
        case LEX_OUT:
            size_t curr_args_count = 0;
            _lexemes io_lexeme = (*token)->lex;
            string format;

            *token = NEXT_TOKEN(NEXT_TOKEN(*token)); // скипаю сразу 2 токена

            format = _strdup((*token)->data);
            if(!format) exit(1);

            *token = NEXT_TOKEN(*token);
            if((*token)->lex == LEX_LPAREN)
                return make_io_node(
                    io_lexeme,
                    format,
                    NULL,
                    curr_args_count
                );
            *token = NEXT_TOKEN(*token);

            ++curr_args_count;
            string* args = (string*)malloc(sizeof(string) * curr_args_count);
            if(!args) exit(1);

            args[curr_args_count - 1] = _strdup((*token)->data);
            if(!args[curr_args_count - 1]) exit(1);
            *token = NEXT_TOKEN(*token);

            while(*token && (*token)->lex != LEX_LPAREN){
                ++curr_args_count;
                
                args = (string*)realloc(args, sizeof(string) * curr_args_count);
                if(!args) exit(1);

                args[curr_args_count - 1] = _strdup((*token)->data);
                if(!args[curr_args_count - 1]) exit(1);
                *token = NEXT_TOKEN(*token);
            }
            
            return make_io_node(
                io_lexeme,
                format,
                args,
                curr_args_count
            );

/* ------------ ввод/вывод ------------ */

/* ------------ цикл for ------------ */

        case LEX_FOR:
            Node
                * for_cond,
                * for_body,
                * iter
            ;
            
            *token = NEXT_TOKEN(*token);

            for_cond = make_cond_node(token);
            *token = NEXT_TOKEN(*token);

            if((*token)->lex == LEX_OBJ_NAME){
                string var_name = _strdup((*token)->data);
                if(!var_name) exit(1);

                *token = NEXT_TOKEN(*token);

                if(is_assign((*token)->lex)){
                    string assign = _strdup((*token)->data);
                    if(!assign) exit(1);

                    *token = NEXT_TOKEN(*token);

                    Node* expr = make_expr_node(token);

                    iter = make_bin_operation(
                        make_empty_literal_const(var_name),
                        expr,
                        assign
                    );
                }
                else if((*token)->lex == LEX_POST_INC || (*token)->lex == LEX_POST_DEC){
                    string op = _strdup((*token)->data);
                    if(!op) exit(1);

                    *token = NEXT_TOKEN(*token);

                    iter = make_un_operation(
                        make_empty_literal_const(var_name),
                        op
                    );
                }
    
                else    iter = make_empty_literal_const(var_name);

                free(var_name);
            }
            else if((*token)->lex == LEX_PREF_DEC || (*token)->lex == LEX_PREF_INC){
                string op = _strdup((*token)->data);
                if(!op) exit(1);
                *token = NEXT_TOKEN(*token);

                Node* operand = make_expr_node(token);
                *token = NEXT_TOKEN(*token);

                iter = make_un_operation(
                    operand,
                    op
                );
            }
            else{
                iter = make_expr_node(token);
                *token = NEXT_TOKEN(*token);
            }

            for_body = tokens_parser(token);

            return make_for_cycle_node(
                for_cond,
                for_body,
                iter
            );

/* ------------ цикл for ------------ */

/* ------------ цикл while ------------ */

// LEX_WHILE не рассматривается, потому что синтаксис обязывает писать сначала do, а потом while
            case LEX_DO:
                Node
                    * while_cond,
                    * while_body
                ;
                _lexemes lexeme = (*token)->lex;

                *token = NEXT_TOKEN(NEXT_TOKEN(*token));

                while_cond = make_cond_node(token);
                while_body = tokens_parser(token);

                return make_do_while_node(
                    lexeme,
                    while_cond,
                    while_body
                );

/* ------------ цикл while ------------ */

/* ------------ стейтменты ------------ */

// ->
            case LEX_INST_POINTER:
                Node* single_command = (Node*)malloc(sizeof(Node));
                if(!single_command) exit(1);

                single_command->node_type = AST_SINGLE_STMT;
                *token = NEXT_TOKEN(*token);

                single_command->op1 = tokens_parser(token);

                return single_command;

// {};
            case LEX_LFPAREN:
                Node* statements = (Node*)malloc(sizeof(Node));
                if(!statements) exit(1);

                statements->node_type = AST_MULTI_STMT;
                while((*token = NEXT_TOKEN(*token))->lex != LEX_RFPAREN){
                    Node* command = tokens_parser(token);

                    statements->op1 = command;

                    Node* next = (Node*)malloc(sizeof(Node));
                    if(!statements) exit(1);

                    next = tokens_parser(token);

                    statements->op2 = next;
                }
                *token = NEXT_TOKEN(NEXT_TOKEN(*token)); // скипаем };

                return statements;

/* ------------ стейтменты ------------ */

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