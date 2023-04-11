#pragma once

#define FG_RED "\033[31m"
#define FG_PURPLE "\033[35m"
#define FG_CYAN "\033[36m"
#define FG_GREEN "\033[32m"
#define FG_YELLOW "\033[33m"
#define FG_WHITE "\033[0m"

enum{
  Hashtab_Size = 200000,
  Max_Keys = 200000,
  Max_Key_Length = 40
};

int getrand(int min, int max);
void print_cap(uint32_t size, char word);
void print_table(uint32_t size, char *title);
double wtime();

