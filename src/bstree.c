#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libraries/bstree.h"

struct bstree *bstree_create(char *key, int value) {
  struct bstree *v = (struct bstree *)malloc(sizeof(struct bstree));
  if (!v) {
    return NULL;
  }

  v->key = key;
  v->value = value;
  v->left = NULL;
  v->right = NULL;

  return v;
}
void bstree_add(struct bstree *tree, char *key, int value) {
  if (tree == NULL)
    return;
  struct bstree *parent, *node;
  while (tree != NULL) {
    parent = tree;
    if (strcmp(key, tree->key) < 0)
      tree = tree->left;
    else if (strcmp(key, tree->key) > 0)
      tree = tree->right;
    else
      return;
  }
  node = bstree_create(key, value);
  if (strcmp(key, parent->key) < 0)
    parent->left = node;
  else
    parent->right = node;
}

void bstree_add_right(struct bstree *tree, char *key, int value) {
  if (tree == NULL)
    return;
  struct bstree *parent, *node;
  while (tree != NULL) {
    parent = tree;
    if (strcmp(key, tree->key) < 0)
      tree = tree->right;
    else if (strcmp(key, tree->key) > 0)
      tree = tree->right;
    else
      return;
  }
  node = bstree_create(key, value);
  if (strcmp(key, parent->key) < 0)
    parent->right = node;
  else
    parent->right = node;
}


struct bstree *bstree_lookup(struct bstree *tree, char *key) {
  while (tree != NULL) {
    if (strcmp(key, tree->key) == 0)
      return tree;
    else if (strcmp(key, tree->key) < 0)
      tree = tree->left;
    else
      tree = tree->right;
  }
  return tree;
}

struct bstree *bstree_min(struct bstree *tree) {
  if (!tree)
    return NULL;

  while (tree->left != NULL)
    tree = tree->left;
  return tree;
}
struct bstree *bstree_max(struct bstree *tree) {
  if (!tree)
    return NULL;

  while (tree->right != NULL)
    tree = tree->right;
  return tree;
}

struct bstree *bstree_delete(struct bstree *tree, char *key) {
  if (!tree)
    return NULL;

  struct bstree *parent = NULL;
  struct bstree *node = tree;

  // Find the node to be deleted and its parent
  while (node) {
    if (strcmp(key, node->key) == 0) {
      break;
    } else if (strcmp(key, node->key) < 0) {
      parent = node;
      node = node->left;
    } else {
      parent = node;
      node = node->right;
    }
  }

  // If the node was not found, return the original tree
  if (!node) {
    return tree;
  }

  // If the node has no children, just remove it
  if (!node->left && !node->right) {
    if (!parent) {
      // The node is the root of the tree
      free(node);
      return NULL;
    } else if (parent->left == node) {
      parent->left = NULL;
    } else {
      parent->right = NULL;
    }
    free(node);
  }
  // If the node has one child, replace it with its child
  else if (!node->left || !node->right) {
    struct bstree *child = node->left ? node->left : node->right;
    if (!parent) {
      // The node is the root of the tree
      free(node);
      return child;
    } else if (parent->left == node) {
      parent->left = child;
    } else {
      parent->right = child;
    }
    free(node);
  }
  // If the node has two children, replace it with the minimum node in its
  // right subtree
  else {
    struct bstree *successor = bstree_min(node->right);
    node->key = successor->key;
    node->value = successor->value;
    tree->right = bstree_delete(tree->right, successor->key);
  }

  return tree;
}

void bstree_free(struct bstree *tree) {
  size_t capacity = 2000000;
  size_t top = 0;
  struct bstree **stack =
      (struct bstree **)malloc(capacity * sizeof(struct bstree *));

  if (!tree)
    return;

  stack[top++] = tree;

  while (top > 0) {
    struct bstree *current = stack[--top];

    if (current->left)
      stack[top++] = current->left;
    if (current->right)
      stack[top++] = current->right;

    // Увеличиваем размер стека, если он заполнен
    if (top == capacity) {
      capacity *= 2;
      stack =
          (struct bstree **)realloc(stack, capacity * sizeof(struct bstree *));
    }

    free(current);
  }

  free(stack);
}