# Enunciado

A partir del peso inicial y final que registró una persona en un tratamiento para adelgazar, calcular e informar el porcentaje que perdió con respecto al peso inicial.

## Solución

```c
#include <stdio.h>
float calcularPerdida(int pI, int pF);

int main() {
    float pesoInicial, pesoFinal, porcentajePerdido, perdida;

    printf("Ingrese su peso inicial: ");
    scanf("%f", &pesoInicial);

    printf("\nIngrese su peso final: ");
    scanf("%f", &pesoFinal);

    printf("\nEl porcentaje de peso que perdio es %10.2f", calcularPerdida(pesoInicial, pesoFinal));

    return 0;
}

float calcularPerdida(int pI, int pF){
    float perdida;
    perdida = pI - pF;
    return (perdida * 100) / pI;
}
```
