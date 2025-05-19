#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include "./dot_c/dot_h/_cmd.h"
#include "./dot_c/dot_h/lexer.h"
#include "./dot_c/dot_h/str.h"
#include "./dot_c/dot_h/ast.h"
#include "./dot_c/dot_h/tokens_parser.h"
#include "./dot_c/dot_h/parse_ast.h"
#include "./dot_c/dot_h/debug_ast.h"

#include <stdio.h>
#include <stdbool.h>

#ifdef __WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#define __ERROR -1
#define __SUCCESS 0
#define __DEFAULT_OTP_FILE_NAME "a"

#endif