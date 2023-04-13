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

/*/---------FNVHash---------/*/
unsigned int FNVHash(char* s) {
	const unsigned int fnv_prime = 0x811C9DC5;
	unsigned int hash = 0;
	unsigned int i = 0;

	for (i = 0; i < strlen(s); s++, i++)
	{
		hash *= fnv_prime;
		hash ^= (*s);
	}

	return hash % Hashtab_Size;
}

/*/---------AddHash---------/*/
unsigned int AddHash(char *s) {
  unsigned int h = 0;
  while (*s)
    h += (unsigned int)*s++;
  return h % Hashtab_Size;
}

/*/---------ELFHash---------/*/
unsigned int ELFHash(char *s) {
  unsigned int h = 0, g;
  while (*s) {
    h = (h << 4) + (unsigned int)*s++;
    g = h & 0xF0000000L;
    if (g)
      h ^= g >> 24;
    h &= ~g;
  }
  return h % Hashtab_Size;
}

/*/---------Jenkins_hash---------/*/
unsigned int Jenkins_hash(char *s) {
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
/*/---------DJBHash---------/*/
unsigned long DJB_hash(char *str) {
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash % Hashtab_Size;
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
/*/-------------------------------DJB---------------------------------------/*/
void hashtab_add_DJB(struct listnode **hashtab, char *key, int value) {
  struct listnode *node;

  int index = DJB_hash(key);
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

  int index = DJB_hash(key);
  for (node = hashtab[index]; node != NULL; node = node->next) {
    if (0 == strcmp(node->key, key))
      return node;
  }
  return NULL;
}
/*/-------------------------------DJB---------------------------------------/*/

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

int get_collisions(struct listnode **hashtab) {
  int count = 0;
  for (int i = 0; i < Hashtab_Size; i++) {
    for (struct listnode *j = !hashtab[i] ? NULL : hashtab[i]->next; j != NULL;
         j = j->next) {
      count += 1;
    }
  }
  return count;
}

int get_collisions_v2(struct listnode **hashtab, int all) {
  int count = 0;
  for (int i = 0; i < Hashtab_Size; i++) {
    if (hashtab[i] != NULL) {
      count += 1;
    }
  }
  return all - count;
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
