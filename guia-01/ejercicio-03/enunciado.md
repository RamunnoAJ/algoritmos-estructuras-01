# Dado el siguiente programa C:

```c
void main() {
  int x, cuad, cubo;
  printf("X\t cuad(X)\t cubo(X)\n");
  for (x = cuad = cubo = 0; x <= 10; x++, cuad = x * x, cubo = x * x * x)
    printf("%4d\t %4d\t %4d\n", x, cuad, cubo);
}
```

Escribir el programa anterior usando la proposición while y la proposición do while

### Solución

Utilizando while:

```c
#include <stdio.h>
int main() {
  int x, cuad, cubo;
  printf("X\t cuad(X)\t cubo(X)\n");

  x = 0;
  cuad = 0;
  cubo = 0;
  while (x <= 10) {
    printf("%4d\t %4d\t %4d\n", x, cuad, cubo);
    x++;
    cuad = x * x;
    cubo = cuad * x;
  }

  return 0;
}
```

Utilizando do while:

```c
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
```
