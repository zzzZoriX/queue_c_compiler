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
        bool is_pointer;
        union {
            int int_value;
            char char_value;
            float flt_value;
            bool bool_value;
            struct AST_Node** p_node_value; // указатель на какой-то объект
        } value;

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


static inline void* __fastcall
get_value_from_ast_node(Node* n){
    if(n->data.is_pointer) return get_value_from_ast_node(*(n->data.value.p_node_value));
    if(comp(n->data.type, (string)"int")) return &n->data.value.int_value;
    if(comp(n->data.type, (string)"char")) return &n->data.value.char_value;
    if(comp(n->data.type, (string)"flt")) return &n->data.value.flt_value;
    if(comp(n->data.type, (string)"bool")) return &n->data.value.bool_value;

    return NULL;
}


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
  * @brief создает узел указателя объекта
  * 
  * @return Node* 
  */
 Node*
 create_p_obj_node(const string, Node**);
#endif