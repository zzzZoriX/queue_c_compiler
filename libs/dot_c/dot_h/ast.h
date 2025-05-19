#ifndef AST_H
#define AST_H

#include "lexeme.h"
#include "str.h"
#include "tokens.h"

#include <stdbool.h>
#include <stdlib.h>

typedef enum _node_type {
    AST_LIT_CNST,
    AST_PLUS,
    AST_MINUS,
    AST_MULTI,
    AST_DIV,
    AST_REM,
    AST_ASSIGN,
    AST_ADD_ASSIGN,
    AST_REDUCE_ASSIGN,
    AST_MUL_ASSIGN,
    AST_DIV_ASSIGN,
    AST_REM_ASSIGN,
    AST_INC,
    AST_DEC,
    AST_DEREF,
    AST_GET_ADDR,
    AST_NUM,
    AST_LIT_CONST,
    AST_CHAR_VALUE,
    AST_BOOLIAN_VALUE,
    AST_NULL_VALUE,
    AST_EXPR,
    AST_EQ,
    AST_NEQ,
    AST_LE,
    AST_L,
    AST_G,
    AST_GE,
    AST_AND,
    AST_OR,
    AST_IF,
    AST_ELSE_IF,
    AST_ELSE,
    AST_WHILE,
    AST_FOR,
    AST_OUT,
    AST_IN,
    AST_SINGLE_STMT,
    AST_MULTI_STMT,
    AST_CALL,
    AST_RET,
    AST_FUNCTION,
    AST_FUNCTION_DECL,
    AST_LPAREN
} _node_type;


typedef enum _data_type {
    TYPE_INT,
    TYPE_VOID,
    TYPE_CHAR,
    TYPE_FLT,
    TYPE_BOOL,
    TYPE_SHORT,
    TYPE_LONG
} _data_type;

typedef struct AST_Node AST_Node;

// значения для типов узла
typedef struct Statements {
    struct AST_Node** nodes;
    unsigned count;
} Statements;

typedef struct LiteralConstant {
    _data_type type;
    string name;
    bool is_ptr, is_unsign;
    union {
        int int_value;
        short short_value;
        long long_value;
        char char_value;
        float flt_value;
        bool bool_value;
    };
} LiteralConstant;

typedef struct Command {
    struct {
        AST_Node* condition,* if_body;
        struct Command* else_;
    } if_else;

    struct {
        struct {
            AST_Node* condition,* iter,* for_body;
        } for_cycle;
        struct {
            AST_Node* condition,* while_body;
        } while_cycle;
    } cycles;

    struct {
        string format;
        struct AST_Node** args;
        int args_count;
    } io;
} Command;

typedef struct Function {
    LiteralConstant function_header;
    AST_Node** args;
    int count;
} Function;

// узел
typedef struct AST_Node {
    _node_type node_type;

    union {
        LiteralConstant constant;
        Command cmd;
        Function function;
    };
    AST_Node* op1,* op2,* op3;
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
make_bin_operation(Node*, Node*, string);

/**
 * @brief создает узел унарной операции
 * 
 * @return Node* 
 */
Node*
make_un_operation(Node*, string);

/**
 * @brief создает узел мат. выражения
 * 
 * @return Node* 
 */
Node*
make_expr_node(_token**);

/**
 * @brief создает узел условного выражения
 * 
 * @return Node* 
 */
Node*
make_cond_node(_token**);

/**
 * @brief создает узел стейтмента
 * 
 * @return Node* 
 */
Node*
make_stmt_node(_token**);

/**
 * @brief создает узел условной конструкции
 * 
 * @return Node* 
 */
Node*
make_if_else_node(_lexemes, Node*, Node*, Node*);

/**
 * @brief создает узел цикла while или do-while
 * 
 * @return Node* 
 */
Node*
make_do_while_node(_lexemes, Node*, Node*);

/**
 * @brief создает узел цикла for
 * 
 * @return Node* 
 */
Node*
make_for_cycle_node(Node*, Node*, Node*);

/**
 * @brief создает узел комманд ввода и вывода
 * 
 * @return Node* 
 */
Node*
make_io_node(_lexemes, string, Node**, int);

/**
 * @brief создает узел функции
 * 
 * @param base  литеральная константа, определяющая тип функции и ее имя
 * @return Node* 
 */
Node*
make_function_node(Node* base, Node**, int, Node*);

/**
 * @brief создает узел для значения int
 * 
 * @return Node* 
 */
Node*
make_int_literal_const(const string, const int, const bool, const bool);

/**
 * @brief создает узел для значения float
 * 
 * @return Node* 
 */
Node*
make_flt_literal_const(const string, const float, const bool, const bool);

/**
 * @brief создает узел для значения bool
 * 
 * @return Node* 
 */
Node*
make_bool_literal_const(const string, const bool, const bool, const bool);

/**
 * @brief создает узел для значения char
 * 
 * @return Node* 
 */
Node*
make_char_literal_const(const string, const char, const bool, const bool);

/**
 * @brief создает узел для значения long
 * 
 * @return Node* 
 */
Node*
make_long_literal_const(const string, const long, const bool, const bool);

/**
 * @brief создает узел для значения short
 * 
 * @return Node* 
 */
Node*
make_short_literal_const(const string, const short, const bool, const bool);

/**
 * @brief создает узел пустой литеральной константы
 * 
 * @return Node* 
 */
Node*
make_empty_literal_const(const string, const bool, const bool);

#endif