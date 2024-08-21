# Enunciado

El siguiente programa lee un arreglo y lo modifica eliminando el elemento de la posición central. Se sabe
que se han cometido algunos errores en los parámetros y punteros (direcciones de). Corregirlo para que
funcione como se espera

```c
#include <stdio.h>
void leevector(int a[], int *dn);
void elimina_central(int a, int n);
void escvector(int n[], int a);
int main(void) { /* programa principal */
    int n;
    int a[20];
    leevector(&a, &n);
    elimina_central(a, *n);
    escvector(a[20], &n);
    return 0;
}
void leevector(int a[], int *dn) {
    int i;
    printf("Ingrese la cantidad de elementos del vector<=100: ");
    scanf("%d", *dn);
    for(i=0; i<*dn; i++) {
        printf("Ingrese el elemento %d: ", i+1);
        scanf("%d", a[i]);
     }
}
void elimina_central (int a, int n) {
    int i;
    for(i = (n + 1) / 2; i < n-1; i++)
        a[i] = a[i+1];
    n--;
}
void escvector(int n[], int a) {
    int i = 0;
    for( ; i < a; i++)
        printf("%d ", n[i]);
}
```

## Solución

```c
#include <stdio.h>
void leevector(int a[], int *dn);
void elimina_central(int a[], int n);
void escvector(int n[], int a);

int main(void) { /* programa principal */
  int n;
  int a[20];
  leevector(a, &n);
  elimina_central(a, n);
  escvector(a, n);
  return 0;
}
void leevector(int a[], int *dn) {
  int i;
  printf("Ingrese la cantidad de elementos del vector<=100: ");
  scanf("%d", dn);
  for (i = 0; i < *dn; i++) {
    printf("Ingrese el elemento %d: ", i + 1);
    scanf("%d", &a[i]);
  }
}
void elimina_central(int a[], int n) {
  int i;
  for (i = (n + 1) / 2; i < n - 1; i++)
    a[i] = a[i + 1];
  n--;
}
void escvector(int n[], int a) {
  int i = 0;
  for (; i < a; i++)
    printf("%d ", n[i]);
}
```
