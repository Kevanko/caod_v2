#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> // for sleep

#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"
#include "../libraries/header.h"

char words_bad[Max_Keys][Max_Key_Length];
char words_good[Max_Keys][Max_Key_Length];

int main() {

  struct bstree *tree_good, *tree_bad, *node_good, *node_bad;
  double time_good = 0.0, time_bad = 0.0;
  clock_t begin, end;

  //---------Read-Bad---------//
  FILE *file = fopen("keys2.txt", "r");
  for (int i = 0; i < Max_Keys; i++) {
    fgets(words_bad[i], Max_Key_Length, file);
    words_bad[i][strlen(words_bad[i]) - 1] = '\0';
  }
  fclose(file);
  //---------Read-Bad---------//

  //---------Read-Good---------//
  file = fopen("keys.txt", "r");
  for (int i = 0; i < Max_Keys; i++) {
    fgets(words_good[i], Max_Key_Length, file);
    words_good[i][strlen(words_good[i]) - 2] = '\0';
  }
  fclose(file);
  //---------Read-Good---------//
  printf(FG_CYAN "\t\t\tExperiment #5 --> Bstree_max (Bad) vs Bstree_max (Good) "
                 "<--\n" FG_WHITE);

  print_cap(121, '-');
  printf(FG_YELLOW "#\t" FG_CYAN "|  " FG_GREEN "time_good\t" FG_CYAN
                   "| " FG_RED " time_bad\t" FG_CYAN "|\t\t" FG_GREEN
                   "key_good\t\t" FG_CYAN "|\t\t" FG_RED "key_bad\t\t\t" FG_CYAN
                   "|\n" FG_WHITE);
  print_cap(121, '-');

  tree_good = bstree_create(words_good[0], 0);
  tree_bad = bstree_create(words_bad[0], 0);

  for (int i = 1; i < Max_Keys; i++) {
    bstree_add(tree_good, words_good[i], i);
    bstree_add(tree_bad, words_bad[i], i);
    if ((i + 1) % 10000 == 0) {

      //---------Good---------//
      begin = clock();
      node_good = bstree_max(tree_good);
      end = clock();
      time_good = (double)(end - begin) / CLOCKS_PER_SEC;
      //---------Good---------//

      //---------Bad---------//
      begin = clock();
      node_bad = bstree_max(tree_bad);
      end = clock();
      time_bad = (double)(end - begin) / CLOCKS_PER_SEC;
      //---------Bad---------//

      printf(FG_YELLOW "%d\t" FG_CYAN "| " FG_GREEN "%f\t" FG_CYAN "| " FG_RED
                       "%f\t" FG_CYAN "|" FG_GREEN "%35.35s\t" FG_CYAN
                       "|" FG_RED " %35.35s\t" FG_CYAN "|\n" FG_WHITE,
             i + 1, time_good, time_bad, node_good->key, node_bad->key);
    }
  }
  print_cap(121, '-');
  bstree_free(tree_good);
  bstree_free(tree_bad);
  return 0;
}