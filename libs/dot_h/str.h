#ifndef STR_H
#define STR_H

#include <string.h>
#include <stdlib.h>

typedef char* string;

/**
 * @brief функция конкатинации строк
 * 
 * @return string 
 */
string
concat(const string, const string);

/**
 * @brief функция конкатинации символа и строки
 * 
 * @return string 
 */
string
c_concat(const char, const string);

/**
 * @brief функция конкатинации строки и символа
 * 
 * @return string 
 */
string
concat_c(const string, const char);

/**
 * @brief функция конкатинации символов
 * 
 * @return string 
 */
string
c_concat_c(const char, const char);

#endif