#include <stdio.h>
#include <stdlib.h>

char* loadfile(char* input) {
  FILE* file = fopen(input, "r");
  if (!file) {
    printf("File could not be found");
    exit(-1);
  }

  fseek(file, 0L, SEEK_END);
  int length = ftell(file);
  rewind(file);

  // allocate length + 1 to make result null terminated
  char* buffer = calloc(length + 1, sizeof(char));
  fread(buffer, sizeof(char), length, file);

  return buffer;
}