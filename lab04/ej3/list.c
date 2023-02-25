#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

struct list{
    list_elem elem;
    _list next;
};

_list empty(void){
    return NULL;
}

_list addl(list_elem e, _list l){
    _list new_node = malloc(sizeof(_list));
    new_node->next = l;
    new_node->elem = e;
    return new_node;
}

bool is_empty(_list l){
    return l == NULL;
}

list_elem head(_list l){
    assert(!is_empty(l));
    return l->elem;
}

_list tail(_list l){
    assert(!is_empty(l));
    return l->next;
}

_list addr(_list l,list_elem e){
    _list p = malloc(sizeof(_list));
    _list q = malloc(sizeof(_list));
    q->elem = e;
    p = l;
    while (p->next == NULL){
        p = p->next;
    }
    p->next = q;
    free(p);
    return l;
}

unsigned int length(_list l){
    _list p = malloc(sizeof(_list));
    int counter = 0;
    return counter;
}

_list concat(_list l, _list l0){
    for (size_t i = 0; i < length(l0); i++){
        addr(l,l0->elem);
        tail(l0);
    }
    return l;
}

list_elem index(_list l, unsigned int n){
    assert(n <= length(l));
    _list p = l;
    unsigned int counter = 0;
    while(counter < n){
        p = p->next;
        counter++;
    }
    return p->elem;
}

_list take(_list l, unsigned int n){
    _list p = malloc(sizeof(_list));
    p = l;
    for (size_t i = 0; i <= n; i++){
        p = p->next;
    }
    while (p != NULL){
        tail(p);
    }
    free(p);
    return l;
}

_list drop(_list l, unsigned int n){
    for (size_t i = 0; i <= n; i++){
        if (is_empty(l))
            break;
        else
            tail(l);        
    }
    return l;
}

_list copy__list(_list l1){
    _list p = malloc(sizeof(_list));
    _list l2 = malloc(sizeof(_list));
    p = l1;
    while (l1 != NULL){
        l2 = addr(l2, p->elem);
        p = p->next;
    }
    free(p);
    return l2;
}

_list destroy (_list l){
    _list p = malloc(sizeof(_list));
    while (l->next != NULL){
        p = l;
        l = l->next;
        free(p);
    }
    free(l);
    return l;
}