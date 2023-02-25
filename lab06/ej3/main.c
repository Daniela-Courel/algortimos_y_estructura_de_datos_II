/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Then, this project's includes, alphabetically ordered */
#include "dict.h"
#include "dict_helpers.h"
#include "helpers.h"
#include "string.h"

#define ADD    'a'
#define REMOVE 'r'
#define DUMP   'u'
#define EMPTY  'e'
#define LOAD   'l'
#define SEARCH 's'
#define REPLACE 'c'
#define SHOW   'h'
#define SIZE   'z'
#define QUIT   'q'

#define RESULT_PREFIX "\t-> "

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s\n\n", program_name);
}

char print_menu(void) {
    char result = '\0';
    char *line = NULL;

    printf("\nChoose what you want to do. Options are:\n"
           "\n"
           "\t**************************************************************\n"
           "\t* z: Size of the dictionary                                  *\n"
           "\t* s: Search for a definition in the dict                     *\n"
           "\t* a: Add a new word to the dict                              *\n"
           "\t* r: Remove a word from the dict                             *\n"
           "\t* c: Change a definition to the dict                         *\n"
           "\t* e: Empty the dict                                          *\n"
           "\t* h: Show the dict in stdout                                 *\n"
           "\t* l: Load the dict from a file                               *\n"
           "\t* u: Dump the dict to a file                                 *\n"
           "\t* q: Quit                                                    *\n"
           "\t**************************************************************\n"
           "\nPlease enter your choice: ");

    line = readline_from_stdin();
    if (line != NULL) {
        result = line[0];
    }

    free(line);
    return (result);
}

bool is_valid_option(char option) {
    bool result = false;

    result = (option == ADD || option == REMOVE ||
              option == DUMP || option == EMPTY || option == LOAD ||
              option == SEARCH || option == SHOW || option == SIZE ||
              option == QUIT);

    return (result);
}

string get_input(const char *message) {
    string result = NULL;
    printf("\t%s: ", message);
    result = readstring_from_stdin();
    assert(result != NULL);
    return (result);
}

dict_t on_add(dict_t current) {
    string definition = NULL;
    string word = NULL;
    word = get_input("Please enter the word to add into the dict");
    if (dict_exists(current, word)) {
        printf(RESULT_PREFIX "The word is already in the dict.\n");
        word = string_destroy(word);
    } else {
        definition = get_input("Please enter the definition");
        current = dict_add(current, word, definition);
        printf(RESULT_PREFIX "The word and definition were added.\n");
    }
    return (current);
}

dict_t on_replace(dict_t current) {
    string definition = NULL;
    string word = NULL;
    word = get_input("Please enter the word to replace in the dict");
    if (!dict_exists(current, word)) {
        printf(RESULT_PREFIX "The word does not exist in the dict.\n");
        word = string_destroy(word);
    } else {
        definition = get_input("Please enter the new definition");
        current = dict_add(current, word, definition);
        printf(RESULT_PREFIX "The definition was replaced.\n");
    }
    return (current);
}

dict_t on_remove(dict_t current) {
    string word =
            get_input("Please enter the word to delete from the dict");
    if (!dict_exists(current, word)) {
        printf(RESULT_PREFIX "The word does not exist in the dict.\n");
    } else {
        current = dict_remove(current, word);
        printf(RESULT_PREFIX "The word was removed.\n");
    }
    word = string_destroy(word);
    return (current);
}

dict_t on_load(dict_t current) {
    string filename
            = get_input("Please enter the filename to load the dict from");
    dict_t other = dict_from_file(filename);
    if (other == NULL) {
        printf("Can not load dict from filename %s\n", string_ref(filename));
    } else {
        printf(RESULT_PREFIX "The dictionary was successfully loaded.\n");
        current = dict_destroy(current);    /* destroy current */
        current = other;
    }
    filename = string_destroy(filename);
    return (current);
}

void on_dump(dict_t current) {
    string filename = get_input("Please enter the filename to dump the file");
    dict_to_file(current, filename);
    filename = string_destroy(filename);
    printf(RESULT_PREFIX "The dictionary was successfully dumped.\n");
}

dict_t on_empty(dict_t current) {
    current = dict_remove_all(current);
    printf(RESULT_PREFIX "All words were removed\n");
    return (current);
}

void on_search(dict_t current) {
    string definition = NULL;
    string word = NULL;
    word = get_input("Please enter the word to search in the dict");
    definition = dict_search(current, word);
    if (definition == NULL) {
        printf(RESULT_PREFIX "The word does not exist in the dict\n");
    } else {
        printf(RESULT_PREFIX "The definition of \"%s\" is : \"%s\"\n",
               string_ref(word), string_ref(definition));
    }
    word = string_destroy(word);
}

void on_size(dict_t current) {
    printf(RESULT_PREFIX "The size of the dict is %u\n", dict_length(current));
}

int main(void) {
    char option = '\0';
    key_t word = '\0';
    value_t value = '\0';
    dict_t current = dict_empty();
    /* print a simple menu and do the requested operations */
    do {
        option = print_menu();
        switch (option) {
            case ADD: //testeada
                printf("Enter the new word: ");
                word = readstring_from_stdin();
                if (dict_exists(current, word)) {
                    printf("This word already exists.");
                }else{
                    printf("Enter the difinition: ");
                    value = readstring_from_stdin();
                    current = dict_add(current, word, value);
                    value = string_destroy(value);
                }
                word = string_destroy(word);
                value = string_destroy(value);

                break;
            case REMOVE: //testeada
                printf("Enter the word to remove: ");
                word = readstring_from_stdin();
                if(!dict_exists(current, word)){
                    printf("This word does not exist.\n");
                }else{
                    current = dict_remove(current, word);
                    printf("The word has been removed.\n");
                }
                word = string_destroy(word);

                break;
            case REPLACE: //testeada
                printf("Enter the word to remplace: ");
                word = readstring_from_stdin();
                if (!dict_exists(current, word)) {
                    printf("This word does not exists.");
                }else{
                    printf("Enter the new difinition: ");
                    value = readstring_from_stdin();
                    current = dict_add(current, word, value);
                }
                word = string_destroy(word);
                value = string_destroy(value);

                break;
            case DUMP:  //testeada
                printf("Enter the filepath name: ");
                string file_dump = readstring_from_stdin();
                dict_to_file(current, file_dump);
                file_dump = string_destroy(file_dump);

                break;
            case EMPTY:   //testeada
                current = dict_remove_all(current);
                printf("The dictionary has been removed.\n ");

                break;
            case LOAD:      //no funca
                printf("Enter the filepath name: ");
                string file = readstring_from_stdin();
                current = dict_from_file(file);
                string_destroy(file);

                break;
            case SEARCH:    //testeada
                printf("Enter the word to search: ");
                word = readstring_from_stdin();
                if (!dict_exists(current, word)) {
                    printf("This word does no exist in this dictionary.\n");
                }else {
                    string_dump(word, stdout);
                    printf(": ");
                    string_dump(dict_search(current, word), stdout);
                }
                word = string_destroy(word);

                break;
            case SHOW:      //testeada
                dict_dump(current, stdout);

                break;
            case SIZE:      //testeada
                printf("The number of words is: %d.\n", dict_length(current));

                break;
            case QUIT:
                current = dict_destroy(current);
                printf(RESULT_PREFIX "Exiting.\n");
                return (EXIT_SUCCESS);
            default:
                printf("\n\"%c\" is invalid. Please choose a valid "
                       "option.\n\n", option);
        }
    } while (option != QUIT);
    current = dict_destroy(current);
    return (EXIT_SUCCESS);
}
