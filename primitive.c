#include <stdio.h>

#define NUM_TO_REG(args) (args - 5)

void print_regs(int *regs) {
  for (int i = 0; i < 4; ++i) {
    printf("%d ", regs[i]);
  }
  printf("\n");
}

int main() {
  /**
   * A -> 0
   * B -> 1
   * C -> 2
   * D -> 3
   */
  int proc[4] = {0, 0, 0, 0};
  int cmd;
  int arg1 = 0;
  int arg2 = 0;

  while (scanf("%d", &cmd) == 1) {
    switch (cmd) {
    case 0:
      return 0;
    case 1:
      scanf("%d %d", &arg1, &arg2);
      proc[NUM_TO_REG(arg1)] =
          (proc[NUM_TO_REG(arg1)] + proc[NUM_TO_REG(arg2)]) & 0xFF;
      break;
    case 2:
      scanf("%d %d", &arg1, &arg2);
      proc[NUM_TO_REG(arg1)] =
          (proc[NUM_TO_REG(arg1)] - proc[NUM_TO_REG(arg2)]) & 0xFF;
      break;
    case 3:
      scanf("%d %d", &arg1, &arg2);
      proc[NUM_TO_REG(arg1)] = arg2 & 0xFF;
      break;
    case 4:
      print_regs(proc);
      break;
    }
  }
  return 0;
}

// ==== решение со степика (совсем забыл про указатели на функцию...) ===
/*
#include <stdio.h>
#include <stdlib.h>

// from register number to r[] index
#define n(rn) (rn-5)
unsigned char r[4];

void stop()
{
  exit(0);
}
void add()
{
  int r1, r2;
  scanf("%d%d", &r1, &r2);
  int rn1 = n(r1);
  int rn2 = n(r2);

  r[rn1] = r[rn1] + r[rn2];
}
void sub()
{
  int r1, r2;
  scanf("%d%d", &r1, &r2);
  int rn1 = n(r1);
  int rn2 = n(r2);

  r[rn1] = r[rn1] - r[rn2];
}
void mov()
{
  int r1, x;
  scanf("%d%d", &r1, &x);

  r[n(r1)] = x;
}
void print()
{
  int i;
  for (i = 0; i < sizeof(r)/sizeof(r[0]); i++)
    printf("%d ", r[i]);
  printf("\n");
}
int main ()
{
  int x;
  typedef void (*Func)();
  Func func[] = {stop, add, sub, mov, print};
  while(1)
  {
    scanf("%d", &x);
    func[x]();
  }
  return 0;
}
*/