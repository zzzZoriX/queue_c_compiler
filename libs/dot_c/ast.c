#include "c:/queue_c_compiler/libs/dot_h/ast.h"
#include <string.h>

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