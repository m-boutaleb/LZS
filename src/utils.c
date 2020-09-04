#define utils_IMPORT
#include "utils.h"

void copy_string(uc* dest, const uc* source,us str_length){
    us i;
    for(i=0; i<str_length-1; i++)
        dest[i] = source[i];
    dest[i]='\0';
}

us compare_string(const uc* dest, const uc* source,us str_length){
    us i=0;
    while((us)str_length--)
        if(dest[i] != source[i++])
            return 1;
    return 0;
}

