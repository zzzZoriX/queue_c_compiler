#ifndef AST_H
#define AST_H

#include "lexeme.h"
#include "str.h"

#include <stdbool.h>
#include <stdlib.h>

typedef enum _node_type {
    AST_LIT_CNST,
    AST_UNARY_OP,
    AST_BINARY_OP,
    AST_STMT
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

// значения для типов узла
typedef struct Statements {
    struct AST_Node** nodes;
    unsigned count;
} Statements;

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


// узел
typedef struct AST_Node {
    _node_type node_type;

    union {
        LiteralConstant constant;
        BinaryOperator bin_op;
        UnaryOperator un_op;
        Statements stmt;
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

/**
 * @brief создает узел блока кода
 * 
 * @return Node* 
 */
Node*
make_stmt_node();

/**
 * @brief создает узел для значения int
 * 
 * @return Node* 
 */
Node*
make_int_literal_const(const int);

/**
 * @brief создает узел для значения float
 * 
 * @return Node* 
 */
Node*
make_flt_literal_const(const float);

/**
 * @brief создает узел для значения bool
 * 
 * @return Node* 
 */
Node*
make_bool_literal_const(const bool);

/**
 * @brief создает узел для значения char
 * 
 * @return Node* 
 */
Node*
make_char_literaL_const(const char);

#endif