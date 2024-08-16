# Enunciado

En el parador Honolulu se dan cursos de windsurf, el importe a abonar por los mismos se calcula de la siguiente forma: 
El costo por cada clase es

- $30 hasta 5 clases
- $25 hasta 12 clases
- $18 más de 12 clases
- Si no dispone de equipo propio debe agregar $5 por cada clase
- Los clientes del parador con tarjeta VIP tienen un descuento del 15% sobre el total.

Determine los datos que debe ingresar

## Solución
```c
#include <stdio.h>
#include <ctype.h>
float calcularImporte(float imp, char fPago);

int main() {
    float importe;
    char tipoPago;

    printf("\nIngrese su método de pago ([C]redito, [D]ebito, [E]fectivo): ");
    scanf("%c", &tipoPago);

    printf("Ingrese el importe: ");
    scanf("%f", &importe);

    tipoPago = toupper(tipoPago);
    printf("\nEl importe final es %10.2f", calcularImporte(importe, tipoPago));

    return 0;
}

float calcularImporte(float imp, char fPago) {
    switch(fPago) {
    case 'C':
        return imp * 1.07;
    case 'D':
        return imp * 1.05;
    case 'E':
        return imp * 0.9;
    default:
        return imp;
    }
}
```
