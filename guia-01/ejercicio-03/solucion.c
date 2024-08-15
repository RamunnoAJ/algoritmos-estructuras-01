#include <stdio.h>
int main() {
  int x, cuad, cubo;
  printf("X\t cuad(X)\t cubo(X)\n");

  x = 0;
  cuad = 0;
  cubo = 0;

  do {
    printf("%4d\t %4d\t %4d\n", x, cuad, cubo);
    x++;
    cuad = x * x;
    cubo = cuad * x;

  } while (x <= 10);

  return 0;
}
