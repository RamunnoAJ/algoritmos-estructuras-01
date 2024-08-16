# Enunciado

Realizar un algoritmo que permita calcular el volumen de un cilindro. Se ingresarán por teclado la altura y el radio del cilindro.

## Solución

```c
#include <stdio.h>
#include <math.h>
#ifndef MPI
#define MPI 3.14159265358979323846
#endif
float calcularVolumen(float a, float r);

int main() {
    float altura, radio;
    printf("Ingrese la altura del cilindro: ");
    scanf("%f", &altura);
    printf("\nIngrese el radio del cilindro: ");
    scanf("%f", &radio);

    printf("\nEl volumen del cilindro es %10.2f", calcularVolumen(altura, radio));

    return 0;
}

float calcularVolumen(float a, float r){
    return MPI * a * r * r;
}
```
