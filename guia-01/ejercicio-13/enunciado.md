# Reescriba el siguiente programa para que ejecute correctamente.

```c
void main() {
 int x;
 scanf ("ld", x);
 if (x = 1)
 Printf('El valor es igual a uno')
 else
 Printf('El valor', X, 'es distinto de 1');
}
```

### Solución

```c
#include <stdio.h>

int main() {
 int x;
 scanf ("%d", &x);
 if (x == 1)
    printf("El valor es igual a uno");
 else
    printf("El valor %d, es distinto de 1", x);

 return 0;
}
```
