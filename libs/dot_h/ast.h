#ifndef AST_H
#define AST_H

#include "str.h"

typedef enum _node_type {
    AST_OBJ,
    AST_OBJ_ANNONS,
    AST_EXPR,
    AST_COND,
    AST_UNARY_OP,
    AST_BINARY_OP,
    AST_STMT,
    AST_ASSIGN
} _node_type;

typedef enum _op_type {
    TYPE_PLUS,
    TYPE_MINUS,
    TYPE_MULTI,
    TYPE_DIV,
    TYPE_REM,
    TYPE_INC,
    TYPE_DEC,
    TYPE_DEREF
} _op_type;

typedef struct AST_Node {
    _node_type node_type;

    union {
        string obj_name;

        double num_value;
        struct AST_Node* node_val;

        struct {
            _op_type type;
            struct AST_Node* oper;
        } un_op;
        
        struct {
            _op_type type;
            struct AST_Node* left,* right;
        } bin_op;

    } data;
} Node;

#endif