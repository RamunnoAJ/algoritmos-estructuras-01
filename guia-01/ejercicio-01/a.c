#include <stdio.h>

int main() {
  float x = 3.5, y = 4.7, z, w, q;
  int verdadero, falso, n = 0, nose;
  w = (int)(x + y);
  q = (int)x + (int)y;
  verdadero = 10 > x;
  falso = y < x;
  nose = sizeof(int) == sizeof n;
  z = x * (y = n++), x = 'A' + n;

  printf("x: %f, y: %f, z: %f, w: %f, q: %f\n", x, y, z, w, q);
  printf("verdadero: %d, falso: %d, n: %d, nose: %d\n", verdadero, falso, n,
         nose);

  return 0;
}
