#include "c:/queue_c_compiler/libs/dot_h/ast.h"
#include <string.h>

Node*
create_int_obj_node(const string name, const int value){
    Node* new_int_node = (Node*)malloc(sizeof(Node));
    if(!new_int_node)
        exit(1);

    new_int_node->data.obj_name = _strdup(name);
    new_int_node->data.type = _strdup("int");
    new_int_node->data.value.int_value = value;

    new_int_node->node_type = AST_OBJ;

    return new_int_node;
}

Node*
create_char_obj_node(const string name, const char value){
    Node* new_char_node = (Node*)malloc(sizeof(Node));
    if(!new_char_node)
        exit(1);

    new_char_node->data.obj_name = _strdup(name);
    new_char_node->data.type = _strdup("char");
    new_char_node->data.value.char_value = value;

    new_char_node->node_type = AST_OBJ;

    return new_char_node;
}

Node*
create_flt_obj_node(const string name, const float value){
    Node* new_flt_node = (Node*)malloc(sizeof(Node));
    if(!new_flt_node)
        exit(1);

    new_flt_node->data.obj_name = _strdup(name);
    new_flt_node->data.type = _strdup("flt");
    new_flt_node->data.value.flt_value = value;

    new_flt_node->node_type = AST_OBJ;

    return new_flt_node;
}

Node*
create_bool_obj_node(const string name, const bool value){
    Node* new_bool_node = (Node*)malloc(sizeof(Node));
    if(!new_bool_node)
        exit(1);

    new_bool_node->data.obj_name = _strdup(name);
    new_bool_node->data.type = _strdup("bool");
    new_bool_node->data.value.bool_value = value;

    new_bool_node->node_type = AST_OBJ;

    return new_bool_node;
}

Node*
create_obj_node(const string name, const Node* value){
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)
        exit(1);

    new_node->data.obj_name = _strdup(name);
    new_node->data.type = _strdup(value->data.type);
    new_node->data.value = value->data.value;

    new_node->node_type = AST_OBJ;

    return new_node;
}

Node*
create_p_obj_node(const string name, Node** value){
    Node* new_p_node = (Node*)malloc(sizeof(Node));
    if(!new_p_node)
        exit(1);

    new_p_node->data.obj_name = _strdup(name);
    new_p_node->data.type = _strdup((*value)->data.type);
    new_p_node->data.is_pointer = true;
    new_p_node->data.value.p_node_value = value;

    new_p_node->node_type = AST_OBJ;

    return new_p_node;
}