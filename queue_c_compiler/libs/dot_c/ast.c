#include "c:/queue_c_compiler/libs/dot_h/ast.h"
#include "C:\Users\Student\Desktop\штота\queue_c_compiler\libs\dot_h\ast.h"

static inline _bin_op_type __fastcall
define_bin_op_type(char op){
    switch(op){
        case '+': return TYPE_PLUS;
        case '-': return TYPE_MINUS;
        case '*': return TYPE_MULTI;
        case '/': return TYPE_DIV;
        case '%': return TYPE_REM;
    }
}
static inline _un_op_type __fastcall
define_un_op_type(string op){
    if(comp(op, c_concat_c('@', '\0'))) return TYPE_DEREF;
    if(comp(op, "++")) return TYPE_INC;
    if(comp(op, "--")) return TYPE_DEC;
}

Node*
make_bin_operation(Node* left, Node* right, char op){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)
        exit(1);

    new_node->node_type = AST_BINARY_OP;
    new_node->bin_op.left = left;
    new_node->bin_op.right = right;
    new_node->bin_op.operation_type = define_bin_op_type(op);

    return new_node;
}

Node*
make_un_operation(Node* operand, string op){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)
        exit(1);
        
    new_node->node_type = AST_UNARY_OP;
    new_node->un_op.operand = operand;
    new_node->un_op.operation_type = define_un_op_type(op);

    return new_node;
}