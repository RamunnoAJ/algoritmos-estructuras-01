# Enunciado

Leer M números y para cada uno calcular e informar el factorial mediante una función entera.

## Solución

```c
#include <stdio.h>
int calcularFactorial(int n);

int main() {
    int n;
    printf("Ingrese un numero para calcular su factorial: ");
    scanf("%d", &n);
    printf("\nEl factorial de %d es %d", n, calcularFactorial(n));

    return 0;
}

int calcularFactorial(int n) {
    int acum;
    acum = 1;

    if (n == 0) {
        return 1;
    } else {
        for (int i = n; i >= 1; i--){
            acum = acum * i;
        }

        return acum;
    }
}

```
