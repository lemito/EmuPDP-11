#include <assert.h>
#include <stdio.h>

#define PRINT_BYTE(byte) printf("%02hhx", byte);
#define PRINT_WORD(word) printf("%04hx", word);


#define isDebug 0
#define DEBUG_PRINT(print) if(isDebug == 1) {print};

#define ERROR 0
#define INFO 1
#define TRACE 2
#define DEBUG 3

#define address Adress

#define MEMSIZE (64 * 1024)

typedef unsigned char byte;  // 1 байт
typedef unsigned short word; // 2 байта
typedef word Adress;         // адрес - также 2 байт

byte mem[MEMSIZE];

// void log(int log_level, const char *fmt, ...) {}

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
      b_write(start+i, input);
    }
  }
}


void mem_dump(address adr, int size) {
  for (int i = 0; i < size; i+=2) {
    address new_adr = adr + i;
    word res = w_read(new_adr);
    DEBUG_PRINT(printf("res="); PRINT_WORD(res) printf("\n");)
    printf("%06o: %06o %04x\n", new_adr, res, res);
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
  printf("%lu", sizeof(word) / sizeof(byte));
  Adress a = 3;
  byte b1 = 0x0b, b0 = 0x0a;
  word w = 0x0b0a;
  b_write(a, b0);
  b_write(a + 1, b1);
  word wres = w_read(a);
  printf("%04hx=%02hhx%02hhx\n", wres, b1, b0);
  assert(wres == w);
  w_write(6, w);
  word ww = w_read(6);
  assert(ww == w);
  b_write(10, 0x54);
  PRINT_BYTE(b_read(10));
}

int main(int argc, char *argv[]) {
  // mem_test();
  load_data();

  mem_dump(0x40, 20);
  printf("\n");
  mem_dump(0x200, 0x26);
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