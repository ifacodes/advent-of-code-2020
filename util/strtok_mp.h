#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* strtok_mp(char* input, const char* delimiter, char** save_ptr) {
  if (input) {
    *save_ptr = input;
  }
  if (!*save_ptr) {
    return '\0';
  }
  char* substring2 = strstr(*save_ptr, "\n\n");
  if (!substring2) {
    return NULL;
  }
  char* tmp = (char*)calloc((size_t)(substring2 - *save_ptr), sizeof(char));
  strncpy(tmp, *save_ptr, (size_t)(substring2 - *save_ptr));
  *save_ptr = substring2 + 2;

  return tmp;
}