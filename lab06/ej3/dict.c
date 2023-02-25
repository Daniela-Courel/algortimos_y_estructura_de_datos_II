#include <assert.h>
#include <stdlib.h>
#include "dict.h"
#include "key_value.h"      

struct _node_t {
    dict_t left;
    dict_t right;
    key_t key;
    value_t value;
};

static key_t dict_max(dict_t tree);

static key_t dict_min(dict_t tree);

static bool invrep(dict_t dict) {
    return dict == NULL || ((dict->left == NULL || (!key_less(dict->key, dict_max(dict->left)) && invrep(dict->left))) &&
           (dict->right == NULL || (key_less(dict->key, dict_min(dict->right)) && invrep(dict->right))));
}

static key_t dict_max(dict_t tree) {
    key_t max_e;
    assert(invrep(tree));
    if (tree != NULL){
        if (tree->right != NULL)
            max_e = dict_max(tree->right);
        else
            max_e = tree->key;
    }
    
    assert(invrep(tree) && dict_exists(tree, max_e));
    return max_e;
}

static key_t dict_min(dict_t tree) {
    key_t min_e;
    assert(invrep(tree));
    if(tree != NULL){
        if (tree->left != NULL)
            min_e = dict_min(tree->left);
        else
            min_e = tree->key;
    }
        
    assert(invrep(tree) && dict_exists(tree, min_e));
    return min_e;
}

dict_t dict_empty(void) {
    dict_t dict = NULL;
    assert(invrep(dict));
    return dict;
}

static struct _node_t *new_node(key_t k, value_t d){
    struct _node_t *n = malloc(sizeof(struct _node_t));
    n->key = k;
    n->value = d;
    n->left = NULL;
    n->right = NULL;
    return n;
}

dict_t dict_add(dict_t dict, key_t word, value_t def) {
    assert(invrep(dict));
    string_dump(word, stdout);
    printf("\n");
    if(dict == NULL){
        dict = new_node(key_clone(word), value_clone(def));
    }else if (key_less(word, dict->key)){
        dict->left = dict_add(dict->left,word,def);
    }else if(key_less(dict->key, word)){
        dict->right = dict_add(dict->right,word,def);
    }else {
        value_t tmp;
        tmp = dict->value;
        dict->value = value_clone(def);
        value_destroy(tmp);
    }
    
    assert(invrep(dict));
    assert(dict_exists(dict, word));
    return dict;
}

value_t dict_search(dict_t dict, key_t word) {
    value_t def;
    assert(invrep(dict) && dict_exists(dict, word));
    if(dict != NULL && string_eq(dict->key, word))
        def = dict->value;
    else if(key_less(word, dict->key)){
        def = dict_search(dict->left, word);
    }else if (key_less(dict->key, word))
        def = dict_search(dict->right, word);
    return def;
}

bool dict_exists(dict_t dict, key_t word) {
    bool exists=false;
    assert(invrep(dict)); 
    if (dict == NULL)
        exists = false;
    else if(string_eq(dict->key, word))
        exists = true;
    else if(key_less(word, dict->key)){
        exists = dict_exists(dict->left, word);
    }else if (key_less(dict->key, word))
        exists = dict_exists(dict->right, word);
    return exists;
}

unsigned int dict_length(dict_t dict) {
    unsigned int length=0;
    assert(invrep(dict));
    if (dict != NULL){
        length = 1 + dict_length(dict->left) + dict_length(dict->right);
    }
    assert(invrep(dict) ||  length > 0);
    return length;
}

static dict_t max_node(dict_t tree) {
    assert(invrep(tree) );
    while(tree->right != NULL && (tree->right)->right != NULL){
        tree = tree->right;
    }
    assert(invrep(tree));
    return tree;
}

static dict_t remove_root(dict_t tree) {
    struct _node_t *p = NULL;
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
        struct _node_t *q = NULL;
        p = max_node(tree->left);
        tree->key = (p->right)->key;
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

dict_t dict_remove(dict_t tree, key_t word) {
    assert(invrep(tree));
    assert(dict_exists(tree, word));
    if(string_eq(tree->key, word)){
        tree = remove_root(tree);
    }else if(key_less(tree->key,word)){
        tree->right = dict_remove(tree->right, word);
    }else
        tree->left = dict_remove(tree->left, word);
    assert(invrep(tree) && !dict_exists(tree, word));
    return tree;
}

dict_t dict_remove_all(dict_t dict) {
    if (dict != NULL){
        dict_destroy(dict->left);
        dict_destroy(dict->right);
        dict-> key = string_destroy(dict->key);
        dict->value = string_destroy(dict->value);
        dict->right = NULL;
        dict->left = NULL;
        free(dict);
        dict = NULL;
    }
    return dict;
}

void dict_dump(dict_t dict, FILE *file) {
    assert(invrep(dict));
    if (dict != NULL) {
        dict_dump(dict->left, file);
        string_dump(dict->key, file);
        fprintf(file, ": ");
        string_dump(dict->value, file);
        fprintf(file, "\n");
        dict_dump(dict->right, file);
    }
}

dict_t dict_destroy(dict_t dict) {
    assert(invrep(dict));
    dict = dict_remove_all(dict);
    assert(dict == NULL);
    return dict;
}
