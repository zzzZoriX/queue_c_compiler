#ifndef STR_H
#define STR_H

#include <string.h>
#include <stdlib.h>

typedef char* string;

#define NULL_STR ""

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

/**
 * @brief проверяет символ на то, является ли он спец. символом (.;,:_ и т.д.)
 * 
 * @return const char 
 */
const char
isspec(const char);

/**
 * @brief сравнивает две строки и возвращает true/false в зависимости от того, равны ли они
 * 
 * @return const char 
 */
const char
comp(const string, const string);

#endif