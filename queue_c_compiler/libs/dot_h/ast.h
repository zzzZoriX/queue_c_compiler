#ifndef AST_H
#define AST_H

#include "lexeme.h"
#include "str.h"

#include <stdbool.h>
#include <stdlib.h>

typedef enum _node_type {
    AST_OBJ,
    AST_OBJ_ANNONS,
    AST_EXPR,
    AST_COND,
    AST_UNARY_OP,
    AST_BINARY_OP,
    AST_STMT,
    AST_ASSIGN,

    AST_NULL
} _node_type;

typedef enum _bin_op_type {
    TYPE_PLUS,
    TYPE_MINUS,
    TYPE_MULTI,
    TYPE_DIV,
    TYPE_REM,
} _bin_op_type;

typedef enum _un_op_type {
    TYPE_INC,
    TYPE_DEC,
    TYPE_DEREF
} _un_op_type;

typedef enum _data_type {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLT,
    TYPE_BOOL
} _data_type;

struct AST_Node;

// 10, "Hello"

typedef struct LiteralConstant {
    _data_type type;
    union {
        int int_value;
        char char_value;
        float flt_value;
        bool bool_value;
    };
} LiteralConstant;

typedef struct BinaryOperator {
    struct AST_Node* left,* right;
    _bin_op_type operation_type;
} BinaryOperator;

typedef struct UnaryOperator {
    struct AST_Node* operand;
    _un_op_type operation_type;
} UnaryOperator;

typedef struct AST_Node {
    _node_type node_type;

    union {
        LiteralConstant constant;
        BinaryOperator bin_op;
        UnaryOperator un_op;
    };
} Node;

/**
 * @brief создает узел бинарной операции
 * 
 * @return Node*
 */
Node*
make_bin_operation(Node*, Node*, char);

/**
 * @brief создает узел унарной операции
 * 
 * @return Node* 
 */
Node*
make_un_operation(Node*, string);

#endif