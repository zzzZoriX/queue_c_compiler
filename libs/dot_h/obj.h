#ifndef OBJ_H
#define OBJ_H

#include <string.h>
#include <ctype.h>


/**
 * @brief проверяет переданную строку на валидность к имени переменной
 * 
 * @return const char 
 */
const char
is_valid_obj_name(const char*);

#endif