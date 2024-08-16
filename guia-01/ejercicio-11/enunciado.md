# Ingresar tres números enteros e indicar si son consecutivos entre sí.

```c
#include <stdio.h>

int main() {
    int a, b, c;
    printf("Ingrese tres numeros enteros\n");
    while(scanf("%d %d %d", &a, &b, &c) == 3) {
        if (c == b + 1 && b == a + 1) {
            printf("\nLos numeros son consecutivos\n");
        } else {
            printf("\nLos numeros no son consecutivos\n");
        }
        printf("Ingrese tres numeros enteros o * para finalizar el programa\n");
    }

    return 0;
}
```
