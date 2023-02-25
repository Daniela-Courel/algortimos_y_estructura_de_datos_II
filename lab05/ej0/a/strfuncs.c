#include <stdio.h>
#include <stdlib.h>
#include "strfuncs.h"

size_t string_length(const char *str){
    unsigned long int counter = 0;
    while (*str != '\0'){
        str++;
        counter++;
    }
    return counter;
}

char *string_filter(const char *str, char c){
    size_t ln = string_length(str);
    char * str_fil = malloc(sizeof(char));
    size_t j = 0;
    for (size_t i = 0; i < ln; i++){
        if (str[i] != c){
            str_fil[j] = str[i];
            j++;
        }
    }
    str_fil = realloc(str_fil, sizeof(char)*j);
    return str_fil;
}