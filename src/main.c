#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> // for sleep

#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"
#include "../libraries/header.h"
  char words[MaxKeys][MaxKeyLenght];
int main() {


  struct bstree *tree_good, *tree_bad, *node_good, *node_bad;

  double time_good = 0.0, time_bad = 0.0;
  clock_t begin, end;

  FILE *file = fopen("Keys.txt", "r");
  if (!file) {
    return 1;
  }

  for (int i = 0; fgets(words[i], MaxKeyLenght, file) && i < MaxKeys; i++) {
    words[i][strlen(words[i]) - 2] = '\0';
  }
  fclose(file);

  printf("#\tgood\t\tbad\t\t\tkey_good\t\t\tkey_bad\n");
  tree_good = bstree_create(words[0], 0);
  tree_bad = bstree_create(words[0], 0);

  for (int i = 1; i < MaxKeys; i++) {
    bstree_add(tree_good, words[i], i);
    bstree_add_right(tree_bad, words[i], i);
    if ((i + 1) % 10000 == 0) {
      // bstree
      begin = clock();
      node_good = bstree_max(tree_good);
      end = clock();
      time_good = (double)(end - begin) / CLOCKS_PER_SEC;

      // hastab
      begin = clock();
      node_bad = bstree_max(tree_bad);
      end = clock();
      time_bad = (double)(end - begin) / CLOCKS_PER_SEC;

      printf("%d\t%f\t%f\t%30.30s \t%30.30s\n",i+1, time_good, time_bad,
             node_good->key, node_bad->key);
    }
  }
  bstree_free(tree_good);
  bstree_free(tree_bad);
  return 0;
}