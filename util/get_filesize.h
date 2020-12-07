
#include <stdio.h>
#include <stdlib.h>

size_t get_filesize(FILE* file) {
  if (!file) {
    printf("File could not be found");
    return -1;
  }

  fseek(file, 0L, SEEK_END);
  size_t length = ftell(file);
  rewind(file);
  return length + 1;
}