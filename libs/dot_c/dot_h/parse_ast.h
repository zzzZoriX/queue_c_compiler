#ifndef PARSE_AST_H
#define PARSE_AST_H

#include "ast.h"
#include "str.h"

#include <stdio.h>
#include <ctype.h>

static string str_types[] = {
    "int", "void", "char", "float",
    "bool", "short", "long"
};

static string str_assigns[] = {
    "=", "+=", "-=", "*=", "/=", "%="
};

static inline string __fastcall
DEFINE_ASSIGN(const _node_type type) {
    switch (type) {
        case AST_ASSIGN:
            return str_assigns[0];
        case AST_ADD_ASSIGN:
            return str_assigns[1];
        case AST_REDUCE_ASSIGN:
            return str_assigns[2];
        case AST_MUL_ASSIGN:
            return str_assigns[3];
        case AST_DIV_ASSIGN:
            return str_assigns[4];
        case AST_REM_ASSIGN:
            return str_assigns[5];
    }
}

void
code_gen(Node*, FILE*);

void
parse_nodes(Node*, FILE*);

#endif