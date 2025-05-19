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
    "=", "+=", "-=", "/=", "*=", "%="
};

void
code_gen(Node*, FILE*);

void
parse_nodes(Node*, FILE*);

#endif