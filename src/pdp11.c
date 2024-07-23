#include "pdp.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  //  // mem_test();
  //  load_data();
  //
  //  mem_dump(0x40, 20);
  //  printf("\n");
  //  mem_dump(0x200, 0x26);
  set_log_level(INFO);

  int x, y;
  scanf("%d%d", &x, &y);

  log(INFO, "%d + %d = %d\n", x, y, x + y - 1);
  log(ERROR, "Oops, %d+%d=%d, not %d\n", x, y, x + y, x + y - 1);
  log(TRACE, "Эту надпись не должны видеть\n");

  int old_log_level = set_log_level(TRACE);

  log(TRACE, "Visible text\n");
  log(DEBUG, "Debug info\n");

  set_log_level(old_log_level);

  log(INFO, "The end!\n");
  log(TRACE, "No code after return\n");
  return 0;
}