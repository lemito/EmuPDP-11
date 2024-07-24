#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reg_dump() {
  for (int i = 0; i < REGSIZE; ++i) {
    printf("r%d: %04o ", i, reg[i]);    
  }
}

void do_halt() {
  reg_dump();
  INFO_("THE END!!!\n", NULL);
  exit(0);
}

void do_add() { INFO_("do_add\n", NULL); }
void do_mov() { INFO_("do_mov\n", NULL); }
void do_nothing() { INFO_("do_nothing\n", NULL); }

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
    printf("%06o: %06o ", pc, work_word);
    pc += 2;
    for (int i = 0; strcmp(cmds[i].name, "TERMINATE") != 0; i++) {
      if ((work_word & cmds[i].mask) == cmds[i].opcode) {
        cmds[i].do_command();
      }
    }
  }
}