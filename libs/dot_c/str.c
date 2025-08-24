#include "./dot_h/str.h"


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
comp(const string dest, const string src){
    return !strcmp(dest, src);
}

const char
comp_n(const string dest, const int n, const string src){
    for(int i = 0; i < n; ++i)
        if(dest[i] != src[i])
            return false;
    
    return true;
}

const string
_read_one_word_from_stream(FILE* stream, const char separ){
    string word = "";
    char c;
    while((c = getc(stream)) != separ && c != EOF)
        word = concat_c(word, c);

    return word;
}

short __fastcall
atosh(const string str){
    short num;
    switch(str[0]){
        case '1': num = 1; break;
        case '2': num = 2; break;
        case '3': num = 3; break;
        case '4': num = 4; break;
        case '5': num = 5; break;
        case '6': num = 6; break;
        case '7': num = 7; break;
        case '8': num = 8; break;
        case '9': num = 9; break;
        default: num = 0;
    }

    size_t i = 1, len = strlen(str);
    while(i < len){
        switch(str[i++]){
            case '1': num *= 10; num += 1; break;
            case '2': num *= 10; num += 2; break;
            case '3': num *= 10; num += 3; break;
            case '4': num *= 10; num += 4; break;
            case '5': num *= 10; num += 5; break;
            case '6': num *= 10; num += 6; break;
            case '7': num *= 10; num += 7; break;
            case '8': num *= 10; num += 8; break;
            case '9': num *= 10; num += 9; break;
            default: num *= 10;
        }   
    }

    return num;
}

string __cdecl
tolower_str(const string str){
    string lower_str = (string)malloc(sizeof(char) * strlen(str));
    if(!lower_str)
        exit(1);
    
    for(int i = 0; i < strlen(str); ++i)
        lower_str[i] = tolower(str[i]);

    return lower_str;
}

bool
is_digits_from(const string str, const int index){
    bool has_dot = false;

    for(int i = index; i < strlen(str); ++i){
        if(!isdigit(str[i]) && str[i] != '.') return false;
        if(str[i] == '.'){
            if(has_dot) return false;
            else has_dot = true;
        }
    }

    return true;
}