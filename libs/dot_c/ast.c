#include "c:/queue_c_compiler/libs/dot_h/ast.h"

#include <math.h>

Node*
tokens_parser(_token**);

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
is_cond(_lexemes lex){
    return
        lex == LEX_EQ       ||
        lex == LEX_NEQ      ||
        lex == LEX_G        ||
        lex == LEX_GE       ||
        lex == LEX_LE       ||
        lex == LEX_L        ||
        lex == LEX_OR       ||
        lex == LEX_AND   
    ;
}

static inline _node_type __fastcall 
define_cond_type_by_lex(_lexemes lex){
    switch(lex){
        case LEX_EQ:    return AST_EQ;
        case LEX_NEQ:   return AST_NEQ;
        case LEX_G:     return AST_G;
        case LEX_GE:    return AST_GE;
        case LEX_LE:    return AST_LE;
        case LEX_L:     return AST_L;
        case LEX_AND:   return AST_AND;
        case LEX_OR:    return AST_OR;
        default:        return AST_EQ;
    }
}

static inline _node_type __fastcall
define_bin_op_type(string op){
    if(comp("+", op))   return AST_PLUS;
    if(comp("*", op))   return AST_MULTI;
    if(comp("-", op))   return AST_MINUS;
    if(comp("%", op))   return AST_REM;
    if(comp("/", op))   return AST_DIV;
    if(comp("<", op))   return AST_L;
    if(comp(">", op))   return AST_G;
    if(comp("&&", op))  return AST_AND;
    if(comp("||", op))  return AST_OR;
    if(comp("==", op))  return AST_EQ;
    if(comp("!=", op))  return AST_NEQ;
    if(comp("=>", op))  return AST_GE;
    if(comp("<=", op))  return AST_LE;
    if(comp("+=", op))  return AST_ADD_ASSIGN;
    if(comp("-=", op))  return AST_REDUCE_ASSIGN;
    if(comp("*=", op))  return AST_MUL_ASSIGN;
    if(comp("/=", op))  return AST_DIV_ASSIGN;
    if(comp("%=", op))  return AST_REM_ASSIGN;
    if (comp(op, c_concat_c('=', '\0'))) return AST_ASSIGN;

    return 0;
}
static inline _node_type __fastcall
define_un_op_type(string op){
    if(comp(op, c_concat_c('@', '\0'))) return AST_DEREF;
    if(comp(op, c_concat_c('&', '\0'))) return AST_GET_ADDR;
    if(comp(op, "++")) return AST_INC;
    if(comp(op, "--")) return AST_DEC;
    if(comp(op, "call"))    return AST_CALL;
    if (comp(op, "ret"))    return AST_RET;

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
make_bin_operation(Node* left, Node* right, string op){
    Node* new_node = make_node(0);

    new_node->op1 = left;
    new_node->op2 = right;
    new_node->node_type = define_bin_op_type(op);

    return new_node;
}

Node*
make_un_operation(Node* operand, string op){
    Node* new_node = make_node(0);
        
    new_node->op1 = operand;
    new_node->node_type = define_un_op_type(op);

    return new_node;
}

Node*
make_expr_node(_token** token){
    Node* expr_node = make_node(AST_EXPR);

    if((*token)->lex == LEX_DIGIT || (*token)->lex == LEX_FLOAT){
        expr_node->node_type = AST_NUM;
        
        if((*token)->lex == LEX_FLOAT){
            expr_node->constant.type = TYPE_FLT;
            expr_node->constant.flt_value = atof((*token)->data);    
        }
        else{
            expr_node->constant.type = TYPE_INT;
            expr_node->constant.int_value = atoi((*token)->data);    
        }

        *token = NEXT_TOKEN(*token);
    }

    if((*token)->lex == LEX_CHAR_VAL){
        expr_node->constant.type = TYPE_CHAR;
        expr_node->constant.char_value = (*token)->data[1];

        *token = NEXT_TOKEN(*token);
    }

    if((*token)->lex == LEX_TRUE || (*token)->lex == LEX_FALSE){
        expr_node->node_type = AST_BOOLIAN_VALUE;
        expr_node->constant.type = TYPE_BOOL;
        expr_node->constant.bool_value = ((*token)->lex == LEX_TRUE ? true : false);

        *token = NEXT_TOKEN(*token);
    }

    if ((*token)->lex == LEX_NULL_VALUE) {
        expr_node->node_type = AST_NULL_VALUE;
        expr_node->constant = (LiteralConstant){0};
        expr_node->constant.type = TYPE_VOID;

        *token = NEXT_TOKEN(*token);
    }

    if((*token)->lex == LEX_PREF_INC || (*token)->lex == LEX_PREF_DEC){
        free(expr_node);
        string op = _strdup((*token)->data);
        if(!op) exit(1);

        *token = NEXT_TOKEN(*token);

        Node* lit = make_empty_literal_const((*token)->data, false);
        *token = NEXT_TOKEN(*token);

        expr_node = make_un_operation(
            lit,
            op
        );
    }

    if((*token)->lex == LEX_OBJ_NAME){

// если унарная операция
        if(NEXT_TOKEN(*token)->lex == LEX_POST_INC || NEXT_TOKEN(*token)->lex == LEX_POST_DEC){
            free(expr_node);
            
            Node* empty_lit_const = make_empty_literal_const((*token)->data, false);
            *token = NEXT_TOKEN(*token);

            string op = _strdup((*token)->data);
            if(!op) exit(1);

            *token = NEXT_TOKEN(*token);

            expr_node = make_un_operation(
                empty_lit_const,
                op
            );
        }

        if(NEXT_TOKEN(*token)->lex == LEX_INST_POINTER){
            free(expr_node);
            *token = NEXT_TOKEN(NEXT_TOKEN(*token));
            expr_node = make_expr_node(token);
        }

// если не унарная операция
        expr_node->node_type = AST_LIT_CNST;
        expr_node->constant.name = _strdup((*token)->data);

        *token = NEXT_TOKEN(*token);
    }

    else if((*token)->lex == LEX_LPAREN){
        *token = NEXT_TOKEN(*token);
        Node* expr = make_expr_node(token);

        *token = NEXT_TOKEN(*token);
        return expr;
    }

    else if ((*token)->lex == LEX_CALL)
        expr_node = tokens_parser(token);

    if(is_operator((*token)->lex)){
        string op = _strdup((*token)->data);
        if(!op) exit(1);
        
        *token = NEXT_TOKEN(*token);

        Node* right = make_expr_node(token);
        
        return make_bin_operation(expr_node, right, op);
    }

    return expr_node;
}

Node*
make_cond_node(_token** token){
    Node* cond = make_node(0);
    
    if ((*token)->lex == LEX_LPAREN)
        *token = NEXT_TOKEN(*token);

    Node* left = make_expr_node(token);

    if((*token)->lex == LEX_INST_POINTER)
        return left;

    if(is_cond((*token)->lex)){
        cond->node_type = define_cond_type_by_lex((*token)->lex);
        *token = NEXT_TOKEN(*token);

        cond->op1 = left;
        cond->op2 = make_cond_node(token);
    }
    else
         return left
    ;

    return cond;
}

Node*
make_stmt_node(_token** token){
    Node* statements = make_node(AST_MULTI_STMT);
    if ((*token)->lex == LEX_LFPAREN)
        *token = NEXT_TOKEN(*token);

    statements->op1 = NULL;
    statements->op2 = NULL;

    while((*token)->lex != LEX_RFPAREN && (*token)->lex != LEX_END){
        Node* command = tokens_parser(token);
        statements->op1 = command;

        if (!*token || (*token)->lex == LEX_RFPAREN)
            break;

        if (*token && (*token)->lex != LEX_END) {
            Node* next = make_stmt_node(token);
            statements->op2 = next;

            break;
        }
    }

    if (*token && (*token)->lex != LEX_END && (*token)->lex == LEX_RFPAREN)
        *token = NEXT_TOKEN(NEXT_TOKEN(*token)); // скипаем };

    if (!statements->op1) {
        free(statements);
        return NULL;
    }

    return statements;
}

Node*
make_if_else_node(_lexemes lexeme, Node* condition, Node* body, Node* else_){
    Node* if_else_node = make_node(
        (
            lexeme == LEX_IF ? 
            AST_IF : (
                lexeme == LEX_ELIF ?
                AST_ELSE_IF : AST_ELSE
            )
        )
    );

    if_else_node->cmd.if_else.condition = condition;
    if_else_node->cmd.if_else.if_body = body;
    if (else_) {
        Command* else_cmd = (Command*)malloc(sizeof(Command));
        if (!else_cmd) exit(1);

        *else_cmd = else_->cmd;

        if_else_node->cmd.if_else.else_ = else_cmd;
    }
    else
        if_else_node->cmd.if_else.else_ = NULL;

    return if_else_node;
}

Node*
make_do_while_node(_lexemes lexeme, Node* condition, Node* body){
    Node* do_while_node = make_node(AST_WHILE);

    do_while_node->cmd.cycles.while_cycle.condition = condition;
    do_while_node->cmd.cycles.while_cycle.while_body = body;

    return do_while_node;
}

Node*
make_for_cycle_node(Node* condition, Node* body, Node* iter){
    Node* for_node = make_node(AST_FOR);

    for_node->cmd.cycles.for_cycle.condition = condition;
    for_node->cmd.cycles.for_cycle.for_body = body;
    for_node->cmd.cycles.for_cycle.iter = iter;

    return for_node;
}

Node*
make_io_node(_lexemes lexeme, string format, Node** args, int count){
    Node* io_node = make_node(
        (lexeme == LEX_IN ? AST_IN : AST_OUT)
    );

    io_node->cmd.io.format = _strdup(format);
    if(!io_node->cmd.io.format)
        exit(1);

    io_node->cmd.io.args = args;
    io_node->cmd.io.args_count = count;

    return io_node;
}

Node*
make_function_node(Node* base, Node** args, int count, Node* body){
    Node* funcion_node = make_node(
        (
            body ? AST_FUNCTION : AST_FUNCTION_DECL
        )
    );

    funcion_node->function.function_header = base->constant;
    funcion_node->function.args = args;
    funcion_node->function.count = count;
    funcion_node->op1 = body;

    return funcion_node;
}

Node*
make_char_literal_const(const string name, const char value, const bool is_ptr){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.char_value = value;
    new_node->constant.name = _strdup(name);
    new_node->constant.type = TYPE_CHAR;
    if(!new_node->constant.name)
        exit(1);
    new_node->constant.is_ptr = is_ptr;

    return new_node;
}

Node*
make_bool_literal_const(const string name, const bool value, const bool is_ptr){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.bool_value = value;
    new_node->constant.name = _strdup(name);
    new_node->constant.type = TYPE_BOOL;
    if(!new_node->constant.name)
        exit(1);
    new_node->constant.is_ptr = is_ptr;

    return new_node;
}

Node*
make_flt_literal_const(const string name, const float value, const bool is_ptr){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.flt_value = value;
    new_node->constant.name = _strdup(name);
    new_node->constant.type = TYPE_FLT;
    if(!new_node->constant.name)
        exit(1);

    return new_node;
}

Node*
make_int_literal_const(const string name, const int value, const bool is_ptr){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.int_value = value;
    new_node->constant.name = _strdup(name);
    new_node->constant.type = TYPE_INT;
    if(!new_node->constant.name)
        exit(1);
    new_node->constant.is_ptr = is_ptr;

    return new_node;
}

Node*
make_long_literal_const(const string name, const long value, const bool is_ptr){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.long_value = value;
    new_node->constant.name = _strdup(name);
    new_node->constant.type = TYPE_LONG;
    if(!new_node->constant.name)
        exit(1);
    new_node->constant.is_ptr = is_ptr;

    return new_node;
}

Node*
make_short_literal_const(const string name, const short value, const bool is_ptr){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.short_value = value;
    new_node->constant.name = _strdup(name);
    new_node->constant.type = TYPE_SHORT;
    if(!new_node->constant.name)
        exit(1);
    new_node->constant.is_ptr = is_ptr;

    return new_node;
}

Node*
make_empty_literal_const(const string name, const bool is_ptr){
    Node* new_node = make_node(AST_LIT_CNST);

    new_node->constant.name = _strdup(name);
    new_node->constant.type = TYPE_VOID;
    if(!new_node->constant.name)
        exit(1);
    new_node->constant.is_ptr = is_ptr;

    return new_node;
}