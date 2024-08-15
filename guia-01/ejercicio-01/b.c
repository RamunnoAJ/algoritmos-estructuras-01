#include <stdio.h>
int main() {
  int resultado = 0, a = 3, b = 1, c;
  resultado++;
  resultado /= a;
  resultado *= b;
  c = resultado && a;
  if (a == b)
    resultado = ++a;
  else
    resultado = 'a';
  a = b = resultado-- + c;

  printf("resultado: %d, a: %d, b: %d, c: %d\n", resultado, a, b, c);

  return 0;
}
