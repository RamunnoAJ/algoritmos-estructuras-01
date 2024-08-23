#include <stdio.h>
#define FILAS 3
#define COLUMNAS 5

void leerDatos(int numeros[FILAS][COLUMNAS], int *n, int *m);
void imprimirDatos(int numeros[FILAS][COLUMNAS], int n, int m);
float calcularPromedio(int numeros[FILAS][COLUMNAS], int n, int m);

int main() {
  int matNumeros[FILAS][COLUMNAS];
  int n, m, i, j;

  leerDatos(matNumeros, &n, &m);
  imprimirDatos(matNumeros, n, m);

  for (i = 0; i < n; i++) {
    printf("El promedio de la fila %d es: %.2f\n", i,
           calcularPromedio(matNumeros, i, m));
  }

  return 0;
}

void leerDatos(int numeros[FILAS][COLUMNAS], int *n, int *m) {
  int i, j;
  FILE *fp;
  fp = fopen("numeros.txt", "r");
  for (i = 0; i < FILAS; i++) {
    for (j = 0; j < COLUMNAS; j++) {
      fscanf(fp, "%d", &numeros[i][j]);
    }
  }

  *n = i;
  *m = j;
}

void imprimirDatos(int numeros[FILAS][COLUMNAS], int n, int m) {
  int i, j;

  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      printf("%d ", numeros[i][j]);
    }
    printf("\n");
  }
}

float calcularPromedio(int numeros[FILAS][COLUMNAS], int n, int m) {
  int j, suma, contador;

  contador = 0;
  for (j = 0; j < m; j++) {
    suma += numeros[n][j];
    contador++;
  }

  return (float)suma / contador;
}
