#include "pdp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  INFO_("do_add\n", NULL);
}
void do_mov() {
  w_write(dd.adr, ss.value);
  INFO_("do_mov\n", NULL);
}
void do_nothing() { INFO_("do_nothing\n", NULL); }

Arg get_mr(word work_word) {
  Arg res;
  int r = work_word & 7;        // номер регистра
  int m = (work_word >> 3) & 7; // номер моды
  /**
   * **Мода 0** : Адрес - номер регистра, значение - значение регистра, тут же
печатаем трассировку `R1`
   * **Мода 1** : Адрес - лежит в регистре, значение читаем в памяти по этому
адресу, тут же печатаем трассировку `(R1)`
  * **Мода 2** : То же, что мода 1, но +2 к значению регистра в конце.
   */
  switch (m) {
    // мода 0, R1
  case 0:
    res.adr = r;
    res.value = reg[r];
    INFO_("R%d ", r);
    break;
  // мода 1, (R1)
  case 1:
    res.adr = reg[r];
    res.value = w_read(res.adr);
    INFO_("(R%d) ", r);
    break;
  // мода 2, (R1)+ или #3
  case 2:
    res.adr = reg[r];
    res.value = w_read(res.adr);
    reg[r] += 2;
    if (r == 7)
      INFO_("#%o ", res.value);
    else
      INFO_("(R%d)+ ", r);
    break;

  }
  return res;
}

word read_cmd() {
  word work_word = w_read(pc);
  printf("%06o: %06o ", pc, work_word);
  pc += 2;

  return work_word;
}

Command cmds[] = {{0170000, 0060000, "add", do_add},
                  {0170000, 0010000, "mov", do_mov},
                  {0177777, 0000000, "halt", do_halt},
                  {0000000, 0000000, "unknow", do_nothing},
                  {0000000, 0000000, "TERMINATE", do_nothing}};


Command parse_cmd(word work_word) {
  Command res;
  for (int i = 0; ; i++) {
    if ((work_word & cmds[i].mask) == cmds[i].opcode) {
      res = cmds[i];
      break;
    }
  }
  ss = get_mr(work_word >> 6);
  dd = get_mr(work_word);
  return res;
}

// тест, что мы правильно определяем команды mov, add, halt
void test_parse_mov()
{
    // trace(TRACE, __FUNCTION__);
    Command cmd = parse_cmd(0017654);
    assert(strcmp(cmd.name, "mov") == 0);
    // trace(TRACE, " ... OK\n");
}
// тест, что мы разобрали правильно аргументы ss и dd в mov R5, R3
void test_mode0()
{
    // trace(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
//    cmd.do_command();
    assert(strcmp(cmd.name, "mov") == 0);
    assert(ss.value == 34);
    assert(ss.adr == 5);
    assert(dd.value == 12);
    assert(dd.adr == 3);
    // trace(TRACE, " ... OK\n");
}
// тест, что mov и мода 0 работают верно в mov R5, R3
 void test_mov()
{
    // trace(TRACE, __FUNCTION__);
    reg[3] = 12;    // dd
    reg[5] = 34;    // ss
    Command cmd = parse_cmd(0010503);
    cmd.do_command();
    assert(reg[3] == 34);
    assert(reg[5] == 34);
    // trace(TRACE, " ... OK\n");
}

void run() {
  pc = 01000;

  word work_word;
  Command cmd;
  // while (1) {
  //   work_word = w_read(pc);
  //   printf("%06o: %06o ", pc, work_word);
  //   pc += 2;
  //   cmd = parse_cmd(work_word);
  //   cmd.do_command();
  // }
//  test_parse_mov();
//  test_mode0();
  test_mov();
}