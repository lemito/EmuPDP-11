#include "pdp.h"
#include <stdio.h>

void run(){
  pc = 01000;

  word work_word;
  while(1){
    work_word = w_read(pc);
    printf("%06o: %06o", pc, work_word);
    pc += 2;
  }
}