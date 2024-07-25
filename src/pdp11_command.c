#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>

Arg ss, dd;

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

void do_add() {
  w_write(dd.adr, ss.value + dd.value);
//   INFO_("do_add\n", NULL);
}
void do_mov() {
  w_write(dd.adr, ss.value);
//   INFO_("do_mov\n", NULL);
}
void do_nothing() { INFO_("do_nothing\n", NULL); }

Command cmds[] = {{0170000, 0060000, "add", do_add},
                  {0170000, 0010000, "mov", do_mov},
                  {0177777, 0000000, "halt", do_halt},
                  {0000000, 0000000, "unknow", do_nothing},
                  {0000000, 0000000, "TERMINATE", do_nothing}};

Command parse_cmd(word work_word) {
  Command res;
  for (int i = 0;; i++) {
    if ((work_word & cmds[i].mask) == cmds[i].opcode) {
      res = cmds[i];
      break;
    }
  }
  ss = get_mr(work_word >> 6);
  dd = get_mr(work_word);
  return res;
}