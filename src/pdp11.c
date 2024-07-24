#include "pdp.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  load_file(argv[argc - 1]);
  run();
  return 0;
}