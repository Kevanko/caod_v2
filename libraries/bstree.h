#pragma once
#include <stdint.h>

struct bstree {
  char *key;
  uint32_t value;
  struct bstree *left;
  struct bstree *right;
};

struct bstree *bstree_create(char *key, int value);
void bstree_add(struct bstree *tree, char *key, int value);
void bstree_add_right(struct bstree *tree, char *key, int value);
struct bstree *bstree_lookup(struct bstree *tree, char *key);
struct bstree *bstree_delete(struct bstree *tree, char *key);
struct bstree *bstree_min(struct bstree *tree);
struct bstree *bstree_max(struct bstree *tree);
void bstree_free(struct bstree* tree);