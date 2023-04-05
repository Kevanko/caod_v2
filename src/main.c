#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> // for sleep

#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"
#include "../libraries/header.h"

struct listnode *hashtab[Hashtab_Size];
char words[MaxKeys][MaxKeyLenght];

int main() {
  struct bstree *tree, *node;
  struct listnode *hash, *node_hash;

  double time_bstree = 0.0, time_hash = 0.0;
  clock_t begin, end;
  FILE *file = fopen("Keys.txt", "r");
  if (!file) {
    return 1;
  }

  for (int i = 0; fgets(words[i], MaxKeyLenght, file) && i < MaxKeys; i++) {
    words[i][strlen(words[i]) - 2] = '\0';
  }
  fclose(file);

  printf("tree\t\thash\t\t\tkey\t\tkey_tree\t\tkey_hash\tvalue\n");
  hashtab_init(hashtab);
  hashtab_add(hashtab, words[0], 0);
  tree = bstree_create(words[0], 0);
  for (int i = 1; i < MaxKeys; i++) {
    bstree_add(tree, words[i], i);
    hashtab_add(hashtab, words[i], i);
    if ((i + 1) % 10000 == 0) {
      char *rand_key = words[getrand(0, i)];
      // bstree
      begin = clock();
      node = bstree_lookup(tree, rand_key);
      end = clock();
      time_bstree = (double)(end - begin) / CLOCKS_PER_SEC;

      // hastab
      begin = clock();
      node_hash = hashtab_lookup(hashtab, rand_key);
      end = clock();
      time_hash = (double)(end - begin) / CLOCKS_PER_SEC;

      printf("%f\t%f %20.25s %20.25s %20.25s\t\t%d\n", time_bstree, time_hash,
             rand_key, node->key, node_hash->key, node->value);
    }
  }

  return 0;
}