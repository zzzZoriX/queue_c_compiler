#include "c:/queue_c_compiler/libs/dot_h/parse_ast.h"

void
print_ast(Node* root){
    printf("AST DUMP:\n");
    traverse_ast(root, 0);
    printf("\n");
}
void
traverse_ast(Node* node, int level){
    if (!node) return;

    print_indent(level);

    switch (node->node_type) {
        case AST_EXPR:
            printf("EXPRESSION\n");
            traverse_ast(node->op1, level + 1);
            traverse_ast(node->op2, level + 1);
            traverse_ast(node->op3, level + 1);
            break;

        case AST_NUM:
            printf("LITERAL CONSTANT: ");
            print_type(node->constant.type);
            printf(" = ");
            print_constant_value(&node->constant);
            printf("\n");
            break;

        case AST_LIT_CNST:
            printf("VARIABLE: %s\n", node->constant.name);
            break;

        case AST_FUNCTION:
            printf("FUNCTION: %s\n", node->constant.name);
            break;

        case AST_IF:
            printf("IF STATEMENT\n");
            print_indent(level + 1);
            printf("CONDITION:\n");
            traverse_ast(node->cmd.if_else.condition, level + 2);
            print_indent(level + 1);
            printf("THEN:\n");
            traverse_ast(node->cmd.if_else.if_body, level + 2);
            if (node->cmd.if_else.else_) {
                print_indent(level + 1);
                printf("ELSE:\n");
                traverse_ast((Node*)node->cmd.if_else.else_, level + 2);
            }
            break;

        case AST_FOR:
            printf("FOR LOOP\n");
            print_indent(level + 1);
            printf("CONDITION:\n");
            traverse_ast(node->cmd.cycles.for_cycle.condition, level + 2);
            print_indent(level + 1);
            printf("ITERATION:\n");
            traverse_ast(node->cmd.cycles.for_cycle.iter, level + 2);
            print_indent(level + 1);
            printf("BODY:\n");
            traverse_ast(node->cmd.cycles.for_cycle.for_body, level + 2);
            break;

        case AST_DO:
            printf("WHILE LOOP\n");
            print_indent(level + 1);
            printf("CONDITION:\n");
            traverse_ast(node->cmd.cycles.while_cycle.condition, level + 2);
            print_indent(level + 1);
            printf("BODY:\n");
            traverse_ast(node->cmd.cycles.while_cycle.while_body, level + 2);
            break;

        case AST_IN:
        case AST_OUT:
            printf("I/O OPERATION: %s\n", node->cmd.io.format);
            for (int i = 0; i < node->cmd.io.args_count; i++) {
                print_indent(level + 1);
                printf("ARG %d: %s\n", i + 1, node->cmd.io.args[i]);
            }
            break;

        case AST_ASSIGN:
            printf("ASSIGN:\n");
            traverse_ast(node->op1, level + 1);
            traverse_ast(node->op2, level + 1);
            break;

        case AST_MULTI_STMT:
            traverse_ast(node->op1, level);
            traverse_ast(node->op2, level);
            break;

        default:
            printf("UNKNOWN NODE TYPE: %d\n", node->node_type);
            traverse_ast(node->op1, level + 1);
            traverse_ast(node->op2, level + 1);
            traverse_ast(node->op3, level + 1);
    }
}


void
print_constant_value(const LiteralConstant* constant){
    switch (constant->type) {
        case TYPE_INT:    printf("%d", constant->int_value); break;
        case TYPE_SHORT:  printf("%hd", constant->short_value); break;
        case TYPE_LONG:   printf("%ld", constant->long_value); break;
        case TYPE_CHAR:  printf("'%c'", constant->char_value); break;
        case TYPE_FLT:    printf("%f", constant->flt_value); break;
        case TYPE_BOOL:   printf("%s", constant->bool_value ? "true" : "false"); break;
        default:          printf("UNKNOWN_VALUE");
    }
}

void
print_type(_data_type type){
    const char* types[] = {
        "TYPE_INT", "TYPE_SHORT", "TYPE_LONG", 
        "TYPE_CHAR", "TYPE_FLT", "TYPE_BOOL"
    };
    printf("%s", types[type]);
}

void
print_indent(int level){
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
}