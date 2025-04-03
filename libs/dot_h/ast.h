#ifndef AST_H
#define AST_H

#include "lexeme.h"
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
        string obj_name, type;
        union {
            int int_value;
            char char_value;
            float flt_value;
            bool bool_value;
            struct AST_Node* node_value;
        } value; // обычный объект

        union {
            int* p_int_value;
            char* p_char_value;
            float* p_float_value;
            bool* p_bool_value;
            struct AST_Node** p_node_value;
        } p_value; // указатель

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


/**
 * @brief создает узел интового объекта
 * 
 * @return Node* 
 */
Node*
create_int_obj_node(const string, const int);

/**
 * @brief создает узел символьного объекта
 * 
 * @return Node* 
 */
Node*
create_char_obj_node(const string, const char);

/**
 * @brief создает узел флоат объекта
 * 
 * @return Node* 
 */
Node*
create_flt_obj_node(const string, const float);

/**
 * @brief создает узел булевого объекта
 * 
 * @return Node* 
 */
Node*
create_bool_obj_node(const string, const bool);

/**
 * @brief создает узел объекта
 * 
 * @return Node* 
 */
Node*
create_obj_node(const string, const Node*);

/**
 * @brief создает узел указателя интового объекта
 * 
 * @return Node* 
 */
 Node*
 create_p_int_obj_node(const string, const int*);
 
 /**
  * @brief создает узел указателя символьного объекта
  * 
  * @return Node* 
  */
 Node*
 create_p_char_obj_node(const string, const char*);
 
 /**
  * @brief создает узел указателя флоат объекта
  * 
  * @return Node* 
  */
 Node*
 create_p_flt_obj_node(const string, const float*);
 
 /**
  * @brief создает узел указателя булевого объекта
  * 
  * @return Node* 
  */
 Node*
 create_p_bool_obj_node(const string, const bool*);
 
 /**
  * @brief создает узел указателя объекта
  * 
  * @return Node* 
  */
 Node*
 create_p_obj_node(const string, const Node**);
#endif