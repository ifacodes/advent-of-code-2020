#include <inttypes.h>
#include <nmmintrin.h>
#include <stdio.h>
#include <stdlib.h>

// linked list element
typedef struct element {
  uint32_t value;
  struct element *next;
} element;

uint32_t hash(uint32_t a) {
  a = (a + 0x7ed55d16) + (a << 12);
  a = (a ^ 0xc761c23c) ^ (a >> 19);
  a = (a + 0x165667b1) + (a << 5);
  a = (a + 0xd3a2646c) ^ (a << 9);
  a = (a + 0xfd7046c5) + (a << 3);
  a = (a ^ 0xb55a4f09) ^ (a >> 16);
  return a % 1024;
}

void hashset_free(element *set[]) {
  for (int i = 0; i < 1024; i++) {
    element *tmp;
    while (set[i]) {
      tmp = set[i];
      set[i] = set[i]->next;
      free(tmp);
    }
  }
  free(set);
}

//
uint32_t hashset_add(element *set[], uint32_t item) {
  // TODO - add item to linked list if hash already has a value
  if (!item) {
    return 1;
  }
  uint32_t h = hash(item);
  if (h >= 1048576) {
    return 1;
  }

  if (!set[h]) {
    set[h] = calloc(1, sizeof(element));
    set[h]->value = item;
    return 0;
  }

  element *current = set[h];

  while (current->next) {
    current = current->next;
  }

  current->next = calloc(1, sizeof(element));
  current->next->value = item;

  return 0;
}

int hashset_find(element *set[], uint32_t query) {
  uint32_t query_hash = hash(query);

  if (!set[query_hash]) {
    return 1;
  }

  element *current = set[query_hash];

  while (current) {
    if (set[query_hash]->value == query) {
      return query;
    }
    current = current->next;
  }

  if (set[query_hash]->value != query) {
    return 1;
  }

  return query;
}