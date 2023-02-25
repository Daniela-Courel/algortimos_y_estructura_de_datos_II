#include <stdio.h>
#include <stdlib.h>
#include "string.h"

int main(void) {
    const char *c = "kansdfds";
    string s = string_create(c);
    const char *d = "ansdfds";
    string k = string_create(d);
    string j = string_clone(k);
    printf("el largo del string es: %d\n", string_length(s));
    printf("el primer string es menor que el segundo?: %d\n", string_less(s,k));
    printf("y al revez?: %d\n", string_less(k,s));
    printf("s y k son iguales?: %d\n", string_eq(s,k));
    printf("j y k son iguales?: %d\n", string_eq(j,k));
    string_dump(s, stdout);
    const char *a = string_ref(s);

    string_destroy(k);
    string_destroy(j);
    string_destroy(s);

    return 0;
}
