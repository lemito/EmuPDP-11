#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void do_halt() {
  INFO_("THE END!!!\n", NULL);
  exit(0);
}

void do_add() {}
void do_mov() {}
void do_nothing() {}

Command cmds[] = {{0170000, 0060000, "add", do_add},
                  {0170000, 0010000, "mov", do_mov},
                  {0177777, 0000000, "halt", do_halt},
                  {0000000, 0000000, "unknow", do_nothing},
                  {0000000, 0000000, "TERMINATE", do_nothing}};

void run() {
  pc = 01000;

  word work_word;
  while (1) {
    work_word = w_read(pc);
    printf("%06o: %06o\n", pc, work_word);
    pc += 2;
    for (int i = 0; strcmp(cmds[i].name, "TERMINATE") != 0; i++) {
      if ((work_word & cmds[i].mask) == cmds[i].opcode) {
        cmds[i].do_command();
      }
    }
  }
}