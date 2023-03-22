#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"

struct bstree *bstree_create(char *key, int value)
{
    struct bstree *v = (struct bstree*)malloc(sizeof(struct bstree));
    if(!v){
        return NULL;
    }

    v->key = key;
    v->value = value;
    v->left = NULL;
    v->right = NULL;

    return v;
}
void bstree_add(struct bstree *tree, char *key, int value)
{
    if(!tree){
        return;
    }
    struct bstree *v = bstree_create(key, value);

    if (!v){
        return;
    }
    struct bstree *parent;
    while(tree != NULL){
        parent = tree;
        if (value > tree->value){
            tree = tree->right;
        }
        else{
            tree = tree->left;
        }
    }
    if(parent->value < value){
        parent->right = v;
    }
    else{
       parent->left = v; 
    }

}
struct bstree *bstree_lookup(struct bstree *tree, char *key)
{
    while (tree != NULL) {
        if (key == tree->key)
            return tree;
        else if (key < tree->key)
            tree = tree->left;
        else
            tree = tree->right;
    }

    return tree;
}
struct bstree *bstree_delete(struct bstree *tree, char *key)
{

}
struct bstree *bstree_min(struct bstree *tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}
struct bstree *bstree_max(struct bstree *tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}