#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"
#include "../libraries/header.h"

struct listnode *hashtab[HASHTAB_SIZE];

int main() {
  struct bstree *tree, *node;

  FILE *file = fopen("Keys.txt", "r");
  if (!file)
    return 1;

  char words[MAX_KEYS - 1][MAX_SIZE];

  for (int i = 0; i < MAX_KEYS; i++) {
    fgets(words[i], MAX_KEYS, file);
  }

  fclose(file);
  printf("BSTREE\n");
  tree = bstree_create(words[0], 0);
  for (int i = 1; i < MAX_KEYS; i++) {
    bstree_add(tree, words[i], i);
    if (i % 10000 == 0) {
      //char *word = words[getrand(0, i)];
      double time = wtime();
      node = bstree_min(tree);
      time = wtime() - time;
      printf("%d\t\t%lf\t%d\n", i, time, node->value);
    }
  }
  bstree_free(tree);

  struct listnode *node2;

  hashtab_init(hashtab);
  printf("HASHTAB\n");
  tree = bstree_create(words[0], 0);
  for (int i = 1; i < MAX_KEYS; i++) {
    hashtab_add(hashtab, words[i], i);
    if (i % 10000 == 0) {
      char *word = words[rand() % i];
      double time = wtime();
      node2 = hashtab_lookup(hashtab, word);
      time = wtime() - time;
      printf("%d\t\t%lf\t%d\n", i, time, node2->value);
    }
  }

  return 0;
}