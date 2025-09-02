#include "./dot_h/tokens_parser.h"
#include "dot_h/ast.h"
#include "dot_h/lexeme.h"
#include "dot_h/str.h"
#include "dot_h/tokens.h"

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

/* ------------ объекты ------------ */

        case LEX_STRUCT:
            *token = NEXT_TOKEN(*token);

            Node** fields = NULL;
            int count = 0;
            
            string name = _strdup((*token)->data);
            if(!name) exit(1);

            *token = NEXT_TOKEN(*token); // скипаем <имя>

            if((*token)->lex != LEX_SEMIC){
                *token = NEXT_TOKEN(*token);

                ++count;
                fields = (Node**)malloc(sizeof(Node*) * count);
                if(!fields) exit(1);

                Node* field = tokens_parser(token);
                fields[count - 1] = field;

                if((*token)->lex == LEX_SEMIC) *token = NEXT_TOKEN(*token);

                while((*token)->lex != LEX_RFPAREN && (*token)->lex != LEX_END){
                    ++count;
                    fields = (Node**)realloc(fields, sizeof(Node*) * count);
                    if(!fields) exit(1);

                    Node* field = tokens_parser(token);
                    fields[count - 1] = field;

                    if((*token)->lex == LEX_SEMIC) *token = NEXT_TOKEN(*token);
                }

                *token = NEXT_TOKEN(NEXT_TOKEN(*token));
            }

            return make_struct_node(name, fields, count);

        case LEX_FUNC:
            *token = NEXT_TOKEN(*token);
            
            Node
                * fun_header,
                * body = NULL,
                ** func_args = NULL
            ;

            if((*token)->lex == LEX_STRUCT){
                string fun_type = concat(
                    (*token)->data,
                    c_concat(' ', (*token)->next_token->data)
                );

                *token = NEXT_TOKEN(NEXT_TOKEN(*token));

                fun_header = make_corr_type_litcnst((*token)->data, fun_type, false, false);

                *token = NEXT_TOKEN(*token);
            }
            else
                fun_header = tokens_parser(token);

            fun_header->node_type = AST_FUNCTION;

            *token = NEXT_TOKEN(*token); // скипаем (

            int args_count = 0;
            if((*token)->lex != LEX_RPAREN) {
                ++args_count;
                func_args = (Node**)malloc(sizeof(Node*) * args_count);
                if (!func_args) exit(1);

                Node* arg = tokens_parser(token);
                func_args[args_count - 1] = arg;

                while((*token)->lex != LEX_RPAREN && (*token)->lex != LEX_END){
                    *token = NEXT_TOKEN(*token);

                    ++args_count;
                    func_args = (Node**)realloc(func_args, sizeof(Node*) * args_count);
                    if (!func_args) exit(1);

                    arg = tokens_parser(token);
                    func_args[args_count - 1] = arg;
                }
            }
            *token = NEXT_TOKEN(*token);
            if ((*token)->lex == LEX_LFPAREN)
                body = tokens_parser(token);

            return make_function_node(
                fun_header,
                func_args,
                args_count,
                body
            );

        case LEX_ARR:
            *token = NEXT_TOKEN(*token);
            const bool is_ptr_arr = (*token)->lex == LEX_POINTER;
            bool is_unsign_arr = false;
            _node_type arr_type = AST_EMPTY_ARRAY;

            while (*token && !is_data_type((*token)->data) && (*token)->lex != LEX_END) {
                if ((*token)->lex == LEX_UNSIGN)
                    is_unsign_arr = true;

                if((*token)->lex == LEX_STRUCT)
                    break;

                *token = NEXT_TOKEN(*token);
            }

            if (!is_data_type((*token)->data)) exit(1);

            string type_arr;
            if((*token)->lex == LEX_STRUCT){
                type_arr = concat(
                    (*token)->data,
                    c_concat(' ', (*token)->next_token->data)
                );

                *token = NEXT_TOKEN(NEXT_TOKEN(*token));
            }
            else{
                type_arr = _strdup((*token)->data);
                *token = NEXT_TOKEN(*token);
            }

            Node* array_head = make_corr_type_litcnst((*token)->data, type_arr, is_ptr_arr, is_unsign_arr);
            *token = NEXT_TOKEN(NEXT_TOKEN(*token)); // скипаем <имя массива>[

            if (atol((*token)->data) < 0) exit(1);
            const size_t size_of_arr = atol((*token)->data);

            Node** array_data = (Node**)calloc(size_of_arr, sizeof(Node*));
            if (!array_data) exit(1);

            for (size_t i = 0; i < size_of_arr; ++i)
                array_data[i] = CREATE_EMPTY_AST();

            *token = NEXT_TOKEN(NEXT_TOKEN(*token)); // скипаем <размер>]

            if((*token)->lex == LEX_RPAREN || (*token)->lex == LEX_COMMA)
                return make_arr_node(array_head->constant, size_of_arr, array_data, AST_ARRAY_AS_FUNC_PARAM);

            *token = NEXT_TOKEN(*token);

            if((*token)->lex == LEX_STRUCT_VALUE_INIT){
                *token = NEXT_TOKEN(*token);
                return make_arr_node(array_head->constant, size_of_arr, array_data, AST_ARRAY_WO_INIT);
            }

            switch ((*token)->lex) {
                case LEX_LFPAREN:
                    *token = NEXT_TOKEN(*token);

                    for (size_t i = 0; i < size_of_arr; ++i)
                        array_data[i] = tokens_parser(token);

                    arr_type = AST_ARRAY_FULL_INIT;

                    break;

                case LEX_LQPAREN:
                    while (*token && (*token)->lex != LEX_SEMIC && (*token)->lex != LEX_END) {
                        if ((*token)->lex == LEX_LQPAREN) *token = NEXT_TOKEN(*token);

                        const size_t index = atol((*token)->data);

                        *token = NEXT_TOKEN(NEXT_TOKEN(NEXT_TOKEN(*token))); // скипаем <индекс>] =
                        array_data[index] = tokens_parser(token);
                        if ((*token)->lex != LEX_SEMIC && (*token)->lex != LEX_END)
                            *token = NEXT_TOKEN(*token);
                    }
                    
                    arr_type = AST_ARRAY_PARTIALLY_INIT;

                case LEX_NULL_VALUE:
                default:
                    break;
            }

            *token = NEXT_TOKEN(*token);

            return make_arr_node(array_head->constant, size_of_arr, array_data, arr_type);

        case LEX_VAR:
            *token = NEXT_TOKEN(*token);

/* ------------ объекты ------------ */

/* ------------ литеральные константы ------------ */

        case LEX_VOID_TYPE:
        case LEX_INT:
        case LEX_LONG:
        case LEX_SHORT:
        case LEX_CHAR:
        case LEX_BOOL:
        case LEX_FLT:
        case LEX_POINTER:
        case LEX_UNSIGN:
            bool is_unsign = (*token)->lex == LEX_UNSIGN;
            const bool is_ptr = (*token)->lex == LEX_POINTER;

            while(*token && !is_data_type((*token)->data) && (*token)->lex != LEX_END) {
                if ((*token)->lex == LEX_UNSIGN)
                    is_unsign = true;

                if((*token)->lex == LEX_STRUCT)
                    break;

                *token = (*token)->next_token;
            }

            if((*token)->lex == LEX_STRUCT){
                string type = concat(
                    (*token)->data,
                    c_concat(' ', (*token)->next_token->data)
                );

                *token = NEXT_TOKEN(NEXT_TOKEN(*token));

                Node* lit_cnst = make_corr_type_litcnst((*token)->data, type, is_ptr, is_unsign);

                *token = NEXT_TOKEN(*token);

                if(is_assign((*token)->lex)){
                    string op = _strdup((*token)->data);
                    if (!op)    exit(1);
                    
                    *token = NEXT_TOKEN(*token);
                    
                    Node* expr = NULL;
                    
                    lit_cnst->node_type = AST_LIT_CNST_WO_INIT;
                    
                    *token = NEXT_TOKEN(*token);
                    
                    Node* assign = make_bin_operation(
                        lit_cnst,
                        expr,
                        op
                    );
                
                    return assign;
                }

                return lit_cnst;
            }
            
            if(!is_data_type((*token)->data)) exit(1);

            const string type = _strdup((*token)->data);
            *token = NEXT_TOKEN(*token);

            Node* lit_const = make_corr_type_litcnst((*token)->data, type, is_ptr, is_unsign);
            
            *token = NEXT_TOKEN(*token);

            if (is_assign((*token)->lex)) {
                string op = _strdup((*token)->data);
                if (!op)    exit(1);

                *token = NEXT_TOKEN(*token);

                Node* expr = NULL;

                if((*token)->lex == LEX_STRUCT_VALUE_INIT)
                    lit_const->node_type = AST_LIT_CNST_WO_INIT;
                else
                    expr = tokens_parser(token);

                *token = NEXT_TOKEN(*token);

                Node* assign = make_bin_operation(
                    lit_const,
                    expr,
                    op
                );

                return assign;
            }

            return lit_const;

/* ------------ литеральные константы ------------ */

/* ------------ выражения ------------ */

        case LEX_LPAREN:
        case LEX_DIGIT:
        case LEX_FLOAT:
        case LEX_CHAR_VAL:
        case LEX_TRUE:
        case LEX_FALSE:
        case LEX_NULL_VALUE:
            return make_expr_node(token);

        case LEX_PREF_INC:
        case LEX_PREF_DEC:
            string op = _strdup((*token)->data);
            *token = NEXT_TOKEN(*token);

            Node* operand = tokens_parser(token);
            *token = NEXT_TOKEN(*token);
            Node* un_op = make_un_operation(
                operand,
                op
            );
            un_op->node_type = comp(op, "++") ? AST_INC_PREF : AST_DEC_PREF;

            return un_op;

/* ------------ выражения ------------ */

/* ------------ if-else ------------ */

        case LEX_IF:
        case LEX_ELIF:
        case LEX_ELSE:
            _lexemes if_else_lexeme = (*token)->lex;
            Node
                * condition = NULL,
                * _else = NULL
            ;

            if((*token)->lex != LEX_ELSE){
                *token = NEXT_TOKEN(*token);

                 condition = make_expr_node(token); // парсим условие
            }
            else *token = NEXT_TOKEN(*token);
                
            Node* if_body = tokens_parser(token); // парсим тело

            while(
                (*token)->lex == LEX_RPAREN ||
                (*token)->lex == LEX_RQPAREN ||
                (*token)->lex == LEX_RFPAREN
            ) *token = NEXT_TOKEN(*token);

            if((*token)->lex == LEX_SEMIC) 
                *token = NEXT_TOKEN(*token);

            if((*token)->lex == LEX_ELIF || (*token)->lex == LEX_ELSE)
                _else = tokens_parser(token);

            return make_if_else_node(
                if_else_lexeme,
                condition,
                if_body,
                _else
            );

/* ------------ if-else ------------ */

/* ------------ ввод/вывод ------------ */

        case LEX_IN:
        case LEX_OUT:
            int curr_args_count = 0;
            _lexemes io_lexeme = (*token)->lex;
            string format;

            *token = NEXT_TOKEN(NEXT_TOKEN(*token)); // скипаю сразу 2 токена

            format = _strdup((*token)->data);
            if(!format) exit(1);

            *token = NEXT_TOKEN(*token);
            if((*token)->lex == LEX_RPAREN)
                return make_io_node(
                    io_lexeme,
                    format,
                    NULL,
                    curr_args_count
                );
            *token = NEXT_TOKEN(*token);

            ++curr_args_count;
            Node** args = (Node**)malloc(sizeof(Node*) * curr_args_count);
            if(!args) exit(1);

            args[curr_args_count - 1] = tokens_parser(token);
            if(!args[curr_args_count - 1]) exit(1);

            if ((*token)->lex != LEX_RPAREN)
                *token = NEXT_TOKEN(*token);

            else {
                *token = NEXT_TOKEN(NEXT_TOKEN(*token));
                return make_io_node(
                    io_lexeme,
                    format,
                    args,
                    curr_args_count
                );
            }

            while(*token && (*token)->lex != LEX_RPAREN){
                ++curr_args_count;
                
                args = (Node**)realloc(args, sizeof(Node) * curr_args_count);
                if(!args) exit(1);

                args[curr_args_count - 1] = tokens_parser(token);
                if(!args[curr_args_count - 1]) exit(1);
                if ((*token)->lex != LEX_RPAREN)
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
            
            *token = NEXT_TOKEN(NEXT_TOKEN(*token));

            for_cond = make_expr_node(token);

            iter = tokens_parser(token);

            for_body = tokens_parser(token);

            return make_for_cycle_node(
                for_cond,
                for_body,
                iter
            );

/* ------------ цикл for ------------ */

/* ------------ цикл while ------------ */

        case LEX_WHILE:
            Node
                * while_cond,
                * while_body
            ;
            _lexemes lexeme = (*token)->lex;
            
            *token = NEXT_TOKEN(*token);
            
            while_cond = make_expr_node(token);
            while_body = tokens_parser(token);
            
            return make_do_while_node(
                lexeme,
                while_cond,
                while_body
            );

/* ------------ цикл while ------------ */

/* ------------ функция call ------------ */

        case LEX_CALL:
            *token = NEXT_TOKEN(*token);

            Node
                * base = make_empty_literal_const((*token)->data, false, false),
                ** calling_func_args = NULL
            ;

            *token = NEXT_TOKEN(NEXT_TOKEN(*token));

            int func_args_count = 0;
            if((*token)->lex != LEX_RPAREN) {
                ++func_args_count;
                calling_func_args = (Node**)malloc(sizeof(Node*) * func_args_count);
                if (!calling_func_args) exit(1);

                Node* current_arg = tokens_parser(token);
                calling_func_args[func_args_count - 1] = current_arg;

                while((*token)->lex != LEX_RPAREN && (*token)->lex != LEX_END){
                    *token = NEXT_TOKEN(*token);

                    ++func_args_count;
                    calling_func_args = (Node**)realloc(calling_func_args, sizeof(Node*) * func_args_count);
                    if (!calling_func_args) exit(1);

                    current_arg = tokens_parser(token);
                    calling_func_args[func_args_count - 1] = current_arg;
                }
            }
            *token = NEXT_TOKEN(*token);

            Node* call_op = make_un_operation(
                make_function_node(
                    base,
                    calling_func_args,
                    func_args_count,
                    NULL
                ),
                _CALL
            );

            if ((*token)->lex == LEX_SEMIC)
                call_op->is_standalone = true;

            return call_op;

/* ------------ функция call ------------ */

/* ------------ функция ret ------------ */

        case LEX_RET:
            string ret = _strdup((*token)->data);
            if (!ret) exit(1);
            Node* ret_expr = NULL;

            *token = NEXT_TOKEN(*token);

            if ((*token)->lex  != LEX_SEMIC)
                ret_expr = tokens_parser(token);

            *token = NEXT_TOKEN(*token);

            return make_un_operation(
                ret_expr,
                ret
            );


/* ------------ функция ret ------------ */

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
            return make_stmt_node(token);

/* ------------ стейтменты ------------ */

/* ------------ операции с переменными ------------ */

        case LEX_OBJ_NAME:
            _lexemes next_lex = NEXT_TOKEN(*token)->lex;
            string var_name = _strdup((*token)->data);
            if(!var_name)   exit(1);
            
            if(
                next_lex == LEX_POST_INC ||
                next_lex == LEX_POST_DEC
            ){
                Node* operand = make_empty_literal_const(var_name, false, false);
                free(var_name);

                *token = NEXT_TOKEN(*token);

                string op = _strdup((*token)->data);
                *token = NEXT_TOKEN(*token);
            
                Node* post_un_op = make_un_operation(
                    operand,
                    op
                );
                post_un_op->node_type = next_lex == LEX_POST_INC ? AST_INC_POST : AST_DEC_POST;

                return post_un_op;
            }
            else if(is_assign(next_lex)){
                *token = NEXT_TOKEN(*token);

                string op = _strdup((*token)->data);
                if(!op) exit(1);
            
                *token = NEXT_TOKEN(*token);
            
                Node* expr = make_expr_node(token);

                Node* obj = (Node*)malloc(sizeof(Node));
                if(!obj) exit(1);

                obj->node_type = AST_LIT_CNST;
                obj->constant.name = _strdup(var_name);
                if (!obj->constant.name) exit(1);

                obj->constant.type = TYPE_NULL;
            
                return make_bin_operation(
                    obj,
                    expr,
                    op
                );
            }
            else if (next_lex == LEX_LQPAREN) {
                Node* node = make_expr_node(token);

                if(is_assign((*token)->next_token->lex)){
                    *token = NEXT_TOKEN(*token);

                    string op = _strdup((*token)->data);
                    if(!op) exit(1);
                    
                    *token = NEXT_TOKEN(*token);
                    
                    Node* expr = make_expr_node(token);

                    return make_bin_operation(node, expr, op);
                }

                return node;
            }
            else if(next_lex == LEX_DBL_TWO_DOTS || next_lex == LEX_PTR_CALL_TO_FIELDS){
                Node* fields_access = make_expr_node(token);

                if(is_assign((*token)->lex)){
                    string op = _strdup((*token)->data);
                    if(!op) exit(1);
                    
                    *token = NEXT_TOKEN(*token);
                    
                    Node* expr = make_expr_node(token);

                    return make_bin_operation(fields_access, expr, op);
                }

                return fields_access;
            }

            free(var_name);

            return make_expr_node(token);
        
        case LEX_GET_ADDR:
        case LEX_POINTER_DEREF:
            string ptr_un_op = _strdup((*token)->data);
            if(!ptr_un_op)   exit(1);
        
            *token = NEXT_TOKEN(*token);
        
            return make_un_operation(
                tokens_parser(token),
                ptr_un_op
            );

/* ------------ операции с переменными ------------ */

        case LEX_RFPAREN:
        case LEX_END: return NULL;
        default: break;
    }

    *token = NEXT_TOKEN(*token);
    return tokens_parser(token);
}

Node*
make_corr_type_litcnst(const string name, const string type, const bool is_ptr, const bool is_unsign){
    if(comp(type, "bool"))      return make_bool_literal_const(name, false, is_ptr, is_unsign);
    if(comp(type, "flt"))       return make_flt_literal_const(name, 0, is_ptr, is_unsign);
    if(comp(type, "short"))     return make_short_literal_const(name, 0, is_ptr, is_unsign);
    if(comp(type, "long"))      return make_long_literal_const(name, 0, is_ptr, is_unsign);
    if(comp(type, "char"))      return make_char_literal_const(name, 0, is_ptr, is_unsign);
    if(comp_n(type, 6, "struct")) return make_custom_literal_const(name, type, is_ptr, is_unsign);
    if (comp(type, _VOID))return make_empty_literal_const(name, is_ptr, is_unsign);
    
    return make_int_literal_const(name, 0, is_ptr, is_unsign);
}