# Enunciado

Leer un conjunto de números enteros, la presencia de ceros intermedios indican fin de un subconjunto y comienzo del siguiente (el fin de datos está indicado con dos ceros consecutivos). 
Se pide calcular e informar: total de números para cada subconjunto y orden del conjunto más numeroso. 
Ejemplo : 8, 9, 0, 7, 2, 7, 4, 0, 5, 6, 1, 0, 0 Respuesta: Subconjunto Cantidad 1 2 2 4 3 3 Subconjunto con más elementos 2.

## Solución

```c
#include <stdio.h>

int main() {
    int n, i, contSub, max, maxSub;
    FILE *fp;
    fp = fopen("numeros.txt", "r");
    i = 0;
    max = -999;

    fscanf(fp, "%d", &n);
    while(n != 0) {
        contSub = 0;
        while(n != 0){
            contSub++;
            fscanf(fp, "%d", &n);
        }
        i++;

        if (contSub > max) {
            max = contSub;
            maxSub = i;
        }

        printf("Para el conjunto %d hay %d elementos\n", i, contSub);
        fscanf(fp, "%d", &n);
    }

    printf("Subconjunto con mas elementos es: %d", maxSub);
    fclose(fp);
    return 0;
}
```
