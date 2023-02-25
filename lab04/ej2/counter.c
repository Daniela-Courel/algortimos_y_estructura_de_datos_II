#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "counter.h"

struct _counter {
    unsigned int count;
};

counter counter_init(void) {
    counter new_counter = malloc(sizeof(counter));
    return new_counter;
}

void counter_inc(counter c) {
    c->count++;
}

bool counter_is_init(counter c) {
    return (c->count == 0);
}

void counter_dec(counter c) {
    c->count--;
}

counter counter_copy(counter c) {
    return c;
}

void counter_destroy(counter c) {
    free(c);
}
