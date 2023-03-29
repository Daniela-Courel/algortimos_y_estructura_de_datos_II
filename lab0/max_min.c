#include <stdio.h>    /* printf(), scanf() */
#include <stdbool.h>  /* tipo bool         */

#include <assert.h>   /* assert() */

#define ARRAY_SIZE 10

struct max_min_result {
    int max_value;
    int min_value;
    unsigned int max_position;
    unsigned int min_position;
};

struct max_min_result compute_max_min(int array[], unsigned int length)
{
    struct max_min_result result = { array[0], array[0], 0, 0 };
    /*result.max_value = array[0];
    result.min_value = array[0];*/
    for (unsigned int i = 1; i < length; i++)
    {
        if (result.max_value<array[i])
        {
            result.max_position = i;
            result.max_value = array[i];
        }
        if (result.min_value>array[i])
        {
            result.min_position = i;
            result.min_value = array[i];
        }
    }
    return result;
}

int main(void)
{
    int array[ARRAY_SIZE] = { 4, -1, 5, 8, 9, 0, 3, 6, 0, 0 };

    for (int i = 0; i < ARRAY_SIZE; i++)
    {
        printf("Ingrese el valor para la posición %d: ", i);
        scanf("%d",&array[i]);
    }    


    struct max_min_result result = compute_max_min(array, ARRAY_SIZE);
    printf("Máximo: %d\n", result.max_value);
    printf("Posición del máximo: %u\n", result.max_position);
    printf("Mínimo: %d\n", result.min_value);
    printf("Posición del mínimo: %u\n", result.min_position);
    return 0;
}

