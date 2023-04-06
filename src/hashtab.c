#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../libraries/hashtab.h"
#include "../libraries/header.h"

// KRHash
unsigned int hashtab_hash(char *key) {
  unsigned int h = 0, hash_mul = 31;
  while (*key)
    h = h * hash_mul + (unsigned int)*key++;
  return h % Hashtab_Size;
}

// DJBHash
unsigned int JenkinsHash(char *s) {
  unsigned int h = 0;
  while (*s) {
    h += (unsigned int)*s++;
    h += (h << 10);
    h ^= (h >> 6);
  }
  h += (h << 3);
  h ^= (h >> 11);
  h += (h << 15);
  return h % Hashtab_Size;
}

void hashtab_init(struct listnode **hashtab) {
  int i;
  for (i = 0; i < Hashtab_Size; i++)
    hashtab[i] = NULL;
}
void hashtab_add(struct listnode **hashtab, char *key, int value) {
  struct listnode *node;

  int index = hashtab_hash(key);
  node = (struct listnode *)malloc(sizeof(*node));

  if (node != NULL) {
    node->key = key;
    node->value = value;
    node->next = hashtab[index];
    hashtab[index] = node;
  }
}

void hashtab_add_DJB(struct listnode **hashtab, char *key, int value) {
  struct listnode *node;

  int index = JenkinsHash(key);
  node = (struct listnode *)malloc(sizeof(*node));

  if (node != NULL) {
    node->key = key;
    node->value = value;
    node->next = hashtab[index];
    hashtab[index] = node;
  }
}

struct listnode *hashtab_lookup_DJB(struct listnode **hashtab, char *key) {
  struct listnode *node;

  int index = JenkinsHash(key);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key))
      return node;
  }
  return NULL;
}

struct listnode *hashtab_lookup(struct listnode **hashtab, char *key) {
  struct listnode *node;

  int index = hashtab_hash(key);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key))
      return node;
  }
  return NULL;
}
void hashtab_delete(struct listnode **hashtab, char *key) {
  struct listnode *node, *prev = NULL;
  int index = hashtab_hash(key);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key)) {
      if (prev == NULL)
        hashtab[index] = node->next;
      else
        prev->next = node->next;
      free(node);
      return;
    }
    prev = node;
  }
}

int get_collisions(struct listnode **hashtab){
  int count = 0;
  for(int i = 0; i < Hashtab_Size; i++){
    for(struct listnode *j = !hashtab[i] ? NULL : hashtab[i]->next; j != NULL; j = j->next){
      count += 1;
    }
  }
  return count;
}

void free_table(struct listnode **hashtab) {
  for (int i = 0; i < Hashtab_Size; i++) {
    struct listnode *current = hashtab[i];
    while (current != NULL) {
      struct listnode *temp = current;
      current = current->next;
      free(temp);
    }
  }
}