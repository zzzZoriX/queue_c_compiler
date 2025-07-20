#ifndef STR_H
#define STR_H

#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

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
 * @brief удаляет лишние пробелы в начале и конце переданной строки
 * 
 * @return string 
 */
string
dex_spaces(const string);

/**
 * @brief сравнивает две строки и возвращает true/false в зависимости от того, равны ли они
 * 
 * @return const char 
 */
const char
comp(const string, const string);

/**
 * @brief читает одно слово из файлового потока
 * 
 * @return const string 
 */
const string
_read_one_word_from_stream(FILE*, const char);

/**
 * @brief переводит строку-число в число типа short
 * 
 * @return short 
 */
short __fastcall
atosh(const string);

/**
 * @brief работает как функция tolower, но для полной строки
 * 
 * @return string 
 */
string __cdecl
tolower_str(const string);

/**
 * @brief проверяет строку на то, состоит ли она только из чисел начиная с определенного индекса
 * 
 * @return true 
 * @return false 
 */
bool
is_digits_from(const string, const int);

#endif