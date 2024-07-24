#include "pdp.h"
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
void load_file(char* filename){
  FILE* input_file = fopen(filename, "r");

  if (input_file == NULL){
    perror(filename);
    exit(errno);
  }

  address start;
  int N;
  byte input;

  while (fscanf(input_file, "%hx %x", &start, &N) == 2) {
    for (int i = 0; i < N; ++i) {
      fscanf(input_file, "%hhx", &input);
      b_write(start + i, input);
    }
  }
}