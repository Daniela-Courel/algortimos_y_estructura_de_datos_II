/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return (x.rank <= y.rank);
}

void swap(player_t array[], unsigned int a, unsigned int b){
    player_t c = array[a];
    array[a] = array[b];
    array[b] = c;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

static unsigned int partition(player_t a[], unsigned int izq, unsigned int der) {
    int ppiv,i,j;
    ppiv = izq;
    i = izq+1;
    j = der;
    while (i<=j){
        if (goes_before(a[i],a[ppiv]))
            i++;
        else if (goes_before(a[j],a[ppiv])){
                swap(a,i,j);
                i++;
                j--;
            } 
        else if(goes_before(a[ppiv],a[j]))  
            j--;
    }

    swap(a,ppiv,j);
    ppiv = j;

    return ppiv;  
}

static void quick_sort_rec(player_t a[], unsigned int izq, unsigned int der) {
    unsigned int ppiv;
    if (der > izq){
        ppiv = partition(a,izq,der);
        printf("izq vale %u \n der vale %u \n ppiv vale %d \n",izq,der,ppiv);
        if(ppiv>0)
            quick_sort_rec(a,izq,ppiv-1);
        quick_sort_rec(a,ppiv+1,der);
    }
}

void sort(player_t a[], unsigned int length) {
    quick_sort_rec(a, 0, (length == 0) ? 0 : length - 1);
}