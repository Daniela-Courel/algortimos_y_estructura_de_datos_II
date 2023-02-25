#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "abb.h"

struct _s_abb {
    abb_elem elem;
    struct _s_abb *left;
    struct _s_abb *right;
};

static bool elem_eq(abb_elem a, abb_elem b) {
    return a == b;
}

static bool elem_less(abb_elem a, abb_elem b) {
    return a < b;
}

static bool invrep(abb tree) {
    return tree == NULL ||
           ((tree->left == NULL || (tree->elem > abb_max(tree->left) && invrep(tree->left))) &&
           (tree->right == NULL || (tree->elem < abb_min(tree->right) && invrep(tree->right))))
           ;
}

static struct _s_abb *new_node(abb_elem e){
    struct _s_abb *n = malloc(sizeof(struct _s_abb));
    n->elem = e;
    n->left = NULL;
    n->right = NULL;
    return n;
}

abb abb_empty(void) {
    abb tree = NULL;
    assert(invrep(tree) && abb_is_empty(tree));
    return tree;
}

abb abb_add(abb tree, abb_elem e) {
    assert(invrep(tree));
    if(tree == NULL){
        tree = new_node(e);
    }else if (elem_less(e, tree->elem))
        tree->left = abb_add(tree->left,e);
    else if(elem_less(tree->elem,e))
        tree->right = abb_add(tree->right,e);
    
    assert(invrep(tree));
    assert(abb_exists(tree, e));
    return tree;
}

bool abb_is_empty(abb tree) {
    assert(invrep(tree));
    return tree == NULL;
}

bool abb_exists(abb tree, abb_elem e) {
    bool exists=false;
    assert(invrep(tree));
    if (tree == NULL)
        exists = false;
    else if(elem_eq(tree->elem, e))
        exists = true;
    else if(elem_less(e, tree->elem)){
        exists = abb_exists(tree->left, e);
    }else if (elem_less(tree->elem,e))
        exists = abb_exists(tree->right, e);
    return exists;
}

unsigned int abb_length(abb tree) {
    unsigned int length=0;
    assert(invrep(tree));
    if (tree != NULL){
        length = 1 + abb_length(tree->left) + abb_length(tree->right);
    }
    assert(invrep(tree) && (abb_is_empty(tree) ||  length > 0));
    return length;
}

static abb max_node(abb tree) {
    assert(invrep(tree) );
    while(tree->right != NULL && (tree->right)->right != NULL){
        tree = tree->right;
    }
    assert(invrep(tree));
    return tree;
}

void abb_dump(abb tree) {
    assert(invrep(tree));
    if (tree != NULL) {
        abb_dump(tree->left);
        printf("%d ", tree->elem);  
        abb_dump(tree->right);
    }
}

static abb remove_root(abb tree) {
    struct _s_abb *p = NULL;
    if (tree->left == NULL) {
        p = tree;
        tree = tree->right;
        
    }else if (tree->right == NULL) {
        p = tree;
        tree = tree->left;

    }else if ((tree->left)->right == NULL){
        p = tree,
        tree = tree->left;
        tree->right = p->right;

    }else{
        struct _s_abb *q = NULL;
        p = max_node(tree->left);
        tree->elem = (p->right)->elem;
        q = p->right;
        if ((p->right)->left != NULL){
            p->right = q->left;
            p = q;
        }else{
            p->right = NULL;
            p = q;
        }
    }
    free(p);

    return tree;
}

abb abb_remove(abb tree, abb_elem e) {
    assert(invrep(tree) && abb_exists(tree, e));
    bool comas = abb_exists(tree, 80);
    comas = comas;
    if(tree->elem == e){
        printf("%d es igual a %d\n", tree->elem, e);
        tree = remove_root(tree);
    }else if(elem_less(tree->elem,e)){
        tree->right = abb_remove(tree->right, e);
    }else
        tree->left = abb_remove(tree->left, e);
    assert(invrep(tree) && !abb_exists(tree, e));
    return tree;
}

abb_elem abb_root(abb tree) {
    abb_elem root;
    assert(invrep(tree) && !abb_is_empty(tree));
    root = tree->elem;
    assert(abb_exists(tree, root));
    return root;
}

abb_elem abb_max(abb tree) {
    abb_elem max_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if (tree != NULL){
        if (tree->right != NULL)
            max_e = abb_max(tree->right);
        else
            max_e = tree->elem;
    }
    
    assert(invrep(tree) && abb_exists(tree, max_e));
    return max_e;
}

abb_elem abb_min(abb tree) {
    abb_elem min_e;
    assert(invrep(tree) && !abb_is_empty(tree));
    if(tree != NULL){
        if (tree->left != NULL)
            min_e = abb_min(tree->left);
        else
            min_e = tree->elem;
    }
        
    assert(invrep(tree) && abb_exists(tree, min_e));
    return min_e;
}


abb abb_destroy(abb tree) {
    assert(invrep(tree));
    if(tree != NULL) {
        abb_destroy(tree->left);
        abb_destroy(tree->right);
        free(tree);
        tree = NULL;
    }
    assert(tree == NULL);
    return tree;
}