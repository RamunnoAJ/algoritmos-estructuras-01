#include <stdio.h>

typedef struct Fila {
  int indice;
  int columnas[20];
  int suma;

} Fila;

int leerDatos();

int main() {
  int error = leerDatos();
  if (error) {
    return 1;
  }

  return 0;
}

int leerDatos() {
  FILE *fp;
  fp = fopen("deeznuts.txt", "r");

  if (fp == NULL) {
    printf("No se pudo abrir el archivo\n");
    return 1;
  }

  return 0;
}
