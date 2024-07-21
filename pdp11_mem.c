#include <assert.h>
#include <stdio.h>

#define MEMSIZE (64 * 1024)

typedef unsigned char byte;
typedef unsigned short word;
typedef word Adress;

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

int main() {
  Adress a = 3;
  byte b1 = 0x0b, b0 = 0x0a;
  word w = 0x0b0a;
  b_write(a, b0);
  b_write(a + 1, b1);
  word wres = w_read(a);
  printf("%04hx=%02hhx%02hhx\n", wres, b1, b0);
  assert(wres == w);
  return 0;
}

void b_write(Adress adr, byte b) { mem[adr] = b; }

byte b_read(Adress adr) { return mem[adr]; }

void w_write(Adress adr, word w) {}

word w_read(Adress adr) {
  word res = 0;

  return 0;
}