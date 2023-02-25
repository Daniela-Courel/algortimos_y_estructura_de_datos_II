#include <stdio.h>
#include "functions.h"
#include <stdbool.h>
#include <stdlib.h>

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size){
    FILE *filepath = fopen(path,"r");
    unsigned int i = 0;

  for(i=0; i<max_size && !feof(filepath); i++ ){
    fscanf(filepath, "%u '%c'\n", &indexes[i], &letters[i]);
  }
    return (i);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}
