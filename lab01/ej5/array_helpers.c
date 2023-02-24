#include <stdio.h>
#include "mybool.h"
#include "array_helpers.h"

unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    FILE *fp;
    fp = fopen(filepath, "r");

    unsigned int size_array;
    fscanf(fp,"%u",&size_array);
    if (size_array > max_size){
        printf("El archivo es contiene más elementos de los que se pueden leer.");
    }
    
    for (unsigned int i = 0; i < size_array; i++){
        fscanf(fp,"%d",&array[i]);
    }
    
    fclose(fp);
    
    return size_array;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0; i < length-1; i++) {
        printf(" %d,",a[i]);
    }
    printf(" %d]\n",a[length-1]);
}

mybool array_is_sorted(int a[], unsigned int length){
    mybool is_sorted = true;
    for (unsigned int i = 0; i < length-1; i++) {
        is_sorted = is_sorted && a[i] <= a[i+1];
    }

    return is_sorted;   
}