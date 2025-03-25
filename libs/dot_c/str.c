#include "c:/queue_c_compiler/libs/dot_h/str.h"
#include <string.h>


string
concat(const string dest, const string src){
    if(!dest || !src)
        return NULL;

    const size_t length = strlen(dest) + strlen(src) + 1;
    string res = (string)malloc(sizeof(char) * length);
    if(!res)
        return NULL;

    size_t i = 0;
    for(; i < strlen(dest); ++i)
        res[i] = dest[i];

    for(size_t k = 0; i < length && k < strlen(src); ++k, ++i)
        res[i] = src[k];

    res[length - 1] = '\0';

    return res;
}

string
c_concat(const char dest, const string src){
    const size_t length = strlen(src) + 2;
    string res = (string)malloc(sizeof(char) * length);
    if(!res)
        return NULL;

    res[0] = dest;

    for(size_t i = 1, k = 0; k < strlen(src) && i < length; ++i, ++k)
        res[i] = src[k];

    res[length - 1] = '\0';

    return res;
}

string
concat_c(const string dest, const char src){
    if(!dest || !src) return dest;
    
    const size_t length = strlen(dest) + 2;
    string res = (string)malloc(sizeof(char) * length);
    if(!res)
        return NULL;

    for(size_t i = 0; i < strlen(dest) && i < length; ++i)
        res[i] = dest[i];

    res[length - 2] = src;
    res[length - 1] = '\0';

    return res;
}

string
c_concat_c(const char dest, const char src){
    string res = (string)malloc(sizeof(char) * 3);
    if(!res)
        return NULL;

    res[0] = dest;
    res[1] = src;
    res[2] = '\0';

    return res;
}

string
dex_spaces(const string src){
    if(src == NULL)
        return NULL;

    const char* start = src;
    const char* end = src + strlen(src) - 1;

    while(isspace(*start))
        start++;

    while(end > start && isspace(*end))
        end--;

    size_t length = end - start + 1;

    string result = (string)malloc(length + 1);
    if(result == NULL)
        return NULL;

    strncpy(result, start, length);
    result[length] = '\0';

    return result;
}

const char
isspec(const char c){
    return (
        c == ';' ||
        c == '(' ||
        c == ')' ||
        c == '{' ||
        c == '}' ||
        c == '[' ||
        c == ']'
    );
}

const char
comp(const string dest, const string src){
    return !strcmp(dest, src);
}

const string
_read_one_word_from_stream(FILE* stream, const char separ){
    string word = "";
    char c;
    while((c = getc(stream)) != separ && c != EOF)
        word = concat_c(word, c);

    return word;
}