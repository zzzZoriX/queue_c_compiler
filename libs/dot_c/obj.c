#include "c:/queue_c_compiler/libs/dot_h/obj.h"

const char
is_valid_obj_name(const char* word){
    if(isdigit(word[0])) 
        return 0;

    for(size_t i = 1; i < strlen(word); ++i)
        if(!isalnum(word[i]) && word[i] != '_')
            return 0;

    return 1;
}