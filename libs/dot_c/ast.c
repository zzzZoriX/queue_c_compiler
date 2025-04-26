#include "c:/queue_c_compiler/libs/dot_h/ast.h"
#include <stdlib.h>
#include <string.h>

static inline bool __fastcall
is_operator(_lexemes lex){
    return
        lex == LEX_PLUS     ||
        lex == LEX_MINUS    ||
        lex == LEX_MUL      ||
        lex == LEX_DIV      ||
        lex == LEX_REM
    ;
}

static inline bool __fastcall
is_comp(_lexemes lex){
    return
        lex == LEX_EQ       ||
        lex == LEX_NEQ      ||
        lex == LEX_G        ||
        lex == LEX_GE       ||
        lex == LEX_LE       ||
        lex == LEX_L        
    ;
}

static inline bool __fastcall
is_logical(_lexemes lex){
    return
        lex == LEX_AND || lex == LEX_OR
    ;
}

static inline _cond_type __fastcall 
define_cond_type_by_lex(_lexemes lex){
    switch(lex){
        case LEX_EQ:    return TYPE_EQ;
        case LEX_NEQ:   return TYPE_NEQ;
        case LEX_G:     return TYPE_G;
        case LEX_GE:    return TYPE_GE;
        case LEX_LE:    return TYPE_LE;
        case LEX_L:     return TYPE_L;
        case LEX_AND:   return TYPE_AND;
        case LEX_OR:    return TYPE_OR;
        default:        return TYPE_COND_EXPR;
    }
}

static inline _bin_op_type __fastcall
define_bin_op_type(char op){
    switch(op){
        case '+': return TYPE_PLUS;
        case '-': return TYPE_MINUS;
        case '*': return TYPE_MULTI;
        case '/': return TYPE_DIV;
        case '%': return TYPE_REM;
    }
    return 0;
}
static inline _un_op_type __fastcall
define_un_op_type(string op){
    if(comp(op, c_concat_c('@', '\0'))) return TYPE_DEREF;
    if(comp(op, "++")) return TYPE_INC;
    if(comp(op, "--")) return TYPE_DEC;

    return 0;
}

static inline Node* __fastcall
make_node(_node_type type){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)
        exit(1);

    new_node->node_type = type;

    return new_node;
}

Node*
make_bin_operation(Node* left, Node* right, char op){
    Node* new_node = make_node(AST_BINARY_OP);

    new_node->bin_op.left = left;
    new_node->bin_op.right = right;
    new_node->bin_op.operation_type = define_bin_op_type(op);

    return new_node;
}

Node*
make_un_operation(Node* operand, string op){
    Node* new_node = make_node(AST_UNARY_OP);
        
    new_node->un_op.operand = operand;
    new_node->un_op.operation_type = define_un_op_type(op);

    return new_node;
}

Node*
make_stmt_node(){
    Node* stmt_node = make_node(AST_STMT);

    stmt_node->stmt.count = 0;
    stmt_node->stmt.nodes = (Node**)malloc(sizeof(Node*));

    return stmt_node;
}

Node*
make_expr_node(_token** token){
    Node* expr_node = make_node(AST_EXPR);

    if((*token)->lex == LEX_DIGIT || (*token)->lex == LEX_FLOAT){
        expr_node->expr.type = TYPE_NUM;
        expr_node->expr.num = atof((*token)->data);

        return expr_node;
    }

    if((*token)->lex == LEX_CHAR_VAL){
        // токен содержит 'символ', чтобы получить код символа - мне нужно обратиться ко второй ячейке строки
        expr_node->expr.ascii_code = (*token)->data[1];

        return expr_node;
    }

    if((*token)->lex == LEX_PREF_INC || (*token)->lex == LEX_PREF_DEC){
        free(expr_node);

        return make_un_operation(
            make_empty_literal_const(NEXT_TOKEN(*token)->data),
            (*token)->data
        );
    }

    if((*token)->lex == LEX_OBJ_NAME){

// если унарная операция
        if(NEXT_TOKEN(*token)->lex == LEX_POST_INC || NEXT_TOKEN(*token)->lex == LEX_POST_DEC){
            free(expr_node);
            
            Node* empty_lit_const = make_empty_literal_const((*token)->data);
            *token = NEXT_TOKEN(*token);

            return make_un_operation(
                empty_lit_const,
                (*token)->data
            );
        }

// если не унарная операция
        expr_node->expr.type = TYPE_LIT_CONST;
        expr_node->expr.lit_const.name = _strdup((*token)->data);

        return expr_node;
    }

    free(expr_node); // дальше эта переменная нигде не используется

    if((*token)->lex == LEX_LPAREN){
        *token = (*token)->next_token;
        Node* expr = make_expr_node(token);

        *token = (*token)->next_token;
        return expr;
    }

    Node* left = make_expr_node(token);

    if(is_operator((*token)->lex)){
        char op = (*token)->data[0];
        *token = (*token)->next_token;

        Node* right = make_expr_node(token);
        
        return make_bin_operation(left, right, op);
    }

    return left;
}

Node*
make_cond_node(_token** token){
    Node* cond = make_node(AST_CONDITION);
    
    *token = NEXT_TOKEN(*token);
    Node* left = make_expr_node(token);
    
    if(is_comp((*token)->lex)){
        cond->cond.type = define_cond_type_by_lex((*token)->lex);
        *token = NEXT_TOKEN(*token);

        cond->cond.comparsion.left = left->expr;
        cond->cond.comparsion.right = make_expr_node(token)->expr;
    }
    else if(is_logical((*token)->lex)){
        cond->cond.type = define_cond_type_by_lex((*token)->lex);
        *token = NEXT_TOKEN(*token);

        cond->cond.bin.left = &left->cond;
        cond->cond.bin.right = &make_expr_node(token)->cond;
    }
    else{
        cond->cond.type = TYPE_COND_EXPR;
        cond->cond.expr = make_expr_node(token)->expr;
    }

    return cond;
}

Node*
make_if_else_node(_cmd_type type, Condition cond, Statements body, Command else_){
    Node* if_else_node = make_node(AST_COMMAND);

    if_else_node->cmd.type = type;
    if_else_node->cmd.if_else.condition = cond;
    if_else_node->cmd.if_else.if_body = body;
    if_else_node->cmd.if_else.else_ = &else_;

    return if_else_node;
}

Node*
make_do_while_node(_cmd_type type, Condition cond, Statements body){
    Node* do_while_node = make_node(AST_COMMAND);

    do_while_node->cmd.type = type;
    do_while_node->cmd.cycles.while_cycle.condition = cond;
    do_while_node->cmd.cycles.while_cycle.while_body = body;

    return do_while_node;
}

Node*
make_for_cycle_node(_cmd_type type, Condition cond, Statements body, UnaryOperator iter){
    Node* for_node = make_node(AST_COMMAND);

    for_node->cmd.type = type;
    for_node->cmd.cycles.for_cycle.condition = cond;
    for_node->cmd.cycles.for_cycle.for_body = body;
    for_node->cmd.cycles.for_cycle.iter = iter;

    return for_node;
}

Node*
make_io_node(_cmd_type type, string format, string* args, int count){
    Node* io_node = make_node(AST_COMMAND);

    io_node->cmd.type = type;
    io_node->cmd.io.format = _strdup(format);
    if(!io_node->cmd.io.format)
        exit(1);

    io_node->cmd.io.args = args;
    io_node->cmd.io.args_count = count;

    return io_node;
}

Node*
make_char_literal_const(const string name, const char value){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.char_value = value;
    new_node->constant.name = _strdup(name);
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}

Node*
make_bool_literal_const(const string name, const bool value){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.bool_value = value;
    new_node->constant.name = _strdup(name);
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}

Node*
make_flt_literal_const(const string name, const float value){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.flt_value = value;
    new_node->constant.name = _strdup(name);
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}

Node*
make_int_literal_const(const string name, const int value){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.int_value = value;
    new_node->constant.name = _strdup(name);
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}

Node*
make_long_literal_const(const string name, const long value){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.long_value = value;
    new_node->constant.name = _strdup(name);
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}

Node*
make_short_literal_const(const string name, const short value){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.short_value = value;
    new_node->constant.name = _strdup(name);
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}

Node*
make_empty_literal_const(const string name){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.name = concat("__empty_", name);
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}