#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#define PRINT_BYTE(byte) printf("%02hhx", byte);
#define PRINT_WORD(word) printf("%04hx", word);

#define isDebug 0
#define DEBUG_PRINT(print)                                                     \
  if (isDebug == 1) {                                                          \
    print                                                                      \
  };

enum LOG_LEVELS { ERROR, INFO, TRACE, DEBUG };

#define address Adress

#define MEMSIZE (64 * 1024)

typedef unsigned char byte;  // 1 байт
typedef unsigned short word; // 2 байта
typedef word Adress;         // адрес - также 2 байт

byte mem[MEMSIZE];

/**
 * запись байта по адресу
 * @param adr
 * @param b
 */
void b_write(Adress adr, byte b);
/**
 * чтение байта по адресу
 * @param adr
 * @return
 */
byte b_read(Adress adr);
/**
 * запись слова по адресу
 * @param adr
 * @param w
 */
void w_write(Adress adr, word w);
/**
 * чтение слова по адресу
 * @param adr
 * @return
 */
word w_read(Adress adr);

void load_data() {
  address start;
  int N;
  byte input;

  while (fscanf(stdin, "%hx %x", &start, &N) == 2) {
    for (int i = 0; i < N; ++i) {
      fscanf(stdin, "%hhx", &input);
      b_write(start + i, input);
    }
  }
}

void mem_dump(address adr, int size) {
  for (int i = 0; i < size; i += 2) {
    address new_adr = adr + i;
    word res = w_read(new_adr);
    DEBUG_PRINT(printf("res="); PRINT_WORD(res) printf("\n");)
    printf("%06o: %06o %04x\n", new_adr, res, res);
  }
}

// значение по умолчанию
static enum LOG_LEVELS log_level = INFO;

enum LOG_LEVELS set_log_level(enum LOG_LEVELS level) {
  enum LOG_LEVELS res = log_level;
  log_level = level;
  return res;
};

void log(enum LOG_LEVELS level, const char *fmt, ...) {
  if (level <= log_level) {
    va_list arg_list;
    va_start(arg_list, fmt);
    vprintf(fmt, arg_list);
    va_end(arg_list);
  }
}

/**
 * Адреса:
 * | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *                                                   |       |
 * Картинка-имитация памяти
 * |---------|                          | №ячейки (адрес)
 * | 0x0a    | -> байт                      0
 * |---------|                              -
 * | 0x0b    | -> байт                      1
 * |---------|                              -
 * | 0x0a    | -> |                         2
 * |---------|    | => слово (2 байт)       -
 * | 0x0b    | -> |                         3
 * |---------|
 */
void mem_test() {
  Adress a = 3;
  byte b1 = 0x0b, b0 = 0x0a;
  word w = 0x0b0a;
  b_write(a, b0);
  b_write(a + 1, b1);
  word wres = w_read(a);
  assert(wres == w);
  w_write(6, w);
  word ww = w_read(6);
  assert(ww == w);
  b_write(10, 0x54);
  PRINT_BYTE(b_read(10));
}

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

void b_write(Adress adr, byte b) { mem[adr] = b; }

byte b_read(Adress adr) { return mem[adr]; }

void w_write(Adress adr, word w) {
  byte b1 = w >> 8;
  mem[adr + 1] = b1;
  byte b0 = w & 0xFF;
  mem[adr] = b0;
}

word w_read(Adress adr) {
  word res = ((word)mem[adr + 1]) << 8;
  res = res | mem[adr];
  return res;
}