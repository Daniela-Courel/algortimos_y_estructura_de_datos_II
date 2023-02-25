#include <stdlib.h>
#include <assert.h>
#include "stack.h"
 
struct _s_stack {
    stack_elem elem;
    struct _s_stack *next;
};

stack stack_empty(){
    return NULL;
}

struct _s_stack *new_node(stack_elem e){
    struct _s_stack *node = malloc(sizeof(struct _s_stack));
    node->next = NULL;
    node->elem = e;
    return node;
}

stack stack_push(stack s, stack_elem e){
    struct _s_stack *new_n = new_node(e);
    new_n->next = s;
    return new_n;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    struct _s_stack *n;
    n = s;
    s = s->next;
    free(n);
    return s;
}

unsigned int stack_size(stack s){
    int counter = 0;
    while (s != NULL){
        counter++;
        s = s->next;
    }
    return counter;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->elem;
}

bool stack_is_empty(stack s){
    return s == NULL;
}

stack_elem *stack_to_array(stack s){
    unsigned int ln = stack_size(s);
    stack_elem * a = malloc(sizeof(struct _s_stack)*ln);
    for (size_t i = 0; i < ln; i++){
        a[ln-i-1] = s->elem;
        s = s->next;
    }
    return a;
}

stack stack_destroy(stack s){
    struct _s_stack *p;
    while (s != NULL){
        p = s;
        s = s->next;
        free(p);
    }
    return s;
}