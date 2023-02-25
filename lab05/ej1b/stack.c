#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "stack.h"

struct _s_stack {
    stack_elem *elems;
    unsigned int size;
    unsigned int capacity;
};


stack stack_empty(){
    stack s = malloc(sizeof(struct _s_stack));
    s->elems = malloc(sizeof(stack_elem)*2);
    s->size = 0;
    s->capacity = 2;  
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(s != NULL);
    assert(s->capacity >= s->size);
    if (s->size == s->capacity){
        s->capacity = s->capacity*2;
        s->elems = realloc(s->elems, sizeof(stack_elem)*s->capacity);
    }
    s->elems[s->size] = e;
    s->size++;
    return s;
}

stack stack_pop(stack s){
    assert(s != NULL);
    s->size--;
    return s;
}

unsigned int stack_size(stack s){
    assert(s != NULL);
    return s->size;
}

stack_elem stack_top(stack s){
    assert(s != NULL);
    return s->elems[s->size-1];
}

bool stack_is_empty(stack s){
    assert(s != NULL);
    return s->size == 0;
}

stack_elem *stack_to_array(stack s){
    assert(s != NULL);
    stack_elem *arr = NULL;
    if(s->size) {
    arr = calloc(s->size, sizeof(stack_elem));
    arr = memcpy(arr, s->elems, s->size*sizeof(stack_elem));
    }
    return arr;
}

stack stack_destroy(stack s){
    assert(s != NULL);
    free(s->elems);
    free(s);
    return s;
}