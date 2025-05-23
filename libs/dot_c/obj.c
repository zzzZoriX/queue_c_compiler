#include "./dot_h/obj.h"

const char
is_valid_obj_name(const char* word){
    if(!isalpha(word[0]) && word[0] != '_') 
        return 0;

    for(size_t i = 1; i < strlen(word); ++i)
        if(!isalnum(word[i]) && word[i] != '_')
            return 0;

    return 1;
}