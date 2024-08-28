#define MAX 20

typedef struct {
  int fila;
  int columna;
  int valor;
} Componente;

int main() {}

void generarArreglo(int mat[][MAX], int n, int m, Componente vec[], int *k) {
  int i, j;
  *k = 0;
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++) {
      if (mat[i][j] % (n + m)) {
        vec[*k].fila = i;
        vec[*k].columna = j;
        vec[*k].valor = mat[i][j];
        (*k)++;
      }
    }
  }
}

// Desarrollar una función que a partir de una matriz de NxM elementos enteros,
// devuelva en un arreglo de structs, fila, columna y valor de las componentes
// de la matriz divisibles por N + M
