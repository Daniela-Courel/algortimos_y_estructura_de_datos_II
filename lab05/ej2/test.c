#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void array_dump(int a[], unsigned int length) {
    fprintf(stdout, "[");
    for (unsigned int i = 0u; i < length; ++i) {
        fprintf(stdout, "%d", a[i]);
        if (i < length - 1) {
            fprintf(stdout, ", ");
        } else {
            fprintf(stdout, "]\n");
        }
    }
}

int main(void) {
    stack s = stack_empty();
    for (size_t i = 0; i < 100; i++){
        s = stack_push(s,i);
    }

    if (stack_is_empty(s))
        printf("la lista está vacía\n");
    else
        printf("la lista no está vacía y su tamaño es: %u\n", stack_size(s));


    stack_elem *revarr = stack_to_array(s);
    revarr = revarr;

    printf("[");
    while( 1 < stack_size(s)){
        printf(" %d,", stack_top(s));
        s = stack_pop(s);
    }
    printf(" %d ]\n", stack_top(s));
    s = stack_pop(s);
    


    if (stack_is_empty(s))
        printf("la lista está vacía \n");
    else
        printf("la lista no está vacía y su tamaño es: %u\n", stack_size(s));

    

    s = stack_destroy(s);
    
    return 0;
}