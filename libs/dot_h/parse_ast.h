#ifndef PARSE_AST_H
#define PARSE_AST_H

#include "ast.h"
#include "tokens_parser.h"

#include <stdio.h>
#include <string.h>

void 
print_indent(int level);

void 
print_type(_data_type);

void 
print_constant_value(const LiteralConstant*);

void 
traverse_ast(Node*, int);

void 
print_ast(Node*);

#endif