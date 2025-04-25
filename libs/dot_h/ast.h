#ifndef AST_H
#define AST_H

#include "lexeme.h"
#include "str.h"
#include "tokens.h"

#include <stdbool.h>
#include <stdlib.h>

typedef enum _node_type {
    AST_LIT_CNST,
    AST_UNARY_OP,
    AST_BINARY_OP,
    AST_STMT,
    AST_EXPR
} _node_type;

typedef enum _bin_op_type {
    TYPE_PLUS,
    TYPE_MINUS,
    TYPE_MULTI,
    TYPE_DIV,
    TYPE_REM,
    TYPE_ASSIGN
} _bin_op_type;

typedef enum _un_op_type {
    TYPE_INC,
    TYPE_DEC,
    TYPE_DEREF
} _un_op_type;

typedef enum _expr_type {
    TYPE_NUM,
    TYPE_LIT_CONST,
    TYPE_CHAR_VALUE,
    TYPE_EXPR
} _expr_type;


typedef enum _data_type {
    TYPE_INT,
    TYPE_CHAR,
    TYPE_FLT,
    TYPE_BOOL,
    TYPE_SHORT,
    TYPE_LONG
} _data_type;

struct AST_Node;

// значения для типов узла
typedef struct Statements {
    struct AST_Node** nodes;
    unsigned count;
} Statements;

typedef struct LiteralConstant {
    _data_type type;
    string name;
    union {
        int int_value;
        short short_value;
        long long_value;
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

typedef struct Expr {
    _expr_type type;
    union {
        float num;
        int ascii_code;
        BinaryOperator bin_op;
        UnaryOperator un_op;
        LiteralConstant lit_const;
    };
} Expr;

// узел
typedef struct AST_Node {
    _node_type node_type;

    union {
        LiteralConstant constant;
        BinaryOperator bin_op;
        UnaryOperator un_op;
        Statements stmt;
        Expr expr;
    };
} Node;

#define FREE_NODE(node){\
    free((node)->name);\
    free((node));\
}

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
 * @brief создает узел мат. выражения
 * 
 * @return Node* 
 */
Node*
make_expr_node(_token**);

/**
 * @brief создает узел для значения int
 * 
 * @return Node* 
 */
Node*
make_int_literal_const(const string, const int);

/**
 * @brief создает узел для значения float
 * 
 * @return Node* 
 */
Node*
make_flt_literal_const(const string, const float);

/**
 * @brief создает узел для значения bool
 * 
 * @return Node* 
 */
Node*
make_bool_literal_const(const string, const bool);

/**
 * @brief создает узел для значения char
 * 
 * @return Node* 
 */
Node*
make_char_literal_const(const string, const char);

/**
 * @brief создает узел для значения long
 * 
 * @return Node* 
 */
Node*
make_long_literal_const(const string, const long);

/**
 * @brief создает узел для значения short
 * 
 * @return Node* 
 */
Node*
make_short_literal_const(const string, const short);

/**
 * @brief создает узел пустой литеральной константы
 * 
 * @return Node* 
 */
Node*
make_empty_literal_const(const string);

#endif