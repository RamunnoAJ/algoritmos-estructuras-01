#include "tdapila.h"
#include <stdio.h>

int main() {
  char caracter;
  TPILA pila;

  iniciap(&pila);
  scanf("%c", &caracter);
  while (caracter != '*') {
    ponep(&pila, caracter);
    scanf("%c", &caracter);
  }

  while (!vaciap(pila)) {
    sacap(&pila, &caracter);
    printf("%c", caracter);
  }
  printf("\n");

  return 0;
}
