#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "functions.h"

#define MAX_SIZE 1000


static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    filepath = parse_filepath(argc,argv);
    unsigned int length=0;
    length = data_from_file(filepath,indexes,letters,MAX_SIZE);


    for (unsigned int i = 0; i < length; i++)
        sorted [indexes[i]] = letters[i];

    dump(sorted, length);

    return EXIT_SUCCESS;
}

