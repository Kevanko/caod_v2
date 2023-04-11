#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> // for sleep

#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"
#include "../libraries/header.h"

struct listnode *hashtab[Hashtab_Size];
char words[Max_Keys][Max_Key_Length];

int main() {

  struct bstree *tree, *node_tree;
  struct listnode *hash, *node_hash;
  double time_tree = 0.0, time_hash = 0.0;
  clock_t begin, end;

  //---------Read-Words---------//
  FILE *file = fopen("keys.txt", "r");
  for (int i = 0; i < Max_Keys; i++) {
    fgets(words[i], Max_Key_Length, file);
    words[i][strlen(words[i]) - 2] = '\0';
  }
  fclose(file);
  //---------Read-Words---------//

  printf(FG_CYAN "\t\t\tExperiment #1 --> Bstree_Lookup vs Hashtab_Lookup <--"
                 "<--\n" FG_WHITE);

  print_cap(121, '-');
  printf(FG_YELLOW "#\t" FG_CYAN "|  " FG_GREEN "time_hash\t" FG_CYAN
                   "| " FG_RED " time_tree\t" FG_CYAN "|\t\t" FG_GREEN
                   "key_hash\t\t" FG_CYAN "|\t\t" FG_RED "key_tree\t\t" FG_CYAN
                   "|\n" FG_WHITE);
  print_cap(121, '-');

  hashtab_init(hashtab);
  hashtab_add(hashtab, words[0], 0);
  tree = bstree_create(words[0], 0);

  for (int i = 1; i < Max_Keys; i++) {
    bstree_add(tree, words[i], i);
    hashtab_add(hashtab, words[i], i);

    if ((i + 1) % 10000 == 0) {
      char *rand_key = words[getrand(0, i)];
      //---------Good---------//
      begin = clock();
      node_tree = bstree_lookup(tree, rand_key);
      end = clock();
      time_tree = (double)(end - begin) / CLOCKS_PER_SEC;
      //---------Good---------//

      //---------Bad---------//
      begin = clock();
      node_hash = hashtab_lookup(hashtab, rand_key);
      end = clock();
      time_hash = (double)(end - begin) / CLOCKS_PER_SEC;
      //---------Bad---------//

      printf(FG_YELLOW "%d\t" FG_CYAN "| " FG_GREEN "%f\t" FG_CYAN "| " FG_RED
                       "%f\t" FG_CYAN "|" FG_GREEN "%35.35s\t" FG_CYAN
                       "|" FG_RED " %35.35s\t" FG_CYAN "|\n" FG_WHITE,
             i + 1, time_hash, time_tree, node_hash->key, node_tree->key);
    }
  }
  print_cap(121, '-');
  bstree_free(tree);
  free_table(hashtab);
  return 0;
}