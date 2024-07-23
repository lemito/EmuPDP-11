#ifndef EMUPDP_11_SRC_PDP_H_
#define EMUPDP_11_SRC_PDP_H_

#define _unused __attribute__((unused))

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
#define REGSIZE 8

typedef unsigned char byte;  // 1 байт
typedef unsigned short word; // 2 байта
typedef word Adress;         // адрес - также 2 байт

typedef struct {
  word mask;
  word opcode;
  char * name;
  void (*do_command)(void);
} Command;

/**
 * pc - program counter (запоминает, какую программу мы выполняем)
 */
#define pc reg[7]

extern  word reg[REGSIZE];

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

enum LOG_LEVELS set_log_level(enum LOG_LEVELS level);

void logger_impl(enum LOG_LEVELS level, const char *fmt, ...);

#define INFO_(text, ...) logger_impl(INFO, text, __VA_ARGS__)

void run();

void load_file(char* filename);



#endif // EMUPDP_11_SRC_PDP_H_
