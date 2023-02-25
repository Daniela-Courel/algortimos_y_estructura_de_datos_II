#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    //scanf("%s", user_input);  el problema con scanf es que deja de leer después de un espácio, así que no lee el apellido
    fgets(user_input, MAX_LENGTH ,stdin);

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}