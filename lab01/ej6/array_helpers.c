#include "array_helpers.h"
#include <stdio.h>
#include "mybool.h"

unsigned int array_from_file(int array[],unsigned int max_size,const char *filepath) {
    
    FILE *input_file = fopen(filepath,"r");
    unsigned int lengt;
    fscanf(input_file,"%u", &lengt);
    unsigned int i = 0;

    if (lengt > max_size)
        printf("El archivo es contiene más elementos de los que se pueden leer.");
    else{
        while (i < lengt)
        {
            fscanf(input_file, "%d", &array[i]);
            i++;
        }
        fclose(input_file);
    }
    return lengt;
}

void array_dump(int a[], unsigned int length) {
    printf("[");
    for (unsigned int i = 0; i < length-1; i++)
        printf(" %d,", a[i]);
    
    printf(" %d]", a[length-1]);
}

mybool array_is_sorted(int a[], unsigned int length){
    mybool sorted = true;
    for (unsigned int i = 0; i < length-1; i++)
    {
        sorted = sorted && a[i] <= a[i+1];
    }

    return sorted;
}


void array_swap(int a[], unsigned int i, unsigned int j){
    unsigned int copy = a[i];
    a[i] = a[j];
    a[j] = copy;
}