#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/time.h>

#include "../libraries/header.h"

int getrand(int min, int max)
{
return (double)rand() / (RAND_MAX + 1.0) * (max - min) + min;
}

double wtime()
{
struct timeval t;
gettimeofday(&t, NULL);
return (double)t.tv_sec + (double)t.tv_usec * 1E-6;
}

void print_cap(uint32_t size, char word) {
  fprintf(stdout, FG_CYAN);
  for (uint32_t i = 0; i < size; i++) {
    fprintf(stdout, "%c", word);
  }
  fprintf(stdout, FG_WHITE "\n");
}
