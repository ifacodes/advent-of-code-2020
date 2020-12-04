#include <stdio.h>
#include <stdlib.h>

char* loadfile(char* input) {
  int length;
  char* buffer;
  FILE* file = fopen(input, "r");
  if (!file) {
    printf("File could not be found");
    exit(-1);
  }
  // get length of file
  fseek(file, 0L, SEEK_END);
  length = ftell(file);
  rewind(file);

  // allocate file size to buffer
  buffer = calloc(length + 1, sizeof(char));

  // read file into buffer
  fread(buffer, sizeof(char), length, file);

  buffer += '\0';

  return buffer;
}