#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>   // for clock_t, clock(), CLOCKS_PER_SEC
#include <unistd.h> // for sleep

#include "../libraries/bstree.h"
#include "../libraries/hashtab.h"
#include "../libraries/header.h"

struct listnode *hashtab_KR[Hashtab_Size];
struct listnode *hashtab_DJB[Hashtab_Size];
char words[Max_Keys][Max_Key_Length];

int main() {

  struct listnode *node_KR, *node_DJB;
  double time_KR = 0.0, time_DJB = 0.0;
  ;
  clock_t begin, end;

  //---------Read-Words---------//
  FILE *file = fopen("keys.txt", "r");
  for (int i = 0; i < Max_Keys; i++) {
    fgets(words[i], Max_Key_Length, file);
    words[i][strlen(words[i]) - 2] = '\0';
  }
  fclose(file);
  //---------Read-Words---------//

  printf(FG_CYAN "\tExperiment #6 --> Hashtab_Lookup_DJB vs Hashtab_Lookup_KP"
                 "<--\n" FG_WHITE);

  print_cap(73, '-');
  printf(FG_YELLOW "#\t" FG_CYAN "|  " FG_GREEN "time_DJB\t" FG_CYAN
                   "| " FG_RED " time_KR\t" FG_CYAN "|  " FG_GREEN
                   "DJB_Collis\t" FG_CYAN "|  " FG_RED "KP_Collis\t" FG_CYAN
                   "|\n" FG_WHITE);
  print_cap(73, '-');

  hashtab_init(hashtab_KR);
  hashtab_init(hashtab_DJB);

  for (int i = 0; i < Max_Keys; i++) {
    hashtab_add(hashtab_KR, words[i], i);
    hashtab_add_DJB(hashtab_DJB, words[i], i);

    if ((i + 1) % 10000 == 0) {
      char *word = words[getrand(0, i)];
      //---------KR---------//
      begin = clock();
      node_KR = hashtab_lookup(hashtab_KR, word);
      end = clock();
      time_KR = (double)(end - begin) / CLOCKS_PER_SEC;
      //---------JR---------//

      //---------DJB---------//
      begin = clock();
      node_DJB = hashtab_lookup_DJB(hashtab_DJB, word);
      end = clock();
      time_DJB = (double)(end - begin) / CLOCKS_PER_SEC;
      //---------DJB---------//
      int collisions_KP = get_collisions(hashtab_KR);
      int collisions_DJB = get_collisions(hashtab_DJB);

      printf(FG_YELLOW "%d\t" FG_CYAN "| " FG_GREEN "%f\t" FG_CYAN "| " FG_RED
                       "%f\t" FG_CYAN "|" FG_GREEN " %d\t\t" FG_CYAN
                       "|" FG_RED " %d\t\t" FG_CYAN "|\n" FG_WHITE,
             i + 1, time_DJB, time_KR, collisions_DJB, collisions_KP);
    }
  }
  print_cap(73, '-');
  free_table(hashtab_KR);
  free_table(hashtab_DJB);
  return 0;
}